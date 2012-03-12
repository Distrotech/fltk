//
// "$Id: osx.h 8657 2011-05-12 11:50:43Z manolo $"
//
// Mac header file for the Fast Light Tool Kit (FLTK).
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

// Do not directly include this file, instead use <fltk3/x.h>.  It will
// include this file if "__APPLE__" is defined.  This is to encourage
// portability of even the system-specific code...
#ifndef FLTK3_DOXYGEN

#if !defined(Fltk3_X_H)
#  error "Never use <fltk3/osx.h> directly; include <fltk3/x.h> instead."
#endif // !Fltk3_X_H

#ifdef __OBJC__
  @class FLWindow; // a subclass of the NSWindow Cocoa class
  typedef FLWindow *Window;
#else
  typedef class FLWindow_subclass_of_ObjectiveC_NSWindow_class *Window;
#endif // __OBJC__

#if !(defined(FL_LIBRARY) || defined(FLTK3_INTERNALS)) // this part is used when compiling an application program
#include <fltk3/Widget.h>

namespace fltk3 {
  typedef struct flCocoaRegion* Region;
}
typedef struct CGContext* CGContextRef;
typedef struct OpaquePMPrintSettings*   PMPrintSettings;
typedef struct OpaquePMPageFormat*      PMPageFormat;
typedef struct OpaquePMPrintSession*    PMPrintSession;
typedef struct CGImage* CGImageRef;
namespace fltk3 {
  typedef CGContextRef Offscreen;
  }

#else // this part must be compiled when building the FLTK libraries

// Standard MacOS C/C++ includes...
#include <ApplicationServices/ApplicationServices.h>
#undef check // because of fltk3::check()

namespace fltk3 {
  typedef CGContextRef Offscreen;
  typedef struct flCocoaRegion {
    int count;
    CGRect *rects;
  } *Region;  // a region is the union of a series of rectangles
}

#  include <fltk3/Window.h>

// Some random X equivalents
struct XPoint { int x, y; };
struct XRectangle {int x, y, width, height;};
#ifndef CGFLOAT_DEFINED //appears with 10.5 in CGBase.h
#if defined(__LP64__) && __LP64__
typedef double CGFloat;
#else
typedef float CGFloat;
#endif
#endif // CGFLOAT_DEFINED

extern CGRect fl_cgrectmake_cocoa(int x, int y, int w, int h);
inline fltk3::Region XRectangleRegion(int x, int y, int w, int h) {
  fltk3::Region R = (fltk3::Region)malloc(sizeof(*R));
  R->count = 1;
  R->rects = (CGRect *)malloc(sizeof(CGRect));
  *(R->rects) = fl_cgrectmake_cocoa(x, y, w, h);
  return R;
}
inline void XDestroyRegion(fltk3::Region r) {
  if(r) {
    free(r->rects);
    free(r);
  }
}
extern void *fl_default_cursor;

// This object contains all mac-specific stuff about a window:
// WARNING: this object is highly subject to change!
class Fl_X {
  
public:
  Window xid;              // pointer to the Cocoa window object (FLWindow*)
  fltk3::Offscreen other_xid;  // pointer for offscreen bitmaps (overlay window)
  fltk3::Window *w;            // FLTK window for 
  fltk3::Region region;
  fltk3::Region subRegion;     // region for this specific subwindow
  Fl_X *next;              // linked tree to support subwindows
  Fl_X *xidChildren, *xidNext; // more subwindow tree
  int wait_for_expose;
  void *cursor;	           // is really NSCursor*
  static Fl_X* first;
  static Fl_X* i(const fltk3::Window* w) {return w->i;}
  static int fake_X_wm(const fltk3::Window*,int&,int&,int&,int&,int&);
  static void make(fltk3::Window*);
  void flush();
  // Quartz additions:
  CGContextRef gc;                 // graphics context (NULL when using QD)
  static void q_fill_context();    // fill a Quartz context with current FLTK state
  static void q_clear_clipping();  // remove all clipping from a Quartz context
  static void q_release_context(Fl_X *x=0); // free all resources associated with fl_gc
  static void q_begin_image(CGRect&, int x, int y, int w, int h);
  static void q_end_image();
  // Cocoa additions
  void destroy(void);
  void map(void);
  void unmap(void);
  int unlink(Fl_X* start = NULL);
  void collapse(void);
  WindowRef window_ref(void);
  void set_key_window(void);
  void set_cursor(fltk3::Cursor);
  static CGImageRef CGImage_from_window_rect(fltk3::Window *win, int x, int y, int w, int h);
  static unsigned char *bitmap_from_window_rect(fltk3::Window *win, int x, int y, int w, int h, int *bytesPerPixel);
  static fltk3::Region intersect_region_and_rect(fltk3::Region current, int x,int y,int w, int h);
  static CGContextRef watch_cursor_image(void);
  static CGContextRef help_cursor_image(void);
  static CGContextRef nesw_cursor_image(void);
  static CGContextRef nwse_cursor_image(void);
  static CGContextRef none_cursor_image(void);
  static void *get_carbon_function(const char *name);
  static void screen_work_area(int &X, int &Y, int &W, int &H, int n); // compute work area of a given screen
  static unsigned short *compute_macKeyLookUp();
private:
  static void relink(fltk3::Window*, fltk3::Window*);
  bool subwindow;
};

extern Window fl_window;

#endif // FL_LIBRARY || FLTK3_INTERNALS

#ifndef MAC_OS_X_VERSION_10_4
#define MAC_OS_X_VERSION_10_4 1040
#endif
#ifndef MAC_OS_X_VERSION_10_5
#define MAC_OS_X_VERSION_10_5 1050
#endif
#ifndef MAC_OS_X_VERSION_10_6
#define MAC_OS_X_VERSION_10_6 1060
#endif

namespace fltk3 {
  typedef CGImageRef Bitmask;
  }

extern CGContextRef fl_gc;

extern Window fl_xid(const fltk3::Window*);
extern fltk3::Window* fl_find(Window xid);
namespace fltk3 {
  void clip_region(fltk3::Region);
}

extern fltk3::Bitmask fl_create_bitmask(int w, int h, const uchar *data);
extern fltk3::Bitmask fl_create_alphamask(int w, int h, int d, int ld, const uchar *data);
extern void fl_delete_bitmask(fltk3::Bitmask bm);
extern fltk3::Offscreen fl_create_offscreen(int w, int h);
//extern void fltk3::copy_offscreen(int x,int y,int w,int h, fltk3::Offscreen gWorld, int srcx,int srcy);
extern void fl_delete_offscreen(fltk3::Offscreen gWorld);
extern void fl_begin_offscreen(fltk3::Offscreen gWorld);
extern void fl_end_offscreen();

extern int fl_parse_color(const char* p, uchar& r, uchar& g, uchar& b);
extern void fl_open_display();

#endif // FLTK3_DOXYGEN

/** \defgroup group_macosx Mac OS X-specific symbols
 Mac OS X-specific symbols declared in <fltk3/x.h> or <fltk3/gl.h>
 @{ */

/** @brief Register a function called for each file dropped onto an application icon.
 \e cb will be called with a single Unix-style file name and path.
 If multiple files were dropped, \e cb will be called multiple times.
 */
extern void fl_open_callback(void (*cb)(const char *));

extern void fl_mac_set_about( fltk3::Callback *cb, void *user_data, unsigned int shortcut = 0);

/** \brief The version number of the running Mac OS X (e.g., 100604 for 10.6.4)
 */
extern int fl_mac_os_version;

class Fl_Mac_App_Menu {
public:
  /** Localizable text for the "About xxx" application menu item */
  static const char *about;
  /** Localizable text for the "Print Front Window" application menu item.
   This menu item won't be displayed if Fl_Mac_App_Menu::print 
   is set to an empty string.
   */
  static const char *print;
  /** Localizable text for the "Services" application menu item */
  static const char *services;
  /** Localizable text for the "Hide xxx" application menu item */
  static const char *hide;
  /** Localizable text for the "Hide Others" application menu item */
  static const char *hide_others;
  /** Localizable text for the "Show All" application menu item */
  static const char *show;
  /** Localizable text for the "Quit xxx" application menu item */
  static const char *quit;
};

/** @} */

//
// End of "$Id: osx.h 8657 2011-05-12 11:50:43Z manolo $".
//

