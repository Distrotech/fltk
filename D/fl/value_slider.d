//
// "$Id: value_slider.d 4288 2005-04-16 00:13:17Z mike $"
//
// Value slider header file for the Fast Light Tool Kit (FLTK).
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

module fl.value_slider;

public import fl.slider;

private import fl.fl;
private import fl.draw;


class Fl_Value_Slider : Fl_Slider {

private:

  Fl_Font textfont_;
  ubyte textsize_;
  Fl_Color textcolor_;

public:

  void draw() {
    int sxx = x(), syy = y(), sww = w(), shh = h();
    int bxx = x(), byy = y(), bww = w(), bhh = h();
    if (horizontal()) {
      bww = 35; sxx += 35; sww -= 35;
    } else {
      syy += 25; bhh = 25; shh -= 25;
    }
    if (damage()&FL_DAMAGE_ALL) draw_box(box(),sxx,syy,sww,shh,color());
    super.draw(sxx+Fl.box_dx(box()),
		    syy+Fl.box_dy(box()),
		    sww-Fl.box_dw(box()),
		    shh-Fl.box_dh(box()));
    draw_box(box(),bxx,byy,bww,bhh,color());
    char buf[128];
    format(buf.ptr);
    fl_font(textfont(), textsize());
    fl_color(active_r() ? textcolor() : fl_inactive(textcolor()));
    fl_draw(buf, bxx, byy, bww, bhh, FL_ALIGN_CLIP);
  }

  int handle(Fl_Event event) {
    if (event == FL_PUSH && Fl.visible_focus()) {
      Fl.focus(this);
      redraw();
    }
    int sxx = x(), syy = y(), sww = w(), shh = h();
    if (horizontal()) {
      sxx += 35; sww -= 35;
    } else {
      syy += 25; shh -= 25;
    }
    return super.handle(event,
      sxx+Fl.box_dx(box()), syy+Fl.box_dy(box()),
      sww-Fl.box_dw(box()), shh-Fl.box_dh(box()));
  }

  this(int X, int Y, int W, int H, char[] l=null) {
    super(X,Y,W,H,l);
    step(1,100);
    textfont_ = FL_HELVETICA;
    textsize_ = 10;
    textcolor_ = FL_FOREGROUND_COLOR;
  }

  Fl_Font textfont() {
    return textfont_;
  }

  void textfont(Fl_Font s) {
    textfont_ = s;
  }

  ubyte textsize() {
    return textsize_;
  }

  void textsize(ubyte s) {
    textsize_ = s;
  }

  Fl_Color textcolor() {
    return textcolor_;
  }

  void textcolor(Fl_Color s) {
    textcolor_ = s;
  }
}

//
// End of "$Id: value_slider.d 5190 2006-06-09 16:16:34Z mike $".
//
