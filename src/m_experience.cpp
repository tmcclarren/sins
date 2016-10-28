/****************************************************************************
** ExperienceWindow meta object code from reading C++ file 'experience.h'
**
** Created: Fri Sep 28 13:00:12 2001
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.1   edited 2001-04-23 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "experience.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *ExperienceWindow::className() const
{
    return "ExperienceWindow";
}

QMetaObject *ExperienceWindow::metaObj = 0;

void ExperienceWindow::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(BaseWindow::className(), "BaseWindow") != 0 )
	badSuperclassWarning("ExperienceWindow","BaseWindow");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString ExperienceWindow::tr(const char* s)
{
    return qApp->translate( "ExperienceWindow", s, 0 );
}

QString ExperienceWindow::tr(const char* s, const char * c)
{
    return qApp->translate( "ExperienceWindow", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* ExperienceWindow::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) BaseWindow::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (ExperienceWindow::*m1_t0)();
    typedef void (QObject::*om1_t0)();
    typedef void (ExperienceWindow::*m1_t1)();
    typedef void (QObject::*om1_t1)();
    typedef void (ExperienceWindow::*m1_t2)();
    typedef void (QObject::*om1_t2)();
    typedef void (ExperienceWindow::*m1_t3)();
    typedef void (QObject::*om1_t3)();
    typedef void (ExperienceWindow::*m1_t4)();
    typedef void (QObject::*om1_t4)();
    typedef void (ExperienceWindow::*m1_t5)();
    typedef void (QObject::*om1_t5)();
    typedef void (ExperienceWindow::*m1_t6)();
    typedef void (QObject::*om1_t6)();
    typedef void (ExperienceWindow::*m1_t7)();
    typedef void (QObject::*om1_t7)();
    typedef void (ExperienceWindow::*m1_t8)();
    typedef void (QObject::*om1_t8)();
    typedef void (ExperienceWindow::*m1_t9)();
    typedef void (QObject::*om1_t9)();
    typedef void (ExperienceWindow::*m1_t10)();
    typedef void (QObject::*om1_t10)();
    typedef void (ExperienceWindow::*m1_t11)();
    typedef void (QObject::*om1_t11)();
    typedef void (ExperienceWindow::*m1_t12)(const struct spawnKilledStruct*);
    typedef void (QObject::*om1_t12)(const struct spawnKilledStruct*);
    typedef void (ExperienceWindow::*m1_t13)(unsigned long,unsigned long,long);
    typedef void (QObject::*om1_t13)(unsigned long,unsigned long,long);
    m1_t0 v1_0 = &ExperienceWindow::updateAverage;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &ExperienceWindow::viewRatePerHour;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &ExperienceWindow::viewRatePerMinute;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    m1_t3 v1_3 = &ExperienceWindow::viewAll;
    om1_t3 ov1_3 = (om1_t3)v1_3;
    m1_t4 v1_4 = &ExperienceWindow::view15Minutes;
    om1_t4 ov1_4 = (om1_t4)v1_4;
    m1_t5 v1_5 = &ExperienceWindow::view30Minutes;
    om1_t5 ov1_5 = (om1_t5)v1_5;
    m1_t6 v1_6 = &ExperienceWindow::view60Minutes;
    om1_t6 ov1_6 = (om1_t6)v1_6;
    m1_t7 v1_7 = &ExperienceWindow::viewClear;
    om1_t7 ov1_7 = (om1_t7)v1_7;
    m1_t8 v1_8 = &ExperienceWindow::calcZEMNextKill;
    om1_t8 ov1_8 = (om1_t8)v1_8;
    m1_t9 v1_9 = &ExperienceWindow::viewZEMraw;
    om1_t9 ov1_9 = (om1_t9)v1_9;
    m1_t10 v1_10 = &ExperienceWindow::viewZEMpercent;
    om1_t10 ov1_10 = (om1_t10)v1_10;
    m1_t11 v1_11 = &ExperienceWindow::viewZEMcalculated;
    om1_t11 ov1_11 = (om1_t11)v1_11;
    m1_t12 v1_12 = &ExperienceWindow::handleCorpse;
    om1_t12 ov1_12 = (om1_t12)v1_12;
    m1_t13 v1_13 = &ExperienceWindow::expChangedInt;
    om1_t13 ov1_13 = (om1_t13)v1_13;
    QMetaData *slot_tbl = QMetaObject::new_metadata(14);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(14);
    slot_tbl[0].name = "updateAverage()";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    slot_tbl[1].name = "viewRatePerHour()";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Public;
    slot_tbl[2].name = "viewRatePerMinute()";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Public;
    slot_tbl[3].name = "viewAll()";
    slot_tbl[3].ptr = (QMember)ov1_3;
    slot_tbl_access[3] = QMetaData::Public;
    slot_tbl[4].name = "view15Minutes()";
    slot_tbl[4].ptr = (QMember)ov1_4;
    slot_tbl_access[4] = QMetaData::Public;
    slot_tbl[5].name = "view30Minutes()";
    slot_tbl[5].ptr = (QMember)ov1_5;
    slot_tbl_access[5] = QMetaData::Public;
    slot_tbl[6].name = "view60Minutes()";
    slot_tbl[6].ptr = (QMember)ov1_6;
    slot_tbl_access[6] = QMetaData::Public;
    slot_tbl[7].name = "viewClear()";
    slot_tbl[7].ptr = (QMember)ov1_7;
    slot_tbl_access[7] = QMetaData::Public;
    slot_tbl[8].name = "calcZEMNextKill()";
    slot_tbl[8].ptr = (QMember)ov1_8;
    slot_tbl_access[8] = QMetaData::Public;
    slot_tbl[9].name = "viewZEMraw()";
    slot_tbl[9].ptr = (QMember)ov1_9;
    slot_tbl_access[9] = QMetaData::Public;
    slot_tbl[10].name = "viewZEMpercent()";
    slot_tbl[10].ptr = (QMember)ov1_10;
    slot_tbl_access[10] = QMetaData::Public;
    slot_tbl[11].name = "viewZEMcalculated()";
    slot_tbl[11].ptr = (QMember)ov1_11;
    slot_tbl_access[11] = QMetaData::Public;
    slot_tbl[12].name = "handleCorpse(const struct spawnKilledStruct*)";
    slot_tbl[12].ptr = (QMember)ov1_12;
    slot_tbl_access[12] = QMetaData::Public;
    slot_tbl[13].name = "expChangedInt(unsigned long,unsigned long,long)";
    slot_tbl[13].ptr = (QMember)ov1_13;
    slot_tbl_access[13] = QMetaData::Public;
    metaObj = QMetaObject::new_metaobject(
	"ExperienceWindow", "BaseWindow",
	slot_tbl, 14,
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
