//
// "$Id: Fl_Image.cxx,v 1.5.2.3.2.1 2001/08/05 23:58:54 easysw Exp $"
//
// Image drawing code for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2001 by Bill Spitzak and others.
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
// Please report all bugs and problems to "fltk-bugs@fltk.org".
//

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/x.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Image.H>

Fl_Image::~Fl_Image() {
}

void Fl_Image::draw(int XP, int YP, int WP, int HP, int cx, int cy) {
}

void Fl_Image::label(Fl_Widget* w) {
  w->image(this);
}

void Fl_Image::label(Fl_Menu_Item* m) {
}

Fl_RGB_Image::~Fl_RGB_Image() {
  if (id) fl_delete_offscreen((Fl_Offscreen)id);
}

void Fl_RGB_Image::draw(int XP, int YP, int WP, int HP, int cx, int cy) {
  // account for current clip region (faster on Irix):
  int X,Y,W,H; fl_clip_box(XP,YP,WP,HP,X,Y,W,H);
  cx += X-XP; cy += Y-YP;
  // clip the box down to the size of image, quit if empty:
  if (cx < 0) {W += cx; X -= cx; cx = 0;}
  if (cx+W > w()) W = w()-cx;
  if (W <= 0) return;
  if (cy < 0) {H += cy; Y -= cy; cy = 0;}
  if (cy+H > h()) H = h()-cy;
  if (H <= 0) return;
  if (!id) {
    id = (ulong)fl_create_offscreen(w(), h());
    fl_begin_offscreen((Fl_Offscreen)id);
    fl_draw_image(array, 0, 0, w(), h(), d, ld);
    fl_end_offscreen();
  }
  fl_copy_offscreen(X, Y, W, H, (Fl_Offscreen)id, cx, cy);
}

void Fl_RGB_Image::label(Fl_Widget* w) {
  w->image(this);
}

void Fl_RGB_Image::label(Fl_Menu_Item* m) {
}


//
// End of "$Id: Fl_Image.cxx,v 1.5.2.3.2.1 2001/08/05 23:58:54 easysw Exp $".
//
