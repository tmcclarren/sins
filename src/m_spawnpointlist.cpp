/****************************************************************************
** SpawnPointListView meta object code from reading C++ file 'spawnpointlist.h'
**
** Created: Fri Sep 28 13:05:16 2001
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.1   edited 2001-04-23 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "spawnpointlist.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *SpawnPointListView::className() const
{
    return "SpawnPointListView";
}

QMetaObject *SpawnPointListView::metaObj = 0;

void SpawnPointListView::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(BaseListView::className(), "BaseListView") != 0 )
	badSuperclassWarning("SpawnPointListView","BaseListView");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString SpawnPointListView::tr(const char* s)
{
    return qApp->translate( "SpawnPointListView", s, 0 );
}

QString SpawnPointListView::tr(const char* s, const char * c)
{
    return qApp->translate( "SpawnPointListView", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* SpawnPointListView::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) BaseListView::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (SpawnPointListView::*m1_t0)();
    typedef void (QObject::*om1_t0)();
    typedef void (SpawnPointListView::*m1_t1)(const SpawnPoint*);
    typedef void (QObject::*om1_t1)(const SpawnPoint*);
    typedef void (SpawnPointListView::*m1_t2)();
    typedef void (QObject::*om1_t2)();
    m1_t0 v1_0 = &SpawnPointListView::refresh;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &SpawnPointListView::newSpawnPoint;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &SpawnPointListView::clear;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    QMetaData *slot_tbl = QMetaObject::new_metadata(3);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(3);
    slot_tbl[0].name = "refresh()";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    slot_tbl[1].name = "newSpawnPoint(const SpawnPoint*)";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Public;
    slot_tbl[2].name = "clear()";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Public;
    metaObj = QMetaObject::new_metaobject(
	"SpawnPointListView", "BaseListView",
	slot_tbl, 3,
	0, 0,
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


const char *SpawnPointWindow::className() const
{
    return "SpawnPointWindow";
}

QMetaObject *SpawnPointWindow::metaObj = 0;

void SpawnPointWindow::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(BaseWindow::className(), "BaseWindow") != 0 )
	badSuperclassWarning("SpawnPointWindow","BaseWindow");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString SpawnPointWindow::tr(const char* s)
{
    return qApp->translate( "SpawnPointWindow", s, 0 );
}

QString SpawnPointWindow::tr(const char* s, const char * c)
{
    return qApp->translate( "SpawnPointWindow", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* SpawnPointWindow::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) BaseWindow::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    QMetaData::Access *slot_tbl_access = 0;
    metaObj = QMetaObject::new_metaobject(
	"SpawnPointWindow", "BaseWindow",
	0, 0,
	0, 0,
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
