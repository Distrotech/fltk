//
// "$Id: Fl_Menu_add.cxx,v 1.21 2000/06/06 14:37:31 mike Exp $"
//
// Menu utilities for the Fast Light Tool Kit (FLTK).
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

// Methods to create/destroy the items in an Fl_Menu_ widget.  Used to
// emulate XForms and to provide convienence functions for building
// menus.  It may make sense to move these functions to Fl_Group.

// This is greatly simplified compared to fltk 1.0 due to the rewrite
// of Fl_Menu_ to use child widgets.  Adding an item just creates the
// new Fl_Item.

// Not at all guaranteed to be Forms compatable, especially with any
// string with a % sign in it!

#include <FL/Fl_Menu_.H>
#include <FL/Fl_Item.H>
#include <FL/Fl_Item_Group.H>
#include <FL/Fl_Divider.H>
#include <FL/Fl_Menu_Item.H>
#include <string.h>

// Return a new menu item:
static int insert_here;

static Fl_Widget* append(
  Fl_Group* g,
  const char *text,
  int flags
) {
  Fl_Group* saved = Fl_Group::current();
  Fl_Group::current(0);
  Fl_Widget* o;
  if (flags & FL_SUBMENU) {
    o = new Fl_Item_Group();
    Fl_Group::current(0);
  } else
    o = new Fl_Item();
  o->copy_label(text);
  if (flags & FL_MENU_TOGGLE) o->type(FL_TOGGLE_ITEM);
  if (flags & FL_MENU_RADIO) o->type(FL_RADIO_ITEM);
  // these flags have been cleverly assigned so this shift and mask
  // converts from the old values to the new ones:
  o->set_flag((flags<<8)&(FL_INACTIVE|FL_VALUE|FL_INVISIBLE));
  if (insert_here) {g->insert(*o, insert_here-1); insert_here = 0;}
  else g->add(o);
  if (flags & FL_MENU_DIVIDER) g->add(new Fl_Divider());
  Fl_Group::current(saved);
  return o;
}

static int find_flag; // lame-o attempt to reuse the code

// Add an item.  The text is split at '/' characters to automatically
// produce submenus (actually a totally unnecessary feature as you can
// now add submenu titles directly by setting SUBMENU in the flags):
Fl_Widget* Fl_Menu_::add(
  const char *text,
  int shortcut,
  Fl_Callback *cb,	
  void *data,
  int flags
) {
  Fl_Group* group = this;

  const char *p;
  char *q;
  char buf[1024];

  int flags1 = 0;
  const char* item;
  for (;;) {    /* do all the supermenus: */
    item = text;

    /* fill in the buf with name, changing \x to x: */
    q = buf;
    if (*text == '_') {text++; flags1 = FL_MENU_DIVIDER;}
    for (p=text; *p && *p != '/' && q < buf+1023; *q++ = *p++)
      if (*p=='\\') {p++; item = buf;}
    *q = 0;

    if (*p != '/') break; /* not a menu title */
    item = buf;
    text = p+1;	/* point at item title */

    /* find a matching menu title: */
    for (int n = group->children();;) {
      if (!n) { // create a new menu
	if (find_flag) return 0;
	group = (Fl_Group*)append(group,item,FL_SUBMENU|flags1);
	break;
      }
      Fl_Widget* w = group->child(--n);
      if (w->is_group() && w->label() && !strcmp(w->label(), item)) {
	group = (Fl_Group*)w;
	break;
      }
    }
    flags1 = 0;
  }

  /* find a matching menu item: */
  Fl_Widget* o;
  for (int n = group->children();;) {
    if (!n) { // create a new item
      if (find_flag) return 0;
      o = append(group, item, flags|flags1);
      break;
    }
    Fl_Widget* w = group->child(--n);
    if (w->label() && !strcmp(w->label(), item)) {
      if (find_flag) return w;
      o = w;
      break;
    }
  }

  /* fill it in */
  o->shortcut(shortcut);
  if (cb) o->callback(cb);
  o->user_data(data);

  return o;
}

// This is a method from the old Fl_Browser:
Fl_Widget* Fl_Menu_::add(const char* text, void* data) {
  return add(text, 0, 0, data, 0);
}

// This is a method from the old Fl_Browser:
Fl_Widget* Fl_Menu_::insert(int n, const char* text, void* data) {
  insert_here = n+1;
  return add(text, 0, 0, data, 0);
}

// Does the exact same parsing as add() and return a pointer to the item,
// or return null if none:
Fl_Widget* Fl_Menu_::find(const char* label) const {
  find_flag = 1;
  Fl_Widget* r = ((Fl_Menu_*)this)->add(label,0,0,0,0);
  find_flag = 0;
  return r;
}

// This is a Forms (and SGI GL library) compatable add function, it
// adds many menu items, with '|' seperating the menu items, and tab
// seperating the menu item names from an optional shortcut string.
Fl_Widget* Fl_Menu_::add(const char *str) {
  char buf[128];
  Fl_Widget* r = 0;
  while (*str) {
    const char* start = str;
    int shortcut = 0;
    char *c;
    for (c = buf; *str && *str != '|'; str++) {
//    if (*str == '\t') {*c++ = 0; shortcut = fl_old_shortcut(str);}
//    else
      *c++ = *str;
    }
    *c = 0;
    if (*str) {
      r = add(buf, shortcut, 0, 0, 0);
      str++;
    } else {
      r = add(start, shortcut, 0, 0, 0);
    }
  }
  return r;
}

//
// End of "$Id: Fl_Menu_add.cxx,v 1.21 2000/06/06 14:37:31 mike Exp $".
//
