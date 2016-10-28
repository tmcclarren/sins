//	player.cpp
//		SINS Distributed under GPL

#include <stdio.h>
#include "player.h"
#include "util.h"
#include "packet.h"
#include "main.h"
#include "itemmgr.h"

Player::Player( EQPacket* pack, const char* name ):
	QObject( NULL, name ),
	Spawn()
{
#ifdef DEBUG
//	debug( "Player::Player()" );
#endif
	this->reset();
	
	// connect me up
	connect( pack, SIGNAL(handleManaUsed(const struct manaDecrementStruct*)), this, SLOT(handleManaUsed(const struct manaDecrementStruct*)) );
	connect( pack, SIGNAL(handleStamina(const struct staminaStruct*)), this, SLOT(handleStamina(const struct staminaStruct*)) );
	connect( pack, SIGNAL(handlePlayerPos(const struct playerUpdateStruct*)), this, SLOT(handlePlayerPos(const struct playerUpdateStruct*)) );
	connect( pack, SIGNAL(handleSkillUp(const struct skillIncreaseStruct*)), this, SLOT(handleSkillUp(const struct skillIncreaseStruct*)) );
	connect( pack, SIGNAL(handleLevelUp(const struct levelUpStruct*)), this, SLOT(handleLevelUp(const struct levelUpStruct*)) );
	connect( pack, SIGNAL(handleXPUpdate(const struct expUpdateStruct*)), this, SLOT(handleXPUpdate(const struct expUpdateStruct*)) );
	connect( pack, SIGNAL(handleHPUpdate(const struct spawnHpUpdateStruct*)), this, SLOT(handleHPUpdate(const struct spawnHpUpdateStruct*)) );
	connect( pack, SIGNAL(handlePlayerProfile(const struct playerProfileStruct*)), this, SLOT(handlePlayerProfile(const struct playerProfileStruct*)) );
	connect( pack, SIGNAL(handleZoneChange(const struct zoneChangeStruct*)), this, SLOT(handleZoneChange(const struct zoneChangeStruct*)) );
	connect( pack, SIGNAL(handleZoneEnd(const struct clientZoneInStruct*)), this, SLOT(handleZoneEnd(const struct clientZoneInStruct*)) );
	connect( pack, SIGNAL(handlePlayerItem(const struct itemPlayerStruct*)), this, SLOT(handlePlayerItem(const struct itemPlayerStruct*)) );
	connect( pack, SIGNAL(backfillPlayer(const struct playerProfileStruct*)), this, SLOT(backfillPlayer(const struct playerProfileStruct*)) );
}

void Player::reset()
{
	// zero our location and heading
	memset( &m_pos, 0, sizeof( m_pos ) );
	memset( &m_data.heading, 0, sizeof( m_data.heading ) );
	
	m_plusmana = 0;
	m_plusHP = 0;	
	m_currentExp = 0;

	m_nextLevelExp = this->calcExpNextLevel();
	m_currLevelExp = this->calcExpCurrLevel();
	
	m_playerData.level = 1;
	m_playerData.race = eWarrior;
	m_playerData.class_ = eHuman;
	
	m_data.spawnId = 1;
	m_data.maxHp = 1;
	m_data.curHp = 1;
	m_data.race = eWarrior;
	m_data.class_ = eHuman;
	m_data.gender = 0;
	m_data.level = 1;

	this->clearFlag( k_unnamed );
	this->setFlag( k_player );
	strcpy( m_data.name, "You" );

	this->setFlag( GameItem::k_uninited );

	this->__preCalcHeading();
	this->__fillConTable();
}

QColor calcPickConColor( int greenRange, int levelDif )
{

	// do the greens
	if ( greenRange > levelDif )
	{
		if ( ( greenRange - 10 ) >= levelDif )
			return QColor( 0, 95, 0 );
		else
		{
			int scale = greenRange - levelDif;
			int greenval = 255 - ( scale * 16 );
			return QColor( 0, greenval, 0 );
		}
	}
	else
	// ok, now we know its blue
	{
		if ( ( greenRange / 2 ) < levelDif )
		{
			// white scale
			int scalemax = (greenRange / 2 ) * -1;
			int scale = ( levelDif + 1 ) * -1;
			int colorval = 127 - ( scale * 127 / scalemax );
			return QColor( colorval, colorval, 255 );
			// 127, 127, 255 --- 0, 0, 255


		}
		else if ( ( greenRange / 2 ) > levelDif )
		{
			// green scale
			int scalemax = ( greenRange / 2 ) * -1;
			int scale = levelDif - ( greenRange + 1 );
			int greenval = 127 - ( scale * 127 / scalemax );
			int blueval = 127 + ( scale * 127 / scalemax );
			return QColor( 0, greenval, blueval );
			// 0, 127, 127 --- 0, 0, 255
		}
		else
			return QColor( 0, 0, 255 );
	}
}

void Player::__fillConTable()
{
// This is the info we have to work with
// Level Range		Green		Red
// 1-12				-4			+3
// 13-22			-6			+3
// 23-24			-7			+3
// 25-34			-8			+3
// 35-40			-10			+3
// 41-42			-11			+3
// 43-44			-12			+3
// 45-48			-13			+3
// 49-51			-14			+3
// 52-54			-15			+3
// 55-57			-16			+3
// 58-60			-17			+3

	UBYTE		myLevel = m_playerData.level;
	
	for ( int level = 1; level < MAX_LEVEL; level++ )
	{	
		// all levels have red as +3, yellow as +1 and +2
		// so lets get the those and even con out of the way first
		if  ( myLevel == level )
			m_conTable[ level ] = QColor( 255, 255, 255 );
		else if ( myLevel == ( level - 1 ) )
			m_conTable[ level ] = QColor( 255, 255, 0 );
		else if ( myLevel == ( level - 2 ) )
			m_conTable[ level ] = QColor( 255, 190, 0 );
		else if ( myLevel <= ( level - 3 ) )
		{
			// do the red shading
			if ( myLevel <= ( level - 13 ) )
				m_conTable[ level ] = QColor( 95, 0, 0 );
			else
			{
				int scale = ( level - myLevel ) - 3;
				int redval = 255 - scale * 16;
				m_conTable[ level ] = QColor( redval, 0, 0 );
			}
		}
		else {
			// 1 - 12
			int		greenRange = -4;

			if ( myLevel < 23 )	// 13 - 22
				greenRange = -6;
			else if ( myLevel < 25 )	// 23 - 24
				greenRange = -7;
			else if ( myLevel < 35 )	// 25 - 34
				greenRange = -8;
			else if ( myLevel < 41 )	// 35 - 40
				greenRange = -10;
			else if ( myLevel < 43 )	// 41 - 42
				greenRange = -11;
			else if ( myLevel < 45 )	// 43 - 44
				greenRange = -12;
			else if ( myLevel < 49)		// 45 - 48
				greenRange = -13;
			else if ( myLevel < 52 )	// 49 - 51
				greenRange = -14;
			else if ( myLevel < 58 )	// 52 - 57
				greenRange = -15;
			else						// 58 - 60
				greenRange = -16;

			m_conTable[ level ] = calcPickConColor( greenRange, level - myLevel );
		}
	}
}

QColor Player::pickConColor( const Spawn* otherSpawn ) const
{
	if ( this->isFlagSet( k_unnamed ) || otherSpawn->isFlagSet( k_unnamed ) )
		return Qt::black;

	return m_conTable[ otherSpawn->level() ];
}

	
void Player::handlePlayerProfile( const struct playerProfileStruct* playerData )
{
#ifdef DEBUG
	debug( "Player::handlePlayerProfile()" );
#endif

	m_playerData = *playerData;

	m_data.race = m_playerData.race;
	m_data.class_ = m_playerData.class_;
	m_data.gender = m_playerData.gender;
	m_data.level = m_playerData.level;

	this->__fillConTable();

	m_nextLevelExp = this->calcExpNextLevel();
	m_currLevelExp = this->calcExpCurrLevel();

	long		maxMana = calcMaxMana();

	// due to the delayed decode, we must reset maxplayer on zone and accumulate all totals
	m_maxStats.STR += m_playerData.stats.STR;
	m_maxStats.STA += m_playerData.stats.STA;
	m_maxStats.CHA += m_playerData.stats.CHA;
	m_maxStats.DEX += m_playerData.stats.DEX;
	m_maxStats.INT += m_playerData.stats.INT;
	m_maxStats.AGI += m_playerData.stats.AGI; 
	m_maxStats.WIS += m_playerData.stats.WIS;

	m_maxMana = maxMana + m_plusmana;

	m_currentExp = m_playerData.exp;

	QString		totalExp;
	QString		message;

	totalExp = Commanate( m_playerData.exp );
	message = "Exp: " + totalExp;

	emit statsChanged( &m_maxStats, &m_playerData.stats );
	
	emit manaChanged( m_playerData.mana, m_maxMana );  // need max mana

	emit expChangedString( message );
	emit expChangedInt( m_currentExp, m_nextLevelExp, 0 );

	for ( int a = 0; a < MAX_SKILL; a++ )
		emit addSkill( a, m_playerData.skills[ a ] );
}

void Player::backfillPlayer( const struct playerProfileStruct* player )
{
#ifdef DEBUG
//	debug( "Player::backfillPlayer()" );
#endif

	m_playerData = *player;

	m_data.race = m_playerData.race;
	m_data.class_ = m_playerData.class_;
	m_data.gender = m_playerData.gender;
	m_data.level = m_playerData.level;
	
	this->__fillConTable();

	m_maxStats.STR = m_playerData.stats.STR;
	m_maxStats.STA = m_playerData.stats.STA;
	m_maxStats.CHA = m_playerData.stats.CHA;
	m_maxStats.DEX = m_playerData.stats.DEX;
	m_maxStats.INT = m_playerData.stats.INT;
	m_maxStats.AGI = m_playerData.stats.AGI; 
	m_maxStats.WIS = m_playerData.stats.WIS;

	m_maxMana = calcMaxMana();
	
	m_plusmana = 0;
	m_plusHP = 0;
	
	m_currentExp = m_playerData.exp;
	m_nextLevelExp = this->calcExpNextLevel();
	m_currLevelExp = this->calcExpCurrLevel();

	QString		totalExp;
	QString		message;

	totalExp = Commanate( m_playerData.exp );
	message = "Exp: " + totalExp;

	emit statsChanged( &m_playerData.stats, &m_playerData.stats );

	emit manaChanged( m_playerData.mana, m_maxMana );
	
	emit expChangedString( message );
	emit expChangedInt( m_currentExp, m_currLevelExp, m_nextLevelExp );

	// merge in our new skills...
	for ( int a = 0; a < MAX_SKILL; a++ )
		emit addSkill( a, m_playerData.skills[ a ] );
}

void Player::dumpBaseStats()
{
	printf( "Your base STR: %i\n", m_playerData.stats.STR );
	printf( "Your base STA: %i\n", m_playerData.stats.STA );
	printf( "Your base CHA: %i\n", m_playerData.stats.CHA );
	printf( "Your base DEX: %i\n", m_playerData.stats.DEX );
	printf( "Your base INT: %i\n", m_playerData.stats.INT ); 
	printf( "Your base AGI: %i\n", m_playerData.stats.AGI );
	printf( "Your base WIS: %i\n", m_playerData.stats.WIS );
}

WORD Player::calcMaxMana()
{
	int		level = this->level();
	int		intelligence = m_maxStats.INT;
	int		wisdom = m_maxStats.WIS;
	
	switch ( this->class_() )
	{
		case eCleric:
		case ePaladin:
		case eDruid:
		case eShaman:
			return ( ( wisdom / 5 ) + 2 ) * level;

		case eBard:
		case eShadowKnight:
		case eNecromancer:
		case eWizard:
		case eMagician:
		case eEnchanter:
			return ( ( intelligence / 5 ) + 2 ) * level;
		case eWarrior:
		case eRanger:
		case eRogue:
		case eMonk:
		default: 
			return 0;
	}

}

unsigned long Player::calcExpToLevel( int level )
{
	typedef struct levelMultiplierTable
	{
		unsigned short		level;
		unsigned short		multiplier;
	} levelMultiplierTable;
	
	static const levelMultiplierTable table[] =
	{
		{ 30, 10 },
		{ 35, 11 },
		{ 40, 12 },
		{ 45, 13 },
		{ 51, 14 },
		{ 52, 15 },
		{ 53, 16 },
		{ 54, 17 },
		{ 55, 19 },
		{ 56, 21 },
		{ 57, 23 },
		{ 58, 25 },
		{ 59, 27 },
		{ (unsigned short)-1, 30 }
	};
			
	float		exp = level * level * level;
	for ( unsigned long i = 0; i < sizeof( table ) / sizeof( levelMultiplierTable ); i++ )
	{
		if ( level < table[ i ].level )
		{
			exp *= table[ i ].multiplier;
			break;
		}
	}
	
	exp *= this->classPenalty();
	exp *= this->racePenalty();
	
	return (unsigned long)(exp);
}

void Player::handleManaUsed( const struct manaDecrementStruct* mana )
{
#ifdef DEBUG
//	debug( "Player::handleManaChanged()" );
#endif

	m_playerData.mana = mana->newMana;
	
	emit manaChanged( m_playerData.mana, m_maxMana );  // need max mana
}

void Player::handleStamina( const struct staminaStruct* stam )
{
#ifdef DEBUG
//	debug( "Player::handleStamina()" );
#endif

	emit stamChanged( 100 - ( stam->fatigue ), 100, stam->food, 127, stam->water, 127 );
}

void Player::handlePlayerPos( const struct playerUpdateStruct* pupdate )
{
#ifdef DEBUG
//	printf( "Player::handlePlayerPos( %d )\n", pupdate->pos.spawnId );
#endif

	QString		tempStr;
	
#ifdef DEBUG
//	printf( "player pos: %d, %d\n", pupdate->yPos, pupdate->xPos );
//	printf( "player dir: %d, %d\n", pupdate->deltaY, pupdate->deltaX );
//	printf( "player head: %d\n", pupdate->pos.heading.heading );
#endif
	m_pos = pupdate->pos;
	m_data.heading = pupdate->pos.heading;

//	printf( "vel: %d %d %d\n",
//		(long)m_data.heading.deltaX,
//		(long)m_data.heading.deltaY,
//		(long)m_data.heading.deltaZ );
	this->__preCalcHeading();

	emit playerUpdate( m_pos );
	
	// following are primarily aimed at the compass object
	emit headingChanged( 360 - ( m_pos.heading.heading * 360 ) / 256 );

	emit xposChanged( this->xPos() );
	emit yposChanged( this->yPos() );
	emit zposChanged( this->zPos() );

	m_updateTime.restart();
}

void Player::handleSkillUp( const struct skillIncreaseStruct* skilli )
{
#ifdef DEBUG
//	debug( "Player::handleSkillUp()" );
#endif

	if ( m_playerData.skills[ skilli->skillId ] != skilli->value )
	{
		m_playerData.skills[ skilli->skillId ] = skilli->value;
		emit changeSkill( skilli->skillId, skilli->value );
	}
	//tempStr.sprintf( "Skill: %s has increased (%d)", skill_name( skilli->skillId ), skilli->value );
	//emit msgReceived( tempStr );
	//emit stsMessage( tempStr );
}

void Player::handleLevelUp( const struct levelUpStruct* levelup )
{
#ifdef DEBUG
//	debug( "Player::handleLevelUp()" );
#endif

	m_playerData.level = levelup->level;
	
	this->__fillConTable();
	
	long			divisor;

	QString			totalExp;
	QString			gainedExp;
	QString			needKills;
	QString			tempStr;

	unsigned long	prevExp = m_currentExp;
	
	divisor = ( levelup->exp > m_currentExp ) ? ( levelup->exp - m_currentExp ) : 1;

	m_currentExp = levelup->exp;
	m_currLevelExp = this->calcExpCurrLevel();
	m_nextLevelExp = this->calcExpNextLevel();

	totalExp = Commanate( m_currentExp );
	gainedExp = Commanate( (UDWORD)( m_currentExp - prevExp ) );
	needKills = Commanate( ( m_nextLevelExp - m_currentExp ) / divisor );

	tempStr = "Exp: " + totalExp + "(" + gainedExp + ")(" + needKills + ")";
	
	emit expChangedString( tempStr );
	emit expChangedInt( m_currentExp, m_currLevelExp, m_nextLevelExp );
	emit levelUp( m_playerData.level );
}

void Player::handleXPUpdate( const struct expUpdateStruct* exp )
{
#ifdef DEBUG
//	debug( "Player::handleXPUpdate()" );
#endif

	long		divisor;
	
	divisor = ( exp->exp > m_currentExp ) ? ( exp->exp - m_currentExp ) : 1;

	if ( m_currentExp > 0 )
	{
		QString		totalExp;
		QString		gainedExp;
		QString		needKills;
		QString		leftExp;
		QString		tempStr;
				
		totalExp = Commanate( exp->exp );
		gainedExp = Commanate( (UDWORD)( exp->exp - m_currentExp ) );
		needKills = Commanate( ( ( m_nextLevelExp - exp->exp ) / divisor ) + 1 );
		leftExp = Commanate( ( m_nextLevelExp - m_currLevelExp ) - ( exp->exp - m_currLevelExp ) );

		tempStr = "Exp: " + totalExp + "(" + gainedExp + ")" + "[" + needKills + "]";

		emit expChangedString( tempStr );

		tempStr = "Exp: " + totalExp + "(" + gainedExp + ")(" + needKills + ") left " + leftExp;

		//emit msgReceived( tempStr );

		//emit expGained( m_lastDeadSpawn.name, m_lastDeadSpawn.level, exp->exp - m_currentExp, currentZone );

		//emit stsMessage( tempStr );
	}

	unsigned long		added = exp->exp - m_currentExp;
	m_currentExp = exp->exp;	
	
	emit expChangedInt( exp->exp, m_nextLevelExp, added );
}

void Player::handleHPUpdate( const struct spawnHpUpdateStruct* hpupdate )
{
#ifdef DEBUG
//	debug( "Player::handleHPUpdate()" );
#endif
	
	if ( hpupdate->spawnId != this->id() )
		return;

	emit hpChanged( hpupdate->curHp, hpupdate->maxHp );
}

void Player::handleZoneChange( const struct zoneChangeStruct* /*newZone*/ )
{
#ifdef DEBUG
//	debug( "Player::handleZoneOut()" );
#endif

	this->reset();
}

void Player::handleZoneEnd( const struct clientZoneInStruct* /*newZone*/ )
{
	this->clearFlag( GameItem::k_uninited );
}

void Player::handlePlayerItem( const struct itemPlayerStruct* itemp )
{
#ifdef DEBUG
//	debug( "Player::handlePlayerItem()" );
#endif

	if ( itemp->item.item.equipSlot < 22 )
	{
		m_maxStats.STR += itemp->item.stats.prim.STR;
		m_maxStats.STA += itemp->item.stats.prim.STA;
		m_maxStats.CHA += itemp->item.stats.prim.CHA;
		m_maxStats.DEX += itemp->item.stats.prim.DEX;
		m_maxStats.INT += itemp->item.stats.prim.INT;
		m_maxStats.AGI += itemp->item.stats.prim.AGI; 
		m_maxStats.WIS += itemp->item.stats.prim.WIS;

		m_plusmana += itemp->item.stats.add.mana; 
		m_plusHP += itemp->item.stats.add.HP;
	
		emit statsChanged( &m_maxStats, &m_playerData.stats );
	
		m_maxMana = calcMaxMana() + m_plusmana;
		
		emit manaChanged( m_playerData.mana, m_maxMana );  // need max mana
	}

}


GroupMgr::GroupMgr( const char* name ):
	QObject( NULL, name )
{
}
 
void GroupMgr::handleGroupInfo( const struct groupMemberStruct* gmem )
{
	printf( "Member: %s - %s (%i)\n", gmem->yourname, gmem->membername, gmem->oper );

	QString				newName = gmem->membername;
	Spawn*				member;
	
	printf( "code: 1:%d 2:%d 3:%d\n", gmem->bgARC, gmem->oper, gmem->ARC2 );
	// is an empty "memberName" really the signal to clear the group?
	if ( newName.isEmpty() )
	{
		printf( "pkt: clearing out group.\n" );
		emit clrGroup();
		m_group.clear();
	}
	else
	{
		member = this->memberByName( newName );
		if ( member )
		{
				emit remGroup( member );
				m_group.removeRef( member );
		}
		else
		{
			Spawn* newMember = NULL; //gItemMgr->spawnByName( newName );
		
			if ( newMember )
				m_group.append( newMember );
			emit addGroup( newMember );
		}
	}

	printf( "Group Members are (%i):\n", m_group.count() );
	int count = 0;
	for ( member = m_group.first(); member != NULL; member++ )
	{
		count++;
		printf( "Mem#%i: %s(%i)\n", count, (const char*)member->name(), member->id() );
	}
}

int GroupMgr::groupSize()
{
	return m_group.count() + 1;
}

int GroupMgr::groupPercentBonus()
{
	switch ( this->groupSize() )
	{
		case 1:		return 100;
		case 2:		return 102;
		case 3:		return 106;
		case 4:		return 110;
		case 5:		return 114;
		case 6:		return 120;
		default:	return 100;
	}
}

unsigned long GroupMgr::totalLevels()
{
	unsigned long total = gPlayer->level();
	
	Spawn*			gm = m_group.first();
	
	while ( gm )
	{
		total += gm->level();
		gm++;
	}
	return total;
}

Spawn* GroupMgr::memberByID( UWORD id )
{
	Spawn*			gm = m_group.first();
	
	while ( gm )
	{
		if ( gm->id() == id )
			return gm;
		gm++;
	}
	return NULL;
}

Spawn* GroupMgr::memberByName( const QString& name )
{
	Spawn*			gm = m_group.first();
	
	while ( gm )
	{
		if ( gm->name() == name )
			return gm;
		gm++;
	}
	return NULL;
}
