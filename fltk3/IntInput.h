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
// "$Id: Fl_Int_Input.H 6614 2009-01-01 16:11:32Z matt $"
//
// Integer input header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Int_Input widget . */

#ifndef Fl_Int_Input_H
#define Fl_Int_Input_H

#include "Input.h"

/**
  The Fl_Int_Input class is a subclass of Fl_Input
  that only allows the user to type decimal digits (or hex numbers of the form 0xaef).
*/
class Fl_Int_Input : public Fl_Input {
public:
  /**
    Creates a new Fl_Int_Input widget using the given position,
    size, and label string. The default boxtype is FL_DOWN_BOX.
    <P>Inherited destructor Destroys the widget and any value associated with it.
  */
  Fl_Int_Input(int X,int Y,int W,int H,const char *l = 0)
      : Fl_Input(X,Y,W,H,l) {type(FL_INT_INPUT);}
};

#endif

//
// End of "$Id: Fl_Int_Input.H 6614 2009-01-01 16:11:32Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::IntInput
class Fl_Int_Input : public fltk::IntInput {
public:
  Fl_Int_Input(int x, int t, int w, int h, const char *label=0)
  : fltk::IntInput(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Int_Input.H 6614 2009-01-01 16:11:32Z matt $"
//
// Integer input header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Int_Input widget . */

#ifndef Fl_Int_Input_H
#define Fl_Int_Input_H

#include "Fl_Input.H"

/**
  The Fl_Int_Input class is a subclass of Fl_Input
  that only allows the user to type decimal digits (or hex numbers of the form 0xaef).
*/
class Fl_Int_Input : public Fl_Input {
public:
  /**
    Creates a new Fl_Int_Input widget using the given position,
    size, and label string. The default boxtype is FL_DOWN_BOX.
    <P>Inherited destructor Destroys the widget and any value associated with it.
  */
  Fl_Int_Input(int X,int Y,int W,int H,const char *l = 0)
      : Fl_Input(X,Y,W,H,l) {type(FL_INT_INPUT);}
};

#endif

//
// End of "$Id: Fl_Int_Input.H 6614 2009-01-01 16:11:32Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id: IntInput.h 4886 2006-03-30 09:55:32Z fabien $"
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

#ifndef fltk_IntInput_h
#define fltk_IntInput_h

#include "FloatInput.h"

namespace fltk {

class FL_API IntInput : public FloatInput {
public:
  IntInput(int x,int y,int w,int h,const char *l = 0)
    : FloatInput(x,y,w,h,l) { type(INT); }
};

}
#endif

//
// End of "$Id: IntInput.h 4886 2006-03-30 09:55:32Z fabien $".
//
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
