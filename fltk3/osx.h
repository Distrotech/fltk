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
// "$Id: mac.H 7035 2010-01-29 21:16:20Z manolo $"
//
// Mac header file for the Fast Light Tool Kit (FLTK).
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

// Do not directly include this file, instead use <FL/x.H>.  It will
// include this file if "__APPLE__" is defined.  This is to encourage
// portability of even the system-specific code...
#ifndef FL_DOXYGEN

#if !defined(Fl_X_H)
#  error "Never use <FL/mac.H> directly; include <FL/x.H> instead."
#endif // !Fl_X_H

// Standard MacOS Carbon API includes...
#include <Carbon/Carbon.h>
#include <config.h>

#ifdef __APPLE_COCOA__
#ifndef MAC_OS_X_VERSION_10_3
#define MAC_OS_X_VERSION_10_3 1030
#endif
#ifndef MAC_OS_X_VERSION_10_4
#define MAC_OS_X_VERSION_10_4 1040
#endif
#ifndef MAC_OS_X_VERSION_10_5
#define MAC_OS_X_VERSION_10_5 1050
#endif
#ifndef MAC_OS_X_VERSION_10_6
#define MAC_OS_X_VERSION_10_6 1060
#endif
#ifndef MAC_OS_X_VERSION_MAX_ALLOWED
#define MAC_OS_X_VERSION_MAX_ALLOWED MAC_OS_X_VERSION_10_3
#endif
#endif // __APPLE_COCOA__

#ifndef CGFLOAT_DEFINED //appears with 10.5 in CGBase.h
#if defined(__LP64__) && __LP64__
typedef double CGFloat;
#else
typedef float CGFloat;
#endif
#endif // CGFLOAT_DEFINED


// Now make some fixes to the headers...
#undef check			// Dunno where this comes from...

// Some random X equivalents
struct XPoint { int x, y; };
struct XRectangle {int x, y, width, height;};

#ifdef __APPLE_COCOA__
// necessary so a CGRect matches exactly what is denoted x,y,w,h for clipping purposes
#define FL_CGRECTMAKE_COCOA(x,y,w,h)  CGRectMake(x, y, w > 0 ? w - 0.9 : 0, h > 0 ? h - 0.9 : 0)

typedef void *Window; // this is really a pter to the subclass FLWindow of NSWindow
typedef struct flCocoaRegion {
  int count;
  CGRect *rects;
} *Fl_Region;  // a region is the union of a series of rectangles
inline Fl_Region XRectangleRegion(int x, int y, int w, int h) {
  Fl_Region R = (Fl_Region)malloc(sizeof(*R));
  R->count = 1;
  R->rects = (CGRect *)malloc(sizeof(CGRect));
  *(R->rects) = FL_CGRECTMAKE_COCOA(x, y, w, h);
  return R;
}
inline void XDestroyRegion(Fl_Region r) {
  if(r) {
	free(r->rects);
	free(r);
	}
}
extern void *fl_default_cursor;
extern void *fl_system_menu;
typedef CGContextRef Fl_Offscreen;
typedef CGImageRef Fl_Bitmask;

#else

typedef WindowRef Window;
typedef RgnHandle Fl_Region;
inline Fl_Region XRectangleRegion(int x, int y, int w, int h) {
  Fl_Region R = NewRgn();
  SetRectRgn(R, x, y, x+w, y+h);
  return R;
}
inline void XDestroyRegion(Fl_Region r) {
  DisposeRgn(r);
}
extern CursHandle fl_default_cursor;
extern Handle fl_system_menu;
typedef GWorldPtr Fl_Offscreen;
typedef GWorldPtr Fl_Bitmask; // Carbon requires a 1-bit GWorld instead of a BitMap

#endif

void fl_clip_region(Fl_Region);

#  include "Window.h"

// This object contains all mac-specific stuff about a window:
// WARNING: this object is highly subject to change!
class Fl_X 
{
public:
  Window xid;              // Cocoa: FLWindow* ; Carbon: WindowRef
  Fl_Offscreen other_xid;  // pointer for offscreen bitmaps (doublebuffer)
  Fl_Window *w;            // FLTK window for 
  Fl_Region region;
  Fl_Region subRegion;     // region for this specific subwindow
  Fl_X *next;              // linked tree to support subwindows
  Fl_X *xidChildren, *xidNext; // more subwindow tree
  int wait_for_expose;
#ifdef __APPLE_COCOA__
  void *cursor;			  // is really NSCursor*
#else
  CursHandle cursor;
#endif
  static Fl_X* first;
  static Fl_X* i(const Fl_Window* w) {return w->i;}
  static int fake_X_wm(const Fl_Window*,int&,int&,int&,int&,int&);
  static void make(Fl_Window*);
  void flush();
  // Quartz additions:
  CGContextRef gc;                 // graphics context (NULL when using QD)
  static void q_fill_context();    // fill a Quartz context with current FLTK state
  static void q_clear_clipping();  // remove all clipping from a Quartz context
  static void q_release_context(Fl_X *x=0); // free all resources associated with fl_gc
  static void q_begin_image(CGRect&, int x, int y, int w, int h);
  static void q_end_image();
};

#ifdef __APPLE_COCOA__
extern void MacDestroyWindow(Fl_Window*,void *);
extern void MacMapWindow(Fl_Window*,void *);
extern void MacUnmapWindow(Fl_Window*,void *);
extern WindowRef MACwindowRef(Fl_Window *w);
extern Fl_Region MacRectRegionIntersect(Fl_Region current, int x,int y,int w, int h);
extern void MacCollapseWindow(Window w);
extern void fl_mac_set_about( Fl_Callback *cb, void *user_data, int shortcut = 0);
#else
extern void MacDestroyWindow(Fl_Window*,WindowPtr);
extern void MacMapWindow(Fl_Window*,WindowPtr);
extern void MacUnmapWindow(Fl_Window*,WindowPtr);
#endif

extern int MacUnlinkWindow(Fl_X*,Fl_X*start=0L);
extern void fl_open_callback(void (*cb)(const char *));

inline Window fl_xid(const Fl_Window*w) 
{
  return Fl_X::i(w)->xid;
}

extern struct Fl_XMap {
  RGBColor rgb;
  ulong pen;
} *fl_current_xmap;

extern FL_EXPORT void *fl_display;
extern FL_EXPORT Window fl_window;
extern FL_EXPORT CGContextRef fl_gc;
extern FL_EXPORT class Fl_Sys_Menu_Bar *fl_sys_menu_bar;


extern Fl_Offscreen fl_create_offscreen(int w, int h);
extern void fl_copy_offscreen(int x,int y,int w,int h, Fl_Offscreen gWorld, int srcx,int srcy);
extern void fl_delete_offscreen(Fl_Offscreen gWorld);
extern void fl_begin_offscreen(Fl_Offscreen gWorld);
extern void fl_end_offscreen();


extern FL_EXPORT Fl_Bitmask fl_create_bitmask(int w, int h, const uchar *data);
extern FL_EXPORT Fl_Bitmask fl_create_alphamask(int w, int h, int d, int ld, const uchar *data);
extern FL_EXPORT void fl_delete_bitmask(Fl_Bitmask bm);

extern void fl_open_display();

// Register a function for opening files via the finder...
extern void fl_open_callback(void (*cb)(const char *));

extern FL_EXPORT int fl_parse_color(const char* p, uchar& r, uchar& g, uchar& b);
#endif // FL_DOXYGEN
//
// End of "$Id: mac.H 7035 2010-01-29 21:16:20Z manolo $".
//


/* suggested twin class
// This is the Twin Class to fltk::osx
class mac : public fltk::osx {
public:
  mac(int x, int t, int w, int h, const char *label=0)
  : fltk::osx(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: mac.H 7035 2010-01-29 21:16:20Z manolo $"
//
// Mac header file for the Fast Light Tool Kit (FLTK).
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

// Do not directly include this file, instead use <FL/x.H>.  It will
// include this file if "__APPLE__" is defined.  This is to encourage
// portability of even the system-specific code...
#ifndef FL_DOXYGEN

#if !defined(Fl_X_H)
#  error "Never use <FL/mac.H> directly; include <FL/x.H> instead."
#endif // !Fl_X_H

// Standard MacOS Carbon API includes...
#include <Carbon/Carbon.h>
#include <config.h>

#ifdef __APPLE_COCOA__
#ifndef MAC_OS_X_VERSION_10_3
#define MAC_OS_X_VERSION_10_3 1030
#endif
#ifndef MAC_OS_X_VERSION_10_4
#define MAC_OS_X_VERSION_10_4 1040
#endif
#ifndef MAC_OS_X_VERSION_10_5
#define MAC_OS_X_VERSION_10_5 1050
#endif
#ifndef MAC_OS_X_VERSION_10_6
#define MAC_OS_X_VERSION_10_6 1060
#endif
#ifndef MAC_OS_X_VERSION_MAX_ALLOWED
#define MAC_OS_X_VERSION_MAX_ALLOWED MAC_OS_X_VERSION_10_3
#endif
#endif // __APPLE_COCOA__

#ifndef CGFLOAT_DEFINED //appears with 10.5 in CGBase.h
#if defined(__LP64__) && __LP64__
typedef double CGFloat;
#else
typedef float CGFloat;
#endif
#endif // CGFLOAT_DEFINED


// Now make some fixes to the headers...
#undef check			// Dunno where this comes from...

// Some random X equivalents
struct XPoint { int x, y; };
struct XRectangle {int x, y, width, height;};

#ifdef __APPLE_COCOA__
// necessary so a CGRect matches exactly what is denoted x,y,w,h for clipping purposes
#define FL_CGRECTMAKE_COCOA(x,y,w,h)  CGRectMake(x, y, w > 0 ? w - 0.9 : 0, h > 0 ? h - 0.9 : 0)

typedef void *Window; // this is really a pter to the subclass FLWindow of NSWindow
typedef struct flCocoaRegion {
  int count;
  CGRect *rects;
} *Fl_Region;  // a region is the union of a series of rectangles
inline Fl_Region XRectangleRegion(int x, int y, int w, int h) {
  Fl_Region R = (Fl_Region)malloc(sizeof(*R));
  R->count = 1;
  R->rects = (CGRect *)malloc(sizeof(CGRect));
  *(R->rects) = FL_CGRECTMAKE_COCOA(x, y, w, h);
  return R;
}
inline void XDestroyRegion(Fl_Region r) {
  if(r) {
	free(r->rects);
	free(r);
	}
}
extern void *fl_default_cursor;
extern void *fl_system_menu;
typedef CGContextRef Fl_Offscreen;
typedef CGImageRef Fl_Bitmask;

#else

typedef WindowRef Window;
typedef RgnHandle Fl_Region;
inline Fl_Region XRectangleRegion(int x, int y, int w, int h) {
  Fl_Region R = NewRgn();
  SetRectRgn(R, x, y, x+w, y+h);
  return R;
}
inline void XDestroyRegion(Fl_Region r) {
  DisposeRgn(r);
}
extern CursHandle fl_default_cursor;
extern Handle fl_system_menu;
typedef GWorldPtr Fl_Offscreen;
typedef GWorldPtr Fl_Bitmask; // Carbon requires a 1-bit GWorld instead of a BitMap

#endif

void fl_clip_region(Fl_Region);

#  include "Fl_Window.H"

// This object contains all mac-specific stuff about a window:
// WARNING: this object is highly subject to change!
class Fl_X 
{
public:
  Window xid;              // Cocoa: FLWindow* ; Carbon: WindowRef
  Fl_Offscreen other_xid;  // pointer for offscreen bitmaps (doublebuffer)
  Fl_Window *w;            // FLTK window for 
  Fl_Region region;
  Fl_Region subRegion;     // region for this specific subwindow
  Fl_X *next;              // linked tree to support subwindows
  Fl_X *xidChildren, *xidNext; // more subwindow tree
  int wait_for_expose;
#ifdef __APPLE_COCOA__
  void *cursor;			  // is really NSCursor*
#else
  CursHandle cursor;
#endif
  static Fl_X* first;
  static Fl_X* i(const Fl_Window* w) {return w->i;}
  static int fake_X_wm(const Fl_Window*,int&,int&,int&,int&,int&);
  static void make(Fl_Window*);
  void flush();
  // Quartz additions:
  CGContextRef gc;                 // graphics context (NULL when using QD)
  static void q_fill_context();    // fill a Quartz context with current FLTK state
  static void q_clear_clipping();  // remove all clipping from a Quartz context
  static void q_release_context(Fl_X *x=0); // free all resources associated with fl_gc
  static void q_begin_image(CGRect&, int x, int y, int w, int h);
  static void q_end_image();
};

#ifdef __APPLE_COCOA__
extern void MacDestroyWindow(Fl_Window*,void *);
extern void MacMapWindow(Fl_Window*,void *);
extern void MacUnmapWindow(Fl_Window*,void *);
extern WindowRef MACwindowRef(Fl_Window *w);
extern Fl_Region MacRectRegionIntersect(Fl_Region current, int x,int y,int w, int h);
extern void MacCollapseWindow(Window w);
extern void fl_mac_set_about( Fl_Callback *cb, void *user_data, int shortcut = 0);
#else
extern void MacDestroyWindow(Fl_Window*,WindowPtr);
extern void MacMapWindow(Fl_Window*,WindowPtr);
extern void MacUnmapWindow(Fl_Window*,WindowPtr);
#endif

extern int MacUnlinkWindow(Fl_X*,Fl_X*start=0L);
extern void fl_open_callback(void (*cb)(const char *));

inline Window fl_xid(const Fl_Window*w) 
{
  return Fl_X::i(w)->xid;
}

extern struct Fl_XMap {
  RGBColor rgb;
  ulong pen;
} *fl_current_xmap;

extern FL_EXPORT void *fl_display;
extern FL_EXPORT Window fl_window;
extern FL_EXPORT CGContextRef fl_gc;
extern FL_EXPORT class Fl_Sys_Menu_Bar *fl_sys_menu_bar;


extern Fl_Offscreen fl_create_offscreen(int w, int h);
extern void fl_copy_offscreen(int x,int y,int w,int h, Fl_Offscreen gWorld, int srcx,int srcy);
extern void fl_delete_offscreen(Fl_Offscreen gWorld);
extern void fl_begin_offscreen(Fl_Offscreen gWorld);
extern void fl_end_offscreen();


extern FL_EXPORT Fl_Bitmask fl_create_bitmask(int w, int h, const uchar *data);
extern FL_EXPORT Fl_Bitmask fl_create_alphamask(int w, int h, int d, int ld, const uchar *data);
extern FL_EXPORT void fl_delete_bitmask(Fl_Bitmask bm);

extern void fl_open_display();

// Register a function for opening files via the finder...
extern void fl_open_callback(void (*cb)(const char *));

extern FL_EXPORT int fl_parse_color(const char* p, uchar& r, uchar& g, uchar& b);
#endif // FL_DOXYGEN
//
// End of "$Id: mac.H 7035 2010-01-29 21:16:20Z manolo $".
//

#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
// "$Id: osx.h 6233 2008-09-14 07:54:06Z spitzak $"
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

Declarations of FLTK symbols and interfaces that only exist if FLTK is
compiled on Windows. It is recommended you avoid using this header
file, and that you segregate code requiring it to it's own source
file.

FLTK is currently using the Carbon interface, and this includes
the <Carbon/Carbon.h> header file. A macro is used to rename the
Carbon "Style" as "XStyle" to avoid conflicts with FLTK. (all
drawing is using Quartz, however!)

Many of the functions have the same name and purpose as ones defined
in x11.h, just with different return types. Due to how Doxygen works,
the X version of these is described here.
*/

#ifndef fltk_osx_h
#define fltk_osx_h

# ifndef DOXYGEN
// Standard MacOS Carbon API includes...
#  define Style XStyle
#  include <Carbon/Carbon.h>
#  undef Style

// Now make some fixes to the headers...
#  undef check			// Dunno where this comes from...
# endif

# include "draw.h"

////////////////////////////////////////////////////////////////

namespace fltk {

/// \name fltk/osx.h
//@{

////////////////////////////////////////////////////////////////
// constant information about the display:

//extern FL_API void    *qdisplay;
extern FL_API void	open_display();
extern FL_API void	close_display();
extern FL_API WindowPtr  quartz_window;
extern FL_API CGContextRef quartz_gc;
extern FL_API Handle    system_menu;
extern FL_API class     SystemMenuBar *system_menu_bar;

////////////////////////////////////////////////////////////////
// event handling:

// we want some way to access last message from system

// Register a function to call when user opens a file in finder:
extern void open_callback(void (*cb)(const char* name));

////////////////////////////////////////////////////////////////
// drawing functions:

extern FL_API void	clip_region(RgnHandle);
extern FL_API RgnHandle	clip_region();
extern FL_API void	draw_into(CGContextRef xid, int w, int h);
extern FL_API void	stop_drawing(CGImageRef xid);
# define HFONT const char* // points at name of font!
extern FL_API HFONT	xfont();

extern FL_API void clear_quartz_clipping();
extern FL_API void begin_quartz_image(CGRect&, const Rectangle&);
extern FL_API void end_quartz_image();

////////////////////////////////////////////////////////////////
# ifdef fltk_Window_h // only include this if <fltk/Window.h> was included

// When fltk tells X about a window, one of these objects is created.
// Warning: this object is highly subject to change!  It's definition
// is only here so that fltk::xid(Window) can be declared inline:

class FL_API CreatedWindow {
public:
  WindowPtr xid; // used by main windows
  Window* window;
  RgnHandle region; // damage region
  void expose(const Rectangle&);
  CreatedWindow* next;
  RgnHandle subRegion; // region which clips out children
  CreatedWindow *children, *brother;
  bool wait_for_expose;
  bool need_new_subRegion;
  bool overlay;
  static CreatedWindow* first;
  static CreatedWindow* find(const Window* window) {return window->i;}
  static int borders(const Window* w, int& dx, int& dy, int& dw, int& dh);
  // Quartz additions:
  CGContextRef gc;
};

extern FL_API void fill_quartz_context();
extern FL_API void release_quartz_context(CreatedWindow *x=0);

// convert xid <-> Window:
//inline WindowPtr xid(const Window*w) {return CreatedWindow::find(w)->xid;}
WindowPtr xid(const Window*);
Window* find(WindowPtr xid);

extern CursPtr default_cursor;
extern CursPtr current_cursor;
extern const Widget* cursor_for;

# endif //Fl_Window_H

//@}

}

# if USE_CAIRO
#  include <fltk/fltk_cairo.h>
#  include <cairo-quartz.h>
# else
   typedef struct _cairo cairo_t;
# endif

#endif

// End of "$Id: osx.h 6233 2008-09-14 07:54:06Z spitzak $".
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
