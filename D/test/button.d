//
// "$Id: button.d 4288 2005-04-16 00:13:17Z mike $"
//
// Button/callback test program for the Fast Light Tool Kit (FLTK).
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

module test.button;

public import std.c.stdlib;

public import fl.fl;
public import fl.ask;
public import fl.window;
public import fl.button;

void beepcb(Fl_Widget w, void* u) {
  fl_beep();
}

void exitcb(Fl_Widget w, void* u) {
  exit(0);
}

int main(char[][] args) {
  Fl_Window window = new Fl_Window(320,65,"FLTK Button demo");
  Fl_Button b1 = new Fl_Button(20, 20, 80, 25, "&Beep");
  b1.callback(&beepcb, null);
  Fl_Button b2 = new Fl_Button(120,20, 80, 25, "&no op");
  Fl_Button b3 = new Fl_Button(220,20, 80, 25, "E&xit");
  b3.callback(&exitcb, null);
  window.end();
  window.show(args);
  return Fl.run();
}

//
// End of "$Id: button.d 4288 2005-04-16 00:13:17Z mike $".
//
