//
// "$Id: Fl_Tiled_Image.cxx,v 1.9 2004/07/04 20:14:16 laza2000 Exp $"
//
// Tiled image code for the Fast Light Tool Kit (FLTK).
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

#include <fltk/TiledImage.h>
#include <fltk/draw.h>
using namespace fltk;

// A tiled image "resizes" to completely fill any passed bounding box,
// so this can just return the values unchanged. This maximizes the
// values with the image size, though, because that allows the align
// code to change the part of the image seen when the image is bigger
// than the are to tile, and to fix old code that did not initialize
// the w & h, or code that assummes this always returns values greater
// than zero.
void TiledImage::_measure(float& w, float& h) const {
  if (!image_) return;
  float iw = w;
  float ih = h;
  image_->measure(iw,ih);
  if (iw > w) w = iw;
  if (ih > h) h = ih;
}

// Tiled image with minimal redraw
void TiledImage::_draw(int x, int y, int w, int h, const Style* style, Flags flags) const
{
  if (!image_) return;
  float fW = (float)w;
  float fH = (float)h;
  image_->measure(fW,fH); if (fW <= 0 || fH <= 0) return;
  int iw = int(fW);
  int ih = int(fH);
  int cx = 0;
  int cy = 0;
  // Perhaps this should use the Align flags to set cx, cy.

  // Figure out the smallest rectangle enclosing this and the clip region:
  int X,Y,W,H; clip_box(x,y,w,h, X, Y, W, H);
  if (W <= 0 || H <= 0) return;
  cx += X-int(x); cy += Y-int(y);
  push_clip(X, Y, W, H);

  int temp = -cx % iw;
  cx = (temp>0 ? iw : 0) - temp;
  temp = -cy % ih;
  cy = (temp>0 ? ih : 0) - temp;

  int ccx=cx;
  while (-cy < H) {
    while (-cx < W) {
      image_->draw(X-cx, Y-cy, iw, ih, style, flags);
      cx -= iw;
    }
    cy -= ih;
    cx = ccx;
  }
  pop_clip();
}

const BoxInfo* TiledImage::boxinfo() const {
  if (image_) return image_->boxinfo();
  else return Symbol::boxinfo();
}

//
// End of "$Id: Fl_Tiled_Image.cxx,v 1.9 2004/07/04 20:14:16 laza2000 Exp $".
//
