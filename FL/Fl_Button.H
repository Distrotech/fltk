//
// "$Id$"
//
// Button header file for the Fast Light Tool Kit (FLTK).
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

#ifndef Fltk1_Button_H
#define Fltk1_Button_H

#include <fltk3/Button.h>
#include "Fl_Widget.H"

#define FL_NORMAL_BUTTON	0
#define FL_TOGGLE_BUTTON	1
#define FL_RADIO_BUTTON		(FL_RESERVED_TYPE+2)
#define FL_HIDDEN_BUTTON	3

extern FL_EXPORT Fl_Shortcut fl_old_shortcut(const char*);

class Fl_Widget_Tracker;

class FL_EXPORT Fl_Button : public Fl_Widget {

protected:

  Fl_Button() {}
  
  static void key_release_timeout(void *p) {
    fltk3::Button::key_release_timeout(p);
  }
  
#if 0 // TODO: FLTK123
  void simulate_key_action();
  virtual void draw();
#endif // TODO: FLTK123

public:
  Fl_Button(int X, int Y, int W, int H, const char *L = 0) {
    _p = new fltk3::Button(X, Y, W, H, L);
    _p->wrapper(this);
  }
  int value(int v) {
    return ((fltk3::Button*)_p)->value(v);
  }
  char value() const {
    return ((fltk3::Button*)_p)->value();
  }
  int set() {
    return ((fltk3::Button*)_p)->set();
  }
  int clear() {
    return ((fltk3::Button*)_p)->clear();
  }
  void setonly() {
    ((fltk3::Button*)_p)->setonly();
  }
  
#if 0 // TODO: FLTK123
  virtual int handle(int);
  int shortcut() const {return shortcut_;}
  void shortcut(int s) {shortcut_ = s;}
  Fl_Boxtype down_box() const {return (Fl_Boxtype)down_box_;}
  void down_box(Fl_Boxtype b) {down_box_ = b;}
  void shortcut(const char *s) {shortcut(fl_old_shortcut(s));}
  Fl_Color down_color() const {return selection_color();}
  void down_color(unsigned c) {selection_color(c);}
#endif // TODO: FLTK123
};

#endif

//
// End of "$Id$".
//
