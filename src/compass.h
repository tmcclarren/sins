#ifndef EQCOMPASS_H
#define EQCOMPASS_H

#include <qwidget.h>
#include <qlistview.h>
#include <qsize.h>

struct tCoords
{
	int x;
	int y;
};

class Compass: public QWidget
{
Q_OBJECT
public:
	Compass( QWidget* parent = NULL, const char* name = NULL );

	QSize sizeHint() const;
	QSizePolicy sizePolicy() const;

public slots:
	void setAngle( int degrees );
	void selectSpawn( QListViewItem* );
	void setPlayer( int, int, int );
	void selSpawnUpdate( int x, int y );
signals:
	void angleChanged( int );

protected:
	void paintEvent( QPaintEvent* );

	void paintCompass( QPainter* );
	void calcMobHeading();
	QRect compassRect() const;
	
	int			ang;
	double		m_dSpawnAngle;
	tCoords		m_cPlayer;
	tCoords		m_cMob;
};

#endif
