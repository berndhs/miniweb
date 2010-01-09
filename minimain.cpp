
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
#include <QApplication>

using namespace miniweb;

void
SetOptions (QApplication &app, CmdOptions & opts)
{
  opts.AddStringOption ("config", "c", app.tr("configuration file"));
  opts.AddStringOption ("website", "w", app.tr("web page"));
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
  QString page ("http://google.com");
  options.SetStringOpt ("website",page);
  web.SetPage (page);
  
  App.exec ();
  

}
