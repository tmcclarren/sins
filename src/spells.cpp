// spells.cpp
//	SINS is distributed under the GPL

#include <stdio.h>
#include "spells.h"
#include "util.h"
#include "itemmgr.h"

Spell::Spell( const struct castStruct* c )
{
	m_spellId = 0;
	m_casterId = 0;
	m_targetId = 0;
	m_duration = 0;

	this->updateSpell( c );
}

void Spell::updateSpell( const struct castStruct* c )
{
	if ( c )
	{
		m_spellId = c->spellId;
		m_targetId = c->targetId;
		m_casterId = gPlayer->id();
		m_spellName = SpellMgr::spellName( m_spellId );

		printf( "Update: %s\n", m_spellName.latin1() );

		Spawn* s = gItemMgr->spawnByID( m_casterId );
		if ( s )
			m_casterName = s->name();
		s = gItemMgr->spawnByID( m_targetId );
		if ( s )
			m_targetName = s->name();
		
		m_castTime = time( 0 );
		m_duration = SpellMgr::spellDuration( m_spellId );
	}
}

SpellMgr::SpellMgr( const char* name ):
	QObject( NULL, name ),
	m_spells( 31 )
{
	m_spells.setAutoDelete( true );
	m_timer = new QTimer( this );
	connect( m_timer, SIGNAL( timeout() ), SLOT( update() ) );
}

void SpellMgr::updateSpell( const struct castStruct* c )
{
	if ( c )
	{
		Spell*		spell = m_spells.find( Spell( c ).key() );
		if ( spell )
			spell->updateSpell( c );
		emit updateSpell( spell );
	}
}

void SpellMgr::clear()
{
	emit clearSpells();
	m_spells.clear();
	m_timer->stop();
}

Spell* SpellMgr::insertSpell( const struct castStruct* c )
{
	if ( c )
	{
		Spell*		spell = m_spells.find( Spell( c ).key() );

		if ( spell )
		{
			this->updateSpell( c );
			m_lastSpell = spell;
			return spell;
		}
		else
		{
			spell = new Spell( c );
			m_spells.insert( spell->key(), spell );
			if ( ( m_spells.count() > 0 ) && ( !m_timer->isActive() ) )
				m_timer->start( 1000 );
			m_lastSpell = spell;
			emit addSpell( spell );
			return spell;
		}
	}
	return NULL;
}

void SpellMgr::deleteSpell( Spell* spell )
{
	if ( spell )
	{
		if ( m_lastSpell == spell )
			m_lastSpell = NULL;
		if ( m_spells.count() == 0 )
			m_timer->stop();
		m_spells.remove( spell->key() );
		emit removeSpell( spell );
	}
}

void SpellMgr::selfStartSpellCast( const struct castStruct* c )
{
	printf( "selfStartSpellCast: %d\n", c->spellId );
	this->insertSpell( c );
}

void SpellMgr::interruptSpellCast( const struct interruptCastStruct* icast )
{
	if ( icast->spawnId == m_lastSpell->casterId() )
	{
		printf( "interrupt %ld by %d\n", m_lastSpell->spellId(), icast->spawnId );
		m_lastSpell->setDuration( -20 );
	}
}

void SpellMgr::selfFinishSpellCast( const struct beginCastStruct* b )
{
	printf( "selfFinishSpellCast: %d\n", b->spellId );
}

void SpellMgr::spellMessage( QString& str )
{
	QString		spell = str.right( str.length() - 7 ); // drop 'Spell: '
	bool		b = false;

	// Your xxx has worn off.
	// Your target resisted the xxx spell.
	// Your spell fizzles.

	printf( "spellMessage: %s\n", spell.latin1() );

	if ( spell.left( 25 ) == QString( "Your target resisted the ") )
	{
		spell = spell.right( spell.length() - 25 );
		spell = spell.left( spell.length() - 7 );
		printf( "resist: '%s'\n", spell.latin1() );
		b = true;
	}
	else if ( spell.right( 20 ) == QString( " spell has worn off." ) )
	{
		spell = spell.right( spell.length() - 5 );
		spell = spell.left( spell.length() - 20 );
		printf( "wore off: '%s'\n", spell.latin1() );
		b = true;
	}

	if ( b )
	{
		// can't really tell which spell/target, so just delete the last one
	}
}

void SpellMgr::update()
{
	QDictIterator<Spell>		it( m_spells );
	Spell*		spell;

	while ( ( spell = it.current() ) )
	{
		++it;
		
		int d = spell->duration();

		// check if either caster/target have despawned
		//         if ( (!pSEQShell->spawns->FindItem(tSpawn, (*it)->casterId())) ||
		//              (!pSEQShell->spawns->FindItem(tSpawn, (*it)->targetId())) ) {
		if ( ( d > 0 ) && spell->targetId() )
		{
			if ( !gItemMgr->spawnByID( spell->targetId() ) )
			{
				printf(  "timeout - caster/target died, stopping '%s'.\n", spell->spellName().latin1() );
				if ( d < 0 )
					d = 0;
			}
			if ( d > -20 )
			{
				spell->setDuration( d - 1 );
				emit updateSpell( spell );
			}
			else
			{
				printf( "Spell '%s' finished.\n", spell->spellName().latin1() );
				this->deleteSpell( spell );
			}
		}
	}
}

QString SpellMgr::spellName( unsigned long spellId )
{
	static char spellname[ 256 ];
	switch ( spellId )
	{
#include "spelldat.h"
		default:
			sprintf( spellname, "%ld", spellId );
	}

	return spellname;
}

long SpellMgr::spellDuration( unsigned long spellId )
{
	long d = 0;
	switch ( spellId )
	{
#include "spelltimes.h"
	}

	return d;
}
