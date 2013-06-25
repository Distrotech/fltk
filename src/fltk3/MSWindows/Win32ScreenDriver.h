//
// "$Id$"
//
// Window Driver for the Fast Light Tool Kit (FLTK).
//
// Copyright 2010-2013 by Bill Spitzak and others.
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
/** \file CocoaWindowDriver.h
 */

#ifndef FLTK3_MSWINDOWS_WIN32_SCREEN_DRIVER_H
#define FLTK3_MSWINDOWS_WIN32_SCREEN_DRIVER_H

#include <config.h>

#ifdef WIN32

#include <fltk3/ScreenDriver.h>

namespace fltk3 {
  
  class FLTK3_EXPORT Win32ScreenDriver : public fltk3::ScreenDriver {
  public:
    Win32ScreenDriver();
  };
  
  extern FLTK3_EXPORT Win32ScreenDriver* win32_screen_driver;

}

#endif // WIN32

#endif // FLTK3_MSWINDOWS_WIN32_SCREEN_DRIVER_H

//
// End of "$Id$".
//
