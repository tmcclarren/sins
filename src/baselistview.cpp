// baselistview.cpp
//		SINS Distributed under GPL

#include <qheader.h>
#include <qstring.h>
#include <qapplication.h>
#include "baselistview.h"
#include "preferences.h"
#include "main.h"

BaseListView::BaseListView( const QString& baseName, QWidget* parent, const char* name ):
	QListView( parent, name )
{
	m_baseName = baseName;
	m_hasColumnSettings = false;

	this->setFont( QApplication::font() );
	this->setShowSortIndicator( true );
	this->setAllColumnsShowFocus( true );
	this->setSelectionMode( Single );
}

QSizePolicy BaseListView::sizePolicy() const
{
	return QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
}

void BaseListView::restoreFromPreferences( const QStringList& columnNames )
{
	int			x = 0;
	QString		columnName;
	QString		columnOrderList;
	int			width;

	m_hasColumnSettings = gSEQPrefs->isPreference( "ColumnOrder", m_baseName );
	
	if ( m_hasColumnSettings )
		columnOrderList = gSEQPrefs->getPrefString( "ColumnOrder", m_baseName );

	do
	{
		if ( m_hasColumnSettings )
		{
			if ( !columnOrderList.isEmpty() )
			{
				int		commaIndex = columnOrderList.find( ',' );
				if ( commaIndex != -1 )
				{
					columnName = columnOrderList.left( commaIndex );
					columnOrderList = columnOrderList.mid( commaIndex + 1 );
				}
				else
				{
					columnName = columnOrderList;
					columnOrderList = "";
				}
			}
			else
				columnName = "";
		}

		else
			columnName = columnNames[ x ];

		if ( columnName.length() )
		{
			width = this->getColumnPrefWidth( columnName );
		
			this->addColumn( columnName );
			this->setColumnWidthMode( x, QListView::Manual );
			this->setColumnWidth( x, width );
		}
		x++;
	}
	while ( columnName.length() );
}

void BaseListView::saveToPreferences()
{
	int			x = 0;
	QString		columnName;
	QString		prefName;
	
	while ( x < this->columns() )
	{
		columnName = this->columnText( x );
		
		if ( !columnName.isEmpty() )
		{
			prefName = this->columnShownPrefName( columnName );
			gSEQPrefs->setPrefBool( prefName, m_baseName, true );
			prefName = this->columnWidthPrefName( columnName );
			gSEQPrefs->setPrefInt( prefName, m_baseName, this->columnWidth( x ) );
		}
		x++;
	}

	QString		columnOrderList;
	for ( x = 0; x < this->columns(); x++ )
	{
		int		section = this->header()->mapToSection( x );
		columnName = this->columnText( section );
		if ( columnOrderList.length() )
			columnOrderList += ",";
		columnOrderList += columnName;
	}
	gSEQPrefs->setPrefValue( "ColumnOrder", m_baseName, columnOrderList );
}			

QString BaseListView::columnShownPrefName( const QString& columnName )
{
	QString		base;
	
	base = columnName;
	base += "Shown";
	
	return base;
}

QString BaseListView::columnWidthPrefName( const QString& columnName )
{
	QString		base;
		
	base = columnName;
	base += "Width";
	
	return base;
}

int BaseListView::getColumnPrefWidth( const QString& columnName )
{
	QString		prefName;
	int			width = 0;
	
	prefName = this->columnShownPrefName( columnName );
	if ( gSEQPrefs->getPrefBool( prefName, m_baseName, true ) )
	{
		prefName = this->columnWidthPrefName( columnName );
		width = gSEQPrefs->getPrefInt( prefName, m_baseName, 40 );
	}
	return width;
}

void BaseListView::toggleShowColumn( int column )
{
	bool		shown;
	int			width;
	QString		prefName;
	QString		columnName;
	
	columnName = this->columnText( column );
	if ( columnName.isEmpty() )
		return;
		
	prefName = this->columnShownPrefName( columnName );
	shown = gSEQPrefs->getPrefBool( prefName, m_baseName, true );
	
	gSEQPrefs->setPrefBool( prefName, m_baseName, !shown );
	if ( shown )
		this->setColumnWidth( column, 0 );
	else
	{
		prefName = this->columnWidthPrefName( columnName );
		width = gSEQPrefs->getPrefInt( prefName, m_baseName, 40 );
		this->setColumnWidth( column, width );
	}
}

