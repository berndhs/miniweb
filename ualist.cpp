

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

#include "ualist.h"
#include "useragent_ff.h"
#include <QFile>
#include "miniwebdebug.h"

namespace miniweb {

UAList::UAList ()
{}

UAList::~UAList ()
{
  Ditch ();
}


void
UAList::Ditch ()
{
  AgentMapType::iterator it;
  for (it = agents.begin(); it != agents.end(); it++) {
    if (it->second) {
      delete it->second;
    }
  }
  agents.clear();
}


bool
UAList::AddAgent (const UserAgent ag)
{
  QString key = ag.ID();
  if (agents.count(key) != 0) {
    return false;
  }
  UserAgent * newag = new UserAgent (ag);
  agents[key] = newag;
  return true;
}

bool
UAList::AddAgent (UserAgent * ag)
{
  if (ag == 0) {
    return false;
  }
  QString key = ag->ID();
  if (agents.count(key) != 0) {
    return false;
  }
  agents[key] = ag;
  return true;
}

bool
UAList::EraseAgent (const QString name)
{
  if (agents.count(name) == 0) {
    return false;
  }
  agents.erase(name);
  return true;
}

UserAgent *
UAList::FindAgent (QString name)
{
  if (agents.count(name) < 1) {
    return 0;
  }
  return agents[name];
}

void
UAList::Write (QIODevice * dev)
{
  if (dev == 0) {
    return;
  }
  QDomDocument doc;
  Domify (doc);
  QByteArray bytes;
  bytes = doc.toByteArray ();
  dev->write (bytes);
}


bool
UAList::Read (QIODevice * dev)
{
  QDomDocument doc;
  QString errmsg;
  int badline (0);
  bool ok =doc.setContent (dev, &errmsg, &badline);
  if (!ok) {
    return false;
  }
  Ditch (); // forget old content
  return Parse (doc);
}

void
UAList::Domify (QDomDocument & doc)
{
  doc.clear ();
  QString emptyDoc ("<?xml version=\"1.0\" encoding=\"utf-8\"?>");
  emptyDoc.append ("\n");
  emptyDoc.append ("<" + UA_FF::tag_File + " version=\"1.0\">\n");
  emptyDoc.append ("</" + UA_FF::tag_File + ">\n");
  doc.setContent (emptyDoc);
  
  QDomElement root = doc.documentElement ();
  AgentMapType::iterator it;
  for (it = agents.begin(); it != agents.end(); it++) {
    it->second->Domify (doc,root);
  }
  
}

bool
UAList::Parse (QDomDocument & doc)
{
  QDomElement root = doc.documentElement ();
  if (root.tagName() != UA_FF::tag_File) {
    return false;
  }
  QDomElement el;
  bool stillOk (true);
  UserAgent * pAg (0);
  for (el = root.firstChildElement(); 
      !el.isNull();
      el = el.nextSiblingElement()) {
    if (el.tagName() == UA_FF::tag_Agent) {
      pAg = new UserAgent;
      stillOk &= pAg->ParseDom (el);
      if (stillOk) {
        AddAgent (pAg);
      }
    } else {
      stillOk = false;
      break;
    }
  }
  return stillOk;
}

void
UAList::Save (QString filename)
{
  QFile file (filename);
  file.open (QFile::WriteOnly);
  Write (&file);
  file.close();
}

bool
UAList::Load (QString filename)
{
  QFile file (filename);
  bool ok = file.open (QFile::ReadOnly);
  if (ok) {
    ok &= Read (&file);
  }
  return ok;
}

UserAgent *
UAList::First ()
{
  agentIt = agents.begin();
  if (agentIt == agents.end()) {
    return 0;
  }
  return agentIt->second;
}

UserAgent *
UAList::Next ()
{
  agentIt++;
  if (agentIt == agents.end()) {
    return 0;
  }
  return agentIt->second;
}

bool
UAList::End ()
{
  return (agentIt == agents.end());
}

} // namespace
