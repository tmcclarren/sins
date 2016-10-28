/****************************************************************************
** LineDlg meta object code from reading C++ file 'map.h'
**
** Created: Fri Sep 28 13:25:38 2001
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.1   edited 2001-04-23 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "map.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *LineDlg::className() const
{
    return "LineDlg";
}

QMetaObject *LineDlg::metaObj = 0;

void LineDlg::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QDialog::className(), "QDialog") != 0 )
	badSuperclassWarning("LineDlg","QDialog");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString LineDlg::tr(const char* s)
{
    return qApp->translate( "LineDlg", s, 0 );
}

QString LineDlg::tr(const char* s, const char * c)
{
    return qApp->translate( "LineDlg", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* LineDlg::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QDialog::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (LineDlg::*m1_t0)(const QString&);
    typedef void (QObject::*om1_t0)(const QString&);
    m1_t0 v1_0 = &LineDlg::changeColor;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    QMetaData *slot_tbl = QMetaObject::new_metadata(1);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(1);
    slot_tbl[0].name = "changeColor(const QString&)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    metaObj = QMetaObject::new_metaobject(
	"LineDlg", "QDialog",
	slot_tbl, 1,
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


const char *DepthSlider::className() const
{
    return "DepthSlider";
}

QMetaObject *DepthSlider::metaObj = 0;

void DepthSlider::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QSlider::className(), "QSlider") != 0 )
	badSuperclassWarning("DepthSlider","QSlider");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString DepthSlider::tr(const char* s)
{
    return qApp->translate( "DepthSlider", s, 0 );
}

QString DepthSlider::tr(const char* s, const char * c)
{
    return qApp->translate( "DepthSlider", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* DepthSlider::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QSlider::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    QMetaData::Access *slot_tbl_access = 0;
    metaObj = QMetaObject::new_metaobject(
	"DepthSlider", "QSlider",
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


const char *DepthControlBox::className() const
{
    return "DepthControlBox";
}

QMetaObject *DepthControlBox::metaObj = 0;

void DepthControlBox::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QVBox::className(), "QVBox") != 0 )
	badSuperclassWarning("DepthControlBox","QVBox");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString DepthControlBox::tr(const char* s)
{
    return qApp->translate( "DepthControlBox", s, 0 );
}

QString DepthControlBox::tr(const char* s, const char * c)
{
    return qApp->translate( "DepthControlBox", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* DepthControlBox::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QVBox::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (DepthControlBox::*m1_t0)(int);
    typedef void (QObject::*om1_t0)(int);
    typedef void (DepthControlBox::*m1_t1)(int);
    typedef void (QObject::*om1_t1)(int);
    typedef void (DepthControlBox::*m1_t2)(int);
    typedef void (QObject::*om1_t2)(int);
    typedef void (DepthControlBox::*m1_t3)(int,int);
    typedef void (QObject::*om1_t3)(int,int);
    typedef void (DepthControlBox::*m1_t4)();
    typedef void (QObject::*om1_t4)();
    typedef int (DepthControlBox::*m1_t5)();
    typedef int (QObject::*om1_t5)();
    typedef int (DepthControlBox::*m1_t6)();
    typedef int (QObject::*om1_t6)();
    typedef void (DepthControlBox::*m1_t7)(const QString&);
    typedef void (QObject::*om1_t7)(const QString&);
    typedef void (DepthControlBox::*m1_t8)();
    typedef void (QObject::*om1_t8)();
    typedef void (DepthControlBox::*m1_t9)(int);
    typedef void (QObject::*om1_t9)(int);
    typedef void (DepthControlBox::*m1_t10)(int);
    typedef void (QObject::*om1_t10)(int);
    m1_t0 v1_0 = &DepthControlBox::updateZPos;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &DepthControlBox::setFloor;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &DepthControlBox::setCeiling;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    m1_t3 v1_3 = &DepthControlBox::setRange;
    om1_t3 ov1_3 = (om1_t3)v1_3;
    m1_t4 v1_4 = &DepthControlBox::resetControls;
    om1_t4 ov1_4 = (om1_t4)v1_4;
    m1_t5 v1_5 = &DepthControlBox::getFloor;
    om1_t5 ov1_5 = (om1_t5)v1_5;
    m1_t6 v1_6 = &DepthControlBox::getCeiling;
    om1_t6 ov1_6 = (om1_t6)v1_6;
    m1_t7 v1_7 = &DepthControlBox::zoneEnd;
    om1_t7 ov1_7 = (om1_t7)v1_7;
    m1_t8 v1_8 = &DepthControlBox::mapLoaded;
    om1_t8 ov1_8 = (om1_t8)v1_8;
    m1_t9 v1_9 = &DepthControlBox::__setFloor;
    om1_t9 ov1_9 = (om1_t9)v1_9;
    m1_t10 v1_10 = &DepthControlBox::__setCeiling;
    om1_t10 ov1_10 = (om1_t10)v1_10;
    QMetaData *slot_tbl = QMetaObject::new_metadata(11);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(11);
    slot_tbl[0].name = "updateZPos(int)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    slot_tbl[1].name = "setFloor(int)";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Public;
    slot_tbl[2].name = "setCeiling(int)";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Public;
    slot_tbl[3].name = "setRange(int,int)";
    slot_tbl[3].ptr = (QMember)ov1_3;
    slot_tbl_access[3] = QMetaData::Public;
    slot_tbl[4].name = "resetControls()";
    slot_tbl[4].ptr = (QMember)ov1_4;
    slot_tbl_access[4] = QMetaData::Public;
    slot_tbl[5].name = "getFloor()";
    slot_tbl[5].ptr = (QMember)ov1_5;
    slot_tbl_access[5] = QMetaData::Public;
    slot_tbl[6].name = "getCeiling()";
    slot_tbl[6].ptr = (QMember)ov1_6;
    slot_tbl_access[6] = QMetaData::Public;
    slot_tbl[7].name = "zoneEnd(const QString&)";
    slot_tbl[7].ptr = (QMember)ov1_7;
    slot_tbl_access[7] = QMetaData::Public;
    slot_tbl[8].name = "mapLoaded()";
    slot_tbl[8].ptr = (QMember)ov1_8;
    slot_tbl_access[8] = QMetaData::Public;
    slot_tbl[9].name = "__setFloor(int)";
    slot_tbl[9].ptr = (QMember)ov1_9;
    slot_tbl_access[9] = QMetaData::Protected;
    slot_tbl[10].name = "__setCeiling(int)";
    slot_tbl[10].ptr = (QMember)ov1_10;
    slot_tbl_access[10] = QMetaData::Protected;
    typedef void (DepthControlBox::*m2_t0)(int);
    typedef void (QObject::*om2_t0)(int);
    typedef void (DepthControlBox::*m2_t1)(int);
    typedef void (QObject::*om2_t1)(int);
    m2_t0 v2_0 = &DepthControlBox::floorChanged;
    om2_t0 ov2_0 = (om2_t0)v2_0;
    m2_t1 v2_1 = &DepthControlBox::ceilingChanged;
    om2_t1 ov2_1 = (om2_t1)v2_1;
    QMetaData *signal_tbl = QMetaObject::new_metadata(2);
    signal_tbl[0].name = "floorChanged(int)";
    signal_tbl[0].ptr = (QMember)ov2_0;
    signal_tbl[1].name = "ceilingChanged(int)";
    signal_tbl[1].ptr = (QMember)ov2_1;
    metaObj = QMetaObject::new_metaobject(
	"DepthControlBox", "QVBox",
	slot_tbl, 11,
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

// SIGNAL floorChanged
void DepthControlBox::floorChanged( int t0 )
{
    activate_signal( "floorChanged(int)", t0 );
}

// SIGNAL ceilingChanged
void DepthControlBox::ceilingChanged( int t0 )
{
    activate_signal( "ceilingChanged(int)", t0 );
}


const char *ZoomButton::className() const
{
    return "ZoomButton";
}

QMetaObject *ZoomButton::metaObj = 0;

void ZoomButton::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QPushButton::className(), "QPushButton") != 0 )
	badSuperclassWarning("ZoomButton","QPushButton");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString ZoomButton::tr(const char* s)
{
    return qApp->translate( "ZoomButton", s, 0 );
}

QString ZoomButton::tr(const char* s, const char * c)
{
    return qApp->translate( "ZoomButton", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* ZoomButton::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QPushButton::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    QMetaData::Access *slot_tbl_access = 0;
    metaObj = QMetaObject::new_metaobject(
	"ZoomButton", "QPushButton",
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


const char *ZoomControlBox::className() const
{
    return "ZoomControlBox";
}

QMetaObject *ZoomControlBox::metaObj = 0;

void ZoomControlBox::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QHBox::className(), "QHBox") != 0 )
	badSuperclassWarning("ZoomControlBox","QHBox");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString ZoomControlBox::tr(const char* s)
{
    return qApp->translate( "ZoomControlBox", s, 0 );
}

QString ZoomControlBox::tr(const char* s, const char * c)
{
    return qApp->translate( "ZoomControlBox", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* ZoomControlBox::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QHBox::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (ZoomControlBox::*m1_t0)(int);
    typedef void (QObject::*om1_t0)(int);
    m1_t0 v1_0 = &ZoomControlBox::zoomChanged;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    QMetaData *slot_tbl = QMetaObject::new_metadata(1);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(1);
    slot_tbl[0].name = "zoomChanged(int)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    metaObj = QMetaObject::new_metaobject(
	"ZoomControlBox", "QHBox",
	slot_tbl, 1,
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


const char *MapMgr::className() const
{
    return "MapMgr";
}

QMetaObject *MapMgr::metaObj = 0;

void MapMgr::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QObject::className(), "QObject") != 0 )
	badSuperclassWarning("MapMgr","QObject");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString MapMgr::tr(const char* s)
{
    return qApp->translate( "MapMgr", s, 0 );
}

QString MapMgr::tr(const char* s, const char * c)
{
    return qApp->translate( "MapMgr", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* MapMgr::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QObject::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (MapMgr::*m1_t0)();
    typedef void (QObject::*om1_t0)();
    typedef void (MapMgr::*m1_t1)(const QString&);
    typedef void (QObject::*om1_t1)(const QString&);
    typedef void (MapMgr::*m1_t2)(const QString&);
    typedef void (QObject::*om1_t2)(const QString&);
    typedef void (MapMgr::*m1_t3)();
    typedef void (QObject::*om1_t3)();
    typedef void (MapMgr::*m1_t4)();
    typedef void (QObject::*om1_t4)();
    typedef void (MapMgr::*m1_t5)();
    typedef void (QObject::*om1_t5)();
    typedef void (MapMgr::*m1_t6)();
    typedef void (QObject::*om1_t6)();
    typedef void (MapMgr::*m1_t7)();
    typedef void (QObject::*om1_t7)();
    typedef void (MapMgr::*m1_t8)(const QString&);
    typedef void (QObject::*om1_t8)(const QString&);
    typedef void (MapMgr::*m1_t9)();
    typedef void (QObject::*om1_t9)();
    typedef void (MapMgr::*m1_t10)();
    typedef void (QObject::*om1_t10)();
    typedef void (MapMgr::*m1_t11)(const QString&);
    typedef void (QObject::*om1_t11)(const QString&);
    typedef void (MapMgr::*m1_t12)(const QString&);
    typedef void (QObject::*om1_t12)(const QString&);
    typedef void (MapMgr::*m1_t13)(int);
    typedef void (QObject::*om1_t13)(int);
    typedef void (MapMgr::*m1_t14)(int);
    typedef void (QObject::*om1_t14)(int);
    m1_t0 v1_0 = &MapMgr::showLineDlg;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &MapMgr::setLineName;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &MapMgr::setLineColor;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    m1_t3 v1_3 = &MapMgr::addLocation;
    om1_t3 ov1_3 = (om1_t3)v1_3;
    m1_t4 v1_4 = &MapMgr::startLine;
    om1_t4 ov1_4 = (om1_t4)v1_4;
    m1_t5 v1_5 = &MapMgr::addLinePoint;
    om1_t5 ov1_5 = (om1_t5)v1_5;
    m1_t6 v1_6 = &MapMgr::delLinePoint;
    om1_t6 ov1_6 = (om1_t6)v1_6;
    m1_t7 v1_7 = &MapMgr::loadMap;
    om1_t7 ov1_7 = (om1_t7)v1_7;
    m1_t8 v1_8 = &MapMgr::loadFileMap;
    om1_t8 ov1_8 = (om1_t8)v1_8;
    m1_t9 v1_9 = &MapMgr::saveMap;
    om1_t9 ov1_9 = (om1_t9)v1_9;
    m1_t10 v1_10 = &MapMgr::zoneBegin;
    om1_t10 ov1_10 = (om1_t10)v1_10;
    m1_t11 v1_11 = &MapMgr::zoneEnd;
    om1_t11 ov1_11 = (om1_t11)v1_11;
    m1_t12 v1_12 = &MapMgr::zoneChanged;
    om1_t12 ov1_12 = (om1_t12)v1_12;
    m1_t13 v1_13 = &MapMgr::changeImageXTranslation;
    om1_t13 ov1_13 = (om1_t13)v1_13;
    m1_t14 v1_14 = &MapMgr::changeImageYTranslation;
    om1_t14 ov1_14 = (om1_t14)v1_14;
    QMetaData *slot_tbl = QMetaObject::new_metadata(15);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(15);
    slot_tbl[0].name = "showLineDlg()";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    slot_tbl[1].name = "setLineName(const QString&)";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Public;
    slot_tbl[2].name = "setLineColor(const QString&)";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Public;
    slot_tbl[3].name = "addLocation()";
    slot_tbl[3].ptr = (QMember)ov1_3;
    slot_tbl_access[3] = QMetaData::Public;
    slot_tbl[4].name = "startLine()";
    slot_tbl[4].ptr = (QMember)ov1_4;
    slot_tbl_access[4] = QMetaData::Public;
    slot_tbl[5].name = "addLinePoint()";
    slot_tbl[5].ptr = (QMember)ov1_5;
    slot_tbl_access[5] = QMetaData::Public;
    slot_tbl[6].name = "delLinePoint()";
    slot_tbl[6].ptr = (QMember)ov1_6;
    slot_tbl_access[6] = QMetaData::Public;
    slot_tbl[7].name = "loadMap()";
    slot_tbl[7].ptr = (QMember)ov1_7;
    slot_tbl_access[7] = QMetaData::Public;
    slot_tbl[8].name = "loadFileMap(const QString&)";
    slot_tbl[8].ptr = (QMember)ov1_8;
    slot_tbl_access[8] = QMetaData::Public;
    slot_tbl[9].name = "saveMap()";
    slot_tbl[9].ptr = (QMember)ov1_9;
    slot_tbl_access[9] = QMetaData::Public;
    slot_tbl[10].name = "zoneBegin()";
    slot_tbl[10].ptr = (QMember)ov1_10;
    slot_tbl_access[10] = QMetaData::Public;
    slot_tbl[11].name = "zoneEnd(const QString&)";
    slot_tbl[11].ptr = (QMember)ov1_11;
    slot_tbl_access[11] = QMetaData::Public;
    slot_tbl[12].name = "zoneChanged(const QString&)";
    slot_tbl[12].ptr = (QMember)ov1_12;
    slot_tbl_access[12] = QMetaData::Public;
    slot_tbl[13].name = "changeImageXTranslation(int)";
    slot_tbl[13].ptr = (QMember)ov1_13;
    slot_tbl_access[13] = QMetaData::Public;
    slot_tbl[14].name = "changeImageYTranslation(int)";
    slot_tbl[14].ptr = (QMember)ov1_14;
    slot_tbl_access[14] = QMetaData::Public;
    typedef void (MapMgr::*m2_t0)();
    typedef void (QObject::*om2_t0)();
    typedef void (MapMgr::*m2_t1)();
    typedef void (QObject::*om2_t1)();
    typedef void (MapMgr::*m2_t2)();
    typedef void (QObject::*om2_t2)();
    m2_t0 v2_0 = &MapMgr::mapUnloaded;
    om2_t0 ov2_0 = (om2_t0)v2_0;
    m2_t1 v2_1 = &MapMgr::mapLoaded;
    om2_t1 ov2_1 = (om2_t1)v2_1;
    m2_t2 v2_2 = &MapMgr::zoneLoaded;
    om2_t2 ov2_2 = (om2_t2)v2_2;
    QMetaData *signal_tbl = QMetaObject::new_metadata(3);
    signal_tbl[0].name = "mapUnloaded()";
    signal_tbl[0].ptr = (QMember)ov2_0;
    signal_tbl[1].name = "mapLoaded()";
    signal_tbl[1].ptr = (QMember)ov2_1;
    signal_tbl[2].name = "zoneLoaded()";
    signal_tbl[2].ptr = (QMember)ov2_2;
    metaObj = QMetaObject::new_metaobject(
	"MapMgr", "QObject",
	slot_tbl, 15,
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

// SIGNAL mapUnloaded
void MapMgr::mapUnloaded()
{
    activate_signal( "mapUnloaded()" );
}

// SIGNAL mapLoaded
void MapMgr::mapLoaded()
{
    activate_signal( "mapLoaded()" );
}

// SIGNAL zoneLoaded
void MapMgr::zoneLoaded()
{
    activate_signal( "zoneLoaded()" );
}


const char *MapWindow::className() const
{
    return "MapWindow";
}

QMetaObject *MapWindow::metaObj = 0;

void MapWindow::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(BaseWindow::className(), "BaseWindow") != 0 )
	badSuperclassWarning("MapWindow","BaseWindow");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString MapWindow::tr(const char* s)
{
    return qApp->translate( "MapWindow", s, 0 );
}

QString MapWindow::tr(const char* s, const char * c)
{
    return qApp->translate( "MapWindow", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* MapWindow::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) BaseWindow::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (MapWindow::*m1_t0)();
    typedef void (QObject::*om1_t0)();
    typedef void (MapWindow::*m1_t1)();
    typedef void (QObject::*om1_t1)();
    typedef void (MapWindow::*m1_t2)();
    typedef void (QObject::*om1_t2)();
    typedef void (MapWindow::*m1_t3)();
    typedef void (QObject::*om1_t3)();
    typedef void (MapWindow::*m1_t4)(int);
    typedef void (QObject::*om1_t4)(int);
    typedef Map *  (MapWindow::*m1_t5)();
    typedef Map *  (QObject::*om1_t5)();
    m1_t0 v1_0 = &MapWindow::mapLoaded;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &MapWindow::mapUnloaded;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &MapWindow::toggleControls;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    m1_t3 v1_3 = &MapWindow::toggleFilterControls;
    om1_t3 ov1_3 = (om1_t3)v1_3;
    m1_t4 v1_4 = &MapWindow::setZPos;
    om1_t4 ov1_4 = (om1_t4)v1_4;
    m1_t5 v1_5 = &MapWindow::getMap;
    om1_t5 ov1_5 = (om1_t5)v1_5;
    QMetaData *slot_tbl = QMetaObject::new_metadata(6);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(6);
    slot_tbl[0].name = "mapLoaded()";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    slot_tbl[1].name = "mapUnloaded()";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Public;
    slot_tbl[2].name = "toggleControls()";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Public;
    slot_tbl[3].name = "toggleFilterControls()";
    slot_tbl[3].ptr = (QMember)ov1_3;
    slot_tbl_access[3] = QMetaData::Public;
    slot_tbl[4].name = "setZPos(int)";
    slot_tbl[4].ptr = (QMember)ov1_4;
    slot_tbl_access[4] = QMetaData::Public;
    slot_tbl[5].name = "getMap()";
    slot_tbl[5].ptr = (QMember)ov1_5;
    slot_tbl_access[5] = QMetaData::Public;
    metaObj = QMetaObject::new_metaobject(
	"MapWindow", "BaseWindow",
	slot_tbl, 6,
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


const char *Map::className() const
{
    return "Map";
}

QMetaObject *Map::metaObj = 0;

void Map::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QWidget::className(), "QWidget") != 0 )
	badSuperclassWarning("Map","QWidget");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString Map::tr(const char* s)
{
    return qApp->translate( "Map", s, 0 );
}

QString Map::tr(const char* s, const char * c)
{
    return qApp->translate( "Map", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* Map::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QWidget::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef bool (Map::*m1_t0)(int);
    typedef bool (QObject::*om1_t0)(int);
    typedef void (Map::*m1_t1)(int);
    typedef void (QObject::*om1_t1)(int);
    typedef int (Map::*m1_t2)();
    typedef int (QObject::*om1_t2)();
    typedef void (Map::*m1_t3)();
    typedef void (QObject::*om1_t3)();
    typedef void (Map::*m1_t4)();
    typedef void (QObject::*om1_t4)();
    typedef void (Map::*m1_t5)(int);
    typedef void (QObject::*om1_t5)(int);
    typedef void (Map::*m1_t6)(int);
    typedef void (QObject::*om1_t6)(int);
    typedef void (Map::*m1_t7)(int,int);
    typedef void (QObject::*om1_t7)(int,int);
    typedef void (Map::*m1_t8)(int);
    typedef void (QObject::*om1_t8)(int);
    typedef void (Map::*m1_t9)(int);
    typedef void (QObject::*om1_t9)(int);
    typedef void (Map::*m1_t10)(int);
    typedef void (QObject::*om1_t10)(int);
    typedef void (Map::*m1_t11)(int);
    typedef void (QObject::*om1_t11)(int);
    typedef void (Map::*m1_t12)();
    typedef void (QObject::*om1_t12)();
    typedef void (Map::*m1_t13)();
    typedef void (QObject::*om1_t13)();
    typedef void (Map::*m1_t14)();
    typedef void (QObject::*om1_t14)();
    typedef void (Map::*m1_t15)();
    typedef void (QObject::*om1_t15)();
    typedef void (Map::*m1_t16)();
    typedef void (QObject::*om1_t16)();
    typedef void (Map::*m1_t17)();
    typedef void (QObject::*om1_t17)();
    typedef void (Map::*m1_t18)();
    typedef void (QObject::*om1_t18)();
    typedef void (Map::*m1_t19)();
    typedef void (QObject::*om1_t19)();
    typedef void (Map::*m1_t20)();
    typedef void (QObject::*om1_t20)();
    typedef void (Map::*m1_t21)();
    typedef void (QObject::*om1_t21)();
    typedef void (Map::*m1_t22)();
    typedef void (QObject::*om1_t22)();
    typedef void (Map::*m1_t23)();
    typedef void (QObject::*om1_t23)();
    typedef void (Map::*m1_t24)();
    typedef void (QObject::*om1_t24)();
    typedef void (Map::*m1_t25)();
    typedef void (QObject::*om1_t25)();
    typedef void (Map::*m1_t26)();
    typedef void (QObject::*om1_t26)();
    typedef void (Map::*m1_t27)();
    typedef void (QObject::*om1_t27)();
    typedef void (Map::*m1_t28)();
    typedef void (QObject::*om1_t28)();
    typedef void (Map::*m1_t29)();
    typedef void (QObject::*om1_t29)();
    typedef void (Map::*m1_t30)();
    typedef void (QObject::*om1_t30)();
    typedef void (Map::*m1_t31)();
    typedef void (QObject::*om1_t31)();
    typedef void (Map::*m1_t32)();
    typedef void (QObject::*om1_t32)();
    typedef void (Map::*m1_t33)();
    typedef void (QObject::*om1_t33)();
    typedef void (Map::*m1_t34)();
    typedef void (QObject::*om1_t34)();
    typedef void (Map::*m1_t35)();
    typedef void (QObject::*om1_t35)();
    typedef void (Map::*m1_t36)();
    typedef void (QObject::*om1_t36)();
    typedef void (Map::*m1_t37)();
    typedef void (QObject::*om1_t37)();
    typedef void (Map::*m1_t38)();
    typedef void (QObject::*om1_t38)();
    typedef void (Map::*m1_t39)();
    typedef void (QObject::*om1_t39)();
    typedef void (Map::*m1_t40)(Spawn*);
    typedef void (QObject::*om1_t40)(Spawn*);
    m1_t0 v1_0 = &Map::canZoom;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &Map::setZoom;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &Map::getZoom;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    m1_t3 v1_3 = &Map::zoomIn;
    om1_t3 ov1_3 = (om1_t3)v1_3;
    m1_t4 v1_4 = &Map::zoomOut;
    om1_t4 ov1_4 = (om1_t4)v1_4;
    m1_t5 v1_5 = &Map::setCeiling;
    om1_t5 ov1_5 = (om1_t5)v1_5;
    m1_t6 v1_6 = &Map::setFloor;
    om1_t6 ov1_6 = (om1_t6)v1_6;
    m1_t7 v1_7 = &Map::moveCenter;
    om1_t7 ov1_7 = (om1_t7)v1_7;
    m1_t8 v1_8 = &Map::decreasePlayerNeighborhood;
    om1_t8 ov1_8 = (om1_t8)v1_8;
    m1_t9 v1_9 = &Map::increasePlayerNeighborhood;
    om1_t9 ov1_9 = (om1_t9)v1_9;
    m1_t10 v1_10 = &Map::setPlayerNeighborhood;
    om1_t10 ov1_10 = (om1_t10)v1_10;
    m1_t11 v1_11 = &Map::setFPS;
    om1_t11 ov1_11 = (om1_t11)v1_11;
    m1_t12 v1_12 = &Map::refreshMap;
    om1_t12 ov1_12 = (om1_t12)v1_12;
    m1_t13 v1_13 = &Map::toggleLockControls;
    om1_t13 ov1_13 = (om1_t13)v1_13;
    m1_t14 v1_14 = &Map::toggleSpawnDepthFiltering;
    om1_t14 ov1_14 = (om1_t14)v1_14;
    m1_t15 v1_15 = &Map::toggleMapDepthFiltering;
    om1_t15 ov1_15 = (om1_t15)v1_15;
    m1_t16 v1_16 = &Map::toggleMapFade;
    om1_t16 ov1_16 = (om1_t16)v1_16;
    m1_t17 v1_17 = &Map::togglePopup;
    om1_t17 ov1_17 = (om1_t17)v1_17;
    m1_t18 v1_18 = &Map::toggleFiltered;
    om1_t18 ov1_18 = (om1_t18)v1_18;
    m1_t19 v1_19 = &Map::toggleVelocityLines;
    om1_t19 ov1_19 = (om1_t19)v1_19;
    m1_t20 v1_20 = &Map::toggleMapLines;
    om1_t20 ov1_20 = (om1_t20)v1_20;
    m1_t21 v1_21 = &Map::toggleAnimate;
    om1_t21 ov1_21 = (om1_t21)v1_21;
    m1_t22 v1_22 = &Map::togglePlayerView;
    om1_t22 ov1_22 = (om1_t22)v1_22;
    m1_t23 v1_23 = &Map::toggleGrid;
    om1_t23 ov1_23 = (om1_t23)v1_23;
    m1_t24 v1_24 = &Map::toggleLocations;
    om1_t24 ov1_24 = (om1_t24)v1_24;
    m1_t25 v1_25 = &Map::toggleDrops;
    om1_t25 ov1_25 = (om1_t25)v1_25;
    m1_t26 v1_26 = &Map::toggleCoins;
    om1_t26 ov1_26 = (om1_t26)v1_26;
    m1_t27 v1_27 = &Map::toggleSpawnPoints;
    om1_t27 ov1_27 = (om1_t27)v1_27;
    m1_t28 v1_28 = &Map::toggleSpawnNames;
    om1_t28 ov1_28 = (om1_t28)v1_28;
    m1_t29 v1_29 = &Map::toggleDebugInfo;
    om1_t29 ov1_29 = (om1_t29)v1_29;
    m1_t30 v1_30 = &Map::toggleBackgroundImage;
    om1_t30 ov1_30 = (om1_t30)v1_30;
    m1_t31 v1_31 = &Map::toggleBlinkAlerted;
    om1_t31 ov1_31 = (om1_t31)v1_31;
    m1_t32 v1_32 = &Map::toggleFocusOnPlayer;
    om1_t32 ov1_32 = (om1_t32)v1_32;
    m1_t33 v1_33 = &Map::setFocusOnSelection;
    om1_t33 ov1_33 = (om1_t33)v1_33;
    m1_t34 v1_34 = &Map::mapUnloaded;
    om1_t34 ov1_34 = (om1_t34)v1_34;
    m1_t35 v1_35 = &Map::mapLoaded;
    om1_t35 ov1_35 = (om1_t35)v1_35;
    m1_t36 v1_36 = &Map::zoneLoaded;
    om1_t36 ov1_36 = (om1_t36)v1_36;
    m1_t37 v1_37 = &Map::pickGridColor;
    om1_t37 ov1_37 = (om1_t37)v1_37;
    m1_t38 v1_38 = &Map::pickBackgroundColor;
    om1_t38 ov1_38 = (om1_t38)v1_38;
    m1_t39 v1_39 = &Map::pickFont;
    om1_t39 ov1_39 = (om1_t39)v1_39;
    m1_t40 v1_40 = &Map::deleteSpawn;
    om1_t40 ov1_40 = (om1_t40)v1_40;
    QMetaData *slot_tbl = QMetaObject::new_metadata(41);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(41);
    slot_tbl[0].name = "canZoom(int)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    slot_tbl[1].name = "setZoom(int)";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Public;
    slot_tbl[2].name = "getZoom()";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Public;
    slot_tbl[3].name = "zoomIn()";
    slot_tbl[3].ptr = (QMember)ov1_3;
    slot_tbl_access[3] = QMetaData::Public;
    slot_tbl[4].name = "zoomOut()";
    slot_tbl[4].ptr = (QMember)ov1_4;
    slot_tbl_access[4] = QMetaData::Public;
    slot_tbl[5].name = "setCeiling(int)";
    slot_tbl[5].ptr = (QMember)ov1_5;
    slot_tbl_access[5] = QMetaData::Public;
    slot_tbl[6].name = "setFloor(int)";
    slot_tbl[6].ptr = (QMember)ov1_6;
    slot_tbl_access[6] = QMetaData::Public;
    slot_tbl[7].name = "moveCenter(int,int)";
    slot_tbl[7].ptr = (QMember)ov1_7;
    slot_tbl_access[7] = QMetaData::Public;
    slot_tbl[8].name = "decreasePlayerNeighborhood(int)";
    slot_tbl[8].ptr = (QMember)ov1_8;
    slot_tbl_access[8] = QMetaData::Public;
    slot_tbl[9].name = "increasePlayerNeighborhood(int)";
    slot_tbl[9].ptr = (QMember)ov1_9;
    slot_tbl_access[9] = QMetaData::Public;
    slot_tbl[10].name = "setPlayerNeighborhood(int)";
    slot_tbl[10].ptr = (QMember)ov1_10;
    slot_tbl_access[10] = QMetaData::Public;
    slot_tbl[11].name = "setFPS(int)";
    slot_tbl[11].ptr = (QMember)ov1_11;
    slot_tbl_access[11] = QMetaData::Public;
    slot_tbl[12].name = "refreshMap()";
    slot_tbl[12].ptr = (QMember)ov1_12;
    slot_tbl_access[12] = QMetaData::Public;
    slot_tbl[13].name = "toggleLockControls()";
    slot_tbl[13].ptr = (QMember)ov1_13;
    slot_tbl_access[13] = QMetaData::Public;
    slot_tbl[14].name = "toggleSpawnDepthFiltering()";
    slot_tbl[14].ptr = (QMember)ov1_14;
    slot_tbl_access[14] = QMetaData::Public;
    slot_tbl[15].name = "toggleMapDepthFiltering()";
    slot_tbl[15].ptr = (QMember)ov1_15;
    slot_tbl_access[15] = QMetaData::Public;
    slot_tbl[16].name = "toggleMapFade()";
    slot_tbl[16].ptr = (QMember)ov1_16;
    slot_tbl_access[16] = QMetaData::Public;
    slot_tbl[17].name = "togglePopup()";
    slot_tbl[17].ptr = (QMember)ov1_17;
    slot_tbl_access[17] = QMetaData::Public;
    slot_tbl[18].name = "toggleFiltered()";
    slot_tbl[18].ptr = (QMember)ov1_18;
    slot_tbl_access[18] = QMetaData::Public;
    slot_tbl[19].name = "toggleVelocityLines()";
    slot_tbl[19].ptr = (QMember)ov1_19;
    slot_tbl_access[19] = QMetaData::Public;
    slot_tbl[20].name = "toggleMapLines()";
    slot_tbl[20].ptr = (QMember)ov1_20;
    slot_tbl_access[20] = QMetaData::Public;
    slot_tbl[21].name = "toggleAnimate()";
    slot_tbl[21].ptr = (QMember)ov1_21;
    slot_tbl_access[21] = QMetaData::Public;
    slot_tbl[22].name = "togglePlayerView()";
    slot_tbl[22].ptr = (QMember)ov1_22;
    slot_tbl_access[22] = QMetaData::Public;
    slot_tbl[23].name = "toggleGrid()";
    slot_tbl[23].ptr = (QMember)ov1_23;
    slot_tbl_access[23] = QMetaData::Public;
    slot_tbl[24].name = "toggleLocations()";
    slot_tbl[24].ptr = (QMember)ov1_24;
    slot_tbl_access[24] = QMetaData::Public;
    slot_tbl[25].name = "toggleDrops()";
    slot_tbl[25].ptr = (QMember)ov1_25;
    slot_tbl_access[25] = QMetaData::Public;
    slot_tbl[26].name = "toggleCoins()";
    slot_tbl[26].ptr = (QMember)ov1_26;
    slot_tbl_access[26] = QMetaData::Public;
    slot_tbl[27].name = "toggleSpawnPoints()";
    slot_tbl[27].ptr = (QMember)ov1_27;
    slot_tbl_access[27] = QMetaData::Public;
    slot_tbl[28].name = "toggleSpawnNames()";
    slot_tbl[28].ptr = (QMember)ov1_28;
    slot_tbl_access[28] = QMetaData::Public;
    slot_tbl[29].name = "toggleDebugInfo()";
    slot_tbl[29].ptr = (QMember)ov1_29;
    slot_tbl_access[29] = QMetaData::Public;
    slot_tbl[30].name = "toggleBackgroundImage()";
    slot_tbl[30].ptr = (QMember)ov1_30;
    slot_tbl_access[30] = QMetaData::Public;
    slot_tbl[31].name = "toggleBlinkAlerted()";
    slot_tbl[31].ptr = (QMember)ov1_31;
    slot_tbl_access[31] = QMetaData::Public;
    slot_tbl[32].name = "toggleFocusOnPlayer()";
    slot_tbl[32].ptr = (QMember)ov1_32;
    slot_tbl_access[32] = QMetaData::Public;
    slot_tbl[33].name = "setFocusOnSelection()";
    slot_tbl[33].ptr = (QMember)ov1_33;
    slot_tbl_access[33] = QMetaData::Public;
    slot_tbl[34].name = "mapUnloaded()";
    slot_tbl[34].ptr = (QMember)ov1_34;
    slot_tbl_access[34] = QMetaData::Public;
    slot_tbl[35].name = "mapLoaded()";
    slot_tbl[35].ptr = (QMember)ov1_35;
    slot_tbl_access[35] = QMetaData::Public;
    slot_tbl[36].name = "zoneLoaded()";
    slot_tbl[36].ptr = (QMember)ov1_36;
    slot_tbl_access[36] = QMetaData::Public;
    slot_tbl[37].name = "pickGridColor()";
    slot_tbl[37].ptr = (QMember)ov1_37;
    slot_tbl_access[37] = QMetaData::Public;
    slot_tbl[38].name = "pickBackgroundColor()";
    slot_tbl[38].ptr = (QMember)ov1_38;
    slot_tbl_access[38] = QMetaData::Public;
    slot_tbl[39].name = "pickFont()";
    slot_tbl[39].ptr = (QMember)ov1_39;
    slot_tbl_access[39] = QMetaData::Public;
    slot_tbl[40].name = "deleteSpawn(Spawn*)";
    slot_tbl[40].ptr = (QMember)ov1_40;
    slot_tbl_access[40] = QMetaData::Public;
    typedef void (Map::*m2_t0)(int);
    typedef void (QObject::*om2_t0)(int);
    m2_t0 v2_0 = &Map::zoomChanged;
    om2_t0 ov2_0 = (om2_t0)v2_0;
    QMetaData *signal_tbl = QMetaObject::new_metadata(1);
    signal_tbl[0].name = "zoomChanged(int)";
    signal_tbl[0].ptr = (QMember)ov2_0;
    metaObj = QMetaObject::new_metaobject(
	"Map", "QWidget",
	slot_tbl, 41,
	signal_tbl, 1,
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

// SIGNAL zoomChanged
void Map::zoomChanged( int t0 )
{
    activate_signal( "zoomChanged(int)", t0 );
}
