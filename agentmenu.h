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

class WebBox;

class AgentMenu : public QWidget {

Q_OBJECT

public:

  AgentMenu (QWidget * parent = 0);
  
  void SetUAList (UAList * ual) { agents = ual; }
  
  void Init ();
  void Start (const QSize sz, const QPoint where, UserAgent & curAgent);
  void Hide ();
  
public slots:
 
  void ItemPicked (QListWidgetItem * item);
  void NothingPicked ();
  void DoEditCurrent ();
  void DoEditNew ();
  
signals:

  void UserAgentChange (const UserAgent newAgt);
  void UserAgentNew ();
  void UserAgentEdit (const QString agentName);

private:

  void FillWidget (UserAgent & cur);
  void Connect ();
  void Disconnect ();
  void Close ();
  void Open ();

  typedef std::map<QListWidgetItem *, QString>   UAIndexType;
  
  UAIndexType uaIndex;
  
  QListWidget * listWidget;
  WebBox      * webBox;
  UAList      * agents;
  QShortcut   * escapeKey;
    
  QSize     mySize;
  QPoint    myTopLeft;

};

}

#endif

