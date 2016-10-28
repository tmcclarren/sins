//	statlist.cpp
//		SINS Distributed under GPL

#include <qlayout.h>
#include "statlist.h"
#include "player.h"
#include "main.h"
#include "preferences.h"
#include "util.h"
//#include <stdio.h>

StatRecord::StatRecord( const QString& name, unsigned short value, unsigned short max )
{
	m_name = name;
	m_value = value;
	m_max = max;
}
	
const FieldMap<StatRecord> StatListView::m_map[] = {
	{ "Stat", StatListView::Stat },
	{ "Value", StatListView::Value },
	{ "Max", StatListView::Max },
	{ "Percent", StatListView::Percent },
	{ NULL, NULL }
};

StatListView::StatListView( QWidget* parent, const char* name ):
	BaseListView( "Statistics", parent, name ),
	ListViewWrapper<StatRecord>( m_map, this, 19 )
{
	m_guessMaxMana = 0;

	connect( gPlayer, SIGNAL( stamChanged(int,int,int,int,int,int) ),		this, SLOT( stamChanged(int,int,int,int,int,int) ) );
	connect( gPlayer, SIGNAL( manaChanged(WORD,WORD) ),						this, SLOT( manaChanged(WORD,WORD) ) );
	connect( gPlayer, SIGNAL( hpChanged(int,int) ),							this, SLOT( hpChanged(int,int) ) );
}

void StatListView::Percent( StatRecord* stat, QString& tmp )
{
	tmp = "?? %";
	
	if ( stat->m_max != 0 )
	{
		tmp.setNum( stat->m_value * 100 / stat->m_max );
		tmp += "%";
	}
}

void StatListView::statChanged( int /*statNum*/, int /*val*/, int /*max*/ )
{
}

void StatListView::hpChanged( int /*val*/, int /*max*/ )
{
}

void StatListView::manaChanged( WORD /*val*/, WORD /*max*/ )
{
}

void StatListView::stamChanged( int /*Sval*/, int /*Smax*/, int /*Fval*/, int /*Fmax*/, int /*Wval*/, int /*Wmax*/ ) 
{
}

void StatListView::resetMaxMana()
{
	m_guessMaxMana = 0;
}

void StatListView::addStats()
{
	QStringList statNames;
	
	statNames
		<< "Hit Points"
		<< "Mana"
		<< "Stamina"
		<< "Food"
		<< "Water"
		<< "STRength"
		<< "STAmina"
		<< "CHaRisma"
		<< "DEXterity"
		<< "INTelligence"
		<< "AGIlity"
		<< "WISdom"
		<< "Magic Resist"
		<< "Fire Resist"
		<< "Cold Resist"
		<< "Disease Resist"
		<< "Poison Resist"
		<< "Armor Class";
		
	for ( int i = 0; i < LIST_MAXLIST; i++ )
	{
		StatRecord*		rec = new StatRecord( statNames[ i ] );
		this->addItem( i, rec );
	}
}
	


StatWindow::StatWindow( const char* name = NULL ):
	BaseWindow( "Statistics", NULL, name )
{
	QHBoxLayout* layout = new QHBoxLayout( this );
	layout->setAutoAdd( true );

	m_statList = new StatListView( this, "stat-list" );
	m_statList->restore();
	m_statList->addStats();
}
	
StatWindow::~StatWindow()
{
	if ( m_statList )
		m_statList->saveToPreferences();
}


