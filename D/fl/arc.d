//
// "$Id: fl_arc.cxx 5349 2006-08-23 14:43:07Z matt $"
//
// Arc functions for the Fast Light Tool Kit (FLTK).
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

// Utility for drawing arcs and circles.  They are added to
// the current fl_begin/fl_vertex/fl_end path.
// Incremental math implementation:

module fl.arc;


private import fl.draw;

/+=
// avoid problems with some platforms that don't 
// implement hypot.
static double _fl_hypot(double x, double y) {
  return sqrt(x*x + y*y);
}


void fl_arc(double x, double y, double r, double start, double end) {

  // draw start point accurately:
  
  double A = start*(M_PI/180);		// Initial angle (radians)
  double X =  r*cos(A);			// Initial displacement, (X,Y)
  double Y = -r*sin(A);			//   from center to initial point
  fl_vertex(x+X,y+Y);			// Insert initial point

  // Maximum arc length to approximate with chord with error <= 0.125
  
  double epsilon; {
    double r1 = _fl_hypot(fl_transform_dx(r,0), // Horizontal "radius"
		          fl_transform_dy(r,0));
    double r2 = _fl_hypot(fl_transform_dx(0,r), // Vertical "radius"
		          fl_transform_dy(0,r));
		      
    if (r1 > r2) r1 = r2;		// r1 = minimum "radius"
    if (r1 < 2.) r1 = 2.;		// radius for circa 9 chords/circle
    
    epsilon = 2*acos(1.0 - 0.125/r1);	// Maximum arc angle
  }
  A = end*(M_PI/180) - A;		// Displacement angle (radians)
  int i = int(ceil(fabs(A)/epsilon));	// Segments in approximation
  
  if (i) {
    epsilon = A/i;			// Arc length for equal-size steps
    double cos_e = cos(epsilon);	// Rotation coefficients
    double sin_e = sin(epsilon);
    do {
      double Xnew =  cos_e*X + sin_e*Y;
		Y = -sin_e*X + cos_e*Y;
      fl_vertex(x + (X=Xnew), y + Y);
    } while (--i);
  }
}

#if 0 // portable version.  X-specific one in fl_vertex.cxx
void fl_circle(double x,double y,double r) {
  _fl_arc(x, y, r, r, 0, 360);
}
}

//
// End of "$Id: fl_arc.cxx 5349 2006-08-23 14:43:07Z matt $".
//
    End of automatic import -+/
//
// "$Id: fl_arci.cxx 5190 2006-06-09 16:16:34Z mike $"
//
// Arc (integer) drawing functions for the Fast Light Tool Kit (FLTK).
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

// "integer" circle drawing functions.  These draw the limited
// circle types provided by X and NT graphics.  The advantage of
// these is that small ones draw quite nicely (probably due to stored
// hand-drawn bitmaps of small circles!) and may be implemented by
// hardware and thus are fast.

// Probably should add fl_chord.

// 3/10/98: created


/+=
private import fl.draw;
#include <FL/x.H>
version (WIN32) {
#include <FL/math.h>
}
version (__APPLE__) {
#include <config.h>
}
=+/

void fl_arc(int x,int y,int w,int h,double a1,double a2) {
  if (w <= 0 || h <= 0) return;
  version (WIN32) {
    int xa = x+w/2+cast(int)(w*cos(a1/180.0*M_PI));
    int ya = y+h/2-cast(int)(h*sin(a1/180.0*M_PI));
    int xb = x+w/2+cast(int)(w*cos(a2/180.0*M_PI));
    int yb = y+h/2-cast(int)(h*sin(a2/180.0*M_PI));
    Arc(fl_gc, x, y, x+w, y+h, xa, ya, xb, yb); 
  } else version (__APPLE__) {
    a1 = (-a1)/180.0f*M_PI; a2 = (-a2)/180.0f*M_PI;
    float cx = x + 0.5f*w - 0.5f, cy = y + 0.5f*h - 0.5f;
    if (w!=h) {
      CGContextSaveGState(fl_gc);
      CGContextTranslateCTM(fl_gc, cx, cy);
      CGContextScaleCTM(fl_gc, w-1.0f, h-1.0f);
      CGContextAddArc(fl_gc, 0, 0, 0.5, a1, a2, 1);
      CGContextRestoreGState(fl_gc);
    } else {
      float r = (w+h)*0.25f-0.5f;
      CGContextAddArc(fl_gc, cx, cy, r, a1, a2, 1);
    }
    CGContextStrokePath(fl_gc);
  } else {
    XDrawArc(fl_display, fl_window, fl_gc, x,y,w-1,h-1, cast(int)(a1*64), cast(int)((a2-a1)*64));
  }
}

void fl_pie(int x,int y,int w,int h,double a1,double a2) {
  if (w <= 0 || h <= 0) return;
  version (WIN32) {
    if (a1 == a2) return;
    int xa = x+w/2+cast(int)(w*cos(a1/180.0*M_PI));
    int ya = y+h/2-cast(int)(h*sin(a1/180.0*M_PI));
    int xb = x+w/2+cast(int)(w*cos(a2/180.0*M_PI));
    int yb = y+h/2-cast(int)(h*sin(a2/180.0*M_PI));
    SelectObject(fl_gc, fl_brush());
    Pie(fl_gc, x, y, x+w, y+h, xa, ya, xb, yb); 
  } else version (__APPLE__) {
    a1 = (-a1)/180.0f*M_PI; a2 = (-a2)/180.0f*M_PI;
    float cx = x + 0.5f*w - 0.5f, cy = y + 0.5f*h - 0.5f;
    if (w!=h) {
      CGContextSaveGState(fl_gc);
      CGContextTranslateCTM(fl_gc, cx, cy);
      CGContextScaleCTM(fl_gc, w, h);
      CGContextAddArc(fl_gc, 0, 0, 0.5, a1, a2, 1);
      CGContextAddLineToPoint(fl_gc, 0, 0);
      CGContextClosePath(fl_gc);
      CGContextRestoreGState(fl_gc);
    } else {
      float r = (w+h)*0.25f;
      CGContextAddArc(fl_gc, cx, cy, r, a1, a2, 1);
      CGContextAddLineToPoint(fl_gc, cx, cy);
      CGContextClosePath(fl_gc);
    }
    CGContextFillPath(fl_gc);
  } else {
    XFillArc(fl_display, fl_window, fl_gc, x,y,w-1,h-1, cast(int)(a1*64),cast(int)((a2-a1)*64));
  }
}

//
// End of "$Id: fl_arci.cxx 5190 2006-06-09 16:16:34Z mike $".
//
