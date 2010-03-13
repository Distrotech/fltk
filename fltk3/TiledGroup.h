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
// "$Id: Fl_Tile.H 6614 2009-01-01 16:11:32Z matt $"
//
// Tile header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Tile widget . */

#ifndef Fl_Tile_H
#define Fl_Tile_H

#include "Group.h"

/**
  The Fl_Tile class lets you resize the children by dragging
  the border between them:
  
  <P ALIGN=CENTER>\image html Fl_Tile.gif </P> 
  \image latex  Fl_Tile.eps "Fl_Tile" width=4cm
  
  <P>For the tiling to work correctly, the children of an 
  Fl_Tile must cover the entire area of the widget, but not
  overlap. This means that all children must touch each 
  other at their edges, and no gaps can't be left inside the 
  Fl_Tile.
  
  <P>Fl_Tile does not normailly draw any graphics of its own.
  The "borders" which can be seen in the snapshot above
  are actually part of the children. Their boxtypes have been set
  to FL_DOWN_BOX creating the impression of 
  "ridges" where the boxes touch. What you see are 
  actually two adjacent FL_DOWN_BOX's drawn next to each 
  other. All neighboring widgets share the same edge - the widget's 
  thick borders make it appear as though the widgets aren't actually
  touching, but they are. If the edges of adjacent widgets do not
  touch, then it will be impossible to drag the corresponding
  edges.</P>
  
  <P>Fl_Tile allows objects to be resized to zero dimensions.
  To prevent this you can use the resizable() to limit where
  corners can be dragged to.</P>
  
  <P>Even though objects can be resized to zero sizes, they must
  initially have non-zero sizes so the Fl_Tile can figure out
  their layout. If desired, call position() after creating the
  children but before displaying the window to set the borders where you
  want.

  <P>Note on resizable(Fl_Widget &w) :
  The "resizable" child widget (which should be invisible) limits where the
  border can be dragged to.  If you don't set it, it will be possible to
  drag the borders right to the edge, and thus resize objects on the edge
  to zero width or height.  The resizable() widget is not
  resized by dragging any borders. See also void Fl_Group::resizable(Fl_Widget &w)

*/
class FL_EXPORT Fl_Tile : public Fl_Group {
public:
  int handle(int);
  /**
    Creates a new Fl_Tile widget using the given position, size,
    and label string. The default boxtype is FL_NO_BOX.
    
    <P>The destructor <I>also deletes all the children</I>. This allows a
    whole tree to be deleted at once, without having to keep a pointer to
    all the children in the user code. A kludge has been done so the 
    Fl_Tile and all of it's children can be automatic (local)
    variables, but you must declare the Fl_Tile <I>first</I>, so
    that it is destroyed last.
  */
  Fl_Tile(int X,int Y,int W,int H,const char*l=0) : Fl_Group(X,Y,W,H,l) {}
  void resize(int, int, int, int);
  void position(int, int, int, int);
};

#endif

//
// End of "$Id: Fl_Tile.H 6614 2009-01-01 16:11:32Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::TiledGroup
class Fl_Tile : public fltk::TiledGroup {
public:
  Fl_Tile(int x, int t, int w, int h, const char *label=0)
  : fltk::TiledGroup(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Tile.H 6614 2009-01-01 16:11:32Z matt $"
//
// Tile header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Tile widget . */

#ifndef Fl_Tile_H
#define Fl_Tile_H

#include "Fl_Group.H"

/**
  The Fl_Tile class lets you resize the children by dragging
  the border between them:
  
  <P ALIGN=CENTER>\image html Fl_Tile.gif </P> 
  \image latex  Fl_Tile.eps "Fl_Tile" width=4cm
  
  <P>For the tiling to work correctly, the children of an 
  Fl_Tile must cover the entire area of the widget, but not
  overlap. This means that all children must touch each 
  other at their edges, and no gaps can't be left inside the 
  Fl_Tile.
  
  <P>Fl_Tile does not normailly draw any graphics of its own.
  The "borders" which can be seen in the snapshot above
  are actually part of the children. Their boxtypes have been set
  to FL_DOWN_BOX creating the impression of 
  "ridges" where the boxes touch. What you see are 
  actually two adjacent FL_DOWN_BOX's drawn next to each 
  other. All neighboring widgets share the same edge - the widget's 
  thick borders make it appear as though the widgets aren't actually
  touching, but they are. If the edges of adjacent widgets do not
  touch, then it will be impossible to drag the corresponding
  edges.</P>
  
  <P>Fl_Tile allows objects to be resized to zero dimensions.
  To prevent this you can use the resizable() to limit where
  corners can be dragged to.</P>
  
  <P>Even though objects can be resized to zero sizes, they must
  initially have non-zero sizes so the Fl_Tile can figure out
  their layout. If desired, call position() after creating the
  children but before displaying the window to set the borders where you
  want.

  <P>Note on resizable(Fl_Widget &w) :
  The "resizable" child widget (which should be invisible) limits where the
  border can be dragged to.  If you don't set it, it will be possible to
  drag the borders right to the edge, and thus resize objects on the edge
  to zero width or height.  The resizable() widget is not
  resized by dragging any borders. See also void Fl_Group::resizable(Fl_Widget &w)

*/
class FL_EXPORT Fl_Tile : public Fl_Group {
public:
  int handle(int);
  /**
    Creates a new Fl_Tile widget using the given position, size,
    and label string. The default boxtype is FL_NO_BOX.
    
    <P>The destructor <I>also deletes all the children</I>. This allows a
    whole tree to be deleted at once, without having to keep a pointer to
    all the children in the user code. A kludge has been done so the 
    Fl_Tile and all of it's children can be automatic (local)
    variables, but you must declare the Fl_Tile <I>first</I>, so
    that it is destroyed last.
  */
  Fl_Tile(int X,int Y,int W,int H,const char*l=0) : Fl_Group(X,Y,W,H,l) {}
  void resize(int, int, int, int);
  void position(int, int, int, int);
};

#endif

//
// End of "$Id: Fl_Tile.H 6614 2009-01-01 16:11:32Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id: TiledGroup.h 5575 2007-01-02 17:31:40Z spitzak $"
//
// The child widgets are expected to be all laid out to touch each other
// and fill this group. The user can then move the boundaries between
// them by grabbing the junctions between the children.
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

#ifndef fltk_TiledGroup_h
#define fltk_TiledGroup_h

#include "Group.h"

namespace fltk {

class FL_API TiledGroup : public Group {
protected:
  void layout();
public:
  int handle(int);
  TiledGroup(int x,int y,int w,int h, const char*l=0, bool begin=false) :
    Group(x,y,w,h,l,begin) {}
  void position(int, int, int, int);
};

}
#endif

//
// End of "$Id: TiledGroup.h 5575 2007-01-02 17:31:40Z spitzak $".
//
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
