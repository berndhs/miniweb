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
#include <QTimer>
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
  void SettingsMenu ();
  void update ();
  void quit   ();
  
  void NewUrlOk ();
  void NewUrlCancel ();
  void EnableNewUrl ();
    
  void LoadDone (bool ok);
  void LoadStarted ();
  void Reload ();
  void ReloadSetup ();
  void ReloadNochange ();
  void ToggleFrame ();
  void Help ();
  
private:
  
  void InitUserMenu ();
  void InitSettingsMenu ();
  void DisableNewUrl ();
  void DisableSettings ();
  
  void EditReload ();
  
  void MakeShortcuts ();
  
  
  MiniPage * thePage;
  
  QMenu   userMenu;
  QMenu   settMenu;
  QMenu   preMenu;
  
  QAction * userQuit;
  QAction * userNevermind;
  QAction * userOpen;
  QAction * userFrame;
  QAction * userSettings;
  QAction * userHelp;
  
  QAction * settReload;
  QAction * settNevermind;

  QApplication  * pApp;
  
  QString currentUrl;
  QUrl    effectiveUrl;
  Qt::WindowFlags  defaultWinFlags;
  bool showFrame;
  
  QTimer   reloadTimer;
  int      reloadSecs;
  bool     reloadOn;
  
  QShortcut  *controlL;
  QShortcut  *controlO;
  QShortcut  *controlM;
  QShortcut  *escapeKey;
  QShortcut  *controlR;
  QShortcut  *controlQ;
  QShortcut  *controlF;
  QShortcut  *controlH;
  QShortcut  *controlB;
  QShortcut  *controlW;
  QShortcut  *controlS;

};

} // namespace

#endif


