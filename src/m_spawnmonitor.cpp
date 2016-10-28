/****************************************************************************
** SpawnMonitor meta object code from reading C++ file 'spawnmonitor.h'
**
** Created: Fri Sep 28 13:04:58 2001
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.1   edited 2001-04-23 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "spawnmonitor.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *SpawnMonitor::className() const
{
    return "SpawnMonitor";
}

QMetaObject *SpawnMonitor::metaObj = 0;

void SpawnMonitor::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QObject::className(), "QObject") != 0 )
	badSuperclassWarning("SpawnMonitor","QObject");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString SpawnMonitor::tr(const char* s)
{
    return qApp->translate( "SpawnMonitor", s, 0 );
}

QString SpawnMonitor::tr(const char* s, const char * c)
{
    return qApp->translate( "SpawnMonitor", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* SpawnMonitor::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QObject::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (SpawnMonitor::*m1_t0)(Spawn*);
    typedef void (QObject::*om1_t0)(Spawn*);
    typedef void (SpawnMonitor::*m1_t1)(Spawn*);
    typedef void (QObject::*om1_t1)(Spawn*);
    typedef void (SpawnMonitor::*m1_t2)(const QString&);
    typedef void (QObject::*om1_t2)(const QString&);
    typedef void (SpawnMonitor::*m1_t3)(const QString&);
    typedef void (QObject::*om1_t3)(const QString&);
    typedef void (SpawnMonitor::*m1_t4)();
    typedef void (QObject::*om1_t4)();
    typedef void (SpawnMonitor::*m1_t5)();
    typedef void (QObject::*om1_t5)();
    m1_t0 v1_0 = &SpawnMonitor::newSpawn;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &SpawnMonitor::killSpawn;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &SpawnMonitor::zoneChanged;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    m1_t3 v1_3 = &SpawnMonitor::zoneEnd;
    om1_t3 ov1_3 = (om1_t3)v1_3;
    m1_t4 v1_4 = &SpawnMonitor::saveSpawnPoints;
    om1_t4 ov1_4 = (om1_t4)v1_4;
    m1_t5 v1_5 = &SpawnMonitor::loadSpawnPoints;
    om1_t5 ov1_5 = (om1_t5)v1_5;
    QMetaData *slot_tbl = QMetaObject::new_metadata(6);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(6);
    slot_tbl[0].name = "newSpawn(Spawn*)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    slot_tbl[1].name = "killSpawn(Spawn*)";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Public;
    slot_tbl[2].name = "zoneChanged(const QString&)";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Public;
    slot_tbl[3].name = "zoneEnd(const QString&)";
    slot_tbl[3].ptr = (QMember)ov1_3;
    slot_tbl_access[3] = QMetaData::Public;
    slot_tbl[4].name = "saveSpawnPoints()";
    slot_tbl[4].ptr = (QMember)ov1_4;
    slot_tbl_access[4] = QMetaData::Public;
    slot_tbl[5].name = "loadSpawnPoints()";
    slot_tbl[5].ptr = (QMember)ov1_5;
    slot_tbl_access[5] = QMetaData::Public;
    typedef void (SpawnMonitor::*m2_t0)(const SpawnPoint*);
    typedef void (QObject::*om2_t0)(const SpawnPoint*);
    typedef void (SpawnMonitor::*m2_t1)();
    typedef void (QObject::*om2_t1)();
    m2_t0 v2_0 = &SpawnMonitor::newSpawnPoint;
    om2_t0 ov2_0 = (om2_t0)v2_0;
    m2_t1 v2_1 = &SpawnMonitor::clearSpawnPoints;
    om2_t1 ov2_1 = (om2_t1)v2_1;
    QMetaData *signal_tbl = QMetaObject::new_metadata(2);
    signal_tbl[0].name = "newSpawnPoint(const SpawnPoint*)";
    signal_tbl[0].ptr = (QMember)ov2_0;
    signal_tbl[1].name = "clearSpawnPoints()";
    signal_tbl[1].ptr = (QMember)ov2_1;
    metaObj = QMetaObject::new_metaobject(
	"SpawnMonitor", "QObject",
	slot_tbl, 6,
	signal_tbl, 2,
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

// SIGNAL newSpawnPoint
void SpawnMonitor::newSpawnPoint( const SpawnPoint* t0 )
{
    // No builtin function for signal parameter type const SpawnPoint*
    QConnectionList *clist = receivers("newSpawnPoint(const SpawnPoint*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const SpawnPoint*);
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

// SIGNAL clearSpawnPoints
void SpawnMonitor::clearSpawnPoints()
{
    activate_signal( "clearSpawnPoints()" );
}
