#include "minipage.h"
#include "webbox.h"
#include <QWebFrame>
#include <QWebView>
#include <QFileDialog>
#include <QFileInfo>
#include <QNetworkAccessManager>
#include <QCursor>

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


MiniPage::MiniPage (QWidget * parent)
{
  setParent (parent);
  pParent = parent;
  boxParent = dynamic_cast<WebBox*>(parent);
  haveScrollbar = false;
  SetScroll ();
  linkTip = 0;
  setLinkDelegationPolicy (DelegateExternalLinks);
  connect (this, SIGNAL (linkClicked (const QUrl &)),
           this, SLOT (HandleLinkClick (const QUrl &)));
  connect (this, SIGNAL (downloadRequested (const QNetworkRequest &)),
           this, SLOT (DownloadRequested (const QNetworkRequest &)));
  connect (this, SIGNAL (linkHovered (const QString &, const QString &, const QString &)),
           this, SLOT (HoverLink (const QString &, const QString &, const QString &)));
  connect (this, SIGNAL (ShowLink (const QPoint, const QString, QWidget *)),
           this, SLOT (CatchShowLink (const QPoint, const QString, QWidget *)));
}

QString
MiniPage::userAgentForUrl (const QUrl & url ) const
{
  if (agentString.length() > 1) {
    return agentString;
  } else {
    return QWebPage::userAgentForUrl (url);
  }
}

void
MiniPage::SetUAString (const QString uas)
{
  agentString = uas;
}

void
MiniPage::ToggleScroll ()
{
  haveScrollbar = !haveScrollbar;
  SetScroll ();
}

void
MiniPage::SetScroll ()
{
  Qt::ScrollBarPolicy scroll;
  if (haveScrollbar) {
    scroll = Qt::ScrollBarAlwaysOn;
  } else {  
    scroll = Qt::ScrollBarAlwaysOff;
  }
  mainFrame()->setScrollBarPolicy (Qt::Vertical, scroll);
}

void
MiniPage::DownloadRequested (const QNetworkRequest & req)
{
  bool loadit(false);
  QString filename;
  AskDownload (req.url(), filename,loadit);
  if (loadit) {
    StartDownload (req,filename);
  }
}


bool MiniPage::IsDownloadable (const QString & name)
{
   return (
            name.endsWith (".gz", Qt::CaseInsensitive)
         || name.endsWith (".tgz", Qt::CaseInsensitive)
         || name.endsWith (".zip", Qt::CaseInsensitive)
         || name.endsWith (".exe", Qt::CaseInsensitive)
         );
}

void 
MiniPage::HandleLinkClick (const QUrl & url)
{
  QString urlStr = url.toString ();
  if (IsDownloadable(urlStr)) {
    bool loadit (false);
    QString filename;
    AskDownload (url, filename, loadit);
    if (loadit) {
      StartDownload (QNetworkRequest(url), filename);
    }
  } else {
    QWebView * pView = dynamic_cast <QWebView*> (this->view());
    if (pView) {
      pView->load (url);
    }
  }
}

void
MiniPage::AskDownload (const QUrl & url, QString & filename, bool & doit)
{
  QString urlStr = url.toString();
  QFileInfo info(urlStr);
  QString name = info.fileName();
  QString file = QFileDialog::getSaveFileName (this->view(),
                 tr("Save this file? ") + url.toString(),
                 name );
  filename = file;
  doit = file.length() > 0;
}

void
MiniPage::StartDownload (const QNetworkRequest & req, const QString & filename)
{
  QNetworkAccessManager * mgr = this->networkAccessManager ();
  if (mgr == 0) {
    return;
  }
  QNetworkReply * reply = mgr->get (req);
  MiniDownload * dl = new MiniDownload (reply, filename);
  if (dl) {
    downloadSet.insert (dl);
    connect (reply, SIGNAL (finished ()), dl, SLOT (Finished()));
    connect (dl, SIGNAL (DownloadFinished (const MiniDownload *, const bool)),
             this, SLOT (CleanupDownload (const MiniDownload *, const bool)));
  }
}

void
MiniPage::CleanupDownload (const MiniDownload * dl, const bool ok)
{
  MiniDownload *myDl = const_cast<MiniDownload*>(dl);
  disconnect (dl, 0, this, 0);
  downloadSet.erase (myDl);
}

void
MiniPage::CatchShowLink (const QPoint here, const QString link, QWidget * pW)
{
  static bool isOn (false);
  bool empty = (link == "");
  if (!empty && !isOn) {
    QString padlink (link);
    padlink.prepend (' ');
    padlink.append (' ');
    if (linkTip == 0) {
      linkTip = new QLineEdit (padlink,pW);
      linkTip->setReadOnly (true);
      linkTip->setFrame (false);
    } else {
      linkTip->setText (padlink);
    }
    QFontMetrics fm = linkTip->fontMetrics();
    QSize sz = fm.size (0,padlink);
    linkTip->resize (sz);
    QPoint local (pW->mapFromGlobal (here));
    linkTip->move (local);
    linkTip->show ();
    isOn = true;
  } else if (empty && isOn) {
    if (linkTip) {
      linkTip->hide();
    }
    isOn = false;
  }
}

void 
MiniPage::HoverLink (const QString & link, const QString & title, const QString & text)
{
  emit ShowLink (QCursor::pos(), link, pParent);
}

} // namespace
