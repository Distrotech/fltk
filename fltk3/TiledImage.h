//
// "$Id$"
//

// 123 TODO: remove stray comments
// 123 TODO: add namespace statements
// 123 TODO: replace class name, constructors and destructor
// 123 TODO: add friend statement for Twin Class
// 123 TODO: add 'compat(FLTK2)' to constructors
// 123 TODO: add twin class with all constructors
// 123 TODO: change all arguments to the FLTK2 class name
// 123 TODO: change the source code to use the new class names
// 123 TODO: add casting to return values
// 123 TODO: move all FLTK2-only functions to the FLTK3 section and implement them
// 123 TODO: remove the FLTK1 and FLTK2 sections in the headers
// 123 TODO: 

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
   Fl_Tiled_Image widget . */

#ifndef Fl_Tiled_Image_H
#  define Fl_Tiled_Image_H

#  include "Image.h"


/**
  This class supports tiling of images
  over a specified area. The source (tile) image is <B>not</B>
  copied unless you call the color_average(),
  desaturate(),
  or inactive()
  methods.
*/
class FL_EXPORT Fl_Tiled_Image : public Fl_Image {
  protected:

  Fl_Image	*image_;		// The image that is shared
  int		alloc_image_;		// Did we allocate this image?

  public:

  Fl_Tiled_Image(Fl_Image *i, int W = 0, int H = 0);
  virtual ~Fl_Tiled_Image();

  virtual Fl_Image *copy(int W, int H);
  Fl_Image *copy() { return copy(w(), h()); }
  virtual void color_average(Fl_Color c, float i);
  virtual void desaturate();
  virtual void draw(int X, int Y, int W, int H, int cx, int cy);
  void draw(int X, int Y) { draw(X, Y, w(), h(), 0, 0); }
  /** Gets The image that is shared */ 
  Fl_Image *image() { return image_; }
};

#endif // !Fl_Tiled_Image_H

//
// End of "$Id: Fl_Tiled_Image.H 6614 2009-01-01 16:11:32Z matt $"
//

/* suggested twin class
// This is the Twin Class to fltk::TiledImage
class Fl_Tiled_Image : public fltk::TiledImage {
public:
  Fl_Tiled_Image(int x, int t, int w, int h, const char *label=0)
  : fltk::TiledImage(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
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
   Fl_Tiled_Image widget . */

#ifndef Fl_Tiled_Image_H
#  define Fl_Tiled_Image_H

#  include "Fl_Image.H"


/**
  This class supports tiling of images
  over a specified area. The source (tile) image is <B>not</B>
  copied unless you call the color_average(),
  desaturate(),
  or inactive()
  methods.
*/
class FL_EXPORT Fl_Tiled_Image : public Fl_Image {
  protected:

  Fl_Image	*image_;		// The image that is shared
  int		alloc_image_;		// Did we allocate this image?

  public:

  Fl_Tiled_Image(Fl_Image *i, int W = 0, int H = 0);
  virtual ~Fl_Tiled_Image();

  virtual Fl_Image *copy(int W, int H);
  Fl_Image *copy() { return copy(w(), h()); }
  virtual void color_average(Fl_Color c, float i);
  virtual void desaturate();
  virtual void draw(int X, int Y, int W, int H, int cx, int cy);
  void draw(int X, int Y) { draw(X, Y, w(), h(), 0, 0); }
  /** Gets The image that is shared */ 
  Fl_Image *image() { return image_; }
};

#endif // !Fl_Tiled_Image_H

//
// End of "$Id: Fl_Tiled_Image.H 6614 2009-01-01 16:11:32Z matt $"
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id: TiledImage.h 5810 2007-05-11 22:44:12Z spitzak $"
//
// A tiled image completely fills the bounding box passed to it with
// replications of the internal Image passed to it.
//
// Copyright 1998-2006 by Bill Spitzak and others.
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

#ifndef fltk_TiledImage_h
#define fltk_TiledImage_h

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
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
