// map.cpp
//		SINS Distributed under GPL

#include "map.h"

#include <qaccel.h>
#include <qapplication.h>
#include <qbuttongroup.h>
#include <qcolordialog.h>
#include <qcombobox.h>
#include <qevent.h>
#include <qfiledialog.h>
#include <qfont.h>
#include <qfontdialog.h>
#include <qfontmetrics.h>
#include <qlayout.h>
#include <qmenubar.h>
#include <qpainter.h>
#include <qpopupmenu.h>
#include <qspinbox.h>

#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "filter.h"
#include "finder.h"
#include "itemmgr.h"
#include "main.h"
#include "player.h"
#include "preferences.h"
#include "spawnlist.h"
#include "spawnmonitor.h"
#include "util.h"

#define INIT_FOV_SIZE	200

#define MAX_ZOOM_STEP	6

const unsigned short Map::m_gridSteps[] = { 1000, 500, 250, 100, 50, 25, 10 };

MapLine::MapLine( const QArray<Location>& locs, const QString& color, const QString& name, eLineType type ):
	m_locations( locs ), m_color( color ), m_name( name ), m_type( type ), m_bounds( 0, 0, 0, 0 )
{
	this->determineBounds();
}

MapLine::MapLine( const Location& l, const QString& color, const QString& name ):
	m_locations( 1 ), m_color( color ), m_name( name ), m_type( e3d ), m_bounds( 0, 0, 0, 0 )
{
	m_locations[ 0 ] = l;
	this->determineBounds();
}

MapLine::MapLine( WORD x, WORD y, WORD z, const QString& color, const QString& name ):
	m_locations( 1 ), m_color( color ), m_name( name ), m_type( e3d ), m_bounds( 0, 0, 0, 0 )
{
	m_locations[ 0 ] = 	Location( x, y, z );
	this->determineBounds();
}

MapLine::MapLine( WORD x, WORD y, const QString& color, const QString& name ):
	m_locations( 1 ), m_color( color ), m_name( name ), m_type( e2d ), m_bounds( 0, 0, 0, 0 )
{
	m_locations[ 0 ] = 	Location( x, y, 0 );
	this->determineBounds();
}

void MapLine::determineBounds()
{
	QCOORD		minX, minY, maxX, maxY;
	
	minX = minY = INT_MAX;
	maxX = maxY = INT_MIN;
	
//	if ( m_locations.size() == 0 )
//		printf( "line with no points!\n" );
	for ( unsigned long i = 0; i < m_locations.size(); i++ )
	{
		Location&	a = m_locations[ i ];
//		printf( "testing point: %d   x, y: %d %d\n", i, a.x, a.y );
		if ( a.x < minX )
			minX = a.x;
		if ( a.x > maxX )
			maxX = a.x;
		if ( a.y < minY )
			minY = a.y;
		if ( a.y > maxY )
			maxY = a.y;
	}
//	printf( "min/maxX: %d  %d  min/maxY: %d  %d\n", minX, maxX, minY, maxY );
	m_bounds = QRect( QPoint( minX, minY ), QPoint( maxX, maxY ) );
}
		
LineDlg::LineDlg( QWidget* parent, QString name, MapMgr* map ):
	QDialog( parent, name, false )
{
#ifdef DEBUG
//	debug( "LineDlg::LineDlg()" );
#endif

	this->setCaption( "Line Properties" );
	
	MapMgr*				pMap = map;

	QHBoxLayout* 		hBoxLayout = new QHBoxLayout( this );
	
	hBoxLayout->setAutoAdd( true );
	
	QVBox*				top = new QVBox( this );
	QHBox*				row2 = new QHBox( top );
	QHBox*				row1 = new QHBox( top );

	new QLabel( "Color: ", row1 );

	m_LineColor = new QComboBox( false, row1, "LineColor" );
	m_LineColor->insertItem( "gray" );
	m_LineColor->insertItem( "darkBlue" );
	m_LineColor->insertItem( "darkGreen" );
	m_LineColor->insertItem( "darkCyan" );
	m_LineColor->insertItem( "darkRed" );
	m_LineColor->insertItem( "darkMagenta" );
	m_LineColor->insertItem( "darkYellow" );
	m_LineColor->insertItem( "darkGray" );
	m_LineColor->insertItem( "white" );
	m_LineColor->insertItem( "blue" );
	m_LineColor->insertItem( "green" );
	m_LineColor->insertItem( "cyan" );
	m_LineColor->insertItem( "red" );
	m_LineColor->insertItem( "magenta" );
	m_LineColor->insertItem( "yellow" );
	m_LineColor->insertItem( "white" );

	m_LineColor->setFixedHeight( m_LineColor->sizeHint().height() );
	m_LineColor->setFixedWidth( m_LineColor->sizeHint().width() );

	m_ColorPreview = new QFrame( row1 );
	m_ColorPreview->setFrameStyle( QFrame::Box | QFrame::Raised );
	m_ColorPreview->setFixedWidth( 50 );
	m_ColorPreview->setFixedHeight( m_LineColor->sizeHint().height() );
	m_ColorPreview->setPalette( QPalette( QColor( gray ) ) );

	// hook on when a color changes
	connect( m_LineColor, SIGNAL( activated( const QString& ) ), map, SLOT( setLineColor( const QString& ) ) );
	connect( m_LineColor, SIGNAL( activated( const QString& ) ), SLOT( changeColor( const QString& ) ) );

	new QLabel ( "Name: ", row2 );

	m_LineName  = new QLineEdit( row2, "LineName" );
	m_LineName->setFixedHeight( m_LineName->sizeHint().height() );
	m_LineName->setFixedWidth( 150 );

	// hook on when the line name changes
	connect( m_LineName, SIGNAL( textChanged( const QString& ) ), map, SLOT( setLineName( const QString& ) ) );

	QPushButton*	ok = new QPushButton( "OK", top );

	// hook on pressing the OK button
	connect( ok, SIGNAL( clicked() ), SLOT( accept() ) );

	for ( int i = 0; i < m_LineColor->count(); i++ )
	{
		if ( m_LineColor->text( i ) == pMap->currentLineColor() )
		{
			m_LineColor->setCurrentItem( i );
			break;
		}
	}
		
	m_LineName->setText( pMap->currentLineName() );
	//setFixedSize(175, 80); 
}

void LineDlg::changeColor( const QString& color )
{
#ifdef DEBUG
//	debug( "LineDlg::changeColor()" );
#endif

	m_ColorPreview->setPalette( QPalette( QColor( color ) ) );
}

MapPopup::MapPopup():
	QLabel( NULL,
			"map-popup",
			WStyle_StaysOnTop + WStyle_Customize + WStyle_NoBorder + WStyle_Tool )
{
	this->setMargin( 1 );
	this->setIndent( 0 );
	this->setAutoMask( false );
	this->setFrameStyle( QFrame::Plain | QFrame::Box );
	this->setLineWidth( 1 );
	this->setAlignment( AlignLeft | AlignTop );
	this->polish();
	this->setText( "" );
	this->adjustSize();
}

void MapPopup::position( const QPoint& mousePoint )
{
	QWidget*		desktop = QApplication::desktop();
	
	int height = desktop->height();
	int width = desktop->width();
	
	QSize mySize = this->frameSize();
	
	QPoint loc = mousePoint;
	
	loc -= QPoint( ( mySize.width() / 2 ), ( mySize.height() + 4 ) );
	
	if ( loc.x() < 0 )
		loc.setX( 0 );
		
	if ( loc.y() < 0 )
		loc.setY( 0 );
		
	if ( ( loc.x() + mySize.width() )  > width )
		loc.setX( width - mySize.width() );
	
	if ( ( loc.y() + mySize.height() ) > height )
		loc.setY( height - mySize.height() );

	this->move( loc );
}

DepthControlBox::DepthControlBox( QWidget* parent, Map* myMap, const char* name ):
	QVBox( parent, name )
{
	m_map = myMap;

	QVBoxLayout* 	vBoxLayout = new QVBoxLayout( this );
	vBoxLayout->setAutoAdd( true );

	m_ceilingText = new QLabel( "", this, "ceiling-text" );
	m_ceilingText->setAlignment( AlignRight );

	QHBox*			hBox = new QHBox( this );	
	m_floorSlider = new DepthSlider( hBox, "floor-slider" );
	m_ceilingSlider = new DepthSlider( hBox, "ceiling-slider" );
	m_floorSlider->setTickmarks( QSlider::Right );
	m_ceilingSlider->setTickmarks( QSlider::Left );

	m_floorText = new QLabel( "", this, "floor-text" );

	connect( gPlayer, SIGNAL( zposChanged( int ) ), this, SLOT( updateZPos( int ) ) );
	connect( m_floorSlider, SIGNAL( valueChanged(int) ), this, SLOT( __setFloor(int) ) );
	connect( m_ceilingSlider, SIGNAL( valueChanged(int) ), this, SLOT( __setCeiling(int) ) );	
	connect( gItemMgr, SIGNAL( zoneEnd(const QString&) ), this, SLOT( zoneEnd(const QString&) ) );
	connect( gMapMgr, SIGNAL( mapLoaded() ), this, SLOT( mapLoaded() ) );
}

void DepthControlBox::zoneEnd( const QString& )
{
/*	WORD		minZ, maxZ;
	int			myMin, myMax;

	myMin = m_floorSlider->minValue();
	myMax = m_floorSlider->maxValue();

	gItemMgr->determineHeight( minZ, maxZ );
	if ( ( minZ < myMin ) || ( maxZ > myMax ) )
	{
		if ( minZ < myMin )
			myMin = minZ;
		if ( maxZ > myMax )
			myMax = myMax;
		this->setRange( myMin, myMax );
	}
*/
}

void DepthControlBox::mapLoaded()
{
	WORD		minZ, maxZ;
	int			myMin, myMax;

	myMin = m_floorSlider->minValue();
	myMax = m_floorSlider->maxValue();

	minZ = gMapMgr->minZ();
	maxZ = gMapMgr->maxZ();

	printf( "map z: %d %d\n", minZ, maxZ );

	if ( ( minZ < myMin ) || ( maxZ > myMax ) )
	{
		if ( minZ < myMin )
			myMin = minZ;
		if ( maxZ > myMax )
			myMax = myMax;
		this->setRange( myMin, myMax );
	}
}

void DepthControlBox::updateZPos( int zPos )
{
	if ( m_map->__getPrefBool( "LockFilterControls", true ) )
	{
		int floor = m_map->__getPrefInt( "UnderfeetDepth", 0 );
		int ceiling = m_map->__getPrefInt( "OverheadDepth", 0 );
		
		m_floorSlider->setValue( -( zPos - floor ) );
		m_floorText->setText( QString::number( -m_floorSlider->value() / 10 ) );
		m_ceilingSlider->setValue( -( zPos + ceiling ) );
		m_ceilingText->setText( QString::number( -m_ceilingSlider->value() / 10 ) );
	}
			
	m_floorSlider->repaint();
	m_ceilingSlider->repaint();
}

void DepthControlBox::resetControls()
{
	m_ceilingSlider->setValue( INT_MIN );
	m_floorSlider->setValue( INT_MAX );
}

void DepthControlBox::setFloor( int newFloor )
{
	int diff = gPlayer->zPos() - newFloor;
	
	m_map->__setPrefInt( "UnderfeetDepth", diff );
	if ( this->getCeiling() < newFloor )
		m_ceilingSlider->setValue( -newFloor );
	m_floorText->setText( QString::number( this->getFloor() / 10 ) );
}
	
void DepthControlBox::__setFloor( int newFloor )
{
	this->setFloor( -newFloor );
	emit floorChanged( -newFloor );
}

void DepthControlBox::setCeiling( int newCeiling )
{
	int diff = newCeiling - gPlayer->zPos();
	m_map->__setPrefInt( "OverheadDepth", diff );
	if ( this->getFloor() > newCeiling )
		m_floorSlider->setValue( -newCeiling );
	m_ceilingText->setText( QString::number( this->getCeiling() / 10 ) );
}

void DepthControlBox::__setCeiling( int newCeiling )
{
	this->setCeiling( -newCeiling );
	emit ceilingChanged( -newCeiling );
}

void DepthControlBox::setRange( int minZ, int maxZ )
{
	int	minDiff = maxZ - minZ;

	if ( minDiff < 100 )
		minDiff = 100;

	// add 10% slop
	int slop = (int) ( minDiff * .1 );
	if ( slop < 10 )
		slop = 10;
	
	m_floorSlider->setRange( -( maxZ + slop ), -( minZ - slop ) );
	m_ceilingSlider->setRange( -( maxZ + slop ), -( minZ - slop ) );
	
	int range = m_floorSlider->maxValue() - m_floorSlider->minValue();
	
	m_floorSlider->setTickInterval( range / 20 );
	m_ceilingSlider->setTickInterval( range / 20 );
	
	m_floorSlider->repaint();
	m_ceilingSlider->repaint();

	int		newFloor = -( m_floorSlider->value() );
	int		newCeiling = -( m_ceilingSlider->value() );

	m_floorText->setText( QString::number( newFloor / 10 ) );
	m_ceilingText->setText( QString::number( newCeiling / 10 ) );

	emit floorChanged( newFloor );
	emit ceilingChanged( newCeiling );
}

DepthSlider::DepthSlider( QWidget* parent, const char* name ):
	QSlider( QSlider::Vertical, parent, name )
{
}

void DepthSlider::paintSlider( QPainter* p, const QColorGroup& cg, const QRect& r )
{
	QSlider::paintSlider( p, cg, r );
	
	int playerPos = this->positionFromValue( - ( gPlayer->zPos() ) );

	p->setPen( gray );
	p->setBrush( gray );

	if ( this->tickmarks() == QSlider::Right )
		p->drawEllipse( this->width() - 3, playerPos, 6, 6 );
	else
		p->drawEllipse( -3, playerPos, 6, 6 );
}

int DepthSlider::available() const
{
    int a;
    switch ( (GUIStyle)style() )
	{
		case WindowsStyle:
			a = ( this->orientation() == Horizontal ) ?
				width() - style().sliderLength() :
				height() - style().sliderLength();
		break;
		default:
		case MotifStyle:
			a = ( this->orientation() == Horizontal ) ?
				width() - style().sliderLength() - 4 :
				height() - style().sliderLength() - 4;
		break;
	}
	return a;
}

int DepthSlider::positionFromValue( int v ) const
{
	int  a = this->available();
	return QRangeControl::positionFromValue( v, a );
}

ZoomButton::ZoomButton( const QString& title, QWidget* parent ):
	QPushButton( title, parent )
{
}

void ZoomButton::drawButton( QPainter* tmp )
{
//	QPushButton::drawButton( tmp );
	if ( this->isOn() )
		tmp->fillRect( 0, 0, this->width(), this->height(), QColor( 255, 255, 0 ) );
	this->drawButtonLabel( tmp );
}

ZoomControlBox::ZoomControlBox( QWidget* parent, Map* myMap, const char* name ):
	QHBox( parent, name )
{
	m_map = myMap;

	this->setBackgroundMode( PaletteBase );
	m_buttonGroup = new QButtonGroup( NULL, "zoom-control-button-group" );
	m_buttonGroup->setExclusive( true );

	for ( int i = 1; i <= ( MAX_ZOOM_STEP + 1 ); i++ )
	{
		ZoomButton*		newButton;
		QString			buttonTitle;
		buttonTitle = QString::number( i );
		buttonTitle += "x";
		newButton = new ZoomButton( buttonTitle, this );
		newButton->setFixedSize( 14, 16 );
		newButton->setToggleButton( true );
		newButton->setFlat( true );
		newButton->setBackgroundMode( PaletteBase );
		m_buttonGroup->insert( newButton );
	}
	this->setFixedHeight( 20 );
	this->setMargin( 0 );
	this->setFrameStyle( QFrame::Panel | QFrame::Sunken );
	this->setLineWidth( 2 );
	int		savedZoom = m_map->__getPrefInt( "ZoomLevel", 0 );
	this->zoomChanged( savedZoom );
	connect( m_buttonGroup, SIGNAL( pressed(int) ), m_map, SLOT( setZoom(int) ) );
}

void ZoomControlBox::zoomChanged( int newZoom )
{
	m_buttonGroup->blockSignals( true );
	int				turnMeOn = newZoom;
	for ( int i = MAX_ZOOM_STEP; i >= 0; i-- )
	{
		QButton*		but = m_buttonGroup->find( i );
		bool			canEnable = m_map->canZoom( i );
		if ( !canEnable )
			turnMeOn = i - 1;
		but->setEnabled( canEnable );
	}
	if ( newZoom > turnMeOn )
		newZoom = turnMeOn;
	m_buttonGroup->setButton( newZoom );
	m_buttonGroup->blockSignals( false );
}

MapMgr::MapMgr( const char* name ):
	QObject( NULL, name )
{
	m_curLineColor = "gray";

	m_lineProps = NULL;

	m_number = 0;
	this->init();
	
	connect( gItemMgr, SIGNAL(zoneBegin()), this, SLOT(zoneBegin()) );
	connect( gItemMgr, SIGNAL(zoneEnd(const QString&)), this, SLOT(zoneEnd(const QString&)) );
	connect( gItemMgr, SIGNAL(zoneChanged(const QString&)), this, SLOT(zoneChanged(const QString&)) );
}

void MapMgr::init()
{
	m_maxX = 50;
	m_maxY = 50;
	m_maxZ = 2000;
	m_minX = -50;
	m_minY = -50;
	m_minZ = -2000;
	m_mapLengthX = 100;
	m_mapLengthY = 100;
	m_xtranslate = 0;
	m_ytranslate = 0;
	
	m_mapLoaded = false;
	m_mapImageLoaded = false;
	m_zoneLoaded = false;
	m_zoneName = "-unknown-";
	m_mapFileName = CONFDIR "unknown.map";
}

void MapMgr::zoneBegin()
{
	qDebug( "MapMgr::zoneBegin()" );
	m_zoneLoaded = true;
}

void MapMgr::zoneEnd( const QString& newZoneName )
{
	qDebug( "MapMgr::zoneEnd()" );
	
	if ( m_zoneName != newZoneName )
		this->zoneChanged( newZoneName );
		
	m_zoneLoaded = true;
	emit zoneLoaded();
}

void MapMgr::zoneChanged( const QString& newZoneName )
{
	qDebug( "MapMgr::zoneChanged()" );
	
	m_zoneLoaded = false;
	m_zoneName = newZoneName;	
	m_mapFileName = CONFDIR;
	m_mapFileName += newZoneName;
	m_mapFileName += ".map";
	
	this->loadFileMap( m_mapFileName );
}

void MapMgr::changeImageXTranslation( int newXTranslate )
{
	m_xtranslate = newXTranslate;
}

void MapMgr::changeImageYTranslation( int newYTranslate )
{
	m_ytranslate = newYTranslate;
}

void MapMgr::setLineName( const QString& name )
{
	MapLabel*		label = m_labels.last();
	
	if ( label )
		label->m_name = name;

	m_curLineName = name;
}


void MapMgr::setLineColor( const QString& color )
{
	MapLabel*		label = m_labels.last();
	
	if ( label )
		label->m_color = color;

	m_curLineColor = color;
}


void MapMgr::showLineDlg()
{
   // create the line properties dialog the first time it is needed
	if ( m_lineProps == NULL )
		m_lineProps = new LineDlg( NULL, "LineDlg", this );

	m_lineProps->show();
}

bool MapMgr::checkPos( const Location& loc )
{
	qDebug( "Map::checkPos()" );

	bool		flag = false;

	if ( loc.x && loc.y )
	{
		if ( loc.x > m_maxX )
		{
			m_maxX = loc.x;
			flag = true;
		}
		
		if ( loc.x < m_minX )
		{
			m_minX = loc.x;
			flag = true;
		}
		
		if ( loc.y > m_maxY )
		{
			m_maxY = loc.y;
			flag = true;
		}
		
		if ( loc.y < m_minY )
		{
			m_minY = loc.y;
			flag = true;
		}

		if ( loc.z > m_maxZ )
			m_maxZ = loc.z;
		
		if ( loc.z < m_minZ )
			m_minZ = loc.z;
		
#ifdef DEBUG
//		printf( "in x: %i, in y: %i, max( %i, %i ) min( %i, %i )\n", x, y, m_maxX, m_maxY, m_minX, m_minY );
#endif
	}
	return flag;
}

void MapMgr::saveMap()
{
#ifdef DEBUG
	debug( "MapMgr::saveMap()" );
#endif

	FILE*					fh;
	int						globHeight = 0;

	if ( ( fh = fopen( m_mapFileName, "w" ) ) == NULL )
	{
		printf( "Error saving map '%s'!\n", (const char*)m_mapFileName );
		return;
	}

	fprintf( fh, "%s,%s,%d,%d,%d,%d,%d,%d\n",
		(const char*)gItemMgr->longZoneName(),
		(const char*)gItemMgr->shortZoneName(),
	    0,
	   	0,
	    0,
	    0,
	    m_mapLengthX,
	    m_mapLengthY );
        if ( gItemMgr->getZEM() != 75 )
            fprintf( fh, "Z,%i\n", gItemMgr->getZEM() );

	MapLine*		line = m_lines.first();
	while ( line )
	{
		// don't save lines where they just hit the line button
		if ( line->m_locations.count() <= 1)
			continue;

		int			ptCount = line->m_locations.size();
		Location	loc;		
		if ( line->m_type == MapLine::e2d )
		{
			loc = line->m_locations[ 0 ];
			if ( globHeight != loc.z )
			{
				fprintf( fh, "H,%i\n", loc.z );
				globHeight = loc.z;
			}
			fprintf( fh, "L,%s,%s,%d", (const char*)line->m_name, (const char*)line->m_color, ptCount );
		}
		else
			fprintf( fh, "M,%s,%s,%d", (const char*)line->m_name, (const char*)line->m_color, ptCount );

		int			i = 0;
		while ( i++ < ptCount )
		{
			loc = line->m_locations[ i ];
			fprintf( fh, ",%d,%d", loc.x, loc.y);
		
			// 3 dimensions
			if ( line->m_type == MapLine::e3d )
				fprintf( fh, ",%d", loc.z );
		}
		fprintf( fh, "\n" );
		line = m_lines.next();
	}
	
	MapLabel*		label = m_labels.first();
	while ( label )
	{
		fprintf( fh, "P,%s,%s,%d,%d\n",
			(const char*)label->m_name,
			(const char*)label->m_color,
			label->m_location.x,
			label->m_location.y );

		label = m_labels.next();
	}


//	for ( int n = 0; n < numAggroInfo; n++ )
//	{
//		fprintf (fh, "A,%s,%d\n", aggroInfo[n].name, aggroInfo[n].range);
//	}

#ifdef DEBUG
	printf( "saveMap() - map '%s' saved with %d lines, %d locations\n", (const char*)m_mapFileName, m_lines.count(), m_labels.count() );
#endif
	fclose( fh );
}

void MapMgr::loadMap()
{
#ifdef DEBUG
//	debug( "MapMgr::loadMap()" );
#endif

	this->init();
	
	QString s( QFileDialog::getOpenFileName( CONFDIR, "*.map" ) );

	if ( s.isNull() )
		return;

	m_mapFileName = s;
	
	this->loadFileMap( m_mapFileName );
}

void MapMgr::loadFileMap( const QString& filename )
{
#ifdef DEBUG
//	debug( "MapMgr::loadFileMap()" );
#endif
	FILE*				fh;
	
	char				line[ MAX_LINE_LENGTH ];
	char				tempstr[ MAX_LINE_LENGTH ];
	char*				tempStr;
	int					mx, my, mz;
	int					globHeight = 0;
	int					filelines = 1;  // number of lines in map file
	const char*			fileNameChr;
	QString				fileEntry( filename );

	emit mapUnloaded();
	
	m_mapLoaded = false;
	
	gItemMgr->setZEM( 75 );

	// free up memory from old map
	m_lines.clear();
	m_labels.clear();
	
	gItemMgr->determineBounds( m_minX, m_maxX, m_minY, m_maxY, m_minZ, m_maxZ );

	fileNameChr = (const char*)fileEntry;
//	printf( "file: %s\n", (const char*)fileEntry );
	if ( ( fh = fopen( fileEntry, "r" ) ) == NULL )
	{
		if ( !findFile( fileEntry ) )
			return;
		fileNameChr = (const char*)fileEntry;
//		printf( "file: %s\n", (const char*)fileEntry );
		if ( ( fh = fopen( fileEntry, "r" ) ) == NULL )
		{
			printf( "Error opening map file '%s'!\n", fileNameChr );
			return;
		}
	}
			
	if ( fgets( line, MAX_LINE_LENGTH, fh ) == NULL)
	{
		printf( "Error reading map file '%s'!\n", fileNameChr );
		return;
	}
	filelines = 1;

	// zone name
	tempStr = strtok( line, "," );
	if ( tempStr == NULL )
	{
		printf( "Error reading zone name in map '%s'!\n", fileNameChr );
		return;
	}
	// strcpy(zoneLong, tempStr);

	// zone short name
	tempStr = strtok( line, "," );
	if ( tempStr == NULL )
	{
		printf( "Error reading short name in map '%s'!\n", fileNameChr );
		return;
	}
	// strcpy(zoneShort, tempStr);
		
	// zone size in X direction
	tempStr = strtok( line, "," );
	if ( tempStr == NULL )
	{
		printf( "Error reading X size in map '%s'!\n", fileNameChr );
		return;
	}
	m_mapLengthX = atoi( tempStr );

	// zone size in Y direction
	tempStr = strtok( line, "\n" );
	if ( tempStr == NULL )
	{
		printf( "Error reading Y size in map '%s'!\n", fileNameChr );
		return;
	}
	m_mapLengthY = atoi( tempStr );

	// for each line of file
	while	(	( filelines < MAX_LINES ) &&
				( fgets( line, MAX_LINE_LENGTH, fh ) != NULL )
			)
	{
		//printf("line = '%s'\n", line );
		filelines++;
		strcpy( tempstr, strtok( line, "," ) );
		switch ( tempstr[ 0 ] )
		{
			case 'A':  // creates aggro ranges
			{
				//printf( "Aggro test\n" );
				//tempStr = strtok( NULL, ",\n" );
				//	if ( tempStr == NULL )
				//	{
				//		printf("Line %d in map '%s' has an A marker with no Name expression!\n", filelines, filename);
				//		break;
				//	}
				//	strncpy( aggroInfo[ numAggroInfo ].name, tempStr, 128 );
				//	printf( "%s and %s\n", aggroInfo[ numAggroInfo ].name, tempStr );
				//	tempStr = strtok( NULL, ",\n" );
				//	if ( tempStr == NULL )
				//	{
				//		printf("Line %d in map '%s' has an A marker with no Range radius!\n", filelines, filename);
				//		break;
				//	}
				//	aggroInfo[ numAggroInfo ].range = atoi( tempStr );
				//	numAggroInfo++;
			}
			break;
				
			case 'H':  // sets global height for L lines
			{
				tempStr = strtok( NULL, ",\n" );
				if ( tempStr == NULL )
				{
					printf("Line %d in map '%s' has an H marker with no Z!\n", filelines, fileNameChr);
					break;
				}
				globHeight = atoi( tempStr );
			}
			break;
				
			case 'Z':  // quick and dirty ZEM implementation
			{
				tempStr = strtok( NULL, ",\n" );
				if ( tempStr == NULL )
				{
					printf( "Line %d in map '%s' has an Z marker with no ZEM!\n", filelines, fileNameChr );
					break;
				}
				gItemMgr->setZEM( atoi( tempStr ) );
				//printf( "ZEM set to %d\n", gItemMgr->getZEM() );
			}
			break;
				
			case 'L':
			case 'M':
			{
				// L = 0, M = 1
				MapLine::eLineType	type = MapLine::e2d;
				QString				color;
				QString				name;
				QList<Location>		locs;

				if ( ( tempstr[ 0 ] - 'L' ) > 0 )
					type = MapLine::e3d;
					
				// line name
				name = strtok( NULL, "," );
				if ( name.isNull() )
				{
					printf( "Error reading line name on line %d in map '%s'!\n", filelines, fileNameChr );
					return;
				}
	
				// line color
				color = strtok( NULL, "," );
				if ( color.isNull() )
				{
					printf( "Error reading line color on line %d in map '%s'!\n", filelines, fileNameChr );
					return;
				}

				int				totalPoints;
				// number of points
				tempStr = strtok( NULL, "," );
				if ( tempStr == NULL )
				{
					printf( "Error reading number of points on line %d in map '%s'!\n", filelines, fileNameChr );
					return;
				}
				totalPoints = atoi( tempStr );

				QArray<Location>	ptArray( totalPoints );
				int					numPoints = 0;
				int					curPointMax = totalPoints - 1;
				
				while ( 1 )
				{
					mx = my = mz = 0;

					// X coord
					tempStr = strtok( NULL, ",\n" );
					if ( tempStr == NULL )
						break;
					mx = atoi( tempStr );

					// Y coord
					tempStr = strtok( NULL, ",\n" );
					if ( tempStr == NULL )
					{
						printf( "Line %d in map '%s' has an X coordinate with no Y!\n", filelines, fileNameChr );
						break;
					}
					my = atoi( tempStr );

					// three dimensions
					if ( type == MapLine::e3d )
					{
						// Z coord
						tempStr = strtok( NULL, ",\n" );
						if ( tempStr == NULL )
						{
							printf("Line %d in map '%s' has X and Y coordinates with no Z!\n", filelines, fileNameChr);
							break;
						}
						mz = atoi( tempStr );
						if ( mz > 4000 || mz < -4000 )
							printf( "Large z value '%d' on line '%d' in map '%s'!\n", mz, filelines, fileNameChr );
					}	
					else
						mz = globHeight;

					// allocate space for the point
					Location		newLoc = Location( mx, my, mz );
					
					ptArray[ numPoints++ ] = newLoc;
					if ( numPoints > curPointMax )
					{
						curPointMax = ptArray.count() + 20;
						ptArray.resize( curPointMax );
					}
					
					// if point isn't inside map dimensions, change map size
					if ( mx > m_maxX ) m_maxX = mx;
					if ( my > m_maxY ) m_maxY = my;
					if ( mx < m_minX ) m_minX = mx;
					if ( my < m_minY ) m_minY = my;
					if ( mz > m_maxZ ) m_maxZ = mz;
					if ( mz < m_minZ ) m_minZ = mz;

				}
				
				ptArray.resize( numPoints );
				
				if ( numPoints > totalPoints )
					printf( "Line %d in map '%s' has more points than specified!\n", filelines, fileNameChr );
				else if ( numPoints < totalPoints )
					printf( "Line %d in map '%s' has fewer points than specified!\n", filelines, fileNameChr );

				filelines++;
					
				MapLine* newLine = new MapLine( ptArray, color, name, type );
				m_lines.append( newLine );					
			}
			break;

			case 'P':
			{
				QString		name;
				QString		color;
				WORD		x;
				WORD		y;
				MapLabel*	newMapLabel;
					
				name = QString( strtok( NULL, "," ) );	// location name
				color = QString( strtok( NULL, "," ) );	// location color
				x = atoi( strtok( NULL, ",\n" ) );
				y = atoi( strtok( NULL, ",\n" ) );

				newMapLabel = new MapLabel( x, y, color, name );
				m_labels.append( newMapLabel );
					
				// if map label isn't inside map dimensions, change map size
				if ( x > m_maxX ) m_maxX = x;
				if ( x < m_minX ) m_minX = x;
				if ( y > m_maxY ) m_maxY = y;
				if ( y < m_minY ) m_minY = y;
			}
			break;
		}
	}
	
	fclose( fh );

	m_mapImageLoaded = false;
	QString mapImageFileName = filename;
	mapImageFileName.truncate( mapImageFileName.findRev( '.' ) );
	mapImageFileName += ".pgm";

	if ( m_mapImage.load( mapImageFileName ) )
	{
		printf( "Loaded map image: '%s'\n", (const char*)mapImageFileName );
		m_mapImageLoaded = true;
	}

	printf( "Loaded map: '%s'\n", fileNameChr );

	m_mapLengthX = m_maxX - m_minX;
	m_mapLengthY = m_maxY - m_minY;

//	if ( numAggroInfo > 0 )
//		for ( n = 0; n < numSpawns; n++ )
//		{
//			if ( spawns[ n ].isMob == 1 )
//				spawnAggroRange[ n ] = 0;
//			for ( int i = 0; i < numAggroInfo; i++ )
//			{
//				printf( "***Finding Match %s, %s, %i\n", aspawn->name, aggroInfo[ i ].name, strstr( spawns[ n ].name, aggroInfo[ i ].name ) );
//				if ( strstr( spawns[ n ].name, aggroInfo[ i ].name ) )
//				{
//					printf( "Found Match %s, %s \n", spawns[ n ].name, aggroInfo[ i ].name );
//					spawnAggroRange[ n ] = aggroInfo[ i ].range;
//					break;
//				}
//			}
//		}
	
	m_mapLoaded = true;
	emit mapLoaded();
}

void MapMgr::addLocation()
{
#ifdef DEBUG
//	debug( "MapMgr::addLocation()" );
#endif

	QString			name;
	QString			color;
	MapLabel*		newLabel;
	QString			temp;
	
	Location		loc = gPlayer->position();
	
	temp.setNum( m_labels.count() );
	
	name = "Loc#";
	name += temp;

	color = "white";
		
	newLabel = new MapLabel( loc.x, loc.y, color, name );

	m_labels.append( newLabel );
	
#ifdef DEBUG
//	printf( "addLocation(): Location %d added at %d/%d\n", m_labels.count(), loc.x, loc.y );
#endif
}

void MapMgr::startLine()
{
#ifdef DEBUG
//	debug( "MapMgr::startLine()" );
#endif

	Location	loc = gPlayer->position();
	QString		color = m_curLineColor;
	QString		name = m_curLineName;
	
	MapLine*	line = new MapLine( loc, color, name );

	m_lines.append( line );
		
#ifdef DEBUG
//	printf( "startLine():  Line %d started at %d/%d\n", m_lines.count(), loc.x, loc.y );
#endif
}

void MapMgr::addLinePoint()
{
#ifdef DEBUG
//	debug( "MapMgr::addLinePoint()" );
#endif
	MapLine*	line = m_lines.last();

	if ( !line )
	{
		this->startLine();
		return;
	}
	
	int 		last = line->m_locations.size();
	
	line->m_locations.resize( last + 1 );
	line->m_locations[ last ] = gPlayer->position();
	
#ifdef DEBUG
//	printf( "addLinePoint() - Point %d added: %d/%d\n", m_lines.count(), loc->x, loc->y );
#endif
}

void MapMgr::delLinePoint()
{
#ifdef DEBUG
//	debug( "MapMgr::delLinePoint()" );
#endif

	MapLine*	line = m_lines.last();

	if ( !line )
		return;

	line->m_locations.resize( line->m_locations.size() - 1 );

#ifdef DEBUG
//	printf( "delLinePoint() - Point %d removed\n", line->m_locations.count() + 1 );
#endif
}

MapWindow::MapWindow( MapMgr* mgr, const QString& title, unsigned short number, const char* name ):
	BaseWindow( title, NULL, name )
{
	m_number = number;
	m_mgr = mgr;

	GameItem::GameItemFlag		flag;
	switch ( m_number )
	{
		case 0:		flag = GameItem::k_userFlag1;	break;
		case 1:		flag = GameItem::k_userFlag2;	break;
		case 2:		flag = GameItem::k_userFlag3;	break;
		case 3:		flag = GameItem::k_userFlag4;	break;
		default:	flag = GameItem::k_highlight;	break;
	}

	QVBoxLayout*	layout = new QVBoxLayout( this );

	m_mapControls = new QHBox( this, "map-controls" );
	m_mapControls->setSpacing( 1 );
	m_mapControls->setMargin( 0 );
	layout->addWidget( m_mapControls );

	QHBoxLayout*	hBoxLayout = new QHBoxLayout( layout );

	m_map = new Map( mgr, number + 1, flag, this, "map" );
	hBoxLayout->addWidget( m_map );
	m_filterControls = new DepthControlBox( this, m_map, "filter-controls" );
	m_filterControls->setRange( mgr->minZ(), mgr->maxZ() );
	m_filterControls->resetControls();
	hBoxLayout->addWidget( m_filterControls );


	new QLabel( "Zoom:", m_mapControls );
	m_zoomControls = new ZoomControlBox( m_mapControls, m_map, "zoom-controls" );
	m_fpsControl = new QSpinBox( 1, 60, 1, m_mapControls, "map-fps-control" );
//	m_fpsControl->setMidLineWidth( 0 );
//	m_fpsControl->setLineWidth( 1 );
//	m_fpsControl->setFrameStyle( QFrame::Box | QFrame::Plain );
	m_fpsControl->setFixedHeight( 20 );
	m_fpsControl->setValue( m_map->__getPrefInt( "Framerate", 10 ) );
	m_fpsControl->setSuffix( "FPS" );

	new QLabel( "Loc:", m_mapControls );
	QHBox*		locHBox = new QHBox( m_mapControls );
	locHBox->setFrameStyle( QFrame::Panel | QFrame::Sunken );
	locHBox->setSpacing( 3 );
	locHBox->setMargin( 2 );
	m_ypos = new QLabel( "0", locHBox );
	m_xpos = new QLabel( "0", locHBox );
	m_zpos = new QLabel( "0", locHBox );
	
	new QLabel( "Find:", m_mapControls );
//	QFrame*	border = new QFrame( m_mapControls, "dummy-frame" );
//	border->setMidLineWidth( 0 );
//	border->setLineWidth( 1 );
//	border->setFrameStyle( QFrame::Box | QFrame::Plain );
	m_find = new QLineEdit( m_mapControls, "find-edit" );
//	m_find->setFrame( false );
//	m_find->move( 1, 1 );
//	m_find->setSizePolicy( QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Fixed ) );
//	m_find->setMinimumSize( 1, 1 );
	m_find->setFixedHeight( 20 );
//	m_mapControls->setStretchFactor( border, 8 );
	m_mapControls->setStretchFactor( m_find, 8 );

	m_finder = new Finder( m_find, flag );

	QPopupMenu*	mapMenu = m_map->getOptionsMenu();
	mapMenu->insertSeparator();
	m_toggleControlsID = mapMenu->insertItem( "Show Controls", this,				SLOT( toggleControls() ) );
	m_toggleFilterControlsID = mapMenu->insertItem( "Show Filter Controls", this,	SLOT( toggleFilterControls() ) );
	mapMenu->setItemChecked( m_toggleControlsID, m_map->__getPrefBool( "ShowControls", true ) );
	mapMenu->setItemChecked( m_toggleFilterControlsID, m_map->__getPrefBool( "ShowFilterControls", true ) );

	connect( m_fpsControl,		SIGNAL( valueChanged(int) ), m_map,		SLOT( setFPS(int) ) );
	connect( m_filterControls,	SIGNAL( floorChanged(int) ), m_map, 	SLOT( setFloor(int) ) );
	connect( m_filterControls,	SIGNAL( ceilingChanged(int) ), m_map,	SLOT( setCeiling(int) ) );
	connect( m_map,				SIGNAL( zoomChanged(int) ),	m_zoomControls, SLOT( zoomChanged(int) ) );
	connect( mgr,				SIGNAL( mapLoaded() ), 					SLOT( mapLoaded() ) );
	connect( mgr,				SIGNAL( mapUnloaded() ),				SLOT( mapUnloaded() ) );
	connect( gPlayer,			SIGNAL( yposChanged(int) ), m_ypos,		SLOT( setNum(int) ) );
	connect( gPlayer,			SIGNAL( xposChanged(int) ), m_xpos,		SLOT( setNum(int) ) );
	connect( gPlayer,			SIGNAL( zposChanged(int) ), this,		SLOT( setZPos(int) ) );

	if ( m_map->__getPrefBool( "ShowControls", true ) )
		m_mapControls->show();
	else
		m_mapControls->hide();
	
	if ( m_map->__getPrefBool( "ShowFilterControls", true ) )
		m_filterControls->show();
	else
		m_filterControls->hide();
}

void MapWindow::mapLoaded()
{
	m_filterControls->setRange( m_mgr->minZ(), m_mgr->maxZ() );
//	m_filterControls->resetControls();
}	

void MapWindow::mapUnloaded()
{
}

void MapWindow::toggleControls()
{
	m_map->__togglePreference( "ShowControls", m_toggleControlsID );
	if ( m_map->__getPrefBool( "ShowControls", true ) )
		m_mapControls->show();
	else
		m_mapControls->hide();
}

void MapWindow::toggleFilterControls()
{
	m_map->__togglePreference( "ShowFilterControls", m_toggleFilterControlsID );
	if ( m_map->__getPrefBool( "ShowFilterControls", true ) )
		m_filterControls->show();
	else
		m_filterControls->hide();
}

void MapWindow::setZPos( int z )
{
	m_zpos->setNum( z / 10 );
}

// put anything you want to do more than once into "init"... anything
// that you do only once when the Map object is instantiated (like
// connecting up slots) should go into the constructor... init is
// supposed to be a reusable "reinitialize" routine
void Map::init()
{
	// sets anything that changes when we change zones
	m_zoomStep = 0;
	m_zoom = 1;
	m_playerFOVSize = INIT_FOV_SIZE;
	m_gridRes = m_gridSteps[ m_zoomStep ];
	m_ratio = 1;
	m_ratioI = 1;
	m_floor = m_mgr->minZ();
	m_ceiling = m_mgr->maxZ();
	m_zPos = 0;
	m_xoff = 0;
	m_yoff = 0;
	m_drag = false;
	m_focusItem = gPlayer;
}

Map::Map( 	MapMgr*		mgr,
			int			number,
			GameItem::GameItemFlag highlightFlag,
			QWidget* parent,
			const char* name ):
	QWidget( parent, name, WRepaintNoErase | WResizeNoErase ),
	m_namesToDraw( 600 )
{
#ifdef DEBUG
//	debug( "Map::Map()" );
#endif
	m_mgr = mgr;
	m_number = number;
	m_highlightFlag = highlightFlag;
	m_optionsMenu = NULL;
	this->init();

	// need to set our policy so we get keyboard events
	this->setFocusPolicy( QWidget::StrongFocus );
//	if ( parent )
//		parent->setFocusProxy( this );

	m_namesToDrawCount = 0;

	m_time = QTime::currentTime();
	m_initTime = QTime::currentTime();
	m_time.start();
	m_initTime.start();
	m_running = false;
	
	m_gridLineColor = QColor( this->__getPrefString( "GridColor", "#006400" ) );
	m_backgroundColor = QColor( this->__getPrefString( "BackgroundColor", "#000000" ) );
	
	QString		fontName = this->__getPrefString( "FontName", "Helvetica" );
	int			fontSize = this->__getPrefInt( "FontSize", 8 );

	m_playerFOVHighlight = QColor( 100, 100, 100 );
	m_playerNeighborhoodHighlight = QColor( 80, 80, 80 );
	m_mapFont = QFont( fontName, fontSize );

	m_flash.start();
	m_bFlash = false;
	
	m_timer = new QTimer( this );

	m_popup = new MapPopup();
	
	this->getOptionsMenu();
		
	if ( this->__getPrefBool( "ShowPopup", true ) )
		this->setMouseTracking( true );
	
	connect( m_timer,	SIGNAL( timeout() ),					SLOT( refreshMap() ) );
	connect( m_mgr,		SIGNAL( mapLoaded() ),					SLOT( mapLoaded() ) );
	connect( m_mgr,		SIGNAL( mapUnloaded() ),				SLOT( mapUnloaded() ) );
	connect( m_mgr,		SIGNAL( zoneLoaded() ),					SLOT( zoneLoaded() ) );
	connect( gItemMgr,	SIGNAL( deleteSpawn(Spawn*) ),			SLOT( deleteSpawn(Spawn*) ) );

	m_offscreen = new QPixmap( this->width(), this->height() );

	if ( m_mgr->isMapLoaded() )
		this->mapLoaded();
}

void Map::mapUnloaded()
{
	this->stopMap();
	this->init();
}

void Map::mapLoaded()
{
	this->init();
	this->setZoom( this->__getPrefInt( "ZoomLevel", 0 ) );
	
	this->startMap();
}

void Map::zoneLoaded()
{
	this->startMap();
}

void Map::pickNewColor( const QString& pref, QColor& newColor )
{
	QColor		temp;
	temp = QColorDialog::getColor( newColor, this, "grid-color" );
	if ( temp.isValid() )
	{
		newColor = temp;
		if ( pref.length() )
			this->__setPrefString( pref, newColor.name() );
	}
}

void Map::pickGridColor()
{
	this->pickNewColor( "GridColor", m_gridLineColor );
}

void Map::pickBackgroundColor()
{
	this->pickNewColor( "BackgroundColor", m_backgroundColor );
}

void Map::pickFont()
{
	bool	ok;
	m_mapFont = QFontDialog::getFont( &ok, m_mapFont );
	if ( ok )
	{
		this->__setPrefString( "FontName", m_mapFont.family() );
		this->__setPrefInt( "FontSize", m_mapFont.pointSize() );
	}
}

void Map::setFPS( int framesPerSecond )
{
	if ( framesPerSecond < 0 )
		framesPerSecond = 1;
	else if ( framesPerSecond > 60 )
		framesPerSecond = 60;
		
	this->__setPrefInt( "Framerate", framesPerSecond );
	if ( this->running() )
		m_timer->start( 1000L / framesPerSecond, false );
}

void Map::startMap()
{
	int		frameRate = this->__getPrefInt( "Framerate", 10 );

	m_timer->start( 1000L / frameRate, false );
	m_time.restart();
	m_initTime.restart();
	m_renderCount = 0;
	
	m_running = true;
}

void Map::stopMap()
{
	m_timer->stop();
	m_running = false;
}

QPopupMenu* Map::getOptionsMenu()
{
	if ( !m_optionsMenu )
	{
		m_optionsMenu = new QPopupMenu( qApp->mainWidget() );
	
		m_showPopupMenuID = m_optionsMenu->insertItem( "Show Popup", this,					SLOT( togglePopup() ) );
		m_filteredMenuID = m_optionsMenu->insertItem( "Show Filtered", this,				SLOT( toggleFiltered() ) );
		m_showMapLinesID = m_optionsMenu->insertItem( "Show Map", this,						SLOT( toggleMapLines() ) );
		m_velocityLinesMenuID = m_optionsMenu->insertItem( "Show Velocity Lines", this,		SLOT( toggleVelocityLines() ) );
		m_animateSpawnsMenuID = m_optionsMenu->insertItem( "Animate Spawn Movement", this,	SLOT( toggleAnimate() ) );
		m_showPlayerViewMenuID = m_optionsMenu->insertItem( "Show Player View", this,		SLOT( togglePlayerView() ) );
		m_showGridMenuID = m_optionsMenu->insertItem( "Show Grid Lines", this,				SLOT( toggleGrid() ) );
		m_showLocationsMenuID = m_optionsMenu->insertItem( "Show Locations", this,			SLOT( toggleLocations() ) );
		m_showDropsMenuID = m_optionsMenu->insertItem( "Show Drops", this,					SLOT( toggleDrops() ) );
		m_showCoinsMenuID = m_optionsMenu->insertItem( "Show Coins", this,					SLOT( toggleCoins() ) );
		m_showSpawnPointsID = m_optionsMenu->insertItem( "Show Spawn Points", this,			SLOT( toggleSpawnPoints() ) );
		m_showSpawnNamesID = m_optionsMenu->insertItem( "Show Spawn Names", this,			SLOT( toggleSpawnNames() ) );
		m_showDebugInfoID = m_optionsMenu->insertItem( "Show Debug Info", this,				SLOT( toggleDebugInfo() ) );
		m_showBackgroundImageID = m_optionsMenu->insertItem( "Show Map Image", this, SLOT( toggleBackgroundImage() ) );
		m_blinkAlertedID = m_optionsMenu->insertItem( "Blink Alerted Spawns", this,			SLOT( toggleBlinkAlerted() ) );
		m_focusOnSelectionID = m_optionsMenu->insertItem( "Focus on Selection", this,		SLOT( setFocusOnSelection() ) );
		m_toggleSpawnDepthFilteringID = m_optionsMenu->insertItem( "Spawn Depth Filtering", this,		SLOT( toggleSpawnDepthFiltering() ) );
		m_toggleMapDepthFilteringID = m_optionsMenu->insertItem( "Map Depth Filtering", this,	SLOT( toggleMapDepthFiltering() ) );
		m_toggleMapFadeID = m_optionsMenu->insertItem( "Fade Map", this,					SLOT( toggleMapFade() ) );	
		m_toggleLockControlsID = m_optionsMenu->insertItem( "Lock Filter Controls", this,	SLOT( toggleLockControls() ) );

		m_optionsMenu->insertItem( "Grid Color...", this, SLOT( pickGridColor() ) );
		m_optionsMenu->insertItem( "Background Color...", this, SLOT( pickBackgroundColor() ) );
		m_optionsMenu->insertItem( "Font...", this, SLOT( pickFont() ) );

		m_optionsMenu->setItemChecked( m_showPopupMenuID, this->__getPrefBool( "ShowPopup", true ) );
		m_optionsMenu->setItemChecked( m_filteredMenuID, this->__getPrefBool( "ShowFiltered", true ) );
		m_optionsMenu->setItemChecked( m_showMapLinesID, this->__getPrefBool( "ShowMapLines", true ) );
		m_optionsMenu->setItemChecked( m_velocityLinesMenuID, this->__getPrefBool( "VelocityLines", true ) );
		m_optionsMenu->setItemChecked( m_animateSpawnsMenuID, this->__getPrefBool( "AnimateSpawnMovement", true ) );
		m_optionsMenu->setItemChecked( m_showPlayerViewMenuID, this->__getPrefBool( "ShowPlayerView", true ) );
		m_optionsMenu->setItemChecked( m_showGridMenuID, this->__getPrefBool( "ShowGrid", true ) );
		m_optionsMenu->setItemChecked( m_showLocationsMenuID, this->__getPrefBool( "ShowMapPoints", true ) );
		m_optionsMenu->setItemChecked( m_showDropsMenuID, this->__getPrefBool( "ShowDrops", true ) );
		m_optionsMenu->setItemChecked( m_showCoinsMenuID, this->__getPrefBool( "ShowCoins", true ) );
		m_optionsMenu->setItemChecked( m_showSpawnPointsID, this->__getPrefBool( "ShowSpawnPoints", true ) );
		m_optionsMenu->setItemChecked( m_showSpawnNamesID, this->__getPrefBool( "ShowNames", true ) );
		m_optionsMenu->setItemChecked( m_showDebugInfoID, this->__getPrefBool( "ShowDebugInfo", true ) );
		m_optionsMenu->setItemChecked( m_showBackgroundImageID, this->__getPrefBool( "ShowBackgroundImage", true ) );
		m_optionsMenu->setItemChecked( m_blinkAlertedID, this->__getPrefBool( "BlinkAlerted", true ) );
		m_optionsMenu->setItemChecked( m_focusOnPlayerID, this->__getPrefBool( "FocusOnPlayer", true ) );
		m_optionsMenu->setItemChecked( m_toggleSpawnDepthFilteringID, this->__getPrefBool( "SpawnDepthFilter", true ) );
		m_optionsMenu->setItemChecked( m_toggleMapDepthFilteringID, this->__getPrefBool( "MapDepthFilter", true ) );
		m_optionsMenu->setItemChecked( m_toggleMapFadeID, this->__getPrefBool( "FadingFloors", true ) );
 	  	m_optionsMenu->setItemChecked( m_toggleLockControlsID, this->__getPrefBool( "LockFilterControls", true ) );
	}	

	return m_optionsMenu;
}

QSize Map::sizeHint() const
{
#ifdef DEBUG
//	debug( "Map::sizeHint()" );
#endif

	return QSize( 600, 600 );
}


QSize Map::minimumSizeHint() const
{
#ifdef DEBUG
//	debug( "Map::minimumSizeHint()" );
#endif

	return QSize( 200, 200 );
}

QSizePolicy Map::sizePolicy() const
{
#ifdef DEBUG
//	debug( "Map::sizePolicy()" );
#endif
	return QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
}

void Map::mousePressEvent( QMouseEvent* event )
{
#ifdef DEBUG
//	debug( "Map::mousePressEvent()" );
#endif
	if ( m_popup )
		m_popup->hide();

	QMouseEvent::ButtonState	bState = event->button();
	
	switch ( bState )
	{
		case LeftButton:
		{
			Spawn* 	spawn = this->closestSpawn( event->pos() );
			if ( spawn )
				gItemMgr->selectionChanged( spawn );
		}
		break;
		
		case MidButton:
		{
			if ( m_zoom > 1 )
			{
				m_focusItem = NULL;
				m_drag = true;
				m_lastDrag = event->pos();
			}
		}
		break;
		
		case RightButton:
		{
			// context menu
			QPopupMenu*	optionsMenu = this->getOptionsMenu();
			optionsMenu->exec( QCursor::pos() );
		}
		break;
	}	
}

void Map::mouseReleaseEvent( QMouseEvent* event )
{
	if ( event->button() == MidButton && m_drag )
		m_drag = false;
}

void Map::mouseMoveEvent( QMouseEvent* event )
{
	if ( m_drag )
	{
		QPoint		diff = event->pos() - m_lastDrag;
		m_lastDrag = event->pos();
		this->moveCenter( diff.x(), diff.y() );
	}
	else
	{
		if ( !this->__getPrefBool( "ShowPopup", true ) )
			return;

		GameItem*		gi = this->closestGameItem( event->pos(), 12 );

		if ( gi )
		{
			QString	string;

			string = gi->info();
		
			m_popup->setText( string  );
			m_popup->adjustSize();
			m_popup->position( this->mapToGlobal( event->pos() ) );
			m_popup->show();
			m_popup->raise();
		}
		else
			m_popup->hide();
	}
}

#define		INCREMENT		20L
void Map::keyPressEvent( QKeyEvent* key )
{
	if ( m_popup )
		m_popup->hide();

	int keyNum = key->key();
	int	moveX = 0;
	int moveY = 0;

	key->accept();

	switch ( keyNum )
	{
		case Key_Plus:		this->zoomIn();		break;
		case Key_Minus:		this->zoomOut();	break;

		case Key_Escape:
			m_focusItem = gPlayer;
		break;

		case Key_Comma:
		case Key_Less:
			this->decreasePlayerNeighborhood( INCREMENT );
		break;

		case Key_Period:
		case Key_Greater:
			this->increasePlayerNeighborhood( INCREMENT );
		break;

//		case Key_Up:
		case Key_8:
			moveY = INCREMENT;
		break;
//		case Key_Down:
		case Key_2:
			moveY = -INCREMENT;
		break;
//		case Key_Left:
		case Key_4:
			moveX = INCREMENT;
		break;
//		case Key_Right:
		case Key_6:
			moveX = -INCREMENT;
		break;
//		case Key_Home:
		case Key_7:
			moveX = INCREMENT;
			moveY = INCREMENT;
		break;
//		case Key_Prior:
		case Key_9:
			moveX = -INCREMENT;
			moveY = INCREMENT;
		break;
//		case Key_End:
		case Key_1:
			moveX = INCREMENT;
			moveY = -INCREMENT;
		break;
//		case Key_Next:
		case Key_3:
			moveX = -INCREMENT;
			moveY = -INCREMENT;
		break;
		default:
			key->ignore();
		break;
	}
	if ( ( moveX || moveY ) && m_zoom > 1 )
	{
		m_focusItem = NULL;
		this->moveCenter( moveX, moveY );
	}		
}

void Map::__setZoom( int zoomStep )
{
	if ( zoomStep < 0 )
		zoomStep = 0;
	else if ( zoomStep > MAX_ZOOM_STEP )
		zoomStep = MAX_ZOOM_STEP;
	
	m_zoomStep = zoomStep;
	m_zoom = ( 1 << m_zoomStep );
	m_gridRes = m_gridSteps[ m_zoomStep ];
	this->__setPrefInt( "ZoomLevel", zoomStep );
}

void Map::setZoom( int zoomStep )
{
	int oldX = 0;
	int oldY = 0;
	
	if ( zoomStep != 0 )
	{
		oldX = (int)( ( m_screenCenterX - ( m_screenLengthX / 2 ) ) * m_ratio );
		oldY = (int)( ( m_screenCenterY - ( m_screenLengthY / 2 ) ) * m_ratio );
	}
	
	this->__setZoom( zoomStep );
	this->calculateScale();
	this->adjustCenter( Location( oldX, oldY, 0 ) );
	emit zoomChanged( m_zoomStep );
}

void Map::setCeiling( int newCeiling )
{
	m_ceiling = newCeiling;
}

void Map::setFloor( int newFloor )
{
	m_floor = newFloor;
}

void Map::decreasePlayerNeighborhood( int amount )
{
	this->setPlayerNeighborhood( m_playerFOVSize - amount );
}

void Map::increasePlayerNeighborhood( int amount )
{
	this->setPlayerNeighborhood( m_playerFOVSize + amount );
}

void Map::setPlayerNeighborhood( int to )
{
	m_playerFOVSize = to;

	if ( m_playerFOVSize < 0 )
		m_playerFOVSize = 0;
	else if ( m_playerFOVSize > 1000 )
		m_playerFOVSize = 1000;
}

void Map::resizeEvent( QResizeEvent* qs )
{
#ifdef DEBUG
//	debug( "Map::resizeEvent()" );
#endif
	m_screenLengthX = qs->size().width();
	m_screenLengthY = qs->size().height();

	m_screenCenterX = m_screenLengthX / 2;
	m_screenCenterY = m_screenLengthY / 2;

	m_offscreen->resize( m_screenLengthX, m_screenLengthY );

	this->calculateScale();
}


void Map::refreshMap()
{
#ifdef DEBUG
//	debug( "Map::refreshMap()" );
#endif
	repaint( false );
}

void Map::__togglePreference( const QString& boolPref, int menuID )
{
	bool	pref = this->__getPrefBool( boolPref, true );
	this->__setPrefBool( boolPref, !pref );
	getOptionsMenu()->setItemChecked( menuID, !pref );
}

bool Map::__getPrefBool( const QString& prefName, bool def )
{
	QString		sectionName = "Map";
	sectionName += QString::number( m_number );
		
	return gSEQPrefs->getPrefBool( prefName, sectionName, def );
}

void Map::__setPrefBool( const QString& prefName, bool newValue )
{
	QString		sectionName = "Map";
	sectionName += QString::number( m_number );
	
	gSEQPrefs->setPrefBool( prefName, sectionName, newValue );
}

int Map::__getPrefInt( const QString& prefName, int def )
{
	QString		sectionName = "Map";
	sectionName += QString::number( m_number );
	
	return gSEQPrefs->getPrefInt( prefName, sectionName, def );
}

void Map::__setPrefInt( const QString& prefName, int newValue )
{
	QString		sectionName = "Map";
	sectionName += QString::number( m_number );
	
	gSEQPrefs->setPrefInt( prefName, sectionName, newValue );
}	

QString Map::__getPrefString( const QString& prefName, const QString& def )
{
	QString		sectionName = "Map";
	sectionName += QString::number( m_number );

	return gSEQPrefs->getPrefString( prefName, sectionName, def );
}

void Map::__setPrefString( const QString& prefName, const QString& newValue )
{
	QString		sectionName = "Map";
	sectionName += QString::number( m_number );

	gSEQPrefs->setPrefValue( prefName, sectionName, newValue );
}


void Map::toggleLockControls()
{
	this->__togglePreference( "LockFilterControls", m_toggleLockControlsID );
}

void Map::toggleSpawnDepthFiltering()
{
	this->__togglePreference( "SpawnDepthFilter", m_toggleSpawnDepthFilteringID );
}

void Map::toggleMapDepthFiltering()
{
	this->__togglePreference( "MapDepthFilter", m_toggleMapDepthFilteringID );
}

void Map::toggleMapFade()
{
	this->__togglePreference( "FadingFloors", m_toggleMapFadeID );
}

void Map::togglePopup()
{
	this->__togglePreference( "ShowPopup", m_showPopupMenuID );
	if ( m_popup )
		m_popup->hide();
	bool on = this->__getPrefBool( "ShowPopup", true );
	this->setMouseTracking( on );
}
	
void Map::toggleFiltered()
{
	this->__togglePreference( "ShowFiltered", m_filteredMenuID );
}

void Map::toggleMapLines()
{
	this->__togglePreference( "ShowMapLines", m_showMapLinesID );
}

void Map::toggleAnimate()
{
	this->__togglePreference( "AnimateSpawnMovement", m_animateSpawnsMenuID );
}

void Map::toggleVelocityLines()
{
	this->__togglePreference( "VelocityLines", m_velocityLinesMenuID );
}

void Map::togglePlayerView()
{
	this->__togglePreference( "ShowPlayerView", m_showPlayerViewMenuID );
}

void Map::toggleGrid()
{
	this->__togglePreference( "ShowGrid", m_showGridMenuID );
}

void Map::toggleLocations()
{
	this->__togglePreference( "ShowMapPoints", m_showLocationsMenuID );
}

void Map::toggleDrops()
{
	this->__togglePreference( "ShowDrops", m_showDropsMenuID );
}

void Map::toggleCoins()
{
	this->__togglePreference( "ShowCoins", m_showCoinsMenuID );
}

void Map::toggleSpawnPoints()
{
	this->__togglePreference( "ShowSpawnPoints", m_showSpawnPointsID );
}

void Map::toggleSpawnNames()
{
	this->__togglePreference( "ShowNames", m_showSpawnNamesID );
}

void Map::toggleBlinkAlerted()
{
	this->__togglePreference( "BlinkAlerted", m_blinkAlertedID );
}

void Map::toggleDebugInfo()
{
	this->__togglePreference( "ShowDebugInfo", m_showDebugInfoID );
}

void Map::toggleBackgroundImage()
{
	this->__togglePreference( "ShowBackgroundImage", m_showBackgroundImageID );
}

void Map::toggleFocusOnPlayer()
{
	this->__togglePreference( "FocusOnPlayer", m_focusOnPlayerID );
}

void Map::setFocusOnSelection()
{
	Spawn*		selected = gItemMgr->selected();
	if ( selected )
		m_focusItem = selected;
}

void Map::moveCenter( int diffX, int diffY )
{
	m_screenCenterX += diffX;
	m_screenCenterY += diffY;

	if ( m_screenCenterX < m_screenBoundLeft )
		m_screenCenterX = m_screenBoundLeft;
	if ( m_screenCenterX > m_screenBoundRight )
		m_screenCenterX = m_screenBoundRight;
	if ( m_screenCenterY < m_screenBoundTop )
		m_screenCenterY = m_screenBoundTop;
	if ( m_screenCenterY > m_screenBoundBottom )
		m_screenCenterY = m_screenBoundBottom;

	this->recalcMapBounds();
	this->repaint( false );
}	

void Map::adjustCenter( const Location& loc )
{
	int		iZMaxX, iZMinX, iZMaxY, iZMinY;

	int		zoomMapLengthX = (int)( m_ratio * m_screenLengthX );
	int		zoomMapLengthY = (int)( m_ratio * m_screenLengthY );
		
	// this code keeps the map centered on the player without showing
	//	empty space when we get close to the map edges

	// iZMaxX is the largest X in map units that can be displayed
	// iZMinX is the smallest...
	//
	// iZMaxX = player.x + ( 1500 / 2 ) = player.x + 750
	// iZMinX = player.x - ( 1500 / 2 ) = player.x - 750
	iZMaxX = loc.x + zoomMapLengthX / 2;
	iZMinX = loc.x - zoomMapLengthX / 2;

	// iZMaxY is the largest Y in map units that can be displayed
	// iZMinY is the smallest...
	//
	// iZMaxY = player.y + ( 1000 / 2 ) = player.y + 500
	// izMinY = player.y - ( 1000 / 2 ) = player.y - 500
	iZMaxY = loc.y + zoomMapLengthY / 2;
	iZMinY = loc.y - zoomMapLengthY / 2;

#ifdef DEBUG
//	printf( "iZMinX,Y, izMaxX,Y: (%d, %d)  (%d, %d)\n", iZMinX, iZMinY, iZMaxX, iZMaxY );
//	printf( "minX,Y, maxX,Y: (%d, %d)  (%d, %d)\n", m_minX, m_minY, m_maxX, m_maxY );
#endif

	// if the map is bigger on the left than leftmost spawn,
	//	shift the map to the right
	if ( iZMinX < m_mgr->minX() )
	{
		iZMaxX -= ( iZMinX - m_mgr->minX() );
		iZMinX -= ( iZMinX - m_mgr->minX() );
	}
	// if the map is bigger on the top than the topmost spawn,
	//	shift the map down
	if ( iZMinY < m_mgr->minY() )
	{
		iZMaxY -= ( iZMinY - m_mgr->minY() );
		iZMinY -= ( iZMinY - m_mgr->minX() );
	}
	// if the map is bigger on the right than the rightmost spawn,
	//	shift the map to the left
	if ( iZMaxX > m_mgr->maxX() )
	{
		iZMinX -= ( iZMaxX - m_mgr->maxX() );
		iZMaxX -= ( iZMaxX - m_mgr->maxX() );
	}
	// if the map is bigger on the bottom than the bottommost spawn,
	//	shift the map up
	if ( iZMaxY > m_mgr->maxY() )
	{
		iZMinY -= ( iZMaxY - m_mgr->maxY() );
		iZMaxY -= ( iZMaxY - m_mgr->maxY() );
	}

#ifdef DEBUG
//	printf( "loc.x, loc.y: %d, %d\n", loc.x, loc.y );
//	printf( "iZMinX,Y, izMaxX,Y: (%d, %d)  (%d, %d)\n", iZMinX, iZMinY, iZMaxX, iZMaxY );
#endif
	// m_screenCenterX = ( <x edge of map> + <empty space> ) * 300 ) / 1500 ) = ?
	// m_screenCenterY = ( <y edge of map> + <empty space> ) * 200 ) / 1000 ) = ?
	m_screenCenterX = ( ( ( iZMaxX + m_xoff ) * m_screenLengthX ) / zoomMapLengthX );
	m_screenCenterY = ( ( ( iZMaxY + m_yoff ) * m_screenLengthY ) / zoomMapLengthY );
	this->recalcMapBounds();
}

void Map::recalcMapBounds()
{
	int		maxX = (int)( m_screenCenterX * m_ratio );
	int		maxY = (int)( m_screenCenterY * m_ratio );
	int		minX = (int)( ( m_screenCenterX - this->width() ) * m_ratio );
	int		minY = (int)( ( m_screenCenterY - this->height() ) * m_ratio );
	
	m_bounds = QRect( minX, minY, maxX - minX, maxY - minY );
}

void Map::recalcScreenBounds()
{
	int		offset = 40;
	int		minX = m_mgr->minX();
	int		minY = m_mgr->minY();
	int		maxX = m_mgr->maxX();
	int		maxY = m_mgr->maxY();
	
	m_screenBoundLeft = (int)( m_screenLengthX + ( ( minX - offset ) / m_ratio ) );
	m_screenBoundRight = (int)( ( maxX + offset ) / m_ratio );
	m_screenBoundTop = (int)( m_screenLengthY + ( ( minY - offset ) / m_ratio ) );
	m_screenBoundBottom = (int)( ( maxY + offset ) / m_ratio );

//	printf( "x, y: %d %d %d %d\n", m_minX, m_maxX, m_minY, m_maxY );
//	printf( "center: %d %d\n", m_screenCenterX, m_screenCenterY );
//	printf( "screenBounds: %d %d %d %d\n", m_screenBoundTop, m_screenBoundLeft, m_screenBoundBottom, m_screenBoundRight );	
}

bool Map::canZoom( int zoomStep )
{
	return (
		( ( m_mgr->mapLengthX() / ( 1 << zoomStep ) ) > 8 ) &&
		( ( m_mgr->mapLengthY() / ( 1 << zoomStep ) ) > 8 ) );
}

void Map::calculateScale()
{
#ifdef DEBUG
//	debug( "Map::calculateScale()" );
#endif
	static bool norecurse = false;

	if ( norecurse )
	{
		printf( "tried to call calculateScale while IN calculateScale already!\n" );
		return;
	}
	
	norecurse = true;

#ifdef DEBUG
//	printf( "mLenX,Y: %d, %d  sLenX,Y: %d, %d\n", m_mgr->mapLengthX(), m_mgr->mapLengthY(), m_screenLengthX, m_screenLengthY );
#endif

	int pxrat, pyrat, zoomMapLengthX, zoomMapLengthY;
	
	// pxrat/pyrat are ratios of map length over zoom level
	//	so, if we have 400 units of map length, and the zoom is 2, we can effectively
	//	display only 200 units of normal resolution stuff
	if ( m_zoom > 1 )
	{
		while ( !this->canZoom( m_zoomStep ) )
			m_zoomStep--;
	}

	pxrat = zoomMapLengthX = ( ( m_mgr->mapLengthX() ) / ( m_zoom ) );
	pyrat = zoomMapLengthY = ( ( m_mgr->mapLengthY() ) / ( m_zoom ) );

#ifdef DEBUG
//	printf( "zoom: %d  zoomX,Y: %d, %d\n", m_zoom, zoomMapLengthX, zoomMapLengthY );
#endif

	// xrat/yrat are the ratios of length in pixels over the number of
	//	units we're displaying -- if we have 300 pixels and 2000 units
	//	of map, at zoom level 3:
	//	(300 / ( 2000 / 3 ) ) = 0.45
	float xrat = (float)m_screenLengthX / zoomMapLengthX;
	float yrat = (float)m_screenLengthY / zoomMapLengthY;

#ifdef DEBUG
//	printf( "ratioX,Y: %f, %f\n", xrat, yrat );
#endif

	// now, which way are we constrained?  if we're trying
	//	to display a 2000x3000 map in a 300x200 pixel area, at
	//	a zoom level of 3:
	//
	//	zoomMapLengthX = int( 2000 / 3 ) = 666
	//	zoomMapLengthY = int( 3000 / 3 ) = 1000
	//	xrat = (double)300 / 666 = 0.45
	//	yrat = (double)200 / 1000 = 0.2
	//	and we will end up with:
	//	zoomMapLengthX = 300 / 0.2 = 1500
	//	zoomMapLengthY = 1000
	//
	//	therefore, a 300x200 pixel area at zoom level 3 will
	//	display 1500 units of the map in the X dimension,
	//	and 1000 units of the map in the Y dimenision
	//
	//	xoff = ( 1500 - 666 ) / 2 = 417
	//	yoff = 0
	//
	//	xoff/yoff represents the extra room on the side of
	//	that dimension that will be empty (because we're more
	//	constrained by the other dimension)
	//
	//	nb: xoff is calculated for all zoom levels, but it's
	//	only useful in zoom level 1 to calculate the screen
	//	center
	
	m_xoff = 0;
	m_yoff = 0;
	
	if ( xrat < yrat )
	{
		zoomMapLengthY = (int)( m_screenLengthY / xrat );
		if ( m_zoom <= 1 )
			m_yoff = ( zoomMapLengthY - pyrat ) / 2;
	}
	else
	{
		zoomMapLengthX = (int)( m_screenLengthX / yrat );
		if ( m_zoom <= 1 )
			m_xoff = ( zoomMapLengthX - pxrat ) / 2;
	}

	m_ratio = (float)zoomMapLengthX / (float)m_screenLengthX;
	m_ratioI = (int) ( ( 1.0 / m_ratio ) * 2048.0 );

	this->recalcScreenBounds();
	
	if ( m_focusItem )
		this->adjustCenter( m_focusItem->approximatePosition( this->animateMap() ) );
	else
		this->recalcMapBounds();
		
//	m_playerFOVSize = this->scale( m_playerFOVSize );

#ifdef DEBUG
//	printf( "screenCenterX, screenCenterY: %d, %d\n", m_screenCenterX, m_screenCenterY );
#endif

	norecurse = false;
}

void Map::deleteSpawn( Spawn* spawn )
{
	if ( m_focusItem == spawn )
		m_focusItem == gPlayer;
}

void Map::__drawGrid( QPainter& tmp )
{
	// paint the grid
	tmp.setPen( m_gridLineColor );

	QString ts;
	QRect	mapBounds = this->getMapBounds();
	
	for ( int gx = ( ( m_mgr->minX() / m_gridRes) - 1 ); gx <= ( ( m_mgr->maxX() / m_gridRes ) + 1 ); gx++ )
	{
		int		scaleX = gx * m_gridRes;
		
		if ( ( mapBounds.left() < scaleX ) && ( scaleX < mapBounds.right() ) )
		{
			int x = this->calcXOffset( scaleX );
	
			tmp.drawLine( x, 0, x, m_screenLengthY );
			ts.sprintf( "%d", scaleX );
			tmp.drawText( x + 1, m_screenLengthY - 2, ts );
		}
	}
	
	for ( int gy = ( ( m_mgr->minY() / m_gridRes ) - 1 ); gy <= ( ( m_mgr->maxY() / m_gridRes ) + 1 ); gy++ )
	{
		int		scaleY = gy * m_gridRes;
		
		if ( ( mapBounds.top() < scaleY ) && ( scaleY < mapBounds.bottom() ) )
		{
			int y = this->calcYOffset( scaleY );
			
			tmp.drawLine( 0, y, m_screenLengthX, y );
			ts.sprintf( "%d", scaleY );
			tmp.drawText( 2, y - 1, ts );
		}
	}
}

void Map::__drawPlayer( QPainter& tmp )
{

#ifdef DEBUG
//	printf( "paint player position\n" );
#endif

	Location		loc = gPlayer->approximatePosition( this->animateMap() );
	
#ifdef DEBUG
//	printf( "player x, y: %d, %d\n", loc.x, loc.y );
#endif

	tmp.setPen( gray );
	tmp.setBrush( white );
	tmp.drawEllipse( calcXOffset( loc.x ) - 3, calcYOffset( loc.y ) - 3, 6, 6 );
}

void Map::__drawPlayerNeighborhood( QPainter& tmp )
{
	Location pos = gPlayer->approximatePosition( this->animateMap() );
	
	// paint player position background
	tmp.setPen( m_playerNeighborhoodHighlight );
	tmp.setBrush( m_playerNeighborhoodHighlight );
	unsigned long		size = this->scale( m_playerFOVSize );

	tmp.drawEllipse(
		this->calcXOffset( pos.x ) - size,
		this->calcYOffset( pos.y ) - size,
		size * 2,
		size * 2 );
}

void Map::__drawPlayerFOV( QPainter& tmp )
{
	// paint the player direction
#ifdef DEBUG
//	printf( "paint the player direction\n");
#endif

	Location		ploc = gPlayer->approximatePosition( this->animateMap() );
	unsigned long	angle;
	
	angle = gPlayer->heading();
	angle *= 360;
	angle /= 256;									// map a 256-segment circle to a 360-segment circle
	
	angle += 60;									// wrap a circle that starts with 0 degrees at 12 o'clock
													// to one that starts with 0 degrees at 3 o'clock
													// assume our FOV angle is ~ 60 degrees, and subtract off
													// half to start our arc at 30 degrees right of where we
													// point, continue to 30 degrees left of where we point
	
	angle %= 360;									// probably not strictly necessary for Qt
	
	angle = 16 * angle;								// angles in Qt are 5760-segment circles

	int player_x = this->calcXOffset( ploc.x );
	int player_y = this->calcYOffset( ploc.y );

	tmp.setPen( m_playerFOVHighlight );
	tmp.setBrush( m_playerFOVHighlight );
	unsigned long		size = this->scale( m_playerFOVSize );
	tmp.drawPie( player_x - ( size + 1 ),
				player_y - ( size + 1 ),
				2 * ( size + 1 ),
				2 * ( size + 1 ),
				angle,
				60 * 16 );							// 60 degrees
}


void Map::__drawLines( QPainter& tmp )
{
#define IN_RECT(RECT,X,Y)\
(\
	( (RECT).left() <= (X) ) &&\
	( (X) <= (RECT).right() ) &&\
	( (RECT).top() <= (Y) ) &&\
	( (Y) <= (RECT).bottom() )\
)

#define MINMAX(MIN,MAX,VAL) ( (MIN) > (VAL) ? (MIN) : ( (MAX) < (VAL) ? (MAX) : (VAL) ) )

#ifdef DEBUG
//	printf( "paint the lines\n" );
#endif
	// paint the lines
	//tmp.setPen( blue );

	float			topm = 0;
	float			botm = 0;
	float			topb = 255;
	float			botb = 255;
	int				headroom = 0;
	int				floorroom = 0;
	
	Location		ploc = gPlayer->approximatePosition( this->animateMap() );

	bool			fadeFloors = this->__getPrefBool( "FadingFloors", true );
	bool			depthFilter = this->__getPrefBool( "MapDepthFilter", true );
	QRect			mapBounds = this->getMapBounds();
	
	if ( fadeFloors )
	{
		headroom = m_ceiling - ploc.z;
		floorroom = ploc.z - m_floor;

		if ( headroom < 10 )
			headroom = 10;
		if ( floorroom < 10 )
			floorroom = 10;
	
		topm = - ( 255.0 / (float)headroom );
		botm = 255.0 / (float)floorroom;
		topb = 255 - ( topm * ploc.z );
		botb = 255 - ( botm * ploc.z );
	}

	// printf("tm: %f, tb:%f  bm:%f bb:%f\n", topm, topb, botm, botb);
	QList<MapLine>*	lines = m_mgr->getLines();
	MapLine*		line = lines->first();

	while ( line )
	{	

#ifdef DEBUG
//		printf( "line->m_color = '%s'\n", (const char*)line->m_color );
#endif
		QArray<Location>&	locs = line->m_locations;
		int					ptCount = locs.size();
		QRect				lineBounds = line->m_bounds;
		
		if ( !lineBounds.intersects( mapBounds ) || ( ptCount == 0 ) )
		{
			line = lines->next();
			if ( ptCount == 0 )
				printf( "empty line\n" );
//			else
//			{
//				printf( "lineBounds: %d %d %d %d\n", lineBounds.left(), lineBounds.top(), lineBounds.right(), lineBounds.bottom() );
//				printf( "mapBounds:  %d %d %d %d\n", mapBounds.left(), mapBounds.top(), mapBounds.right(), mapBounds.bottom() );
//			}
			continue;
		}
		
		int					lineZ = locs[ 0 ].z;
		int					oColor = 255;
		int					nColor = 255;
		int					uColor = 255;
		
		int					i = 0;
		int					curX = 0;
		int					curY = 0;
		int					curZ = 0;
		bool				drewLast = true;
		bool				lineIs2D = ( line->m_type == MapLine::e2d );
		bool				lineZInBounds = ( ( m_floor <= lineZ ) && ( lineZ <= m_ceiling ) );

		tmp.setPen( line->m_color );

		if ( fadeFloors )
		{
			if ( lineZ > ploc.z )
				oColor = (int)( ( lineZ * topm ) + topb );
			else
				oColor = (int)( ( lineZ * botm ) + botb );
		
			oColor = MINMAX( 0, 255, oColor );
		}
		
		curX = locs[ 0 ].x;
		curY = locs[ 0 ].y;
		
		if ( IN_RECT( mapBounds, curX, curY ) )
		{
			tmp.moveTo( this->calcXOffset( curX ), this->calcYOffset( curY ) );
			drewLast = true;
		}
		else
			drewLast = false;
		
		int		lastX, lastY;
		bool	doDraw = false;

		while ( ++i < ptCount )
		{
			doDraw = false;
			lastX = curX;
			lastY = curY;
			curX = locs[ i ].x;
			curY = locs[ i ].y;
			curZ = locs[ i ].z;
		
			if ( IN_RECT( mapBounds, curX, curY ) )
			{
				if ( !depthFilter || lineIs2D || lineZ == 0 )
					doDraw = true;
				else
				{
					if ( fadeFloors )
					{
						if ( curZ > ploc.z )
							nColor = (int)( ( curZ * topm ) + topb );
						else
							nColor = (int)( ( curZ * botm ) + botb );
						nColor = MINMAX( 0, 255, nColor );

						uColor = ( nColor + oColor ) / 2;
						if ( uColor != 0 )
						{
							tmp.setPen( QColor( uColor, uColor, uColor ) );
							doDraw = true;
						}
					}
					else if ( lineZInBounds || ( m_floor <= locs[ i ].z ) && ( locs[ i ].z <= m_ceiling ) )
						doDraw = true;
				}
			}
			
			if ( doDraw )
			{
				if ( !drewLast )
					tmp.moveTo( this->calcXOffset( lastX ), this->calcYOffset( lastY ) );
				tmp.lineTo( this->calcXOffset( curX ), this->calcYOffset( curY ) );
				drewLast = true;
			}
			else
			{
				if ( drewLast )
					tmp.lineTo( this->calcXOffset( curX ), this->calcYOffset( curY ) );
				drewLast = false;
			}
		}

		line = lines->next();
	}
}


void Map::__drawLocations( QPainter& tmp )
{
#ifdef DEBUG
//	printf( "paint the locations\n" );
#endif

	QList<MapLabel>*	labels = m_mgr->getLabels();
	MapLabel*			current = labels->first();
	
	while ( current )
	{
		// are both these necessary?
		if ( QColor( current->m_color ) == m_backgroundColor )
			tmp.setPen( QColor( ~ ( m_backgroundColor.rgb() ) ) );
		else
			tmp.setPen( current->m_color );
		//tmp.setBrush( current->m_color );

		tmp.drawText( calcXOffset( current->m_location.x ) - 2,
			calcYOffset( current->m_location.y ) - 2,
			current->m_name );
			
		current = labels->next();
	}
}


void Map::__drawDrops( QPainter& tmp )
{
#ifdef DEBUG
//	printf( "paint the dropped items\n" );
#endif

	QIntDictIterator<Drop>	it( gItemMgr->drops() );
	
	int			ixl;
	int			iyl;	
	const int	drawsize = 3;
	
	tmp.setPen( darkRed );
	Drop*		d;
	
	while ( it.current() )
	{
		d = it.current();
		ixl = calcXOffset( d->xPos() );
		iyl = calcYOffset( d->yPos() );

		tmp.drawLine( ixl - drawsize, iyl - drawsize, ixl + drawsize, iyl + drawsize );
		tmp.drawLine( ixl - drawsize, iyl + drawsize, ixl + drawsize, iyl - drawsize );

		++it;
	}
}


void Map::__drawCoins( QPainter& tmp )
{
#ifdef DEBUG
//	printf( "paint the coin items\n" );
#endif
	QIntDictIterator<Coins>	it( gItemMgr->coins() );
	
	int			ixl;
	int			iyl;	
	const int	drawsize = 3;
	
	tmp.setPen( yellow );
	Coins*		c;
	
	while ( it.current() )
	{
		c = it.current();

		ixl = calcXOffset( c->xPos() );
		iyl = calcYOffset( c->yPos() );

		tmp.drawLine( ixl - drawsize, iyl - drawsize, ixl + drawsize, iyl + drawsize );
		tmp.drawLine( ixl - drawsize, iyl + drawsize, ixl + drawsize, iyl - drawsize );

		++it;
	}
}

Spawn* Map::closestSpawn( const QPoint& point, unsigned long slop  )
{
	QIntDictIterator<Spawn>		it( gItemMgr->spawns() );
	unsigned long				closestDistance;
	unsigned long				distance;
	Spawn*						s;
	Spawn*						closest = NULL;
	bool						animate = this->animateMap();
	
	closestDistance = ULONG_MAX;
	
	while ( it.current() )
	{
		s = it.current();
		++it;
		
		Location		loc = s->approximatePosition( animate );

		QPoint			mobLoc( this->calcXOffset( loc.x ), this->calcYOffset( loc.y ) );
		
		mobLoc -= point;

		distance = ( mobLoc.x() * mobLoc.x()  ) + ( mobLoc.y() * mobLoc.y() );

		if ( distance < slop && distance < closestDistance )
		{
			closestDistance = distance;
			closest = s;
		}
	}
	
	return closest;
}			

GameItem* Map::closestGameItem( const QPoint& point, unsigned long slop  )
{
	QIntDictIterator<Spawn>		it( gItemMgr->spawns() );
	QIntDictIterator<Coins>		itc( gItemMgr->coins() );
	QIntDictIterator<Drop>		itd( gItemMgr->drops() );
	unsigned long				closestDistance;
	unsigned long				distance;
	GameItem*					closest = NULL;
	bool						animate = this->animateMap();
	
	closestDistance = ULONG_MAX;

	while ( it.current() )
	{
		Spawn* s = it.current();
		++it;
		
		Location		loc = s->approximatePosition( animate );

		QPoint			mobLoc( this->calcXOffset( loc.x ), this->calcYOffset( loc.y ) );
		
		mobLoc -= point;

		distance = ( mobLoc.x() * mobLoc.x()  ) + ( mobLoc.y() * mobLoc.y() );

		if ( distance < slop && distance < closestDistance )
		{
			closestDistance = distance;
			closest = s;
		}
	}
	
	while ( itc.current() )
	{
		Coins* c = itc.current();
		++itc;
		
		Location		loc = c->position();
		
		QPoint			mobLoc( this->calcXOffset( loc.x ), this->calcYOffset( loc.y ) );
		
		mobLoc -= point;

		distance = ( mobLoc.x() * mobLoc.x()  ) + ( mobLoc.y() * mobLoc.y() );

		if ( distance < slop && distance < closestDistance )
		{
			closestDistance = distance;
			closest = c;
		}
	}
			
	while ( itd.current() )
	{
		Drop* d = itd.current();
		++itd;
		
		Location		loc = d->position();
		
		QPoint			mobLoc( this->calcXOffset( loc.x ), this->calcYOffset( loc.y ) );
		
		mobLoc -= point;

		distance = ( mobLoc.x() * mobLoc.x()  ) + ( mobLoc.y() * mobLoc.y() );

		if ( distance < slop && distance < closestDistance )
		{
			closestDistance = distance;
			closest = d;
		}
	}
		
	return closest;
}			

void Map::__drawSpawnNames( QPainter& tmp )
{
	int				count = m_namesToDrawCount;
	bool			animate = this->animateMap();
	QFontMetrics	fm( m_mapFont );

	tmp.setPen( darkGray );		
	while ( count-- )
	{
		Spawn*		s = m_namesToDraw[ count ];
		
		bool		staleUpdate = ( s->updateTime().elapsed() > 60000L );
		
		Location	loc;

		if ( !staleUpdate )
			loc = s->approximatePosition( animate );
		else
			loc = s->position();

		int				xloc = this->calcXOffset( loc.x );
		int				yloc = this->calcYOffset( loc.y );
		
		QString			text;
		text.sprintf( "%2d: %s", s->level(), (const char*)s->name() );

		int				width = fm.width( text );
		tmp.drawText( xloc - ( width / 2 ), yloc + 10, text );
	}
	m_namesToDrawCount = 0;
}

void Map::__drawSpawns( QPainter& tmp )
{
#ifdef DEBUG
//	printf( "paint the spawns\n" );
#endif
	bool			animate = this->animateMap();
	
	Location		ploc = gPlayer->approximatePosition( animate );
	int				pxloc = this->calcXOffset( ploc.x );
	int				pyloc = this->calcYOffset( ploc.y );
	
	int				floor = ploc.z - this->__getPrefInt( "UnderfeetDepth", INIT_FOV_SIZE );
	int				ceiling = ploc.z + this->__getPrefInt( "OverheadDepth", INIT_FOV_SIZE );
	bool			depthFilteringOn = this->__getPrefBool( "SpawnDepthFilter", true );
	bool			showFilteredSpawns = this->__getPrefBool( "ShowFiltered", true );
	bool			velocityLines = this->__getPrefBool( "VelocityLines", true );
	bool			showingNames = this->__getPrefBool( "ShowNames", true );
	bool			blinkAlerted = this->__getPrefBool( "BlinkAlerted", true );

	m_zPos = ploc.z;
	m_namesToDrawCount = 0;

	// paint the spawns
	if ( m_flash.elapsed() > 200 )  // milliseconds between flashing
	{
		m_bFlash = !m_bFlash;
		m_flash.restart();
	}

	QIntDictIterator<Spawn>		it( gItemMgr->spawns() );
	QRect						mapBounds = this->getMapBounds();
	
	Spawn*		s;
	while ( ( s = it.current() ) )
	{
		++it;

		int			drawsize = 4;
		bool		staleUpdate = ( s->updateTime().elapsed() > 60000L );
		bool		selected = s->isSelected();
		bool		depthFiltered = depthFilteringOn && s->depthFilter( floor, ceiling );		
		bool		filtered = !showFilteredSpawns && s->isFlagSet( GameItem::k_filtered );
	
		// if we're not selected, and we're either filtered, or depthFiltered
		if	( !selected && ( filtered || depthFiltered ) )
			continue;
		
		Location		loc;
		
		if ( !staleUpdate )
			loc = s->approximatePosition( animate );
		else
			loc = s->position();
		
		bool		onScreen =	( mapBounds.left() < loc.x ) &&
								( loc.x < mapBounds.right() ) &&
								( mapBounds.top() < loc.y ) &&
								( loc.y < mapBounds.bottom() );
	
		if ( !selected && !onScreen )
			continue;
			 	
		int				xloc = this->calcXOffset( loc.x );
		int				yloc = this->calcYOffset( loc.y );

		if ( selected )
		{
			tmp.setPen( magenta );
			tmp.drawLine( pxloc, pyloc, xloc, yloc );
			if ( !onScreen )
				continue;
		}

		if ( showingNames )
		{
			long		xdiff = pxloc - xloc;
			long		ydiff = pyloc - yloc;
			long		cirDist = this->scale( m_playerFOVSize );

			long		dist = ( xdiff * xdiff ) + ( ydiff * ydiff );
			if ( dist < ( cirDist * cirDist ) )
				m_namesToDraw.insert( m_namesToDrawCount++, s);
		}


#ifdef DEBUG
//		printf( "draw velocities\n" );
#endif
		// draw velocities
		// don't draw the velocity line for the user's player.
		if ( velocityLines && !s->isPlayer() )
		{
			tmp.setPen( darkGray );
			if ( s->deltaX() || s->deltaY() )
				tmp.drawLine( xloc, yloc, xloc - s->deltaX(), yloc - s->deltaY() );
		}

		// select brush color
		if ( s->level() == 0 || s->isFlagSet( GameItem::k_unnamed ) )
			tmp.setBrush( gray );
		else
			tmp.setBrush( gPlayer->pickConColor( s ) );

		if ( blinkAlerted && s->isFlagSet( GameItem::k_alert ) && m_bFlash )
			tmp.setPen( yellow );
		else if ( m_bFlash && s->isFlagSet( m_highlightFlag ) )
			tmp.setPen( white );
		else if ( s->isFlagSet( GameItem::k_unnamed ) )
		{
			tmp.setPen( NoPen );
			drawsize = 3;
		}
		else
		{
			if ( s->isPC() )
			{
				if ( s->isCorpse() )
					tmp.setPen( yellow );
				else
					tmp.setPen( magenta );
			}
			else
			{
				if ( s->isCorpse() )
					tmp.setPen( cyan );
				else
				{
					tmp.setPen( NoPen );
					drawsize = 3;
				}
			}
		}
					

#ifdef DEBUG
//		printf( "draw corpse boxes\n" );
#endif
		// box for corpse, otherwise circle
		if ( s->isCorpse() )
			tmp.drawRect( xloc - drawsize, yloc - drawsize, 2 * drawsize, 2 * drawsize );
		else
		{	
			if ( !s->isPC() || s->isFlagSet( GameItem::k_unnamed ) )
				tmp.drawEllipse( xloc - drawsize, yloc - drawsize, 2 * drawsize, 2 * drawsize );
			else
			{
				tmp.drawLine( xloc, yloc - drawsize, xloc, yloc + drawsize );
				tmp.drawLine( xloc - drawsize, yloc, xloc + drawsize, yloc );
			}
		}

#ifdef DEBUG
//			printf( "PvP handling\n" );
#endif
/*				// if spawn is another pc, on a different team, and within 8 levels
			// highlight it flashing
			if ( m_bFlash )
			{
				if ( s->highlighted() )
				{
					tmp.setPen( yellow ); 
					tmp.setBrush( NoBrush );
					tmp.drawRect( calcXOffset( xlocation ) - 4,
						calcYOffset( ylocation ) - 4, 8, 8 );
					tmp.setBrush( SolidPattern );
				}

				if ( this->__getPrefBool( pvp ) && ( s->isPC() == 0 ) )
				{
					// if not the same team as us
					if ( !isSameTeam( gPlayer->race(), it->race() ) )
					{
						int diff = it->level() - gPlayer->level();
						if ( diff < 0 )
							diff *= -1;
						// if we are within 8 levels of other player
						if ( diff <= 8 )
						{
							// they are in your range
							switch ( diff + 8 )
							{
								// easy
								case 0:  // you are 8 above them
								case 1:		tmp.setPen( green ); break;
								case 2:  // you are 6 above them
								case 3:		tmp.setPen( darkGreen ); break;
								case 4:  // you are 4 above them
								case 5:		tmp.setPen( blue ); break;
								case 6:  // you are 2 above them
								case 7:		tmp.setPen( darkBlue ); break;
								case 8:		tmp.setPen( white ); break;
								case 9:  // you are 1 below them
								case 10:	tmp.setPen( yellow ); break;
								case 11:  // you are 3 below them
								case 12:	tmp.setPen( magenta ); break;
								case 13:  // you are 5 below them
								case 14:	tmp.setPen( red ); break;
								case 15:  // you are 7 below them
								case 16:	tmp.setPen( darkRed ); break;
							}
							tmp.setBrush( NoBrush );
							tmp.drawRect( calcXOffset( xlocation ) - drawsize - 1,
								calcYOffset( ylocation ) - drawsize - 1, 
								2 * ( drawsize + 1 ),
								2 * ( drawsize + 1 ) );
							tmp.setBrush( SolidPattern );
						}
					}
				} // if decorate pvp

		       // circle around pvp pets
				if ( this->__getPrefBool( pvp ) && ( it->petOwnerId() != 0 ) )
				{
					if ( !isSameTeam( gPlayer->race(), spawns[ ID2Index( it->petOwnerId() ) ].race() ) )
					{
						tmp.setBrush( NoBrush );
						tmp.setPen( pickConColor( gPlayer->getLevel(), it->level() ) );
						//	    tmp.drawEllipse (calcXOffset (xlocation) - 4,
						//                calcYOffset (ylocation) - 4, 8, 8);
						tmp.drawEllipse( calcXOffset( xlocation ) - 3,
						    calcYOffset( ylocation ) - 3, 6, 6);
						tmp.setBrush( SolidPattern );
					}
				}
			}
*/
	}

#ifdef DEBUG
//	printf( "done drawing spawns\n" );
#endif
}

void Map::__drawSpawnPoints( QPainter& tmp )
{
	long		count = gSpawnMonitor->spawnPoints().count();

	if ( !count )
		return;
	
	QAsciiDictIterator<SpawnPoint>		it( gSpawnMonitor->spawnPoints() );
	SpawnPoint*		sp;
	while ( ( sp = it.current() ) )
	{
		++it;

		if ( sp->m_diffTime == 0 || sp->m_deathTime == 0 )
			tmp.setPen( darkGray );
		else
		{
			unsigned char age = sp->age();

			if ( age == 255 )
				continue;

			if ( age > 220 )
			{
				if ( m_renderCount % 2 )
					continue;
				tmp.setPen( red );
			}
			else
				tmp.setPen( QColor( age, age, 0 ) );
		}
	
		int			x = this->calcXOffset( sp->x );
		int			y = this->calcYOffset( sp->y );

		tmp.drawLine( x, y - 2, x, y + 2 );
		tmp.drawLine( x - 2, y, x + 2, y );
	}
}
	
void Map::__drawDebugInfo( QPainter& tmp, int fps )
{
	// show coords of upper left corner and lower right corner
	tmp.setPen( yellow );
	QString ts;
	ts.sprintf( "(%d, %d)", (int)( m_screenCenterX * m_ratio ), (int)( m_screenCenterY * m_ratio ) );
	tmp.drawText( 10, 8, ts );
	ts.sprintf( "(%d, %d)",
		(int)( ( m_screenCenterX - this->width() ) * m_ratio ),
		(int)( ( m_screenCenterY - this->height() ) * m_ratio ) );
	tmp.drawText( this->width() - 90, this->height() - 14, ts );

	// show spawns spots being watched, spawn points found
	long		count = gSpawnMonitor->spawnPoints().count();

	ts.sprintf( "Spawns: %d SPs: %ld", gSpawnMonitor->spawns().count(), count );
	tmp.drawText( 4, this->height() - 14, ts );

	// show frame times
	ts.sprintf( "%2dfps/%dms", fps, m_time.elapsed() );
	tmp.drawText( this->width() - 60, 8, ts );
}
	
bool Map::__drawMapImage( QPainter& p )
{
	QPixmap		mapImage = gMapMgr->mapImage();

	p.save();
	double		scaleX = (double)( m_screenLengthX ) / (double)mapImage.width();
	double		scaleY = (double)( m_screenLengthY ) / (double)mapImage.height();

	scaleX *= m_zoom;
	scaleY *= m_zoom;

	if ( scaleX > 3.0 || scaleY > 3.0 )
		return false;

	p.scale( scaleX, scaleY );

	int		x = this->calcXOffset( gMapMgr->maxX() );
	int		y = this->calcYOffset( gMapMgr->maxY() );

	x += gMapMgr->xtranslate();
	y += gMapMgr->ytranslate();

	p.drawPixmap( x, y, mapImage );
	p.restore();
	return true;
}

void Map::paintMap( QPainter* p )
{

#ifdef DEBUG
	static long		frameTimes[ 40 ];
	static int		frameTimeIndex = 0;

//	debug( "Map::paintMap()" );
#endif
	
	m_renderCount++;
	
	if ( !m_running )
	{
		if ( !gMapMgr->isMapImageLoaded() || !this->__drawMapImage( *p ) )
		{
			m_offscreen->fill( black );
			p->drawPixmap( 0, 0, *m_offscreen );
		}
		return;
	}

	if ( m_focusItem )
	{
		if ( m_zoom > 1 )
			this->calculateScale();
   	}

	QPainter		tmp;
	bool			zoneLoaded = m_mgr->isZoneLoaded();
	   	
	// begin painting
	tmp.begin( m_offscreen );
	tmp.setPen( NoPen );
	tmp.setFont( m_mapFont );

	if (	!gMapMgr->isMapImageLoaded() ||
			!this->__getPrefBool( "ShowBackgroundImage", true ) ||
			!this->__drawMapImage( tmp ) )
		tmp.fillRect( m_offscreen->rect(), m_backgroundColor );

	bool		playerInited = !gPlayer->isFlagSet( GameItem::k_uninited );

	// if there is no zone loaded, there are some things we won't draw,
	//	like, the player, the spawns and drops, etc.
	if ( zoneLoaded )
	{
		if ( playerInited )
		{
			if ( this->__getPrefBool( "ShowPlayerView", true ) )
				this->__drawPlayerNeighborhood( tmp );
	
			if ( this->__getPrefBool( "ShowPlayerView", true ) )
				this->__drawPlayerFOV( tmp );
		}
	}
	
	if ( this->__getPrefBool( "ShowGrid", true ) )
		this->__drawGrid( tmp );

	if ( this->__getPrefBool( "ShowMapLines", true ) )
		this->__drawLines( tmp );
	
	if ( this->__getPrefBool( "ShowMapPoints", true ) )
		this->__drawLocations( tmp );
	
	if  ( zoneLoaded )
	{
		if ( this->__getPrefBool( "ShowSpawnPoints", true ) )
			this->__drawSpawnPoints( tmp );

		if ( playerInited )
			this->__drawPlayer( tmp );

		if ( this->__getPrefBool( "ShowDrops", true ) )
			this->__drawDrops( tmp );
	
		if ( this->__getPrefBool( "ShowCoins", true ) )
			this->__drawCoins( tmp );
	
		this->__drawSpawns( tmp );
	
		if ( playerInited && this->__getPrefBool( "ShowNames", true ) )
			this->__drawSpawnNames( tmp );
	}
	
#ifdef DEBUG
	if ( this->__getPrefBool( "ShowDebugInfo", true ) )
	{
		long			totalTime = 0;
		float			fps = 0;
	
		frameTimes[ frameTimeIndex ] = m_time.elapsed();
		frameTimeIndex = ( frameTimeIndex + 1 ) % 40;
	
		for ( int i = 0; i < 40; i++ )
			totalTime += frameTimes[ i ];
	
		fps = 40.0 / ( totalTime / 1000.0 );
	
		this->__drawDebugInfo( tmp, (int)fps );
		m_time.restart();
	}
#endif

	tmp.end();

	p->drawPixmap( 0, 0, *m_offscreen );
}

void Map::paintEvent( QPaintEvent* )
{
#ifdef DEBUG
//	debug( "Map::paintEvent()" );
#endif
	QPainter		p;

	p.begin( this );
	this->paintMap( &p );
	p.end();
}


/*
void Map::makeSpawnLine(int n){
      struct trackPoint *walk = &firstPoint[n];
      int cnt=0;
      cnt = cnt;
      while (walk){
          cnt++;
          walk = walk->next;
      }  
      walk = &firstPoint[n];
      while (cnt>254){
          makeSimpleLine(walk, 255, n);
          for (int c = 0;c < 254;c++,cnt--,walk = walk->next){
             //we back up one point.
 	     //For loops are fun!
             if (!walk) break;
          }
      }
      if (cnt > 1)
          makeSimpleLine(walk, cnt, n);
}

void Map::makeSimpleLine(trackPoint *walk, int numpnts, int n){

         trackPoint *walk2;
         char dapath[256];
         //Don't save lines where they just hit the line button. Andrew
         sprintf(dapath,"%s/%s_mobpath.map", CONFDIR, zoneShort);
         FILE *fh = fopen(dapath,"a");
         if (!fh) return;
	 fprintf (fh, "M,%s,%s,%d", (const char*)spawns[n].name, "blue", numpnts);
	 for (int c = 0; c < numpnts && walk != 0; c++, walk=walk->next)
	 {
	    fprintf (fh, ",%d,%d,%d", walk->x, walk->y, walk->z);
            walk2 = walk;
	 }
	 fprintf (fh, "\n");
         fflush(fh);
         fclose(fh);
         walk = walk2;//move back one point.

}

*/


