/+- This file was imported from C++ using a script
//
// "$Id: xbm_image.d 4288 2005-04-16 00:13:17Z mike $"
//
// XBM image header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2005 by Bill Spitzak and others.
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

module fl.xbm_image;

public import fl.bitmap;

class Fl_XBM_Image : Fl_Bitmap {

  public:

  Fl_XBM_Image(char* filename);
};

} // !Fl_XBM_Image_H

//
// End of "$Id: xbm_image.d 4288 2005-04-16 00:13:17Z mike $".
//
    End of automatic import -+/
/+- This file was imported from C++ using a script
//
// "$Id: xbm_image.d 5190 2006-06-09 16:16:34Z mike $"
//
// Fl_XBM_Image routines.
//
// Copyright 1997-2005 by Bill Spitzak and others.
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
//   Fl_XBM_Image.Fl_XBM_Image() - Load an XBM file.
//

//
// Include necessary header files...
//

#include <FL/Fl.H>
private import fl.xbm_image;
#include <stdio.h>
#include <stdlib.h>
private import fl.flstring;

//
// 'Fl_XBM_Image.Fl_XBM_Image()' - Load an XBM file.
//

Fl_XBM_Image.Fl_XBM_Image(char *name) : Fl_Bitmap((char *)0,0,0) {
  FILE	*f;
  ubyte	*ptr;

  if ((f = fopen(name, "rb")) == NULL) return;

  char buffer[1024];
  char junk[1024];
  int wh[2]; // width and height
  int i;
  for (i = 0; i<2; i++) {
    for (;;) {
      if (!fgets(buffer,1024,f)) {
        fclose(f);
	return;
      }
      int r = sscanf(buffer,"#define %s %d",junk,&wh[i]);
      if (r >= 2) break;
    }
  }

  // skip to data array:
  for (;;) {
    if (!fgets(buffer,1024,f)) {
      fclose(f);
      return;
    }
    if (!strncmp(buffer,"static ",7)) break;
  }

  // Allocate memory...
  w(wh[0]);
  h(wh[1]);

  int n = ((wh[0]+7)/8)*wh[1];
  array = new ubyte[n];

  // read the data:
  for (i = 0, ptr = (ubyte *)array; i < n;) {
    if (!fgets(buffer,1024,f)) {
      fclose(f);
      return;
    }
    char *a = buffer;
    while (*a && i<n) {
      uint t;
      if (sscanf(a," 0x%x",&t)>0) {
        *ptr++ = (ubyte)t;
	i ++;
      }
      while (*a && *a++ != ',');
    }
  }

  fclose(f);
}


//
// End of "$Id: xbm_image.d 5190 2006-06-09 16:16:34Z mike $".
//
    End of automatic import -+/
