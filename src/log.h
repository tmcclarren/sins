#ifndef EQLOG_H
#define EQLOG_H

//#include <net/if.h>
//#include <netinet/in.h>
//#include <netinet/if_ether.h>

#ifdef __FreeBSD__
#include <sys/types.h>
#include <netinet/in_systm.h>
#include <netinet/in.h>
#endif

#include <netinet/ip.h>
#include <netinet/udp.h>
//#include <arpa/inet.h>

#ifdef	__FreeBSD__
//#include <netinet/in_systm.h>
#else
//#include <net/if_packet.h>
#endif

#include "everquest.h"

#include <stdio.h>
#include <time.h>
#include <qdialog.h>
#include <qfile.h>
#include <qlist.h>
#include <qvaluelist.h>
#include <qtextstream.h>

class QPopupMenu;
class EQInterface;
class EQLog;




void itemdb( const struct itemStruct* item );
void spawndb( const struct dbSpawnStruct* spawn );
void petdb( const struct petStruct* spawn );
QString print_addr( unsigned long addr, unsigned long client_addr = 0 );

// internal structure to keep track of the time that the server sent
// to the client and a time stamp of the packet for further calculation
struct eqTimeStamp
{
	struct timeOfDayStruct	zoneInTime;
	time_t					packetReferenceTime;
};
typedef struct eqTimeStamp EQTimeStamp;

class LogMgr: public QObject
{
Q_OBJECT
public:
	LogMgr( const char* name = NULL );
	
	QPopupMenu*	getLogMenu();

	void addLogger( const EQLog* logger );
	void deleteLogger( const EQLog* logger );
	
	bool getEQTimeOfDay( const time_t timeConvert, struct timeOfDayStruct* eqTimeOfDay );

public slots:
	void handleTime( const struct timeOfDayStruct* tday );

protected:
	EQTimeStamp			m_eqTime;
	QPopupMenu*			m_logMenu;
	QList<EQLog>		m_logs;
};



// generic logger class to allow reuse
class EQLog: public QObject
{
Q_OBJECT
public:
	EQLog( const QString& file, bool doLog, const char* name = NULL );

	~EQLog();
	
	virtual void doLog( bool on );
	
	bool logPacket( int size, unsigned char* buffer );
	
public slots:
	void toggleLog();
	
protected:
	bool logData( unsigned int len, unsigned char* data,
		struct in_addr* saddr = NULL,
		struct in_addr* daddr = NULL,
		unsigned int sport = 0,
		unsigned int dport = 0 );
	
	virtual bool openLogFile();
	
	bool				m_log;
	
	QFile				m_logFile;
	QTextStream*		m_stream;
};


// provides a log of all the sessions spawns, poofs, and kills
class SpawnLog: public EQLog
{
Q_OBJECT
public:
	SpawnLog( const QString& file, bool doLog, const char* name = NULL );

public slots:
	void handleZoneSpawns( const struct zoneSpawnsStruct* zspawns, int len );
	void handleZoneEnd( const struct clientZoneInStruct* newZone );
	void handleNewSpawn( const struct addSpawnStruct* spawn );
	void handleDeleteSpawn( const struct deleteSpawnStruct* delspawn );
	void handleCorpse( const struct spawnKilledStruct* deadspawn );

protected:
};



// provides a log of all the packets -- useful for seeing the whole session
//	in hex and ascii in a more or less human-grokable form
class PacketLog: public EQLog
{
Q_OBJECT
public:
	PacketLog( const QString& fileName, bool doLog, const char* name = NULL );

public slots:
	void handlePacket( const void* buffer, int size );
};


// does the above, only let's you see which way the packet was going, plus
//	shows the op code separated out... in addition, you can filter for
//	only op codes you are interested in
class OpCodeLog: public EQLog
{
Q_OBJECT
public:
	OpCodeLog( const QString& fileName, bool doLog, const char* name = NULL );

	bool logOpCode( const OpCode& opcode, int direction );

	void addOpCode( const OpCode& opCode );
	void deleteOpCode( const OpCode& opCode );
	
public slots:
	virtual void handleOpCode( const OpCode& opcode, int direction, void* data, unsigned int len );
	virtual void unhandledOpCode( const OpCode& opcode, int direction, void* data, unsigned int len );

	virtual void editOpCodeList();
	
protected:
	QValueList<OpCode>		m_logOpCodes;
};


// provides a log of most of the stuff that would appear in your EQ chat
//	window, and some other stuff as well... this is designed to actually
//	interpret the binary stream and print out everything in plain text
class SessionLog: public EQLog
{
Q_OBJECT
public:
	SessionLog( const EQInterface* intf, const QString& file, bool doLog, const char* name = NULL );

public slots:
	void handleNewMessage( const QString& newMessage );
};


class EncryptedPacketLog: public EQLog
{
Q_OBJECT
public:
	EncryptedPacketLog( const char* basePath, bool doLog, const char* name = NULL );

public slots:
	void handleNewSpawn( const struct addSpawnStruct* spawn );
	void handleZoneSpawns( const struct zoneSpawnsStruct* zspawns, int count );

	void handlePlayerProfile( const struct playerProfileStruct* player );
protected:
	virtual bool openLogFile();

	FILE*		m_playerPacketsFile;	
	FILE*		m_spawnPacketsFile;
	FILE*		m_zoneSpawnsPacketsFile;
};




struct dbSpawnList
{
	struct dbSpawnList*		next;
	dbSpawnStruct*			spawn;
};


// at some point this will interface to an SQL-ized database (maybe client-server,
//	to mysqld running on the local host or even across a network)
class DatabaseLog: public EQLog
{
Q_OBJECT
public:
	DatabaseLog( const char* file, bool doLog, const char* name = NULL );

public slots:
	void logItem( const ItemStruct& item );
	
	void handleNewSpawn( const struct addSpawnStruct* spawn );
	void handleZoneSpawns( const struct zoneSpawnStruct* zspawns );
	void handleZoneEnd( const struct clientZoneInStruct* newZone );
	void backfillSpawn( const struct spawnStruct* spawn );

	void handlePlayerCont( const struct containerPlayerStruct* containp );
	void handlePlayerBook( const struct bookPlayerStruct* bookp );

	void handleSummonedItem( const struct summonedItemStruct* itemsum );
	void handlePlayerItem( const struct itemPlayerStruct* itemp );
	void handleTradeItem( const struct itemReceivedStruct* itemr );
	void handleTradeItem2( const struct tradeItemStruct* itemt );
	void handleCorpseItem( const struct itemReceivedStruct* itemc );
	
protected:
	dbSpawnList*				m_ZoneSpawns;
};

class QListView;
class QPushButton;
class QLineEdit;

class OpCodeDlg: public QDialog
{
Q_OBJECT
public:
	OpCodeDlg::OpCodeDlg( QValueList<OpCode>& opCodeList, QWidget* parent = NULL, const char* name = NULL );
	OpCodeDlg::~OpCodeDlg();
	
	QSize sizeHint() const;
	bool getOpCode( const QString& string, OpCode& code );

public slots:
	void textChanged( const QString& newText );
	void selectionChanged();
	void addOpCode();
	void deleteOpCode();
	
protected:
	void populateOpCodeList();
	
	QValueList<OpCode>&	m_opCodes;
	QListView*		m_opCodeList;
	QPushButton*	m_addButton;
	QPushButton*	m_deleteButton;
	QPushButton*	m_okButton;
	QPushButton*	m_cancelButton;
	QLineEdit*		m_opCodeString;
};

#endif

