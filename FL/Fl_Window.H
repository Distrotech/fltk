//
// "$Id$"
//
// Window header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Window widget . */

#ifndef Fl_Window_H
#define Fl_Window_H
#include "../fltk/Window.h"

// stub class to map Fl_Window to fltk::Window
class Fl_Window : public fltk::Window {
  friend class Fl_X;
public:
  Fl_Window(int w, int h, const char* title= 0) 
  : fltk::Window(w, h, title) { }
  Fl_Window(int x, int y, int w, int h, const char* title = 0) 
  : fltk::Window(x, y, w, h, title) { }
private:
  Fl_Window(const Fl_Window&);
  Fl_Window& operator=(const Fl_Window&);
};

#endif

//
// End of "$Id$".
//
