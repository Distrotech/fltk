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

#ifdef USE_X11



#endif	// USE_X11


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


#if defined(__APPLE_QUARTZ__)
#elif defined(WIN32)

#include "MSWindows/GDIGraphicsDriver.h"

void fltk3::GDIGraphicsDriver::rect(int x, int y, int w, int h) {
  if (w<=0 || h<=0) return;
  x += origin_x(); y += origin_y();
  MoveToEx(fl_gc, x, y, 0L); 
  LineTo(fl_gc, x+w-1, y);
  LineTo(fl_gc, x+w-1, y+h-1);
  LineTo(fl_gc, x, y+h-1);
  LineTo(fl_gc, x, y);
}
#else
#endif


#if defined(__APPLE_QUARTZ__)
#elif defined(WIN32)
void fltk3::GDIGraphicsDriver::rectf(int x, int y, int w, int h) {
  if (w<=0 || h<=0) return;
  x += origin_x(); y += origin_y();
  RECT rect;
  rect.left = x; rect.top = y;  
  rect.right = x + w; rect.bottom = y + h;
  FillRect(fl_gc, &rect, fl_brush());
}
#else
#endif


#if defined(__APPLE_QUARTZ__)
#elif defined(WIN32)
void fltk3::GDIGraphicsDriver::xyline(int x, int y, int x1) {
  x += origin_x(); y += origin_y(); x1 += origin_x();
  MoveToEx(fl_gc, x, y, 0L); LineTo(fl_gc, x1+1, y);
}
#else
#endif


#if defined(__APPLE_QUARTZ__)
#elif defined(WIN32)
void fltk3::GDIGraphicsDriver::xyline(int x, int y, int x1, int y2) {
  x += origin_x(); y += origin_y(); x1 += origin_x(); y2 += origin_y();
  if (y2 < y) y2--;
  else y2++;
  MoveToEx(fl_gc, x, y, 0L); 
  LineTo(fl_gc, x1, y);
  LineTo(fl_gc, x1, y2);
}
#else
#endif


#if defined(__APPLE_QUARTZ__)
#elif defined(WIN32)
void fltk3::GDIGraphicsDriver::xyline(int x, int y, int x1, int y2, int x3) {
  x += origin_x(); y += origin_y(); x1 += origin_x(); y2 += origin_y(); x3 += origin_x();
  if(x3 < x1) x3--;
  else x3++;
  MoveToEx(fl_gc, x, y, 0L); 
  LineTo(fl_gc, x1, y);
  LineTo(fl_gc, x1, y2);
  LineTo(fl_gc, x3, y2);
}
#else
#endif


#if defined(__APPLE_QUARTZ__)
#elif defined(WIN32)
void fltk3::GDIGraphicsDriver::yxline(int x, int y, int y1) {
  x += origin_x(); y += origin_y(); y1 += origin_y();
  if (y1 < y) y1--;
  else y1++;
  MoveToEx(fl_gc, x, y, 0L); LineTo(fl_gc, x, y1);
}
#else
#endif


#if defined(__APPLE_QUARTZ__)
#elif defined(WIN32)
void fltk3::GDIGraphicsDriver::yxline(int x, int y, int y1, int x2) {
  x += origin_x(); y += origin_y(); y1 += origin_y(); x2 += origin_x();
  if (x2 > x) x2++;
  else x2--;
  MoveToEx(fl_gc, x, y, 0L); 
  LineTo(fl_gc, x, y1);
  LineTo(fl_gc, x2, y1);
}
#else
#endif


#if defined(__APPLE_QUARTZ__)
#elif defined(WIN32)
void fltk3::GDIGraphicsDriver::yxline(int x, int y, int y1, int x2, int y3) {
  x += origin_x(); y += origin_y(); y1 += origin_y(); x2 += origin_x(); y3 += origin_y();
  if(y3<y1) y3--;
  else y3++;
  MoveToEx(fl_gc, x, y, 0L); 
  LineTo(fl_gc, x, y1);
  LineTo(fl_gc, x2, y1);
  LineTo(fl_gc, x2, y3);
}
#else
#endif


#if defined(__APPLE_QUARTZ__)
#elif defined(WIN32)
void fltk3::GDIGraphicsDriver::line(int x, int y, int x1, int y1) {
  x += origin_x(); y += origin_y(); x1 += origin_x(); y1 += origin_y();
  MoveToEx(fl_gc, x, y, 0L); 
  LineTo(fl_gc, x1, y1);
  // Draw the last point *again* because the GDI line drawing
  // functions will not draw the last point ("it's a feature!"...)
  SetPixel(fl_gc, x1, y1, fl_RGB());
}
#else
#endif


#if defined(__APPLE_QUARTZ__)
#elif defined(WIN32)
void fltk3::GDIGraphicsDriver::line(int x, int y, int x1, int y1, int x2, int y2) {
  x += origin_x(); y += origin_y(); x1 += origin_x(); y1 += origin_y(); x2 += origin_x(); y2 += origin_y();
  MoveToEx(fl_gc, x, y, 0L); 
  LineTo(fl_gc, x1, y1);
  LineTo(fl_gc, x2, y2);
  // Draw the last point *again* because the GDI line drawing
  // functions will not draw the last point ("it's a feature!"...)
  SetPixel(fl_gc, x2, y2, fl_RGB());
}
#else
#endif


#if defined(__APPLE_QUARTZ__)
#elif defined(WIN32)
void fltk3::GDIGraphicsDriver::loop(int x, int y, int x1, int y1, int x2, int y2) {
  x += origin_x(); y += origin_y(); x1 += origin_x(); y1 += origin_y(); x2 += origin_x(); y2 += origin_y();
  MoveToEx(fl_gc, x, y, 0L); 
  LineTo(fl_gc, x1, y1);
  LineTo(fl_gc, x2, y2);
  LineTo(fl_gc, x, y);
}
#else
#endif


#if defined(__APPLE_QUARTZ__)
#elif defined(WIN32)
void fltk3::GDIGraphicsDriver::loop(int x, int y, int x1, int y1, int x2, int y2, int x3, int y3) {
  x += origin_x(); y += origin_y(); x1 += origin_x(); y1 += origin_y(); 
  x2 += origin_x(); y2 += origin_y(); x3 += origin_x(); y3 += origin_y();
  MoveToEx(fl_gc, x, y, 0L); 
  LineTo(fl_gc, x1, y1);
  LineTo(fl_gc, x2, y2);
  LineTo(fl_gc, x3, y3);
  LineTo(fl_gc, x, y);
}
#else
#endif


#if defined(__APPLE_QUARTZ__)
#elif defined(WIN32)
void fltk3::GDIGraphicsDriver::polygon(int x, int y, int x1, int y1, int x2, int y2) {
  x += origin_x(); y += origin_y(); x1 += origin_x(); y1 += origin_y(); x2 += origin_x(); y2 += origin_y();
  XPoint p[3];
  p[0].x = x;  p[0].y = y;
  p[1].x = x1; p[1].y = y1;
  p[2].x = x2; p[2].y = y2;
  SelectObject(fl_gc, fl_brush());
  Polygon(fl_gc, p, 3);
}
#else
#endif


#if defined(__APPLE_QUARTZ__)
#elif defined(WIN32)
void fltk3::GDIGraphicsDriver::polygon(int x, int y, int x1, int y1, int x2, int y2, int x3, int y3) {
  x += origin_x(); y += origin_y(); x1 += origin_x(); y1 += origin_y(); 
  x2 += origin_x(); y2 += origin_y(); x3 += origin_x(); y3 += origin_y();
  XPoint p[4];
  p[0].x = x;  p[0].y = y;
  p[1].x = x1; p[1].y = y1;
  p[2].x = x2; p[2].y = y2;
  p[3].x = x3; p[3].y = y3;
  SelectObject(fl_gc, fl_brush());
  Polygon(fl_gc, p, 4);
}
#else
#endif


#if defined(__APPLE_QUARTZ__)
#elif defined(WIN32)
void fltk3::GDIGraphicsDriver::point(int x, int y) {
  x += origin_x(); y += origin_y();
  SetPixel(fl_gc, x, y, fl_RGB());
}
#else
#endif

////////////////////////////////////////////////////////////////

#if !defined(WIN32) && !defined(__APPLE__)
#endif


#if defined(__APPLE_QUARTZ__)
#elif defined(WIN32)
void fltk3::GDIGraphicsDriver::restore_clip() {
  fl_clip_state_number++;
  fltk3::Region r = clip_region();
  SelectClipRgn(fl_gc, r); //if r is NULL, clip is automatically cleared
}
#else
#endif


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

#if defined(__APPLE_QUARTZ__)
#elif defined(WIN32)
void fltk3::GDIGraphicsDriver::push_clip(int x, int y, int w, int h) {
  x += origin_x(); y += origin_y();
  fltk3::Region r;
  if (w > 0 && h > 0) {
    r = XRectangleRegion(x,y,w,h);
    fltk3::Region current = clip_region();
    if (current) {
      CombineRgn(r,r,current,RGN_AND);
    }
  } else { // make empty clip region:
    r = CreateRectRgn(0,0,0,0);
  }
  region_stack_push(r);
  restore_clip();
}
#else
#endif


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


#if defined(__APPLE_QUARTZ__)
#elif defined(WIN32)
int fltk3::GDIGraphicsDriver::not_clipped(int x, int y, int w, int h) {
  x += origin_x(); y += origin_y();
  if (x+w <= 0 || y+h <= 0) return 0;
  fltk3::Region r = clip_region();
  if (!r) return 1;
  RECT rect;
  if (is_printer()) { // in case of print context, convert coords from logical to device
    POINT pt[2] = { {x, y}, {x + w, y + h} };
    LPtoDP(fl_gc, pt, 2);
    rect.left = pt[0].x; rect.top = pt[0].y; rect.right = pt[1].x; rect.bottom = pt[1].y;
  } else {
    rect.left = x; rect.top = y; rect.right = x+w; rect.bottom = y+h;
  }
  return RectInRegion(r,&rect);
}
#else
#endif


// return rectangle surrounding intersection of this rectangle and clip:
#if defined(__APPLE_QUARTZ__)
#elif defined(WIN32)
int fltk3::GDIGraphicsDriver::clip_box(int x, int y, int w, int h, int& X, int& Y, int& W, int& H){
  X = x; Y = y; W = w; H = h;
  fltk3::Region r = clip_region();
  if (!r) return 0;
  x += origin_x(); y += origin_y();
  X = x; Y = y;
  // The win32 API makes no distinction between partial and complete
  // intersection, so we have to check for partial intersection ourselves.
  // However, given that the regions may be composite, we have to do
  // some voodoo stuff...
  fltk3::Region rr = XRectangleRegion(x,y,w,h);
  fltk3::Region temp = CreateRectRgn(0,0,0,0);
  int ret;
  if (CombineRgn(temp, rr, r, RGN_AND) == NULLREGION) { // disjoint
    W = H = 0;
    ret = 2;
  } else if (EqualRgn(temp, rr)) { // complete
    ret = 0;
  } else {	// partial intersection
    RECT rect;
    GetRgnBox(temp, &rect);
    if (is_printer()) { // if print context, convert coords from device to logical
      POINT pt[2] = { {rect.left, rect.top}, {rect.right, rect.bottom} };
      DPtoLP(fl_gc, pt, 2);
      X = pt[0].x; Y = pt[0].y; W = pt[1].x - X; H = pt[1].y - Y;
    }
    else {
      X = rect.left; Y = rect.top; W = rect.right - X; H = rect.bottom - Y;
    }
    ret = 1;
  }
  DeleteObject(temp);
  DeleteObject(rr);
  X -= origin_x(); Y -= origin_y();
  return ret;
}
#else
#endif

//
// End of "$Id$".
//
