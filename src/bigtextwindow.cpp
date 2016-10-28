// bigtextwindow.cpp
//		SINS Distributed under GPL

#include <qcolordialog.h>
#include <qfontdialog.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qmenubar.h>
#include <qpalette.h>
#include <qpopupmenu.h>
#include <qstring.h>
#include "interface.h"
#include "bigtextwindow.h"

BigTextWindow::BigTextWindow( EQInterface* intf, const char* name ):
	BaseWindow( "Messages", NULL, name )
{
	QVBoxLayout*		layout = new QVBoxLayout( this );
	layout->setAutoAdd( true );

	QPopupMenu*	myMenu = new QPopupMenu( this );
	myMenu->insertItem( "Font", this, SLOT( pickFont() ) );
	myMenu->insertItem( "Color", this, SLOT( pickColor() ) );
	myMenu->insertItem( "Background", this, SLOT( pickBackground() ) );
	QMenuBar*	myMenuBar = new QMenuBar( this );
	myMenuBar->insertItem( "&View", myMenu );

	
	m_label = new QLabel( this, "text" );
	m_label->setSizePolicy( QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding ) );
	m_label->setAutoResize( true );
	m_font = QFont( "Helvetica", 36 );

	m_label->setFont( m_font );
	m_label->setText( "Can you read this?" );
	//this->setCaption( "Messages" );
	connect( intf, SIGNAL( newMessage( const QString& ) ), this, SLOT( newMessage( const QString& ) ) );	
}

void BigTextWindow::newMessage( const QString& newMsg )
{
	m_label->setText( newMsg );
}

void BigTextWindow::pickFont()
{
	QFont		newFont = m_font;
	bool		ok;
	newFont = QFontDialog::getFont( &ok, newFont, this );
	if ( ok )
	{
		m_label->setFont( newFont );
		m_font = newFont;
	}
}

void BigTextWindow::pickColor()
{
	QColor		newColor;
	newColor = QColorDialog::getColor( m_color, this );
	m_color = newColor;
	QPalette	palette( m_color, m_background );
	m_label->setPalette( palette );
}

void BigTextWindow::pickBackground()
{
	QColor		newColor;
	newColor = QColorDialog::getColor( m_color, this );
	m_background = newColor;
	QPalette	palette( m_color, m_background );
	m_label->setPalette( palette );
}

