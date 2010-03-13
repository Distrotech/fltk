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
// This is the Twin Class to fltk::StyleSet
class Fl_Style_Sheet : public fltk::StyleSet {
public:
  Fl_Style_Sheet(int x, int t, int w, int h, const char *label=0)
  : fltk::StyleSet(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id: StyleSet.h 4886 2006-03-30 09:55:32Z fabien $"
//
// Saves and restores all the styles used by Widget constructors. Fluid
// uses this so you can preview a style without fluid's own control
// panels changing. I think this is broken, anybody want to fix it?
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

#ifndef fltk_StyleSet_h
#define fltk_StyleSet_h

#include "Style.h"

namespace fltk {

class FL_API StyleSet {
  NamedStyle* first_style;
  Theme theme;
  Color background;
  void* reserved; // pointer to extra saved stuff
public:
  StyleSet();
  void make_current();
  ~StyleSet();
};

}

#endif
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
