//
// "$Id: Fl_Valuator.cxx,v 1.9 1999/12/15 08:31:00 bill Exp $"
//
// Valuator widget for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-1999 by Bill Spitzak and others.
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
// Please report all bugs and problems to "fltk-bugs@easysw.com".
//

// Base class for sliders and all other one-value "knobs"

#include <FL/Fl.H>
#include <FL/Fl_Valuator.H>
#include <FL/math.h>
#include <stdio.h>

Fl_Valuator::Fl_Valuator(int X, int Y, int W, int H, const char* L)
  : Fl_Widget(X,Y,W,H,L) {
  align(FL_ALIGN_BOTTOM);
  when(FL_WHEN_CHANGED);
  value_ = 0.0;
  step_ = 0.0;
  minimum_ = 0.0;
  maximum_ = 1.0;
  linesize_ = 1;
  pagesize_ = 10;
}

void Fl_Valuator::precision(int p) {
  double B = 1.0;
  for (int i=0; i<p; i++) B *= 10;
  step_ = 1.0/B;
}

void Fl_Valuator::value_damage() {
  damage(FL_DAMAGE_EXPOSE); // default version does partial-redraw
}

int Fl_Valuator::value(double v) {
  clear_changed();
  if (v == value_) return 0;
  value_ = v;
  value_damage();
  return 1;
}

double Fl_Valuator::previous_value_;

// inline void Fl_Valuator::handle_push() {previous_value_ = value_;}

void Fl_Valuator::handle_drag(double v) {
  if (v != value_) {
    value_ = v;
    value_damage();
    if (when() & FL_WHEN_CHANGED || !Fl::pushed()) do_callback();
    else set_changed();
  }
}

void Fl_Valuator::handle_release() {
  if (when()&FL_WHEN_RELEASE && !Fl::pushed()) {
    // insure changed() is off even if no callback is done.  It may have
    // been turned on by the drag, and then the slider returned to it's
    // initial position:
    clear_changed();
    // now do the callback only if slider in new position or always is on:
    if (value_ != previous_value_ || when() & FL_WHEN_NOT_CHANGED)
      do_callback();
  }
}

double Fl_Valuator::round(double v) const {
  return step_ ? rint(v/step_)*step_ : v;
}

double Fl_Valuator::clamp(double v) const {
  if ((v<minimum_) == (minimum_<=maximum_)) return minimum_;
  else if ((v>maximum_) == (minimum_<=maximum_)) return maximum_;
  else return v;
}

double Fl_Valuator::softclamp(double v) const {
  int which = (minimum_ <= maximum_);
  double p = previous_value_;
  if ((v<minimum_)==which && p!=minimum_ && (p<minimum_)!=which)
    return minimum_;
  else if ((v>maximum_)==which && p!=maximum_ && (p>maximum_)!=which)
    return maximum_;
  else
    return v;
}

double Fl_Valuator::increment(double v, int n) const {
  double s = step_;
  if (!s) s = (maximum_-minimum_)/100;
  else if (minimum_ > maximum_) n = -n;
  return rint(v/s+n)*s;
}

int Fl_Valuator::format(char* buffer) {
  double v = value();
  if (!step_) return sprintf(buffer, "%g", v);
  int i, x;
  double b = rint(1.0/step_);
  for (x = 10, i = 2; x < b; x *= 10) i++;
  if (x == b) i--;
  return sprintf(buffer, "%.*f", i, v);
}

int Fl_Valuator::handle(int event) {
  switch(event) {
  case FL_ENTER:
  case FL_LEAVE:
    if (highlight_color() && takesevents()) damage(FL_DAMAGE_HIGHLIGHT);
    return 1;
  case FL_FOCUS:
  case FL_UNFOCUS:
    damage(FL_DAMAGE_HIGHLIGHT);
    return 1;
  case FL_KEYBOARD: {
    int i = linesize();
    if (Fl::event_state()&(FL_SHIFT|FL_CTRL|FL_ALT)) i = pagesize();
    switch (Fl::event_key()) {
    case FL_Down:
    case FL_Left:
    case FL_BackSpace:
      i = -i;
    case FL_Up:
    case FL_Right:
    case ' ':
      handle_drag(clamp(increment(value(), i)));
      return 1;
    case FL_Home:
      handle_drag(minimum());
      return 1;
    case FL_End:
      handle_drag(maximum());
      return 1;
    }}
  }
  return 0;
}

//
// End of "$Id: Fl_Valuator.cxx,v 1.9 1999/12/15 08:31:00 bill Exp $".
//
