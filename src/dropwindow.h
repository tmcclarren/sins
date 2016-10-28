// dropwindow.h
//		SINS Distributed under GPL

#ifndef DROPWINDOW_H
#define DROPWINDOW_H

#include <qdatetime.h>
#include <qstring.h>
#include "basewindow.h"
#include "listviewwrapper.h"
#include "baselistview.h"
#include "everquest.h"

class QListView;
class QPushButton;
class EQInterface;

class DropRecord
{
public:
	DropRecord( const ItemStruct& itemStruct );
	
	ItemStruct		m_item;
	QDateTime		m_timeStamp;
};

class DropListView: public BaseListView, public ListViewWrapper<DropRecord>
{
Q_OBJECT
public:
	static const FieldMap<DropRecord> m_map[];
	
	DropListView( QWidget* parent = NULL, const char* name = NULL );
	
	static void Time( DropRecord* drop, QString& tmp ) { tmp = drop->m_timeStamp.toString(); }
	static void Item( DropRecord* drop, QString& tmp ) { tmp = drop->m_item.item.lore; }
	static void ID( DropRecord* drop, QString& tmp ) { tmp = QString::number( drop->m_item.item.itemNr ); }
	static void Value( DropRecord* drop, QString& tmp ) { tmp = QString::number( drop->m_item.item.cost ); }

public slots:
	void newItem( const ItemStruct& item );
};	
	
class DropWindow: public BaseWindow
{
Q_OBJECT
public:
	DropWindow( EQInterface* intf, const char* name = NULL );
	~DropWindow();
	
public slots:
	void selectionChanged();
	void lookupItem();

protected:
	DropListView*			m_dropList;
	QPushButton*			m_lookupButton;
};

#endif
