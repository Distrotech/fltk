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
// "$Id: Fl_Menu_Button.H 6614 2009-01-01 16:11:32Z matt $"
//
// Menu button header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Menu_Button widget . */

#ifndef Fl_Menu_Button_H
#define Fl_Menu_Button_H

#include "Menu_.h"

/**
  This is a button that when pushed pops up a menu (or hierarchy of
  menus) defined by an array of 
  Fl_Menu_Item objects.
  <P ALIGN=CENTER>\image html  menu_button.gif</P>
  \image latex  menu_button.eps " menu_button" width=5cm
  <P>Normally any mouse button will pop up a menu and it is lined up
  below the button as shown in the picture.  However an Fl_Menu_Button
  may also control a pop-up menu.  This is done by setting the type()
  , see below. </P>
  <P>The menu will also pop up in response to shortcuts indicated by
  putting a '&' character in the label(). </P>
  <P>Typing the shortcut() of any of the menu items will cause
  callbacks exactly the same as when you pick the item with the mouse.
  The '&' character in menu item names are only looked at when the menu is
  popped up, however. </P>
  <P>When the user picks an item off the menu, the item's callback is
  done with the menu_button as the Fl_Widget* argument.  If the
  item does not have a callback the menu_button's callback is done
  instead.
*/
class FL_EXPORT Fl_Menu_Button : public Fl_Menu_ {
protected:
  void draw();
public:
  // values for type:
  enum {POPUP1 = 1, POPUP2, POPUP12, POPUP3, POPUP13, POPUP23, POPUP123};
  int handle(int);
  const Fl_Menu_Item* popup();
  Fl_Menu_Button(int,int,int,int,const char * =0);
};

#endif

//
// End of "$Id: Fl_Menu_Button.H 6614 2009-01-01 16:11:32Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::menuButton
class Fl_Menu_Button : public fltk::menuButton {
public:
  Fl_Menu_Button(int x, int t, int w, int h, const char *label=0)
  : fltk::menuButton(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Menu_Button.H 6614 2009-01-01 16:11:32Z matt $"
//
// Menu button header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Menu_Button widget . */

#ifndef Fl_Menu_Button_H
#define Fl_Menu_Button_H

#include "Fl_Menu_.H"

/**
  This is a button that when pushed pops up a menu (or hierarchy of
  menus) defined by an array of 
  Fl_Menu_Item objects.
  <P ALIGN=CENTER>\image html  menu_button.gif</P>
  \image latex  menu_button.eps " menu_button" width=5cm
  <P>Normally any mouse button will pop up a menu and it is lined up
  below the button as shown in the picture.  However an Fl_Menu_Button
  may also control a pop-up menu.  This is done by setting the type()
  , see below. </P>
  <P>The menu will also pop up in response to shortcuts indicated by
  putting a '&' character in the label(). </P>
  <P>Typing the shortcut() of any of the menu items will cause
  callbacks exactly the same as when you pick the item with the mouse.
  The '&' character in menu item names are only looked at when the menu is
  popped up, however. </P>
  <P>When the user picks an item off the menu, the item's callback is
  done with the menu_button as the Fl_Widget* argument.  If the
  item does not have a callback the menu_button's callback is done
  instead.
*/
class FL_EXPORT Fl_Menu_Button : public Fl_Menu_ {
protected:
  void draw();
public:
  // values for type:
  enum {POPUP1 = 1, POPUP2, POPUP12, POPUP3, POPUP13, POPUP23, POPUP123};
  int handle(int);
  const Fl_Menu_Item* popup();
  Fl_Menu_Button(int,int,int,int,const char * =0);
};

#endif

//
// End of "$Id: Fl_Menu_Button.H 6614 2009-01-01 16:11:32Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
