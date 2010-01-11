
#include "newagent.h"
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

#include "webbox.h"
#include <QDateTime>
#include "miniwebdebug.h"

namespace miniweb {

NewAgent::NewAgent (QWidget * parent) 
:uaList (0)
{
  QWidget::setParent (parent);
  webBox = dynamic_cast<WebBox*> (parent);
  hide ();
  controlD = new QShortcut ( QKeySequence (tr("Ctrl+D")), this);
  controlA = new QShortcut ( QKeySequence (tr("Ctrl+A")), this);
  escapeKey = new QShortcut ( QKeySequence (Qt::Key_Escape), this);
}

void
NewAgent::Init (UAList * ual)
{
  uaList = ual;
}

void
NewAgent::ConnectButtons ()
{
  if (webBox) { 
    connect (webBox->newCancel, SIGNAL ( clicked ()),
             this, SLOT ( DoCancel ()));
    connect (webBox->newSave, SIGNAL ( clicked ()),
             this, SLOT ( DoSave ()));
    connect (webBox->newDelete, SIGNAL ( clicked ()),
             this, SLOT ( DoDelete ()));
    connect (controlD, SIGNAL ( activated ()), 
             this, SLOT ( DoDelete()));
    connect (controlA, SIGNAL ( activated ()),
             this, SLOT ( DoSave ()));
    connect (escapeKey, SIGNAL ( activated ()),
             this, SLOT ( DoCancel ()));
  }
}

void
NewAgent::DisconnectButtons ()
{
  if (webBox) { 
    disconnect (webBox->newCancel, SIGNAL ( clicked ()),
             this, SLOT ( DoCancel ()));
    disconnect (webBox->newSave, SIGNAL ( clicked ()),
             this, SLOT ( DoSave ()));
    disconnect (webBox->newDelete, SIGNAL ( clicked ()),
             this, SLOT ( DoDelete ()));
    disconnect (controlD, SIGNAL ( activated ()), 
             this, SLOT ( DoDelete()));
    disconnect (controlA, SIGNAL ( activated ()),
             this, SLOT ( DoSave ()));
    disconnect (escapeKey, SIGNAL ( activated ()),
             this, SLOT ( DoCancel ()));
  }
}

void
NewAgent::OpenWin (QString title)
{
  if (webBox) {
    webBox->SetPage ("about:blank");
    webBox->newTitle->setText (title);
  }
  ConnectButtons ();
  show ();
}

void
NewAgent::CloseWin ()
{
  if (webBox) {
    webBox->Back ();
  }
  DisconnectButtons ();
  hide ();
}

void
NewAgent::EditNew ()
{
  QDateTime now (QDateTime::currentDateTime());
  QString newName (tr("Agent"));
  uint nowSecs = now.toTime_t ();
  newName.append (QString::number(nowSecs));
  EditAgent (newName, true);
}

void
NewAgent::EditAgent (QString name, bool isnew)
{
  if (uaList == 0 || webBox == 0) {
    return;
  }
  QString title (tr("Edit Agent"));
  UserAgent * ag;
  ag = uaList->FindAgent (name);
  if (isnew || ag == 0) {
    ag = new UserAgent;
    if (ag == 0) {
      return;
    }
    ag->SetID (name);
    title = tr("New Agent");
  }
  newAgent = ag;
  webBox->newName->setText (ag->ID());
  webBox->newUAString->setPlainText (ag->UAString());
  webBox->newHeight->setText (QString::number(ag->High()));
  webBox->newWidth->setText (QString::number(ag->Wide()));
  OpenWin (title);
}

void 
NewAgent::DoCancel ()
{
  CloseWin ();
}

void
NewAgent::DoSave ()
{
  if (uaList && webBox) {
    if (newAgent) {
      newAgent->SetID (webBox->newName->text());
      newAgent->SetUAString (webBox->newUAString->toPlainText());
      newAgent->SetHigh (webBox->newHeight->text().toInt());
      newAgent->SetWide (webBox->newWidth->text().toInt());
      uaList->AddAgent (newAgent);
      newAgent = 0;
    }
  }
  CloseWin ();
}

void
NewAgent::DoDelete ()
{
  if (uaList && webBox) {
    QString name = webBox->newName->text();
    uaList->EraseAgent (name);
  }
  CloseWin ();
}

} // namespace

