//
// "$Id$"
//
// Tiled image code for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2009 by Bill Spitzak and others.
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


#include <FL/Fl.H>
#include <FL/Fl_Tiled_Image.H>
#include <FL/fl_draw.H>

/**
  The constructors create a new tiled image containing the specified image.
  Use a width and height of 0 to tile the whole window/widget.
*/
fltk::TiledImage::TiledImage(Fl_Image *i,	// I - Image to tile
                               int      W,	// I - Width of tiled area
			       int      H) :	// I - Height of tiled area
  Fl_Image(W,H,0) {
  image_       = i;
  alloc_image_ = 0;

    if (W == 0) w(fltk::w());
    if (H == 0) h(fltk::h());
}
/**
  The destructor frees all memory and server resources that are used by
  the tiled image.
*/
fltk::TiledImage::~TiledImage() {
  if (alloc_image_) delete image_;
}


//
// 'fltk::TiledImage::copy()' - Copy and resize a tiled image...
//

Fl_Image *			// O - New image
fltk::TiledImage::copy(int W,	// I - New width
                     int H) {	// I - New height
  if (W == w() && H == h()) return this;
  else return new fltk::TiledImage(image_, W, H);
}


//
// 'fltk::TiledImage::color_average()' - Blend colors...
//

void
fltk::TiledImage::color_average(Fl_Color c,	// I - Color to blend with
                              float    i) {	// I - Blend fraction
  if (!alloc_image_) {
    image_       = image_->copy();
    alloc_image_ = 1;
  }

  image_->color_average(c, i);
}


//
// 'fltk::TiledImage::desaturate()' - Convert the image to grayscale...
//

void
fltk::TiledImage::desaturate() {
  if (!alloc_image_) {
    image_       = image_->copy();
    alloc_image_ = 1;
  }

  image_->desaturate();
}


//
// 'fltk::TiledImage::draw()' - Draw a shared image...
//

void
fltk::TiledImage::draw(int X,	// I - Starting X position
                     int Y,	// I - Starting Y position
		     int W,	// I - Width of area to be filled
		     int H,	// I - Height of area to be filled
		     int cx,	// I - "Source" X position
		     int cy) {	// I - "Source" Y position
  if (!image_->w() || !image_->h()) return;
  if (W == 0) W = fltk::w();
  if (H == 0) H = fltk::h();

  fl_push_clip(X, Y, W, H);

  X += cx;
  Y += cy;

  X = X - (X % image_->w());
  Y = Y - (Y % image_->h());

  W += X;
  H += Y;

  for (int yy = Y; yy < H; yy += image_->h())
    for (int xx = X; xx < W; xx += image_->w())
      image_->draw(xx, yy);

  fl_pop_clip();
}


//
// End of "$Id$".
//
