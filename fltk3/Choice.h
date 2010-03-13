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
// "$Id: Fl_Choice.H 6614 2009-01-01 16:11:32Z matt $"
//
// Choice header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Choice widget . */

#ifndef Fl_Choice_H
#define Fl_Choice_H

#include "Menu_.h"

/**
  \class Fl_Choice
  \brief A button that is used to pop up a menu.

  This is a button that, when pushed, pops up a menu (or hierarchy of menus)
  defined by an array of Fl_Menu_Item objects.
  Motif calls this an OptionButton.

  The only difference between this and a Fl_Menu_Button is that the name of
  the most recent chosen menu item is displayed inside the box, while the
  label is displayed outside the box. However, since the use of this is most
  often to control a single variable rather than do individual callbacks,
  some of the Fl_Menu_Button methods are redescribed here in those terms.

  When the user picks an item off the menu the value() is set to that item
  and then the item's callback is done with the menu_button as the
  \c Fl_Widget* argument. If the item does not have a callback the
  menu_button's callback is done instead.

  All three mouse buttons pop up the menu. The Forms behavior of the first
  two buttons to increment/decrement the choice is not implemented.  This
  could be added with a subclass, however.

  The menu will also pop up in response to shortcuts indicated by putting
  a '\&' character in the label().  See Fl_Button::shortcut(int s) for a
  description of this.

  Typing the shortcut() of any of the items will do exactly the same as when
  you pick the item with the mouse.  The '\&' character in item names are
  only looked at when the menu is popped up, however.

  \image html choice.gif
  \image latex choice.eps  "Fl_Choice" width=4cm
  \todo Refactor the doxygen comments for Fl_Choice changed() documentation.

  \li <tt>int Fl_Widget::changed() const</tt>
      This value is true the user picks a different value. <em>It is turned
      off by value() and just before doing a callback (the callback can turn
      it back on if desired).</em>
  \li <tt>void Fl_Widget::set_changed()</tt>
      This method sets the changed() flag.
  \li <tt>void Fl_Widget::clear_changed()</tt>
      This method clears the changed() flag.
  \li <tt>Fl_Boxtype Fl_Choice::down_box() const</tt>
      Gets the current down box, which is used when the menu is popped up.
      The default down box type is \c FL_DOWN_BOX.
  \li <tt>void Fl_Choice::down_box(Fl_Boxtype b)</tt>
      Sets the current down box type to \p b.
 */
class FL_EXPORT Fl_Choice : public Fl_Menu_ {
protected:
  void draw();
public:
  int handle(int);

  Fl_Choice(int X, int Y, int W, int H, const char *L = 0);

  /**
    Gets the index of the last item chosen by the user.
    The index is zero initially.
   */
  int value() const {return Fl_Menu_::value();}

  int value(int v);

  int value(const Fl_Menu_Item* v);
};

#endif

//
// End of "$Id: Fl_Choice.H 6614 2009-01-01 16:11:32Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::Choice
class Fl_Choice : public fltk::Choice {
public:
  Fl_Choice(int x, int t, int w, int h, const char *label=0)
  : fltk::Choice(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Choice.H 6614 2009-01-01 16:11:32Z matt $"
//
// Choice header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Choice widget . */

#ifndef Fl_Choice_H
#define Fl_Choice_H

#include "Fl_Menu_.H"

/**
  \class Fl_Choice
  \brief A button that is used to pop up a menu.

  This is a button that, when pushed, pops up a menu (or hierarchy of menus)
  defined by an array of Fl_Menu_Item objects.
  Motif calls this an OptionButton.

  The only difference between this and a Fl_Menu_Button is that the name of
  the most recent chosen menu item is displayed inside the box, while the
  label is displayed outside the box. However, since the use of this is most
  often to control a single variable rather than do individual callbacks,
  some of the Fl_Menu_Button methods are redescribed here in those terms.

  When the user picks an item off the menu the value() is set to that item
  and then the item's callback is done with the menu_button as the
  \c Fl_Widget* argument. If the item does not have a callback the
  menu_button's callback is done instead.

  All three mouse buttons pop up the menu. The Forms behavior of the first
  two buttons to increment/decrement the choice is not implemented.  This
  could be added with a subclass, however.

  The menu will also pop up in response to shortcuts indicated by putting
  a '\&' character in the label().  See Fl_Button::shortcut(int s) for a
  description of this.

  Typing the shortcut() of any of the items will do exactly the same as when
  you pick the item with the mouse.  The '\&' character in item names are
  only looked at when the menu is popped up, however.

  \image html choice.gif
  \image latex choice.eps  "Fl_Choice" width=4cm
  \todo Refactor the doxygen comments for Fl_Choice changed() documentation.

  \li <tt>int Fl_Widget::changed() const</tt>
      This value is true the user picks a different value. <em>It is turned
      off by value() and just before doing a callback (the callback can turn
      it back on if desired).</em>
  \li <tt>void Fl_Widget::set_changed()</tt>
      This method sets the changed() flag.
  \li <tt>void Fl_Widget::clear_changed()</tt>
      This method clears the changed() flag.
  \li <tt>Fl_Boxtype Fl_Choice::down_box() const</tt>
      Gets the current down box, which is used when the menu is popped up.
      The default down box type is \c FL_DOWN_BOX.
  \li <tt>void Fl_Choice::down_box(Fl_Boxtype b)</tt>
      Sets the current down box type to \p b.
 */
class FL_EXPORT Fl_Choice : public Fl_Menu_ {
protected:
  void draw();
public:
  int handle(int);

  Fl_Choice(int X, int Y, int W, int H, const char *L = 0);

  /**
    Gets the index of the last item chosen by the user.
    The index is zero initially.
   */
  int value() const {return Fl_Menu_::value();}

  int value(int v);

  int value(const Fl_Menu_Item* v);
};

#endif

//
// End of "$Id: Fl_Choice.H 6614 2009-01-01 16:11:32Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id: Choice.h 4319 2005-05-08 19:18:50Z spitzak $"
//
// Popup list of items that the user can choose one of. Based on Motif
// but modern equivalent is the OS/X popup choices.
//
// This is not a "combo box". You should try this, but if you insist
// on that use the InputBrowser widget.
//
// Copyright 2002 by Bill Spitzak and others.
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

#ifndef fltk_Choice_h
#define fltk_Choice_h

#include "Menu.h"

namespace fltk {

class FL_API Choice : public Menu {
public:
  int handle(int);
  int handle(int, const Rectangle&);
  Choice(int,int,int,int,const char * = 0);
  static NamedStyle* default_style;
  void draw();
};

}

#endif

//
// End of "$Id: Choice.h 4319 2005-05-08 19:18:50Z spitzak $".
//
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
