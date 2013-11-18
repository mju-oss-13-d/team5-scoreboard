# Process this file with automake to produce Makefile.in.
# Makefile.am for scoreboard/src.
#
# Copyright 2012 Daniel Jun (unipro.kr@gmail.com)
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

bin_PROGRAMS = scoreboard
scoreboard_SOURCES = \
	main.cpp boardframe.cpp lcdwindow.cpp statictitle.cpp \
	ctrlpanel.cpp gamepanel.cpp teampanel.cpp config.cpp confdlg.cpp
noinst_HEADERS = resource.h common.hpp \
	main.hpp boardframe.hpp lcdwindow.hpp statictitle.hpp \
	ctrlpanel.hpp gamepanel.hpp teampanel.hpp config.hpp confdlg.hpp
EXTRA_DIST = scoreboard.xpm scoreboard.ico
scoreboard_CPPFLAGS = @CPPFLAGS@
scoreboard_CXXFLAGS = @CXXFLAGS@
scoreboard_LDFLAGS = @LDFLAGS@
scoreboard_LDADD = @LIBS@

if HAVE_WINDRES
scoreboard_SOURCES += scoreboard.rc
WINDRES = `wx-config --rescomp`
.rc.o:
	$(WINDRES) -i $< -o $@
else
EXTRA_DIST += scoreboard.rc
endif
