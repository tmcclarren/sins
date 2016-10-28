/****************************************************************************
** CategoryMgr meta object code from reading C++ file 'category.h'
**
** Created: Fri Sep 28 12:59:12 2001
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.1   edited 2001-04-23 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "category.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *CategoryMgr::className() const
{
    return "CategoryMgr";
}

QMetaObject *CategoryMgr::metaObj = 0;

void CategoryMgr::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QComboBox::className(), "QComboBox") != 0 )
	badSuperclassWarning("CategoryMgr","QComboBox");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString CategoryMgr::tr(const char* s)
{
    return qApp->translate( "CategoryMgr", s, 0 );
}

QString CategoryMgr::tr(const char* s, const char * c)
{
    return qApp->translate( "CategoryMgr", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* CategoryMgr::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QComboBox::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (CategoryMgr::*m1_t0)(int);
    typedef void (QObject::*om1_t0)(int);
    m1_t0 v1_0 = &CategoryMgr::handleActivate;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    QMetaData *slot_tbl = QMetaObject::new_metadata(1);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(1);
    slot_tbl[0].name = "handleActivate(int)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Protected;
    typedef void (CategoryMgr::*m2_t0)();
    typedef void (QObject::*om2_t0)();
    typedef void (CategoryMgr::*m2_t1)();
    typedef void (QObject::*om2_t1)();
    m2_t0 v2_0 = &CategoryMgr::categoriesChanged;
    om2_t0 ov2_0 = (om2_t0)v2_0;
    m2_t1 v2_1 = &CategoryMgr::categoryChanged;
    om2_t1 ov2_1 = (om2_t1)v2_1;
    QMetaData *signal_tbl = QMetaObject::new_metadata(2);
    signal_tbl[0].name = "categoriesChanged()";
    signal_tbl[0].ptr = (QMember)ov2_0;
    signal_tbl[1].name = "categoryChanged()";
    signal_tbl[1].ptr = (QMember)ov2_1;
    metaObj = QMetaObject::new_metaobject(
	"CategoryMgr", "QComboBox",
	slot_tbl, 1,
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

// SIGNAL categoriesChanged
void CategoryMgr::categoriesChanged()
{
    activate_signal( "categoriesChanged()" );
}

// SIGNAL categoryChanged
void CategoryMgr::categoryChanged()
{
    activate_signal( "categoryChanged()" );
}
