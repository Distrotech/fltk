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
// "$Id: Fl_Group.H 7074 2010-02-13 12:25:58Z AlbrechtS $"
//
// Group header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Group, Fl_End classes . */

#ifndef Fl_Group_H
#define Fl_Group_H

#ifndef Fl_Widget_H
#include "Widget.h"
#endif

/**
  The Fl_Group class is the FLTK container widget. It maintains
  an array of child widgets. These children can themselves be any widget
  including Fl_Group. The most important subclass of Fl_Group
  is fltk::Window, however groups can also be used to control radio buttons 
  or to enforce resize behavior.
*/
class FL_EXPORT Fl_Group : public Fl_Widget {

  Fl_Widget** array_;
  Fl_Widget* savedfocus_;
  Fl_Widget* resizable_;
  int children_;
  int *sizes_; // remembered initial sizes of children

  int navigation(int);
  static Fl_Group *current_;
 
  // unimplemented copy ctor and assignment operator
  Fl_Group(const Fl_Group&);
  Fl_Group& operator=(const Fl_Group&);

protected:
  void draw();
  void draw_child(Fl_Widget& widget) const;
  void draw_children();
  void draw_outside_label(const Fl_Widget& widget) const ;
  void update_child(Fl_Widget& widget) const;
  int  *sizes();

public:

  int handle(int);
  void begin();
  void end();
  static Fl_Group *current();
  static void current(Fl_Group *g);

  /**
    Returns how many child widgets the group has.
  */
  int children() const {return children_;}
  /**
    Returns array()[n].  <i>No range checking is done!</i>
  */
  Fl_Widget* child(int n) const {return array()[n];}
  int find(const Fl_Widget*) const;
  /**
    See int Fl_Group::find(const Fl_Widget *w) const 
  */
  int find(const Fl_Widget& o) const {return find(&o);}
  Fl_Widget* const* array() const;

  void resize(int,int,int,int);
  /**
    Creates a new Fl_Group widget using the given position, size,
    and label string. The default boxtype is FL_NO_BOX.
  */
  Fl_Group(int,int,int,int, const char * = 0);
  virtual ~Fl_Group();
  void add(Fl_Widget&);
  /**
    See void Fl_Group::add(Fl_Widget &w) 
  */
  void add(Fl_Widget* o) {add(*o);}
  void insert(Fl_Widget&, int i);
  /**
    This does insert(w, find(before)).  This will append the
    widget if \p before is not in the group.
  */
  void insert(Fl_Widget& o, Fl_Widget* before) {insert(o,find(before));}
  void remove(Fl_Widget&);
  /**
    Removes the widget \p o from the group.
    \sa void remove(Fl_Widget&)
  */
  void remove(Fl_Widget* o) {remove(*o);}
  void clear();

  /**
    See void Fl_Group::resizable(Fl_Widget *box) 
  */
  void resizable(Fl_Widget& o) {resizable_ = &o;}
  /**
    The resizable widget defines the resizing box for the group. When the
    group is resized it calculates a new size and position for all of its
    children. Widgets that are horizontally or vertically inside the
    dimensions of the box are scaled to the new size. Widgets outside the
    box are moved.

    In these examples the gray area is the resizable:

    \image html resizebox1.gif
    
    \image html resizebox2.gif
    
    \image latex resizebox1.eps "before resize"  width=4cm
    
    \image latex resizebox2.eps "after resize"   width=4cm

    The resizable may be set to the group itself, in which case all the
    contents are resized. This is the default value for Fl_Group,
    although NULL is the default for fltk::Window and Fl_Pack.

    If the resizable is NULL then all widgets remain a fixed size
    and distance from the top-left corner.

    It is possible to achieve any type of resize behavior by using an
    invisible Fl_Box as the resizable and/or by using a hierarchy
    of child Fl_Group's.
  */
  void resizable(Fl_Widget* o) {resizable_ = o;}
  /**
    See void Fl_Group::resizable(Fl_Widget *box) 
  */
  Fl_Widget* resizable() const {return resizable_;}
  /**
    Adds a widget to the group and makes it the resizable widget.
  */
  void add_resizable(Fl_Widget& o) {resizable_ = &o; add(o);}
  void init_sizes();

  /**
    Controls whether the group widget clips the drawing of
    child widgets to its bounding box.
    
    Set \p c to 1 if you want to clip the child widgets to the
    bounding box.

    The default is to not clip (0) the drawing of child widgets.
  */
  void clip_children(int c) { if (c) set_flag(CLIP_CHILDREN); else clear_flag(CLIP_CHILDREN); }
  /**
    Returns the current clipping mode.

    \return true, if clipping is enabled, false otherwise.

    \see void Fl_Group::clip_children(int c)
  */
  unsigned int clip_children() { return (flags() & CLIP_CHILDREN) != 0; }

  /** Returns an Fl_Group pointer if this widget is an Fl_Group.
  
      \retval NULL if this widget is not derived from Fl_Group.
      \note This method is provided to avoid dynamic_cast.
      \todo More documentation ...
   */
  virtual Fl_Group* as_group() const { return (Fl_Group*)this; }

  // back compatibility functions:

  /**
    \deprecated This is for backwards compatibility only. You should use
    \e W->%take_focus() instead.
    \sa Fl_Widget::take_focus();
  */
  void focus(Fl_Widget* W) {W->take_focus();}

  /** This is for forms compatibility only */
  Fl_Widget* & _ddfdesign_kludge() {return resizable_;}

  /** This is for forms compatibility only */
  void forms_end();
};

// dummy class used to end child groups in constructors for complex
// subclasses of Fl_Group:
/**
  This is a dummy class that allows you to end a Fl_Group in a constructor list of a
  class:
  \code 
   class MyClass {
   Fl_Group group;
   Fl_Button button_in_group;
   Fl_End end;
   Fl_Button button_outside_group;
   MyClass();
  };
  MyClass::MyClass() :
   group(10,10,100,100),
   button_in_group(20,20,60,30),
   end(),
   button_outside_group(10,120,60,30)
  {} 
  \endcode
*/
class FL_EXPORT Fl_End {
public:
  /** All it does is calling Fl_Group::current()->end() */
  Fl_End() {Fl_Group::current()->end();}
};

#endif

//
// End of "$Id: Fl_Group.H 7074 2010-02-13 12:25:58Z AlbrechtS $".
//

/* suggested twin class
// This is the Twin Class to fltk::Group
class Fl_Group : public fltk::Group {
public:
  Fl_Group(int x, int t, int w, int h, const char *label=0)
  : fltk::Group(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Group.H 7074 2010-02-13 12:25:58Z AlbrechtS $"
//
// Group header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Group, Fl_End classes . */

#ifndef Fl_Group_H
#define Fl_Group_H

#ifndef Fl_Widget_H
#include "Fl_Widget.H"
#endif

/**
  The Fl_Group class is the FLTK container widget. It maintains
  an array of child widgets. These children can themselves be any widget
  including Fl_Group. The most important subclass of Fl_Group
  is Fl_Window, however groups can also be used to control radio buttons 
  or to enforce resize behavior.
*/
class FL_EXPORT Fl_Group : public Fl_Widget {

  Fl_Widget** array_;
  Fl_Widget* savedfocus_;
  Fl_Widget* resizable_;
  int children_;
  int *sizes_; // remembered initial sizes of children

  int navigation(int);
  static Fl_Group *current_;
 
  // unimplemented copy ctor and assignment operator
  Fl_Group(const Fl_Group&);
  Fl_Group& operator=(const Fl_Group&);

protected:
  void draw();
  void draw_child(Fl_Widget& widget) const;
  void draw_children();
  void draw_outside_label(const Fl_Widget& widget) const ;
  void update_child(Fl_Widget& widget) const;
  int  *sizes();

public:

  int handle(int);
  void begin();
  void end();
  static Fl_Group *current();
  static void current(Fl_Group *g);

  /**
    Returns how many child widgets the group has.
  */
  int children() const {return children_;}
  /**
    Returns array()[n].  <i>No range checking is done!</i>
  */
  Fl_Widget* child(int n) const {return array()[n];}
  int find(const Fl_Widget*) const;
  /**
    See int Fl_Group::find(const Fl_Widget *w) const 
  */
  int find(const Fl_Widget& o) const {return find(&o);}
  Fl_Widget* const* array() const;

  void resize(int,int,int,int);
  /**
    Creates a new Fl_Group widget using the given position, size,
    and label string. The default boxtype is FL_NO_BOX.
  */
  Fl_Group(int,int,int,int, const char * = 0);
  virtual ~Fl_Group();
  void add(Fl_Widget&);
  /**
    See void Fl_Group::add(Fl_Widget &w) 
  */
  void add(Fl_Widget* o) {add(*o);}
  void insert(Fl_Widget&, int i);
  /**
    This does insert(w, find(before)).  This will append the
    widget if \p before is not in the group.
  */
  void insert(Fl_Widget& o, Fl_Widget* before) {insert(o,find(before));}
  void remove(Fl_Widget&);
  /**
    Removes the widget \p o from the group.
    \sa void remove(Fl_Widget&)
  */
  void remove(Fl_Widget* o) {remove(*o);}
  void clear();

  /**
    See void Fl_Group::resizable(Fl_Widget *box) 
  */
  void resizable(Fl_Widget& o) {resizable_ = &o;}
  /**
    The resizable widget defines the resizing box for the group. When the
    group is resized it calculates a new size and position for all of its
    children. Widgets that are horizontally or vertically inside the
    dimensions of the box are scaled to the new size. Widgets outside the
    box are moved.

    In these examples the gray area is the resizable:

    \image html resizebox1.gif
    
    \image html resizebox2.gif
    
    \image latex resizebox1.eps "before resize"  width=4cm
    
    \image latex resizebox2.eps "after resize"   width=4cm

    The resizable may be set to the group itself, in which case all the
    contents are resized. This is the default value for Fl_Group,
    although NULL is the default for Fl_Window and Fl_Pack.

    If the resizable is NULL then all widgets remain a fixed size
    and distance from the top-left corner.

    It is possible to achieve any type of resize behavior by using an
    invisible Fl_Box as the resizable and/or by using a hierarchy
    of child Fl_Group's.
  */
  void resizable(Fl_Widget* o) {resizable_ = o;}
  /**
    See void Fl_Group::resizable(Fl_Widget *box) 
  */
  Fl_Widget* resizable() const {return resizable_;}
  /**
    Adds a widget to the group and makes it the resizable widget.
  */
  void add_resizable(Fl_Widget& o) {resizable_ = &o; add(o);}
  void init_sizes();

  /**
    Controls whether the group widget clips the drawing of
    child widgets to its bounding box.
    
    Set \p c to 1 if you want to clip the child widgets to the
    bounding box.

    The default is to not clip (0) the drawing of child widgets.
  */
  void clip_children(int c) { if (c) set_flag(CLIP_CHILDREN); else clear_flag(CLIP_CHILDREN); }
  /**
    Returns the current clipping mode.

    \return true, if clipping is enabled, false otherwise.

    \see void Fl_Group::clip_children(int c)
  */
  unsigned int clip_children() { return (flags() & CLIP_CHILDREN) != 0; }

  /** Returns an Fl_Group pointer if this widget is an Fl_Group.
  
      \retval NULL if this widget is not derived from Fl_Group.
      \note This method is provided to avoid dynamic_cast.
      \todo More documentation ...
   */
  virtual Fl_Group* as_group() const { return (Fl_Group*)this; }

  // back compatibility functions:

  /**
    \deprecated This is for backwards compatibility only. You should use
    \e W->%take_focus() instead.
    \sa Fl_Widget::take_focus();
  */
  void focus(Fl_Widget* W) {W->take_focus();}

  /** This is for forms compatibility only */
  Fl_Widget* & _ddfdesign_kludge() {return resizable_;}

  /** This is for forms compatibility only */
  void forms_end();
};

// dummy class used to end child groups in constructors for complex
// subclasses of Fl_Group:
/**
  This is a dummy class that allows you to end a Fl_Group in a constructor list of a
  class:
  \code 
   class MyClass {
   Fl_Group group;
   Fl_Button button_in_group;
   Fl_End end;
   Fl_Button button_outside_group;
   MyClass();
  };
  MyClass::MyClass() :
   group(10,10,100,100),
   button_in_group(20,20,60,30),
   end(),
   button_outside_group(10,120,60,30)
  {} 
  \endcode
*/
class FL_EXPORT Fl_End {
public:
  /** All it does is calling Fl_Group::current()->end() */
  Fl_End() {Fl_Group::current()->end();}
};

#endif

//
// End of "$Id: Fl_Group.H 7074 2010-02-13 12:25:58Z AlbrechtS $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id: Group.h 5915 2007-06-19 17:49:29Z spitzak $"
//
// Group is the base class for all container widgets. For historical
// reasons it also provides a default version of layout.
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

#ifndef fltk_Group_h
#define fltk_Group_h

#ifndef fltk_Widget_h
# include "Widget.h"
#endif

namespace fltk {

class FL_API Group : public Widget {
public:

  int children() const {return children_;}
  Widget* child(int n) const {return array_[n];}

  void draw();
  void layout();
  int handle(int);

  void begin() {current_ = this;}
  void end() {current_ = (Group*)parent();}
  static Group *current() {return current_;}
  static void current(Group *g) {current_ = g;}

  int find(const Widget*) const;
  int find(const Widget& o) const {return find(&o);}

  Group(int,int,int,int, const char * = 0, bool begin=false);
  virtual ~Group();
  void add(Widget&);
  void add(Widget* o) {add(*o);}
  void insert(Widget&, int index);
  void insert(Widget& o, Widget* before) {insert(o,find(before));}
  void remove(int index);
  void remove(Widget& o) {remove(find(o));}
  void remove(Widget* o) {remove(find(*o));}
  void remove_all();
  void replace(int index, Widget&);
  void replace(Widget& old, Widget& o) {replace(find(old),o);}
  void swap(int indexA, int indexB);
  void clear();

  void resizable(Widget& o) {resizable_ = &o;}
  void resizable(Widget* o) {resizable_ = o;}
  Widget* resizable() const {return resizable_;}
  void add_resizable(Widget& o) {resizable_ = &o; add(o);}
  void init_sizes();

  void focus_index(int v) {focus_index_ = v;}
  void set_focus(Widget* w) {focus_index_ = find(w);}
  int  focus_index() const {return focus_index_;}
  static int navigation_key();

  // back compatability function:
  friend FL_FORMS_API void end_group(); // forms emulation function
  void fix_old_positions();

  Flags resize_align() const {return resize_align_;}
  void resize_align(Flags f) {resize_align_ = f;}

protected:

  void draw_child(Widget&) const;
  void update_child(Widget&) const;
  void draw_outside_label(Widget&) const ;
  int initial_w, initial_h;
  int* sizes();
  void layout(const Rectangle&, int layout_damage);

private:

  int children_;
  int focus_index_;
  Widget** array_;
  Widget* resizable_;
  Flags resize_align_;
  int *sizes_; // remembered initial sizes of children

  static Group *current_;

};

}

#endif

//
// End of "$Id: Group.h 5915 2007-06-19 17:49:29Z spitzak $".
//
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
