//
// "$Id$"
//
// Widget header file for the Fast Light Tool Kit (FLTK).
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
   fltk::Widget, Fl_Label classes . */

#ifndef Fl_Widget_H
#define Fl_Widget_H

#include "../FL/Enumerations.H"

#include "../FL3/Widget.h"

// This define maps the Fl_Widget directly onto fltk::Widget. Even though this
// is hardly elegant, it causes very little problems with FLTK1 compatibility.
// Coding style must be set at run-time for best compatibility.
#define Fl_Widget fltk::Widget

#define Fl_Widget fltk::Widget
#define Fl_Callback fltk::Callback
#define Fl_Callback0 fltk::Callback0
#define Fl_Callback1 fltk::Callback1

#endif

//
// End of "$Id$".
//
