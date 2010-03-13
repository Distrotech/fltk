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
// "$Id: win32.H 6614 2009-01-01 16:11:32Z matt $"
//
// WIN32 header file for the Fast Light Tool Kit (FLTK).
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
// include this file if WIN32 is defined.  This is to encourage
// portability of even the system-specific code...

#ifndef FL_DOXYGEN
#ifndef Fl_X_H
#  error "Never use <FL/win32.H> directly; include <FL/x.H> instead."
#endif // !Fl_X_H

#include <windows.h>
// In some of the distributions, the gcc header files are missing some stuff:
#ifndef LPMINMAXINFO
#define LPMINMAXINFO MINMAXINFO*
#endif
#ifndef VK_LWIN
#define VK_LWIN 0x5B
#define VK_RWIN 0x5C
#define VK_APPS 0x5D
#endif

// some random X equivalents
typedef HWND Window;
typedef POINT XPoint;
struct XRectangle {int x, y, width, height;};
typedef HRGN Fl_Region;
FL_EXPORT void fl_clip_region(Fl_Region);
inline Fl_Region XRectangleRegion(int x, int y, int w, int h) {
    return CreateRectRgn(x,y,x+w,y+h);
}
inline void XDestroyRegion(Fl_Region r) {DeleteObject(r);}
inline void XClipBox(Fl_Region r,XRectangle* rect) {
    RECT win_rect; GetRgnBox(r,&win_rect);
    rect->x=win_rect.left;
    rect->y=win_rect.top;
    rect->width=win_rect.right-win_rect.left;
    rect->height=win_rect.bottom-win_rect.top;
}
#define XDestroyWindow(a,b) DestroyWindow(b)
#define XMapWindow(a,b) ShowWindow(b, SW_RESTORE)
#define XUnmapWindow(a,b) ShowWindow(b, SW_HIDE)

#include "Fl_Window.H"
// this object contains all win32-specific stuff about a window:
// Warning: this object is highly subject to change!
class FL_EXPORT Fl_X {
public:
  // member variables - add new variables only at the end of this block
  Window xid;
  HBITMAP other_xid; // for double-buffered windows
  Fl_Window* w;
  Fl_Region region;
  Fl_X *next;
  int wait_for_expose;
  HDC private_dc; // used for OpenGL
  HCURSOR cursor;
  HDC saved_hdc;  // saves the handle of the DC currently loaded
  // static variables, static functions and member functions
  static Fl_X* first;
  static Fl_X* i(const Fl_Window* w) {return w->i;}
  static int fake_X_wm(const Fl_Window* w,int &X, int &Y,
		                 int &bt,int &bx,int &by);
  void setwindow(Fl_Window* wi) {w=wi; wi->i=this;}
  void flush() {w->flush();}
  void set_minmax(LPMINMAXINFO minmax);
  void mapraise();
  static Fl_X* make(Fl_Window*);
};
extern FL_EXPORT HCURSOR fl_default_cursor;
extern FL_EXPORT UINT fl_wake_msg;
inline Window fl_xid(const Fl_Window*w) {Fl_X *temp = Fl_X::i(w); return temp ? temp->xid : 0;}
FL_EXPORT Fl_Window* fl_find(Window xid);
extern FL_EXPORT char fl_override_redirect; // hack into Fl_Window::make_xid()
extern FL_EXPORT int fl_background_pixel;  // hack into Fl_Window::make_xid()

// most recent fl_color() or fl_rgbcolor() points at one of these:
extern FL_EXPORT struct Fl_XMap {
  COLORREF rgb;	// this should be the type the RGB() macro returns
  HPEN pen;	// pen, 0 if none created yet
  int brush;	// ref to solid brush, 0 if none created yet
} *fl_current_xmap;
inline COLORREF fl_RGB() {return fl_current_xmap->rgb;}
inline HPEN fl_pen() {return fl_current_xmap->pen;}
FL_EXPORT HBRUSH fl_brush(); // allocates a brush if necessary
FL_EXPORT HBRUSH fl_brush_action(int); // now does the real work

extern FL_EXPORT HINSTANCE fl_display;
extern FL_EXPORT Window fl_window;
extern FL_EXPORT HDC fl_gc;
extern FL_EXPORT HPALETTE fl_palette; // non-zero only on 8-bit displays!
extern FL_EXPORT HDC fl_GetDC(Window);
extern FL_EXPORT MSG fl_msg;
extern FL_EXPORT void fl_release_dc(HWND w, HDC dc);
extern FL_EXPORT void fl_save_dc( HWND w, HDC dc);

// off-screen pixmaps: create, destroy, draw into, copy to window
typedef HBITMAP Fl_Offscreen;
#define fl_create_offscreen(w, h) CreateCompatibleBitmap(fl_gc, w, h)

extern FL_EXPORT HDC fl_makeDC(HBITMAP);

# define fl_begin_offscreen(b) \
   HDC _sgc=fl_gc; Window _sw=fl_window; \
   fl_gc=fl_makeDC(b); int _savedc = SaveDC(fl_gc); fl_window=(HWND)b; fl_push_no_clip()

# define fl_end_offscreen() \
   fl_pop_clip(); RestoreDC(fl_gc, _savedc); DeleteDC(fl_gc); fl_window=_sw; fl_gc = _sgc

FL_EXPORT void fl_copy_offscreen(int x,int y,int w,int h,HBITMAP pixmap,int srcx,int srcy);
FL_EXPORT void fl_copy_offscreen_with_alpha(int x,int y,int w,int h,HBITMAP pixmap,int srcx,int srcy);
#define fl_delete_offscreen(bitmap) DeleteObject(bitmap);

// Bitmap masks
typedef HBITMAP Fl_Bitmask;

extern FL_EXPORT Fl_Bitmask fl_create_bitmask(int w, int h, const uchar *data);
extern FL_EXPORT Fl_Bitmask fl_create_alphamask(int w, int h, int d, int ld, const uchar *data);
extern FL_EXPORT void fl_delete_bitmask(Fl_Bitmask bm);

// Dummy function to register a function for opening files via the window manager...
inline void fl_open_callback(void (*)(const char *)) {}

extern FL_EXPORT int fl_parse_color(const char* p, uchar& r, uchar& g, uchar& b);
#endif // FL_DOXYGEN
//
// End of "$Id: win32.H 6614 2009-01-01 16:11:32Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::win32
class win32 : public fltk::win32 {
public:
  win32(int x, int t, int w, int h, const char *label=0)
  : fltk::win32(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: win32.H 6614 2009-01-01 16:11:32Z matt $"
//
// WIN32 header file for the Fast Light Tool Kit (FLTK).
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
// include this file if WIN32 is defined.  This is to encourage
// portability of even the system-specific code...

#ifndef FL_DOXYGEN
#ifndef Fl_X_H
#  error "Never use <FL/win32.H> directly; include <FL/x.H> instead."
#endif // !Fl_X_H

#include <windows.h>
// In some of the distributions, the gcc header files are missing some stuff:
#ifndef LPMINMAXINFO
#define LPMINMAXINFO MINMAXINFO*
#endif
#ifndef VK_LWIN
#define VK_LWIN 0x5B
#define VK_RWIN 0x5C
#define VK_APPS 0x5D
#endif

// some random X equivalents
typedef HWND Window;
typedef POINT XPoint;
struct XRectangle {int x, y, width, height;};
typedef HRGN Fl_Region;
FL_EXPORT void fl_clip_region(Fl_Region);
inline Fl_Region XRectangleRegion(int x, int y, int w, int h) {
    return CreateRectRgn(x,y,x+w,y+h);
}
inline void XDestroyRegion(Fl_Region r) {DeleteObject(r);}
inline void XClipBox(Fl_Region r,XRectangle* rect) {
    RECT win_rect; GetRgnBox(r,&win_rect);
    rect->x=win_rect.left;
    rect->y=win_rect.top;
    rect->width=win_rect.right-win_rect.left;
    rect->height=win_rect.bottom-win_rect.top;
}
#define XDestroyWindow(a,b) DestroyWindow(b)
#define XMapWindow(a,b) ShowWindow(b, SW_RESTORE)
#define XUnmapWindow(a,b) ShowWindow(b, SW_HIDE)

#include "Fl_Window.H"
// this object contains all win32-specific stuff about a window:
// Warning: this object is highly subject to change!
class FL_EXPORT Fl_X {
public:
  // member variables - add new variables only at the end of this block
  Window xid;
  HBITMAP other_xid; // for double-buffered windows
  Fl_Window* w;
  Fl_Region region;
  Fl_X *next;
  int wait_for_expose;
  HDC private_dc; // used for OpenGL
  HCURSOR cursor;
  HDC saved_hdc;  // saves the handle of the DC currently loaded
  // static variables, static functions and member functions
  static Fl_X* first;
  static Fl_X* i(const Fl_Window* w) {return w->i;}
  static int fake_X_wm(const Fl_Window* w,int &X, int &Y,
		                 int &bt,int &bx,int &by);
  void setwindow(Fl_Window* wi) {w=wi; wi->i=this;}
  void flush() {w->flush();}
  void set_minmax(LPMINMAXINFO minmax);
  void mapraise();
  static Fl_X* make(Fl_Window*);
};
extern FL_EXPORT HCURSOR fl_default_cursor;
extern FL_EXPORT UINT fl_wake_msg;
inline Window fl_xid(const Fl_Window*w) {Fl_X *temp = Fl_X::i(w); return temp ? temp->xid : 0;}
FL_EXPORT Fl_Window* fl_find(Window xid);
extern FL_EXPORT char fl_override_redirect; // hack into Fl_Window::make_xid()
extern FL_EXPORT int fl_background_pixel;  // hack into Fl_Window::make_xid()

// most recent fl_color() or fl_rgbcolor() points at one of these:
extern FL_EXPORT struct Fl_XMap {
  COLORREF rgb;	// this should be the type the RGB() macro returns
  HPEN pen;	// pen, 0 if none created yet
  int brush;	// ref to solid brush, 0 if none created yet
} *fl_current_xmap;
inline COLORREF fl_RGB() {return fl_current_xmap->rgb;}
inline HPEN fl_pen() {return fl_current_xmap->pen;}
FL_EXPORT HBRUSH fl_brush(); // allocates a brush if necessary
FL_EXPORT HBRUSH fl_brush_action(int); // now does the real work

extern FL_EXPORT HINSTANCE fl_display;
extern FL_EXPORT Window fl_window;
extern FL_EXPORT HDC fl_gc;
extern FL_EXPORT HPALETTE fl_palette; // non-zero only on 8-bit displays!
extern FL_EXPORT HDC fl_GetDC(Window);
extern FL_EXPORT MSG fl_msg;
extern FL_EXPORT void fl_release_dc(HWND w, HDC dc);
extern FL_EXPORT void fl_save_dc( HWND w, HDC dc);

// off-screen pixmaps: create, destroy, draw into, copy to window
typedef HBITMAP Fl_Offscreen;
#define fl_create_offscreen(w, h) CreateCompatibleBitmap(fl_gc, w, h)

extern FL_EXPORT HDC fl_makeDC(HBITMAP);

# define fl_begin_offscreen(b) \
   HDC _sgc=fl_gc; Window _sw=fl_window; \
   fl_gc=fl_makeDC(b); int _savedc = SaveDC(fl_gc); fl_window=(HWND)b; fl_push_no_clip()

# define fl_end_offscreen() \
   fl_pop_clip(); RestoreDC(fl_gc, _savedc); DeleteDC(fl_gc); fl_window=_sw; fl_gc = _sgc

FL_EXPORT void fl_copy_offscreen(int x,int y,int w,int h,HBITMAP pixmap,int srcx,int srcy);
FL_EXPORT void fl_copy_offscreen_with_alpha(int x,int y,int w,int h,HBITMAP pixmap,int srcx,int srcy);
#define fl_delete_offscreen(bitmap) DeleteObject(bitmap);

// Bitmap masks
typedef HBITMAP Fl_Bitmask;

extern FL_EXPORT Fl_Bitmask fl_create_bitmask(int w, int h, const uchar *data);
extern FL_EXPORT Fl_Bitmask fl_create_alphamask(int w, int h, int d, int ld, const uchar *data);
extern FL_EXPORT void fl_delete_bitmask(Fl_Bitmask bm);

// Dummy function to register a function for opening files via the window manager...
inline void fl_open_callback(void (*)(const char *)) {}

extern FL_EXPORT int fl_parse_color(const char* p, uchar& r, uchar& g, uchar& b);
#endif // FL_DOXYGEN
//
// End of "$Id: win32.H 6614 2009-01-01 16:11:32Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
// "$Id: win32.h 6233 2008-09-14 07:54:06Z spitzak $"
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

This header includes the horrible <windows.h> header file, followed
by a large list of undef's to get rid of name conflicts. It is recommended
you use this if you need any windows functions rather than including
that file directly.

You can probably combine FLTK with other libraries that make their own
WIN32 window classes.  The easiest way is to call fltk::wait(), it
will call DispatchMessage() for all messages to the other windows. If
your other library insists on reading all the events, it will still
work (as long as it calls DispatchMessage()), but you will
have to arrange for the function fltk::flush() to be called regularily
so that widgets are updated. Timeouts, the idle function, and file
descriptor callbacks will not work in this case.

Many of the functions have the same name and purpose as ones defined
in x11.h, just with different return types. Due to how Doxygen works,
the X version of these is described here.
*/

#if defined(_MSC_VER)
# pragma once /* speeds up compilation */
#endif

#ifndef fltk_win32_h
#define fltk_win32_h

#ifndef DOXYGEN

#ifndef WIN32_LEAN_AND_MEAN
# define WIN32_LEAN_AND_MEAN
#endif

# include <windows.h>
# include <winuser.h>
# undef DELETE
# undef ERROR
# undef IN
# undef OPAQUE
# undef OUT
# undef POINT
//#undef far
# undef max
# undef min
//#undef near

#if USE_CAIRO
# include <fltk/fltk_cairo.h>
# include <cairo-win32.h>
#endif

extern "C" {

// Function pointer declarations
// WAS: I suspect these can be put into win32/run.cxx!

typedef HWND (WINAPI *pfCreateWindowExW)(DWORD dwExStyle, LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam);
typedef HMODULE (WINAPI *pfLoadLibraryW)(LPCWSTR lpFileName);
typedef BOOL (WINAPI *pfPeekMessage)(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);
typedef BOOL (WINAPI *pfGetMessage)(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax);
typedef LRESULT (WINAPI *pfDispatchMessage)(const MSG *lpmsg);
typedef BOOL (WINAPI *pfSetWindowTextW)(HWND hWnd, LPCWSTR lpString);
typedef LRESULT (WINAPI *pfDefWindowProc)(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
typedef BOOL (WINAPI *pfPostMessage)(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
typedef int (WINAPI *pfMessageBoxW)(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType);

typedef HFONT (WINAPI *pfCreateFontIndirectW)(CONST LOGFONTW *);
typedef BOOL (WINAPI *pfGetTextMetricsW)(HDC, LPTEXTMETRICW);

extern pfCreateWindowExW __CreateWindowExW;
extern pfLoadLibraryW	 __LoadLibraryW;
extern pfPeekMessage	 __PeekMessage;
extern pfGetMessage	 __GetMessage;
extern pfDispatchMessage __DispatchMessage;
extern pfSetWindowTextW	 __SetWindowTextW;
extern pfDefWindowProc	 __DefWindowProc;
extern pfPostMessage	 __PostMessage;
extern pfMessageBoxW	 __MessageBoxW;

extern pfCreateFontIndirectW __CreateFontIndirectW;
extern pfGetTextMetricsW     __GetTextMetricsW;

}; /* extern "C" */
#endif // !DOXYGEN

#include "draw.h"

namespace fltk {

/// \name fltk/win32.h
//@{

////////////////////////////////////////////////////////////////
// constant information about the display:

extern FL_API void	open_display();
extern FL_API void	close_display();
extern FL_API HINSTANCE	xdisplay;
extern FL_API HPALETTE	xpalette; // non-zero only on 8-bit displays!

////////////////////////////////////////////////////////////////
// event handling:

extern FL_API MSG msg;

////////////////////////////////////////////////////////////////
// drawing functions:

extern FL_API HDC	dc;
extern FL_API HDC	getDC();
extern FL_API HFONT	xfont();
extern FL_API TEXTMETRICW* textmetric();
extern FL_API COLORREF	current_xpixel;
extern FL_API COLORREF	xpixel(Color i);
extern FL_API HPEN	setpen();
extern FL_API HBRUSH	setbrush();
extern FL_API void	clip_region(HRGN);
extern FL_API HRGN	clip_region();

extern FL_API void	draw_into(HBITMAP, int w, int h);
extern FL_API void	stop_drawing(HBITMAP);
extern FL_API void	stop_drawing(HWND);

////////////////////////////////////////////////////////////////
#ifdef fltk_Window_h // only include this if <fltk/Fl_Window.h> was included

// When fltk tells X about a window, one of these objects is created.
// Warning: this object is highly subject to change!  It's definition
// is only here so that fl_xid can be declared inline:

class FL_API CreatedWindow {
public:
  HWND xid;
  HDC dc;
  HBITMAP backbuffer;
  HDC bdc;
  Window* window;
  HRGN region;
  void expose(const Rectangle&);
  CreatedWindow* next;
  bool wait_for_expose;
  bool backbuffer_bad; // used for XDBE
  bool overlay; // true if redraw_overlay was called
  HCURSOR cursor;
  const Widget* cursor_for;
  static CreatedWindow* first;
  static CreatedWindow* find(const Window* window) {return window->i;}
  void set_minmax(LPMINMAXINFO minmax);
  static void create(Window*);
};

// convert xid <-> Window:
inline HWND xid(const Window*w) {return CreatedWindow::find(w)->xid;}
Window* find(HWND xid);

extern FL_API HCURSOR default_cursor;

#endif // Fl_Window_H

//@}

}

#endif

//
// End of "$Id: win32.h 6233 2008-09-14 07:54:06Z spitzak $".
//
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
