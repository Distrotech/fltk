// "$Id: Valuator.h 6944 2009-11-27 12:18:37Z cwarrens $"
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

#ifndef fltk2_Valuator_h
#define fltk2_Valuator_h

#include <fltk3/Valuator.h>
#include "Widget.h"

namespace fltk {

class FL_API Valuator : public Widget {

public:
  Valuator() {}
  Valuator(int X, int Y, int W, int H, const char* L=0L) {
    _p = new fltk3::Valuator(X, Y, W, H, L);
    _p->wrapper(this);
  }
  // in Wrapper: int handle(int);
  double value() const {
    return ((fltk3::Valuator*)_p)->value();
  }
  bool value(double v) {
    bool ret = (value()!=v);
    ((fltk3::Valuator*)_p)->value(v);
    return ret;
  }
  double minimum() const {
    return ((fltk3::Valuator*)_p)->minimum();
  }
  void minimum(double a) {
    ((fltk3::Valuator*)_p)->minimum(a);
  }
  double maximum() const {
    return ((fltk3::Valuator*)_p)->maximum();
  }
  void maximum(double a) {
    ((fltk3::Valuator*)_p)->maximum(a);
  }
  void range(double a, double b) {
    ((fltk3::Valuator*)_p)->range(a, b);
  }
  double step() const {
    return ((fltk3::Valuator*)_p)->step();
  }
  void step(double a) {
    ((fltk3::Valuator*)_p)->step(a);
  }
  
#if 0 // TODO: FLTK123
  double linesize() const {
    return ((fltk3::Valuator*)_p)->linesize();
  }
  void linesize(double a) {
    ((fltk3::Valuator*)_p)->linesize(a);
  }
  double linesize_setting() const {
    return ((fltk3::Valuator*)_p)->linesize_setting();
  }
  virtual int format(char*);
#ifdef FLTK_1_SLIDER
  void step(double a, int b) {step(a/b);}
  void bounds(double a, double b) {minimum_=a; maximum_=b;}
  void precision(int p) {
    int B = 1;
    for (int i=0; i<p; i++) B *= 10;
    step_ = 1.0f/B;
  }
#endif
  double previous_value() const {return previous_value_;}
  void handle_push() {previous_value_ = value_;}
  void handle_drag(double newvalue);
  void handle_release();
  virtual void value_damage(); // callback whenever value changes
  void set_value(double v) {value_ = v;} // change w/o doing value_damage
#endif // TODO: FLTK123
};

}

#endif

// End of "$Id: Valuator.h 6944 2009-11-27 12:18:37Z cwarrens $".
