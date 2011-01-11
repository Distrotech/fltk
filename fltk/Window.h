// "$Id: Window.h 6150 2008-08-04 22:53:30Z spitzak $"
//
// Window widget. This must be the outermost group. You can also put
// them inside other widgets to use the system's window hierarchy.
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

#ifndef fltk2_Window_h
#define fltk2_Window_h

#include <fltk3/Window.h>
#include "Group.h"

namespace fltk {

#if 0 // TODO: FLTK123
  
// value for x,y to indicate window system places window
const int USEDEFAULT = ((int)0x80000000); // same as Win32 value

class CreatedWindow;
class Monitor;

#endif // TODO: FLTK123

class FL_API Window : public Group {
public:

  Window(int W, int H, const char *l = 0) {
    fltk3::Group *curr = fltk3::Group::current();
    _p = new fltk3::Window(W, H, l);
    _p->wrapper(this);
    fltk3::Group::current(curr);
  }
  Window(int X, int Y, int W, int H, const char *l = 0, bool fBegin = false) {
    fltk3::Group *curr = fltk3::Group::current();
    _p = new fltk3::Window(X, Y, W, H, l);
    _p->wrapper(this);
    // FIXME: this should not cause a begin in FLTK3 for compatibility
    if (fBegin) 
      begin();
    else
      fltk3::Group::current(curr);
  }
  void show(int argc, char **argv) {
    ((fltk3::Window*)_p)->show(argc, argv); 
  }
  void fullscreen_off(int x, int y, int w, int h) {
    ((fltk3::Window*)_p)->fullscreen_off(x, y, w, h); 
  }
  void iconize() {
    ((fltk3::Window*)_p)->iconize(); 
  }
  void fullscreen() {
    ((fltk3::Window*)_p)->fullscreen(); 
  }
  const char* label() const {
    return ((fltk3::Window*)_p)->label(); 
  }
  const char* iconlabel() {
    return ((fltk3::Window*)_p)->iconlabel(); 
  }
  void label(const char *p) {
    ((fltk3::Window*)_p)->label(p); 
  }
  void iconlabel(const char *il) {
    ((fltk3::Window*)_p)->iconlabel(il); 
  }
  void label(const char* label, const char* iconlabel) {
    ((fltk3::Window*)_p)->label(label, iconlabel); 
  }
  void copy_label(const char* c) {
    ((fltk3::Window*)_p)->copy_label(c); 
  }
  const void* icon() const {
    return ((fltk3::Window*)_p)->icon(); 
  }
  void icon(const void * ic) {
    ((fltk3::Window*)_p)->icon(ic); 
  }
  static const char* xclass() {
    return fltk3::Window::default_xclass(); 
  }
  static void xclass(const char* v) {
    fltk3::Window::default_xclass(v); 
  }
  
#if 0 // TODO: FLTK123
  void maximize() {
    ((fltk3::Window*)_p)->maximize(); 
  }
  virtual ~Window();  
  void border(bool set)	{set ? clear_flag(NOBORDER) : set_flag(NOBORDER);}
  void clear_border()    {set_flag(NOBORDER);} 
  bool border() const	{return !flag(NOBORDER);}
  void set_override()	{set_flag(NOBORDER|OVERRIDE);}
  bool override() const {return flag(OVERRIDE); }
  const Window* child_of() const {return child_of_;}
  void child_of(const Window* w);
  void set_modal()	{set_flag(MODAL);}
  void set_non_modal()	{set_flag(NON_MODAL);}
  bool double_buffer() const {return flag(DOUBLE);}
  void set_double_buffer() {set_flag(DOUBLE);}
  void clear_double_buffer() {clear_flag(DOUBLE);}
  void free_backbuffer();
  virtual void draw_overlay();
  void redraw_overlay();
  void erase_overlay();
  void hotspot(int x, int y, bool offscreen = false);
  void hotspot(const Widget*, bool offscreen = false);
  void hotspot(const Widget& p, bool offscrn = false) {hotspot(&p,offscrn);}
  void size_range(int a, int b, int c=0, int d=0, int e=0, int f=0){ minw=(short)a; minh=(short)b; maxw=(short)c; maxh=(short)d; dw=(uchar)e; dh=(uchar)f; size_range_(); }
  bool get_size_range( int *min_w, int *min_h, int *max_w, int *max_h );
  bool shown() const {return i != 0;}
  void show();
  void show(const Window* parent);
  bool exec(const Window* parent = 0, bool grab = false);
  void make_exec_return(bool);
  void show_inside(const Window* parent);
  virtual void destroy();
  bool iconic() const;
  void fullscreen(const Monitor&);
  static void default_callback(Window*, void* v);
  virtual int handle(int);
  virtual void layout();
  void system_layout();
  virtual void flush();
  virtual void draw();
  static Window* first();
  static void first(Window*);
  Window* next();
  void borders( Rectangle *r ) const;
  static const Window* drawing_window() {return drawing_window_;}
  static const Window* drawing_window_;
  void* backbuffer() const;
protected:
  virtual void create();
#endif // TODO: FLTK123
  
};

}

#endif

//
// End of "$Id: Window.h 6150 2008-08-04 22:53:30Z spitzak $".
//
