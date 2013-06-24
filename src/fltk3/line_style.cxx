//
// "$Id$"
//
// Line style code for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2010 by Bill Spitzak and others.
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

/**
  \file fl_line_style.cxx
  \brief Line style drawing utility hiding different platforms.
*/

#include <fltk3/run.h>
#include <fltk3/draw.h>
#include <fltk3/x.h>
#include <fltk3/Printer.h>
#include "flstring.h"
#include <stdio.h>

// We save the current line width (absolute value) here.
// This is currently used only for X11 clipping, see src/fltk3::rect.cxx.
// FIXME: this would probably better be in class fltk3::
int fl_line_width_ = 0;



//
// End of "$Id$".
//
