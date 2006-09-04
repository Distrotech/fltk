//
// "$Id: slider.d 4288 2005-04-16 00:13:17Z mike $"
//
// Slider header file for the Fast Light Tool Kit (FLTK).
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

module fl.slider;

public import fl.valuator;
private import fl.enumerations;
private import fl.draw;
private import std.c.math;


class Fl_Slider : Fl_Valuator {
private:
  float slider_size_;
  ubyte slider_;
  void _Fl_Slider() {
    slider_size_ = 0;
    slider_ = 0; // FL_UP_BOX;
  }

  void draw_bg(int X, int Y, int W, int H) {
    fl_push_clip(X, Y, W, H);
    draw_box();
    fl_pop_clip();
  
    Fl_Color black = active_r() ? FL_FOREGROUND_COLOR : FL_INACTIVE_COLOR;
    if (type() == FL_VERT_NICE_SLIDER) {
      draw_box(FL_THIN_DOWN_BOX, X+W/2-2, Y, 4, H, black);
    } else if (type() == FL_HOR_NICE_SLIDER) {
      draw_box(FL_THIN_DOWN_BOX, X, Y+H/2-2, W, 4, black);
    }
  }

protected:

  // these allow subclasses to put the slider in a smaller area:
  void draw(int X, int Y, int W, int H) {
    double val;
    if (minimum() == maximum())
      val = 0.5;
    else {
      val = (value()-minimum())/(maximum()-minimum());
      if (val > 1.0) val = 1.0;
      else if (val < 0.0) val = 0.0;
    }
  
    int ww = (horizontal() ? W : H);
    int xx, S;
    if (type()==FL_HOR_FILL_SLIDER || type() == FL_VERT_FILL_SLIDER) {
      S = cast(int)(val*ww+.5);
      if (minimum()>maximum()) {S = ww-S; xx = ww-S;}
      else xx = 0;
    } else {
      S = cast(int)(slider_size_*ww+.5);
      int T = (horizontal() ? H : W)/2+1;
      if (type()==FL_VERT_NICE_SLIDER || type()==FL_HOR_NICE_SLIDER) T += 4;
      if (S < T) S = T;
      xx = cast(int)(val*(ww-S)+.5);
    }
    int xsl, ysl, wsl, hsl;
    if (horizontal()) {
      xsl = X+xx;
      wsl = S;
      ysl = Y;
      hsl = H;
    } else {
      ysl = Y+xx;
      hsl = S;
      xsl = X;
      wsl = W;
    }
  
    draw_bg(X, Y, W, H);
  
    Fl_Boxtype box1 = slider();
    if (!box1) {box1 = (box()&-2); if (!box1) box1 = FL_UP_BOX;}
    if (type() == FL_VERT_NICE_SLIDER) {
      draw_box(box1, xsl, ysl, wsl, hsl, FL_GRAY);
      int d = (hsl-4)/2;
      draw_box(FL_THIN_DOWN_BOX, xsl+2, ysl+d, wsl-4, hsl-2*d,selection_color());
    } else if (type() == FL_HOR_NICE_SLIDER) {
      draw_box(box1, xsl, ysl, wsl, hsl, FL_GRAY);
      int d = (wsl-4)/2;
      draw_box(FL_THIN_DOWN_BOX, xsl+d, ysl+2, wsl-2*d, hsl-4,selection_color());
    } else {
      if (wsl>0 && hsl>0) draw_box(box1, xsl, ysl, wsl, hsl, selection_color());
    }
  
    draw_label(xsl, ysl, wsl, hsl);
    if (Fl.focus() is this) {
      if (type() == FL_HOR_FILL_SLIDER || type() == FL_VERT_FILL_SLIDER) draw_focus();
      else draw_focus(box1, xsl, ysl, wsl, hsl);
    }
}

  int handle(int event, int X, int Y, int W, int H) {
    switch (event) {
    case FL_PUSH:
      if (!Fl.event_inside(X, Y, W, H)) return 0;
      handle_push();
    case FL_DRAG: {
  
      double val;
      if (minimum() == maximum())
        val = 0.5;
      else {
        val = (value()-minimum())/(maximum()-minimum());
        if (val > 1.0) val = 1.0;
        else if (val < 0.0) val = 0.0;
      }
  
      int ww = (horizontal() ? W : H);
      int mx = (horizontal() ? Fl.event_x()-X : Fl.event_y()-Y);
      int S;
      static int offcenter;
  
      if (type() == FL_HOR_FILL_SLIDER || type() == FL_VERT_FILL_SLIDER) {
  
        S = 0;
        if (event == FL_PUSH) {
  	int xx = cast(int)(val*ww+.5);
  	offcenter = mx-xx;
  	if (offcenter < -10 || offcenter > 10) offcenter = 0;
  	else return 1;
        }
  
      } else {
  
        S = cast(int)(slider_size_*ww+.5); if (S >= ww) return 0;
        int T = (horizontal() ? H : W)/2+1;
        if (type()==FL_VERT_NICE_SLIDER || type()==FL_HOR_NICE_SLIDER) T += 4;
        if (S < T) S = T;
        if (event == FL_PUSH) {
  	int xx = cast(int)(val*(ww-S)+.5);
  	offcenter = mx-xx;
  	if (offcenter < 0) offcenter = 0;
  	else if (offcenter > S) offcenter = S;
  	else return 1;
        }
      }
  
      int xx = mx-offcenter;
      double v;
      char tryAgain = 1;
      while (tryAgain)
      {
        tryAgain = 0;
        if (xx < 0) {
          xx = 0;
          offcenter = mx; if (offcenter < 0) offcenter = 0;
        } else if (xx > (ww-S)) {
          xx = ww-S;
          offcenter = mx-xx; if (offcenter > S) offcenter = S;
        }
        v = round(xx*(maximum()-minimum())/(ww-S) + minimum());
        // make sure a click outside the sliderbar moves it:
        if (event == FL_PUSH && v == value()) {
          offcenter = S/2;
          event = FL_DRAG;
          tryAgain = 1;
        }
      }
      handle_drag(clamp(v));
      } return 1;
    case FL_RELEASE:
      handle_release();
      return 1;
    case FL_KEYBOARD :
      switch (Fl.event_key()) {
        case FL_Up:
          if (horizontal()) return 0;
          handle_push();
  	handle_drag(clamp(increment(value(),-1)));
  	handle_release();
  	return 1;
        case FL_Down:
          if (horizontal()) return 0;
          handle_push();
  	handle_drag(clamp(increment(value(),1)));
  	handle_release();
  	return 1;
        case FL_Left:
          if (!horizontal()) return 0;
          handle_push();
  	handle_drag(clamp(increment(value(),-1)));
  	handle_release();
  	return 1;
        case FL_Right:
          if (!horizontal()) return 0;
          handle_push();
  	handle_drag(clamp(increment(value(),1)));
  	handle_release();
  	return 1;
        default:
          return 0;
      }
      // break not required because of switch...
    case FL_FOCUS :
    case FL_UNFOCUS :
      if (Fl.visible_focus()) {
        redraw();
        return 1;
      } else return 0;
    case FL_ENTER :
    case FL_LEAVE :
      return 1;
    default:
      return 0;
    }
  }
  
public:

  void draw() {
    if (damage()&FL_DAMAGE_ALL) draw_box();
    draw(x()+Fl.box_dx(box()),
         y()+Fl.box_dy(box()),
         w()-Fl.box_dw(box()),
         h()-Fl.box_dh(box()));
  }

  int handle(int event) {
    if (event == FL_PUSH && Fl.visible_focus()) {
      Fl.focus(this);
      redraw();
    }
    return handle(event,
  		x()+Fl.box_dx(box()),
  		y()+Fl.box_dy(box()),
  		w()-Fl.box_dw(box()),
  		h()-Fl.box_dh(box()));
  }

  this(int X, int Y, int W, int H, char* l=null) {
    super(X, Y, W, H, l);
    box(FL_DOWN_BOX);
    _Fl_Slider();
  }

  this(ubyte t, int X, int Y, int W, int H, char* l) {
    super(X, Y, W, H, l);
    type(t);
    box(t==FL_HOR_NICE_SLIDER || t==FL_VERT_NICE_SLIDER ? FL_FLAT_BOX : FL_DOWN_BOX);
    _Fl_Slider();
  }

  int scrollvalue(int p, int W, int t, int l) {
  //	p = position, first line displayed
  //	w = window, number of lines displayed
  //	t = top, number of first line
  //	l = length, total number of lines
    step(1, 1);
    if (p+W > t+l) l = p+W-t;
    slider_size(W >= l ? 1.0 : cast(double)(W)/cast(double)(l));
    bounds(t, l-W+t);
    return value(p);
  }

  void bounds(double a, double b) {
    if (minimum() != a || maximum() != b) {
      super.bounds(a, b); 
      damage(FL_DAMAGE_EXPOSE);
    }
  }

  float slider_size() {return slider_size_;}
  void slider_size(double v) {
    if (v <  0) v = 0;
    if (v > 1) v = 1;
    if (slider_size_ != v) {
      slider_size_ = v; 
      damage(FL_DAMAGE_EXPOSE);
    }
  }

  Fl_Boxtype slider() {return slider_;}
  void slider(Fl_Boxtype c) {slider_ = c;}
}

//
// End of "$Id: slider.d 4288 2005-04-16 00:13:17Z mike $".
//

/+=
#include <FL/Fl.H>
private import fl.slider;
private import fl.draw;
#include <math.h>



    End of automatic import -+/
