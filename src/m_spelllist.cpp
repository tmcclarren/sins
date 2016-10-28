/****************************************************************************
** SpellListView meta object code from reading C++ file 'spelllist.h'
**
** Created: Fri Sep 28 13:06:05 2001
**      by: The Qt MOC ($Id: qt/src/moc/moc.y   2.3.1   edited 2001-04-23 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#if !defined(Q_MOC_OUTPUT_REVISION)
#define Q_MOC_OUTPUT_REVISION 9
#elif Q_MOC_OUTPUT_REVISION != 9
#error "Moc format conflict - please regenerate all moc files"
#endif

#include "spelllist.h"
#include <qmetaobject.h>
#include <qapplication.h>



const char *SpellListView::className() const
{
    return "SpellListView";
}

QMetaObject *SpellListView::metaObj = 0;

void SpellListView::initMetaObject()
{
    if ( metaObj )
	return;
    if ( qstrcmp(BaseListView::className(), "BaseListView") != 0 )
	badSuperclassWarning("SpellListView","BaseListView");
    (void) staticMetaObject();
}

#ifndef QT_NO_TRANSLATION

QString SpellListView::tr(const char* s)
{
    return qApp->translate( "SpellListView", s, 0 );
}

QString SpellListView::tr(const char* s, const char * c)
{
    return qApp->translate( "SpellListView", s, c );
}

#endif // QT_NO_TRANSLATION

QMetaObject* SpellListView::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    (void) BaseListView::staticMetaObject();
#ifndef QT_NO_PROPERTIES
#endif // QT_NO_PROPERTIES
    typedef void (SpellListView::*m1_t0)(Spell*);
    typedef void (QObject::*om1_t0)(Spell*);
    typedef void (SpellListView::*m1_t1)(Spell*);
    typedef void (QObject::*om1_t1)(Spell*);
    typedef void (SpellListView::*m1_t2)(Spell*);
    typedef void (QObject::*om1_t2)(Spell*);
    m1_t0 v1_0 = &SpellListView::addSpell;
    om1_t0 ov1_0 = (om1_t0)v1_0;
    m1_t1 v1_1 = &SpellListView::removeSpell;
    om1_t1 ov1_1 = (om1_t1)v1_1;
    m1_t2 v1_2 = &SpellListView::updateSpell;
    om1_t2 ov1_2 = (om1_t2)v1_2;
    QMetaData *slot_tbl = QMetaObject::new_metadata(3);
    QMetaData::Access *slot_tbl_access = QMetaObject::new_metaaccess(3);
    slot_tbl[0].name = "addSpell(Spell*)";
    slot_tbl[0].ptr = (QMember)ov1_0;
    slot_tbl_access[0] = QMetaData::Public;
    slot_tbl[1].name = "removeSpell(Spell*)";
    slot_tbl[1].ptr = (QMember)ov1_1;
    slot_tbl_access[1] = QMetaData::Public;
    slot_tbl[2].name = "updateSpell(Spell*)";
    slot_tbl[2].ptr = (QMember)ov1_2;
    slot_tbl_access[2] = QMetaData::Public;
    metaObj = QMetaObject::new_metaobject(
	"SpellListView", "BaseListView",
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
