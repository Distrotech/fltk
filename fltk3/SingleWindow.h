//
// "$Id$"
//

// 123 TODO: remove stray comments
// 123 TODO: add namespace statements
// 123 TODO: replace class name, constructors and destructor
// 123 TODO: add friend statement for Twin Class
// 123 TODO: add 'compat(FLTK2)' to constructors
// 123 TODO: add twin class with all constructors
// 123 TODO: change all arguments to the FLTK2 class name
// 123 TODO: change the source code to use the new class names
// 123 TODO: add casting to return values
// 123 TODO: move all FLTK2-only functions to the FLTK3 section and implement them
// 123 TODO: remove the FLTK1 and FLTK2 sections in the headers
// 123 TODO: 

//
// "$Id: Fl_Single_Window.H 6614 2009-01-01 16:11:32Z matt $"
//
// Single-buffered window header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2009 by Bill Spitzak and others.
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

/* \file
   Fl_Single_Window class . */

#ifndef Fl_Single_Window_H
#define Fl_Single_Window_H

#include "Window.h"

/**
  This is the same as fltk::Window.  However, it is possible that
  some implementations will provide double-buffered windows by default.
  This subcan be used to force single-buffering.  This may be
  useful for modifying existing programs that use incremental update, or
  for some types of image data, such as a movie flipbook.
*/
class FL_EXPORT Fl_Single_Window : public Fl_Window {
public:
  void show();
  void show(int a, char **b) {Fl_Window::show(a,b);}
  void flush();
   /**
    Creates a new Fl_Single_Window widget using the given
    size, and label (title) string.
  */
  Fl_Single_Window(int W, int H, const char *l=0)
    : Fl_Window(W,H,l) {}
  /**
    Creates a new Fl_Single_Window widget using the given
    position, size, and label (title) string.
  */
  Fl_Single_Window(int X, int Y, int W, int H, const char *l=0)
    : Fl_Window(X,Y,W,H,l) {}
  int make_current();
};

#endif

//
// End of "$Id: Fl_Single_Window.H 6614 2009-01-01 16:11:32Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::singlwWindow
class Fl_Single_Window : public fltk::singlwWindow {
public:
  Fl_Single_Window(int x, int t, int w, int h, const char *label=0)
  : fltk::singlwWindow(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Single_Window.H 6614 2009-01-01 16:11:32Z matt $"
//
// Single-buffered window header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2009 by Bill Spitzak and others.
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

/* \file
   Fl_Single_Window class . */

#ifndef Fl_Single_Window_H
#define Fl_Single_Window_H

#include "Fl_Window.H"

/**
  This is the same as Fl_Window.  However, it is possible that
  some implementations will provide double-buffered windows by default.
  This subcan be used to force single-buffering.  This may be
  useful for modifying existing programs that use incremental update, or
  for some types of image data, such as a movie flipbook.
*/
class FL_EXPORT Fl_Single_Window : public Fl_Window {
public:
  void show();
  void show(int a, char **b) {Fl_Window::show(a,b);}
  void flush();
   /**
    Creates a new Fl_Single_Window widget using the given
    size, and label (title) string.
  */
  Fl_Single_Window(int W, int H, const char *l=0)
    : Fl_Window(W,H,l) {}
  /**
    Creates a new Fl_Single_Window widget using the given
    position, size, and label (title) string.
  */
  Fl_Single_Window(int X, int Y, int W, int H, const char *l=0)
    : Fl_Window(X,Y,W,H,l) {}
  int make_current();
};

#endif

//
// End of "$Id: Fl_Single_Window.H 6614 2009-01-01 16:11:32Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
