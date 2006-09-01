/+- This file was imported from C++ using a script
//
// "$Id: fl_engraved_label.cxx 5190 2006-06-09 16:16:34Z mike $"
//
// Engraved label drawing routines for the Fast Light Tool Kit (FLTK).
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

// Drawing code for XForms style engraved & embossed labels

#include <FL/Fl.H>
private import fl.widget;
private import fl.draw;

// data[] is dx, dy, color triples

static void innards(
    Fl_Label  o, int X, int Y, int W, int H, Fl_Align alignment,
    int data[][3], int n)
{
  Fl_Align a1 = alignment;
  if (a1 & FL_ALIGN_CLIP) {
    fl_clip(X, Y, W, H); a1 = (Fl_Align)(a1&~FL_ALIGN_CLIP);}
  fl_font((Fl_Font)o.font, o.size);
  for (int i = 0; i < n; i++) {
    fl_color((Fl_Color)(i < n-1 ? data[i][2] : o.color));
    fl_draw(o.value, X+data[i][0], Y+data[i][1], W, H, a1);
  }
  if (alignment & FL_ALIGN_CLIP) fl_pop_clip();
}

static void fl_shadow_label(
    Fl_Label  o, int X, int Y, int W, int H, Fl_Align alignment)
{
  static int data[2][3] = {{2,2,FL_DARK3},{0,0,0}};
  innards(o, X, Y, W, H, alignment, data, 2);
}

static void fl_engraved_label(
    Fl_Label  o, int X, int Y, int W, int H, Fl_Align alignment)
{
  static int data[7][3] = {
    {1,0,FL_LIGHT3},{1,1,FL_LIGHT3},{0,1,FL_LIGHT3},
    {-1,0,FL_DARK3},{-1,-1,FL_DARK3},{0,-1,FL_DARK3},
    {0,0,0}};
  innards(o, X, Y, W, H, alignment, data, 7);
}

static void fl_embossed_label(
    Fl_Label  o, int X, int Y, int W, int H, Fl_Align alignment)
{
  static int data[7][3] = {
    {-1,0,FL_LIGHT3},{-1,-1,FL_LIGHT3},{0,-1,FL_LIGHT3},
    {1,0,FL_DARK3},{1,1,FL_DARK3},{0,1,FL_DARK3},
    {0,0,0}};
  innards(o, X, Y, W, H, alignment, data, 7);
}

Fl_Labeltype fl_define_FL_SHADOW_LABEL() {
  Fl.set_labeltype(_FL_SHADOW_LABEL, fl_shadow_label, 0);
  return _FL_SHADOW_LABEL;
}
Fl_Labeltype fl_define_FL_ENGRAVED_LABEL() {
  Fl.set_labeltype(_FL_ENGRAVED_LABEL, fl_engraved_label, 0);
  return _FL_ENGRAVED_LABEL;
}
Fl_Labeltype fl_define_FL_EMBOSSED_LABEL() {
  Fl.set_labeltype(_FL_EMBOSSED_LABEL, fl_embossed_label, 0);
  return _FL_EMBOSSED_LABEL;
}

//
// End of "$Id: fl_engraved_label.cxx 5190 2006-06-09 16:16:34Z mike $".
//
    End of automatic import -+/
