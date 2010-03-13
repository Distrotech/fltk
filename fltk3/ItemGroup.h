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
// This is the Twin Class to fltk::ItemGroup
class Fl_Item_Group : public fltk::ItemGroup {
public:
  Fl_Item_Group(int x, int t, int w, int h, const char *label=0)
  : fltk::ItemGroup(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id: ItemGroup.h 5575 2007-01-02 17:31:40Z spitzak $"
//
// Widget designed to be a nested list in a menu or browser. This
// copies the drawing and style code from Item. I did not modify the
// base Menu class this way because the style inheritance would mess
// up the styles of MenuButton and MenuBar. Code is in Item.cxx
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

#ifndef fltk_ItemGroup_h
#define fltk_ItemGroup_h

#include "Menu.h"

namespace fltk {

class FL_API ItemGroup : public Menu {
public:
  void draw();
  void layout();
  int handle(int);
  ItemGroup(const char* label = 0, bool begin=false);
  ItemGroup(const char* label, const Symbol*, bool begin=false);
};

/** \class MenuSection
  This class will elegantly facilitate dynamic (& hand-made) menu code writing
  by creating and calling begin() on an ItemGroup in the constructor and
  calling end() in the destructor:
  \code
  mymenu->begin();
  new Item("in main menu");
  {MenuSection g("submenu title");
    new Item("in submenu");
    new Item("also in submenu");
  } // destructor ends the submenu
  \endcode
*/
class FL_API MenuSection {
  ItemGroup* group_;
public:
  //! build a typical submenu group section, then call begin()
  MenuSection(const char* label = 0) { group_ = new ItemGroup(label,true); }

  MenuSection(const char* label, const Symbol* i) { group_ = new ItemGroup(label,i,true); }

  //! call end() at destruction
  ~MenuSection() {group_->end();}

  //! The ItemGroup created by this.
  ItemGroup* group() const {return group_;}
};

}

#endif
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
