//
// "$Id: fl_rect.cxx,v 1.12 2000/02/14 11:32:58 bill Exp $"
//
// Rectangle drawing routines for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-1999 by Bill Spitzak and others.
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
// Please report all bugs and problems to "fltk-bugs@easysw.com".
//

// These routines from fl_draw.H are used by the standard boxtypes
// and thus are always linked into an fltk program.
// Also all fl_clip routines, since they are always linked in so
// that minimal update works.

#include <FL/Fl_Widget.H>
#include <FL/fl_draw.H>
#include <FL/x.H>

void fl_rect(int x, int y, int w, int h) {
  if (w<=0 || h<=0) return;
#ifdef WIN32
  MoveToEx(fl_gc, x, y, 0L); 
  LineTo(fl_gc, x+w-1, y);
  LineTo(fl_gc, x+w-1, y+h-1);
  LineTo(fl_gc, x, y+h-1);
  LineTo(fl_gc, x, y);
#else
  XDrawRectangle(fl_display, fl_window, fl_gc, x, y, w-1, h-1);
#endif
}

void fl_rectf(int x, int y, int w, int h) {
  if (w<=0 || h<=0) return;
#ifdef WIN32
  RECT rect;
  rect.left = x; rect.top = y;  
  rect.right = x + w; rect.bottom = y + h;
  FillRect(fl_gc, &rect, fl_brush());
#else
  if (w && h) XFillRectangle(fl_display, fl_window, fl_gc, x, y, w, h);
#endif
}

void fl_xyline(int x, int y, int x1) {
#ifdef WIN32
  MoveToEx(fl_gc, x, y, 0L); LineTo(fl_gc, x1+1, y);
#else
  XDrawLine(fl_display, fl_window, fl_gc, x, y, x1, y);
#endif
}

void fl_xyline(int x, int y, int x1, int y2) {
#ifdef WIN32
  if (y2 < y) y2--;
  else y2++;
  MoveToEx(fl_gc, x, y, 0L); 
  LineTo(fl_gc, x1, y);
  LineTo(fl_gc, x1, y2);
#else
  XPoint p[3];
  p[0].x = x;  p[0].y = p[1].y = y;
  p[1].x = p[2].x = x1; p[2].y = y2;
  XDrawLines(fl_display, fl_window, fl_gc, p, 3, 0);
#endif
}

void fl_xyline(int x, int y, int x1, int y2, int x3) {
#ifdef WIN32
  if(x3 < x1) x3--;
  else x3++;
  MoveToEx(fl_gc, x, y, 0L); 
  LineTo(fl_gc, x1, y);
  LineTo(fl_gc, x1, y2);
  LineTo(fl_gc, x3, y2);
#else
  XPoint p[4];
  p[0].x = x;  p[0].y = p[1].y = y;
  p[1].x = p[2].x = x1; p[2].y = p[3].y = y2;
  p[3].x = x3;
  XDrawLines(fl_display, fl_window, fl_gc, p, 4, 0);
#endif
}

void fl_yxline(int x, int y, int y1) {
#ifdef WIN32
  if (y1 < y) y1--;
  else y1++;
  MoveToEx(fl_gc, x, y, 0L); LineTo(fl_gc, x, y1);
#else
  XDrawLine(fl_display, fl_window, fl_gc, x, y, x, y1);
#endif
}

void fl_yxline(int x, int y, int y1, int x2) {
#ifdef WIN32
  if (x2 > x) x2++;
  else x2--;
  MoveToEx(fl_gc, x, y, 0L); 
  LineTo(fl_gc, x, y1);
  LineTo(fl_gc, x2, y1);
#else
  XPoint p[3];
  p[0].x = p[1].x = x;  p[0].y = y;
  p[1].y = p[2].y = y1; p[2].x = x2;
  XDrawLines(fl_display, fl_window, fl_gc, p, 3, 0);
#endif
}

void fl_yxline(int x, int y, int y1, int x2, int y3) {
#ifdef WIN32
  if(y3<y1) y3--;
  else y3++;
  MoveToEx(fl_gc, x, y, 0L); 
  LineTo(fl_gc, x, y1);
  LineTo(fl_gc, x2, y1);
  LineTo(fl_gc, x2, y3);
#else
  XPoint p[4];
  p[0].x = p[1].x = x;  p[0].y = y;
  p[1].y = p[2].y = y1; p[2].x = p[3].x = x2;
  p[3].y = y3;
  XDrawLines(fl_display, fl_window, fl_gc, p, 4, 0);
#endif
}

void fl_line(int x, int y, int x1, int y1) {
#ifdef WIN32
  MoveToEx(fl_gc, x, y, 0L); 
  LineTo(fl_gc, x1, y1);
  // Draw the last point *again* because the GDI line drawing
  // functions will not draw the last point ("it's a feature!"...)
  SetPixel(fl_gc, x1, y1, fl_RGB());
#else
  XDrawLine(fl_display, fl_window, fl_gc, x, y, x1, y1);
#endif
}

void fl_line(int x, int y, int x1, int y1, int x2, int y2) {
#ifdef WIN32
  MoveToEx(fl_gc, x, y, 0L); 
  LineTo(fl_gc, x1, y1);
  LineTo(fl_gc, x2, y2);
  // Draw the last point *again* because the GDI line drawing
  // functions will not draw the last point ("it's a feature!"...)
  SetPixel(fl_gc, x2, y2, fl_RGB());
#else
  XPoint p[3];
  p[0].x = x;  p[0].y = y;
  p[1].x = x1; p[1].y = y1;
  p[2].x = x2; p[2].y = y2;
  XDrawLines(fl_display, fl_window, fl_gc, p, 3, 0);
#endif
}

void fl_loop(int x, int y, int x1, int y1, int x2, int y2) {
#ifdef WIN32
  MoveToEx(fl_gc, x, y, 0L); 
  LineTo(fl_gc, x1, y1);
  LineTo(fl_gc, x2, y2);
  LineTo(fl_gc, x, y);
#else
  XPoint p[4];
  p[0].x = x;  p[0].y = y;
  p[1].x = x1; p[1].y = y1;
  p[2].x = x2; p[2].y = y2;
  p[3].x = x;  p[3].y = y;
  XDrawLines(fl_display, fl_window, fl_gc, p, 4, 0);
#endif
}

void fl_loop(int x, int y, int x1, int y1, int x2, int y2, int x3, int y3) {
#ifdef WIN32
  MoveToEx(fl_gc, x, y, 0L); 
  LineTo(fl_gc, x1, y1);
  LineTo(fl_gc, x2, y2);
  LineTo(fl_gc, x3, y3);
  LineTo(fl_gc, x, y);
#else
  XPoint p[5];
  p[0].x = x;  p[0].y = y;
  p[1].x = x1; p[1].y = y1;
  p[2].x = x2; p[2].y = y2;
  p[3].x = x3; p[3].y = y3;
  p[4].x = x;  p[4].y = y;
  XDrawLines(fl_display, fl_window, fl_gc, p, 5, 0);
#endif
}

void fl_polygon(int x, int y, int x1, int y1, int x2, int y2) {
  XPoint p[4];
  p[0].x = x;  p[0].y = y;
  p[1].x = x1; p[1].y = y1;
  p[2].x = x2; p[2].y = y2;
#ifdef WIN32
  SelectObject(fl_gc, fl_brush());
  Polygon(fl_gc, p, 3);
#else
  p[3].x = x;  p[3].y = y;
  XFillPolygon(fl_display, fl_window, fl_gc, p, 3, Convex, 0);
  XDrawLines(fl_display, fl_window, fl_gc, p, 4, 0);
#endif
}

void fl_polygon(int x, int y, int x1, int y1, int x2, int y2, int x3, int y3) {
  XPoint p[5];
  p[0].x = x;  p[0].y = y;
  p[1].x = x1; p[1].y = y1;
  p[2].x = x2; p[2].y = y2;
  p[3].x = x3; p[3].y = y3;
#ifdef WIN32
  SelectObject(fl_gc, fl_brush());
  Polygon(fl_gc, p, 4);
#else
  p[4].x = x;  p[4].y = y;
  XFillPolygon(fl_display, fl_window, fl_gc, p, 4, Convex, 0);
  XDrawLines(fl_display, fl_window, fl_gc, p, 5, 0);
#endif
}

void fl_point(int x, int y) {
#ifdef WIN32
  SetPixel(fl_gc, x, y, fl_RGB());
#else
  XDrawPoint(fl_display, fl_window, fl_gc, x, y);
#endif
}

////////////////////////////////////////////////////////////////
// The clipping stack:

#define STACK_SIZE 11
#define STACK_MAX (STACK_SIZE - 2)
static Region rstack[STACK_SIZE];
static int rstackptr=0;
int fl_clip_state_number=0; // used by gl_begin.C to update GL clip

#ifndef WIN32
// Missing X call: (is this the fastest way to init a 1-rectangle region?)
// MSWindows equivalent exists, implemented inline in win32.H
Region XRectangleRegion(int x, int y, int w, int h) {
  XRectangle R;
  R.x = x; R.y = y; R.width = w; R.height = h;
  Region r = XCreateRegion();
  XUnionRectWithRegion(&R, r, r);
  return r;
}
#endif

// Make the system's clip match the top of the clip stack.  This can
// be used after changing the stack, or to undo any clobbering of clip
// done by your program:
void fl_restore_clip() {
  fl_clip_state_number++;
  Region r = rstack[rstackptr];
#ifdef WIN32
  SelectClipRgn(fl_gc, r); //if r is NULL, clip is automatically cleared
#else
  if (r) XSetRegion(fl_display, fl_gc, r);
  else XSetClipMask(fl_display, fl_gc, 0);
#endif
}

// Replace the top of the clip stack:
void fl_clip_region(Region r) {
  Region oldr = rstack[rstackptr];
  if (oldr) XDestroyRegion(oldr);
  rstack[rstackptr] = r;
  fl_restore_clip();
}

// Intersect & push a new clip rectangle:
void fl_clip(int x, int y, int w, int h) {
  Region r;
  if (w > 0 && h > 0) {
    r = XRectangleRegion(x,y,w,h);
    Region current = rstack[rstackptr];
    if (current) {
#ifndef WIN32
      Region temp = XCreateRegion();
      XIntersectRegion(current, r, temp);
      XDestroyRegion(r);
      r = temp;
#else
      CombineRgn(r,r,current,RGN_AND);
#endif
    }
  } else { // make empty clip region:
#ifndef WIN32
    r = XCreateRegion();
#else
    r = CreateRectRgn(0,0,0,0);
#endif
  }
  if (rstackptr < STACK_MAX) rstack[++rstackptr] = r;
  fl_restore_clip();
}

// Replace top of stack with top of stack minus this rectangle:
void fl_clip_out(int x, int y, int w, int h) {
  if (w <= 0 || h <= 0) return;
  Region r = XRectangleRegion(x,y,w,h);
  Region current = rstack[rstackptr];
// This is not needed as caller must do push of a clip beforehand.
//if (!current) current = rstack[rstackptr] =
//  XRectangleRegion(0,0,Fl_Window::current()->w(),Fl_Window::current()->h());
#ifndef WIN32
  Region temp = XCreateRegion();
  XSubtractRegion(current, r, temp);
  XDestroyRegion(r);
  XDestroyRegion(current);
  rstack[rstackptr] = temp;
#else
  CombineRgn(current,current,r,RGN_DIFF);
#endif
  fl_restore_clip();
}

// make there be no clip (used by fl_begin_offscreen() only!)
void fl_push_no_clip() {
  // this does not test maximum so that this is guaranteed to work,
  // there is one extra slot at the top of the stack.
  /*if (rstackptr < STACK_MAX)*/ rstack[++rstackptr] = 0;
  fl_restore_clip();
}

// pop back to previous clip:
void fl_pop_clip() {
  if (rstackptr > 0) {
    Region oldr = rstack[rstackptr--];
    if (oldr) XDestroyRegion(oldr);
    fl_restore_clip();
  }
}

////////////////////////////////////////////////////////////////
// clipping tests:

// does this rectangle intersect current clip?
int fl_not_clipped(int x, int y, int w, int h) {
  // first check against the window so we get rid of coordinates
  // outside the 16-bit range the X/Win32 calls take:
  if (x+w <= 0 || y+h <= 0 || x >= Fl_Window::current()->w()
      || y >= Fl_Window::current()->h()) return 0;
  Region r = rstack[rstackptr];
#ifndef WIN32
  return r ? XRectInRegion(r, x, y, w, h) : 1;
#else
  if (!r) return 1;
  RECT rect;
  rect.left = x; rect.top = y; rect.right = x+w; rect.bottom = y+h;
  return RectInRegion(r,&rect);
#endif
}

// return rectangle surrounding intersection of this rectangle and clip:
int fl_clip_box(int x, int y, int w, int h, int& X, int& Y, int& W, int& H) {
  Region r = rstack[rstackptr];
  if (!r) {X = x; Y = y; W = w; H = h; return 0;}
  // Test against the window to get 16-bit values (this is only done if
  // a clip region exists as otherwise it breaks fl_push_no_clip()):
  int ret = 0;
  if (x < 0) {w += x; x = 0; ret = 1;}
  if (y < 0) {h += y; y = 0; ret = 1;}
  int t = Fl_Window::current()->w(); if (x+w > t) {w = t-x; ret = 1;}
  t = Fl_Window::current()->h(); if (y+h > t) {h = t-y; ret = 1;}
  X = x; Y = y;
  // check for total clip (or for empty rectangle):
  if (w <= 0 || h <= 0) {W = H = 0; return 2;}
#ifndef WIN32
  switch (XRectInRegion(r, x, y, w, h)) {
  case 0: // completely outside
    W = H = 0;
    return 2;
  case 1: // completely inside:
    W = w; H = h;
    return ret;
  default: // partial:
    break;
  }
  Region rr = XRectangleRegion(x,y,w,h);
  Region temp = XCreateRegion();
  XIntersectRegion(r, rr, temp);
  XRectangle rect;
  XClipBox(temp, &rect);
  X = rect.x; Y = rect.y; W = rect.width; H = rect.height;
  XDestroyRegion(temp);
  XDestroyRegion(rr);
  return 1;
#else
// The win32 API makes no distinction between partial and complete
// intersection, so we have to check for partial intersection ourselves.
// However, given that the regions may be composite, we have to do
// some voodoo stuff...
// WAS: we may want to simlify this as no calls in fltk use the return
// value anyways.
  Region rr = XRectangleRegion(x,y,w,h);
  Region temp = CreateRectRgn(0,0,0,0);
  if (CombineRgn(temp, rr, r, RGN_AND) == NULLREGION) { // disjoint
    W = H = 0;
    ret = 2;
  } else if (EqualRgn(temp, rr)) { // complete
    W = w; H = h;
    // ret = ret
  } else {	// parital intersection
    RECT rect;
    GetRgnBox(temp, &rect);
    X = rect.left; Y = rect.top; W = rect.right - X; H = rect.bottom - Y;
    ret = 1;
  }
  DeleteObject(temp);
  DeleteObject(rr);
  return ret;
#endif
}

//
// End of "$Id: fl_rect.cxx,v 1.12 2000/02/14 11:32:58 bill Exp $".
//
