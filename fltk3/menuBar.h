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
// "$Id: Fl_Menu_Bar.H 6614 2009-01-01 16:11:32Z matt $"
//
// Menu bar header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Menu_Bar widget . */

#ifndef Fl_Menu_Bar_H
#define Fl_Menu_Bar_H

#include "Menu_.h"

/**
  This widget provides a standard menubar interface.  Usually you will
  put this widget along the top edge of your window.  The height of the
  widget should be 30 for the menu titles to draw correctly with the
  default font.
  <P>The items on the bar and the menus they bring up are defined by a
  single Fl_Menu_Item
  array.  Because a Fl_Menu_Item array defines a hierarchy, the
  top level menu defines the items in the menubar, while the submenus
  define the pull-down menus. Sub-sub menus and lower pop up to the right
  of the submenus. </P>
  <P ALIGN=CENTER>\image html  menubar.gif</P>
  \image latex  menubar.eps " menubar" width=12cm
  <P>If there is an item in the top menu that is not a title of a
  submenu, then it acts like a "button" in the menubar.  Clicking on it
  will pick it. </P>
  <P>When the user picks an item off the menu, the item's callback is
  done with the menubar as the Fl_Widget* argument.  If the item
  does not have a callback the menubar's callback is done instead. </P>
  <P>Submenus will also pop up in response to shortcuts indicated by
  putting a '&' character in the name field of the menu item. If you put a
  '&' character in a top-level "button" then the shortcut picks it.  The
  '&' character in submenus is ignored until the menu is popped up. </P>
  <P>Typing the shortcut() of any of the menu items will cause
  callbacks exactly the same as when you pick the item with the mouse.
*/
class FL_EXPORT Fl_Menu_Bar : public Fl_Menu_ {
protected:
    void draw();
public:
    int handle(int);
  /**
      Creates a new Fl_Menu_Bar widget using the given position,
    size, and label string. The default boxtype is FL_UP_BOX.
    <P>The constructor sets menu() to NULL.  See 
    Fl_Menu_ for the methods to set or change the menu. </P>
    <P>labelsize(), labelfont(), and labelcolor()
    are used to control how the menubar items are drawn.  They are
    initialized from the Fl_Menu static variables, but you can
    change them if desired. </P>
    <P>label() is ignored unless you change align() to
    put it outside the menubar.
    <P>The destructor removes the Fl_Menu_Bar widget and all of its
    menu items.
  */
    Fl_Menu_Bar(int X, int Y, int W, int H,const char *l=0)
      : Fl_Menu_(X,Y,W,H,l) {}
};

#endif

//
// End of "$Id: Fl_Menu_Bar.H 6614 2009-01-01 16:11:32Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::MenuBar
class Fl_Menu_Bar : public fltk::MenuBar {
public:
  Fl_Menu_Bar(int x, int t, int w, int h, const char *label=0)
  : fltk::MenuBar(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Menu_Bar.H 6614 2009-01-01 16:11:32Z matt $"
//
// Menu bar header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Menu_Bar widget . */

#ifndef Fl_Menu_Bar_H
#define Fl_Menu_Bar_H

#include "Fl_Menu_.H"

/**
  This widget provides a standard menubar interface.  Usually you will
  put this widget along the top edge of your window.  The height of the
  widget should be 30 for the menu titles to draw correctly with the
  default font.
  <P>The items on the bar and the menus they bring up are defined by a
  single Fl_Menu_Item
  array.  Because a Fl_Menu_Item array defines a hierarchy, the
  top level menu defines the items in the menubar, while the submenus
  define the pull-down menus. Sub-sub menus and lower pop up to the right
  of the submenus. </P>
  <P ALIGN=CENTER>\image html  menubar.gif</P>
  \image latex  menubar.eps " menubar" width=12cm
  <P>If there is an item in the top menu that is not a title of a
  submenu, then it acts like a "button" in the menubar.  Clicking on it
  will pick it. </P>
  <P>When the user picks an item off the menu, the item's callback is
  done with the menubar as the Fl_Widget* argument.  If the item
  does not have a callback the menubar's callback is done instead. </P>
  <P>Submenus will also pop up in response to shortcuts indicated by
  putting a '&' character in the name field of the menu item. If you put a
  '&' character in a top-level "button" then the shortcut picks it.  The
  '&' character in submenus is ignored until the menu is popped up. </P>
  <P>Typing the shortcut() of any of the menu items will cause
  callbacks exactly the same as when you pick the item with the mouse.
*/
class FL_EXPORT Fl_Menu_Bar : public Fl_Menu_ {
protected:
    void draw();
public:
    int handle(int);
  /**
      Creates a new Fl_Menu_Bar widget using the given position,
    size, and label string. The default boxtype is FL_UP_BOX.
    <P>The constructor sets menu() to NULL.  See 
    Fl_Menu_ for the methods to set or change the menu. </P>
    <P>labelsize(), labelfont(), and labelcolor()
    are used to control how the menubar items are drawn.  They are
    initialized from the Fl_Menu static variables, but you can
    change them if desired. </P>
    <P>label() is ignored unless you change align() to
    put it outside the menubar.
    <P>The destructor removes the Fl_Menu_Bar widget and all of its
    menu items.
  */
    Fl_Menu_Bar(int X, int Y, int W, int H,const char *l=0)
      : Fl_Menu_(X,Y,W,H,l) {}
};

#endif

//
// End of "$Id: Fl_Menu_Bar.H 6614 2009-01-01 16:11:32Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id: MenuBar.h 4886 2006-03-30 09:55:32Z fabien $"
//
// Menu bar, each submenu is a pull-down menu. Any items act like
// a button in the menu bar.
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

#ifndef fltk_MenuBar_h
#define fltk_MenuBar_h

#include "Menu.h"

namespace fltk {

class FL_API MenuBar : public Menu {
public:
  MenuBar(int x,int y,int w,int h,const char *l=0);
  static NamedStyle* default_style;
  int handle(int);
protected:
  void draw();
private:
  int highlight_, last_;
  Widget *lastfocus_;
};

}
#endif

//
// End of "$Id: MenuBar.h 4886 2006-03-30 09:55:32Z fabien $".
//
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
