// category.cpp
//		SINS Distributed under GPL

#include "category.h"
#include "preferences.h"
#include "main.h"
#include <stdlib.h>
#include <stdio.h>

Category::Category( const char* name, const char* filter, const char* filterout )
{
	m_name = name;
	m_filter = filter;
	m_filterout = filterout;
	m_flags = 0;
	
	this->createRegex();
}

void Category::createRegex()
{
	char 	buf[ 1024 ];
	int		error;
	
	if ( !m_filter.isEmpty() )
	{
		if ( ( error = regcomp( &m_re, m_filter, REG_EXTENDED | REG_ICASE ) ) )
		{
			regerror( error, &m_re, buf, sizeof( buf ) );
			fprintf( stderr, "category regex error: '%s' - '%s'\n", (const char*)m_filter, buf ); 
		}
	}
	
	if ( !m_filterout.isEmpty() )
	{
		if ( ( error = regcomp( &m_reout, m_filterout, REG_EXTENDED | REG_ICASE ) ) )
		{
			regerror( error, &m_reout, buf, sizeof( buf ) );
			fprintf( stderr, "category regex error: '%s' - '%s'\n", (const char*)m_filterout, buf );
		}
	}
}	

Category::~Category()
{
	regfree( &m_re );
	regfree( &m_reout );
}

CategoryMgr::CategoryMgr( QWidget* parent, const char* name ):
	QComboBox( false, parent, name )
{
	this->loadCategories();

	connect( this, SIGNAL(activated(int)), this, SLOT(handleActivate(int)) );
}

void CategoryMgr::addCategory( const QString& name, const QString& filter,
	const QString& filterout )
{
	Category*		cat = new Category( name, filter, filterout );
	m_categories.append( cat );
	this->insertItem( name );
	emit categoriesChanged();
}

void CategoryMgr::clearCategories()
{
}

QString CategoryMgr::spawnFilterString( const Spawn* s, GameItem::GameItemFlag flags )
{
	QString		temp;
	
	temp.sprintf( "%s%s%s%s%s",
		( flags & GameItem::k_hidden ) ? "Hidden:" : "",
		( flags & GameItem::k_filtered ) ? "Filtered:" : "",
		( flags & GameItem::k_aggressor ) ? "Aggressor:" : "",
		( flags & GameItem::k_highlight ) ? "Highlight:" : "",
		(const char*)s->filterString() );

	return temp;
}

void CategoryMgr::loadCategories()
{
	this->clearCategories();
	
	int			i;
	QString		tempStr;
	
	for ( i = 1; i < 25; i++ )
	{
		// attempt to pull a button title from the preferences
		tempStr.sprintf( "Category%d_Name", i );
		if ( gSEQPrefs->isPreference( tempStr, "SpawnList" ) )
		{
			QString		name;
			QString		filter;
			QString		filterout;
			
			name = gSEQPrefs->getPrefString( tempStr, "SpawnList" );
			tempStr.sprintf( "Category%d_Filter", i );
			filter = gSEQPrefs->getPrefString( tempStr, "SpawnList" );
			tempStr.sprintf( tempStr, "Category%d_Hidden", i );
			tempStr.sprintf( "Category%d_FilterOut", i );
			if ( gSEQPrefs->isPreference( tempStr, "SpawnList" ) )
				filterout = tempStr;	
	
//			printf( "%d: Got '%s' '%s'\n", i, (const char*)name, (const char*)filter );
			if ( !name.isEmpty() && !filter.isEmpty() )
				this->addCategory( name,  filter, filterout );
		}
	}
}

Category* CategoryMgr::currentCategory()
{
	int			i = this->currentItem();
	
	Category*	cat = m_categories.at( i );

	return cat;
}

bool CategoryMgr::isSpawnInCategory( Category* cat, const Spawn* spawn )
{
	if ( !cat )
		return true;
		
	regmatch_t				matchArray[ 1 ];
	int						eflags = 0;
	
	regex_t* regex = &( cat->m_re );

	QString		filterString = this->spawnFilterString( spawn, GameItem::k_none );

	if ( regexec( regex, filterString, 1, matchArray, eflags ) == REG_NOMATCH )
		return false;
		
	QString			filterout = cat->m_filterout;
	
	if ( !filterout.isEmpty() )

	{
		regex = &( cat->m_reout );
		if ( regexec( regex, filterString, 1, matchArray, eflags ) )
			return false;
	}

	return true;
}
	
void CategoryMgr::handleActivate( int /*index*/ )
{
#ifdef DEBUG
	debug( "CategoryMgr::handleActivate()" );
#endif
	emit categoryChanged();
}
