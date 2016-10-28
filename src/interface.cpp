// interface.cpp
//	SINS Distributed under GPL

#include "main.h"
#include "preferences.h"
#include "basewindow.h"
#include "bigtextwindow.h"
#include "category.h"
#include "compass.h"
#include "dropwindow.h"
#include "experience.h"
#include "filter.h"
#include "interface.h"
#include "itemmgr.h"
#include "log.h"
#include "map.h"
//#include "msgdlg.h"
#include "packet.h"
#include "skilllist.h"
#include "spawnlist.h"
#include "spawnmonitor.h"
#include "spawnpointlist.h"
#include "spells.h"
#include "statlist.h"
#include "util.h"

#include <qapplication.h>
#include <qcheckbox.h>
#include <qcombobox.h>
#include <qdatetime.h>
#include <qfont.h>
#include <qhbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qlistview.h>
#include <qlayout.h>
#include <qlcdnumber.h>
#include <qmessagebox.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qpushbutton.h>
#include <qspinbox.h>
#include <qsplitter.h>
#include <qstatusbar.h>
#include <qtimer.h>
#include <qvbox.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// the main interface widget
EQInterface::EQInterface( QWidget* parent, const char* name ):
	QMainWindow( parent, name )
{
#ifdef DEBUG
//	debug( "EQInterface::EQInterface()" );
#endif
	m_stsbarStatus = NULL;
	m_stsbarZone = NULL;
	m_stsbarSpawns = NULL;
	m_stsbarExp = NULL;
	m_stsbarPkt = NULL;

	m_spawnList = NULL;
	m_lastMap = NULL;
	
	for ( int i = 0; i < MAX_MAPS; i++ )
		m_map[ i ] = NULL;
		
	this->setFont( QApplication::font() );
	
	// the first call to menuBar() makes it exist
	menuBar()->setSeparator( QMenuBar::InWindowsStyle );

	this->__createSplitters();
	this->__createChildren();
	this->__createStatusBar();
	this->__createBigTextWindow();
	this->__createCompassWindow();
	this->__createDropWindow();
	this->__createExperienceWindow();
	this->__createSkillsWindow();
	this->__createStatWindow();
	this->__createSpawnPointWindow();
	this->__createMessageBoxes();
	this->__createMenus();
//	this->__restoreSplitterSizes();
	this->__restoreWindow();
	
//	new MessageLog( this, "~/messages.log", true, "message-log" );

	if ( m_stsbarZone )
	{
		connect( gItemMgr, SIGNAL( zoneChanged(const QString&) ), m_stsbarZone, SLOT( setText(const QString&) ) );
		connect( gItemMgr, SIGNAL( zoneEnd(const QString&) ), m_stsbarZone, SLOT( setText(const QString&) ) );
	}
	
	if ( m_stsbarExp )
		connect( gPlayer, SIGNAL( expChangedString(const QString&) ), m_stsbarExp, SLOT( setText(const QString&) ) );

	if ( m_stsbarStatus )
		connect( this, SIGNAL( newMessage(const QString&) ), m_stsbarStatus, SLOT( setText(const QString&) ) );
		
	if ( m_stsbarSpawns )
		connect( gItemMgr, SIGNAL( numSpawns(int) ), SLOT( numSpawns(int) ) );

	if ( m_stsbarPkt )
		connect( gPacket, SIGNAL( numPacket(int) ), SLOT( numPacket(int) ) );

	connect( gPacket, SIGNAL(captureTargetChanged(const QString&,const QString&)),		SLOT(captureTargetChanged(const QString&,const QString&)));
	connect( gPacket, SIGNAL(handleMoney(const void*)), 								SLOT(handleMoney(const void*)));
	connect( gPacket, SIGNAL(handleMoneyUpdate(const struct moneyUpdateStruct*)),		SLOT(handleMoneyUpdate(const struct moneyUpdateStruct*)));
	connect( gPacket, SIGNAL(handleSysMsg(const struct systemMessageStruct*)),			SLOT(handleSysMsg(const struct systemMessageStruct*)));
	connect( gPacket, SIGNAL(handleBeginCast(const struct beginCastStruct*)),			SLOT(handleBeginCast(const struct beginCastStruct*)));
	connect( gPacket, SIGNAL(handleSpecialMsg(const struct spMesgStruct*)),				SLOT(handleSpecialMsg(const struct spMesgStruct*)));
	connect( gPacket, SIGNAL(handlePlayerCont(const struct containerPlayerStruct*)),	SLOT(handlePlayerCont(const struct containerPlayerStruct*)));
	connect( gPacket, SIGNAL(handlePlayerBook(const struct bookPlayerStruct*)),			SLOT(handlePlayerBook(const struct bookPlayerStruct*)));
	connect( gPacket, SIGNAL(handleEmote(const struct emoteTextStruct*)),				SLOT(handleEmote(const struct emoteTextStruct*)));
	connect( gPacket, SIGNAL(handleChannelMsg(const struct channelMessageStruct*)),		SLOT(handleChannelMsg(const struct channelMessageStruct*)));
	connect( gPacket, SIGNAL(handleSummonedItem(const struct summonedItemStruct*)),		SLOT(handleSummonedItem(const struct summonedItemStruct*)));
	connect( gPacket, SIGNAL(handlePlayerItem(const struct itemPlayerStruct*)),			SLOT(handlePlayerItem(const struct itemPlayerStruct*)));
	connect( gPacket, SIGNAL(handleTradeItem( const struct itemReceivedStruct*)),		SLOT(handleTradeItem(const struct itemReceivedStruct*)));
	connect( gPacket, SIGNAL(handleTradeItem2(const struct tradeItemStruct*)),			SLOT(handleTradeItem2(const struct tradeItemStruct*)));
	connect( gPacket, SIGNAL(handleCorpseItem(const struct itemReceivedStruct*)),		SLOT(handleCorpseItem(const struct itemReceivedStruct*)));
	connect( gPacket, SIGNAL(handleShopItem(const struct itemShopStruct*)),				SLOT(handleShopItem(const struct itemShopStruct*)));
	connect( gPacket, SIGNAL(handleClientTarget(const struct clientTargetStruct*)),		SLOT(handleClientTarget(const struct clientTargetStruct*)));
	connect( gPacket, SIGNAL(handleAttack1(const struct attack1Struct*)),				SLOT(handleAttack1(const struct attack1Struct*)));
	connect( gPacket, SIGNAL(handleAttack2(const struct attack2Struct*)),				SLOT(handleAttack2(const struct attack2Struct*)));
	connect( gPacket, SIGNAL(handleHPUpdate(const struct spawnHpUpdateStruct*)),		SLOT(handleHPUpdate(const struct spawnHpUpdateStruct*)));
	connect( gPacket, SIGNAL(handleInspect(const struct inspectingStruct*)),			SLOT(handleInspect(const struct inspectingStruct*)));
	connect( gPacket, SIGNAL(handleRandom(const struct randomStruct*)),					SLOT(handleRandom(const struct randomStruct*)));
	connect( gPacket, SIGNAL(handleConsRequest(const struct considerStruct*)),			SLOT(handleConsRequest(const struct considerStruct*)) );
	connect( gPacket, SIGNAL(handleConsMessage(const struct considerStruct*)),			SLOT(handleConsMessage(const struct considerStruct*)) );
}

EQInterface::~EQInterface()
{
	delete m_bigTextWindow;
	m_bigTextWindow = NULL;
	delete m_compass;
	m_compass = NULL;
	delete m_dropWindow;
	m_dropWindow = NULL;
	delete m_expWindow;
	m_expWindow = NULL;
	delete m_skills;
	m_skills = NULL;
	delete m_stats;
	m_stats = NULL;
	delete m_spawnPointWindow;
	m_spawnPointWindow = NULL;
	
	for ( int i = 0; i < MAX_MAPS; i++ )
	{
		if ( !m_map[ i ].isNull() )
		{
			delete (MapWindow*) m_map[ i ];
			m_map[ i ] = NULL;
		}
	}	
}

void EQInterface::__createStatusBar()
{
	// the first call to statusBar() makes it exist
	statusBar()->clear();
	statusBar()->setFont( QApplication::font() );
	statusBar()->setSizeGripEnabled( false );
	
	if ( gSEQPrefs->getPrefBool( "ShowStatus", "StatusBar", false ) )
	{
		m_stsbarStatus = new QLabel( statusBar(), "Status" );
		m_stsbarStatus->setText( "Waiting..." );
		m_stsbarStatus->setMinimumHeight( m_stsbarStatus->sizeHint().height() );
		m_stsbarStatus->setMinimumWidth( 100 );
		statusBar()->addWidget( m_stsbarStatus, 8 );
	}

	if ( gSEQPrefs->getPrefBool( "ShowZone", "StatusBar", false ) )
	{
		m_stsbarZone = new QLabel( statusBar(), "Zone" );
		m_stsbarZone->setText( "Zone: [unknown]" );
		m_stsbarZone->setMinimumHeight( m_stsbarZone->sizeHint().height() );
		statusBar()->addWidget( m_stsbarZone, 2, true );
	}

	if ( gSEQPrefs->getPrefBool( "ShowSpawns", "StatusBar", false ) )
	{
		m_stsbarSpawns = new QLabel( statusBar(), "Mobs" );
		m_stsbarSpawns->setText( "Mobs:" );
		m_stsbarSpawns->setMinimumHeight( m_stsbarSpawns->sizeHint().height() );
		statusBar()->addWidget( m_stsbarSpawns, 1, true );
	}

	if ( gSEQPrefs->getPrefBool( "ShowExp", "StatusBar", false ) )
	{
		m_stsbarExp = new QLabel( statusBar(), "Exp" );
		m_stsbarExp->setText( "Exp [unknown]" );
		m_stsbarExp->setMinimumHeight( m_stsbarExp->sizeHint().height() );
		statusBar()->addWidget( m_stsbarExp, 1, true );
	}

	if ( gSEQPrefs->getPrefBool( "ShowPacketCounter", "StatusBar", false ) )
	{
		m_stsbarPkt = new QLabel( statusBar(), "Pkt" );
		m_stsbarPkt->setText( "Pkt 0" );
		m_stsbarPkt->setMinimumHeight( m_stsbarPkt->sizeHint().height() );
		statusBar()->addWidget( m_stsbarPkt, 0, true );
	}
}

void EQInterface::__createSplitters()
{
	// main widgets
	// make a VBox to use as central widget
	QVBox*	centralBox = new QVBox( this );
	this->setCentralWidget( centralBox );

	// make the horizontal splitter dividing the map from the other objects
	// and add it to the main window
//	m_splitH = new QSplitter( QSplitter::Horizontal, centralBox, "SplitH" );
//	m_splitH->setOpaqueResize( true );
}

void EQInterface::__createMenus()
{
#ifdef DEBUG
//	debug( "EQInterface::__createMenus()" );
#endif

	menuBar()->setFont( QApplication::font() );
	
	// file menu
	QPopupMenu* menu = new QPopupMenu;
	menu->setFont( QApplication::font() );

//	menu->insertItem( "Dump Spawns", gItemMgr,				SLOT( dumpSpawns() ) );
//	menu->insertItem( "Dump Drops", gItemMgr,				SLOT( dumpDrops() ),				CTRL + Key_D );
//	menu->insertItem( "Dump Coins", gItemMgr,				SLOT( dumpCoins() ) );	

//	menu->insertItem( "Create MessageBox", this,			SLOT( createMessageBox() ),			Key_F11 );
	
	if ( ( gSEQPrefs->getPrefBool( "Playback", "VPacket", false ) ) || ( gSEQPrefs->getPrefBool( "Record", "VPacket", false ) ) )
	{
		menu->insertItem( "Inc Playback Speed", gPacket,	SLOT( incPlayback() ),				CTRL + Key_BracketRight );
		menu->insertItem( "Dec Playback Speed", gPacket,	SLOT( decPlayback() ),				CTRL + Key_BracketLeft );
	}
	menu->insertItem( "&Save Settings", gSEQPrefs,			SLOT( save() ),			CTRL + Key_S );
	menu->insertItem( "&Quit", qApp,						SLOT( quit() ) );
	menuBar()->insertItem( "&File", menu );

	// map menu
	menu = new QPopupMenu;
  	menu->insertItem( "&Open Map",		gMapMgr,		SLOT( loadMap() ),			CTRL + Key_O );
 	menu->insertItem( "&Save Map",		gMapMgr,		SLOT( saveMap() ),			CTRL + Key_M );
	menu->insertItem( "Save Spawn Points", gSpawnMonitor, SLOT( saveSpawnPoints() ), CTRL + Key_P );
//	menu->insertItem( "Load Spawn Points", gSpawnMonitor, SLOT( loadSpawnPoints() ) );
	menu->insertSeparator();
  	menu->insertItem( "Add Location",	gMapMgr,		SLOT( addLocation() ),		ALT + Key_O );
  	menu->insertItem( "Add &Line",		gMapMgr,		SLOT( startLine() ),		ALT + Key_L );
  	menu->insertItem( "Add Line &Point",	gMapMgr,	SLOT( addLinePoint() ),		ALT + Key_P );
  	menu->insertItem( "&Del Line Point",	gMapMgr,	SLOT( delLinePoint() ),		ALT + Key_D );
  	menu->insertItem( "Line Properties...",	gMapMgr,	SLOT( showLineDlg() ),		CTRL + Key_L );
	
	QPopupMenu*		popup = new QPopupMenu();
	QSpinBox*		spinBox = new QSpinBox( -200, 200, 10, popup, "x-translate" );
	spinBox->setWrapping( true );
	spinBox->setButtonSymbols( QSpinBox::PlusMinus );
	spinBox->setPrefix( "X: " );
	spinBox->setValue( 0 );
	popup->insertItem( spinBox );
	connect( spinBox, SIGNAL( valueChanged(int) ), gMapMgr, SLOT( changeImageXTranslation(int) ) );
	
	spinBox = new QSpinBox( -200, 200, 10, popup, "y-translate" );
	spinBox->setButtonSymbols( QSpinBox::PlusMinus );
	spinBox->setPrefix( "Y: " );
	spinBox->setValue( 0 );
	popup->insertItem( spinBox );
	connect( spinBox, SIGNAL( valueChanged(int) ), gMapMgr, SLOT( changeImageYTranslation(int) ) );

	menu->insertItem( "X/Y Translation", popup );

	menuBar()->insertItem( "&Map", menu );

	// window menu
	menu = new QPopupMenu;
	menu->setFont( QApplication::font() );
	menu->insertItem( "Map View 1",	1 ); menu->setAccel( Key_F1, 1 );
	menu->insertItem( "Map View 2",	2 ); menu->setAccel( Key_F2, 2 );
	menu->insertItem( "Map View 3",	3 ); menu->setAccel( Key_F3, 3 );
	menu->insertItem( "Map View 4",	4 ); menu->setAccel( Key_F4, 4 );
	
	connect( menuBar(), SIGNAL( activated(int) ), this, SLOT( openMapView(int) ) );
	menu->insertSeparator();
	
	menu->insertItem( "Experience Window", this,	SLOT( viewExpWindow() ),	Key_F6 );
	menu->insertItem( "Stats", this,				SLOT( viewStats() ),		Key_F7 );
	menu->insertItem( "Skills", this,				SLOT( viewSkills() ),		Key_F8 );
	menu->insertItem( "Compass", this,				SLOT( viewCompass() ),		Key_F9 );
	menu->insertItem( "Big Text", this,				SLOT( viewBigTextWindow() ),Key_F10 );
	menu->insertItem( "Drops", this,				SLOT( viewDropWindow() ),	Key_F11 );	
	menu->insertItem( "Spawn Points", this,			SLOT( viewSpawnPointWindow() ), Key_F12 );
	menuBar()->insertItem( "&Window", menu );
		
	menu = gLogMgr->getLogMenu();
	menuBar()->insertItem( "&Log", menu );

	menu = new QPopupMenu;
	menu->insertItem( "Filters", this, SLOT( editFilters() ) );
	menu->insertItem( "Alerts", this, SLOT( editAlerts() ) );
	menu->insertItem( "Categories", this, SLOT( editCategories() ) );
	menuBar()->insertItem( "Edit", menu );
}

void EQInterface::__createMessageBoxes()
{
/*
	// create message boxes defined in config preferences
	char*		title = NULL;
	int			i = 0;
	int			j = 0;
	MsgDialog*	pMsgDlg;
	QString		tempStr;
	
	for ( i = 1; i < 15; i++ )
	{
		// attempt to pull a button title from the preferences
		tempStr.sprintf( "MessageBox%d_Title", i );
		if ( gSEQPrefs->isPreference( tempStr ) )
		{
			title = strdup( gSEQPrefs->getPrefString( tempStr ) );
			//        pMsgDlg = new MsgDialog(topLevelWidget(), title, m_stringList);
			//        pMsgDlg = new MsgDialog(this, title, m_stringList);
			// using the parentWidget makes this messagebox isolated from the
			// main application
			pMsgDlg = new MsgDialog( parentWidget(), title, m_stringList );
			m_msgDialogList.append( pMsgDlg );

			// connect signal for new messages
			connect( this, SIGNAL( newMessage(int) ), pMsgDlg, SLOT( newMessage(int) ) );

			// set additive mode
			tempStr.sprintf( "MessageBox%d_Additive", i );
			pMsgDlg->setAdditive( gSEQPrefs->getPrefBool( tempStr ) ); 

			// set control mode
			tempStr.sprintf( "MessageBox%d_HideControls", i );
			pMsgDlg->showControls( !gSEQPrefs->getPrefBool( tempStr ) ); 

			// set msg type mode
			tempStr.sprintf( "MessageBox%d_ShowMsgType", i );
			pMsgDlg->showMsgType( gSEQPrefs->getPrefBool( tempStr ) ); 

			// configure buttons
			for ( j = 1; j < 15; j++ )
			{
				bool name = false;
				bool filter = false;

				// attempt to pull button description from the preferences
				tempStr.sprintf( "MessageBox%d_Button%dName", i, j );
				name = gSEQPrefs->isPreference( tempStr );
				QString buttonname( gSEQPrefs->getPrefString( tempStr ) ); 
				tempStr.sprintf( "MessageBox%d_Button%dFilter", i, j );
				filter = gSEQPrefs->isPreference( tempStr );
				QString buttonfilter( gSEQPrefs->getPrefString( tempStr ) );
				tempStr.sprintf( "MessageBox%d_Button%dColor", i, j );
				QString buttoncolor( gSEQPrefs->getPrefString( tempStr ) );
				tempStr.sprintf( "MessageBox%d_Button%dActive", i, j );

				// if we have a name and filter string
				if ( name && filter )
				{
					// add the button
					pMsgDlg->addButton( buttonname, buttonfilter, buttoncolor, gSEQPrefs->getPrefBool( tempStr ) ); 
				}
				else if ( name || filter )
				{
					fprintf( stderr, "Error: Incomplete definition of Button '%s'\n", title);
				}
				// allow skipped numbers
				//             break; // no more buttons
			}
		
			QSize		s = pMsgDlg->size();
			QPoint		p = pMsgDlg->pos();
			int			x, y, w, h;
			
			tempStr.sprintf( "MessageBox%d_WindowX", i );
			x = gSEQPrefs->getPrefInt( tempStr, p.x() ); 
			tempStr.sprintf( "MessageBox%d_WindowY", i );
			y = gSEQPrefs->getPrefInt(tempStr, p.y() ); 
			tempStr.sprintf( "MessageBox%d_WindowW", i );
			w = gSEQPrefs->getPrefInt(tempStr, s.width() ); 
			tempStr.sprintf( "MessageBox%d_WindowH", i );
			h = gSEQPrefs->getPrefInt( tempStr, s.height() ); 
			pMsgDlg->resize( w, h );
			pMsgDlg->show();
			if ( gSEQPrefs->getPrefBool("UseWindowPos", "Interface", false ) )
				pMsgDlg->move( x, y );

			free( title );

		}
		// allow skipped numbers
		//      else
		//        break;
	
	}
*/
}

void EQInterface::__createSpawnPointWindow()
{
	m_spawnPointWindow = new SpawnPointWindow( "spawn-point-window" );
	if ( m_spawnPointWindow->shouldShow() )
		m_spawnPointWindow->show();
}

void EQInterface::__createBigTextWindow()
{
	m_bigTextWindow = new BigTextWindow( this, "big-text-window" );
	if ( m_bigTextWindow->shouldShow() )
		m_bigTextWindow->show();
}

void EQInterface::__createCompassWindow()
{
	// create our compass object
	m_compass = new BaseWindow( "Compass", NULL, "compass-window" );

	m_compass->setFixedWidth( 120 );
	m_compass->setFixedHeight( 140 );

	QBoxLayout*		compassLayout = new QVBoxLayout( m_compass );
	compassLayout->setAutoAdd( true );
	Compass*		compass = new Compass( m_compass, "compass" );
	QHBox*			coordsbox = new QHBox( m_compass );
	
	compass->setFixedWidth( 120 );
	compass->setFixedHeight( 120 );

	QLabel*		xPos;
	QLabel*		yPos;
	QLabel*		zPos;

	// create the xpos label
	QLabel* labelx = new QLabel( "X:", coordsbox );
	labelx->setFixedHeight( labelx->sizeHint().height() );
	xPos = new QLabel( "----", coordsbox );
	xPos->setFixedHeight( xPos->sizeHint().height() );
	xPos->setAlignment( QLabel::AlignRight | QLabel::AlignVCenter );

	// create the ypos label
	QLabel* labely = new QLabel( "Y:", coordsbox );
	labely->setFixedHeight( labely->sizeHint().height() );
	yPos = new QLabel( "----", coordsbox );
	yPos->setFixedHeight( yPos->sizeHint().height() );
	yPos->setAlignment( QLabel::AlignRight | QLabel::AlignVCenter );

	// create the zpos label
	QLabel* labelz = new QLabel( "Z:", coordsbox );
	labelz->setFixedHeight( labelz->sizeHint().height() );
	zPos = new QLabel( "----",coordsbox );
	zPos->setFixedHeight( zPos->sizeHint().height() );      
	zPos->setAlignment( QLabel::AlignRight | QLabel::AlignVCenter );

	connect( gPlayer, SIGNAL( xposChanged(int) ), xPos, SLOT( setNum(int) ) );
	connect( gPlayer, SIGNAL( yposChanged(int) ), yPos, SLOT( setNum(int) ) );
	connect( gPlayer, SIGNAL( zposChanged(int) ), zPos, SLOT( setNum(int) ) );
	connect( gPlayer, SIGNAL( headingChanged(int) ), compass, SLOT( setAngle(int) ) );
	
	if ( m_compass->shouldShow() )
		m_compass->show();
}

void EQInterface::__createDropWindow()
{
	m_dropWindow = new DropWindow( this, "drop-window" );
	if ( m_dropWindow->shouldShow() )
		m_dropWindow->show();
}

void EQInterface::__createStatWindow()
{
	m_stats = new StatWindow( "stat-window" );
	if ( m_stats->shouldShow() )
		m_stats->show();
}

void EQInterface::__createSkillsWindow()
{
	m_skills = new SkillWindow( "skill-window" );
	if ( m_skills->shouldShow() )
		m_skills->show();
}

void EQInterface::__createExperienceWindow()
{
	// initialize the experience window
	m_expWindow = new ExperienceWindow();
	// set initial view options
	if ( gSEQPrefs->getPrefBool( "ShowExpWindow", "Interface", false ) )
		this->viewExpWindow();
}

void EQInterface::__createChildren()
{
	QHBox*	catBox = new QHBox( this->centralWidget() );
	catBox->setSpacing( 2 );

	// build the "Category" picker
	QLabel* label = new QLabel( "Category:", catBox );
//	label->setAlignment( AlignLeft | AlignTop );
	m_catCombo = new CategoryMgr( catBox, "cat-list" );
	m_catCombo->setFixedHeight( 20 );

	// build the "Select On" combo box
	label = new QLabel( "Select On:", catBox );
//	label->setAlignment( AlignLeft | AlignTop );
	QStringList		conList;
	conList << "Consider" << "Target" << "None";
	QComboBox*		selectBox = new QComboBox( catBox, "select-list" );
	selectBox->insertStringList( conList );
	selectBox->setFixedHeight( 20 );
	connect( selectBox, SIGNAL( activated(int) ), this, SLOT( setSelectMode(int) ) );
	
	// build the FPM spin box
//	m_catCombo->setFrameStyle( QFrame::Box | QFrame::Plain );
	m_FPM = new QSpinBox( 9, 120, 1, catBox, "spawnlist-fpm" );
//	m_FPM->setFrameStyle( QFrame::Box | QFrame::Plain );
//	m_FPM->setMidLineWidth( 0 );
//	m_FPM->setLineWidth( 1 );
	m_FPM->setValue( gSEQPrefs->getPrefInt( "FPM", "SpawnList", 30 ) );
	m_FPM->setSuffix( "FPM" );
	m_FPM->setSpecialValueText( "Instant" );
	m_FPM->setFixedHeight( 20 );

	// add a spacer so the other stuff is right-aligned
	QWidget*	spacer = new QWidget( catBox );
	catBox->setStretchFactor( spacer, 10 );

	// build the "Raw" checkbox for displaying Raw data
	m_rawSpawns = new QCheckBox( "Raw", catBox, "raw-spawns" );
	connect( m_rawSpawns, SIGNAL( toggled(bool) ), this, SLOT( toggleRawDisplay(bool) ) );
	
	// build the spawn list
	m_spawnList = new SpawnListView( m_catCombo, this->centralWidget(), "spawn-list" );
	m_spawnList->installEventFilter( this );
	m_spawnList->restore();

	// build some maps
	for ( int i = 0; i < MAX_MAPS; i++ )
	{
		QString	 section = "Map";
		section += QString::number( i + 1 );
		
		if ( gSEQPrefs->getPrefBool( "Shown", section, false ) )
			this->openMapView( i + 1 );
	}

	connect( m_FPM, SIGNAL( valueChanged(int) ), m_spawnList, SLOT( setFPM(int) ) );
}


void EQInterface::__createNetworkStats()
{
	//if ( gSEQPrefs->net_stats )
	//{
	//	QVBox*		netInfo = new QVBox(NULL);
	//	QLCDNumber*	pCounter = new QLCDNumber( 7, netInfo, "pkts" );
	//	pCounter->setSegmentStyle( QLCDNumber::Flat );
	//	QLCDNumber*	pSeqexp = new QLCDNumber( 7, netInfo, "seqexp" );
	//	pSeqexp->setSegmentStyle( QLCDNumber::Flat );
	//	pSeqexp->setHexMode();
	//	QLCDNumber*	pSeqcur = new QLCDNumber( 7, netInfo, "seqcur" );
	//	pSeqcur->setSegmentStyle( QLCDNumber::Flat );
	//	pSeqcur->setHexMode();
	//
	//	connect( gPacket, SIGNAL( packetReceived(int) ), pCounter, SLOT( display(int) ) );
	//	connect( gPacket, SIGNAL( seqExpect(int) ), pSeqexp, SLOT( display(int) ) );
	//	connect( gPacket, SIGNAL( seqReceive(int) ), pSeqcur, SLOT( display(int) ) );
	//	netInfo->show();
	//}
}

void EQInterface::__saveSplitterSizes()
{
	QValueList<int>					list = m_splitH->sizes();
	QValueList<int>::Iterator		it = list.begin();
	QString							tempStr;
	int								i = 0;

	while ( it != list.end() )
	{
		i++;
		tempStr.sprintf( "SplitH_Size%d", i );
		gSEQPrefs->setPrefInt( tempStr, "Interface", *it );
//		printf( "saving splitH%d: %d\n", i, *it );
		++it;
	}
}

void EQInterface::__restoreSplitterSizes()
{
#ifdef DEBUG
//	debug( "EQInterface::__restoreSplitterSize()" );
#endif

	// restore splitter sizes
	QValueList<int> 	list;
	QString				tempStr;
	int					i = 0;
	int					x;
	
	for ( ; ; )
	{
		i++;
		tempStr.sprintf( "SplitH_Size%d", i );
		if ( gSEQPrefs->isPreference( tempStr, "Interface" ) )
		{
			x = gSEQPrefs->getPrefInt( tempStr, "Interface" );
#ifdef DEBUG
//			printf( "'%s' %d\n", (const char*)tempStr, x );
#endif
			list.append( x );
		}
		else
			break;
	}

	m_splitH->setSizes( list );
	list.clear();
}

void EQInterface::__saveWindow()
{
	QRect		r;
	int			x, y;
	
	r = frameGeometry();

	x = gSEQPrefs->getPrefInt( "WindowXOffset", "Interface", 0 );
	y = gSEQPrefs->getPrefInt( "WindowYOffset", "Interface", 0 );

	if ( gSEQPrefs->isPreference( "WindowX", "Interface" ) )
		gSEQPrefs->setPrefInt( "WindowX", "Interface", r.left() + x );
	if ( gSEQPrefs->isPreference( "WindowY", "Interface" ) )
		gSEQPrefs->setPrefInt( "WindowY", "Interface", r.top() + y );
	if ( gSEQPrefs->isPreference( "WindowW", "Interface" ) )
		gSEQPrefs->setPrefInt( "WindowW", "Interface", width() );
	if ( gSEQPrefs->isPreference( "WindowH", "Interface" ) )
		gSEQPrefs->setPrefInt( "WindowH", "Interface", height() );
}

void EQInterface::__restoreWindow()
{
	QSize	s = size();
	QPoint	p = pos();

	int			x, y, w, h;

	x = gSEQPrefs->getPrefInt( "WindowX", "Interface", p.x() );
	y = gSEQPrefs->getPrefInt( "WindowY", "Interface", p.y() );
	w = gSEQPrefs->getPrefInt( "WindowW", "Interface", s.width() );
	h = gSEQPrefs->getPrefInt( "WindowH", "Interface", s.height() );

	this->resize( w, h );
	
	this->move( x, y );

	// set caption if we have one 
	if ( gSEQPrefs->isPreference( "Title", "Interface" ) )
		this->setCaption( QString( gSEQPrefs->getPrefString( "Title", "Interface" ) ) );
	else
	{
		QString 	ip = gSEQPrefs->getPrefString( "IP", "Network", "-unknown-" );
		QString		dev = gSEQPrefs->getPrefString( "Device", "Network", "-unknown-" );

		this->captureTargetChanged( dev, ip );		
	}

	this->show();

	if ( !gSEQPrefs->getPrefBool( "ShowSpawnList", "Interface", true ) )
		m_spawnList->hide();
}

void EQInterface::__togglePreference( const QString& prefName, int menuID )
{
	bool		state;
	
	state = gSEQPrefs->getPrefBool( prefName, "Interface" );
	state = !state;

	gSEQPrefs->setPrefBool( prefName, "Interface", state );
	
	menuBar()->setItemChecked( menuID, state );
}


void EQInterface::captureTargetChanged( const QString& device, const QString& ip )
{
	QString		caption;
	
	caption = "SINS          Device: ";
	caption += device;
	caption += "    IP: ";
	caption += ip;
	this->setCaption( caption );
}

void EQInterface::savePrefs()
{
	QString		tempStr;

	// save spawnlist label geometries
	if ( m_spawnList )
		m_spawnList->saveToPreferences();
		
/*
	// save message dialog geometries
	MsgDialog* diag;
	int i = 0;

	for ( diag = m_msgDialogList.first(); diag != NULL; diag = m_msgDialogList.next() )
	{
	// determine the message box number from the config file
		for ( i = 1; i < 15; i++ )
		{
			tempStr.sprintf( "MessageBox%d_Title", i );
			if ( !strcmp( gSEQPrefs->getPrefString( tempStr, "" ), diag->name() ) )
				break;
		}

		// get geometry from dialog
		r = diag->frameGeometry();
		// enlightenment
		//    r = diag->topLevelWidget()->geometry();  // x,y take into account frame

		tempStr.sprintf( "MessageBox%d_WindowX", i );
		if ( gSEQPrefs->isPreference( tempStr ) )
			gSEQPrefs->setPrefValue( tempStr, r.left() + x );
		tempStr.sprintf( "MessageBox%d_WindowY", i );
		if ( gSEQPrefs->isPreference(tempStr ) )
			gSEQPrefs->setPrefValue( tempStr, r.top() + y );

		tempStr.sprintf( "MessageBox%d_WindowW", i );
		if ( gSEQPrefs->isPreference( tempStr ) )
			gSEQPrefs->setPrefValue( tempStr, diag->width() );
		tempStr.sprintf( "MessageBox%d_WindowH", i);
		if ( gSEQPrefs->isPreference( tempStr ) )
			gSEQPrefs->setPrefValue( tempStr, diag->height() );
	}
*/

	this->__saveWindow();
	
	//this->__saveSplitterSizes();
	
	// save visible state of interface objects
	gSEQPrefs->setPrefBool( "ShowSpawnList", "Interface", !m_spawnList->isHidden() );
}

void EQInterface::viewChannelMsgs()
{
}

void EQInterface::toggleShowHide( int menuId, QWidget* widget )
{
	if ( widget->isHidden() )
	{
		widget->show();
		menuBar()->setItemChecked( menuId, true );
	}
	else
	{
		widget->hide();
		menuBar()->setItemChecked( menuId, false );
	}
}

void EQInterface::viewSpawnList()
{
	this->toggleShowHide( m_viewSpawnListID, m_spawnList );
}

void EQInterface::viewExpWindow()
{
	m_expWindow->show();
	m_expWindow->raise();
}

void EQInterface::viewStats()
{
	m_stats->show();
	m_stats->raise();
}

void EQInterface::viewSkills()
{
	m_skills->show();
	m_skills->raise();
}

void EQInterface::viewCompass()
{
	m_compass->show();
	m_compass->raise();
}

void EQInterface::viewBigTextWindow()
{
	m_bigTextWindow->show();
	m_bigTextWindow->raise();
}

void EQInterface::viewSpawnPointWindow()
{
	m_spawnPointWindow->show();
	m_spawnPointWindow->raise();
}

void EQInterface::viewDropWindow()
{
	m_dropWindow->show();
	m_dropWindow->raise();
}

void EQInterface::openMapView( int number )
{
	if ( number >= 1 && number <= MAX_MAPS )
	{
		number--;
		if ( m_map[ number ].isNull() )
		{
			QString title = "Map ";
			title += QString::number( number + 1 );
			m_map[ number ] = new MapWindow( gMapMgr, title, number, "map" );
			m_map[ number ]->getMap()->installEventFilter( this );
		}
		
		(m_map[ number ])->show();
		(m_map[ number ])->raise();
		m_lastMap = m_map[ number ]->getMap();
	}
}

bool EQInterface::eventFilter( QObject* dest, QEvent* event )
{
	static bool	filter = false;
	bool		kept = false;

	if ( filter )
		return true;

	filter = true;

	if ( event->type() == QEvent::KeyPress )
	{
		QKeyEvent*		keyEvent = (QKeyEvent*)event;

		// simple check -- this will give keystrokes to everything but the
		// spawn list, first
		if ( dest != m_spawnList && dest != m_lastMap )
			kept = false;

		// if the destination is the map, let the map try to handle
		// it... if it doesn't handle it, give it to the spawnlist
		else if ( dest == m_lastMap )
		{
			m_lastMap->keyPressEvent( keyEvent );
			kept = keyEvent->isAccepted();
			if ( !kept )
			{
				m_spawnList->keyPressEvent( keyEvent );
				kept = true;
			}
		}
		// else if the destination is the spawn list, see if it's
		// something that map will handle
		else
		{
			m_lastMap->keyPressEvent( keyEvent );
			kept = keyEvent->isAccepted();			
		}
	}

	filter = false;
	return kept;
}

void EQInterface::editFilters()
{
	QStringList		filterFields;
	
	filterFields = m_spawnList->getColumnNames();
	
	FilterDlg*	dlg = new FilterDlg( gFilterMgr, filterFields, this, "filter-dlg" );
	if ( dlg->exec() == QDialog::Accepted )
		;	
	delete dlg;
}

void EQInterface::editAlerts()
{
	QStringList		filterFields;
	
	filterFields = m_spawnList->getColumnNames();
	
	FilterDlg*	dlg = new FilterDlg( gAlerter, filterFields, this, "alert-dlg" );
	if ( dlg->exec() == QDialog::Accepted )
		;	
	delete dlg;
}

void EQInterface::editCategories()
{
}

void EQInterface::toggleRawDisplay( bool on )
{
	m_spawnList->setRaw( on );
	m_spawnList->resync();
}

void EQInterface::setSelectMode( int m )
{
	m_selectMode = m;
}

void EQInterface::createMessageBox()
{
}

void EQInterface::numSpawns( int num )
{
	// only update once per sec
	static QTime		lastupdate = QTime::currentTime();

	if ( lastupdate.elapsed() < 1000L )
		return;
	
	lastupdate.restart();

	QString tempStr;
	tempStr.sprintf( "Mobs: %d", num );
	m_stsbarSpawns->setText( tempStr );
}

void EQInterface::numPacket( int num )
{
	static QTime		lastupdate = QTime::currentTime();
	static QTime		packetStartTime = QTime::currentTime();
	static int			initialcount = 0;

	QString		tempStr;
	int			delta;

	// if passed 0 reset the average
	if ( num == 0 )
	{
		packetStartTime.restart();
		initialcount = 0;
		return;
	}

	// only update once per sec
	if ( lastupdate.elapsed() < 1000L )
		return;
	
	lastupdate.restart();

	delta = packetStartTime.elapsed();
	num -= initialcount;
	if ( num && delta )
		tempStr.sprintf( "Pkt: %d (%2.1f)", num, (float) ( num << 10 ) / (float) delta );
	else   
		tempStr.sprintf( "Pkt: %d", num );

	m_stsbarPkt->setText( tempStr );
}

// TODO:  clear after timeout miliseconds
void EQInterface::stsMessage( const QString& string, int /*timeout*/ )
{
	m_stsbarStatus->setText( string );
}

void EQInterface::msgReceived( const QString& instring )
{
	QString string( instring );

	int				index = 0;
	
	// strip out newlines
	while( -1 != ( index = string.find( '\n' ) ) )
		string.replace( index, 1, " " );

	while( -1 != (index = string.find( '\r' ) ) )
		string.replace( index, 1, " " );

	if ( gSEQPrefs->getPrefBool( "UseStdout", "Interface" ) )
	{
		fprintf( stdout, "%s\n", string.ascii() );
		fflush( stdout );
	}

	m_stringList.append( string );
	emit newMessage( string );
}

void EQInterface::handleMoney( const void* /*data*/ )
{
	QString		tempStr;
	
	tempStr.sprintf( "Money: " );
	this->msgReceived( tempStr );
}

void EQInterface::handleMoneyUpdate( const struct moneyUpdateStruct* moneyp )
{
	if ( moneyp->amount != 0 )
	{
		QString		tempStr;
	
		tempStr.sprintf( "Money: Type: %d Amount: %ld\n",
			moneyp->cointype,
			moneyp->amount );

		this->msgReceived( tempStr );
	}
}

void EQInterface::handleSysMsg( const struct systemMessageStruct* smsg )
{
	QString		tempStr;
	
	if ( !smsg->message[ 0 ] )
		return;

	if ( !strncmp( smsg->message, "Your faction", 12 ) )
		tempStr.sprintf( "Faction: %s", smsg->message );
	else
		tempStr.sprintf( "System: %s", smsg->message );
	this->msgReceived( tempStr );
}

void EQInterface::handleBeginCast( const struct beginCastStruct* bcast )
{
	QString		tempStr;
	switch ( bcast->param2 )
	{
		case 0:		tempStr.sprintf( "Scribe" );			break;
		case 1:		tempStr.sprintf( "Memorize" );			break;
		case 2:		tempStr.sprintf( "Forget" );			break;
		case 3:		tempStr.sprintf( "Cast" );				break;
		default:	tempStr.sprintf( "Unknown" );
	}
	
	tempStr.sprintf( "Cast: %s (%x) - %d,%d,%d ",
		(const char*)SpellMgr::spellName( bcast->spellId ),
		bcast->spellId,
		bcast->param1,
		bcast->param2,
		bcast->param3 );
	this->msgReceived( tempStr );
}

void EQInterface::handleSpecialMsg( const struct spMesgStruct* spmsg )
{
	QString		tempStr;
	
	if ( !spmsg->message[ 0 ] )
		return;

	switch ( spmsg->msgType )
	{
		case 13:
			if ( !strncmp( spmsg->message, "Your target is too far away", 20 ) ) 
				tempStr.sprintf( "Attack: %s", spmsg->message );
			else if ( !strncmp( spmsg->message, "You can't see your target", 18 ) ) 
				tempStr.sprintf( "Attack: %s", spmsg->message );
			else if ( !strncmp( spmsg->message, "Your target resisted", 18 ) ) 
				tempStr.sprintf( "Spell: %s", spmsg->message );
			else 
				tempStr.sprintf( "Special: %s (%ld)", spmsg->message, spmsg->msgType );
		break;
		case 15:
			tempStr.sprintf( "Exp: %s", spmsg->message );
		break;
		default:
			tempStr.sprintf( "Special: %s (%ld)", spmsg->message, spmsg->msgType );
		break;
	}
	this->msgReceived( tempStr );
}

void EQInterface::handleEmote( const struct emoteTextStruct* emotetext )
{
	QString				tempStr;

	if ( m_viewChannelMsgs )
	{
		tempStr.sprintf( "Emote: %s", emotetext->text );
		this->msgReceived( tempStr );
	}
}

void EQInterface::handleChannelMsg( const struct channelMessageStruct* cmsg )
{
#ifdef DEBUG
	debug( "EQInterface::handleChannelMsg()\n" );
#endif

	QString				tempStr;
	QString				tempStr2;

	if ( m_viewChannelMsgs )
	{
		switch ( cmsg->chanNum )
		{
			case 0:			tempStr = "Guild";		break;
			case 2:			tempStr = "Group";		break;
			case 3:			tempStr = "Shout";		break;
			case 4:			tempStr = "Auction";	break;
			case 5:			tempStr = "OOC";		break;
			case 7:			tempStr	= "Tell";		break;
			case 8:			tempStr = "Say";		break;
			case 15:		tempStr = "GM-Tell";
			default:		tempStr.sprintf( "Chan%02x", cmsg->chanNum );
		}

		if ( cmsg->language )
		{
			tempStr2.sprintf( "'%s' - %s {%s}",
				cmsg->sender,
				cmsg->message,
				(const char*)Spawn::languageName( cmsg->language ) );
		}
		else // don't show common, its obvious 
		{
			tempStr2.sprintf( "'%s' - %s",
				cmsg->sender,
				cmsg->message );	
		}
		tempStr += ": ";
		tempStr += tempStr2;
		this->msgReceived( tempStr );
	}
}

void EQInterface::handlePlayerCont( const struct containerPlayerStruct* containp )
{
	QString				tempStr;

	tempStr.sprintf( "Container: %s, *%s, %d slots, %ldcp",
		containp->item.name,
		containp->item.lore,
		containp->numSlots,
		containp->item.cost );

	this->msgReceived( tempStr );
}

void EQInterface::handlePlayerBook( const struct bookPlayerStruct* bookp )
{
	QString				tempStr;

	tempStr.sprintf( "Item: Book: %s, *%s, %s, %ldcp",
		bookp->item.name,
		bookp->item.lore,
		bookp->file,
		bookp->item.cost );
		
	this->msgReceived( tempStr );
}

void EQInterface::handleSummonedItem( const struct summonedItemStruct* itemsum )
{
	QString				tempStr;
	
	tempStr.sprintf( "Summoned: %s(%i), %ldcp",
		itemsum->item.item.lore,
		itemsum->item.item.itemNr,
		itemsum->item.item.cost );

	this->msgReceived( tempStr );
}

void EQInterface::handlePlayerItem( const struct itemPlayerStruct* itemp )
{
	QString				tempStr;

	tempStr.sprintf( "Item: %s(%i), %ldcp Slot: %i",
		itemp->item.item.lore,
		itemp->item.item.itemNr,
		itemp->item.item.cost,
		itemp->item.item.equipSlot);

	this->msgReceived( tempStr );
}

void EQInterface::handleTradeItem( const struct itemReceivedStruct* itemr )
{
	QString				tempStr;

	tempStr.sprintf( "Received item: %s (%i), %ldcp",
		itemr->item.item.lore,
		itemr->item.item.itemNr,
		itemr->item.item.cost );

	this->msgReceived( tempStr );
	
	emit newItem( itemr->item );
}

void EQInterface::handleTradeItem2( const struct tradeItemStruct* itemt )
{
	QString				tempStr;
	
	tempStr.sprintf( "Dropped item: %s(%i), %ldcp",
		itemt->item.item.lore,
		itemt->item.item.itemNr,
		itemt->item.item.cost );

	this->msgReceived( tempStr );

	emit newItem( itemt->item );
}

void EQInterface::handleCorpseItem( const struct itemReceivedStruct* itemc )
{
	QString				tempStr;
	
	tempStr.sprintf( "Drop: %s(%i), %ldcp",
		itemc->item.item.lore,
		itemc->item.item.itemNr,
		itemc->item.item.cost );

	this->msgReceived( tempStr );

	emit newItem( itemc->item );
}

void EQInterface::handleShopItem( const struct itemShopStruct* items )
{
	QString				tempStr;

	tempStr.sprintf( "Shop: %s(%i), %ldcp",
		items->item.item.lore,
		items->item.item.itemNr,
		items->item.item.cost );

	this->msgReceived( tempStr );

	emit newItem( items->item );
}

void EQInterface::handleConsMessage( const struct considerStruct* con )
{
	QString		str;
	QString		temp;

	if ( con->playerid == con->targetid )
		str = "YOU";
	else
	{
		const Spawn*		sp = gItemMgr->spawnByID( con->targetid );
		if ( sp )
			str = sp->name();
	}
	
	if ( con->level )
	{
		temp.sprintf( "  L:%ld", con->level );
		str += temp;
	}
	
	if ( con->curHp )
	{
		temp.sprintf( "  HP:%ld", con->curHp );
		str += temp;
	}

	if ( con->faction )
	{
		temp.sprintf( "  F:%ld", con->faction );
		str += temp;
	}

	this->msgReceived( str );
}

void EQInterface::handleConsRequest( const struct considerStruct* con )
{
	if ( m_selectMode == SelectOnConsider )
	{
		if ( con->playerid != con->targetid )
		{
			Spawn*	target = gItemMgr->spawnByID( con->targetid );
		
			if ( target )
				gItemMgr->selectionChanged( target );
		}
	}
}

void EQInterface::handleClientTarget( const struct clientTargetStruct* cts )
{
	if ( m_selectMode == SelectOnTarget )
	{
		if ( cts->newTarget	)
		{
			Spawn*	target = gItemMgr->spawnByID( cts->newTarget );
			
			if ( target )
				gItemMgr->selectionChanged( target );
		}
	}
}

void EQInterface::handleAttack1( const struct attack1Struct* /*atk1*/ )
{
}

void EQInterface::handleAttack2( const struct attack2Struct* /*atk2*/ )
{
}

void EQInterface::handleHPUpdate( const struct spawnHpUpdateStruct* hpupdate )
{
	if ( hpupdate->spawnId == gPlayer->id() )
	;	//emit updateSpawnHp( hpupdate->spawnId, hpupdate->curHp + m_plusHP, hpupdate->maxHp );
	else
	;	//emit updateSpawnHp( hpupdate->spawnId, hpupdate->curHp, hpupdate->maxHp );

	//printf ("HPUPDATE: %x - %d of %d\n",hpupdate->spawnId,hpupdate->curHp,hpupdate->maxHp);
	//printf ("HPUPDATE2: %x - %d of %d or %d\n",hpupdate->spawnId,hpupdate->unknown0,hpupdate->unknown1, hpupdate->unknown2);
}

void EQInterface::handleInspect( const struct inspectingStruct* inspt )
{
	//  printf ("INSPECT: %d\n", len);
	printf( "She/he has:\n" );
	for ( int inp = 0; inp < 21; inp++ )
		printf( "\t%s (icn:%i)\n", inspt->itemNames[ inp ], inspt->icons[ inp ] );

	printf( "\tinfo: %s\n", inspt->mytext );
}

void EQInterface::handleRandom( const struct randomStruct* randr )
{
	printf( "RANDOM: Request random number between %ld and %ld\n", randr->bottom, randr->top );
}

