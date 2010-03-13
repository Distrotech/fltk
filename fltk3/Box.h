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
// "$Id: Fl_Box.H 6614 2009-01-01 16:11:32Z matt $"
//
// Box header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Box widget . */

#ifndef Fl_Box_H
#define Fl_Box_H

#ifndef Fl_Widget_H
#include "Widget.h"
#endif

/**
  This widget simply draws its box, and possibly it's label.  Putting it
  before some other widgets and making it big enough to surround them
  will let you draw a frame around them.
*/
class FL_EXPORT Fl_Box : public Fl_Widget {
protected:
  void draw();
public:
  /**
    - The first constructor sets box() to FL_NO_BOX, which
    means it is invisible. However such widgets are useful as placeholders
    or Fl_Group::resizable()
    values.  To change the box to something visible, use box(n).
    - The second form of the constructor sets the box to the specified box
    type.
    <P>The destructor removes the box.
  */
    Fl_Box(int X, int Y, int W, int H, const char *l=0)
	: Fl_Widget(X,Y,W,H,l) {}
  /**    See Fl_Box::Fl_Box(int x, int y, int w, int h, const char * = 0)   */
    Fl_Box(Fl_Boxtype b, int X, int Y, int W, int H, const char *l)
	: Fl_Widget(X,Y,W,H,l) {box(b);}

  virtual int handle(int);
};

#endif

//
// End of "$Id: Fl_Box.H 6614 2009-01-01 16:11:32Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::Box
class Fl_Box : public fltk::Box {
public:
  Fl_Box(int x, int t, int w, int h, const char *label=0)
  : fltk::Box(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Box.H 6614 2009-01-01 16:11:32Z matt $"
//
// Box header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Box widget . */

#ifndef Fl_Box_H
#define Fl_Box_H

#ifndef Fl_Widget_H
#include "Fl_Widget.H"
#endif

/**
  This widget simply draws its box, and possibly it's label.  Putting it
  before some other widgets and making it big enough to surround them
  will let you draw a frame around them.
*/
class FL_EXPORT Fl_Box : public Fl_Widget {
protected:
  void draw();
public:
  /**
    - The first constructor sets box() to FL_NO_BOX, which
    means it is invisible. However such widgets are useful as placeholders
    or Fl_Group::resizable()
    values.  To change the box to something visible, use box(n).
    - The second form of the constructor sets the box to the specified box
    type.
    <P>The destructor removes the box.
  */
    Fl_Box(int X, int Y, int W, int H, const char *l=0)
	: Fl_Widget(X,Y,W,H,l) {}
  /**    See Fl_Box::Fl_Box(int x, int y, int w, int h, const char * = 0)   */
    Fl_Box(Fl_Boxtype b, int X, int Y, int W, int H, const char *l)
	: Fl_Widget(X,Y,W,H,l) {box(b);}

  virtual int handle(int);
};

#endif

//
// End of "$Id: Fl_Box.H 6614 2009-01-01 16:11:32Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id: Box.h 5865 2007-06-01 13:04:19Z sanel.z $"
//
// Define your own values for box() on a widget by making one of these.
//
// Copyright 2002 by Bill Spitzak and others.
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
// Please report all bugs and problems to "fltk-bugs@fltk.org".
//

#ifndef fltk_Box_h
#define fltk_Box_h

#include "Color.h"
#include "Flags.h"
#include "Symbol.h"

namespace fltk {

typedef Symbol Box;

class FL_API FrameBox : public Box {
protected:
  const char* data_;
  const Box* down_;
public:
  const char* data() const {return data_;}
  void data(const char* d) {data_ = d;}
  void _draw(const Rectangle&) const;
  void inset(Rectangle&) const;
  bool fills_rectangle() const;
  bool is_frame() const;
  FrameBox(const char* name, int dx,int dy,int dw,int dh, const char* pattern, const Box* down=0)
    : Box(name),data_(pattern),down_(down) {set_inset(dx,dy,-dw,-dh);}
};

class FL_API FlatBox : public Box {
public:
  void _draw(const Rectangle&) const;
  bool fills_rectangle() const;
  bool is_frame() const;
  FlatBox(const char* n);
};

class FL_API HighlightBox : public FlatBox {
  const Box* down_;
public:
  void _draw(const Rectangle&) const;
  bool fills_rectangle() const;
  bool is_frame() const;
  HighlightBox(const char* n, const Box* d);
};

}

#endif

//
// End of "$Id: Box.h 5865 2007-06-01 13:04:19Z sanel.z $".
//
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
