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
// "$Id: Fl_Progress.H 6614 2009-01-01 16:11:32Z matt $"
//
// Progress bar widget definitions.
//
// Copyright 2000-2009 by Michael Sweet.
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
   Fl_Progress widget . */

#ifndef _Fl_Progress_H_
#  define _Fl_Progress_H_

//
// Include necessary headers.
//

#include "Widget.h"


//
// Progress class...
//
/**
    Displays a progress bar for the user.
*/
class FL_EXPORT Fl_Progress : public Fl_Widget
{
  float	value_,
	minimum_,
	maximum_;

  protected:

  virtual void draw();

  public:

  Fl_Progress(int x, int y, int w, int h, const char *l = 0);

  /** Sets the maximum value in the progress widget.  */
  void	maximum(float v) { maximum_ = v; redraw(); }
  /** Gets the maximum value in the progress widget.  */
  float	maximum() const { return (maximum_); }

  /** Sets the minimum value in the progress widget.  */
  void	minimum(float v) { minimum_ = v; redraw(); }
  /** Gets the minimum value in the progress widget.  */
  float	minimum() const { return (minimum_); }

  /** Sets the current value in the progress widget.  */
  void	value(float v) { value_ = v; redraw(); }
  /** Gets the current value in the progress widget.  */
  float	value() const { return (value_); }
};

#endif // !_Fl_Progress_H_

//
// End of "$Id: Fl_Progress.H 6614 2009-01-01 16:11:32Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::ProgressBar
class Fl_Progress : public fltk::ProgressBar {
public:
  Fl_Progress(int x, int t, int w, int h, const char *label=0)
  : fltk::ProgressBar(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Progress.H 6614 2009-01-01 16:11:32Z matt $"
//
// Progress bar widget definitions.
//
// Copyright 2000-2009 by Michael Sweet.
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
   Fl_Progress widget . */

#ifndef _Fl_Progress_H_
#  define _Fl_Progress_H_

//
// Include necessary headers.
//

#include "Fl_Widget.H"


//
// Progress class...
//
/**
    Displays a progress bar for the user.
*/
class FL_EXPORT Fl_Progress : public Fl_Widget
{
  float	value_,
	minimum_,
	maximum_;

  protected:

  virtual void draw();

  public:

  Fl_Progress(int x, int y, int w, int h, const char *l = 0);

  /** Sets the maximum value in the progress widget.  */
  void	maximum(float v) { maximum_ = v; redraw(); }
  /** Gets the maximum value in the progress widget.  */
  float	maximum() const { return (maximum_); }

  /** Sets the minimum value in the progress widget.  */
  void	minimum(float v) { minimum_ = v; redraw(); }
  /** Gets the minimum value in the progress widget.  */
  float	minimum() const { return (minimum_); }

  /** Sets the current value in the progress widget.  */
  void	value(float v) { value_ = v; redraw(); }
  /** Gets the current value in the progress widget.  */
  float	value() const { return (value_); }
};

#endif // !_Fl_Progress_H_

//
// End of "$Id: Fl_Progress.H 6614 2009-01-01 16:11:32Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id: ProgressBar.h 4886 2006-03-30 09:55:32Z fabien $"
//
// Progress indicator with bar that fills up and text showing the
// job being done and expected time to go. Not fully implemented yet.
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

#ifndef fltk_ProgressBar_h
#define fltk_ProgressBar_h

#include "Widget.h"

namespace fltk {

class FL_API ProgressBar : public Widget {
protected:
  double mMin;
  double mMax;
  double mPresent;
  double mStep;
  bool mShowPct;
  Color mTextColor;
  void draw();
public:
  ProgressBar(int x, int y, int w, int h, const char *lbl = 0);
  void range(double min, double max, double step = 1)  { mMin = min; mMax = max; mStep = step; };
  void step(double step)		{ mPresent += step; redraw(); };
  double minimum()	{ return mMin; }
  double maximum()	{ return mMax; }
  void minimum(double nm) { mMin = nm; };
  void maximum(double nm) { mMax = nm; };
  double position()	{ return mPresent; }
  double step()		{ return mStep; }
  void position(double pos) 	{ mPresent = pos; redraw(); }
  void showtext(bool st)	{ mShowPct = st; }
  bool showtext()		{ return mShowPct; }
  void text_color(Color col)	{ mTextColor = col; }
  Color text_color() 	{ return mTextColor; }
};

}
#endif

#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
