

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
#include "minidownload.h"
#include <QFile>

namespace miniweb {

void
MiniDownload::Finished ()
{
  disconnect (reply, 0, this, 0);
  QFile target (targetFile);
  bool ok = target.open (QFile::WriteOnly);
  if (ok) {
    QByteArray byteBuf;
    int inChunk  (0);
    int outChunk (0);
    qint64 blockSize (128*1024);
    do {
      byteBuf = reply->read (blockSize);
      inChunk = byteBuf.size();
      if (inChunk > 0) {
        outChunk = target.write (byteBuf);
        ok &= inChunk == outChunk;
      }
    } while (inChunk > 0 && outChunk > 0 && ok);
  }
  target.close();
  reply->close();
  emit DownloadFinished (this, ok);
}


} // namespace

