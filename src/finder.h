// finder.h
//		SINS Distributed under GPL

#ifndef FINDER_H
#define FINDER_H

#include <qobject.h>
#include "spawn.h"

class QLineEdit;
class QRegExp;

class Finder: public QObject
{
Q_OBJECT
public:
	Finder( QLineEdit* editor, GameItem::GameItemFlag flagToUse );

public slots:
	void handleFind();
	
protected:
	QLineEdit*		m_editor;
	QRegExp*		m_reg;
	GameItem::GameItemFlag	m_flag;
};

#endif
