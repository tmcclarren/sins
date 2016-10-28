// category.h
//		SINS Distributed under GPL

#ifndef CATEGORY_H
#define CATEGORY_H

#include <qstring.h>
#include <qcombobox.h>
#include <qlist.h>

#ifdef __FreeBSD__
#include <sys/stat.h>
#endif

#include <regex.h>
#include "spawn.h"
#include "itemmgr.h"
#include "spawnlist.h"

class Category
{
public:
	Category( const char* name, const char* filter, const char* filterout );
	~Category();
	
	void createRegex();
	
	QString					m_name;
	QString					m_filter;
	QString					m_filterout;
	
	unsigned long			m_flags;
	regex_t					m_re;
	regex_t					m_reout;
};
	

class CategoryMgr: public QComboBox
{
Q_OBJECT
public:
	CategoryMgr( QWidget* parent = NULL, const char* name = NULL );

	QString spawnFilterString( const Spawn* s, GameItem::GameItemFlag flags );
	
	void addCategory( const QString& name, const QString& filter,
		const QString& filterout );

	void clearCategories();
	
	void loadCategories();

	Category* currentCategory();
	bool isSpawnInCategory( Category* cat, const Spawn* spawn );

protected slots:
	void handleActivate( int index );

signals:
	void categoriesChanged();
	void categoryChanged();
	
protected:
	QList<Category>			m_categories;
};

#endif
