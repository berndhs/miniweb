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

MiniPage::MiniPage ()
{
}

QString
MiniPage::userAgentForUrl (const QUrl & url ) const
{
  return "Opera/8.01 (J2ME/MIDP; Opera Mini/3.0.6306/1528; en; U; ssr)";
}



} // namespace
