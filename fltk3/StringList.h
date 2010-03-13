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
// This is the Twin Class to fltk::StringList
class Fl_String_List : public fltk::StringList {
public:
  Fl_String_List(int x, int t, int w, int h, const char *label=0)
  : fltk::StringList(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
// "$Id: StringList.h 5709 2007-02-23 01:03:47Z spitzak $"
//
// Copyright 1998-2007 by Bill Spitzak and others.
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

#ifndef fltk_StringList_h
#define fltk_StringList_h

#include "Menu.h"

namespace fltk {

class FL_API StringHierarchy : public List {
  Widget* generated_item_;
public:
  // fltk::List virtual functions:
  virtual Widget* child(const Menu*, const int* indexes, int level);
  // virtual functions to return hierarchy of strings:
  virtual int children(const Menu*, const int* indexes, int level) = 0;
  virtual const char* label(const Menu*, const int* indexes, int level)=0;
  // label() can mess with this item to change flags, font, etc:
  Widget* generated_item() {return generated_item_;}
  StringHierarchy() {generated_item_ = 0;}
  ~StringHierarchy() {delete generated_item_;}
};

class FL_API StringList : public StringHierarchy {
public:
  // overrides of StringHierarchy virtual functions:
  virtual int children(const Menu*, const int* indexes, int level);
  virtual const char* label(const Menu*, const int* indexes, int level);
  // new virtual funcitons:
  virtual int children(const Menu*) = 0;
  virtual const char* label(const Menu*, int index) = 0;
};

class FL_API StringArray : public StringList {
  const char* const * array;
  int children_;
public:
  // overrides of StringList virtual functions:
  virtual int children(const Menu*);
  virtual const char* label(const Menu*, int index);
  // Constructors to use a constant array of strings:
  StringArray(const char*const* a, int n) : array(a), children_(n) {}
  StringArray(const char*const* a) {set(a);}
  StringArray(const char* s) {set(s);}
  StringArray() {children_ = 0;}
  // change the array:
  void set(const char*const* a, int n) {array=a; children_ = n;}
  void set(const char*const* a);
  void set(const char* s); // nul-seperated list
};

}
#endif
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
