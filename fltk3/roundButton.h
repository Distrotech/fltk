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
// "$Id: Fl_Round_Button.H 6614 2009-01-01 16:11:32Z matt $"
//
// Round button header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Round_Button widget . */

#ifndef Fl_Round_Button_H
#define Fl_Round_Button_H

#include "LightButton.h"

/**
  Buttons generate callbacks when they are clicked by the user.  You
  control exactly when and how by changing the values for type()
  and when().
  <P ALIGN=CENTER>\image html Fl_Round_Button.gif</P> 
  \image latex  Fl_Round_Button.eps " Fl_Round_Button" width=4cm
  <P>The Fl_Round_Button subclass display the "on" state by
  turning on a light, rather than drawing pushed in.  The shape of the
  "light" is initially set to FL_ROUND_DOWN_BOX.  The color of the light
  when on is controlled with selection_color(), which defaults to
  FL_RED.
*/
class FL_EXPORT Fl_Round_Button : public Fl_Light_Button {
public:
  Fl_Round_Button(int x,int y,int w,int h,const char *l = 0);
};

#endif

//
// End of "$Id: Fl_Round_Button.H 6614 2009-01-01 16:11:32Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::roundButton
class Fl_Round_Button : public fltk::roundButton {
public:
  Fl_Round_Button(int x, int t, int w, int h, const char *label=0)
  : fltk::roundButton(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Round_Button.H 6614 2009-01-01 16:11:32Z matt $"
//
// Round button header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Round_Button widget . */

#ifndef Fl_Round_Button_H
#define Fl_Round_Button_H

#include "Fl_Light_Button.H"

/**
  Buttons generate callbacks when they are clicked by the user.  You
  control exactly when and how by changing the values for type()
  and when().
  <P ALIGN=CENTER>\image html Fl_Round_Button.gif</P> 
  \image latex  Fl_Round_Button.eps " Fl_Round_Button" width=4cm
  <P>The Fl_Round_Button subclass display the "on" state by
  turning on a light, rather than drawing pushed in.  The shape of the
  "light" is initially set to FL_ROUND_DOWN_BOX.  The color of the light
  when on is controlled with selection_color(), which defaults to
  FL_RED.
*/
class FL_EXPORT Fl_Round_Button : public Fl_Light_Button {
public:
  Fl_Round_Button(int x,int y,int w,int h,const char *l = 0);
};

#endif

//
// End of "$Id: Fl_Round_Button.H 6614 2009-01-01 16:11:32Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
