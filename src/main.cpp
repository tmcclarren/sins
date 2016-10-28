//	main.cpp
//		SINS Distributed under GPL

// main.cpp is the entrypoint to SINS, it parses the commandline
// options and initializes the application

#include <qapplication.h>
#include <qwindowsstyle.h>
#include <qfile.h>
#include <qdir.h>

#include "main.h"
#include "interface.h"
#include "preferences.h"	// prefrence file class

#include "packet.h"
#include "player.h"
#include "itemmgr.h"
#include "log.h"
#include "map.h"
#include "spawnmonitor.h"
#include "spells.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <getopt.h>			// for long GNU-style options


// **********************************
// defines used for option processing 
// **********************************

#define OPTION_LIST "i:rvf:g::j::u:s:aedo:RCp:ncFAGKSVPNbtTL:xWX:Y:Z:"

// for long options without any short (single letter) equivalent, we'll
// assign single char nonprinting character equivalents, as is common
// for many GNU utilities

#define  VERSION_OPTION              10
#define  IPADDR_OPTION               11
#define  MACADDR_OPTION              12
#define  GLOBAL_LOG_FILENAME_OPTION  13
#define  ZONE_LOG_FILENAME_OPTION    14
#define  UNKNOWN_LOG_FILENAME_OPTION 15
#define  GLOBAL_LOG_OPTION           16
#define  ZONE_LOG_OPTION             17
#define  UNKNOWN_ZONE_LOG_OPTION     18
#define  PLAYBACK_SPEED_OPTION       19
#define  SHOW_MAP_POINTS_OPTION      20
#define  ENCRYPTED_LOG_FILE_OPTION   21
#define  ENCRYPTED_LOG_OPTION        22
#define  SYSTIME_SPAWNTIME_OPTION    23
#define  SPAWNLOG_FILENAME_OPTION    24
#define  DISABLE_SPAWNLOG_OPTION     25

// note that ASCII 32 is a space, best to stop at 31 and pick up again
// at 128 or higher

// add your options here
//	format:
//		<long option name>,
//		<no_argument|optional_argument|required_argument>,
//		NULL,
//		<single option char or unprintable number like VERSION_OPTION>
static struct option option_list[] = {
	{ "broken-decode",				no_argument,		NULL,	'b' },
	{ "despawn-alert",				no_argument,		NULL,	'd' },
	{ "filter-file",				required_argument,	NULL,	'f' },
	{ "record-filename",			optional_argument,	NULL,	'g' },
	{ "help",						no_argument,		NULL,	'h' },
	{ "net-interface",				required_argument,	NULL,	'i' },
	{ "playback-filename",			optional_argument,	NULL,	'j' },
	{ "font-size",					required_argument,	NULL,	'p' },
	{ "framerate",					required_argument,	NULL,	'u' },
	{ "filter-case-sensitive",		no_argument,		NULL,	'C' },
	{ "show-packet-numbers",		no_argument,		NULL,	'N' },
	{ "no-promiscuous",				no_argument,		NULL,	'P' },
	{ "version",					no_argument,		NULL,	VERSION_OPTION },
	{ "playback-speed",				required_argument,	NULL,	PLAYBACK_SPEED_OPTION },
	{ "ip-address",					required_argument,	NULL,	IPADDR_OPTION },
	{ "mac-address",				required_argument,	NULL,	MACADDR_OPTION },
	{ "global-log-filename",		required_argument,	NULL,	GLOBAL_LOG_FILENAME_OPTION },
	{ "zone-log-filename",			required_argument,	NULL,	ZONE_LOG_FILENAME_OPTION },
	{ "unknown-log-filename",		required_argument,	NULL,	UNKNOWN_LOG_FILENAME_OPTION },
	{ "log-all",					no_argument,		NULL,	GLOBAL_LOG_OPTION },
	{ "log-zone",					no_argument,		NULL,	ZONE_LOG_OPTION },
	{ "log-unknown",				no_argument,		NULL,	UNKNOWN_ZONE_LOG_OPTION },
	{ "encrypted-log-filebase",		required_argument,	NULL,	ENCRYPTED_LOG_FILE_OPTION },
	{ "log-encrypted",				no_argument,		NULL,	ENCRYPTED_LOG_OPTION },
	{ "systime-spawntime",			no_argument,		NULL,	SYSTIME_SPAWNTIME_OPTION },
	{ "spawnlog-filename",			required_argument,	NULL,	SPAWNLOG_FILENAME_OPTION },
	{ "disable-spawnlog",			no_argument,		NULL,	DISABLE_SPAWNLOG_OPTION },
	{ 0, 0, 0, 0 }
};

bool findHomeConfDir( QString& homeDirPath )
{
	homeDirPath = QDir::homeDirPath();
	homeDirPath += "/.sins";

	QDir		homeDir( homeDirPath );

	if ( homeDir.exists() )
		return true;
	else
	{
		homeDirPath = "";
		return false;
	}
}
	
// prefName is the name to look up in the preferences object
// fileName is the name of the file, without the path
// look up the path in preferences, check to see if it exists,
// if not, look up the path "~<user>/.sins/<filename>", if that doesn't
// exist, lookup the path "<CONFDIR>/<filename>"
QString findConfigurationFile( const QString& section, const QString& prefName, const QString& fileName )
{
	QString		prefPath;
	QFile		temp;
	
	if ( gSEQPrefs->isPreference( prefName, section ) )
	{
		prefPath = gSEQPrefs->getPrefString( prefName, section );
		temp.setName( prefPath );
		printf( "testing: %s\n", (const char*)prefPath );
		if ( temp.exists() )
			return prefPath;
	}

	bool hasHome = findHomeConfDir( prefPath );
	prefPath += "/";
	prefPath += fileName;

	temp.setName( prefPath );
	
	if ( hasHome && temp.exists() )
	{
		gSEQPrefs->setPrefString( prefName, section, prefPath, false );
		return prefPath;
	}
	
	prefPath = CONFDIR;
	prefPath += fileName;
	
	gSEQPrefs->setPrefString( prefName, section, prefPath, false );
	return prefPath;
}

// global parameters, so all parts of SINS have access to it
Player*						gPlayer = NULL;
ItemMgr*					gItemMgr = NULL;
GroupMgr*					gGroupMgr = NULL;
EQPacket*					gPacket = NULL;
FilterMgr*					gFilterMgr = NULL;
Alerter*					gAlerter = NULL;
PreferenceFile*				gSEQPrefs = NULL;
MapMgr*						gMapMgr = NULL;
LogMgr*						gLogMgr = NULL;
SpawnMonitor*				gSpawnMonitor = NULL;
SpellMgr*					gSpellMgr = NULL;
EQInterface*				gInterface = NULL;

int main( int argc, char** argv )
{
	int					opt;
	int					o_help = 0;
	int					option_index = 0;

	// print the version number
	printf( "SINS %s, released under the GPL.\n", VERSION );

	// initialize the parameters with default values
	QString 	configfile;
	QFile		temp;
	
	bool		hasHome = findHomeConfDir( configfile );
	configfile += "/sins.conf";
	
	temp.setName( configfile );
	if ( !hasHome || !temp.exists() )
	{
		configfile = CONFDIR "/sins.conf";
		temp.setName( configfile );
		if ( !temp.exists() )
			configfile = CONFDIR "/showeq.conf";
	}
	
	// scan command line arguments for a specified config file
	int i = 1;
	while ( i < argc )
	{
		if ( ( argv[ i ][ 0 ] == '-') && ( argv[ i ][ 1 ] == 'o' ) )
			configfile = argv[ i + 1 ];
		i++;
	}

	// see preference.cpp for info on how to use preferences class
	printf( "Using config file '%s'\n", (const char*)configfile );

	gSEQPrefs = new PreferenceFile( configfile );

	QString		spawnFilter = findConfigurationFile( "Filters", "SpawnFilterFile", "filters.conf" );
	QString		alertFilter = findConfigurationFile( "Filters", "SpawnAlertFile", "alerts.conf" );
	
	printf( "Using SpawnFilter file '%s'\n", (const char*)spawnFilter );
	printf( "Using Alert file '%s'\n", (const char*)alertFilter );

	// decoder override for coping with encryption changes
#if HAVE_LIBEQ
	if ( gSEQPrefs->getPrefBool( "BrokenDecode", "Misc", false ) )
		printf("Disabling decoder due to sins.conf preferences\n");
#else
	// default to broken decoder if libEQ not present
	gSEQPrefs->setPrefBool( "BrokenDecode", "Misc", true, false );
	printf( "Disabling decoder due to missing libEQ.a\n" );
#endif

	// parse the commandline for commandline parameters
	while ( ( opt = getopt_long( argc, argv, OPTION_LIST, option_list, &option_index ) ) != -1 )
	{
		switch ( opt )
		{
			case 'o':
				// config file was already taken care of, ignore
			break;
			
			case 'd':
				// set the request to alert on despawns
				gSEQPrefs->setPrefBool( "DeSpawnAlert", "Filters", true, false );
			break;
			
			case 'i':
				// set the interface
				if ( optarg )
					gSEQPrefs->setPrefString( "Device", "Network", optarg, false );
			break;
			
			case 'f':
				// set the spawn filter file
				if ( optarg )
					gSEQPrefs->setPrefString( "SpawnFilterFile", "Filters", optarg, false );
			break;
			
			case 'j':
				// packet playback mode
				if ( optarg )
					gSEQPrefs->setPrefString( "Filename", "VPacket", optarg, false );
				gSEQPrefs->setPrefBool( "Playback", "VPacket", true, false );
				gSEQPrefs->setPrefBool( "Record", "VPacket", false, true );
			break;
			
			case 'g':
				// packet record mode
				if ( optarg )
					gSEQPrefs->setPrefString( "Filename", "VPacket", optarg, false );
				gSEQPrefs->setPrefBool( "Playback", "VPacket", false, false );
				gSEQPrefs->setPrefBool( "Record", "VPacket", true, false );
			break;
			
			case 'u':
				// set framerate
				gSEQPrefs->setPrefInt( "Framerate", "Map", atoi( optarg ), false );
			break;
			
			case 'a':
				// enable use of enlightenment audio
				gSEQPrefs->setPrefBool( "SpawnFilterAudio", "Filters", true, false );
			break;
			
			case 'R':
				// use regular expressions for filter
				gSEQPrefs->setPrefBool( "SpawnFilterRegex", "Filters", true, false );
			break;
			
			case 'C':
				// make filter case sensitive
				gSEQPrefs->setPrefBool( "SpawnFilterIsCaseSensitive", "Filters", true, false );
			break;
			
			case 'p':
				// set point size of skills and spawn font
				gSEQPrefs->setPrefInt( "Fontsize", "Interface", atoi( optarg ), false );
			break;
			
			case 'A':
				// cool spawn alert
				gSEQPrefs->setPrefBool( "AlertInfo", "Filters", true, false );
			break;
			
			case 'P':
				// don't use Promiscuous mode on sniffing
				gSEQPrefs->setPrefBool( "NoPromiscuous", "Network", false, false );
			break;
			
			case 'N':
				// show net info
				gSEQPrefs->setPrefBool( "NetStats", "Interface", true, false );
			break;
			
			case 'b':
				// 'b'roken decode -- don't deal with spawn packets
				gSEQPrefs->setPrefBool( "BrokenDecode", "Misc", true, false );
				printf( "Disabling decoder due to command-line parameter\n" );
			break;
			
			case VERSION_OPTION:
				printf( "SINS %s\n", VERSION );
				printf( "SINS comes with NO WARRANTY.\n" );
				printf( "You may redistribute copies of SINS under the terms of\n" );
				printf( "The GNU General Public License.\n" );
				printf( "For updates and information, please visit Owl Boy\n" );
				exit( 0 );
			break;

			case IPADDR_OPTION:
				// IP address to track
				gSEQPrefs->setPrefString( "IP", "Network", optarg, false );
			break;

			case MACADDR_OPTION:
				// MAC address to track for those on DHCP
				gSEQPrefs->setPrefString( "MAC", "Network", optarg, false );
			break;

			case GLOBAL_LOG_FILENAME_OPTION:
				// filename for logging all packets
				gSEQPrefs->setPrefString( "GlobalLogFilename", "Log", optarg, false );
			break;

			case ZONE_LOG_FILENAME_OPTION:
				// filename for logging zone change packets
				gSEQPrefs->setPrefString( "ZoneLogFilename", "Log", optarg, false );
			break;

			case UNKNOWN_LOG_FILENAME_OPTION:
				// filename for logging unknown zone change packets
				gSEQPrefs->setPrefString( "UnknownZoneLogFilename", "Log", optarg, false );
			break;

			case GLOBAL_LOG_OPTION:
				// log everything
				gSEQPrefs->setPrefBool( "LogAllPackets", "Log", true, false );
			break;

			case ZONE_LOG_OPTION:
				// log all zone change packets
				gSEQPrefs->setPrefBool( "LogZonePackets", "Log", true, false );
			break;

			case UNKNOWN_ZONE_LOG_OPTION:
				// log only unfamiliar zone change packets
				gSEQPrefs->setPrefBool( "LogUnknownZonePackets", "Log", true, false );
			break;

			case PLAYBACK_SPEED_OPTION:
				gSEQPrefs->setPrefInt( "PlaybackRate", "VPacket", atoi( optarg ), false );
			break;

			case ENCRYPTED_LOG_FILE_OPTION:
				gSEQPrefs->setPrefString( "EncryptedLogFilenameBase", "Log", optarg, false );
			break;

			case ENCRYPTED_LOG_OPTION:
				gSEQPrefs->setPrefBool( "LogEncrypted", "Log", true, false );
			break;

			case SYSTIME_SPAWNTIME_OPTION:
				gSEQPrefs->setPrefBool( "SystimeSpawntime", "Interface", true, false );
			break;

			case SPAWNLOG_FILENAME_OPTION:
				gSEQPrefs->setPrefString( "SpawnLogFilename", "Log", optarg, false );
			break;

			case DISABLE_SPAWNLOG_OPTION:
				gSEQPrefs->setPrefBool( "LogSpawns", "Log", false, true );
			break;

			case 'h': 
			// fall through
			default:
				// default, spit out the help
				o_help = 1;
		}
	}

	if ( optind < ( argc - 1 ) )
	{
		// if there were arguments we did not understand, print out the help
		o_help = 1;
	}

	if ( o_help )
	{
		// the default help text
		printf( "Usage:\n  %s [<options>] [<client IP address>]\n\n", argv[ 0 ] );
		printf( "  -h, --help                     shows this help\n" );
		printf( "  -o CONFIGFILE                  alternate sins.conf pathname\n" );
		printf( "      --version                  prints SINS version number\n" );
		printf( "  -i, --net-interface=DEVICE     specify which network device to bind to\n" );
		printf( "  -f, --filter-file=FILENAME     sets spawn filter file\n" );
		printf( "  -d, --despawn-alert            enables de-spawn alerting\n" ); 
		printf( "  -C, --filter-case-sensitive    spawn alert and filter is case sensitive\n" );
		printf( "  -p, --font-size=SIZE           sets the point size of the skill and spawn\n" );
		printf( "                                 table fonts\n" );
		printf( "  -u, --framerate=FPS            framerate of updates (default 5fps)\n" );
		printf( "  -P, --no-promiscuous           don't sniff the network in promiscuous mode\n" );
		printf( "  -N, --show-packet-numbers      show network info dialog\n" );
		printf( "  -j, --playback-file=FILENAME   playback packets from FILENAME prev recorded\n" );
		printf( "                                 with -g option\n" );
		printf( "      --playback-speed=SPEED     -1 = paused  0 = max  1 = slow  9 = fast\n" );
		printf( "  -g, --record-file=FILENAME     record packets to FILENAME to playback with\n" );
		printf( "                                 -j option\n" );
		printf( "  -b, --broken-decode            broken decode -- don't decode spawn packets\n" );
		printf( "  -x, --log-spawns               log spawns into spawns.db\n" );
		printf( "      --systime-spawntime        show spawn time using UNIX systtem time\n" );
		printf( "      --ip-address=IP            client IP address\n" );
		printf( "      --mac-address=MAC          client MAC address as 00:00:00:00:00:00\n" );
		printf( "      --log-all                  log all packets to global logfile\n" );
		printf( "      --global-log-filename=FILE use FILE for above packet logging\n" );
		printf( "      --log-zone                 like --log-all, but only zone data\n" );
		printf( "      --zone-log-filename=FILE   use FILE for above packet logging\n" );
		printf( "      --log-unknown              log only unrecognized zone data\n" );
		printf( "      --unknown-log-filename=FILE use FILE for above packet logging\n" );
		printf( "      --log-encrypted            log some unprocessed encrypted data\n" );
		printf( "      --encrypted-log-filebase=FILE use FILE as base for above logging\n" );
		printf( "      --disable-spawnlog         disable spawn logging to spawnlog.txt\n" );
		printf( "      --spawnlog-filename=FILE   use FILE instead of spawnlog.txt\n" );
		exit ( 0 );
	}

	// create application instance
	QApplication				qapp( argc, argv );

	QApplication::setStyle( new QWindowsStyle() );
	
	int fontSize = gSEQPrefs->getPrefInt( "Fontsize", "Interface", 8 );
	
	QApplication::setFont( QFont( "Helvetica",  fontSize ) );

	QString filterFile = gSEQPrefs->getPrefString( "SpawnFilterFile", "Filters" );
	QString	alertFile = gSEQPrefs->getPrefString( "SpawnAlertFile", "Filters" );

	gPacket = new EQPacket( "packet" );	
	gPlayer = new Player( gPacket, "player" );
	gFilterMgr = new FilterMgr( filterFile, GameItem::k_filtered, "filter-mgr" );
	gItemMgr = new ItemMgr( gPacket, "item-mgr" );
	gAlerter = new Alerter( alertFile );
	gGroupMgr = new GroupMgr( "group-mgr" );
	gMapMgr = new MapMgr( "map-mgr" );
	gLogMgr = new LogMgr( "log-mgr" );
	gSpawnMonitor = new SpawnMonitor( "spawn-monitor" );
	gSpellMgr = new SpellMgr( "spell-mgr" );

	QObject::connect( gFilterMgr, SIGNAL(filtersChanged()), gItemMgr, SLOT(filtersChanged()) );
	QObject::connect( gAlerter, SIGNAL(filtersChanged()), gItemMgr, SLOT(filtersChanged()) );
	QObject::connect( gItemMgr, SIGNAL(processSpawn(Spawn*)), gFilterMgr, SLOT(processSpawn(Spawn*)) );
	QObject::connect( gItemMgr, SIGNAL(processSpawn(Spawn*)), gAlerter, SLOT(processSpawn(Spawn*)) );
	QObject::connect( gItemMgr, SIGNAL(addSpawn(Spawn*)), gAlerter, SLOT(addSpawn(Spawn*)) );
	QObject::connect( gItemMgr, SIGNAL(deleteSpawn(Spawn*)), gAlerter, SLOT(deleteSpawn(Spawn*)) );
	QObject::connect( gItemMgr, SIGNAL(killSpawn(Spawn*)), gAlerter, SLOT(killSpawn(Spawn*)) );
	
	if ( gSEQPrefs->getPrefBool( "BrokenDecode", "Misc", true ) )
		printf( "\
***DECRYPTION DISABLED***\n\
Decoder has been manually disabled by either -b, the BrokenDecode option,\n\
or a missing libEQ.a library.\n"\
		 );

	if ( optind != argc )
		gSEQPrefs->setPrefString( "IP", "Network", argv[ optind ], false );

	// the main interface widget
	gInterface = new EQInterface( NULL, "interface" );
	
	qapp.setMainWidget( gInterface );

	// start the packet capturing
	gPacket->start( 10 );

	int ret = qapp.exec();

	printf( "quit\n" );
	gInterface->savePrefs();
	delete gInterface;
	gInterface = NULL;	
	delete gSpellMgr;
	gSpellMgr = NULL;
	delete gMapMgr;
	gMapMgr = NULL;
	delete gGroupMgr;
	gGroupMgr = NULL;
	delete gAlerter;
	gAlerter = NULL;
	delete gItemMgr;
	gItemMgr = NULL;
	delete gFilterMgr;
	gFilterMgr = NULL;
	delete gPlayer;
	gPlayer = NULL;
	delete gPacket;
	gPacket = NULL;

	gSEQPrefs->save();
	delete gSEQPrefs;
	gSEQPrefs = NULL;
	
	return ret;
}
