//
// "$Id$"
//
// implementation of fltk3::Device class for the Fast Light Tool Kit (FLTK).
//
// Copyright 2010-2011 by Bill Spitzak and others.
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
// Please report all bugs and problems to:
//
//     http://www.fltk.org/str.php
//

#include <fltk3/run.h>
#include <fltk3/GraphicsDriver.h>
#include <fltk3/Image.h>


// Pointer to the fltk3::GraphicsDriver object that currently handles all graphics operations
FLTK3_EXPORT fltk3::GraphicsDriver *fltk3::graphics_driver; 

const fltk3::GraphicsDriver::matrix fltk3::GraphicsDriver::m0 = {1, 0, 0, 1, 0, 0};

fltk3::GraphicsDriver::GraphicsDriver() {
  font_ = 0;
  size_ = 0;
  sptr=0; rstackptr=0; 
  rstack[0] = NULL;
  fl_clip_state_number=0;
  m = m0; 
  fl_matrix = &m; 
  p = (XPOINT *)0;
  font_descriptor_ = NULL;
  p_size = 0;
  n = 0;
  o.x = o.y = 0;
  optr = 0;
}

void fltk3::GraphicsDriver::text_extents(const char*t, int n, int& dx, int& dy, int& w, int& h)
{
  w = (int)width(t, n);
  h = - height();
  dx = 0;
  dy = descent();
}

//
// End of "$Id$".
//
