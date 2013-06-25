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

#ifndef FLTK3_UNIX_UNIX_SYSTEM_DRIVER_H
#define FLTK3_UNIX_UNIX_SYSTEM_DRIVER_H

#include <config.h>

#ifdef USE_X11

#include <fltk3/SystemDriver.h>

namespace fltk3 {
  
  class FLTK3_EXPORT UnixSystemDriver : public fltk3::SystemDriver {
  public:
    UnixSystemDriver();
  };
  
  extern FLTK3_EXPORT UnixSystemDriver* unix_system_driver;
  
}

#endif // USE_X11

#endif // FLTK3_UNIX_UNIX_SYSTEM_DRIVER_H

//
// End of "$Id$".
//
