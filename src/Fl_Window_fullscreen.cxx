//
// "$Id"
//
// Fullscreen window support for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998 by Bill Spitzak and others.
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

// Turning the border on/off by changing the motif_wm_hints property
// works on Irix 4DWM.  Does not appear to work for any other window
// manager.  Fullscreen still works on some window managers (fvwm is one)
// because they allow the border to be placed off-screen.

// Unfortunatly most X window managers ignore changes to the border
// and refuse to position the border off-screen, so attempting to make
// the window full screen will lose the size of the border off the
// bottom and right.

#include <FL/Fl.H>
#include <FL/x.H>

void Fl_Window::border(int b) {
  if (b) {
    if (border()) return;
    clear_flag(FL_NOBORDER);
  } else {
    if (!border()) return;
    set_flag(FL_NOBORDER);
  }
#ifdef WIN32
  // not yet implemented, but it's possible
  // for full fullscreen we have to make the window topmost as well
#else
  if (shown()) Fl_X::i(this)->sendxjunk();
#endif
}

void Fl_Window::fullscreen() {
  border(0);
  if (!x()) x(1); // force it to call XResizeWindow()
  resize(0,0,Fl::w(),Fl::h());
}

void Fl_Window::fullscreen_off(int X,int Y,int W,int H) {
#ifdef WIN32
  border(1);
  resize(X,Y,W,H);
#else
  // this order produces less blinking on IRIX:
  resize(X,Y,W,H);
  border(1);
#endif
}

//
// End of "$Id: Fl_Window_fullscreen.cxx,v 1.2 1998/10/19 20:46:09 mike Exp $".
//
