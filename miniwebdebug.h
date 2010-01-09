#ifndef MINIWEBDEBUG_H
#define MINIWEBDEBUG_H

//
//  Copyright (C) 2009 - Bernd H Stramm 
//
// This program is distributed under the terms of 
// the GNU General Public License version 3 
//
// This software is distributed in the hope that it will be useful, 
// but WITHOUT ANY WARRANTY; without even the implied warranty 
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
//


#include <qapplication.h>
#include <iostream>

#if MINIWEB_DEBUG
#include <QDebug>
#define QDEBUG qDebug
#endif

namespace miniweb {

void UseMyOwnMsgHandler ();

void MiniwebMessageOutput (QtMsgType type, const char* msg);


}
#endif
