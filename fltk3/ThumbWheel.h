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
// "$Id: Fl_Roller.H 6614 2009-01-01 16:11:32Z matt $"
//
// Roller header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Roller widget . */

#ifndef Fl_Roller_H
#define Fl_Roller_H

#ifndef Fl_Valuator_H
#include "Valuator.h"
#endif

/**
  The Fl_Roller widget is a "dolly" control commonly used to
  move 3D objects.
  <P ALIGN=CENTER>\image html Fl_Roller.gif 
  \image latex Fl_Roller.eps "Fl_Roller" width=4cm
*/
class FL_EXPORT Fl_Roller : public Fl_Valuator {
protected:
  void draw();
public:
  int handle(int);
  Fl_Roller(int X,int Y,int W,int H,const char* L=0);
};

#endif

//
// End of "$Id: Fl_Roller.H 6614 2009-01-01 16:11:32Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::ThumbWheel
class Fl_Roller : public fltk::ThumbWheel {
public:
  Fl_Roller(int x, int t, int w, int h, const char *label=0)
  : fltk::ThumbWheel(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Roller.H 6614 2009-01-01 16:11:32Z matt $"
//
// Roller header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Roller widget . */

#ifndef Fl_Roller_H
#define Fl_Roller_H

#ifndef Fl_Valuator_H
#include "Fl_Valuator.H"
#endif

/**
  The Fl_Roller widget is a "dolly" control commonly used to
  move 3D objects.
  <P ALIGN=CENTER>\image html Fl_Roller.gif 
  \image latex Fl_Roller.eps "Fl_Roller" width=4cm
*/
class FL_EXPORT Fl_Roller : public Fl_Valuator {
protected:
  void draw();
public:
  int handle(int);
  Fl_Roller(int X,int Y,int W,int H,const char* L=0);
};

#endif

//
// End of "$Id: Fl_Roller.H 6614 2009-01-01 16:11:32Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id: ThumbWheel.h 4886 2006-03-30 09:55:32Z fabien $"
//
// Inventor-style thumbwheel control for a single floating point value.
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

#ifndef fltk_ThumbWheel_h
#define fltk_ThumbWheel_h

#ifndef fltk_Valuator_h
#include "Valuator.h"
#endif

namespace fltk {

class FL_API ThumbWheel : public Valuator {
public:
#ifdef FLTK_1_SLIDER
  // for back-compatability only
  enum {HORIZONTAL = 1};
#endif
  int handle(int);
  ThumbWheel(int X,int Y,int W,int H,const char* L=0);

protected:
  void draw();
};

}

#endif

//
// End of "$Id: ThumbWheel.h 4886 2006-03-30 09:55:32Z fabien $".
//
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
