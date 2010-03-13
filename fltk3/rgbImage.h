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
// "$Id: Fl_RGB_Image.H 6942 2009-11-18 12:22:51Z AlbrechtS $"
//
// RGB Image header file for the Fast Light Tool Kit (FLTK).
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

#ifndef Fl_RGB_Image_H
# define Fl_RGB_Image_H
# include "Fl_Image.H"
#endif // !Fl_RGB_Image_H

//
// End of "$Id: Fl_RGB_Image.H 6942 2009-11-18 12:22:51Z AlbrechtS $".
//

/* suggested twin class
// This is the Twin Class to fltk::rgbImage
class Fl_RGB_Image : public fltk::rgbImage {
public:
  Fl_RGB_Image(int x, int t, int w, int h, const char *label=0)
  : fltk::rgbImage(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_RGB_Image.H 6942 2009-11-18 12:22:51Z AlbrechtS $"
//
// RGB Image header file for the Fast Light Tool Kit (FLTK).
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

#ifndef Fl_RGB_Image_H
# define Fl_RGB_Image_H
# include "Fl_Image.H"
#endif // !Fl_RGB_Image_H

//
// End of "$Id: Fl_RGB_Image.H 6942 2009-11-18 12:22:51Z AlbrechtS $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id: rgbImage.h 5568 2006-12-30 07:54:24Z spitzak $"
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

// This is an obsolete class from fltk2 development. All functionality
// has been moved to the base Image class.

#ifndef fltk_rgbImage_h
#define fltk_rgbImage_h

#include "Image.h"

namespace fltk {

class FL_API rgbImage : public Image {
public:
  //bool write_jpeg(const char *filename, int quality=75, int dpi=150);
  rgbImage(const char* name=0) : Image(name) {}
  rgbImage(const uchar* d, PixelType p, int W, int H) :
    Image(d,p,W,H,fltk::depth(p)*W) {}
  rgbImage(const uchar* d, PixelType p, int W, int H, int linedelta) :
    Image(d,p,W,H,linedelta) {}
};

}

#endif

//
// End of "$Id: rgbImage.h 5568 2006-12-30 07:54:24Z spitzak $".
//
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
