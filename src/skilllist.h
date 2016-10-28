// skilllist.h
//		SINS Distributed under GPL

#ifndef SKILLLIST_H
#define SKILLLIST_H

#include <qintdict.h>
#include "listviewwrapper.h"
#include "baselistview.h"
#include "basewindow.h"

class QListViewItem;

class SkillRecord
{
public:
	SkillRecord( unsigned short skillID, unsigned short value );

	unsigned short		m_skillID;
	unsigned short		m_value;
};
	
class SkillListView: public BaseListView, public ListViewWrapper<SkillRecord>
{
Q_OBJECT
public:
	static const FieldMap<SkillRecord> m_map[];

	SkillListView( QWidget* parent = NULL, const char* name = NULL );

	static void Value( SkillRecord* in, QString& tmp );	
	static void Skill( SkillRecord* in, QString& tmp ) { tmp = SkillListView::skillName( in->m_skillID ); }
		
	static QString SkillListView::skillName( int skillId );

public slots:
	void addSkill( int skillId, int value );
	void changeSkill( int skillId, int value );
};

class SkillWindow: public BaseWindow
{
Q_OBJECT
public:
	SkillWindow( const char* name = NULL );
	~SkillWindow();

protected:
	SkillListView*		m_skillList;
};

#endif
