/****************************************************************************
** EQPacket meta object code from reading C++ file 'packet.h'
**
** Created: Fri Sep 28 13:03:21 2001
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.1   edited 2001-04-23 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "packet.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *EQPacket::className() const
{
    return "EQPacket";
}

QMetaObject *EQPacket::metaObj = 0;

void EQPacket::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QObject::className(), "QObject") != 0 )
	badSuperclassWarning("EQPacket","QObject");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString EQPacket::tr(const char* s)
{
    return qApp->translate( "EQPacket", s, 0 );
}

QString EQPacket::tr(const char* s, const char * c)
{
    return qApp->translate( "EQPacket", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* EQPacket::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QObject::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (EQPacket::*m1_t0)();
    typedef void (QObject::*om1_t0)();
    typedef void (EQPacket::*m1_t1)();
    typedef void (QObject::*om1_t1)();
    typedef void (EQPacket::*m1_t2)();
    typedef void (QObject::*om1_t2)();
    m1_t0 v1_0 = &EQPacket::incPlayback;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &EQPacket::decPlayback;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &EQPacket::processPackets;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    QMetaData *slot_tbl = QMetaObject::new_metadata(3);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(3);
    slot_tbl[0].name = "incPlayback()";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    slot_tbl[1].name = "decPlayback()";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Public;
    slot_tbl[2].name = "processPackets()";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Protected;
    typedef void (EQPacket::*m2_t0)(const QString&,const QString&);
    typedef void (QObject::*om2_t0)(const QString&,const QString&);
    typedef void (EQPacket::*m2_t1)();
    typedef void (QObject::*om2_t1)();
    typedef void (EQPacket::*m2_t2)(const struct playerProfileStruct*);
    typedef void (QObject::*om2_t2)(const struct playerProfileStruct*);
    typedef void (EQPacket::*m2_t3)(const struct spawnStruct*);
    typedef void (QObject::*om2_t3)(const struct spawnStruct*);
    typedef void (EQPacket::*m2_t4)(int);
    typedef void (QObject::*om2_t4)(int);
    typedef void (EQPacket::*m2_t5)(int);
    typedef void (QObject::*om2_t5)(int);
    typedef void (EQPacket::*m2_t6)(int);
    typedef void (QObject::*om2_t6)(int);
    typedef void (EQPacket::*m2_t7)(int);
    typedef void (QObject::*om2_t7)(int);
    typedef void (EQPacket::*m2_t8)(const void*,int);
    typedef void (QObject::*om2_t8)(const void*,int);
    typedef void (EQPacket::*m2_t9)(const OpCode&,int,void*,unsigned int);
    typedef void (QObject::*om2_t9)(const OpCode&,int,void*,unsigned int);
    typedef void (EQPacket::*m2_t10)(const struct playerProfileStruct*);
    typedef void (QObject::*om2_t10)(const struct playerProfileStruct*);
    typedef void (EQPacket::*m2_t11)(const struct zoneSpawnsStruct*,int);
    typedef void (QObject::*om2_t11)(const struct zoneSpawnsStruct*,int);
    typedef void (EQPacket::*m2_t12)(const struct addSpawnStruct*);
    typedef void (QObject::*om2_t12)(const struct addSpawnStruct*);
    typedef void (EQPacket::*m2_t13)(const struct itemShopStruct*);
    typedef void (QObject::*om2_t13)(const struct itemShopStruct*);
    typedef void (EQPacket::*m2_t14)(const struct itemReceivedStruct*);
    typedef void (QObject::*om2_t14)(const struct itemReceivedStruct*);
    typedef void (EQPacket::*m2_t15)(const struct itemReceivedStruct*);
    typedef void (QObject::*om2_t15)(const struct itemReceivedStruct*);
    typedef void (EQPacket::*m2_t16)(const struct tradeItemStruct*);
    typedef void (QObject::*om2_t16)(const struct tradeItemStruct*);
    typedef void (EQPacket::*m2_t17)(const struct itemPlayerStruct*);
    typedef void (QObject::*om2_t17)(const struct itemPlayerStruct*);
    typedef void (EQPacket::*m2_t18)(const struct summonedItemStruct*);
    typedef void (QObject::*om2_t18)(const struct summonedItemStruct*);
    typedef void (EQPacket::*m2_t19)(const struct clientZoneOutStruct*);
    typedef void (QObject::*om2_t19)(const struct clientZoneOutStruct*);
    typedef void (EQPacket::*m2_t20)(const struct clientZoneInStruct*);
    typedef void (QObject::*om2_t20)(const struct clientZoneInStruct*);
    typedef void (EQPacket::*m2_t21)(const struct zoneChangeStruct*);
    typedef void (QObject::*om2_t21)(const struct zoneChangeStruct*);
    typedef void (EQPacket::*m2_t22)(const struct spawnKilledStruct*);
    typedef void (QObject::*om2_t22)(const struct spawnKilledStruct*);
    typedef void (EQPacket::*m2_t23)(const struct deleteSpawnStruct*);
    typedef void (QObject::*om2_t23)(const struct deleteSpawnStruct*);
    typedef void (EQPacket::*m2_t24)(const struct channelMessageStruct*);
    typedef void (QObject::*om2_t24)(const struct channelMessageStruct*);
    typedef void (EQPacket::*m2_t25)(const struct timeOfDayStruct*);
    typedef void (QObject::*om2_t25)(const struct timeOfDayStruct*);
    typedef void (EQPacket::*m2_t26)(const struct bookTextStruct*);
    typedef void (QObject::*om2_t26)(const struct bookTextStruct*);
    typedef void (EQPacket::*m2_t27)(const struct randomStruct*);
    typedef void (QObject::*om2_t27)(const struct randomStruct*);
    typedef void (EQPacket::*m2_t28)(const struct emoteTextStruct*);
    typedef void (QObject::*om2_t28)(const struct emoteTextStruct*);
    typedef void (EQPacket::*m2_t29)(const struct bookPlayerStruct*);
    typedef void (QObject::*om2_t29)(const struct bookPlayerStruct*);
    typedef void (EQPacket::*m2_t30)(const struct containerPlayerStruct*);
    typedef void (QObject::*om2_t30)(const struct containerPlayerStruct*);
    typedef void (EQPacket::*m2_t31)(const struct inspectingStruct*);
    typedef void (QObject::*om2_t31)(const struct inspectingStruct*);
    typedef void (EQPacket::*m2_t32)(const struct spawnHpUpdateStruct*);
    typedef void (QObject::*om2_t32)(const struct spawnHpUpdateStruct*);
    typedef void (EQPacket::*m2_t33)(const struct spMesgStruct*);
    typedef void (QObject::*om2_t33)(const struct spMesgStruct*);
    typedef void (EQPacket::*m2_t34)(const struct beginCastStruct*);
    typedef void (QObject::*om2_t34)(const struct beginCastStruct*);
    typedef void (EQPacket::*m2_t35)(const struct memorizeSlotStruct*);
    typedef void (QObject::*om2_t35)(const struct memorizeSlotStruct*);
    typedef void (EQPacket::*m2_t36)(const struct spawnPosUpdateStruct*);
    typedef void (QObject::*om2_t36)(const struct spawnPosUpdateStruct*);
    typedef void (EQPacket::*m2_t37)(const struct expUpdateStruct*);
    typedef void (QObject::*om2_t37)(const struct expUpdateStruct*);
    typedef void (EQPacket::*m2_t38)(const struct levelUpStruct*);
    typedef void (QObject::*om2_t38)(const struct levelUpStruct*);
    typedef void (EQPacket::*m2_t39)(const struct skillIncreaseStruct*);
    typedef void (QObject::*om2_t39)(const struct skillIncreaseStruct*);
    typedef void (EQPacket::*m2_t40)(const struct newDoorStruct*);
    typedef void (QObject::*om2_t40)(const struct newDoorStruct*);
    typedef void (EQPacket::*m2_t41)(const void*);
    typedef void (QObject::*om2_t41)(const void*);
    typedef void (EQPacket::*m2_t42)(const void*);
    typedef void (QObject::*om2_t42)(const void*);
    typedef void (EQPacket::*m2_t43)(const struct interruptCastStruct*);
    typedef void (QObject::*om2_t43)(const struct interruptCastStruct*);
    typedef void (EQPacket::*m2_t44)(const struct systemMessageStruct*);
    typedef void (QObject::*om2_t44)(const struct systemMessageStruct*);
    typedef void (EQPacket::*m2_t45)(const struct playerUpdateStruct*);
    typedef void (QObject::*om2_t45)(const struct playerUpdateStruct*);
    typedef void (EQPacket::*m2_t46)(const struct equipChangeStruct*);
    typedef void (QObject::*om2_t46)(const struct equipChangeStruct*);
    typedef void (EQPacket::*m2_t47)(const struct actionStruct*);
    typedef void (QObject::*om2_t47)(const struct actionStruct*);
    typedef void (EQPacket::*m2_t48)(const struct castOnStruct*);
    typedef void (QObject::*om2_t48)(const struct castOnStruct*);
    typedef void (EQPacket::*m2_t49)(const struct manaDecrementStruct*);
    typedef void (QObject::*om2_t49)(const struct manaDecrementStruct*);
    typedef void (EQPacket::*m2_t50)(const struct staminaStruct*);
    typedef void (QObject::*om2_t50)(const struct staminaStruct*);
    typedef void (EQPacket::*m2_t51)(const struct addDropStruct*);
    typedef void (QObject::*om2_t51)(const struct addDropStruct*);
    typedef void (EQPacket::*m2_t52)(const struct deleteDropStruct*);
    typedef void (QObject::*om2_t52)(const struct deleteDropStruct*);
    typedef void (EQPacket::*m2_t53)(const struct addCoinsStruct*);
    typedef void (QObject::*om2_t53)(const struct addCoinsStruct*);
    typedef void (EQPacket::*m2_t54)(const struct deleteCoinsStruct*);
    typedef void (QObject::*om2_t54)(const struct deleteCoinsStruct*);
    typedef void (EQPacket::*m2_t55)(const void*);
    typedef void (QObject::*om2_t55)(const void*);
    typedef void (EQPacket::*m2_t56)(const void*);
    typedef void (QObject::*om2_t56)(const void*);
    typedef void (EQPacket::*m2_t57)(const void*);
    typedef void (QObject::*om2_t57)(const void*);
    typedef void (EQPacket::*m2_t58)(const void*);
    typedef void (QObject::*om2_t58)(const void*);
    typedef void (EQPacket::*m2_t59)(const struct attack1Struct*);
    typedef void (QObject::*om2_t59)(const struct attack1Struct*);
    typedef void (EQPacket::*m2_t60)(const struct attack2Struct*);
    typedef void (QObject::*om2_t60)(const struct attack2Struct*);
    typedef void (EQPacket::*m2_t61)(const struct considerStruct*);
    typedef void (QObject::*om2_t61)(const struct considerStruct*);
    typedef void (EQPacket::*m2_t62)(const struct considerStruct*);
    typedef void (QObject::*om2_t62)(const struct considerStruct*);
    typedef void (EQPacket::*m2_t63)(const struct newGuildStruct*);
    typedef void (QObject::*om2_t63)(const struct newGuildStruct*);
    typedef void (EQPacket::*m2_t64)(const struct moneyUpdateStruct*);
    typedef void (QObject::*om2_t64)(const struct moneyUpdateStruct*);
    typedef void (EQPacket::*m2_t65)(const void*);
    typedef void (QObject::*om2_t65)(const void*);
    typedef void (EQPacket::*m2_t66)(const struct clientTargetStruct*);
    typedef void (QObject::*om2_t66)(const struct clientTargetStruct*);
    typedef void (EQPacket::*m2_t67)(const struct bindWoundStruct*);
    typedef void (QObject::*om2_t67)(const struct bindWoundStruct*);
    typedef void (EQPacket::*m2_t68)(const struct groupMemberStruct*);
    typedef void (QObject::*om2_t68)(const struct groupMemberStruct*);
    typedef void (EQPacket::*m2_t69)(const OpCode&,int,void*,unsigned int);
    typedef void (QObject::*om2_t69)(const OpCode&,int,void*,unsigned int);
    m2_t0 v2_0 = &EQPacket::captureTargetChanged;
    om2_t0 ov2_0 = (om2_t0)v2_0;
    m2_t1 v2_1 = &EQPacket::keyFound;
    om2_t1 ov2_1 = (om2_t1)v2_1;
    m2_t2 v2_2 = &EQPacket::backfillPlayer;
    om2_t2 ov2_2 = (om2_t2)v2_2;
    m2_t3 v2_3 = &EQPacket::backfillSpawn;
    om2_t3 ov2_3 = (om2_t3)v2_3;
    m2_t4 v2_4 = &EQPacket::packetReceived;
    om2_t4 ov2_4 = (om2_t4)v2_4;
    m2_t5 v2_5 = &EQPacket::seqReceive;
    om2_t5 ov2_5 = (om2_t5)v2_5;
    m2_t6 v2_6 = &EQPacket::seqExpect;
    om2_t6 ov2_6 = (om2_t6)v2_6;
    m2_t7 v2_7 = &EQPacket::numPacket;
    om2_t7 ov2_7 = (om2_t7)v2_7;
    m2_t8 v2_8 = &EQPacket::handlePacket;
    om2_t8 ov2_8 = (om2_t8)v2_8;
    m2_t9 v2_9 = &EQPacket::handleOpCode;
    om2_t9 ov2_9 = (om2_t9)v2_9;
    m2_t10 v2_10 = &EQPacket::handlePlayerProfile;
    om2_t10 ov2_10 = (om2_t10)v2_10;
    m2_t11 v2_11 = &EQPacket::handleZoneSpawns;
    om2_t11 ov2_11 = (om2_t11)v2_11;
    m2_t12 v2_12 = &EQPacket::handleNewSpawn;
    om2_t12 ov2_12 = (om2_t12)v2_12;
    m2_t13 v2_13 = &EQPacket::handleShopItem;
    om2_t13 ov2_13 = (om2_t13)v2_13;
    m2_t14 v2_14 = &EQPacket::handleCorpseItem;
    om2_t14 ov2_14 = (om2_t14)v2_14;
    m2_t15 v2_15 = &EQPacket::handleTradeItem;
    om2_t15 ov2_15 = (om2_t15)v2_15;
    m2_t16 v2_16 = &EQPacket::handleTradeItem2;
    om2_t16 ov2_16 = (om2_t16)v2_16;
    m2_t17 v2_17 = &EQPacket::handlePlayerItem;
    om2_t17 ov2_17 = (om2_t17)v2_17;
    m2_t18 v2_18 = &EQPacket::handleSummonedItem;
    om2_t18 ov2_18 = (om2_t18)v2_18;
    m2_t19 v2_19 = &EQPacket::handleZoneBegin;
    om2_t19 ov2_19 = (om2_t19)v2_19;
    m2_t20 v2_20 = &EQPacket::handleZoneEnd;
    om2_t20 ov2_20 = (om2_t20)v2_20;
    m2_t21 v2_21 = &EQPacket::handleZoneChange;
    om2_t21 ov2_21 = (om2_t21)v2_21;
    m2_t22 v2_22 = &EQPacket::handleCorpse;
    om2_t22 ov2_22 = (om2_t22)v2_22;
    m2_t23 v2_23 = &EQPacket::handleDeleteSpawn;
    om2_t23 ov2_23 = (om2_t23)v2_23;
    m2_t24 v2_24 = &EQPacket::handleChannelMsg;
    om2_t24 ov2_24 = (om2_t24)v2_24;
    m2_t25 v2_25 = &EQPacket::handleTime;
    om2_t25 ov2_25 = (om2_t25)v2_25;
    m2_t26 v2_26 = &EQPacket::handleBookText;
    om2_t26 ov2_26 = (om2_t26)v2_26;
    m2_t27 v2_27 = &EQPacket::handleRandom;
    om2_t27 ov2_27 = (om2_t27)v2_27;
    m2_t28 v2_28 = &EQPacket::handleEmote;
    om2_t28 ov2_28 = (om2_t28)v2_28;
    m2_t29 v2_29 = &EQPacket::handlePlayerBook;
    om2_t29 ov2_29 = (om2_t29)v2_29;
    m2_t30 v2_30 = &EQPacket::handlePlayerCont;
    om2_t30 ov2_30 = (om2_t30)v2_30;
    m2_t31 v2_31 = &EQPacket::handleInspect;
    om2_t31 ov2_31 = (om2_t31)v2_31;
    m2_t32 v2_32 = &EQPacket::handleHPUpdate;
    om2_t32 ov2_32 = (om2_t32)v2_32;
    m2_t33 v2_33 = &EQPacket::handleSpecialMsg;
    om2_t33 ov2_33 = (om2_t33)v2_33;
    m2_t34 v2_34 = &EQPacket::handleBeginCast;
    om2_t34 ov2_34 = (om2_t34)v2_34;
    m2_t35 v2_35 = &EQPacket::handleMemSpell;
    om2_t35 ov2_35 = (om2_t35)v2_35;
    m2_t36 v2_36 = &EQPacket::handleSpawnUpdate;
    om2_t36 ov2_36 = (om2_t36)v2_36;
    m2_t37 v2_37 = &EQPacket::handleXPUpdate;
    om2_t37 ov2_37 = (om2_t37)v2_37;
    m2_t38 v2_38 = &EQPacket::handleLevelUp;
    om2_t38 ov2_38 = (om2_t38)v2_38;
    m2_t39 v2_39 = &EQPacket::handleSkillUp;
    om2_t39 ov2_39 = (om2_t39)v2_39;
    m2_t40 v2_40 = &EQPacket::handleDoor;
    om2_t40 ov2_40 = (om2_t40)v2_40;
    m2_t41 v2_41 = &EQPacket::handleDoorOpen;
    om2_t41 ov2_41 = (om2_t41)v2_41;
    m2_t42 v2_42 = &EQPacket::handleIllusion;
    om2_t42 ov2_42 = (om2_t42)v2_42;
    m2_t43 v2_43 = &EQPacket::handleBadCast;
    om2_t43 ov2_43 = (om2_t43)v2_43;
    m2_t44 v2_44 = &EQPacket::handleSysMsg;
    om2_t44 ov2_44 = (om2_t44)v2_44;
    m2_t45 v2_45 = &EQPacket::handlePlayerPos;
    om2_t45 ov2_45 = (om2_t45)v2_45;
    m2_t46 v2_46 = &EQPacket::handleEquipChange;
    om2_t46 ov2_46 = (om2_t46)v2_46;
    m2_t47 v2_47 = &EQPacket::handleAction;
    om2_t47 ov2_47 = (om2_t47)v2_47;
    m2_t48 v2_48 = &EQPacket::handleCastOn;
    om2_t48 ov2_48 = (om2_t48)v2_48;
    m2_t49 v2_49 = &EQPacket::handleManaUsed;
    om2_t49 ov2_49 = (om2_t49)v2_49;
    m2_t50 v2_50 = &EQPacket::handleStamina;
    om2_t50 ov2_50 = (om2_t50)v2_50;
    m2_t51 v2_51 = &EQPacket::handleNewDrop;
    om2_t51 ov2_51 = (om2_t51)v2_51;
    m2_t52 v2_52 = &EQPacket::handleDeleteDrop;
    om2_t52 ov2_52 = (om2_t52)v2_52;
    m2_t53 v2_53 = &EQPacket::handleNewCoins;
    om2_t53 ov2_53 = (om2_t53)v2_53;
    m2_t54 v2_54 = &EQPacket::handleDeleteCoins;
    om2_t54 ov2_54 = (om2_t54)v2_54;
    m2_t55 v2_55 = &EQPacket::handleOpenVendor;
    om2_t55 ov2_55 = (om2_t55)v2_55;
    m2_t56 v2_56 = &EQPacket::handleCloseVendor;
    om2_t56 ov2_56 = (om2_t56)v2_56;
    m2_t57 v2_57 = &EQPacket::handleOpenGM;
    om2_t57 ov2_57 = (om2_t57)v2_57;
    m2_t58 v2_58 = &EQPacket::handleCloseGM;
    om2_t58 ov2_58 = (om2_t58)v2_58;
    m2_t59 v2_59 = &EQPacket::handleAttack1;
    om2_t59 ov2_59 = (om2_t59)v2_59;
    m2_t60 v2_60 = &EQPacket::handleAttack2;
    om2_t60 ov2_60 = (om2_t60)v2_60;
    m2_t61 v2_61 = &EQPacket::handleConsRequest;
    om2_t61 ov2_61 = (om2_t61)v2_61;
    m2_t62 v2_62 = &EQPacket::handleConsMessage;
    om2_t62 ov2_62 = (om2_t62)v2_62;
    m2_t63 v2_63 = &EQPacket::handleNewGuild;
    om2_t63 ov2_63 = (om2_t63)v2_63;
    m2_t64 v2_64 = &EQPacket::handleMoneyUpdate;
    om2_t64 ov2_64 = (om2_t64)v2_64;
    m2_t65 v2_65 = &EQPacket::handleMoney;
    om2_t65 ov2_65 = (om2_t65)v2_65;
    m2_t66 v2_66 = &EQPacket::handleClientTarget;
    om2_t66 ov2_66 = (om2_t66)v2_66;
    m2_t67 v2_67 = &EQPacket::handleBindWound;
    om2_t67 ov2_67 = (om2_t67)v2_67;
    m2_t68 v2_68 = &EQPacket::handleGroupInfo;
    om2_t68 ov2_68 = (om2_t68)v2_68;
    m2_t69 v2_69 = &EQPacket::unhandledOpCode;
    om2_t69 ov2_69 = (om2_t69)v2_69;
    QMetaData *signal_tbl = QMetaObject::new_metadata(70);
    signal_tbl[0].name = "captureTargetChanged(const QString&,const QString&)";
    signal_tbl[0].ptr = (QMember)ov2_0;
    signal_tbl[1].name = "keyFound()";
    signal_tbl[1].ptr = (QMember)ov2_1;
    signal_tbl[2].name = "backfillPlayer(const struct playerProfileStruct*)";
    signal_tbl[2].ptr = (QMember)ov2_2;
    signal_tbl[3].name = "backfillSpawn(const struct spawnStruct*)";
    signal_tbl[3].ptr = (QMember)ov2_3;
    signal_tbl[4].name = "packetReceived(int)";
    signal_tbl[4].ptr = (QMember)ov2_4;
    signal_tbl[5].name = "seqReceive(int)";
    signal_tbl[5].ptr = (QMember)ov2_5;
    signal_tbl[6].name = "seqExpect(int)";
    signal_tbl[6].ptr = (QMember)ov2_6;
    signal_tbl[7].name = "numPacket(int)";
    signal_tbl[7].ptr = (QMember)ov2_7;
    signal_tbl[8].name = "handlePacket(const void*,int)";
    signal_tbl[8].ptr = (QMember)ov2_8;
    signal_tbl[9].name = "handleOpCode(const OpCode&,int,void*,unsigned int)";
    signal_tbl[9].ptr = (QMember)ov2_9;
    signal_tbl[10].name = "handlePlayerProfile(const struct playerProfileStruct*)";
    signal_tbl[10].ptr = (QMember)ov2_10;
    signal_tbl[11].name = "handleZoneSpawns(const struct zoneSpawnsStruct*,int)";
    signal_tbl[11].ptr = (QMember)ov2_11;
    signal_tbl[12].name = "handleNewSpawn(const struct addSpawnStruct*)";
    signal_tbl[12].ptr = (QMember)ov2_12;
    signal_tbl[13].name = "handleShopItem(const struct itemShopStruct*)";
    signal_tbl[13].ptr = (QMember)ov2_13;
    signal_tbl[14].name = "handleCorpseItem(const struct itemReceivedStruct*)";
    signal_tbl[14].ptr = (QMember)ov2_14;
    signal_tbl[15].name = "handleTradeItem(const struct itemReceivedStruct*)";
    signal_tbl[15].ptr = (QMember)ov2_15;
    signal_tbl[16].name = "handleTradeItem2(const struct tradeItemStruct*)";
    signal_tbl[16].ptr = (QMember)ov2_16;
    signal_tbl[17].name = "handlePlayerItem(const struct itemPlayerStruct*)";
    signal_tbl[17].ptr = (QMember)ov2_17;
    signal_tbl[18].name = "handleSummonedItem(const struct summonedItemStruct*)";
    signal_tbl[18].ptr = (QMember)ov2_18;
    signal_tbl[19].name = "handleZoneBegin(const struct clientZoneOutStruct*)";
    signal_tbl[19].ptr = (QMember)ov2_19;
    signal_tbl[20].name = "handleZoneEnd(const struct clientZoneInStruct*)";
    signal_tbl[20].ptr = (QMember)ov2_20;
    signal_tbl[21].name = "handleZoneChange(const struct zoneChangeStruct*)";
    signal_tbl[21].ptr = (QMember)ov2_21;
    signal_tbl[22].name = "handleCorpse(const struct spawnKilledStruct*)";
    signal_tbl[22].ptr = (QMember)ov2_22;
    signal_tbl[23].name = "handleDeleteSpawn(const struct deleteSpawnStruct*)";
    signal_tbl[23].ptr = (QMember)ov2_23;
    signal_tbl[24].name = "handleChannelMsg(const struct channelMessageStruct*)";
    signal_tbl[24].ptr = (QMember)ov2_24;
    signal_tbl[25].name = "handleTime(const struct timeOfDayStruct*)";
    signal_tbl[25].ptr = (QMember)ov2_25;
    signal_tbl[26].name = "handleBookText(const struct bookTextStruct*)";
    signal_tbl[26].ptr = (QMember)ov2_26;
    signal_tbl[27].name = "handleRandom(const struct randomStruct*)";
    signal_tbl[27].ptr = (QMember)ov2_27;
    signal_tbl[28].name = "handleEmote(const struct emoteTextStruct*)";
    signal_tbl[28].ptr = (QMember)ov2_28;
    signal_tbl[29].name = "handlePlayerBook(const struct bookPlayerStruct*)";
    signal_tbl[29].ptr = (QMember)ov2_29;
    signal_tbl[30].name = "handlePlayerCont(const struct containerPlayerStruct*)";
    signal_tbl[30].ptr = (QMember)ov2_30;
    signal_tbl[31].name = "handleInspect(const struct inspectingStruct*)";
    signal_tbl[31].ptr = (QMember)ov2_31;
    signal_tbl[32].name = "handleHPUpdate(const struct spawnHpUpdateStruct*)";
    signal_tbl[32].ptr = (QMember)ov2_32;
    signal_tbl[33].name = "handleSpecialMsg(const struct spMesgStruct*)";
    signal_tbl[33].ptr = (QMember)ov2_33;
    signal_tbl[34].name = "handleBeginCast(const struct beginCastStruct*)";
    signal_tbl[34].ptr = (QMember)ov2_34;
    signal_tbl[35].name = "handleMemSpell(const struct memorizeSlotStruct*)";
    signal_tbl[35].ptr = (QMember)ov2_35;
    signal_tbl[36].name = "handleSpawnUpdate(const struct spawnPosUpdateStruct*)";
    signal_tbl[36].ptr = (QMember)ov2_36;
    signal_tbl[37].name = "handleXPUpdate(const struct expUpdateStruct*)";
    signal_tbl[37].ptr = (QMember)ov2_37;
    signal_tbl[38].name = "handleLevelUp(const struct levelUpStruct*)";
    signal_tbl[38].ptr = (QMember)ov2_38;
    signal_tbl[39].name = "handleSkillUp(const struct skillIncreaseStruct*)";
    signal_tbl[39].ptr = (QMember)ov2_39;
    signal_tbl[40].name = "handleDoor(const struct newDoorStruct*)";
    signal_tbl[40].ptr = (QMember)ov2_40;
    signal_tbl[41].name = "handleDoorOpen(const void*)";
    signal_tbl[41].ptr = (QMember)ov2_41;
    signal_tbl[42].name = "handleIllusion(const void*)";
    signal_tbl[42].ptr = (QMember)ov2_42;
    signal_tbl[43].name = "handleBadCast(const struct interruptCastStruct*)";
    signal_tbl[43].ptr = (QMember)ov2_43;
    signal_tbl[44].name = "handleSysMsg(const struct systemMessageStruct*)";
    signal_tbl[44].ptr = (QMember)ov2_44;
    signal_tbl[45].name = "handlePlayerPos(const struct playerUpdateStruct*)";
    signal_tbl[45].ptr = (QMember)ov2_45;
    signal_tbl[46].name = "handleEquipChange(const struct equipChangeStruct*)";
    signal_tbl[46].ptr = (QMember)ov2_46;
    signal_tbl[47].name = "handleAction(const struct actionStruct*)";
    signal_tbl[47].ptr = (QMember)ov2_47;
    signal_tbl[48].name = "handleCastOn(const struct castOnStruct*)";
    signal_tbl[48].ptr = (QMember)ov2_48;
    signal_tbl[49].name = "handleManaUsed(const struct manaDecrementStruct*)";
    signal_tbl[49].ptr = (QMember)ov2_49;
    signal_tbl[50].name = "handleStamina(const struct staminaStruct*)";
    signal_tbl[50].ptr = (QMember)ov2_50;
    signal_tbl[51].name = "handleNewDrop(const struct addDropStruct*)";
    signal_tbl[51].ptr = (QMember)ov2_51;
    signal_tbl[52].name = "handleDeleteDrop(const struct deleteDropStruct*)";
    signal_tbl[52].ptr = (QMember)ov2_52;
    signal_tbl[53].name = "handleNewCoins(const struct addCoinsStruct*)";
    signal_tbl[53].ptr = (QMember)ov2_53;
    signal_tbl[54].name = "handleDeleteCoins(const struct deleteCoinsStruct*)";
    signal_tbl[54].ptr = (QMember)ov2_54;
    signal_tbl[55].name = "handleOpenVendor(const void*)";
    signal_tbl[55].ptr = (QMember)ov2_55;
    signal_tbl[56].name = "handleCloseVendor(const void*)";
    signal_tbl[56].ptr = (QMember)ov2_56;
    signal_tbl[57].name = "handleOpenGM(const void*)";
    signal_tbl[57].ptr = (QMember)ov2_57;
    signal_tbl[58].name = "handleCloseGM(const void*)";
    signal_tbl[58].ptr = (QMember)ov2_58;
    signal_tbl[59].name = "handleAttack1(const struct attack1Struct*)";
    signal_tbl[59].ptr = (QMember)ov2_59;
    signal_tbl[60].name = "handleAttack2(const struct attack2Struct*)";
    signal_tbl[60].ptr = (QMember)ov2_60;
    signal_tbl[61].name = "handleConsRequest(const struct considerStruct*)";
    signal_tbl[61].ptr = (QMember)ov2_61;
    signal_tbl[62].name = "handleConsMessage(const struct considerStruct*)";
    signal_tbl[62].ptr = (QMember)ov2_62;
    signal_tbl[63].name = "handleNewGuild(const struct newGuildStruct*)";
    signal_tbl[63].ptr = (QMember)ov2_63;
    signal_tbl[64].name = "handleMoneyUpdate(const struct moneyUpdateStruct*)";
    signal_tbl[64].ptr = (QMember)ov2_64;
    signal_tbl[65].name = "handleMoney(const void*)";
    signal_tbl[65].ptr = (QMember)ov2_65;
    signal_tbl[66].name = "handleClientTarget(const struct clientTargetStruct*)";
    signal_tbl[66].ptr = (QMember)ov2_66;
    signal_tbl[67].name = "handleBindWound(const struct bindWoundStruct*)";
    signal_tbl[67].ptr = (QMember)ov2_67;
    signal_tbl[68].name = "handleGroupInfo(const struct groupMemberStruct*)";
    signal_tbl[68].ptr = (QMember)ov2_68;
    signal_tbl[69].name = "unhandledOpCode(const OpCode&,int,void*,unsigned int)";
    signal_tbl[69].ptr = (QMember)ov2_69;
    metaObj = QMetaObject::new_metaobject(
	"EQPacket", "QObject",
	slot_tbl, 3,
	signal_tbl, 70,
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

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL captureTargetChanged
void EQPacket::captureTargetChanged( const QString& t0, const QString& t1 )
{
    // No builtin function for signal parameter type const QString&,const QString&
    QConnectionList *clist = receivers("captureTargetChanged(const QString&,const QString&)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const QString&);
    typedef void (QObject::*RT2)(const QString&,const QString&);
    RT0 r0;
    RT1 r1;
    RT2 r2;
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
	    case 2:
#ifdef Q_FP_CCAST_BROKEN
		r2 = reinterpret_cast<RT2>(*(c->member()));
#else
		r2 = (RT2)*(c->member());
#endif
		(object->*r2)(t0, t1);
		break;
	}
    }
}

// SIGNAL keyFound
void EQPacket::keyFound()
{
    activate_signal( "keyFound()" );
}

// SIGNAL backfillPlayer
void EQPacket::backfillPlayer( const struct playerProfileStruct* t0 )
{
    // No builtin function for signal parameter type const struct playerProfileStruct*
    QConnectionList *clist = receivers("backfillPlayer(const struct playerProfileStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct playerProfileStruct*);
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

// SIGNAL backfillSpawn
void EQPacket::backfillSpawn( const struct spawnStruct* t0 )
{
    // No builtin function for signal parameter type const struct spawnStruct*
    QConnectionList *clist = receivers("backfillSpawn(const struct spawnStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct spawnStruct*);
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

// SIGNAL packetReceived
void EQPacket::packetReceived( int t0 )
{
    activate_signal( "packetReceived(int)", t0 );
}

// SIGNAL seqReceive
void EQPacket::seqReceive( int t0 )
{
    activate_signal( "seqReceive(int)", t0 );
}

// SIGNAL seqExpect
void EQPacket::seqExpect( int t0 )
{
    activate_signal( "seqExpect(int)", t0 );
}

// SIGNAL numPacket
void EQPacket::numPacket( int t0 )
{
    activate_signal( "numPacket(int)", t0 );
}

// SIGNAL handlePacket
void EQPacket::handlePacket( const void* t0, int t1 )
{
    // No builtin function for signal parameter type const void*,int
    QConnectionList *clist = receivers("handlePacket(const void*,int)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const void*);
    typedef void (QObject::*RT2)(const void*,int);
    RT0 r0;
    RT1 r1;
    RT2 r2;
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
	    case 2:
#ifdef Q_FP_CCAST_BROKEN
		r2 = reinterpret_cast<RT2>(*(c->member()));
#else
		r2 = (RT2)*(c->member());
#endif
		(object->*r2)(t0, t1);
		break;
	}
    }
}

// SIGNAL handleOpCode
void EQPacket::handleOpCode( const OpCode& t0, int t1, void* t2, unsigned int t3 )
{
    // No builtin function for signal parameter type const OpCode&,int,void*,unsigned int
    QConnectionList *clist = receivers("handleOpCode(const OpCode&,int,void*,unsigned int)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const OpCode&);
    typedef void (QObject::*RT2)(const OpCode&,int);
    typedef void (QObject::*RT3)(const OpCode&,int,void*);
    typedef void (QObject::*RT4)(const OpCode&,int,void*,unsigned int);
    RT0 r0;
    RT1 r1;
    RT2 r2;
    RT3 r3;
    RT4 r4;
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
	    case 2:
#ifdef Q_FP_CCAST_BROKEN
		r2 = reinterpret_cast<RT2>(*(c->member()));
#else
		r2 = (RT2)*(c->member());
#endif
		(object->*r2)(t0, t1);
		break;
	    case 3:
#ifdef Q_FP_CCAST_BROKEN
		r3 = reinterpret_cast<RT3>(*(c->member()));
#else
		r3 = (RT3)*(c->member());
#endif
		(object->*r3)(t0, t1, t2);
		break;
	    case 4:
#ifdef Q_FP_CCAST_BROKEN
		r4 = reinterpret_cast<RT4>(*(c->member()));
#else
		r4 = (RT4)*(c->member());
#endif
		(object->*r4)(t0, t1, t2, t3);
		break;
	}
    }
}

// SIGNAL handlePlayerProfile
void EQPacket::handlePlayerProfile( const struct playerProfileStruct* t0 )
{
    // No builtin function for signal parameter type const struct playerProfileStruct*
    QConnectionList *clist = receivers("handlePlayerProfile(const struct playerProfileStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct playerProfileStruct*);
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

// SIGNAL handleZoneSpawns
void EQPacket::handleZoneSpawns( const struct zoneSpawnsStruct* t0, int t1 )
{
    // No builtin function for signal parameter type const struct zoneSpawnsStruct*,int
    QConnectionList *clist = receivers("handleZoneSpawns(const struct zoneSpawnsStruct*,int)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct zoneSpawnsStruct*);
    typedef void (QObject::*RT2)(const struct zoneSpawnsStruct*,int);
    RT0 r0;
    RT1 r1;
    RT2 r2;
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
	    case 2:
#ifdef Q_FP_CCAST_BROKEN
		r2 = reinterpret_cast<RT2>(*(c->member()));
#else
		r2 = (RT2)*(c->member());
#endif
		(object->*r2)(t0, t1);
		break;
	}
    }
}

// SIGNAL handleNewSpawn
void EQPacket::handleNewSpawn( const struct addSpawnStruct* t0 )
{
    // No builtin function for signal parameter type const struct addSpawnStruct*
    QConnectionList *clist = receivers("handleNewSpawn(const struct addSpawnStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct addSpawnStruct*);
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

// SIGNAL handleShopItem
void EQPacket::handleShopItem( const struct itemShopStruct* t0 )
{
    // No builtin function for signal parameter type const struct itemShopStruct*
    QConnectionList *clist = receivers("handleShopItem(const struct itemShopStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct itemShopStruct*);
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

// SIGNAL handleCorpseItem
void EQPacket::handleCorpseItem( const struct itemReceivedStruct* t0 )
{
    // No builtin function for signal parameter type const struct itemReceivedStruct*
    QConnectionList *clist = receivers("handleCorpseItem(const struct itemReceivedStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct itemReceivedStruct*);
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

// SIGNAL handleTradeItem
void EQPacket::handleTradeItem( const struct itemReceivedStruct* t0 )
{
    // No builtin function for signal parameter type const struct itemReceivedStruct*
    QConnectionList *clist = receivers("handleTradeItem(const struct itemReceivedStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct itemReceivedStruct*);
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

// SIGNAL handleTradeItem2
void EQPacket::handleTradeItem2( const struct tradeItemStruct* t0 )
{
    // No builtin function for signal parameter type const struct tradeItemStruct*
    QConnectionList *clist = receivers("handleTradeItem2(const struct tradeItemStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct tradeItemStruct*);
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

// SIGNAL handlePlayerItem
void EQPacket::handlePlayerItem( const struct itemPlayerStruct* t0 )
{
    // No builtin function for signal parameter type const struct itemPlayerStruct*
    QConnectionList *clist = receivers("handlePlayerItem(const struct itemPlayerStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct itemPlayerStruct*);
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

// SIGNAL handleSummonedItem
void EQPacket::handleSummonedItem( const struct summonedItemStruct* t0 )
{
    // No builtin function for signal parameter type const struct summonedItemStruct*
    QConnectionList *clist = receivers("handleSummonedItem(const struct summonedItemStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct summonedItemStruct*);
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

// SIGNAL handleZoneBegin
void EQPacket::handleZoneBegin( const struct clientZoneOutStruct* t0 )
{
    // No builtin function for signal parameter type const struct clientZoneOutStruct*
    QConnectionList *clist = receivers("handleZoneBegin(const struct clientZoneOutStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct clientZoneOutStruct*);
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

// SIGNAL handleZoneEnd
void EQPacket::handleZoneEnd( const struct clientZoneInStruct* t0 )
{
    // No builtin function for signal parameter type const struct clientZoneInStruct*
    QConnectionList *clist = receivers("handleZoneEnd(const struct clientZoneInStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct clientZoneInStruct*);
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

// SIGNAL handleZoneChange
void EQPacket::handleZoneChange( const struct zoneChangeStruct* t0 )
{
    // No builtin function for signal parameter type const struct zoneChangeStruct*
    QConnectionList *clist = receivers("handleZoneChange(const struct zoneChangeStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct zoneChangeStruct*);
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

// SIGNAL handleCorpse
void EQPacket::handleCorpse( const struct spawnKilledStruct* t0 )
{
    // No builtin function for signal parameter type const struct spawnKilledStruct*
    QConnectionList *clist = receivers("handleCorpse(const struct spawnKilledStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct spawnKilledStruct*);
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

// SIGNAL handleDeleteSpawn
void EQPacket::handleDeleteSpawn( const struct deleteSpawnStruct* t0 )
{
    // No builtin function for signal parameter type const struct deleteSpawnStruct*
    QConnectionList *clist = receivers("handleDeleteSpawn(const struct deleteSpawnStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct deleteSpawnStruct*);
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

// SIGNAL handleChannelMsg
void EQPacket::handleChannelMsg( const struct channelMessageStruct* t0 )
{
    // No builtin function for signal parameter type const struct channelMessageStruct*
    QConnectionList *clist = receivers("handleChannelMsg(const struct channelMessageStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct channelMessageStruct*);
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

// SIGNAL handleTime
void EQPacket::handleTime( const struct timeOfDayStruct* t0 )
{
    // No builtin function for signal parameter type const struct timeOfDayStruct*
    QConnectionList *clist = receivers("handleTime(const struct timeOfDayStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct timeOfDayStruct*);
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

// SIGNAL handleBookText
void EQPacket::handleBookText( const struct bookTextStruct* t0 )
{
    // No builtin function for signal parameter type const struct bookTextStruct*
    QConnectionList *clist = receivers("handleBookText(const struct bookTextStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct bookTextStruct*);
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

// SIGNAL handleRandom
void EQPacket::handleRandom( const struct randomStruct* t0 )
{
    // No builtin function for signal parameter type const struct randomStruct*
    QConnectionList *clist = receivers("handleRandom(const struct randomStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct randomStruct*);
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

// SIGNAL handleEmote
void EQPacket::handleEmote( const struct emoteTextStruct* t0 )
{
    // No builtin function for signal parameter type const struct emoteTextStruct*
    QConnectionList *clist = receivers("handleEmote(const struct emoteTextStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct emoteTextStruct*);
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

// SIGNAL handlePlayerBook
void EQPacket::handlePlayerBook( const struct bookPlayerStruct* t0 )
{
    // No builtin function for signal parameter type const struct bookPlayerStruct*
    QConnectionList *clist = receivers("handlePlayerBook(const struct bookPlayerStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct bookPlayerStruct*);
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

// SIGNAL handlePlayerCont
void EQPacket::handlePlayerCont( const struct containerPlayerStruct* t0 )
{
    // No builtin function for signal parameter type const struct containerPlayerStruct*
    QConnectionList *clist = receivers("handlePlayerCont(const struct containerPlayerStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct containerPlayerStruct*);
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

// SIGNAL handleInspect
void EQPacket::handleInspect( const struct inspectingStruct* t0 )
{
    // No builtin function for signal parameter type const struct inspectingStruct*
    QConnectionList *clist = receivers("handleInspect(const struct inspectingStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct inspectingStruct*);
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

// SIGNAL handleHPUpdate
void EQPacket::handleHPUpdate( const struct spawnHpUpdateStruct* t0 )
{
    // No builtin function for signal parameter type const struct spawnHpUpdateStruct*
    QConnectionList *clist = receivers("handleHPUpdate(const struct spawnHpUpdateStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct spawnHpUpdateStruct*);
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

// SIGNAL handleSpecialMsg
void EQPacket::handleSpecialMsg( const struct spMesgStruct* t0 )
{
    // No builtin function for signal parameter type const struct spMesgStruct*
    QConnectionList *clist = receivers("handleSpecialMsg(const struct spMesgStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct spMesgStruct*);
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

// SIGNAL handleBeginCast
void EQPacket::handleBeginCast( const struct beginCastStruct* t0 )
{
    // No builtin function for signal parameter type const struct beginCastStruct*
    QConnectionList *clist = receivers("handleBeginCast(const struct beginCastStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct beginCastStruct*);
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

// SIGNAL handleMemSpell
void EQPacket::handleMemSpell( const struct memorizeSlotStruct* t0 )
{
    // No builtin function for signal parameter type const struct memorizeSlotStruct*
    QConnectionList *clist = receivers("handleMemSpell(const struct memorizeSlotStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct memorizeSlotStruct*);
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

// SIGNAL handleSpawnUpdate
void EQPacket::handleSpawnUpdate( const struct spawnPosUpdateStruct* t0 )
{
    // No builtin function for signal parameter type const struct spawnPosUpdateStruct*
    QConnectionList *clist = receivers("handleSpawnUpdate(const struct spawnPosUpdateStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct spawnPosUpdateStruct*);
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

// SIGNAL handleXPUpdate
void EQPacket::handleXPUpdate( const struct expUpdateStruct* t0 )
{
    // No builtin function for signal parameter type const struct expUpdateStruct*
    QConnectionList *clist = receivers("handleXPUpdate(const struct expUpdateStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct expUpdateStruct*);
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

// SIGNAL handleLevelUp
void EQPacket::handleLevelUp( const struct levelUpStruct* t0 )
{
    // No builtin function for signal parameter type const struct levelUpStruct*
    QConnectionList *clist = receivers("handleLevelUp(const struct levelUpStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct levelUpStruct*);
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

// SIGNAL handleSkillUp
void EQPacket::handleSkillUp( const struct skillIncreaseStruct* t0 )
{
    // No builtin function for signal parameter type const struct skillIncreaseStruct*
    QConnectionList *clist = receivers("handleSkillUp(const struct skillIncreaseStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct skillIncreaseStruct*);
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

// SIGNAL handleDoor
void EQPacket::handleDoor( const struct newDoorStruct* t0 )
{
    // No builtin function for signal parameter type const struct newDoorStruct*
    QConnectionList *clist = receivers("handleDoor(const struct newDoorStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct newDoorStruct*);
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

// SIGNAL handleDoorOpen
void EQPacket::handleDoorOpen( const void* t0 )
{
    // No builtin function for signal parameter type const void*
    QConnectionList *clist = receivers("handleDoorOpen(const void*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const void*);
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

// SIGNAL handleIllusion
void EQPacket::handleIllusion( const void* t0 )
{
    // No builtin function for signal parameter type const void*
    QConnectionList *clist = receivers("handleIllusion(const void*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const void*);
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

// SIGNAL handleBadCast
void EQPacket::handleBadCast( const struct interruptCastStruct* t0 )
{
    // No builtin function for signal parameter type const struct interruptCastStruct*
    QConnectionList *clist = receivers("handleBadCast(const struct interruptCastStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct interruptCastStruct*);
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

// SIGNAL handleSysMsg
void EQPacket::handleSysMsg( const struct systemMessageStruct* t0 )
{
    // No builtin function for signal parameter type const struct systemMessageStruct*
    QConnectionList *clist = receivers("handleSysMsg(const struct systemMessageStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct systemMessageStruct*);
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

// SIGNAL handlePlayerPos
void EQPacket::handlePlayerPos( const struct playerUpdateStruct* t0 )
{
    // No builtin function for signal parameter type const struct playerUpdateStruct*
    QConnectionList *clist = receivers("handlePlayerPos(const struct playerUpdateStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct playerUpdateStruct*);
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

// SIGNAL handleEquipChange
void EQPacket::handleEquipChange( const struct equipChangeStruct* t0 )
{
    // No builtin function for signal parameter type const struct equipChangeStruct*
    QConnectionList *clist = receivers("handleEquipChange(const struct equipChangeStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct equipChangeStruct*);
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

// SIGNAL handleAction
void EQPacket::handleAction( const struct actionStruct* t0 )
{
    // No builtin function for signal parameter type const struct actionStruct*
    QConnectionList *clist = receivers("handleAction(const struct actionStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct actionStruct*);
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

// SIGNAL handleCastOn
void EQPacket::handleCastOn( const struct castOnStruct* t0 )
{
    // No builtin function for signal parameter type const struct castOnStruct*
    QConnectionList *clist = receivers("handleCastOn(const struct castOnStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct castOnStruct*);
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

// SIGNAL handleManaUsed
void EQPacket::handleManaUsed( const struct manaDecrementStruct* t0 )
{
    // No builtin function for signal parameter type const struct manaDecrementStruct*
    QConnectionList *clist = receivers("handleManaUsed(const struct manaDecrementStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct manaDecrementStruct*);
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

// SIGNAL handleStamina
void EQPacket::handleStamina( const struct staminaStruct* t0 )
{
    // No builtin function for signal parameter type const struct staminaStruct*
    QConnectionList *clist = receivers("handleStamina(const struct staminaStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct staminaStruct*);
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

// SIGNAL handleNewDrop
void EQPacket::handleNewDrop( const struct addDropStruct* t0 )
{
    // No builtin function for signal parameter type const struct addDropStruct*
    QConnectionList *clist = receivers("handleNewDrop(const struct addDropStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct addDropStruct*);
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

// SIGNAL handleDeleteDrop
void EQPacket::handleDeleteDrop( const struct deleteDropStruct* t0 )
{
    // No builtin function for signal parameter type const struct deleteDropStruct*
    QConnectionList *clist = receivers("handleDeleteDrop(const struct deleteDropStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct deleteDropStruct*);
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

// SIGNAL handleNewCoins
void EQPacket::handleNewCoins( const struct addCoinsStruct* t0 )
{
    // No builtin function for signal parameter type const struct addCoinsStruct*
    QConnectionList *clist = receivers("handleNewCoins(const struct addCoinsStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct addCoinsStruct*);
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

// SIGNAL handleDeleteCoins
void EQPacket::handleDeleteCoins( const struct deleteCoinsStruct* t0 )
{
    // No builtin function for signal parameter type const struct deleteCoinsStruct*
    QConnectionList *clist = receivers("handleDeleteCoins(const struct deleteCoinsStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct deleteCoinsStruct*);
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

// SIGNAL handleOpenVendor
void EQPacket::handleOpenVendor( const void* t0 )
{
    // No builtin function for signal parameter type const void*
    QConnectionList *clist = receivers("handleOpenVendor(const void*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const void*);
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

// SIGNAL handleCloseVendor
void EQPacket::handleCloseVendor( const void* t0 )
{
    // No builtin function for signal parameter type const void*
    QConnectionList *clist = receivers("handleCloseVendor(const void*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const void*);
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

// SIGNAL handleOpenGM
void EQPacket::handleOpenGM( const void* t0 )
{
    // No builtin function for signal parameter type const void*
    QConnectionList *clist = receivers("handleOpenGM(const void*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const void*);
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

// SIGNAL handleCloseGM
void EQPacket::handleCloseGM( const void* t0 )
{
    // No builtin function for signal parameter type const void*
    QConnectionList *clist = receivers("handleCloseGM(const void*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const void*);
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

// SIGNAL handleAttack1
void EQPacket::handleAttack1( const struct attack1Struct* t0 )
{
    // No builtin function for signal parameter type const struct attack1Struct*
    QConnectionList *clist = receivers("handleAttack1(const struct attack1Struct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct attack1Struct*);
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

// SIGNAL handleAttack2
void EQPacket::handleAttack2( const struct attack2Struct* t0 )
{
    // No builtin function for signal parameter type const struct attack2Struct*
    QConnectionList *clist = receivers("handleAttack2(const struct attack2Struct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct attack2Struct*);
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

// SIGNAL handleConsRequest
void EQPacket::handleConsRequest( const struct considerStruct* t0 )
{
    // No builtin function for signal parameter type const struct considerStruct*
    QConnectionList *clist = receivers("handleConsRequest(const struct considerStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct considerStruct*);
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

// SIGNAL handleConsMessage
void EQPacket::handleConsMessage( const struct considerStruct* t0 )
{
    // No builtin function for signal parameter type const struct considerStruct*
    QConnectionList *clist = receivers("handleConsMessage(const struct considerStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct considerStruct*);
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

// SIGNAL handleNewGuild
void EQPacket::handleNewGuild( const struct newGuildStruct* t0 )
{
    // No builtin function for signal parameter type const struct newGuildStruct*
    QConnectionList *clist = receivers("handleNewGuild(const struct newGuildStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct newGuildStruct*);
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

// SIGNAL handleMoneyUpdate
void EQPacket::handleMoneyUpdate( const struct moneyUpdateStruct* t0 )
{
    // No builtin function for signal parameter type const struct moneyUpdateStruct*
    QConnectionList *clist = receivers("handleMoneyUpdate(const struct moneyUpdateStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct moneyUpdateStruct*);
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

// SIGNAL handleMoney
void EQPacket::handleMoney( const void* t0 )
{
    // No builtin function for signal parameter type const void*
    QConnectionList *clist = receivers("handleMoney(const void*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const void*);
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

// SIGNAL handleClientTarget
void EQPacket::handleClientTarget( const struct clientTargetStruct* t0 )
{
    // No builtin function for signal parameter type const struct clientTargetStruct*
    QConnectionList *clist = receivers("handleClientTarget(const struct clientTargetStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct clientTargetStruct*);
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

// SIGNAL handleBindWound
void EQPacket::handleBindWound( const struct bindWoundStruct* t0 )
{
    // No builtin function for signal parameter type const struct bindWoundStruct*
    QConnectionList *clist = receivers("handleBindWound(const struct bindWoundStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct bindWoundStruct*);
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

// SIGNAL handleGroupInfo
void EQPacket::handleGroupInfo( const struct groupMemberStruct* t0 )
{
    // No builtin function for signal parameter type const struct groupMemberStruct*
    QConnectionList *clist = receivers("handleGroupInfo(const struct groupMemberStruct*)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const struct groupMemberStruct*);
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

// SIGNAL unhandledOpCode
void EQPacket::unhandledOpCode( const OpCode& t0, int t1, void* t2, unsigned int t3 )
{
    // No builtin function for signal parameter type const OpCode&,int,void*,unsigned int
    QConnectionList *clist = receivers("unhandledOpCode(const OpCode&,int,void*,unsigned int)");
    if ( !clist || signalsBlocked() )
	return;
    typedef void (QObject::*RT0)();
    typedef void (QObject::*RT1)(const OpCode&);
    typedef void (QObject::*RT2)(const OpCode&,int);
    typedef void (QObject::*RT3)(const OpCode&,int,void*);
    typedef void (QObject::*RT4)(const OpCode&,int,void*,unsigned int);
    RT0 r0;
    RT1 r1;
    RT2 r2;
    RT3 r3;
    RT4 r4;
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
	    case 2:
#ifdef Q_FP_CCAST_BROKEN
		r2 = reinterpret_cast<RT2>(*(c->member()));
#else
		r2 = (RT2)*(c->member());
#endif
		(object->*r2)(t0, t1);
		break;
	    case 3:
#ifdef Q_FP_CCAST_BROKEN
		r3 = reinterpret_cast<RT3>(*(c->member()));
#else
		r3 = (RT3)*(c->member());
#endif
		(object->*r3)(t0, t1, t2);
		break;
	    case 4:
#ifdef Q_FP_CCAST_BROKEN
		r4 = reinterpret_cast<RT4>(*(c->member()));
#else
		r4 = (RT4)*(c->member());
#endif
		(object->*r4)(t0, t1, t2, t3);
		break;
	}
    }
}
