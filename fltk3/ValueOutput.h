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
// "$Id: Fl_Value_Output.H 6902 2009-09-27 11:06:56Z matt $"
//
// Value output header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Value_Output widget . */

#ifndef Fl_Value_Output_H
#define Fl_Value_Output_H

#ifndef Fl_Valuator_H
#include "Valuator.h"
#endif

/**
  The Fl_Value_Output widget displays a floating point value.
  If step() is not zero, the user can adjust the value by
  dragging the mouse left and right.  The left button moves one step()
  per pixel, the middle by 10 * step(), and the right button by 
  100 * step().
  <P>This is much lighter-weight than 
  Fl_Value_Input because it contains no text editing code or
  character buffer. </P>
  <P ALIGN=CENTER>\image html Fl_Value_Output.gif 
  \image latex  Fl_Value_Output.eps "Fl_Value_Output" width=8cm
*/
class FL_EXPORT Fl_Value_Output : public Fl_Valuator {
  Fl_Font textfont_;
  Fl_Fontsize textsize_;
  uchar soft_;
  Fl_Color textcolor_;

protected:
  void draw();

public:
  int handle(int);
  Fl_Value_Output(int x,int y,int w,int h,const char *l=0);

  /**
    If "soft" is turned on, the user is allowed to drag the value outside
    the range.  If they drag the value to one of the ends, let go, then
    grab again and continue to drag, they can get to any value.  Default is
    one.
  */
  void soft(uchar s) {soft_ = s;}
  /**
    If "soft" is turned on, the user is allowed to drag the value outside
    the range.  If they drag the value to one of the ends, let go, then
    grab again and continue to drag, they can get to any value.  Default is
    one.
  */
  uchar soft() const {return soft_;}

  /**    Gets the typeface of the text in the value box.  */
  Fl_Font textfont() const {return textfont_;}
  /**    Sets the typeface of the text in the value box.  */
  void textfont(Fl_Font s) {textfont_ = s;}
  /**    Gets the size of the text in the value box.  */
  Fl_Fontsize textsize() const {return textsize_;}
  void textsize(Fl_Fontsize s) {textsize_ = s;}
  /**    Sets the color of the text in the value box.  */
  Fl_Color textcolor() const {return textcolor_;}
  /**    Gets the color of the text in the value box.  */
  void textcolor(Fl_Color s) {textcolor_ = s;}
};

#endif

//
// End of "$Id: Fl_Value_Output.H 6902 2009-09-27 11:06:56Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::ValueOutput
class Fl_Value_Output : public fltk::ValueOutput {
public:
  Fl_Value_Output(int x, int t, int w, int h, const char *label=0)
  : fltk::ValueOutput(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Value_Output.H 6902 2009-09-27 11:06:56Z matt $"
//
// Value output header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Value_Output widget . */

#ifndef Fl_Value_Output_H
#define Fl_Value_Output_H

#ifndef Fl_Valuator_H
#include "Fl_Valuator.H"
#endif

/**
  The Fl_Value_Output widget displays a floating point value.
  If step() is not zero, the user can adjust the value by
  dragging the mouse left and right.  The left button moves one step()
  per pixel, the middle by 10 * step(), and the right button by 
  100 * step().
  <P>This is much lighter-weight than 
  Fl_Value_Input because it contains no text editing code or
  character buffer. </P>
  <P ALIGN=CENTER>\image html Fl_Value_Output.gif 
  \image latex  Fl_Value_Output.eps "Fl_Value_Output" width=8cm
*/
class FL_EXPORT Fl_Value_Output : public Fl_Valuator {
  Fl_Font textfont_;
  Fl_Fontsize textsize_;
  uchar soft_;
  Fl_Color textcolor_;

protected:
  void draw();

public:
  int handle(int);
  Fl_Value_Output(int x,int y,int w,int h,const char *l=0);

  /**
    If "soft" is turned on, the user is allowed to drag the value outside
    the range.  If they drag the value to one of the ends, let go, then
    grab again and continue to drag, they can get to any value.  Default is
    one.
  */
  void soft(uchar s) {soft_ = s;}
  /**
    If "soft" is turned on, the user is allowed to drag the value outside
    the range.  If they drag the value to one of the ends, let go, then
    grab again and continue to drag, they can get to any value.  Default is
    one.
  */
  uchar soft() const {return soft_;}

  /**    Gets the typeface of the text in the value box.  */
  Fl_Font textfont() const {return textfont_;}
  /**    Sets the typeface of the text in the value box.  */
  void textfont(Fl_Font s) {textfont_ = s;}
  /**    Gets the size of the text in the value box.  */
  Fl_Fontsize textsize() const {return textsize_;}
  void textsize(Fl_Fontsize s) {textsize_ = s;}
  /**    Sets the color of the text in the value box.  */
  Fl_Color textcolor() const {return textcolor_;}
  /**    Gets the color of the text in the value box.  */
  void textcolor(Fl_Color s) {textcolor_ = s;}
};

#endif

//
// End of "$Id: Fl_Value_Output.H 6902 2009-09-27 11:06:56Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id: ValueOutput.h 5197 2006-06-14 07:43:46Z spitzak $"
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
// Please report all bugs and problems to "fltk-bugs@easysw.com".
//

#ifndef fltk_ValueOutput_h
#define fltk_ValueOutput_h

#include "Valuator.h"

namespace fltk {

class FL_API ValueOutput : public Valuator {
public:
  void draw();
  int handle(int);
  ValueOutput(int x,int y,int w,int h,const char *l = 0)
    : Valuator(x, y, w, h, l) {align(ALIGN_LEFT);}
};

}

#endif

//
// End of "$Id: ValueOutput.h 5197 2006-06-14 07:43:46Z spitzak $".
//
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
