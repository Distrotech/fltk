#
# "$Id: Makefile,v 1.4 1998/10/21 14:18:53 mike Exp $"
#
# Top-level makefile for the Fast Light Tool Kit (FLTK).
#
# Copyright 1998 by Bill Spitzak and others.
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Library General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Library General Public License for more details.
#
# You should have received a copy of the GNU Library General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
# USA.
#
# Please report all bugs and problems to "fltk-bugs@easysw.com".
#

SHELL=/bin/sh

DIRS	=	src fluid test

all:	depend
	for dir in $(DIRS); do\
		echo "=== making $$dir ===";\
		(cd $$dir;$(MAKE));\
	done

install: all
	for dir in $(DIRS); do\
		echo "=== installing $$dir ===";\
		(cd $$dir;$(MAKE) install);\
	done

depend:
	for dir in $(DIRS); do\
		echo "=== making dependencies in $$dir ===";\
		if test ! -f $$dir/makedepend; then\
			touch 0101000070 $$dir/makedepend;\
		fi;\
		(cd $$dir;$(MAKE) depend);\
	done

clean:
	-@ rm -f core config.cache *.o *.bck
	for dir in $(DIRS); do\
		echo "=== cleaning $$dir ===";\
		(cd $$dir;$(MAKE) clean);\
	done

#
# End of "$Id: Makefile,v 1.4 1998/10/21 14:18:53 mike Exp $".
#
