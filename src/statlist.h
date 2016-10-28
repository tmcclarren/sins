// statlist.h
//		SINS Distributed under GPL

#ifndef STATLIST_H
#define STATLIST_H

#include <qstring.h>
#include "baselistview.h"
#include "basewindow.h"
#include "listviewwrapper.h"
#include "everquest.h"

#define LIST_HP		0
#define LIST_MANA	1
#define LIST_STAM	2
#define LIST_FOOD	3
#define LIST_WTR	4
#define LIST_STR	5
#define LIST_STA	6
#define LIST_CHA	7
#define LIST_DEX	8
#define LIST_INT	9
#define LIST_AGI	10
#define LIST_WIS	11
#define LIST_MR		12
#define LIST_FR		13
#define LIST_CR		14
#define LIST_DR		15
#define LIST_PR		16
#define LIST_AC		17
#define LIST_MAXLIST 18

class QListViewItem;
class EQInterface;

class StatRecord
{
public:
	StatRecord( const QString& name, unsigned short value = 0, unsigned short max = 0 );
	
	QString				m_name;
	unsigned short		m_value;
	unsigned short		m_max;
};

class StatListView: public BaseListView, public ListViewWrapper<StatRecord>
{
Q_OBJECT
public:
	static const FieldMap<StatRecord> m_map[];

	StatListView( QWidget* parent = NULL, const char* name = NULL );

	static void Stat( StatRecord* stat, QString& tmp ) { tmp = stat->m_name; }
	static void Value( StatRecord* stat , QString& tmp ) { tmp = QString::number( stat->m_value ); }
	static void Max( StatRecord* stat, QString& tmp ) { tmp = QString::number( stat->m_max ); }
	static void Percent( StatRecord* stat, QString& tmp );
		
public slots:
	void statChanged( int statNum, int val, int max );
	void hpChanged( int val, int max );					// 
	void manaChanged( WORD val, WORD max );
	void stamChanged( int Sval, int Smax, int Fval, int Fmax, int Wval, int Wmax );
	
protected:
	void resetMaxMana();
	void addStats();
	
	int 		m_guessMaxMana;
	
	friend class StatWindow;
};

class StatWindow: public BaseWindow
{
Q_OBJECT
public:
	StatWindow( const char* name = NULL );
	~StatWindow();
	
protected:
	StatListView*	m_statList;
};


#endif
