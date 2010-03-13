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
// "$Id: Fl_Timer.H 6614 2009-01-01 16:11:32Z matt $"
//
// Timer header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Timer widget . */

#ifndef Fl_Timer_H
#define Fl_Timer_H

#ifndef Fl_Widget_H
#include "Widget.h"
#endif

// values for type():
#define FL_NORMAL_TIMER		0
#define FL_VALUE_TIMER		1
#define FL_HIDDEN_TIMER		2

/**
  This is provided only to emulate the Forms Timer widget.  It works by
  making a timeout callback every 1/5 second.  This is wasteful and
  inaccurate if you just want something to happen a fixed time in the
  future.  You should directly call 
  Fl::add_timeout() instead.
*/
class FL_EXPORT Fl_Timer : public Fl_Widget {
  static void stepcb(void *);
  void step();
  char on, direction_;
  double delay, total;
  long lastsec,lastusec;
protected:
  void draw();
public:
  int handle(int);
  Fl_Timer(uchar t,int x,int y,int w,int h, const char *l);
  ~Fl_Timer();
  void value(double);
  /** See void Fl_Timer::value(double)  */
  double value() const {return delay>0.0?delay:0.0;}
  /**
    Gets or sets the direction of the timer.  If the direction is zero
    then the timer will count up, otherwise it will count down from the
    initial value().
  */
  char direction() const {return direction_;}
  /**
    Gets or sets the direction of the timer.  If the direction is zero
    then the timer will count up, otherwise it will count down from the
    initial value().
  */
  void direction(char d) {direction_ = d;}
  /**    Gets or sets whether the timer is suspended.  */
  char suspended() const {return !on;}
  void suspended(char d);
};

#endif

//
// End of "$Id: Fl_Timer.H 6614 2009-01-01 16:11:32Z matt $".
//


/* suggested twin class
// This is the Twin Class to fltk::timer
class Fl_Timer : public fltk::timer {
public:
  Fl_Timer(int x, int t, int w, int h, const char *label=0)
  : fltk::timer(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Timer.H 6614 2009-01-01 16:11:32Z matt $"
//
// Timer header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Timer widget . */

#ifndef Fl_Timer_H
#define Fl_Timer_H

#ifndef Fl_Widget_H
#include "Fl_Widget.H"
#endif

// values for type():
#define FL_NORMAL_TIMER		0
#define FL_VALUE_TIMER		1
#define FL_HIDDEN_TIMER		2

/**
  This is provided only to emulate the Forms Timer widget.  It works by
  making a timeout callback every 1/5 second.  This is wasteful and
  inaccurate if you just want something to happen a fixed time in the
  future.  You should directly call 
  Fl::add_timeout() instead.
*/
class FL_EXPORT Fl_Timer : public Fl_Widget {
  static void stepcb(void *);
  void step();
  char on, direction_;
  double delay, total;
  long lastsec,lastusec;
protected:
  void draw();
public:
  int handle(int);
  Fl_Timer(uchar t,int x,int y,int w,int h, const char *l);
  ~Fl_Timer();
  void value(double);
  /** See void Fl_Timer::value(double)  */
  double value() const {return delay>0.0?delay:0.0;}
  /**
    Gets or sets the direction of the timer.  If the direction is zero
    then the timer will count up, otherwise it will count down from the
    initial value().
  */
  char direction() const {return direction_;}
  /**
    Gets or sets the direction of the timer.  If the direction is zero
    then the timer will count up, otherwise it will count down from the
    initial value().
  */
  void direction(char d) {direction_ = d;}
  /**    Gets or sets whether the timer is suspended.  */
  char suspended() const {return !on;}
  void suspended(char d);
};

#endif

//
// End of "$Id: Fl_Timer.H 6614 2009-01-01 16:11:32Z matt $".
//

#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
