//
// "$Id: FloatInput.h 4886 2006-03-30 09:55:32Z fabien $"
//
// NumericInput modified to only allow floating point to by
// typed. Currently this is implemented by the base class by checking
// type() but this may change in the future.
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

#ifndef fltk2_FloatInput_h
#define fltk2_FloatInput_h

#include <fltk3/FloatInput.h>
#include "NumericInput.h"

namespace fltk {

class FL_API FloatInput : public NumericInput {
public:
  FloatInput() {}
  FloatInput(int x,int y,int w,int h,const char *l = 0) {
    _p = new fltk3::FloatInput(x, y, w, h, l);
    _p->wrapper(this);
  }
  long lvalue() const {
    return strtol(value(), 0, 0);
  }
  int ivalue() const {
    return strtol(value(), 0, 0);
  }
  double fvalue() const {
    return strtod(value(), 0);
  }
  
#if 0 // TODO: FLTK123
  enum { FLOAT = 1, INT = 2 };
#endif // TODO: FLTK123
  
};

}
#endif

//
// End of "$Id: FloatInput.h 4886 2006-03-30 09:55:32Z fabien $".
//
