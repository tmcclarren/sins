// basewindow.cpp
//		SINS Distributed under GPL

#include <qstring.h>
#include <stdio.h>
#include "qregexp.h"
#include "basewindow.h"
#include "preferences.h"
#include "main.h"

BaseWindow::BaseWindow( const QString& caption, QWidget* parent, const char* name, WFlags f ):
	QWidget( parent, name, f )
{
	m_name = caption;
	m_name.stripWhiteSpace();
	m_name.replace( QRegExp( "\\s" ), "" );	
	this->setCaption( caption );
	this->restoreFromPreferences();
}

BaseWindow::~BaseWindow()
{
//	printf( "%s base window destructor called\n", (const char*)m_name );
	if ( gSEQPrefs )
		this->saveToPreferences();
}

void BaseWindow::restoreFromPreferences()
{
	QSize	s = this->size();
	QPoint	p = this->pos();

	int			x, y, w, h;

	x = gSEQPrefs->getPrefInt( "WindowX", m_name, p.x() );
	y = gSEQPrefs->getPrefInt( "WindowY", m_name, p.y() );
	w = gSEQPrefs->getPrefInt( "WindowW", m_name, s.width() );
	h = gSEQPrefs->getPrefInt( "WindowH", m_name, s.height() );

//	printf( "resizing %d/%d\n", w, h );
	this->resize( w, h );

//	printf( "moving window to %d/%d\n", x, y );
	this->move( x, y );

	if ( gSEQPrefs->isPreference( "Title", m_name ) )
		this->setCaption( QString( gSEQPrefs->getPrefString( "Title", m_name ) ) );

	m_shouldShow = false;
	if ( gSEQPrefs->getPrefBool( "Shown", m_name, false ) )
	{
//		printf( "showing %s\n", (const char*)m_name );
		m_shouldShow = true;
	}
}

void BaseWindow::saveToPreferences()
{
	QString		tmp;
	QRect		r;
	int			x, y;
	
	r = this->frameGeometry();

	x = gSEQPrefs->getPrefInt( "WindowXOffset", m_name, 0 );
	y = gSEQPrefs->getPrefInt( "WindowYOffset", m_name, 0 );

	gSEQPrefs->setPrefInt( "WindowX", m_name, r.left() + x );
	gSEQPrefs->setPrefInt( "WindowY", m_name, r.top() + y );
	gSEQPrefs->setPrefInt( "WindowW", m_name, this->width() );
	gSEQPrefs->setPrefInt( "WindowH", m_name, this->height() );
	gSEQPrefs->setPrefBool( "Shown", m_name, !this->isHidden() );
	
//	printf( "saving X/Y/W/H %d/%d/%d/%d\n", r.left(), r.top(), this->width(), this->height() );
}


