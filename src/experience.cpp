//	experience.cpp
//		SINS Distributed under GPL

#include "experience.h"
#include "interface.h"
#include "util.h"
#include "main.h"
#include "player.h"
#include "spawn.h"
#include "itemmgr.h"

#include <qgrid.h>
#include <qtimer.h>
#include <qhbox.h>
#include <qvgroupbox.h>
#include <qmessagebox.h>
#include <stdio.h>

ExperienceRecord::ExperienceRecord( const QString& mob_name, int mob_level, long xp_gained, const QString& zone_name ):
	m_mob_name( mob_name ),
	m_mob_level( mob_level ),
	m_xp_gained( xp_gained ),
	m_zone_name( zone_name )
{
	m_time = QDateTime::currentDateTime();
}

long ExperienceRecord::getExpValue() const
{
	// TODO: This isn't right for all mob levels!
	//     But casey's working on it!
	return m_mob_level * m_mob_level * 75;
}

long ExperienceRecord::getExpValueZEM() const
{
	return m_mob_level * m_mob_level * gItemMgr->getZEM();
}
 
long ExperienceRecord::getExpValuep() const
{
	int baseExp = getExpValueZEM();
	float p_penalty = gPlayer->classPenalty();

	return (int)( (float)baseExp * ( p_penalty / (float)10 ) );
}

long ExperienceRecord::getExpValueg() const
{
	int pExp = getExpValuep();
	int myLevel = gPlayer->level();
	
	// groupSize is in addition to yourself 5==full group
	int gBonus = gGroupMgr->groupPercentBonus();
	
	// calculate group aggregate level
	unsigned long totalLevels = gGroupMgr->totalLevels();
	
	printf("My Level: %d  Group Tot: %ld  Bonus: %d\n", myLevel, totalLevels, gBonus);

	return (int)( (float)pExp * ( (float)gBonus / (float)100 ) * ( (float)myLevel / (float)totalLevels ) );
}

ExperienceWindow::ExperienceWindow():
	BaseWindow( "Experience" )
{
	m_ratio = 1;
	m_timeframe = 0;
	m_calcZEM = false;
	m_ZEMviewtype = 0;
	m_lastMobKilledName = "";
	m_lastMobKilledLevel = 0;
	
	m_view_menu = new QPopupMenu( this );

	m_view_menu->insertItem( "&All Mobs", this, SLOT(viewAll()) );
	m_view_menu->insertItem( "Previous &15 Minutes", this, SLOT(view15Minutes()) );
	m_view_menu->insertItem( "Previous &30 Minutes", this, SLOT(view30Minutes()) );
	m_view_menu->insertItem( "Previous &60 Minutes", this, SLOT(view60Minutes()) );
	m_view_menu->setItemChecked( m_view_menu->idAt( 0 ), true );

	m_view_menu->insertSeparator();

	m_exp_rate_menu = new QPopupMenu( this );
	m_exp_rate_menu->insertItem( "per &minute", this, SLOT(viewRatePerMinute()) );
	m_exp_rate_menu->insertItem( "per &hour", this, SLOT(viewRatePerHour()) );
	m_exp_rate_menu->setItemChecked( m_exp_rate_menu->idAt( 0 ), true );

	m_view_menu->insertItem( "Experience &Rate", m_exp_rate_menu );
	m_view_menu->insertSeparator();
	m_view_menu->insertItem( "Clear", this, SLOT(viewClear()) );
	m_view_menu->insertSeparator();
	m_view_menu->insertItem( "Calculate ZEM on next kill", this, SLOT(calcZEMNextKill()) );

	m_ZEM_menu = new QPopupMenu( this );
	m_ZEM_menu->insertItem( "Calculated Value", this, SLOT(viewZEMcalculated()) );
	m_ZEM_menu->insertItem( "Raw Value", this, SLOT(viewZEMraw()) );
	m_ZEM_menu->insertItem( "Percent Bonus", this, SLOT(viewZEMpercent()) );
	m_ZEM_menu->setItemChecked( m_ZEM_menu->idAt( 0 ), true );

	m_view_menu->insertItem( "ZEM View Options", m_ZEM_menu );
	
	m_menu_bar = new QMenuBar( this );
	m_menu_bar->insertItem( "&View", m_view_menu );
	QVBoxLayout*		layout = new QVBoxLayout( this );
	layout->addSpacing( m_menu_bar->height() + 5 );
	QGroupBox* listGBox = new QVGroupBox( "Experience Log", this );
	layout->addWidget( listGBox );

	m_exp_listview = new QListView( listGBox );
	m_exp_listview->addColumn( "Time" );
	m_exp_listview->addColumn( "Mob" );
	m_exp_listview->addColumn( "Level" );
	m_exp_listview->addColumn( "Base Exp" );
	m_exp_listview->addColumn( "ZEM total" );
	m_exp_listview->addColumn( "Class total" );
	m_exp_listview->addColumn( "Group total" );
	m_exp_listview->addColumn( "Experience Gained" );

	m_exp_listview->setMinimumSize( m_exp_listview->sizeHint().width(), 200 );

	QGroupBox* statsGBox = new QVGroupBox( "Statistics", this );
	layout->addWidget( statsGBox );

	QGrid* statsGrid = new QGrid( 4, statsGBox );

	new QLabel( "Total Experience Received:", statsGrid );
	m_total_received = new QLabel( statsGrid );

	new QLabel( "Play Time:", statsGrid );
	m_play_time = new QLabel( statsGrid );

	new QLabel( "Total Mobs Killed:", statsGrid );
	m_mob_count = new QLabel( statsGrid );

	m_experience_rate_label = new QLabel( "Experience Rate (per minute):", statsGrid );
	m_experience_rate = new QLabel( statsGrid );

	new QLabel( "Average Experience per Mob:", statsGrid );
	m_average_per_mob = new QLabel( statsGrid );

	new QLabel( "Estimated Kills To Level:", statsGrid );
	m_kills_to_level = new QLabel( statsGrid );

	new QLabel( "Experience Remaining:", statsGrid );
	m_experience_remaining = new QLabel( statsGrid );

	new QLabel( "Estimated Time To Level:", statsGrid );
	m_time_to_level = new QLabel( statsGrid );

	//this->setCaption( "Experience" );
	// ewww, why can't we just get it from QGrid? :(
	((QGridLayout*)statsGrid->layout())->setColStretch( 1, 1 );
	((QGridLayout*)statsGrid->layout())->setColStretch( 3, 1 );
	statsGrid->layout()->setSpacing( 5 );

	updateAverage( );

	connect( gPacket, SIGNAL(handleCorpse(const struct spawnKilledStruct*)), this, SLOT(handleCorpse(const struct spawnKilledStruct*)));
	connect( gPlayer, SIGNAL(expChangedInt(unsigned long, unsigned long, long)), this, SLOT(expChangedInt(unsigned long, unsigned long, long)));

	// timer to update the average xp
	QTimer* timer = new QTimer( this );
	connect( timer, SIGNAL(timeout()), SLOT(updateAverage()) );

	// calculate every 15 seconds
	timer->start( 15 * 1000 );
}

void ExperienceWindow::handleCorpse( const struct spawnKilledStruct* deadSpawn )
{
	const Spawn*		sp = gItemMgr->spawnByID( deadSpawn->spawnId );
	if ( sp )
	{
		m_lastMobKilledName = sp->name();
		m_lastMobKilledLevel = sp->level();
	}
}

void ExperienceWindow::expChangedInt( unsigned long /*curExp*/, unsigned long /*levelExp*/, long addExp )
{
	QString		zone = gItemMgr->shortZoneName();

	if ( m_lastMobKilledName.length() && ( m_lastMobKilledName != "<unknown>" ) )	
		this->addExpRecord( m_lastMobKilledName, m_lastMobKilledLevel, addExp, zone );
}
	

void ExperienceWindow::addExpRecord( const QString& mob_name, int mob_level, long xp_gained, const QString& zone_name )
{
	ExperienceRecord*		xp = new ExperienceRecord( mob_name, mob_level, xp_gained, zone_name );

#ifdef DEBUG
	resize( sizeHint() );
	qDebug("ExperienceWindow::addExpRecord() '%s', lvl %d, exp %ld", mob_name.ascii(), mob_level, xp_gained );
#endif

	m_exp_list.append( xp );

	// convert everything to string representations for the list view
	QString			s_mob_name = mob_name;
	QString			s_mob_level;
	QString			s_xp_gained;
	QString			s_xp_value;
	QString			s_xp_valueZEM;
	QString			s_xp_valuep;
	QString			s_xp_valueg;
	QString			s_time;
	
	s_mob_level.setNum( mob_level );
	s_xp_gained.setNum( xp_gained );

	if ( m_calcZEM )
	{
		calculateZEM( xp_gained, mob_level );
		m_calcZEM = false;
		m_view_menu->setItemChecked( m_view_menu->idAt( 9 ), false );
	}   

	s_xp_value.setNum( xp->getExpValue() );

	switch ( m_ZEMviewtype )
	{
		case 1:
			s_xp_valueZEM.setNum( gItemMgr->getZEM());
		break;
		case 2:
			s_xp_valueZEM.setNum( ( (float)( gItemMgr->getZEM() - 75 ) / (float)75 ) * 100 );
		break;
		default:
			s_xp_valueZEM.setNum( xp->getExpValueZEM() );
		break;
	}
	s_xp_valuep.setNum( xp->getExpValuep() );
	s_xp_valueg.setNum( xp->getExpValueg() );
	
	s_time = xp->getTime().toString();

	QListViewItem*		new_exp_entry = new QListViewItem( m_exp_listview,
												s_time,
												s_mob_name,
												s_mob_level,
												s_xp_value,
												s_xp_valueZEM,
												s_xp_valuep,
												s_xp_valueg,
												s_xp_gained );

	m_exp_listview->insertItem( new_exp_entry );
	m_exp_listview->setSelected( new_exp_entry, true );
	m_exp_listview->ensureItemVisible( new_exp_entry );

	// and update the average display
	updateAverage();

}

void ExperienceWindow::updateAverage()
{
	static bool force = true;

	if ( !force && !isVisible() )
		return;

	force = false;

	// calculate the earliest time to accept
	QDateTime	time_cutoff;
	double		total_exp = 0;

	if ( m_timeframe )
		time_cutoff = QDateTime::currentDateTime().addSecs( m_timeframe * -60 );

	// start at the end, add up the xp & mob count until we hit the
	// beginning of list or the time cutoff
	QListIterator<ExperienceRecord> it( m_exp_list );

	ExperienceRecord*	rec;
	int					mob_count = 0;
	QDateTime			first_kill_time = QDateTime::currentDateTime();

	it.toLast();
	rec = *it;
	while ( rec && rec->getTime() >= time_cutoff )
	{
		total_exp += rec->getExpGained();
		mob_count++;

		if ( rec->getTime() < first_kill_time )
			first_kill_time = rec->getTime();

		--it;
		rec = *it;
	}

	// calculate the number of minutes that have passed
	float minutes = (float)first_kill_time.secsTo( QDateTime::currentDateTime() ) / (float)60;

	if ( minutes < 1 )
		minutes = 0;

	// calculate and display the averages
	QString			s_avg_exp;
	QString			s_play_time;
	QString			s_total_exp;
	QString			s_mob_count;
	QString			s_mob_avg_exp;
	QString			s_exp_remaining;
	QString			s_kills_to_level;
	QString			s_time_to_level;
	float			avg_exp;
	long			exp_remaining;
	int				time_to_level;

	if ( !m_timeframe )
	{
		avg_exp = ( minutes ? total_exp / minutes : 0 );
		s_avg_exp = Commanate( (UDWORD)( avg_exp * m_ratio ) );
		s_play_time.setNum( minutes );
		s_play_time += " min";
	}
	else
	{
		avg_exp = total_exp / m_timeframe;
		s_avg_exp = Commanate( (UDWORD)( avg_exp * m_ratio ) );
		s_play_time.setNum( m_timeframe );
		s_play_time += " min";
	}

	if ( m_ratio == 1 )
		m_experience_rate_label->setText( "Experience Rate (per minute):" );
	else if ( m_ratio == 60 )
		m_experience_rate_label->setText( "Experience Rate (per hour):" );

	s_total_exp = Commanate( (UDWORD)total_exp );
	s_mob_count.setNum( (UDWORD)mob_count );

	if (mob_count)
		s_mob_avg_exp = Commanate( (UDWORD)( total_exp / mob_count ) );
	else
		s_mob_avg_exp = "0";

	exp_remaining = gPlayer->maxExp() - gPlayer->currentExp();
	if ( exp_remaining < 0 )
		exp_remaining = 0;

	if ( exp_remaining > 0 )
		s_exp_remaining = Commanate( exp_remaining );
	else
		s_exp_remaining = "unknown";

	if ( mob_count )
		s_kills_to_level.setNum( exp_remaining / ( total_exp / mob_count ) );
	else
		s_kills_to_level = "unknown";

	time_to_level = (int)( exp_remaining / avg_exp );

	if ( avg_exp )
	{
		if ( time_to_level > 120 )
			s_time_to_level = QString( "%1 hours, %2 minutes" ).arg( (int)(time_to_level / 60) ).arg( time_to_level % 60 );
		else if ( time_to_level > 60 )
			s_time_to_level = QString( "1 hour, %2 minutes" ).arg( time_to_level % 60 );
		else
			s_time_to_level = QString( "%1 minutes" ).arg( (int)time_to_level );
	}
	else
		s_time_to_level = "unknown";

	m_total_received->setText( s_total_exp );
	m_mob_count->setText( s_mob_count );
	m_average_per_mob->setText( s_mob_avg_exp );
	m_experience_remaining->setText( s_exp_remaining );

	m_play_time->setText( s_play_time );
	m_experience_rate->setText( s_avg_exp );
	m_kills_to_level->setText( s_kills_to_level );
	m_time_to_level->setText( s_time_to_level );
}

void ExperienceWindow::resizeEvent( QResizeEvent* /*e*/ )
{
}

void ExperienceWindow::viewAll()
{
	m_timeframe = 0;
	updateAverage();
	m_view_menu->setItemChecked( m_view_menu->idAt( 0 ), true );
	m_view_menu->setItemChecked( m_view_menu->idAt( 1 ), false );
	m_view_menu->setItemChecked( m_view_menu->idAt( 2 ), false );
	m_view_menu->setItemChecked( m_view_menu->idAt( 3 ), false );
}

void ExperienceWindow::view15Minutes()
{
	m_timeframe = 15;
	updateAverage();
	m_view_menu->setItemChecked( m_view_menu->idAt( 0 ), false );
	m_view_menu->setItemChecked( m_view_menu->idAt( 1 ), true );
	m_view_menu->setItemChecked( m_view_menu->idAt( 2 ), false );
	m_view_menu->setItemChecked( m_view_menu->idAt( 3 ), false );
}

void ExperienceWindow::view30Minutes()
{
	m_timeframe = 30;
	updateAverage();
	m_view_menu->setItemChecked( m_view_menu->idAt( 0 ), false );
	m_view_menu->setItemChecked( m_view_menu->idAt( 1 ), false );
	m_view_menu->setItemChecked( m_view_menu->idAt( 2 ), true );
	m_view_menu->setItemChecked( m_view_menu->idAt( 3 ), false );
}

void ExperienceWindow::view60Minutes()
{
	m_timeframe = 60;
	updateAverage();
	m_view_menu->setItemChecked( m_view_menu->idAt( 0 ), false );
	m_view_menu->setItemChecked( m_view_menu->idAt( 1 ), false );
	m_view_menu->setItemChecked( m_view_menu->idAt( 2 ), false );
	m_view_menu->setItemChecked( m_view_menu->idAt( 3 ), true );
}

void ExperienceWindow::viewRatePerHour()
{
	m_ratio = 60;
	updateAverage();
	m_exp_rate_menu->setItemChecked( m_exp_rate_menu->idAt( 0 ), false );
	m_exp_rate_menu->setItemChecked( m_exp_rate_menu->idAt( 1 ), true );
}

void ExperienceWindow::viewRatePerMinute()
{
	m_ratio = 1;
	updateAverage();
	m_exp_rate_menu->setItemChecked( m_exp_rate_menu->idAt( 0 ), true );
	m_exp_rate_menu->setItemChecked( m_exp_rate_menu->idAt( 1 ), false );
}

void ExperienceWindow::calcZEMNextKill()
{
	m_calcZEM = true;
	m_view_menu->setItemChecked( m_view_menu->idAt( 9 ), true );
}

void ExperienceWindow::viewZEMcalculated()
{
	m_ZEMviewtype = 0;
	m_ZEM_menu->setItemChecked( m_ZEM_menu->idAt( 0 ), true );
	m_ZEM_menu->setItemChecked( m_ZEM_menu->idAt( 1 ), false );
	m_ZEM_menu->setItemChecked( m_ZEM_menu->idAt( 2 ), false );
}

void ExperienceWindow::viewZEMraw()
{
	m_ZEMviewtype = 1;
	m_ZEM_menu->setItemChecked( m_ZEM_menu->idAt( 0 ), false );
	m_ZEM_menu->setItemChecked( m_ZEM_menu->idAt( 1 ), true );
	m_ZEM_menu->setItemChecked( m_ZEM_menu->idAt( 2 ), false );
}

void ExperienceWindow::viewZEMpercent()
{
	m_ZEMviewtype = 2;
	m_ZEM_menu->setItemChecked( m_ZEM_menu->idAt( 0 ), false );
	m_ZEM_menu->setItemChecked( m_ZEM_menu->idAt( 1 ), false );
	m_ZEM_menu->setItemChecked( m_ZEM_menu->idAt( 2 ), true );
}

void ExperienceWindow::viewClear()
{

	switch ( QMessageBox::information( this, "ShowEQ",
		"This function will clear all data listed in the experience "
		"log.  Do you want to continue?",
		"&OK", "&Cancel", QString::null, 1, 1 ) )
	{
		case 0:
			m_exp_list.clear();
			m_exp_listview->clear();
		break;

		default:
		break;
	}
}

void ExperienceWindow::calculateZEM( long xp_gained, int mob_level )
{
	int myLevel = gPlayer->level();
	unsigned long totalLevels = gGroupMgr->totalLevels();
	float penalty = gPlayer->classPenalty();
	int gBonus = gGroupMgr->groupPercentBonus();
	
	float temp = ( (float)totalLevels / (float)myLevel );
	temp *= ( (float)100 / (float)gBonus );
	temp /= ( mob_level * mob_level );
	temp *= 10;
	temp /= penalty;
	
	int ZEM = (int) ( (float)xp_gained * temp );
	printf( "xpgained: %ld\ngroup_ag: %ld\nmyLevel: %d\ngbonus: %d\nmob_level: %d\npenalty: %f\n", xp_gained, totalLevels, myLevel, gBonus, mob_level, penalty );
	printf( "ZEM = %d\n", ZEM );
	gItemMgr->setZEM( ZEM );
}
