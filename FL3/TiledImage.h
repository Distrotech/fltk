//
// "$Id: Fl_Tiled_Image.H 6614 2009-01-01 16:11:32Z matt $"
//
// Tiled image header file for the Fast Light Tool Kit (FLTK).
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

/* \file
   fltk::TiledImage widget . */

#ifndef fltk3_tiled_image_h
#  define fltk3_tiled_image_h

#  include "../FL/Fl_Image.H"

namespace fltk {

/**
  This class supports tiling of images
  over a specified area. The source (tile) image is <B>not</B>
  copied unless you call the color_average(),
  desaturate(),
  or inactive()
  methods.
*/
  class FL_EXPORT TiledImage : public ::Fl_Image {
  protected:

  Fl_Image	*image_;		// The image that is shared
  int		alloc_image_;		// Did we allocate this image?

  public:

  TiledImage(Fl_Image *i, int W = 0, int H = 0);
  virtual ~TiledImage();

  virtual Fl_Image *copy(int W, int H);
  Fl_Image *copy() { return copy(w(), h()); }
  virtual void color_average(Fl_Color c, float i);
  virtual void desaturate();
  virtual void draw(int X, int Y, int W, int H, int cx, int cy);
  void draw(int X, int Y) { draw(X, Y, w(), h(), 0, 0); }
  /** Gets The image that is shared */ 
  Fl_Image *image() { return image_; }
}; // class TiledImage

}; // namespace fltk

#endif // !fltk::TiledImage_H

//==============================================================================
  
#if 0
  
#include "Symbol.h"

namespace fltk {

class FL_API TiledImage : public Symbol {
protected:
  const Symbol* image_;
public:
  TiledImage(Symbol *i) : Symbol(0), image_(i) {}
  const Symbol* image() const {return image_;}
  void image(const Symbol* i) {image_ = i;}
  void _measure(int& w, int& h) const;
  void _draw(const Rectangle&) const;
};

}
#endif

//
// End of "$Id: TiledImage.h 5810 2007-05-11 22:44:12Z spitzak $"
//
