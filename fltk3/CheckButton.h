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
// "$Id: Fl_Check_Button.H 6614 2009-01-01 16:11:32Z matt $"
//
// Check button header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Check_Button widget . */

#ifndef Fl_Check_Button_H
#define Fl_Check_Button_H

#include "LightButton.h"

/**
  \class Fl_Check_Button
  \brief A button with an "checkmark" to show its status.

  \image html Fl_Check_Button.gif
  \image latex Fl_Check_Button.eps  "Fl_Check_Button" width=4cm
  Buttons generate callbacks when they are clicked by the user. You control
  exactly when and how by changing the values for type() and when().

  The Fl_Check_Button subclass displays its "ON" state by showing a "checkmark"
  rather than drawing itself pushed in.
  
  \todo Refactor Fl_Check_Button doxygen comments (add color() info etc?)
  \todo Generate Fl_Check_Button.gif with visible checkmark.
 */
class FL_EXPORT Fl_Check_Button : public Fl_Light_Button {
public:
  Fl_Check_Button(int X, int Y, int W, int H, const char *L = 0);
};

#endif

//
// End of "$Id: Fl_Check_Button.H 6614 2009-01-01 16:11:32Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::CheckButton
class Fl_Check_Button : public fltk::CheckButton {
public:
  Fl_Check_Button(int x, int t, int w, int h, const char *label=0)
  : fltk::CheckButton(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Check_Button.H 6614 2009-01-01 16:11:32Z matt $"
//
// Check button header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Check_Button widget . */

#ifndef Fl_Check_Button_H
#define Fl_Check_Button_H

#include "Fl_Light_Button.H"

/**
  \class Fl_Check_Button
  \brief A button with an "checkmark" to show its status.

  \image html Fl_Check_Button.gif
  \image latex Fl_Check_Button.eps  "Fl_Check_Button" width=4cm
  Buttons generate callbacks when they are clicked by the user. You control
  exactly when and how by changing the values for type() and when().

  The Fl_Check_Button subclass displays its "ON" state by showing a "checkmark"
  rather than drawing itself pushed in.
  
  \todo Refactor Fl_Check_Button doxygen comments (add color() info etc?)
  \todo Generate Fl_Check_Button.gif with visible checkmark.
 */
class FL_EXPORT Fl_Check_Button : public Fl_Light_Button {
public:
  Fl_Check_Button(int X, int Y, int W, int H, const char *L = 0);
};

#endif

//
// End of "$Id: Fl_Check_Button.H 6614 2009-01-01 16:11:32Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id: CheckButton.h 4910 2006-04-06 19:26:22Z fabien $"
//
// Button with a checkmark to the left of it.
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

#ifndef fltk_CheckButton_h
#define fltk_CheckButton_h

#include "Button.h"

namespace fltk {

class FL_API CheckButton : public Button {
public:
  CheckButton(int x,int y,int w,int h,const char *l = 0);
  static NamedStyle* default_style;

  virtual void draw();
};

}

#endif

//
// End of "$Id: CheckButton.h 4910 2006-04-06 19:26:22Z fabien $".
//
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
