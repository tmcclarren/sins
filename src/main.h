//	main.h
//		SINS Distributed under GPL

#ifndef __MAIN_H__
#define __MAIN_H__

#include "../conf.h"

class Player;
class ItemMgr;
class GroupMgr;
class EQPacket;
class FilterMgr;
class Alerter;
class PreferenceFile;
class QApplication;
class QStringList;
class MapMgr;
class LogMgr;
class SpawnMonitor;
class SpellMgr;
class EQInterface;

extern Player*					gPlayer;
extern ItemMgr*					gItemMgr;
extern GroupMgr*				gGroupMgr;
extern EQPacket*				gPacket;
extern FilterMgr*				gFilterMgr;
extern Alerter*					gAlerter;
extern PreferenceFile*			gSEQPrefs;
extern MapMgr*					gMapMgr;
extern LogMgr*					gLogMgr;
extern SpawnMonitor*			gSpawnMonitor;
extern SpellMgr*				gSpellMgr;
extern EQInterface*				gInterface;

#endif
