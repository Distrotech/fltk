//
// "$Id: Fl_Return_Button.cxx,v 1.30 2001/07/23 09:50:05 spitzak Exp $"
//
// Return button widget for the Fast Light Tool Kit (FLTK).
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

#include <fltk/Fl.h>
#include <fltk/Fl_Return_Button.h>
#include <fltk/fl_draw.h>

// this is public so fl_draw_symbol can call it:
void fl_glyph_return(const Fl_Widget*, int,
		     int x,int y,int w,int h, Fl_Flags)
{
  int size = w; if (h<size) size = h;
  int d = (size+2)/4; if (d<3) d = 3;
  int t = (size+9)/12; if (t<1) t = 1;
  int x0 = x+(w-2*d-2*t-1)/2;
  int x1 = x0+d;
  int y0 = y+h/2;
#if 1
  fl_color(FL_LIGHT3);
  fl_newpath();
  fl_vertex(x0, y0);
  fl_vertex(x1, y0+d);
  fl_vertex(x1, y0+t);
  fl_vertex(x1+d+2*t, y0+t);
  fl_vertex(x1+d+2*t, y0-d);
  fl_stroke();
  fl_line(x1, y0-t, x1, y0-d);
  fl_color(fl_gray_ramp(0));
  fl_line(x0, y0, x1, y0-d);
  fl_newpath();
  fl_vertex(x1+1, y0-t);
  fl_vertex(x1+d, y0-t);
  fl_vertex(x1+d, y0-d);
  fl_vertex(x1+d+2*t, y0-d);
  fl_color(FL_DARK3); fl_stroke();
#else // solid arrow written by Carl
  fl_color(fl_inactive(fc, f));
  fl_polygon(x0,y0, x1,y0+d, x1, y0-d);
  fl_rectf(x1,y0-t,d,2*t+1);
  fl_rectf(x1+d,y0-d,2*t+1,d+t+1);
#endif
}

void Fl_Return_Button::draw() {
  Fl_Flags flags = draw_button();
  int W = h();
  if (w()/3 < W) W = w()/3;
  draw_glyph(0, w()-W-4, 0, W, h(), flags);
  draw_inside_label(0, 0, w()-W+4, h(), flags);
}

static void revert(Fl_Style* s) {
  s->selection_color = FL_GRAY;
  s->selection_text_color = FL_BLACK;
  s->glyph = fl_glyph_return;
}
static Fl_Named_Style style("Return_Button", revert, &Fl_Return_Button::default_style);
Fl_Named_Style* Fl_Return_Button::default_style = &::style;

Fl_Return_Button::Fl_Return_Button(int x,int y,int w,int h,const char *l)
  : Fl_Button(x,y,w,h,l)
{
  style(default_style);
  shortcut(FL_Enter);
}

//
// End of "$Id: Fl_Return_Button.cxx,v 1.30 2001/07/23 09:50:05 spitzak Exp $".
//
