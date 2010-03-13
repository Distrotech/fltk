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
// "$Id: Fl_Tabs.H 6614 2009-01-01 16:11:32Z matt $"
//
// Tab header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Tabs widget . */

#ifndef Fl_Tabs_H
#define Fl_Tabs_H

#include "Group.h"

/**
  The Fl_Tabs widget is the "file card tabs"
  interface that allows you to put lots and lots of buttons and
  switches in a panel, as popularized by many toolkits.
  
  \image html  tabs.gif
  \image latex tabs.eps "Fl_Tabs" width=8cm
  
  Clicking the tab makes a child visible() by calling
  show() on it, and all other children are made invisible
  by calling hide() on them. Usually the children are Fl_Group widgets
  containing several widgets themselves.
  
  Each child makes a card, and its label() is printed
  on the card tab, including the label font and style.  The
  selection color of that child is used to color the tab, while
  the color of the child determines the background color of the pane.
  
  The size of the tabs is controlled by the bounding box of the
  children (there should be some space between the children and
  the edge of the Fl_Tabs), and the tabs may be placed
  "inverted" on the bottom - this is determined by which
  gap is larger. It is easiest to lay this out in fluid, using the
  fluid browser to select each child group and resize them until
  the tabs look the way you want them to.
*/
class FL_EXPORT Fl_Tabs : public Fl_Group {
  Fl_Widget *value_;
  Fl_Widget *push_;
  int tab_positions(int*, int*);
  int tab_height();
  void draw_tab(int x1, int x2, int W, int H, Fl_Widget* o, int sel=0);
protected:
  void redraw_tabs();
  void draw();

public:
  int handle(int);
  Fl_Widget *value();
  int value(Fl_Widget *);
  Fl_Widget *push() const {return push_;}
  int push(Fl_Widget *);
  Fl_Tabs(int,int,int,int,const char * = 0);
  Fl_Widget *which(int event_x, int event_y);
};

#endif

//
// End of "$Id: Fl_Tabs.H 6614 2009-01-01 16:11:32Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::TabGroup
class Fl_Tabs : public fltk::TabGroup {
public:
  Fl_Tabs(int x, int t, int w, int h, const char *label=0)
  : fltk::TabGroup(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Tabs.H 6614 2009-01-01 16:11:32Z matt $"
//
// Tab header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Tabs widget . */

#ifndef Fl_Tabs_H
#define Fl_Tabs_H

#include "Fl_Group.H"

/**
  The Fl_Tabs widget is the "file card tabs"
  interface that allows you to put lots and lots of buttons and
  switches in a panel, as popularized by many toolkits.
  
  \image html  tabs.gif
  \image latex tabs.eps "Fl_Tabs" width=8cm
  
  Clicking the tab makes a child visible() by calling
  show() on it, and all other children are made invisible
  by calling hide() on them. Usually the children are Fl_Group widgets
  containing several widgets themselves.
  
  Each child makes a card, and its label() is printed
  on the card tab, including the label font and style.  The
  selection color of that child is used to color the tab, while
  the color of the child determines the background color of the pane.
  
  The size of the tabs is controlled by the bounding box of the
  children (there should be some space between the children and
  the edge of the Fl_Tabs), and the tabs may be placed
  "inverted" on the bottom - this is determined by which
  gap is larger. It is easiest to lay this out in fluid, using the
  fluid browser to select each child group and resize them until
  the tabs look the way you want them to.
*/
class FL_EXPORT Fl_Tabs : public Fl_Group {
  Fl_Widget *value_;
  Fl_Widget *push_;
  int tab_positions(int*, int*);
  int tab_height();
  void draw_tab(int x1, int x2, int W, int H, Fl_Widget* o, int sel=0);
protected:
  void redraw_tabs();
  void draw();

public:
  int handle(int);
  Fl_Widget *value();
  int value(Fl_Widget *);
  Fl_Widget *push() const {return push_;}
  int push(Fl_Widget *);
  Fl_Tabs(int,int,int,int,const char * = 0);
  Fl_Widget *which(int event_x, int event_y);
};

#endif

//
// End of "$Id: Fl_Tabs.H 6614 2009-01-01 16:11:32Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id: TabGroup.h 5575 2007-01-02 17:31:40Z spitzak $"
//
// For making a "tabbed dialog box". Each child widget creates a tab.
// Only one is visible at a time. This works best if all the children
// have the same size and they don't cover a strip at the top for the
// tabs.
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

#ifndef fltk_TabGroup_h
#define fltk_TabGroup_h

#include "Group.h"

#define MIN_TABSIZE 30

namespace fltk {

class TabGroup;


enum {TAB_LEFT, TAB_RIGHT, TAB_SELECTED};

class FL_API TabGroupPager {
public:

    TabGroupPager() : shift_(0), border_(10), slope_(5), extra_space_(5),_noclip(false) {}
    
    /* Pager template methods definition */

    /*! this method must update the tab positions and width array, returns the selected tab    */
    virtual int update_positions(TabGroup* g, int numchildren, int& selected, 
	int& cumulated_width, int& available_width , int* tab_pos, int* tab_width) { return selected;}
    /*! draw the tabs for this custom pager, return false means no custom draw is made */
    virtual bool draw_tabs(TabGroup* g, int selected, int* tab_pos, int* tab_width) { return false;}
    /*! determine and return the index of the child group at the corresponding pos */
    virtual int which(TabGroup* g, int m_x,int m_y)=0;
    /*! virtual copy from a prototype */
    virtual TabGroupPager* clone() const=0;

    virtual const char * mode_name() const = 0;
    virtual int id() const = 0;

    /*! return max width available for drawing tab thumbnails */
    virtual int available_width(TabGroup *g ) const;

    // tab appearance
    int  border()	const {return border_;}
    int  slope()		const {return slope_;}
    int  extra_space()	const {return extra_space_;}
    void border(int v)	{border_=v;}
    void slope(int v)	{slope_=v;}
    void extra_space(int v) {extra_space_=v;}
    
    /*! shifting to nth+1 tab to draw, permit to 'keep' a position while 
	changing tabs and tab is in the interval
    */
    int  shift()	const {return shift_;}
    void shift(int v)	{shift_=v;}
    int spacing()	const {return slope_+extra_space_;}
    /*! determines if we forbid partial tabs drawing with clipping */
    void noclip(bool v) {_noclip=v;}
  
private:
    int shift_, border_, slope_, extra_space_;
    bool _noclip; 
  
};

// fltk default factory pagers
const int PAGER_MENU   = 0; //<-- two left and right buttons  provide prev page  and next page 
const int PAGER_SHRINK = 1; //<-- tabs outside rect are shrinked to very small slice to fit


class FL_API TabGroup : public Group {

public:
  int handle(int);

  TabGroup(int,int,int,int,const char * = 0, bool begin=false);
  ~TabGroup() {delete pager_;}
  static NamedStyle* default_style;

  int value() const;
  bool value(int);
  int which(int event_x, int event_y);
  Widget *selected_child();
  bool selected_child(Widget *);
  void set_draw_outline( bool draw_outline );
  
  //! setting the pager_ to a tabgroup, pager is _never_ null by design
  void pager(TabGroupPager * value);
  //! returning the current pager_ responsible of this instance
  TabGroupPager * pager() const {return pager_;}
  //! setting the default pager_ for future tabgroups, a default pager is _never_ null by design
  static void default_pager(TabGroupPager * v);
  //! setting the default pager_ from the built-in ones
  static void default_pager(int factory_pager_index);

  int tab_height();
  int tab_positions(int*, int*);

  void draw_tab(int x1, int x2, int W, int H, Widget* o, int sel=0);
  void draw_tab_background();

protected:
  void draw();

private:
  int push(Widget *);
  bool _drawOutline;
  TabGroupPager* pager_;
  static TabGroupPager* default_pager_;
};

}

#endif

//
// End of "$Id: TabGroup.h 5575 2007-01-02 17:31:40Z spitzak $".
//
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
