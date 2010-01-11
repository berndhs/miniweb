#ifndef AGENTMENU_H
#define AGENTMENU_H

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

#include <QSize>
#include <QPoint>
#include <QObject>
#include <QListWidget>
#include <QListWidgetItem>
#include <QShortcut>
#include <map>

#include "ualist.h"


namespace miniweb {

class AgentMenu : public QWidget {

Q_OBJECT

public:

  AgentMenu (QWidget * parent = 0);
  
  void Init (QListWidget * widget, UAList * ual);
  void Start (const QSize sz, const QPoint where, UserAgent & curAgent);
  void Hide ();
  
public slots:
 
  void ItemPicked (QListWidgetItem * item);
  void NothingPicked ();
  
signals:

  void UserAgentChange (const UserAgent newAgt);

private:

  void FillWidget (UserAgent & cur);

  typedef std::map<QListWidgetItem *, QString>   UAIndexType;
  
  UAIndexType uaIndex;
  
  QListWidget * listWidget;
  UAList      * agents;
  QShortcut   * escapeKey;
    
  QSize     mySize;
  QPoint    myTopLeft;

};

}

#endif

