/+- This file was imported from C++ using a script
//
// "$Id: Fl_Single_Window.H 4288 2005-04-16 00:13:17Z mike $"
//
// Single-buffered window header file for the Fast Light Tool Kit (FLTK).
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

#ifndef Fl_Single_Window_H
#define Fl_Single_Window_H

#include "Fl_Window.H"

class FL_EXPORT Fl_Single_Window : public Fl_Window {
public:
  void show();
  void show(int a, char **b) {Fl_Window::show(a,b);}
  void flush();
  Fl_Single_Window(int W, int H, const char *l=0)
    : Fl_Window(W,H,l) {}
  Fl_Single_Window(int X, int Y, int W, int H, const char *l=0)
    : Fl_Window(X,Y,W,H,l) {}
  int make_current();
};

#endif

//
// End of "$Id: Fl_Single_Window.H 4288 2005-04-16 00:13:17Z mike $".
//
    End of automatic import -+/
/+- This file was imported from C++ using a script
//
// "$Id: Fl_Single_Window.cxx 5190 2006-06-09 16:16:34Z mike $"
//
// Single-buffered window for the Fast Light Tool Kit (FLTK).
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

//	A window with a single-buffered context
//
//	This is provided for systems where the base class is double
//	buffered.  You can turn it off using this subclass in case
//	your display looks better without it.

#include <FL/Fl_Single_Window.H>

void Fl_Single_Window::show() {Fl_Window::show();}
void Fl_Single_Window::flush() {Fl_Window::flush();}

//
// End of "$Id: Fl_Single_Window.cxx 5190 2006-06-09 16:16:34Z mike $".
//
    End of automatic import -+/
