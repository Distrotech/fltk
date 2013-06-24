//
// "$Id$"
//
// Rectangle drawing routines for the Fast Light Tool Kit (FLTK).
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
  \file fl_rect.cxx
  \brief Drawing and clipping routines for rectangles.
*/

// These routines from draw.h are used by the standard boxtypes
// and thus are always linked into an fltk program.
// Also all fl_clip routines, since they are always linked in so
// that minimal update works.

#include <config.h>
#include <fltk3/run.h>
#include <fltk3/Widget.h>
#include <fltk3/Printer.h>
#include <fltk3/draw.h>
#include <fltk3/x.h>

// fl_line_width_ must contain the absolute value of the current
// line width to be used for X11 clipping (see below).
// This is defined in src/fltk3::line_style.cxx
extern int fl_line_width_;

#ifdef __APPLE_QUARTZ__
extern float fl_quartz_line_width_;
#endif

void fltk3::GraphicsDriver::push_origin() {
  if (optr==origin_stack_size)
    fltk3::error("fltk3::push_origin(): origin stack overflow.");
  else
    ostack[optr++] = o;
}

void fltk3::GraphicsDriver::pop_origin() {
  if (optr==0)
    fltk3::error("fltk3::pop_origin(): origin stack underflow.");
  else 
    o = ostack[--optr];
}

void fltk3::GraphicsDriver::translate_origin(int dx, int dy) {
  o.x += dx;
  o.y += dy;
}

void fltk3::GraphicsDriver::origin(int x, int y) {
  o.x = x;
  o.y = y;
}

////////////////////////////////////////////////////////////////

void fltk3::GraphicsDriver::clip_region(fltk3::Region r) {
  fltk3::Region oldr = rstack[rstackptr];
  if (oldr) XDestroyRegion(oldr);
  rstack[rstackptr] = r;
  restore_clip();
}

void fltk3::GraphicsDriver::region_stack_push(fltk3::Region r) {
  if (rstackptr < region_stack_max) rstack[++rstackptr] = r;
  else fltk3::warning("fltk3::push_clip: clip stack overflow!\n");
}


// make there be no clip (used by fl_begin_offscreen() only!)
void fltk3::GraphicsDriver::push_no_clip() {
  if (rstackptr < region_stack_max) rstack[++rstackptr] = 0;
  else fltk3::warning("fltk3::push_no_clip: clip stack overflow!\n");
  restore_clip();
}

// pop back to previous clip:
void fltk3::GraphicsDriver::pop_clip() {
  if (rstackptr > 0) {
    fltk3::Region oldr = rstack[rstackptr--];
    if (oldr) XDestroyRegion(oldr);
  } else fltk3::warning("fltk3::pop_clip: clip stack underflow!\n");
  restore_clip();
}


//
// End of "$Id$".
//
