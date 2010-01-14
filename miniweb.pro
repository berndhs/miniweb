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

FORMS	+= webbox.ui \
	

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
	cmdoptions.cpp \
	minimain.cpp \
	miniwebconfig.cpp \
	minipage.cpp \
	webbox.cpp \
	version.cpp \
	ualist.cpp \
	useragent.cpp \
	useragent_ff.cpp \
	agentmenu.cpp \
	newagent.cpp \
	minidownload.cpp \
	miniwebdebug.cpp


HEADERS	=  \
	cmdoptions.h \
	miniwebconfig.h \
	minipage.h \
	webbox.h \
	version.h \
	ualist.h \
	useragent.h \
	useragent_ff.h \
	agentmenu.h \
	newagent.h \
	minidownload.h \
	miniwebdebug.h


