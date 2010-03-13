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
// "$Id: Fl_Fill_Slider.H 6614 2009-01-01 16:11:32Z matt $"
//
// Filled slider header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Fill_Slider widget . */

#ifndef Fl_Fill_Slider_H
#define Fl_Fill_Slider_H

#include "Fl_Slider.H"
/** Widget that draws a filled horizontal  slider,  useful as a progress or value meter*/
class Fl_Fill_Slider : public Fl_Slider {
public:
    /** Creates the slider from its position,size and optional title. */
    Fl_Fill_Slider(int x,int y,int w,int h,const char *l=0)
	: Fl_Slider(x,y,w,h,l) {type(FL_VERT_FILL_SLIDER);}
};

#endif

//
// End of "$Id: Fl_Fill_Slider.H 6614 2009-01-01 16:11:32Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::FillSlider
class Fl_Fill_Slider : public fltk::FillSlider {
public:
  Fl_Fill_Slider(int x, int t, int w, int h, const char *label=0)
  : fltk::FillSlider(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Fill_Slider.H 6614 2009-01-01 16:11:32Z matt $"
//
// Filled slider header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Fill_Slider widget . */

#ifndef Fl_Fill_Slider_H
#define Fl_Fill_Slider_H

#include "Fl_Slider.H"
/** Widget that draws a filled horizontal  slider,  useful as a progress or value meter*/
class Fl_Fill_Slider : public Fl_Slider {
public:
    /** Creates the slider from its position,size and optional title. */
    Fl_Fill_Slider(int x,int y,int w,int h,const char *l=0)
	: Fl_Slider(x,y,w,h,l) {type(FL_VERT_FILL_SLIDER);}
};

#endif

//
// End of "$Id: Fl_Fill_Slider.H 6614 2009-01-01 16:11:32Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id: FillSlider.h 5450 2006-09-19 02:33:42Z spitzak $"
//
// Copyright 2006 by Bill Spitzak and others.
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
//

#ifndef fltk_FillSlider_h
#define fltk_FillSlider_h

#include "Slider.h"

namespace fltk {

/*! Vertical Slider that is filled from the end (like a progress bar) */
class FL_API FillSlider : public Slider {
public:
  FillSlider(int x,int y,int w,int h,const char *l=0)
    : Slider(x,y,w,h,l) {slider_size(0);}
};

}

#endif

//
// End of "$Id: FillSlider.h 5450 2006-09-19 02:33:42Z spitzak $".
//
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
