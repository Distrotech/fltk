//
// "$Id: Fl_Dial.cxx,v 1.41 2002/12/09 04:52:25 spitzak Exp $"
//
// Circular dial widget for the Fast Light Tool Kit (FLTK).
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

#include <fltk/Dial.h>
#include <fltk/events.h>
#include <fltk/damage.h>
#include <fltk/Box.h>
#include <fltk/draw.h>
#include <stdlib.h>
#include <fltk/math.h>
using namespace fltk;

// All angles are measured with 0 to the right and counter-clockwise

void Dial::draw() {
  int X = 0; int Y = 0; int W = w(); int H = h();
  if (!(type() == FILL && box() == OVAL_BOX)) {
    if (damage()&DAMAGE_ALL) draw_box();
    box()->inset(X,Y,W,H);
  }
  Color fillcolor = selection_color();
  Color linecolor = highlight_color();
  if (!active_r()) {
    fillcolor = inactive(fillcolor);
    linecolor = inactive(linecolor);
  }
  float angle = (a2-a1)*float((value()-minimum())/(maximum()-minimum())) + a1;
  if (type() == FILL) {
    if (damage()&DAMAGE_EXPOSE && box() == OVAL_BOX) draw_background();
    setcolor(color());
    fillpie(X, Y, W-1, H-1,
	    270-a1, angle > a1 ? 360+270-angle : 270-360-angle);
    setcolor(fillcolor);
    fillpie(X, Y, W-1, H-1, 270-angle, 270-a1);
    if (box() == OVAL_BOX) {
      addellipse(X, Y, W-1, H-1);
      setcolor(linecolor);
      strokepath();
    }
  } else {
    if (!(damage()&DAMAGE_ALL)) {
      addellipse(X+1, Y+1, W-2, H-2);
      setcolor(color());
      fillpath();
    }
    push_matrix();
    translate(X+W/2-.5f, Y+H/2-.5f);
    scale(W-1, H-1);
    rotate(45-angle);
    if (type() == LINE) {
      static float v[4][2] = {{0,0}, {-0.04f,0}, {-0.25f,0.25f}, {0,0.04f}};
      addvertices(4,v);
    } else {
      addcircle(-0.20f, 0.20f, 0.07f);
    }
    setcolor(fillcolor);
    fillstrokepath(linecolor);
    pop_matrix();
  }
  if (focused()) {
    addellipse(X+2, Y+2, W-5, H-5);
    setcolor(linecolor);
    line_style(DASH);
    strokepath();
    line_style(0);
  }
}


int Dial::handle(int event) {
  int X = 0; int Y = 0; int W = w(); int H = h();
  box()->inset(X,Y,W,H);
  switch (event) {
  case PUSH:
    handle_push();
  case DRAG: {
    int mx = event_x()-X-W/2;
    int my = event_y()-Y-H/2;
    if (!mx && !my) return 1;
    float angle = 270-atan2f((float)-my, (float)mx)*float(180/M_PI);
    float oldangle = (a2-a1)*float((value()-minimum())/(maximum()-minimum())) + a1;
    while (angle < oldangle-180) angle += 360;
    while (angle > oldangle+180) angle -= 360;
    double val;
    if ((a1<a2) ? (angle <= a1) : (angle >= a1)) {
      val = minimum();
    } else if ((a1<a2) ? (angle >= a2) : (angle <= a2)) {
      val = maximum();
    } else {
      val = minimum() + (maximum()-minimum())*(angle-a1)/(a2-a1);
    }
    handle_drag(val);
  } return 1;
  case RELEASE:
    if (!pushed()) handle_release();
    return 1;
  default:
    return Valuator::handle(event);
  }
}

static void revert(Style* s) {
  s->box = OVAL_BOX;
  s->selection_color = GRAY60;
  s->highlight_color = BLACK;
}
static NamedStyle style("Dial", revert, &Dial::default_style);
NamedStyle* Dial::default_style = &::style;

Dial::Dial(int x, int y, int w, int h, const char* l)
  : Valuator(x, y, w, h, l) {
  style(default_style);
  a1 = 45;
  a2 = 315;
  //set_click_to_focus();
}

//
// End of "$Id: Fl_Dial.cxx,v 1.41 2002/12/09 04:52:25 spitzak Exp $".
//
