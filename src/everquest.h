// everquest.h
//		SINS Distributed under GPL

// Structures used in the network layer of Everquest

#ifndef EVERQUEST_H
#define EVERQUEST_H

#define MAX_SKILL	74

// *********************************
// compiler override to ensure byte aligned structures
// THE FOLLOWING IS IMPORANT -- if you move it, you'll
// break packet decoding... these structs are in packed
// form such that bytes coming off the wire are sucked out
// of buffers in precisely this form
// *********************************
#pragma pack(1)

// definitions to get datatype widths correct
// -- a 'char' definition in here should really only be
// used to denote something that is a human readable string

#define WORD		short int
#define UWORD		unsigned short int
#define DWORD		long
#define UDWORD		unsigned long
#define UBYTE		unsigned char
#define BYTE		char

struct location
{
	WORD			y;
	WORD			x;
	WORD			z;
};
typedef struct location LocationStruct;

// generic structures used in specific structures below
struct primStatStruct
{
	BYTE			STR;
	BYTE			STA;
	BYTE			WIS;
	BYTE			DEX;
	BYTE			AGI;
	BYTE			CHA;
	BYTE			INT;
};
typedef struct primStatStruct PrimStatStruct;

struct addStatStruct
{
	BYTE			MR;              // magic resist
	BYTE			FR;              // fire resist
	BYTE			CR;              // cold resist
	BYTE			DR;              // disease resist
	BYTE			PR;              // poison resist
	BYTE			HP;              // hit points
	BYTE			mana;            // mana
	BYTE			AC;              // armor class
};
typedef struct addStatStruct AddStatStruct;

struct statStruct
{
	PrimStatStruct	prim;
	AddStatStruct	add;
};
typedef struct statStruct StatStruct;

struct itemBaseStruct
{
	char			name[ 35 ];      // name of item
	char			lore[ 60 ];      // lore text, same as name if no lore
	char			idfile[ 6 ];     // don't know what this is used for, eg: IT63
	WORD			flag;            // 0x5f31 normal item, 0x3633 player made
	BYTE			unknown0[ 22 ];  // placeholder
	UBYTE			weight;          // weight of item
	BYTE			nosave;          // nosave flag 1=normal, 0=nosave, -1=spell?
	BYTE			nodrop;          // nodrop flag 1=normal, 0=nodrop, -1=??
	UBYTE			size;            // sdize of item
	BYTE			unknown1;        // placeholder
	UWORD			itemNr;          // unique item type number
	UWORD			iconNr;          // icon nr
	WORD			equipSlot;       // current equip slot
	UDWORD			slots_;          // slots where this item goes
	DWORD			cost;            // item cost in copper
};
typedef struct itemBaseStruct ItemBaseStruct;

// item structure used for items in shops, on players, etc
struct itemStruct
{
	ItemBaseStruct	item;
	
	BYTE			unknown2[ 20 ];    // placeholder
	
	StatStruct		stats;
	
	BYTE			unknown3[ 2 ];   // placeholder
	UBYTE			light;           // light effect of this item
	BYTE			delay;           // weapon delay
	BYTE			damage;          // weapon damage
	BYTE			unknown4;        // placeholder
	UBYTE			range;           // range of weapon
	UBYTE			skill;           // skill of this weapon
	BYTE			magic;           // magic flag, 0(0000=unique?, 1(0001)=magic, 12(1100)=meat?, 14(1110)=normal?, 15(1111)=???
	BYTE			level0;          // casting level
	UBYTE			material;        // material?
	BYTE			unknown5[2];     // placeholder
	UDWORD			color;           // amounts of RGB in original color
	BYTE			unknown6[2];     // placeholder
	UWORD			spellId0;        // spell ID of special effect
	UWORD			classes;         // classes that can use this item
	BYTE			unknown7[2];     // placeholder
	UWORD			races;           // races that can use this item
	BYTE			unknown8;        // placeholder
	BYTE			numSlots;        // number of slots?-ATB
	BYTE			unknown9;
	UBYTE			level;           // casting level
	BYTE			number;          // number of items in stack
	BYTE			unknown10;       // placeholder
	UWORD			spellId;         // spell ID of special effect
	BYTE			unknown11[ 26 ]; // placeholder
};
typedef struct itemStruct ItemStruct;

struct spawnHeadingStruct
{
	UBYTE			heading;
	BYTE			deltaHeading;
	LocationStruct	loc;
	DWORD			deltaY:10,       // velocity Y
				 		spacer1:1,
						deltaZ:10,       // velocity Z
						spacer2:1,
						deltaX:10;       // velocity X
};
typedef struct spawnHeadingStruct SpawnHeading;

// spawn generic struct
struct spawnStruct
{
	UBYTE			unknown0[ 49 ];	// placeholder

	SpawnHeading	heading;

	UBYTE			unknown1[ 1 ];	// placeholder
	UWORD			spawnId;		// id of new spawn
	UBYTE			unknown2[ 2 ];	// placeholder
	UWORD			petOwnerId;		// id of pet owner (0 if not a pet)
	WORD			maxHp;			// maximum hp's of Spawn
	WORD			curHp;			// current hp's of Spawn
	UBYTE			race;			// race
	UBYTE			NPC;			// NPC flag, 0 = player, 1 = mob, 2 = corpse, 3 = mob corpse, 10 = me
	UBYTE			class_;			// class
	UBYTE			gender;			// gender flag, 0 = male, 1 = female, 2 = other
	UBYTE			level;			// level of spawn (might be one byte)
	UBYTE			unknown3[ 4 ];	// placeholder
	UBYTE			light;			// light emitting
	UBYTE			unknown4[ 9 ];	// placeholder
	UBYTE			equipment[ 9 ];	// equipment worn
	char			name[ 30 ];		// name of spawn (len is 30 or less)
	char			lastname[ 20 ];	// last name of player
	UBYTE			unknown5[ 2 ];	// placeholder
	UBYTE			deity;			
	UBYTE			unknown6[ 15 ];
};
typedef struct spawnStruct SpawnStruct;

struct spawnUpdateStruct
{
	UWORD			spawnId;		// id of spawn to update
	BYTE			animLoop;
	SpawnHeading	heading;
};
typedef struct spawnUpdateStruct SpawnUpdate;

struct spellBuff
{
	BYTE			unknown1;
	UBYTE			level;
	BYTE			unknown2[ 2 ];
	WORD			spell;
	DWORD			duration;
};
typedef struct spellBuff SpellBuff;

struct opCode
{
	UBYTE			code;
	UBYTE			version;
	
	// kinda silly -- this is required for us to be able to stuff them in a QValueList
	bool operator== ( const struct opCode t ) const
	{
		return ( code == t.code && version == t.version );
	}
};
typedef struct opCode OpCode;

// specific structures defining opcodes

// item owned by the player
struct itemPlayerStruct
{
	OpCode			code;			// 0x64 (was 0x60), 0x21
	ItemStruct		item;			// refer to itemStruct for members
};

// item received by the player 
struct itemReceivedStruct
{
	OpCode			code;			// 0x31, 0x21
	ItemStruct		item;			// refer to itemStruct for members
};

// item in a shop
struct itemShopStruct
{
	OpCode			code;			// 0x0c (was 0x14), 0x21
	BYTE			unknown0[ 4 ];	// shopkeeper id must be in here
	BYTE			itemType;		// 0 - item, 1 - container, 2 - book
	ItemStruct		item;			// refer to itemStruct for members
};

// client changes target struct
struct clientTargetStruct
{
	OpCode			code;			// 0x62, 0x21
	UWORD			newTarget;
	UWORD			unknown0;
};

// channel message received or sent
struct channelMessageStruct
{
	OpCode			code;			// 0x41, 0x21
	UWORD			unknown0[ 16 ];
	char			sender[ 23 ];	// senders name (len might be wrong)
	UBYTE			unknown1[ 9 ];
	UBYTE			language;
	BYTE			unknown2[ 1 ];
	UBYTE			chanNum;
	BYTE			unknown3[ 3 ];
	char			message[ 0 ];	// variable length message
};

// new spawn
struct addSpawnStruct
{
	OpCode			code;			// 0x46, 0x21
	DWORD			unknown1;
	SpawnStruct		spawn;
};

// delete spawn
struct deleteSpawnStruct
{
	OpCode			code;			// 0xd8 (was 0x37), 0x21
	UWORD			spawnId;		// spawn id to delete
};


// book belonging to player
struct bookPlayerStruct
{
	OpCode			code;			// 0x65 (was 0x61), 0x21
	
	ItemBaseStruct	item;
	
	BYTE			unknown3[ 23 ];	// placeholder
	char			file[ 15 ];		// filename of text on server
	BYTE			unknown4[ 12 ];	// placeholder
};

// container belonging to player
struct containerPlayerStruct
{
	OpCode			code;			// 0x66 (was 0x62), 0x21
	
	ItemBaseStruct	item;

	BYTE			unknown3[ 20 ];	// placeholder

	StatStruct		stats;

	BYTE			unknown4[ 2 ];	// placeholder
	UBYTE			light;			// light effect of this item
	BYTE			delay;			// weapon delay
	BYTE			damage;			// weapon damage
	BYTE			unknown5;		// placeholder
	UBYTE			range;			// range of weapon
	UBYTE			skill;			// skill of this weapon
	BYTE			magic;			// magic flag, 0(0000=unique?, 1(0001)=magic, 12(1100)=meat?, 14(1110)=normal?, 15(1111)=???
	BYTE			level0;			// casting level
	UBYTE			material;		// material?
	BYTE			unknown6[ 2 ];	// placeholder
	UDWORD			color;			// amounts of RGB in original color 
	BYTE			unknown7[ 2 ];	// placeholder
	UWORD			spellId0;		// spell id of special effect
	UWORD			classes;		// classes that can use this item (this is not exactly)
	UWORD			races;			// races that can use this item(like items)
	BYTE			unknown8;		// placeholder
	BYTE			numSlots;		// number of slots in bag
	BYTE			unknown9;		// placeholder
	UBYTE			level;			// casting level
	BYTE			number;			// number of items in stack
	BYTE			unknown10;		// placeholder
	UWORD			spellId;		// spell id of special effect
};

// server system message
struct systemMessageStruct
{
	OpCode			code;			// 0xa4, 0x21
	char			message[ 0 ];	// variable length message
};

// spawn HP update
struct spawnHpUpdateStruct
{
	OpCode			code;			// 0x75, 0x20
	UWORD			spawnId;		// id of spawn to update
	WORD			unknown0;		// placeholder
	WORD			curHp;			// current hp of spawn
	WORD			unknown1;		// placeholder
	WORD			maxHp;			// maximum hp of spawn
	WORD			unknown2;		// placeholder
};

// spawn position update
struct spawnPosUpdateStruct
{
	OpCode			code;			// 0xa1 (was 0x85), 0x20
	DWORD			numUpdates;		// number of SpawnUpdate's
	SpawnUpdate		updates[ 0 ];	// variable number of updates
};

// player update
struct playerUpdateStruct
{
	OpCode			code;			// 0xd1, 0x20
	SpawnUpdate		pos;
};

// player profile
struct playerProfileStruct
{
	OpCode			code;			// 0x3d (was 0x35), 0x21
	BYTE			unknown0[ 4 ];	// placeholder								02
	char			name[ 30 ];		// name of player							06
	char			lastName[ 20 ];	// last name of player						36
	WORD			unknown1;		// placeholder								56
	UBYTE			race;			// player race								58
	BYTE			unknown2;		// placeholder								59
	UBYTE			class_;			// player class								60
	UBYTE			gender;			// player gender							61
	UBYTE			level;			// level of player (might be one byte)		62
	BYTE			unknown3[ 3 ];	// placeholder								63
	UDWORD			exp;			// current Experience						66
	WORD			unknown4;		//											70
	WORD			mana;			// mana										72
	BYTE			unknown5[ 51 ];	//											74
	PrimStatStruct	stats;
	BYTE			unknown6[ 518 ];
	SpellBuff		buffs[ 15 ];
	BYTE			unknown7[ 1080 ];
	WORD			spellbook[ 256 ];
	WORD			memSpells[ 8 ];
	BYTE			unknown8[ 54 ];
	UDWORD			platinum;
	UDWORD			gold;
	UDWORD			silver;
	UDWORD			copper;
	BYTE			unknown9[ 32 ];
	UBYTE			skills[ MAX_SKILL ];	// list of skills
	BYTE			unknown10[ 154 ];
	char			guild[ 144 ];
	BYTE			unknown11[ 1376 ];
	char			groupMembers[ 5 ][ 48 ];
	BYTE			unknown12[ 72 ];
};

// zone spawns
struct zoneSpawnsStruct
{
	OpCode			code;				// 0x47, 0x21
	DWORD			numSpawns;
	SpawnStruct		spawn[ 0 ];			// variable number of spawns
};

// zone is-about-to-change
struct zoneChangeStruct
{
	OpCode			code;				// 0xa3, 0x20
	char			charName[ 32 ];		// character name
	char			zoneName[ 15 ];		// short zone name
	BYTE			unknown0049[ 21 ];
};


// client zone out 
struct clientZoneOutStruct
{
	OpCode			code;				// 0x2a, 0x20
	DWORD			unknown0;
	char			name[ 20 ];			// player firstname
	DWORD			unknown1;
	DWORD			unknown2;
	DWORD			unknown3;
};

// client zone in
struct clientZoneInStruct
{
	OpCode			code;				// 0x5b (was 0xcb), 0x20
	char			charName[ 30 ];		// character name
	char			shortName[ 15 ];	// short zone name
	BYTE			unknown1[ 5 ];
	char			longName[ 180 ];
	char			unknown2[ 142 ];
};

// door
struct newDoorStruct
{
	OpCode			code;				// 0x94, 0x20
	char			name[ 8 ];			// filename of door?
	BYTE			unknown[ 40 ];		// placeholder
};

// special message
struct spMesgStruct
{
	OpCode			code;				// 0x80, 0x21
	DWORD			msgType;			// type of message
	char			message[ 0 ];		// message, followed by four 0 bytes?
};

// reading a book
struct bookTextStruct
{
	OpCode			code;				// 0x59, 0x20
	char			text[ 0 ];			// text of item reading
};

// emote text
struct emoteTextStruct
{
	OpCode			code;				// 0x15, 0x20
	char			text[ 0 ];			// text of item reading
};


// level up
struct levelUpStruct
{
	OpCode			code;				// 0x86, 0x21
	UDWORD			level;				// new level
	UDWORD			levelOld;			// old level
	UDWORD			exp;				// current Experience
};

// exp update
struct expUpdateStruct
{
	OpCode			code;				// 0x87, 0x21
	UDWORD			exp;				// current experience value
};

// time of day
struct timeOfDayStruct
{
	OpCode			code;				// 0xf2, 0x20
	BYTE			hour;				// 1-24
	BYTE			minute;				// 0-59
	BYTE			day;				// 1-28
	BYTE			month;				// 1-12
	UWORD			year;				// year
};

// skill increase
struct skillIncreaseStruct
{
	OpCode			code;				// 0x92, 0x20
	WORD			skillId;			// id of skill
	BYTE			unknown0[ 2 ];		// placeholder
	WORD			value;				// new value of skill
	BYTE			unknown1[ 2 ];		// new value of skill
};

// memorize slot operations, mem, forget, etc
struct memorizeSlotStruct
{
	OpCode			code;				// 0x82, 0x21
	BYTE			slot;				// memorization slot (0-7)
	BYTE			unknown0[ 3 ];		// placeholder
	UWORD			spellId;			// id of spell (offset of spell in spdat.eff)
	BYTE			unknown1[ 6 ];		// placeholder 00,00,01,00,00,00
};

struct castStruct
{
	OpCode			code;				// 0x7e
	WORD			unknown1;			// placeholder
	WORD			spellId;			// spell ID
	WORD			unknown2;			// placeholder
	WORD			unknown3;			// placeholder
	UDWORD			targetId;			// the current selected target
	BYTE			unknown4[ 4 ];		// placeholder
};

// begin casting
struct beginCastStruct
{
	OpCode			code;				// 0x7d, 0xb2
	UWORD			spawnId;			// id of who is casting
	WORD			unknown0;			// placeholder
	UWORD			spellId;			// id of spell
	WORD			param1;				// paramater 1?
	WORD			param2;				// paramater 2?
	WORD			param3;				// parameter 3?
};

// interrupted Casting 
struct interruptCastStruct
{
	OpCode			code;				// 0xd3, 0x21
	UWORD			spawnId;			// id of who is casting
	WORD			unknown0;			// placeholder
	char			message[ 0 ];
};

// kill something
struct spawnKilledStruct
{
	OpCode			code;				// 0x4a, 0x20
	UWORD			spawnId;			// id of spawn that died
	WORD			unknown0;	
	UWORD			killerId;
	BYTE			unknown1[ 10 ];
};

// when somebody changes what they're wearing or give a pet a weapon (model changes)
struct equipChangeStruct
{
	OpCode			code;				// 0x92, 0x20
	UWORD			spawnId;
	BYTE			unknown0[ 2 ];
	UBYTE			wearSlotId;
	UBYTE			newItemId;
	BYTE			unknown1[ 6 ];		// first few bytes react to clothing changes
};

struct castOnStruct
{
	OpCode			code;				// 0x46, 0x20
	UWORD			targetId;
	BYTE			unknown0[ 2 ];
	UWORD			sourceId;
	BYTE			unknown1[ 26 ];		// might be some spell info?
};

struct manaDecrementStruct
{
	OpCode			code;				// 0x7f, 0x21
	WORD			newMana;			// amount of mana left after cast
	WORD			spellID; 
};

struct summonedItemStruct
{
	OpCode			code;				// 0x78, 0x21
	ItemStruct		item;
};

struct tradeItemStruct
{
	OpCode			code;				// 0xdf, 0x20
	BYTE			unknown[ 6 ];
	BYTE			itemtype;
	ItemStruct		item;
};

struct staminaStruct
{
	OpCode			code;				// 0x57, 0x21
	WORD			food;				// (low numbers are more hungry 127-0)
	WORD			water;				// (low numbers are more thirsty 127-0)
	WORD			fatigue;			// (high numbers are more fatigued 0-100)
};

struct addCoinsStruct
{
	OpCode			code;				// 0x07, 0x20
	UBYTE			unknown0[ 24 ];		// no clue
	UWORD			dropId;
	UBYTE			unknown1[ 22 ];
	UDWORD			amount;
	UBYTE			unknown2[ 4 ];
	float			yPos;
	float			xPos;
	float			zPos;
	UBYTE			unknown3[ 12 ];		// blank space
	BYTE			type[ 15 ];			// silver gold whatever
	UBYTE			unknown4[ 17 ];
};

struct deleteCoinsStruct
{
	OpCode			code;				// 0x08, 0x20
	UWORD			dropId;				// guess
	BYTE			unknown0[ 6 ];
};

struct addDropStruct
{
	OpCode			code;				// 0x35, 0x20
	UBYTE			unknown0[ 8 ];
	UWORD			itemNr; 
	UBYTE			unknown1[ 2 ];
	UWORD			dropId;
	UBYTE			unknown2[ 26 ];
	float			yPos;
	float			xPos;
	float			zPos;
	UBYTE			unknown3[ 4 ];
	char			idFile[ 16 ];		// maybe be 4?
	UBYTE			unknown4[ 168 ];
};

struct deleteDropStruct
{
	OpCode			code;				// 0x36, 0x20
	UWORD			dropId;
	BYTE			unknown0[ 6 ];
};

struct attack1Struct
{
	OpCode			code;				// 0xf5, 0x20
	UWORD			spawnId;
	WORD			unknown0;
	WORD			unknown1;
	WORD			unknown2;
	WORD			unknown3;
	WORD			unknown4;
};

struct attack2Struct
{
	OpCode			code;				// 0x9f, 0x20
	UWORD			spawnId;
	WORD			unknown0;
	WORD			unknown1;
	WORD			unknown2;
	WORD			unknown3;
	WORD			unknown4;
};

struct considerStruct
{ 
	OpCode			code;				// 0x37, 0x21
	UWORD			playerid; 
	BYTE			unknown0[ 2 ];
	UWORD			targetid; 
	BYTE			unknown1[ 2 ]; 
	DWORD			faction;
	DWORD			level;
	DWORD			curHp; 
	DWORD			maxHp;
};

struct newGuildStruct
{
	OpCode			code;				// 0x7b, 0x21
	BYTE			unknown0[ 8 ];
	char			guildname[ 56 ]; 
};

struct moneyUpdateStruct
{
	OpCode			code;				// 0x3d, 0x21
	UWORD			unknown0;
	BYTE			unknown1[ 2 ];
	UBYTE			cointype;
	BYTE			unknown2[ 3 ];
	UDWORD			amount; 
};

struct bindWoundStruct
{
	OpCode			code;				// 0x83, 0x21
	UWORD			playerid;
	BYTE			unknown0[ 2 ];
	DWORD			hpmaybe;
};

struct inspectedStruct
{
	OpCode			code;				// 0xbf, 0x20
	UWORD			inspectorId;
	UBYTE			unknown0[ 2 ];
	UWORD			inspectedId;		// should be you
	UBYTE			unknown1[ 2 ];
};

struct inspectingStruct
{
	OpCode			code;				// 0xb6, 0x20
	BYTE			unknown0[ 40 ];
	char			itemNames[ 21 ][ 32 ];	// 21 names, len 32
	UWORD			icons[ 21 ];  
	BYTE			unknown1[ 2 ];
	char			mytext[ 200 ];
	BYTE			unknown2[ 88 ];
};

struct randomStruct
{
	OpCode			code;				// 0xe7, 0x21
	UDWORD			bottom;				// bottom bound
	UDWORD			top;				// top bound
};

struct groupMemberStruct
{
	OpCode			code;				// 0x26, 0x40
	char			yourname[ 32 ];
	char			membername[ 32 ];
	BYTE			unknown0[ 35 ];
	BYTE			bgARC;				// add = 2, remove = 3, clear = 0- bad guess-ATB
	BYTE			unknown1[ 83 ];
	BYTE			oper;				// add = 4, remove = 3
	BYTE			ARC2;				// ?? -  add = c8, remove 1 = c5, clear = 01
	BYTE			unknown2[ 131 ];
};

struct actionStruct
{
	OpCode			code;				// 0x58, 0x20
	UWORD			target;
	BYTE			unknown0[ 2 ];
	UWORD			source;
	BYTE			unknown1[ 2 ];
	BYTE			type;				// casts, falls, bashes, etc...?
	BYTE			unknown2;
	WORD			spell;
	DWORD			damage;
	BYTE			unknown3[ 6 ];
	DWORD			range;
	BYTE			unknown4[ 2 ];
};

// *********************************
// compiler override to ensure byte aligned structures
// THE FOLLOWING IS IMPORANT -- reset to make other
// files compile normally
// *********************************
#pragma pack()

// db spawn struct (adds zone spawn was in)
struct dbSpawnStruct
{
	SpawnStruct		spawn;
	char			zoneName[ 40 ];
};

// pet spawn struct (puts pet and owner in one struct)
struct petStruct 
{
	SpawnStruct		owner;
	SpawnStruct		pet;
};


#endif

//. .7...6....,X....D4.M.\.....P.v..>..W....
//123456789012345678901234567890123456789012
//000000000111111111122222222223333333333444
