// spells.h
//	SINS is distributed under GPL

#ifndef SPELLS_H
#define SPELLS_H

#include <qdict.h>
#include <qtimer.h>
#include <qstring.h>
#include <time.h>
#include "everquest.h"

class Spell
{
public:
	Spell( const struct castStruct* c = NULL );

	void updateSpell( const struct castStruct* c = NULL );

	long spellId() { return m_spellId; }
	long targetId() { return m_targetId; }
	long casterId() { return m_casterId; }
	time_t castTime() { return m_castTime; }
	long duration() { return m_duration; }
	void setDuration( long d ) { m_duration = d; }

	QString spellName() { return m_spellName; }
	QString targetName() { return m_targetName; }
	QString casterName() { return m_casterName; }

	QString	key()
	{
		QString		key;
		key.sprintf( "%ld%ld%ld", m_spellId, m_casterId, m_targetId );
		return key;
	}

protected:
	long		m_spellId;
	long		m_casterId;
	long		m_targetId;
	long		m_duration;
	time_t		m_castTime;

	QString		m_spellName;
	QString		m_casterName;
	QString		m_targetName;
	QString		m_str;

	struct castStruct m_cast;
};

class SpellMgr: public QObject
{
Q_OBJECT
public:
	SpellMgr( const char* name = NULL );

	Spell* insertSpell( const struct castStruct* c );
	void updateSpell( const struct castStruct* c );
	void deleteSpell( Spell* );
	void clear();

	static QString spellName( unsigned long spellId );
	static long spellDuration( unsigned long spellId );

signals:
	void addSpell( Spell* );
	void removeSpell( Spell* );
	void updateSpell( Spell* );
	void clearSpells();

public slots:
	void selfStartSpellCast( const struct castStruct* );
	void interruptSpellCast( const struct interruptCastStruct* );
	void selfFinishSpellCast( const struct beginCastStruct* );
	void spellMessage( QString& );
	void update();

protected:
	QDict<Spell>		m_spells;
	QTimer*				m_timer;
	Spell*				m_lastSpell;
};

#endif
