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
// This is the Twin Class to fltk::BarGroup
class Fl_Bar_Group : public fltk::BarGroup {
public:
  Fl_Bar_Group(int x, int t, int w, int h, const char *label=0)
  : fltk::BarGroup(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id: BarGroup.h 5575 2007-01-02 17:31:40Z spitzak $"
//
// The BarGroup is a closable strip that can be put in the edges of a Pack,
// usually it contains toolbars or buttons.
//
// Copyright 2002-2006  by Bill Spitzak and others.
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

#ifndef fltk_BarGroup_h
#define fltk_BarGroup_h

#include "Group.h"

namespace fltk {

class FL_API BarGroup : public Group {
  bool open_;
  bool highlighted;
  bool pushed;
  int glyph_size_;
  int saved_size;
  void glyph_box(Rectangle&) const;
public:
  BarGroup(int x,int y,int w ,int h,const char *l = 0,bool begin=false);
  static NamedStyle* default_style;
  void layout();
  int handle(int);
  void draw();
  bool opened() const {return open_;}
  bool opened(bool);
  bool open() {return opened(true);}
  bool close() {return opened(false);}
  int glyph_size() const {return glyph_size_;}
  void glyph_size(int v) {glyph_size_ = v;}
};

}
#endif

//
// End of "$Id: BarGroup.h 5575 2007-01-02 17:31:40Z spitzak $".
//
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
