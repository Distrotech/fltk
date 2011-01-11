//
// "$Id: NumericInput.h 4886 2006-03-30 09:55:32Z fabien $"
//
// One-line text input field, which handles up/down arrows to
// change the digit to the right of the cursor. This still allows
// arbitrary text such as a math expression to be typed, if you
// want to restrict the user to a number use FloatInput or IntInput.
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

#ifndef fltk2_NumericInput_h
#define fltk2_NumericInput_h

#include <fltk3/NumericInput.h>
#include "Input.h"
#include <math.h>

namespace fltk {

class FL_API NumericInput : public Input {
  
public:
  NumericInput() {}
  NumericInput(int x,int y, int w,int h,const char* l = 0) {
    _p = new fltk3::NumericInput(x, y, w, h, l);
    _p->wrapper(this);
  }
  const char *value() const {
    return Input::value();
  }
  void value(int v) {
    char buf[100];
    sprintf(buf, "%d", v);
    Input::value(buf);
  }
  void value(double A) {
    char buf[32];
    if (int(A)==A) {
      snprintf(buf, 32, "%d", int(A));
    } else {
      int n = (int)ceil(log10(fabs(A)));
      if (n>0 || n<-6) {
        snprintf(buf, 32, "%g", A);
      } else {
        snprintf(buf, 32, "%.7f", A);
        char *s = buf; while (*s) s++; s--;
        while (s>buf && *s=='0') s--;
        if (*s=='.') s--;
        s[1] = 0;
      }
    }
    Input::value(buf);
  }
  
#if 0 // TODO: FLTK123
 protected:
  int handle_arrow(int);
  int handle(int);
#endif // TODO: FLTK123
  
};

}
#endif

//
// End of "$Id: NumericInput.h 4886 2006-03-30 09:55:32Z fabien $"
//
