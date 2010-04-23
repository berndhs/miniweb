#ifndef MINIPAGE_H
#define MINIPAGE_H

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

#include <QWebPage>
#include <QWidget>
#include <QString>
#include <QNetworkRequest>
#include <QUrl>
#include <QLabel>
#include <QLineEdit>
#include "miniwebdebug.h"
#include "minidownload.h"
#include <set>

namespace miniweb {

class WebBox;

class MiniPage : public QWebPage {

Q_OBJECT 

public:

   MiniPage (QWidget * parent);
   
   QString userAgentForUrl ( const QUrl & url ) const;
   
   void SetUAString (const QString uas);
   void ToggleScroll ();

public slots:

   void DownloadRequested (const QNetworkRequest & req);
   void HandleLinkClick (const QUrl & url);
   void CleanupDownload (const MiniDownload * dl, const bool ok);
   void HoverLink (const QString & link, const QString & title, const QString & text);
   
   void CatchShowLink (const QPoint here, const QString link, QWidget * pW);
   
signals:

   void ShowLink (const QPoint here, const QString link, QWidget * pW);
   
private:

   void SetScroll ();
   void AskDownload (const QUrl & url, QString & destFile, bool & doLoad);
   bool IsDownloadable (const QString & name);
   void StartDownload (const QNetworkRequest & req, const QString & filename);

   QString agentString;
   bool    haveScrollbar;
   
   typedef std::set <MiniDownload *> DownloadSetType;
   
   DownloadSetType    downloadSet;
   
   QWidget  *pParent;
   WebBox   *boxParent;
   
   QLineEdit *linkTip;

};

}


#endif
