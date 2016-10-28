//	packet.h
//		SINS Distributed under GPL

#ifndef EQPACKET_H
#define EQPACKET_H

#define MAXPACKETCACHECOUNT 255
#define MAXPACKETCACHESIZE  640
#define MAXSPAWNDATA	    49152

#include <qobject.h>
#include <qintdict.h>
#include <qlist.h>
#include <qqueue.h>

extern "C" {
#include <pcap.h>
}

// if this isn't here, we don't get the necessary defs from qthread.h
#define QT_THREAD_SUPPORT 1
#include <qthread.h>

#include "everquest.h"

#define FROM_CLIENT		1
#define FROM_SERVER		2


class VPacket;
class Player;
class EQPacket;

// a simple thread class to handle our decryption thread -- it should
//	really have one more routine, which is "locateKey" found in the
//	packet class -- have to move that at some point
class DecryptThread: public QThread
{
public:
	DecryptThread( EQPacket* pack );
	
	virtual void run();
	
protected:
	EQPacket*		m_packet;
};

// thread class to handle packet capturing
// my first instinct was to make this static, but it seems possible that
// you could instantiate more than one of these and monitor more than a single
// client machine... the architecture is not entirely there to do this yet,
// since the interface isn't set up to deal with it, but I have been trying to
// make it such that you can run SINS faceless... a faceless SINS would allow
// logging, which has some utility on it's own... monitoring two or more client
// machines with just logging facilities might be useful
// in this class, run calls pcap_loop and the loop routine is passed a stub
// function (see packet.cpp) which in turn calls back into this specific object's
// packetCallback... this is how packets get enqueue'd
// getPacket is the routine that other classes are expected to call to get
// packets off the queue... note that, contrary to good design principles,
// getPacket returns a malloc'ed chunk of memory that the caller is execpted
// to free... failing to do so will result in massive memory leakage

struct EQPktRec
{
	int				len;
	unsigned char	data[ 0 ];
};
typedef struct EQPktRec EQPktRec;

class EQSession
{
public:
	EQSession::EQSession( unsigned long ip ):
		m_ip( ip )
	{
	}

	unsigned long	m_ip;
};

class PacketCaptureThread: public QThread
{
public:
	PacketCaptureThread( EQPacket* pack, const char* device, const char* hostname, int address_type );
	void refilter( const char* device, const char* hostname, int address_type, unsigned long serverPort );
	void clear();

	virtual void run();

	void packetCallback( const struct pcap_pkthdr* ph, const u_char* data );
	EQPktRec* getPacket();									// MUST BE FREE'd be the caller
	
protected:
	EQPacket*					m_packet;					// don't really need
	QMutex						m_packetCaptureMutex;		// mutex to prevent simultaneous queue access
	pcap_t*						m_pcache_pcap;				// our packet capture filter
	QQueue<EQPktRec>			m_packetCache;				// queue for our packets
};


// EQPacket is the main object for dealing with all the network cruft, including
// setting up packet capturing, decryption, and emitting signals for the packet
// data that you can hook up to and actually do something useful with
// the idea is that it's entirely 'self-sufficient'... you simply instantiate it,
// hook up to whatever signals you're interested in (via Qt's 'connect' function),
// and call 'start' on it 
class EQPacket: public QObject
{
Q_OBJECT
public:
	EQPacket( const char* name = NULL );

	// start/stop are used to start and stop the timer object embedded in EQPacket
	//	that is responsible for actually keeping the central loop for packet
	//	handling running (not the thread object which actually reads the packets,
	//	but the application-side which actually interprets them)
	void start( int delay = 0 );
	void stop();
	
public slots:
	void incPlayback();
	void decPlayback();

protected slots:
	// central entry point -- see .cpp file for notes, this is the function called
	// from our timer
	void processPackets();

signals:
	void captureTargetChanged( const QString& device, const QString& ip );
	
	void keyFound();
	
	void backfillPlayer( const struct playerProfileStruct* player );
	void backfillSpawn( const struct spawnStruct* spawn );

	void packetReceived( int );
	void seqReceive( int );
	void seqExpect( int );

	void numPacket( int );

	// handlePacket is emitted for each packet that passes through the packet
	// 	handler (i.e., you should receive one and only one 'numPacket' signal
	//	for each 'handlePacket')
	//	you can catch this to examine unprocessed packets -- unlike
	//	'handleOpCode' which is emitted for processed packets
	//	'data' here will still contain ack. bytes and the opcode and any
	//	other garbage that comes directly from the server, minus the ethernet
	//	headers
	void handlePacket( const void* data, int len );
	
	// handleOpCode is emitted before each op code is dealt with, you can
	//	either catch all op codes by listening for it, or listen to the
	//	signals for each op code individually by connecting to the signals
	//	below.  you probably don't want to do both since then you'll get
	//	both signals for each op code
	void handleOpCode( const OpCode& opcode, int direction, void* data, unsigned int len );

	// all the below are signals emitted through opCode dispatch ("dispatchOpCode")
	//	the first three are the three encrypted opCodes -- if you catch them here,
	//	they'll be decrypted, but you should be aware that they will probably come
	//	out of order relative to the other OpCodes since they're queued until they've
	//	been decoded -- best not to do anything too stateful with them
	//	the ItemMgr knows how to deal with that, you can look at the "backfill"
	//	routines
	void handlePlayerProfile( const struct playerProfileStruct* data );
	void handleZoneSpawns( const struct zoneSpawnsStruct* data, int count);
	void handleNewSpawn( const struct addSpawnStruct* data );

	void handleShopItem( const struct itemShopStruct* data );
	void handleCorpseItem( const struct itemReceivedStruct* data );
	void handleTradeItem( const struct itemReceivedStruct* data );
	void handleTradeItem2( const struct tradeItemStruct* data );
	void handlePlayerItem( const struct itemPlayerStruct* data );
	void handleSummonedItem( const struct summonedItemStruct* data );
	void handleZoneBegin( const struct clientZoneOutStruct* data );
	void handleZoneEnd( const struct clientZoneInStruct* data );
	void handleZoneChange( const struct zoneChangeStruct* data );
	void handleCorpse( const struct spawnKilledStruct* data );
	void handleDeleteSpawn( const struct deleteSpawnStruct* data );
	void handleChannelMsg( const struct channelMessageStruct* data );
	void handleTime( const struct timeOfDayStruct* data );
	void handleBookText( const struct bookTextStruct* data );
	void handleRandom( const struct randomStruct* data );
	void handleEmote( const struct emoteTextStruct* data );
	void handlePlayerBook( const struct bookPlayerStruct* data );
	void handlePlayerCont( const struct containerPlayerStruct* data );
	void handleInspect( const struct inspectingStruct* data );
	void handleHPUpdate( const struct spawnHpUpdateStruct* data );
	void handleSpecialMsg( const struct spMesgStruct* data );
	void handleBeginCast( const struct beginCastStruct* data );
	void handleMemSpell( const struct memorizeSlotStruct* data );
	void handleSpawnUpdate( const struct spawnPosUpdateStruct* data );
	void handleXPUpdate( const struct expUpdateStruct* data );
	void handleLevelUp( const struct levelUpStruct* data );
	void handleSkillUp( const struct skillIncreaseStruct* data );
	void handleDoor( const struct newDoorStruct* data );
	void handleDoorOpen( const void* data );
	void handleIllusion( const void* data );
	void handleBadCast( const struct interruptCastStruct* data );
	void handleSysMsg( const struct systemMessageStruct* data );
	void handlePlayerPos( const struct playerUpdateStruct* data );
	void handleEquipChange( const struct equipChangeStruct* data );
	void handleAction( const struct actionStruct* data );
	void handleCastOn( const struct castOnStruct* data );
	void handleManaUsed( const struct manaDecrementStruct* data );
	void handleStamina( const struct staminaStruct* data );
	void handleNewDrop( const struct addDropStruct* data );
	void handleDeleteDrop( const struct deleteDropStruct* data );
	void handleNewCoins( const struct addCoinsStruct* data );
	void handleDeleteCoins( const struct deleteCoinsStruct* data );
	void handleOpenVendor( const void* data );
	void handleCloseVendor( const void* data );
	void handleOpenGM( const void* data );
	void handleCloseGM( const void* data );
	void handleAttack1( const struct attack1Struct* data );
	void handleAttack2( const struct attack2Struct* data );
	void handleConsRequest( const struct considerStruct* data );
	void handleConsMessage( const struct considerStruct* data );
	void handleNewGuild( const struct newGuildStruct* data );
	void handleMoneyUpdate( const struct moneyUpdateStruct* data );
	void handleMoney( const void* data );
	void handleClientTarget( const struct clientTargetStruct* data );
	void handleBindWound( const struct bindWoundStruct* data );
	void handleGroupInfo( const struct groupMemberStruct* data );
	
	// unhandledOpCode is only emitted for each op code we find in the
	//	stream that is not dealt with in the code in the packet class.
	//	you can connect to this if you want to do things like log new
	//	op codes that haven't been documented
	void unhandledOpCode( const OpCode& opcode, int direction, void* data, unsigned int len );

protected:
	void __stripAck( u_char*& data, int& len );

	void locateKey();
	void foundKey();

	void resetDecryptor();		

	int decryptPacket( unsigned char* data, int* len, const char* cli );	
	void processSpawn(struct dbSpawnStruct* dbSpawn, int dbemit);
	void decodePacket( unsigned char* buffer );
	void dispatchOpCode( int len, unsigned char* data, int direction = 0 );
	void dispatchSplitOpCode( int len, unsigned char* data );

	QTimer*						m_timer;
	VPacket*					m_pVPacket;
	bool						m_playbackPackets;
	bool						m_recordPackets;
	
	bool						m_busyDecoding;
	bool						m_insideZone;
	
	// client monitoring stuff... m_client_addr is the current clients IP,
	// the dictionary is a list of IPs that have EQ sessions running
	unsigned long				m_client_addr;
	QIntDict<EQSession>			m_sessions;
	bool						m_autoFindSession;

	int							m_nPacket;

	bool						m_userResync;
	int							serverSeq;
	unsigned int				serverSeqExp;
	bool						serverSeqClear;
	int							serverCacheLen[ MAXPACKETCACHECOUNT ];
	unsigned int				serverCacheSeq[ MAXPACKETCACHECOUNT ];
	unsigned char				serverCachePkt[ MAXPACKETCACHECOUNT ] [MAXPACKETCACHESIZE ];
	unsigned char				serverData[ MAXSPAWNDATA ];
	int							serverDataSize;
	int							serverCacheCount;

	// decryption thread related stuff
	//	we create a decryption thread upon zoning in, and let it run until it
	//	finds a key or is cancelled (i.e. by quitting/zoning out) -- the mutex
	//	here controls access to the encypted packet queues below, since we don't
	//	want to be mucking with them in the main loop and in the decryption
	//	thread at the same time
	DecryptThread*				m_decryptThread;
	bool						m_decryptActive;
	QMutex						m_queueMutex;
	bool						m_cancelDecrypt;
	
	// our packet capture thread
	PacketCaptureThread*		m_packetCaptureThread;
	
	// queues for still-encrypted packets
	QList<EQPktRec>				m_playerProfiles;
	QList<EQPktRec>				m_zoneSpawns;
	QList<EQPktRec>				m_spawns;

	UDWORD						m_decodeKey;
	
	friend class DecryptThread;
};

bool isEncryptedOpCode( unsigned int opCode );

#endif
