// listviewwrapper.h
//		SINS Distributed under GPL

#ifndef LISTVIEWWRAPPER_H
#define LISTVIEWWRAPPER_H

#include <qstringlist.h>
#include <qvaluelist.h>
#include <qintdict.h>
#include <stdio.h>

// why is this like this?
//	Qt doesn't deal with templates because of 'moc', so in order to templatize a
//	class inside the Qt hierarchy, you need to create a secondary wrapper class,
//	not derived from QObject (and, consequently, also not using SIGNAL/SLOT),
//	and glom that onto the side of your derived class (i.e., this particular
//	template class is glommed onto the side of QListView), using multiple inheritance
//	if you want to see how this particular class is used, you can look at
//	the StatListView or SpawnListView classes, that latter is a slightly more
//	complicated use, since it is derived from it's own parent class that is
//	itself derived from this parent template class
//	it's not very pretty, but it works -- once 'moc' deals with templates, it
//	won't be necessary

class QWidget;
class QListViewItem;
class BaseListView;


// a FieldMap is a simple class for getting strings into the columns of a list
//	view.  the "m_fieldName" is the list view header, and "m_formatter" is a ptr.
//	to a function that takes whatever class "T" the list view is displaying,
//	as an argument, and returns whatever string is supposed to go in column
//	"m_fieldName" for that particular instance of T
template < class T >
class FieldMap
{
public:
	QString				m_fieldName;
	typedef void		(*FormatFunc)( T*, QString& );
	FormatFunc			m_formatter;
//	void				(*m_formatter)( T*, QString& );
};

// a RowMap is a class which makes a mapping of instances of "T" to their
//	respective "rows" in a QListView.  "m_listViewItem" here will be a ptr.
//	to the actual QListViewItem inside the QListView that represents "m_item".
//	this class is used by the ListViewWrapper to connect QListViewItems (or
//	subclasses thereof) to "T"s
template < class T >
class RowMap
{
public:
	RowMap( QListViewItem* listItem, T* item )
	{
		m_item = item;
		m_listViewItem = listItem;
	}
	
	~RowMap()
	{
		m_listViewItem = NULL;
		m_item = NULL;
	}

	QListViewItem*	m_listViewItem;
	T*				m_item;
};

// if you are trying to display class "T" inside a QListView, inherit this class
//	alongside QListView, and a lot of your insertion/deletion can be handled for
//	you... also, because the ListViewWrapper deals with objects derived from
//	BaseListView, saving/restoring of column settings is automatic.
//	ListViewWrapper deals with a dictionary object that holds instances

//	of class "T", which means you need keys for insertion/deletion...
//	but, what if you don't have a unique key for representing T?
//	simple, use the ptr. to T itself, coerced to an int.
//
//	one important thing to note about this class, is that the last
//	parameter to the constructor, "dictSize", should be set correctly.
//	setting it too small will impact performance negatively
//	it should be prime, and it should be bigger than the largest number
//	of instances of T you expect to be stored at one time
template < class T >
class ListViewWrapper
{
public:
	ListViewWrapper( const FieldMap<T> map[],
		BaseListView* view,
		int dictSize = 17 ):
			m_items( dictSize )
	{
		m_items.setAutoDelete( true );
		m_listView = view;
		
		int				x = 0;
		const char*		tmp = map[ x ].m_fieldName;
		
		while ( tmp )
		{
			m_map << map[ x++ ];
			tmp = map[ x ].m_fieldName;
		}
		
		this->populateHeader();
	}
			
	ListViewWrapper( const QValueList<FieldMap<T> >& map,
		BaseListView* view,
		int dictSize = 17 ):
			m_items( dictSize )
	{
		m_items.setAutoDelete( true );
		m_listView = view;
		m_map = map;
	
		this->populateHeader();
	}

	virtual ~ListViewWrapper() 
	{
	}

	void populateHeader()
	{
		QStringList		headers = this->getColumnNames();
		
		int x = 0;
		QString		aHeader = headers[ x++ ];
		
		while ( !aHeader.isNull() )
		{
			m_listView->setColumnText( x, aHeader );
			aHeader = headers[ x++ ];
		}
	}
	
	QStringList getColumnNames()
	{
		QStringList		columns;
	
		int items = m_map.count();

		int x = 0;
	
		while ( items-- )
			columns << ( m_map[ x++ ].m_fieldName );
	
		return columns;
	}
	
	void addItem( long key, T* newItem )
	{
		RowMap<T>*		rowMap = m_items.find( key );
	
		if ( rowMap )
			return;
	
		QListViewItem*	newListViewItem = this->createNewListItem( newItem );
		RowMap<T>*		newRowMap = new RowMap<T>( newListViewItem, newItem );
	
		m_items.insert( key, newRowMap );
		this->updateItem( key );
	}
	
	void deleteItem( long key )
	{
		RowMap<T>*		rowMap = m_items.find( key );
		if ( rowMap && rowMap->m_listViewItem )
		{
			delete rowMap->m_listViewItem;
			rowMap->m_listViewItem = NULL;
		}	
		m_items.remove( key );
	}
		
	void updateItem( long key )
	{
		int		columns = m_listView->columns();
	
		RowMap<T>*			rowMap = m_items.find( key );
		if ( !rowMap )
			return;
		
		QString			text;
		T*				item = rowMap->m_item;
		QListViewItem*	listItem = rowMap->m_listViewItem;
		
		while ( columns-- )
		{
			(* ( m_map[ columns ] ).m_formatter )( item, text );
			listItem->setText( columns, text );
		}
	}

	void updateItem( RowMap<T>* rowMap )
	{
		
		int		columns = m_listView->columns();

		QString			text;
		QListViewItem*	listItem = rowMap->m_listViewItem;
		T*				item = 	rowMap->m_item;

#ifdef DEBUG
		if ( !listItem || !item )
			printf( "missing item or list item!\n" );
#endif
		
		while ( columns-- )
		{
			(* ( m_map[ columns ] ).m_formatter )( item, text );
			listItem->setText( columns, text );
		}
	}

	void updateAll()
	{

		QIntDictIterator<RowMap<T> >	it( m_items );
	
		while ( it.current() )
		{
			RowMap<T>*	rowMap = it.current();
			++it;
			this->updateItem( rowMap );
		}
	}
	
	T* getItem( long key )
	{
		RowMap<T>*			rowMap = m_items.find( key );
		if ( rowMap )
			return rowMap->m_item;
	
		return NULL;
	}
	
	void restore()
	{
		QStringList	list = this->getColumnNames();
		m_listView->restoreFromPreferences( list );
		if ( m_listView->hasColumnSettings() )
		{
			int			columns = m_listView->columns();

			QValueList<FieldMap<T> >			newMap;

			QString		header;
		
			for ( int i = 0; i < columns; i++ )
			{
				header = m_listView->columnText( i );
				QValueList<FieldMap<T> >::Iterator	it;

				for ( it = m_map.begin(); it != m_map.end(); ++it )
				{
					if ( (*it).m_fieldName == header )
					{
						newMap << *it;
						break;

					}
				}
			}
			m_map = newMap;
		}
	}

	virtual	QListViewItem* createNewListItem( T* )
	{
		QListViewItem*	newItem = new QListViewItem( m_listView );
		return newItem;
	}

	FieldMap<T>::FormatFunc fieldFormatter( const QString& fieldName )
	{
		int				x = 0;
		QString			tmp = m_map[ x ].m_fieldName;
	
		while ( tmp.length() && ( tmp != fieldName ) )
		{
			x++;
			tmp = m_map[ x ].m_fieldName;
		}
	
		if ( !tmp.length() )
			return NULL;

		return m_map[ x ].m_formatter;
	}

protected:
	QValueList<FieldMap<T> >	m_map;
	BaseListView*				m_listView;
	QIntDict<RowMap<T> >		m_items;
};

//template < class T > QValueList<FieldMap<T> >	ListViewWrapper<T>::m_map;

#endif
