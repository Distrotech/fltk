//
// "$Id: valuator.d 4288 2005-04-16 00:13:17Z mike $"
//
// Valuator header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2005 by Bill Spitzak and others.
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

module fl.valuator;

public import fl.widget;

private import fl.fl;
private import std.math;
private import std.c.string;
private import std.c.stdio;
private import std.ctype;

// shared type() values for classes that work in both directions:
const Fl_Type FL_VERTICAL		= 0;
const Fl_Type FL_HORIZONTAL		= 1;

class Fl_Valuator : Fl_Widget {

private:

  const double epsilon = 4.66e-10;

  double value_;
  double previous_value_;
  double min, max; // truncates to this range *after* rounding
  double A; int B; // rounds to multiples of A/B, or no rounding if A is zero

protected:

  int horizontal() {
    return type()&1;
  }

  this(int X, int Y, int W, int H, char[] L=null) {
    super(X,Y,W,H,L);
    alignment(FL_ALIGN_BOTTOM);
    when(FL_WHEN_CHANGED);
    value_ = 0;
    previous_value_ = 1;
    min = 0;
    max = 1;
    A = 0.0;
    B = 1;
  }

  double previous_value() {
    return previous_value_;
  }

  void handle_push() {
    previous_value_ = value_;
  }

  double softclamp(double v) {
    int which = (min<=max);
    double p = previous_value_;
    if ((v<min)==which && p!=min && (p<min)!=which) return min;
    else if ((v>max)==which && p!=max && (p>max)!=which) return max;
    else return v;
  }

  void handle_drag(double v) {
    if (v != value_) {
      value_ = v;
      value_damage();
      set_changed();
      if (when() & FL_WHEN_CHANGED) do_callback();
    }
  }

  void handle_release() {
    if (when()&FL_WHEN_RELEASE) {
      // insure changed() is off even if no callback is done.  It may have
      // been turned on by the drag, and then the slider returned to it's
      // initial position:
      clear_changed();
      // now do the callback only if slider in new position or always is on:
      if (value_ != previous_value_ || when() & FL_WHEN_NOT_CHANGED) {
        do_callback();
      }
    }
  }

  void value_damage() {
    damage(FL_DAMAGE_EXPOSE);
  }

  void set_value(double v) {
    value_ = v;
  }

public:

  void bounds(double a, double b) {
    min=a; max=b;
  }

  double minimum() {
    return min;
  }

  void minimum(double a) {
    min = a;
  }

  double maximum() {
    return max;
  }

  void maximum(double a) {
    max = a;
  }

  void range(double a, double b) {
    min = a; max = b;
  }

  void step(int a) {
    A = a; B = 1;
  }

  void step(double a, int b) {
    A = a; B = b;
  }

  void step(double s) {
    if (s < 0) s = -s;
    A = rint(s);
    B = 1;
    while (fabs(s-A/B) > epsilon && B<=(0x7fffffff/10)) {B *= 10; A = rint(s*B);}
  }

  double step() {
    return A/B;
  }

  void precision(int p) {
    A = 1.0;
    for (B = 1; p--;) B *= 10;
  }

  double value() {
    return value_;
  }

  int value(double v) {
    clear_changed();
    if (v == value_) return 0;
    value_ = v;
    value_damage();
    return 1;
  }

  int format(char[] buffer) {
    if (buffer[$-1]!=0) buffer ~= 0; 
    double v = value();
    // MRS: THIS IS A HACK - RECOMMEND ADDING BUFFER SIZE ARGUMENT
    if (!A || !B) return snprintf(buffer, 128, "%g", v);
  
    // Figure out how many digits are required to correctly format the
    // value.
    int i, c = 0;
    char temp[32];
    // output a number with many digits after the decimal point. This
    // seems to be needed to get high precission
    snprintf(temp, temp.length, "%.12f", A/B);
    // strip all trailing 0's
    for (i=strlen(temp)-1; i>0; i--) {
      if (temp[i]!='0') break;
    }
    // count digits until we find the decimal point (or comma or whatever
    // letter is set in the current locale)
    for (; i>0; i--, c++) {
      if (!isdigit(temp[i])) break;
    }
  
    // MRS: THIS IS A HACK - RECOMMEND ADDING BUFFER SIZE ARGUMENT
    return snprintf(buffer, 128, "%.*f", c, v);
  }

  double round(double v) {
    if (A) return rint(v*B/A)*A/B;
    else return v;
  }

  double clamp(double v) {
    if ((v<min)==(min<=max)) return min;
    else if ((v>max)==(min<=max)) return max;
    else return v;
  }

  double increment(double v, int n) {
    if (!A) return v+n*(max-min)/100;
    if (min > max) n = -n;
    return (rint(v*B/A)+n)*A/B;
  }
}

//
// End of "$Id: valuator.d 5190 2006-06-09 16:16:34Z mike $".
//
