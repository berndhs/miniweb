#include "miniwebdebug.h"
#include <stdlib.h>
#include <qapplication.h>

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


using namespace std;

namespace miniweb {

void UseMyOwnMsgHandler ()
{
  qInstallMsgHandler (miniweb::MiniwebMessageOutput);
}

void MiniwebMessageOutput (QtMsgType type, const char* msg)
{
#if MINIWEB_DEBUG
  switch (type) {
  case QtDebugMsg:
    cout << "Qt Debug: " << msg << endl;
    break;
  case QtWarningMsg:
    cout << "Qt Warn: " << msg << endl;
    break;
  case QtCriticalMsg:
    cout << "Qt Critical: " << msg << endl;
    break;
  case QtFatalMsg:
    cout << "Qt Fatal: " << msg << endl;
    abort();
    break;
  default:
    cout << " unknown Qt msg type: " << msg << endl;
    break;
  }
#else
  switch (type) {
  case QtFatalMsg:
    cout << "Qt Fatal: " << msg << endl;
    abort();
    break;
  case QtDebugMsg:
  case QtWarningMsg:
  case QtCriticalMsg:
  default:
    // start prayer, maybe it's not a problem
    break;
  }
#endif

}

}
