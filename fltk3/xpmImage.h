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
// "$Id: Fl_XPM_Image.H 6614 2009-01-01 16:11:32Z matt $"
//
// XPM image header file for the Fast Light Tool Kit (FLTK).
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
  
   Fl_XPM_Image class . */

#ifndef Fl_XPM_Image_H
#define Fl_XPM_Image_H
#  include "Pixmap.h"

/**
  The Fl_XPM_Image class supports loading, caching,
  and drawing of X Pixmap (XPM) images, including transparency.
*/
class FL_EXPORT Fl_XPM_Image : public Fl_Pixmap {

  public:

  Fl_XPM_Image(const char* filename);
};

#endif // !Fl_XPM_Image

//
// End of "$Id: Fl_XPM_Image.H 6614 2009-01-01 16:11:32Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::xpmImage
class Fl_XPM_Image : public fltk::xpmImage {
public:
  Fl_XPM_Image(int x, int t, int w, int h, const char *label=0)
  : fltk::xpmImage(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_XPM_Image.H 6614 2009-01-01 16:11:32Z matt $"
//
// XPM image header file for the Fast Light Tool Kit (FLTK).
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
  
   Fl_XPM_Image class . */

#ifndef Fl_XPM_Image_H
#define Fl_XPM_Image_H
#  include "Fl_Pixmap.H"

/**
  The Fl_XPM_Image class supports loading, caching,
  and drawing of X Pixmap (XPM) images, including transparency.
*/
class FL_EXPORT Fl_XPM_Image : public Fl_Pixmap {

  public:

  Fl_XPM_Image(const char* filename);
};

#endif // !Fl_XPM_Image

//
// End of "$Id: Fl_XPM_Image.H 6614 2009-01-01 16:11:32Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id: xpmImage.h 5568 2006-12-30 07:54:24Z spitzak $"
//
// Image subclass that draws the data from an xpm format file.
// XPM is a file format designed for small icons in X, it can
// be convienently #include'd to inline the image into a program.
// Just pass the pointer defined by the file to the constructor.
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

#ifndef fltk_xpmImage_h
#define fltk_xpmImage_h

#include "Image.h"

namespace fltk {

class FL_API xpmImage : public Image {
public:
  const char * const * data;
  // XPM files define the data all kinds of ways, so the constructor
  // is overloaded to accept all the ones we have seen:
  xpmImage(const char * const * d, const char* name = 0) :
    Image(name), data(d) {}
  xpmImage(const unsigned char* const * d, const char* name = 0) :
    Image(name), data((char**)d) {}
  xpmImage(char ** d, const char* name = 0) :
    Image(name), data(d) {}
  bool fetch();

  //! For xpmFileImage to reuse fetch() code.
  static bool fetch(Image&, const char* const* data);
};

}

#endif

//
// End of "$Id: xpmImage.h 5568 2006-12-30 07:54:24Z spitzak $".
//
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
