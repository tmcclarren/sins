/****************************************************************************
** EQInterface meta object code from reading C++ file 'interface.h'
**
** Created: Fri Sep 28 13:17:18 2001
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.1   edited 2001-04-23 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "interface.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *EQInterface::className() const
{
    return "EQInterface";
}

QMetaObject *EQInterface::metaObj = 0;

void EQInterface::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QMainWindow::className(), "QMainWindow") != 0 )
	badSuperclassWarning("EQInterface","QMainWindow");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString EQInterface::tr(const char* s)
{
    return qApp->translate( "EQInterface", s, 0 );
}

QString EQInterface::tr(const char* s, const char * c)
{
    return qApp->translate( "EQInterface", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* EQInterface::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QMainWindow::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (EQInterface::*m1_t0)(const QString&,const QString&);
    typedef void (QObject::*om1_t0)(const QString&,const QString&);
    typedef void (EQInterface::*m1_t1)(const QString&);
    typedef void (QObject::*om1_t1)(const QString&);
    typedef void (EQInterface::*m1_t2)(const QString&,int);
    typedef void (QObject::*om1_t2)(const QString&,int);
    typedef void (EQInterface::*m1_t3)(int);
    typedef void (QObject::*om1_t3)(int);
    typedef void (EQInterface::*m1_t4)(int);
    typedef void (QObject::*om1_t4)(int);
    typedef void (EQInterface::*m1_t5)();
    typedef void (QObject::*om1_t5)();
    typedef void (EQInterface::*m1_t6)(const void*);
    typedef void (QObject::*om1_t6)(const void*);
    typedef void (EQInterface::*m1_t7)(const struct moneyUpdateStruct*);
    typedef void (QObject::*om1_t7)(const struct moneyUpdateStruct*);
    typedef void (EQInterface::*m1_t8)(const struct systemMessageStruct*);
    typedef void (QObject::*om1_t8)(const struct systemMessageStruct*);
    typedef void (EQInterface::*m1_t9)(const struct beginCastStruct*);
    typedef void (QObject::*om1_t9)(const struct beginCastStruct*);
    typedef void (EQInterface::*m1_t10)(const struct spMesgStruct*);
    typedef void (QObject::*om1_t10)(const struct spMesgStruct*);
    typedef void (EQInterface::*m1_t11)(const struct containerPlayerStruct*);
    typedef void (QObject::*om1_t11)(const struct containerPlayerStruct*);
    typedef void (EQInterface::*m1_t12)(const struct bookPlayerStruct*);
    typedef void (QObject::*om1_t12)(const struct bookPlayerStruct*);
    typedef void (EQInterface::*m1_t13)(const struct emoteTextStruct*);
    typedef void (QObject::*om1_t13)(const struct emoteTextStruct*);
    typedef void (EQInterface::*m1_t14)(const struct channelMessageStruct*);
    typedef void (QObject::*om1_t14)(const struct channelMessageStruct*);
    typedef void (EQInterface::*m1_t15)(const struct summonedItemStruct*);
    typedef void (QObject::*om1_t15)(const struct summonedItemStruct*);
    typedef void (EQInterface::*m1_t16)(const struct itemPlayerStruct*);
    typedef void (QObject::*om1_t16)(const struct itemPlayerStruct*);
    typedef void (EQInterface::*m1_t17)(const struct itemReceivedStruct*);
    typedef void (QObject::*om1_t17)(const struct itemReceivedStruct*);
    typedef void (EQInterface::*m1_t18)(const struct tradeItemStruct*);
    typedef void (QObject::*om1_t18)(const struct tradeItemStruct*);
    typedef void (EQInterface::*m1_t19)(const struct itemReceivedStruct*);
    typedef void (QObject::*om1_t19)(const struct itemReceivedStruct*);
    typedef void (EQInterface::*m1_t20)(const struct itemShopStruct*);
    typedef void (QObject::*om1_t20)(const struct itemShopStruct*);
    typedef void (EQInterface::*m1_t21)(const struct attack1Struct*);
    typedef void (QObject::*om1_t21)(const struct attack1Struct*);
    typedef void (EQInterface::*m1_t22)(const struct attack2Struct*);
    typedef void (QObject::*om1_t22)(const struct attack2Struct*);
    typedef void (EQInterface::*m1_t23)(const struct spawnHpUpdateStruct*);
    typedef void (QObject::*om1_t23)(const struct spawnHpUpdateStruct*);
    typedef void (EQInterface::*m1_t24)(const struct inspectingStruct*);
    typedef void (QObject::*om1_t24)(const struct inspectingStruct*);
    typedef void (EQInterface::*m1_t25)(const struct randomStruct*);
    typedef void (QObject::*om1_t25)(const struct randomStruct*);
    typedef void (EQInterface::*m1_t26)(const struct clientTargetStruct*);
    typedef void (QObject::*om1_t26)(const struct clientTargetStruct*);
    typedef void (EQInterface::*m1_t27)(const struct considerStruct*);
    typedef void (QObject::*om1_t27)(const struct considerStruct*);
    typedef void (EQInterface::*m1_t28)(const struct considerStruct*);
    typedef void (QObject::*om1_t28)(const struct considerStruct*);
    typedef void (EQInterface::*m1_t29)();
    typedef void (QObject::*om1_t29)();
    typedef void (EQInterface::*m1_t30)();
    typedef void (QObject::*om1_t30)();
    typedef void (EQInterface::*m1_t31)();
    typedef void (QObject::*om1_t31)();
    typedef void (EQInterface::*m1_t32)();
    typedef void (QObject::*om1_t32)();
    typedef void (EQInterface::*m1_t33)();
    typedef void (QObject::*om1_t33)();
    typedef void (EQInterface::*m1_t34)();
    typedef void (QObject::*om1_t34)();
    typedef void (EQInterface::*m1_t35)();
    typedef void (QObject::*om1_t35)();
    typedef void (EQInterface::*m1_t36)();
    typedef void (QObject::*om1_t36)();
    typedef void (EQInterface::*m1_t37)(int);
    typedef void (QObject::*om1_t37)(int);
    typedef void (EQInterface::*m1_t38)();
    typedef void (QObject::*om1_t38)();
    typedef void (EQInterface::*m1_t39)();
    typedef void (QObject::*om1_t39)();
    typedef void (EQInterface::*m1_t40)();
    typedef void (QObject::*om1_t40)();
    typedef void (EQInterface::*m1_t41)(bool);
    typedef void (QObject::*om1_t41)(bool);
    typedef void (EQInterface::*m1_t42)(int);
    typedef void (QObject::*om1_t42)(int);
    m1_t0 v1_0 = &EQInterface::captureTargetChanged;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &EQInterface::msgReceived;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &EQInterface::stsMessage;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    m1_t3 v1_3 = &EQInterface::numSpawns;
    om1_t3 ov1_3 = (om1_t3)v1_3;
    m1_t4 v1_4 = &EQInterface::numPacket;
    om1_t4 ov1_4 = (om1_t4)v1_4;
    m1_t5 v1_5 = &EQInterface::savePrefs;
    om1_t5 ov1_5 = (om1_t5)v1_5;
    m1_t6 v1_6 = &EQInterface::handleMoney;
    om1_t6 ov1_6 = (om1_t6)v1_6;
    m1_t7 v1_7 = &EQInterface::handleMoneyUpdate;
    om1_t7 ov1_7 = (om1_t7)v1_7;
    m1_t8 v1_8 = &EQInterface::handleSysMsg;
    om1_t8 ov1_8 = (om1_t8)v1_8;
    m1_t9 v1_9 = &EQInterface::handleBeginCast;
    om1_t9 ov1_9 = (om1_t9)v1_9;
    m1_t10 v1_10 = &EQInterface::handleSpecialMsg;
    om1_t10 ov1_10 = (om1_t10)v1_10;
    m1_t11 v1_11 = &EQInterface::handlePlayerCont;
    om1_t11 ov1_11 = (om1_t11)v1_11;
    m1_t12 v1_12 = &EQInterface::handlePlayerBook;
    om1_t12 ov1_12 = (om1_t12)v1_12;
    m1_t13 v1_13 = &EQInterface::handleEmote;
    om1_t13 ov1_13 = (om1_t13)v1_13;
    m1_t14 v1_14 = &EQInterface::handleChannelMsg;
    om1_t14 ov1_14 = (om1_t14)v1_14;
    m1_t15 v1_15 = &EQInterface::handleSummonedItem;
    om1_t15 ov1_15 = (om1_t15)v1_15;
    m1_t16 v1_16 = &EQInterface::handlePlayerItem;
    om1_t16 ov1_16 = (om1_t16)v1_16;
    m1_t17 v1_17 = &EQInterface::handleTradeItem;
    om1_t17 ov1_17 = (om1_t17)v1_17;
    m1_t18 v1_18 = &EQInterface::handleTradeItem2;
    om1_t18 ov1_18 = (om1_t18)v1_18;
    m1_t19 v1_19 = &EQInterface::handleCorpseItem;
    om1_t19 ov1_19 = (om1_t19)v1_19;
    m1_t20 v1_20 = &EQInterface::handleShopItem;
    om1_t20 ov1_20 = (om1_t20)v1_20;
    m1_t21 v1_21 = &EQInterface::handleAttack1;
    om1_t21 ov1_21 = (om1_t21)v1_21;
    m1_t22 v1_22 = &EQInterface::handleAttack2;
    om1_t22 ov1_22 = (om1_t22)v1_22;
    m1_t23 v1_23 = &EQInterface::handleHPUpdate;
    om1_t23 ov1_23 = (om1_t23)v1_23;
    m1_t24 v1_24 = &EQInterface::handleInspect;
    om1_t24 ov1_24 = (om1_t24)v1_24;
    m1_t25 v1_25 = &EQInterface::handleRandom;
    om1_t25 ov1_25 = (om1_t25)v1_25;
    m1_t26 v1_26 = &EQInterface::handleClientTarget;
    om1_t26 ov1_26 = (om1_t26)v1_26;
    m1_t27 v1_27 = &EQInterface::handleConsRequest;
    om1_t27 ov1_27 = (om1_t27)v1_27;
    m1_t28 v1_28 = &EQInterface::handleConsMessage;
    om1_t28 ov1_28 = (om1_t28)v1_28;
    m1_t29 v1_29 = &EQInterface::viewSpawnList;
    om1_t29 ov1_29 = (om1_t29)v1_29;
    m1_t30 v1_30 = &EQInterface::viewStats;
    om1_t30 ov1_30 = (om1_t30)v1_30;
    m1_t31 v1_31 = &EQInterface::viewSkills;
    om1_t31 ov1_31 = (om1_t31)v1_31;
    m1_t32 v1_32 = &EQInterface::viewCompass;
    om1_t32 ov1_32 = (om1_t32)v1_32;
    m1_t33 v1_33 = &EQInterface::viewExpWindow;
    om1_t33 ov1_33 = (om1_t33)v1_33;
    m1_t34 v1_34 = &EQInterface::viewBigTextWindow;
    om1_t34 ov1_34 = (om1_t34)v1_34;
    m1_t35 v1_35 = &EQInterface::viewDropWindow;
    om1_t35 ov1_35 = (om1_t35)v1_35;
    m1_t36 v1_36 = &EQInterface::viewSpawnPointWindow;
    om1_t36 ov1_36 = (om1_t36)v1_36;
    m1_t37 v1_37 = &EQInterface::openMapView;
    om1_t37 ov1_37 = (om1_t37)v1_37;
    m1_t38 v1_38 = &EQInterface::editFilters;
    om1_t38 ov1_38 = (om1_t38)v1_38;
    m1_t39 v1_39 = &EQInterface::editAlerts;
    om1_t39 ov1_39 = (om1_t39)v1_39;
    m1_t40 v1_40 = &EQInterface::editCategories;
    om1_t40 ov1_40 = (om1_t40)v1_40;
    m1_t41 v1_41 = &EQInterface::toggleRawDisplay;
    om1_t41 ov1_41 = (om1_t41)v1_41;
    m1_t42 v1_42 = &EQInterface::setSelectMode;
    om1_t42 ov1_42 = (om1_t42)v1_42;
    QMetaData *slot_tbl = QMetaObject::new_metadata(43);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(43);
    slot_tbl[0].name = "captureTargetChanged(const QString&,const QString&)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    slot_tbl[1].name = "msgReceived(const QString&)";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Public;
    slot_tbl[2].name = "stsMessage(const QString&,int)";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Public;
    slot_tbl[3].name = "numSpawns(int)";
    slot_tbl[3].ptr = (QMember)ov1_3;
    slot_tbl_access[3] = QMetaData::Public;
    slot_tbl[4].name = "numPacket(int)";
    slot_tbl[4].ptr = (QMember)ov1_4;
    slot_tbl_access[4] = QMetaData::Public;
    slot_tbl[5].name = "savePrefs()";
    slot_tbl[5].ptr = (QMember)ov1_5;
    slot_tbl_access[5] = QMetaData::Public;
    slot_tbl[6].name = "handleMoney(const void*)";
    slot_tbl[6].ptr = (QMember)ov1_6;
    slot_tbl_access[6] = QMetaData::Public;
    slot_tbl[7].name = "handleMoneyUpdate(const struct moneyUpdateStruct*)";
    slot_tbl[7].ptr = (QMember)ov1_7;
    slot_tbl_access[7] = QMetaData::Public;
    slot_tbl[8].name = "handleSysMsg(const struct systemMessageStruct*)";
    slot_tbl[8].ptr = (QMember)ov1_8;
    slot_tbl_access[8] = QMetaData::Public;
    slot_tbl[9].name = "handleBeginCast(const struct beginCastStruct*)";
    slot_tbl[9].ptr = (QMember)ov1_9;
    slot_tbl_access[9] = QMetaData::Public;
    slot_tbl[10].name = "handleSpecialMsg(const struct spMesgStruct*)";
    slot_tbl[10].ptr = (QMember)ov1_10;
    slot_tbl_access[10] = QMetaData::Public;
    slot_tbl[11].name = "handlePlayerCont(const struct containerPlayerStruct*)";
    slot_tbl[11].ptr = (QMember)ov1_11;
    slot_tbl_access[11] = QMetaData::Public;
    slot_tbl[12].name = "handlePlayerBook(const struct bookPlayerStruct*)";
    slot_tbl[12].ptr = (QMember)ov1_12;
    slot_tbl_access[12] = QMetaData::Public;
    slot_tbl[13].name = "handleEmote(const struct emoteTextStruct*)";
    slot_tbl[13].ptr = (QMember)ov1_13;
    slot_tbl_access[13] = QMetaData::Public;
    slot_tbl[14].name = "handleChannelMsg(const struct channelMessageStruct*)";
    slot_tbl[14].ptr = (QMember)ov1_14;
    slot_tbl_access[14] = QMetaData::Public;
    slot_tbl[15].name = "handleSummonedItem(const struct summonedItemStruct*)";
    slot_tbl[15].ptr = (QMember)ov1_15;
    slot_tbl_access[15] = QMetaData::Public;
    slot_tbl[16].name = "handlePlayerItem(const struct itemPlayerStruct*)";
    slot_tbl[16].ptr = (QMember)ov1_16;
    slot_tbl_access[16] = QMetaData::Public;
    slot_tbl[17].name = "handleTradeItem(const struct itemReceivedStruct*)";
    slot_tbl[17].ptr = (QMember)ov1_17;
    slot_tbl_access[17] = QMetaData::Public;
    slot_tbl[18].name = "handleTradeItem2(const struct tradeItemStruct*)";
    slot_tbl[18].ptr = (QMember)ov1_18;
    slot_tbl_access[18] = QMetaData::Public;
    slot_tbl[19].name = "handleCorpseItem(const struct itemReceivedStruct*)";
    slot_tbl[19].ptr = (QMember)ov1_19;
    slot_tbl_access[19] = QMetaData::Public;
    slot_tbl[20].name = "handleShopItem(const struct itemShopStruct*)";
    slot_tbl[20].ptr = (QMember)ov1_20;
    slot_tbl_access[20] = QMetaData::Public;
    slot_tbl[21].name = "handleAttack1(const struct attack1Struct*)";
    slot_tbl[21].ptr = (QMember)ov1_21;
    slot_tbl_access[21] = QMetaData::Public;
    slot_tbl[22].name = "handleAttack2(const struct attack2Struct*)";
    slot_tbl[22].ptr = (QMember)ov1_22;
    slot_tbl_access[22] = QMetaData::Public;
    slot_tbl[23].name = "handleHPUpdate(const struct spawnHpUpdateStruct*)";
    slot_tbl[23].ptr = (QMember)ov1_23;
    slot_tbl_access[23] = QMetaData::Public;
    slot_tbl[24].name = "handleInspect(const struct inspectingStruct*)";
    slot_tbl[24].ptr = (QMember)ov1_24;
    slot_tbl_access[24] = QMetaData::Public;
    slot_tbl[25].name = "handleRandom(const struct randomStruct*)";
    slot_tbl[25].ptr = (QMember)ov1_25;
    slot_tbl_access[25] = QMetaData::Public;
    slot_tbl[26].name = "handleClientTarget(const struct clientTargetStruct*)";
    slot_tbl[26].ptr = (QMember)ov1_26;
    slot_tbl_access[26] = QMetaData::Public;
    slot_tbl[27].name = "handleConsRequest(const struct considerStruct*)";
    slot_tbl[27].ptr = (QMember)ov1_27;
    slot_tbl_access[27] = QMetaData::Public;
    slot_tbl[28].name = "handleConsMessage(const struct considerStruct*)";
    slot_tbl[28].ptr = (QMember)ov1_28;
    slot_tbl_access[28] = QMetaData::Public;
    slot_tbl[29].name = "viewSpawnList()";
    slot_tbl[29].ptr = (QMember)ov1_29;
    slot_tbl_access[29] = QMetaData::Public;
    slot_tbl[30].name = "viewStats()";
    slot_tbl[30].ptr = (QMember)ov1_30;
    slot_tbl_access[30] = QMetaData::Public;
    slot_tbl[31].name = "viewSkills()";
    slot_tbl[31].ptr = (QMember)ov1_31;
    slot_tbl_access[31] = QMetaData::Public;
    slot_tbl[32].name = "viewCompass()";
    slot_tbl[32].ptr = (QMember)ov1_32;
    slot_tbl_access[32] = QMetaData::Public;
    slot_tbl[33].name = "viewExpWindow()";
    slot_tbl[33].ptr = (QMember)ov1_33;
    slot_tbl_access[33] = QMetaData::Public;
    slot_tbl[34].name = "viewBigTextWindow()";
    slot_tbl[34].ptr = (QMember)ov1_34;
    slot_tbl_access[34] = QMetaData::Public;
    slot_tbl[35].name = "viewDropWindow()";
    slot_tbl[35].ptr = (QMember)ov1_35;
    slot_tbl_access[35] = QMetaData::Public;
    slot_tbl[36].name = "viewSpawnPointWindow()";
    slot_tbl[36].ptr = (QMember)ov1_36;
    slot_tbl_access[36] = QMetaData::Public;
    slot_tbl[37].name = "openMapView(int)";
    slot_tbl[37].ptr = (QMember)ov1_37;
    slot_tbl_access[37] = QMetaData::Public;
    slot_tbl[38].name = "editFilters()";
    slot_tbl[38].ptr = (QMember)ov1_38;
    slot_tbl_access[38] = QMetaData::Public;
    slot_tbl[39].name = "editAlerts()";
    slot_tbl[39].ptr = (QMember)ov1_39;
    slot_tbl_access[39] = QMetaData::Public;
    slot_tbl[40].name = "editCategories()";
    slot_tbl[40].ptr = (QMember)ov1_40;
    slot_tbl_access[40] = QMetaData::Public;
    slot_tbl[41].name = "toggleRawDisplay(bool)";
    slot_tbl[41].ptr = (QMember)ov1_41;
    slot_tbl_access[41] = QMetaData::Public;
    slot_tbl[42].name = "setSelectMode(int)";
    slot_tbl[42].ptr = (QMember)ov1_42;
    slot_tbl_access[42] = QMetaData::Public;
    typedef void (EQInterface::*m2_t0)(const QString&);
    typedef void (QObject::*om2_t0)(const QString&);
    typedef void (EQInterface::*m2_t1)(const ItemStruct&);
    typedef void (QObject::*om2_t1)(const ItemStruct&);
    m2_t0 v2_0 = &EQInterface::newMessage;
    om2_t0 ov2_0 = (om2_t0)v2_0;
    m2_t1 v2_1 = &EQInterface::newItem;
    om2_t1 ov2_1 = (om2_t1)v2_1;
    QMetaData *signal_tbl = QMetaObject::new_metadata(2);
    signal_tbl[0].name = "newMessage(const QString&)";
    signal_tbl[0].ptr = (QMember)ov2_0;
    signal_tbl[1].name = "newItem(const ItemStruct&)";
    signal_tbl[1].ptr = (QMember)ov2_1;
    metaObj = QMetaObject::new_metaobject(
	"EQInterface", "QMainWindow",
	slot_tbl, 43,
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

// SIGNAL newMessage
void EQInterface::newMessage( const QString& t0 )
{
    activate_signal_strref( "newMessage(const QString&)", t0 );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL newItem
void EQInterface::newItem( const ItemStruct& t0 )
{
    // No builtin function for signal parameter type const ItemStruct&
    QConnectionList *clist = receivers("newItem(const ItemStruct&)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const ItemStruct&);
    RT0 r0;
    RT1 r1;
    QConnectionListIt it(*clist);
    QConnection   *c;
    QSenderObject *object;
    while ( (c=it.current()) ) {
	++it;
	object = (QSenderObject*)c->object();
	object->setSender( this );
	switch ( c->numArgs() ) {
	    case 0:
#ifdef Q_FP_CCAST_BROKEN
		r0 = reinterpret_cast<RT0>(*(c->member()));
#else
		r0 = (RT0)*(c->member());
#endif
		(object->*r0)();
		break;
	    case 1:
#ifdef Q_FP_CCAST_BROKEN
		r1 = reinterpret_cast<RT1>(*(c->member()));
#else
		r1 = (RT1)*(c->member());
#endif
		(object->*r1)(t0);
		break;
	}
    }
}
