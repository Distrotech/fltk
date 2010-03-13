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
// "$Id: Fl_Scrollbar.H 6683 2009-03-14 11:46:43Z engelsman $"
//
// Scroll bar header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Scrollbar widget . */

#ifndef Fl_Scrollbar_H
#define Fl_Scrollbar_H

#include "Slider.h"

/**
  The Fl_Scrollbar widget displays a slider with arrow buttons at
  the ends of the scrollbar. Clicking on the arrows move up/left and
  down/right by linesize(). Scrollbars also accept FL_SHORTCUT events:
  the arrows move by linesize(), and vertical scrollbars take Page
  Up/Down (they move by the page size minus linesize()) and Home/End
  (they jump to the top or bottom).

  Scrollbars have step(1) preset (they always return integers). If
  desired you can set the step() to non-integer values. You will then
  have to use casts to get at the floating-point versions of value()
  from Fl_Slider.

  \image html  scrollbar.gif 
  \image latex scrollbar.eps "Fl_Scrollbar" width=4cm
*/
class FL_EXPORT Fl_Scrollbar : public Fl_Slider {

  int linesize_;
  int pushed_;
  static void timeout_cb(void*);
  void increment_cb();
protected:
  void draw();

public:

  Fl_Scrollbar(int X,int Y,int W,int H, const char *L = 0);
  ~Fl_Scrollbar();
  int handle(int);

  /**
    Gets the integer value (position) of the slider in the scrollbar.
    You can get the floating point value with Fl_Slider::value().

    \see Fl_Scrollbar::value(int p)
    \see Fl_Scrollbar::value(int pos, int size, int first, int total)
  */
  int value() const {return int(Fl_Slider::value());}

  /**
    Sets the value (position) of the slider in the scrollbar.

    \see Fl_Scrollbar::value()
    \see Fl_Scrollbar::value(int pos, int size, int first, int total)
  */
  int value(int p) {return int(Fl_Slider::value((double)p));}

  /**
    Sets the position, size and range of the slider in the scrollbar.
    \param[in] pos   position, first line displayed
    \param[in] size  window size, number of lines displayed
    \param[in] first number of first line
    \param[in] total total number of lines

    You should call this every time your window changes size, your data
    changes size, or your scroll position changes (even if in response
    to a callback from this scrollbar).
    All necessary calls to redraw() are done.

    Calls Fl_Slider::scrollvalue(int pos, int size, int first, int total).
  */
  int value(int pos, int size, int first, int total) {
    return scrollvalue(pos, size, first, total);
  }

  /**
    Get the size of step, in lines, that the arror keys move.
  */
  int linesize() const {return linesize_;}

  /**
    This number controls how big the steps are that the arrow keys do.
    In addition page up/down move by the size last sent to value()
    minus one linesize().  The default is 16.
  */
  void linesize(int i) {linesize_ = i;}

};

#endif

//
// End of "$Id: Fl_Scrollbar.H 6683 2009-03-14 11:46:43Z engelsman $".
//

/* suggested twin class
// This is the Twin Class to fltk::Scrollbar
class Fl_Scrollbar : public fltk::Scrollbar {
public:
  Fl_Scrollbar(int x, int t, int w, int h, const char *label=0)
  : fltk::Scrollbar(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Scrollbar.H 6683 2009-03-14 11:46:43Z engelsman $"
//
// Scroll bar header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Scrollbar widget . */

#ifndef Fl_Scrollbar_H
#define Fl_Scrollbar_H

#include "Fl_Slider.H"

/**
  The Fl_Scrollbar widget displays a slider with arrow buttons at
  the ends of the scrollbar. Clicking on the arrows move up/left and
  down/right by linesize(). Scrollbars also accept FL_SHORTCUT events:
  the arrows move by linesize(), and vertical scrollbars take Page
  Up/Down (they move by the page size minus linesize()) and Home/End
  (they jump to the top or bottom).

  Scrollbars have step(1) preset (they always return integers). If
  desired you can set the step() to non-integer values. You will then
  have to use casts to get at the floating-point versions of value()
  from Fl_Slider.

  \image html  scrollbar.gif 
  \image latex scrollbar.eps "Fl_Scrollbar" width=4cm
*/
class FL_EXPORT Fl_Scrollbar : public Fl_Slider {

  int linesize_;
  int pushed_;
  static void timeout_cb(void*);
  void increment_cb();
protected:
  void draw();

public:

  Fl_Scrollbar(int X,int Y,int W,int H, const char *L = 0);
  ~Fl_Scrollbar();
  int handle(int);

  /**
    Gets the integer value (position) of the slider in the scrollbar.
    You can get the floating point value with Fl_Slider::value().

    \see Fl_Scrollbar::value(int p)
    \see Fl_Scrollbar::value(int pos, int size, int first, int total)
  */
  int value() const {return int(Fl_Slider::value());}

  /**
    Sets the value (position) of the slider in the scrollbar.

    \see Fl_Scrollbar::value()
    \see Fl_Scrollbar::value(int pos, int size, int first, int total)
  */
  int value(int p) {return int(Fl_Slider::value((double)p));}

  /**
    Sets the position, size and range of the slider in the scrollbar.
    \param[in] pos   position, first line displayed
    \param[in] size  window size, number of lines displayed
    \param[in] first number of first line
    \param[in] total total number of lines

    You should call this every time your window changes size, your data
    changes size, or your scroll position changes (even if in response
    to a callback from this scrollbar).
    All necessary calls to redraw() are done.

    Calls Fl_Slider::scrollvalue(int pos, int size, int first, int total).
  */
  int value(int pos, int size, int first, int total) {
    return scrollvalue(pos, size, first, total);
  }

  /**
    Get the size of step, in lines, that the arror keys move.
  */
  int linesize() const {return linesize_;}

  /**
    This number controls how big the steps are that the arrow keys do.
    In addition page up/down move by the size last sent to value()
    minus one linesize().  The default is 16.
  */
  void linesize(int i) {linesize_ = i;}

};

#endif

//
// End of "$Id: Fl_Scrollbar.H 6683 2009-03-14 11:46:43Z engelsman $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id: Scrollbar.h 5956 2007-10-17 19:57:31Z spitzak $"
//
// Scrollbar, controls an integer position of a window of a given
// size inside a data set of a given total size.
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

#ifndef fltk_Scrollbar_h
#define fltk_Scrollbar_h

#include "Slider.h"

namespace fltk {

class FL_API Scrollbar : public Slider {

public:
  Scrollbar(int x,int y,int w,int h, const char *l = 0);
  static NamedStyle* default_style;

  int value() const {return int(Slider::value());}
  bool value(int position) {return Slider::value(position);}
  bool value(int position, int size, int top, int total);
  int handle(int);

  int pagesize() const {return pagesize_;}
  void pagesize(int a) {pagesize_ = a;}

protected:
  void draw();

private:
  int pagesize_;
  static void timeout_cb(void*);
  void increment_cb();

};

}

#endif

//
// End of "$Id: Scrollbar.h 5956 2007-10-17 19:57:31Z spitzak $".
//
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
