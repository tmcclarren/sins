// experience.h
//		SINS Distributed under GPL

#ifndef EXPERIENCE_H
#define EXPERIENCE_H

#include "basewindow.h"
#include <qobject.h>
#include <qlist.h>
#include <qlistview.h>
#include <qcombobox.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qmenubar.h>
#include <qdatetime.h>

#include "packet.h"

class ExperienceRecord
{
public:

	ExperienceRecord( const QString& mob_name, int mob_level, long xp_gained, const QString& zone_name );

	const QString &getMobName() const { return m_mob_name; }
	int getMobLevel() const { return m_mob_level; }
	long getExpGained() const { return m_xp_gained; }
	
	long getExpValue() const;			// BASE calculated from spawn level
	long getExpValueZEM() const;		// calculated from spawn level and ZEM
	long getExpValuep() const;			// calculated from spawn level and ZEM + penalty
	long getExpValueg() const;			// calculated from spawn level and all + group

	const QDateTime& getTime()  const { return m_time; }
	const QString& getZoneName() const { return m_zone_name; }

protected:
	QString				m_mob_name;
	int				m_mob_level;
	long				m_xp_gained;
	QString				m_zone_name;
	QDateTime			m_time;
};

class ExperienceWindow: public BaseWindow
{
Q_OBJECT
public:
	ExperienceWindow();

public slots:
	void updateAverage( );
	void viewRatePerHour();
	void viewRatePerMinute();
	void viewAll();
	void view15Minutes();
	void view30Minutes();
	void view60Minutes();
	void viewClear();
	void calcZEMNextKill();
	void viewZEMraw();
	void viewZEMpercent();
	void viewZEMcalculated();

	void handleCorpse( const struct spawnKilledStruct* deadspawn );
	void expChangedInt( unsigned long, unsigned long, long );
	
protected:
	void addExpRecord( const QString& mob_name, int mob_level, long xp_gained, const QString& zone_name );
	void resizeEvent( QResizeEvent * );
	void calculateZEM( long xp_gained, int mob_level );

	QListView*			m_exp_listview;

	QLabel*				m_experience_rate_label;
	QLabel*				m_total_received;
	QLabel*			 	m_mob_count;
	QLabel*				m_average_per_mob;
	QLabel*				m_experience_remaining;
	QLabel*				m_play_time;
	QLabel*				m_experience_rate;
	QLabel* 			m_kills_to_level;
	QLabel*				m_time_to_level;

	QList<ExperienceRecord>		m_exp_list;

	QMenuBar*			m_menu_bar;
	QPopupMenu*			m_view_menu;
	QPopupMenu*			m_exp_rate_menu;
	QPopupMenu*			m_ZEM_menu;

	int					m_timeframe;
	int					m_ratio;
	bool				m_calcZEM;
	int					m_ZEMviewtype;
	
	QString				m_lastMobKilledName;
	UBYTE				m_lastMobKilledLevel;
};

#endif
