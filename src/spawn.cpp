#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "spawn.h"
#include "player.h"
#include "util.h"
#include "preferences.h"
#include "itemmgr.h"

GameItem::GameItem()
{
	m_id = 0;
	m_flags = 0;
	this->setFlag( k_dirty );
}
	
GameItem::GameItem( UWORD id )
{
	m_id = id;
	m_flags = 0;

	this->setFlag( (GameItemFlag)( k_unnamed | k_dirty | k_posChanged | k_hpChanged | k_levelChanged ) );
}
	

unsigned long GameItem::calcDist( WORD x2, WORD y2, WORD /*z2*/ ) const
{
#ifdef DEBUG
//	debug( "GameItem::calcDist()" );
#endif
	long	xdist;
	long	ydist;
//	long	zdist;

	double		distance;
		
	xdist = ( this->xPos() - x2 );
	xdist *= xdist;
	ydist = ( this->yPos() - y2 );
	ydist *= ydist;
//	zdist = ( this->zPos() - z2 );
//	zdist *= zdist;
		

	distance = xdist + ydist;

	distance = sqrt( distance );
	return (unsigned long)distance;
}

QString GameItem::name() const
{
	return "";
}

Spawn::Spawn():
	GameItem()
{
	m_flags = k_none;

	memset( &m_data, 0, sizeof( m_data ) );

	m_spawnDate = QDate::currentDate();
	m_spawnTime = QTime::currentTime();
	m_spawnTime.start();
	m_updateTime = QTime::currentTime();
	m_updateTime.start();

	strcpy( m_data.name, "<unknown>" );
	m_name = "<unknown>";

	this->setFlag( (GameItemFlag)( k_unnamed | k_dirty | k_posChanged | k_hpChanged | k_levelChanged ) );
}

Spawn::Spawn( UWORD id, const SpawnHeading& heading ):
	GameItem( id )
{
	m_flags = k_none;

	memset( &m_data, 0, sizeof( m_data ) );

	m_spawnDate = QDate::currentDate();
	m_spawnTime = QTime::currentTime();
	m_spawnTime.start();
	m_updateTime = QTime::currentTime();
	m_updateTime.start();

	strcpy( m_data.name, "<unknown>" );
	m_name = "<unknown>";

	m_data.spawnId = id;
	m_data.heading = heading;
	this->__preCalcHeading();
	m_spawnInfo = "";

	this->setFlag( (GameItemFlag)( k_unnamed | k_dirty | k_posChanged | k_hpChanged | k_levelChanged ) );
}
	
Spawn::Spawn( const SpawnStruct& indata, long /*aggroRange*/ ):
	GameItem( indata.spawnId )
{
	m_data = indata;
	m_flags = k_none;
	
	m_spawnDate = QDate::currentDate();
	m_spawnTime = QTime::currentTime();
	m_spawnTime.start();
	m_updateTime = QTime::currentTime();
	m_updateTime.start();

	this->transformName();

	m_spawnInfo = this->processEquipment();
	this->setFlag( (GameItemFlag)( k_dirty | k_posChanged | k_hpChanged | k_levelChanged ) );
}

QString Spawn::__fixName()
{
	// fix the silly a_bat## names
	// replace all underscores with spaces and all numeric's
	//	with NULL (they appear at the end)

	QString		nameStr = "";

	char*		name = m_data.name;
	int			size = sizeof( m_data.name ) - 1;
	int			index = 0;

	while ( *name && size )
	{
		if ( ( *name >= '0' ) &&  ( *name <= '9' ) )
		{
			name++;
			size--;
			continue;
//			nameStr[ index ] = 0;
//			break;
		}
		else if ( *name == '_' )
			nameStr[ index++ ] = ' ';
		else
			nameStr[ index++ ] = *name;
		name++;
		size--;
	}

	QString		test;
	test = nameStr;








	test = test.right( 6 );

	if ( test == "corpse" )
	{
		this->setHP( -1 );
		this->__stop();

		this->setFlag( (GameItemFlag)( k_dirty | k_corpse ) );

		this->setFlag( k_corpseNameSet );
	}
	return nameStr;
}

void Spawn::transformName()
{
	QString		temp = this->__fixName();
	QString		orig = temp;
	QString		article;

	if ( temp.startsWith( "a " ) )
	{
		temp = temp.mid( 2 );
		article = "a";
	}
	else if ( temp.startsWith( "an " ) )
	{
		temp = temp.mid( 3 );
		article = "an";
	}
	else if ( temp.startsWith( "the " ) )
	{
		temp = temp.mid( 4 );
		article = "the";
	}
	
	Spawn* parent = NULL;
	if ( this->petOwnerID() != 0 )
	{
		parent = gItemMgr->spawnByID( this->petOwnerID() );
		if ( parent )
		{
			QString		parentName = parent->__fixName();
			parentName += "'s pet";
			temp = parentName;
		}
		else
			;
//			printf( "spawn is a pet, but I can't find it's owner\n" );
	}
	
	if ( this->isCorpse() )
	{
		// append the corpse stuff if the spawn is a corpse and it's not already there
		if ( !this->isFlagSet( k_corpseNameSet ) )
			temp += "'s corpse";
	}

	if ( parent && parent->isPC() )
	{
		temp += " (";
		temp += orig;
		temp += ")";
	}
	
	if ( !article.isEmpty() )
	{
		temp += ", ";
		temp += article;
	}
	
	m_name = temp;
}

QString Spawn::info() const
{
	QString string;
	
	string.sprintf( "%s\nLevel: %2d\tHP: %2d\t X/Y/Z: %5d/%5d/%5d\nRace: %s\t Class: %s\nEquipment: %s", 
		(const char*)this->name(),
		this->level(),
		this->curHp(),
		this->xPos(),
		this->yPos(),
		this->zPos(),
		(const char*)this->raceName(),
		(const char*)this->className_(),
		(const char*)this->equipString() );
	
	return string;
}

QString Spawn::processEquipment() const
{
	int					i;
	static QString		locs[] = { "H", "C", "A", "W", "G", "L", "F", "1", "2" };

	QString		tempStr = "";

	// check if it carries a lightsource
	if ( m_data.light )
	{
		tempStr = "Light:";
		tempStr += this->lightName();
	}

	// worn stuff
	for ( i = 0; i < 7; i++ )
	{
		if ( m_data.equipment[ i ] )
		{
			tempStr += locs[ i ];
			tempStr += ":";
			tempStr += this->materialName( m_data.equipment[ i ] );
			tempStr += " ";
		}
	}

	// worn weapons
	for ( i = 7; i < 9; i++ )
	{
		if ( m_data.equipment[ i ] )
		{
			tempStr += locs[ i ];
			tempStr += ":";
			tempStr += this->weaponName( m_data.equipment[ i ] );
			tempStr += " ";
		}
	}
	return tempStr;
}

QString Spawn::filterString() const
{
	QString		text;

	text.sprintf( "Name:%s:Level:%d:HP:%d:MaxHP:%d:Race:%s:Class:%s:NPC:%d:X:%i;Y:%i;Z:%i:",
		(const char*)this->name(),
		m_data.level,
		m_data.curHp,
		m_data.maxHp,
		(const char*)this->raceName(),

		(const char*)this->className_(),
		m_data.NPC,
		this->xPos(),
		this->yPos(),
		this->zPos() );

	return text;
}

void Spawn::__stop()
{
	m_data.heading.deltaX = 0;
	m_data.heading.deltaY = 0;
	m_data.heading.deltaZ = 0;
	this->__preCalcHeading();
}

void Spawn::backfill( const SpawnStruct& spawnData )
{
	SpawnStruct		oldspawn;
	
	// copy the data into the list
	oldspawn = m_data;
	m_data = spawnData;
	
	this->transformName();
	
	// preserve heading/location
	m_data.heading = oldspawn.heading;
	
	// preserve hitpoints
	m_data.maxHp = oldspawn.maxHp;
	m_data.curHp = oldspawn.curHp;
	
	// preseve equipment changes
	for ( int i = 0; i < 9; i++ )
		if ( oldspawn.equipment[ i ] )
			m_data.equipment[ i ] = oldspawn.equipment[ i ];
	
	// preserve level if the mob has leveled (not likely, but what the hell!)
	if ( oldspawn.level > m_data.level )
		m_data.level = oldspawn.level;
	
	// preserve NPC setting...  have they died since the spawn info?
	if ( this->isFlagSet( k_corpse ) )
	{
		// no hit points
		m_data.curHp = -1;
	
		// corpses don't move
		this->__stop();
	}
	
	m_spawnInfo = this->processEquipment();

	this->clearFlag( k_unnamed );
	this->setFlag( (GameItemFlag)( k_dirty | k_posChanged | k_hpChanged | k_levelChanged ) );
}

void Spawn::updatePosition( const SpawnUpdate& pos )
{
#ifdef DEBUG
//	debug( "Spawn::updatePosition" );
#endif

	m_data.heading = pos.heading;
	this->__preCalcHeading();
	// i have done some checking.  it appears that this feild 
	// (unknown0) contains the curent animation loop of the mob 
	// in question (walking/running/standing etc..)
	// 0 = standing.  when this is 0 the mob stops moving in the game
	// even though the velocity numbers arent 0.  this fix should reduce 
	// drift when a mob stops moving. (or turns)

	if ( pos.animLoop == 0 )
		this->__stop();
	
	m_updateTime.restart();
	
	this->setFlag( (GameItemFlag)( k_dirty | k_posChanged ) );
}

void Spawn::setCorpse()
{
	this->setHP( -1 );

	this->__stop();
	this->setFlag( (GameItemFlag)( k_dirty | k_corpse ) );
	this->transformName();
}

void Spawn::__preCalcHeading()
{

#define SPEED_FACTOR	0.0013
	
	m_preCalcHeading.x = m_data.heading.deltaX * SPEED_FACTOR;
	m_preCalcHeading.y = m_data.heading.deltaY * SPEED_FACTOR;
	m_preCalcHeading.z = m_data.heading.deltaZ * SPEED_FACTOR;
}
	
Location Spawn::approximatePosition( bool animate )
{
	Location		loc( m_data.heading.loc.x, m_data.heading.loc.y, m_data.heading.loc.z  );	

/*	loc.x = this->xPos();
	loc.y = this->yPos();
	loc.z = this->zPos();
*/
	if ( animate )
	{
		int		msec = m_updateTime.elapsed();
		
		loc.x += (WORD)( m_preCalcHeading.x * msec );
		loc.y += (WORD)( m_preCalcHeading.y * msec );
		loc.z += (WORD)( m_preCalcHeading.z * msec );
#ifdef DEBUG
//		printf( "msec: %d  x,y: %d %d  approx x,y: %d %d\n", msec, m_data.heading.xPos, m_data.heading.yPos, loc.x, loc.y );
#endif
	}

	return loc;
}

// return 1 if race1 race2 are on same pvp team
bool Spawn::isSameTeam( int otherRace ) const
{
	switch ( this->race() )
	{
		case eHuman: case eBarbarian: case eErudite:
		switch ( otherRace )
		{
			case eHuman: case eBarbarian: case eErudite:
				return true;
		}								
		case eWoodElf: case eHighElf: case eHalfElf:
		switch ( otherRace )
		{
			case eWoodElf: case eHighElf: case eHalfElf:
				return true;
		}
		case eDarkElf: case eTroll: case eOgre:
		switch ( otherRace )
		{
			case eDarkElf: case eTroll: case eOgre:
				return true;
		}
		case eDwarf: case eHalfling: case eGnome:
		switch ( otherRace )
		{
			case eDwarf: case eHalfling: case eGnome:
				return true;
		}
	}
	
	return false;
}
  
float Spawn::classPenalty() const
{
	switch ( this->class_() )
	{
		case eWarrior:		return 9;
		case eCleric:		return 10;
		case ePaladin:		return 14;
		case eRanger:		return 14;
		case eShadowKnight:	return 14;
		case eDruid: 		return 10;
		case eMonk:			return 12;
		case eBard:			return 14;
		case eRogue:		return 9.05;
		case eShaman:		return 10;
		case eNecromancer:	return 11;
		case eWizard:		return 11;
		case eMagician:		return 11;
		case eEnchanter:	return 11;

		default:			return 10;
	}
}

float Spawn::racePenalty() const
{
	switch ( this->race() )
	{
		case eHuman:   		return 10;
		case eBarbarian:	return 10.5;
		case eErudite:   	return 10;
		case eWoodElf:		return 10;
		case eHighElf:   	return 10;
		case eDarkElf:		return 10;
		case eHalfElf:		return 10;
		case eDwarf:		return 10;
		case eTroll:		return 12;
		case eOgre:			return 11.5;
		case eHalfling:		return 9.5;
		case eGnome:		return 10;
		case eIksar:		return 12;
		default :			return 10;
	}
}


Coins::Coins( const struct addCoinsStruct& incoins ):
	GameItem( incoins.dropId )
{
	m_data = incoins;
}

Coins::Coins( const struct deleteCoinsStruct& incoins ):
	GameItem( incoins.dropId )
{
}

QString Coins::info() const

{
	return this->name();
}

QString Coins::name() const
{
	QString		buff;
	
	buff.sprintf( "Coins: %c %ld", m_data.type[ 0 ], m_data.amount );

	
	return buff;
}

QString Coins::filterString() const
{
	QString		text;

	text.sprintf(
		"Name:Coins %c %ld:Race:Coins:Class:Thing:NPC:5:X:%.0f:Y:%.0f:Z:%.0f",
		m_data.type[ 0 ],
		m_data.amount,
		m_data.xPos,
		m_data.yPos,
		m_data.zPos );
	return text;
}



Drop::Drop( const struct addDropStruct& indrop ):
	GameItem( indrop.dropId )
{
	m_data = indrop;
	init();
}


Drop::Drop( const struct deleteDropStruct& indrop ):
	GameItem( indrop.dropId )
{
}

QString Drop::info() const
{
	return m_dropInfo;
}

QString Drop::name() const
{
	return m_dropInfo;
}

QString Drop::filterString() const
{
	QString		text;

	const char*	dropInfo = (const char*)m_dropInfo;
	
	text.sprintf(
		"Name:%s:Race:Drop:Class:Thing:NPC:6:X:%.0f:Y:%.0f:Z:%.0f",
		dropInfo,
		m_data.xPos,
		m_data.yPos,
		m_data.zPos );

	return text;
}


void Drop::init()
{
	QString			info;
	QString			out;
	
	out = "Drop: ";
	info = getItemNameFromDB( m_data.itemNr );

	if ( info.isEmpty() )
	{
		info = m_data.idFile;

		// printf("idfile: %s\n", sinfo);

		if ( info[ 0 ] == 'I' & info[ 1 ] == 'T' )
			info.remove( 0, 2 );

		// printf("trimmed: %s\n", sinfo);

		int thingnum = info.toInt();

		// printf("thingnum: %i\n", thingnum);

		if ( thingnum > 0 )
			out += Spawn::weaponName( (unsigned char)thingnum );
		else
			out += m_data.idFile;
	}
	// not found thing in DB 
	else
		out = "Drop: " + info;
	
	m_dropInfo = out;
}

QString Spawn::raceName() const
{
	static QString names[] = {
		"<unknown>",				// 0
		"Human",					// 1
		"Barbarian",				// 2
		"Erudite",					// 3
		"Wood Elf",					// 4
		"High Elf",					// 5
		"Dark Elf",					// 6
		"Half-Elf",					// 7
		"Dwarf",					// 8
		"Troll",					// 9

		"Ogre",						// 10
		"Halfling",
		"Gnome",
		"Aviak",
		"Highpass Citizen",
		"Brownie",
		"Centaur",
		"Golem",
		"Giant/Cyclops",
		"Trakanon",
		"Venril Sathir",			// 20
		"Evil Eye",
		"Beetle",
		"Kerra",
		"Fish",
		"Fairy",
		"Froglok",
		"Froglok Ghoul",
		"Fungusman",
		"Gargoyle",
		"Gasbag",					// 30
		"Gel Cube",
		"Ghost",
		"Ghoul",
		"Bat, Giant",
		"Eel, Giant",
		"Rat, Giant",
		"Snake, Giant",
		"Spider, Giant",
		"Gnoll",
		"Goblin",					// 40
		"Gorilla",
		"Wolf",
		"Bear",
		"Guard, Freeport",
		"Demi Lich",
		"Imp",
		"Griffin",
		"Kobold",
		"Dragon, Lava",
		"Lion",						// 50
		"Lizard Man",
		"Mimic",
		"Minotaur",
		"Orc",
		"Beggar, Human",
		"Pixie",
		"Drachnid",
		"Solusek Ro",
		"Bloodgills",
		"Skeleton",					// 60
		"Shark",
		"Tunare",
		"Tiger",
		"Treant",
		"Vampire",
		"Rallos Zek",
		"Were Wolf",
		"Tentacle",
		"Will O' Wisp",
		"Zombie",					// 70
		"Citizen, Qeynos",
		"Ship",
		"Launch",
		"Piranha",
		"Elemental",
		"Puma/Boat",
		"Citizen, Neriak",
		"Citizen, Erudin",
		"Bixie",
		"Hand",						// 80
		"Citizen, Rivervale",
		"Scarecrow",
		"Skunk",
		"Elemental, Snake",
		"Spectre",
		"Sphinx",
		"Armadillo",
		"Clockwork Gnome",
		"Drake",
		"Citizen, Halas",			// 90
		"Alligator",
		"Citizen, Grobb",
		"Citizen, Oggok",
		"Citizen, Kaladim",
		"Cazic-Thule",
		"Cockatrice",
		"Daisy Man",
		"Vampire, Elf",
		"Denizen",
		"Dervish",					// 100
		"Efreeti",
		"Froglok Tadpole",
		"Kedge",
		"Leech",
		"Swordfish",
		"Guard, Felwithe",
		"Mammoth",
		"Eye of Zomm",
		"Wasp",
		"Mermaid",					// 110
		"Harpie",
		"Guard, Faydark",
		"Drixie",
		"Ship, Ghost",
		"Clam",
		"Sea Horse",
		"Ghost, Dwarf",
		"Ghost, Erudite",
		"Sabertooth Cat",
		"Elemental, Wolf",			// 120
		"Gorgon",
		"Dragon Skeleton",
		"Innoruuk",
		"Unicorn",
		"Pegasus",
		"Djinn",
		"Invisible Man",
		"Iksar",
		"Scorpion",
		"Dodo Bird",				// 130
		"Sarnak",
		"Draglock",
		"Drolvarg",
		"Mosquito",
		"Rhino",
		"Xalgoz",
		"Goblin (Kunark)",
		"Yeti",
		"Citizen, Iksar",
		"Giant, Forest",			// 140
		"Burynai",
		"Goo",
		"Spectral Sarnak",
		"Burynai",
		"Goo",
		"Iksar Scorpion",
		"Erollisi",
		"Fish (Kunark)",
		"Bertoxxulous",
		"Bristlebane",				// 150
		"Fay Drake",
		"Sarnak Skeleton",
		"Ratman",
		"Wyvern",
		"Sarnak Skeleton",
		"Devourer",
		"Iksar Golem",
		"Wurm",
		"Devourer",
		"Raptor",					// 160
		"Iksar Skeleton",

		"Man Eating Plant",
		"Raptor",
		"",
		"Crawler",
		"",
		"Cactus",
		"Holgresh",
		"",
		"Snow Dervish",				// 170
		"Dire Wolf",
		"Manticore",
		"",
		"",
		"Suit of Armor",
		"Rabbit",
		"Walrus",
		"Geonid",
		"",
		"",							// 180
		"Faun",
		"",
		"Coldain",
		"",
		"",
		"",
		"",
		"Frost Giant",
		"Storm Giant",
		"",							// 190
		"Tundra Kodiak/Ulthork",	// 191
		"",							// 192
		"",							// 193
		"",							// 194
		"",							// 195
		"",							// 196
		"",							// 197
		"Sea Turtle?"				// 198
	};

	if ( m_data.race > 198 )

		return "<unknown>";
	else
		return names[ m_data.race ];
}

QString Spawn::className_() const
{
	int		classID = m_data.class_;

	static QString names[] = {
		"<unknown>",		// 0
		"Warrior",			// 1
		"Cleric",			// 2
		"Paladin",			// 3
		"Ranger",			// 4
		"ShadowKnight",		// 5
		"Druid",			// 6
		"Monk",				// 7
		"Bard",				// 8
		"Rogue",			// 9
		"Shaman",			// 10
		"Necromancer",
		"Wizard",
		"Magician",
		"Enchanter",
		"Beastlord",
		"Banker",
		"GM Warrior",
		"GM Cleric",
		"GM Paladin",
		"GM Ranger",		// 20
		"GM ShadowKnight",
		"GM Druid",
		"GM Monk",
		"GM Bard",
		"GM Rogue",
		"GM Shaman",
		"GM Necromancer",
		"GM Wizard",
		"GM Magician",
		"GM Enchanter",		// 30
		"GM Beastlord",
		"Shopkeeper"
	};

	if ( classID > 30 )
		return "<unknown>";
	else
		return names[ classID ];
}

QString Spawn::lightName() const
{
	int		lightID = m_data.light;

	typedef struct lightName
	{
		QString		shortName;
		QString		longName;
	} lightName;
	
	static lightName names[] =
	{
		{ "",		"" },						// 0
		{ "CDL",	"Candle" },					// 1
		{ "TR",		"Torch" },					// 2
		{ "TGS",	"Tiny Glowing Skull" },		// 3
		{ "SL",		"Small Lantern" },			// 4
		{ "SoM",	"Stein of Moggok" },		// 5
		{ "LL",		"Large Lantern" },			// 6
		{ "FL",		"Flameless Lantern" },		// 7
		{ "GoS",	"Globe of Stars" },			// 8
		{ "LG",		"Light Globe" },			// 9
		{ "LS",		"Lightstone" },				// 10
		{ "GLS",	"Greater Lightstone" },		// 11
		{ "FBE",	"Fire Beetle Eye" },		// 12
		{ "CL",		"Coldlight" }				// 13
	};
		
	if ( lightID >= 0 && lightID < 14 )
		return names[ lightID ].shortName;
	else
		return "";
}

QString Spawn::typeName() const
{
	int		npc = m_data.NPC;

	static QString names[] =
	{
		"Player",			// 0
		"Mob",				// 1
		"Player Corpse",	// 2
		"Mob Corpse",		// 3
		"4",
		"5",				
		"6",
		"7",
		"8",
		"9",
		"You"				// 10
	};
	
	if ( npc <= 10 )

		return names[ npc ];
	else
		return "?";
}		

QString Spawn::materialName( unsigned char material )
{
	QString mat = "";
	
	static QString names [] =
	{
		"None",					// 0x00
		"Leather",				// 0x01
		"Ringmail",				// 0x02
		"Plate",				// 0x03
		"Cured Silk",			// 0x04
		"Chitin",				// 0x05
		"",						// 0x06
		"Scale/BlackIron",		// 0x07
		"",						// 0x08
		"",						// 0x09
		"ElementRobe",			// 0x0A
		"BlightedRobe",			// 0x0B
		"Crystalline",			// 0x0C
		"OracleRobe",			// 0x0D
		"KedgeRobe",			// 0x0E
		"MetallicRobe",			// 0x0F
		"Robe",					// 0x10
		"VeliousLeather",		// 0x11
		"VeliousChain",			// 0x12
		"PogPlate",				// 0x13
		"Ulthork/Tizmak",		// 0x14
		"Ry`Gorr",				// 0x15
		"Kael/Guardian",		// 0x16
		"VeliousMonk"			// 0x17
	};

	if ( material <= 0x17 )
		mat = names[ material ];

	if ( !mat.length() )	
		mat.sprintf( "U%02x", material );
	
	return mat;
}


QString Spawn::weaponName( unsigned char weaponID )
{
	QString		weapon = "";

	static QString names[] = {
		"None",				//0x00
		"1HSword",			//0x01
		"2HSword",			//0x02
		"Axe",				//0x03
		"Bow",				//0x04
		"Dagger",			//0x05
		"Flute",			//0x06
		"Mace",				//0x07
		"2HStaff",			//0x08
		"DwarvenAxe",		//0x09
		"Arrow",			//0x0A
		"",					//0x0b
		"",					//0x0c
		"",					//0x0d
		"WarHammer",		//0x0e
		"Trumpet",			//0x0f
		"Spear",			//0x10
		"ShortSpear",		//0x11
		"Club",				//0x12
		"MorningStar",		//0x13
		"Rapier",			//0x14
		"Lute",				//0x15
		"",					//0x16
		"Halberd",			//0x17
		"2HHammer",			//0x18
		"2HBattleAxe",		//0x19
		"IcyBlade(P)",		//0x1A
		"Book",				//0x1B
		"DarkBook",			//0x1C
		"WrithingStaff",	//0x1D
		"",					//0x1e
		"SpikeClub",		//0x1F
		"Broom",			//0x20
		"HammFlat",			//0x21
		"Shortsword",		//0x22
		"Scepter",			//0x23
		"Torch",			//0x24
		"Cudgel",			//0x25
		"FishingPole",		//0x26
		"Scythe",			//0x27
		"Harvester",		//0x28
		"Scimitar",			//0x29
		"Falchion",			//0x2A
		"Pick",				//0x2B
		"",					//0x2c
		"CrystalStaff",		//0x2D
		"BoneWand",			//0x2E
		"Wand",				//0x2F
		"Lantern",			//0x30
		"Maul",				//0x31
		"Dirk",				//0x32
		"GoldScepter",		//0x33
		"Shovel",			//0x34
		"Flamberge",		//0x35
		"",					//0x36
		"",					//0x37
		"Stein",			//0x38
		"BroadSword",		//0x39
		"BastardSword",		//0x3a
		"MiningPick",		//0x3b
		"BattleAxe",		//0x3c
		"Whip",				//0x3d
		"FlameSword",		//0x3e
		"Generic",			//0x3f
		"Generic",			//0x40
		"Letter",			//0x41
		"Forge",			//0x42
		"Doll",				//0x43
		"Manastone",		//0x44
		"Oven",				//0x45
		"BrewBarrel",		//0x46
		"Claws",			//0x47
		"Stone",			//0x48
		"Kiln",				//0x49
		"PotteryWheel",		//0x4A
		"WoodenCrook",		//0x4B
		"",					//0x4c
		"",					//0x4d
		"",					//0x4e
		"",					//0x4f
		"ExecutionerAxe",	//0x50
		"Lamentation",		//0x51
		"Fer'Esh",			//0x52
		"Silver2HAxe",		//0x53
		"GreatCleaver",		//0x54
		"SerratedSword",	//0x55
		"Falchion",			//0x56
		"YkeshaSS",			//0x57
		"SwarmCaller",		//0x58
		"",					//0x59
		"SwordPassage",		//0x5a
		"Ulak",				//0x5b
		"Wurmslayer",		//0x5c
		"",					//0x5d
		"Duster/Sapper",	//0x5e
		"YkeshaTB",			//0x5f
		"",					//0x60
		"",					//0x61
		"Tooth",			//0x62
		"Bladecatcher",		//0x63
		"SheerBlade",		//0x64
		"Ketchata",			//0x65
		"",			//0x66
		"PartisanSpear",	//0x67
		"KunzarKu'juch",	//0x68
		"Shan'Tok",			//0x69
		"",					//0x6a
		"",					//0x6b
		"",					//0x6c
		"",					//0x6d
		"LegChopper",		//0x6e
		"",					//0x6f
		"",					//0x70
		"",					//0x71
		"",					//0x72
		"Mallet",			//0x73
		"",					//0x74
		"",					//0x75
		"Envy",				//0x76
		"LupineDigger",		//0x77
		"BlackTranslucentBlade",//0x78
		"WhiteTranslucentBlade",//0x79
		"Velium2HStaff",	//0x7a
		"",					//0x7b
		"",					//0x7c
		"SarnakSkullStaff",	//0x7d
		"WoodStaff",		//0x7e
		"",					//0x7f
		"Loom",				//0x80
		"",					//0x81
		"MorningStar",		//0x82
		"Defiance",			//0x83
		"Harpoon",			//0x84
		"Bowl",				//0x85
		"",					//0x86
		"",					//0x87
		"Claw",				//0x88
		"",					//0x89
		"",					//0x8a
		"",					//0x8b
		"Ragebringer",		//0x8c
		"WarEpic1hBlue",	//0x8d
		"WarEpic1hRed",		//0x8e
		"",					//0x8f
		"",					//0x90
		"",					//0x91
		"",					//0x92
		"",					//0x93
		"BardEpic",			//0x94
		"RangerEpic",		//0x95
		"DruidEpic",		//0x96
		"MageEpic",			//0x97
		"",					//0x98
		"NecroEpic",		//0x99
		"ShamanEpic",		//0x9a
		"WizardEpic",		//0x9b
		"ClericEpic",		//0x9c
		"EnchanterEpic",	//0x9d
		"",					//0x9e
		"MonkEpic",			//0x9f
		"PaladinEpic",		//0xa0
		"",					//0xa1
		"",					//0xa2
		"RedJeweledSword",	//0xa3
		"BlueJeweledSword",	//0xa4
		"",					//0xa5
		"",					//0xa6
		"JeweledDirk",		//0xa7
		"VeliumSword",		//0xa8
		"",					//0xa9
		"Velium2hAxe",		//0xaa
		"VeliumAxe",		//0xab
		"VeliumSpear",		//0xac
		"",					//0xad
		"",					//0xae
		"",					//0xaf
		"",					//0xb0
		"",					//0xb1
		"",					//0xb2
		"",					//0xb3
		"",					//0xb4
		"",					//0xb5
		"",					//0xb6
		"",					//0xb7
		"",					//0xb8
		"",					//0xb9
		"VeliumGreatStaff",	//0xba
		"VeliumSpear",		//0xbb
		"VeliumLongSword",	//0xbc
		"VeliumMorningStar",//0xbd
		"VeliumTwoHandedSword",//0xbe
		"VeliumShortSword",	//0xbf
		"VeliumScimitar",	//0xc0
		"VeliumWarhammer",	//0xc1
		"VeliumDagger",		//0xc2
		"VeliumRapier",		//0xc3
		"",					//0xc4
		"",					//0xc5
		"BFG",				//0xc6
		"Crossbow",			//0xc7
		"QeynosShield",		//0xc8
		"WoodenShield",		//0xc9
		"KiteShield",		//0xca
		"SmRoundShield",	//0xcb
		"DarkwoodShield",	//0xcc
		"BoneShield",		//0xcd
		"DarkShield",		//0xce
		"MarrsPromise",		//0xcf
		"",					//0xd0
		"ShellShield1",		//0xD1
		"ShimmerOrb",		//0xd2
		"UnicornShield",	//0xd3
		"NautilusShield",	//0xd4
		"MistmooreShield",	//0xD5
		"ChitinShield",		//0xD6
		"",					//0xd7
		"IksTargShield",	//0xD8
		"FrogskinShield",	//0xd9
		"ScaleShield",		//0xda
		"ShellShield2",		//0xDb
		"",					//0xdc
		"SarnakShield",		//0xDd
		"",					//0xde
		"OrnateRunedShield",//0xDf
		"",					//0xe0
		"GreySheild"		//0xe1
//		"Chunk",			//0x190
//		"Mushroom",			//0x192
//		"Bark",				//0x193
	};

	if ( weaponID <= 0xe1 )
		weapon = names[ weaponID ];

	if ( !weapon.length() )
		weapon.sprintf( "U%02x", weaponID );

	return weapon;
}

QString Spawn::languageName( long langID )
{
	QString lang = "";

	static QString names[] =
	{
		"Common Tongue",	// 0
		"Barbarian",		// 1
		"Erudian",			// 2
		"Elvish",			// 3
		"Teir'Dal",			// 4
		"Dwarvish",			// 5
		"Troll",			// 6
		"Ogre",				// 7
		"Gnomish",			// 8
		"Halfling",			// 9
		"Thieves Cant",		// 10
		"Old Erudian",
		"Elder Elvish",
		"Froglok",
		"Goblin",
		"Gnoll",
		"Giant Tongue",
		"Kobold",
		"Lizardman",
		"Orcish",
		"Faerie",			// 20
		"Dragon",			// 21
		"Elder Dragon",		// 22
		"Dark Speech"		// 23
	};

	if ( langID <= 23 )
		lang = names[ langID ];

	if ( !lang.length() )
		lang.sprintf( "%ld", langID );
	
	return lang;
}
