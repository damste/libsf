# Copyright (C) 2001  MandrakeSoft S.A.
#
#   MandrakeSoft S.A.
#   43, rue d'Aboukir
#   75002 Paris - France
#   http://www.linux-mandrake.com/
#   http://www.mandrakesoft.com/
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA


.SUFFIXES: .cpp


SHELL = /bin/sh



CC = cl
CXX = cl
CFLAGS = /nologo /G6 /MT /W3 /GX- /DNDEBUG /DWIN32 /D_WINDOWS /Ox 
CXXFLAGS = /nologo /G6 /MT /W3 /GX- /DNDEBUG /DWIN32 /D_WINDOWS /Ox 

LDFLAGS = 
LIBS = 
RANLIB = echo


.cpp.o:
	$(CXX) /c $(CXXFLAGS) /Tp$< /Fo$@


all: make_cmos_image

make_cmos_image.exe: make_cmos_image.o
	link  /nologo /subsystem:console /incremental:no /machine:I386 /out:$@  make_cmos_image.o

clean:
	-del *.o
	-del make_cmos_image.exe

dist-clean: clean
	-del Makefile
