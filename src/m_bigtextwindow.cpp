/****************************************************************************
** BigTextWindow meta object code from reading C++ file 'bigtextwindow.h'
**
** Created: Fri Sep 28 12:58:58 2001
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.1   edited 2001-04-23 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "bigtextwindow.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *BigTextWindow::className() const
{
    return "BigTextWindow";
}

QMetaObject *BigTextWindow::metaObj = 0;

void BigTextWindow::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(BaseWindow::className(), "BaseWindow") != 0 )
	badSuperclassWarning("BigTextWindow","BaseWindow");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString BigTextWindow::tr(const char* s)
{
    return qApp->translate( "BigTextWindow", s, 0 );
}

QString BigTextWindow::tr(const char* s, const char * c)
{
    return qApp->translate( "BigTextWindow", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* BigTextWindow::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) BaseWindow::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (BigTextWindow::*m1_t0)(const QString&);
    typedef void (QObject::*om1_t0)(const QString&);
    typedef void (BigTextWindow::*m1_t1)();
    typedef void (QObject::*om1_t1)();
    typedef void (BigTextWindow::*m1_t2)();
    typedef void (QObject::*om1_t2)();
    typedef void (BigTextWindow::*m1_t3)();
    typedef void (QObject::*om1_t3)();
    m1_t0 v1_0 = &BigTextWindow::newMessage;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &BigTextWindow::pickFont;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &BigTextWindow::pickColor;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    m1_t3 v1_3 = &BigTextWindow::pickBackground;
    om1_t3 ov1_3 = (om1_t3)v1_3;
    QMetaData *slot_tbl = QMetaObject::new_metadata(4);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(4);
    slot_tbl[0].name = "newMessage(const QString&)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    slot_tbl[1].name = "pickFont()";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Public;
    slot_tbl[2].name = "pickColor()";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Public;
    slot_tbl[3].name = "pickBackground()";
    slot_tbl[3].ptr = (QMember)ov1_3;
    slot_tbl_access[3] = QMetaData::Public;
    metaObj = QMetaObject::new_metaobject(
	"BigTextWindow", "BaseWindow",
	slot_tbl, 4,
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
