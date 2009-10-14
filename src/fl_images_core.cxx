//
// "$Id$"
//
// FLTK images library core.
//
// Copyright 1997-2009 by Easy Software Products.
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
// Contents:
//
//   fltk::register_images() - Register the image formats.
//   fl_check_images()    - Check for a supported image format.
//

//
// Include necessary header files...
//

#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_BMP_Image.H>
#include <FL/Fl_GIF_Image.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_PNM_Image.H>
#include <stdio.h>
#include <stdlib.h>
#include "flstring.h"


//
// Define a simple global image registration function that registers
// the extra image formats that aren't part of the core FLTK library.
//

static Fl_Image	*fl_check_images(const char *name, uchar *header, int headerlen);


//
// 'fl_register_images()' - Register the image formats.
//

void fltk::register_images() {
  fltk::SharedImage::add_handler(fl_check_images);
}


//
// 'fl_check_images()' - Check for a supported image format.
//

Fl_Image *					// O - Image, if found
fl_check_images(const char *name,		// I - Filename
                uchar      *header,		// I - Header data from file
		int) {				// I - Amount of data (not used)
  if (memcmp(header, "GIF87a", 6) == 0 ||
      memcmp(header, "GIF89a", 6) == 0)	// GIF file
    return new Fl_GIF_Image(name);

  if (memcmp(header, "BM", 2) == 0)	// BMP file
    return new Fl_BMP_Image(name);

  if (header[0] == 'P' && header[1] >= '1' && header[1] <= '7')
					// Portable anymap
    return new Fl_PNM_Image(name);

#ifdef HAVE_LIBPNG
  if (memcmp(header, "\211PNG", 4) == 0)// PNG file
    return new Fl_PNG_Image(name);
#endif // HAVE_LIBPNG

#ifdef HAVE_LIBJPEG
  if (memcmp(header, "\377\330\377", 3) == 0 &&
					// Start-of-Image
      header[3] >= 0xc0 && header[3] <= 0xef)
	   				// APPn for JPEG file
    return new Fl_JPEG_Image(name);
#endif // HAVE_LIBJPEG

  return 0;
}


//
// End of "$Id$".
//
