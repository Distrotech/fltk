//
// "$Id: fl_labeltype.cxx 5190 2006-06-09 16:16:34Z mike $"
//
// Label drawing routines for the Fast Light Tool Kit (FLTK).
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

// Drawing code for the (one) common label types.
// Other label types (symbols) are in their own source files
// to avoid linking if not used.

module fl.labeltype;

private import fl.enumerations;
private import fl.fl;
private import fl.widget;
private import fl.group;
private import fl.draw;
private import fl.image;


struct Fl_Label {
  char* value;
  Fl_Image image;
  Fl_Image deimage;
  ubyte type;
  ubyte font;
  ubyte size;
  uint color;

  // draw label with arbitrary alignment in arbitrary box:
  void draw(int X, int Y, int W, int H, Fl_Align alignment) {
    if (!value && !image) return;
    table[type](this, X, Y, W, H, alignment);
  }

  void measure(inout int W, inout int H) {
    if (!value && !image) {
      W = H = 0;
      return;
    }
    Fl_Label_Measure_F f = measure_lut[type]; 
    if (!f) f = &fl_normal_measure;
    f(this, W, H);
  }
}

void fl_no_label(Fl_Label* o, int X, int Y, int W, int H, Fl_Align a) {
}

void fl_normal_label(Fl_Label* o, int X, int Y, int W, int H, Fl_Align alignment) {
  fl_font(o.font, o.size);
  fl_color(o.color);
  fl_draw(o.value, X, Y, W, H, alignment, o.image);
}

void fl_normal_measure(Fl_Label* o, inout int W, inout int H) {
  fl_font(o.font, o.size);
  fl_measure(o.value, W, H);
  if (o.image) {
    if (o.image.w() > W) W = o.image.w();
    H += o.image.h();
  }
}

const int MAX_LABELTYPE = 16; 

static Fl_Label_Draw_F table[MAX_LABELTYPE] = [
  &fl_normal_label,
  &fl_no_label,
  &fl_normal_label,	// _FL_SHADOW_LABEL,
  &fl_normal_label,	// _FL_ENGRAVED_LABEL,
  &fl_normal_label,	// _FL_EMBOSSED_LABEL,
  &fl_no_label,		// _FL_MULTI_LABEL,
  &fl_no_label,		// _FL_ICON_LABEL,
  // FL_FREE_LABELTYPE+n:
  &fl_no_label, &fl_no_label, &fl_no_label,
  &fl_no_label, &fl_no_label, &fl_no_label,
  &fl_no_label, &fl_no_label, &fl_no_label
];

static Fl_Label_Measure_F measure_lut[MAX_LABELTYPE];

/+=
void Fl.set_labeltype(Fl_Labeltype t,Fl_Label_Draw_F  f,Fl_Label_Measure_F m) 
{
  table[t] = f; measure[t] = m;
}

////////////////////////////////////////////////////////////////


// include these vars here so they can be referenced without including
// Fl_Input_ code:
private import fl.input_;

//
// End of "$Id: fl_labeltype.cxx 5190 2006-06-09 16:16:34Z mike $".
//
    End of automatic import -+/
