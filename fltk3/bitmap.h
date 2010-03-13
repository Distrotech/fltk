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
// "$Id: Fl_Bitmap.H 6614 2009-01-01 16:11:32Z matt $"
//
// Bitmap header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Bitmap widget . */

#ifndef Fl_Bitmap_H
#define Fl_Bitmap_H
#  include "Image.h"

class Fl_Widget;
struct Fl_Menu_Item;

/**
  The Fl_Bitmap class supports caching and drawing of mono-color
  (bitmap) images. Images are drawn using the current color.
*/
class FL_EXPORT Fl_Bitmap : public Fl_Image {
  public:

  /** pointer to raw bitmap data */
  const uchar *array;
  /** Non-zero if array points to bitmap data allocated internally */
  int alloc_array;
#if defined(__APPLE__) || defined(WIN32)
  /** for internal use */
  void *id;
#else
  /** for internal use */
  unsigned id;
#endif // __APPLE__ || WIN32
  /** The constructors create a new bitmap from the specified bitmap data */
  Fl_Bitmap(const uchar *bits, int W, int H) :
    Fl_Image(W,H,0), array(bits), alloc_array(0), id(0) {data((const char **)&array, 1);}
  /** The constructors create a new bitmap from the specified bitmap data */
  Fl_Bitmap(const char *bits, int W, int H) :
    Fl_Image(W,H,0), array((const uchar *)bits), alloc_array(0), id(0) {data((const char **)&array, 1);}
  virtual ~Fl_Bitmap();
  virtual Fl_Image *copy(int W, int H);
  Fl_Image *copy() { return copy(w(), h()); }
  virtual void draw(int X, int Y, int W, int H, int cx=0, int cy=0);
  void draw(int X, int Y) {draw(X, Y, w(), h(), 0, 0);}
  virtual void label(Fl_Widget*w);
  virtual void label(Fl_Menu_Item*m);
  virtual void uncache();
};

#endif

//
// End of "$Id: Fl_Bitmap.H 6614 2009-01-01 16:11:32Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::bitmap
class Fl_Bitmap : public fltk::bitmap {
public:
  Fl_Bitmap(int x, int t, int w, int h, const char *label=0)
  : fltk::bitmap(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Bitmap.H 6614 2009-01-01 16:11:32Z matt $"
//
// Bitmap header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Bitmap widget . */

#ifndef Fl_Bitmap_H
#define Fl_Bitmap_H
#  include "Fl_Image.H"

class Fl_Widget;
struct Fl_Menu_Item;

/**
  The Fl_Bitmap class supports caching and drawing of mono-color
  (bitmap) images. Images are drawn using the current color.
*/
class FL_EXPORT Fl_Bitmap : public Fl_Image {
  public:

  /** pointer to raw bitmap data */
  const uchar *array;
  /** Non-zero if array points to bitmap data allocated internally */
  int alloc_array;
#if defined(__APPLE__) || defined(WIN32)
  /** for internal use */
  void *id;
#else
  /** for internal use */
  unsigned id;
#endif // __APPLE__ || WIN32
  /** The constructors create a new bitmap from the specified bitmap data */
  Fl_Bitmap(const uchar *bits, int W, int H) :
    Fl_Image(W,H,0), array(bits), alloc_array(0), id(0) {data((const char **)&array, 1);}
  /** The constructors create a new bitmap from the specified bitmap data */
  Fl_Bitmap(const char *bits, int W, int H) :
    Fl_Image(W,H,0), array((const uchar *)bits), alloc_array(0), id(0) {data((const char **)&array, 1);}
  virtual ~Fl_Bitmap();
  virtual Fl_Image *copy(int W, int H);
  Fl_Image *copy() { return copy(w(), h()); }
  virtual void draw(int X, int Y, int W, int H, int cx=0, int cy=0);
  void draw(int X, int Y) {draw(X, Y, w(), h(), 0, 0);}
  virtual void label(Fl_Widget*w);
  virtual void label(Fl_Menu_Item*m);
  virtual void uncache();
};

#endif

//
// End of "$Id: Fl_Bitmap.H 6614 2009-01-01 16:11:32Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
