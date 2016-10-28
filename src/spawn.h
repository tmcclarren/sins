//	spawn.h
//		SINS Distributed under GPL

#ifndef SPAWN_H
#define SPAWN_H

#include <qobject.h>
#include <qlist.h>
#include <qstring.h>
#include <qdatetime.h>
#include "everquest.h"

class SpawnListView;

template < class T >
class LocationT
{
public:
	LocationT()
	{
		x = 0; y = 0; z = 0;
	}
	
	LocationT( T x2, T y2, T z2 )
	{
		x = x2; y = y2; z = z2;
	}
	
	T			x;
	T			y;
	T			z;
};

class Location: public LocationT<WORD>
{
public:
	Location(): LocationT<WORD>() { }
	Location( const LocationStruct& loc ): LocationT<WORD>( loc.x, loc.y, loc.z ) { }
	Location( WORD x2, WORD y2, WORD z2 ): LocationT<WORD>( x2, y2, z2 ) { }
};

class FPLocation: public LocationT<float>
{
public:
	FPLocation(): LocationT<float>() { }
	FPLocation( float x2, float y2, float z2 ): LocationT<float>( x2, y2, z2 ) { }
};

class GameItem
{
public:
	enum GameItemFlag {
		k_none =			0x00000000,
		k_filtered =		0x00000001,
		k_hidden =			0x00000002,
		k_highlight =	 	0x00000004,
		k_aggressor =		0x00000008,
		k_selected =		0x00000010,
		k_corpse =			0x00000020,
		k_unnamed =			0x00000040,
		k_corpseNameSet =	0x00000080,
		k_player =			0x00000100,
		k_alert =			0x00000200,
		k_uninited =		0x00000400,
		k_userFlag1 =		0x00100000,
		k_userFlag2 =		0x00200000,
		k_userFlag3 =		0x00400000,
		k_userFlag4 =		0x00800000,
		k_dirty =			0x80000000,
		k_posChanged =		0x40000000,
		k_hpChanged =		0x20000000,
		k_levelChanged =	0x10000000
	};
	
	GameItem();

	GameItem( UWORD id );

	// stuff subclasses need to deal with
	virtual WORD xPos() const = 0;
	virtual WORD yPos() const = 0;
	virtual WORD zPos() const = 0;
	virtual QString info() const = 0;

	// the following are all 'getters'	
	const UWORD id() const { return m_id; }
	
	virtual QString name() const;	
	virtual QString filterString() const { return ""; }
	virtual QString dump() const { return filterString(); }

	const Location position() const { return Location( this->xPos(), this->yPos(), this->zPos() ); }



	unsigned long calcDist( WORD x2, WORD y2, WORD z2 ) const;
	unsigned long calcDist( const Location& loc ) const { return this->calcDist( loc.x, loc.y, loc.z ); }
	
	// flag operations -- trying not to expose them to world
	void setFlag( GameItemFlag flag ) { m_flags |= flag; }
	void clearFlag( GameItemFlag flag ) { m_flags &= ~flag; }
	bool isFlagSet( GameItemFlag flag ) const { return ( ( m_flags & flag ) != 0 ); }
	
	void setSelected() { this->setFlag( k_selected ); }
	void clearSelected() { this->clearFlag( k_selected ); }
	bool isSelected() const { return ( this->isFlagSet( k_selected ) ); }

protected:
	UWORD 			m_id;
	unsigned long	m_flags;
};

class Spawn: public GameItem
{
public:
	enum Class {
		eWarrior = 1,
		eCleric = 2,
		ePaladin = 3,
		eRanger = 4,
		eShadowKnight = 5,
		eDruid = 6,
		eMonk = 7,
		eBard = 8,
		eRogue = 9,
		eShaman = 10,
		eNecromancer = 11,
		eWizard = 12,
		eMagician = 13,
		eEnchanter = 14 };

	enum Race {
		eHuman = 1,
		eBarbarian = 2,
		eErudite = 3,



		eWoodElf = 4,
		eHighElf = 5,
		eDarkElf = 6,
		eHalfElf = 7,
		eDwarf = 8,
		eTroll = 9,
		eOgre = 10,
		eHalfling = 11,
		eGnome = 12,
		eIksar = 128 };

	Spawn();
	Spawn( UWORD id, const SpawnHeading& heading );
	Spawn( const SpawnStruct& indata, long aggroRange = 0 );
	virtual ~Spawn() { }

	// the following are all 'getters'...
	QString	name() const { return m_name; }
	QString info() const;
	QString equipString() const { return m_spawnInfo; }

	WORD xPos() const { return m_data.heading.loc.x; }
	WORD yPos() const { return m_data.heading.loc.y; }
	WORD zPos() const { return m_data.heading.loc.z; }
	DWORD deltaX() const { return m_data.heading.deltaX; }
	DWORD deltaY() const { return m_data.heading.deltaY; }
	DWORD deltaZ() const { return m_data.heading.deltaZ; }
	UBYTE level() const { return m_data.level; }
	WORD curHp() const { return m_data.curHp; }
	WORD maxHp() const { return m_data.maxHp; }
	UBYTE race() const { return m_data.race; }
	UBYTE class_() const { return m_data.class_; }
	UBYTE gender() const { return m_data.gender; }
	UBYTE NPC() const { return m_data.NPC; }
	UBYTE light() const { return m_data.light; }
	UBYTE heading() const { return m_data.heading.heading; }
	BYTE deltaHeading() const { return m_data.heading.deltaHeading; }
	UWORD petOwnerID() const { return m_data.petOwnerId; }
	UBYTE equipment( int i ) const { return m_data.equipment[ i ]; }

	bool isPC() const { return ( m_data.NPC == 0 ); }
	bool isMob() const { return ( m_data.NPC == 1 ); }

	bool isSameTeam( int otherRace ) const;
	bool isCorpse() const { return this->isFlagSet( k_corpse ); }
	bool isPlayer() const { return this->isFlagSet( k_player ); }
	
	QTime spawnTime() const { return m_spawnTime; }
	QDate spawnDate() const { return m_spawnDate; }
	QTime updateTime() const { return m_updateTime; }

	QString raceName() const;
	QString className_() const;		// QObject already has 'className', so we need the "_"
	QString lightName() const;
	QString typeName() const;
	static QString materialName( unsigned char index );
	static QString weaponName( unsigned char index );
	static QString languageName( long index );
	
	bool depthFilter( int floor, int ceiling ) const
	{
		return ( ( zPos() < floor ) || ( zPos() > ceiling ) );
	}
	
	long aggroRange() const { return 0; }

	QString filterString() const;
	
	QString processEquipment() const;

	float classPenalty() const;
	float racePenalty() const;
	
	// the following are 'setters'
	void backfill( const SpawnStruct& spawnData );
	void updatePosition( const SpawnUpdate& update );
	void setHP( WORD newHP ) { m_data.curHp = newHP; this->setFlag( k_hpChanged ); }
	void setCorpse();
	
	Location approximatePosition( bool animate );
	
	void transformName();	
protected:
	friend class		SpawnListView;

	QString __fixName();

	void __preCalcHeading();			// pre-calculates using the speed factor
	void __stop();
	
	FPLocation			m_preCalcHeading;
	SpawnStruct			m_data;
	QString				m_spawnInfo;
	QString				m_name;
	QDate				m_spawnDate;
	QTime				m_spawnTime;
	QTime				m_updateTime;
};

class Drop: public GameItem
{
public:
	Drop( const struct addDropStruct& indrop );
	Drop( const struct deleteDropStruct& indrop );
	virtual ~Drop() { }

	WORD xPos() const { return ( (WORD)m_data.xPos ); }
	WORD yPos() const { return ( (WORD)m_data.yPos ); }
	WORD zPos() const { return ( (WORD)m_data.zPos ); }

	QString info() const;
	
	QString name() const;
	
	QString filterString() const;

protected:
	void			init();

	struct addDropStruct	m_data;
	QString					m_dropInfo;
};

class Coins: public GameItem
{
public:
	Coins( const struct addCoinsStruct& incoins );
	Coins( const struct deleteCoinsStruct& incoins );

	WORD xPos() const { return ( (WORD)m_data.xPos ); }
	WORD yPos() const { return ( (WORD)m_data.yPos ); }
	WORD zPos() const { return ( (WORD)m_data.zPos ); }

	QString info() const;
	QString name() const;
	QString filterString() const;

protected:
	struct addCoinsStruct	m_data;
};

#endif
