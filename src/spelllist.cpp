// spelllist.cpp
//	SINS is distributed under GPL

#include "spelllist.h"
#include "main.h"

SpellListItem::SpellListItem( QListView* parent, Spell* spell ): QListViewItem( parent )
{
	m_textColor = Qt::black;
	m_spell = spell;
}

// overridden from base class in order to change color and style attributes
void SpellListItem::paintCell( QPainter* p, const QColorGroup& cg, int column, int width, int alignment )
{
#ifdef DEBUG
//	debug( "SpellListItem::paintCell()" );
#endif
	QColorGroup newCg( cg );

	newCg.setColor( QColorGroup::Text, m_textColor );

	QFont		font = this->listView()->font();
	if ( m_spell->duration() < 10 )
		font.setBold( true );
	else
		font.setBold( false );
	p->setFont( font );
	
	QListViewItem::paintCell( p, newCg, column, width, alignment );
}

SpellListViewWrapper::SpellListViewWrapper( const FieldMap<Spell> map[], BaseListView* view ):
	ListViewWrapper<Spell>( map, view, 31 )
{
}

QColor SpellListViewWrapper::pickSpellColor( Spell* /*s*/, QColor /*def*/ )
{
	return Qt::black;
}

QListViewItem* SpellListViewWrapper::createNewListItem( Spell* s )
{
	SpellListItem*		newItem = new SpellListItem( m_listView, s );
	newItem->setTextColor( this->pickSpellColor( s ) );
	return newItem;
}

const FieldMap<Spell> SpellListView::m_map[] = {
	{ "ID", SpellListView::SpellID },
	{ "Name", SpellListView::SpellName },
	{ "Caster", SpellListView::CasterName },
	{ "Target", SpellListView::TargetName },
	{ "Cast", SpellListView::CastTime },
	{ "Duration", SpellListView::Duration },
	{ NULL, NULL }
};

SpellListView::SpellListView( QWidget* parent = NULL, const char* name = NULL ):
	BaseListView( "Spells", parent, name ),
	SpellListViewWrapper( m_map, this )
{
	connect( gSpellMgr, SIGNAL( addSpell(Spell*) ), this, SLOT( addSpell(Spell*) ) );
	connect( gSpellMgr, SIGNAL( removeSpell(Spell*) ), this, SLOT( removeSpell(Spell*) ) );
	connect( gSpellMgr, SIGNAL( updateSpell(Spell*) ), this, SLOT( updateSpell(Spell*) ) );
}

void SpellListView::CastTime( Spell* /*spell*/, QString& tmp )
{
	tmp = "";
}

void SpellListView::Duration( Spell* spell, QString& tmp )
{
	int d = spell->duration();
	if ( d < 0 )
		d = 0;
	int h = d / 3600;
	d %= 3600;

	tmp.sprintf( "%02d:%02d:%02d", h, d / 60, d % 60 );
}

void SpellListView::addSpell( Spell* spell )
{
	this->addItem( (int)spell, spell );
}

void SpellListView::removeSpell( Spell* spell )
{
	this->deleteItem( (int)spell );
}

void SpellListView::updateSpell( Spell* spell )
{
	this->updateItem( (int)spell );
}
