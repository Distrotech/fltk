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
// "$Id: Fl_Overlay_Window.H 6614 2009-01-01 16:11:32Z matt $"
//
// Overlay window header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Overlay_Window class . */

#ifndef Fl_Overlay_Window_H
#define Fl_Overlay_Window_H

#include "DoubleBufferWindow.h"

/**
  This window provides double buffering and also the ability to draw the
  "overlay" which is another picture placed on top of the main image. The
  overlay is designed to be a rapidly-changing but simple graphic such as
  a mouse selection box. Fl_Overlay_Window uses the overlay
  planes provided by your graphics hardware if they are available.
  <P>If no hardware support is found the overlay is simulated by drawing
  directly into the on-screen copy of the double-buffered window, and
  "erased" by copying the backbuffer over it again.  This means the
  overlay will blink if you change the image in the window.
*/
class FL_EXPORT Fl_Overlay_Window : public Fl_Double_Window {
  friend class _Fl_Overlay;
  virtual void draw_overlay() = 0;
  fltk::Window *overlay_;
public:
  void show();
  void flush();
  void hide();
  void resize(int,int,int,int);
  ~Fl_Overlay_Window();
  int can_do_overlay();
  void redraw_overlay();
  /**
    Creates a new Fl_Overlay_Window widget using the given
    position, size, and label (title) string. If the 
    positions (x,y) are not given, then the window manager
    will choose them.
  */
  Fl_Overlay_Window(int W, int H, const char *l=0)
    : Fl_Double_Window(W,H,l) {overlay_ = 0; force_doublebuffering_=1; image(0); }
   /**
    See Fl_Overlay_Window::Fl_Overlay_Window(int W, int H, const char *l=0)
  */
 Fl_Overlay_Window(int X, int Y, int W, int H, const char *l=0)
    : Fl_Double_Window(X,Y,W,H,l) {overlay_ = 0; force_doublebuffering_=1; image(0); }
  void show(int a, char **b) {Fl_Double_Window::show(a,b);}
};

#endif

//
// End of "$Id: Fl_Overlay_Window.H 6614 2009-01-01 16:11:32Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::overlayWindow
class Fl_Overlay_Window : public fltk::overlayWindow {
public:
  Fl_Overlay_Window(int x, int t, int w, int h, const char *label=0)
  : fltk::overlayWindow(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Overlay_Window.H 6614 2009-01-01 16:11:32Z matt $"
//
// Overlay window header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Overlay_Window class . */

#ifndef Fl_Overlay_Window_H
#define Fl_Overlay_Window_H

#include "Fl_Double_Window.H"

/**
  This window provides double buffering and also the ability to draw the
  "overlay" which is another picture placed on top of the main image. The
  overlay is designed to be a rapidly-changing but simple graphic such as
  a mouse selection box. Fl_Overlay_Window uses the overlay
  planes provided by your graphics hardware if they are available.
  <P>If no hardware support is found the overlay is simulated by drawing
  directly into the on-screen copy of the double-buffered window, and
  "erased" by copying the backbuffer over it again.  This means the
  overlay will blink if you change the image in the window.
*/
class FL_EXPORT Fl_Overlay_Window : public Fl_Double_Window {
  friend class _Fl_Overlay;
  virtual void draw_overlay() = 0;
  fltk::Window *overlay_;
public:
  void show();
  void flush();
  void hide();
  void resize(int,int,int,int);
  ~Fl_Overlay_Window();
  int can_do_overlay();
  void redraw_overlay();
  /**
    Creates a new Fl_Overlay_Window widget using the given
    position, size, and label (title) string. If the 
    positions (x,y) are not given, then the window manager
    will choose them.
  */
  Fl_Overlay_Window(int W, int H, const char *l=0)
    : Fl_Double_Window(W,H,l) {overlay_ = 0; force_doublebuffering_=1; image(0); }
   /**
    See Fl_Overlay_Window::Fl_Overlay_Window(int W, int H, const char *l=0)
  */
 Fl_Overlay_Window(int X, int Y, int W, int H, const char *l=0)
    : Fl_Double_Window(X,Y,W,H,l) {overlay_ = 0; force_doublebuffering_=1; image(0); }
  void show(int a, char **b) {Fl_Double_Window::show(a,b);}
};

#endif

//
// End of "$Id: Fl_Overlay_Window.H 6614 2009-01-01 16:11:32Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
