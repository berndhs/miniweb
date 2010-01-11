#ifndef UALIST_H
#define UALIST_H
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

#include <QIODevice>
#include <QString>
#include <map>
#include "useragent.h"

namespace miniweb {

class UAList {

public:

  UAList ();
  ~UAList ();
  
  bool AddAgent (const UserAgent ag);
  bool AddAgent (UserAgent * ag);
  
  UserAgent * FindAgent (const QString name);
  UserAgent * First ();
  UserAgent * Next ();
  bool        End ();
  
  void Save (QString filename);
  bool Load (QString filename);
  
  bool Read (QIODevice *dev);
  void Write (QIODevice *dev);
 
private:

  void Domify (QDomDocument & doc);
  bool Parse  (QDomDocument & doc);
  
  void Ditch ();

  typedef std::map <QString, UserAgent *> AgentMapType;
  
  AgentMapType  agents;
  
  AgentMapType::iterator agentIt;

};


}



#endif
