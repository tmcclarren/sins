// spawnlist.h
//		SINS Distributed under GPL

#ifndef SPAWNLIST_H
#define SPAWNLIST_H

#include <qlistview.h>
#include <qdatetime.h>
#include <qintdict.h>

#include "listviewwrapper.h"
#include "baselistview.h"
#include "everquest.h"
#include "spawn.h"

class CategoryMgr;
class QTimer;
class EQInterface;
class SpawnListView;

class SpawnItem: public QListViewItem
{
public:
	SpawnItem( QListView* parent, Spawn* spawn );

	SpawnItem::~SpawnItem();
	virtual void paintCell( QPainter *p, const QColorGroup &cg, int column, int width, int alignment );

	const QColor textColor() const { return m_textColor; }
	void setTextColor( const QColor &color );

protected:
	QColor					m_textColor;
	Spawn*					m_spawn;
};

class SpawnListViewWrapper: public ListViewWrapper<Spawn>
{
public:
	SpawnListViewWrapper( const FieldMap<Spawn> map[], BaseListView* view );
	virtual ~SpawnListViewWrapper() { }

	// overridden to create SpawnItem's instead of QListViewItem's
	virtual	QListViewItem* createNewListItem( Spawn* );
	QColor pickSpawnConColor( const Spawn* s ) const;
};

class SpawnListView: public BaseListView, public SpawnListViewWrapper
{
Q_OBJECT
public:
	// mapper
	static const FieldMap<Spawn> m_map[];
	
	SpawnListView( CategoryMgr* categoryMgr, QWidget* parent = NULL, const char* name = NULL );
	
	// usual member routines
	static void Name( Spawn* s, QString& tmp );
	static void Level( Spawn* s, QString& tmp ) { tmp.sprintf( "%2d", s->level() ); }
	static void HP( Spawn*, QString& );
	static void X( Spawn* s, QString& tmp ) { tmp.sprintf( "%5d", s->xPos() ); }
	static void Y( Spawn* s, QString& tmp ) { tmp.sprintf( "%5d", s->yPos() ); }
	static void Z( Spawn* s, QString& tmp ) { tmp.sprintf( "%5d", s->zPos() ); }
	static void ID( Spawn* s, QString& tmp ) { tmp.sprintf( "%d", s->id() ); }
	static void Dist( Spawn* s, QString& tmp );
	static void Race( Spawn* s, QString& tmp );
	static void Class( Spawn* s, QString& tmp );
	static void Info( Spawn* s, QString& tmp );
	static void Spawned( Spawn* s, QString& tmp );
	static void LastName( Spawn* s, QString& tmp );

	static void setRaw( bool raw ) { m_raw = raw; }

public slots:
	void clear();
	void refilter();
	void resync();
	void refresh();
		
	void addSpawn( Spawn* spawn );
	void deleteSpawn( Spawn* spawn );
	void killSpawn( Spawn* spawn );
	void spawnChanged( Spawn* spawn );

	void levelUp( int newPlayerLevel );

	void handleSelectItem( Spawn* spawn );
	void categoryChanged();
		
	void zoneChanged( const QString& newZoneName );

	void setFPM( int framesPerMinute );

	void toggleKeepSelectedVisible();

protected slots:
	void deletingSpawnItem( SpawnItem* spawnItem );
	void handleSelectItem( QListViewItem* newItem );
	void reallySelect();

	void spawnListRightButton( QListViewItem* item, const QPoint& point, int col );

protected:
	int getTimerDelay() { return m_timerDelay; }

	friend class	SpawnItem;
	friend class	EQInterface;

	QTimer*			m_timer;
	QTimer*			m_selectTimer;
	CategoryMgr*	m_categoryMgr;
	QListViewItem*	m_itemToSelect;
	int				m_timerDelay;
	static bool		m_raw;
	bool			m_keepSelectedVisible;
};

#endif
