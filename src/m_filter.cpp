/****************************************************************************
** FilterList meta object code from reading C++ file 'filter.h'
**
** Created: Fri Sep 28 13:00:38 2001
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.1   edited 2001-04-23 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "filter.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *FilterList::className() const
{
    return "FilterList";
}

QMetaObject *FilterList::metaObj = 0;

void FilterList::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QObject::className(), "QObject") != 0 )
	badSuperclassWarning("FilterList","QObject");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString FilterList::tr(const char* s)
{
    return qApp->translate( "FilterList", s, 0 );
}

QString FilterList::tr(const char* s, const char * c)
{
    return qApp->translate( "FilterList", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* FilterList::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QObject::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    QMetaData::Access *slot_tbl_access = 0;
    metaObj = QMetaObject::new_metaobject(
	"FilterList", "QObject",
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


const char *FilterMgr::className() const
{
    return "FilterMgr";
}

QMetaObject *FilterMgr::metaObj = 0;

void FilterMgr::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QObject::className(), "QObject") != 0 )
	badSuperclassWarning("FilterMgr","QObject");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString FilterMgr::tr(const char* s)
{
    return qApp->translate( "FilterMgr", s, 0 );
}

QString FilterMgr::tr(const char* s, const char * c)
{
    return qApp->translate( "FilterMgr", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* FilterMgr::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QObject::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (FilterMgr::*m1_t0)(Spawn*);
    typedef void (QObject::*om1_t0)(Spawn*);
    m1_t0 v1_0 = &FilterMgr::processSpawn;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    QMetaData *slot_tbl = QMetaObject::new_metadata(1);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(1);
    slot_tbl[0].name = "processSpawn(Spawn*)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    typedef void (FilterMgr::*m2_t0)();
    typedef void (QObject::*om2_t0)();
    m2_t0 v2_0 = &FilterMgr::filtersChanged;
    om2_t0 ov2_0 = (om2_t0)v2_0;
    QMetaData *signal_tbl = QMetaObject::new_metadata(1);
    signal_tbl[0].name = "filtersChanged()";
    signal_tbl[0].ptr = (QMember)ov2_0;
    metaObj = QMetaObject::new_metaobject(
	"FilterMgr", "QObject",
	slot_tbl, 1,
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

// SIGNAL filtersChanged
void FilterMgr::filtersChanged()
{
    activate_signal( "filtersChanged()" );
}


const char *Alerter::className() const
{
    return "Alerter";
}

QMetaObject *Alerter::metaObj = 0;

void Alerter::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(FilterMgr::className(), "FilterMgr") != 0 )
	badSuperclassWarning("Alerter","FilterMgr");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString Alerter::tr(const char* s)
{
    return qApp->translate( "Alerter", s, 0 );
}

QString Alerter::tr(const char* s, const char * c)
{
    return qApp->translate( "Alerter", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* Alerter::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) FilterMgr::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (Alerter::*m1_t0)(Spawn*);
    typedef void (QObject::*om1_t0)(Spawn*);
    typedef void (Alerter::*m1_t1)(Spawn*);
    typedef void (QObject::*om1_t1)(Spawn*);
    typedef void (Alerter::*m1_t2)(Spawn*);
    typedef void (QObject::*om1_t2)(Spawn*);
    m1_t0 v1_0 = &Alerter::addSpawn;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &Alerter::deleteSpawn;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &Alerter::killSpawn;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    QMetaData *slot_tbl = QMetaObject::new_metadata(3);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(3);
    slot_tbl[0].name = "addSpawn(Spawn*)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    slot_tbl[1].name = "deleteSpawn(Spawn*)";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Public;
    slot_tbl[2].name = "killSpawn(Spawn*)";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Public;
    metaObj = QMetaObject::new_metaobject(
	"Alerter", "FilterMgr",
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


const char *FilterDlg::className() const
{
    return "FilterDlg";
}

QMetaObject *FilterDlg::metaObj = 0;

void FilterDlg::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QDialog::className(), "QDialog") != 0 )
	badSuperclassWarning("FilterDlg","QDialog");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString FilterDlg::tr(const char* s)
{
    return qApp->translate( "FilterDlg", s, 0 );
}

QString FilterDlg::tr(const char* s, const char * c)
{
    return qApp->translate( "FilterDlg", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* FilterDlg::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QDialog::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (FilterDlg::*m1_t0)(const QString&);
    typedef void (QObject::*om1_t0)(const QString&);
    typedef void (FilterDlg::*m1_t1)();
    typedef void (QObject::*om1_t1)();
    typedef void (FilterDlg::*m1_t2)();
    typedef void (QObject::*om1_t2)();
    typedef void (FilterDlg::*m1_t3)();
    typedef void (QObject::*om1_t3)();
    typedef void (FilterDlg::*m1_t4)();
    typedef void (QObject::*om1_t4)();
    m1_t0 v1_0 = &FilterDlg::textChanged;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &FilterDlg::selectionChanged;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &FilterDlg::addFilter;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    m1_t3 v1_3 = &FilterDlg::deleteFilter;
    om1_t3 ov1_3 = (om1_t3)v1_3;
    m1_t4 v1_4 = &FilterDlg::toggleActive;
    om1_t4 ov1_4 = (om1_t4)v1_4;
    QMetaData *slot_tbl = QMetaObject::new_metadata(5);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(5);
    slot_tbl[0].name = "textChanged(const QString&)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    slot_tbl[1].name = "selectionChanged()";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Public;
    slot_tbl[2].name = "addFilter()";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Public;
    slot_tbl[3].name = "deleteFilter()";
    slot_tbl[3].ptr = (QMember)ov1_3;
    slot_tbl_access[3] = QMetaData::Public;
    slot_tbl[4].name = "toggleActive()";
    slot_tbl[4].ptr = (QMember)ov1_4;
    slot_tbl_access[4] = QMetaData::Public;
    metaObj = QMetaObject::new_metaobject(
	"FilterDlg", "QDialog",
	slot_tbl, 5,
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
