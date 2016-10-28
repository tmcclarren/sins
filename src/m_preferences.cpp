/****************************************************************************
** PreferenceFile meta object code from reading C++ file 'preferences.h'
**
** Created: Fri Sep 28 13:03:54 2001
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.1   edited 2001-04-23 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "preferences.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *PreferenceFile::className() const
{
    return "PreferenceFile";
}

QMetaObject *PreferenceFile::metaObj = 0;

void PreferenceFile::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(QObject::className(), "QObject") != 0 )
	badSuperclassWarning("PreferenceFile","QObject");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString PreferenceFile::tr(const char* s)
{
    return qApp->translate( "PreferenceFile", s, 0 );
}

QString PreferenceFile::tr(const char* s, const char * c)
{
    return qApp->translate( "PreferenceFile", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* PreferenceFile::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) QObject::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (PreferenceFile::*m1_t0)();
    typedef void (QObject::*om1_t0)();
    typedef void (PreferenceFile::*m1_t1)();
    typedef void (QObject::*om1_t1)();
    typedef void (PreferenceFile::*m1_t2)();
    typedef void (QObject::*om1_t2)();
    m1_t0 v1_0 = &PreferenceFile::save;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &PreferenceFile::load;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &PreferenceFile::revert;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    QMetaData *slot_tbl = QMetaObject::new_metadata(3);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(3);
    slot_tbl[0].name = "save()";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    slot_tbl[1].name = "load()";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Public;
    slot_tbl[2].name = "revert()";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Public;
    metaObj = QMetaObject::new_metaobject(
	"PreferenceFile", "QObject",
	slot_tbl, 3,
	0, 0,
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
