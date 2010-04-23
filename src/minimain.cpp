
//  Copyright (C) 2010 - Bernd H Stramm 
//
// This program is distributed under the terms of 
// the GNU General Public License version 3 
//
// This software is distributed in the hope that it will be useful, 
// but WITHOUT ANY WARRANTY; without even the implied warranty 
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
//

#include <stdlib.h>
#include "cmdoptions.h"
#include "miniwebconfig.h"
#include "miniwebdebug.h"
#include "version.h"
#include "webbox.h"
#include "ualist.h"
#include <QApplication>



using namespace miniweb;

void
SetOptions (QApplication &app, CmdOptions & opts)
{
  opts.AddStringOption ("config", "c", app.tr("configuration file"));
  opts.AddStringOption ("website", "w", app.tr("web page"));
  opts.AddStringOption ("useragent","u", app.tr("User Agent string"));
}

bool
FindPageOption (CmdOptions & opts, QString & page)
{
  bool changed = opts.SetStringOpt ("website",page);
  QStringList args = opts.Arguments();
  if (args.isEmpty()) {
    return changed;
  }
  page = args.first ();
  return true;
}

int
main (int argc, char*argv[])
{

  QApplication App (argc, argv);
  
  UseMyOwnMsgHandler();
  
  miniweb::CmdOptions options ("MiniWeb");
  SetOptions (App,options);
  
  bool optsOk = options.Parse (argc, argv);
  if (!optsOk) {
    options.Usage ();
    exit (1);
  }
  
  if (options.WantHelp()) {
    options.Usage ();
    exit (0);
  }
  
  if (options.WantVersion ()) {
    CLIVersion ();
    exit (0);
  }
  
  WebBox web;
  web.SetApp (&App);
  web.show();
  QString page ("about:blank");
  FindPageOption (options, page);
  
  QString agentname ("Max");
  options.SetStringOpt ("useragent", agentname);
  
  miniweb::MiniwebConfig  cfg;
  miniweb::UAList         agents;
  
  bool loaded = agents.Load (cfg.UserAgentFile());
  if (!loaded) {
    agents.Load (QString(":/agentfile.xml"));
  }
  UserAgent * ag (0);
  ag = agents.FindAgent (agentname);
  if (ag == 0) {
   qFatal ("no user agent");
  }
  web.SetAgent (*ag);
  web.SetUAList (&agents);
  web.SetPage (page);
  
  App.exec ();
 
  agents.Save (cfg.UserAgentFile());
  cfg.Write (); 

}
