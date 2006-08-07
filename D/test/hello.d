//
// "$Id: hello.d 4650 2005-11-18 10:08:13Z matt $"
//
// Hello, World! program for the Fast Light Tool Kit (FLTK) in "D".
//
// Copyright 1998-2006 by Bill Spitzak and others.
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

public import fl.fl;
public import fl.window;
public import fl.box;

public import std.c.osx.coregraphics.cgcontext;

int main(char[][] args) {
  Fl_Window window = new Fl_Window(300,180,"D-FLTK test: hello.d");
  Fl_Box box = new Fl_Box(FL_UP_BOX,20,40,260,100,"Hello, World!");
  box.labelfont(FL_BOLD+FL_ITALIC);
  box.labelsize(36);
  box.labeltype(FL_SHADOW_LABEL);
  window.end();
  window.show(args);
  return Fl.run();
}

//
// End of "$Id: hello.d 4650 2005-11-18 10:08:13Z matt $".
//
