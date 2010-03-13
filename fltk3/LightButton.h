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
// "$Id: Fl_Light_Button.H 6614 2009-01-01 16:11:32Z matt $"
//
// Lighted button header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Light_Button widget . */

#ifndef Fl_Light_Button_H
#define Fl_Light_Button_H

#include "Button.h"

/**
  <P>This subclass displays the "on" state by turning on a light, 
  rather than drawing pushed in.  The shape of the  "light" 
  is initially set to FL_DOWN_BOX.  The color of the light when
  on is controlled with selection_color(), which defaults to FL_YELLOW.

  Buttons generate callbacks when they are clicked by the user.  You
  control exactly when and how by changing the values for type() and when().
  <P ALIGN=CENTER>\image html Fl_Light_Button.gif</P> 
  \image latex Fl_Light_Button.eps "Fl_Light_Button" width=4cm
*/
class FL_EXPORT Fl_Light_Button : public Fl_Button {
protected:
    virtual void draw();
public:
    virtual int handle(int);
    Fl_Light_Button(int x,int y,int w,int h,const char *l = 0);
};

#endif

//
// End of "$Id: Fl_Light_Button.H 6614 2009-01-01 16:11:32Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::LightButton
class Fl_Light_Button : public fltk::LightButton {
public:
  Fl_Light_Button(int x, int t, int w, int h, const char *label=0)
  : fltk::LightButton(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Light_Button.H 6614 2009-01-01 16:11:32Z matt $"
//
// Lighted button header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Light_Button widget . */

#ifndef Fl_Light_Button_H
#define Fl_Light_Button_H

#include "Fl_Button.H"

/**
  <P>This subclass displays the "on" state by turning on a light, 
  rather than drawing pushed in.  The shape of the  "light" 
  is initially set to FL_DOWN_BOX.  The color of the light when
  on is controlled with selection_color(), which defaults to FL_YELLOW.

  Buttons generate callbacks when they are clicked by the user.  You
  control exactly when and how by changing the values for type() and when().
  <P ALIGN=CENTER>\image html Fl_Light_Button.gif</P> 
  \image latex Fl_Light_Button.eps "Fl_Light_Button" width=4cm
*/
class FL_EXPORT Fl_Light_Button : public Fl_Button {
protected:
    virtual void draw();
public:
    virtual int handle(int);
    Fl_Light_Button(int x,int y,int w,int h,const char *l = 0);
};

#endif

//
// End of "$Id: Fl_Light_Button.H 6614 2009-01-01 16:11:32Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id: LightButton.h 4886 2006-03-30 09:55:32Z fabien $"
//
// Forms/XForms/Flame style button with indicator light on left
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

#ifndef fltk_Light_Button_h
#define fltk_Light_Button_h

#include "CheckButton.h"

namespace fltk {

class FL_API LightButton : public CheckButton {
public:
  LightButton(int x,int y,int w,int h,const char *l = 0);
  static NamedStyle* default_style;
  static void default_glyph(const Widget*, int, int,int,int,int, Flags);
};

}
#endif

//
// End of "$Id: LightButton.h 4886 2006-03-30 09:55:32Z fabien $".
//
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
