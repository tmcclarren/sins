/****************************************************************************
** SpellMgr meta object code from reading C++ file 'spells.h'
**
** Created: Fri Sep 28 13:05:51 2001
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.1   edited 2001-04-23 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "spells.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *SpellMgr::className() const
{
    return "SpellMgr";
}

QMetaObject *SpellMgr::metaObj = 0;

void SpellMgr::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QObject::className(), "QObject") != 0 )
	badSuperclassWarning("SpellMgr","QObject");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString SpellMgr::tr(const char* s)
{
    return qApp->translate( "SpellMgr", s, 0 );
}

QString SpellMgr::tr(const char* s, const char * c)
{
    return qApp->translate( "SpellMgr", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* SpellMgr::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QObject::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (SpellMgr::*m1_t0)(const struct castStruct*);
    typedef void (QObject::*om1_t0)(const struct castStruct*);
    typedef void (SpellMgr::*m1_t1)(const struct interruptCastStruct*);
    typedef void (QObject::*om1_t1)(const struct interruptCastStruct*);
    typedef void (SpellMgr::*m1_t2)(const struct beginCastStruct*);
    typedef void (QObject::*om1_t2)(const struct beginCastStruct*);
    typedef void (SpellMgr::*m1_t3)(QString&);
    typedef void (QObject::*om1_t3)(QString&);
    typedef void (SpellMgr::*m1_t4)();
    typedef void (QObject::*om1_t4)();
    m1_t0 v1_0 = &SpellMgr::selfStartSpellCast;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &SpellMgr::interruptSpellCast;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &SpellMgr::selfFinishSpellCast;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    m1_t3 v1_3 = &SpellMgr::spellMessage;
    om1_t3 ov1_3 = (om1_t3)v1_3;
    m1_t4 v1_4 = &SpellMgr::update;
    om1_t4 ov1_4 = (om1_t4)v1_4;
    QMetaData *slot_tbl = QMetaObject::new_metadata(5);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(5);
    slot_tbl[0].name = "selfStartSpellCast(const struct castStruct*)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    slot_tbl[1].name = "interruptSpellCast(const struct interruptCastStruct*)";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Public;
    slot_tbl[2].name = "selfFinishSpellCast(const struct beginCastStruct*)";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Public;
    slot_tbl[3].name = "spellMessage(QString&)";
    slot_tbl[3].ptr = (QMember)ov1_3;
    slot_tbl_access[3] = QMetaData::Public;
    slot_tbl[4].name = "update()";
    slot_tbl[4].ptr = (QMember)ov1_4;
    slot_tbl_access[4] = QMetaData::Public;
    typedef void (SpellMgr::*m2_t0)(Spell*);
    typedef void (QObject::*om2_t0)(Spell*);
    typedef void (SpellMgr::*m2_t1)(Spell*);
    typedef void (QObject::*om2_t1)(Spell*);
    typedef void (SpellMgr::*m2_t2)(Spell*);
    typedef void (QObject::*om2_t2)(Spell*);
    typedef void (SpellMgr::*m2_t3)();
    typedef void (QObject::*om2_t3)();
    m2_t0 v2_0 = &SpellMgr::addSpell;
    om2_t0 ov2_0 = (om2_t0)v2_0;
    m2_t1 v2_1 = &SpellMgr::removeSpell;
    om2_t1 ov2_1 = (om2_t1)v2_1;
    m2_t2 v2_2 = &SpellMgr::updateSpell;
    om2_t2 ov2_2 = (om2_t2)v2_2;
    m2_t3 v2_3 = &SpellMgr::clearSpells;
    om2_t3 ov2_3 = (om2_t3)v2_3;
    QMetaData *signal_tbl = QMetaObject::new_metadata(4);
    signal_tbl[0].name = "addSpell(Spell*)";
    signal_tbl[0].ptr = (QMember)ov2_0;
    signal_tbl[1].name = "removeSpell(Spell*)";
    signal_tbl[1].ptr = (QMember)ov2_1;
    signal_tbl[2].name = "updateSpell(Spell*)";
    signal_tbl[2].ptr = (QMember)ov2_2;
    signal_tbl[3].name = "clearSpells()";
    signal_tbl[3].ptr = (QMember)ov2_3;
    metaObj = QMetaObject::new_metaobject(
	"SpellMgr", "QObject",
	slot_tbl, 5,
	signal_tbl, 4,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    metaObj->set_slot_access( slot_tbl_access );
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    return metaObj;
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL addSpell
void SpellMgr::addSpell( Spell* t0 )
{
    // No builtin function for signal parameter type Spell*
    QConnectionList *clist = receivers("addSpell(Spell*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(Spell*);
    RT0 r0;
    RT1 r1;
    QConnectionListIt it(*clist);
    QConnection   *c;
    QSenderObject *object;
    while ( (c=it.current()) ) {
	++it;
	object = (QSenderObject*)c->object();
	object->setSender( this );
	switch ( c->numArgs() ) {
	    case 0:
#ifdef Q_FP_CCAST_BROKEN
		r0 = reinterpret_cast<RT0>(*(c->member()));
#else
		r0 = (RT0)*(c->member());
#endif
		(object->*r0)();
		break;
	    case 1:
#ifdef Q_FP_CCAST_BROKEN
		r1 = reinterpret_cast<RT1>(*(c->member()));
#else
		r1 = (RT1)*(c->member());
#endif
		(object->*r1)(t0);
		break;
	}
    }
}

// SIGNAL removeSpell
void SpellMgr::removeSpell( Spell* t0 )
{
    // No builtin function for signal parameter type Spell*
    QConnectionList *clist = receivers("removeSpell(Spell*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(Spell*);
    RT0 r0;
    RT1 r1;
    QConnectionListIt it(*clist);
    QConnection   *c;
    QSenderObject *object;
    while ( (c=it.current()) ) {
	++it;
	object = (QSenderObject*)c->object();
	object->setSender( this );
	switch ( c->numArgs() ) {
	    case 0:
#ifdef Q_FP_CCAST_BROKEN
		r0 = reinterpret_cast<RT0>(*(c->member()));
#else
		r0 = (RT0)*(c->member());
#endif
		(object->*r0)();
		break;
	    case 1:
#ifdef Q_FP_CCAST_BROKEN
		r1 = reinterpret_cast<RT1>(*(c->member()));
#else
		r1 = (RT1)*(c->member());
#endif
		(object->*r1)(t0);
		break;
	}
    }
}

// SIGNAL updateSpell
void SpellMgr::updateSpell( Spell* t0 )
{
    // No builtin function for signal parameter type Spell*
    QConnectionList *clist = receivers("updateSpell(Spell*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(Spell*);
    RT0 r0;
    RT1 r1;
    QConnectionListIt it(*clist);
    QConnection   *c;
    QSenderObject *object;
    while ( (c=it.current()) ) {
	++it;
	object = (QSenderObject*)c->object();
	object->setSender( this );
	switch ( c->numArgs() ) {
	    case 0:
#ifdef Q_FP_CCAST_BROKEN
		r0 = reinterpret_cast<RT0>(*(c->member()));
#else
		r0 = (RT0)*(c->member());
#endif
		(object->*r0)();
		break;
	    case 1:
#ifdef Q_FP_CCAST_BROKEN
		r1 = reinterpret_cast<RT1>(*(c->member()));
#else
		r1 = (RT1)*(c->member());
#endif
		(object->*r1)(t0);
		break;
	}
    }
}

// SIGNAL clearSpells
void SpellMgr::clearSpells()
{
    activate_signal( "clearSpells()" );
}
