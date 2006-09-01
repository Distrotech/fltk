/+- This file was imported from C++ using a script
//
// "$Id: menu_.d 4288 2005-04-16 00:13:17Z mike $"
//
// Menu base class header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2005 by Bill Spitzak and others.
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

module fl.menu_;


module fl.widget;
public import fl.widget;
}
public import fl.menu_item;

class Fl_Menu_ : Fl_Widget {

  Fl_Menu_Item *menu_;
  Fl_Menu_Item *value_;

protected:

  ubyte alloc;
  ubyte down_box_;
  ubyte textfont_;
  ubyte textsize_;
  uint textcolor_;

public:
  Fl_Menu_(int,int,int,int,char * =0);
  ~Fl_Menu_();

  int item_pathname(char *name, int namelen, Fl_Menu_Item *finditem=0) const;
  Fl_Menu_Item* picked(Fl_Menu_Item*);
  Fl_Menu_Item* find_item(char *name);

  Fl_Menu_Item* test_shortcut() {return picked(menu()->test_shortcut());}
  void global();

  Fl_Menu_Item *menu() {return menu_;}
  void menu(Fl_Menu_Item *m);
  void copy(Fl_Menu_Item *m, void* user_data = 0);
  int  add(char*, int shortcut, Fl_Callback , void* = 0, int = 0);
  int  add(char* a, char* b, Fl_Callback  c,
	  void* d = 0, int e = 0) {return add(a,fl_old_shortcut(b),c,d,e);}
  int  size() ;
  void size(int W, int H) { Fl_Widget.size(W, H); }
  void clear();
  int  add(char *);
  void replace(int,char *);
  void remove(int);
  void shortcut(int i, int s) {menu_[i].shortcut(s);}
  void mode(int i,int fl) {menu_[i].flags = fl;}
  int  mode(int i) {return menu_[i].flags;}

  Fl_Menu_Item *mvalue() {return value_;}
  int value() {return value_ ? (int)(value_-menu_) : -1;}
  int value(Fl_Menu_Item*);
  int value(int i) {return value(menu_+i);}
  char *text() {return value_ ? value_.text : 0;}
  char *text(int i) {return menu_[i].text;}

  Fl_Font textfont() {return (Fl_Font)textfont_;}
  void textfont(ubyte c) {textfont_=c;}
  ubyte textsize() {return textsize_;}
  void textsize(ubyte c) {textsize_=c;}
  Fl_Color textcolor() {return (Fl_Color)textcolor_;}
  void textcolor(uint c) {textcolor_=c;}

  Fl_Boxtype down_box() {return (Fl_Boxtype)down_box_;}
  void down_box(Fl_Boxtype b) {down_box_ = b;}

  // back compatability:
  Fl_Color down_color() {return selection_color();}
  void down_color(uint c) {selection_color(c);}
};

}

//
// End of "$Id: menu_.d 4288 2005-04-16 00:13:17Z mike $".
//
    End of automatic import -+/
/+- This file was imported from C++ using a script
//
// "$Id: menu_.d 5190 2006-06-09 16:16:34Z mike $"
//
// Common menu code for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2005 by Bill Spitzak and others.
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

// This is a base class for all items that have a menu:
//	Fl_Menu_Bar, Fl_Menu_Button, Fl_Choice
// This provides storage for a menu item, functions to add/modify/delete
// items, and a call for when the user picks a menu item.

// More code in Fl_Menu_add.cxx

#include <FL/Fl.H>
private import fl.menu_;
private import fl.flstring;
#include <stdio.h>
#include <stdlib.h>

// Set 'pathname' of specified menuitem
//    If finditem==NULL, mvalue() is used (the most recently picked menuitem)
//    Returns:
//       0 : OK
//      -1 : item not found (name="")
//      -2 : 'name' not large enough (name="")
//
#define SAFE_STRCAT(s) \
    { len += strlen(s); if ( len >= namelen ) { *name='\0'; return(-2); } else strcat(name,(s)); }
int Fl_Menu_.item_pathname(char *name, int namelen, Fl_Menu_Item *finditem) {
    int len = 0;
    finditem = finditem ? finditem : mvalue();    
    name[0] = '\0';
    for ( int t=0; t<size(); t++ ) {
        Fl_Menu_Item *m = &(menu()[t]);
	if ( m.submenu() ) {				// submenu? descend
	    if (*name) SAFE_STRCAT("/");
	    if (m.label()) SAFE_STRCAT(m.label());
	} else {
	    if (m.label()) {				// menu item?
		if ( m == finditem ) {			// found? tack on itemname, done.
		    SAFE_STRCAT("/");
		    SAFE_STRCAT(m.label());
		    return(0);
		}
	    } else {					// end of submenu? pop
	        char *ss = strrchr(name, '/');
		if ( ss ) { *ss = 0; len = strlen(name); }	// "File/Edit" -> "File"
		else { name[0] = '\0'; len = 0; }		// "File" -> ""
		continue;
	    }
	}
    }
    *name = '\0';
    return(-1);						// item not found
}

// FIND MENU ITEM INDEX, GIVEN MENU PATHNAME
//     eg. "Edit/Copy"
//     Will also return submenus, eg. "Edit"
//     Returns NULL if not found.
//
const Fl_Menu_Item *
Fl_Menu_.find_item(char *name)
{
  char menupath[1024] = "";	// File/Export

  for ( int t=0; t < size(); t++ ) {
    Fl_Menu_Item *m = menu_ + t;

    if (m.flags&FL_SUBMENU) {
      // IT'S A SUBMENU
      // we do not support searches through FL_SUBMENU_POINTER links
      if (menupath[0]) strlcat(menupath, "/", sizeof(menupath));
      strlcat(menupath, m.label(), sizeof(menupath));
      if (!strcmp(menupath, name)) return m;
    } else {
      if (!m.label()) {
	// END OF SUBMENU? Pop back one level.
	char *ss = strrchr(menupath, '/');
	if ( ss ) *ss = 0;
	else menupath[0] = '\0';
	continue;
      }

      // IT'S A MENU ITEM
      char itempath[1024];	// eg. Edit/Copy
      strcpy(itempath, menupath);
      if (itempath[0]) strlcat(itempath, "/", sizeof(itempath));
      strlcat(itempath, m.label(), sizeof(itempath));
      if (!strcmp(itempath, name)) return m;
    }
  }

  return (Fl_Menu_Item *)0;
}

int Fl_Menu_.value(Fl_Menu_Item* m) {
  clear_changed();
  if (value_ != m) {value_ = m; return 1;}
  return 0;
}

// When user picks a menu item, call this.  It will do the callback.
// Unfortunatly this also casts away for the checkboxes, but this
// was necessary so non-checkbox menus can really be declared const...
const Fl_Menu_Item* Fl_Menu_.picked(Fl_Menu_Item* v) {
  if (v) {
    if (v.radio()) {
      if (!v.value()) { // they are turning on a radio item
	set_changed();
	((Fl_Menu_Item*)v)->setonly();
      }
      redraw();
    } else if (v.flags & FL_MENU_TOGGLE) {
      set_changed();
      ((Fl_Menu_Item*)v)->flags ^= FL_MENU_VALUE;
      redraw();
    } else if (v != value_) { // normal item
      set_changed();
    }
    value_ = v;
    if (when()&(FL_WHEN_CHANGED|FL_WHEN_RELEASE)) {
      if (changed() || when()&FL_WHEN_NOT_CHANGED) {
	if (value_ && value_.callback_) value_.do_callback((Fl_Widget )this);
	else do_callback();
      }
    }
  }
  return v;
}

// turn on one of a set of radio buttons
void Fl_Menu_Item.setonly() {
  flags |= FL_MENU_RADIO | FL_MENU_VALUE;
  Fl_Menu_Item* j;
  for (j = this; ; ) {	// go down
    if (j.flags & FL_MENU_DIVIDER) break; // stop on divider lines
    j++;
    if (!j.text || !j.radio()) break; // stop after group
    j.clear();
  }
  for (j = this-1; ; j--) { // go up
    if (!j.text || (j.flags&FL_MENU_DIVIDER) || !j.radio()) break;
    j.clear();
  }
}

Fl_Menu_.Fl_Menu_(int X,int Y,int W,int H,char* l)
: Fl_Widget(X,Y,W,H,l) {
  set_flag(SHORTCUT_LABEL);
  box(FL_UP_BOX);
  when(FL_WHEN_RELEASE_ALWAYS);
  value_ = menu_ = 0;
  alloc = 0;
  selection_color(FL_SELECTION_COLOR);
  textfont(FL_HELVETICA);
  textsize((ubyte)FL_NORMAL_SIZE);
  textcolor(FL_FOREGROUND_COLOR);
  down_box(FL_NO_BOX);
}

int Fl_Menu_.size() {
  if (!menu_) return 0;
  return menu_.size();
}

void Fl_Menu_.menu(Fl_Menu_Item* m) {
  clear();
  value_ = menu_ = (Fl_Menu_Item*)m;
}

// this version is ok with new Fl_Menu_add code with fl_menu_array_owner:

void Fl_Menu_.copy(Fl_Menu_Item* m, void* ud) {
  int n = m.size();
  Fl_Menu_Item* newMenu = new Fl_Menu_Item[n];
  memcpy(newMenu, m, n*sizeof(Fl_Menu_Item));
  menu(newMenu);
  alloc = 1; // make destructor free array, but not strings
  // for convienence, provide way to change all the user data pointers:
  if (ud) for (; n--;) {
    if (newMenu.callback_) newMenu.user_data_ = ud;
    newMenu++;
  }
}

Fl_Menu_::~Fl_Menu_() {
  clear();
}

// Fl_Menu.add() uses this to indicate the owner of the dynamically-
// expanding array.  We must not free this array:
Fl_Menu_  fl_menu_array_owner = 0;

void Fl_Menu_.clear() {
  if (alloc) {
    if (alloc>1) for (int i = size(); i--;)
      if (menu_[i].text) free((void*)menu_[i].text);
    if (this == fl_menu_array_owner)
      fl_menu_array_owner = 0;
    else
      delete[] menu_;
    menu_ = 0;
    value_ = 0;
    alloc = 0;
  }
}

//
// End of "$Id: menu_.d 5190 2006-06-09 16:16:34Z mike $".
//
    End of automatic import -+/
