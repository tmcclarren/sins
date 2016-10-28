// util.h
//		SINS Distributed under GPL

#ifndef EQUTIL_H
#define EQUTIL_H

#include <qcolor.h>
#include <qstring.h>

#include "everquest.h"
#include "main.h"

QString Commanate( UDWORD number );
char* getItemNameFromDB( int itemNr );
bool findFile( QString& fileName );

#endif
