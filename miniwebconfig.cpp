#include "miniwebconfig.h"
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
#include <QFile>
#include <QDomElement>
#include <QDesktopServices>

namespace miniweb {

QString MiniwebConfig::doctypetag("miniwebcfg");
QString MiniwebConfig::filetag   ("feedfile");
QString MiniwebConfig::useragent ("useragent");
QString MiniwebConfig::screenwidth ("wide");
QString MiniwebConfig::screenheight ("high");
QString MiniwebConfig::soetag   ("saveonexit");
QString MiniwebConfig::ststag   ("storytextsize");
QString MiniwebConfig::boolattr ("yesorno");
int     MiniwebConfig::maxTextFactor (10000);
int     MiniwebConfig::minTextFactor (10);

MiniwebConfig::MiniwebConfig()
{
  SetDefault();
}

MiniwebConfig::MiniwebConfig (const MiniwebConfig &cfg)
:feedListFile(cfg.feedListFile),
 configFile(cfg.configFile),
 saveonexit(cfg.saveonexit),
 running(false),
 storytextsize(cfg.storytextsize)
{
  changed = true;
}

MiniwebConfig &
MiniwebConfig::operator= (const MiniwebConfig & cfg)
{
  feedListFile = cfg.feedListFile;
  configFile = cfg.configFile;
  analog = cfg.analog;
  saveonexit = cfg.saveonexit;
  running = false;
  storytextsize = cfg.storytextsize;
  changed = true;
  return *this;
}

void
MiniwebConfig::SetDefault ()
{
  QString homedir = QDesktopServices::storageLocation(QDesktopServices::HomeLocation);
  feedListFile = homedir + "/.miniweb_marks.xml";
  configFile = homedir + "/.miniweb_cfg.xml";
  analog = true;
  saveonexit = true;
  storytextsize = 85;
  changed = false;
}

void
MiniwebConfig::Read ()
{
  QFile cfgfile(ConfigFile());
  cfgfile.open(QFile::ReadOnly);
  QDomDocument dom;
  dom.setContent (&cfgfile);
  cfgfile.close();
  
  QDomElement doc = dom.documentElement();
  if (doc.tagName() != doctypetag) {
    return;
  }
  for (QDomElement el = doc.firstChildElement();
       !el.isNull();
       el = el.nextSiblingElement()) {
    if (el.tagName() == filetag) {
      if (el.hasAttribute("name")) {
        SetFeedListFile(el.attribute("name"));
      }
    } else if (el.tagName () == soetag) {
      SetSaveOnExit (BoolOption(el,boolattr));
    } else if (el.tagName () == ststag) {
      int sz = el.attribute("percent").toInt();
      if (sz < minTextFactor) { sz = minTextFactor; }
      if (sz > maxTextFactor) { sz = maxTextFactor; }
      SetStoryTextSize (sz);
    }
  }
}

bool
MiniwebConfig::BoolOption (const QDomElement & el,  
                        const QString     & attr)
{
  QString yesorno = el.attribute(attr).toLower();
  QString yes = QString("yes").toLower();
  bool y = (yesorno == yes);
  return y;
}

void
MiniwebConfig::Write ()
{
  QFile cfgfile(ConfigFile());
  cfgfile.open(QFile::WriteOnly);
  QDomDocument dom;
  QString emptyDoc ("<?xml version=\"1.0\" encoding=\"utf-8\"?>");
  emptyDoc.append ("\n");
  emptyDoc.append ("<" + doctypetag + " version=\"1.0\">\n");
  emptyDoc.append ("</" + doctypetag + ">\n");
  dom.setContent (emptyDoc);
  QDomElement root = dom.documentElement();
  QDomElement el;
  
  el = dom.createElement (filetag);
  el.setAttribute ("name", FeedListFile());
  root.appendChild (el);
  
  QString yesorno;
  
  el.setAttribute (boolattr, yesorno);
  root.appendChild (el);
  
  el = dom.createElement (soetag);
  yesorno = SaveOnExit() ? "yes" : "no";
  el.setAttribute (boolattr, yesorno);
  root.appendChild (el);
  
  el = dom.createElement (ststag);
  int sz = StoryTextSize();
  el.setAttribute("percent",QString::number(sz));
  root.appendChild (el);
  
  QByteArray bytes;
  bytes = dom.toByteArray();
  cfgfile.write(bytes);
  cfgfile.close();
}

}
