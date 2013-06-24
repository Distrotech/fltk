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

#ifndef FLTK3_OSX_COCOA_WINDOW_DRIVER_H
#define FLTK3_OSX_COCOA_WINDOW_DRIVER_H

#include <config.h>

#ifdef __APPLE__

#include <fltk3/WindowDriver.h>

namespace fltk3 {
  
  class FLTK3_EXPORT CocoaWindowDriver : public fltk3::WindowDriver {
  public:
    CocoaWindowDriver();
    
    virtual void iconize(fltk3::Window*);
    virtual void decoration_size(bool, int&, int&, int&, int&);

  };
  
  extern FLTK3_EXPORT CocoaWindowDriver cocoa_window_driver;
  
}

#endif // __APPLE__

#endif // FLTK3_OSX_COCOA_WINDOW_DRIVER_H

//
// End of "$Id$".
//
