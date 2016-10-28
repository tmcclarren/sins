//	dropwindow.cpp
//		SINS Distributed under GPL

#include <stdio.h>
#include <stdlib.h>

#include <qlayout.h>
#include <qlistview.h>
#include <qstring.h>
#include <qpushbutton.h>
#include "interface.h"
#include "preferences.h"
#include "main.h"
#include "dropwindow.h"

DropRecord::DropRecord( const ItemStruct& item )
{
	m_item = item;
	m_timeStamp = QDateTime::currentDateTime();
}

const FieldMap<DropRecord> DropListView::m_map[] = {
	{ "Time", DropListView::Time },
	{ "Item", DropListView::Item },
	{ "ID", DropListView::ID },
	{ "Value", DropListView::Value },
	{ NULL, NULL }
};

DropListView::DropListView( QWidget* parent, const char* name ):
	BaseListView( "Drops", parent, name ),
	ListViewWrapper<DropRecord>( m_map, this, 211 )
{
}

void DropListView::newItem( const ItemStruct& item )
{
	DropRecord*		exists = this->getItem( item.item.itemNr );

	if ( exists )
		return;
	
	DropRecord*		newItem = new DropRecord( item );
	this->addItem( (long)item.item.itemNr, newItem );
}

DropWindow::DropWindow( EQInterface* intf, const char* name ):
	BaseWindow( "Drops", NULL, name )
{
	QVBoxLayout* vBoxLayout = new QVBoxLayout( this );
	vBoxLayout->setAutoAdd( true );

	m_dropList = new DropListView( this, "drop-list" );
	m_dropList->restore();
	
	m_lookupButton = new QPushButton( "Lookup", this );
	m_lookupButton->setEnabled( false );

	connect( m_lookupButton, SIGNAL( clicked() ), this, SLOT( lookupItem() ) );
	connect( m_dropList, SIGNAL( selectionChanged() ), this, SLOT( selectionChanged() ) );
	connect( intf, SIGNAL( newItem(const ItemStruct&) ), m_dropList, SLOT( newItem(const ItemStruct&) ) );
}

void DropWindow::selectionChanged()
{
	if ( m_dropList->selectedItem() )
		m_lookupButton->setEnabled( true );
	else
		m_lookupButton->setEnabled( false );
}

void DropWindow::lookupItem()
{
	QListViewItem*		selected = m_dropList->selectedItem();
	if ( selected )
	{
		QString		name = selected->text( 0 );
		QString		browser = gSEQPrefs->getPrefString( "Browser", "Interface", "netscape" );
		QString		url = "http://eqdb.allakhazam.com/itemsearch.html?terms=";
		
		name = name.replace( QRegExp( " " ), "+" );
		
		QString		command = browser;
		command += " ";
		command += url;
		command += name;
		
		if ( -1 == system( command ) )
			printf( "'%s' - failed\n", (const char*)command );
	}
}

DropWindow::~DropWindow()
{
	if ( m_dropList )
		m_dropList->saveToPreferences();
}

