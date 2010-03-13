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


/* suggested twin class
// This is the Twin Class to fltk::AlignGroup
class Fl_Align_Group : public fltk::AlignGroup {
public:
  Fl_Align_Group(int x, int t, int w, int h, const char *label=0)
  : fltk::AlignGroup(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
// Layout header file for the Fast Light Tool Kit (FLTK).
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

#ifndef fltk_AlignGroup_h
#define fltk_AlignGroup_h

#include "Group.h"

namespace fltk {

class FL_API AlignGroup : public Group {
  bool vertical_;
  uchar n_to_break_,dw_,dh_;
  Flags align_;

public:

  void layout();

  // WAS: this should have a begin=false argument added somehow.
  AlignGroup(int X, int Y, int W, int H, const char* L = 0,
	     uchar n_to_break = 0, bool vertical = 1,
	     Flags align = ALIGN_LEFT,
	     uchar dw = 0,uchar dh = 0)
    : Group(X,Y,W,H,L),
      vertical_(vertical), n_to_break_(n_to_break), dw_(dw), dh_(dh),
      align_(align) {}

  bool vertical() const {return vertical_;}
  void vertical(bool v) {vertical_ = v;}

  uchar n_to_break() const {return n_to_break_;}
  void n_to_break(uchar n) {n_to_break_ = n;}

  uchar dw() const {return dw_;}
  void dw(uchar d) {dw_ = d;}
  uchar dh() const {return dh_;}
  void dh(uchar d) {dh_ = d;}

  Flags align() const {return align_;}
  void align(Flags a) {align_ = a;}
};

}

#endif
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
