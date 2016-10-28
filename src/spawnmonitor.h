// spawnmonitor.h
//		SINS Distributed under GPL

#ifndef SPAWNMONITOR_H
#define SPAWNMONITOR_H

// unfortunately, Qt's notions of time aren't convenient enough to use for something
//	like Spawn timing, since QTime doesn't have any simple way to subtract 2 times
//	that might be more than a full day apart... I rely on the functions in "time.h"
//	for now...
//
//	since we're only really interested in holding timestamps in wall-clock time
//	for spawn points, we don't do any funky real-time -> EQ-time conversions.
//	the first instantiation of the "SpawnPoint" class, m_spawnTime will contain the
//	actual time it is at the time of instantiation, later we get updated by the
//  SpawnMonitor to reflect that spawn point's cycle time and set m_diffTime
//
//	the SpawnMonitor contains one IntDict holding a SpawnPoint for every new
//	spawn that comes in... if a spawn occurs for a SpawnPoint that already exists
//	in "m_spawns", then that SpawnPoint is moved to "m_points" and is promoted
//	to an actual spawn point and deleted from "m_spawns"...
//
//	this is experimental, since it's quite possible there might be false positives
//	because the spawns are random... a few false positivies are acceptable provided
//	there is some utility in the spawn timing functionality... i will probably try
//	to derive some test to weed out the false positives based on how old they are:
//	i.e. if a spawn point in m_points doesn't get an update for over 2 weeks, remove
//	it... i don't know enough yet to determine what length is "too old", since there
//	are rumored to be very rare, yet static, spawns in EQ

#include "spawn.h"
#include <time.h>
#include <qobject.h>
#include <qasciidict.h>

class SpawnPoint: public Location
{
public:
	SpawnPoint( UWORD spawnID, const Location& loc, time_t diffTime = 0 ):
		Location( loc ),
		m_spawnTime( time( 0 ) ),
		m_deathTime( 0 ),
		m_diffTime( diffTime ),
		m_lastID( spawnID ),
		m_count( 1 )
	{
	}
	
	unsigned char age()
	{
		if ( m_deathTime == 0 )
			return 0;

		long		scaledColor = 255;
		float		ratio = (float)( time( 0 ) - m_deathTime ) / (float)m_diffTime;

		scaledColor = (long)( scaledColor * ratio );
		if ( scaledColor > 255 )
			scaledColor = 255;
		else if ( scaledColor < 0 )
			scaledColor = 0;
		return (unsigned char)scaledColor;
	}

	
	time_t			m_spawnTime;
	time_t			m_deathTime;
	time_t			m_diffTime;
	UWORD			m_lastID;
	unsigned short	m_count;
};

class SpawnMonitor: public QObject
{
Q_OBJECT
public:
	SpawnMonitor::SpawnMonitor( const char* name = NULL );

	const QAsciiDict<SpawnPoint>& spawnPoints() { return m_points; }
	const QAsciiDict<SpawnPoint>& spawns() { return m_spawns; }

public slots:
	void newSpawn( Spawn* spawn );
	void killSpawn( Spawn* spawn );
	void zoneChanged( const QString& newZoneName );
	void zoneEnd( const QString& newZoneName );
	void saveSpawnPoints();
	void loadSpawnPoints();

signals:
	void newSpawnPoint( const SpawnPoint* spawnPoint );
	void clearSpawnPoints();

protected:
	void restartSpawnPoint( SpawnPoint* spawnPoint );
	void checkSpawnPoint( Spawn* spawn );

	QString					m_zoneName;
	QAsciiDict<SpawnPoint>	m_spawns;
	QAsciiDict<SpawnPoint>	m_points;
};

#endif
