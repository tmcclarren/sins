/****************************************************************************
** BaseListView meta object code from reading C++ file 'baselistview.h'
**
** Created: Fri Sep 28 12:58:35 2001
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.1   edited 2001-04-23 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "baselistview.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *BaseListView::className() const
{
    return "BaseListView";
}

QMetaObject *BaseListView::metaObj = 0;

void BaseListView::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QListView::className(), "QListView") != 0 )
	badSuperclassWarning("BaseListView","QListView");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString BaseListView::tr(const char* s)
{
    return qApp->translate( "BaseListView", s, 0 );
}

QString BaseListView::tr(const char* s, const char * c)
{
    return qApp->translate( "BaseListView", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* BaseListView::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QListView::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    QMetaData::Access *slot_tbl_access = 0;
    metaObj = QMetaObject::new_metaobject(
	"BaseListView", "QListView",
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
