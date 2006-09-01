//
// "$Id: box.d 4288 2005-04-16 00:13:17Z mike $"
//
// Box header file for the Fast Light Tool Kit (FLTK).
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

module fl.box;

public import fl.widget;
private import fl.enumerations;


class Fl_Box : Fl_Widget {
protected:
  void draw() {
    draw_box();
    draw_label();
  }

public:
  this(int X, int Y, int W, int H, char *l=null) {
    super(X,Y,W,H,l);
  }

  this(Fl_Boxtype b, int X, int Y, int W, int H, char *l) {
    super(X,Y,W,H,l);
    box(b);
  }

  int handle(int event) {
    if (event == FL_ENTER || event == FL_LEAVE) return 1;
    else return 0;
  }
}

//
// End of "$Id: box.d 4288 2005-04-16 00:13:17Z mike $".
//
