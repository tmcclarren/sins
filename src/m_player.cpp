/****************************************************************************
** Player meta object code from reading C++ file 'player.h'
**
** Created: Fri Sep 28 13:03:58 2001
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.1   edited 2001-04-23 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "player.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *Player::className() const
{
    return "Player";
}

QMetaObject *Player::metaObj = 0;

void Player::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QObject::className(), "QObject") != 0 )
	badSuperclassWarning("Player","QObject");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString Player::tr(const char* s)
{
    return qApp->translate( "Player", s, 0 );
}

QString Player::tr(const char* s, const char * c)
{
    return qApp->translate( "Player", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* Player::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QObject::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (Player::*m1_t0)(const struct manaDecrementStruct*);
    typedef void (QObject::*om1_t0)(const struct manaDecrementStruct*);
    typedef void (Player::*m1_t1)(const struct staminaStruct*);
    typedef void (QObject::*om1_t1)(const struct staminaStruct*);
    typedef void (Player::*m1_t2)(const struct playerUpdateStruct*);
    typedef void (QObject::*om1_t2)(const struct playerUpdateStruct*);
    typedef void (Player::*m1_t3)(const struct skillIncreaseStruct*);
    typedef void (QObject::*om1_t3)(const struct skillIncreaseStruct*);
    typedef void (Player::*m1_t4)(const struct levelUpStruct*);
    typedef void (QObject::*om1_t4)(const struct levelUpStruct*);
    typedef void (Player::*m1_t5)(const struct expUpdateStruct*);
    typedef void (QObject::*om1_t5)(const struct expUpdateStruct*);
    typedef void (Player::*m1_t6)(const struct spawnHpUpdateStruct*);
    typedef void (QObject::*om1_t6)(const struct spawnHpUpdateStruct*);
    typedef void (Player::*m1_t7)(const struct playerProfileStruct*);
    typedef void (QObject::*om1_t7)(const struct playerProfileStruct*);
    typedef void (Player::*m1_t8)(const struct zoneChangeStruct*);
    typedef void (QObject::*om1_t8)(const struct zoneChangeStruct*);
    typedef void (Player::*m1_t9)(const struct clientZoneInStruct*);
    typedef void (QObject::*om1_t9)(const struct clientZoneInStruct*);
    typedef void (Player::*m1_t10)(const struct itemPlayerStruct*);
    typedef void (QObject::*om1_t10)(const struct itemPlayerStruct*);
    typedef void (Player::*m1_t11)(const struct playerProfileStruct*);
    typedef void (QObject::*om1_t11)(const struct playerProfileStruct*);
    m1_t0 v1_0 = &Player::handleManaUsed;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &Player::handleStamina;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &Player::handlePlayerPos;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    m1_t3 v1_3 = &Player::handleSkillUp;
    om1_t3 ov1_3 = (om1_t3)v1_3;
    m1_t4 v1_4 = &Player::handleLevelUp;
    om1_t4 ov1_4 = (om1_t4)v1_4;
    m1_t5 v1_5 = &Player::handleXPUpdate;
    om1_t5 ov1_5 = (om1_t5)v1_5;
    m1_t6 v1_6 = &Player::handleHPUpdate;
    om1_t6 ov1_6 = (om1_t6)v1_6;
    m1_t7 v1_7 = &Player::handlePlayerProfile;
    om1_t7 ov1_7 = (om1_t7)v1_7;
    m1_t8 v1_8 = &Player::handleZoneChange;
    om1_t8 ov1_8 = (om1_t8)v1_8;
    m1_t9 v1_9 = &Player::handleZoneEnd;
    om1_t9 ov1_9 = (om1_t9)v1_9;
    m1_t10 v1_10 = &Player::handlePlayerItem;
    om1_t10 ov1_10 = (om1_t10)v1_10;
    m1_t11 v1_11 = &Player::backfillPlayer;
    om1_t11 ov1_11 = (om1_t11)v1_11;
    QMetaData *slot_tbl = QMetaObject::new_metadata(12);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(12);
    slot_tbl[0].name = "handleManaUsed(const struct manaDecrementStruct*)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    slot_tbl[1].name = "handleStamina(const struct staminaStruct*)";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Public;
    slot_tbl[2].name = "handlePlayerPos(const struct playerUpdateStruct*)";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Public;
    slot_tbl[3].name = "handleSkillUp(const struct skillIncreaseStruct*)";
    slot_tbl[3].ptr = (QMember)ov1_3;
    slot_tbl_access[3] = QMetaData::Public;
    slot_tbl[4].name = "handleLevelUp(const struct levelUpStruct*)";
    slot_tbl[4].ptr = (QMember)ov1_4;
    slot_tbl_access[4] = QMetaData::Public;
    slot_tbl[5].name = "handleXPUpdate(const struct expUpdateStruct*)";
    slot_tbl[5].ptr = (QMember)ov1_5;
    slot_tbl_access[5] = QMetaData::Public;
    slot_tbl[6].name = "handleHPUpdate(const struct spawnHpUpdateStruct*)";
    slot_tbl[6].ptr = (QMember)ov1_6;
    slot_tbl_access[6] = QMetaData::Public;
    slot_tbl[7].name = "handlePlayerProfile(const struct playerProfileStruct*)";
    slot_tbl[7].ptr = (QMember)ov1_7;
    slot_tbl_access[7] = QMetaData::Public;
    slot_tbl[8].name = "handleZoneChange(const struct zoneChangeStruct*)";
    slot_tbl[8].ptr = (QMember)ov1_8;
    slot_tbl_access[8] = QMetaData::Public;
    slot_tbl[9].name = "handleZoneEnd(const struct clientZoneInStruct*)";
    slot_tbl[9].ptr = (QMember)ov1_9;
    slot_tbl_access[9] = QMetaData::Public;
    slot_tbl[10].name = "handlePlayerItem(const struct itemPlayerStruct*)";
    slot_tbl[10].ptr = (QMember)ov1_10;
    slot_tbl_access[10] = QMetaData::Public;
    slot_tbl[11].name = "backfillPlayer(const struct playerProfileStruct*)";
    slot_tbl[11].ptr = (QMember)ov1_11;
    slot_tbl_access[11] = QMetaData::Public;
    typedef void (Player::*m2_t0)(int);
    typedef void (QObject::*om2_t0)(int);
    typedef void (Player::*m2_t1)(int);
    typedef void (QObject::*om2_t1)(int);
    typedef void (Player::*m2_t2)(int);
    typedef void (QObject::*om2_t2)(int);
    typedef void (Player::*m2_t3)(const QString&);
    typedef void (QObject::*om2_t3)(const QString&);
    typedef void (Player::*m2_t4)(unsigned long,unsigned long,long);
    typedef void (QObject::*om2_t4)(unsigned long,unsigned long,long);
    typedef void (Player::*m2_t5)(int);
    typedef void (QObject::*om2_t5)(int);
    typedef void (Player::*m2_t6)(int,int,int,int,int,int,int);
    typedef void (QObject::*om2_t6)(int,int,int,int,int,int,int);
    typedef void (Player::*m2_t7)(int);
    typedef void (QObject::*om2_t7)(int);
    typedef void (Player::*m2_t8)(int,int);
    typedef void (QObject::*om2_t8)(int,int);
    typedef void (Player::*m2_t9)(int,int);
    typedef void (QObject::*om2_t9)(int,int);
    typedef void (Player::*m2_t10)(const struct primStatStruct*,const struct primStatStruct*);
    typedef void (QObject::*om2_t10)(const struct primStatStruct*,const struct primStatStruct*);
    typedef void (Player::*m2_t11)(WORD,WORD);
    typedef void (QObject::*om2_t11)(WORD,WORD);
    typedef void (Player::*m2_t12)(int,int,int,int,int,int);
    typedef void (QObject::*om2_t12)(int,int,int,int,int,int);
    typedef void (Player::*m2_t13)(int,int);
    typedef void (QObject::*om2_t13)(int,int);
    typedef void (Player::*m2_t14)(const SpawnUpdate&);
    typedef void (QObject::*om2_t14)(const SpawnUpdate&);
    m2_t0 v2_0 = &Player::xposChanged;
    om2_t0 ov2_0 = (om2_t0)v2_0;
    m2_t1 v2_1 = &Player::yposChanged;
    om2_t1 ov2_1 = (om2_t1)v2_1;
    m2_t2 v2_2 = &Player::zposChanged;
    om2_t2 ov2_2 = (om2_t2)v2_2;
    m2_t3 v2_3 = &Player::expChangedString;
    om2_t3 ov2_3 = (om2_t3)v2_3;
    m2_t4 v2_4 = &Player::expChangedInt;
    om2_t4 ov2_4 = (om2_t4)v2_4;
    m2_t5 v2_5 = &Player::headingChanged;
    om2_t5 ov2_5 = (om2_t5)v2_5;
    m2_t6 v2_6 = &Player::playerChanged;
    om2_t6 ov2_6 = (om2_t6)v2_6;
    m2_t7 v2_7 = &Player::levelUp;
    om2_t7 ov2_7 = (om2_t7)v2_7;
    m2_t8 v2_8 = &Player::addSkill;
    om2_t8 ov2_8 = (om2_t8)v2_8;
    m2_t9 v2_9 = &Player::changeSkill;
    om2_t9 ov2_9 = (om2_t9)v2_9;
    m2_t10 v2_10 = &Player::statsChanged;
    om2_t10 ov2_10 = (om2_t10)v2_10;
    m2_t11 v2_11 = &Player::manaChanged;
    om2_t11 ov2_11 = (om2_t11)v2_11;
    m2_t12 v2_12 = &Player::stamChanged;
    om2_t12 ov2_12 = (om2_t12)v2_12;
    m2_t13 v2_13 = &Player::hpChanged;
    om2_t13 ov2_13 = (om2_t13)v2_13;
    m2_t14 v2_14 = &Player::playerUpdate;
    om2_t14 ov2_14 = (om2_t14)v2_14;
    QMetaData *signal_tbl = QMetaObject::new_metadata(15);
    signal_tbl[0].name = "xposChanged(int)";
    signal_tbl[0].ptr = (QMember)ov2_0;
    signal_tbl[1].name = "yposChanged(int)";
    signal_tbl[1].ptr = (QMember)ov2_1;
    signal_tbl[2].name = "zposChanged(int)";
    signal_tbl[2].ptr = (QMember)ov2_2;
    signal_tbl[3].name = "expChangedString(const QString&)";
    signal_tbl[3].ptr = (QMember)ov2_3;
    signal_tbl[4].name = "expChangedInt(unsigned long,unsigned long,long)";
    signal_tbl[4].ptr = (QMember)ov2_4;
    signal_tbl[5].name = "headingChanged(int)";
    signal_tbl[5].ptr = (QMember)ov2_5;
    signal_tbl[6].name = "playerChanged(int,int,int,int,int,int,int)";
    signal_tbl[6].ptr = (QMember)ov2_6;
    signal_tbl[7].name = "levelUp(int)";
    signal_tbl[7].ptr = (QMember)ov2_7;
    signal_tbl[8].name = "addSkill(int,int)";
    signal_tbl[8].ptr = (QMember)ov2_8;
    signal_tbl[9].name = "changeSkill(int,int)";
    signal_tbl[9].ptr = (QMember)ov2_9;
    signal_tbl[10].name = "statsChanged(const struct primStatStruct*,const struct primStatStruct*)";
    signal_tbl[10].ptr = (QMember)ov2_10;
    signal_tbl[11].name = "manaChanged(WORD,WORD)";
    signal_tbl[11].ptr = (QMember)ov2_11;
    signal_tbl[12].name = "stamChanged(int,int,int,int,int,int)";
    signal_tbl[12].ptr = (QMember)ov2_12;
    signal_tbl[13].name = "hpChanged(int,int)";
    signal_tbl[13].ptr = (QMember)ov2_13;
    signal_tbl[14].name = "playerUpdate(const SpawnUpdate&)";
    signal_tbl[14].ptr = (QMember)ov2_14;
    metaObj = QMetaObject::new_metaobject(
	"Player", "QObject",
	slot_tbl, 12,
	signal_tbl, 15,
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

// SIGNAL xposChanged
void Player::xposChanged( int t0 )
{
    activate_signal( "xposChanged(int)", t0 );
}

// SIGNAL yposChanged
void Player::yposChanged( int t0 )
{
    activate_signal( "yposChanged(int)", t0 );
}

// SIGNAL zposChanged
void Player::zposChanged( int t0 )
{
    activate_signal( "zposChanged(int)", t0 );
}

// SIGNAL expChangedString
void Player::expChangedString( const QString& t0 )
{
    activate_signal_strref( "expChangedString(const QString&)", t0 );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL expChangedInt
void Player::expChangedInt( unsigned long t0, unsigned long t1, long t2 )
{
    // No builtin function for signal parameter type unsigned long,unsigned long,long
    QConnectionList *clist = receivers("expChangedInt(unsigned long,unsigned long,long)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(unsigned long);
    typedef void (QObject::*RT2)(unsigned long,unsigned long);
    typedef void (QObject::*RT3)(unsigned long,unsigned long,long);
    RT0 r0;
    RT1 r1;
    RT2 r2;
    RT3 r3;
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
	    case 2:
#ifdef Q_FP_CCAST_BROKEN
		r2 = reinterpret_cast<RT2>(*(c->member()));
#else
		r2 = (RT2)*(c->member());
#endif
		(object->*r2)(t0, t1);
		break;
	    case 3:
#ifdef Q_FP_CCAST_BROKEN
		r3 = reinterpret_cast<RT3>(*(c->member()));
#else
		r3 = (RT3)*(c->member());
#endif
		(object->*r3)(t0, t1, t2);
		break;
	}
    }
}

// SIGNAL headingChanged
void Player::headingChanged( int t0 )
{
    activate_signal( "headingChanged(int)", t0 );
}

// SIGNAL playerChanged
void Player::playerChanged( int t0, int t1, int t2, int t3, int t4, int t5, int t6 )
{
    // No builtin function for signal parameter type int,int,int,int,int,int,int
    QConnectionList *clist = receivers("playerChanged(int,int,int,int,int,int,int)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(int);
    typedef void (QObject::*RT2)(int,int);
    typedef void (QObject::*RT3)(int,int,int);
    typedef void (QObject::*RT4)(int,int,int,int);
    typedef void (QObject::*RT5)(int,int,int,int,int);
    typedef void (QObject::*RT6)(int,int,int,int,int,int);
    typedef void (QObject::*RT7)(int,int,int,int,int,int,int);
    RT0 r0;
    RT1 r1;
    RT2 r2;
    RT3 r3;
    RT4 r4;
    RT5 r5;
    RT6 r6;
    RT7 r7;
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
	    case 2:
#ifdef Q_FP_CCAST_BROKEN
		r2 = reinterpret_cast<RT2>(*(c->member()));
#else
		r2 = (RT2)*(c->member());
#endif
		(object->*r2)(t0, t1);
		break;
	    case 3:
#ifdef Q_FP_CCAST_BROKEN
		r3 = reinterpret_cast<RT3>(*(c->member()));
#else
		r3 = (RT3)*(c->member());
#endif
		(object->*r3)(t0, t1, t2);
		break;
	    case 4:
#ifdef Q_FP_CCAST_BROKEN
		r4 = reinterpret_cast<RT4>(*(c->member()));
#else
		r4 = (RT4)*(c->member());
#endif
		(object->*r4)(t0, t1, t2, t3);
		break;
	    case 5:
#ifdef Q_FP_CCAST_BROKEN
		r5 = reinterpret_cast<RT5>(*(c->member()));
#else
		r5 = (RT5)*(c->member());
#endif
		(object->*r5)(t0, t1, t2, t3, t4);
		break;
	    case 6:
#ifdef Q_FP_CCAST_BROKEN
		r6 = reinterpret_cast<RT6>(*(c->member()));
#else
		r6 = (RT6)*(c->member());
#endif
		(object->*r6)(t0, t1, t2, t3, t4, t5);
		break;
	    case 7:
#ifdef Q_FP_CCAST_BROKEN
		r7 = reinterpret_cast<RT7>(*(c->member()));
#else
		r7 = (RT7)*(c->member());
#endif
		(object->*r7)(t0, t1, t2, t3, t4, t5, t6);
		break;
	}
    }
}

// SIGNAL levelUp
void Player::levelUp( int t0 )
{
    activate_signal( "levelUp(int)", t0 );
}

// SIGNAL addSkill
void Player::addSkill( int t0, int t1 )
{
    // No builtin function for signal parameter type int,int
    QConnectionList *clist = receivers("addSkill(int,int)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(int);
    typedef void (QObject::*RT2)(int,int);
    RT0 r0;
    RT1 r1;
    RT2 r2;
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
	    case 2:
#ifdef Q_FP_CCAST_BROKEN
		r2 = reinterpret_cast<RT2>(*(c->member()));
#else
		r2 = (RT2)*(c->member());
#endif
		(object->*r2)(t0, t1);
		break;
	}
    }
}

// SIGNAL changeSkill
void Player::changeSkill( int t0, int t1 )
{
    // No builtin function for signal parameter type int,int
    QConnectionList *clist = receivers("changeSkill(int,int)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(int);
    typedef void (QObject::*RT2)(int,int);
    RT0 r0;
    RT1 r1;
    RT2 r2;
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
	    case 2:
#ifdef Q_FP_CCAST_BROKEN
		r2 = reinterpret_cast<RT2>(*(c->member()));
#else
		r2 = (RT2)*(c->member());
#endif
		(object->*r2)(t0, t1);
		break;
	}
    }
}

// SIGNAL statsChanged
void Player::statsChanged( const struct primStatStruct* t0, const struct primStatStruct* t1 )
{
    // No builtin function for signal parameter type const struct primStatStruct*,const struct primStatStruct*
    QConnectionList *clist = receivers("statsChanged(const struct primStatStruct*,const struct primStatStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct primStatStruct*);
    typedef void (QObject::*RT2)(const struct primStatStruct*,const struct primStatStruct*);
    RT0 r0;
    RT1 r1;
    RT2 r2;
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
	    case 2:
#ifdef Q_FP_CCAST_BROKEN
		r2 = reinterpret_cast<RT2>(*(c->member()));
#else
		r2 = (RT2)*(c->member());
#endif
		(object->*r2)(t0, t1);
		break;
	}
    }
}

// SIGNAL manaChanged
void Player::manaChanged( WORD t0, WORD t1 )
{
    // No builtin function for signal parameter type WORD,WORD
    QConnectionList *clist = receivers("manaChanged(WORD,WORD)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(WORD);
    typedef void (QObject::*RT2)(WORD,WORD);
    RT0 r0;
    RT1 r1;
    RT2 r2;
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
	    case 2:
#ifdef Q_FP_CCAST_BROKEN
		r2 = reinterpret_cast<RT2>(*(c->member()));
#else
		r2 = (RT2)*(c->member());
#endif
		(object->*r2)(t0, t1);
		break;
	}
    }
}

// SIGNAL stamChanged
void Player::stamChanged( int t0, int t1, int t2, int t3, int t4, int t5 )
{
    // No builtin function for signal parameter type int,int,int,int,int,int
    QConnectionList *clist = receivers("stamChanged(int,int,int,int,int,int)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(int);
    typedef void (QObject::*RT2)(int,int);
    typedef void (QObject::*RT3)(int,int,int);
    typedef void (QObject::*RT4)(int,int,int,int);
    typedef void (QObject::*RT5)(int,int,int,int,int);
    typedef void (QObject::*RT6)(int,int,int,int,int,int);
    RT0 r0;
    RT1 r1;
    RT2 r2;
    RT3 r3;
    RT4 r4;
    RT5 r5;
    RT6 r6;
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
	    case 2:
#ifdef Q_FP_CCAST_BROKEN
		r2 = reinterpret_cast<RT2>(*(c->member()));
#else
		r2 = (RT2)*(c->member());
#endif
		(object->*r2)(t0, t1);
		break;
	    case 3:
#ifdef Q_FP_CCAST_BROKEN
		r3 = reinterpret_cast<RT3>(*(c->member()));
#else
		r3 = (RT3)*(c->member());
#endif
		(object->*r3)(t0, t1, t2);
		break;
	    case 4:
#ifdef Q_FP_CCAST_BROKEN
		r4 = reinterpret_cast<RT4>(*(c->member()));
#else
		r4 = (RT4)*(c->member());
#endif
		(object->*r4)(t0, t1, t2, t3);
		break;
	    case 5:
#ifdef Q_FP_CCAST_BROKEN
		r5 = reinterpret_cast<RT5>(*(c->member()));
#else
		r5 = (RT5)*(c->member());
#endif
		(object->*r5)(t0, t1, t2, t3, t4);
		break;
	    case 6:
#ifdef Q_FP_CCAST_BROKEN
		r6 = reinterpret_cast<RT6>(*(c->member()));
#else
		r6 = (RT6)*(c->member());
#endif
		(object->*r6)(t0, t1, t2, t3, t4, t5);
		break;
	}
    }
}

// SIGNAL hpChanged
void Player::hpChanged( int t0, int t1 )
{
    // No builtin function for signal parameter type int,int
    QConnectionList *clist = receivers("hpChanged(int,int)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(int);
    typedef void (QObject::*RT2)(int,int);
    RT0 r0;
    RT1 r1;
    RT2 r2;
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
	    case 2:
#ifdef Q_FP_CCAST_BROKEN
		r2 = reinterpret_cast<RT2>(*(c->member()));
#else
		r2 = (RT2)*(c->member());
#endif
		(object->*r2)(t0, t1);
		break;
	}
    }
}

// SIGNAL playerUpdate
void Player::playerUpdate( const SpawnUpdate& t0 )
{
    // No builtin function for signal parameter type const SpawnUpdate&
    QConnectionList *clist = receivers("playerUpdate(const SpawnUpdate&)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const SpawnUpdate&);
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


const char *GroupMgr::className() const
{
    return "GroupMgr";
}

QMetaObject *GroupMgr::metaObj = 0;

void GroupMgr::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QObject::className(), "QObject") != 0 )
	badSuperclassWarning("GroupMgr","QObject");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString GroupMgr::tr(const char* s)
{
    return qApp->translate( "GroupMgr", s, 0 );
}

QString GroupMgr::tr(const char* s, const char * c)
{
    return qApp->translate( "GroupMgr", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* GroupMgr::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QObject::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (GroupMgr::*m1_t0)(const groupMemberStruct*);
    typedef void (QObject::*om1_t0)(const groupMemberStruct*);
    m1_t0 v1_0 = &GroupMgr::handleGroupInfo;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    QMetaData *slot_tbl = QMetaObject::new_metadata(1);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(1);
    slot_tbl[0].name = "handleGroupInfo(const groupMemberStruct*)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    typedef void (GroupMgr::*m2_t0)(Spawn*);
    typedef void (QObject::*om2_t0)(Spawn*);
    typedef void (GroupMgr::*m2_t1)(Spawn*);
    typedef void (QObject::*om2_t1)(Spawn*);
    typedef void (GroupMgr::*m2_t2)();
    typedef void (QObject::*om2_t2)();
    m2_t0 v2_0 = &GroupMgr::addGroup;
    om2_t0 ov2_0 = (om2_t0)v2_0;
    m2_t1 v2_1 = &GroupMgr::remGroup;
    om2_t1 ov2_1 = (om2_t1)v2_1;
    m2_t2 v2_2 = &GroupMgr::clrGroup;
    om2_t2 ov2_2 = (om2_t2)v2_2;
    QMetaData *signal_tbl = QMetaObject::new_metadata(3);
    signal_tbl[0].name = "addGroup(Spawn*)";
    signal_tbl[0].ptr = (QMember)ov2_0;
    signal_tbl[1].name = "remGroup(Spawn*)";
    signal_tbl[1].ptr = (QMember)ov2_1;
    signal_tbl[2].name = "clrGroup()";
    signal_tbl[2].ptr = (QMember)ov2_2;
    metaObj = QMetaObject::new_metaobject(
	"GroupMgr", "QObject",
	slot_tbl, 1,
	signal_tbl, 3,
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

// SIGNAL addGroup
void GroupMgr::addGroup( Spawn* t0 )
{
    // No builtin function for signal parameter type Spawn*
    QConnectionList *clist = receivers("addGroup(Spawn*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(Spawn*);
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

// SIGNAL remGroup
void GroupMgr::remGroup( Spawn* t0 )
{
    // No builtin function for signal parameter type Spawn*
    QConnectionList *clist = receivers("remGroup(Spawn*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(Spawn*);
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

// SIGNAL clrGroup
void GroupMgr::clrGroup()
{
    activate_signal( "clrGroup()" );
}
