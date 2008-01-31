//
// "$Id$"
//
// Valuator header file for the Fast Light Tool Kit (FLTK).
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
 * Fl_Valuator widget definitions for the Fast Light Tool Kit (FLTK).
 */

#ifndef Fl_Valuator_H
#define Fl_Valuator_H

#ifndef Fl_Widget_H
#include "Fl_Widget.H"
#endif

// shared type() values for classes that work in both directions:
#define FL_VERTICAL		0
#define FL_HORIZONTAL		1

/**
 * The <TT>Fl_Valuator</TT> class controls a single floating-point value.
 *
 * This class controls a single floating-point value
 * and provides a consistent interface to set the value, range, and step,
 * and insures that callbacks are done the same for every object.
 * 
 * There are probably more of these classes in FLTK than any others:
 * 
 * \image html valuators.gif
 * 
 * In the above diagram each box surrounds an actual subclass.  These
 * are further differentiated by setting the <TT> type()</TT></A> 
 * of the widget to the symbolic value labeling the
 * widget.  The ones labelled &quot;0&quot; are the default versions with a <TT>
 * type(0)</TT>.  For consistency the symbol <TT>FL_VERTICAL</TT> is
 * defined as zero.
 */
class FL_EXPORT Fl_Valuator : public Fl_Widget {

  double value_;
  double previous_value_;
  double min, max; // truncates to this range *after* rounding
  double A; int B; // rounds to multiples of A/B, or no rounding if A is zero

protected:

  int horizontal() const {return type()&1;}

  /**
   * Creates a new <TT>Fl_Valuator</TT> widget.
   * 
   * The constructor creates a new widget using the given position,
   * size, and label string. The default boxtype is <TT>FL_NO_BOX</TT>.
   *
   * \param[in] x, y, w, h position and size of the Widget
   * \param[in] label widget label, default is no label
   */
  Fl_Valuator(int X, int Y, int W, int H, const char* L);

  double previous_value() const {return previous_value_;}
  void handle_push() {previous_value_ = value_;}
  double softclamp(double);
  void handle_drag(double newvalue);
  void handle_release(); // use drag() value
  virtual void value_damage(); // cause damage() due to value() changing
  void set_value(double v) {value_ = v;}

public:

  /**
   * Sets the minimum and maximum values for the valuator widget.
   *
   * <tt>bounds(double, double)</tt> is the same as <tt>range(double, double)</tt>.
   *
   * \param[in] a minimum value
   * \param[in] b maximum value
   * \see minimum(), maximum(), minimum(double), maximum(double)
   * \see range(double, double)
   */
  void bounds(double a, double b) {min=a; max=b;}

  /**
   * Gets the minimum value for the valuator.
   *
   * \return minimum value
   * \see minimum(double), maximum()
   */
  double minimum() const {return min;}

  /**
   * Sets the minimum value for the valuator.
   *
   * \param[in] a minimum value
   * \see minimum(), maximum(double)
   */
  void minimum(double a) {min = a;}

  /**
   * Gets the maximum value for the valuator.
   *
   * \return maximum value
   * \see maximum(double), minimum()
   */
  double maximum() const {return max;}

  /**
   * Sets the maximum value for the valuator.
   *
   * \param[in] a maximum value
   * \see maximum(), minimum(double)
   */
  void maximum(double a) {max = a;}

  /**
   * Sets the minimum and maximum values for the valuator. 
   * 
   * When the user manipulates the widget, the value is limited to this
   * range. This clamping is done <I>after</I> rounding to the step
   * value (this makes a difference if the range is not a multiple of
   * the step).
   *
   * The minimum may be greater than the maximum. This has the
   * effect of &quot;reversing&quot; the object so the larger values
   * are in the opposite direction. This also switches which end of
   * the filled sliders is filled.
   * 
   * Some widgets consider this a &quot;soft&quot; range.  This
   * means they will stop at the range, but if the user releases and
   * grabs the control again and tries to move it further, it is
   * allowed.
   * 
   * The range may affect the display. You must <TT>redraw()</TT>
   * the widget after changing the range.
   *
   * \param[in] min minimum value
   * \param[in] max maximum value
   * \see minimum(), maximum(), minimum(double), maximum(double)
   * \see bounds(double, double)
   */
  void range(double a, double b) {min = a; max = b;}

  /**
   * Sets the step value. 
   *
   * \param[in] a ratio as an integer
   * \see step(double), step(double, int)
   */
  void step(int a) {A = a; B = 1;}

  /**
   * Sets the step value. 
   *
   * As the user moves the mouse the
   * value is rounded to the nearest multiple of the step value. This
   * is done <I>before</I> clamping it to the range. For most widgets
   * the default step is zero.
   * 
   * For precision the step is stored as the ratio of two
   * integers, <i>a/b</i>. You can set these integers directly. Currently
   * setting a floating point value sets the nearest <i>a/1</i> or <i>1/b</i> value
   * possible.
   *
   * \param[in] a, b ratio as a fraction
   * \see step(double), step(int)
   */
  void step(double a, int b) {A = a; B = b;}

  /**
   * Sets the step value. 
   *
   * \param[in] a ratio as a floating point number
   * \see step(int), step(double, int)
   */
  void step(double s);

  /**
   * Gets the step value.
   * 
   * \return step value as a floating point number
   */
  double step() const {return A/B;}

  /**
   * Sets the step value to 1/10<SUP>digits</SUP>.
   *
   * \param[in] digits new precision
   */
  void precision(int digits);

  /** 
   * Gets the current value.
   *
   * \return current value
   */
  double value() const {return value_;}
  
  /**
   * Gets or sets the current value. 
   *
   * The new value is <I>not</I>
   * clamped or otherwise changed before storing it. Use
   * <TT>clamp()</TT> or <TT>round()</TT> to modify the value before
   * calling <TT>value()</TT>. The widget is redrawn if the new value
   * is different than the current one. The initial value is zero.
   *
   * \param[in] v new value
   * \return 1 if the value changed, 0 otherwise
   */
  int value(double v);

  /**
   * Format the fields numerical value into a string.
   * 
   * Uses internal rules to format the fields numerical value into
   * the character array pointed to by the passed parameter.
   *
   * The actual format used depends on the current step value. If
   * the step value has been set to zero then a %g format is used.
   * If the step value is non-zero, then a %.*f format is used,
   * where the precision is calculated to show sufficient digits
   * for the current step value. An integer step value, such as 1
   * or 1.0, gives a precision of 0, so the formatted value will
   * appear as an integer.
   *
   * This method is used by the <TT>Fl_Value_...</TT> group of widgets to
   * format the current value into a text string.
   * The return value is the length of the formatted text.
   * The formatted value is written into in <i>buffer</i>.
   * <i>buffer</i> should have space for at least 128 bytes.
   * 
   * You may override this function to create your own text formatting.
   *
   * \param[out] buffer pointer to a 128 byte buffer that will
   *             contain the formatted value
   * \return length of the formatted text
   */
  virtual int format(char *buffer);

  /**
   * Round the passed value to the nearest step increment.  
   * 
   * Does nothing if step is zero.
   *
   * \param[in] v value
   * \return rounded value
   */
  double round(double); // round to nearest multiple of step
  
  /**
   * Clamps the passed value to the valuator range.
   *
   * \param[in] v value
   * \return clamped value
   */
  double clamp(double v); // keep in range

  /**
   * Adds <i>n</i> times the step value to the passed value. 
   * 
   * If step was set to zero it uses <TT>fabs(maximum() - minimum()) /
   * 100</TT>.
   *
   * \param[in] value this value will be incremented
   * \param[in] n increment value <i>n</i> times
   * \return the incremented value
   */
  double increment(double value, int n); // add n*step to value
};

#endif

//
// End of "$Id$".
//
