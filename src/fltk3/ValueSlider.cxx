//
// "$Id$"
//
// Value slider widget for the Fast Light Tool Kit (FLTK).
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

#include <fltk3/run.h>
#include <fltk3/ValueSlider.h>
#include <fltk3/draw.h>
#include <math.h>


/**
 Creates a new fltk3::ValueSlider widget using the given
 position, size, and label string. The default boxtype is fltk3::DOWN_BOX.
 */
fltk3::ValueSlider::ValueSlider(int X, int Y, int W, int H, const char*l)
: fltk3::Slider(X,Y,W,H,l) 
{
  step(1,100);
  textfont(fltk3::HELVETICA);
  textsize(10);
  textcolor(fltk3::FOREGROUND_COLOR);
}


void fltk3::ValueSlider::draw() 
{
  int sxx = 0, syy = 0, sww = w(), shh = h();
  int bxx = 0, byy = 0, bww = w(), bhh = h();
  if (horizontal()) {
    bww = 35; sxx += 35; sww -= 35;
  } else {
    syy += 25; bhh = 25; shh -= 25;
  }
  if (damage()&fltk3::DAMAGE_ALL) 
    draw_box(Boxtype(box()|(horizontal()?TIE_LEFT:TIE_TOP)),sxx,syy,sww,shh,color());
  Slider::draw(sxx+fltk3::box_dx(box()),
               syy+fltk3::box_dy(box()),
               sww-fltk3::box_dw(box()),
               shh-fltk3::box_dh(box()));
  draw_box(Boxtype(box()|(horizontal()?TIE_RIGHT:TIE_BOTTOM)),bxx,byy,bww,bhh,color());
  char buf[128];
  format(buf);
  fltk3::font(textfont(), textsize());
  fltk3::color(active_r() ? textcolor() : fltk3::inactive(textcolor()));
  fltk3::draw(buf, bxx, byy, bww, bhh, fltk3::ALIGN_CLIP);
}


int fltk3::ValueSlider::handle(int event) 
{
  if (event == fltk3::PUSH && fltk3::visible_focus()) {
    fltk3::focus(this);
    redraw();
  }
  int sxx = 0, syy = 0, sww = w(), shh = h();
  if (horizontal()) {
    sxx += 35; sww -= 35;
  } else {
    syy += 25; shh -= 25;
  }
  return Slider::handle(event,
                        sxx+fltk3::box_dx(box()),
                        syy+fltk3::box_dy(box()),
                        sww-fltk3::box_dw(box()),
                        shh-fltk3::box_dh(box()));
}


//
// End of "$Id$".
//
