// itemmgr.cpp
//		SINS Distributed under GPL

#include <qdict.h>
#include <qlistview.h>		// ick
#include <stdio.h>
#include <limits.h>

#include "itemmgr.h"
#include "packet.h"
#include "main.h"
#include "preferences.h"
#include "spawnlist.h"

ItemMgr::ItemMgr( EQPacket* pack, const char* name ):
	QObject( NULL, name ),
	m_Spawns( 613 ),
	m_Drops( 211 ),
	m_Coins( 211 )
{
	m_Spawns.setAutoDelete( true );
	m_Drops.setAutoDelete( true );
	m_Coins.setAutoDelete( true );
	
	m_shortZoneName = "";
	m_longZoneName = "";
	
	m_selected = NULL;

	connect( pack, SIGNAL(handleNewSpawn(const struct addSpawnStruct*)), SLOT(handleNewSpawn(const struct addSpawnStruct*)) );
	connect( pack, SIGNAL(handleZoneSpawns(const struct zoneSpawnsStruct*,int)), SLOT(handleZoneSpawns(const struct zoneSpawnsStruct*,int)) );
	connect( pack, SIGNAL(handleEquipChange(const struct equipChangeStruct*)), SLOT(handleEquipChange(const struct equipChangeStruct*)) );
	connect( pack, SIGNAL(handleZoneEnd(const struct clientZoneInStruct*)), SLOT(handleZoneEnd(const struct clientZoneInStruct*)) );
	connect( pack, SIGNAL(handleZoneBegin(const struct clientZoneOutStruct*)), SLOT(handleZoneBegin(const struct clientZoneOutStruct*)) );
	connect( pack, SIGNAL(handleZoneChange(const struct zoneChangeStruct*)), SLOT(handleZoneChange(const struct zoneChangeStruct*)) );
	connect( pack, SIGNAL(handleCorpse(const struct spawnKilledStruct*)), SLOT(handleCorpse(const struct spawnKilledStruct*)) );
	connect( pack, SIGNAL(handleHPUpdate(const struct spawnHpUpdateStruct*)), SLOT(handleHPUpdate( const struct spawnHpUpdateStruct*)) );
	connect( pack, SIGNAL(handleSpawnUpdate(const struct spawnPosUpdateStruct*)), SLOT(handleSpawnUpdate(const struct spawnPosUpdateStruct*)) );
	connect( pack, SIGNAL(handleNewDrop(const struct addDropStruct*)), SLOT(handleNewDrop(const struct addDropStruct*)) );
	connect( pack, SIGNAL(handleDeleteDrop(const struct deleteDropStruct*)), SLOT(handleDeleteDrop(const struct deleteDropStruct*)) );
	connect( pack, SIGNAL(handleNewCoins(const struct addCoinsStruct*)), SLOT(handleNewCoins(const struct addCoinsStruct*)) );
	connect( pack, SIGNAL(handleDeleteCoins(const struct deleteCoinsStruct*)), SLOT(handleDeleteCoins(const struct deleteCoinsStruct*)) );
	connect( pack, SIGNAL(handleDeleteSpawn(const struct deleteSpawnStruct*)), SLOT(handleDeleteSpawn(const struct deleteSpawnStruct*)) );
	connect( pack, SIGNAL(backfillSpawn(const struct spawnStruct*)), SLOT(backfillSpawn(const struct spawnStruct*)) );
	connect( pack, SIGNAL(keyFound()), SLOT(keyFound()) );
}

void ItemMgr::clear()
{
	m_Spawns.clear();
	m_Drops.clear();
	m_Coins.clear();
	
	m_shortZoneName = "";
	m_longZoneName = "";
}

Spawn* ItemMgr::spawnByID( UWORD id ) const
{
	if ( m_Spawns.find( id ) )
		return m_Spawns[ id ];
	else
		return NULL;
}

const QString ItemMgr::shortZoneName() const
{
	return m_shortZoneName;
}

const QString ItemMgr::longZoneName() const
{
	return m_longZoneName;
}


void ItemMgr::dumpSpawns()
{
#ifdef DEBUG
//	debug( "ItemMgr::dumpSpawns()" );
#endif

	QIntDictIterator<Spawn>		it( m_Spawns );

	printf( "ItemMgr::m_spawns:\n" );
	while ( it.current() )
	{
		printf( "%s\n", (const char*)it.current()->dump() );
		++it;
	}
	printf( "\n" );
}

void ItemMgr::dumpDrops()
{
#ifdef DEBUG
//	debug( "ItemMgr::dumpDrops()" );
#endif

	QIntDictIterator<Drop>		it( m_Drops );

	while ( it.current() )
	{
		printf( "%s\n", (const char*)it.current()->dump() );
		++it;
	}
}

void ItemMgr::dumpCoins()
{
#ifdef DEBUG
//	debug( "ItemMgr::dumpCoins()" );
#endif

	QIntDictIterator<Coins>		it( m_Coins );

	while ( it.current() )
	{
		printf( "%s\n", (const char*)it.current()->dump() );
		++it;
	}
}

void ItemMgr::determineHeight( WORD& minZ, WORD& maxZ ) const
{
	WORD	dummy1, dummy2, dummy3, dummy4;
	this->determineBounds( dummy1, dummy2, dummy3, dummy4, minZ, maxZ );
}

void ItemMgr::determineBounds( WORD& minX, WORD& maxX, WORD& minY, WORD& maxY, WORD& minZ, WORD& maxZ ) const
{
	QIntDictIterator<Spawn>		it( m_Spawns );

	minX = minY = minZ = INT_MAX;
	maxX = maxY = maxZ = INT_MIN;
	
	while ( it.current() )
	{
		Spawn*		spawn = it.current();
		
		WORD		x = spawn->xPos();
		WORD		y = spawn->yPos();
		WORD		z = spawn->zPos();
		
		if ( x > maxX ) maxX = x;
		if ( x < minX ) minX = x;
		if ( y > maxY ) maxY = y;
		if ( y < minY ) minY = y;
		if ( z > maxZ ) maxZ = z;
		if ( z < minZ ) minZ = z;
		
		++it;
	}
}

void ItemMgr::dump()
{
	this->dumpSpawns();
}

void ItemMgr::handleEquipChange( const equipChangeStruct* /*wearing*/ )
{
#ifdef DEBUG
//   debug( "ItemMgr::handleEquipmentChange()" );
#endif

/*
//printf("Spawn %i was going to wear %i in slot %i.\n", wearing->spawnId, wearing->newItemId, wearing->wearSlotId);
   
   if ((wearing->wearSlotId < 9))
   {
     int n = ID2Index(wearing->spawnId);
     if (-1 != n)
     {
	spawns[n].equipment[wearing->wearSlotId] = wearing->newItemId;
	processEquipment (&spawns[n], spawnInfo[n]);

        // update spawnlist
        if (m_pSpawnList)
           m_pSpawnList->UpdateSpawn(&spawns[n]);

	// Buh-Bye silly Wearing updates   - JohnQ
      //  if (*spawnInfo[n])
      //  {
      //    QString temp("");
      //    temp.sprintf("Wearing: '%s' - '%s'", spawns[n].name, spawnInfo[n]);
      //    emit
      //       msgReceived(temp);
       // }
     }
   }
*/
}

void ItemMgr::keyFound()
{
	QIntDictIterator<Spawn>		it( m_Spawns );
	Spawn*		spawn;

	// we do this so we can get pet's names correct
	while ( ( spawn = it.current() ) )
	{
		++it;
		spawn->transformName();
	}
	
	emit allSpawnsChanged();
#ifdef DEBUG
//	this->dumpSpawns();
#endif
}

void ItemMgr::filtersChanged()
{
	emit allSpawnsChanged();
}

void ItemMgr::handleZoneEnd( const clientZoneInStruct* newZone )
{
	m_shortZoneName = newZone->shortName;
	m_longZoneName = newZone->longName;

#ifdef DEBUG
	printf( "ItemMgr::handleZoneEnd( short:%s long:%s )\n", (const char*)m_shortZoneName, (const char*)m_longZoneName );
#endif
	emit zoneEnd( m_shortZoneName );
}

void ItemMgr::handleZoneBegin( const clientZoneOutStruct* )
{
#ifdef DEBUG
	debug( "ItemMgr::handleZoneBegin()" );
#endif
	this->clear();
	
	m_shortZoneName = "-unknown-";
	m_longZoneName = "-unknown-";

	emit zoneBegin();
}

void ItemMgr::handleZoneChange( const zoneChangeStruct* zoneChange )
{
	this->clear();
	
	m_shortZoneName = zoneChange->zoneName;

#ifdef DEBUG
	printf( "ItemMgr::handleZoneChange( %s )\n", (const char*)m_shortZoneName );
#endif
	
	emit zoneChanged( m_shortZoneName );
}

void ItemMgr::handleCorpse( const spawnKilledStruct* deadspawn )
{
#ifdef DEBUG
//	debug( "ItemMgr::handleCorpse()" );
#endif
	Spawn*		spawn = m_Spawns.find( deadspawn->spawnId );

	if ( !spawn )
		return;

	spawn->setCorpse();
	
	emit killSpawn( spawn );
}

void ItemMgr::handleDeleteSpawn( const deleteSpawnStruct* delspawn )
{
#ifdef DEBUG
//	debug( "ItemMgr::handleDeleteSpawn()" );
#endif

	Spawn*		spawn = m_Spawns.find( delspawn->spawnId );
	
	if ( spawn )
	{
		if ( m_selected == spawn )
			m_selected = NULL;
			
		emit deleteSpawn( spawn );
		m_Spawns.remove( delspawn->spawnId );	
   }
}


void ItemMgr::handleHPUpdate( const spawnHpUpdateStruct* hpupdate )
{
#ifdef DEBUG
//	debug( "ItemMgr::handleHPUpdate()" );
#endif

	if ( hpupdate->spawnId == gPlayer->id() )
		return;

	Spawn* spawn = m_Spawns.find( hpupdate->spawnId );
	if ( spawn )
	{
		spawn->setHP( hpupdate->curHp );
		emit spawnChanged( spawn );
	}
}


void ItemMgr::handleSpawnUpdate( const spawnPosUpdateStruct* updates )
{
#ifdef DEBUG
//	debug( "ItemMgr::handleSpawnUpdate()" );
#endif
	for ( int a = 0; a < updates->numUpdates; a++ )
	{
		UWORD		id = updates->updates[ a ].spawnId;
		
		Spawn*		spawn = m_Spawns.find( id );
		
		if ( !spawn )
		{
//			printf( "in SpawnUpdate adding spawn %d\n", id );
			spawn = new Spawn( id, updates->updates[ a ].heading );
			
			if ( spawn )
			{
				m_Spawns.insert( id, spawn );
				emit addSpawn( spawn );
				emit numSpawns( m_Spawns.count() );
			}
		}

		spawn->updatePosition( updates->updates[ a ] );
		emit spawnChanged( spawn );
	}
}
				
/*		
	if ( spawn )
	{

		if ( spawn->isplayer  == 10 )
		{
			location*		loc = spawn->m_trackPoints.first();
			if ( !loc || ( loc->x == 0 && loc->y == 0 ) )
			{t
				if ( !loc )
					loc = new location( update.x, update.y, update.z );
				
				spawn->m_trackPoints.append( loc );
			}
		}
		
		if ( gSEQPrefs->walkpathrecord )
		{
			unsigned int	count = spawn->m_trackPoints.count();
			location*		loc = spawn->m_trackPoints.end();
			
			if ( loc && ( loc->x != update.x || loc->y != update.y ) )
			{
				location*		newLoc = new location( update.x, update.y, update.z );

				spawn->m_trackPoints.append( newLoc );
				if ( gSEQPrefs->walkpathlength != -1 && count >= gSEQPrefs->walkpathlength )
					spawn->m_trackPoints.append( newLoc );
		}
	}
}
*/

void ItemMgr::handleNewSpawn( const struct addSpawnStruct* aspawn )
{
#ifdef DEBUG
//	QString		nameTmp = aspawn->spawn.name;
//	printf( "ItemMgr::handleNewSpawn( %s )\n", (const char*)nameTmp );
#endif
	
	SpawnStruct	spawn = aspawn->spawn;
	
	if ( spawn.NPC == 10 )
	{
		spawn.spawnId = gPlayer->id();
		printf( "player spawn id: %d\n", spawn.spawnId );
	}

	this->__addSpawn( spawn );
}

void ItemMgr::handleZoneSpawns( const struct zoneSpawnsStruct* zspawns, int count )
{
#ifdef DEBUG
//	debug( "ItemMgr::handleZoneSpawns()" );
#endif

	for ( int a = 0; a < count; a++ )
	{
		SpawnStruct		spawn = zspawns->spawn[ a ];
		this->__addSpawn( spawn );
	}
}

void ItemMgr::handleNewDrop( const addDropStruct* adrop )
{
#ifdef DEBUG
//	debug( "ItemMgr::handleNewDrop()" );
#endif

	Drop*		newDrop = new Drop( *adrop );
	
	if ( m_Drops.find( adrop->dropId ) )
		m_Drops.replace( adrop->dropId, newDrop );
	else
		m_Drops.insert( adrop->dropId, newDrop );
}

void ItemMgr::handleDeleteDrop( const deleteDropStruct* rdrop )
{
#ifdef DEBUG
//	debug( "ItemMgr::deleteDrop()" );
#endif
	if ( m_Drops.find( rdrop->dropId ) )
		m_Drops.remove( rdrop->dropId );
}

void ItemMgr::handleNewCoins( const addCoinsStruct* cdrop )
{
#ifdef DEBUG
//	debug( "ItemMgr::newCoins()" );
#endif

	Coins*		newCoins = new Coins( *cdrop );
	
	if ( m_Coins.find( cdrop->dropId ) )
		m_Coins.replace( cdrop->dropId, newCoins );
	else
		m_Coins.insert( cdrop->dropId, newCoins );
}

void ItemMgr::handleDeleteCoins( const deleteCoinsStruct* crdrop )
{
#ifdef DEBUG
//	debug( "ItemMgr::deleteCoins()" );
#endif
	if ( m_Coins.find( crdrop->dropId ) )
		m_Coins.remove( crdrop->dropId );
}


void ItemMgr::backfillSpawn( const struct spawnStruct* spawnData )
{
#ifdef DEBUG
//	debug( "ItemMgr::backfillSpawn()" );
#endif

	Spawn*					spawn;

	spawn = m_Spawns.find( spawnData->spawnId );
	if ( !spawn )
		spawn = this->__addSpawn( *spawnData );
	else
	{
		spawn->backfill( *spawnData );
		emit processSpawn( spawn );
		emit spawnChanged( spawn );
	}
}

Spawn* ItemMgr::__addSpawn( const SpawnStruct& spawn )
{
	Spawn* newSpawn = m_Spawns.find( spawn.spawnId );
	
	if ( newSpawn )
	{
#ifdef DEBUG
//		printf( "replace spawn %d\n", spawn.spawnId );
#endif
		return newSpawn;
	}
	else
	{
#ifdef DEBUG
//		printf( "new spawn %d\n", spawn.spawnId );
#endif
		newSpawn = new Spawn( spawn );
		
		if ( newSpawn )
		{
			m_Spawns.insert( spawn.spawnId, newSpawn );
			emit processSpawn( newSpawn );
			emit addSpawn( newSpawn );
			emit numSpawns( m_Spawns.count() );
		}
	}

	return newSpawn;
}

void ItemMgr::selectionChanged( Spawn* newSelectedItem )
{
	if ( m_selected )
		m_selected->clearSelected();
	
	m_selected = newSelectedItem;

	if ( m_selected )
		m_selected->setSelected();
	
	emit handleSelectItem( newSelectedItem );
}
