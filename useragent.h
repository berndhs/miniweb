#ifndef USERAGENT_H
#define USERAGENT_H

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
#include <QDomDocument>
#include <QDomElement>

namespace miniweb {

class UserAgent {

public:

  UserAgent ();
  UserAgent (const UserAgent & ag);
  
  QString ID () const { return id; }
  QString UAString () const { return uaString; }
  int     Wide () { return wide; }
  int     High () { return high; }
  
  void SetID (const QString i) { id = i; }
  void SetUAString (const QString ua) { uaString = ua; }
  void SetWide (const int w) { wide = w; }
  void SetHigh (const int h) { high = h; }
  
  void Domify (QDomDocument & doc, QDomElement & el); 
  bool ParseDom (QDomElement & el);
  
private:

  QString id;
  QString uaString;
  int     wide;
  int     high;
  
};

}



#endif
