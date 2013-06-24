//
// "$Id$"
//
// implementation of fltk3::Device class for the Fast Light Tool Kit (FLTK).
//
// Copyright 2010-2011 by Bill Spitzak and others.
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
// Please report all bugs and problems to:
//
//     http://www.fltk.org/str.php
//

#include <config.h>

#ifdef WIN32

#include "Win32WindowDriver.h"
#include <fltk3/x.h>
#include <stdio.h>


fltk3::Win32WindowDriver::Win32WindowDriver()
{
  fprintf(stderr, "Loading Window Driver\n");
}


void fltk3::Win32WindowDriver::iconize(fltk3::Window* win)
{
  ShowWindow(Fl_X::i(win)->xid, SW_SHOWMINNOACTIVE);
}


void fltk3::Win32WindowDriver::decoration_size(bool isResizable, int& top, int& left, int& right, int& bottom)
{
  if (isResizable) {
    left = right = GetSystemMetrics(SM_CXSIZEFRAME);
    top = bottom = GetSystemMetrics(SM_CYSIZEFRAME);
  } else {
    left = right = GetSystemMetrics(SM_CXFIXEDFRAME);
    top = bottom = GetSystemMetrics(SM_CYFIXEDFRAME);
  }
  top += GetSystemMetrics(SM_CYCAPTION);
}


#endif // WIN32

//
// End of "$Id$".
//
