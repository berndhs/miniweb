#include "useragent.h"

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
#include "useragent_ff.h"
#include "miniwebdebug.h"

namespace miniweb {


UserAgent::UserAgent ()
:wide(0),
 high(0)
 {
 }
 
UserAgent::UserAgent (const UserAgent & ag)
:id (ag.id),
 uaString (ag.uaString),
 wide (ag.wide),
 high (ag.high)
{
}

void
UserAgent::Domify (QDomDocument & doc, QDomElement &el )
{
  QDomElement agentel;
  QDomElement newel;
  agentel = doc.createElement (UA_FF::tag_Agent);
  agentel.setAttribute (UA_FF::attr_Name, ID());
  
  newel = doc.createElement (UA_FF::tag_UAString);
  QDomText txt = doc.createTextNode (UAString());
  newel.appendChild (txt);
  agentel.appendChild (newel);
  
  newel = doc.createElement (UA_FF::tag_Size);
  newel.setAttribute (UA_FF::attr_Wide, QString::number (Wide()));
  newel.setAttribute (UA_FF::attr_High, QString::number (High()));
  agentel.appendChild (newel);

  el.appendChild (agentel);
}

bool
UserAgent::ParseDom (QDomElement & el)
{
  QString tag = el.tagName();
  if (tag != UA_FF::tag_Agent) {
    return false;
  }
  QString str = el.attribute (UA_FF::attr_Name);
  if (str.length() < 1) {
    return false;
  }
  SetID (str);
  QDomElement nextel;
  bool haveString (false);
  bool haveSize (false);
  for (nextel = el.firstChildElement ();
       !nextel.isNull();
       nextel = nextel.nextSiblingElement ()) {
    tag = nextel.tagName ();
    if (tag == UA_FF::tag_UAString) {
      str = nextel.text();
      SetUAString (str);
      haveString = true;
    } else if (tag == UA_FF::tag_Size) {
      str = nextel.attribute (UA_FF::attr_Wide);
      int w = str.toLong();
      SetWide (w);
      str = nextel.attribute (UA_FF::attr_High);
      int h = str.toLong ();
      SetHigh (h);
      haveSize = true;
    }
  }
  return haveSize && haveString;
}

UserAgent*
UserAgent::NewDefaultAgent ()
{
  UserAgent * tmp = new UserAgent;
  tmp->SetID ("Max");
  tmp->SetUAString ("Maxwell Smart");
  tmp->SetWide (800);
  tmp->SetHigh (600);
  return tmp;
}

} // namespace
