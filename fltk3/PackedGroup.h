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
// "$Id: Fl_Pack.H 6664 2009-02-18 09:27:54Z AlbrechtS $"
//
// Pack header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Pack widget . */

#ifndef Fl_Pack_H
#define Fl_Pack_H

#include <FL/Fl_Group.H>

/**
  This widget was designed to add the functionality of compressing and
  aligning widgets.
  <P>If type() is Fl_Pack::HORIZONTAL all the children are
  resized to the height of the Fl_Pack, and are moved next to
  each other horizontally. If type() is not Fl_Pack::HORIZONTAL
  then the children are resized to the width and are stacked below each
  other.  Then the Fl_Pack resizes itself to surround the child
  widgets.
  <P>This widget is needed for the Fl_Tabs.
  In addition you may want to put the Fl_Pack inside an 
  Fl_Scroll.

  <P>The resizable for Fl_Pack is set to NULL by default.</p>
  <P>See also: Fl_Group::resizable()
*/
class FL_EXPORT Fl_Pack : public Fl_Group {
  int spacing_;

public:
  enum { // values for type(int)
    VERTICAL = 0,
    HORIZONTAL = 1
  };

protected:
  void draw();

public:
  Fl_Pack(int x,int y,int w ,int h,const char *l = 0);
  /**
    Gets the number of extra pixels of blank space that are added
    between the children.
  */
  int spacing() const {return spacing_;}
  /**
    Sets the number of extra pixels of blank space that are added
    between the children.
  */
  void spacing(int i) {spacing_ = i;}
  /** Same as Fl_Group::type() */
  uchar horizontal() const {return type();}
};

#endif

//
// End of "$Id: Fl_Pack.H 6664 2009-02-18 09:27:54Z AlbrechtS $".
//

/* suggested twin class
// This is the Twin Class to fltk::PackedGroup
class Fl_Pack : public fltk::PackedGroup {
public:
  Fl_Pack(int x, int t, int w, int h, const char *label=0)
  : fltk::PackedGroup(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Pack.H 6664 2009-02-18 09:27:54Z AlbrechtS $"
//
// Pack header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Pack widget . */

#ifndef Fl_Pack_H
#define Fl_Pack_H

#include <FL/Fl_Group.H>

/**
  This widget was designed to add the functionality of compressing and
  aligning widgets.
  <P>If type() is Fl_Pack::HORIZONTAL all the children are
  resized to the height of the Fl_Pack, and are moved next to
  each other horizontally. If type() is not Fl_Pack::HORIZONTAL
  then the children are resized to the width and are stacked below each
  other.  Then the Fl_Pack resizes itself to surround the child
  widgets.
  <P>This widget is needed for the Fl_Tabs.
  In addition you may want to put the Fl_Pack inside an 
  Fl_Scroll.

  <P>The resizable for Fl_Pack is set to NULL by default.</p>
  <P>See also: Fl_Group::resizable()
*/
class FL_EXPORT Fl_Pack : public Fl_Group {
  int spacing_;

public:
  enum { // values for type(int)
    VERTICAL = 0,
    HORIZONTAL = 1
  };

protected:
  void draw();

public:
  Fl_Pack(int x,int y,int w ,int h,const char *l = 0);
  /**
    Gets the number of extra pixels of blank space that are added
    between the children.
  */
  int spacing() const {return spacing_;}
  /**
    Sets the number of extra pixels of blank space that are added
    between the children.
  */
  void spacing(int i) {spacing_ = i;}
  /** Same as Fl_Group::type() */
  uchar horizontal() const {return type();}
};

#endif

//
// End of "$Id: Fl_Pack.H 6664 2009-02-18 09:27:54Z AlbrechtS $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id: PackedGroup.h 6132 2008-05-29 23:09:01Z TobiasFar $"
//
// Group that places all it's child widgets packed against the
// edges. The edge is decided by the PACK_VERTICAL flag stored on
// the child and by whether the child is before or after the
// resizable() child.
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
// Please report all bugs and problems to "fltk-bugs@fltk.org".
//

#ifndef fltk_PackedGroup_h
#define fltk_PackedGroup_h

#include "Group.h"

namespace fltk {

class FL_API PackedGroup : public Group {
  int spacing_;
  int margin_left_;
  int margin_right_;
  int margin_top_;
  int margin_bottom_;
public:
  enum { // values for type(int), for back-compatability
    NORMAL	= GROUP_TYPE,
    ALL_CHILDREN_VERTICAL = GROUP_TYPE+1
  };
  void layout();
  PackedGroup(int x, int y, int w, int h, const char *l = 0, bool begin=false);
  int spacing() const {return spacing_;}
  void spacing(int i) {spacing_ = i;}

  int margin_left() const {return margin_left_;}
  void margin_left(int m) {margin_left_ = m;}
  int margin_right() const {return margin_right_;}
  void margin_right(int m) {margin_right_ = m;}
  int margin_top() const {return margin_top_;}
  void margin_top(int m) {margin_top_ = m;}
  int margin_bottom() const {return margin_bottom_;}
  void margin_bottom(int m) {margin_bottom_ = m;}

  void margin(int m) {margin_left_ = margin_right_ = margin_top_ = margin_bottom_ = m;}
};

}

#endif

//
// End of "$Id: PackedGroup.h 6132 2008-05-29 23:09:01Z TobiasFar $".
//
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
