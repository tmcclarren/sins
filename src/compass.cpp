#include "compass.h"
#include <qpainter.h>
#include <qpixmap.h>
#include <qfont.h>

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

Compass::Compass( QWidget* parent, const char *name ):
	QWidget( parent, name )
{
	ang = 0;
	m_dSpawnAngle = -1;
}

void Compass::setAngle( int degrees )
{
	if ( ang == ( ( 360 - degrees ) + 90 ) )
		return;
	ang = ( 360 - degrees ) + 90;
	repaint ( compassRect(), FALSE );
	emit angleChanged( ang );
}

const QRect compass_rect( -3, 0, 40, 6 );

QSize Compass::sizeHint() const
{
	return QSize( 110, 110 );
}

QSizePolicy Compass::sizePolicy() const
{
	return QSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );
}

void Compass::selSpawnUpdate( int x, int y )
{
	// Recalc the mob heading
	m_cMob.x = x;
	m_cMob.y = y;

	this->calcMobHeading();
}

void Compass::calcMobHeading()
{
	int		deltaX, deltaY;
	double	quadRads, quadDegs;

	deltaX = m_cPlayer.x - m_cMob.x;
	deltaY = ( m_cPlayer.y - m_cMob.y ) * -1;

	quadRads = atan2( deltaY, deltaX );

	// convert radians to degrees
	quadDegs = ( quadRads/( 2 * M_PI ) ) * 360;

	// account for stuff in the lower half of the circle
	if ( quadDegs < 0 )
		quadDegs += 360.0;

	m_dSpawnAngle = quadDegs;

	this->repaint( compassRect(), false );
}

QRect Compass::compassRect() const
{
	QRect r( 0, 0, width(), height() );
	r.moveBottomLeft( rect().bottomLeft() );
	return r;
}

void Compass::setPlayer( int x, int y, int /*z*/ )
{
	m_cPlayer.x = x;
	m_cPlayer.y = y;

	if ( m_dSpawnAngle > 0 )
		this->calcMobHeading();
}

void Compass::selectSpawn( QListViewItem* pItem )
{
	QString strTemp;

	if ( pItem )
	{
		// get the x value out of the list item
		strTemp = pItem->text( 4 );
		m_cMob.x = strTemp.toInt();

		// get the x value out of the list item
		strTemp = pItem->text( 5 );
		m_cMob.y = strTemp.toInt();

		//      printf("Mob x: %d, y: %d\n", m_cMob.x, m_cMob.y);
		this->calcMobHeading();
	}
	else
		m_dSpawnAngle = -1;
}

void Compass::paintCompass( QPainter* p )
{
	QRect cr = compassRect();
	QPixmap pix( cr.size() );
	QPainter tmp;
	pix.fill( this, cr.topLeft() );

	tmp.begin( &pix );

	tmp.setBrush( QColor( 64, 64, 64 ) );
	tmp.setPen( darkGray );
	tmp.drawEllipse( 0, 0, pix.width(), pix.height() );
	tmp.setPen( gray );
	tmp.drawLine(0, pix.height() / 2, pix.width(), pix.height() / 2 );
	tmp.drawLine( pix.width() / 2, 0, pix.width() / 2, pix.height() );
	tmp.drawLine( pix.width() / 4, pix.height() / 4, pix.width() - pix.width() / 4, pix.height() -pix.height() / 4 );
	tmp.drawLine( pix.width() - pix.width() / 4, pix.height() / 4, pix.width() / 4, pix.height() - pix.height() / 4 );
	tmp.translate( pix.width() / 2, pix.height() / 2 );

	tmp.rotate( -ang );
	tmp.setBrush( blue );
	tmp.setPen( blue );
	tmp.drawLine( 0 - pix.width() / 4, 0, pix.width() / 2, 0 );
	tmp.drawLine( 0, 0 - pix.height() / 4, 0, pix.height() / 4 );
	tmp.setBrush( red );
	tmp.setPen( red );
	tmp.drawLine( 0, 1, pix.width() / 2, 1 );
	tmp.drawLine( 0, -1, pix.width() / 2, -1 );
	tmp.setBrush( blue );
	tmp.setPen( red );
	tmp.drawEllipse( 0 - 5, 0 - 5, 10, 10 );
	tmp.setBrush( red );
	tmp.setPen( red );
	tmp.drawEllipse( pix.width() / 2 - 2, -2, 4, 4 );

	if ( m_dSpawnAngle > 0 )
	{
		tmp.resetXForm();
		tmp.translate( pix.width() / 2, pix.height() / 2 );
		tmp.rotate( -m_dSpawnAngle );
		tmp.setPen( green );
		tmp.setBrush( green );
		tmp.drawEllipse( pix.width() / 2 - 2, -2, 4, 4 );
	}

	tmp.end();
	p->drawPixmap( cr.topLeft(), pix );
}

void Compass::paintEvent( QPaintEvent* e )
{
	QRect			updateR = e->rect();
	QPainter		p;
	p.begin( this );
	if ( updateR.intersects ( compassRect() ) )
		this->paintCompass( &p );
	p.end();
}
