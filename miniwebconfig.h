#ifndef MINIWEBCONFIG_H
#define MINIWEBCONFIG_H
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
#include <QDomElement>


namespace miniweb {


class MiniwebConfig {

public:

   MiniwebConfig ();
   MiniwebConfig (const MiniwebConfig & cfg);
   
   MiniwebConfig & operator = (const MiniwebConfig & cfg);
   
   void SetDefault();
   void Read ();
   void Write ();
   
   QString FeedListFile() { return feedListFile; }
   QString ConfigFile()   { return configFile; }
   bool    Analog () { return analog; }
   bool    Changed () { return changed; }
   bool    SaveOnExit () { return saveonexit; }
   int     StoryTextSize () { return storytextsize; }
   
 
   void SetFeedListFile (QString f) { feedListFile = f;}
   void SetConfigFile   (QString cf) { configFile = cf; }
   void SetAnalog  (const bool show) { analog = show; }
   void SetChanged (const bool c)    { changed = c; }
   void SetSaveOnExit (const bool soe) { saveonexit = soe; }
   void SetStoryTextSize (const int sz) { storytextsize = sz; }
   
   static int maxTextFactor;
   static int minTextFactor;


private:

   QString feedListFile;
   QString configFile;
   bool    analog;
   bool    changed;
   bool    saveonexit;
   bool    running;
   int     storytextsize;
   
   static QString filetag;
   static QString doctypetag;
   static QString useragent;
   static QString screenwidth;
   static QString screenheight;
   static QString soetag;
   static QString ststag;
   static QString boolattr;
   
   
   bool BoolOption (const QDomElement & el, const QString & attr);
 
};

}


#endif
