#ifndef MINIWEB_VERSION_H
#define MINIWEB_VERSION_H

//
//  Copyright (C) 2009 - Bernd H Stramm 
//
// This program is distributed under the terms of 
// the GNU General Public License version 3 
//
// This software is distributed in the hope that it will be useful, 
// but WITHOUT ANY WARRANTY; without even the implied warranty 
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
//

#include <string>

namespace miniweb {

  std::string MyName();
  std::string Version() ;
  
  void ShowVersionWindow();
  void CLIVersion();

}

#endif
