// util.cpp
//		SINS Distributed under GPL

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <qcolor.h>
#include "util.h"
#include "opcodes.h"

// generate comma separated string from long int
QString Commanate( UDWORD number )
{
	UDWORD		threeDigits;
	QString		oldstring;
	QString		newstring;

	char		buffer[ 4 ];

	if ( number >= 1000L )
		oldstring = Commanate( number / 1000L );

	threeDigits = number % 1000L;
	if ( oldstring.isNull() )
		sprintf( buffer, "%lu", threeDigits );
	else
		sprintf( buffer, "%03lu", threeDigits );

	if ( oldstring.isNull() )
		newstring = buffer;
	else
		newstring = oldstring + "," + buffer;

	return newstring;
}

char* getItemNameFromDB( int itemNr )
{
	FILE*				idb;
	struct itemStruct	i;
	int					found = 0;

	if ( ( idb = fopen( "~/item.db", "r" ) ) != NULL )
	{
		while ( fread( &i, sizeof( itemStruct ), 1, idb ) )
		{
			if ( itemNr == i.item.itemNr )
			{
				found = 1;
				break;
			}
		}
		fclose( idb );
	}

	if ( !found )
		return "";
	else
		return i.item.lore;
}

#include <qfileinfo.h>
#include <qdir.h>
#include <qstringlist.h>

bool findFile( QString& filename )
{
	bool			found = false;
	
	QFileInfo		fi( filename );
	QDir			dir( fi.dirPath( true ) );	
	QString			fileLower = fi.fileName().lower();
	
	QStringList		dirEntries = dir.entryList();

	for ( QStringList::Iterator it = dirEntries.begin();
			it != dirEntries.end();
			++it )
	{
		QString entry( (*it).lower() );
		if ( entry == fileLower )
		{
			filename = fi.dirPath( true );
			filename += "/";
			filename += *it;
			found = true;
			break;
		}
	}
	return found;
}
