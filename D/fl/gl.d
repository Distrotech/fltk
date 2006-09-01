/+- This file was imported from C++ using a script
//
// "$Id: gl.h 4288 2005-04-16 00:13:17Z mike $"
//
// OpenGL header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2005 by Bill Spitzak and others.
//
// You must include this instead of GL/gl.h to get the Microsoft
// APIENTRY stuff included (from <windows.h>) prior to the OpenGL
// header files.
//
// This file also provides "missing" OpenGL functions, and
// gl_start() and gl_finish() to allow OpenGL to be used in any window
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

version (!FL_gl_H) {
#  define FL_gl_H

public import fl.enumerations; // for color names
version (WIN32) {
#    include <windows.h>
}
version (!APIENTRY) {
version (__CYGWIN__) {
const int APIENTRY = __attribute__ ((__stdcall__)); 
} else {
#      define APIENTRY
}
}

version (__APPLE__) {
#    include <OpenGL/gl.h>
} else {
#    include <GL/gl.h>
}

void gl_start();
void gl_finish();

void gl_color(Fl_Color);
void gl_color(int c) {gl_color((Fl_Color)c);} // back compatability

void gl_rect(int x,int y,int w,int h);
void gl_rectf(int x,int y,int w,int h) {glRecti(x,y,x+w,y+h);}

void gl_font(int fontid, int size);
int  gl_height();
int  gl_descent();
double gl_width(char *);
double gl_width(char *, int n);
double gl_width(ubyte);

void gl_draw(char*);
void gl_draw(char*, int n);
void gl_draw(char*, int x, int y);
void gl_draw(char*, float x, float y);
void gl_draw(char*, int n, int x, int y);
void gl_draw(char*, int n, float x, float y);
void gl_draw(char*, int x, int y, int w, int h, Fl_Align);
void gl_measure(char*, int& x, int& y);

void gl_draw_image(ubyte *, int x,int y,int w,int h, int d=3, int ld=0);

} // !FL_gl_H

//
// End of "$Id: gl.h 4288 2005-04-16 00:13:17Z mike $".
//
    End of automatic import -+/
