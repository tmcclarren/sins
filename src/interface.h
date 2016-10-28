// interface.h
//		SINS Distributed under GPL

#ifndef INTERFACE_H
#define INTERFACE_H

#define MAX_MAPS		4

#include <qguardedptr.h>
#include <qmainwindow.h>
#include "everquest.h"

class QCheckBox;
class QLabel;
class QLineEdit;
class QVBox;
class QComboBox;
class QTimer;
class QSpinBox;
class QSplitter;
class QDialog;
class QListView;

class EQPacket;
class Map;
class MapWindow;
class Spawn;
class BaseWindow;
class BigTextWindow;
class CategoryMgr;
class DropWindow;
class ExperienceWindow;
class SkillListView;
class SkillWindow;
class SpawnListView;
class SpawnPointWindow;
class StatListView;
class StatWindow;

class EQInterface: public QMainWindow
{
Q_OBJECT
public:
	enum SelectMode {
		SelectOnConsider = 0,
		SelectOnTarget,
		None
	};

	EQInterface( QWidget* parent = NULL, const char* name = NULL );
	~EQInterface();
	
	bool eventFilter( QObject* dest, QEvent* event );
	SpawnListView* spawnList() { return m_spawnList; }

public slots:
	void captureTargetChanged( const QString& device, const QString& ip );
	
	void msgReceived( const QString& );
	void stsMessage( const QString &, int timeout = 0 );
	void numSpawns( int );
	void numPacket( int );

	void savePrefs();

	void handleMoney( const void* data );
	void handleMoneyUpdate( const struct moneyUpdateStruct* data );
	void handleSysMsg( const struct systemMessageStruct* smsg );
	void handleBeginCast( const struct beginCastStruct* bcast );
	void handleSpecialMsg( const struct spMesgStruct* spmsg );
	void handlePlayerCont( const struct containerPlayerStruct* containp );
	void handlePlayerBook( const struct bookPlayerStruct* bookp );
	void handleEmote( const struct emoteTextStruct* emotetext );
	void handleChannelMsg( const struct channelMessageStruct* cmsg );
	void handleSummonedItem( const struct summonedItemStruct* itemsum );
	void handlePlayerItem( const struct itemPlayerStruct* itemp );
	void handleTradeItem( const struct itemReceivedStruct* itemr );
	void handleTradeItem2( const struct tradeItemStruct* itemt );
	void handleCorpseItem( const struct itemReceivedStruct* itemc );
	void handleShopItem( const struct itemShopStruct* items );
	void handleAttack1( const struct attack1Struct* atk1 );
	void handleAttack2( const struct attack2Struct* atk2 );
	void handleHPUpdate( const struct spawnHpUpdateStruct* hpupdate );
	void handleInspect( const struct inspectingStruct* inspt );
	void handleRandom( const struct randomStruct* randr );
	void handleClientTarget( const struct clientTargetStruct* data );
	void handleConsRequest( const struct considerStruct* );
	void handleConsMessage( const struct considerStruct* cons );
	
	void viewSpawnList();
	void viewStats();
	void viewSkills();
	void viewCompass();
	void viewExpWindow();
	void viewBigTextWindow();
	void viewDropWindow();
	void viewSpawnPointWindow();
	void openMapView( int map );
	
	void editFilters();
	void editAlerts();
	void editCategories();

	void toggleRawDisplay( bool );	
	void setSelectMode( int m );

signals:
	void newMessage( const QString& message );
	void newItem( const ItemStruct& rec );

protected:
	void toggleShowHide( int menuId, QWidget* widget );
	void __togglePreference( const QString& preferenceName, int menuID );
	
	void viewChannelMsgs();

	void createMessageBox();
	
	void __createStatusBar();
	void __createSplitters();
	void __createMenus();
	void __createMessageBoxes();
	void __createBigTextWindow();
	void __createCompassWindow();
	void __createDropWindow();
	void __createStatWindow();
	void __createSkillsWindow();
	void __createSpawnPointWindow();
	void __createExperienceWindow();
	void __createChildren();
	void __createNetworkStats();

	void __saveSplitterSizes();
	void __restoreSplitterSizes();
	void __saveWindow();
	void __restoreWindow();

	// child widgets
	QGuardedPtr<MapWindow>	m_map[ MAX_MAPS ];
	SpawnListView*		m_spawnList;
	CategoryMgr*		m_catCombo;
	QSplitter*			m_splitH;
	QSpinBox*			m_FPM;
	QCheckBox*			m_rawSpawns;

	QLabel*				m_stsbarSpawns;
	QLabel*				m_stsbarStatus;
	QLabel*				m_stsbarZone;
	QLabel*				m_stsbarID;
	QLabel*				m_stsbarExp;
	QLabel*				m_stsbarPkt;

	// other windows
	BigTextWindow*		m_bigTextWindow;
	DropWindow*			m_dropWindow;
	ExperienceWindow*	m_expWindow;
	BaseWindow*			m_compass;
	StatWindow*			m_stats;
	SkillWindow*		m_skills;
	SpawnPointWindow*	m_spawnPointWindow;

//	QList<MsgDialog> 	m_msgDialogList;
	QStringList			m_stringList;

	bool				m_viewChannelMsgs;
	
	int					m_viewMapID;
	int					m_viewSpawnListID;
	
	int					m_selectMode;
	Map*				m_lastMap;
};

#endif
