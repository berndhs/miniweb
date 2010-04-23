#ifndef USERAGENT_FF_H
#define USERAGENT_FF_H

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

namespace miniweb {

class UA_FF {

public:

 static QString tag_File; 
 static QString tag_Agent; 
 static QString tag_UAString;
 static QString tag_Size; 
 
 static QString attr_Name;
 static QString attr_Wide;
 static QString attr_High;
 
};

} // namespace



#endif

