//
// "$Id: x.d 5262 2006-07-18 11:23:20Z matt $"
//
// OS specific dispatch file for the Fast Light Tool Kit (FLTK).
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

// These are internal fltk symbols that are necessary or useful for
// calling Xlib.  You should include this file if (and ONLY if) you
// need to call Xlib directly.  These symbols may not exist on non-X
// systems.

module fl.x;

public import fl.enumerations;

//version (Apple) {
  public import fl.mac;
//}

version (X11) {
  public import fl.x11;
}

version (Win32) {
  public import fl.win32;
}

//
// End of "$Id: x.d 5262 2006-07-18 11:23:20Z matt $".
//
