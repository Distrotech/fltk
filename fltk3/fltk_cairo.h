//
// "$Id$"
//

// 123 TODO: remove stray comments
// 123 TODO: add namespace statements
// 123 TODO: replace class name, constructors and destructor
// 123 TODO: add friend statement for Twin Class
// 123 TODO: add 'compat(FLTK2)' to constructors
// 123 TODO: add twin class with all constructors
// 123 TODO: change all arguments to the FLTK2 class name
// 123 TODO: change the source code to use the new class names
// 123 TODO: add casting to return values
// 123 TODO: move all FLTK2-only functions to the FLTK3 section and implement them
// 123 TODO: remove the FLTK1 and FLTK2 sections in the headers
// 123 TODO: 

//
// "$Id: Fl_Cairo.H 6716 2009-03-24 01:40:44Z fabien $"
//
// Main header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2009 by Bill Spitzak and others.
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

/* \file
    Handling transparently platform dependent cairo include files 
*/

#ifndef FL_CAIRO_H
# define FL_CAIRO_H
# ifdef HAVE_CAIRO

// Cairo is currently supported for the following platforms:
// Win32, Apple Quartz, X11

# include <FL/Fl_Export.H>

# if defined(USE_X11) // X11
#  include <cairo-xlib.h>
# elif defined(WIN32)
#  include <cairo-win32.h>
# elif defined(__APPLE_QUARTZ__)
#  include <cairo-quartz.h>
# else
#  error Cairo is not supported on that platform.
# endif

/** 
   \addtogroup group_cairo
   @{
*/

/** 
   Contains all the necessary info on the current cairo context.
   A private internal & unique corresponding object is created to
   permit cairo context state handling while keeping it opaque.
   For internal use only.
   \note Only available when configure has the --enable-cairo option
*/
class FL_EXPORT Fl_Cairo_State {
public:
  Fl_Cairo_State() : cc_(0), own_cc_(false), autolink_(false), window_(0), gc_(0) {}

    // access attributes
    cairo_t* cc() const {return cc_;}		 ///< Gets the current cairo context
    bool autolink() const {return autolink_;}	 ///< Gets the autolink option. See Fl::cairo_autolink_context(bool)
    /** Sets the current cairo context, \p own indicates cc deletion is handle externally by user */
    void cc(cairo_t* c, bool own=true)  {	 
	if (cc_ && own_cc_) cairo_destroy(cc_); 
	cc_=c;
	if (!cc_) window_=0;
	own_cc_=own;
    }
    void  autolink(bool b);                     ///< Sets the autolink option, only available with --enable-cairoext
    void  window(void* w)  {window_=w;}		///< Sets the window \p w to keep track on
    void* window() const {return window_;}	///< Gets the last window attached to a cc
    void  gc(void* c)  {gc_=c;}		        ///< Sets the gc \p c to keep track on
    void* gc() const {return gc_;}		///< Gets the last gc attached to a cc

private:
    cairo_t * cc_;	 // contains the unique autoupdated cairo context
    bool own_cc_;	 // indicates whether we must delete the cc, useful for internal cleanup
    bool autolink_;	 // true by default, permits to prevent the automatic cairo mapping on fltk windows for custom cairo implementations
    void* window_, *gc_; // for keeping track internally of last win+gc treated
};

/** @} */

# endif // HAVE_CAIRO
#endif // FL_CAIRO_H

//
// End of "$Id: Fl_Cairo.H 6716 2009-03-24 01:40:44Z fabien $" .
//

/* suggested twin class
// This is the Twin Class to fltk::fltk_cairo
class Fl_Cairo : public fltk::fltk_cairo {
public:
  Fl_Cairo(int x, int t, int w, int h, const char *label=0)
  : fltk::fltk_cairo(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Cairo.H 6716 2009-03-24 01:40:44Z fabien $"
//
// Main header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2009 by Bill Spitzak and others.
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

/* \file
    Handling transparently platform dependent cairo include files 
*/

#ifndef FL_CAIRO_H
# define FL_CAIRO_H
# ifdef HAVE_CAIRO

// Cairo is currently supported for the following platforms:
// Win32, Apple Quartz, X11

# include <FL/Fl_Export.H>

# if defined(USE_X11) // X11
#  include <cairo-xlib.h>
# elif defined(WIN32)
#  include <cairo-win32.h>
# elif defined(__APPLE_QUARTZ__)
#  include <cairo-quartz.h>
# else
#  error Cairo is not supported on that platform.
# endif

/** 
   \addtogroup group_cairo
   @{
*/

/** 
   Contains all the necessary info on the current cairo context.
   A private internal & unique corresponding object is created to
   permit cairo context state handling while keeping it opaque.
   For internal use only.
   \note Only available when configure has the --enable-cairo option
*/
class FL_EXPORT Fl_Cairo_State {
public:
  Fl_Cairo_State() : cc_(0), own_cc_(false), autolink_(false), window_(0), gc_(0) {}

    // access attributes
    cairo_t* cc() const {return cc_;}		 ///< Gets the current cairo context
    bool autolink() const {return autolink_;}	 ///< Gets the autolink option. See Fl::cairo_autolink_context(bool)
    /** Sets the current cairo context, \p own indicates cc deletion is handle externally by user */
    void cc(cairo_t* c, bool own=true)  {	 
	if (cc_ && own_cc_) cairo_destroy(cc_); 
	cc_=c;
	if (!cc_) window_=0;
	own_cc_=own;
    }
    void  autolink(bool b);                     ///< Sets the autolink option, only available with --enable-cairoext
    void  window(void* w)  {window_=w;}		///< Sets the window \p w to keep track on
    void* window() const {return window_;}	///< Gets the last window attached to a cc
    void  gc(void* c)  {gc_=c;}		        ///< Sets the gc \p c to keep track on
    void* gc() const {return gc_;}		///< Gets the last gc attached to a cc

private:
    cairo_t * cc_;	 // contains the unique autoupdated cairo context
    bool own_cc_;	 // indicates whether we must delete the cc, useful for internal cleanup
    bool autolink_;	 // true by default, permits to prevent the automatic cairo mapping on fltk windows for custom cairo implementations
    void* window_, *gc_; // for keeping track internally of last win+gc treated
};

/** @} */

# endif // HAVE_CAIRO
#endif // FL_CAIRO_H

//
// End of "$Id: Fl_Cairo.H 6716 2009-03-24 01:40:44Z fabien $" .
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
// fltk_cairo.h
//
// Copyright 1998-2006 by Bill Spitzak and others.
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
// Please report all bugs and problems to "fltk-bugs@fltk.org".

/** \file
  "Portably" include cairo common definitions for fltk. If fltk is
  compiled correctly, you can create a cairo "surface" from an fltk
  Window and then make your own cairo context to draw into it.

  FLTK may also be compiled to use cairo for \e all it's drawing, by
  adding --enable_cairo when running ./configure. In this case this
  has already been done when draw() is called, and the cairo context
  is in fltk::cc.
*/

#ifndef fltk_cairo_h
#define fltk_cairo_h

#include <fltk/FL_API.h>
#include <cairo.h>

namespace fltk {
  extern FL_API cairo_t * cr;
  class Window;
  FL_API cairo_surface_t * cairo_create_surface(Window* w);
}

#endif

// End of fltk_cairo.h

#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
