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

WebBox::WebBox (QApplication * app)
{
  showFrame = true;
  pApp = app;
  defaultWinFlags = this->windowFlags();
  
  setupUi (this);
  webView->setPage (&thePage) ;
  
  InitUserMenu ();
  
  connect (theButton, SIGNAL (clicked()), this, SLOT (UserWantsSomething()));
  
  DisableNewUrl ();
  
}

WebBox::WebBox ()
{}

WebBox::~WebBox ()
{}

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
WebBox::DisableNewUrl ()
{
  newUrl->hide ();
  disconnect (textOK, 0, 0, 0);
  disconnect (textCancel, 0, 0, 0);
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
  currentUrl = url;
  QUrl pageUrl (url);
  webView->load (pageUrl);
}

void
WebBox::EnableNewUrl ()
{
  newUrl->show ();
  connect (textCancel, SIGNAL (clicked()), this, SLOT (NewUrlCancel ()) );
  connect (textOK, SIGNAL (clicked()), this, SLOT (NewUrlOk ()));
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
