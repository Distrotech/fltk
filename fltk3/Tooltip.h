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
// "$Id: Fl_Tooltip.H 6902 2009-09-27 11:06:56Z matt $"
//
// Tooltip header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Tooltip widget . */

#ifndef Fl_Tooltip_H
#define Fl_Tooltip_H

#include <FL/Fl.H>
#include <FL/Fl_Widget.H>

/**
  The Fl_Tooltip class provides tooltip support for
  all FLTK widgets. It contains only static methods.
*/
class FL_EXPORT Fl_Tooltip {
public:
  /**    Gets the tooltip delay. The default delay is 1.0 seconds.  */
  static float delay() { return delay_; }
  /**    Sets the tooltip delay. The default delay is 1.0 seconds.  */
  static void delay(float f) { delay_ = f; }
  /**
    Gets the tooltip hover delay, the delay between tooltips.
    The default delay is 0.2 seconds.
  */
  static float hoverdelay() { return hoverdelay_; }
  /**
    Sets the tooltip hover delay, the delay between tooltips.
    The default delay is 0.2 seconds.
  */
  static void hoverdelay(float f) { hoverdelay_ = f; }
  /**    Returns non-zero if tooltips are enabled.  */
  static int enabled() { return enabled_; }
  /**    Enables tooltips on all widgets (or disables if <i>b</i> is false).  */
  static void enable(int b = 1) { enabled_ = b;}
  /**    Same as enable(0), disables tooltips on all widgets.  */
  static void disable() { enabled_ = 0; }
  static void (*enter)(Fl_Widget* w);
  static void enter_area(Fl_Widget* w, int X, int Y, int W, int H, const char* tip);
  static void (*exit)(Fl_Widget *w);
  /** Gets the current widget target */
  static Fl_Widget* current() {return widget_;}
  static void current(Fl_Widget*);

  /**    Gets the typeface for the tooltip text.  */
  static Fl_Font font() { return font_; }
  /**    Sets the typeface for the tooltip text.  */
  static void font(Fl_Font i) { font_ = i; }
  /**    Gets the size of the tooltip text.  */
  static Fl_Fontsize size() { return size_; }
  /**    Sets the size of the tooltip text.  */
  static void size(Fl_Fontsize s) { size_ = s; }
  /** Gets the background color for tooltips. The default background color is a pale yellow.  */
  static Fl_Color color() { return color_; }
  /** Sets the background color for tooltips. The default background color is a pale yellow.  */
  static void color(Fl_Color c) { color_ = c; }
  /** Gets the color of the text in the tooltip. The default is  black. */
  static Fl_Color textcolor() { return textcolor_; }
  /** Sets the color of the text in the tooltip. The default is  black. */
  static void textcolor(Fl_Color c) { textcolor_ = c; }

  // These should not be public, but Fl_Widget::tooltip() needs them...
  // fabien: made it private with only a friend function access
private:
  friend void Fl_Widget::tooltip(const char *);
  static void enter_(Fl_Widget* w);
  static void exit_(Fl_Widget *w);

private:
  static float delay_; //!< delay before a tooltip is shown
  static float hoverdelay_; //!< delay between tooltips
  static int enabled_;
  static Fl_Color color_;
  static Fl_Color textcolor_;
  static Fl_Font font_;
  static Fl_Fontsize size_;
  static Fl_Widget* widget_; //!< Keeps track of the current target widget
};

#endif

//
// End of "$Id: Fl_Tooltip.H 6902 2009-09-27 11:06:56Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::Tooltip
class Fl_Tooltip : public fltk::Tooltip {
public:
  Fl_Tooltip(int x, int t, int w, int h, const char *label=0)
  : fltk::Tooltip(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Tooltip.H 6902 2009-09-27 11:06:56Z matt $"
//
// Tooltip header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Tooltip widget . */

#ifndef Fl_Tooltip_H
#define Fl_Tooltip_H

#include <FL/Fl.H>
#include <FL/Fl_Widget.H>

/**
  The Fl_Tooltip class provides tooltip support for
  all FLTK widgets. It contains only static methods.
*/
class FL_EXPORT Fl_Tooltip {
public:
  /**    Gets the tooltip delay. The default delay is 1.0 seconds.  */
  static float delay() { return delay_; }
  /**    Sets the tooltip delay. The default delay is 1.0 seconds.  */
  static void delay(float f) { delay_ = f; }
  /**
    Gets the tooltip hover delay, the delay between tooltips.
    The default delay is 0.2 seconds.
  */
  static float hoverdelay() { return hoverdelay_; }
  /**
    Sets the tooltip hover delay, the delay between tooltips.
    The default delay is 0.2 seconds.
  */
  static void hoverdelay(float f) { hoverdelay_ = f; }
  /**    Returns non-zero if tooltips are enabled.  */
  static int enabled() { return enabled_; }
  /**    Enables tooltips on all widgets (or disables if <i>b</i> is false).  */
  static void enable(int b = 1) { enabled_ = b;}
  /**    Same as enable(0), disables tooltips on all widgets.  */
  static void disable() { enabled_ = 0; }
  static void (*enter)(Fl_Widget* w);
  static void enter_area(Fl_Widget* w, int X, int Y, int W, int H, const char* tip);
  static void (*exit)(Fl_Widget *w);
  /** Gets the current widget target */
  static Fl_Widget* current() {return widget_;}
  static void current(Fl_Widget*);

  /**    Gets the typeface for the tooltip text.  */
  static Fl_Font font() { return font_; }
  /**    Sets the typeface for the tooltip text.  */
  static void font(Fl_Font i) { font_ = i; }
  /**    Gets the size of the tooltip text.  */
  static Fl_Fontsize size() { return size_; }
  /**    Sets the size of the tooltip text.  */
  static void size(Fl_Fontsize s) { size_ = s; }
  /** Gets the background color for tooltips. The default background color is a pale yellow.  */
  static Fl_Color color() { return color_; }
  /** Sets the background color for tooltips. The default background color is a pale yellow.  */
  static void color(Fl_Color c) { color_ = c; }
  /** Gets the color of the text in the tooltip. The default is  black. */
  static Fl_Color textcolor() { return textcolor_; }
  /** Sets the color of the text in the tooltip. The default is  black. */
  static void textcolor(Fl_Color c) { textcolor_ = c; }

  // These should not be public, but Fl_Widget::tooltip() needs them...
  // fabien: made it private with only a friend function access
private:
  friend void Fl_Widget::tooltip(const char *);
  static void enter_(Fl_Widget* w);
  static void exit_(Fl_Widget *w);

private:
  static float delay_; //!< delay before a tooltip is shown
  static float hoverdelay_; //!< delay between tooltips
  static int enabled_;
  static Fl_Color color_;
  static Fl_Color textcolor_;
  static Fl_Font font_;
  static Fl_Fontsize size_;
  static Fl_Widget* widget_; //!< Keeps track of the current target widget
};

#endif

//
// End of "$Id: Fl_Tooltip.H 6902 2009-09-27 11:06:56Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
// "$Id: Tooltip.h 4886 2006-03-30 09:55:32Z fabien $"
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

#ifndef fltk_Tooltip_h
#define fltk_Tooltip_h

#include "MenuWindow.h"

namespace fltk {

class FL_API Tooltip : public MenuWindow {
public:
  Tooltip();
  void draw();
  void layout();

  static float delay() { return delay_; }
  static void delay(float f) { delay_ = f; }
  static bool enabled() { return enabled_; }
  static void enable(bool b = true) { enabled_ = b; }
  static void disable() { enabled_ = false; }

  typedef const char* (*Generator)(Widget*, void*);
  static void enter(Widget*, const Rectangle&, Generator, void* = 0);
  static void enter(Widget*, const Rectangle&, const char* text);
  static void enter(Widget*);
  static void current(Widget*);
  static void exit();

  static Widget* current_widget() { return current_widget_; }
  static const Rectangle& current_rectangle() { return current_rectangle_; }
  static Generator current_generator() { return current_generator_; }
  static void* current_data()	{ return current_data_; }
  static Tooltip* instance()	{ return instance_; }

  static NamedStyle* default_style;
#ifdef FLTK_1_WIDGET  // back-compatability section:
  static Widget* current()	{ return current_widget_; }
  static Font* font()		{ return default_style->textfont(); }
  static void font(Font* i)	{ default_style->textfont(i); }
  static float size()		{ return default_style->labelsize(); }
  static void size(float s)	{ default_style->labelsize(s); }
  static void textcolor(Color c){ default_style->labelcolor(c); }
  static Color textcolor()	{ return default_style->labelcolor(); }
  static void color(Color c)	{ default_style->color(c); }
  static Color color()		{ return default_style->color(); }
  static void box(Box* b)	{ default_style->box(b); }
  static Box* box()		{ return default_style->box(); }
#endif

private:
  static float delay_;
  static bool enabled_;
  static Widget* current_widget_;
  static Rectangle current_rectangle_;
  static Generator current_generator_;
  static void* current_data_;
  static Tooltip* instance_;
  static void tooltip_timeout(void*);
};

}

#endif

//
// End of "$Id: Tooltip.h 4886 2006-03-30 09:55:32Z fabien $".
//
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
