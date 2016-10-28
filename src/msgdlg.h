// msgdlg.h
//	SINS distributed under GPL

// Todo:
//
//   Implement coloring based on filter
//   Can MyButton and CButDlg be moved into MsgDialog to avoid namespace issues?
//      I tried and ran into problems with moc... maybe sigs and slots are not
//      supported for a class within a class

#ifndef MSGDLG_H
#define MSGDLG_H

#include <qlist.h>
#include <qwidget.h>
#include <qpushbutton.h>
#include <qmultilineedit.h>
#include <qcheckbox.h>
#include <qdialog.h>
#include <qarray.h>
#include <qregexp.h>
#include <qlayout.h>
#include <qlabel.h>
#include <qpopupmenu.h>

class EditCheckBox;		// button for use in MsgDialog
class CButDlg;   		// dialog for editing a button
class MyEdit;

// MsgDialog
//
// Class provides a topLevel dialog for displaying messages.  Features include:
//
//  - List of checkboxes which can be edited for filters
//  - Configuration of additive or subtractive filtering
//        (a match on a filter will show the message if additive, will
//         filter the message if subtractive)
//  - WordWrapping with indentation
//
// public Slots:
//
//    newMessage(int index)    - the index into the array of strings to add 
//    setAdditive(bool bAdd)   -  change the filter scheme: 
//                                 TRUE is a positive filter, FALSE is negative 
//    setMargin(int nIndent)     { m_nIndent = nIndent; refresh(); }
//
// If you wish to construct and have a list of strings already that you wish 
// to send to the dialog, you can use the constructor to send a stringlist
//

class MsgDialog: public QWidget
{
Q_OBJECT
public:
   MsgDialog( QWidget* parent, const char* name, QStringList &list );

   bool isAdditive() { return m_bAdditiveFilter; }
   int  indentMargin() { return m_nIndent; }
   QRect getRect() { return rect(); }

public slots:
	void newMessage( int );
	void setAdditive( bool bAdd );
	void setMargin( int nIndent );
	void addButton( const QString& name, const QString& filter, const QString& color, bool bAct );
	void toggleControls();
	void setButton( EditCheckBox* but, bool active );
	void showControls( bool );
	void showMsgType( bool );

protected slots:
	void editButton( EditCheckBox* );			// popup button edit dialog
	void addFilter( const QString& );			// add a filter (no refresh)
	void delFilter( const QString& );			// delete a filter (no refresh)
	void refresh();								// refresh msgs based on active filters
	void addFilter( EditCheckBox* );
	void scrollLock( bool );
	void setIndexing( bool );

	// for the popupmenu
	void menuAboutToShow();
	void editButton();
	void addButton();

protected:
	void addMessage(QString &);
	bool eventFilter( QObject*, QEvent* );
  	EditCheckBox* newButton( const QString& name, const QString &filter, const QString& color, bool bAct );
	void rightButtonPressed();
	void appendWithWrap( QString& );
	void applyStyle( QString& );

	bool               m_bScrollLock;
	int                m_nButtons;        // num of buttons (needed for sizing)
	int                m_nIndent;         // spaces to indent
	int                m_nLockIndex;
	int                m_nIndex;
	bool               m_bUseIndexing;
	bool               m_bShowType;
	int                m_nShown;          // num of messages shown
	int                m_nEditItem;

	MyEdit*            m_pEdit;
	QStringList*       m_pStringList;
	QStringList        m_filterList;
	QBoxLayout*        m_pButtonsLayout;
	QCheckBox*         m_pMsgTypeCheckBox;
	QCheckBox*         m_pAdditiveCheckBox;
	QWidget*           m_pButtonsPanel;
 	bool               m_bAdditiveFilter;
	QLabel*            m_pStatusBar;
	QLabel*            m_pStatusBarLock;
	QLabel*            m_pStatusBarMsgcount;
	QLabel*            m_pStatusBarTotMsgcount;
	QLabel*            m_pStatusBarFilter;
	QPopupMenu*        m_pMenu;
	EditCheckBox*      m_pButtonOver;
};


// EditCheckBox - implements a Checkbox button with a filter attached.
//            uses eventFilter to catch right click's over itself to 
//            popup a button edit dialog
//
class EditCheckBox: public QCheckBox
{
Q_OBJECT
public:
	EditCheckBox( const char* name, QWidget* parent, QWidget* owner );

	const QString& name() { return m_name; }
 	const QString& filter() { return m_filter; }
	const QColor& color() { return m_color; }

public slots:
	void setFilter( const QString& string ) { m_filter = string; }
	void setText( const QString& string ) { QButton::setText(string); }
	void toggled( bool on )
	{
		if ( on )
			emit addFilter( m_filter );
		else
			emit delFilter( m_filter );
	}
	void setColor( const QColor& color ) { m_color = color; }

signals:
	void editButton( EditCheckBox* );
	void addFilter( const QString& );
	void delFilter( const QString& );
	void refresh();
	void setButton( EditCheckBox* but, bool active );

protected:
	bool eventFilter( QObject* o, QEvent* e );
	void paintEvent( QPaintEvent* e );

	QString			m_name;
	QString			m_filter;
	QColor			m_color;
	QWidget*		m_pOwner;
};

// CButDlg - implements a configuration editing a EditCheckBox object
class CButDlg: public QDialog
{
Q_OBJECT
public:
	CButDlg( QWidget* parent, QString name, EditCheckBox* but );
}; 


// MyEdit inherits from QMultiLineEdit and overrides some of the functionality
// to provide more what I need
class MyEdit: public QMultiLineEdit
{
Q_OBJECT
public:
	MyEdit( QWidget* parent = NULL, const char* name = NULL );

	void pageDown( bool bSelected ) { QMultiLineEdit::pageDown( bSelected ); }

protected:
	void paintCell( QPainter*, int row, int col );
	bool eventFilter( QObject* o, QEvent* e );
};

#endif

