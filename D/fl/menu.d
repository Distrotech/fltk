/+- This file was imported from C++ using a script
//
// "$Id: menu.d 4288 2005-04-16 00:13:17Z mike $"
//
// Old menu header file for the Fast Light Tool Kit (FLTK).
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

// this include file is for back compatability only
public import fl.menu_item;

//
// End of "$Id: menu.d 4288 2005-04-16 00:13:17Z mike $".
//
    End of automatic import -+/
/+- This file was imported from C++ using a script
//
// "$Id: menu.d 5259 2006-07-17 20:33:45Z matt $"
//
// Menu code for the Fast Light Tool Kit (FLTK).
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

// Warning: this menu code is quite a mess!

// This file contains code for implementing Fl_Menu_Item, and for
// methods for bringing up popup menu hierarchies without using the
// Fl_Menu_ widget.

#include <FL/Fl.H>
private import fl.menu_window;
private import fl.menu_;
private import fl.draw;
#include <stdio.h>

version (__APPLE__) {
#  include <Carbon/Carbon.h>
}

// appearance of current menus are pulled from this parent widget:


=+/

const int LEADING = 4;  // extra vertical leading

/+=


void menuwindow.position(int X, int Y) {
  if (title) {title.position(X, title.y()+Y-y());}
  Fl_Menu_Window.position(X, Y);
  // x(X); y(Y); // don't wait for response from X
}


////////////////////////////////////////////////////////////////

void menuwindow.drawentry(Fl_Menu_Item* m, int n, int eraseit) {
  if (!m) return; // this happens if -1 is selected item and redrawn

  int BW = Fl.box_dx(box());
  int xx = BW;
  int W = w();
  int ww = W-2*BW-1;
  int yy = BW+1+n*itemheight;
  int hh = itemheight - LEADING;

  if (eraseit && n != selected) {
    fl_push_clip(xx+1, yy-(LEADING-2)/2, ww-2, hh+(LEADING-2));
    draw_box(box(), 0, 0, w(), h(), button ? button.color() : color());
    fl_pop_clip();
  }

  m.draw(xx, yy, ww, hh, button, n==selected);

  // the shortcuts and arrows assumme fl_color() was left set by draw():
  if (m.submenu()) {
    int sz = (hh-7)&-2;
    int y1 = yy+(hh-sz)/2;
    int x1 = xx+ww-sz-3;
    fl_polygon(x1+2, y1, x1+2, y1+sz, x1+sz/2+2, y1+sz/2);
  } else if (m.shortcut_) {
    Fl_Font f = m.labelsize_ || m.labelfont_ ? (Fl_Font)m.labelfont_ :
                    button ? button.textfont() : FL_HELVETICA;
    fl_font(f, m.labelsize_ ? m.labelsize_ :
                   button ? button.textsize() : FL_NORMAL_SIZE);
    fl_draw(fl_shortcut_label(m.shortcut_), xx, yy, ww-3, hh, FL_ALIGN_RIGHT);
  }

  if (m.flags & FL_MENU_DIVIDER) {
    fl_color(FL_DARK3);
    fl_xyline(BW-1, yy+hh+(LEADING-2)/2, W-2*BW+2);
    fl_color(FL_LIGHT3);
    fl_xyline(BW-1, yy+hh+((LEADING-2)/2+1), W-2*BW+2);
  }
}

void menutitle.draw() {
  menu.draw(0, 0, w(), h(), button, 2);
}

void menuwindow.draw() {
  if (damage() != FL_DAMAGE_CHILD) {	// complete redraw
    fl_draw_box(box(), 0, 0, w(), h(), button ? button.color() : color());
    if (menu) {
      Fl_Menu_Item* m; int j;
      for (m=menu.first(), j=0; m.text; j++, m = m.next()) drawentry(m, j, 0);
    }
  } else {
    if (damage() & FL_DAMAGE_CHILD && selected!=drawn_selected) { // change selection
      drawentry(menu.next(drawn_selected), drawn_selected, 1);
      drawentry(menu.next(selected), selected, 1);
    }
  }	    
  drawn_selected = selected;
}


////////////////////////////////////////////////////////////////

int menuwindow.find_selected(int mx, int my) {
  if (!menu || !menu.text) return -1;
  mx -= x();
  my -= y();
  if (my < 0 || my >= h()) return -1;
  if (!itemheight) { // menubar
    int xx = 3; int n = 0;
    Fl_Menu_Item* m = menu ? menu.first() : 0;
    for (; ; m = m.next(), n++) {
      if (!m.text) return -1;
      xx += m.measure(0, button) + 16;
      if (xx > mx) break;
    }
    return n;
  }
  if (mx < Fl.box_dx(box()) || mx >= w()) return -1;
  int n = (my-Fl.box_dx(box())-1)/itemheight;
  if (n < 0 || n>=numitems) return -1;
  return n;
}

// return horizontal position for item n in a menubar:
int menuwindow.titlex(int n) {
  Fl_Menu_Item* m;
  int xx = 3;
  for (m=menu.first(); n--; m = m.next()) xx += m.measure(0, button) + 16;
  return xx;
}

////////////////////////////////////////////////////////////////
// Fl_Menu_Item.popup(...)

// Because Fl.grab() is done, all events go to one of the menu windows.
// But the handle method needs to look at all of them to find out
// what item the user is pointing at.  And it needs a whole lot
// of other state variables to determine what is going on with
// the currently displayed menus.
// So the main loop (handlemenu()) puts all the state in a structure
// and puts a pointer to it in a static location, so the handle()
// on menus can refer to it and alter it.  The handle() method
// changes variables in this state to indicate what item is
// picked, but does not actually alter the display, instead the
// main loop does that.  This is because the X mapping and unmapping
// of windows is slow, and we don't want to fall behind the events.



static int backward(int menu) { // previous item in menu menu if possible
  menustate &pp = *p;
  menuwindow &m = *(pp.p[menu]);
  int item = (menu == pp.menu_number) ? pp.item_number : m.selected;
  if (item < 0) item = m.numitems;
  while (--item >= 0) {
    Fl_Menu_Item* m1 = m.menu.next(item);
    if (m1.activevisible()) {setitem(m1, menu, item); return 1;}
  }
  return 0;
}

int menuwindow.handle(int e) {
  menustate &pp = *p;
  switch (e) {
  case FL_KEYBOARD:
    switch (Fl.event_key()) {
    case FL_BackSpace:
    case 0xFE20: // backtab
    BACKTAB:
      if (!backward(pp.menu_number)) {pp.item_number = -1;backward(pp.menu_number);}
      return 1;
    case FL_Up:
      if (pp.menubar && pp.menu_number == 0) {
        // Do nothing...
      } else if (backward(pp.menu_number)) {
        // Do nothing...
      } else if (pp.menubar && pp.menu_number==1) {
        setitem(0, pp.p[0]->selected);
      }
      return 1;
    case FL_Tab:
      if (Fl.event_shift()) goto BACKTAB;
    case FL_Down:
      if (pp.menu_number || !pp.menubar) forward(pp.menu_number);
      else if (pp.menu_number < pp.nummenus-1) forward(pp.menu_number+1);
      return 1;
    case FL_Right:
      if (pp.menubar && (pp.menu_number<=0 || pp.menu_number==1 && pp.nummenus==2))
	forward(0);
      else if (pp.menu_number < pp.nummenus-1) forward(pp.menu_number+1);
      return 1;
    case FL_Left:
      if (pp.menubar && pp.menu_number<=1) backward(0);
      else if (pp.menu_number>0)
	setitem(pp.menu_number-1, pp.p[pp.menu_number-1]->selected);
      return 1;
    case FL_Enter:
    case FL_KP_Enter:
    case ' ':
      pp.state = DONE_STATE;
      return 1;
    case FL_Escape:
      setitem(0, -1, 0);
      pp.state = DONE_STATE;
      return 1;
    }
    break;
  case FL_SHORTCUT: {
    for (int mymenu = pp.nummenus; mymenu--;) {
      menuwindow &mw = *(pp.p[mymenu]);
      int item; Fl_Menu_Item* m = mw.menu.find_shortcut(&item);
      if (m) {
	setitem(m, mymenu, item);
	if (!m.submenu()) pp.state = DONE_STATE;
	return 1;
      }
    }} break;
  case FL_ENTER:
  case FL_MOVE:
  case FL_PUSH:
  case FL_DRAG: {
version (__QNX__) {
    // STR 704: workaround QNX X11 bug - in QNX a FL_MOVE event is sent
    // right after FL_RELEASE...
    if (pp.state == DONE_STATE) return 1;
} // __QNX__
    int mx = Fl.event_x_root();
    int my = Fl.event_y_root();
    int item=0; int mymenu = pp.nummenus-1;
    // Clicking or dragging outside menu cancels it...
    if ((!pp.menubar || mymenu) && !pp.is_inside(mx, my)) {
      setitem(0, -1, 0);
      if (e==FL_PUSH)
        pp.state = DONE_STATE;
      return 1;
    }
    for (mymenu = pp.nummenus-1; ; mymenu--) {
      item = pp.p[mymenu]->find_selected(mx, my);
      if (item >= 0) break;
      if (mymenu <= 0) return 0;
    }
    if (my == 0 && item > 0) setitem(mymenu, item - 1);
    else setitem(mymenu, item);
    if (e == FL_PUSH) {
      if (pp.current_item && pp.current_item.submenu() // this is a menu title
	  && item != pp.p[mymenu]->selected // and it is not already on
	  && !pp.current_item.callback_) // and it does not have a callback
	pp.state = MENU_PUSH_STATE;
      else
	pp.state = PUSH_STATE;
    }} return 1;
  case FL_RELEASE:
    // do nothing if they try to pick inactive items
    if (pp.current_item && !pp.current_item.activevisible()) {
      if (pp.state==INITIAL_STATE) {
        setitem(0, -1, 0);
        pp.state = DONE_STATE;
      }
      return 1;
    }
    // Mouse must either be held down/dragged some, or this must be
    // the second click (not the one that popped up the menu):
    if (!Fl.event_is_click() || pp.state == PUSH_STATE ||
	pp.menubar && pp.current_item && !pp.current_item.submenu() // button
	) {
#if 0 // makes the check/radio items leave the menu up
      Fl_Menu_Item* m = pp.current_item;
      if (m && button && (m.flags & (FL_MENU_TOGGLE|FL_MENU_RADIO))) {
	((Fl_Menu_ )button)->picked(m);
	pp.p[pp.menu_number]->redraw();
      } else
}
	pp.state = DONE_STATE;
    }
    return 1;
  }
  return Fl_Window.handle(e);
}


const Fl_Menu_Item*
Fl_Menu_Item.popup(
  int X, int Y,
  char* title,
  Fl_Menu_Item* picked,
  Fl_Menu_  but
  ) const
{
  static Fl_Menu_Item dummy; // static so it is all zeros
  dummy.text = title;
  return pulldown(X, Y, 0, 0, picked, but, title ? &dummy : 0);
}

// Recursive search of all submenus for anything with this key as a
// shortcut.  Only uses the shortcut field, ignores &x in the labels:
const Fl_Menu_Item* Fl_Menu_Item.test_shortcut() {
  Fl_Menu_Item* m = first();
  Fl_Menu_Item* ret = 0;
  if (m) for (; m.text; m = m.next()) {
    if (m.activevisible()) {
      // return immediately any match of an item in top level menu:
      if (Fl.test_shortcut(m.shortcut_)) return m;
      // if (Fl_Widget.test_shortcut(m.text)) return m;
      // only return matches from lower menu if nothing found in top menu:
      if (!ret && m.submenu()) {
	Fl_Menu_Item* s =
	  (m.flags&FL_SUBMENU) ? m+1:(Fl_Menu_Item*)m.user_data_;
	ret = s.test_shortcut();
      }
    }
  }
  return ret;
}

//
// End of "$Id: menu.d 5259 2006-07-17 20:33:45Z matt $".
//
    End of automatic import -+/
