// finder.cpp
//		SINS Distributed under GPL

#include <stdio.h>
#include <qlineedit.h>
#include <qregexp.h>
#include "finder.h"
#include "spawn.h"
#include "itemmgr.h"

Finder::Finder( QLineEdit* editor, GameItem::GameItemFlag flagToUse ):
	QObject( NULL, "finder" )
{
	m_flag = flagToUse;
	m_editor = editor;
	m_reg = NULL;
	connect( editor, SIGNAL( returnPressed() ), this, SLOT( handleFind() ) );
}

void Finder::handleFind()
{
	QString		textToFind = m_editor->text();
	
	if ( textToFind.length() )
	{
		if ( m_reg )
			delete m_reg;
		
		m_reg = new QRegExp( textToFind );
	
		if ( m_reg->isValid() )
		{
			QIntDictIterator<Spawn>		it( gItemMgr->spawns() );
			Spawn*			sp;
			while ( ( sp = it.current() ) )
			{
				++it;
		
				if ( m_reg->match( sp->name() ) != -1  )
					sp->setFlag( m_flag );
				else
					sp->clearFlag( m_flag );
			}
		}
		else
		{
			delete m_reg;
			m_reg = NULL;
		}
	}
}
