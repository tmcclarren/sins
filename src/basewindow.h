// basewindow.h
//		SINS Distributed under GPL

#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <qwidget.h>
#include <qstring.h>

class BaseWindow: public QWidget
{
Q_OBJECT
public:
	BaseWindow( const QString& caption, QWidget* parent = NULL, const char* name = NULL, WFlags f = 0 );
	~BaseWindow();	
	
	virtual void restoreFromPreferences();
	virtual void saveToPreferences();

	bool shouldShow() { return m_shouldShow; }
	
protected:
	QString		m_name;
	bool		m_shouldShow;
};

#endif
