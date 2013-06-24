//
// "$Id: WindowDriver.h 9930 2013-05-31 13:04:25Z manolo $"
//
// Definition of classes fltk3::GraphicsDriver, fltk3::SurfaceDevice, fltk3::DisplayDevice
// for the Fast Light Tool Kit (FLTK).
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
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//
/** \file WindowDriver.h
 \brief declaration of class WindowDriver
 */

#ifndef FLTK3_WINDOW_DRIVER_H
#define FLTK3_WINDOW_DRIVER_H

#include <config.h>

#include <fltk3/x.h>
#include <fltk3/Object.h>
#include <fltk3/Window.h>
#include <stdlib.h>

namespace fltk3 {
  
  class FLTK3_EXPORT WindowDriver : public Object {
  public:
    WindowDriver();
    virtual ~WindowDriver() { }
    
    virtual void iconize(fltk3::Window*) = 0;
    virtual void decoration_size(bool, int&, int&, int&, int&) = 0;
  };
  
  FLTK3_EXPORT extern WindowDriver *window_driver;
  
}

#endif // Fltk3_Device_H

//
// End of "$Id: WindowDriver.h 9930 2013-05-31 13:04:25Z manolo $".
//
