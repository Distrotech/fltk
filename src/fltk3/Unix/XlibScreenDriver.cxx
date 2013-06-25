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

#include "XlibScreenDriver.h"
#include <fltk3/x.h>
#include <stdio.h>
#include <fltk3/ask.h>


fltk3::XlibScreenDriver::XlibScreenDriver()
{
}


void fltk3::CocoaScreenDriver::beep(int type)
{
  switch (type) {
    case fltk3::BEEP_DEFAULT :
    case fltk3::BEEP_ERROR :
      if (!fl_display) fl_open_display();      
      XBell(fl_display, 100);
      break;
    default :
      if (!fl_display) fl_open_display();
      XBell(fl_display, 50);
      break;
  }
  

#endif // USE_X11

//
// End of "$Id$".
//
