//
// "$Id: navigation.cxx 8500 2011-03-03 09:20:46Z bgbnbigben $"
//
// Navigation test program for the Fast Light Tool Kit (FLTK).
//
// Silly test of navigation keys. This is not a recommended method of
// laying out your panels!
//
// Copyright 1998-2006 by Bill Spitzak and others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems on the following page:
//
//    http://www.fltk.org/str.php
//

int main(int, char **) {
  return 0;
}

#if 0 // FIXME: 123-2

#include <stdio.h>
#include <stdlib.h>
#include <fltk/run.h>
#include <fltk/Window.h>
#include <fltk/Input.h>

#define WIDTH 600
#define HEIGHT 300
#define GRID 25

using namespace fltk;

int main(int argc, char **argv) {
  if (argc > 1) srand(atoi(argv[1]));
  Window window(WIDTH,HEIGHT,argv[0]);
  window.end(); // don't auto-add children
  for (int i = 0; i<10000; i++) {
    // make up a random size of widget:
    int x = rand()%(WIDTH/GRID+1) * GRID;
    int y = rand()%(HEIGHT/GRID+1) * GRID;
    int w = rand()%(WIDTH/GRID+1) * GRID;
    if (w < x) {w = x-w; x-=w;} else {w = w-x;}
    int h = rand()%(HEIGHT/GRID+1) * GRID;
    if (h < y) {h = y-h; y-=h;} else {h = h-y;}
    if (w < GRID || h < GRID || w < h) continue;
    // find where to insert it and see if it intersects something:
    Widget *j = 0;
    int n; for (n=0; n < window.children(); n++) {
      Widget *o = window.child(n);
      if (x<o->x()+o->w() && x+w>o->x() &&
	  y<o->y()+o->h() && y+h>o->y()) break;
      if (!j && (y < o->y() || (y == o->y() && x < o->x()))) j = o;
    }
    // skip if intersection:
    if (n < window.children()) continue;
    window.insert(*(new Input(x,y,w,h)),j);
  }
  window.resizable(window);
  window.show();
  return fltk::run();
}

#endif

//
// End of "$Id: navigation.cxx 8500 2011-03-03 09:20:46Z bgbnbigben $".
//
