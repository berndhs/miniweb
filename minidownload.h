#ifndef MINIDOWNLOAD_H
#define MINIDOWNLOAD_H

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

#include <QString>
#include <QNetworkReply>

namespace miniweb {

class MiniDownload : public QObject {

Q_OBJECT

public:

  MiniDownload ():reply(0) {}
  MiniDownload (QNetworkReply * rpl, const QString & tgt)
          :reply (rpl),targetFile(tgt) {}
  
  QString Target () { return targetFile; }
  QNetworkReply * Reply () { return reply; }
  
  void SetTarget (const QString & tgt) { targetFile = tgt; }
  void SetReply  (QNetworkReply * rpl) { reply = rpl; }
  
public slots:

  void Finished ();
  
signals:
 
  void DownloadFinished (const MiniDownload * dl, const bool ok);

private:

  QNetworkReply  * reply;
  QString          targetFile;
  
};

}


#endif
