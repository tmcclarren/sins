/****************************************************************************
** LogMgr meta object code from reading C++ file 'log.h'
**
** Created: Fri Sep 28 13:02:13 2001
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.1   edited 2001-04-23 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "log.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *LogMgr::className() const
{
    return "LogMgr";
}

QMetaObject *LogMgr::metaObj = 0;

void LogMgr::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QObject::className(), "QObject") != 0 )
	badSuperclassWarning("LogMgr","QObject");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString LogMgr::tr(const char* s)
{
    return qApp->translate( "LogMgr", s, 0 );
}

QString LogMgr::tr(const char* s, const char * c)
{
    return qApp->translate( "LogMgr", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* LogMgr::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QObject::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (LogMgr::*m1_t0)(const struct timeOfDayStruct*);
    typedef void (QObject::*om1_t0)(const struct timeOfDayStruct*);
    m1_t0 v1_0 = &LogMgr::handleTime;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    QMetaData *slot_tbl = QMetaObject::new_metadata(1);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(1);
    slot_tbl[0].name = "handleTime(const struct timeOfDayStruct*)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    metaObj = QMetaObject::new_metaobject(
	"LogMgr", "QObject",
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


const char *EQLog::className() const
{
    return "EQLog";
}

QMetaObject *EQLog::metaObj = 0;

void EQLog::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QObject::className(), "QObject") != 0 )
	badSuperclassWarning("EQLog","QObject");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString EQLog::tr(const char* s)
{
    return qApp->translate( "EQLog", s, 0 );
}

QString EQLog::tr(const char* s, const char * c)
{
    return qApp->translate( "EQLog", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* EQLog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QObject::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (EQLog::*m1_t0)();
    typedef void (QObject::*om1_t0)();
    m1_t0 v1_0 = &EQLog::toggleLog;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    QMetaData *slot_tbl = QMetaObject::new_metadata(1);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(1);
    slot_tbl[0].name = "toggleLog()";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    metaObj = QMetaObject::new_metaobject(
	"EQLog", "QObject",
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


const char *SpawnLog::className() const
{
    return "SpawnLog";
}

QMetaObject *SpawnLog::metaObj = 0;

void SpawnLog::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(EQLog::className(), "EQLog") != 0 )
	badSuperclassWarning("SpawnLog","EQLog");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString SpawnLog::tr(const char* s)
{
    return qApp->translate( "SpawnLog", s, 0 );
}

QString SpawnLog::tr(const char* s, const char * c)
{
    return qApp->translate( "SpawnLog", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* SpawnLog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) EQLog::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (SpawnLog::*m1_t0)(const struct zoneSpawnsStruct*,int);
    typedef void (QObject::*om1_t0)(const struct zoneSpawnsStruct*,int);
    typedef void (SpawnLog::*m1_t1)(const struct clientZoneInStruct*);
    typedef void (QObject::*om1_t1)(const struct clientZoneInStruct*);
    typedef void (SpawnLog::*m1_t2)(const struct addSpawnStruct*);
    typedef void (QObject::*om1_t2)(const struct addSpawnStruct*);
    typedef void (SpawnLog::*m1_t3)(const struct deleteSpawnStruct*);
    typedef void (QObject::*om1_t3)(const struct deleteSpawnStruct*);
    typedef void (SpawnLog::*m1_t4)(const struct spawnKilledStruct*);
    typedef void (QObject::*om1_t4)(const struct spawnKilledStruct*);
    m1_t0 v1_0 = &SpawnLog::handleZoneSpawns;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &SpawnLog::handleZoneEnd;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &SpawnLog::handleNewSpawn;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    m1_t3 v1_3 = &SpawnLog::handleDeleteSpawn;
    om1_t3 ov1_3 = (om1_t3)v1_3;
    m1_t4 v1_4 = &SpawnLog::handleCorpse;
    om1_t4 ov1_4 = (om1_t4)v1_4;
    QMetaData *slot_tbl = QMetaObject::new_metadata(5);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(5);
    slot_tbl[0].name = "handleZoneSpawns(const struct zoneSpawnsStruct*,int)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    slot_tbl[1].name = "handleZoneEnd(const struct clientZoneInStruct*)";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Public;
    slot_tbl[2].name = "handleNewSpawn(const struct addSpawnStruct*)";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Public;
    slot_tbl[3].name = "handleDeleteSpawn(const struct deleteSpawnStruct*)";
    slot_tbl[3].ptr = (QMember)ov1_3;
    slot_tbl_access[3] = QMetaData::Public;
    slot_tbl[4].name = "handleCorpse(const struct spawnKilledStruct*)";
    slot_tbl[4].ptr = (QMember)ov1_4;
    slot_tbl_access[4] = QMetaData::Public;
    metaObj = QMetaObject::new_metaobject(
	"SpawnLog", "EQLog",
	slot_tbl, 5,
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


const char *PacketLog::className() const
{
    return "PacketLog";
}

QMetaObject *PacketLog::metaObj = 0;

void PacketLog::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(EQLog::className(), "EQLog") != 0 )
	badSuperclassWarning("PacketLog","EQLog");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString PacketLog::tr(const char* s)
{
    return qApp->translate( "PacketLog", s, 0 );
}

QString PacketLog::tr(const char* s, const char * c)
{
    return qApp->translate( "PacketLog", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* PacketLog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) EQLog::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (PacketLog::*m1_t0)(const void*,int);
    typedef void (QObject::*om1_t0)(const void*,int);
    m1_t0 v1_0 = &PacketLog::handlePacket;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    QMetaData *slot_tbl = QMetaObject::new_metadata(1);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(1);
    slot_tbl[0].name = "handlePacket(const void*,int)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    metaObj = QMetaObject::new_metaobject(
	"PacketLog", "EQLog",
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


const char *OpCodeLog::className() const
{
    return "OpCodeLog";
}

QMetaObject *OpCodeLog::metaObj = 0;

void OpCodeLog::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(EQLog::className(), "EQLog") != 0 )
	badSuperclassWarning("OpCodeLog","EQLog");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString OpCodeLog::tr(const char* s)
{
    return qApp->translate( "OpCodeLog", s, 0 );
}

QString OpCodeLog::tr(const char* s, const char * c)
{
    return qApp->translate( "OpCodeLog", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* OpCodeLog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) EQLog::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (OpCodeLog::*m1_t0)(const OpCode&,int,void*,unsigned int);
    typedef void (QObject::*om1_t0)(const OpCode&,int,void*,unsigned int);
    typedef void (OpCodeLog::*m1_t1)(const OpCode&,int,void*,unsigned int);
    typedef void (QObject::*om1_t1)(const OpCode&,int,void*,unsigned int);
    typedef void (OpCodeLog::*m1_t2)();
    typedef void (QObject::*om1_t2)();
    m1_t0 v1_0 = &OpCodeLog::handleOpCode;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &OpCodeLog::unhandledOpCode;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &OpCodeLog::editOpCodeList;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    QMetaData *slot_tbl = QMetaObject::new_metadata(3);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(3);
    slot_tbl[0].name = "handleOpCode(const OpCode&,int,void*,unsigned int)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    slot_tbl[1].name = "unhandledOpCode(const OpCode&,int,void*,unsigned int)";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Public;
    slot_tbl[2].name = "editOpCodeList()";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Public;
    metaObj = QMetaObject::new_metaobject(
	"OpCodeLog", "EQLog",
	slot_tbl, 3,
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


const char *SessionLog::className() const
{
    return "SessionLog";
}

QMetaObject *SessionLog::metaObj = 0;

void SessionLog::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(EQLog::className(), "EQLog") != 0 )
	badSuperclassWarning("SessionLog","EQLog");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString SessionLog::tr(const char* s)
{
    return qApp->translate( "SessionLog", s, 0 );
}

QString SessionLog::tr(const char* s, const char * c)
{
    return qApp->translate( "SessionLog", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* SessionLog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) EQLog::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (SessionLog::*m1_t0)(const QString&);
    typedef void (QObject::*om1_t0)(const QString&);
    m1_t0 v1_0 = &SessionLog::handleNewMessage;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    QMetaData *slot_tbl = QMetaObject::new_metadata(1);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(1);
    slot_tbl[0].name = "handleNewMessage(const QString&)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    metaObj = QMetaObject::new_metaobject(
	"SessionLog", "EQLog",
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


const char *EncryptedPacketLog::className() const
{
    return "EncryptedPacketLog";
}

QMetaObject *EncryptedPacketLog::metaObj = 0;

void EncryptedPacketLog::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(EQLog::className(), "EQLog") != 0 )
	badSuperclassWarning("EncryptedPacketLog","EQLog");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString EncryptedPacketLog::tr(const char* s)
{
    return qApp->translate( "EncryptedPacketLog", s, 0 );
}

QString EncryptedPacketLog::tr(const char* s, const char * c)
{
    return qApp->translate( "EncryptedPacketLog", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* EncryptedPacketLog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) EQLog::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (EncryptedPacketLog::*m1_t0)(const struct addSpawnStruct*);
    typedef void (QObject::*om1_t0)(const struct addSpawnStruct*);
    typedef void (EncryptedPacketLog::*m1_t1)(const struct zoneSpawnsStruct*,int);
    typedef void (QObject::*om1_t1)(const struct zoneSpawnsStruct*,int);
    typedef void (EncryptedPacketLog::*m1_t2)(const struct playerProfileStruct*);
    typedef void (QObject::*om1_t2)(const struct playerProfileStruct*);
    m1_t0 v1_0 = &EncryptedPacketLog::handleNewSpawn;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &EncryptedPacketLog::handleZoneSpawns;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &EncryptedPacketLog::handlePlayerProfile;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    QMetaData *slot_tbl = QMetaObject::new_metadata(3);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(3);
    slot_tbl[0].name = "handleNewSpawn(const struct addSpawnStruct*)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    slot_tbl[1].name = "handleZoneSpawns(const struct zoneSpawnsStruct*,int)";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Public;
    slot_tbl[2].name = "handlePlayerProfile(const struct playerProfileStruct*)";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Public;
    metaObj = QMetaObject::new_metaobject(
	"EncryptedPacketLog", "EQLog",
	slot_tbl, 3,
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


const char *DatabaseLog::className() const
{
    return "DatabaseLog";
}

QMetaObject *DatabaseLog::metaObj = 0;

void DatabaseLog::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(EQLog::className(), "EQLog") != 0 )
	badSuperclassWarning("DatabaseLog","EQLog");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString DatabaseLog::tr(const char* s)
{
    return qApp->translate( "DatabaseLog", s, 0 );
}

QString DatabaseLog::tr(const char* s, const char * c)
{
    return qApp->translate( "DatabaseLog", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* DatabaseLog::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) EQLog::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (DatabaseLog::*m1_t0)(const ItemStruct&);
    typedef void (QObject::*om1_t0)(const ItemStruct&);
    typedef void (DatabaseLog::*m1_t1)(const struct addSpawnStruct*);
    typedef void (QObject::*om1_t1)(const struct addSpawnStruct*);
    typedef void (DatabaseLog::*m1_t2)(const struct zoneSpawnStruct*);
    typedef void (QObject::*om1_t2)(const struct zoneSpawnStruct*);
    typedef void (DatabaseLog::*m1_t3)(const struct clientZoneInStruct*);
    typedef void (QObject::*om1_t3)(const struct clientZoneInStruct*);
    typedef void (DatabaseLog::*m1_t4)(const struct spawnStruct*);
    typedef void (QObject::*om1_t4)(const struct spawnStruct*);
    typedef void (DatabaseLog::*m1_t5)(const struct containerPlayerStruct*);
    typedef void (QObject::*om1_t5)(const struct containerPlayerStruct*);
    typedef void (DatabaseLog::*m1_t6)(const struct bookPlayerStruct*);
    typedef void (QObject::*om1_t6)(const struct bookPlayerStruct*);
    typedef void (DatabaseLog::*m1_t7)(const struct summonedItemStruct*);
    typedef void (QObject::*om1_t7)(const struct summonedItemStruct*);
    typedef void (DatabaseLog::*m1_t8)(const struct itemPlayerStruct*);
    typedef void (QObject::*om1_t8)(const struct itemPlayerStruct*);
    typedef void (DatabaseLog::*m1_t9)(const struct itemReceivedStruct*);
    typedef void (QObject::*om1_t9)(const struct itemReceivedStruct*);
    typedef void (DatabaseLog::*m1_t10)(const struct tradeItemStruct*);
    typedef void (QObject::*om1_t10)(const struct tradeItemStruct*);
    typedef void (DatabaseLog::*m1_t11)(const struct itemReceivedStruct*);
    typedef void (QObject::*om1_t11)(const struct itemReceivedStruct*);
    m1_t0 v1_0 = &DatabaseLog::logItem;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &DatabaseLog::handleNewSpawn;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &DatabaseLog::handleZoneSpawns;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    m1_t3 v1_3 = &DatabaseLog::handleZoneEnd;
    om1_t3 ov1_3 = (om1_t3)v1_3;
    m1_t4 v1_4 = &DatabaseLog::backfillSpawn;
    om1_t4 ov1_4 = (om1_t4)v1_4;
    m1_t5 v1_5 = &DatabaseLog::handlePlayerCont;
    om1_t5 ov1_5 = (om1_t5)v1_5;
    m1_t6 v1_6 = &DatabaseLog::handlePlayerBook;
    om1_t6 ov1_6 = (om1_t6)v1_6;
    m1_t7 v1_7 = &DatabaseLog::handleSummonedItem;
    om1_t7 ov1_7 = (om1_t7)v1_7;
    m1_t8 v1_8 = &DatabaseLog::handlePlayerItem;
    om1_t8 ov1_8 = (om1_t8)v1_8;
    m1_t9 v1_9 = &DatabaseLog::handleTradeItem;
    om1_t9 ov1_9 = (om1_t9)v1_9;
    m1_t10 v1_10 = &DatabaseLog::handleTradeItem2;
    om1_t10 ov1_10 = (om1_t10)v1_10;
    m1_t11 v1_11 = &DatabaseLog::handleCorpseItem;
    om1_t11 ov1_11 = (om1_t11)v1_11;
    QMetaData *slot_tbl = QMetaObject::new_metadata(12);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(12);
    slot_tbl[0].name = "logItem(const ItemStruct&)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    slot_tbl[1].name = "handleNewSpawn(const struct addSpawnStruct*)";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Public;
    slot_tbl[2].name = "handleZoneSpawns(const struct zoneSpawnStruct*)";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Public;
    slot_tbl[3].name = "handleZoneEnd(const struct clientZoneInStruct*)";
    slot_tbl[3].ptr = (QMember)ov1_3;
    slot_tbl_access[3] = QMetaData::Public;
    slot_tbl[4].name = "backfillSpawn(const struct spawnStruct*)";
    slot_tbl[4].ptr = (QMember)ov1_4;
    slot_tbl_access[4] = QMetaData::Public;
    slot_tbl[5].name = "handlePlayerCont(const struct containerPlayerStruct*)";
    slot_tbl[5].ptr = (QMember)ov1_5;
    slot_tbl_access[5] = QMetaData::Public;
    slot_tbl[6].name = "handlePlayerBook(const struct bookPlayerStruct*)";
    slot_tbl[6].ptr = (QMember)ov1_6;
    slot_tbl_access[6] = QMetaData::Public;
    slot_tbl[7].name = "handleSummonedItem(const struct summonedItemStruct*)";
    slot_tbl[7].ptr = (QMember)ov1_7;
    slot_tbl_access[7] = QMetaData::Public;
    slot_tbl[8].name = "handlePlayerItem(const struct itemPlayerStruct*)";
    slot_tbl[8].ptr = (QMember)ov1_8;
    slot_tbl_access[8] = QMetaData::Public;
    slot_tbl[9].name = "handleTradeItem(const struct itemReceivedStruct*)";
    slot_tbl[9].ptr = (QMember)ov1_9;
    slot_tbl_access[9] = QMetaData::Public;
    slot_tbl[10].name = "handleTradeItem2(const struct tradeItemStruct*)";
    slot_tbl[10].ptr = (QMember)ov1_10;
    slot_tbl_access[10] = QMetaData::Public;
    slot_tbl[11].name = "handleCorpseItem(const struct itemReceivedStruct*)";
    slot_tbl[11].ptr = (QMember)ov1_11;
    slot_tbl_access[11] = QMetaData::Public;
    metaObj = QMetaObject::new_metaobject(
	"DatabaseLog", "EQLog",
	slot_tbl, 12,
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


const char *OpCodeDlg::className() const
{
    return "OpCodeDlg";
}

QMetaObject *OpCodeDlg::metaObj = 0;

void OpCodeDlg::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QDialog::className(), "QDialog") != 0 )
	badSuperclassWarning("OpCodeDlg","QDialog");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString OpCodeDlg::tr(const char* s)
{
    return qApp->translate( "OpCodeDlg", s, 0 );
}

QString OpCodeDlg::tr(const char* s, const char * c)
{
    return qApp->translate( "OpCodeDlg", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* OpCodeDlg::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QDialog::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (OpCodeDlg::*m1_t0)(const QString&);
    typedef void (QObject::*om1_t0)(const QString&);
    typedef void (OpCodeDlg::*m1_t1)();
    typedef void (QObject::*om1_t1)();
    typedef void (OpCodeDlg::*m1_t2)();
    typedef void (QObject::*om1_t2)();
    typedef void (OpCodeDlg::*m1_t3)();
    typedef void (QObject::*om1_t3)();
    m1_t0 v1_0 = &OpCodeDlg::textChanged;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &OpCodeDlg::selectionChanged;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &OpCodeDlg::addOpCode;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    m1_t3 v1_3 = &OpCodeDlg::deleteOpCode;
    om1_t3 ov1_3 = (om1_t3)v1_3;
    QMetaData *slot_tbl = QMetaObject::new_metadata(4);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(4);
    slot_tbl[0].name = "textChanged(const QString&)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    slot_tbl[1].name = "selectionChanged()";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Public;
    slot_tbl[2].name = "addOpCode()";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Public;
    slot_tbl[3].name = "deleteOpCode()";
    slot_tbl[3].ptr = (QMember)ov1_3;
    slot_tbl_access[3] = QMetaData::Public;
    metaObj = QMetaObject::new_metaobject(
	"OpCodeDlg", "QDialog",
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
