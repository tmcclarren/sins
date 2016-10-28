// spawnpointlist.cpp
//		SINS Distributed under GPL

#include <qlayout.h>
#include <time.h>
#include "spawnpointlist.h"
#include "main.h"

const FieldMap<SpawnPoint> SpawnPointListView::m_map[] = {
	{ "X", SpawnPointListView::X },
	{ "Y", SpawnPointListView::Y },
	{ "Z", SpawnPointListView::Z },
	{ "Remaining", SpawnPointListView::TimeRemaining },
	{ NULL, NULL }
};

SpawnPointListView::SpawnPointListView( QWidget* parent, const char* name = NULL ):
	BaseListView( "Spawn Points", parent, name ),
	ListViewWrapper<SpawnPoint>( m_map, this, 41 )
{
	connect( gSpawnMonitor, SIGNAL( newSpawnPoint(const SpawnPoint*) ),
		this, SLOT( newSpawnPoint(const SpawnPoint*) ) );
	connect( gSpawnMonitor, SIGNAL( clearSpawnPoints() ),
		this, SLOT( clear() ) );

	// put in all the spawn points that might already be present in
	// the spawn monitor
	QAsciiDictIterator<SpawnPoint>		it( gSpawnMonitor->spawnPoints() );
	SpawnPoint*		sp;

	while ( ( sp = it.current() ) )
	{
		++it;
		this->addItem( (int)sp, sp );
	}

	m_timer = new QTimer( this, "spawn-point-timer" );
	connect( m_timer, SIGNAL( timeout() ), this, SLOT( refresh() ) );
	m_timer->start( 10000, false );
}

void SpawnPointListView::refresh()
{
	this->updateAll();
}

void SpawnPointListView::newSpawnPoint( const SpawnPoint* sp )
{
	this->addItem( (int)sp, (SpawnPoint*)sp );
}

void SpawnPointListView::clear()
{
	BaseListView::clear();
	m_items.clear();
}

void SpawnPointListView::TimeRemaining( SpawnPoint* sp, QString& tmp )
{
	if ( sp->m_diffTime == 0 || sp->m_deathTime == 0 )
		tmp = "?";
	else
	{
		long		secs = time( 0 ) - sp->m_deathTime;
		secs = sp->m_diffTime - secs;

		if ( secs > 0 )
			tmp.sprintf( "%2ld:%02ld", secs / 60, secs % 60  );
		else
			tmp = "now";
	}
}

SpawnPointWindow::SpawnPointWindow( const char* name = NULL ):
	BaseWindow( "Spawn Points", NULL, name )
{
	QHBoxLayout*	layout = new QHBoxLayout( this );
	layout->setAutoAdd( true );

	m_spawnPointList = new SpawnPointListView( this, "spawn-point-list" );
	m_spawnPointList->restore();
};

SpawnPointWindow::~SpawnPointWindow()
{
	if ( m_spawnPointList )
		m_spawnPointList->saveToPreferences();
}
