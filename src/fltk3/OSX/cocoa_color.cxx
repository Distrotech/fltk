//
// "$Id$"
//
// MacOS color functions for the Fast Light Tool Kit (FLTK).
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

#ifdef __APPLE__

// The fltk "colormap".  This allows ui colors to be stored in 8-bit
// locations, and provides a level of indirection so that global color
// changes can be made.  Not to be confused with the X colormap, which
// I try to hide completely.

// matt: Neither Quartz nor Quickdraw support colormaps in this implementation
// matt: Quartz support done

#include <config.h>
#include <fltk3/run.h>
#include <fltk3/x.h>
#include <fltk3/draw.h>

extern unsigned fl_cmap[256];

void fltk3::set_color(fltk3::Color i, unsigned c) {
  if (fl_cmap[i] != c) {
    fl_cmap[i] = c;
  }
}

#endif

//
// End of "$Id$".
//