XUPProjectSettings {
	EXECUTE_RELEASE	= miniweb
	EXECUTE_DEBUG	= miniwebd
}

# //
# //  Copyright (C) 2009 - Bernd H Stramm
# //
# // This program is distributed under the terms of
# // the GNU General Public License version 3
# //
# // This software is distributed in the hope that it will be useful,
# // but WITHOUT ANY WARRANTY; without even the implied warranty
# // of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# //

CONFIG	+= qt app debug_and_release


QT	+= core gui xml network webkit

RESOURCES	+= miniweb.qrc

FORMS	+= ui/webbox.ui \

MAKEFILE = MakeMini
	

TRANSLATIONS	= 

CONFIG(release, debug|release) {
	DEFINES	+= QT_NO_DEBUG
	DEFINES	+= QT_NO_DEBUG_OUTPUT
	DEFINES	+= MINIWEB_DEBUG=0
	QMAKE_CXXFLAGS_RELEASE	-= -g
	TARGET	= miniweb
}

CONFIG(debug, debug|release) {
	DEFINES	+= MINIWEB_DEBUG=1
	TARGET	= miniwebd
}


SOURCES	=  \
	src/cmdoptions.cpp \
	src/minimain.cpp \
	src/miniwebconfig.cpp \
	src/minipage.cpp \
	src/webbox.cpp \
	src/version.cpp \
	src/ualist.cpp \
	src/useragent.cpp \
	src/useragent_ff.cpp \
	src/agentmenu.cpp \
	src/newagent.cpp \
	src/minidownload.cpp \
	src/miniwebdebug.cpp


HEADERS	=  \
	src/cmdoptions.h \
	src/miniwebconfig.h \
	src/minipage.h \
	src/webbox.h \
	src/version.h \
	src/ualist.h \
	src/useragent.h \
	src/useragent_ff.h \
	src/agentmenu.h \
	src/newagent.h \
	src/minidownload.h \
	src/miniwebdebug.h


