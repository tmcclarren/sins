//	spawnlist.cpp
//		SINS Distributed under GPL

#include <qapplication.h>
#include <qcolor.h>
#include <qfont.h>
#include <qlist.h>
#include <qpainter.h>
#include <qregexp.h>
#include <qstring.h>
#include <qtimer.h>
#include <stdio.h>

#ifdef __FreeBSD__
#include <sys/types.h>
#endif

#include "spawnlist.h"
#include "main.h"
#include "player.h"
#include "spawn.h"
#include "itemmgr.h"
#include "util.h"
#include "preferences.h"
#include "category.h"

#define INSTANT		9

SpawnItem::SpawnItem( QListView* parent, Spawn* spawn ):
	QListViewItem( parent )
{
#ifdef DEBUG
//	debug( "SpawnItem::SpawnItem()" );
#endif
	m_textColor = Qt::black;
	m_spawn = spawn;
}

void SpawnItem::setTextColor( const QColor& color )
{
	m_textColor = color;
	this->repaint();
}

// overridden from base class in order to change color and style attributes
void SpawnItem::paintCell( QPainter* p, const QColorGroup& cg, int column, int width, int alignment )
{
#ifdef DEBUG
//	debug( "SpawnItem::paintCell()" );
#endif

	QColorGroup newCg( cg );

	newCg.setColor( QColorGroup::Text, m_textColor );

	QFont		font = this->listView()->font();
	if ( m_spawn->isFlagSet( GameItem::k_alert ) )
		font.setBold( true );
	else
		font.setBold( false );
	p->setFont( font );
	
	QListViewItem::paintCell( p, newCg, column, width, alignment );
}

SpawnItem::~SpawnItem()
{
	if ( this->listView() )
		((SpawnListView*)this->listView())->deletingSpawnItem( this );
}


SpawnListViewWrapper::SpawnListViewWrapper( const FieldMap<Spawn> map[], BaseListView* view ):
	ListViewWrapper<Spawn>( map, view, 613 )
{
}

QListViewItem* SpawnListViewWrapper::createNewListItem( Spawn* s )
{
	SpawnItem*		newItem = new SpawnItem( m_listView, s );
	newItem->setTextColor( this->pickSpawnConColor( s ) );
	s->clearFlag( GameItem::k_levelChanged );
	return newItem;
}

QColor SpawnListViewWrapper::pickSpawnConColor( const Spawn* s ) const
{
	// color by pvp team
	if ( gSEQPrefs->getPrefBool( "PvPTeamColoring", "Interface", false ) )
	{
		switch ( s->race() )
		{
			case Spawn::eHuman: case Spawn::eBarbarian: case Spawn::eErudite:
				return Qt::blue;
			break;

			case Spawn::eWoodElf: case Spawn::eHighElf: case Spawn::eHalfElf:
				return QColor( 196, 206, 12 );
			break;

			case Spawn::eDarkElf: case Spawn::eTroll: case Spawn::eOgre:
				return QColor( 206, 151, 33);
			break;

			case Spawn::eDwarf: case Spawn::eHalfling: case Spawn::eGnome:
				return Qt::magenta;
			break;
		}
	}

	// color by consider difficulty
	else if ( !s->isCorpse() )
	{
		QColor color = gPlayer->pickConColor( s );
		if ( color == Qt::white )
			color = Qt::black;
		if ( color == Qt::yellow )
			color = QColor( 206, 151, 33 );
		return color;
	}

	return Qt::gray;
}


const FieldMap<Spawn> SpawnListView::m_map[] = {
	{ "Name", SpawnListView::Name },
	{ "Level", SpawnListView::Level },
	{ "HP", SpawnListView::HP },
	{ "X", SpawnListView::X },
	{ "Y", SpawnListView::Y },
	{ "Z", SpawnListView::Z },
	{ "ID", SpawnListView::ID },
	{ "Dist", SpawnListView::Dist },
	{ "Race", SpawnListView::Race },
	{ "Class", SpawnListView::Class },
	{ "Info", SpawnListView::Info },
	{ "Spawned", SpawnListView::Spawned },
	{ "LastName", SpawnListView::LastName },
	{ NULL, NULL },
};


bool SpawnListView::m_raw = false;

SpawnListView::SpawnListView( CategoryMgr* categoryMgr, QWidget* parent, const char* name ):
	BaseListView( "SpawnList", parent, name ),
	SpawnListViewWrapper( m_map, this )
{
#ifdef DEBUG
//	debug( "SpawnListView::SpawnListView()" );
#endif
	m_itemToSelect = NULL;
	m_categoryMgr = categoryMgr;
	m_keepSelectedVisible = gSEQPrefs->getPrefBool( "KeepSelect", "SpawnList", true );

	m_timer = new QTimer( this );
	connect( m_timer, SIGNAL( timeout() ), this, SLOT( refresh() ) );
	
	m_selectTimer = new QTimer( this );
	connect( m_selectTimer, SIGNAL( timeout() ), SLOT( reallySelect() ) );

	connect( gItemMgr, SIGNAL( addSpawn(Spawn*) ), SLOT( addSpawn(Spawn*) ) );
	connect( gItemMgr, SIGNAL( deleteSpawn(Spawn*) ), SLOT( deleteSpawn(Spawn*) ) );
	connect( gItemMgr, SIGNAL( killSpawn(Spawn*) ), SLOT( killSpawn(Spawn*) ) );
	connect( gItemMgr, SIGNAL( zoneChanged( const QString& ) ), SLOT( zoneChanged( const QString& ) ) );
	connect( gItemMgr, SIGNAL( handleSelectItem(Spawn*) ), SLOT( handleSelectItem(Spawn*) ) );
	connect( gItemMgr, SIGNAL( allSpawnsChanged() ), SLOT( refilter() ) );
	connect( this, SIGNAL( selectionChanged(QListViewItem*) ), SLOT( handleSelectItem(QListViewItem*) ) );
	connect( categoryMgr, SIGNAL( categoryChanged() ), SLOT( categoryChanged() ) );
	connect( this, SIGNAL( rightButtonClicked( QListViewItem*, const QPoint&, int ) ), SLOT( spawnListRightButton( QListViewItem*, const QPoint&, int ) ) );
	connect( gPlayer, SIGNAL( levelUp(int) ), SLOT( levelUp(int) ) );

	if ( this->getTimerDelay() == INSTANT )
		connect( gItemMgr, SIGNAL( spawnChanged(Spawn*) ), SLOT( spawnChanged(Spawn*) ) );
		
	this->setFPM( gSEQPrefs->getPrefInt( "FPM", "SpawnList", 10 ) );
}

void SpawnListView::Name( Spawn* s, QString& tmp )
{
	if ( !m_raw )
		tmp = s->name();
	else
	{
		tmp = "";
		int i = 0;
		while ( i <= 30 && s->m_data.name[ i ] )
		{
			tmp += s->m_data.name[ i ];
			i++;
		}
	}
}

void SpawnListView::HP( Spawn* s, QString& tmp )
{
	WORD			hp;

	hp = s->curHp();
	
	if ( hp <= 0 )
		tmp = "0";
	else if ( hp > 100 )
		tmp = "100";
	else
		tmp.sprintf( "%3d", hp );
}

void SpawnListView::Dist( Spawn* s, QString& tmp )
{
	tmp.sprintf( "%6ld", s->calcDist( gPlayer->xPos(), gPlayer->yPos(), gPlayer->zPos() ) );
}

void SpawnListView::Spawned( Spawn* s, QString& tmp )
{
	QDate		createDate = s->spawnDate();
	
	tmp = "";
	// spawn time
	if ( createDate != QDate::currentDate() )
		tmp = createDate.dayName( createDate.dayOfWeek() ) + " ";

	tmp += s->spawnTime().toString();
}

void SpawnListView::Race( Spawn* s, QString& tmp )
{
	if ( !m_raw )
		tmp = s->raceName();
	else
		tmp = QString::number( s->m_data.race );
}

void SpawnListView::Class( Spawn* s, QString& tmp )
{
	if ( !m_raw )
		tmp = s->className_();
	else
		tmp = QString::number( s->m_data.class_ );
}

void SpawnListView::Info( Spawn* s, QString& tmp )
{
	if ( !m_raw )
		tmp = s->equipString();
	else
	{
		tmp = "";
		int  i = 0;
		while ( i < 9 )
		{
			QString		tmp2;
			tmp2.sprintf( "%02x", s->m_data.equipment[ i ] );
			if ( tmp.length() )
				tmp += " ";
			tmp += tmp2;
			i++;
		}
	}
}

void SpawnListView::LastName( Spawn* s, QString& tmp  )
{
	tmp = "";
	int i = 0;
	while ( i <= 20 && s->m_data.lastname[ i ] )
	{
		tmp += s->m_data.lastname[ i ];
		i++;
	}
}

void SpawnListView::clear()
{
	BaseListView::clear();
	m_items.clear();
}

void SpawnListView::refilter()
{
	m_timer->stop();
	this->clear();
	
	QIntDictIterator<Spawn>		it( gItemMgr->spawns() );
	Spawn*						s;
	
	while ( it.current() )
	{
		s = it.current();
		++it;

		// we just call addSpawn which checks for filtering itself		
		this->addSpawn( s );
	}
	m_timer->start( this->getTimerDelay(), false );
}

void SpawnListView::resync()
{
	QIntDictIterator<RowMap<Spawn> >	it( m_items );

	while ( it.current() )
	{
		RowMap<Spawn>*	rowMap = it.current();
		++it;

		Spawn*		spawn = rowMap->m_item;
		if ( spawn )
		{
			SpawnItem*		listItem = (SpawnItem*)rowMap->m_listViewItem;
			if ( listItem )
				listItem->setTextColor( this->pickSpawnConColor( spawn ) );
			this->updateItem( spawn->id() );
		}
	}
}

void SpawnListView::refresh()
{
	QIntDictIterator<RowMap<Spawn> >	it( m_items );
	
	while ( it.current() )
	{
		RowMap<Spawn>*	rowMap = it.current();
		++it;
		
		Spawn*		spawn = rowMap->m_item;
		if ( spawn )
		{
			if ( spawn->isFlagSet( GameItem::k_dirty ) )
			{
				this->updateItem( spawn->id() );
				spawn->clearFlag( GameItem::k_dirty );
			}
		}
	}
}
	
void SpawnListView::addSpawn( Spawn* spawn )
{
#ifdef DEBUG
//	debug( "SpawnListView::addSpawn()" );
#endif
	if ( m_categoryMgr->isSpawnInCategory( m_categoryMgr->currentCategory(), spawn ) &&
		!spawn->isFlagSet( GameItem::k_filtered ) )
		this->addItem( spawn->id(), spawn );
}

void SpawnListView::deleteSpawn( Spawn* spawn )
{
#ifdef DEBUG
//	debug( "SpawnListView::deleteSpawn()" );
#endif
	this->deleteItem( spawn->id() );
}

void SpawnListView::killSpawn( Spawn* spawn )
{
	RowMap<Spawn>*	item = m_items.find( spawn->id() );
	if ( item && item->m_listViewItem )
		((SpawnItem*)item->m_listViewItem)->setTextColor( Qt::gray );
}

void SpawnListView::spawnChanged( Spawn* spawn )
{
	this->updateItem( spawn->id() );
}

void SpawnListView::levelUp( int /*newPlayerLevel*/ )
{
	this->resync();
}

void SpawnListView::deletingSpawnItem( SpawnItem* spawnItem )
{
	if ( spawnItem == m_itemToSelect )
		m_itemToSelect = NULL;
}

// this is the routine that we hook up to the ItemMgr's
//	"selectionChanged" signal -- it is intended ot catch
//	selection changes from the map, for instance
void SpawnListView::handleSelectItem( Spawn* spawn )
{
	RowMap<Spawn>*	item = m_items.find( spawn->id() );
	if ( item )
	{
		QListViewItem*	listItem = item->m_listViewItem;
		if ( listItem && listItem != m_listView->selectedItem() )
		{
			m_listView->setSelected( listItem, true );
			if ( m_keepSelectedVisible )
				m_listView->ensureItemVisible( listItem );
		}
	}
}

// this is the routine that is called from our own "selectionChanged"
// 	signal -- the purpose of this is to avoid massive amounts of
//	CPU grinding when one is using the arrow keys to traverse the
//	spawn list -- with this method, we simply record which item
//	the user has currently selected in the spawn list, and then
//	if a half-second elapses without the user changing the selection
//	we then proceed to tell the ItemMgr about our new selection,
//	by virtue of the fact that the selection timer will call
//	"reallySelect", which is somewhat CPU intensive
void SpawnListView::handleSelectItem( QListViewItem* item )
{
	m_selectTimer->start( 500L, true );
	m_itemToSelect = item;
}

// using "m_itemToSelect", run through our list of items in the
//	dictionary, and find the one that holds the reference to
//	"m_itemToSelect" -- then, call the ItemMgr to let it know
//	the selected item in the list view changed
void SpawnListView::reallySelect()
{	
	if ( !m_itemToSelect )
		return;
		
	QIntDictIterator<RowMap<Spawn> >	it( m_items );
	
	while ( it.current() )
	{
		RowMap<Spawn>*	rowMap = it.current();
		++it;
		
		QListViewItem*	listViewItem = rowMap->m_listViewItem;
		if ( listViewItem == m_itemToSelect )
		{
			gItemMgr->selectionChanged( rowMap->m_item );
			break;
		}
	}
	m_itemToSelect = NULL;
}

void SpawnListView::categoryChanged()
{
	Category*	cat = m_categoryMgr->currentCategory();

	if ( cat )
	{
		this->clear();
		
		QIntDict<Spawn>			spawns = gItemMgr->spawns();
		QIntDictIterator<Spawn> it ( spawns );

		while ( it.current() )
		{
			Spawn*					spawn = it.current();
			++it;
	
			if ( spawn )
			{
				if ( m_categoryMgr->isSpawnInCategory( cat, spawn )  &&
					!spawn->isFlagSet( GameItem::k_filtered ) )			
				{
					// setting the levelChanged flag will cause the color
					// to get set
					spawn->setFlag( GameItem::k_levelChanged );
					this->addSpawn( spawn );
				}
			}
		}
	}
}

void SpawnListView::zoneChanged( const QString& /*newZoneName*/ )
{
	m_timer->stop();
	this->clear();
	m_timer->start( this->getTimerDelay(), false );
}

void SpawnListView::setFPM( int framesPerMinute )
{
	m_timerDelay = 60000L / framesPerMinute;			// 60,000 milliseconds per minute
	gSEQPrefs->setPrefInt( "FPM", "SpawnList", framesPerMinute );
	m_timer->start( this->getTimerDelay(), false );
	if ( framesPerMinute == INSTANT )
		connect( gItemMgr, SIGNAL( spawnChanged(Spawn*) ), SLOT( spawnChanged(Spawn*) ) );
	else
		disconnect( gItemMgr, SIGNAL( spawnChanged(Spawn*) ), this, SLOT( spawnChanged(Spawn*) ) );
}

void SpawnListView::toggleKeepSelectedVisible()
{
	m_keepSelectedVisible = !m_keepSelectedVisible;
	gSEQPrefs->setPrefBool( "KeepSelect", "SpawnList", m_keepSelectedVisible );
}

void SpawnListView::spawnListRightButton( QListViewItem* item, const QPoint& /*point*/, int col )
{
	if ( item && col != -1 )
	{
		QString		columnText;
		QString		columnName;
		
		QStringList		columns = this->getColumnNames();
		columnName = columns[ col ];
		columnText = item->text( col );
		gFilterMgr->addFilter( columnName, columnText );
	}
}
