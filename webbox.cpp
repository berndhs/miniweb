#include "webbox.h"
#include "miniwebdebug.h"

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


namespace miniweb {

WebBox::WebBox ()
{
  showFrame = true;
  reloadOn = false;
  reloadSecs = 0;  // 1 day
  pApp = 0;
  uaList = 0;
  defaultWinFlags = this->windowFlags();
  effectiveUrl = QUrl("");
  
  setupUi (this);
  thePage = new MiniPage (this);
  webView->setPage (thePage) ;
  loadingLabel->hide ();
  failedLabel->hide ();
  
  InitUserMenu ();
  InitSettingsMenu ();
  MakeShortcuts ();
  DisableNewUrl ();
  DisableSettings ();
  agentMenu->hide();
  
  reloadTimer.setParent (this);
  reloadTimer.stop ();
  
  connect (theButton, SIGNAL (clicked()), this, SLOT (UserWantsSomething()));
  connect (webView, SIGNAL (loadFinished (bool)),
           this, SLOT (LoadDone (bool)));
  connect (webView, SIGNAL (loadStarted ()), 
           this, SLOT (LoadStarted ()));
  connect (agentMenu, SIGNAL (UserAgentChange (const UserAgent)),
            this, SLOT (SetAgent (const UserAgent)));
  
  
}

void
WebBox::MakeShortcuts ()
{
  controlB = new QShortcut (QKeySequence (tr("Ctrl+B")), this);
  controlF = new QShortcut (QKeySequence (tr("Ctrl+F")), this);
  controlH = new QShortcut (QKeySequence (tr("Ctrl+H")), this);
  controlL = new QShortcut (QKeySequence (tr("Ctrl+L")), this);
  controlO = new QShortcut (QKeySequence (tr("Ctrl+O")), this);
  controlM = new QShortcut (QKeySequence (tr("Ctrl+M")), this);
  controlR = new QShortcut (QKeySequence (tr("Ctrl+R")), this);
  controlQ = new QShortcut (QKeySequence (tr("Ctrl+Q")), this);
  controlW = new QShortcut (QKeySequence (tr("Ctrl+W")), this);
  controlS = new QShortcut (QKeySequence (tr("Ctrl+S")), this);
  escapeKey = new QShortcut (QKeySequence (Qt::Key_Escape), this);
  connect (controlB, SIGNAL (activated()), webView, SLOT (back()));
  connect (controlF, SIGNAL (activated()), webView, SLOT (forward()));
  connect (controlH, SIGNAL (activated()), this, SLOT (Help()));
  connect (controlL, SIGNAL (activated()), this, SLOT (EnableNewUrl()));
  connect (controlO, SIGNAL (activated()), this, SLOT (EnableNewUrl()));
  connect (controlM, SIGNAL (activated()), this, SLOT (UserWantsSomething()));
  connect (controlR, SIGNAL (activated()), webView, SLOT (reload()));
  connect (controlQ, SIGNAL (activated()), this, SLOT (quit()));
  connect (controlW, SIGNAL (activated()), this, SLOT (ToggleFrame()));
  connect (controlS, SIGNAL (activated()), this, SLOT (SettingsMenu()));
}


void
WebBox::SetUAList (UAList * ual)
{
  uaList = ual;
  agentMenu->Init (agentWidget, uaList);
}


void
WebBox::update ()
{
  QWidget::update ();
}

void
WebBox::quit ()
{
  if (pApp) {
    pApp->quit();
  }
}

void
WebBox::Help ()
{
  SetPage ("qrc:/helpman.html");
}

void
WebBox::License ()
{
  SetPage ("qrc:/LICENSE.html");
}

void
WebBox::Resize (const int wid, const int hi)
{
  QSize size (wid,hi);
  this->resize (size);
  webView->resize (size);
}

void
WebBox::Reload () 
{
  webView->reload ();
}

void
WebBox::SetAgent (const UserAgent &ag, const bool setsize)
{
  curAgent = ag;
  if (thePage) {
    thePage->SetUAString (ag.UAString());
  }
  if (setsize) {
    Resize (ag.Wide(),ag.High());
    curSize = QSize (ag.Wide(), ag.High());
  }
}

void
WebBox::LoadDone (bool ok)
{
  loadingLabel->hide();
  if (ok) {
    failedLabel->hide();
    effectiveUrl = webView->url();
  } else {
    failedLabel->show();
  }
}

void
WebBox::LoadStarted ()
{
  failedLabel->hide();
  loadingLabel->show();
}

void
WebBox::DisableNewUrl ()
{
  newUrl->hide ();
  disconnect (textOK, 0, 0, 0);
  disconnect (textCancel, 0, 0, 0);
  disconnect (escapeKey, 0, 0, 0);
  disconnect (textEnter, 0, 0, 0);
}

void
WebBox::DisableSettings ()
{
  settBox->hide ();
  disconnect (settOK, 0, 0, 0);
  disconnect (settCancel, 0, 0, 0);
  disconnect (escapeKey, 0, 0, 0);
  disconnect (settEdit, 0, 0, 0);
}

void
WebBox::SetFrame (const bool frame)
{
  showFrame = frame;
  if (showFrame) {
    setWindowFlags (defaultWinFlags);
    this->show();
  } else {
    Qt::WindowFlags flags = defaultWinFlags;
    flags |= Qt::FramelessWindowHint;
    setWindowFlags (flags);
    this->show();
  }
}

void
WebBox::InitUserMenu ()
{
  userQuit = userMenu.addAction (tr("Quit"));
  userNevermind = userMenu.addAction (tr("Cancel"));
  userOpen = userMenu.addAction (tr("Open..."));
  userSettings = userMenu.addAction (tr("Settings..."));
  userHelp = userMenu.addAction (tr("Help..."));
  userLicense = userMenu.addAction (tr("License..."));
}

void
WebBox::InitSettingsMenu ()
{
  settReload = settMenu.addAction (tr("Reload Timer..."));
  settFrame = settMenu.addAction (tr("Frame On/Off"));
  settSwitchPortrait = settMenu.addAction (tr("Portrait / Landscape"));
  settUserAgent = settMenu.addAction (tr("User Agent..."));
  settNevermind = settMenu.addAction (tr("Cancel"));
}

void
WebBox::SetPage (QString url)
{
  QString newurl (url);
  if (url.length() == 0) {
    return;
  }
  if (url.indexOf(":") < 0) {
    newurl.prepend("http://");
  }
  if (url == "about:blank") {
    newurl = QString("qrc:/blank.html");
  }
  currentUrl = newurl;
  QUrl pageUrl (newurl);
  webView->stop ();
  webView->load (pageUrl);
}

void
WebBox::EnableNewUrl ()
{
  newUrl->show ();
  oldUrl->setPlainText(effectiveUrl.toString());
  textEnter->clear ();
  textEnter->setFocus ();
  connect (textCancel, SIGNAL (clicked()), this, SLOT (NewUrlCancel ()));
  connect (escapeKey, SIGNAL (activated()), this, SLOT (NewUrlCancel ()));
  connect (textOK, SIGNAL (clicked()), this, SLOT (NewUrlOk ()));
  connect (textEnter, SIGNAL (returnPressed()), this, SLOT (NewUrlOk ()));
}

void
WebBox::EditReload ()
{
  settBox->setTitle (tr("Reload Timer (secs)"));
  settEdit->setText (QString::number (reloadSecs) );
  settBox->show();
  connect (settOK, SIGNAL (clicked()), this, SLOT (ReloadSetup()));
  connect (settCancel, SIGNAL (clicked()), this, SLOT (ReloadNochange()));
  connect (settEdit, SIGNAL (returnPressed()), this, SLOT (ReloadSetup()));
  connect (escapeKey, SIGNAL (activated()), this, SLOT (ReloadNochange()));
}

void
WebBox::NewUrlOk ()
{
  QString addr = textEnter->text();
  DisableNewUrl ();
  SetPage (addr);
}

void
WebBox::NewUrlCancel ()
{
  DisableNewUrl ();
}

void
WebBox::ReloadSetup ()
{
  QString userValue = settEdit->text();
  DisableSettings ();
  int userInt = userValue.toLong ();
  if (userInt < 1) {
    reloadTimer.stop();
    disconnect (&reloadTimer, 0, 0, 0);
    reloadSecs = 0;
  } else {
    reloadSecs = userInt;
    connect (&reloadTimer, SIGNAL (timeout()), this, SLOT (Reload()));
    reloadTimer.start (reloadSecs * 1000);
  }
}

void
WebBox::ReloadNochange ()
{
  DisableSettings ();
}

void
WebBox::ToggleFrame ()
{
  SetFrame (!showFrame);
}

void
WebBox::SwitchSides ()
{
  int w = curSize.width();
  int h = curSize.height();
  curSize.setWidth (h);
  curSize.setHeight (w);
  Resize (h,w);
}

void
WebBox::UserWantsSomething ()
{
  QPoint here = theButton->pos();
  QAction * userWants = userMenu.exec(mapToGlobal(here));
  if (userWants == userQuit) {
    quit();
  } else if (userWants == userNevermind) {
    return;
  } else if (userWants == userOpen) {
    EnableNewUrl ();
  } else if (userWants == userSettings) {
    SettingsMenu();
  } else if (userWants == userHelp) {
    Help ();
  } else if (userWants == userLicense) {
    License ();
  }
}

void
WebBox::SettingsMenu ()
{
  QPoint here = theButton->pos();
  QAction * userWants = settMenu.exec (mapToGlobal(here));
  if (userWants == settReload) {
    EditReload ();
  } else if (userWants == settNevermind) {
    return;
  } else if (userWants == settFrame) {
    ToggleFrame ();
  } else if (userWants == settSwitchPortrait) {
    SwitchSides ();
  } else if (userWants == settUserAgent) {
    agentMenu->Start (curSize, theButton->pos(), curAgent);
  }
}

}
