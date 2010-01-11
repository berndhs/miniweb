
#include "agentmenu.h"

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
#include "miniwebdebug.h"

namespace miniweb {

AgentMenu::AgentMenu (QWidget * parent)
:listWidget(0),
 agents (0),
 escapeKey (0),
 mySize (QSize(0,0)),
 myTopLeft (QPoint(0,0))
{
  QWidget::setParent (parent);
  uaIndex.clear();
  hide ();
}

void
AgentMenu::Init (QListWidget * widget, UAList * ual)
{
  listWidget = widget;
  agents = ual;
  if (listWidget) {
    connect (listWidget, SIGNAL (itemActivated (QListWidgetItem*)),
             this, SLOT (ItemPicked (QListWidgetItem*)));
    escapeKey = new QShortcut (QKeySequence (Qt::Key_Escape), this);
  }
  hide ();
}

void
AgentMenu::Start (const QSize sz, const QPoint where, UserAgent & curAgent)
{
   if (listWidget == 0) {
     return;
   }
   FillWidget (curAgent);
   this->setGeometry (QRect (where, sz));
   int listShorter = 20;
   QPoint listTop (where.x(), where.y() + listShorter);
   QSize  listSize (sz.width(), sz.height() - listShorter);
   listWidget->setGeometry (QRect (listTop, listSize));
   myTopLeft = where;
   mySize = sz;
   connect (escapeKey , SIGNAL (activated()),
            this, SLOT (NothingPicked()));
   show ();
}

void
AgentMenu::FillWidget (UserAgent & cur)
{
  if (listWidget == 0 || agents == 0) {
    return;
  }
  QString name;
  QListWidgetItem * item;
  QString curKey = cur.ID();
  QListWidgetItem * curItem(0);
  int row(0);
  listWidget->clear();
  uaIndex.clear();
  UserAgent * ag (0);
  listWidget->addItem (QString(tr("No Change")));
  for (ag = agents->First(), row=1; !agents->End(); ag = agents->Next(), row++) {
    if (ag == 0) {
      break;
    }
    QString key = ag->ID();
    listWidget->addItem (key);
    item = listWidget->item(row);
    uaIndex [item] = key;
    if (key == curKey) {
      curItem = item;
    }
  }
  if (curItem) {
    listWidget->setCurrentItem (curItem,QItemSelectionModel::Select);
  }
  listWidget->setFocus();
}

void
AgentMenu::ItemPicked (QListWidgetItem * item)
{
  hide ();
  if (escapeKey) {
    disconnect (escapeKey, 0, 0, 0);
  }
  if (listWidget == 0 || agents == 0) {
    return;
  }
  if (item) {
    if (uaIndex.count(item) > 0) {
      QString key = uaIndex[item];
      UserAgent * agt = agents->FindAgent (key);
      if (agt) {
        emit UserAgentChange (*agt);
      }
    }
  }
}

void
AgentMenu::NothingPicked ()
{
  ItemPicked (0);
}

} // namespace

