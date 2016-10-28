//	filter.cpp
//		SINS Distributed under GPL

#include <qfile.h>

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include <qapplication.h>
#include <qcombobox.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qlistview.h>
#include <qpushbutton.h>
#include <qtextstream.h>
#include <qvbox.h>

#include "filter.h"
#include "interface.h"
#include "spawn.h"
#include "spawnlist.h"
#include "preferences.h"
#include "main.h"
#include "player.h"

#define MAXLEN   5000

Filter::Filter( const QString& name, int cFlags )
{
	m_filterString = name;
	m_active = true;
	
	switch ( regcomp( &m_regex, m_filterString, cFlags ) )
	{
		case 0:	// no error
		break;
		case REG_BADRPT:
			fprintf(stderr, "Filter Error: '%s' - ", (const char*)m_filterString );
			fprintf(stderr, "Invalid use of repetition operators such as using '*' as the first character.\n");
		break;
		case REG_BADBR:
			fprintf(stderr, "Filter Error: '%s' - ", (const char*)m_filterString );
			fprintf(stderr, "Invalid use of back reference operator\n");
		break;
		case REG_EBRACE:
			fprintf(stderr, "Filter Error: '%s' - ", (const char*)m_filterString );
			fprintf(stderr, "Un-matched bracket list operators\n");
		break;
		case REG_EBRACK:
			fprintf(stderr, "Filter Error: '%s' - ", (const char*)m_filterString );
			fprintf(stderr, "Un-matched bracket list operators.\n");
		break;
		case REG_ERANGE:
			fprintf(stderr, "Filter Error: '%s' - ", (const char*)m_filterString );
			fprintf(stderr, "Invalid use of the range operator, eg. the ending point of the range occurs prior to the starting point.\n");
		break;
		case REG_ECTYPE:
			fprintf(stderr, "Filter Error: '%s' - ", (const char*)m_filterString );
			fprintf(stderr, "Unknown character class (const char*)m_filterString.\n");
		break;
		case REG_ECOLLATE:
			fprintf(stderr, "Filter Error: '%s' - ", (const char*)m_filterString );
			fprintf(stderr, "Invalid collating element.\n");
		break;
		case REG_EPAREN:
			fprintf(stderr, "Filter Error: '%s' - ", (const char*)m_filterString );
			fprintf(stderr, "Un-matched parenthesis group operators.\n");
		break;
		case REG_ESUBREG:
			fprintf(stderr, "Filter Error: '%s' - ", (const char*)m_filterString );
			fprintf(stderr, "Invalid back reference to a subexpression\n");
		break;
#ifndef __FreeBSD__
		case REG_EEND:
			fprintf(stderr, "Filter Error: '%s' - ", (const char*)m_filterString );
			fprintf(stderr, "Non specific error.\n");
		break;
#endif
		case REG_EESCAPE:
			fprintf(stderr, "Filter Error: '%s' - ", (const char*)m_filterString );
			fprintf(stderr, "Trailing backslash.\n");
		break;
		case REG_BADPAT:
			fprintf(stderr, "Filter Error: '%s' - ", (const char*)m_filterString );
			fprintf(stderr, "Invalid use of pattern operators such as group or list.\n");
		break;
#ifndef __FreeBSD__
		case REG_ESIZE:
			fprintf(stderr, "Filter Error: '%s' - ", (const char*)m_filterString );
			fprintf(stderr, "Compiled regular expression requires a pattern buffer larger than 64 Kb.\n");
		break;
#endif
		case REG_ESPACE:
			fprintf(stderr, "Filter Error: '%s' - ", (const char*)m_filterString );
			fprintf(stderr, "The regex routines ran out of memory\n");
		break;
		}
}

Filter::~Filter()
{
	regfree( &m_regex );
}

FilterList::FilterList( const QString& type, int cFlags ):
	m_filterList( 31 )
{
	m_flags = cFlags;
	m_type = type;

	m_filterList.setAutoDelete( true );
}

bool FilterList::isFiltered( Spawn* spawn )
{
	regmatch_t	matchArray[ 1 ];

#ifdef DEBUG
//   printf("isFiltered(%s)\n", string);
#endif
	QString		filterString = "";
	
	FieldMap<Spawn>::FormatFunc		t = NULL;
	if ( gInterface )
	{
		SpawnListView*		listView = NULL;
		listView = gInterface->spawnList();
		if ( listView )
			t = listView->fieldFormatter( m_type );
	}

	if ( t )
		(*t)( spawn, filterString );

	if ( filterString.isEmpty() )
		return false;
		
	QDictIterator<Filter>	it( m_filterList );
	Filter*		f;

	while ( ( f = it.current() ) )
	{
		++it;
		if ( f->m_active )
			if ( regexec( &( f->m_regex ), filterString, 1, matchArray, m_flags ) != REG_NOMATCH )
			{
				//printf( "spawn %s filtered\n", (const char*)filterString );
				return true;
			}
	}
	//printf( "spawn %s not filtered\n", (const char*)filterString );
	return false;
}

void FilterList::deleteFilter( const QString& filterString )
{
	Filter*	filter;
	
	filter = m_filterList.find( filterString );
	if ( filter )
	{
		m_filterList.remove( filterString );
	
#ifdef DEBUG
		printf( "Removed '%s' from List\n", (const char*)filterString );
#endif
	}
}

void FilterList::addFilter( const QString& filterString )
{
	Filter*	filter;
	
	filter = m_filterList.find( filterString );

	if ( filter )
		return;
	
	filter = new Filter( filterString, m_flags );

	m_filterList.insert( filterString, filter );
	
#ifdef DEBUG
//	printf( "added filter '%s': '%s'\n", (const char*)m_type, (const char*)filterString );
#endif
}

Filter* FilterList::findFilter( const QString& filterString )
{
	Filter*	filter;
	
	filter = m_filterList.find( filterString );
	return filter;
}

void FilterList::listFilters()
{
#ifdef DEBUG
//  debug( "Filter::listFilters()" );
#endif
	QDictIterator<Filter>	it( m_filterList );

	printf( "Filtered on: %s\n", (const char*)m_type ); 
	while ( it.current() )
	{
		printf( "'%s'\n", (const char*)it.current()->m_filterString );
		++it;
	}
}


FilterMgr::FilterMgr( const QString& filterFile, GameItem::GameItemFlag flags, const char* name ):
	QObject( NULL, name ),
	m_filterListList( 7 )
{
	m_file = filterFile;
	m_flag = flags;
	m_sync = false;
	
	this->loadFilters();
	m_sync = true;
}

FilterMgr::~FilterMgr()
{
	this->saveFilters();
}

// isFiltered
// check to see if something is filtered based on current spawn filters
// returns: false = not filtered, true = filtered
bool FilterMgr::isFiltered( Spawn* spawn )
{
	if ( spawn->isFlagSet( GameItem::k_unnamed ) )
		return false;
		
	QString		tempStr;
	
	QDictIterator<FilterList>	it( m_filterListList );
	FilterList*		f;

	while ( ( f = it.current() ) )
	{
		++it;
		if ( f->isFiltered( spawn ) )
		{
//			printf( "spawn %s filtered\n", (const char*)spawn->name() );	
			return true;
		}
	}
//	printf( "spawn %s not filtered\n", (const char*)spawn->name() );
	return false;
}
	
void FilterMgr::listFilters()
{
	QDictIterator<FilterList>	it( m_filterListList );
	FilterList*		f;
	while ( ( f = it.current() ) )
	{
		++it;
		f->listFilters();
	}
}

void FilterMgr::addFilter( const QString& type, const QString& filterString )
{
	FilterList*		filterList = m_filterListList.find( type );

	if ( !filterList )
	{
		filterList = new FilterList( type, REG_ICASE );
		m_filterListList.insert( type, filterList );
	}

	filterList->addFilter( filterString );
	this->resyncSpawns();
}

void FilterMgr::deleteFilter( const QString& type, const QString& filterString )
{
	FilterList*		filterList = m_filterListList.find( type );

	if ( filterList )
	{
		Filter*		filter = filterList->m_filterList.find( filterString );
		if ( filter )
		{
			filterList->deleteFilter( filterString );
			this->resyncSpawns();
		}
	}
}

bool FilterMgr::toggleActive( const QString& type, const QString& filterString )
{
	FilterList*		filterList = m_filterListList.find( type );
	if ( filterList )
	{
		Filter*		filter = filterList->m_filterList.find( filterString );
		if ( filter )
		{
			filter->m_active = !filter->m_active;
			this->resyncSpawns();
			return filter->m_active;
		}
	}
	return false;
}

void FilterMgr::resyncSpawns()
{
	if ( !m_sync )
		return;
		
	QIntDictIterator<Spawn>		it( gItemMgr->spawns() );
	Spawn*		s;

	while ( ( s = it.current() ) )
	{
		++it;

		if ( this->isFiltered( s ) )
			s->setFlag( m_flag );
		else
			s->clearFlag( m_flag );
	}
	emit filtersChanged();
}

void FilterMgr::processSpawn( Spawn* spawn )
{
	if ( this->isFiltered( spawn ) )
		spawn->setFlag( m_flag );
	else
		spawn->clearFlag( m_flag );
}

// loadFilters
// parses the filter file and builds filter list
void FilterMgr::loadFilters()
{
#ifdef DEBUG
//	debug( "FilterMgr::loadFilters()" );
#endif

	QFile		in;
	in.setName( m_file );
	QString		msg;
	
	int			p;

	// free any current list
	m_filterListList.clear();

	// parse spawnfilter file
	if ( !m_file.isEmpty() )
	{
		if ( !in.open( IO_ReadOnly ) )
		{
			fprintf( stderr, "Couldn't open filter file. '%s' - %s\n", (const char*)m_file, strerror( errno ) );
			goto done;
		}

		QString		sType;

		while ( in.readLine( msg, MAXLEN ) > 0 )
		{
			//printf( "line: %s\n", (const char*)msg );
			// treat lines beginning with # or ; as comments
			if ( ( msg[ 0 ] == '#' ) || ( msg[ 0 ] == ';' ) )
				continue;

			msg = msg.stripWhiteSpace();

			if ( msg[ 0 ] == 0 )
				continue;

			// new [Section]
			if ( msg[ 0 ] == '[' )
			{
				p = msg.find( ']' );
				if ( -1 != p )
					sType = msg.mid( 1, p - 1 );
				continue;
			}

			if ( !sType.isNull() && !sType.isEmpty() )
			{
				if ( !msg.isEmpty() )
					this->addFilter( sType, msg );
			}
			else if ( !msg.isEmpty() )
				this->addFilter( "Name", msg );
				
		}
		in.close();
	}

done:
	;
#ifdef DEBUG
	this->listFilters();
#endif
}

void FilterMgr::saveFilters()
{
#ifdef DEBUG
//	debug( "Filter::saveFilters()" );
#endif

	QFile			inFile;
	QFile			outFile;
	QString			msg;

	int				p;

	// save file
	if ( m_file.isEmpty() )
		return;

	QString			infilename = m_file;
	QString			outfilename = m_file + ".new";
		
	inFile.setName( infilename );
	outFile.setName( outfilename );
		
	if ( !inFile.open( IO_ReadOnly ) )
		fprintf( stderr, "Couldn't open filter file: '%s' - %s\n", (const char*)infilename, strerror( errno ) );

	if ( !outFile.open( IO_WriteOnly ) )
	{
		fprintf( stderr, "Couldn't open filter save file: '%s' - %s\n", (const char*)outfilename, strerror( errno ) );
		return;
	}
						
	QString			sType;
	QTextStream		out( &outFile );
		
	while ( inFile.readLine( msg, MAXLEN ) > 0 )
	{
		// preserve blank lines
		if ( msg[ 0 ] == '\n' )
		{
			out << '\n';
			continue;
		}
		
		// treat lines beginning with # or ; as comments
		if ( ( msg[ 0 ] == '#') || ( msg[ 0 ] == ';' ) )
		{
			out << msg;
			continue;
		}
		
		// terminate the line
		msg.stripWhiteSpace();

		// new [Section]
		if ( msg[ 0 ] == '[' )
		{
			p = msg.find( ']' );
			if ( -1 != p )
				sType = msg.mid( 1, p - 1 );
			out << '[' << sType << ']' << '\n';
			FilterList* filterList = m_filterListList.find( sType );
			if ( filterList )
			{
				QDictIterator<Filter>	it( filterList->m_filterList );
				
				while ( it.current() )
				{
					QString		filterString = it.current()->m_filterString;
					out << filterString << '\n';
					++it;
				}
				m_filterListList.remove( sType );
			}
		}

	}
			
	// dump any we have left
	if ( !m_filterListList.isEmpty() )
	{
		QDictIterator<FilterList>	it( m_filterListList );
		
		while ( it.current() )
		{
			out << '[' << it.current()->m_type << ']' << '\n';
			QDictIterator<Filter>	it2( it.current()->m_filterList );
			
			while ( it2.current() )
			{
				out << it2.current()->m_filterString << '\n';
				++it2;
			}
			
			out << '\n';
			++it;
		}
	}

	outFile.close();
	inFile.close();

	// printf ("Filter file saved '%s'\n", outfilename);

	// rename files
	QString		tempStr;
	tempStr = "cp " + infilename + " " + infilename + ".bak";

#ifdef DEBUG
	printf( "%s\n", (const char*)tempStr );
#endif
	if ( -1 == system( tempStr ) )
		fprintf( stderr, "'%s' - failed\n", (const char*)tempStr );

	tempStr = "mv -f ";
	tempStr += outfilename;
	tempStr += " ";
	tempStr += infilename;

#ifdef DEBUG
	printf( "%s\n", (const char*)tempStr );
#endif
	if ( -1 == system( tempStr ) )
		fprintf( stderr, "'%s' - failed\n", (const char*)tempStr );

	m_sync = false;
	this->loadFilters();
	m_sync = true;
}


Alerter::Alerter( const QString& file ):
	FilterMgr( file, GameItem::k_alert, "alerter" )
{
}

void Alerter::playAlert()
{
	// generic system beep for those without a soundcard
	if ( !gSEQPrefs->getPrefBool( "SpawnFilterAudio", "Filters" ) )
		printf( "\a" );
	else
	{
		const char*		command;
		command = gSEQPrefs->getPrefString( "SpawnAudioCommand", "Filters" );
		if ( *command )
			system( command );
	}
}

void Alerter::addSpawn( Spawn* spawn )
{
	if ( !this->isFiltered( spawn ) )
		return;
		
	QString 		tempStr;
		
	if ( !gSEQPrefs->getPrefBool( "AlertInfo", "Filters" ) )
	{
		tempStr = "Spawn: ";
		tempStr += spawn->name();
	}
	else
	{	
		long			timeval;
		struct tm*		tp;

		time( &timeval );
		tp = localtime( &timeval );

		QString		tempStr2;
		tempStr2 = spawn->processEquipment();
		tempStr.sprintf( "Spawn: %s/%s/%s/%s [%d-%d-%d %d:%d:%d] (%d,%d,%d) LVL %d, HP %d/%d  %s",
				(const char*)spawn->name(),
				(const char*)spawn->raceName(),
				(const char*)spawn->className_(),
				(const char*)spawn->lightName(),
				1900 + tp->tm_year,
				tp->tm_mon,
				tp->tm_mday,
				tp->tm_hour,
				tp->tm_min,
				tp->tm_sec,
				spawn->xPos(),
				spawn->yPos(),
				spawn->zPos(),
				spawn->level(),
				spawn->curHp(),
				spawn->maxHp(),
				(const char*)tempStr2 );
	}

	this->playAlert();
}

void Alerter::deleteSpawn( Spawn* spawn )
{
	if ( !gSEQPrefs->getPrefBool( "DeSpawnAlert", "Filters", false ) )
		return;

	QString tempStr1 = "DeSpawn: ";
	
	if ( !this->isFiltered( spawn ) )
		return;
		
	if ( gSEQPrefs->getPrefBool( "AlertInfo", "Filters" ) )
	{
		long			timeval;
		struct tm*		tp;

		time( &timeval );
		tp = localtime( & timeval );
			
		QString tempStr2;

		tempStr2.sprintf( "%s/%s/%s/%s",
				(const char*)spawn->name(),
				(const char*)spawn->raceName(),
				(const char*)spawn->className_(),
				(const char*)spawn->lightName() );
		tempStr1 += tempStr2;
	}
	else 
		tempStr1 += spawn->name();
	
	this->playAlert();
}

void Alerter::killSpawn( Spawn* spawn )
{	
	if ( !this->isFiltered( spawn ) )
		return;
	
	QString			tempStr1( "Died: " );

	long			timeval;
	struct tm*		tp;

	time( &timeval );
	tp = localtime( &timeval );

	QString			tempStr2;
	
	tempStr2 = spawn->processEquipment();

	tempStr2.sprintf( "%s/%s/%s/%s [%d-%d-%d %d:%d:%d] (%d,%d,%d) LVL %d, HP %d/%d  %s",
			(const char*)spawn->name(),
			(const char*)spawn->raceName(),
			(const char*)spawn->className_(),
			(const char*)spawn->lightName(),
			1900 + tp->tm_year,
			tp->tm_mon,
			tp->tm_mday,
			tp->tm_hour,
			tp->tm_min,
			tp->tm_sec,
			spawn->xPos(),
			spawn->yPos(),
			spawn->zPos(),
			spawn->level(),
			spawn->curHp(),
			spawn->maxHp(),
			(const char*)tempStr2 );

	tempStr1 += tempStr2;
	
	this->playAlert();
}

#if 0
// ToggleFilterSelected
//
// This will toggle something from the current filters.  It will use
// the column selected which is changed by 'right clicking' on a column
// in the spawnlist display.
//
// For example:  If you clicked on an 'orc' and then right clicked on the 
//   'Race' column, then hit the hotkey that called this routine
//    all spawns that have a race identical to the orc will be filtered.
//    If a filter already matches this, it will be remmoved.
//
void Map::toggleFilterSelected(void)
{
#ifdef DEBUG
//printf("Map::ToggleFilterSelected() - Selected ID %d, col %d\n", 
//  selectedSpawnId, selectedColumn);
#endif

  int n = ID2Index(selectedSpawnId);

  if (-1 != n)
  {
    // derive filter string based on column selected
    char strBuf[64];
    char *filter = strBuf;
    class Filter* pFilter = NULL;

/*//printf("selectedColumn %d\n", selectedColumn);
    switch(selectedColumn)
    {
      default:
      case 0:    // Name
         filter  = spawns[n].name;
         pFilter = m_filter;
         break;
      case 1:    // level
         sprintf(strBuf, "%d", spawns[n].level);
         pFilter = m_filterLevel;
         break;
      case 2:    // HP's
         sprintf(strBuf, "%d", spawns[n].level);
         pFilter = m_filterHP;
         break;
      case 3:    // MaxHP
         sprintf(strBuf, "%d", spawns[n].level);
         pFilter = m_filterMaxHP;
         break;
      case 8:    // Dist 
         sprintf(strBuf, "%d", calcDist(spawns[n].xPos, spawns[n].yPos));
         pFilter = m_filterDist;
         break;
      case 9:   // Race 
         filter = race_name(spawns[n].race);
         pFilter = m_filterRace;
         break;
      case 10:   // Class 
         filter = class_name(spawns[n].class_);
         pFilter = m_filterClass;
         break;
      case 11:   // Info 
         filter = spawnInfo[n];
         pFilter = m_filterInfo;
         break;
    }
    if (pFilter->isFiltered(filter))
    {
      // Remove this name from the filters 
      pFilter->remFilter(filter);

      // Display spawn info (shoudl put in a statusbar)
      QString temp("");
      temp.sprintf("Removed filter for '%s'", filter);
      emit stsMessage(temp);
    }
    else
    {
      // Filter this name
      pFilter->addFilter(filter);

      // Display spawn info (shoudl put in a statusbar)
      QString temp("");
      temp.sprintf("Added filter for '%s'", filter);
      emit stsMessage(temp);
    } // end else remove

    // Re-apply filters to current spawns and repaint map with changes
    refreshSpawnList();
    refreshMap();

    return;
  }
#ifdef DEBUG
printf("ToggleFilterSelected - cannot find selection\n");
#endif
*/
}
#endif

#include "clear.xpm"
#include "cross.xpm"

FilterDlg::FilterDlg( FilterMgr* filters, const QStringList& filterFields, QWidget* parent, const char* name ):
	QDialog( parent, name, true ),
	m_clear( (const char**)clear_xpm ),
	m_checked( (const char**)cross_xpm )
{
	m_filters = filters;

	QHBoxLayout* hBoxLayout = new QHBoxLayout( this );
	hBoxLayout->setAutoAdd( true );
	m_filterList = new QListView( this );
	m_filterList->setShowSortIndicator( true );
	m_filterList->setAllColumnsShowFocus( true );
	m_filterList->setSelectionMode( QListView::Single );
	m_filterList->addColumn( "Filter On" );
	m_filterList->addColumn( "Regular Expression" );
	m_filterList->addColumn( "Active" );
	
	QVBox*		vBox = new QVBox( this );
	QHBox*		hBox1 = new QHBox( vBox );
	QHBox*		hBox2 = new QHBox( vBox );
	
	new QLabel( "Filter on: ", hBox1 );
	
	m_filterOn = new QComboBox( hBox1 );
	m_filterOn->insertStringList( filterFields );

	new QLabel( "Regular Expression: ", hBox2 );
	m_filterString = new QLineEdit( hBox2 );
	
	m_addButton = new QPushButton( "Add", vBox );
	m_addButton->setEnabled( false );
	m_deleteButton = new QPushButton( "Delete", vBox );
	m_deleteButton->setEnabled( false );
	m_activeButton = new QPushButton( "Active", vBox );
	m_activeButton->setEnabled( false );
	m_okButton = new QPushButton( "OK", vBox );

	this->populateFilterList();
	
	connect( m_okButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
	connect( m_addButton, SIGNAL( clicked() ), this, SLOT( addFilter() ) );
	connect( m_deleteButton, SIGNAL( clicked() ), this, SLOT( deleteFilter() ) );
	connect( m_activeButton, SIGNAL( clicked() ), this, SLOT( toggleActive() ) );
	connect( m_filterString, SIGNAL( textChanged(const QString&) ), this, SLOT( textChanged(const QString&) ) );
	connect( m_filterList, SIGNAL( selectionChanged() ), this, SLOT( selectionChanged() ) );
	
	this->setCaption( "Edit Filters" );
}

FilterDlg::~FilterDlg()
{
}

QSize FilterDlg::sizeHint() const
{
	return QSize( 500, 300 );
}

void FilterDlg::populateFilterList()
{
	m_filterList->clear();
	this->selectionChanged();
	
	if ( !m_filters )
		return;
	
	QDictIterator<FilterList>	it( m_filters->m_filterListList );
			
	while ( it.current() )
	{
		QString		type = it.current()->m_type;
		
		QDictIterator<Filter>	it2( it.current()->m_filterList );
				
		while ( it2.current() )
		{
			QString		filterString = it2.current()->m_filterString;
				
			QListViewItem*	item = new QListViewItem( m_filterList, type, filterString );
			if ( it2.current()->m_active )
				item->setPixmap( 2, m_checked );
			else
				item->setPixmap( 2, m_clear );
			++it2;
		}
		++it;
	}
}

void FilterDlg::textChanged( const QString& newText )
{
	if ( newText.isEmpty() )
		m_addButton->setEnabled( false );
	else
		m_addButton->setEnabled( true );
}

void FilterDlg::selectionChanged()
{
	if ( m_filterList->selectedItem() )
	{
		m_deleteButton->setEnabled( true );
		m_activeButton->setEnabled( true );
	}
	else
	{
		m_deleteButton->setEnabled( false );
		m_activeButton->setEnabled( false );
	}
}

void FilterDlg::addFilter()
{
	QString		type = m_filterOn->currentText();
	QString		filterString = m_filterString->text();
	
	if ( !filterString.isEmpty() && !filterString.isNull() )
	{
		m_filters->addFilter( type, filterString );
		this->populateFilterList();
		m_filterString->clear();
	}
}

void FilterDlg::deleteFilter()
{
	QListViewItem*		selected = m_filterList->selectedItem();
	QString				type = selected->text( 0 );
	QString				filterString = selected->text( 1 );

	m_filters->deleteFilter( type, filterString );
	delete selected;
}

void FilterDlg::toggleActive()
{
	QListViewItem*		selected = m_filterList->selectedItem();
	QString				type = selected->text( 0 );
	QString				filterString = selected->text( 1 );
	
	if ( m_filters->toggleActive( type, filterString ) )
		selected->setPixmap( 2, m_checked );
	else
		selected->setPixmap( 2, m_clear );
}
