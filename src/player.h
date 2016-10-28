//	player.h
//		SINS Distributed under GPL

#ifndef PLAYER_H
#define PLAYER_H

#include <qwidget.h>
#include "everquest.h"
#include "main.h"
#include "spawn.h"

#define MAX_LEVEL	100

class EQPacket;

class Player: public QObject, public Spawn
{
Q_OBJECT
public:
	Player( EQPacket* pack, const char* name = NULL );
	
	unsigned long currentExp() { return m_currentExp; }
	unsigned long maxExp() { return m_nextLevelExp; }
	unsigned long minExp() { return m_currLevelExp; }
	
	QColor pickConColor( const Spawn* s ) const;

public slots:
	void handleManaUsed( const struct manaDecrementStruct* mana );
	void handleStamina( const struct staminaStruct* stam );
	void handlePlayerPos( const struct playerUpdateStruct* pupdate );
	void handleSkillUp( const struct skillIncreaseStruct* skilli );
	void handleLevelUp( const struct levelUpStruct* levelup );
	void handleXPUpdate( const struct expUpdateStruct* exp );
	void handleHPUpdate( const struct spawnHpUpdateStruct* hpupdate );
	void handlePlayerProfile( const struct playerProfileStruct* player );
	void handleZoneChange( const struct zoneChangeStruct* newZone );
	void handleZoneEnd( const struct clientZoneInStruct* newZone );
	void handlePlayerItem( const struct itemPlayerStruct* itemp );
	void backfillPlayer( const struct playerProfileStruct* player );

signals:
	void xposChanged( int );
	void yposChanged( int );
	void zposChanged( int );
	
	void expChangedString( const QString& );
	void expChangedInt( unsigned long, unsigned long, long );

	void headingChanged( int );
	void playerChanged( int, int, int, int, int, int, int );

	void levelUp( int );
	void addSkill( int, int );
	void changeSkill( int, int );
	void statsChanged( const struct primStatStruct*, const struct primStatStruct* );
	void manaChanged( WORD, WORD );
	void stamChanged( int, int, int, int, int, int );
	void hpChanged( int, int );
	
	void playerUpdate( const SpawnUpdate& newPos );
	
protected:
	void __fillConTable();
	unsigned long calcExpCurrLevel() { return ( this->calcExpToLevel( this->level() - 1 ) ); }
	unsigned long calcExpNextLevel() { return ( this->calcExpToLevel( this->level() ) ); }
	unsigned long calcExpToLevel( int level );

	WORD calcMaxMana();
	
	void reset();
	
	void setData( const struct playerProfileStruct& player );
	
	void dumpBaseStats();
	
	SpawnUpdate			m_pos;
	PrimStatStruct		m_maxStats;
	
	struct playerProfileStruct	m_playerData;
	
	unsigned long		m_currentExp;
	unsigned long		m_nextLevelExp;
	unsigned long		m_currLevelExp;
	
	WORD				m_maxMana;
			
	WORD				m_plusmana;
	int					m_plusHP;
	
	QColor				m_conTable[ MAX_LEVEL ];
	unsigned char		playerSkills[ 74 ];
};


class GroupMgr: public QObject
{
Q_OBJECT
public:
	GroupMgr( const char* name = NULL);
	
	Spawn* memberByID( UWORD id );
	Spawn* memberByName( const QString& name );

	int groupSize();
	int groupPercentBonus();
	
	unsigned long totalLevels();
	
public slots:
	void handleGroupInfo( const groupMemberStruct* gmem  );

signals:
	void addGroup( Spawn* mem );
	void remGroup( Spawn* mem );
	void clrGroup();

protected:
	QList<Spawn>		m_group;
};
	
#endif

