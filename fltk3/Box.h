//
// "$Id$"
//
// Box header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2010 by Bill Spitzak and others.
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
   fltk3::Box widget . */

#ifndef FLTK3_Box_H
#define FLTK3_Box_H

#ifndef Fl_Widget_H
#include "Widget.h"
#endif

namespace fltk3 {
  class Box;
}

/**
  This widget simply draws its box, and possibly it's label.  Putting it
  before some other widgets and making it big enough to surround them
  will let you draw a frame around them.
*/
class FL_EXPORT fltk3::Box : public fltk3::Widget {
public:
  /**
    - The first constructor sets box() to fltk3::NO_BOX, which
    means it is invisible. However such widgets are useful as placeholders
    or fltk3::Group::resizable()
    values.  To change the box to something visible, use box(n).
    - The second form of the constructor sets the box to the specified box
    type.
    <P>The destructor removes the box.
  */
    Box(int X, int Y, int W, int H, const char *l=0)
	: fltk3::Widget(X,Y,W,H,l) {}
  /**    See fltk3::Box::Box(int x, int y, int w, int h, const char * = 0)   */
    Box(fltk3::Boxtype b, int X, int Y, int W, int H, const char *l)
	: fltk3::Widget(X,Y,W,H,l) {box(b);}

  virtual int handle(int);
};

#endif

//
// End of "$Id$".
//
