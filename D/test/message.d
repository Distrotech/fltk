//
// "$Id: message.d 4626 2005-11-02 13:57:56Z matt $"
//
// Message test program for the Fast Light Tool Kit (FLTK).
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

public import fl.fl;
public import fl.window;
public import fl.ask;

public import std.stdio;
public import std.string;

int main(char[][] args) {
  Fl.scheme(null);
  Fl.args(args);
  Fl.get_system_colors();

  fl_message("Spelling check sucessful, %d errors found with %g%% confidence\0",
	     1002, 100*(15/77.0));

  fl_alert("Quantum fluctuations in the space-time continuum detected, "
	   "you have %g seconds to comply.\0", 10.0);

  writef("fl_choice returned %d\n",
    fl_choice("Do you really want to %.*s?\0", "No\0", "Yes\0", null, "continue\0"));

  writef("fl_choice returned %d\n\0",
    fl_choice("Choose one of the following:\0","choice0\0","choice1\0","choice2\0"));

  char* r;

  r = fl_input("Please enter a string for '%.*s':\0", "this is the default value\0",
	       "testing\0");
  writef("fl_input returned \"%s\"\n", r ? toString(r) : "NULL");

  r = fl_password("Enter %.*s's password:\0", null, "somebody\0");
  writef("fl_password returned \"%s\"\n", r ? toString(r) : "NULL");

  return 0;
}

//
// End of "$Id: message.d 4626 2005-11-02 13:57:56Z matt $".
//
