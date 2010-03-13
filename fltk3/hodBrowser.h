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
// "$Id: Fl_Hold_Browser.H 6614 2009-01-01 16:11:32Z matt $"
//
// Hold browser header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Hold_Browser widget . */

#ifndef Fl_Hold_Browser_H
#define Fl_Hold_Browser_H

#include "Browser.h"

/**
  The Fl_Hold_Browser is a subclass of Fl_Browser
  which lets the user select a single item, or no items by clicking on
  the empty space.  As long as the mouse button is held down the item
  pointed to by it is highlighted, and this highlighting remains on when
  the mouse button is released. Normally the callback is done when the
  user releases the mouse, but you can change this with when().
  <P>See Fl_Browser for methods to add and remove lines from the browser.
*/
class Fl_Hold_Browser : public Fl_Browser {
public:
  /**
    Creates a new Fl_Hold_Browser widget using the given
    position, size, and label string. The default boxtype is FL_DOWN_BOX.
    The constructor specializes Fl_Browser() by setting the type to FL_HOLD_BROWSER.
    The destructor destroys the widget and frees all memory that has been allocated.
 */
  Fl_Hold_Browser(int X,int Y,int W,int H,const char *l=0)
	: Fl_Browser(X,Y,W,H,l) {type(FL_HOLD_BROWSER);}
};

#endif

//
// End of "$Id: Fl_Hold_Browser.H 6614 2009-01-01 16:11:32Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::hodBrowser
class Fl_Hold_Browser : public fltk::hodBrowser {
public:
  Fl_Hold_Browser(int x, int t, int w, int h, const char *label=0)
  : fltk::hodBrowser(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Hold_Browser.H 6614 2009-01-01 16:11:32Z matt $"
//
// Hold browser header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Hold_Browser widget . */

#ifndef Fl_Hold_Browser_H
#define Fl_Hold_Browser_H

#include "Fl_Browser.H"

/**
  The Fl_Hold_Browser is a subclass of Fl_Browser
  which lets the user select a single item, or no items by clicking on
  the empty space.  As long as the mouse button is held down the item
  pointed to by it is highlighted, and this highlighting remains on when
  the mouse button is released. Normally the callback is done when the
  user releases the mouse, but you can change this with when().
  <P>See Fl_Browser for methods to add and remove lines from the browser.
*/
class Fl_Hold_Browser : public Fl_Browser {
public:
  /**
    Creates a new Fl_Hold_Browser widget using the given
    position, size, and label string. The default boxtype is FL_DOWN_BOX.
    The constructor specializes Fl_Browser() by setting the type to FL_HOLD_BROWSER.
    The destructor destroys the widget and frees all memory that has been allocated.
 */
  Fl_Hold_Browser(int X,int Y,int W,int H,const char *l=0)
	: Fl_Browser(X,Y,W,H,l) {type(FL_HOLD_BROWSER);}
};

#endif

//
// End of "$Id: Fl_Hold_Browser.H 6614 2009-01-01 16:11:32Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
