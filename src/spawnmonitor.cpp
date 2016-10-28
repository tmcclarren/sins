// spawnmonitor.cpp
//		SINS Distributed under GPL

#include "spawnmonitor.h"
#include "itemmgr.h"
#include "main.h"
#include "util.h"

#include <qdir.h>
#include <qfile.h>
#include <qfileinfo.h>
#include <qtextstream.h>


SpawnMonitor::SpawnMonitor( const char* name ):
	QObject( NULL, name ),
	m_spawns( 613 ),
	m_points( 211 )
{
	m_spawns.setAutoDelete( true );
	m_points.setAutoDelete( true );

	connect( gItemMgr, SIGNAL( addSpawn(Spawn*) ), this, SLOT( newSpawn(Spawn*) ) );
	connect( gItemMgr, SIGNAL( killSpawn(Spawn*) ), this, SLOT( killSpawn(Spawn*) ) );
	connect( gItemMgr, SIGNAL( zoneChanged(const QString&) ), this, SLOT( zoneChanged(const QString&) ) );
	connect( gItemMgr, SIGNAL( zoneEnd(const QString&) ), this, SLOT( zoneEnd( const QString&) ) );
}

void SpawnMonitor::newSpawn( Spawn* spawn )
{
//	debug( "SpawnMonitor::handleNewSpawn" );
	this->checkSpawnPoint( spawn );
};

void SpawnMonitor::killSpawn( Spawn* killedSpawn )
{
	QAsciiDictIterator<SpawnPoint>		it( m_points );

	SpawnPoint*		sp;
	while ( ( sp = it.current() ) )
	{
		if ( killedSpawn->id() == sp->m_lastID )
		{
			//printf( "death time: %d    %d\n", killedSpawn->spawnId, time( 0 ) );
			this->restartSpawnPoint( sp );
			break;
		}
		++it;
	}
}

void SpawnMonitor::zoneChanged( const QString& newZoneName )
{
	emit clearSpawnPoints();
	m_spawns.clear();
	m_points.clear();
	m_zoneName = newZoneName;
	this->loadSpawnPoints();
}

void SpawnMonitor::zoneEnd( const QString& newZoneName )
{
	m_zoneName = newZoneName;
}

void SpawnMonitor::restartSpawnPoint( SpawnPoint* sp )
{
	sp->m_lastID = 0;
	sp->m_deathTime = time( 0 );
}
	
void SpawnMonitor::checkSpawnPoint( Spawn* spawn )
{
//	debug( "SpawnMonitor::checkSpawnPoint" );

	// ignore player spawns
	if ( spawn->NPC() == 0 )
		return;

	char		tempKey[ 7 ];

	*((WORD*)tempKey) = spawn->xPos();
	*((WORD*)( tempKey + 2 )) = spawn->yPos();
	*((WORD*)( tempKey + 4 )) = spawn->zPos();
	tempKey[ 6 ] = 0;

//	printf( "tempKey: " );
//	printf( "%d ", *( (unsigned short*)tempKey ) );
//	printf( "%d ", *( (unsigned short*)( tempKey + 2 ) ) );
//	printf( "%d ", *( (unsigned short*)( tempKey + 4 ) ) );
//	printf( "\n" );

	SpawnPoint*		sp;
	sp = m_points.find( tempKey );
	if ( sp )
	{
		//if ( sp->m_lastID != 0 )
		//	printf( "DOUBLE SPAWN\n" );

		sp->m_lastID = spawn->id();
		sp->m_spawnTime = time( 0 );

//		printf( "spawn time: %d    %d\n", sp->m_lastID, sp->m_spawnTime );

		if ( sp->m_deathTime != 0  )
		{
			sp->m_diffTime = sp->m_spawnTime - sp->m_deathTime;
//			printf( "setting diffTime: %d\n", sp->m_diffTime );
		}

		sp->m_count++;
	}
	else
	{
		sp = m_spawns.find( tempKey );
		if ( sp )
		{
			sp->m_lastID = spawn->id();
			sp->m_spawnTime = time( 0 );
			sp->m_count++;

			m_points.insert( tempKey, sp );
			emit newSpawnPoint( sp );
			m_spawns.take( tempKey );
		}
		else
		{
			sp = new SpawnPoint( spawn->id(), spawn->position() );
			m_spawns.insert( tempKey, sp );
		}
	}
}

void SpawnMonitor::saveSpawnPoints()
{
//	debug( "SpawnMonitor::saveSpawnPoints" );

	QString		fileName;
	
	fileName = CONFDIR;
	fileName += m_zoneName;
	fileName += ".sp";

	QString		newName = fileName + ".new";
	QFile		spFile( newName );

	if ( !spFile.open( IO_WriteOnly ) )
	{
		printf( "Failed to open %s for writing", (const char*)newName );
		return;
	}
	
	QTextStream	output( &spFile );
	
	QAsciiDictIterator<SpawnPoint>		it( m_points );
	SpawnPoint* sp;

	while ( ( sp = it.current() ) )
	{
		++it;
		
		output	<< sp->x
				<< " "
				<< sp->y
				<< " "
				<< sp->z
				<< " "
				<< (unsigned long)sp->m_diffTime
				<< "\n";
	}

	spFile.close();

	QFileInfo		fi( spFile );
	QFile			old( fileName );
	QDir			dir( fi.dir() );
	QString			backupName = fileName + ".bak";

	if ( old.exists() )
	{
		if ( dir.rename( fileName, backupName ) )
		{
			if ( !dir.rename( newName, fileName ) )
				printf( "Failed to rename %s to %s\n", (const char*)newName, (const char*)fileName );
		}
	}
	else
	{
		if ( !dir.rename( newName, fileName ) )
			printf( "Failed to rename %s to %s\n", (const char*)newName, (const char*)fileName );
	}
}


void SpawnMonitor::loadSpawnPoints()
{
	QString		fileName;
	
	fileName = CONFDIR;
	fileName += m_zoneName;
	fileName += ".sp";

	if ( !findFile( fileName ) )
	{
		printf( "Can't find spawn point file %s\n", (const char*)fileName );
		return;
	}

	QFile		spFile( fileName );

	if ( !spFile.open( IO_ReadOnly ) )
	{
		printf( "Can't open spawn point file %s\n", (const char*)fileName );
		return;
	}

	QTextStream		input( &spFile );
	
	while ( !input.atEnd() )
	{
		WORD			x, y, z;
		unsigned long	diffTime;

		input >> x;
//printf( "x: %d\n", x );
		input >> y;
//printf( "y: %d\n", y );
		input >> z;
//printf( "z: %d\n", z );
		input >> diffTime;
//printf( "diff: %d\n", diffTime );

		Location	loc( x, y, z );
		SpawnPoint*	p = new SpawnPoint( 0, loc, diffTime );
		if ( p )
		{
			char		tempKey[ 7 ];

			*((WORD*)tempKey) = x;
			*((WORD*)( tempKey + 2 )) = y;
			*((WORD*)( tempKey + 4 )) = z;
			tempKey[ 6 ] = 0;
			
			if ( !m_points.find( tempKey ) )
			{
				m_points.insert( tempKey, p );
				emit newSpawnPoint( p );
			}
			else
				delete p;
		}
	}
	printf( "Loaded spawn points: %s\n", (const char*)fileName );
}
