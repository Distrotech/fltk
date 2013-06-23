//
// "$Id$"
//
// Color functions for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2010 by Bill Spitzak and others.
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

/**
  \file fl_color.cxx
  \brief Color handling
*/

// Implementation of fltk3::color(i), fltk3::color(r,g,b).

#  include "xcolor.h"
#  include <fltk3/run.h>
#  include <fltk3/x.h>
#  include <fltk3/draw.h>

unsigned fl_cmap[256] = {
#include "cmap.h" // this is a file produced by "cmap_cxx":
};

/**
    Returns the RGB value(s) for the given FLTK color index.
    
    This form returns the RGB values packed in a 32-bit unsigned
    integer with the red value in the upper 8 bits, the green value
    in the next 8 bits, and the blue value in bits 8-15.  The lower
    8 bits will always be 0.
*/
unsigned fltk3::get_color(fltk3::Color i) {
  if (i & 0xffffff00) return (i);
  else return fl_cmap[i];
}
/**
    Sets an entry in the fltk3::color index table.  You can set it to
    any 8-bit RGB color.  The color is not allocated until fltk3::color(i)
    is used.
*/
void fltk3::set_color(fltk3::Color i, uchar red, uchar green, uchar blue) {
  fltk3::set_color((fltk3::Color)(i & 255),
	((unsigned)red<<24)+((unsigned)green<<16)+((unsigned)blue<<8));
}
/**
    Returns the RGB value(s) for the given FLTK color index. 
    
    This form returns the red, green, and blue values
    separately in referenced variables.

    See also unsigned get_color(fltk3::Color c)
 */
void fltk3::get_color(fltk3::Color i, uchar &red, uchar &green, uchar &blue) {
  unsigned c;

  if (i & 0xffffff00) c = (unsigned)i;
  else c = fl_cmap[i];

  red   = uchar(c>>24);
  green = uchar(c>>16);
  blue  = uchar(c>>8);
}

/**
  Returns the weighted average color between the two given colors.
  The red, green and blue values are averages using the following formula:
  \code
  color = color1 * weight  + color2 * (1 - weight)
  \endcode
  Thus, a \p weight value of 1.0 will return the first color, while a
  value of 0.0 will return the second color.
  \param[in] color1, color2 boundary colors
  \param[in] weight weighting factor
*/
fltk3::Color fltk3::color_average(fltk3::Color color1, fltk3::Color color2, float weight) {
  unsigned rgb1;
  unsigned rgb2;
  uchar r, g, b;

  if (color1 & 0xffffff00) rgb1 = color1;
  else rgb1 = fl_cmap[color1 & 255];

  if (color2 & 0xffffff00) rgb2 = color2;
  else rgb2 = fl_cmap[color2 & 255];

  r = (uchar)(((uchar)(rgb1>>24))*weight + ((uchar)(rgb2>>24))*(1-weight));
  g = (uchar)(((uchar)(rgb1>>16))*weight + ((uchar)(rgb2>>16))*(1-weight));
  b = (uchar)(((uchar)(rgb1>>8))*weight + ((uchar)(rgb2>>8))*(1-weight));

  return fltk3::rgb_color(r, g, b);
}

/**
  Returns the inactive, dimmed version of the given color
*/
fltk3::Color fltk3::inactive(fltk3::Color c) {
  return fltk3::color_average(c, fltk3::GRAY, .33f);
}

/**
  Returns a color that contrasts with the background color.
  This will be the foreground color if it contrasts sufficiently with the
  background color. Otherwise, returns \p fltk3::WHITE or \p fltk3::BLACK depending
  on which color provides the best contrast.
  \param[in] fg,bg foreground and background colors
  \return contrasting color
*/
fltk3::Color fltk3::contrast(fltk3::Color fg, fltk3::Color bg) {
  unsigned c1, c2;	// RGB colors
  int l1, l2;		// Luminosities


  // Get the RGB values for each color...
  if (fg & 0xffffff00) c1 = (unsigned)fg;
  else c1 = fl_cmap[fg];

  if (bg & 0xffffff00) c2 = (unsigned)bg;
  else c2 = fl_cmap[bg];

  // Compute the luminosity...
  l1 = ((c1 >> 24) * 30 + ((c1 >> 16) & 255) * 59 + ((c1 >> 8) & 255) * 11) / 100;
  l2 = ((c2 >> 24) * 30 + ((c2 >> 16) & 255) * 59 + ((c2 >> 8) & 255) * 11) / 100;

  // Compare and return the contrasting color...
  if ((l1 - l2) > 99) return fg;
  else if ((l2 - l1) > 99) return fg;
  else if (l2 > 127) return fltk3::BLACK;
  else return fltk3::WHITE;
}
/**
   @}
*/
//
// End of "$Id$".
//
