// filter.h
//		SINS Distributed under GPL

#ifndef FILTER_H
#define FILTER_H

#include <sys/types.h>
#include <regex.h>

#include <qobject.h>
#include <qstring.h>
#include <qdict.h>
#include <qdialog.h>
#include <qpopupmenu.h>
#include "itemmgr.h"

class Spawn;
class QListView;
class QButton;
class QComboBox;
class QLineEdit;

class Filter
{
public:
	Filter( const QString& filterString, int cFlags = 0 );
	~Filter();

	regex_t			m_regex;
	QString			m_filterString;
	bool			m_active;
};

class FilterList: public QObject
{
Q_OBJECT
public:
	FilterList( const QString& type, int cFlags = 0 );

	bool isFiltered( Spawn* spawn );

	void addFilter( const QString& name ); 
	void deleteFilter( const QString& name ); 

	void listFilters();

	friend class	FilterMgr;
	friend class	FilterDlg;
protected:
	Filter* findFilter( const QString& name );
	
	QString			m_type;
	QDict<Filter>	m_filterList;
	
	char			m_flags;        // flags passed to regcomp
};

class FilterMgr: public QObject
{
Q_OBJECT
public:
	FilterMgr::FilterMgr( const QString& fileName, GameItem::GameItemFlag flags = GameItem::k_none, const char* name = NULL );
	FilterMgr::~FilterMgr();
	
	bool isFiltered( Spawn* spawn );

	void loadFilters();
	void saveFilters();
	void listFilters();
	void addFilter( const QString& type, const QString& filterString );
	void deleteFilter( const QString& type, const QString& filterString );
	bool toggleActive( const QString& type, const QString& filterString );
	
	void resyncSpawns();
	
	friend class	FilterDlg;

public slots:
	void processSpawn( Spawn* spawn );
	
signals:
	void filtersChanged();
	
protected:
	FilterList*	findFilterList( const QString& type );
	
	QDict<FilterList>		m_filterListList;
	GameItem::GameItemFlag	m_flag;	
	QString					m_file;
	bool					m_sync;
};

class Alerter: public FilterMgr
{
Q_OBJECT
public:
	Alerter( const QString& fileName );
	
public slots:
	void addSpawn( Spawn* spawn );
	void deleteSpawn( Spawn* spawn );
	void killSpawn( Spawn* spawn );
	
protected:
	void playAlert();
};

class FilterDlg: public QDialog
{
Q_OBJECT
public:
	FilterDlg::FilterDlg( FilterMgr* filters, const QStringList& filterFields, QWidget* parent = NULL, const char* name = NULL );
	FilterDlg::~FilterDlg();
	
	QSize sizeHint() const;

public slots:
	void textChanged( const QString& newText );
	void selectionChanged();
	void addFilter();
	void deleteFilter();
	void toggleActive();
	
protected:
	void populateFilterList();
	
	QPixmap			m_clear;
	QPixmap			m_checked;

	FilterMgr*		m_filters;
	
	QListView*		m_filterList;
	QPushButton*	m_addButton;
	QPushButton*	m_deleteButton;
	QPushButton*	m_okButton;
	QPushButton*	m_cancelButton;
	QPushButton*	m_activeButton;
	QComboBox*		m_filterOn;
	QLineEdit*		m_filterString;
};

#endif

