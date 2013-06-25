//
// "$Id$"
//
// implementation of fltk3::Device class for the Fast Light Tool Kit (FLTK).
//
// Copyright 2010-2011 by Bill Spitzak and others.
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
// Please report all bugs and problems to:
//
//     http://www.fltk.org/str.php
//

#include <config.h>

#ifdef __APPLE__

#include "CocoaWindowDriver.h"

#include <fltk3/x.h>
#include <fltk3/run.h>
#include <fltk3/draw.h>
#include <fltk3/Window.h>


fltk3::CocoaWindowDriver::CocoaWindowDriver()
{
}


void fltk3::CocoaWindowDriver::iconize(fltk3::Window* win)
{
  Fl_X::i(win)->collapse();
}


void fltk3::CocoaWindowDriver::decoration_size(bool, int& top, int& left, int& right, int& bottom)
{
  top = 24;
  left = 2;
  right = 2;
  bottom = 2;
}


void fltk3::CocoaWindowDriver::draw_decoration(fltk3::Window* win)
{
  // on OS X, windows have no frame. To resize a window, we drag the lower right
  // corner. This code draws a little ribbed triangle for dragging.
  // Starting with 10.7, OS X windows have a hidden frame and the corner is no longer needed
  if (fl_mac_os_version < 100700) {
    if (fl_gc && !win->parent() && win->resizable() && (!win->size_range_set || win->minh!=win->maxh || win->minw!=win->maxw)) {
      int dx = fltk3::box_dw(win->box())-fltk3::box_dx(win->box());
      int dy = fltk3::box_dh(win->box())-fltk3::box_dy(win->box());
      if (dx<=0) dx = 1;
      if (dy<=0) dy = 1;
      int x1 = w()-dx-1, x2 = x1, y1 = h()-dx-1, y2 = y1;
      fltk3::Color c[4] = {
        color(),
        fltk3::color_average(color(), fltk3::WHITE, 0.7f),
        fltk3::color_average(color(), fltk3::BLACK, 0.6f),
        fltk3::color_average(color(), fltk3::BLACK, 0.8f),
      };
      int i;
      for (i=dx; i<12; i++) {
        fltk3::color(c[i&3]);
        fltk3::line(x1--, y1, x2, y2--);
      }
    }
  }
}


#endif // __APPLE__

//
// End of "$Id$".
//
