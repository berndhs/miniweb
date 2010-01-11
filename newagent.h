#ifndef NEWAGENT_H
#define NEWAGENT_H

//
//  Copyright (C) 2010 - Bernd H Stramm 
//
// This program is distributed under the terms of 
// the GNU General Public License version 3 
//
// This software is distributed in the hope that it will be useful, 
// but WITHOUT ANY WARRANTY; without even the implied warranty 
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
//

#include <QWidget>
#include <QFrame>
#include <QShortcut>
#include "ualist.h"

namespace miniweb {

class WebBox;

class NewAgent : public QFrame {

Q_OBJECT

public:

   NewAgent (QWidget * parent = 0);
   
   void Init (UAList * ual);
   
public slots:

  void DoCancel ();
  void DoSave ();
  void DoDelete ();
  void EditNew ();
  void EditAgent (const QString name, bool isnew = false);
   

private:

  void ConnectButtons ();
  void DisconnectButtons ();
  void CloseWin ();
  void OpenWin (QString title);
  
  UserAgent  * newAgent;

  UAList * uaList;
  WebBox * webBox;
  
  QShortcut * controlD;  // delete
  QShortcut * controlA;  // save
  QShortcut * escapeKey; // cancel

};

}

#endif
