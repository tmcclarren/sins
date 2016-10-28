// spawnpointlist.h
//		SINS Distributed under GPL

#ifndef SPAWNPOINTLIST_H
#define SPAWNPOINTLIST_H

#include <qtimer.h>
#include "baselistview.h"
#include "basewindow.h"
#include "listviewwrapper.h"
#include "everquest.h"
#include "spawnmonitor.h"

class EQInterface;
class QListViewItem;

class SpawnPointListView: public BaseListView, public ListViewWrapper<SpawnPoint>
{
Q_OBJECT
public:
	static const FieldMap<SpawnPoint> m_map[];

	SpawnPointListView( QWidget* parent = NULL, const char* name = NULL );

	static void X( SpawnPoint* sp, QString& tmp ) { tmp.sprintf( "%5d", sp->x ); }
	static void Y( SpawnPoint* sp, QString& tmp ) { tmp.sprintf( "%5d", sp->y ); }
	static void Z( SpawnPoint* sp, QString& tmp ) { tmp.sprintf( "%5d", sp->z ); }
	static void TimeRemaining( SpawnPoint* sp, QString& tmp );

public slots:
	void refresh();
	void newSpawnPoint( const SpawnPoint* sp );
	void clear();

protected:
	QTimer*			m_timer;
};

class SpawnPointWindow: public BaseWindow
{
Q_OBJECT
public:
	SpawnPointWindow( const char* name = NULL );
	~SpawnPointWindow();
	
protected:
	SpawnPointListView*		m_spawnPointList;
};

#endif
