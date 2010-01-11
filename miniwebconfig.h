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
   
   QString ConfigFile()   { return configFile; }
   QString UserAgentFile() { return userAgentFile; }
   bool    Changed () { return changed; }
   bool    SaveOnExit () { return saveonexit; }
   int     StoryTextSize () { return storytextsize; }
   
   void SetConfigFile   (QString cf) { configFile = cf; }
   void SetUserAgentFile (QString uaf) { userAgentFile = uaf; }
   void SetChanged (const bool c)    { changed = c; }
   void SetSaveOnExit (const bool soe) { saveonexit = soe; }
   void SetStoryTextSize (const int sz) { storytextsize = sz; }
   
   static int maxTextFactor;
   static int minTextFactor;


private:

   QString configFile;
   QString userAgentFile;
   bool    changed;
   bool    saveonexit;
   bool    running;
   int     storytextsize;
   
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
