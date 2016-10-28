/****************************************************************************
** ItemMgr meta object code from reading C++ file 'itemmgr.h'
**
** Created: Fri Sep 28 13:01:47 2001
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.1   edited 2001-04-23 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "itemmgr.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *ItemMgr::className() const
{
    return "ItemMgr";
}

QMetaObject *ItemMgr::metaObj = 0;

void ItemMgr::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QObject::className(), "QObject") != 0 )
	badSuperclassWarning("ItemMgr","QObject");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString ItemMgr::tr(const char* s)
{
    return qApp->translate( "ItemMgr", s, 0 );
}

QString ItemMgr::tr(const char* s, const char * c)
{
    return qApp->translate( "ItemMgr", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* ItemMgr::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QObject::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (ItemMgr::*m1_t0)(Spawn*);
    typedef void (QObject::*om1_t0)(Spawn*);
    typedef void (ItemMgr::*m1_t1)();
    typedef void (QObject::*om1_t1)();
    typedef void (ItemMgr::*m1_t2)();
    typedef void (QObject::*om1_t2)();
    typedef void (ItemMgr::*m1_t3)(const struct zoneSpawnsStruct*,int);
    typedef void (QObject::*om1_t3)(const struct zoneSpawnsStruct*,int);
    typedef void (ItemMgr::*m1_t4)(const struct equipChangeStruct*);
    typedef void (QObject::*om1_t4)(const struct equipChangeStruct*);
    typedef void (ItemMgr::*m1_t5)(const struct clientZoneInStruct*);
    typedef void (QObject::*om1_t5)(const struct clientZoneInStruct*);
    typedef void (ItemMgr::*m1_t6)(const struct clientZoneOutStruct*);
    typedef void (QObject::*om1_t6)(const struct clientZoneOutStruct*);
    typedef void (ItemMgr::*m1_t7)(const struct zoneChangeStruct*);
    typedef void (QObject::*om1_t7)(const struct zoneChangeStruct*);
    typedef void (ItemMgr::*m1_t8)(const struct spawnKilledStruct*);
    typedef void (QObject::*om1_t8)(const struct spawnKilledStruct*);
    typedef void (ItemMgr::*m1_t9)(const struct spawnHpUpdateStruct*);
    typedef void (QObject::*om1_t9)(const struct spawnHpUpdateStruct*);
    typedef void (ItemMgr::*m1_t10)(const struct spawnPosUpdateStruct*);
    typedef void (QObject::*om1_t10)(const struct spawnPosUpdateStruct*);
    typedef void (ItemMgr::*m1_t11)(const struct addSpawnStruct*);
    typedef void (QObject::*om1_t11)(const struct addSpawnStruct*);
    typedef void (ItemMgr::*m1_t12)(const struct deleteSpawnStruct*);
    typedef void (QObject::*om1_t12)(const struct deleteSpawnStruct*);
    typedef void (ItemMgr::*m1_t13)(const struct addDropStruct*);
    typedef void (QObject::*om1_t13)(const struct addDropStruct*);
    typedef void (ItemMgr::*m1_t14)(const struct deleteDropStruct*);
    typedef void (QObject::*om1_t14)(const struct deleteDropStruct*);
    typedef void (ItemMgr::*m1_t15)(const struct addCoinsStruct*);
    typedef void (QObject::*om1_t15)(const struct addCoinsStruct*);
    typedef void (ItemMgr::*m1_t16)(const struct deleteCoinsStruct*);
    typedef void (QObject::*om1_t16)(const struct deleteCoinsStruct*);
    typedef void (ItemMgr::*m1_t17)(const struct spawnStruct*);
    typedef void (QObject::*om1_t17)(const struct spawnStruct*);
    typedef void (ItemMgr::*m1_t18)();
    typedef void (QObject::*om1_t18)();
    typedef void (ItemMgr::*m1_t19)();
    typedef void (QObject::*om1_t19)();
    typedef void (ItemMgr::*m1_t20)();
    typedef void (QObject::*om1_t20)();
    m1_t0 v1_0 = &ItemMgr::selectionChanged;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &ItemMgr::keyFound;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &ItemMgr::filtersChanged;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    m1_t3 v1_3 = &ItemMgr::handleZoneSpawns;
    om1_t3 ov1_3 = (om1_t3)v1_3;
    m1_t4 v1_4 = &ItemMgr::handleEquipChange;
    om1_t4 ov1_4 = (om1_t4)v1_4;
    m1_t5 v1_5 = &ItemMgr::handleZoneEnd;
    om1_t5 ov1_5 = (om1_t5)v1_5;
    m1_t6 v1_6 = &ItemMgr::handleZoneBegin;
    om1_t6 ov1_6 = (om1_t6)v1_6;
    m1_t7 v1_7 = &ItemMgr::handleZoneChange;
    om1_t7 ov1_7 = (om1_t7)v1_7;
    m1_t8 v1_8 = &ItemMgr::handleCorpse;
    om1_t8 ov1_8 = (om1_t8)v1_8;
    m1_t9 v1_9 = &ItemMgr::handleHPUpdate;
    om1_t9 ov1_9 = (om1_t9)v1_9;
    m1_t10 v1_10 = &ItemMgr::handleSpawnUpdate;
    om1_t10 ov1_10 = (om1_t10)v1_10;
    m1_t11 v1_11 = &ItemMgr::handleNewSpawn;
    om1_t11 ov1_11 = (om1_t11)v1_11;
    m1_t12 v1_12 = &ItemMgr::handleDeleteSpawn;
    om1_t12 ov1_12 = (om1_t12)v1_12;
    m1_t13 v1_13 = &ItemMgr::handleNewDrop;
    om1_t13 ov1_13 = (om1_t13)v1_13;
    m1_t14 v1_14 = &ItemMgr::handleDeleteDrop;
    om1_t14 ov1_14 = (om1_t14)v1_14;
    m1_t15 v1_15 = &ItemMgr::handleNewCoins;
    om1_t15 ov1_15 = (om1_t15)v1_15;
    m1_t16 v1_16 = &ItemMgr::handleDeleteCoins;
    om1_t16 ov1_16 = (om1_t16)v1_16;
    m1_t17 v1_17 = &ItemMgr::backfillSpawn;
    om1_t17 ov1_17 = (om1_t17)v1_17;
    m1_t18 v1_18 = &ItemMgr::dumpDrops;
    om1_t18 ov1_18 = (om1_t18)v1_18;
    m1_t19 v1_19 = &ItemMgr::dumpCoins;
    om1_t19 ov1_19 = (om1_t19)v1_19;
    m1_t20 v1_20 = &ItemMgr::dumpSpawns;
    om1_t20 ov1_20 = (om1_t20)v1_20;
    QMetaData *slot_tbl = QMetaObject::new_metadata(21);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(21);
    slot_tbl[0].name = "selectionChanged(Spawn*)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    slot_tbl[1].name = "keyFound()";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Public;
    slot_tbl[2].name = "filtersChanged()";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Public;
    slot_tbl[3].name = "handleZoneSpawns(const struct zoneSpawnsStruct*,int)";
    slot_tbl[3].ptr = (QMember)ov1_3;
    slot_tbl_access[3] = QMetaData::Public;
    slot_tbl[4].name = "handleEquipChange(const struct equipChangeStruct*)";
    slot_tbl[4].ptr = (QMember)ov1_4;
    slot_tbl_access[4] = QMetaData::Public;
    slot_tbl[5].name = "handleZoneEnd(const struct clientZoneInStruct*)";
    slot_tbl[5].ptr = (QMember)ov1_5;
    slot_tbl_access[5] = QMetaData::Public;
    slot_tbl[6].name = "handleZoneBegin(const struct clientZoneOutStruct*)";
    slot_tbl[6].ptr = (QMember)ov1_6;
    slot_tbl_access[6] = QMetaData::Public;
    slot_tbl[7].name = "handleZoneChange(const struct zoneChangeStruct*)";
    slot_tbl[7].ptr = (QMember)ov1_7;
    slot_tbl_access[7] = QMetaData::Public;
    slot_tbl[8].name = "handleCorpse(const struct spawnKilledStruct*)";
    slot_tbl[8].ptr = (QMember)ov1_8;
    slot_tbl_access[8] = QMetaData::Public;
    slot_tbl[9].name = "handleHPUpdate(const struct spawnHpUpdateStruct*)";
    slot_tbl[9].ptr = (QMember)ov1_9;
    slot_tbl_access[9] = QMetaData::Public;
    slot_tbl[10].name = "handleSpawnUpdate(const struct spawnPosUpdateStruct*)";
    slot_tbl[10].ptr = (QMember)ov1_10;
    slot_tbl_access[10] = QMetaData::Public;
    slot_tbl[11].name = "handleNewSpawn(const struct addSpawnStruct*)";
    slot_tbl[11].ptr = (QMember)ov1_11;
    slot_tbl_access[11] = QMetaData::Public;
    slot_tbl[12].name = "handleDeleteSpawn(const struct deleteSpawnStruct*)";
    slot_tbl[12].ptr = (QMember)ov1_12;
    slot_tbl_access[12] = QMetaData::Public;
    slot_tbl[13].name = "handleNewDrop(const struct addDropStruct*)";
    slot_tbl[13].ptr = (QMember)ov1_13;
    slot_tbl_access[13] = QMetaData::Public;
    slot_tbl[14].name = "handleDeleteDrop(const struct deleteDropStruct*)";
    slot_tbl[14].ptr = (QMember)ov1_14;
    slot_tbl_access[14] = QMetaData::Public;
    slot_tbl[15].name = "handleNewCoins(const struct addCoinsStruct*)";
    slot_tbl[15].ptr = (QMember)ov1_15;
    slot_tbl_access[15] = QMetaData::Public;
    slot_tbl[16].name = "handleDeleteCoins(const struct deleteCoinsStruct*)";
    slot_tbl[16].ptr = (QMember)ov1_16;
    slot_tbl_access[16] = QMetaData::Public;
    slot_tbl[17].name = "backfillSpawn(const struct spawnStruct*)";
    slot_tbl[17].ptr = (QMember)ov1_17;
    slot_tbl_access[17] = QMetaData::Public;
    slot_tbl[18].name = "dumpDrops()";
    slot_tbl[18].ptr = (QMember)ov1_18;
    slot_tbl_access[18] = QMetaData::Public;
    slot_tbl[19].name = "dumpCoins()";
    slot_tbl[19].ptr = (QMember)ov1_19;
    slot_tbl_access[19] = QMetaData::Public;
    slot_tbl[20].name = "dumpSpawns()";
    slot_tbl[20].ptr = (QMember)ov1_20;
    slot_tbl_access[20] = QMetaData::Public;
    typedef void (ItemMgr::*m2_t0)(const QString&);
    typedef void (QObject::*om2_t0)(const QString&);
    typedef void (ItemMgr::*m2_t1)(const QString&);
    typedef void (QObject::*om2_t1)(const QString&);
    typedef void (ItemMgr::*m2_t2)();
    typedef void (QObject::*om2_t2)();
    typedef void (ItemMgr::*m2_t3)(Spawn*);
    typedef void (QObject::*om2_t3)(Spawn*);
    typedef void (ItemMgr::*m2_t4)(Spawn*);
    typedef void (QObject::*om2_t4)(Spawn*);
    typedef void (ItemMgr::*m2_t5)(Spawn*);
    typedef void (QObject::*om2_t5)(Spawn*);
    typedef void (ItemMgr::*m2_t6)(Spawn*);
    typedef void (QObject::*om2_t6)(Spawn*);
    typedef void (ItemMgr::*m2_t7)(Spawn*);
    typedef void (QObject::*om2_t7)(Spawn*);
    typedef void (ItemMgr::*m2_t8)();
    typedef void (QObject::*om2_t8)();
    typedef void (ItemMgr::*m2_t9)(Coins*);
    typedef void (QObject::*om2_t9)(Coins*);
    typedef void (ItemMgr::*m2_t10)(Coins*);
    typedef void (QObject::*om2_t10)(Coins*);
    typedef void (ItemMgr::*m2_t11)(Drop*);
    typedef void (QObject::*om2_t11)(Drop*);
    typedef void (ItemMgr::*m2_t12)(Drop*);
    typedef void (QObject::*om2_t12)(Drop*);
    typedef void (ItemMgr::*m2_t13)(int);
    typedef void (QObject::*om2_t13)(int);
    typedef void (ItemMgr::*m2_t14)(Spawn*);
    typedef void (QObject::*om2_t14)(Spawn*);
    m2_t0 v2_0 = &ItemMgr::zoneEnd;
    om2_t0 ov2_0 = (om2_t0)v2_0;
    m2_t1 v2_1 = &ItemMgr::zoneChanged;
    om2_t1 ov2_1 = (om2_t1)v2_1;
    m2_t2 v2_2 = &ItemMgr::zoneBegin;
    om2_t2 ov2_2 = (om2_t2)v2_2;
    m2_t3 v2_3 = &ItemMgr::processSpawn;
    om2_t3 ov2_3 = (om2_t3)v2_3;
    m2_t4 v2_4 = &ItemMgr::addSpawn;
    om2_t4 ov2_4 = (om2_t4)v2_4;
    m2_t5 v2_5 = &ItemMgr::deleteSpawn;
    om2_t5 ov2_5 = (om2_t5)v2_5;
    m2_t6 v2_6 = &ItemMgr::killSpawn;
    om2_t6 ov2_6 = (om2_t6)v2_6;
    m2_t7 v2_7 = &ItemMgr::spawnChanged;
    om2_t7 ov2_7 = (om2_t7)v2_7;
    m2_t8 v2_8 = &ItemMgr::allSpawnsChanged;
    om2_t8 ov2_8 = (om2_t8)v2_8;
    m2_t9 v2_9 = &ItemMgr::addCoins;
    om2_t9 ov2_9 = (om2_t9)v2_9;
    m2_t10 v2_10 = &ItemMgr::deleteCoins;
    om2_t10 ov2_10 = (om2_t10)v2_10;
    m2_t11 v2_11 = &ItemMgr::addDrop;
    om2_t11 ov2_11 = (om2_t11)v2_11;
    m2_t12 v2_12 = &ItemMgr::deleteDrop;
    om2_t12 ov2_12 = (om2_t12)v2_12;
    m2_t13 v2_13 = &ItemMgr::numSpawns;
    om2_t13 ov2_13 = (om2_t13)v2_13;
    m2_t14 v2_14 = &ItemMgr::handleSelectItem;
    om2_t14 ov2_14 = (om2_t14)v2_14;
    QMetaData *signal_tbl = QMetaObject::new_metadata(15);
    signal_tbl[0].name = "zoneEnd(const QString&)";
    signal_tbl[0].ptr = (QMember)ov2_0;
    signal_tbl[1].name = "zoneChanged(const QString&)";
    signal_tbl[1].ptr = (QMember)ov2_1;
    signal_tbl[2].name = "zoneBegin()";
    signal_tbl[2].ptr = (QMember)ov2_2;
    signal_tbl[3].name = "processSpawn(Spawn*)";
    signal_tbl[3].ptr = (QMember)ov2_3;
    signal_tbl[4].name = "addSpawn(Spawn*)";
    signal_tbl[4].ptr = (QMember)ov2_4;
    signal_tbl[5].name = "deleteSpawn(Spawn*)";
    signal_tbl[5].ptr = (QMember)ov2_5;
    signal_tbl[6].name = "killSpawn(Spawn*)";
    signal_tbl[6].ptr = (QMember)ov2_6;
    signal_tbl[7].name = "spawnChanged(Spawn*)";
    signal_tbl[7].ptr = (QMember)ov2_7;
    signal_tbl[8].name = "allSpawnsChanged()";
    signal_tbl[8].ptr = (QMember)ov2_8;
    signal_tbl[9].name = "addCoins(Coins*)";
    signal_tbl[9].ptr = (QMember)ov2_9;
    signal_tbl[10].name = "deleteCoins(Coins*)";
    signal_tbl[10].ptr = (QMember)ov2_10;
    signal_tbl[11].name = "addDrop(Drop*)";
    signal_tbl[11].ptr = (QMember)ov2_11;
    signal_tbl[12].name = "deleteDrop(Drop*)";
    signal_tbl[12].ptr = (QMember)ov2_12;
    signal_tbl[13].name = "numSpawns(int)";
    signal_tbl[13].ptr = (QMember)ov2_13;
    signal_tbl[14].name = "handleSelectItem(Spawn*)";
    signal_tbl[14].ptr = (QMember)ov2_14;
    metaObj = QMetaObject::new_metaobject(
	"ItemMgr", "QObject",
	slot_tbl, 21,
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

// SIGNAL zoneEnd
void ItemMgr::zoneEnd( const QString& t0 )
{
    activate_signal_strref( "zoneEnd(const QString&)", t0 );
}

// SIGNAL zoneChanged
void ItemMgr::zoneChanged( const QString& t0 )
{
    activate_signal_strref( "zoneChanged(const QString&)", t0 );
}

// SIGNAL zoneBegin
void ItemMgr::zoneBegin()
{
    activate_signal( "zoneBegin()" );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL processSpawn
void ItemMgr::processSpawn( Spawn* t0 )
{
    // No builtin function for signal parameter type Spawn*
    QConnectionList *clist = receivers("processSpawn(Spawn*)");
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

// SIGNAL addSpawn
void ItemMgr::addSpawn( Spawn* t0 )
{
    // No builtin function for signal parameter type Spawn*
    QConnectionList *clist = receivers("addSpawn(Spawn*)");
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

// SIGNAL deleteSpawn
void ItemMgr::deleteSpawn( Spawn* t0 )
{
    // No builtin function for signal parameter type Spawn*
    QConnectionList *clist = receivers("deleteSpawn(Spawn*)");
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

// SIGNAL killSpawn
void ItemMgr::killSpawn( Spawn* t0 )
{
    // No builtin function for signal parameter type Spawn*
    QConnectionList *clist = receivers("killSpawn(Spawn*)");
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

// SIGNAL spawnChanged
void ItemMgr::spawnChanged( Spawn* t0 )
{
    // No builtin function for signal parameter type Spawn*
    QConnectionList *clist = receivers("spawnChanged(Spawn*)");
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

// SIGNAL allSpawnsChanged
void ItemMgr::allSpawnsChanged()
{
    activate_signal( "allSpawnsChanged()" );
}

// SIGNAL addCoins
void ItemMgr::addCoins( Coins* t0 )
{
    // No builtin function for signal parameter type Coins*
    QConnectionList *clist = receivers("addCoins(Coins*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(Coins*);
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

// SIGNAL deleteCoins
void ItemMgr::deleteCoins( Coins* t0 )
{
    // No builtin function for signal parameter type Coins*
    QConnectionList *clist = receivers("deleteCoins(Coins*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(Coins*);
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

// SIGNAL addDrop
void ItemMgr::addDrop( Drop* t0 )
{
    // No builtin function for signal parameter type Drop*
    QConnectionList *clist = receivers("addDrop(Drop*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(Drop*);
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

// SIGNAL deleteDrop
void ItemMgr::deleteDrop( Drop* t0 )
{
    // No builtin function for signal parameter type Drop*
    QConnectionList *clist = receivers("deleteDrop(Drop*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(Drop*);
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

// SIGNAL numSpawns
void ItemMgr::numSpawns( int t0 )
{
    activate_signal( "numSpawns(int)", t0 );
}

// SIGNAL handleSelectItem
void ItemMgr::handleSelectItem( Spawn* t0 )
{
    // No builtin function for signal parameter type Spawn*
    QConnectionList *clist = receivers("handleSelectItem(Spawn*)");
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
