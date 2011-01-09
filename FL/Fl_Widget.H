//
// "$Id$"
//
// Widget header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2010 by Bill Spitzak and others.
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
   Fl_Widget, Fl_Label classes . */

#ifndef FLTK1_Widget_H
#define FLTK1_Widget_H

#include <fltk3/Wrapper.h>
#include <fltk3/Widget.h>
#include "Enumerations.H"

#ifdef _WIN64
#ifdef __GNUC__
#include <stdint.h>
#else
#include <stddef.h>  // M$VC
#endif
typedef intptr_t fl_intptr_t;
typedef uintptr_t fl_uintptr_t;
#else
typedef long fl_intptr_t;
typedef unsigned long fl_uintptr_t;
#endif

class Fl_Widget;
class Fl_Window;
class Fl_Group;
class Fl_Image;

#if 0  // TODO: FLTK123


/** Default callback type definition for all fltk widgets (by far the most used) */
typedef void (Fl_Callback )(Fl_Widget*, void*);
/** Default callback type pointer definition for all fltk widgets */
typedef Fl_Callback* Fl_Callback_p; // needed for BORLAND
/** One parameter callback type definition passing only the widget */
typedef void (Fl_Callback0)(Fl_Widget*);
/** Callback type definition passing the widget and a long data value */
typedef void (Fl_Callback1)(Fl_Widget*, long);

/** This struct stores all information for a text or mixed graphics label.

    \todo For FLTK 1.3, the Fl_Label type will become a widget by itself. That way
          we will be avoiding a lot of code duplication by handling labels in 
          a similar fashion to widgets containing text. We also provide an easy
          interface for very complex labels, containing html or vector graphics.
 */
struct FL_EXPORT Fl_Label {
  /** label text */
  const char* value;
  /** optional image for an active label */
  Fl_Image* image;
  /** optional image for a deactivated label */
  Fl_Image* deimage;
  /** label font used in text */
  Fl_Font font;
  /** size of label font */
  Fl_Fontsize size;
  /** text color */
  Fl_Color color;
  /** alignment of label */
  Fl_Align align_;
  /** type of label. \see Fl_Labeltype */
  uchar type;

  /** Draws the label aligned to the given box */
  void draw(int,int,int,int, Fl_Align) const ;
  void measure(int &w, int &h) const ;
};

#endif  // TODO: FLTK123


class FL_EXPORT Fl_Widget : public fltk3::Wrapper {
  friend class Fl_Group;
  
protected:
  
  enum {
    INACTIVE        = 1<<0,
    INVISIBLE       = 1<<1,
    OUTPUT          = 1<<2,
    NOBORDER        = 1<<3,
    FORCE_POSITION  = 1<<4,
    NON_MODAL       = 1<<5,
    SHORTCUT_LABEL  = 1<<6,
    CHANGED         = 1<<7,
    OVERRIDE        = 1<<8,
    VISIBLE_FOCUS   = 1<<9,
    COPIED_LABEL    = 1<<10,
    CLIP_CHILDREN   = 1<<11,
    MENU_WINDOW     = 1<<12,
    TOOLTIP_WINDOW  = 1<<13,
    MODAL           = 1<<14,
    NO_OVERLAY      = 1<<15,
    GROUP_RELATIVE  = 1<<16,
    COPIED_TOOLTIP  = 1<<17,
    USERFLAG3       = 1<<29,
    USERFLAG2       = 1<<30,
    USERFLAG1       = 1<<31
  };
  
  Fl_Widget() {}
  
  void x(int v) { 
    ((fltk3::Widget*)_p)->x(v); 
  }
  void y(int v) { 
    ((fltk3::Widget*)_p)->y(v); 
  }
  void w(int v) {
    ((fltk3::Widget*)_p)->w(v); 
  }
  void h(int v) { 
    ((fltk3::Widget*)_p)->h(v); 
  }
  unsigned int flags() const { 
    return ((fltk3::Widget*)_p)->flags();
  }
  void set_flag(unsigned int c) {
    ((fltk3::Widget*)_p)->set_flag(c);
  }
  void clear_flag(unsigned int c) { 
    ((fltk3::Widget*)_p)->clear_flag(c); 
  }
  void draw_box() const {
    ((fltk3::Widget*)_p)->draw_box(); 
  }
  void draw_box(Fl_Boxtype t, Fl_Color c) const { 
    ((fltk3::Widget*)_p)->draw_box((fltk3::Boxtype)t, c); 
  }
  void draw_box(Fl_Boxtype t, int x,int y,int w,int h, Fl_Color c) const { 
    ((fltk3::Widget*)_p)->draw_box((fltk3::Boxtype)t, x, y, w, h, c); 
  }
  void draw_backdrop() const { 
    ((fltk3::Widget*)_p)->draw_backdrop(); 
  }
  void draw_focus() {
    ((fltk3::Widget*)_p)->draw_focus(); 
  }
  void draw_focus(Fl_Boxtype t, int x,int y,int w,int h) const { 
    ((fltk3::Widget*)_p)->draw_focus((fltk3::Boxtype)t, x, y, w, h); 
  }
  void draw_label() const { 
    ((fltk3::Widget*)_p)->draw_label(); 
  }
  void draw_label(int x, int y, int w, int h) const {
    ((fltk3::Widget*)_p)->draw_label(x, y, w, h); 
  }
  
public:

  Fl_Widget(int x, int y, int w, int h, const char *label=0L) {
    _p = new fltk3::Widget(x, y, w, h, label);
    _p->wrapper(this);
  }
  
#if 0 // TODO: FLTK123
  virtual ~Fl_Widget() {}
  virtual void draw() {}
  virtual int handle(int event) {}
  virtual void resize(int x, int y, int w, int h) {}
  virtual void show() {}
  virtual void hide() {}
  virtual Fl_Group* as_group() {}
  virtual Fl_Window* as_window() {}
  virtual class Fl_Gl_Window* as_gl_window() {}
#endif // TODO: FLTK123
  
  Fl_Group* parent() const {
    return (Fl_Group*)( ((fltk3::Widget*)_p)->parent()->wrapper() );
  }
  void parent(Fl_Group* p) {
    ((fltk3::Widget*)_p)->parent( (fltk3::Group*)( ((Fl_Widget*)p)->_p ) );
  }
  uchar type() const {
    return ((fltk3::Widget*)_p)->type(); 
  }
  void type(uchar t) {
    ((fltk3::Widget*)_p)->type(t); 
  }
  int x() const {
    return ((fltk3::Widget*)_p)->x(); 
  }
  int y() const {
    return ((fltk3::Widget*)_p)->y(); 
  }
  int w() const {
    return ((fltk3::Widget*)_p)->w(); 
  }
  int h() const {
    return ((fltk3::Widget*)_p)->h(); 
  }
  int damage_resize(int x, int y, int w, int h) {
    return ((fltk3::Widget*)_p)->damage_resize(x, y, w, h); 
  }
  void position(int X,int Y) {
    ((fltk3::Widget*)_p)->position(X, Y);
  }
  void size(int W,int H) {
    ((fltk3::Widget*)_p)->size(W, H);
  }
  Fl_Align align() const {
    return (Fl_Align)((fltk3::Widget*)_p)->align(); 
  }
  void align(Fl_Align alignment) {
    ((fltk3::Widget*)_p)->align((fltk3::Align)alignment); 
  }
  Fl_Boxtype box() const { 
    return (Fl_Boxtype)((fltk3::Widget*)_p)->box(); 
  }
  void box(Fl_Boxtype new_box) { 
    ((fltk3::Widget*)_p)->box((fltk3::Boxtype)new_box); 
  }
  Fl_Color color() const {
    return (Fl_Color)((fltk3::Widget*)_p)->color(); 
  }
  void color(Fl_Color bg) {
    ((fltk3::Widget*)_p)->color((fltk3::Color)bg); 
  }
  Fl_Color selection_color() const {
    return (Fl_Color)((fltk3::Widget*)_p)->selection_color(); 
  }
  void selection_color(Fl_Color a) {
    ((fltk3::Widget*)_p)->selection_color((fltk3::Color)a); 
  }
  void color(Fl_Color bg, Fl_Color sel) {
    ((fltk3::Widget*)_p)->color((fltk3::Color)bg, (fltk3::Color)sel); 
  }
  const char* label() const {
    return ((fltk3::Widget*)_p)->label(); 
  }
  void label(const char* text) {
    ((fltk3::Widget*)_p)->label(text); 
  }
  void copy_label(const char *new_label) {
    ((fltk3::Widget*)_p)->copy_label(new_label); 
  }
  void label(Fl_Labeltype a, const char* b) {
    ((fltk3::Widget*)_p)->label((fltk3::Labeltype)a, b); 
  }
  Fl_Color labelcolor() const {
    return (Fl_Color)((fltk3::Widget*)_p)->labelcolor(); 
  }
  void labelcolor(Fl_Color c) {
    ((fltk3::Widget*)_p)->labelcolor((fltk3::Color)c); 
  }  
  Fl_Labeltype labeltype() const { 
    return (Fl_Labeltype)((fltk3::Widget*)_p)->labeltype(); 
  }
  void labeltype(Fl_Labeltype a) { 
    ((fltk3::Widget*)_p)->labeltype((fltk3::Labeltype)a); 
  }
  Fl_Font labelfont() const { 
    return (Fl_Font)((fltk3::Widget*)_p)->labelfont(); 
  }
  void labelfont(Fl_Font f) { 
    ((fltk3::Widget*)_p)->labelfont((fltk3::Font)f); 
  }
  Fl_Fontsize labelsize() const { 
    return (Fl_Fontsize)((fltk3::Widget*)_p)->labelsize(); 
  }
  void labelsize(Fl_Fontsize pix) {
    ((fltk3::Widget*)_p)->labelsize((fltk3::Fontsize)pix); 
  }
  const char *tooltip() const {
    return ((fltk3::Widget*)_p)->tooltip(); 
  }
  void tooltip(const char *text) {
    ((fltk3::Widget*)_p)->tooltip(text); 
  }
  void copy_tooltip(const char *text) {
    ((fltk3::Widget*)_p)->copy_tooltip(text); 
  }
  
#if 0 // TODO: FLTK123
  Fl_Image* image() {}
  const Fl_Image* image() const {}
  void image(Fl_Image* img) {}
  void image(Fl_Image& img) {}
  Fl_Image* deimage() {}
  const Fl_Image* deimage() const {}
  void deimage(Fl_Image* img) {}
  void deimage(Fl_Image& img) {}
  Fl_Callback_p callback() const {}
  void callback(Fl_Callback* cb, void* p) {}
  void callback(Fl_Callback* cb) {}
  void callback(Fl_Callback0*cb) {}
  void callback(Fl_Callback1*cb, long p=0) {}
  void* user_data() const {}
  void user_data(void* v) {}
  long argument() const {}
  void argument(long v) {}
  Fl_When when() const {}
  void when(uchar i) {}
  unsigned int visible() const {}
  int visible_r() const {}
  void set_visible() {}
  void clear_visible() {}
  unsigned int active() const {}
  int active_r() const {}
  void activate() {}
  void deactivate() {}
  unsigned int output() const {}
  void set_output() {}
  void clear_output() {}
  unsigned int takesevents() const {}
  unsigned int changed() const {}
  void set_changed() {}
  void clear_changed() {}
  int take_focus() {}
  void set_visible_focus() {}
  void clear_visible_focus() {}
  void visible_focus(int v) {}
  unsigned int  visible_focus() {}
  static void default_callback(Fl_Widget *cb, void *d) {}
  void do_callback() {}
  void do_callback(Fl_Widget* o,long arg) {}
  void do_callback(Fl_Widget* o,void* arg=0) {}
  int test_shortcut() {}
  static unsigned int label_shortcut(const char *t) {}
  static int test_shortcut(const char*, const bool require_alt = false) {}
  int contains(const Fl_Widget *w) const {}
  int inside(const Fl_Widget* w) const {}
  void redraw() {}
  void redraw_label() {}
  uchar damage() const {}
  void clear_damage(uchar c = 0) {}
  void damage(uchar c) {}
  void damage(uchar c, int x, int y, int w, int h) {}
  void draw_label(int, int, int, int, Fl_Align) const {}
  void measure_label(int& ww, int& hh) const {}
  Fl_Window* window() const {}
  Fl_Color color2() const {}
  void color2(unsigned a) {}
#endif  // TODO: FLTK123
  
};

#define FL_RESERVED_TYPE 100

#endif

//
// End of "$Id$".
//
