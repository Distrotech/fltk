//
// "$Id: Fl_BMP_Image.cxx,v 1.1.2.4 2002/05/25 02:56:59 easysw Exp $"
//
// Fl_BMP_Image routines.
//
// Copyright 1997-2002 by Easy Software Products.
// Image support donated by Matthias Melcher, Copyright 2000.
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
// Contents:
//
//   Fl_BMP_Image::Fl_BMP_Image() - Load a BMP image file.
//

//
// Include necessary header files...
//

#include <FL/Fl_BMP_Image.H>
#include <config.h>
#include <stdio.h>
#include <stdlib.h>


//
// BMP definitions...
//

#ifndef BI_RGB
#  define BI_RGB       0             // No compression - straight BGR data
#  define BI_RLE8      1             // 8-bit run-length compression
#  define BI_RLE4      2             // 4-bit run-length compression
#  define BI_BITFIELDS 3             // RGB bitmap with RGB masks
#endif // !BI_RGB


//
// Local functions...
//

static int		read_long(FILE *fp);
static unsigned short	read_word(FILE *fp);
static unsigned int	read_dword(FILE *fp);


//
// 'Fl_BMP_Image::Fl_BMP_Image()' - Load a BMP image file.
//

Fl_BMP_Image::Fl_BMP_Image(const char *bmp) // I - File to read
  : Fl_RGB_Image(0,0,0) {
  FILE		*fp;		// File pointer
  int		info_size,	// Size of info header
		depth,		// Depth of image (bits)
		compression,	// Type of compression
		colors_used,	// Number of colors used
		x, y,		// Looping vars
		color,		// Color of RLE pixel
		count,		// Number of times to repeat
		temp,		// Temporary color
		align;		// Alignment bytes
  unsigned long	offbits;	// Offset to image data
  uchar		bit,		// Bit in image
		byte;		// Byte in image
  uchar		*ptr;		// Pointer into pixels
  uchar		colormap[256][3];// Colormap

  // Open the file...
  if ((fp = fopen(bmp, "rb")) == NULL) return;

  // Get the header...
  getc(fp);			// Skip "BM" sync chars
  getc(fp);
  read_dword(fp);		// Skip size
  read_word(fp);		// Skip reserved stuff
  read_word(fp);
  offbits = read_dword(fp);	// Read offset to image data

  // Then the bitmap information...
  info_size = read_dword(fp);
  w(read_long(fp));
  h(read_long(fp));
  read_word(fp);
  depth = read_word(fp);

  if (info_size < 40) {
    // Old Windows/OS2 BMP header...
    compression = BI_RGB;
    colors_used = 0;

    count = info_size - 12;
  } else {
    // New BMP header...
    compression = read_dword(fp);
    read_dword(fp);
    read_long(fp);
    read_long(fp);
    colors_used = read_dword(fp);
    read_dword(fp);

    count = info_size - 40;
  }

  // Skip remaining header bytes...
  while (count > 0) {
    getc(fp);
    count --;
  }

  // Get colormap...
  if (colors_used == 0 && depth <= 8)
    colors_used = 1 << depth;

  for (count = 0; count < colors_used; count ++) {
    // Read BGR color...
    fread(colormap, colors_used, 3, fp);

    // Skip pad byte for new BMP files...
    if (info_size > 12) getc(fp);
  }

  // Setup image and buffers...
  d(3);
  fseek(fp, offbits, SEEK_SET);

  array = new uchar[w() * h() * d()];
  alloc_array = 1;

  // Read the image data...
  color = 0;
  count = 0;
  align = 0;
  byte  = 0;
  temp  = 0;

  for (y = h() - 1; y >= 0; y --) {
    ptr = (uchar *)array + y * w() * d();

    switch (depth)
    {
      case 1 : // Bitmap
          for (x = w(), bit = 128; x > 0; x --) {
	    if (bit == 128) byte = getc(fp);

	    if (byte & bit) {
	      *ptr++ = colormap[1][2];
	      *ptr++ = colormap[1][1];
	      *ptr++ = colormap[1][0];
	    } else {
	      *ptr++ = colormap[0][2];
	      *ptr++ = colormap[0][1];
	      *ptr++ = colormap[0][0];
	    }

	    if (bit > 1)
	      bit >>= 1;
	    else
	      bit = 128;
	  }

          // Read remaining bytes to align to 32 bits...
	  for (temp = (w() + 7) / 8; temp & 3; temp ++) {
	    getc(fp);
	  }
          break;

      case 4 : // 16-color
          for (x = w(), bit = 0xf0; x > 0; x --) {
	    // Get a new count as needed...
            if (compression != BI_RLE4 && count == 0) {
	      count = 2;
	      color = -1;
            }

	    if (count == 0) {
	      while (align > 0) {
	        align --;
		getc(fp);
              }

	      if ((count = getc(fp)) == 0) {
		if ((count = getc(fp)) == 0) {
		  // End of line...
                  x ++;
		  continue;
		} else if (count == 1) {
                  // End of image...
		  break;
		} else if (count == 2) {
		  // Delta...
		  count = getc(fp) * getc(fp) * w();
		  color = 0;
		} else {
		  // Absolute...
		  color = -1;
		  align = ((4 - (count & 3)) / 2) & 1;
		}
	      } else {
	        color = getc(fp);
	      }
            }

            // Get a new color as needed...
	    count --;

            if (bit == 0xf0) {
              if (color < 0) temp = getc(fp);
	      else temp = color;

              // Copy the color value...
	      *ptr++ = colormap[temp >> 4][2];
	      *ptr++ = colormap[temp >> 4][1];
	      *ptr++ = colormap[temp >> 4][0];
	      bit    = 0x0f;
            } else {
              // Copy the color value...
	      *ptr++ = colormap[temp & 15][2];
	      *ptr++ = colormap[temp & 15][1];
	      *ptr++ = colormap[temp & 15][0];
	      bit    = 0xf0;
	    }
	  }

	  if (!compression) {
            // Read remaining bytes to align to 32 bits...
	    for (temp = (w() + 1) / 2; temp & 3; temp ++) {
	      getc(fp);
	    }
	  }
          break;

      case 8 : // 256-color
          for (x = w(); x > 0; x --) {
	    // Get a new count as needed...
            if (compression != BI_RLE8) {
	      count = 1;
	      color = -1;
            }

	    if (count == 0) {
	      while (align > 0) {
	        align --;
		getc(fp);
              }

	      if ((count = getc(fp)) == 0) {
		if ((count = getc(fp)) == 0) {
		  // End of line...
                  x ++;
		  continue;
		} else if (count == 1) {
		  // End of image...
		  break;
		} else if (count == 2) {
		  // Delta...
		  count = getc(fp) * getc(fp) * w();
		  color = 0;
		} else {
		  // Absolute...
		  color = -1;
		  align = (2 - (count & 1)) & 1;
		}
	      } else {
	        color = getc(fp);
              }
            }

            // Get a new color as needed...
            if (color < 0) temp = getc(fp);
	    else temp = color;

            count --;

            // Copy the color value...
	    *ptr++ = colormap[temp][2];
	    *ptr++ = colormap[temp][1];
	    *ptr++ = colormap[temp][0];
	  }

	  if (!compression) {
            // Read remaining bytes to align to 32 bits...
	    for (temp = w(); temp & 3; temp ++) {
	      getc(fp);
	    }
	  }
          break;

      case 24 : // 24-bit RGB
          for (x = w(); x > 0; x --, ptr += 3) {
	    ptr[2] = getc(fp);
	    ptr[1] = getc(fp);
	    ptr[0] = getc(fp);
	  }

          // Read remaining bytes to align to 32 bits...
	  for (temp = w() * 3; temp & 3; temp ++) {
	    getc(fp);
	  }
          break;
    }
  }

  // Close the file and return...
  fclose(fp);
}


//
// 'read_word()' - Read a 16-bit unsigned integer.
//

static unsigned short	// O - 16-bit unsigned integer
read_word(FILE *fp) {	// I - File to read from
  unsigned char b0, b1;	// Bytes from file

  b0 = getc(fp);
  b1 = getc(fp);

  return ((b1 << 8) | b0);
}


//
// 'read_dword()' - Read a 32-bit unsigned integer.
//

static unsigned int		// O - 32-bit unsigned integer
read_dword(FILE *fp) {		// I - File to read from
  unsigned char b0, b1, b2, b3;	// Bytes from file

  b0 = getc(fp);
  b1 = getc(fp);
  b2 = getc(fp);
  b3 = getc(fp);

  return ((((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
}


//
// 'read_long()' - Read a 32-bit signed integer.
//

static int			// O - 32-bit signed integer
read_long(FILE *fp) {		// I - File to read from
  unsigned char b0, b1, b2, b3;	// Bytes from file

  b0 = getc(fp);
  b1 = getc(fp);
  b2 = getc(fp);
  b3 = getc(fp);

  return ((int)(((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
}


//
// End of "$Id: Fl_BMP_Image.cxx,v 1.1.2.4 2002/05/25 02:56:59 easysw Exp $".
//
