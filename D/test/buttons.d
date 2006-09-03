//
// "$Id: buttons.cxx 4640 2005-11-06 09:55:36Z matt $"
//
// Another button test program for the Fast Light Tool Kit (FLTK).
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

private import std.stdio;
private import fl.fl;
private import fl.window;
private import fl.button;
private import fl.return_button;
private import fl.repeat_button;
private import fl.check_button;
private import fl.light_button;
private import fl.round_button;
private import fl.tooltip;

void return_cb(Fl_Widget w, void* d) {
  writefln("Return callback called...");
}

void repeat_cb(Fl_Widget w, void* d) {
  writefln("Repeat callback called...");
}

int main(char[][] args) {
  Fl_Widget w;
  Fl_Window  window = new Fl_Window(320,130);
  (new Fl_Button(10, 10, 130, 30, "Fl_Button")).tooltip("This is a Tooltip.");
  w = new Fl_Return_Button(150, 10, 160, 30, "Fl_Return_Button");
  w.callback(&return_cb);
  w = new Fl_Repeat_Button(10,50,130,30,"Fl_Repeat_Button");
  w.callback(&repeat_cb);
  new Fl_Light_Button(10,90,130,30,"Fl_Light_Button");
  new Fl_Round_Button(150,50,160,30,"Fl_Round_Button");
  new Fl_Check_Button(150,90,160,30,"Fl_Check_Button");
  window.end();
  window.show(args);
  return Fl.run();
}

//
// End of "$Id: buttons.cxx 4640 2005-11-06 09:55:36Z matt $".
//
