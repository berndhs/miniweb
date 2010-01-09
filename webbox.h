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
#include "ui_webbox.h"
#include "minipage.h"


namespace miniweb {


class WebBox : public QWidget, public Ui_WebBox {

Q_OBJECT

public:

  WebBox ();
  ~WebBox ();
  
  void SetApp (QApplication * papp) { pApp = papp;}
  
  void SetPage (QString url);
  
  void SetFrame (const bool frame);
  
public slots:

  void UserWantsSomething ();
  void update ();
  void quit   ();
  
  void NewUrlOk ();
  void NewUrlCancel ();
    
  void LoadDone (bool ok);
  void LoadStarted ();
  
private:
#if 0
  WebBox ();
  #endif
  
  void InitUserMenu ();
  void DisableNewUrl ();
  void EnableNewUrl ();
  
  
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

};

} // namespace

#endif


