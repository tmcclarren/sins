/****************************************************************************
** SkillListView meta object code from reading C++ file 'skilllist.h'
**
** Created: Wed Sep 26 11:33:33 2001
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.1   edited 2001-04-23 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "skilllist.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *SkillListView::className() const
{
    return "SkillListView";
}

QMetaObject *SkillListView::metaObj = 0;

void SkillListView::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(BaseListView::className(), "BaseListView") != 0 )
	badSuperclassWarning("SkillListView","BaseListView");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString SkillListView::tr(const char* s)
{
    return qApp->translate( "SkillListView", s, 0 );
}

QString SkillListView::tr(const char* s, const char * c)
{
    return qApp->translate( "SkillListView", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* SkillListView::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) BaseListView::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (SkillListView::*m1_t0)(int,int);
    typedef void (QObject::*om1_t0)(int,int);
    typedef void (SkillListView::*m1_t1)(int,int);
    typedef void (QObject::*om1_t1)(int,int);
    m1_t0 v1_0 = &SkillListView::addSkill;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &SkillListView::changeSkill;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    QMetaData *slot_tbl = QMetaObject::new_metadata(2);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(2);
    slot_tbl[0].name = "addSkill(int,int)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    slot_tbl[1].name = "changeSkill(int,int)";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Public;
    metaObj = QMetaObject::new_metaobject(
	"SkillListView", "BaseListView",
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


const char *SkillWindow::className() const
{
    return "SkillWindow";
}

QMetaObject *SkillWindow::metaObj = 0;

void SkillWindow::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(BaseWindow::className(), "BaseWindow") != 0 )
	badSuperclassWarning("SkillWindow","BaseWindow");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString SkillWindow::tr(const char* s)
{
    return qApp->translate( "SkillWindow", s, 0 );
}

QString SkillWindow::tr(const char* s, const char * c)
{
    return qApp->translate( "SkillWindow", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* SkillWindow::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) BaseWindow::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    QMetaData::Access *slot_tbl_access = 0;
    metaObj = QMetaObject::new_metaobject(
	"SkillWindow", "BaseWindow",
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
