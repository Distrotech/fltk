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
// "$Id: Fl_Color_Chooser.H 6614 2009-01-01 16:11:32Z matt $"
//
// Color chooser header file for the Fast Light Tool Kit (FLTK).
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

/** \file
   Fl_Color_Chooser widget . */

// The color chooser object and the color chooser popup.  The popup
// is just a window containing a single color chooser and some boxes
// to indicate the current and cancelled color.

#ifndef Fl_Color_Chooser_H
#define Fl_Color_Chooser_H

#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Value_Input.H>

#ifndef FL_DOXYGEN

/** For internal use only */
class FL_EXPORT Flcc_HueBox : public Fl_Widget {
  int px, py;
protected:
  void draw();
  int handle_key(int);
public:
  int handle(int);
  Flcc_HueBox(int X, int Y, int W, int H) : Fl_Widget(X,Y,W,H) {
  px = py = 0;}
};

/** For internal use only */
class FL_EXPORT Flcc_ValueBox : public Fl_Widget {
  int py;
protected:
  void draw();
  int handle_key(int);
public:
  int handle(int);
  Flcc_ValueBox(int X, int Y, int W, int H) : Fl_Widget(X,Y,W,H) {
  py = 0;}
};

/** For internal use only */
class FL_EXPORT Flcc_Value_Input : public Fl_Value_Input {
public:
  int format(char*);
  Flcc_Value_Input(int X, int Y, int W, int H) : Fl_Value_Input(X,Y,W,H) {}
};

#endif // !FL_DOXYGEN

/** \addtogroup group_comdlg 
    @{ */

/**
  \class Fl_Color_Chooser
  \brief The Fl_Color_Chooser widget provides a standard RGB color chooser.

  \image html fl_color_chooser.jpg
  \image latex fl_color_chooser.eps "fl_color_chooser()" width=5cm

  You can place any number of the widgets into a panel of your own design.
  The diagram shows the widget as part of a color chooser dialog created by
  the fl_color_chooser() function. The Fl_Color_Chooser widget contains the
  hue box, value slider, and rgb input fields from the above diagram (it
  does not have the color chips or the Cancel or OK buttons).
  The callback is done every time the user changes the rgb value. It is not
  done if they move the hue control in a way that produces the \e same rgb
  value, such as when saturation or value is zero.

  The fl_color_chooser() function pops up a window to let the user pick an
  arbitrary RGB color. They can pick the hue and saturation in the "hue box"
  on the left (hold down CTRL to just change the saturation), and the
  brightness using the vertical slider. Or they can type the 8-bit numbers
  into the RGB Fl_Value_Input fields, or drag the mouse across them to adjust
  them.  The pull-down menu lets the user set the input fields to show RGB,
  HSV, or 8-bit RGB (0 to 255).

  fl_color_chooser() returns non-zero if the user picks ok, and updates the
  RGB values.  If the user picks cancel or closes the window this returns
  zero and leaves RGB unchanged.

  If you use the color chooser on an 8-bit screen, it will allocate all the
  available colors, leaving you no space to exactly represent the color the
  user picks! You can however use fl_rectf() to fill a region with a simulated
  color using dithering.
 */
/** @} */
class FL_EXPORT Fl_Color_Chooser : public Fl_Group {
  Flcc_HueBox huebox;
  Flcc_ValueBox valuebox;
  Fl_Choice choice;
  Flcc_Value_Input rvalue;
  Flcc_Value_Input gvalue;
  Flcc_Value_Input bvalue;
  Fl_Box resize_box;
  double hue_, saturation_, value_;
  double r_, g_, b_;
  void set_valuators();
  static void rgb_cb(Fl_Widget*, void*);
  static void mode_cb(Fl_Widget*, void*);
public:
  /** Returns which Fl_Color_Chooser variant is currently active */
  int mode() {return choice.value();}

  /**
    Returns the current hue.
    0 <= hue < 6. Zero is red, one is yellow, two is green, etc.
    <em>This value is convenient for the internal calculations - some other
    systems consider hue to run from zero to one, or from 0 to 360.</em>
   */
  double hue() const {return hue_;}

  /**
    Returns the saturation.
    0 <= saturation <= 1.
   */
  double saturation() const {return saturation_;}

  /**
    Returns the value/brightness.
    0 <= value <= 1.
   */
  double value() const {return value_;}

  /**
    Returns the current red value.
    0 <= r <= 1.
   */
  double r() const {return r_;}

  /**
    Returns the current green value.
    0 <= g <= 1.
   */
  double g() const {return g_;}

  /**
    Returns the current blue value.
    0 <= b <= 1.
   */
  double b() const {return b_;}

  int hsv(double H, double S, double V);

  int rgb(double R, double G, double B);

  static void hsv2rgb(double H, double S, double V, double& R, double& G, double& B);

  static void rgb2hsv(double R, double G, double B, double& H, double& S, double& V);

  Fl_Color_Chooser(int X, int Y, int W, int H, const char *L = 0);
};

FL_EXPORT int fl_color_chooser(const char* name, double& r, double& g, double& b);
FL_EXPORT int fl_color_chooser(const char* name, uchar& r, uchar& g, uchar& b);

#endif

//
// End of "$Id: Fl_Color_Chooser.H 6614 2009-01-01 16:11:32Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::ColorChooser
class Fl_Color_Chooser : public fltk::ColorChooser {
public:
  Fl_Color_Chooser(int x, int t, int w, int h, const char *label=0)
  : fltk::ColorChooser(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Color_Chooser.H 6614 2009-01-01 16:11:32Z matt $"
//
// Color chooser header file for the Fast Light Tool Kit (FLTK).
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

/** \file
   Fl_Color_Chooser widget . */

// The color chooser object and the color chooser popup.  The popup
// is just a window containing a single color chooser and some boxes
// to indicate the current and cancelled color.

#ifndef Fl_Color_Chooser_H
#define Fl_Color_Chooser_H

#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Value_Input.H>

#ifndef FL_DOXYGEN

/** For internal use only */
class FL_EXPORT Flcc_HueBox : public Fl_Widget {
  int px, py;
protected:
  void draw();
  int handle_key(int);
public:
  int handle(int);
  Flcc_HueBox(int X, int Y, int W, int H) : Fl_Widget(X,Y,W,H) {
  px = py = 0;}
};

/** For internal use only */
class FL_EXPORT Flcc_ValueBox : public Fl_Widget {
  int py;
protected:
  void draw();
  int handle_key(int);
public:
  int handle(int);
  Flcc_ValueBox(int X, int Y, int W, int H) : Fl_Widget(X,Y,W,H) {
  py = 0;}
};

/** For internal use only */
class FL_EXPORT Flcc_Value_Input : public Fl_Value_Input {
public:
  int format(char*);
  Flcc_Value_Input(int X, int Y, int W, int H) : Fl_Value_Input(X,Y,W,H) {}
};

#endif // !FL_DOXYGEN

/** \addtogroup group_comdlg 
    @{ */

/**
  \class Fl_Color_Chooser
  \brief The Fl_Color_Chooser widget provides a standard RGB color chooser.

  \image html fl_color_chooser.jpg
  \image latex fl_color_chooser.eps "fl_color_chooser()" width=5cm

  You can place any number of the widgets into a panel of your own design.
  The diagram shows the widget as part of a color chooser dialog created by
  the fl_color_chooser() function. The Fl_Color_Chooser widget contains the
  hue box, value slider, and rgb input fields from the above diagram (it
  does not have the color chips or the Cancel or OK buttons).
  The callback is done every time the user changes the rgb value. It is not
  done if they move the hue control in a way that produces the \e same rgb
  value, such as when saturation or value is zero.

  The fl_color_chooser() function pops up a window to let the user pick an
  arbitrary RGB color. They can pick the hue and saturation in the "hue box"
  on the left (hold down CTRL to just change the saturation), and the
  brightness using the vertical slider. Or they can type the 8-bit numbers
  into the RGB Fl_Value_Input fields, or drag the mouse across them to adjust
  them.  The pull-down menu lets the user set the input fields to show RGB,
  HSV, or 8-bit RGB (0 to 255).

  fl_color_chooser() returns non-zero if the user picks ok, and updates the
  RGB values.  If the user picks cancel or closes the window this returns
  zero and leaves RGB unchanged.

  If you use the color chooser on an 8-bit screen, it will allocate all the
  available colors, leaving you no space to exactly represent the color the
  user picks! You can however use fl_rectf() to fill a region with a simulated
  color using dithering.
 */
/** @} */
class FL_EXPORT Fl_Color_Chooser : public Fl_Group {
  Flcc_HueBox huebox;
  Flcc_ValueBox valuebox;
  Fl_Choice choice;
  Flcc_Value_Input rvalue;
  Flcc_Value_Input gvalue;
  Flcc_Value_Input bvalue;
  Fl_Box resize_box;
  double hue_, saturation_, value_;
  double r_, g_, b_;
  void set_valuators();
  static void rgb_cb(Fl_Widget*, void*);
  static void mode_cb(Fl_Widget*, void*);
public:
  /** Returns which Fl_Color_Chooser variant is currently active */
  int mode() {return choice.value();}

  /**
    Returns the current hue.
    0 <= hue < 6. Zero is red, one is yellow, two is green, etc.
    <em>This value is convenient for the internal calculations - some other
    systems consider hue to run from zero to one, or from 0 to 360.</em>
   */
  double hue() const {return hue_;}

  /**
    Returns the saturation.
    0 <= saturation <= 1.
   */
  double saturation() const {return saturation_;}

  /**
    Returns the value/brightness.
    0 <= value <= 1.
   */
  double value() const {return value_;}

  /**
    Returns the current red value.
    0 <= r <= 1.
   */
  double r() const {return r_;}

  /**
    Returns the current green value.
    0 <= g <= 1.
   */
  double g() const {return g_;}

  /**
    Returns the current blue value.
    0 <= b <= 1.
   */
  double b() const {return b_;}

  int hsv(double H, double S, double V);

  int rgb(double R, double G, double B);

  static void hsv2rgb(double H, double S, double V, double& R, double& G, double& B);

  static void rgb2hsv(double R, double G, double B, double& H, double& S, double& V);

  Fl_Color_Chooser(int X, int Y, int W, int H, const char *L = 0);
};

FL_EXPORT int fl_color_chooser(const char* name, double& r, double& g, double& b);
FL_EXPORT int fl_color_chooser(const char* name, uchar& r, uchar& g, uchar& b);

#endif

//
// End of "$Id: Fl_Color_Chooser.H 6614 2009-01-01 16:11:32Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id: ColorChooser.h 5197 2006-06-14 07:43:46Z spitzak $"
//
// Color chooser header file for the Fast Light Tool Kit (FLTK).
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

// The color chooser object and the color chooser popup.  The popup
// is just a window containing a single color chooser and some boxes
// to indicate the current and cancelled color.

#ifndef fltk_ColorChooser_h
#define fltk_ColorChooser_h

#include "Group.h"

namespace fltk {

class FL_API ccHueBox : public Widget {
  int px, py;
protected:
  void draw();
public:
  int handle(int);
  ccHueBox(int X, int Y, int W, int H) : Widget(X,Y,W,H) {
  px = py = 0;}
};

class FL_API ccValueBox : public Widget {
  int py;
  bool is_alpha() const;
protected:
  void draw();
public:
  int handle(int);
  ccValueBox(int X, int Y, int W, int H) : Widget(X,Y,W,H) {
  py = 0;}
};

class FL_API ccCellBox : public Widget {
public:
  ccCellBox(int X, int Y, int W, int H) : Widget(X,Y,W,H) {}
  void draw();
  int handle(int);
};

class FL_API ColorChooser : public Group {
  friend class ccHueBox;
  friend class ccValueBox;
  friend class ccCellBox;
  ccHueBox huebox;
  ccValueBox valuebox;
  ccValueBox alphabox;
  ccCellBox cellbox;
  float hue_, saturation_, value_;
  float r_, g_, b_, a_;
  bool no_value_;
  bool support_no_value;
public:
  float h() const {return hue_;}
  float s() const {return saturation_;}
  float v() const {return value_;}
  float r() const {return r_;}
  float g() const {return g_;}
  float b() const {return b_;}
  float a() const {return a_;}
  bool no_value() const {return no_value_;}
  bool no_value(bool);
  Color value() const;
  bool value(Color);
  bool hsv(float,float,float);
  bool rgb(float,float,float);
  bool a(float);
  void hide_a();
  void hide_no_value() {support_no_value = false;}
  static void hsv2rgb(float, float, float,float&,float&,float&);
  static void rgb2hsv(float, float, float,float&,float&,float&);
  ColorChooser(int,int,int,int,const char* = 0);
  void layout();
  float setcell(int,float,float,float,float);
  float getcell(int,float,float,float,float);
};

// Convience functions to pop-up a control panel:

FL_API bool color_chooser(const char* name, float& r, float& g, float& b);
FL_API bool color_chooser(const char* name, float& r, float& g, float& b, float& a);
FL_API bool color_chooser(const char* name, uchar& r, uchar& g, uchar& b);
FL_API bool color_chooser(const char* name, uchar& r, uchar& g, uchar& b, uchar& a);
FL_API bool color_chooser(const char* name, Color& c);

}

#endif

//
// End of "$Id: ColorChooser.h 5197 2006-06-14 07:43:46Z spitzak $".
//
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
