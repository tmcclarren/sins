/****************************************************************************
** Compass meta object code from reading C++ file 'compass.h'
**
** Created: Fri Sep 28 12:59:30 2001
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.1   edited 2001-04-23 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "compass.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *Compass::className() const
{
    return "Compass";
}

QMetaObject *Compass::metaObj = 0;

void Compass::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QWidget::className(), "QWidget") != 0 )
	badSuperclassWarning("Compass","QWidget");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString Compass::tr(const char* s)
{
    return qApp->translate( "Compass", s, 0 );
}

QString Compass::tr(const char* s, const char * c)
{
    return qApp->translate( "Compass", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* Compass::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QWidget::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (Compass::*m1_t0)(int);
    typedef void (QObject::*om1_t0)(int);
    typedef void (Compass::*m1_t1)(QListViewItem*);
    typedef void (QObject::*om1_t1)(QListViewItem*);
    typedef void (Compass::*m1_t2)(int,int,int);
    typedef void (QObject::*om1_t2)(int,int,int);
    typedef void (Compass::*m1_t3)(int,int);
    typedef void (QObject::*om1_t3)(int,int);
    m1_t0 v1_0 = &Compass::setAngle;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &Compass::selectSpawn;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &Compass::setPlayer;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    m1_t3 v1_3 = &Compass::selSpawnUpdate;
    om1_t3 ov1_3 = (om1_t3)v1_3;
    QMetaData *slot_tbl = QMetaObject::new_metadata(4);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(4);
    slot_tbl[0].name = "setAngle(int)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    slot_tbl[1].name = "selectSpawn(QListViewItem*)";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Public;
    slot_tbl[2].name = "setPlayer(int,int,int)";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Public;
    slot_tbl[3].name = "selSpawnUpdate(int,int)";
    slot_tbl[3].ptr = (QMember)ov1_3;
    slot_tbl_access[3] = QMetaData::Public;
    typedef void (Compass::*m2_t0)(int);
    typedef void (QObject::*om2_t0)(int);
    m2_t0 v2_0 = &Compass::angleChanged;
    om2_t0 ov2_0 = (om2_t0)v2_0;
    QMetaData *signal_tbl = QMetaObject::new_metadata(1);
    signal_tbl[0].name = "angleChanged(int)";
    signal_tbl[0].ptr = (QMember)ov2_0;
    metaObj = QMetaObject::new_metaobject(
	"Compass", "QWidget",
	slot_tbl, 4,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    metaObj->set_slot_access( slot_tbl_access );
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    return metaObj;
}

// SIGNAL angleChanged
void Compass::angleChanged( int t0 )
{
    activate_signal( "angleChanged(int)", t0 );
}
