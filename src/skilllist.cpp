//	skilllist.cpp
//		SINS Distributed under GPL

#include <qlayout.h>
#include "skilllist.h"
#include "player.h"
#include "main.h"

SkillRecord::SkillRecord( unsigned short skillID, unsigned short value )
{
	m_skillID = skillID;
	m_value = value;
}

const FieldMap<SkillRecord> SkillListView::m_map[] = {
	{ "Skill", SkillListView::Skill },
	{ "Value", SkillListView::Value },
	{ NULL, NULL }
};

SkillListView::SkillListView( QWidget* parent, const char* name ):
	BaseListView( "Skills", parent, name ),
	ListViewWrapper<SkillRecord>( m_map, this, 257 )
{
	connect( gPlayer, 	SIGNAL( addSkill(int,int) ),				this, SLOT( addSkill(int,int) ) );
	connect( gPlayer,	SIGNAL( changeSkill(int,int) ),				this, SLOT( changeSkill(int,int) ) );
}

void SkillListView::Value( SkillRecord* skill, QString& tmp )
{
	if ( skill->m_value == 254 )
		tmp = "N/A";
	else
		tmp.sprintf( "%3d", skill->m_value );
}

// called to add a skill to the skills list
void SkillListView::addSkill( int skillId, int value )
{
	QString		tempStr;

	// check if this is a valid skill
	if ( value == 255 )
		return;

	if ( this->getItem( skillId ) )
		return;
		
	SkillRecord*	newRec = new SkillRecord( skillId, value );

	this->addItem( skillId, newRec );
}

void SkillListView::changeSkill( int skillId, int value )
{
	QString		tempStr;

	SkillRecord*	rec = this->getItem( skillId );
	if ( rec )
	{
		rec->m_value = value;
		this->updateItem( skillId );
	}
}

QString SkillListView::skillName( int skillId )
{
	static QString num;
	
	static QString names[] = {
		"1H Blunt",					// 0
		"1H Slashing",				// 1
		"2H Blunt",					// 2
		"2H Slashing",				// 3
		"Abjuration",				// 4
		"Alteration",				// 5
		"Apply Poison",				// 6
		"Archery",					// 7
		"Backstab",					// 8
		"Bind Wound",				// 9
		"Bash",						// 10
		"Block",
		"Brass Instruments",
		"Channeling",
		"Conjuration",
		"Defense",
		"Disarm",
		"Disarm Traps",
		"Divination",
		"Dodge",
		"Double Attack",			// 20
		"Dragon Punch",
		"Duel Wield",
		"Eagle Strike",
		"Evocation",
		"Feign Death",
		"Flying Kick",
		"Forage",
		"Hand To Hand",
		"Hide",
		"Kick",						// 30
		"Meditate",
		"Mend",
		"Offense",
		"Parry",
		"Pick Lock",
		"Piercing",
		"Riposte",
		"Round Kick",
		"Safe Fall",
		"Sense Heading",			// 40
		"Sing",
		"Sneak",
		"Specialize Abjure",
		"Specialize Alteration",
		"Specialize Conjuration",
		"Specialize Divinatation",
		"Specialize Evocation",
		"Pick Pockets",
		"Stringed Instruments",
		"Swimming",					// 50
		"Throwing",
		"Tiger Claw",
		"Tracking",
		"Wind Instruments",
		"Fishing",
		"Make Poison",
		"Tinkering",
		"Research",
		"Alchemy",
		"Baking",					// 60
		"Tailoring",
		"Sense Traps",
		"Blacksmithing",
		"Fletching",
		"Brewing",
		"Alcohol Tolerance",
		"Begging",
		"Jewelry Making",
		"Pottery",
		"Percussion Instruments",	// 70
		"Intimidation",
		"Berserking",
		"Taunt"						// 73
	};

	if ( skillId > 73 )
	{
		num = QString::number( skillId );
		return num;
	}	
	else
		return names[ skillId ];
	
}

SkillWindow::SkillWindow( const char* name = NULL ):
	BaseWindow( "Skills", NULL, name )
{
	QHBoxLayout* layout = new QHBoxLayout( this );
	layout->setAutoAdd( true );
	m_skillList = new SkillListView( this, "skill-list" );
	m_skillList->restore();
}

SkillWindow::~SkillWindow()
{
	if ( m_skillList )
		m_skillList->saveToPreferences();
}

