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
// "$Id: Fl_Output.H 6898 2009-09-23 20:43:27Z matt $"
//
// Output header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Output widget . */

#ifndef Fl_Output_H
#define Fl_Output_H

#include "Input.h"
/**
  This widget displays a piece of text.  When you set the value()
  , Fl_Output does a strcpy() to it's own storage,
  which is useful for program-generated values.  The user may select
  portions of the text using the mouse and paste the contents into other
  fields or programs.
  <P align=CENTER>\image html text.gif</P> 
  \image latex text.eps "Fl_Output" width=8cm
  <P>There is a single subclass, 
  Fl_Multiline_Output, which allows you to display multiple lines of
  text. Fl_Multiline_Output does not provide scroll bars. If a more 
  complete text editing widget is needed, use Fl_Text_Display instead.</P>
  <P>The text may contain any characters except \\0, and will correctly
  display anything, using ^X notation for unprintable control characters
  and \\nnn notation for unprintable characters with the high bit set. It
  assumes the font can draw any characters in the ISO-Latin1 character
  set.
*/
class Fl_Output : public Fl_Input {
public:
  /**
    Creates a new Fl_Output widget using the given position,
    size, and label string. The default boxtype is FL_DOWN_BOX.
    <P>Inherited destrucor destroys the widget and any value associated with it.
  */
    Fl_Output(int X,int Y,int W,int H, const char *l = 0)
    : Fl_Input(X, Y, W, H, l) {type(FL_NORMAL_OUTPUT);}
};

#endif 

//
// End of "$Id: Fl_Output.H 6898 2009-09-23 20:43:27Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::Output
class Fl_Output : public fltk::Output {
public:
  Fl_Output(int x, int t, int w, int h, const char *label=0)
  : fltk::Output(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Output.H 6898 2009-09-23 20:43:27Z matt $"
//
// Output header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Output widget . */

#ifndef Fl_Output_H
#define Fl_Output_H

#include "Fl_Input.H"
/**
  This widget displays a piece of text.  When you set the value()
  , Fl_Output does a strcpy() to it's own storage,
  which is useful for program-generated values.  The user may select
  portions of the text using the mouse and paste the contents into other
  fields or programs.
  <P align=CENTER>\image html text.gif</P> 
  \image latex text.eps "Fl_Output" width=8cm
  <P>There is a single subclass, 
  Fl_Multiline_Output, which allows you to display multiple lines of
  text. Fl_Multiline_Output does not provide scroll bars. If a more 
  complete text editing widget is needed, use Fl_Text_Display instead.</P>
  <P>The text may contain any characters except \\0, and will correctly
  display anything, using ^X notation for unprintable control characters
  and \\nnn notation for unprintable characters with the high bit set. It
  assumes the font can draw any characters in the ISO-Latin1 character
  set.
*/
class Fl_Output : public Fl_Input {
public:
  /**
    Creates a new Fl_Output widget using the given position,
    size, and label string. The default boxtype is FL_DOWN_BOX.
    <P>Inherited destrucor destroys the widget and any value associated with it.
  */
    Fl_Output(int X,int Y,int W,int H, const char *l = 0)
    : Fl_Input(X, Y, W, H, l) {type(FL_NORMAL_OUTPUT);}
};

#endif 

//
// End of "$Id: Fl_Output.H 6898 2009-09-23 20:43:27Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id: Output.h 4886 2006-03-30 09:55:32Z fabien $"
//
// One-line text output, the user can select text and copy it
// to other applications.
//
// Copyright 1998-2006 by Bill Spitzak and others.
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

#ifndef fltk_Output_h
#define fltk_Output_h

#include "Input.h"

namespace fltk {

class FL_API Output : public Input {
  virtual bool replace(int, int, const char*, int); // does nothing
public:
  Output(int x, int y, int w, int h, const char *l = 0);
  int handle(int);
  // this style is so Motif can have different color for output vs input:
  static NamedStyle* default_style;
};

}

#endif 

//
// End of "$Id: Output.h 4886 2006-03-30 09:55:32Z fabien $".
//
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
