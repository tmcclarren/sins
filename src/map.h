//	map.h
//		SINS Distributed under GPL

#ifndef MAP_H
#define MAP_H

#include <qarray.h>
#include <qdialog.h>
#include <qgrid.h>
#include <qintdict.h>
#include <qlabel.h>
#include <qlist.h>
#include <qpixmap.h>
#include <qpushbutton.h>
#include <qslider.h>
#include <qstring.h>
#include <qwidget.h>
#include <qvbox.h>
#include <qvector.h>
#include <limits.h>

#include "basewindow.h"
#include "everquest.h"
#include "spawnlist.h"
#include "player.h"

#define	MAX_LINE_LENGTH		16384
#define MAX_LINES			16384

class QButtonGroup;
class QComboBox;
class QLineEdit;
class QPopupMenu;
class QSpinBox;
class QVBox;
class EQInterface;
class Map;
class MapMgr;
class Filter;
class Finder;

class LineDlg: public QDialog
{
Q_OBJECT

public:
	LineDlg( QWidget* parent, QString name, MapMgr* map );

	QComboBox* 			m_LineColor;
	QLineEdit*			m_LineName;
	QFrame*				m_ColorPreview;

public slots:
	void changeColor( const QString & );
};

// class to represent labelled locations on the map
class MapLabel
{
public:
	MapLabel():
		m_location(), m_color(), m_name() { }
	
	MapLabel( WORD x, WORD y, const QString& color, const QString& name ):
		m_location( x, y, 0 ), m_color( color ), m_name( name ) { }
		
	Location			m_location;

	QString				m_color;
	QString				m_name;
};

// class to represent the lines on the map
class MapLine
{
public:
	enum eLineType {
		e2d,
		e3d
	};

	MapLine(): m_locations(), m_color(), m_name() { }
	
	MapLine( const QArray<Location>& locs, const QString& color, const QString& name, eLineType type );	
	MapLine( const Location& loc, const QString& color, const QString& name );
	MapLine( WORD x, WORD y, WORD z, const QString& color, const QString& name );
	MapLine( WORD x, WORD y, const QString& color, const QString& name );
	
	void determineBounds();
		
	QArray<Location>	m_locations;	
	QString				m_color;
	QString				m_name;
	eLineType			m_type;
	QRect				m_bounds;
};

// "tooltip"-style popup window that shows up over the map
class MapPopup: public QLabel
{
public:
	MapPopup();

	void position( const QPoint& mouse );
};


class DepthSlider: public QSlider
{
Q_OBJECT
public:
	DepthSlider( QWidget* parent = NULL, const char* name = NULL );
	
protected:
	virtual void paintSlider( QPainter* p, const QColorGroup& cg, const QRect& r );
	int available() const;
	int positionFromValue( int ) const;
};

class DepthControlBox: public QVBox
{
Q_OBJECT
public:
	DepthControlBox( QWidget* parent = NULL, Map* myMap = NULL, const char* name = NULL );

public slots:
	void updateZPos( int zPos );

	void setFloor( int newFloor );
	void setCeiling( int newCeiling );	

	void setRange( int minZ, int maxZ );

	void resetControls();

	int getFloor() { return -( m_floorSlider->value() ); }
	int getCeiling() { return -( m_ceilingSlider->value() ); }

	void zoneEnd( const QString& );
	void mapLoaded();

signals:
	void floorChanged( int newFloor );
	void ceilingChanged( int newCeiling );
	
protected slots:
	void __setFloor( int newFloor );
	void __setCeiling( int newCeiling );

protected:
	DepthSlider*				m_floorSlider;
	DepthSlider*				m_ceilingSlider;
	Map*						m_map;
	QLabel*						m_floorText;
	QLabel*						m_ceilingText;
};

class ZoomButton: public QPushButton
{
Q_OBJECT
public:
	ZoomButton( const QString& title, QWidget* parent );
	
	virtual void drawButton( QPainter* );
};

class ZoomControlBox: public QHBox
{
Q_OBJECT
public:
	ZoomControlBox( QWidget* parent = NULL, Map* myMap = NULL, const char* name = NULL );

public slots:
	void zoomChanged( int );

protected:
	QButtonGroup*		m_buttonGroup;
	Map*				m_map;
};

class MapMgr: public QObject
{
Q_OBJECT
public:
	MapMgr( const char* name = NULL );
	
	void init();
	
	bool checkPos( const Location& loc );
	
	// for map editting
	QString currentLineColor() { return m_curLineColor; }
	QString currentLineName() { return m_curLineName; }

	QList<MapLabel>* getLabels() { return &m_labels; }
	QList<MapLine>* getLines() { return &m_lines; }
	
	WORD minX() { return m_minX; }
	WORD minY() { return m_minY; }
	WORD maxX() { return m_maxX; }
	WORD maxY() { return m_maxY; }
	WORD minZ() { return m_minZ; }
	WORD maxZ() { return m_maxZ; }

	int mapLengthX() { return m_mapLengthX; }
	int mapLengthY() { return m_mapLengthY; }
	
	int xtranslate() { return m_xtranslate; }
	int ytranslate() { return m_ytranslate; }

	bool isMapLoaded() { return m_mapLoaded; }
	bool isMapImageLoaded() { return m_mapImageLoaded; }
	bool isZoneLoaded() { return m_zoneLoaded; }
	
	QPixmap& mapImage() { return m_mapImage; }

public slots:
	// map editing
	void showLineDlg();
	void setLineName( const QString& );
	void setLineColor( const QString& );
	void addLocation();
	void startLine();
	void addLinePoint();
	void delLinePoint();
	
	// map loading/saving
	void loadMap();
	void loadFileMap( const QString& fullPath );
	void saveMap();

	// map display
	void zoneBegin();
	void zoneEnd( const QString& newZoneName );
	void zoneChanged( const QString& newZoneName );
	
	void changeImageXTranslation( int );
	void changeImageYTranslation( int );
signals:
	void mapUnloaded();
	void mapLoaded();
	void zoneLoaded();

protected:
	bool __fixFileName( QString& filename );			// fixes up filename to match something that actually exists
	
	static QPopupMenu*			m_menu;

	bool						m_mapLoaded;
	bool						m_mapImageLoaded;
	bool						m_zoneLoaded;
	QString						m_mapFileName;
	QString						m_zoneName;
		
	int							m_number;

	int							m_xtranslate;
	int							m_ytranslate;
	
	QList<MapLabel>				m_labels;
	QList<MapLine>				m_lines;

	QString						m_curLineColor;
	QString						m_curLineName;
	LineDlg*					m_lineProps;

	WORD						m_minX;					// min/max are the boundaries of the zone, as far as we know
	WORD						m_maxX;					//	they change as spawns move around
	WORD						m_minY;
	WORD						m_maxY;
	WORD						m_minZ;
	WORD						m_maxZ;
	int							m_mapLengthX;			// m_maxX - m_minX
	int							m_mapLengthY;			// m_maxY - m_minY

	QPixmap						m_mapImage;
};
	
class MapWindow: public BaseWindow
{
Q_OBJECT
public:
	MapWindow( MapMgr* mgr, const QString& title, unsigned short number, const char* name );

public slots:
	void mapLoaded();
	void mapUnloaded();

	void toggleControls();
	void toggleFilterControls();

	void setZPos( int );

	Map* getMap() { return m_map; }
protected:
	Map*					m_map;
	MapMgr*					m_mgr;
	DepthControlBox*		m_filterControls;
	QHBox*					m_mapControls;
	ZoomControlBox*			m_zoomControls;
	QSpinBox*				m_fpsControl;
	QLineEdit*				m_find;
	Finder*					m_finder;
	QLabel*					m_ypos;
	QLabel*					m_xpos;
	QLabel*					m_zpos;
	unsigned short			m_number;
	int						m_toggleControlsID;
	int						m_toggleFilterControlsID;
};

class Map: public QWidget
{
Q_OBJECT
public:
	Map(	MapMgr*		mgr,
			int			number,
			GameItem::GameItemFlag highlightFlag,
			QWidget* parent = NULL,
			const char *name = NULL );
	
	// Qt cruft
	QSize sizeHint() const;
	QSize minimumSizeHint() const;
	QSizePolicy sizePolicy() const;
	QRect getRect() { return rect(); }

	QPopupMenu* getOptionsMenu();
	
	// finds the spawn closest to "point" but still within "slop"
	Spawn* closestSpawn( const QPoint& point, unsigned long slop = ULONG_MAX );
	// likewise, but includes Coin and Drop objects
	GameItem* closestGameItem( const QPoint& point, unsigned long slop = ULONG_MAX );
	
	bool running() { return m_running; }
	
public slots:
	// zoom routines
	bool canZoom( int zoomStep );
	void setZoom( int zoomStep );
	int getZoom() { return m_zoomStep; }
	void zoomIn() { this->setZoom( ++m_zoomStep ); }
	void zoomOut() { this->setZoom( --m_zoomStep ); }
	void setCeiling( int newCeiling );
	void setFloor( int newFloor );

	void moveCenter( int diffX, int diffY );

	void decreasePlayerNeighborhood( int amount );
	void increasePlayerNeighborhood( int amount );
	void setPlayerNeighborhood( int to );

	void setFPS( int framesPerSecond );
	void refreshMap();

	void toggleLockControls();
	void toggleSpawnDepthFiltering();
	void toggleMapDepthFiltering();
	void toggleMapFade();
	void togglePopup();
	void toggleFiltered();
	void toggleVelocityLines();
	void toggleMapLines();
	void toggleAnimate();
	void togglePlayerView();
	void toggleGrid();
	void toggleLocations();
	void toggleDrops();
	void toggleCoins();
	void toggleSpawnPoints();
	void toggleSpawnNames();
	void toggleDebugInfo();
	void toggleBackgroundImage();
	void toggleBlinkAlerted();
	void toggleFocusOnPlayer();
	void setFocusOnSelection();
	
	void mapUnloaded();
	void mapLoaded();
	void zoneLoaded();

	void pickGridColor();
	void pickBackgroundColor();
	void pickFont();
	
	void deleteSpawn( Spawn* spawn );

signals:
	void zoomChanged( int newZoom );

protected:
	friend class DepthControlBox;
	friend class ZoomControlBox;
	friend class MapWindow;
	friend class EQInterface;

	// inits anything that should be "fresh" when we enter a new zone
	void init();

	// start/stop the map on it's timer (for refreshing the map)
	void startMap();
	void stopMap();
	bool animateMap() { return this->__getPrefBool( "AnimateSpawnMovement", true  ); }
	
	// more Qt cruft		
	void paintEvent( QPaintEvent* );
	void mousePressEvent( QMouseEvent* );
	void mouseReleaseEvent( QMouseEvent* );
	void mouseMoveEvent( QMouseEvent* event );
	void resizeEvent( QResizeEvent* );
	void keyPressEvent( QKeyEvent* );

	// keeps the map boundaries, and keeps the map centered
	// and makes sure we don't scroll too far
	void calculateScale();
	void adjustCenter( const Location& loc );
	void recalcScreenBounds();
	void recalcMapBounds();
		
	void __togglePreference( const QString& boolPref, int menuID );
	void __setZoom( int zoomStep );

	// preference routines (mostly just to keep pref naming straight)
	bool __getPrefBool( const QString& prefName, bool def );
	void __setPrefBool( const QString& prefName, bool newValue );
	int __getPrefInt( const QString& prefName, int def );
	void __setPrefInt( const QString& prefName, int newValue );
	void __setPrefString( const QString& prefName, const QString& newValue );
	QString __getPrefString( const QString& prefName, const QString& defValue );

	// drawing routines
	void paintMap( QPainter* );
	void __drawPlayerNeighborhood( QPainter& tmp );			// draws the large circle showing stuff nearby
	bool __drawMapImage( QPainter& tmp );					// draws a loaded map image (i.e., "LakeofIllOmen.pgm" )
	void __drawGrid( QPainter& tmp );						// draws the map grid
	void __drawPlayerFOV( QPainter& tmp );					// draws our field of view lines
	void __drawLines( QPainter& tmp );						// draws the map
	void __drawLocations( QPainter& tmp );					// draws locations on the map
	void __drawPlayer( QPainter& tmp );						// draws the dot representing the player
	void __drawDrops( QPainter& tmp );						// draws dots representing drops
	void __drawCoins( QPainter& tmp );						// draws dots representing coins
	void __drawSpawns( QPainter& tmp );						// draws a dot for each spawn, with velocity line
	void __drawSpawnNames( QPainter& tmp );					// draws spawn names
	void __drawSpawnPoints( QPainter& tmp );				// draw each spawn point
	void __drawDebugInfo( QPainter& tmp, int fps );			// draws some debug info onto the map

	QRect& getMapBounds() { return m_bounds; }

	void pickNewColor( const QString& pref, QColor& newColor );

	// used for drawing stuff onto the map -- translate stuff from "EQ" coords into pixel coords
	//int calcXOffset( int mapCoordinate ) { return m_screenCenterX - (int)( mapCoordinate / m_ratioX ); }
	//int calcYOffset( int mapCoordinate ) { return m_screenCenterY - (int)( mapCoordinate / m_ratioY ); }
	int calcXOffset( int mapCoordinate ) { return m_screenCenterX - ( ( mapCoordinate * m_ratioI ) >> 11 ); }
	int calcYOffset( int mapCoordinate ) { return m_screenCenterY - ( ( mapCoordinate * m_ratioI ) >> 11 ); }
	
	int scale( int mapCoordinate ) { return (int) ( mapCoordinate / m_ratio ); }
	
	static const unsigned short		m_gridSteps[];
	
	MapMgr*						m_mgr;
	GameItem::GameItemFlag		m_highlightFlag;

	unsigned short				m_number;
	
	QPopupMenu*					m_optionsMenu;
	MapPopup*					m_popup;

	QPixmap*					m_offscreen;

	QTime						m_flash;
	bool						m_bFlash;

	QPoint						m_lastDrag;
	bool						m_drag;
	
	// for display purposes -- saves lots of recalcs
	int							m_zoomStep;				// 0 to MAX_ZOOM_STEP (an index into our grid stepping)
	int							m_zoom;					// the zoom level -- '2' is x2, 3 is x3, etc.
	WORD						m_zPos;
	WORD						m_ceiling;
	WORD						m_floor;
	int							m_xoff;
	int							m_yoff;
	int							m_gridRes;
	
	// calculated in 'recalcScreenBounds'
	int							m_screenBoundTop;		// this is a 'bounding' rectangle for m_screenCenter
	int							m_screenBoundLeft;		// we don't let m_screenCenter go beyond these coords
	int							m_screenBoundBottom;
	int							m_screenBoundRight;

	// calculated in 'calculateScale'	
	float						m_ratio;				// ratio of screen size to actual map size
	int							m_ratioI;
	
	// calculated in 'adjustCenter'
	int							m_screenCenterX;		// EQ map origin (0,0) in the view port's local coordinate system
	int							m_screenCenterY;
	QRect						m_bounds;				// the top-left and lower-right pixels in EQ map coordinates
	
	// calculated in 'resizeEvent'
	int							m_screenLengthX;		// screen size, in pixels
	int							m_screenLengthY;

	QFont						m_mapFont;
	QColor						m_playerFOVHighlight;
	QColor						m_playerNeighborhoodHighlight;
	long						m_playerFOVSize;
	QColor						m_gridLineColor;
	QColor						m_backgroundColor;

	QTimer*						m_timer;
	QTime						m_time;
	QTime						m_initTime;
	bool						m_running;
	
	unsigned long				m_renderCount;
	
	Spawn*						m_focusItem;

	QVector<Spawn>				m_namesToDraw;
	int							m_namesToDrawCount;

	int							m_toggleLockControlsID;
	int							m_toggleSpawnDepthFilteringID;
	int							m_toggleMapDepthFilteringID;
	int							m_toggleMapFadeID;
	int							m_showPopupMenuID;
	int							m_filteredMenuID;
	int							m_velocityLinesMenuID;
	int							m_animateSpawnsMenuID;
	int							m_showPlayerViewMenuID;
	int							m_showGridMenuID;
	int							m_showMapLinesID;
	int							m_showLocationsMenuID;
	int							m_showDropsMenuID;
	int							m_showCoinsMenuID;
	int							m_showBackgroundImageID;
	int							m_focusOnPlayerID;
	int							m_focusOnSelectionID;
	int							m_showSpawnPointsID;
	int							m_showSpawnNamesID;
	int							m_blinkAlertedID;
	int							m_showDebugInfoID;
};

#endif
