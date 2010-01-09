#include "webbox.h"


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
  pApp = app;
  
  setupUi (this);
  webView->setPage (&thePage) ;
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
WebBox::SetPage (QString url)
{
  QUrl pageUrl (url);
  webView->load (pageUrl);
}

}
