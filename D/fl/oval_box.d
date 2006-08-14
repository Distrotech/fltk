//
// "$Id: oval_box.d 5190 2006-06-09 16:16:34Z mike $"
//
// Oval box drawing code for the Fast Light Tool Kit (FLTK).
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

module fl.oval_box;

private import fl.fl;
private import fl.draw;

void fl_oval_flat_box(int x, int y, int w, int h, Fl_Color c) {
  fl_color(c);
  fl_pie(x, y, w, h, 0, 360);
}

void fl_oval_frame(int x, int y, int w, int h, Fl_Color c) {
  fl_color(c);
  fl_arc(x, y, w, h, 0, 360);
}

void fl_oval_box(int x, int y, int w, int h, Fl_Color c) {
  fl_oval_flat_box(x,y,w,h,c);
  fl_oval_frame(x,y,w,h,FL_BLACK);
}

void fl_oval_shadow_box(int x, int y, int w, int h, Fl_Color c) {
  fl_oval_flat_box(x+3,y+3,w,h,FL_DARK3);
  fl_oval_box(x,y,w,h,c);
}

//
// End of "$Id: oval_box.d 5190 2006-06-09 16:16:34Z mike $".
//
