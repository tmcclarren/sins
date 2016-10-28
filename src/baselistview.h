// baselistview.h
//		SINS Distributed under GPL

#ifndef BASELISTVIEW_H
#define BASELISTVIEW_H

#include <qlistview.h>
#include <qstringlist.h>

class QWidget;
class BaseListView;

class BaseListView: public QListView
{
Q_OBJECT
public:
	BaseListView( const QString& baseName,
		QWidget* parent = NULL, 
		const char* name = NULL );
	
	QSizePolicy sizePolicy() const;

	virtual void restoreFromPreferences( const QStringList& columnNames );
	virtual void saveToPreferences();

	bool hasColumnSettings() { return m_hasColumnSettings; }

protected:
	int getColumnPrefWidth( const QString& columnName );
	QString	columnShownPrefName( const QString& columnName );
	QString columnWidthPrefName( const QString& columnName );
	void toggleShowColumn( int column );

	bool						m_hasColumnSettings;	
	QString						m_baseName;
};

#endif
