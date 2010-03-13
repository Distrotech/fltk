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
// "$Id: Fl_Value_Slider.H 6902 2009-09-27 11:06:56Z matt $"
//
// Value slider header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Value_Slider widget . */

#ifndef Fl_Value_Slider_H
#define Fl_Value_Slider_H

#include "Slider.h"

/**
  The Fl_Value_Slider widget is a Fl_Slider widget
  with a box displaying the current value.
  <P ALIGN=CENTER>\image html value_slider.gif 
  \image latex  value_slider.eps "Fl_Value_Slider" width=4cm
*/
class FL_EXPORT Fl_Value_Slider : public Fl_Slider {
    Fl_Font textfont_;
    Fl_Fontsize textsize_;
    Fl_Color textcolor_;
protected:
    void draw();
public:
    int handle(int);
    Fl_Value_Slider(int x,int y,int w,int h, const char *l = 0);
    /**    Gets the typeface of the text in the value box.  */
    Fl_Font textfont() const {return textfont_;}
    /**    Sets the typeface of the text in the value box.  */
    void textfont(Fl_Font s) {textfont_ = s;}
    /**    Gets the size of the text in the value box.  */
    Fl_Fontsize textsize() const {return textsize_;}
    /**    Sets the size of the text in the value box.  */
    void textsize(Fl_Fontsize s) {textsize_ = s;}
    /**    Gets the color of the text in the value box.  */
    Fl_Color textcolor() const {return textcolor_;}
    /**    Sets the color of the text in the value box.  */
    void textcolor(Fl_Color s) {textcolor_ = s;}
};

#endif

//
// End of "$Id: Fl_Value_Slider.H 6902 2009-09-27 11:06:56Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::ValueSlider
class Fl_Value_Slider : public fltk::ValueSlider {
public:
  Fl_Value_Slider(int x, int t, int w, int h, const char *label=0)
  : fltk::ValueSlider(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Value_Slider.H 6902 2009-09-27 11:06:56Z matt $"
//
// Value slider header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Value_Slider widget . */

#ifndef Fl_Value_Slider_H
#define Fl_Value_Slider_H

#include "Fl_Slider.H"

/**
  The Fl_Value_Slider widget is a Fl_Slider widget
  with a box displaying the current value.
  <P ALIGN=CENTER>\image html value_slider.gif 
  \image latex  value_slider.eps "Fl_Value_Slider" width=4cm
*/
class FL_EXPORT Fl_Value_Slider : public Fl_Slider {
    Fl_Font textfont_;
    Fl_Fontsize textsize_;
    Fl_Color textcolor_;
protected:
    void draw();
public:
    int handle(int);
    Fl_Value_Slider(int x,int y,int w,int h, const char *l = 0);
    /**    Gets the typeface of the text in the value box.  */
    Fl_Font textfont() const {return textfont_;}
    /**    Sets the typeface of the text in the value box.  */
    void textfont(Fl_Font s) {textfont_ = s;}
    /**    Gets the size of the text in the value box.  */
    Fl_Fontsize textsize() const {return textsize_;}
    /**    Sets the size of the text in the value box.  */
    void textsize(Fl_Fontsize s) {textsize_ = s;}
    /**    Gets the color of the text in the value box.  */
    Fl_Color textcolor() const {return textcolor_;}
    /**    Sets the color of the text in the value box.  */
    void textcolor(Fl_Color s) {textcolor_ = s;}
};

#endif

//
// End of "$Id: Fl_Value_Slider.H 6902 2009-09-27 11:06:56Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id: ValueSlider.h 4886 2006-03-30 09:55:32Z fabien $"
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

#ifndef fltk_Value_Slider_h
#define fltk_Value_Slider_h

#include "Slider.h"
#include "FloatInput.h"

namespace fltk {

class FL_API ValueSlider : public Slider {
public:
  FloatInput input;
  int handle(int);
  void draw();
  ValueSlider(int x,int y,int w,int h, const char *l = 0);
  ~ValueSlider();
  void layout();
  virtual void value_damage(); // cause damage() due to value() changing

private:
  static void input_cb(Widget*,void*);
  void slider_rect(Rectangle&);
};

}
#endif

//
// End of "$Id: ValueSlider.h 4886 2006-03-30 09:55:32Z fabien $".
//
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
