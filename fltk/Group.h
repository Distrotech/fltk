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

#ifndef fltk2_Group_h
#define fltk2_Group_h

#include <fltk3/Group.h>
#include "Widget.h"

namespace fltk {

class FL_API Group : public Widget {
public:
  
  Group() {}
  Group(int x, int y, int w, int h, const char *l = 0, bool aBegin=false) {
    fltk3::Group *curr = fltk3::Group::current();
    _p = new fltk3::Group(x, y, w, h, l);
    _p->wrapper(this);
    if (aBegin)
      begin();
    else 
      fltk3::Group::current(curr);
  }
  void begin() { 
    ((fltk3::Group*)_p)->begin(); 
  }
  void end() { 
    ((fltk3::Group*)_p)->end(); 
  }
  void resizable(Widget* o) {
    ((fltk3::Group*)_p)->resizable( (fltk3::Widget*)(o->_p) ); 
  }
  void resizable(Widget& o) {
    resizable(&o);
  }
  
#if 0 // TODO: FLTK123  
  int children() const {return children_;}
  Widget* child(int n) const {return array_[n];}
  void draw();
  void layout();
  int handle(int);
  static Group *current() {return current_;}
  static void current(Group *g) {current_ = g;}
  int find(const Widget*) const;
  int find(const Widget& o) const {return find(&o);}
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
#endif // TODO: FLTK123
};

}

#endif

//
// End of "$Id: Group.h 5915 2007-06-19 17:49:29Z spitzak $".
//
