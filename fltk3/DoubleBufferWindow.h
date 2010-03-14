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
// "$Id: Fl_Double_Window.H 6614 2009-01-01 16:11:32Z matt $"
//
// Double-buffered window header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Double_Window widget . */

#ifndef Fl_Double_Window_H
#define Fl_Double_Window_H

#include "Window.h"

/**
  The Fl_Double_Window provides a double-buffered window.
  If possible this will use the X double buffering extension (Xdbe).  If
  not, it will draw the window data into an off-screen pixmap, and then
  copy it to the on-screen window.
  <P>It is highly recommended that you put the following code before the
  first show() of <I>any</I> window in your program: </P>
  \code
  Fl::visual(FL_DOUBLE|FL_INDEX)
  \endcode
  This makes sure you can use Xdbe on servers where double buffering
  does not exist for every visual.
*/
class FL_EXPORT Fl_Double_Window : public Fl_Window {
protected:
  void flush(int eraseoverlay);
  /**
    Force double buffering, even if the OS already buffers windows
    (overlays need that on MacOS and Windows2000)
  */
  char force_doublebuffering_;
public:
  void show();
  void show(int a, char **b) {Fl_Window::show(a,b);}
  void flush();
  void resize(int,int,int,int);
  void hide();
  ~Fl_Double_Window();
  /**
    Creates a new Fl_Double_Window widget using the given
    position, size, and label (title) string.
  */
  Fl_Double_Window(int W, int H, const char *l = 0) 
    : Fl_Window(W,H,l), force_doublebuffering_(0) { type(FL_DOUBLE_WINDOW); }
   /**
    See  Fl_Double_Window::Fl_Double_Window(int w, int h, const char *label = 0)
  */
  Fl_Double_Window(int X, int Y, int W, int H, const char *l = 0)
    : Fl_Window(X,Y,W,H,l), force_doublebuffering_(0) { type(FL_DOUBLE_WINDOW); }
};

#endif

//
// End of "$Id: Fl_Double_Window.H 6614 2009-01-01 16:11:32Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::DoubleBufferWindow
class Fl_Double_Window : public fltk::DoubleBufferWindow {
public:
  Fl_Double_Window(int x, int t, int w, int h, const char *label=0)
  : fltk::DoubleBufferWindow(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Double_Window.H 6614 2009-01-01 16:11:32Z matt $"
//
// Double-buffered window header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Double_Window widget . */

#ifndef Fl_Double_Window_H
#define Fl_Double_Window_H

#include "Window.h"

/**
  The Fl_Double_Window provides a double-buffered window.
  If possible this will use the X double buffering extension (Xdbe).  If
  not, it will draw the window data into an off-screen pixmap, and then
  copy it to the on-screen window.
  <P>It is highly recommended that you put the following code before the
  first show() of <I>any</I> window in your program: </P>
  \code
  Fl::visual(FL_DOUBLE|FL_INDEX)
  \endcode
  This makes sure you can use Xdbe on servers where double buffering
  does not exist for every visual.
*/
class FL_EXPORT Fl_Double_Window : public Fl_Window {
protected:
  void flush(int eraseoverlay);
  /**
    Force double buffering, even if the OS already buffers windows
    (overlays need that on MacOS and Windows2000)
  */
  char force_doublebuffering_;
public:
  void show();
  void show(int a, char **b) {Fl_Window::show(a,b);}
  void flush();
  void resize(int,int,int,int);
  void hide();
  ~Fl_Double_Window();
  /**
    Creates a new Fl_Double_Window widget using the given
    position, size, and label (title) string.
  */
  Fl_Double_Window(int W, int H, const char *l = 0) 
    : Fl_Window(W,H,l), force_doublebuffering_(0) { type(FL_DOUBLE_WINDOW); }
   /**
    See  Fl_Double_Window::Fl_Double_Window(int w, int h, const char *label = 0)
  */
  Fl_Double_Window(int X, int Y, int W, int H, const char *l = 0)
    : Fl_Window(X,Y,W,H,l), force_doublebuffering_(0) { type(FL_DOUBLE_WINDOW); }
};

#endif

//
// End of "$Id: Fl_Double_Window.H 6614 2009-01-01 16:11:32Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
// This class is provided for back compatability only with some fltk2.0
// versions. You can turn on double buffering on a normal window if
// you want it.
  
#ifndef fltk_DoubleBufferWindow_h
#define fltk_DoubleBufferWindow_h

#ifndef fltk_Window_h
# include "Window.h"
#endif

namespace fltk {

class DoubleBufferWindow : public Window {

public:
  DoubleBufferWindow(int x, int y, int w, int h, const char*l = 0)
    : Window(x,y,w,h,l) {set_double_buffer();}
    
  DoubleBufferWindow(int w, int h, const char*l = 0)
    : Window(w,h,l) {set_double_buffer();}

};

}

#endif
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
