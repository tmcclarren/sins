#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include <unistd.h>
#include <time.h>
#include <errno.h>

#include <qapplication.h>
#include <qfiledialog.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qlistview.h>
#include <qpopupmenu.h>
#include <qpushbutton.h>
#include <qvbox.h>

#include "log.h"
#include "preferences.h"
#include "util.h"
#include "opcodes.h"
#include "packet.h"
#include "interface.h"
#include "player.h"
#include "spawn.h"
#include "itemmgr.h"

// increment this when changing spawnlogout format so parsers know to expect
// something different
const int			spawnlog_version = 2;

QString lookupOpCode( const OpCode& /*code*/ )
{
	return "";
}

QString print_addr( unsigned long addr, unsigned long client_addr )
{
	QString paddr;
	
	if ( addr == client_addr )
		paddr = "client";
	else
	{
		paddr.sprintf( "%ld.%ld.%ld.%ld",
			addr & 0x000000ff,
			( addr & 0x0000ff00 ) >> 8,
			( addr & 0x00ff0000 ) >> 16,
			( addr & 0xff000000 ) >> 24 );
	}
	return paddr;
}

QString getTime()
{
	time_t			clock;
	struct tm* 		current;

	time( &clock );
	current = localtime( &clock );

	QString		ret;
	ret.sprintf( "%02d.%02d.%02d", current->tm_hour, current->tm_min, current->tm_sec );
	return ret;
}

LogMgr::LogMgr( const char* name ):
	QObject( NULL, name )
{
	gLogMgr = this;
	m_logMenu = NULL;
	m_logMenu = this->getLogMenu();
	
//	new EncryptedPacketLog(
//		gSEQPrefs->getPrefString( "EncryptedLogFilenameBase", "Log" ),
//		gSEQPrefs->getPrefBool( "LogEncrypted", "Log", false ),
//		"encrypted-packet-log" );
		
	int 		menuID;
	
	PacketLog*	packetLog = new PacketLog(
		gSEQPrefs->getPrefString( "GlobalLogFilename", "Log" ),
		gSEQPrefs->getPrefBool( "LogAllPackets", "Log" ),
		"packet-log" );
	
	menuID = m_logMenu->insertItem( "All Packets", packetLog, SLOT( toggleLog() ), ALT + Key_F12 );
	
	OpCodeLog*	opCodeLog = new OpCodeLog(
		gSEQPrefs->getPrefString( "OpCodeLogFilename", "Log" ),
		gSEQPrefs->getPrefBool( "LogOpCodes", "Log" ),
		"opcode-log" );

	menuID = m_logMenu->insertItem( "Op Codes", opCodeLog, SLOT( toggleLog() ), ALT + Key_F11 );
	m_logMenu->insertSeparator();
	m_logMenu->insertItem( "Edit Op Code list...", opCodeLog, SLOT( editOpCodeList() ) );

	OpCode		c;
	c.code = 0x26;
	c.version = 0x40; // weird
	opCodeLog->addOpCode( c );

	new SpawnLog(
		gSEQPrefs->getPrefString( "SpawnLogFilename", "Log" ),
		gSEQPrefs->getPrefBool( "LogSpawns", "Log" ),



		"spawn-text-log" );
}

void LogMgr::addLogger( const EQLog* log )
{
	if ( !m_logs.containsRef( log ) )
		m_logs.append( log );
}

void LogMgr::deleteLogger( const EQLog* log )
{
	m_logs.removeRef( log );
}
	
void LogMgr::handleTime( const timeOfDayStruct* tday )
{
	m_eqTime.zoneInTime.minute = tday->minute;
	m_eqTime.zoneInTime.hour = tday->hour;
	m_eqTime.zoneInTime.day = tday->day;
	m_eqTime.zoneInTime.month = tday->month;
	m_eqTime.zoneInTime.year = tday->year;

	m_eqTime.packetReferenceTime = time( NULL );

	printf( "TIME: %02d:%02d %02d/%02d/%04d\n",
				tday->hour, tday->minute, tday->month,
				tday->day, tday->year);
}

bool LogMgr::getEQTimeOfDay( time_t timeConvert, struct timeOfDayStruct* eqTimeOfDay )
{
	// check to see if we have a reference time to go by
	if ( m_eqTime.packetReferenceTime == 0 )
		return false;

	unsigned long diff = timeConvert - m_eqTime.packetReferenceTime;
	
	// there are 3 seconds per 1 EQ Minute
	diff /= 3;

	// the minutes range from 0 - 59
	diff += m_eqTime.zoneInTime.minute;

	eqTimeOfDay->minute = diff % 60;
	diff /= 60;

	// the hours range from 1-24: 1 = 1am, 2 = 2
	// ...  23 = 11 pm, 24 = 12 am
	// modify it so that it works from
	// 0 - 23 for our calculations
	diff += ( m_eqTime.zoneInTime.hour - 1);
	eqTimeOfDay->hour = ( diff % 24 ) + 1;
	diff /= 24;

	// the days range from 1-28
	// modify it so that it works from

	// 0-27 for our calculations
	diff += ( m_eqTime.zoneInTime.day - 1 );
	eqTimeOfDay->day = ( diff % 28 ) + 1;
	diff /= 28;

	// the months range from 1-12
	// modify it so that it works from
	// 0-11 for our calculations
	diff += ( m_eqTime.zoneInTime.month - 1 );
	eqTimeOfDay->month = ( diff % 12 ) + 1;
	diff /= 12;

	eqTimeOfDay->year = m_eqTime.zoneInTime.year + diff;

	return true;
}

QPopupMenu* LogMgr::getLogMenu()
{
	if ( !m_logMenu )
		m_logMenu = new QPopupMenu;
	return m_logMenu;
}

/*
void EQLog::pickLogFile()
{
	QString		currentFile = m_logFile.name();

	
	QString		newFileName;
	newFileName = QFileDialog::getSaveFileName( currentFile );
	
	if ( !newFileName.isNull() )
	{
		m_logFile.close();
		m_logFile.setName( newFileName );
		if ( m_logFile.exists() )
		{
			// pick overwrite/append
			m_logFile.open( IO_WriteOnly | IO_Append );
		}
		else
			m_logFile.open( IO_WriteOnly | IO_Append );
	}
}
*/

EQLog::EQLog( const QString& file, bool doLog, const char* name ):
	QObject( gPacket, name ),
	m_logFile( file )
{
	m_stream = NULL;

	this->doLog( doLog );
}

bool EQLog::openLogFile()
{
	if ( !m_logFile.open( IO_WriteOnly | IO_Append ) )
	{
		printf( "Error opening %s\n", (const char*)m_logFile.name() );
		m_log = false;
		return false;
	}
	
	m_stream = new QTextStream( &m_logFile );
	
	return true;
}
	
void EQLog::doLog( bool on )
{
	if ( on )
	{
		if ( !this->openLogFile() )
			on = false;
	}

	m_log = on;
}

void EQLog::toggleLog()
{
	this->doLog( !m_log );
}

bool EQLog::logPacket( int /*size*/, unsigned char* buffer )
{
//	debug( "EQLog::logPacket()" );
	
	u_char*			data;
	struct ip*		ip;
	struct udphdr*		udp;
	unsigned int		hlen, len;
	unsigned int		sport, dport;
	bool			log_return = false;
	
	data = (unsigned char*)buffer;
	ip = (struct ip*)buffer;
	hlen = ip->ip_hl * 4;
	len = ntohs( ip->ip_len );
	if ( len != 0 )
	{
		len -= hlen;
		data += hlen;

		udp = (struct udphdr*)data;
		len -= sizeof( struct udphdr );
		data += sizeof( struct udphdr );

#ifdef __FreeBSD__
		sport = ntohs( udp->uh_sport );
		dport = ntohs( udp->uh_dport );
#else
		sport = ntohs( udp->source );
		dport = ntohs( udp->dest );
#endif

		log_return = this->logData( len, data, &ip->ip_src, &ip->ip_dst, sport, dport );
	}
	
	return log_return;
}

// logs packet data
bool EQLog::logData( unsigned int len, unsigned char* data,
	struct in_addr* saddr, struct in_addr* daddr,
	unsigned int source, unsigned int dest )
{

//	debug( "EQLog::logData()" );

	if ( !m_log )
		return false;
		
	time_t			now;
	QString			output;
	QString			hex;
	QString			asc;
	
	now = time( NULL );

	if ( saddr && saddr->s_addr )
	{
		*m_stream << print_addr( saddr->s_addr ) << " : " << source << " ->";
		*m_stream << print_addr( daddr->s_addr ) << " : " << dest;
		*m_stream << "\n";
	}

	*m_stream << len << "\t" << ctime( &now );
	
	unsigned long		c;
	for ( c = 0; c < len; c++ )
	{
		if ( c && !( c % 16 ) )
		{
			output.sprintf( "%03ld | %s | %s", c - 16, (const char*)hex, (const char*)asc );
			*m_stream << output << "\n";
			hex = "";
			asc = "";
		}

		output.sprintf( "%02x ", data[ c ] );
		hex += output;

		if ( ( data[ c ] >= 32 ) && ( data[ c ] <= 126 ) )
			asc += data[ c ];
		else
			asc += '.';
	}

	if ( c % 16 )
		c = c - ( c % 16 );
	else
		c -= 16;
	output.sprintf( "%03ld | %-48s | %s \n\n", c, (const char*)hex, (const char*)asc );
	*m_stream << output;

	return true;
}


EQLog::~EQLog()
{
	m_logFile.close();
}

 
SpawnLog::SpawnLog( const QString& file, bool doLog, const char* name ):
	EQLog( file, doLog, name )

{
	connect( gPacket, SIGNAL( handleZoneSpawns(const struct zoneSpawnsStruct*, int) ),
		this, SLOT( handleZoneSpawns(const struct zoneSpawnsStruct*, int) ) );
	connect( gPacket, SIGNAL( handleZoneEnd(const struct clientZoneInStruct*) ),
		this, SLOT( handleZoneEnd(const struct clientZoneInStruct*) ) );
	connect( gPacket, SIGNAL( handleNewSpawn(const struct addSpawnStruct*) ),
		this, SLOT( handleNewSpawn(const struct addSpawnStruct*) ) );
	connect( gPacket, SIGNAL( handleDeleteSpawn(const struct deleteSpawnStruct*) ),
		this, SLOT( handleDeleteSpawn(const struct deleteSpawnStruct*) ) );
	connect( gPacket, SIGNAL( handleCorpse(const struct spawnKilledStruct*) ),
		this, SLOT( handleCorpse(const struct spawnKilledStruct*) ) );

}

void SpawnLog::handleZoneSpawns( const struct zoneSpawnsStruct* zspawns, int count )
{
	if ( !m_log )
		return;
	
	*m_stream << "ZONE SPAWNS:\n";

	QString		zoneName = gItemMgr->shortZoneName();

	struct timeOfDayStruct		eqTime;
	time_t timeCurrent = time( NULL );
	gLogMgr->getEQTimeOfDay( timeCurrent, &eqTime );
	
	QString		time = getTime();
	
	for ( int a = 0; a < count; a++ )
	{
		QString		output;
		output.sprintf( "+:%s(%d):%d,%d,%d:%s:%d:%s:%02d.%02d.%02d.%02d.%04d",
						zspawns->spawn[ a ].name,
						zspawns->spawn[ a ].spawnId,
						zspawns->spawn[ a ].heading.loc.x,
						zspawns->spawn[ a ].heading.loc.y,
						zspawns->spawn[ a ].heading.loc.z,
						(const char*)time,
						spawnlog_version,
						(const char*)zoneName,
						eqTime.hour,
						eqTime.minute,
						eqTime.month,
						eqTime.day,
						eqTime.year );
		
		*m_stream << output << "\n";
	}

	*m_stream << "END ZONE SPAWNS\n";
}

void SpawnLog::handleZoneEnd( const struct clientZoneInStruct* newZone )
{
	if ( !m_log )

		return;

	QString		zoneName = newZone->shortName;
	
	*m_stream << "----------\nNEW ZONE:" << zoneName << "\n----------\n";
	*m_stream << " :name(spawnID):Xpos:Ypos:Zpos:H.m.s:Ver:Zone:eqHour.eqMinute.eqMonth.eqDay.eqYear\n";
}












void SpawnLog::handleNewSpawn( const struct addSpawnStruct* spawn )
{
	if ( !m_log )

		return;
		
	struct timeOfDayStruct		eqTime;

	time_t timeCurrent = time( NULL );
	gLogMgr->getEQTimeOfDay( timeCurrent, &eqTime );


	QString		zoneName = gItemMgr->shortZoneName();
	QString		time = getTime();
	
	QString 	output;
	output.sprintf( "+:%s(%d):%d,%d,%d:%s:%d:%s:%02d.%02d.%02d.%02d.%04d",
					spawn->spawn.name,
					spawn->spawn.spawnId,
					spawn->spawn.heading.loc.x,
					spawn->spawn.heading.loc.y,
					spawn->spawn.heading.loc.z,
					(const char*)time,
					spawnlog_version,
					(const char*)zoneName,
					eqTime.hour,
					eqTime.minute,
					eqTime.month,
					eqTime.day,
					eqTime.year);
	
	*m_stream << output << "\n";
}

void SpawnLog::handleDeleteSpawn( const struct deleteSpawnStruct* delspawn )
{
	if ( !m_log )
		return;
		
	const Spawn*	spawn = gItemMgr->spawnByID( delspawn->spawnId );
	
	if ( !spawn )
		return;

	struct timeOfDayStruct			eqTime;


	time_t		timeCurrent = time( NULL );		
	gLogMgr->getEQTimeOfDay( timeCurrent, &eqTime );
	QString		zoneName = gItemMgr->shortZoneName();
	QString		time = getTime();
	
	QString		output;
	output.sprintf( "-:%s(%d):%d,%d,%d:%s:%d:%s:%02d.%02d.%02d.%02d.%04d",
				(const char*)spawn->name(),
				delspawn->spawnId,
				spawn->xPos(),
				spawn->yPos(),
				spawn->zPos(),
				(const char*)time,
				spawnlog_version,
				(const char*)zoneName,
				eqTime.hour,
				eqTime.minute,
				eqTime.month,
				eqTime.day,
				eqTime.year);
	
	*m_stream << output << "\n";
}


void SpawnLog::handleCorpse( const struct spawnKilledStruct* deadspawn )
{
	if ( !m_log )
		return;
		
	const Spawn*	spawn = gItemMgr->spawnByID( deadspawn->spawnId );

	
	if ( !spawn )
		return;
		
	struct timeOfDayStruct				eqTime;

	time_t timeCurrent = time( NULL );		
	gLogMgr->getEQTimeOfDay( timeCurrent, &eqTime );
	
	QString		zoneName = gItemMgr->shortZoneName();
	QString		time = getTime();
	
	QString		output;
	output.sprintf( "x:%s(%d):%d,%d,%d:%s:%d:%s:%02d.%02d.%02d.%02d.%04d",
				(const char*)spawn->name(),
				deadspawn->spawnId,
				spawn->xPos(),
				spawn->yPos(),
				spawn->zPos(),
				(const char*)time,
				spawnlog_version,
				(const char*)zoneName,
				eqTime.hour,
				eqTime.minute,
				eqTime.month,
				eqTime.day,
				eqTime.year );
	
	*m_stream << output << "\n";
}




PacketLog::PacketLog( const QString& file, bool doLog, const char* name ):
	EQLog( file, doLog, name )

{
	connect( gPacket, SIGNAL( handlePacket(const void*, int) ), this, SLOT( handlePacket(const void*, int) ) );
}

void PacketLog::handlePacket( const void* buffer, int size )
{
	if ( m_log && !this->logPacket( size, (unsigned char*)buffer ) )
		this->doLog( false );
}
	




OpCodeLog::OpCodeLog( const QString& file, bool doLog, const char* name = NULL ):
	EQLog( file, doLog, name )
{
	connect( gPacket, SIGNAL( handleOpCode(const OpCode&, int, void*, unsigned int) ), this, SLOT( handleOpCode(const OpCode&, int, void*, unsigned int) ) );
	connect( gPacket, SIGNAL( unhandledOpCode(const OpCode&, int, void*, unsigned int) ), this, SLOT( unhandledOpCode(const OpCode&, int, void*, unsigned int) ) );
}

bool OpCodeLog::logOpCode( const OpCode& opcode, int direction )
{
	if ( !m_log )
		return false;
		
	QString		output;
	output.sprintf( "OpCode: %2x %2x\t", opcode.code, opcode.version );
	
	*m_stream << output;
	
	if ( direction == FROM_SERVER )
		*m_stream << " <-- to client\n";
	else
		*m_stream << " --> to server\n";



	return true;	

}

void OpCodeLog::handleOpCode( const OpCode& opcode, int direction, void* data, unsigned int len )
{
	if ( m_log )
	{
		if ( !this->logOpCode( opcode, direction ) || !this->logData( len, (unsigned char*)data ) )
			this->doLog( false );

	}
}

void OpCodeLog::unhandledOpCode( const OpCode& /*opcode*/, int /*direction*/, void* /*data*/, unsigned int /*len*/ )
{
	if ( m_log )
	{
//		if ( !this->logOpCode( opcode, direction ) || !this->logData( len, (unsigned char*)data ) )
//			this->doLog( false );
	}
}



void OpCodeLog::addOpCode( const OpCode& opCode )
{
	if ( !m_logOpCodes.contains( opCode ) )
		m_logOpCodes.append( opCode );
}

void OpCodeLog::deleteOpCode( const OpCode& opCode )
{
	if ( m_logOpCodes.contains( opCode ) )
		m_logOpCodes.remove( opCode );
}

void OpCodeLog::editOpCodeList()
{
	OpCodeDlg*		dlg = new OpCodeDlg( m_logOpCodes, NULL, "opcode-dlg" );
	if ( dlg->exec() == QDialog::Accepted )
		;
	delete dlg;
}


SessionLog::SessionLog( const EQInterface* intf, const QString& file, bool doLog, const char* name = NULL ):
	EQLog( file, doLog, name )
{
	connect( intf, SIGNAL(newMessage(const QString&)), this, SLOT(handleNewMessage(const QString&)) );
}


void SessionLog::handleNewMessage( const QString& /*newMessage*/ )
{
//	fprintf( m_logFile, "%s\n", (const char*)newMessage );
//	fflush( m_logFile);
}


EncryptedPacketLog::EncryptedPacketLog( const char* /*basePath*/, bool doLog, const char* name = NULL ):
	EQLog( "", doLog, name )

{
	connect( gPacket, SIGNAL( handlePlayerProfile(const struct playerProfileStruct*) ), this, SLOT( handlePlayerProfile(const struct playerProfileStruct*) ) );
	connect( gPacket, SIGNAL( handleNewSpawn(const struct addSpawnStruct*) ), this, SLOT( handleNewSpawn(const struct addSpawnStruct*) ) );
	connect( gPacket, SIGNAL( handleZoneSpawns(const struct zoneSpawnsStruct*,int) ), this, SLOT( handleZoneSpawns(const struct zoneSpawnsStruct*,int) ) );
}

bool EncryptedPacketLog::openLogFile()
{
/*	bool		ret = true;
	
	QString		base = m_file;





	QString		playerPacketsFile = base + "CODE_CHAR_PROFILE.log";
	QString		spawnPacketsFile =  base + "CODE_NEW_SPAWN.log";
	QString		zoneSpawnsPacketsFile = base + "CODE_ZONE_SPAWNS.log";

	m_playerPacketsFile = fopen( playerPacketsFile, "a" );
	m_spawnPacketsFile = fopen( spawnPacketsFile, "a" );
	m_zoneSpawnsPacketsFile = fopen( zoneSpawnsPacketsFile, "a" );
	
	if ( !m_playerPacketsFile || !m_spawnPacketsFile || !m_zoneSpawnsPacketsFile )
	{
		fclose( m_playerPacketsFile );
		fclose( m_spawnPacketsFile );
		fclose( m_zoneSpawnsPacketsFile );
		m_log = false;
		ret = false;
	}
	
	if ( m_log )
	{
		printf( "Logging CODE_CHAR_PROFILE packets to: %s\n", (const char*)playerPacketsFile );
		printf( "Logging CODE_ZONE_SPAWNS packets to: %s\n", (const char*)zoneSpawnsPacketsFile );
		printf( "Logging CODE_NEW_SPAWN packets to: %s\n", (const char*)spawnPacketsFile );
	}
	
	return ret;
*/
	return false;
}

void EncryptedPacketLog::handlePlayerProfile( const struct playerProfileStruct* /*player*/ )

{
//	if ( m_log )
//		this->logData( m_playerPacketsFile, sizeof( player ), (unsigned char*)player );
}

void EncryptedPacketLog::handleNewSpawn( const struct addSpawnStruct* /*spawn*/ )
{
//	if ( m_log )
//		this->logData( m_spawnPacketsFile, sizeof( spawn ), (unsigned char*)spawn );
}

void EncryptedPacketLog::handleZoneSpawns( const struct zoneSpawnsStruct* /*zspawns*/, int /*count*/ )
{
//	if ( m_log )
//		this->logData( m_zoneSpawnsPacketsFile, sizeof( zspawns ), (unsigned char*)zspawns );
}





DatabaseLog::DatabaseLog( const char* file, bool doLog, const char* name ):
	EQLog( file, doLog, name )
{
}

void DatabaseLog::backfillSpawn( const struct spawnStruct* /*spawn*/ )
{
//	logSpawn();
}

void DatabaseLog::handleNewSpawn( const struct addSpawnStruct* /*spawn*/ )
{
//	logSpawn();
}

void DatabaseLog::handleZoneSpawns( const struct zoneSpawnStruct* /*zspawns*/ )
{
	// queue up
}

void DatabaseLog::handleZoneEnd( const struct clientZoneInStruct* /*newZone*/ )
{
/*
	// Now dequeue all our spawns adding the name
	// of the zone to each one, then processing it.
	while ( m_ZoneSpawns )
	{
		dbSpawn = m_ZoneSpawns->spawn;
		strcpy( dbSpawn->zoneName, gItemMgr.longZoneName() );
		logSpawn( dbSpawn );
		m_ZoneSpawns = m_ZoneSpawns->next;
	}

*/

}

void DatabaseLog::handlePlayerCont( const struct containerPlayerStruct* containp )
{
	if ( !m_log )

		return;
		
	struct itemStruct				itdbhold;
	
	memset( &itdbhold, 0, sizeof( itemStruct ) );
	memcpy( &itdbhold, ((unsigned char*)containp) + 2, sizeof( containerPlayerStruct ) );

	itemdb( &itdbhold );	// ??

}


void DatabaseLog::handlePlayerBook( const struct bookPlayerStruct* bookp )
{
	if ( !m_log )
		return;
		

	struct itemStruct			itdbh;


	memset( &itdbh, 0, sizeof( itemStruct ) );
	memcpy( &itdbh, ((unsigned char*)bookp) + 2, sizeof( bookPlayerStruct ) );

	itemdb( &itdbh );		// ??
}

void DatabaseLog::handleSummonedItem( const struct summonedItemStruct* itemsum )
{
	if ( !m_log )
		return;

		

	this->logItem( itemsum->item );
}

void DatabaseLog::handlePlayerItem( const struct itemPlayerStruct* itemp )
{
	if ( !m_log )
		return;
		
	this->logItem( itemp->item );
}


void DatabaseLog::handleTradeItem( const struct itemReceivedStruct* itemr )
{
	if ( !m_log )
		return;
		
	this->logItem( itemr->item );
}

void DatabaseLog::handleTradeItem2( const struct tradeItemStruct* itemt )
{

	if ( !m_log )
		return;
		
	this->logItem( itemt->item );
}


void DatabaseLog::handleCorpseItem( const struct itemReceivedStruct* itemc )
{
	if ( !m_log )
		return;

		
	this->logItem( itemc->item );
}

void DatabaseLog::logItem( const ItemStruct& item )

{
	if ( !m_log )
		return;
		
	itemdb( &item );
}

#define ITEM_DB		"/usr/local/share/sins/item.db"
#define SPAWN_DB	"/usr/local/share/sins/spawn.db"
#define PET_DB		"/usr/local/share/sins/pet.db"

// saves item to item DB
void itemdb( const struct itemStruct* item )
{
	FILE*				idb;
	struct itemStruct	i;
	bool				found = false;

	// if it exists, return
	if ( ( idb = fopen( ITEM_DB, "r" ) ) != NULL )

	{
		while ( fread( &i, sizeof( itemStruct ), 1, idb ) )
		{
			if ( item->item.itemNr == i.item.itemNr )
			{
				found = true;
				break;
			}
		}
		fclose( idb );
	}

	// else add it to the database
	if ( !found )
	{
		if ( ( idb = fopen( ITEM_DB, "a" ) ) != NULL )
		{
			printf( "New Item: %s(%i)\n", item->item.name, item->item.itemNr );
			fwrite( item, sizeof (itemStruct), 1, idb );
			fclose( idb );
		}
	}
}

// saves spawn to spawn DB
/*
void spawndb( const struct dbSpawnStruct* dbSpawn )
{
	FILE*					sdb;
	struct dbSpawnStruct	s;
	int						found = 0;
	char					thisname[ 256 ];
	char					dbname[ 256 ];

	// Check if this is not a player or a corpse
	if ( dbSpawn->spawn.NPC == 0 || dbSpawn->spawn.NPC == 2 )
		return;

	strcpy( thisname, dbSpawn->spawn.name );
	for ( int a = 0; a < strlen( dbSpawn->spawn.name ); a++ )
		if ( thisname[ a ] <= '9' )
			thisname[ a ] = 0;


	if ( ( sdb = fopen( SPAWN_DB, "r" ) ) != NULL )

	{
		while ( fread( &s, sizeof( dbSpawnStruct ), 1, sdb ) )
		{
			strcpy( dbname, s.spawn.name );
			for ( int a = 0; a < strlen( s.spawn.name ); a++ )

				if ( dbname[ a ] <= '9' )
					dbname[ a ] = 0;
			if (	!strcmp( dbname, thisname ) &&
					( dbSpawn->spawn.maxHp == s.spawn.maxHp ) &&	// added to catch changed guards
					( dbSpawn->spawn.level == s.spawn.level ) &&
					!strcmp( dbSpawn->zoneName, s.zoneName ) )
			{
				found = 1;

				break;
			}
		}
		fclose ( sdb );
	}

	else 

		puts( "Error opening spawn file '" SPAWN_DB "'" );


	if ( !found )
	{
		if ( ( sdb = fopen( SPAWN_DB, "a" ) ) != NULL )
		{
			fwrite( dbSpawn, sizeof( dbSpawnStruct ), 1, sdb );
			fclose( sdb );
		}
		else
			puts( "Error opening spawn file '" SPAWN_DB "'" );
	}
}

void petdb( const struct petStruct* spawn )

{
	FILE*				pdb;
	struct petStruct	s;
	int					found = 0;
	char				dbname[ 256 ];

	if ( ( pdb = fopen( PET_DB, "r" ) ) != NULL )
	{
		while ( fread( &s, sizeof( petStruct ), 1, pdb ) )
		{
			// unique on owner class, owner level and pet level

			if (	( spawn->owner.class_ == s.owner.class_ ) && 
					( spawn->owner.level == s.owner.level ) &&
					( spawn->pet.level == s.pet.level ) )
			{

				found = 1;
				break;
			}
		}
		fclose( pdb );
	}

	if ( !found )
	{
		if ( ( pdb = fopen( PET_DB, "a" ) ) != NULL )
		{
			fwrite( spawn, sizeof( petStruct ), 1, pdb );
				fclose( pdb );

		}
	}   
}
*/


/*
void DatabaseLog::logSpawn( const struct )
{
	// printf("d %s  %i\n", dbSpawn->spawn.name, dbemit);   
	if ( showeq_params->logSpawns ) 
	{
		// send to spawn DB
		// printf("Adding %s to spawn db\n", dbSpawn->spawn.name);
		// This is a pet if petOwnerId isn't 0
		if ( dbSpawn->spawn.petOwnerId != 0 )
				{
			Spawn*		ownerSpawn = gItemMgr.spawnByID( dbSpawn->spawn.petOwnerId );
			if ( ownerSpawn )
			{
				// First see if the pet owner is a player, if so log it in the pet db.
				if ( ownerSpawn.isPC() )
				{
					sPet.owner = ownerSpawn.m_data;
					sPet.pet = dbSpawn->spawn;
					petdb( &sPet );
				}
				// Otherwise its a NPC's pet, just log it for now
				else
					spawndb( dbSpawn );
			}
		}
		else
			spawndb( dbSpawn );
	}
}
*/




OpCodeDlg::OpCodeDlg( QValueList<OpCode>& opCodeList, QWidget* parent, const char* name ):
	QDialog( parent, name, true ),
	m_opCodes( opCodeList )
{
	QHBoxLayout* hBoxLayout = new QHBoxLayout( this );
	hBoxLayout->setAutoAdd( true );
	m_opCodeList = new QListView( this );
	m_opCodeList->setShowSortIndicator( true );
	m_opCodeList->setAllColumnsShowFocus( true );
	m_opCodeList->setSelectionMode( QListView::Single );
	m_opCodeList->addColumn( "Op Code" );
	m_opCodeList->addColumn( "Name" );
	
	QVBox*		vBox = new QVBox( this );
	
	QHBox*		hBox = new QHBox( vBox );
	new QLabel( "Op Code: ", hBox );
	m_opCodeString = new QLineEdit( hBox );
	
	m_addButton = new QPushButton( "Add", vBox );
	m_addButton->setEnabled( false );
	m_deleteButton = new QPushButton( "Delete", vBox );
	m_deleteButton->setEnabled( false );
	m_okButton = new QPushButton( "OK", vBox );

	this->populateOpCodeList();
	
	connect( m_okButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
	connect( m_addButton, SIGNAL( clicked() ), this, SLOT( addOpCode() ) );
	connect( m_deleteButton, SIGNAL( clicked() ), this, SLOT( deleteOpCode() ) );
	connect( m_opCodeString, SIGNAL( textChanged(const QString&) ), this, SLOT( textChanged(const QString&) ) );
	connect( m_opCodeList, SIGNAL( selectionChanged() ), this, SLOT( selectionChanged() ) );
	
	this->setCaption( "Edit Op Codes" );
}

OpCodeDlg::~OpCodeDlg()
{
}

QSize OpCodeDlg::sizeHint() const
{
	return QSize( 500, 300 );
}

void OpCodeDlg::populateOpCodeList()
{
	m_opCodeList->clear();
	this->selectionChanged();
	
	QValueListIterator<OpCode>		it;
	
	for ( it = m_opCodes.begin(); it != m_opCodes.end(); ++it )
	{
		QString		hex;
		hex.sprintf( "%02x %02x", (*it).code, (*it).version );
		QString		text = ::lookupOpCode( *it );
		new QListViewItem( m_opCodeList, hex, text );
	}
}

void OpCodeDlg::textChanged( const QString& newText )
{
	OpCode		code;
	if ( newText.length() && this->getOpCode( newText, code ) )
		m_addButton->setEnabled( true );
	else
		m_addButton->setEnabled( false );
}

void OpCodeDlg::selectionChanged()
{
	if ( m_opCodeList->selectedItem() )
		m_deleteButton->setEnabled( true );
	else
		m_deleteButton->setEnabled( false );
}


bool OpCodeDlg::getOpCode( const QString& string, OpCode& code )
{
	bool		ok;
	
	code.version = 0xFF;
	code.code = 0xFF;
		
	ushort		tmp = string.toUShort( &ok, 16 );
	if ( ok )
	{
		code.version = tmp & 0x00FF;
		code.code = ( tmp >> 8 ) & 0x00FF;
		return true;
	}

	return false;	
}


void OpCodeDlg::addOpCode()
{
	QString		opCodeString = m_opCodeString->text();
	
//	printf( "opCodeString: %s\n", (const char*)opCodeString );
	
	if ( opCodeString.length() )
	{
		OpCode		code;
		if ( this->getOpCode( opCodeString, code ) )
		{
			if ( m_opCodes.findIndex( code ) == -1 )
			{
				m_opCodes.append( code );
				this->populateOpCodeList();
				m_opCodeString->clear();
			}
		}
	}
}

void OpCodeDlg::deleteOpCode()
{
	QListViewItem*		selected = m_opCodeList->selectedItem();
	QString				opCodeString = selected->text( 0 );
	OpCode				opCode;
	
	if ( this->getOpCode( opCodeString, opCode ) )
		m_opCodes.remove( opCode );
	delete selected;
}
