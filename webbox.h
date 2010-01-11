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
#include "ualist.h"
#include "agentmenu.h"


namespace miniweb {


class WebBox : public QWidget, public Ui_WebBox {

Q_OBJECT

public:

  WebBox ();
  
  void SetApp (QApplication * papp) { pApp = papp;}
  void SetUAList (UAList * ul);
  
  void SetPage (QString url);
  void Back ();
  void Blank ();
  
  void Resize (const int wid, const int hi);
  
  void SetFrame (const bool frame);
  
  UAList * UserAgentList () { return uaList; }
  
public slots:


  void SetAgent (const UserAgent &ag, const bool setsize = true);
  
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
  void SwitchSides ();
  void License ();
  
  void EditReload ();
  
  void MakeShortcuts ();
  
  
  MiniPage * thePage;
  
  UAList        * uaList;
  
  UserAgent        curAgent ;
  QSize            curSize;
  
  QMenu   userMenu;
  QMenu   settMenu;
  
  QAction * userQuit;
  QAction * userNevermind;
  QAction * userOpen;
  QAction * userSettings;
  QAction * userHelp;
  QAction * userLicense;
  QAction * userVersion;
  
  QAction * settReload;
  QAction * settNevermind;
  QAction * settUserAgent;
  QAction * settSwitchPortrait;
  QAction * settScrollbar;
  QAction * settFrame;

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


