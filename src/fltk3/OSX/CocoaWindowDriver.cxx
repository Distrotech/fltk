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


fltk3::CocoaWindowDriver fltk3::cocoa_window_driver;


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



#endif // __APPLE__

//
// End of "$Id$".
//
