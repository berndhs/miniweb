#ifndef WEBBOX_H
#define WEBBOX_H

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
#include <QMenu>
#include <QShortcut>
#include <QSize>
#include "ui_webbox.h"
#include "minipage.h"
#include "useragent.h"


namespace miniweb {


class WebBox : public QWidget, public Ui_WebBox {

Q_OBJECT

public:

  WebBox ();
  
  void SetApp (QApplication * papp) { pApp = papp;}
  
  void SetPage (QString url);
  
  void Resize (const int wid, const int hi);
  void SetAgent (const UserAgent &ag, const bool setsize = true);
  
  void SetFrame (const bool frame);
  
public slots:

  void UserWantsSomething ();
  void update ();
  void quit   ();
  
  void NewUrlOk ();
  void NewUrlCancel ();
  void EnableNewUrl ();
    
  void LoadDone (bool ok);
  void LoadStarted ();
  
private:
  
  void InitUserMenu ();
  void DisableNewUrl ();
  
  
  MiniPage * thePage;
  
  QMenu   userMenu;
  
  QAction * userQuit;
  QAction * userNevermind;
  QAction * userOpen;
  QAction * userFrame;

  QApplication  * pApp;
  
  QString currentUrl;
  Qt::WindowFlags  defaultWinFlags;
  bool showFrame;
  
  QShortcut  *controlL;
  QShortcut  *controlO;
  QShortcut  *controlM;
  QShortcut  *escapeKey;

};

} // namespace

#endif


