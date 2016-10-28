// spelllist.h
//		SINS is disitributed under GPL

#ifndef SPELLLIST_H
#define SPELLLIST_H

#include <time.h>
#include <qlistview.h>
#include <qstring.h>
#include <qtimer.h>
#include "everquest.h"
#include "baselistview.h"
#include "listviewwrapper.h"
#include "spells.h"

class SpellListItem: public QListViewItem
{
public:
	SpellListItem( QListView* parent, Spell* spell );
	
	virtual void paintCell( QPainter* p, const QColorGroup& cg, int column, int width, int alignment );

	void setTextColor( const QColor& color ) { m_textColor = color; }
	QColor textColor() { return m_textColor; }

protected:
	QColor		m_textColor;
	Spell*		m_spell;
};



class SpellListViewWrapper: public ListViewWrapper<Spell>
{
public:
	SpellListViewWrapper( const FieldMap<Spell> map[], BaseListView* view );
	
	QColor pickSpellColor( Spell* item, QColor def = Qt::black );

	virtual QListViewItem* createNewListItem( Spell* );
};


class SpellListView: public BaseListView, public SpellListViewWrapper
{
Q_OBJECT
public:
	static const FieldMap<Spell>	m_map[];

	SpellListView( QWidget* parent = NULL, const char* name = NULL );

	static void SpellID( Spell* spell, QString& tmp ) { tmp = QString::number( spell->spellId() ); }
	static void SpellName( Spell* spell, QString& tmp ) { tmp = spell->spellName(); }
	static void CasterID( Spell* spell, QString& tmp ) { tmp = QString::number( spell->casterId() ); }
	static void CasterName( Spell* spell, QString& tmp ) { tmp = spell->casterName(); }
	static void TargetID( Spell* spell, QString& tmp ) { tmp = QString::number( spell->targetId() ); }
	static void TargetName( Spell* spell, QString& tmp ) { tmp = spell->targetName(); }
	static void CastTime( Spell* spell, QString& tmp );
	static void Duration( Spell* spell, QString& tmp );

public slots:
	void addSpell( Spell* spell );
	void removeSpell( Spell* spell );
	void updateSpell( Spell* spell );

protected:
//	QValueList<QString>		m_categoryList;
	QTimer*					m_timer;
};

#endif
