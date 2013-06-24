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

#ifdef USE_X11

#include "XlibWindowDriver.h"
#include <fltk3/x.h>
#include <stdio.h>


fltk3::XlibWindowDriver::XlibWindowDriver()
{
  fprintf(stderr, "Loading Window Driver\n");
}


void fltk3::XlibWindowDriver::iconize(fltk3::Window* win)
{
  XIconifyWindow(fl_display, Fl_X::i(win)->xid, fl_screen);
}


void fltk3::XlibWindowDriver::decoration_size(bool, int& top, int& left, int& right, int& bottom)
{
  // Ensure border is on screen; these values are generic enough
  // to work with many window managers, and are based on KDE defaults.
  top = 20;
  left = 4;
  right = 4;
  bottom = 8;
}


#endif // USE_X11

//
// End of "$Id$".
//
