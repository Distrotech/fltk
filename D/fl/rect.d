//
// "$Id: rect.d 5190 2006-06-09 16:16:34Z mike $"
//
// Rectangle drawing routines for the Fast Light Tool Kit (FLTK).
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

// These routines from fl_draw.H are used by the standard boxtypes
// and thus are always linked into an fltk program.
// Also all fl_clip routines, since they are always linked in so
// that minimal update works.

module fl.rect;

public import fl.x;
public import fl.fl;
public import fl.draw;

version (__APPLE__) {
  private import fl.mac;
  private import std.c.osx.qd.quickdraw;
  private import std.c.osx.carbon.carbon;
}


void fl_rect(int x, int y, int w, int h) {
  if (w<=0 || h<=0) return;
  version (WIN32) {
    MoveToEx(fl_gc, x, y, 0L); 
    LineTo(fl_gc, x+w-1, y);
    LineTo(fl_gc, x+w-1, y+h-1);
    LineTo(fl_gc, x, y+h-1);
    LineTo(fl_gc, x, y);
  } else version (__APPLE__) {
    if (fl_quartz_line_width_==1.0f) CGContextSetShouldAntialias(fl_gc, false);
    CGRect rect;
    rect.origin.x = x;
    rect.origin.y = y;
    rect.size.width = w-1;
    rect.size.height = h-1;
    CGContextStrokeRect(fl_gc, rect);
    if (fl_quartz_line_width_==1.0f) CGContextSetShouldAntialias(fl_gc, true);
  } else {
    XDrawRectangle(fl_display, fl_window, fl_gc, x, y, w-1, h-1);
  }
}

void fl_rectf(int x, int y, int w, int h, Fl_Color c) {fl_color(c); fl_rectf(x,y,w,h);}

void fl_rectf(int x, int y, int w, int h) {
  if (w<=0 || h<=0) return;
  version (WIN32) {
    RECT rect;
    rect.left = x; rect.top = y;  
    rect.right = x + w; rect.bottom = y + h;
    FillRect(fl_gc, &rect, fl_brush());
  } else version (__APPLE__) {
    if (fl_quartz_line_width_==1.0f) CGContextSetShouldAntialias(fl_gc, false);
    CGRect rect;
    rect.origin.x = x;
    rect.origin.y = y;
    rect.size.width = w-1;
    rect.size.height = h-1;
    CGContextFillRect(fl_gc, rect);
    if (fl_quartz_line_width_==1.0f) CGContextSetShouldAntialias(fl_gc, true);
  } else {
    if (w && h) XFillRectangle(fl_display, fl_window, fl_gc, x, y, w, h);
  }
}

void fl_xyline(int x, int y, int x1) {
  version (WIN32) {
    MoveToEx(fl_gc, x, y, 0L); LineTo(fl_gc, x1+1, y);
  } else version (__APPLE__) {
    if (fl_quartz_line_width_==1.0f) CGContextSetShouldAntialias(fl_gc, false);
    CGContextMoveToPoint(fl_gc, x, y);
    CGContextAddLineToPoint(fl_gc, x1, y);
    CGContextStrokePath(fl_gc);
    if (fl_quartz_line_width_==1.0f) CGContextSetShouldAntialias(fl_gc, true);
  } else {
    XDrawLine(fl_display, fl_window, fl_gc, x, y, x1, y);
  }
}

void fl_xyline(int x, int y, int x1, int y2) {
  version (WIN32) {
    if (y2 < y) y2--;
    else y2++;
    MoveToEx(fl_gc, x, y, 0L); 
    LineTo(fl_gc, x1, y);
    LineTo(fl_gc, x1, y2);
  } else version (__APPLE__) {
    if (fl_quartz_line_width_==1.0f) CGContextSetShouldAntialias(fl_gc, false);
    CGContextMoveToPoint(fl_gc, x, y);
    CGContextAddLineToPoint(fl_gc, x1, y);
    CGContextAddLineToPoint(fl_gc, x1, y2);
    CGContextStrokePath(fl_gc);
    if (fl_quartz_line_width_==1.0f) CGContextSetShouldAntialias(fl_gc, true);
  } else {
    XPoint p[3];
    p[0].x = x;  p[0].y = p[1].y = y;
    p[1].x = p[2].x = x1; p[2].y = y2;
    XDrawLines(fl_display, fl_window, fl_gc, p, 3, 0);
  }
}

void fl_xyline(int x, int y, int x1, int y2, int x3) {
  version (WIN32) {
    if(x3 < x1) x3--;
    else x3++;
    MoveToEx(fl_gc, x, y, 0L); 
    LineTo(fl_gc, x1, y);
    LineTo(fl_gc, x1, y2);
    LineTo(fl_gc, x3, y2);
  } else version (__APPLE__) {
    if (fl_quartz_line_width_==1.0f) CGContextSetShouldAntialias(fl_gc, false);
    CGContextMoveToPoint(fl_gc, x, y);
    CGContextAddLineToPoint(fl_gc, x1, y);
    CGContextAddLineToPoint(fl_gc, x1, y2);
    CGContextAddLineToPoint(fl_gc, x3, y2);
    CGContextStrokePath(fl_gc);
    if (fl_quartz_line_width_==1.0f) CGContextSetShouldAntialias(fl_gc, true);
  } else {
    XPoint p[4];
    p[0].x = x;  p[0].y = p[1].y = y;
    p[1].x = p[2].x = x1; p[2].y = p[3].y = y2;
    p[3].x = x3;
    XDrawLines(fl_display, fl_window, fl_gc, p, 4, 0);
  }
}

void fl_yxline(int x, int y, int y1) {
  version (WIN32) {
    if (y1 < y) y1--;
    else y1++;
    MoveToEx(fl_gc, x, y, 0L); LineTo(fl_gc, x, y1);
  } else version (__APPLE__) {
    if (fl_quartz_line_width_==1.0f) CGContextSetShouldAntialias(fl_gc, false);
    CGContextMoveToPoint(fl_gc, x, y);
    CGContextAddLineToPoint(fl_gc, x, y1);
    CGContextStrokePath(fl_gc);
    if (fl_quartz_line_width_==1.0f) CGContextSetShouldAntialias(fl_gc, true);
  } else {
    XDrawLine(fl_display, fl_window, fl_gc, x, y, x, y1);
  }
}

void fl_yxline(int x, int y, int y1, int x2) {
  version (WIN32) {
    if (x2 > x) x2++;
    else x2--;
    MoveToEx(fl_gc, x, y, 0L); 
    LineTo(fl_gc, x, y1);
    LineTo(fl_gc, x2, y1);
  } else version (__APPLE__) {
    if (fl_quartz_line_width_==1.0f) CGContextSetShouldAntialias(fl_gc, false);
    CGContextMoveToPoint(fl_gc, x, y);
    CGContextAddLineToPoint(fl_gc, x, y1);
    CGContextAddLineToPoint(fl_gc, x2, y1);
    CGContextStrokePath(fl_gc);
    if (fl_quartz_line_width_==1.0f) CGContextSetShouldAntialias(fl_gc, true);
  } else {
    XPoint p[3];
    p[0].x = p[1].x = x;  p[0].y = y;
    p[1].y = p[2].y = y1; p[2].x = x2;
    XDrawLines(fl_display, fl_window, fl_gc, p, 3, 0);
  }
}

void fl_yxline(int x, int y, int y1, int x2, int y3) {
  version (WIN32) {
    if(y3<y1) y3--;
    else y3++;
    MoveToEx(fl_gc, x, y, 0L); 
    LineTo(fl_gc, x, y1);
    LineTo(fl_gc, x2, y1);
    LineTo(fl_gc, x2, y3);
  } else version (__APPLE__) {
    if (fl_quartz_line_width_==1.0f) CGContextSetShouldAntialias(fl_gc, false);
    CGContextMoveToPoint(fl_gc, x, y);
    CGContextAddLineToPoint(fl_gc, x, y1);
    CGContextAddLineToPoint(fl_gc, x2, y1);
    CGContextAddLineToPoint(fl_gc, x2, y3);
    CGContextStrokePath(fl_gc);
    if (fl_quartz_line_width_==1.0f) CGContextSetShouldAntialias(fl_gc, true);
  } else {
    XPoint p[4];
    p[0].x = p[1].x = x;  p[0].y = y;
    p[1].y = p[2].y = y1; p[2].x = p[3].x = x2;
    p[3].y = y3;
    XDrawLines(fl_display, fl_window, fl_gc, p, 4, 0);
  }
}

void fl_line(int x, int y, int x1, int y1) {
  version (WIN32) {
    MoveToEx(fl_gc, x, y, 0L); 
    LineTo(fl_gc, x1, y1);
    // Draw the last point *again* because the GDI line drawing
    // functions will not draw the last point ("it's a feature!"...)
    SetPixel(fl_gc, x1, y1, fl_RGB());
  } else version (__APPLE__) {
    if (fl_quartz_line_width_==1.0f ) CGContextSetShouldAntialias(fl_gc, false);
    CGContextMoveToPoint(fl_gc, x, y);
    CGContextAddLineToPoint(fl_gc, x1, y1);
    CGContextStrokePath(fl_gc);
    if (fl_quartz_line_width_==1.0f) CGContextSetShouldAntialias(fl_gc, true);
  } else {
    XDrawLine(fl_display, fl_window, fl_gc, x, y, x1, y1);
  }
}

void fl_line(int x, int y, int x1, int y1, int x2, int y2) {
  version (WIN32) {
    MoveToEx(fl_gc, x, y, 0L); 
    LineTo(fl_gc, x1, y1);
    LineTo(fl_gc, x2, y2);
    // Draw the last point *again* because the GDI line drawing
    // functions will not draw the last point ("it's a feature!"...)
    SetPixel(fl_gc, x2, y2, fl_RGB());
  } else version (__APPLE__) {
    if (fl_quartz_line_width_==1.0f ) CGContextSetShouldAntialias(fl_gc, false);
    CGContextMoveToPoint(fl_gc, x, y);
    CGContextAddLineToPoint(fl_gc, x1, y1);
    CGContextAddLineToPoint(fl_gc, x2, y2);
    CGContextStrokePath(fl_gc);
    if (fl_quartz_line_width_==1.0f ) CGContextSetShouldAntialias(fl_gc, true);
  } else {
    XPoint p[3];
    p[0].x = x;  p[0].y = y;
    p[1].x = x1; p[1].y = y1;
    p[2].x = x2; p[2].y = y2;
    XDrawLines(fl_display, fl_window, fl_gc, p, 3, 0);
  }
}

void fl_loop(int x, int y, int x1, int y1, int x2, int y2) {
  version (WIN32) {
    MoveToEx(fl_gc, x, y, 0L); 
    LineTo(fl_gc, x1, y1);
    LineTo(fl_gc, x2, y2);
    LineTo(fl_gc, x, y);
  } else version (__APPLE__) {
    CGContextMoveToPoint(fl_gc, x, y);
    CGContextAddLineToPoint(fl_gc, x1, y1);
    CGContextAddLineToPoint(fl_gc, x2, y2);
    CGContextClosePath(fl_gc);
    CGContextStrokePath(fl_gc);
  } else {
    XPoint p[4];
    p[0].x = x;  p[0].y = y;
    p[1].x = x1; p[1].y = y1;
    p[2].x = x2; p[2].y = y2;
    p[3].x = x;  p[3].y = y;
    XDrawLines(fl_display, fl_window, fl_gc, p, 4, 0);
  }
}

void fl_loop(int x, int y, int x1, int y1, int x2, int y2, int x3, int y3) {
  version (WIN32) {
    MoveToEx(fl_gc, x, y, 0L); 
    LineTo(fl_gc, x1, y1);
    LineTo(fl_gc, x2, y2);
    LineTo(fl_gc, x3, y3);
    LineTo(fl_gc, x, y);
  } else version (__APPLE__) {
    CGContextMoveToPoint(fl_gc, x, y);
    CGContextAddLineToPoint(fl_gc, x1, y1);
    CGContextAddLineToPoint(fl_gc, x2, y2);
    CGContextAddLineToPoint(fl_gc, x3, y3);
    CGContextClosePath(fl_gc);
    CGContextStrokePath(fl_gc);
  } else {
    XPoint p[5];
    p[0].x = x;  p[0].y = y;
    p[1].x = x1; p[1].y = y1;
    p[2].x = x2; p[2].y = y2;
    p[3].x = x3; p[3].y = y3;
    p[4].x = x;  p[4].y = y;
    XDrawLines(fl_display, fl_window, fl_gc, p, 5, 0);
  }
}

void fl_polygon(int x, int y, int x1, int y1, int x2, int y2) {
  XPoint p[4];
  p[0].x = x;  p[0].y = y;
  p[1].x = x1; p[1].y = y1;
  p[2].x = x2; p[2].y = y2;
  version (WIN32) {
    SelectObject(fl_gc, fl_brush());
    Polygon(fl_gc, p, 3);
  } else version (__APPLE__) {
    CGContextMoveToPoint(fl_gc, x, y);
    CGContextAddLineToPoint(fl_gc, x1, y1);
    CGContextAddLineToPoint(fl_gc, x2, y2);
    CGContextClosePath(fl_gc);
    CGContextFillPath(fl_gc);
  } else {
    p[3].x = x;  p[3].y = y;
    XFillPolygon(fl_display, fl_window, fl_gc, p, 3, Convex, 0);
    XDrawLines(fl_display, fl_window, fl_gc, p, 4, 0);
  }
}

void fl_polygon(int x, int y, int x1, int y1, int x2, int y2, int x3, int y3) {
  XPoint p[5];
  p[0].x = x;  p[0].y = y;
  p[1].x = x1; p[1].y = y1;
  p[2].x = x2; p[2].y = y2;
  p[3].x = x3; p[3].y = y3;
  version (WIN32) {
    SelectObject(fl_gc, fl_brush());
    Polygon(fl_gc, p, 4);
  } else version (__APPLE__) {
    CGContextMoveToPoint(fl_gc, x, y);
    CGContextAddLineToPoint(fl_gc, x1, y1);
    CGContextAddLineToPoint(fl_gc, x2, y2);
    CGContextAddLineToPoint(fl_gc, x3, y3);
    CGContextClosePath(fl_gc);
    CGContextFillPath(fl_gc);
  } else {
    p[4].x = x;  p[4].y = y;
    XFillPolygon(fl_display, fl_window, fl_gc, p, 4, Convex, 0);
    XDrawLines(fl_display, fl_window, fl_gc, p, 5, 0);
  }
}

void fl_point(int x, int y) {
  version (WIN32) {
    SetPixel(fl_gc, x, y, fl_RGB());
  } else version (__APPLE__) {
    if (fl_quartz_line_width_==1.0f) CGContextSetShouldAntialias(fl_gc, false);
    CGContextMoveToPoint(fl_gc, x, y);
    CGContextAddLineToPoint(fl_gc, x, y);
    CGContextStrokePath(fl_gc);
    if (fl_quartz_line_width_==1.0f) CGContextSetShouldAntialias(fl_gc, true);
  } else {
    XDrawPoint(fl_display, fl_window, fl_gc, x, y);
  }
}

////////////////////////////////////////////////////////////////

const int STACK_SIZE = 10; 
const int STACK_MAX = (STACK_SIZE - 1); 
static Fl_Region rstack[STACK_SIZE];
static int rstackptr=0;
int fl_clip_state_number=0; // used by gl_begin.cxx to update GL clip

/+=
#if !defined(WIN32) && !defined(__APPLE__)
// Missing X call: (is this the fastest way to init a 1-rectangle region?)
// MSWindows equivalent exists, implemented in win32.H
Fl_Region XRectangleRegion(int x, int y, int w, int h) {
  XRectangle R;
  R.x = x; R.y = y; R.width = w; R.height = h;
  Fl_Region r = XCreateRegion();
  XUnionRectWithRegion(&R, r, r);
  return r;
}
}

version (__APPLE_QD__) {
extern Fl_Region fl_window_region;
} else version (__APPLE_QUARTZ__) {
// warning: the Quartz implementation currently uses Quickdraw calls to achieve
//          clipping. A future version should instead use 'CGContectClipToRect'
//          and friends.
extern Fl_Region fl_window_region;
}
=+/

// undo any clobbering of clip done by your program:
void fl_restore_clip() {
  fl_clip_state_number++;
  Fl_Region r = rstack[rstackptr];
  version (WIN32) {
    SelectClipRgn(fl_gc, r); //if r is NULL, clip is automatically cleared
  } else version (__APPLE__) {
    if ( fl_window )
    {
      GrafPtr port = GetWindowPort( fl_window );
      if ( port ) { 
        RgnHandle portClip = NewRgn();
        CopyRgn( fl_window_region, portClip ); // changed
        if ( r )
          SectRgn( portClip, r, portClip );
        Rect portRect; GetPortBounds(port, &portRect);
        Fl_X.q_clear_clipping();
        ClipCGContextToRegion(fl_gc, &portRect, portClip );
        Fl_X.q_fill_context();
        DisposeRgn( portClip );
      }
    }
  } else {
    if (r) XSetRegion(fl_display, fl_gc, r);
    else XSetClipMask(fl_display, fl_gc, 0);
  }
}

// Replace the top of the clip stack:
void fl_clip_region(Fl_Region r) {
  Fl_Region oldr = rstack[rstackptr];
  if (oldr) XDestroyRegion(oldr);
  rstack[rstackptr] = r;
  fl_restore_clip();
}

/+=
// Return the current clip region...
Fl_Region fl_clip_region() {
  return rstack[rstackptr];
}
=+/

void fl_clip(int x, int y, int w, int h) {
  fl_push_clip(x, y, w, h);
}

// Intersect & push a new clip rectangle:
void fl_push_clip(int x, int y, int w, int h) {
  Fl_Region r;
  if (w > 0 && h > 0) {
    r = XRectangleRegion(x,y,w,h);
    Fl_Region current = rstack[rstackptr];
    if (current) {
      version (WIN32) {
        CombineRgn(r,r,current,RGN_AND);
      } else version (__APPLE__) {
        SectRgn(r, current, r);
      } else {
        Fl_Region temp = XCreateRegion();
        XIntersectRegion(current, r, temp);
        XDestroyRegion(r);
        r = temp;
      }
    }
  } else { // make empty clip region:
    version (WIN32) {
      r = CreateRectRgn(0,0,0,0);
    } else version (__APPLE__) {
      r = NewRgn();
      SetEmptyRgn(r);
    } else {
      r = XCreateRegion();
    }
  }
  if (rstackptr < STACK_MAX) rstack[++rstackptr] = r;
  else Fl.warning("fl_push_clip: clip stack overflow!\n");
  fl_restore_clip();
}

// make there be no clip (used by fl_begin_offscreen() only!)
void fl_push_no_clip() {
  if (rstackptr < STACK_MAX) rstack[++rstackptr] = null;
  else Fl.warning("fl_push_no_clip: clip stack overflow!\n");
  fl_restore_clip();
}

// pop back to previous clip:
void fl_pop_clip() {
  if (rstackptr > 0) {
    Fl_Region oldr = rstack[rstackptr--];
    if (oldr) XDestroyRegion(oldr);
  } else Fl.warning("fl_pop_clip: clip stack underflow!\n");
  fl_restore_clip();
}

// does this rectangle intersect current clip?
int fl_not_clipped(int x, int y, int w, int h) {
  if (x+w <= 0 || y+h <= 0) return 0;
  Fl_Region r = rstack[rstackptr];
  version (WIN32) {
    if (!r) return 1;
    RECT rect;
    rect.left = x; rect.top = y; rect.right = x+w; rect.bottom = y+h;
    return RectInRegion(r,&rect);
  } else version (__APPLE__) {
    if (!r) return 1;
    Rect rect;
    rect.left = x; rect.top = y; rect.right = x+w; rect.bottom = y+h;
    return RectInRgn(&rect, r);
  } else {
    return r ? XRectInRegion(r, x, y, w, h) : 1;
  }
}

/+=
// return rectangle surrounding intersection of this rectangle and clip:
int fl_clip_box(int x, int y, int w, int h, int& X, int& Y, int& W, int& H){
  X = x; Y = y; W = w; H = h;
  Fl_Region r = rstack[rstackptr];
  if (!r) return 0;
version (WIN32) {
// The win32 API makes no distinction between partial and complete
// intersection, so we have to check for partial intersection ourselves.
// However, given that the regions may be composite, we have to do
// some voodoo stuff...
  Fl_Region rr = XRectangleRegion(x,y,w,h);
  Fl_Region temp = CreateRectRgn(0,0,0,0);
  int ret;
  if (CombineRgn(temp, rr, r, RGN_AND) == NULLREGION) { // disjoint
    W = H = 0;
    ret = 2;
  } else if (EqualRgn(temp, rr)) { // complete
    ret = 0;
  } else {	// parital intersection
    RECT rect;
    GetRgnBox(temp, &rect);
    X = rect.left; Y = rect.top; W = rect.right - X; H = rect.bottom - Y;
    ret = 1;
  }
  DeleteObject(temp);
  DeleteObject(rr);
  return ret;
} else version (__APPLE_QD__) {
  RgnHandle rr = NewRgn();
  SetRectRgn( rr, x, y, x+w, y+h );
  SectRgn( r, rr, rr );
  Rect rp; GetRegionBounds(rr, &rp);
  X = rp.left;
  Y = rp.top;
  W = rp.right - X;
  H = rp.bottom - Y;
  DisposeRgn( rr );
  if ( H==0 ) return 2;
  if ( h==H && w==W ) return 0;
  return 0;
} else version (__APPLE_QUARTZ__) {
  RgnHandle rr = NewRgn();
  SetRectRgn( rr, x, y, x+w, y+h );
  SectRgn( r, rr, rr );
  Rect rp; GetRegionBounds(rr, &rp);
  X = rp.left;
  Y = rp.top;
  W = rp.right - X;
  H = rp.bottom - Y;
  DisposeRgn( rr );
  if ( H==0 ) return 2;
  if ( h==H && w==W ) return 0;
  return 0;
} else {
  switch (XRectInRegion(r, x, y, w, h)) {
  case 0: // completely outside
    W = H = 0;
    return 2;
  case 1: // completely inside:
    return 0;
  default: // partial:
    break;
  }
  Fl_Region rr = XRectangleRegion(x,y,w,h);
  Fl_Region temp = XCreateRegion();
  XIntersectRegion(r, rr, temp);
  XRectangle rect;
  XClipBox(temp, &rect);
  X = rect.x; Y = rect.y; W = rect.width; H = rect.height;
  XDestroyRegion(temp);
  XDestroyRegion(rr);
  return 1;
}
}

//
// End of "$Id: fl_rect.cxx 5190 2006-06-09 16:16:34Z mike $".
//
    End of automatic import -+/
