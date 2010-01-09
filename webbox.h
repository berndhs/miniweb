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
#include "ui_webbox.h"
#include "minipage.h"


namespace miniweb {


class WebBox : public QWidget, public Ui_WebBox {

Q_OBJECT

public:

  WebBox (QApplication *app);
  ~WebBox ();
  
  void SetPage (QString url);
  
public slots:

  void update ();
  void quit   ();
  
private:

  WebBox ();
  
  MiniPage thePage;

  QApplication  * pApp;

};

} // namespace

#endif


