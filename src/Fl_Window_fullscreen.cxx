//
// "$Id$"
//
// Fullscreen window support for the Fast Light Tool Kit (FLTK).
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

// Turning the border on/off by changing the motif_wm_hints property
// works on Irix 4DWM.  Does not appear to work for any other window
// manager.  Fullscreen still works on some window managers (fvwm is one)
// because they allow the border to be placed off-screen.

// Unfortunately most X window managers ignore changes to the border
// and refuse to position the border off-screen, so attempting to make
// the window full screen will lose the size of the border off the
// bottom and right.

#include <fltk3/run.h>
#include <fltk3/x.H>

#include <config.h>

void fltk3::Window::border(int b) {
  if (b) {
    if (border()) return;
    clear_flag(NOBORDER);
  } else {
    if (!border()) return;
    set_flag(NOBORDER);
  }
#if defined(USE_X11)
  if (shown()) Fl_X::i(this)->sendxjunk();
#elif defined(WIN32)
  // not yet implemented, but it's possible
  // for full fullscreen we have to make the window topmost as well
#elif defined(__APPLE_QUARTZ__)
  // warning: not implemented in Quartz/Carbon
#else
# error unsupported platform
#endif
}

void fltk3::Window::fullscreen() {
#ifndef WIN32
  //this would clobber the fake wm, since it relies on the border flags to
  //determine its thickness
  border(0);
#endif
#if defined(__APPLE__) || defined(WIN32)
  int sx, sy, sw, sh;
  fltk3::screen_xywh(sx, sy, sw, sh, x()+w()/2, y()+h()/2);
  // if we are on the main screen, we will leave the system menu bar unobstructed
  if (fltk3::x()>=sx && fltk3::y()>=sy && fltk3::x()+fltk3::w()<=sx+sw && fltk3::y()+fltk3::h()<=sy+sh) {
    sx = fltk3::x(); sy = fltk3::y(); 
    sw = fltk3::w(); sh = fltk3::h();
  }
  if (x()==sx) x(sx+1); // make sure that we actually execute the resize
  resize(sx, sy, sw, sh);
#else
  if (!x()) x(1); // force it to call XResizeWindow()
  resize(0,0,fltk3::w(),fltk3::h());
#endif
}

void fltk3::Window::fullscreen_off(int X,int Y,int W,int H) {
  // this order produces less blinking on IRIX:
  resize(X,Y,W,H);
#ifndef WIN32
  border(1);
#endif
}

//
// End of "$Id$".
//
