//
// "$Id$"
//
// Portable drawing routines for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2011 by Bill Spitzak and others.
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
  \file fl_vertex.cxx
  \brief  Portable drawing code for drawing arbitrary shapes with
          simple 2D transformations.
*/

// Portable drawing code for drawing arbitrary shapes with
// simple 2D transformations.  See also fltk3::arc.cxx

// matt: the Quartz implementation purposely doesn't use the Quartz matrix
//       operations for reasons of compatibility and maintainability

#include <config.h>
#include <fltk3/draw.h>
#include <fltk3/x.h>
#include <fltk3/run.h>
#include <fltk3/math.h>
#include <stdlib.h>

void fltk3::GraphicsDriver::push_matrix() {
  if (sptr==matrix_stack_size)
    fltk3::error("fltk3::push_matrix(): matrix stack overflow.");
  else
    stack[sptr++] = m;
}

void fltk3::GraphicsDriver::pop_matrix() {
  if (sptr==0)
    fltk3::error("fltk3::pop_matrix(): matrix stack underflow.");
  else 
    m = stack[--sptr];
}

void fltk3::GraphicsDriver::mult_matrix(double a, double b, double c, double d, double x, double y) {
  matrix o;
  o.a = a*m.a + b*m.c;
  o.b = a*m.b + b*m.d;
  o.c = c*m.a + d*m.c;
  o.d = c*m.b + d*m.d;
  o.x = x*m.a + y*m.c + m.x;
  o.y = x*m.b + y*m.d + m.y;
  m = o;
}

void fltk3::GraphicsDriver::rotate(double d) {
  if (d) {
    double s, c;
    if (d == 0) {s = 0; c = 1;}
    else if (d == 90) {s = 1; c = 0;}
    else if (d == 180) {s = 0; c = -1;}
    else if (d == 270 || d == -90) {s = -1; c = 0;}
    else {s = sin(d*M_PI/180); c = cos(d*M_PI/180);}
    mult_matrix(c,-s,s,c,0,0);
  }
}

void fltk3::GraphicsDriver::begin_points() {n = 0; what = POINT_;}

void fltk3::GraphicsDriver::begin_line() {n = 0; what = LINE;}

void fltk3::GraphicsDriver::begin_loop() {n = 0; what = LOOP;}

void fltk3::GraphicsDriver::begin_polygon() {n = 0; what = POLYGON;}

double fltk3::GraphicsDriver::transform_x(double x, double y) {return x*m.a + y*m.c + m.x;}

double fltk3::GraphicsDriver::transform_y(double x, double y) {return x*m.b + y*m.d + m.y;}

double fltk3::GraphicsDriver::transform_dx(double x, double y) {return x*m.a + y*m.c;}

double fltk3::GraphicsDriver::transform_dy(double x, double y) {return x*m.b + y*m.d;}

void fltk3::GraphicsDriver::transformed_vertex0(COORD_T x, COORD_T y) {
  x += origin_x(); y += origin_y();
  if (!n || x != p[n-1].x || y != p[n-1].y) {
    if (n >= p_size) {
      p_size = p ? 2*p_size : 16;
      p = (XPOINT*)realloc((void*)p, p_size*sizeof(*p));
    }
    p[n].x = x;
    p[n].y = y;
    n++;
  }
}

void fltk3::GraphicsDriver::transformed_vertex(double xf, double yf) {
  transformed_vertex0(COORD_T(rint(xf)), COORD_T(rint(yf)));
}

void fltk3::GraphicsDriver::vertex(double x,double y) {
  transformed_vertex0(COORD_T(x*m.a + y*m.c + m.x), COORD_T(x*m.b + y*m.d + m.y));
}

void fltk3::GraphicsDriver::end_points() {
  int n = vertex_no();
  XPOINT *p = vertices();
  for (int i=0; i<n; i++) point(p[i].x, p[i].y);
}


void fltk3::GraphicsDriver::fixloop() {  // remove equal points from closed path
  while (n>2 && p[n-1].x == p[0].x && p[n-1].y == p[0].y) n--;
}

void fltk3::GraphicsDriver::end_loop() {
  fixloop();
  if (n>2) transformed_vertex((COORD_T)p[0].x-origin_x(), (COORD_T)p[0].y-origin_y());
  end_line();
}


void fltk3::GraphicsDriver::begin_complex_polygon() {
  begin_polygon();
  gap_ = 0;
}


void fltk3::GraphicsDriver::gap() {
  while (n>gap_+2 && p[n-1].x == p[gap_].x && p[n-1].y == p[gap_].y) n--;
  if (n > gap_+2) {
    transformed_vertex((COORD_T)p[gap_].x-origin_x(), (COORD_T)p[gap_].y-origin_y());
    gap_ = n;
  } else {
    n = gap_;
  }
}

void fltk3::GraphicsDriver::prepare_circle(double x, double y, double r, int& llx, int& lly, int& w, int& h, double& xt, double& yt)
{
  xt = transform_x(x,y);
  yt = transform_y(x,y);
  double rx = r * (m.c ? sqrt(m.a*m.a+m.c*m.c) : fabs(m.a));
  double ry = r * (m.b ? sqrt(m.b*m.b+m.d*m.d) : fabs(m.d));
  llx = (int)rint(xt-rx);
  w = (int)rint(xt+rx)-llx;
  lly = (int)rint(yt-ry);
  h = (int)rint(yt+ry)-lly;
}

//
// End of "$Id$".
//
