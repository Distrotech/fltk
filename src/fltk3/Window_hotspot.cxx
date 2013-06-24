//
// "$Id$"
//
// Common hotspot routines for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2010 by Bill Spitzak and others.
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
//     http://www.fltk.org/str.php
//

#include <fltk3/run.h>
#include <fltk3/Window.h>
#include <fltk3/WindowDriver.h>
#include <fltk3/x.h>
#include <stdio.h>

void fltk3::Window::hotspot(int X, int Y, int offscreen) {
  int mx,my;

  // Update the screen position based on the mouse position.
  fltk3::get_mouse(mx,my);
  X = mx-X; Y = my-Y;

  // If offscreen is 0 (the default), make sure that the window
  // stays on the screen, if possible.
  if (!offscreen) {
    int scr_x, scr_y, scr_w, scr_h;
    fltk3::screen_work_area(scr_x, scr_y, scr_w, scr_h);

    int top = 0;
    int left = 0;
    int right = 0;
    int bottom = 0;

    if (border()) {
      window_driver->decoration_size((size_range_set && (maxw != minw || maxh != minh)),
                                     top, left, right, bottom);
    }
    // now insure contents are on-screen (more important than border):
    if (X+w()+right > scr_w+scr_x) X = scr_w+scr_x-right-w();
    if (X-left < scr_x) X = left + scr_x;
    if (Y+h()+bottom > scr_h+scr_y) Y = scr_h+scr_y-bottom-h();
    if (Y-top < scr_y) Y = top + scr_y;
    // make sure that we will force this position
    if (X==x()) x(X-1);
  }

  position(X,Y);
}

void fltk3::Window::hotspot(const fltk3::Widget *o, int offscreen) {
  int X = o->w()/2;
  int Y = o->h()/2;
  while (o != this && o) {
    X += o->x(); Y += o->y();
    o = o->window();
  }
  hotspot(X,Y,offscreen);
}


//
// End of "$Id$".
//
