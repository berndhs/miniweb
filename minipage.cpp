#include "minipage.h"

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



} // namespace
