//
// "$Id$"
//
// Dial header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2005 by Bill Spitzak and others.
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

/** \file
 * Fl_Dial widget definitions for the Fast Light Tool Kit (FLTK).
 */

#ifndef Fl_Dial_H
#define Fl_Dial_H

#ifndef Fl_Valuator_H
#include "Fl_Valuator.H"
#endif

// values for type():
/// Draws a normal dial with a knob.
#define FL_NORMAL_DIAL	0
/// Draws a dial with a line. 
#define FL_LINE_DIAL	1
/// Draws a dial with a filled arc.
#define FL_FILL_DIAL	2

/**
 * The <TT>Fl_Dial</TT> widget provides a circular dial to control a
 * single floating point value.
 * \image html "dial.gif"
 */
class FL_EXPORT Fl_Dial : public Fl_Valuator {

  short a1,a2;

protected:

  // these allow subclasses to put the dial in a smaller area:
  void draw(int, int, int, int);
  int handle(int, int, int, int, int);
  void draw();

public:

  int handle(int);
 
  /**
   * Creates a new <TT>Fl_Dial</TT> widget.
   *
   * Creates a <TT>Fl_Dial</TT> widget using the given position, size,
   * and label string. The default type is <TT>FL_NORMAL_DIAL</TT>.
   *
   * \param[in] x, y, w, h position and size of the Dial
   * \param[in] label widget label, default is no label
   */
  Fl_Dial(int x,int y,int w,int h, const char *label = 0);

  /**
   * Get the angle used for the minimum value. 
   * The default minimum value is 45 degrees.
   *
   * \see angle1(short)
   */
  short angle1() const {return a1;}

  /**
   * Set the angle used for the minimum value. 
   * The default minimum value is 45 degrees.
   * 0 degrees is straight down and the angles progress clockwise.
   * Normally angle1 is less than angle2, but if you reverse them the 
   * dial moves counter-clockwise.
   *
   * \param[in] a minimum angle in degrees
   *
   * \see angle2(short), angle1(), angles(short, short)
   */
  void angle1(short a) {a1 = a;}

  /**
   * Get the angle used for the maximum value. 
   * The default maximum value is 45 degrees.
   *
   * \see angle2(short)
   */
  short angle2() const {return a2;}

  /**
   * Set the angle used for the maximum value. 
   * The default maximum value is 315 degrees.
   * 0 degrees is straight down and the angles progress clockwise.
   * Normally angle1 is less than angle2, but if you reverse them the 
   * dial moves counter-clockwise.
   *
   * \param[in] a maximum angle in degrees
   *
   * \see angle1(short), angle2(), angles(short, short)
   */
  void angle2(short a) {a2 = a;}

  /**
   * Set the minimum and maximum angle.
   * The default values are 45 and 315 degrees.
   * 0 degrees is straight down and the angles progress clockwise.
   * Normally angle1 is less than angle2, but if you reverse them the 
   * dial moves counter-clockwise.
   *
   * \param[in] a minimum angle in degrees
   * \param[in] b maximum angle in degrees
   *
   * \see angle1(short), angle2(short)
   */
  void angles(short a, short b) {a1 = a; a2 = b;}

};

#endif

//
// End of "$Id$".
//
