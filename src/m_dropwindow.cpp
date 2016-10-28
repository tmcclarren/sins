/****************************************************************************
** DropListView meta object code from reading C++ file 'dropwindow.h'
**
** Created: Fri Sep 28 12:59:50 2001
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.1   edited 2001-04-23 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "dropwindow.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *DropListView::className() const
{
    return "DropListView";
}

QMetaObject *DropListView::metaObj = 0;

void DropListView::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(BaseListView::className(), "BaseListView") != 0 )
	badSuperclassWarning("DropListView","BaseListView");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString DropListView::tr(const char* s)
{
    return qApp->translate( "DropListView", s, 0 );
}

QString DropListView::tr(const char* s, const char * c)
{
    return qApp->translate( "DropListView", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* DropListView::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) BaseListView::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (DropListView::*m1_t0)(const ItemStruct&);
    typedef void (QObject::*om1_t0)(const ItemStruct&);
    m1_t0 v1_0 = &DropListView::newItem;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    QMetaData *slot_tbl = QMetaObject::new_metadata(1);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(1);
    slot_tbl[0].name = "newItem(const ItemStruct&)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    metaObj = QMetaObject::new_metaobject(
	"DropListView", "BaseListView",
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


const char *DropWindow::className() const
{
    return "DropWindow";
}

QMetaObject *DropWindow::metaObj = 0;

void DropWindow::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(BaseWindow::className(), "BaseWindow") != 0 )
	badSuperclassWarning("DropWindow","BaseWindow");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString DropWindow::tr(const char* s)
{
    return qApp->translate( "DropWindow", s, 0 );
}

QString DropWindow::tr(const char* s, const char * c)
{
    return qApp->translate( "DropWindow", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* DropWindow::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) BaseWindow::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (DropWindow::*m1_t0)();
    typedef void (QObject::*om1_t0)();
    typedef void (DropWindow::*m1_t1)();
    typedef void (QObject::*om1_t1)();
    m1_t0 v1_0 = &DropWindow::selectionChanged;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &DropWindow::lookupItem;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    QMetaData *slot_tbl = QMetaObject::new_metadata(2);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(2);
    slot_tbl[0].name = "selectionChanged()";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    slot_tbl[1].name = "lookupItem()";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Public;
    metaObj = QMetaObject::new_metaobject(
	"DropWindow", "BaseWindow",
	slot_tbl, 2,
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
