//
// "$Id$"
//
// Integer input header file for the Fast Light Tool Kit (FLTK).
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
   fltk3::IntInput widget . */

#ifndef FLTK3_Int_Input_H
#define FLTK3_Int_Input_H

#include "NumericInput.H"

namespace fltk3 {
  class IntInput;
}

/**
  The fltk3::IntInput class is a subclass of fltk3::Input
  that only allows the user to type decimal digits (or hex numbers of the form 0xaef).
*/
class FL_EXPORT fltk3::IntInput : public fltk3::NumericInput {
public:
  /**
    Creates a new fltk3::IntInput widget using the given position,
    size, and label string. The default boxtype is fltk3::DOWN_BOX.
    <P>Inherited destructor Destroys the widget and any value associated with it.
  */
  IntInput(int X,int Y,int W,int H,const char *l = 0)
      : NumericInput(X,Y,W,H,l) {type(FL_INT_INPUT);}
};

#endif

//
// End of "$Id$".
//
