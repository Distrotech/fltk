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
// "$Id: Fl_Sys_Menu_Bar.H 6975 2009-12-21 18:43:13Z matt $"
//
// MacOS system menu bar header file for the Fast Light Tool Kit (FLTK).
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

#ifndef Fl_Sys_Menu_Bar_H
#define Fl_Sys_Menu_Bar_H

#include "menuBar.h"
#include "x.h"

#ifdef __APPLE__

class FL_EXPORT Fl_Sys_Menu_Bar : public Fl_Menu_Bar {
protected:
  void draw();
public:
  Fl_Sys_Menu_Bar(int x,int y,int w,int h,const char *l=0)
      : Fl_Menu_Bar(x,y,w,h,l) {
    deactivate();			// don't let the old area take events
    fl_sys_menu_bar = this;
  }
  void menu(const Fl_Menu_Item *m);
#ifdef __APPLE_COCOA__
  int add(const char* label, int shortcut, Fl_Callback*, void *user_data=0, int flags=0);
  void remove(int n);
  void replace(int rank, const char *name);
  enum menuOrItemOperation { itemAtIndex, setKeyEquivalent, setKeyEquivalentModifierMask, setState, initWithTitle,
    numberOfItems, setSubmenu, setEnabled, addSeparatorItem, setTitle, removeItem, addNewItem, renameItem };
  // function doMenuOrItemOperation is in file Fl_cocoa.mm because it contains objective-c code
  static void *doMenuOrItemOperation( menuOrItemOperation operation, ...);
#endif
};

#else

typedef Fl_Menu_Bar Fl_Sys_Menu_Bar;

#endif

#endif

//
// End of "$Id: Fl_Sys_Menu_Bar.H 6975 2009-12-21 18:43:13Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::SystemMenuBar
class Fl_Sys_Menu_Bar : public fltk::SystemMenuBar {
public:
  Fl_Sys_Menu_Bar(int x, int t, int w, int h, const char *label=0)
  : fltk::SystemMenuBar(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Sys_Menu_Bar.H 6975 2009-12-21 18:43:13Z matt $"
//
// MacOS system menu bar header file for the Fast Light Tool Kit (FLTK).
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

#ifndef Fl_Sys_Menu_Bar_H
#define Fl_Sys_Menu_Bar_H

#include "Fl_Menu_Bar.H"
#include "x.H"

#ifdef __APPLE__

class FL_EXPORT Fl_Sys_Menu_Bar : public Fl_Menu_Bar {
protected:
  void draw();
public:
  Fl_Sys_Menu_Bar(int x,int y,int w,int h,const char *l=0)
      : Fl_Menu_Bar(x,y,w,h,l) {
    deactivate();			// don't let the old area take events
    fl_sys_menu_bar = this;
  }
  void menu(const Fl_Menu_Item *m);
#ifdef __APPLE_COCOA__
  int add(const char* label, int shortcut, Fl_Callback*, void *user_data=0, int flags=0);
  void remove(int n);
  void replace(int rank, const char *name);
  enum menuOrItemOperation { itemAtIndex, setKeyEquivalent, setKeyEquivalentModifierMask, setState, initWithTitle,
    numberOfItems, setSubmenu, setEnabled, addSeparatorItem, setTitle, removeItem, addNewItem, renameItem };
  // function doMenuOrItemOperation is in file Fl_cocoa.mm because it contains objective-c code
  static void *doMenuOrItemOperation( menuOrItemOperation operation, ...);
#endif
};

#else

typedef Fl_Menu_Bar Fl_Sys_Menu_Bar;

#endif

#endif

//
// End of "$Id: Fl_Sys_Menu_Bar.H 6975 2009-12-21 18:43:13Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id:$"
//
// MacOS system menu bar header file for the Fast Light Tool Kit (FLTK2).
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
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//

#ifndef fltk_SystemMenuBar_h
#define fltk_SystemMenuBar_h 

#include "MenuBar.h"

struct Fl_Menu_Item;

namespace fltk {

#ifdef __APPLE__

class FL_API SystemMenuBar : public MenuBar {
protected:
  void draw();
public:
  SystemMenuBar(int x,int y,int w,int h,const char *l=0)
      : MenuBar(x,y,w,h,l) {
	   deactivate();			// don't let the old area take events
	  }
  void layout();
};

#else

typedef MenuBar SystemMenuBar;

#endif

}

#endif

//
// End of "$Id:$".
//
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
