// itemmgr.h
//		SINS Distributed under GPL

#ifndef ITEMMGR_H
#define ITEMMGR_H

#include "spawn.h"
#include "player.h"
#include "filter.h"
#include <qobject.h>
#include <qstring.h>
#include <qintdict.h>
#include <qdict.h>

class QListViewItem;
class EQPacket;
class Alerter;

typedef QIntDictIterator<Spawn> SpawnIterator;
typedef QIntDictIterator<Coins> CoinsIterator;
typedef QIntDictIterator<Drop> DropIterator;

class ItemMgr: public QObject
{
Q_OBJECT
public:
	ItemMgr( EQPacket* pack, const char* name = NULL );

	void clear();

	Spawn* spawnByID( UWORD id ) const;
	
	const QString shortZoneName() const;
	const QString longZoneName() const;
	
	int getZEM() const { return m_zoneEM; }
	void setZEM( int newZEM ) { m_zoneEM = newZEM; }

	void determineHeight( WORD& minZ, WORD& maxZ ) const;	
	void determineBounds( WORD& minX, WORD& maxX, WORD& minY, WORD& maxY, WORD& minZ, WORD& maxZ ) const;
	
	void dump();

	const QIntDict<Spawn>& spawns() { return m_Spawns; }
	const QIntDict<Drop>& drops() { return m_Drops; }
	const QIntDict<Coins>& coins() { return m_Coins; }

	Spawn* selected() { return m_selected; }
	
public slots:
	void selectionChanged( Spawn* spawn );

	void keyFound();
	void filtersChanged();	
	
	void handleZoneSpawns( const struct zoneSpawnsStruct* zspawns, int count );

	void handleEquipChange( const struct equipChangeStruct* wearing );
	void handleZoneEnd( const struct clientZoneInStruct* newZone );
	void handleZoneBegin( const struct clientZoneOutStruct* zout );
	void handleZoneChange( const struct zoneChangeStruct* zoneChange );
	void handleCorpse( const struct spawnKilledStruct* deadspawn );
	void handleHPUpdate( const struct spawnHpUpdateStruct* hpupdate );
	void handleSpawnUpdate( const struct spawnPosUpdateStruct* updates );
	void handleNewSpawn( const struct addSpawnStruct* spawn );
	void handleDeleteSpawn( const struct deleteSpawnStruct* spawn );
	void handleNewDrop( const struct addDropStruct* adrop );
	void handleDeleteDrop( const struct deleteDropStruct* rdrop );
	void handleNewCoins( const struct addCoinsStruct* cdrop );
	void handleDeleteCoins( const struct deleteCoinsStruct* crdrop );

	void backfillSpawn( const struct spawnStruct* spawn );
	
	void dumpDrops();
	void dumpCoins();
	void dumpSpawns();

signals:
	void zoneEnd( const QString& newZoneName );
	void zoneChanged( const QString& newZoneName );
	void zoneBegin();

	void processSpawn( Spawn* spawn );
	void addSpawn( Spawn* spawn );
	void deleteSpawn( Spawn* spawn );
	void killSpawn( Spawn* spawn );

	void spawnChanged( Spawn* spawn );
	void allSpawnsChanged();
	
	void addCoins( Coins* coins );
	void deleteCoins( Coins* coins );
	
	void addDrop( Drop* drop );
	void deleteDrop( Drop* drop );
	
	void numSpawns( int );
	
	void handleSelectItem( Spawn* spawn );

protected:
	Spawn* __addSpawn( const SpawnStruct& newSpawn );
	
	QIntDict<Spawn>				m_Spawns;
	QIntDict<Drop>				m_Drops;
	QIntDict<Coins>				m_Coins;		

	QString						m_longZoneName;
	QString						m_shortZoneName;
	
	int							m_zoneEM;
	
	Spawn*						m_selected;

	FilterMgr*					m_filters;
};

#endif
