/+- This file was imported from C++ using a script
//
// "$Id: grab.d 5190 2006-06-09 16:16:34Z mike $"
//
// Grab/release code for the Fast Light Tool Kit (FLTK).
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

#include <config.h>
#include <FL/Fl.H>
#include <FL/x.H>

////////////////////////////////////////////////////////////////
// "Grab" is done while menu systems are up.  This has several effects:
// Events are all sent to the "grab window", which does not even
// have to be displayed (and in the case of Fl_Menu.cxx it isn't).
// The system is also told to "grab" events and send them to this app.
// This also modifies how Fl_Window.show() works, on X it turns on
// override_redirect, it does similar things on WIN32.

extern void fl_fix_focus(); // in Fl.cxx

version (WIN32) {
// We have to keep track of whether we have captured the mouse, since
// MSWindows shows little respect for this... Grep for fl_capture to
// see where and how this is used.
extern HWND fl_capture;
}

version (__APPLE__) {
// MacOS Carbon does not seem to have a mechanism to grab the mouse pointer
extern WindowRef fl_capture;
}


//
// End of "$Id: grab.d 5190 2006-06-09 16:16:34Z mike $".
//
    End of automatic import -+/
