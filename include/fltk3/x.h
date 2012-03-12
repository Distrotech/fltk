//
// "$Id: x.h 8381 2011-02-06 10:24:23Z manolo $"
//
// X11 header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2011 by Bill Spitzak and others.
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

// These are internal fltk symbols that are necessary or useful for
// calling Xlib.  You should include this file if (and ONLY if) you
// need to call Xlib directly.  These symbols may not exist on non-X
// systems.

/** \class Fl_Mac_App_Menu 
 Mac OS-specific class allowing to localize the application menu.
 
 These character strings are used to build the application menu. They can be localized
 at run time to any UTF-8 text by placing instructions such as this \e very 
 early in the program:
 \verbatim
 Fl_Mac_App_Menu::print = "Imprimer la fenêtre";
 \endverbatim
*/

#if !defined(Fltk3_X_H) && !defined(FLTK3_DOXYGEN) 
#  define Fltk3_X_H

#  include "enumerations.h"

#  ifdef WIN32
#    include "win32.h"
#  elif defined(__APPLE__)
#    include "osx.h"
#  else
#    if defined(_ABIN32) || defined(_ABI64) // fix for broken SGI Irix X .h files
#      pragma set woff 3322
#    endif
#    include <X11/Xlib.h>
#    include <X11/Xutil.h>
#    if defined(_ABIN32) || defined(_ABI64)
#      pragma reset woff 3322
#    endif
#    include <X11/Xatom.h>
#    include "Window.h"
#    include "Xutf8.h"
// Mirror X definition of Region to fltk3::Region, for portability...
namespace fltk3 {
  typedef ::Region Region;
}

FLTK3_EXPORT void fl_open_display();
FLTK3_EXPORT void fl_open_display(Display*);
FLTK3_EXPORT void fl_close_display();

// constant info about the X server connection:
extern FLTK3_EXPORT Display *fl_display;
extern FLTK3_EXPORT int fl_screen;
extern FLTK3_EXPORT XVisualInfo *fl_visual;
extern FLTK3_EXPORT Colormap fl_colormap;


// drawing functions:
extern FLTK3_EXPORT GC fl_gc;
extern FLTK3_EXPORT Window fl_window;
FLTK3_EXPORT ulong fl_xpixel(fltk3::Color i);
FLTK3_EXPORT ulong fl_xpixel(uchar r, uchar g, uchar b);

namespace fltk3 {
  FLTK3_EXPORT void clip_region(fltk3::Region);
  FLTK3_EXPORT fltk3::Region clip_region();
}

// feed events into fltk:
FLTK3_EXPORT int fl_handle(const XEvent&);

// you can use these in fltk3::add_handler() to look at events:
extern FLTK3_EXPORT const XEvent* fl_xevent;
extern FLTK3_EXPORT ulong fl_event_time;

// off-screen pixmaps: create, destroy, draw into, copy to window:
namespace fltk3 {
  typedef ulong Offscreen;
}
#   define fl_create_offscreen(w,h) \
  XCreatePixmap(fl_display, \
	      (fltk3::SurfaceDevice::surface()->class_name() == fltk3::DisplayDevice::class_id ? \
	      fl_window : fl_xid(fltk3::first_window()) ) , \
	      w, h, fl_visual->depth)
// begin/end are macros that save the old state in local variables:
#    define fl_begin_offscreen(pixmap) \
  ::Window _sw=fl_window; fl_window=pixmap; \
  fltk3::SurfaceDevice *_ss = fltk3::SurfaceDevice::surface(); fltk3::DisplayDevice::display_device()->set_current(); \
  fltk3::push_no_clip()
#    define fl_end_offscreen() \
  fltk3::pop_clip(); fl_window = _sw; _ss->set_current()

#    define fl_delete_offscreen(pixmap) XFreePixmap(fl_display, pixmap)

// Bitmap masks
namespace fltk3 {
  typedef ulong Bitmask;
}

extern FLTK3_EXPORT fltk3::Bitmask fl_create_bitmask(int w, int h, const uchar *data);
extern FLTK3_EXPORT fltk3::Bitmask fl_create_alphamask(int w, int h, int d, int ld, const uchar *data);
extern FLTK3_EXPORT void fl_delete_bitmask(fltk3::Bitmask bm);

#if defined(FL_LIBRARY) || defined(FLTK3_INTERNALS)
namespace fltk3 {
  extern FLTK3_EXPORT ::Window message_window;
}
extern FLTK3_EXPORT void *fl_xftfont;
FLTK3_EXPORT fltk3::Region XRectangleRegion(int x, int y, int w, int h); // in fltk3::rect.cxx

// access to core fonts:
// This class provides a "smart pointer" that returns a pointer to an XFontStruct.
// The global variable fl_xfont can be called wherever a bitmap "core" font is
// needed, e.g. when rendering to a GL context under X11.
// With Xlib / X11 fonts, fl_xfont will return the current selected font.
// With XFT / X11 fonts, fl_xfont will attempt to return the bitmap "core" font most
// similar to (usually the same as) the current XFT font.
class Fl_XFont_On_Demand
{
public:
  Fl_XFont_On_Demand(XFontStruct* p = NULL) : ptr(p) { }
  Fl_XFont_On_Demand& operator=(const Fl_XFont_On_Demand& x)
  { ptr = x.ptr;  return *this; }
  Fl_XFont_On_Demand& operator=(XFontStruct* p)
  { ptr = p;  return *this; }
  XFontStruct* value();
  operator XFontStruct*() { return value(); }
  XFontStruct& operator*() { return *value(); }
  XFontStruct* operator->() { return value(); }
  bool operator==(const Fl_XFont_On_Demand& x) { return ptr == x.ptr; }
  bool operator!=(const Fl_XFont_On_Demand& x) { return ptr != x.ptr; }
private:
  XFontStruct *ptr;
};
extern FLTK3_EXPORT Fl_XFont_On_Demand fl_xfont;

// this object contains all X-specific stuff about a window:
// Warning: this object is highly subject to change!  
// FL_LIBRARY or FLTK3_INTERNALS must be defined to access this class.
class FLTK3_EXPORT Fl_X {
public:
  Window xid;
  Window other_xid;
  fltk3::Window *w;
  fltk3::Region region;
  Fl_X *next;
  char wait_for_expose;
  char backbuffer_bad; // used for XDBE
  static Fl_X* first;
  static Fl_X* i(const fltk3::Window* wi) {return wi->i;}
  void setwindow(fltk3::Window* wi) {w=wi; wi->i=this;}
  void sendxjunk();
  static void make_xid(fltk3::Window*,XVisualInfo* =fl_visual, Colormap=fl_colormap);
  static Fl_X* set_xid(fltk3::Window*, Window);
  // kludges to get around protection:
  void flush() {w->flush();}
  static void x(fltk3::Window* wi, int X) {wi->x(X);}
  static void y(fltk3::Window* wi, int Y) {wi->y(Y);}
};

extern FLTK3_EXPORT char fl_override_redirect; // hack into Fl_X::make_xid()
extern FLTK3_EXPORT int fl_background_pixel;  // hack into Fl_X::make_xid()

inline Window fl_xid(const fltk3::Window* w) { 
  Fl_X *temp = Fl_X::i(w); 
  return temp ? temp->xid : 0;
}

#else

extern Window fl_xid_(const fltk3::Window* w);
#define fl_xid(w) fl_xid_(w)

#endif // FL_LIBRARY || FLTK3_INTERNALS

FLTK3_EXPORT fltk3::Window* fl_find(Window xid);


// Dummy function to register a function for opening files via the window manager...
inline void fl_open_callback(void (*)(const char *)) {}

extern FLTK3_EXPORT int fl_parse_color(const char* p, uchar& r, uchar& g, uchar& b);

#  endif
#endif

//
// End of "$Id: x.h 8381 2011-02-06 10:24:23Z manolo $".
//
