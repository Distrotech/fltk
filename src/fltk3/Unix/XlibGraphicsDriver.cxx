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

#include <config.h>

#ifdef USE_X11

#include "XlibGraphicsDriver.h"

#include <fltk3/run.h>
#include <fltk3/x.h>
#include <fltk3/draw.h>
#include <fltk3/Widget.h>
#include <fltk3/MenuItem.h>
#include <fltk3/Bitmap.h>
#include <fltk3/Printer.h>
#include <fltk3/Image.h>
#include <fltk3/DoubleWindow.h>
#include <fltk3/utf8.h>

#include "../flstring.h"
#include "../font.h"

extern int fl_line_width_;

#ifndef SHRT_MAX
#define SHRT_MAX (32767)
#endif

extern int fltk3_start(fltk3::Bitmap *bm,
                       int XP, int YP, int WP, int HP,
                       int w, int h, int &cx, int &cy,
                       int &X, int &Y, int &W, int &H);

extern int fltk3_start(fltk3::RGBImage *img,
                       int XP, int YP, int WP, int HP,
                       int w, int h, int &cx, int &cy,
                       int &X, int &Y, int &W, int &H);

// Composite an image with alpha on systems that don't have accelerated
// alpha compositing...
static void alpha_blend(fltk3::RGBImage *img, int X, int Y, int W, int H, int cx, int cy) {
  int ld = img->ld();
  if (ld == 0) ld = img->w() * img->d();
  uchar *srcptr = (uchar*)img->array + cy * ld + cx * img->d();
  int srcskip = ld - img->d() * W;
  
  uchar *dst = new uchar[W * H * 3];
  uchar *dstptr = dst;
  
  fltk3::read_image(dst, X+fltk3::origin_x(), Y+fltk3::origin_y(), W, H, 0);
  
  uchar srcr, srcg, srcb, srca;
  uchar dstr, dstg, dstb, dsta;
  
  if (img->d() == 2) {
    // Composite grayscale + alpha over RGB...
    for (int y = H; y > 0; y--, srcptr+=srcskip)
      for (int x = W; x > 0; x--) {
	srcg = *srcptr++;
	srca = *srcptr++;
        
	dstr = dstptr[0];
	dstg = dstptr[1];
	dstb = dstptr[2];
	dsta = 255 - srca;
        
	*dstptr++ = (srcg * srca + dstr * dsta) >> 8;
	*dstptr++ = (srcg * srca + dstg * dsta) >> 8;
	*dstptr++ = (srcg * srca + dstb * dsta) >> 8;
      }
  } else {
    // Composite RGBA over RGB...
    for (int y = H; y > 0; y--, srcptr+=srcskip)
      for (int x = W; x > 0; x--) {
	srcr = *srcptr++;
	srcg = *srcptr++;
	srcb = *srcptr++;
	srca = *srcptr++;
        
	dstr = dstptr[0];
	dstg = dstptr[1];
	dstb = dstptr[2];
	dsta = 255 - srca;
        
	*dstptr++ = (srcr * srca + dstr * dsta) >> 8;
	*dstptr++ = (srcg * srca + dstg * dsta) >> 8;
	*dstptr++ = (srcb * srca + dstb * dsta) >> 8;
      }
  }
  
  fltk3::draw_image(dst, X, Y, W, H, 3, 0);
  
  delete[] dst;
}

/*
 We need to check some coordinates for areas for clipping before we
 use X functions, because X can't handle coordinates outside the 16-bit
 range. Since all windows use relative coordinates > 0, we do also
 check for negative values. X11 only, see also STR #2304.
 
 Note that this is only necessary for large objects, where only a
 part of the object is visible. The draw() functions (e.g. box
 drawing) must be clipped correctly. This is usually only a matter
 for large container widgets. The individual child widgets will be
 clipped completely.
 
 We define the usable X coordinate space as [ -LW : SHRT_MAX - LW ]
 where LW = current line width for drawing. This is done so that
 horizontal and vertical line drawing works correctly, even in real
 border cases, e.g. drawing a rectangle slightly outside the top left
 window corner, but with a line width so that a part of the line should
 be visible (in this case 2 of 5 pixels):
 
 fltk3::line_style (fltk3::SOLID,5);	// line width = 5
 fltk3::rect (-1,-1,100,100);	// top/left: 2 pixels visible
 
 In this example case, no clipping would be done, because X can
 handle it and clip unneeded pixels.
 
 Note that we must also take care of the case where fl_line_width_
 is zero (maybe unitialized). If this is the case, we assume a line
 width of 1.
 
 Todo: Arbitrary line drawings (e.g. polygons) and clip regions
 are not yet done.
 
 Note:
 
 We could use max. screen coordinates instead of SHRT_MAX, but that
 would need more work and would probably be slower. We assume that
 all window coordinates are >= 0 and that no window extends up to
 32767 - LW (where LW = current line width). Thus it is safe to clip
 all coordinates to this range before calling X functions. If this
 is not true, then clip_to_short() and clip_x() must be redefined.
 
 It would be somewhat easier if we had fl_clip_w and fl_clip_h, as
 defined in FLTK 2.0 (for the upper clipping bounds)...
 */

/*
 clip_to_short() returns 1, if the area is invisible (clipped),
 because ...
 
 (a) w or h are <= 0		i.e. nothing is visible
 (b) x+w or y+h are < kmin	i.e. left of or above visible area
 (c) x or y are > kmax	i.e. right of or below visible area
 
 kmin and kmax are the minimal and maximal X coordinate values,
 as defined above. In this case x, y, w, and h are not changed.
 
 It returns 0, if the area is potentially visible and X can handle
 clipping. x, y, w, and h may have been adjusted to fit into the
 X coordinate space.
 
 Use this for clipping rectangles, as used in fltk3::rect() and
 fltk3::rectf().
 */

static int clip_to_short(int &x, int &y, int &w, int &h) {
  
  int lw = (fl_line_width_ > 0) ? fl_line_width_ : 1;
  int kmin = -lw;
  int kmax = SHRT_MAX - lw;
  
  if (w <= 0 || h <= 0) return 1;		// (a)
  if (x+w < kmin || y+h < kmin) return 1;	// (b)
  if (x > kmax || y > kmax) return 1;		// (c)
  
  if (x < kmin) { w -= (kmin-x); x = kmin; }
  if (y < kmin) { h -= (kmin-y); y = kmin; }
  if (x+w > kmax) w = kmax - x;
  if (y+h > kmax) h = kmax - y;
  
  return 0;
}

/*
 clip_x() returns a coordinate value clipped to the 16-bit coordinate
 space (see above). This can be used to draw horizontal and vertical
 lines that can be handled by X11. Each single coordinate value can
 be clipped individually, and the result can be used directly, e.g.
 in fltk3::xyline() and fltk3::yxline(). Note that this can't be used for
 arbitrary lines (not horizontal or vertical).
 */
static int clip_x (int x) {
  
  int lw = (fl_line_width_ > 0) ? fl_line_width_ : 1;
  int kmin = -lw;
  int kmax = SHRT_MAX - lw;
  
  if (x < kmin)
    x = kmin;
  else if (x > kmax)
    x = kmax;
  return x;
}


void fltk3::XlibGraphicsDriver::end_points() {
  int n = vertex_no();
  if (n > 1) XDrawPoints(fl_display, fl_window, fl_gc, vertices(), n, 0);
}


void fltk3::XlibGraphicsDriver::end_line() {
  int n = vertex_no();
  XPOINT *p = vertices();
  if (n < 2) {
    end_points();
    return;
  }
  if (n>1) XDrawLines(fl_display, fl_window, fl_gc, p, n, 0);
}

void fltk3::XlibGraphicsDriver::end_polygon() {
  fixloop();
  int n = vertex_no();
  XPOINT *p = vertices();
  if (n < 3) {
    end_line();
    return;
  }
  if (n>2) XFillPolygon(fl_display, fl_window, fl_gc, p, n, Convex, 0);
}

void fltk3::XlibGraphicsDriver::end_complex_polygon() {
  gap();
  int n = vertex_no();
  XPOINT *p = vertices();
  if (n < 3) {
    end_line();
    return;
  }
  if (n>2) XFillPolygon(fl_display, fl_window, fl_gc, p, n, 0, 0);
}

void fltk3::XlibGraphicsDriver::circle(double x, double y, double r) {
  int llx, lly, w, h;
  double xt, yt;
  prepare_circle(x, y, r, llx, lly, w, h, xt, yt);
  (vertex_kind() == POLYGON ? XFillArc : XDrawArc)
  (fl_display, fl_window, fl_gc, llx+origin_x(), lly+origin_y(), w, h, 0, 360*64);
}

void fltk3::XlibGraphicsDriver::arc(int x,int y,int w,int h,double a1,double a2) {
  if (w <= 0 || h <= 0) return;
  x += origin_x(); y += origin_y();
  XDrawArc(fl_display, fl_window, fl_gc, x,y,w-1,h-1, int(a1*64),int((a2-a1)*64));
}

void fltk3::XlibGraphicsDriver::pie(int x,int y,int w,int h,double a1,double a2) {
  if (w <= 0 || h <= 0) return;
  x += origin_x(); y += origin_y();
  XDrawArc(fl_display, fl_window, fl_gc, x,y,w-1,h-1, int(a1*64),int((a2-a1)*64));
  XFillArc(fl_display, fl_window, fl_gc, x,y,w-1,h-1, int(a1*64),int((a2-a1)*64));
}


void fltk3::XlibGraphicsDriver::draw(fltk3::Bitmap *bm, int XP, int YP, int WP, int HP, int cx, int cy) {
  int X, Y, W, H;
  if (!bm->array) {
    bm->draw_empty(XP, YP);
    return;
  }
  if (fltk3_start(bm, XP, YP, WP, HP, bm->w(), bm->h(), cx, cy, X, Y, W, H)) {
    return;
  }
  if (!bm->id_) bm->id_ = fl_create_bitmask(bm->w(), bm->h(), bm->array);
  
  XSetStipple(fl_display, fl_gc, bm->id_);
  int ox = X+origin_x()-cx; if (ox < 0) ox += bm->w();
  int oy = Y+origin_y()-cy; if (oy < 0) oy += bm->h();
  XSetTSOrigin(fl_display, fl_gc, ox, oy);
  XSetFillStyle(fl_display, fl_gc, FillStippled);
  XFillRectangle(fl_display, fl_window, fl_gc, X+origin_x(), Y+origin_y(), W, H);
  XSetFillStyle(fl_display, fl_gc, FillSolid);
}

void fltk3::XlibGraphicsDriver::copy_offscreen(int x, int y, int w, int h, fltk3::Offscreen pixmap, int srcx, int srcy) {
  XCopyArea(fl_display, pixmap, fl_window, fl_gc, srcx, srcy, w, h, x+origin_x(), y+origin_y());
}


// maybe someone feels inclined to implement alpha blending on X11?
char fltk3::XlibGraphicsDriver::can_do_alpha_blending() {
  return 0;
}

void fltk3::XlibGraphicsDriver::draw(fltk3::RGBImage *img, int XP, int YP, int WP, int HP, int cx, int cy) {
  int X, Y, W, H;
  // Don't draw an empty image...
  if (!img->d() || !img->array) {
    img->draw_empty(XP, YP);
    return;
  }
  if (fltk3_start(img, XP, YP, WP, HP, img->w(), img->h(), cx, cy, X, Y, W, H)) {
    return;
  }
  if (!img->id_) {
    if (img->d() == 1 || img->d() == 3) {
      img->id_ = fl_create_offscreen(img->w(), img->h());
      fl_begin_offscreen((fltk3::Offscreen)img->id_);
      fltk3::push_origin(); fltk3::origin(0,0);
      fltk3::draw_image(img->array, 0, 0, img->w(), img->h(), img->d(), img->ld());
      fltk3::pop_origin();
      fl_end_offscreen();
    }
  }
  if (img->id_) {
    if (img->mask_) {
      // I can't figure out how to combine a mask with existing region,
      // so cut the image down to a clipped rectangle:
      int nx, ny; fltk3::clip_box(X,Y,W,H,nx,ny,W,H);
      cx += nx-X; X = nx;
      cy += ny-Y; Y = ny;
      // make X use the bitmap as a mask:
      XSetClipMask(fl_display, fl_gc, img->mask_);
      int ox = X-cx; if (ox < 0) ox += img->w();
      int oy = Y-cy; if (oy < 0) oy += img->h();
      XSetClipOrigin(fl_display, fl_gc, X-cx, Y-cy);
    }
    
    copy_offscreen(X, Y, W, H, img->id_, cx, cy);
    
    if (img->mask_) {
      // put the old clip region back
      XSetClipOrigin(fl_display, fl_gc, 0, 0);
      fltk3::restore_clip();
    }
  } else {
    // Composite image with alpha manually each time...
    alpha_blend(img, X, Y, W, H, cx, cy);
  }
}

void fltk3::XlibGraphicsDriver::line_style(int style, int width, char* dashes) {
  // save line width in global variable for X11 clipping
  if (width == 0) fl_line_width_ = 1;
  else fl_line_width_ = width>0 ? width : -width;
  int ndashes = dashes ? strlen(dashes) : 0;
  // emulate the WIN32 dash patterns on X
  char buf[7];
  if (!ndashes && (style&0xff)) {
    int w = width ? width : 1;
    char dash, dot, gap;
    // adjust lengths to account for cap:
    if (style & 0x200) {
      dash = char(2*w);
      dot = 1; // unfortunately 0 does not work
      gap = char(2*w-1);
    } else {
      dash = char(3*w);
      dot = gap = char(w);
    }
    char* p = dashes = buf;
    switch (style & 0xff) {
      case fltk3::DASH:	*p++ = dash; *p++ = gap; break;
      case fltk3::DOT:	*p++ = dot; *p++ = gap; break;
      case fltk3::DASHDOT:	*p++ = dash; *p++ = gap; *p++ = dot; *p++ = gap; break;
      case fltk3::DASHDOTDOT: *p++ = dash; *p++ = gap; *p++ = dot; *p++ = gap; *p++ = dot; *p++ = gap; break;
    }
    ndashes = p-buf;
  }
  static int Cap[4] = {CapButt, CapButt, CapRound, CapProjecting};
  static int Join[4] = {JoinMiter, JoinMiter, JoinRound, JoinBevel};
  XSetLineAttributes(fl_display, fl_gc, width,
		     ndashes ? LineOnOffDash : LineSolid,
		     Cap[(style>>8)&3], Join[(style>>12)&3]);
  if (ndashes) XSetDashes(fl_display, fl_gc, 0, dashes, ndashes);
}


void fltk3::XlibGraphicsDriver::draw(fltk3::Pixmap *pxm, int XP, int YP, int WP, int HP, int cx, int cy) {
  int X, Y, W, H;
  if (pxm->prepare(XP, YP, WP, HP, cx, cy, X, Y, W, H)) return;
  if (pxm->mask_) {
    // I can't figure out how to combine a mask with existing region,
    // so cut the image down to a clipped rectangle:
    int nx, ny; fltk3::clip_box(X,Y,W,H,nx,ny,W,H);
    cx += nx-X; X = nx;
    cy += ny-Y; Y = ny;
    // make X use the bitmap as a mask:
    XSetClipMask(fl_display, fl_gc, pxm->mask_);
    int ox = X-cx; if (ox < 0) ox += pxm->w();
    int oy = Y-cy; if (oy < 0) oy += pxm->h();
    XSetClipOrigin(fl_display, fl_gc, X+origin_x()-cx, Y+origin_y()-cy);
  }
  copy_offscreen(X, Y, W, H, pxm->id_, cx, cy);
  if (pxm->mask_) {
    // put the old clip region back
    XSetClipOrigin(fl_display, fl_gc, 0, 0);
    fltk3::restore_clip();
  }
}


void fltk3::XlibGraphicsDriver::rect(int x, int y, int w, int h) {
  if (w<=0 || h<=0) return;
  x += origin_x(); y += origin_y();
  if (!clip_to_short(x, y, w, h))
    XDrawRectangle(fl_display, fl_window, fl_gc, x, y, w-1, h-1);
}

void fltk3::XlibGraphicsDriver::rectf(int x, int y, int w, int h) {
  if (w<=0 || h<=0) return;
  x += origin_x(); y += origin_y();
  if (!clip_to_short(x, y, w, h))
    XFillRectangle(fl_display, fl_window, fl_gc, x, y, w, h);
}

void fltk3::XlibGraphicsDriver::xyline(int x, int y, int x1) {
  x += origin_x(); y += origin_y(); x1 += origin_x();
  XDrawLine(fl_display, fl_window, fl_gc, clip_x(x), clip_x(y), clip_x(x1), clip_x(y));
}
void fltk3::XlibGraphicsDriver::xyline(int x, int y, int x1, int y2) {
  x += origin_x(); y += origin_y(); x1 += origin_x(); y2 += origin_y();
  XPoint p[3];
  p[0].x = clip_x(x);  p[0].y = p[1].y = clip_x(y);
  p[1].x = p[2].x = clip_x(x1); p[2].y = clip_x(y2);
  XDrawLines(fl_display, fl_window, fl_gc, p, 3, 0);
}

void fltk3::XlibGraphicsDriver::xyline(int x, int y, int x1, int y2, int x3) {
  x += origin_x(); y += origin_y(); x1 += origin_x(); y2 += origin_y(); x3 += origin_x();
  XPoint p[4];
  p[0].x = clip_x(x);  p[0].y = p[1].y = clip_x(y);
  p[1].x = p[2].x = clip_x(x1); p[2].y = p[3].y = clip_x(y2);
  p[3].x = clip_x(x3);
  XDrawLines(fl_display, fl_window, fl_gc, p, 4, 0);
}

void fltk3::XlibGraphicsDriver::yxline(int x, int y, int y1) {
  x += origin_x(); y += origin_y(); y1 += origin_y();
  XDrawLine(fl_display, fl_window, fl_gc, clip_x(x), clip_x(y), clip_x(x), clip_x(y1));
}

void fltk3::XlibGraphicsDriver::yxline(int x, int y, int y1, int x2) {
  x += origin_x(); y += origin_y(); y1 += origin_y(); x2 += origin_x();
  XPoint p[3];
  p[0].x = p[1].x = clip_x(x);  p[0].y = clip_x(y);
  p[1].y = p[2].y = clip_x(y1); p[2].x = clip_x(x2);
  XDrawLines(fl_display, fl_window, fl_gc, p, 3, 0);
}

void fltk3::XlibGraphicsDriver::yxline(int x, int y, int y1, int x2, int y3) {
  x += origin_x(); y += origin_y(); y1 += origin_y(); x2 += origin_x(); y3 += origin_y();
  XPoint p[4];
  p[0].x = p[1].x = clip_x(x);  p[0].y = clip_x(y);
  p[1].y = p[2].y = clip_x(y1); p[2].x = p[3].x = clip_x(x2);
  p[3].y = clip_x(y3);
  XDrawLines(fl_display, fl_window, fl_gc, p, 4, 0);
}

void fltk3::XlibGraphicsDriver::line(int x, int y, int x1, int y1) {
  x += origin_x(); y += origin_y(); x1 += origin_x(); y1 += origin_y();
  XDrawLine(fl_display, fl_window, fl_gc, x, y, x1, y1);
}


void fltk3::XlibGraphicsDriver::line(int x, int y, int x1, int y1, int x2, int y2) {
  x += origin_x(); y += origin_y(); x1 += origin_x(); y1 += origin_y(); x2 += origin_x(); y2 += origin_y();
  XPoint p[3];
  p[0].x = x;  p[0].y = y;
  p[1].x = x1; p[1].y = y1;
  p[2].x = x2; p[2].y = y2;
  XDrawLines(fl_display, fl_window, fl_gc, p, 3, 0);
}


void fltk3::XlibGraphicsDriver::loop(int x, int y, int x1, int y1, int x2, int y2) {
  x += origin_x(); y += origin_y(); x1 += origin_x(); y1 += origin_y(); x2 += origin_x(); y2 += origin_y();
  XPoint p[4];
  p[0].x = x;  p[0].y = y;
  p[1].x = x1; p[1].y = y1;
  p[2].x = x2; p[2].y = y2;
  p[3].x = x;  p[3].y = y;
  XDrawLines(fl_display, fl_window, fl_gc, p, 4, 0);
}

void fltk3::XlibGraphicsDriver::loop(int x, int y, int x1, int y1, int x2, int y2, int x3, int y3) {
  x += origin_x(); y += origin_y(); x1 += origin_x(); y1 += origin_y();
  x2 += origin_x(); y2 += origin_y(); x3 += origin_x(); y3 += origin_y();
  XPoint p[5];
  p[0].x = x;  p[0].y = y;
  p[1].x = x1; p[1].y = y1;
  p[2].x = x2; p[2].y = y2;
  p[3].x = x3; p[3].y = y3;
  p[4].x = x;  p[4].y = y;
  XDrawLines(fl_display, fl_window, fl_gc, p, 5, 0);
}


void fltk3::XlibGraphicsDriver::polygon(int x, int y, int x1, int y1, int x2, int y2) {
  x += origin_x(); y += origin_y(); x1 += origin_x(); y1 += origin_y(); x2 += origin_x(); y2 += origin_y();
  XPoint p[4];
  p[0].x = x;  p[0].y = y;
  p[1].x = x1; p[1].y = y1;
  p[2].x = x2; p[2].y = y2;
  p[3].x = x;  p[3].y = y;
  XFillPolygon(fl_display, fl_window, fl_gc, p, 3, Convex, 0);
  XDrawLines(fl_display, fl_window, fl_gc, p, 4, 0);
}

void fltk3::XlibGraphicsDriver::polygon(int x, int y, int x1, int y1, int x2, int y2, int x3, int y3) {
  x += origin_x(); y += origin_y(); x1 += origin_x(); y1 += origin_y();
  x2 += origin_x(); y2 += origin_y(); x3 += origin_x(); y3 += origin_y();
  XPoint p[5];
  p[0].x = x;  p[0].y = y;
  p[1].x = x1; p[1].y = y1;
  p[2].x = x2; p[2].y = y2;
  p[3].x = x3; p[3].y = y3;
  p[4].x = x;  p[4].y = y;
  XFillPolygon(fl_display, fl_window, fl_gc, p, 4, Convex, 0);
  XDrawLines(fl_display, fl_window, fl_gc, p, 5, 0);
}

void fltk3::XlibGraphicsDriver::point(int x, int y) {
  x += origin_x(); y += origin_y();
  XDrawPoint(fl_display, fl_window, fl_gc, clip_x(x), clip_x(y));
}

// Missing X call: (is this the fastest way to init a 1-rectangle region?)
// MSWindows equivalent exists, implemented inline in win32.h
fltk3::Region XRectangleRegion(int x, int y, int w, int h) {
  //x += fltk3::origin_x(); y += fltk3::origin_y();
  XRectangle R;
  clip_to_short(x, y, w, h);
  R.x = x; R.y = y; R.width = w; R.height = h;
  fltk3::Region r = XCreateRegion();
  XUnionRectWithRegion(&R, r, r);
  return r;
}

void fltk3::XlibGraphicsDriver::restore_clip() {
  fl_clip_state_number++;
  fltk3::Region r = clip_region();
  if (r) XSetRegion(fl_display, fl_gc, r);
  else XSetClipMask(fl_display, fl_gc, 0);
}

void fltk3::XlibGraphicsDriver::push_clip(int x, int y, int w, int h) {
  x += origin_x(); y += origin_y();
  fltk3::Region r;
  if (w > 0 && h > 0) {
    r = XRectangleRegion(x,y,w,h);
    fltk3::Region current = clip_region();
    if (current) {
      fltk3::Region temp = XCreateRegion();
      XIntersectRegion(current, r, temp);
      XDestroyRegion(r);
      r = temp;
    }
  } else { // make empty clip region:
    r = XCreateRegion();
  }
  region_stack_push(r);
  restore_clip();
}

int fltk3::XlibGraphicsDriver::not_clipped(int x, int y, int w, int h) {
  x += origin_x(); y += origin_y();
  if (x+w <= 0 || y+h <= 0) return 0;
  fltk3::Region r = clip_region();
  if (!r) return 1;
  // get rid of coordinates outside the 16-bit range the X calls take.
  if (clip_to_short(x,y,w,h)) return 0;	// clipped
  return XRectInRegion(r, x, y, w, h);
}


int fltk3::XlibGraphicsDriver::clip_box(int x, int y, int w, int h, int& X, int& Y, int& W, int& H){
  X = x; Y = y; W = w; H = h;
  x += origin_x(); y += origin_y();
  fltk3::Region r = clip_region();
  if (!r) return 0;
  switch (XRectInRegion(r, x, y, w, h)) {
    case 0: // completely outside
      W = H = 0;
      return 2;
    case 1: // completely inside:
      return 0;
    default: // partial:
      break;
  }
  fltk3::Region rr = XRectangleRegion(x,y,w,h);
  fltk3::Region temp = XCreateRegion();
  XIntersectRegion(r, rr, temp);
  XRectangle rect;
  XClipBox(temp, &rect);
  X = rect.x; Y = rect.y; W = rect.width; H = rect.height;
  XDestroyRegion(temp);
  XDestroyRegion(rr);
  X -= origin_x(); Y -= origin_y();
  return 1;
}


#endif // USE_X11

//
// End of "$Id$".
//
