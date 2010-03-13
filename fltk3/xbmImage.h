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
// "$Id: Fl_XBM_Image.H 6614 2009-01-01 16:11:32Z matt $"
//
// XBM image header file for the Fast Light Tool Kit (FLTK).
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
   Fl_XBM_Image class . */

#ifndef Fl_XBM_Image_H
#define Fl_XBM_Image_H
#  include "Bitmap.h"

/**
  The Fl_XBM_Image class supports loading, caching,
  and drawing of X Bitmap (XBM) bitmap files.
*/
class FL_EXPORT Fl_XBM_Image : public Fl_Bitmap {

  public:

  Fl_XBM_Image(const char* filename);
};

#endif // !Fl_XBM_Image_H

//
// End of "$Id: Fl_XBM_Image.H 6614 2009-01-01 16:11:32Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::xbmImage
class Fl_XBM_Image : public fltk::xbmImage {
public:
  Fl_XBM_Image(int x, int t, int w, int h, const char *label=0)
  : fltk::xbmImage(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_XBM_Image.H 6614 2009-01-01 16:11:32Z matt $"
//
// XBM image header file for the Fast Light Tool Kit (FLTK).
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
   Fl_XBM_Image class . */

#ifndef Fl_XBM_Image_H
#define Fl_XBM_Image_H
#  include "Fl_Bitmap.H"

/**
  The Fl_XBM_Image class supports loading, caching,
  and drawing of X Bitmap (XBM) bitmap files.
*/
class FL_EXPORT Fl_XBM_Image : public Fl_Bitmap {

  public:

  Fl_XBM_Image(const char* filename);
};

#endif // !Fl_XBM_Image_H

//
// End of "$Id: Fl_XBM_Image.H 6614 2009-01-01 16:11:32Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id: xbmImage.h 5581 2007-01-05 03:04:04Z spitzak $"
//
// Image subclass for in-memory xbm data (you #include the .xbm file
// and then construct this).
//
// Copyright 2002 by Bill Spitzak and others.
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

#ifndef fltk_xbmImage_h
#define fltk_xbmImage_h

#include "Image.h"

namespace fltk {

class FL_API xbmImage : public Image {
public:
  const unsigned char *array;
  xbmImage(const unsigned char *bits, int w,int h) :
    Image(fltk::MASK,w,h), array(bits) {}
  xbmImage(const char *bits, int w, int h) :
    Image(fltk::MASK,w,h), array((const unsigned char *)bits) {}
  bool fetch();
};

}

#endif

//
// End of "$Id: xbmImage.h 5581 2007-01-05 03:04:04Z spitzak $".
//
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
