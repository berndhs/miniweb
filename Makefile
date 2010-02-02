#
# top level makefile for miniweb
#
# //
# //  Copyright (C) 2010 - Bernd H Stramm 
# //
# // This program is distributed under the terms of 
# // the GNU General Public License version 3 
# //
# // This software is distributed in the hope that it will be useful, 
# // but WITHOUT ANY WARRANTY; without even the implied warranty 
# // of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
# //


EXEC = miniweb
MINIWEB_MAKEFILE = Make_Q
DESTDIR=$(HOME)/bin

all:
	sh build.sh
  
clean:
	if [ -e $(MINIWEB_MAKEFILE) ]; then $(MAKE) -i -f $(MINIWEB_MAKEFILE) clean; fi 
	if [ -e $(MINIWEB_MAKEFILE) ]; then $(RM) $(MINIWEB_MAKEFILE)* ; fi 
	$(RM) $(EXEC)
  
install:
	install $(EXEC) $(DESTDIR)

