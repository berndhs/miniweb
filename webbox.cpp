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
  pApp = 0;
  defaultWinFlags = this->windowFlags();
  
  setupUi (this);
  thePage = new MiniPage (this);
  webView->setPage (thePage) ;
  loadingLabel->hide ();
  failedLabel->hide ();
  
  InitUserMenu ();
  
  connect (theButton, SIGNAL (clicked()), this, SLOT (UserWantsSomething()));
  connect (webView, SIGNAL (loadFinished (bool)),
           this, SLOT (LoadDone (bool)));
  connect (webView, SIGNAL (loadStarted ()), 
           this, SLOT (LoadStarted ()));
  
  DisableNewUrl ();
  
}
#if 0
WebBox::WebBox ()
{}
#endif
WebBox::~WebBox ()
{
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
WebBox::LoadDone (bool ok)
{
  loadingLabel->hide();
  if (ok) {
    failedLabel->hide();
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
  disconnect (textEnter, 0, 0, 0);
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
  userFrame = userMenu.addAction (tr("Frame On/Off"));
  userNevermind = userMenu.addAction (tr("Cancel"));
  userOpen = userMenu.addAction (tr("Open..."));
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
  connect (textCancel, SIGNAL (clicked()), this, SLOT (NewUrlCancel ()) );
  connect (textOK, SIGNAL (clicked()), this, SLOT (NewUrlOk ()));
  connect (textEnter, SIGNAL (returnPressed()), this, SLOT (NewUrlOk ()));
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
  } else if (userWants == userFrame) {
    SetFrame (!showFrame);
  }
}

}
