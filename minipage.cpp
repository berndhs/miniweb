#include "minipage.h"
#include <QWebFrame>
#include <QWebView>
#include <QFileDialog>
#include <QFileInfo>
#include <QNetworkAccessManager>

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

MiniPage::MiniPage (QObject * parent)
{
  setParent (parent);
  haveScrollbar = false;
  SetScroll ();
  setLinkDelegationPolicy (DelegateExternalLinks);
  connect (this, SIGNAL (linkClicked (const QUrl &)),
           this, SLOT (HandleLinkClick (const QUrl &)));
  connect (this, SIGNAL (downloadRequested (const QNetworkRequest &)),
           this, SLOT (DownloadRequested (const QNetworkRequest &)));
  connect (this, SIGNAL (statusBarMessage (const QString &)),
           this, SLOT (StatusBar (const QString &)));
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
  qDebug () << " download requested";
  qDebug () << " destination url " << req.url().toString ();
  bool loadit(false);
  QString filename;
  AskDownload (req.url(), filename,loadit);
  if (loadit) {
    StartDownload (req,filename);
  }
}

void
MiniPage::StatusBar (const QString & msg)
{
  qDebug () << "status bar message " << msg;
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
    qDebug () << " try to download " << urlStr;
    bool loadit (false);
    QString filename;
    AskDownload (url, filename, loadit);
    if (loadit) {
      StartDownload (QNetworkRequest(url), filename);
    }
  } else {
    qDebug () << " try to load as page " << urlStr;
    QWebView * pView = dynamic_cast <QWebView*> (this->view());
    if (pView) {
      pView->load (url);
    } else {
      qDebug () << " no WebView pointer";
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
  qDebug () << " they want to put it in " << file;
  filename = file;
  doit = file.length() > 0;
}

void
MiniPage::StartDownload (const QNetworkRequest & req, const QString & filename)
{
  QNetworkAccessManager * mgr = this->networkAccessManager ();
  if (mgr == 0) {
  qDebug () << " no manager ! " ;
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
  if (ok) {
    qDebug () << " download worked for file " << myDl->Target();
  } else {
    qDebug () << " download failed for " << myDl->Target();
  }
  disconnect (dl, 0, this, 0);
  downloadSet.erase (myDl);
}


} // namespace
