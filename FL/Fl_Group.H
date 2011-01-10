//
// "$Id$"
//
// Group header file for the Fast Light Tool Kit (FLTK).
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

#ifndef FLTK1_Group_H
#define FLTK1_Group_H

#include <fltk3/Group.h>
#include "Fl_Widget.H"


class FL_EXPORT Fl_Group : public Fl_Widget {

protected:
  Fl_Group() {
  }
  void draw_child(Fl_Widget& widget) const {
    fltk3::Widget *w3 = (fltk3::Widget*)widget._p;
    ((fltk3::Group*)_p)->draw_child(*w3);
  }
  void draw_children() {
    ((fltk3::Group*)_p)->draw_children(); 
  }
  void draw_outside_label(const Fl_Widget& widget) const {
    fltk3::Widget *w3 = (fltk3::Widget*)widget._p;
    ((fltk3::Group*)_p)->draw_outside_label(*w3);
  }
  void update_child(Fl_Widget& widget) const {
    fltk3::Widget *w3 = (fltk3::Widget*)widget._p;
    ((fltk3::Group*)_p)->update_child(*w3);
  }
  int *sizes() {
    return ((fltk3::Group*)_p)->sizes(); 
  }
  
public:

  // in Wrapper: void draw();
  // in Wrapper: int handle(int);
  // in Wrapper: void resize(int,int,int,int);
  // in Wrapper: virtual ~Fl_Group();
  virtual Fl_Group* as_group() { 
    return this; 
  }
  void begin() { 
    ((fltk3::Group*)_p)->begin(); 
  }
  void end() { 
    ((fltk3::Group*)_p)->end(); 
  }
  static Fl_Group *current() {
    return (Fl_Group*)( fltk3::Group::current()->wrapper() );
  }
  static void current(Fl_Group *g) {
    fltk3::Group::current( (fltk3::Group*)( ((Fl_Widget*)g)->_p ) );
  }
  int children() const {
    return ((fltk3::Group*)_p)->children(); 
  }
  Fl_Widget* child(int n) const {
    return (Fl_Widget*)( ((fltk3::Group*)_p)->child(n)->wrapper() );
  }
  int find(const Fl_Widget *g) const {
    return ((fltk3::Group*)_p)->find( ( (fltk3::Widget*)((Fl_Widget*)g)->_p ) );
  }
  int find(const Fl_Widget& o) const {
    return find(&o);
  }
  // TODO: Fl_Widget* const* array() const;  
  Fl_Group(int x, int y, int w, int h, const char *l = 0) {
    _p = new fltk3::Group(x, y, w, h, l);
    _p->wrapper(this);
  }
  void add(Fl_Widget &w) {
    add(&w);
  }
  void add(Fl_Widget* o) {
    ((fltk3::Group*)_p)->add( ( (fltk3::Widget*)((Fl_Widget*)o)->_p ) );
  }
  void insert(Fl_Widget &widget, int i) { 
    fltk3::Widget *w3 = (fltk3::Widget*)widget._p;
    ((fltk3::Group*)_p)->insert(*w3, i);
  }
  void insert(Fl_Widget& o, Fl_Widget* before) {
    fltk3::Widget *w3 = (fltk3::Widget*)o._p;
    ((fltk3::Group*)_p)->insert(*w3, (fltk3::Widget*)((Fl_Widget*)before)->_p);
  }
  void remove(int index) {
    ((fltk3::Group*)_p)->remove(index); 
  }
  void remove(Fl_Widget &w) {
    remove(&w);
  }
  void remove(Fl_Widget* o) {
    ((fltk3::Group*)_p)->remove( ( (fltk3::Widget*)((Fl_Widget*)o)->_p ) );
  }
  void clear() {
    ((fltk3::Group*)_p)->clear(); 
  }
  void resizable(Fl_Widget& o) {
    resizable(&o);
  }
  void resizable(Fl_Widget* o) { 
    ((fltk3::Group*)_p)->resizable( (fltk3::Widget*)(o->_p) ); 
  }  
  Fl_Widget* resizable() const {
    return (Fl_Widget*)( ((fltk3::Group*)_p)->resizable()->wrapper() );
  }
  void add_resizable(Fl_Widget& o) {
    fltk3::Widget *w3 = (fltk3::Widget*)o._p;
    ((fltk3::Group*)_p)->add_resizable(*w3);
  }
  void init_sizes() {
    ((fltk3::Group*)_p)->init_sizes(); 
  }
  void clip_children(int c) {
    ((fltk3::Group*)_p)->clip_children(c); 
  }
  unsigned int clip_children() {
    return ((fltk3::Group*)_p)->clip_children(); 
  }
  void focus(Fl_Widget* W) {
    ((fltk3::Group*)_p)->focus( ( (fltk3::Widget*)((Fl_Widget*)W)->_p ) );
  }
  // TODO: Fl_Widget* & _ddfdesign_kludge() {return resizable_;}
  void forms_end() {
    ((fltk3::Group*)_p)->forms_end(); 
  }  
};

#if 0 // TODO: FLTK123

class FL_EXPORT Fl_End {
public:
  Fl_End() {Fl_Group::current()->end();}
};

#endif // TODO: FLTK123

#endif

//
// End of "$Id$".
//
