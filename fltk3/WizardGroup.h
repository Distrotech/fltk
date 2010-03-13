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
// "$Id: Fl_Wizard.H 6614 2009-01-01 16:11:32Z matt $"
//
// Fl_Wizard widget definitions.
//
// Copyright 1999-2009 by Easy Software Products.
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
   Fl_Wizard widget . */

//
// Include necessary header files...
//

#ifndef _Fl_Wizard_H_
#  define _Fl_Wizard_H_

#  include <FL/Fl_Group.H>


/**
    This widget is based off the Fl_Tabs
    widget, but instead of displaying tabs it only changes "tabs" under
    program control. Its primary purpose is to support "wizards" that
    step a user through configuration or troubleshooting tasks.

    <P>As with Fl_Tabs, wizard panes are composed of child (usually
    Fl_Group) widgets. Navigation buttons must be added separately.
*/
class FL_EXPORT Fl_Wizard : public Fl_Group
{
  Fl_Widget *value_;

  void draw();

  public:

  Fl_Wizard(int, int, int, int, const char * = 0);

  void		next();
  void		prev();
  Fl_Widget	*value();
  void		value(Fl_Widget *);
};

#endif // !_Fl_Wizard_H_

//
// End of "$Id: Fl_Wizard.H 6614 2009-01-01 16:11:32Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::WizardGroup
class Fl_Wizard : public fltk::WizardGroup {
public:
  Fl_Wizard(int x, int t, int w, int h, const char *label=0)
  : fltk::WizardGroup(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Wizard.H 6614 2009-01-01 16:11:32Z matt $"
//
// Fl_Wizard widget definitions.
//
// Copyright 1999-2009 by Easy Software Products.
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
   Fl_Wizard widget . */

//
// Include necessary header files...
//

#ifndef _Fl_Wizard_H_
#  define _Fl_Wizard_H_

#  include <FL/Fl_Group.H>


/**
    This widget is based off the Fl_Tabs
    widget, but instead of displaying tabs it only changes "tabs" under
    program control. Its primary purpose is to support "wizards" that
    step a user through configuration or troubleshooting tasks.

    <P>As with Fl_Tabs, wizard panes are composed of child (usually
    Fl_Group) widgets. Navigation buttons must be added separately.
*/
class FL_EXPORT Fl_Wizard : public Fl_Group
{
  Fl_Widget *value_;

  void draw();

  public:

  Fl_Wizard(int, int, int, int, const char * = 0);

  void		next();
  void		prev();
  Fl_Widget	*value();
  void		value(Fl_Widget *);
};

#endif // !_Fl_Wizard_H_

//
// End of "$Id: Fl_Wizard.H 6614 2009-01-01 16:11:32Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id: WizardGroup.h 4288 2005-04-16 00:13:17Z mike $"
//
// WizardGroup widget definitions.
//
// Copyright 1999-2006 by Easy Software Products and others.
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

//
// Include necessary header files...
//

#ifndef _fltk_WizardGroup_h_
#define _fltk_WizardGroup_h_

#include "Group.h"

namespace fltk {

class FL_API WizardGroup : public Group {
  Widget * value_;
public:
  WizardGroup(int x,int y,int w,int h, const char * l = 0, bool begin=false)
    : Group(x,y,w,h,l,begin), value_(0) {  box(THIN_UP_BOX);}

  void          draw(); 
  void		next();
  void		prev();
  void		value(Widget *);
  //! return  the current visible child.
  Widget *      value() const { return value_;}
};

}

#endif

//
// End of "$Id: WizardGroup.h 4288 2005-04-16 00:13:17Z mike $".
//
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
