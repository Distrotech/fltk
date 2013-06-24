//
// "$Id$"
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
/** \file Device.h 
 \brief declaration of classes fltk3::SurfaceDevice, 
 fltk3::DisplayDevice, fltk3::DevicePlugin.
 */

#ifndef Fltk3_Device_H
#define Fltk3_Device_H

#include <config.h>

#include <fltk3/GraphicsDriver.h>

#include <fltk3/x.h>
#include <fltk3/Object.h>
#include <fltk3/Plugin.h>
#include <fltk3/Image.h>
#include <fltk3/Bitmap.h>
#include <fltk3/Pixmap.h>
#include <fltk3/RGBImage.h>
#include <stdlib.h>

class Fl_Font_Descriptor;
class Fl_Surface_Device;

namespace fltk3 {
    
  /**
   \brief A surface that's susceptible to receive graphical output.
   */
  class FLTK3_EXPORT SurfaceDevice : public Object {
    friend class ::Fl_Surface_Device;
    /** \brief The graphics driver in use by this surface. */
    fltk3::GraphicsDriver *_driver;
    static SurfaceDevice *_surface; // the surface that currently receives graphics output
  protected:
    /** \brief Constructor that sets the graphics driver to use for the created surface. */
    SurfaceDevice(fltk3::GraphicsDriver *graphics_driver) {_driver = graphics_driver; };
  public:
    virtual void set_current(void);
    /** \brief Sets the graphics driver of this drawing surface. */
    inline void driver(fltk3::GraphicsDriver *graphics_driver) {_driver = graphics_driver;};
    /** \brief Returns the graphics driver of this drawing surface. */
    inline fltk3::GraphicsDriver *driver() {return _driver; };
    /** \brief the surface that currently receives graphics output */
    static inline fltk3::SurfaceDevice *surface() {return _surface; };
    /** \brief The destructor. */
    virtual ~SurfaceDevice();
  };
  
  /**
   \brief A display to which the computer can draw.
   */
  class FLTK3_EXPORT DisplayDevice : public fltk3::SurfaceDevice {
    static DisplayDevice *_display; // the platform display device
  public:
    /** \brief A constructor that sets the graphics driver used by the display */
    DisplayDevice(fltk3::GraphicsDriver *graphics_driver);
    /** Returns the platform display device. */
    static inline DisplayDevice *display_device() {return _display;};
  };
  
  /**
   This plugin socket allows the integration of new device drivers for special
   window or screen types. It is currently used to provide an automated printing
   service for OpenGL windows, if linked with fltk_gl.
   */
  class FLTK3_EXPORT DevicePlugin : public fltk3::Plugin {
  public:
    /** \brief The constructor */
    DevicePlugin(const char *name)
    : fltk3::Plugin(klass(), name) { }
    /** \brief Returns the class name */
    virtual const char *klass() { return "fltk:device"; }
    /** \brief Returns the plugin name */
    virtual const char *name() = 0;
    /** \brief Prints a widget 
     \param w the widget
     \param x,y offsets where to print relatively to coordinates origin
     \param height height of the current drawing area
     */
    virtual int print(fltk3::Widget* w, int x, int y, int height) = 0;
  };
  
}

#endif // Fltk3_Device_H

//
// End of "$Id$".
//
