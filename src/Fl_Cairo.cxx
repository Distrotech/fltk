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
#include "config.h"

#ifdef HAVE_CAIRO

#include <FL/Fl.H>
#include <FL/x.H>
#include <FL/Fl_Window.H>

// static Fl module initialization :
Fl_Cairo_State Fl::cairo_state;	///< contains all necesary info for current cairo context mapping
// Fl cairo features implementation

/** Makes the window w current, and return a valid cairo context. */
cairo_t * Fl::cairo_make_current(Fl_Window* wi) {
    if (!wi) return NULL; // Precondition
    
    if (fl_gc==0) { // means remove current cc
	Fl::cairo_cc(0); // destroy any previous cc
	return 0;
    }
    //wi->make_current();

#if defined(UNIX_X11)
    return Fl::cairo_make_current(fl_gc, wi->w(), wi->h());
#else
    return Fl::cairo_make_current(fl_gc, wi->w(), wi->h());
#endif
}
/** Creates a cairo context from a gc only, get its window size  or offscreen size if fl_window is null */
cairo_t * Fl::cairo_make_current(void *gc) {
    int W=0,H=0;
#if defined(__APPLE_QUARTZ__) 
    if (fl_window) {
      Rect portRect; 
      GetPortBounds(GetWindowPort( fl_window ), &portRect);
      W = portRect.right-portRect.left;
      H = portRect.bottom-portRect.top;
    } 
    else {
      W = CGBitmapContextGetHeight(fl_gc);
      H = CGBitmapContextGetHeight(fl_gc);
    }
#elif defined(WIN32)
    // we don't need any W,H for WIN32
#elif defined(UNIX_X11)
    //FIXME X11 get W,H
    // gc will be the window handle here
# warning FIXME get W,H for cairo_make_current(void*)
#else
# error Cairo is not supported under this platform.
#endif
    if (!gc) {
	Fl::cairo_cc(0);
	return 0;
    }
    if (gc==Fl::cairo_cc() && fl_window== (Window) Fl::cairo_window())
	return Fl::cairo_cc();
    Fl::cairo_window(fl_gc); // keep track for next time
    cairo_surface_t * s = Fl::cairo_create_surface(gc, W, H);
    cairo_t * c = cairo_create(s);
    cairo_surface_destroy(s);
    Fl::cairo_cc(c);
    return c;
}

/** Creates a cairo context from a gc and its size */
cairo_t * Fl::cairo_make_current(void *gc, int W, int H) {
    cairo_surface_t * s = Fl::cairo_create_surface(gc, W, H);
    cairo_t * c = cairo_create(s);
    cairo_surface_destroy(s);
    Fl::cairo_cc(c);
    return c;
}
/** 
    Creates transparently a cairo_surface_t object.
    gc is an HDC context in  WIN32, a CGContext* in Quartz, a display on X11
 */
cairo_surface_t * Fl::cairo_create_surface(void * gc, int W, int H) {
# if   defined(WIN32)
    return cairo_win32_surface_create((HDC) gc);
# elif defined(__APPLE_QUARTZ__)
    return cairo_quartz_surface_create_for_cg_context((CGContext*) gc, W, H);
# elif defined(__APPLE_QD__)
#  error Cairo is not supported under Apple Quickdraw, please use Apple Quartz.
# elif defined(UNIX_X11) // X11
    return cairo_xlib_surface_create(fl_display, fl_window,fl_visual->visual, W, H);
# else
#  error Cairo is not supported under this platform.
# endif
}
#endif // HAVE_CAIRO

//
// End of "$Id"
//
