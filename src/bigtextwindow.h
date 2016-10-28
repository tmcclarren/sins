// bigtextwindow.h
//		SINS Distributed under GPL

#ifndef BIGTEXTWINDOW_H
#define BIGTEXTWINDOW_H

#include <qfont.h>
#include <qcolor.h>
#include "basewindow.h"

class QLabel;
class EQInterface;

class BigTextWindow: public BaseWindow
{
Q_OBJECT
public:
	BigTextWindow( EQInterface* intf, const char* name = NULL );
	
public slots:
	void newMessage( const QString& string );
	
	void pickFont();
	void pickColor();
	void pickBackground();

protected:
	QLabel*		m_label;
	QFont		m_font;
	QColor		m_color;
	QColor		m_background;
};

#endif
