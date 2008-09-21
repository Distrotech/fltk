//
// "$Id"
//
// Main header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2008 by Bill Spitzak and others.
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

/** \file
    FlCairo include file hanling transparently platform dependent cairo include files
 */
#ifndef FL_CAIRO_H
# define FL_CAIRO_H
# ifdef HAVE_CAIRO

// Cairo is currently supported for the following platforms:
// Win32, Apple Quartz, X11

# include <FL/Fl_Export.H>

# if defined(WIN32)
#  include <cairo/cairo-win32.h>
# elif defined(__APPLE_QUARTZ__)
#  include <cairo/cairo-quartz.h>
# elif defined(__APPLE_QD__)
#  error Apple Quartz is necessary for Cairo upport.
# elif defined(X11) // X11
#  include <cairo/cairo-xlib.h>
# else
# error Cairo is not supported on that platform.
# endif

# endif // HAVE_CAIRO
#endif // FL_CAIRO_H

/** Contains all the necessary info on the current cairo context */
class FL_EXPORT Fl_Cairo_State {
public:
    Fl_Cairo_State() : cc_(0), own_cc_(false), autolink_(true) {}

    // access attributes
    cairo_t* cc() const {return cc_;}		 ///< Gets the current cairo context
    bool autolink() const {return autolink_;}	 ///< Gets the autolink option
    void cc(cairo_t* c, bool own=true)  {	 ///< Sets the current cairo context, own indicates cc deletion is made by us
	if (cc_ && own_cc_) cairo_destroy(cc_); 
	cc_=c;
	if (!cc_) window_=0;
	own_cc_=own;
    }
    void autolink(bool b)  {autolink_ = b;}	///< Gets the autolink option
    void window(void* w)  {window_=w;}		///< Sets the window to keep track on
    void* window()  {return window_;}		///< Gets the last window attached to a cc

private:
    cairo_t * cc_;	///< contains the unique autoupdated cairo context
    bool own_cc_;	///< indicates whether we must delete the cc, useful for internal cleanup
    bool autolink_;	///< true by default, permits to prevent the automatic cairo mapping on fltk windows for custom cairo implementations
    void* window_;
};

//
// End of "$Id"
//
