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
#include <QString>

namespace miniweb {

class MiniPage : public QWebPage {

public:

   MiniPage ();
   
   QString userAgentForUrl ( const QUrl & url ) const;

};

}


#endif
