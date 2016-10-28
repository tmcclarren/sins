/****************************************************************************
** SpawnListView meta object code from reading C++ file 'spawnlist.h'
**
** Created: Fri Sep 28 13:04:43 2001
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.1   edited 2001-04-23 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "spawnlist.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *SpawnListView::className() const
{
    return "SpawnListView";
}

QMetaObject *SpawnListView::metaObj = 0;

void SpawnListView::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(BaseListView::className(), "BaseListView") != 0 )
	badSuperclassWarning("SpawnListView","BaseListView");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString SpawnListView::tr(const char* s)
{
    return qApp->translate( "SpawnListView", s, 0 );
}

QString SpawnListView::tr(const char* s, const char * c)
{
    return qApp->translate( "SpawnListView", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* SpawnListView::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) BaseListView::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (SpawnListView::*m1_t0)();
    typedef void (QObject::*om1_t0)();
    typedef void (SpawnListView::*m1_t1)();
    typedef void (QObject::*om1_t1)();
    typedef void (SpawnListView::*m1_t2)();
    typedef void (QObject::*om1_t2)();
    typedef void (SpawnListView::*m1_t3)();
    typedef void (QObject::*om1_t3)();
    typedef void (SpawnListView::*m1_t4)(Spawn*);
    typedef void (QObject::*om1_t4)(Spawn*);
    typedef void (SpawnListView::*m1_t5)(Spawn*);
    typedef void (QObject::*om1_t5)(Spawn*);
    typedef void (SpawnListView::*m1_t6)(Spawn*);
    typedef void (QObject::*om1_t6)(Spawn*);
    typedef void (SpawnListView::*m1_t7)(Spawn*);
    typedef void (QObject::*om1_t7)(Spawn*);
    typedef void (SpawnListView::*m1_t8)(int);
    typedef void (QObject::*om1_t8)(int);
    typedef void (SpawnListView::*m1_t9)(Spawn*);
    typedef void (QObject::*om1_t9)(Spawn*);
    typedef void (SpawnListView::*m1_t10)();
    typedef void (QObject::*om1_t10)();
    typedef void (SpawnListView::*m1_t11)(const QString&);
    typedef void (QObject::*om1_t11)(const QString&);
    typedef void (SpawnListView::*m1_t12)(int);
    typedef void (QObject::*om1_t12)(int);
    typedef void (SpawnListView::*m1_t13)();
    typedef void (QObject::*om1_t13)();
    typedef void (SpawnListView::*m1_t14)(SpawnItem*);
    typedef void (QObject::*om1_t14)(SpawnItem*);
    typedef void (SpawnListView::*m1_t15)(QListViewItem*);
    typedef void (QObject::*om1_t15)(QListViewItem*);
    typedef void (SpawnListView::*m1_t16)();
    typedef void (QObject::*om1_t16)();
    typedef void (SpawnListView::*m1_t17)(QListViewItem*,const QPoint&,int);
    typedef void (QObject::*om1_t17)(QListViewItem*,const QPoint&,int);
    m1_t0 v1_0 = &SpawnListView::clear;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &SpawnListView::refilter;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &SpawnListView::resync;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    m1_t3 v1_3 = &SpawnListView::refresh;
    om1_t3 ov1_3 = (om1_t3)v1_3;
    m1_t4 v1_4 = &SpawnListView::addSpawn;
    om1_t4 ov1_4 = (om1_t4)v1_4;
    m1_t5 v1_5 = &SpawnListView::deleteSpawn;
    om1_t5 ov1_5 = (om1_t5)v1_5;
    m1_t6 v1_6 = &SpawnListView::killSpawn;
    om1_t6 ov1_6 = (om1_t6)v1_6;
    m1_t7 v1_7 = &SpawnListView::spawnChanged;
    om1_t7 ov1_7 = (om1_t7)v1_7;
    m1_t8 v1_8 = &SpawnListView::levelUp;
    om1_t8 ov1_8 = (om1_t8)v1_8;
    m1_t9 v1_9 = &SpawnListView::handleSelectItem;
    om1_t9 ov1_9 = (om1_t9)v1_9;
    m1_t10 v1_10 = &SpawnListView::categoryChanged;
    om1_t10 ov1_10 = (om1_t10)v1_10;
    m1_t11 v1_11 = &SpawnListView::zoneChanged;
    om1_t11 ov1_11 = (om1_t11)v1_11;
    m1_t12 v1_12 = &SpawnListView::setFPM;
    om1_t12 ov1_12 = (om1_t12)v1_12;
    m1_t13 v1_13 = &SpawnListView::toggleKeepSelectedVisible;
    om1_t13 ov1_13 = (om1_t13)v1_13;
    m1_t14 v1_14 = &SpawnListView::deletingSpawnItem;
    om1_t14 ov1_14 = (om1_t14)v1_14;
    m1_t15 v1_15 = &SpawnListView::handleSelectItem;
    om1_t15 ov1_15 = (om1_t15)v1_15;
    m1_t16 v1_16 = &SpawnListView::reallySelect;
    om1_t16 ov1_16 = (om1_t16)v1_16;
    m1_t17 v1_17 = &SpawnListView::spawnListRightButton;
    om1_t17 ov1_17 = (om1_t17)v1_17;
    QMetaData *slot_tbl = QMetaObject::new_metadata(18);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(18);
    slot_tbl[0].name = "clear()";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    slot_tbl[1].name = "refilter()";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Public;
    slot_tbl[2].name = "resync()";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Public;
    slot_tbl[3].name = "refresh()";
    slot_tbl[3].ptr = (QMember)ov1_3;
    slot_tbl_access[3] = QMetaData::Public;
    slot_tbl[4].name = "addSpawn(Spawn*)";
    slot_tbl[4].ptr = (QMember)ov1_4;
    slot_tbl_access[4] = QMetaData::Public;
    slot_tbl[5].name = "deleteSpawn(Spawn*)";
    slot_tbl[5].ptr = (QMember)ov1_5;
    slot_tbl_access[5] = QMetaData::Public;
    slot_tbl[6].name = "killSpawn(Spawn*)";
    slot_tbl[6].ptr = (QMember)ov1_6;
    slot_tbl_access[6] = QMetaData::Public;
    slot_tbl[7].name = "spawnChanged(Spawn*)";
    slot_tbl[7].ptr = (QMember)ov1_7;
    slot_tbl_access[7] = QMetaData::Public;
    slot_tbl[8].name = "levelUp(int)";
    slot_tbl[8].ptr = (QMember)ov1_8;
    slot_tbl_access[8] = QMetaData::Public;
    slot_tbl[9].name = "handleSelectItem(Spawn*)";
    slot_tbl[9].ptr = (QMember)ov1_9;
    slot_tbl_access[9] = QMetaData::Public;
    slot_tbl[10].name = "categoryChanged()";
    slot_tbl[10].ptr = (QMember)ov1_10;
    slot_tbl_access[10] = QMetaData::Public;
    slot_tbl[11].name = "zoneChanged(const QString&)";
    slot_tbl[11].ptr = (QMember)ov1_11;
    slot_tbl_access[11] = QMetaData::Public;
    slot_tbl[12].name = "setFPM(int)";
    slot_tbl[12].ptr = (QMember)ov1_12;
    slot_tbl_access[12] = QMetaData::Public;
    slot_tbl[13].name = "toggleKeepSelectedVisible()";
    slot_tbl[13].ptr = (QMember)ov1_13;
    slot_tbl_access[13] = QMetaData::Public;
    slot_tbl[14].name = "deletingSpawnItem(SpawnItem*)";
    slot_tbl[14].ptr = (QMember)ov1_14;
    slot_tbl_access[14] = QMetaData::Protected;
    slot_tbl[15].name = "handleSelectItem(QListViewItem*)";
    slot_tbl[15].ptr = (QMember)ov1_15;
    slot_tbl_access[15] = QMetaData::Protected;
    slot_tbl[16].name = "reallySelect()";
    slot_tbl[16].ptr = (QMember)ov1_16;
    slot_tbl_access[16] = QMetaData::Protected;
    slot_tbl[17].name = "spawnListRightButton(QListViewItem*,const QPoint&,int)";
    slot_tbl[17].ptr = (QMember)ov1_17;
    slot_tbl_access[17] = QMetaData::Protected;
    metaObj = QMetaObject::new_metaobject(
	"SpawnListView", "BaseListView",
	slot_tbl, 18,
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
