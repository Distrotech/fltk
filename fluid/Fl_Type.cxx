//
// "$Id: Fl_Type.cxx,v 1.20 2000/08/21 03:56:24 spitzak Exp $"
//
// Widget type code for the Fast Light Tool Kit (FLTK).
//
// Each object described by Fluid is one of these objects.  They
// are all stored in a double-linked list.
//
// They "type" of the object is covered by the virtual functions.
// There will probably be a lot of these virtual functions.
//
// The type browser is also a list of these objects, but they
// are "factory" instances, not "real" ones.  These objects exist
// only so the "make" method can be called on them.  They are
// not in the linked list and are not written to files or
// copied or otherwise examined.
//
// Copyright 1998-1999 by Bill Spitzak and others.
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
// Please report all bugs and problems to "fltk-bugs@easysw.com".
//

#include <FL/Fl.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Item.H>
#include <FL/fl_draw.H>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Fl_Type.h"
#include "Fluid_Image.h"

////////////////////////////////////////////////////////////////

Fl_Type *Fl_Type::first;
Fl_Type *Fl_Type::last;

class Widget_List : public Fl_List {
  virtual int children(const Fl_Group*, int* indexes, int level);
  virtual Fl_Widget* child(const Fl_Group*, int* indexes, int level);
  virtual void value_changed(const Fl_Group*, Fl_Widget*);
};

static Widget_List widgetlist;

static Fl_Browser *widget_browser;

static void Widget_Browser_callback(Fl_Widget *,void *w) {
  if (w && Fl::event_clicks())
    ((Fl_Type*)w)->open();
}

Fl_Widget *make_widget_browser(int x,int y,int w,int h) {
  widget_browser = new Fl_Browser(x,y,w,h);
  widget_browser->type(FL_MULTI_BROWSER);
  widget_browser->end();
  widget_browser->list(&widgetlist);
  widget_browser->callback(Widget_Browser_callback);
  widget_browser->indented(1);
  return widget_browser;
}

int Widget_List::children(const Fl_Group*, int* indexes, int level) {
  Fl_Type* item = Fl_Type::first;
  if (!item) return 0;
  for (int l = 0; l < level; l++) {
    int i = indexes[l];
    for (;;) {
      if (!item || item->level < l) return -1;
      if (item->level == l) {if (!i) break; --i;}
      item = item->next;
    }
    if (!item->is_parent()) return -1;
    item = item->next;
  }
  int n = 0;
  while (item && item->level >= level) {
    if (item->level == level) n++;
    item = item->next;
  }
  return n;
}

Fl_Widget* Widget_List::child(const Fl_Group*, int* indexes, int level) {
  Fl_Type* item = Fl_Type::first;
  if (!item) return 0;
  for (int l = 0;; l++) {
    int i = indexes[l];
    for (;;) {
      if (!item || item->level < l) return 0;
      if (item->level == l) {if (!i) break; --i;}
      item = item->next;
    }
    if (l >= level) break;
    item = item->next;
  }
  static Fl_Widget* widget;
  if (!widget) {
    Fl_Group::current(0);
    widget = new Fl_Item();
  }
  widget->user_data(item);
  widget->type(item->is_parent() ? FL_GROUP : 0);
  if (item->new_selected) widget->set_flag(FL_VALUE);
  else widget->clear_flag(FL_VALUE);
  if (item->open_) widget->set_flag(FL_OPEN);
  else widget->clear_flag(FL_OPEN);
  widget->label(item->title());
  widget->w(0);

  return widget;
}

void Widget_List::value_changed(const Fl_Group*, Fl_Widget* w) {
  Fl_Type* item = (Fl_Type*)(w->user_data());
  item->open_ = w->flags()&FL_OPEN ? 1 : 0;
  int i = w->flags()&FL_VALUE ? 1 : 0;
  if (i != item->new_selected) {
    item->new_selected = i;
    selection_changed(item);
  }
}

void select(Fl_Type* item, int value) {
  if (value != item->new_selected) {
    item->new_selected = value;
    selection_changed(item);
    widget_browser->redraw();
  }
}

void select_only(Fl_Type* i) {
  Fl_Type* item = Fl_Type::first;
  while (item) {select(item, item==i); item = item->next;}
}

void deselect() {
  Fl_Type* item = Fl_Type::first;
  while (item) {select(item,0); item = item->next;}
  Fl_Type::current = 0; // this breaks the paste & merge functions
}

// Generate a descriptive text for this item, to put in browser & window titles
const char* Fl_Type::title() {
  const char* c = name(); if (c) return c;
  return type_name();
}

#if 0
extern const char* subclassname(Fl_Type*);

void Widget_Browser::item_draw(void *v, int x, int y, int, int h) const {
  Fl_Type *l = (Fl_Type *)v;
  x += 3 + l->level * 10;
  fl_color(item_selected(v) ? selection_text_color() : text_color());
  if (l->is_parent()) {
    int dy = (h-11)/2;
    if (!l->next || l->next->level <= l->level) {
      if (l->open_!=(l==pushedtitle)) {
	fl_loop(x,y+dy+5,x+5,y+dy+10,x+10,y+dy+5);
      } else {
	fl_loop(x+2,y+dy,x+7,y+dy+5,x+2,y+dy+10);
      }
    } else {
      if (l->open_!=(l==pushedtitle)) {
	fl_polygon(x,y+dy+5,x+5,y+dy+10,x+10,y+dy+5);
      } else {
	fl_polygon(x+2,y+dy,x+7,y+dy+5,x+2,y+dy+10);
      }
    }
    x += 10;
  }
  if (l->is_widget() || l->is_class()) {
    const char* c = subclassname(l);
    if (!strncmp(c,"Fl_",3)) c += 3;
    fl_font(text_font(), text_size());
    fl_draw(c, x, y+h-fl_descent());
    x += int(fl_width(c)+fl_width('n'));
    c = l->name();
    if (c) {
      fl_font(text_font()->bold(), text_size());
      fl_draw(c, x, y+h-fl_descent());
    } else if ((c=l->label())) {
      char buf[50]; char* p = buf;
      *p++ = '"';
      for (int i = 20; i--;) {
	if (! (*c & -32)) break;
	*p++ = *c++;
      }
      if (*c) {strcpy(p,"..."); p+=3;}
      *p++ = '"';
      *p = 0;
      fl_draw(buf, x, y+h-fl_descent());
    }
  } else {
    const char* c = l->title();
    char buf[60]; char* p = buf;
    for (int i = 55; i--;) {
      if (! (*c & -32)) break;
      *p++ = *c++;
    }
    if (*c) {strcpy(p,"..."); p+=3;}
    *p = 0;
    fl_font(l->is_code_block() && (l->level==0 || l->parent->is_class())
	     ? text_font() : text_font()->bold(), text_size());
    fl_draw(buf, x, y+h-fl_descent());
  }
}

int Widget_Browser::item_width(void *v) const {
  Fl_Type *l = (Fl_Type *)v;

  int w = 3 + l->level*10;
  if (l->is_parent()) w += 10;

  if (l->is_widget() || l->is_class()) {
    const char* c = l->type_name();
    if (!strncmp(c,"Fl_",3)) c += 3;
    fl_font(text_font(), text_size());
    w += int(fl_width(c) + fl_width('n'));
    c = l->name();
    if (c) {
      fl_font(text_font()->bold(), text_size());
      w += int(fl_width(c));
    } else if ((c=l->label())) {
      char buf[50]; char* p = buf;
      *p++ = '"';
      for (int i = 20; i--;) {
	if (! (*c & -32)) break;
	*p++ = *c++;
      }
      if (*c) {strcpy(p,"..."); p+=3;}
      *p++ = '"';
      *p = 0;
      w += int(fl_width(buf));
    }
  } else {
    const char* c = l->title();
    char buf[60]; char* p = buf;
    for (int i = 55; i--;) {
      if (! (*c & -32)) break;
      *p++ = *c++;
    }
    if (*c) {strcpy(p,"..."); p+=3;}
    *p = 0;
    fl_font(l->is_code_block() && (l->level==0 || l->parent->is_class())
	    ? text_font() : text_font()->bold(), text_size());
    w += int(fl_width(buf));
  }

  return w;
}
#endif

void redraw_browser() {
  widget_browser->relayout();
}

#if 0
int Widget_Browser::handle(int e) {
  static Fl_Type *title;
  Fl_Type *l;
  int X,Y,W,H; bbox(X,Y,W,H);
  switch (e) {
  case FL_PUSH:
    if (!Fl::event_inside(X,Y,W,H)) break;
    l = (Fl_Type*)find_item(Fl::event_y());
    if (l) {
      X += 10*l->level;
      if (l->is_parent() && Fl::event_x()>X && Fl::event_x()<X+13) {
	title = pushedtitle = l;
	redraw_line(l);
	return 1;
      }
    }
    break;
  case FL_DRAG:
    if (!title) break;
    l = (Fl_Type*)find_item(Fl::event_y());
    if (l) {
      X += 10*l->level;
      if (l->is_parent() && Fl::event_x()>X && Fl::event_x()<X+13) ;
      else l = 0;
    }
    if (l != pushedtitle) {
      if (pushedtitle) redraw_line(pushedtitle);
      if (l) redraw_line(l);
      pushedtitle = l;
    }
    return 1;
  case FL_RELEASE:
    if (!title) {
      l = (Fl_Type*)find_item(Fl::event_y());
      if (l && l->new_selected && (Fl::event_clicks() || Fl::event_state(FL_CTRL)))
	l->open();
      break;
    }
    l = pushedtitle;
    title = pushedtitle = 0;
    if (l) {
      if (l->open_) {
	l->open_ = 0;
      } else {
	l->open_ = 1;
	for (Fl_Type*k=l->next; k&&k->level>l->level;) {
	  if (k->is_parent() && !k->open_) {
	    Fl_Type *j;
	    for (j = k->next; j && j->level>k->level; j = j->next);
	    k = j;
	  } else
	    k = k->next;
	}
      }
      redraw();
    }
    return 1;
  }
  return Fl_Browser_::handle(e);
}
#endif

Fl_Type::Fl_Type() {
  factory = 0;
  parent = 0;
  next = prev = 0;
  selected = new_selected = 0;
  name_ = 0;
  label_ = 0;
  tooltip_ = 0;
  user_data_ = 0;
  user_data_type_ = 0;
  callback_ = 0;
  level = 0;
}

// turn a click at x,y on this into the actual picked object:
Fl_Type* Fl_Type::click_test(int,int) {return 0;}
void Fl_Type::add_child(Fl_Type*, Fl_Type*) {}
void Fl_Type::move_child(Fl_Type*, Fl_Type*) {}
void Fl_Type::remove_child(Fl_Type*) {}

// add a list of widgets as a new child of p:
void Fl_Type::add(Fl_Type *p) {
  parent = p;
  Fl_Type *end = this;
  while (end->next) end = end->next;
  Fl_Type *q;
  int newlevel;
  if (p) {
    for (q = p->next; q && q->level > p->level; q = q->next);
    newlevel = p->level+1;
  } else {
    q = 0;
    newlevel = 0;
  }
  for (Fl_Type *t = this->next; t; t = t->next) t->level += (newlevel-level);
  level = newlevel;
  if (q) {
    prev = q->prev;
    prev->next = this;
    q->prev = end;
    end->next = q;
  } else if (first) {
    prev = last;
    prev->next = this;
    end->next = 0;
    last = end;
  } else {
    first = this;
    last = end;
    prev = end->next = 0;
  }
  if (p) p->add_child(this,0);
  open_ = 1;
  modflag = 1;
  redraw_browser();
}

// add to a parent before another widget:
void Fl_Type::insert(Fl_Type *g) {
  Fl_Type *end = this;
  while (end->next) end = end->next;
  parent = g->parent;
  int newlevel = g->level;
  for (Fl_Type *t = this->next; t; t = t->next) t->level += newlevel-level;
  level = newlevel;
  prev = g->prev;
  if (prev) prev->next = this; else first = this;
  end->next = g;
  g->prev = end;
  if (parent) parent->add_child(this, g);
  redraw_browser();
}

// delete from parent:
Fl_Type *Fl_Type::remove() {
  Fl_Type *end = this;
  for (;;) {
    if (!end->next || end->next->level <= level) break;
    end = end->next;
  }
  if (prev) prev->next = end->next;
  else first = end->next;
  if (end->next) end->next->prev = prev;
  else last = prev;
  Fl_Type *r = end->next;
  prev = end->next = 0;
  if (parent) parent->remove_child(this);
  parent = 0;
  redraw_browser();
  selection_changed(0);
  return r;
}

// update a string member:
int storestring(const char *n, const char * & p, int nostrip) {
  if (n == p) return 0;
  int length = 0;
  if (n) { // see if blank, strip leading & trailing blanks
    if (!nostrip) while (isspace(*n)) n++;
    const char *e = n + strlen(n);
    if (!nostrip) while (e > n && isspace(*(e-1))) e--;
    length = e-n;
    if (!length) n = 0;
  }    
  if (n == p) return 0;
  if (n && p && !strncmp(n,p,length) && !p[length]) return 0;
  if (p) free((void *)p);
  if (!n || !*n) {
    p = 0;
  } else {
    char *q = (char *)malloc(length+1);
    strncpy(q,n,length);
    q[length] = 0;
    p = q;
  }
  modflag = 1;
  return 1;
}

void Fl_Type::name(const char *n) {
  if (storestring(n,name_)) widget_browser->redraw();
}

void Fl_Type::label(const char *n) {
  if (storestring(n,label_,1)) {
    setlabel(label_);
    if (!name_) widget_browser->redraw();
  }
}

void Fl_Type::tooltip(const char *n) {
  storestring(n,tooltip_,1);
}

void Fl_Type::callback(const char *n) {
  storestring(n,callback_);
}

void Fl_Type::user_data(const char *n) {
  storestring(n,user_data_);
}

void Fl_Type::user_data_type(const char *n) {
  storestring(n,user_data_type_);
}

void Fl_Type::open() {
  printf("Open of '%s' is not yet implemented\n",type_name());
}

void Fl_Type::setlabel(const char *) {}

Fl_Type::~Fl_Type() {
  // warning: destructor only works for widgets that have been add()ed.
  if (prev) prev->next = next; else first = next;
  if (next) next->prev = prev; else last = prev;
  if (current == this) current = 0;
  modflag = 1;
  if (parent) parent->remove_child(this);
  if (widget_browser) redraw_browser();
}

int Fl_Type::is_parent() const {return 0;}
int Fl_Type::is_widget() const {return 0;}
int Fl_Type::is_valuator() const {return 0;}
int Fl_Type::is_button() const {return 0;}
int Fl_Type::is_light_button() const {return 0;}
int Fl_Type::is_menu_item() const {return 0;}
int Fl_Type::is_menu_button() const {return 0;}
int Fl_Type::is_group() const {return 0;}
int Fl_Type::is_window() const {return 0;}
int Fl_Type::is_code_block() const {return 0;}
int Fl_Type::is_decl_block() const {return 0;}
int Fl_Type::is_class() const {return 0;}
int Fl_Type::is_counter() const {return 0;}
int Fl_Type::is_adjuster() const {return 0;}
int Fl_Type::is_slider() const {return 0;}
int Fl_Type::is_scrollbar() const {return 0;}
int Fl_Type::is_choice() const {return 0;}
int Fl_Type::is_browser() const {return 0;}
int Fl_Type::is_input() const {return 0;}
int Fl_Type::is_value_input() const {return 0;}
int Fl_Type::is_value_output() const {return 0;}
int Fl_Type::is_value_slider() const {return 0;}

////////////////////////////////////////////////////////////////

Fl_Type *in_this_only; // set if menu popped-up in window

void select_all_cb(Fl_Widget *,void *) {
  Fl_Type *p = Fl_Type::current ? Fl_Type::current->parent : 0;
  if (in_this_only) {
    Fl_Type *t = p;
    for (; t && t != in_this_only; t = t->parent);
    if (t != in_this_only) p = in_this_only;
  }
  for (;;) {
    if (p) {
      int foundany = 0;
      for (Fl_Type *t = p->next; t && t->level>p->level; t = t->next) {
	if (!t->new_selected) {select(t,1); foundany = 1;}
      }
      if (foundany) break;
      p = p->parent;
    } else {
      for (Fl_Type *t = Fl_Type::first; t; t = t->next)
	select(t,1);
      break;
    }
  }
  selection_changed(p);
}

static void delete_children(Fl_Type *p) {
  Fl_Type *f;
  for (f = p; f && f->next && f->next->level > p->level; f = f->next);
  for (; f != p; ) {
    Fl_Type *g = f->prev;
    delete f;
    f = g;
  }
}

void delete_all(int selected_only) {
  for (Fl_Type *f = Fl_Type::first; f;) {
    if (f->selected || !selected_only) {
      delete_children(f);
      Fl_Type *g = f->next;
      delete f;
      f = g;
    } else f = f->next;
  }
  if(!selected_only)
  {
    include_H_from_C=1;
    images_dir="./";
  }

  selection_changed(0);
}

// move f (and it's children) into list before g:
// returns pointer to whatever is after f & children
void Fl_Type::move_before(Fl_Type* g) {
  if (level != g->level) printf("move_before levels don't match! %d %d\n",
				level, g->level);
  Fl_Type* n;
  for (n = next; n && n->level > level; n = n->next);
  if (n == g) return;
  Fl_Type *l = n ? n->prev : Fl_Type::last;
  prev->next = n;
  if (n) n->prev = prev; else Fl_Type::last = prev;
  prev = g->prev;
  l->next = g;
  if (prev) prev->next = this; else Fl_Type::first = this;
  g->prev = l;
  if (parent) parent->move_child(this,g);
  redraw_browser();
}

// move selected widgets in their parent's list:
void earlier_cb(Fl_Widget*,void*) {
  Fl_Type *f;
  for (f = Fl_Type::first; f; ) {
    Fl_Type* nxt = f->next;
    if (f->selected) {
      Fl_Type* g;
      for (g = f->prev; g && g->level > f->level; g = g->prev);
      if (g && g->level == f->level && !g->selected) f->move_before(g);
    }
    f = nxt;
  }
}

void later_cb(Fl_Widget*,void*) {
  Fl_Type *f;
  for (f = Fl_Type::last; f; ) {
    Fl_Type* prv = f->prev;
    if (f->selected) {
      Fl_Type* g;
      for (g = f->next; g && g->level > f->level; g = g->next);
      if (g && g->level == f->level && !g->selected) g->move_before(f);
    }
    f = prv;
  }
}

////////////////////////////////////////////////////////////////

// write a widget and all it's children:
void Fl_Type::write() {
    write_indent(level);
    write_word(type_name());
    write_word(name());
    write_open(level);
    write_properties();
    write_close(level);
    if (!is_parent()) return;
    // now do children:
    write_open(level);
    Fl_Type *child;
    for (child = next; child && child->level > level; child = child->next)
	if (child->level == level+1) child->write();
    write_close(level);
}

void Fl_Type::write_properties() {
  // repeat this for each attribute:
  if (label()) {
    write_indent(level+1);
    write_word("label");
    write_word(label());
  }
  if (user_data()) {
    write_indent(level+1);
    write_word("user_data");
    write_word(user_data());
    if (user_data_type()) {
      write_word("user_data_type");
      write_word(user_data_type());
    }
  }
  if (callback()) {
    write_indent(level+1);
    write_word("callback");
    write_word(callback());
  }
  if (is_parent() && open_) write_word("open");
  if (selected) write_word("selected");
  if (tooltip()) {
    write_indent(level+1);
    write_word("tooltip");
    write_word(tooltip());
  }
}

void Fl_Type::read_property(const char *c) {
  if (!strcmp(c,"label"))
    label(read_word());
  else if (!strcmp(c,"tooltip"))
    tooltip(read_word());
  else if (!strcmp(c,"user_data"))
    user_data(read_word());
  else if (!strcmp(c,"user_data_type"))
    user_data_type(read_word());
  else if (!strcmp(c,"callback"))
    callback(read_word());
  else if (!strcmp(c,"open"))
    open_ = 1;
  else if (!strcmp(c,"selected"))
    select(this,1);
  else
    read_error("Unknown property \"%s\"", c);
}

int Fl_Type::read_fdesign(const char*, const char*) {return 0;}

//
// End of "$Id: Fl_Type.cxx,v 1.20 2000/08/21 03:56:24 spitzak Exp $".
//
