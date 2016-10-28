// packet.cpp
//	SINS Distributed under GPL

#include <sys/param.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/poll.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

#ifdef	__FreeBSD__
#include <sys/time.h>
#include <net/bpf.h>
#include <netinet/in_systm.h>   
#include <net/if.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <netinet/ip.h>  
#include <netinet/udp.h>
#include <arpa/inet.h>
#else
#include <net/if.h>
#include <net/if_packet.h>
#include <netinet/if_ether.h>
#include <netinet/in.h>
#include <netinet/ip.h>  
#include <netinet/udp.h>
#include <arpa/inet.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <netdb.h>
#include <string.h>

#include <qtimer.h>
#include <qdatetime.h>
#include "packet.h"
#include "opcodes.h"
//#include "player.h"
#include "util.h"
#include "main.h"
#include "preferences.h"
#include "vpacket.h"

// packet notes:
//	i wanted to write down some notes about packets here so that i wouldn't
//	have to derive them every time --
//	packets from the server have something of the following format:
//	<14 bytes>	ethernet header -- defined in if_ether.h
//		6 bytes src, 6 bytes dst, 2 bytes type
//
//	<12 bytes + 2 addrs of 4 bytes = 20 bytes> ip header - defined in ip.h
//
//	<8 bytes> udp header - defined in udp.h
//
//		42 bytes of header information
//
//	<8 bytes>
//		internal UDP state?  the last 3 words seem to get incremented with each
//		packet from the server, with some missing
//
//	<4 bytes>
//		opcode and version
//
// if you're looking at tcpdump output, it doesn't print the ethernet headers
// if you're looking at global.log, it doesn't print the ethernet headers, the
//	ip headers, or the udp headers, but it does print the 8 bytes between the
//	udp headers and the start of the instruction/opcode



#define IP_ADDRESS_TYPE   11   // these were chosen arbitrarily
#define MAC_ADDRESS_TYPE  12

// packet version is a unique number that should be bumped every time packet 
// structure (ie. encryption) changes.  It is checked by the VPacket feature
// (currently the date of the last packet structure change)
#define PACKETVERSION  40100
#define PKTBUF_LEN	65535

// 0x2d20, 0x6121, 0x4921
bool isEncryptedOpCode( unsigned long opcode )
{
	return (( opcode == CODE_CHAR_PROFILE ) || ( opcode == CODE_ZONE_SPAWNS ) || ( opcode == CODE_NEW_SPAWN ));
}

#if HAVE_LIBEQ
extern "C"
{
	// function to determine the zone key given a spawn and player packet
	UDWORD FindKey( unsigned char* player, int plen, unsigned char* spawn, int slen );

	// function to decrypt the packet given a pre-determined key
	int ProcessPacket( unsigned char* data, int* len, UDWORD* key, const char* cli,
		unsigned char* player = NULL, int plen = 0);

	// function to decrypt a spawn packet given a pre-determined key
	void DecodeSpawn( unsigned char* spawn, int slen, UDWORD key );
}
#endif



DecryptThread::DecryptThread( EQPacket* pack ):
	QThread()
{
	m_packet = pack;
}

void DecryptThread::run()
{
	m_packet->locateKey();
}



PacketCaptureThread::PacketCaptureThread( EQPacket* packet,
	const char* device,
	const char* hostname,
	int address_type )
{
	struct bpf_program	bpp;
	char				buff[ 4096 ];

	m_packet = packet;
	
	if ( address_type == MAC_ADDRESS_TYPE )
		printf( "Opening packet capture on device %s, MAC host %s\n", device, hostname );
	else if ( address_type == IP_ADDRESS_TYPE )
		printf( "Opening packet capture on device %s, IP host %s\n", device, hostname );
	else
	{
		fprintf( stderr, "Internal error: strange address_type value (%d)\n", address_type );
		this->exit();
	}

	m_pcache_pcap = pcap_open_live( (char*) device, 1500, true, 0, buff );

#ifdef __FreeBSD__
	// if we're on FreeBSD, we need to call ioctl on the file descriptor
	// with BIOCIMMEDIATE to get the kernel Berkeley Packet Filter device
	// to return packets to us immediately, rather than holding them in
	// it's internal buffer... if we don't do this, we end up getting 32K
	// worth of packets all at once, at long intervals -- if someone
	// knows a less hacky way of doing this, I'd love to hear about it.
	// the problem here is that libpcap doesn't expose an API to do this
	// in any way
	int fd = *((int*)m_pcache_pcap);
	int temp = 1;
	if ( ioctl( fd, BIOCIMMEDIATE, &temp ) < 0 )
		fprintf( stderr, "PCAP couldn't set immediate mode on BSD\n" );
#endif

	if ( !m_pcache_pcap )
	{
		fprintf( stderr, "PCAP failed to open device %s  %s\n", device, buff );
		this->exit();
	}

	// the string buffer "pcapStr" is the rule compiled by pcap_compile to tell
	// pcap how to select packets.  the documentation on filters supplied
	// with pcap is awful, however tcpdump uses the same pcap interface and
	// its filters are well documented. cpphack
	if ( address_type == MAC_ADDRESS_TYPE )
		// new MAC-based filtering.  MAC must be in 00:00:00:00:00:00 format.
		// had to use address_type since this module has no access to the 
		// showeq_params structure.  cpphack
		sprintf( buff, "udp[0:2] > 1024 and udp[2:2] > 1024 and ether host %s", hostname );
	else
		// modified to auto-detect IP.  listen for udp dest port 9000 to detect
		// an active EQ session address.  not perfect, but pretty solid.  may
		// get false positives if some other prog is talking to port 9000.
		sprintf( buff, "udp[2:2] = 9000 or (udp[0:2] > 1024 and udp[2:2] > 1024 and host %s)", hostname );

	// may need to be copied...
	if ( pcap_compile( m_pcache_pcap, &bpp, buff, 1, 0 ) == -1 )
	{
		// filter fail
		fprintf( stderr, "PCAP failed to compile filter for device %s: %s\n", device, pcap_geterr( m_pcache_pcap ) );
		this->exit();
	}

	if ( pcap_setfilter( m_pcache_pcap, &bpp) == -1 )
	{
		fprintf( stderr, "PCAP failed to apply filter on device %s: %s\n", device, pcap_geterr( m_pcache_pcap ) );
		this->exit();
	}

	// we're alive
}

void PacketCaptureThread::refilter( const char* device,
	const char* /*hostname*/,
	int /*address_type*/,
	unsigned long serverPort )
{
	struct bpf_program	bpp;
	char				buff[ 2048 ];

	sprintf( buff, "udp[0:2] = 9000 or udp[0:2] = %ld or udp[2:2] = %ld", serverPort, serverPort );
	
	// may need to be copied... dunno
	if ( pcap_compile( m_pcache_pcap, &bpp, buff, 1, 0 ) == -1 )
	{
		// filter fail
		fprintf( stderr, "PCAP failed to compile filter for device %s: %s\n", device, pcap_geterr( m_pcache_pcap ) );
		this->exit();
	}

	if ( pcap_setfilter( m_pcache_pcap, &bpp ) == -1 )
	{
		fprintf( stderr, "PCAP failed to apply filter on device %s: %s\n", device, pcap_geterr( m_pcache_pcap ) );
		this->exit();
	}
}

void PacketCaptureThread::clear()
{
	m_packetCaptureMutex.lock();
	m_packetCache.clear();
	m_packetCaptureMutex.unlock();
}

// callback to put a packet on the back of the packet cache
// doesn't check for malloc failure
void PacketCaptureThread::packetCallback( const struct pcap_pkthdr* ph, const u_char* data )
{
#ifdef DEBUG
//	printf( "EQPacketCallback()\n" );
#endif

	EQPktRec*	pc;
	
	pc = (EQPktRec*)malloc( sizeof( EQPktRec ) + ph->len );
	pc->len = ph->len;
	memcpy( pc->data, data, ph->len );

	m_packetCaptureMutex.lock();

	m_packetCache.enqueue( pc );
	
	m_packetCaptureMutex.unlock();
}

// sucks a packet off the front of the packet cache
// if we have one, return length of packet, otherwise, 0
EQPktRec* PacketCaptureThread::getPacket()
{
#ifdef DEBUG
//	printf( "EQPacketGetPacket()\n" );
#endif
	EQPktRec*		pc = NULL;

	m_packetCaptureMutex.lock();

	pc = m_packetCache.dequeue();
	
	m_packetCaptureMutex.unlock();

	return pc;
}

void __callbackStub( u_char* param, const struct pcap_pkthdr* ph, const u_char* data )
{
	PacketCaptureThread*	me = (PacketCaptureThread*)param;
	me->packetCallback( ph, data );
}

void PacketCaptureThread::run()
{
	// loop until a packet arrives, -1 ensures we don't return until
	// something happens, and then we'll call packetCallback, and just
	// go right back to waiting
	pcap_loop( m_pcache_pcap, -1, __callbackStub, (u_char*)this );
}



// this is the 'central' loop for the application... basically, EQPacket
// creates a separate thread (check pcap.c) to read and store packets from
// the network that match our 'profile' as EQ packets
// it also creates a timer to check for stored packets from that thread,
// and attempts to process, decode, and handle them
// the call chain is something like:
// <timer object>
//     |--> processPacket
//             |--> decodePacket
//                     |--> logPacket
//                     |--> dispatchOpCode
//                             |--> decryptPacket
//                             |--> handle<opCode>
//
// the packet capture (pcap) side of things simply detaches a thread and
// blocks until a packet arrives, appends it to the packet queue, and blocks
// again... that queue grows until we handle the packets in the application loop.
// we get the packets from the packet capture code by calling EQPacketGetPacket.
// EQPacketGetPacket will return a non-zero value representing the size of the
// packet when it has something for us.


// EQPacket class - sets up packet capturing
EQPacket::EQPacket( const char* name ):
	QObject( NULL, name )
{
#ifdef DEBUG
//	debug( "EQPacket::EQPacket()" );
#endif
	m_autoFindSession = false;
	m_userResync = false;

	QString		ip = gSEQPrefs->getPrefString( "IP", "Network", "127.0.0.1" );
	QString		device = gSEQPrefs->getPrefString( "Device", "Network", "eth0" );
	QString		mac = gSEQPrefs->getPrefString( "MAC", "Network", "0" );
	
	// substitute "special" IP which is interpreted in pcap.c
	// to set up a different filter for picking up new sessions
	ip = ip.upper();
	
	if ( ip == "AUTO" || ip == "127.0.0.1" )
	{
		printf( "Setting auto-find mode\n" );
		m_autoFindSession = true;
		m_client_addr = 0;
		if ( ip == "AUTO" )
			ip = "127.0.0.1";
	}
	else
	{
		struct in_addr			ia;

		if ( inet_aton( ip, &ia ) == 0 )		// invalid
		{
			struct hostent*		he;
			// assume it's a hostname and try to get it's address
			he = gethostbyname( ip );
			if ( !he )
			{
				printf( "Invalid address: %s\n", (const char*)ip );
				exit( 1 );
			}
			memcpy( &ia, he->h_addr_list[ 0 ], he->h_length );
		}

		m_client_addr = ia.s_addr;
		ip = inet_ntoa( ia );
		printf( "Setting address: %s\n", (const char*)ip );
	}

	gSEQPrefs->setPrefString( "IP", "Network", ip, false );		// don't save

	m_playbackPackets = gSEQPrefs->getPrefBool( "Playback", "VPacket", false );
	m_recordPackets = !m_playbackPackets && gSEQPrefs->getPrefBool( "Record", "VPacket", false );
		
	// important stuff below: this creates the pcap filter thread which
	// collects packets to deliver to us -- it establishes it's own thread
	// and stipulates it's own callback, putting packets in it's cache
	// as they come in for us to read off
	// if you look further down in this routine, you'll see where we
	// create our own timer to look for these packets periodically and
	// read them in (m_timer)
	if ( !m_playbackPackets )
	{
		QString		devtype;
		int			addtype;
		
		if ( mac.length()== 17 )
		{
			devtype = mac;
			addtype = MAC_ADDRESS_TYPE;
		}
		else
		{
			devtype = ip;
			addtype = IP_ADDRESS_TYPE;
		}
		m_packetCaptureThread = new PacketCaptureThread( this, device, devtype, addtype );		    
		m_packetCaptureThread->start();
	}

	m_busyDecoding = false;

	m_insideZone = false;
	
	serverSeqExp = 0;
	serverSeqClear = true;
	serverCacheCount = 0;


	// our key is unknown
	m_decodeKey = 0;

	// we're not locating keys
	m_decryptActive = false;
	m_decryptThread = NULL;
	m_cancelDecrypt = false;
	
	// important: here is where we create the timer to read packets as the
	// pcap thread caches them... processPackets looks for packets on the
	// packet cache held by the pcap thread and tries to process them...
	m_timer = new QTimer( this );
	connect( m_timer, SIGNAL( timeout() ), this, SLOT( processPackets() ) );

	// setup VPacket
	m_pVPacket = NULL;

	// first param to VPacket is the filename
	// second param is playback speed:  0 = fast as poss, 1 = 1X, 2 = 2X etc
	if ( gSEQPrefs->isPreference( "Filename", "VPacket" ) )
	{
		const char*		filename = gSEQPrefs->getPrefString( "Filename", "VPacket" );

		bool			flush = gSEQPrefs->getPrefBool( "FlushPackets", "VPacket", false );
		int				speed = gSEQPrefs->getPrefInt( "PlaybackRate", "VPacket", 0 );
		int				compress = gSEQPrefs->getPrefInt( "CompressTime", "VPacket", 0 );
		
		if ( m_recordPackets )
		{
			m_pVPacket = new VPacket( filename, 1, true );
			// must appear before next call to getPrefString, which uses a static string
			printf( "Recording packets to '%s' for future playback\n", filename );
			if ( flush )
				m_pVPacket->setFlushPacket( true );
		}
		else if ( m_playbackPackets )
		{
			m_pVPacket = new VPacket( filename, 1, false );
			m_pVPacket->setCompressTime( compress );
			m_pVPacket->setPlaybackSpeed( speed );
			printf( "Playing back packets from '%s' at speed '%d'\n", filename, speed );
		}
	}
	else
	{
		gSEQPrefs->setPrefBool( "Record", "VPacket", false, false );
		m_recordPackets = false;
		gSEQPrefs->setPrefBool( "Playback", "VPacket", false, false );
		m_playbackPackets = false;
	}

	m_nPacket = 0;
}

void EQPacket::resetDecryptor()
{
#ifdef DEBUG
//	debug( "EQPacket::resetDecryptor()" );
#endif

	// kill our decryption thread if active
	if ( m_decryptActive )
	{
		// request cancellation and wait for it if successful
		m_cancelDecrypt = true;
		m_decryptThread->wait();

		// unlock our mutex (in case thread left it locked)
		m_queueMutex.unlock();
	}

	m_cancelDecrypt = false;
	
	// NOTE: since we know the decryption thread is not running and since we are
	//       the main thread, we don't need to use the mutex to clear the queues

	m_playerProfiles.clear();
	m_zoneSpawns.clear();
	m_spawns.clear();

	// set our key to zero
	m_decodeKey = 0;

	// let anyone interested know we changed it
	// emit keyChanged();

	// we're no longer looking
	m_decryptActive = false;
}

// this gets called from our decryption thread and takes a stab at trying
//	to decrypt, using the queued up encrypted packets from
//	server, if we succeed, we proceed to "foundKey"
void EQPacket::locateKey()
{
#ifdef DEBUG
//	debug( "EQPacket::locateKey()" );
#endif

	EQPktRec*			player;
	EQPktRec*			spawn;

	// grab our player packet
	player = m_playerProfiles.first();

#if HAVE_LIBEQ
	// find a shiny new key
	// we use any "new spawn" that we've gotten since zone to brute force the key
	//	(nb: I'm not sure what "player" is used for inside FindKey or whether it's
	//	used at all)
	spawn = m_spawns.first();
	
	while ( !m_decodeKey && spawn && !m_cancelDecrypt )
	{
		m_decodeKey = FindKey( player->data, player->len, spawn->data, spawn->len );
		spawn = m_spawns.next();
	}
#else
	m_decodeKey = 0;
#endif

	// bail if we didn't find a key at all
	if ( !m_decodeKey )
		m_decryptActive = false;
}

// this function unrolls the queued up packets that we're saving,
//	and sends them to anyone listening to the "backfill" signals
void EQPacket::foundKey()
{
#ifdef DEBUG
//	debug( "EQPacket::foundKey()" );
#endif

	unsigned int				j;
	EQPktRec*					pkt;
	struct playerProfileStruct*	pdata;
	struct zoneSpawnsStruct*	zdata;
	struct addSpawnStruct*		ndata;
	struct spawnStruct*			sdata;

#if !HAVE_LIBEQ
	printf( "BUG: libEQ not present, returning from FoundKey()\n" );
	return;
#endif

	// lock our mutex
	m_queueMutex.lock();

	// decode our player packet queue
	pkt = m_playerProfiles.first();
	while ( pkt )
	{
#if HAVE_LIBEQ
		// ick, too bad our interface to libEQ.a is written with indeterminate types
		// like "int"
		if ( ProcessPacket( pkt->data, (int*)&pkt->len, &m_decodeKey, "" ) )
		{
			pdata = (struct playerProfileStruct*)pkt->data;
			emit backfillPlayer( pdata );
		}
		else
#endif
			printf( "Warning: Failed to decrypt queued Player Profile packet.\n" );
		pkt = m_playerProfiles.next();		
	}
	m_playerProfiles.clear();

	// decode our zone spawns packet queue
	pkt = m_zoneSpawns.first();
	while ( pkt )
	{
#if HAVE_LIBEQ
		if ( ProcessPacket( pkt->data, (int*)&pkt->len, &m_decodeKey, "" ) )
		{
			zdata = (struct zoneSpawnsStruct*)pkt->data;
			for ( j = 0; j < ( pkt->len - 2 ) / sizeof( struct spawnStruct ); j++ )
			{
				sdata = (struct spawnStruct*)&zdata->spawn[ j ];
				emit backfillSpawn( sdata );
			}
		}
		else
#endif
			printf( "Warning: Failed to decrypt queued Zone Spawns packet.\n" );
		pkt = m_zoneSpawns.next();
	}
	m_zoneSpawns.clear();


	// decode our spawns packet queue
	pkt = m_spawns.first();
#if HAVE_LIBEQ
	while ( pkt )
	{
		DecodeSpawn( pkt->data, pkt->len, m_decodeKey );
		ndata = (struct addSpawnStruct*)pkt->data;
		sdata = (struct spawnStruct*)( &ndata->spawn );

		emit backfillSpawn( sdata );
		pkt = m_spawns.next();
	}
#endif
	m_spawns.clear();

	// unlock our mutex
	m_queueMutex.unlock();

	// let them know we're done
	m_decryptActive = false;

	// pass on the good news!
	printf( "FOUND KEY: 0x%08lx\n", m_decodeKey );
	emit keyFound();
	
	return;
}

// gets called from "dispatchOpCode", in the central timer loop
//	this function will attempt to decrypt the packet by calling
//	"ProcessPacket", which fails when the key is wrong
//	if we fail, and the packet is one of the encrypted opcode types,
//	it is queued up for decryption later
//	if there are any queued up packets on the queues of encrypted
//	packets, then we fork off the thread to decrypt them if it's
//	not already active
int EQPacket::decryptPacket( unsigned char* data, int* len, const char* cli )
{
#ifdef DEBUG
//	debug( "EQPacket::decryptPacket()" );
#endif

	unsigned long			opcode;
	EQPktRec*				player = NULL;
	EQPktRec*				pktrec = NULL;
	int						result;
	UDWORD					prevKey;	

	// get the opcode of the current packet
	opcode = data[ 1 ] | (data[ 0 ] << 8 );

	// skip if its not an encrypted packet
	if ( !isEncryptedOpCode( opcode ) )
		return 0;

	// grab our player packet
	player = m_playerProfiles.first();

	// lock our mutex so the queues can't unwind before this packet is in
	// nb: we only need to lock when the queue's are being used
	if ( m_decryptActive )
		m_queueMutex.lock();
 
	prevKey = m_decodeKey;

	// try processing the packet first
#if HAVE_LIBEQ
	if ( player )
		result = ProcessPacket( data, len, &m_decodeKey, cli, player->data, player->len );
	else
		result = ProcessPacket( data, len, &m_decodeKey, cli );
#else
	result = 0;
#endif

	if ( result )
	{
		if ( m_decryptActive )
			m_queueMutex.unlock();
		// check to see if we found a key
		if ( prevKey != m_decodeKey )
			this->foundKey();
		return result;
	}

	// queue it up...  allocate storage for our encrypted packet
	if ( ( opcode == CODE_CHAR_PROFILE ) || ( opcode == CODE_ZONE_SPAWNS ) )
		pktrec = (EQPktRec*)malloc( sizeof( EQPktRec ) + PKTBUF_LEN );
	else if ( opcode == CODE_NEW_SPAWN )
		pktrec = (EQPktRec*)malloc( sizeof( EQPktRec ) + *len );

	// bail if we can't get memory...
	if ( !pktrec )
	{
		printf( "Warning: Couldn't allocate memory to queue encrypted packet.\n" );
		// release our mutex
		if ( m_decryptActive )
			m_queueMutex.unlock();
		return result;
	}

	// grab the packet info
	pktrec->len = *len;
	memcpy( pktrec->data, data, *len );

	// queue the packet
	switch ( opcode )
	{
		case CODE_CHAR_PROFILE:
			m_playerProfiles.append( pktrec );
		break;

		case CODE_ZONE_SPAWNS:
			m_zoneSpawns.append( pktrec );
		break;

		case CODE_NEW_SPAWN:
			m_spawns.append( pktrec );
		break;
	}

	// release the mutex and return if the decryption thread is already running
	if ( m_decryptActive )
	{
		m_queueMutex.unlock();
		return result;
	}

	// start the decryption thread if we have player/spawn packets available
	else 
	{
		if ( m_spawns.count() )
		{
			if ( !m_decryptThread )
				m_decryptThread = new DecryptThread( this );
			m_decryptThread->start();
			m_decryptActive = true;
		}
	}

	return result;
}

// start the timer to process packets
void EQPacket::start( int delay )
{
#ifdef DEBUG
//	debug( "EQPacket::start()" );
#endif
	m_timer->start( delay, false );
}

// stop the timer to process packet
void EQPacket::stop()
{
#ifdef DEBUG
//	debug( "EQPacket::stop()" );
#endif
	m_timer->stop();
}

// reads packets and processes waiting packets
void EQPacket::processPackets()
{
#ifdef DEBUG
//	debug( "EQPacket::processPackets()" );
#endif
	// make sure we are not called while already busy
	if ( m_busyDecoding )
		return;
		
	// set flag that we are busy decoding
	m_busyDecoding = true;

	EQPktRec*				packet = NULL;
	int						size;

	// if in packet playback mode fetch packets from VPacket class
	if ( m_playbackPackets )
	{
		time_t			now;
		QTime			time;
		int				i = 0;
		unsigned char	buffer[ 4096 ];
		
		long version = PACKETVERSION;

		time.start();
		// decode packets from the playback buffer, for 100 milliseconds
		do 
		{
			size = m_pVPacket->playback( (char*)buffer, sizeof( buffer ), &now, &version );
			if ( size )
			{
				i++;
				if ( PACKETVERSION == version )
					this->decodePacket( buffer + sizeof( struct ether_header ) );
				else
				{
					fprintf( stderr, "Error:  The version of the packet stream has " \
								"changed since '%s' was recorded - disabling playback\n", 
								(const char*)gSEQPrefs->getPrefString( "Filename", "VPacket" ) );
					gSEQPrefs->setPrefBool( "Playback", "VPacket", false, false );
					m_playbackPackets = false;
					break;
				}

			}
			else
				break;
		} while ( time.elapsed() < 100 );
	}

	// otherwise fetch them from pcap
	else
	{
		int loopCount = 0;
		int resync_max = gSEQPrefs->getPrefBool( "AutoResync", "Network", 0 );

		if ( !resync_max )
			resync_max = 100000;

		while ( ( packet = m_packetCaptureThread->getPacket() ) && loopCount < resync_max )
		{
			loopCount++;

			// get pointer to MAC layer header
			unsigned char*			buffer = packet->data;
			size = packet->len;
			
			struct ether_header*	ep = (struct ether_header*)buffer;

			// if its not an IP packet, discard the packet
			if ( !( ntohs( ep->ether_type) == ETHERTYPE_IP ) )
				continue;

			// now... we know the rest is an IP udp packet concerning the
			// host in question, because pcap takes care of that
			// we assume its an everquest packet

			// send the packet onto the recorder with the appropriate timestamp
			if ( m_recordPackets )
				m_pVPacket->record( (const char*)buffer, size, time( NULL ), PACKETVERSION );

			// send the packet onto the decoder once we have one
			this->decodePacket( buffer + sizeof( struct ether_header ) );
			
			if ( loopCount > resync_max )
			{
				loopCount = resync_max;
				m_packetCaptureThread->clear();
			}

			free( packet );
		}
	} 
	// clear decoding flag
	m_busyDecoding = false;
}

void EQPacket::__stripAck( u_char*& data, int& len )
{
	// check if the packet contains embedded ack information 
	// and strip it out of exists 
	if ( data[ 1 ] == 0x04 || data[ 1 ] == 0x08 )
	{				
		// if offset 1 is 4, then its got ack info
		// strip out ack by shifting packet over ack info
		data[ 5 ] = data[ 3 ];	data[ 4 ] = data[ 2 ];
		data[ 3 ] = 0x00;		data[ 2 ] = data[ 0 ];
		data += 2;	len -= 2;
	}
	else if ( data[ 1 ] == 0x14 || data[ 1 ] == 0x18 )
	{
		// strip out ack
		data[ 6 ] = data[ 3 ];	data[ 5 ] = data[ 2 ];
		data[ 4 ] = 0x00;		data[ 3 ] = data[ 0 ];
		data += 3;	len -= 3;
	}
	else if ( data[ 1 ] == 0x24 )
	{
		data[ 7 ] = data[ 3 ];	data[ 6 ] = data[ 2 ];
		data[ 5 ] = 0x00;		data[ 4 ] = data[ 0 ];
		data += 4;	len -= 4;
	}
	else if ( data[ 1 ] == 0x34 )
	{
		data[ 8 ] = data[ 3 ];	data[ 7 ] = data[ 2 ];
		data[ 6 ] = 0x00;		data[ 5 ] = data[ 0 ];
		data += 5;	len -= 5;
	}
	else if ( data[ 1 ] == 0x44 )
	{
		data[ 9 ] = data[ 3 ];	data[ 8 ] = data[ 2 ];
		data[ 7 ] = 0x00;		data[ 6 ] = data[ 0 ];
		data += 6;	len -= 6;
	}
	else if ( data[ 1 ] == 0x64 )
	{
		data[ 5 ] = data[ 3 ];	data[ 6 ] = data[ 2 ];
		data[ 7 ] = 0x00;		data[ 8 ] = data[ 0 ];
		data += 8;	len -= 8;
	}
	else if ( data[ 1 ] == 0x74 )
	{
		data[ 12 ] = data[ 3 ];	data[ 11 ] = data[ 2 ];
		data[ 10 ] = 0x00;		data[ 9 ] = data[ 0 ];
		data += 9;	len -= 9;
	}
	else if ( data[ 1 ] == 0x02 )
		data[ 1 ] = 0;
}

// this function decides the fate of the Everquest packet
// and dispatches it to the correct packet handling function
//	buffer here already points past the end of the ethernet headers,
//	to the start of the ip headers
void EQPacket::decodePacket( unsigned char* buffer )
{
#ifdef DEBUG
//	debug( "EQPacket::decodePacket()" );
#endif

	u_char*					data = (unsigned char*)buffer;
	struct ip*				ip = (struct ip*)buffer;

	struct udphdr*			udp;
	int						hlen, len;

	hlen = ip->ip_hl * 4;
	len = ntohs( ip->ip_len );
	len -= hlen;
	data += hlen;

	udp = (struct udphdr*)data;
	len -= sizeof( struct udphdr );
	data += sizeof( struct udphdr );

	emit numPacket( ++m_nPacket );
	emit handlePacket( data, len );
	
	// do a couple of checks on the packet
	// if the first byte of a packet is 0, then its a pure ack packet
	if ( !data[ 0 ] )
		return;
	
	unsigned long			destPort;
	unsigned long			srcPort;

#ifdef __FreeBSD__
	destPort = ntohs( udp->uh_dport );
	srcPort = ntohs( udp->uh_sport );
#else
	destPort = ntohs( udp->dest );
	srcPort = ntohs( udp->source );
#endif

	// chat server packet, throw it out
	if ( ( destPort == 9000 ) || ( destPort == 5999 ) || ( srcPort == 5999 ) )
		return;

	// is it a port 9000 packet? it's an EQ client address
	if ( srcPort == 9000 )
	{
		QString		ipStr = inet_ntoa( ip->ip_dst );
				
		EQSession*	session = m_sessions.find( ip->ip_dst.s_addr );
		if ( !session )
		{
			printf( "Detected port 9000 on %s\n", (const char*)ipStr );
			session = new EQSession( ip->ip_dst.s_addr );
			m_sessions.insert( ip->ip_dst.s_addr, session );
		}
		
		if ( m_autoFindSession )
		{
			gSEQPrefs->setPrefString( "IP", "Network", ipStr, false );
			m_client_addr = ip->ip_dst.s_addr;
			m_autoFindSession = false;
		}
		
		if ( data[ 0 ] == 0x12 && data[ 1 ] == 0x00 )
		{
			unsigned long	opcode = data[ 9 ] | ( data[ 8 ] << 8 );
			
			if ( opcode == 0x0480 )
			{
				unsigned long	serverPort = data[ 139 ] | ( data[ 138 ] << 8 );

				if ( m_client_addr == ip->ip_dst.s_addr )
				{
					printf( "Locking on to %s with new port %ld\n", (const char*)ipStr, serverPort );
					QString		device = gSEQPrefs->getPrefString( "Device", "Network", "eth0" );
				
					m_packetCaptureThread->refilter( device, ipStr, IP_ADDRESS_TYPE, serverPort );
					serverCacheCount = 0;
					emit captureTargetChanged( device, ipStr );
				}
			}
		}
		return;
	}

	// packet from client
	if ( ip->ip_src.s_addr == m_client_addr )
	{
		if ( data[ 0 ] == 0x10 )
		{
			// unacknowledged packet 
			// dispatch packet
			this->__stripAck( data, len );
			this->dispatchOpCode( len - 9, data + 5, FROM_CLIENT );
		}
		else if ( data[ 0 ] == 0x12 )
		{
			// unacknowledged packet
			// dispatch packet 
			this->__stripAck( data, len );
			this->dispatchOpCode( len - 12, data + 8, FROM_CLIENT );
		}
		return;
	}
	
	// packet from server
	this->__stripAck( data, len );

	// check if its an acknowledged or unacknowledged packet
	if ( data[ 0 ] == 0x10 )
	{
		// unacknowledged packet
		// packet coming from zone server
		// dispatch packet
		this->dispatchOpCode( len - 9, data + 5, FROM_SERVER );
		return;
	}
	else
	{
		unsigned int            serverSeq = data[ 5 ] | (data[ 4 ] << 8 );

		// assume this is an acknowledged packet
		// is this start of sequence and seq clear?
		if ( ( data[ 0 ] == 0x3a ) || ( data[ 0 ] == 0x32 ) || m_userResync )
		{
			m_userResync = false;
			serverSeqExp = serverSeq + 1;
			serverSeqExp %= 0x10000;
			serverSeqClear = 0;
			serverCacheCount = 0;
			emit packetReceived( serverCacheCount );
			if ( data[ 0 ] == 0x32 )
				this->dispatchOpCode( len - 12, data + 8, FROM_SERVER );
			else
				this->dispatchSplitOpCode( len, data );
		}

		else if ( ( !serverSeqClear ) && ( serverSeq >= serverSeqExp ) )
		{
			// need to fix this for wrap
			int	found = 0;
			// check if its in our cache already
			for ( int a = 0; a < serverCacheCount; a++ )
			{
				if ( serverCacheSeq[ a ] == serverSeq )
				found = a + 1;
			}
			if ( ( !found ) && ( serverCacheCount < MAXPACKETCACHECOUNT ) )
			{
				int t;
				// printf ("Packet not found in cache, adding %x(%d)\n", serverSeq,serverCacheCount);
				// a packet we need to put into the cache
				serverCacheLen[ serverCacheCount ] = len;
				serverCacheSeq[ serverCacheCount ] = serverSeq;
				for ( int a = 0; a < len; a++ )
					serverCachePkt[ serverCacheCount ][ a ] = data[ a ];
				serverCacheCount++;
				emit packetReceived( serverCacheCount );
				t = gSEQPrefs->getPrefInt( "AutoResync", "Network", false );
				if ( t > 0 && serverCacheCount > t )
				{
					m_userResync = true;
					printf( "Auto Resyncing the network\n" );
				}
				// printf ("Packet already in cache, not adding %x\n",serverSeq);
			}

			// run through our saved packets and try to find match
			bool	packetSent;
			do
			{
				packetSent = false;
				int				found = 0;
				for ( int a = 0; a < serverCacheCount; a++ )
				{
					if ( serverCacheSeq[ a ] == serverSeqExp )
						found = a + 1;
				}
				if ( found )
				{
					// dispatch the packet
					// printf ("Found packet in cache and removed, %x(%d)\n",serverCacheSeq[found-1], serverCacheCount-1);
					if (	( serverCachePkt[ found - 1 ][ 0 ] == 0x3a ) ||
							( serverCachePkt[ found - 1 ][ 0 ] == 0x1a ) ||
							( serverCachePkt[ found - 1 ][ 0 ] == 0x0a ) )
						this->dispatchSplitOpCode( serverCacheLen[ found - 1 ],
							serverCachePkt[ found - 1 ] );
					else
						this->dispatchOpCode( serverCacheLen[ found - 1 ] - 12,
							serverCachePkt[ found - 1 ] + 8,
							FROM_SERVER );
	
					serverSeqExp++;
					serverSeqExp %= 0x10000;

					//emit seqExpect( serverSeqExp );
					packetSent = true;
					// remove packet from cache
					if ( serverCacheCount > 1 )
					{
						serverCacheLen[ found - 1 ] = serverCacheLen[ serverCacheCount - 1 ];
						serverCacheSeq[ found - 1 ] = serverCacheSeq[ serverCacheCount - 1 ];
						for ( int a = 0; a < serverCacheLen[ serverCacheCount - 1 ]; a++)
							serverCachePkt[ found - 1 ][ a ] = serverCachePkt[ serverCacheCount - 1 ][ a ];
					}
					serverCacheCount--;
					emit packetReceived( serverCacheCount );
				}
			} while ( packetSent );
		}
	}
}

/*		unsigned int		serverSeq = data[ 5 ] | (data[ 4 ] << 8 );

		if ( serverCacheCount > 0 )
		{
			//printf( "SEQ: checking cache for %04x - cache count %04d\n", serverSeqExp, serverCacheCount );	
			// search the cache for our next packet
			for ( int a = 0; a < serverCacheCount; a++ )
			{
				if ( serverCacheSeq[ a ] == serverSeqExp )
				{
					//emit seqExpect (serverSeqExp);
					//printf( "SEQ: found %04x in cache - cache count %04d\n", serverSeqExp, serverCacheCount );
					serverSeqExp = serverSeq + 1;
					serverSeqExp %= 0x10000;
					this->dispatchSplitOpCode( serverCacheLen[ a ], serverCachePkt[ a ] );
					if ( ( serverCacheCount - 1 ) == a )
						serverCacheCount--;
				}
				if ( ( serverCachePkt[ a ][ 0 ] == 0x1a ) || ( serverCachePkt[ a ][ 0 ] == 0x3a ) && serverSeqClear )
				{
					//emit seqReceive (serverSeq);
					//emit seqExpect (serverSeqExp);
					//printf( "SEQ: new seq start from cache" );
					serverSeq = serverCachePkt[ a ][ 5 ] | (serverCachePkt[ a ][ 4 ] << 8 );
					if ( serverSeq == 0xFFFF )
						serverSeqExp = 0;
					else
					{
						serverSeqExp = serverSeq + 1;
						serverSeqExp %= 0x10000;
					}
					serverSeqClear = false;
					
					this->dispatchSplitOpCode( serverCacheLen[ a ], serverCachePkt[ a ] );
					if ( ( serverCacheCount - 1 ) == a )
						serverCacheCount--;
				}

				//printf( "SEQ: found %04x in cache instead - cache count %04d\n", serverCacheSeq[ a ], serverCacheCount );
			}
		}

		// assume this is an acknowledged packet
		// this is the start of a new sequence
		if ( ( data[ 0 ] == 0x3a || data[ 0 ] == 0x1a ) && serverSeqClear )
		{
			//emit seqReceive (serverSeq);
			//emit seqExpect (serverSeqExp);
			//unsigned int opcode    = data[15] | (data[14] << 8);
			//printf( "SEQ: new seq found in data stream,  %04x\n", serverSeq );
			if ( serverSeq == 0xFFFF )
				serverSeqExp = 0;
			else
			{
				serverSeqExp = serverSeq + 1;
				serverSeqExp %= 0x10000;
			}
			serverSeqClear = false;

			this->dispatchSplitOpCode( len, data );
			// check the cache to see if we have next packet
			for ( int a = 0; a < serverCacheCount; a++ )
			{
				//printf( "SEQ: checking cache for %04x - cache count %04d\n", serverSeqExp, serverCacheCount );
				if ( serverCacheSeq[ a ] == serverSeqExp )
				{
					//printf( "SEQ: found %04x in cache - cache count %04d\n", serverSeqExp, serverCacheCount );
					serverSeqExp = serverSeq + 1;
					serverSeqExp %= 0x10000;
					this->dispatchSplitOpCode( serverCacheLen[ a ], serverCachePkt[ a ] );
					if ( ( serverCacheCount - 1 ) == a )
						serverCacheCount--;
				}
			}
			return;
		}
		else if ( ( data[ 0 ] == 0x0a ) && ( serverSeq == serverSeqExp ) )
		{
			serverSeqExp = serverSeq + 1;
			serverSeqExp %= 0x10000;

			//emit seqExpect (serverSeqExp);
			//emit packetReceived (serverCacheCount);
			//printf( "SEQ: next in seq found in data stream, %04x\n", serverSeq );
			this->dispatchSplitOpCode( len, data );
			return;
		}
		else if ( serverSeq > serverSeqExp )
		{
			serverCacheLen[ serverCacheCount ] = len;
			serverCacheSeq[ serverCacheCount ] = serverSeq;
			//printf( "SEQ: out of order seq, sending to cache, %04x\n", serverSeq );
			// lets cache the packet till we are there in the seq
			for ( int a = 0; a < len; a++ )
				serverCachePkt[ serverCacheCount ][ a ] = data[ a ];

			serverCacheCount++;
		}
	}
}
*/


/*
void __dumpPlayerPos( const struct playerUpdateStruct* pdata )
{
	printf("x,y,dx,dy: %d,%d    %d,%d\n",
		pdata->pos.xPos,
		pdata->pos.yPos,
		pdata->pos.deltaX,
		pdata->pos.deltaY );
}
*/

void EQPacket::dispatchOpCode( int len, unsigned char* data, int direction = 0 )
{
#ifdef DEBUG
//	debug( "EQPacket::dispatchOpCode()" );
#endif

	int					decrypted = 0;
	bool				handled = true;
	unsigned char*		temp = data;
	
	if ( len < 0 )
		return;

	bool 		broken = gSEQPrefs->getPrefBool( "BrokenDecode", "Misc" );
	QString		ip = gSEQPrefs->getPrefString( "IP", "Network", "127.0.0.1" );
	
   // pre-process the packets
	if ( !broken )
#if HAVE_LIBEQ
		decrypted = this->decryptPacket( data, &len, ip );
#else
		printf( "BUG: broken_decode should not be disabled if libEQ.a support not present\n" );
		exit( 1 );
#endif
 
	OpCode		opcode = *((OpCode*)data);

	emit handleOpCode( opcode, direction, data, len );
	
	unsigned short	opcodenum = opcode.version | ( opcode.code << 8 );
	
	switch ( opcodenum )
	{
		case CODE_SHOP_ITEM:		emit handleShopItem(		(itemShopStruct*)data );		break;
		case CODE_CORPSE_ITEM:		emit handleCorpseItem(		(itemReceivedStruct*)data );	break;
		case CODE_TRADE_ITEM:		emit handleTradeItem(		(itemReceivedStruct*)data );	break;
		case CODE_TRADE_ITEM2:		emit handleTradeItem2(		(tradeItemStruct*)data );		break;
		case CODE_PLAYER_ITEM:		emit handlePlayerItem(		(itemPlayerStruct*)data );		break;
		case CODE_SUMMONED_ITEM:	emit handleSummonedItem(	(summonedItemStruct*)data );	break;
		case CODE_CORPSE:			emit handleCorpse(			(spawnKilledStruct*)data );		break;
		case CODE_DELETE_SPAWN:		emit handleDeleteSpawn(		(deleteSpawnStruct*)data );		break;
		
		case CODE_TIME:				emit handleTime(			(timeOfDayStruct*)data );		break;
		case CODE_BOOKTEXT:			emit handleBookText(		(bookTextStruct*)data );		break;
		case CODE_RANDOM:			emit handleRandom(			(randomStruct*)data );			break;
		case CODE_EMOTE:			emit handleEmote(			(emoteTextStruct*)data );		break;
		case CODE_PLAYER_BOOK:		emit handlePlayerBook(		(bookPlayerStruct*)data );		break;
		case CODE_PLAYER_CONT:		emit handlePlayerCont(		(containerPlayerStruct*)data );	break;
		case CODE_INSPECT:			emit handleInspect(			(inspectingStruct*)data );		break;
		case CODE_HP_UPDATE:		emit handleHPUpdate(		(spawnHpUpdateStruct*)data );	break;
		case CODE_SPECIAL_MSG:		emit handleSpecialMsg(		(spMesgStruct*)data );			break;
		case CODE_BEGIN_CAST:		emit handleBeginCast(		(beginCastStruct*)data );		break;
		case CODE_MEM_SPELL:		emit handleMemSpell(		(memorizeSlotStruct*)data );	break;
		case CODE_XP_UPDATE:		emit handleXPUpdate(		(expUpdateStruct*)data );		break;
		case CODE_LEVEL_UP:			emit handleLevelUp(			(levelUpStruct*)data );			break;
		case CODE_SKILL_UP:			emit handleSkillUp(			(skillIncreaseStruct*)data );	break;
		case CODE_DOOR:				emit handleDoor(			(newDoorStruct*)data );			break;
		case CODE_DOOR_OPEN:		emit handleDoorOpen(		data );							break;
		case CODE_ILLUSION:			emit handleIllusion( 		data );							break;
		case CODE_BAD_CAST:			emit handleBadCast(			(interruptCastStruct*)data );	break;		
		case CODE_SYS_MSG:			emit handleSysMsg(			(systemMessageStruct*)data );	break;
		case CODE_ARMOR_CHANGE:		emit handleEquipChange(		(equipChangeStruct*)data );		break;
		case CODE_ACTION:			emit handleAction( 			(actionStruct*)data );			break;
		case CODE_CAST_ON:			emit handleCastOn( 			(castOnStruct*)data );			break;
		case CODE_MANA_USED:		emit handleManaUsed(		(manaDecrementStruct*)data );	break;
		case CODE_STAMINA:			emit handleStamina(			(staminaStruct*)data );			break;
		
		case CODE_NEW_DROP:			emit handleNewDrop(			(addDropStruct*)data );			break;		
		case CODE_DELETE_DROP:		emit handleDeleteDrop(		(deleteDropStruct*)data );		break;
		case CODE_NEW_COINS:		emit handleNewCoins(		(addCoinsStruct*)data );		break;
		case CODE_DELETE_COINS:		emit handleDeleteCoins(		(deleteCoinsStruct*)data );		break;
		
		case CODE_VENDOR_OPEN:		emit handleOpenVendor(		data );							break;
		case CODE_VENDOR_CLOSE:		emit handleCloseVendor(		data );							break;
		
		case CODE_GM_OPEN:			emit handleOpenGM( 			data );							break;
		case CODE_GM_CLOSE:			emit handleCloseGM( 		data );							break;
		
		case CODE_ATTACK1:			emit handleAttack1(			(attack1Struct*)data ); 		break;
		case CODE_ATTACK2:			emit handleAttack2(			(attack2Struct*)data );			break;
		
		case CODE_NEW_GUILD:		emit handleNewGuild(		(newGuildStruct*)data );		break;
		
		case CODE_MONEY_UPDATE:		emit handleMoneyUpdate(		(moneyUpdateStruct*)data );		break;
		case CODE_MONEY:			emit handleMoney(			data );							break;
		
		case CODE_CLIENT_TARGET:	emit handleClientTarget(	(clientTargetStruct*)data );	break;
		
		case CODE_BIND_WOUND:		emit handleBindWound(		(bindWoundStruct*)data );		break;
		
		case CODE_GROUP_INFO:		emit handleGroupInfo(		(groupMemberStruct*)data );		break;

		case CODE_PLAYER_POS:
		{
			// only nabbing player position changes from the client means we don't
			// get false positives -- sometimes corpse drags will get caught as
			// player positional updates, otherwise
			if ( direction == FROM_CLIENT && m_insideZone )
				emit handlePlayerPos( (playerUpdateStruct*)data );
		}
		break;
		
		case CODE_NEW_SPAWN:
		{
			if ( m_insideZone )
				emit handleNewSpawn( (addSpawnStruct*)data );
		}
		break;

		case CODE_SPAWN_UPDATE:
		{
			if ( m_insideZone )
				emit handleSpawnUpdate( (spawnPosUpdateStruct*)data );
		}
		break;
		
		case CODE_ZONE_CHANGE:
		{
			m_insideZone = false;
			emit handleZoneChange( (zoneChangeStruct*)data );
			if ( direction == FROM_CLIENT )
				this->resetDecryptor();
		}
		break;		
		
		case CODE_ZONE_END:
		{
			m_insideZone = true;
			emit handleZoneEnd( (clientZoneInStruct*)data );
		}
		break;
		
		case CODE_ZONE_BEGIN:		
		{
			m_insideZone = true;
			if ( direction == FROM_SERVER )
				emit handleZoneBegin( (clientZoneOutStruct*)data );
		}
		break;
		
		case CODE_CHANNEL_MSG:	
		{
			if ( direction == FROM_SERVER )
				emit handleChannelMsg( (channelMessageStruct*)data );
		}
		break;
		
		case CODE_ZONE_SPAWNS:
		{
			if ( decrypted )
			{
				int count;
				count = ( len - sizeof( struct zoneSpawnsStruct ) ) / sizeof( SpawnStruct );
				emit handleZoneSpawns( (zoneSpawnsStruct*)data, count );
			}
		}
		break;

		case CODE_CHAR_PROFILE:
		{
			if ( decrypted )
				emit handlePlayerProfile( (playerProfileStruct*)data );
		}
		break;

		case CODE_CON:
		{
			if ( direction == FROM_CLIENT )
				emit handleConsRequest(	(considerStruct*)data );
			else
				emit handleConsMessage( (considerStruct*)data );	
		}
		break;
		
		default:					handled = false;											break;
	}					
	
	if ( !handled )
		emit unhandledOpCode( opcode, direction, temp, len );
		
}

// combines data from split packets
void EQPacket::dispatchSplitOpCode( int len, unsigned char* data )
{
#ifdef DEBUG
//	debug( "EQPacket::dispatchSplitOpCode()" );
#endif 
	if ( ( data[ 0 ] == 0x3a ) || ( data[ 0 ] == 0x1a ) )
		// clear data
		serverDataSize = 0;

	// add data
	for ( int a = 0; a < ( len - 16 ); a++ )
	{
		serverData[ serverDataSize ] = data[ a + 12 ];
		serverDataSize++;
	}

	// check if this is last part of data
	if ( data[ 9 ] == ( data[ 11 ] - 1 ) )
		this->dispatchOpCode( serverDataSize - 2, serverData + 2 );
}

void EQPacket::incPlayback()
{
	if ( m_pVPacket )
	{
		int x = m_pVPacket->playbackSpeed();
		switch ( x )
		{ 
			// if we were paused go to 1X not full speed
			case -1:	x = 1;		break;
			// can't go faster than full speed
			case 0:		return;		break;
			case 9:		x = 0;		break;
			default:	x += 1;		break;
		}

		emit numPacket( 0 );  // this resets the packet average
		m_pVPacket->setPlaybackSpeed( x );

		QString string;
		if ( x > 0 )
			string.sprintf( "Playback speed set to %d", x ); 
		else
			string = "Playback speed set as fast as possible"; 
//		emit stsMessage(string, 5000);
	}
}

void EQPacket::decPlayback()
{
	if ( m_pVPacket )
	{
		int x = m_pVPacket->playbackSpeed();
		switch ( x )
		{
			// paused
			case -1:		return;		break;
			// slower than 1 is paused
			case 1:			x = -1;		break;
			// if we were full speed goto 9
			case 0:			x = 9;		break;
			default:		x -= 1;		break;
		}
		emit numPacket( 0 );  // this resets the packet average
		m_pVPacket->setPlaybackSpeed( x );

		QString string;
		if ( x == 0 ) 
			string = "Playback speed set as fast as possible"; 
		else if ( x < 0 )
			string = "Playback paused (']' to resume)"; 
		else
			string.sprintf( "Playback speed set to %d", x ); 
//		emit stsMessage( string, 5000 );
	}
}


