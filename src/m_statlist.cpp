/****************************************************************************
** StatListView meta object code from reading C++ file 'statlist.h'
**
** Created: Wed Sep 26 11:35:53 2001
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.1   edited 2001-04-23 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "statlist.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *StatListView::className() const
{
    return "StatListView";
}

QMetaObject *StatListView::metaObj = 0;

void StatListView::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(BaseListView::className(), "BaseListView") != 0 )
	badSuperclassWarning("StatListView","BaseListView");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString StatListView::tr(const char* s)
{
    return qApp->translate( "StatListView", s, 0 );
}

QString StatListView::tr(const char* s, const char * c)
{
    return qApp->translate( "StatListView", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* StatListView::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) BaseListView::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (StatListView::*m1_t0)(int,int,int);
    typedef void (QObject::*om1_t0)(int,int,int);
    typedef void (StatListView::*m1_t1)(int,int);
    typedef void (QObject::*om1_t1)(int,int);
    typedef void (StatListView::*m1_t2)(WORD,WORD);
    typedef void (QObject::*om1_t2)(WORD,WORD);
    typedef void (StatListView::*m1_t3)(int,int,int,int,int,int);
    typedef void (QObject::*om1_t3)(int,int,int,int,int,int);
    m1_t0 v1_0 = &StatListView::statChanged;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &StatListView::hpChanged;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &StatListView::manaChanged;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    m1_t3 v1_3 = &StatListView::stamChanged;
    om1_t3 ov1_3 = (om1_t3)v1_3;
    QMetaData *slot_tbl = QMetaObject::new_metadata(4);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(4);
    slot_tbl[0].name = "statChanged(int,int,int)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    slot_tbl[1].name = "hpChanged(int,int)";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Public;
    slot_tbl[2].name = "manaChanged(WORD,WORD)";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Public;
    slot_tbl[3].name = "stamChanged(int,int,int,int,int,int)";
    slot_tbl[3].ptr = (QMember)ov1_3;
    slot_tbl_access[3] = QMetaData::Public;
    metaObj = QMetaObject::new_metaobject(
	"StatListView", "BaseListView",
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


const char *StatWindow::className() const
{
    return "StatWindow";
}

QMetaObject *StatWindow::metaObj = 0;

void StatWindow::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(BaseWindow::className(), "BaseWindow") != 0 )
	badSuperclassWarning("StatWindow","BaseWindow");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString StatWindow::tr(const char* s)
{
    return qApp->translate( "StatWindow", s, 0 );
}

QString StatWindow::tr(const char* s, const char * c)
{
    return qApp->translate( "StatWindow", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* StatWindow::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) BaseWindow::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    QMetaData::Access *slot_tbl_access = 0;
    metaObj = QMetaObject::new_metaobject(
	"StatWindow", "BaseWindow",
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
