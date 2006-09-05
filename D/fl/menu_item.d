//
// "$Id: menu_item.d 4288 2005-04-16 00:13:17Z mike $"
//
// Menu item header file for the Fast Light Tool Kit (FLTK).
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

module fl.menu_item;

public import fl.widget;
public import fl.image;
private import fl.fl;
private import fl.menu_;
private import fl.menu;
private import fl.labeltype;
private import fl.draw;

const int FL_MENU_INACTIVE = 1;
const int FL_MENU_TOGGLE= 2;
const int FL_MENU_VALUE = 4;
const int FL_MENU_RADIO = 8;
const int FL_MENU_INVISIBLE = 0x10;
const int FL_SUBMENU_POINTER = 0x20;
const int FL_SUBMENU = 0x40;
const int FL_MENU_DIVIDER = 0x80;
const int FL_MENU_HORIZONTAL = 0x100;


struct Fl_Menu_Item {
  char* text;	// label()
  int shortcut_;
  Fl_Callback callback_;
  void* user_data_;
  int flags;
  ubyte labeltype_;
  ubyte labelfont_;
  ubyte labelsize_;
  uint labelcolor_;

  // advance N items, skipping submenus:
  Fl_Menu_Item* next(int n=1) {
    if (n < 0) return null; // this is so selected==-1 returns NULL
    Fl_Menu_Item* m = this;
    int nest = 0;
    if (!m.visible()) n++;
    while (n>0) {
      if (!m.text) {
        if (!nest) return m;
        nest--;
      } else if (m.flags&FL_SUBMENU) {
        nest++;
      }
      m++;
      if (!nest && m.visible()) n--;
    }
    return m;
  }
  Fl_Menu_Item* first() { return next(0); }
/+=

  // methods on menu items:
  char* label() {return text;}
  void label(char* a) {text=a;}
  void label(Fl_Labeltype a,char* b) {labeltype_ = a; text = b;}
  Fl_Labeltype labeltype() {return (Fl_Labeltype)labeltype_;}
  void labeltype(Fl_Labeltype a) {labeltype_ = a;}
  Fl_Color labelcolor() {return (Fl_Color)labelcolor_;}
  void labelcolor(uint a) {labelcolor_ = a;}
  Fl_Font labelfont() {return (Fl_Font)labelfont_;}
  void labelfont(ubyte a) {labelfont_ = a;}
  ubyte labelsize() {return labelsize_;}
  void labelsize(ubyte a) {labelsize_ = a;}
  Fl_Callback_p callback() {return callback_;}
  void callback(Fl_Callback  c, void* p) {callback_=c; user_data_=p;}
  void callback(Fl_Callback  c) {callback_=c;}
  void callback(Fl_Callback0 c) {callback_=(Fl_Callback )c;}
  void callback(Fl_Callback1 c, int p=0) {callback_=(Fl_Callback )c; user_data_=(void*)p;}
=+/
  void* user_data() {return user_data_;}
  void user_data(void* v) {user_data_ = v;}
  int argument() {return cast(int)user_data_;}
  void argument(int v) {user_data_ = cast(void*)v;}
  int shortcut() {return shortcut_;}
  void shortcut(int s) {shortcut_ = s;}
  int submenu() {return flags&(FL_SUBMENU|FL_SUBMENU_POINTER);}
  int checkbox() {return flags&FL_MENU_TOGGLE;}
  int radio() {return flags&FL_MENU_RADIO;}
  int value() {return flags&FL_MENU_VALUE;}
  void set() {flags |= FL_MENU_VALUE;}
  void clear() {flags &= ~FL_MENU_VALUE;}
  void setonly() {
    flags |= FL_MENU_RADIO | FL_MENU_VALUE;
    Fl_Menu_Item* j;
    for (j = this; ; ) {  // go down
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
  int visible() {return !(flags&FL_MENU_INVISIBLE);}
  void show() {flags &= ~FL_MENU_INVISIBLE;}
  void hide() {flags |= FL_MENU_INVISIBLE;}
  int active() {return !(flags&FL_MENU_INACTIVE);}
  void activate() {flags &= ~FL_MENU_INACTIVE;}
  void deactivate() {flags |= FL_MENU_INACTIVE;}
  int activevisible() {return !(flags&0x11);}
/+=
  // compatibility for FLUID so it can set the image of a menu item...
  void image(Fl_Image  a) {a.label(this);}
  void image(Fl_Image  a) {a.label(this);}
=+/
  // used by menubar:
  int measure(int* hp, Fl_Menu_ m) {
    Fl_Label l;
    l.value   = text;
    l.image   = null;
    l.deimage = null;
    l.type    = labeltype_;
    l.font    = labelsize_ || labelfont_ ? labelfont_ : (m ? m.textfont() : FL_HELVETICA);
    l.size    = labelsize_ ? labelsize_ : m ? m.textsize() : FL_NORMAL_SIZE;
    l.color   = FL_FOREGROUND_COLOR; // this makes no difference?
    fl_draw_shortcut = 1;
    int w = 0; int h = 0;
    if (hp)
      l.measure(w, *hp);
    else 
      l.measure(w, h);
    fl_draw_shortcut = 0;
    if (flags & (FL_MENU_TOGGLE|FL_MENU_RADIO)) w += 14;
    return w;
  }

  void draw(int x, int y, int w, int h, Fl_Menu_ m, int selected=0) {
    Fl_Label l;
    l.value   = text;
    l.image   = null;
    l.deimage = null;
    l.type    = labeltype_;
    l.font    = labelsize_ || labelfont_ ? labelfont_ : (m ? m.textfont() : FL_HELVETICA);
    l.size    = labelsize_ ? labelsize_ : m ? m.textsize() : FL_NORMAL_SIZE;
    l.color   = labelcolor_ ? labelcolor_ : m ? m.textcolor() : FL_FOREGROUND_COLOR;
    if (!active()) l.color = fl_inactive(l.color);
    Fl_Color color = m ? m.color() : FL_GRAY;
    if (selected) {
      Fl_Color r = m ? m.selection_color() : FL_SELECTION_COLOR;
      Fl_Boxtype b = m && m.down_box() ? m.down_box() : FL_FLAT_BOX;
      if (fl_contrast(r,color)!=r) { // back compatability boxtypes
        if (selected == 2) { // menu title
          r = color;
          b = m ? m.box() : FL_UP_BOX;
        } else {
          r = FL_COLOR_CUBE-1; // white
          l.color = fl_contrast(labelcolor_, r);
        }
      } else {
        l.color = fl_contrast(labelcolor_, r);
      }
      if (selected == 2) { // menu title
        fl_draw_box(b, x, y, w, h, r);
        x += 3;
        w -= 8;
      } else {
        fl_draw_box(b, x+1, y-(LEADING-2)/2, w-2, h+(LEADING-2), r);
      }
    }
  
    if (flags & (FL_MENU_TOGGLE|FL_MENU_RADIO)) {
      int d = (h - FL_NORMAL_SIZE + 1) / 2;
      int W = h - 2 * d;
  
      if (flags & FL_MENU_RADIO) {
        fl_draw_box(FL_ROUND_DOWN_BOX, x+2, y+d, W, W, FL_BACKGROUND2_COLOR);
        if (value()) {
          fl_color(labelcolor_);
          int tW = (W - Fl.box_dw(FL_ROUND_DOWN_BOX)) / 2 + 1;
          if ((W - tW) & 1) tW++; // Make sure difference is even to center
          int td = Fl.box_dx(FL_ROUND_DOWN_BOX) + 1;
          switch (tW) {
            // Larger circles draw fine...
            default :
              fl_pie(x + td + 2, y + d + td, tW, tW, 0.0, 360.0);
              break;
            // Small circles don't draw well on many systems...
            case 6 :
              fl_rectf(x + td + 4, y + d + td, tW - 4, tW);
              fl_rectf(x + td + 3, y + d + td + 1, tW - 2, tW - 2);
              fl_rectf(x + td + 2, y + d + td + 2, tW, tW - 4);
              break;
  
            case 5 :
            case 4 :
            case 3 :
              fl_rectf(x + td + 3, y + d + td, tW - 2, tW);
              fl_rectf(x + td + 2, y + d + td + 1, tW, tW - 2);
              break;
  
            case 2 :
            case 1 :
              fl_rectf(x + td + 2, y + d + td, tW, tW);
              break;
          }
        }
      } else {
        fl_draw_box(FL_DOWN_BOX, x+2, y+d, W, W, FL_BACKGROUND2_COLOR);
        if (value()) {
          fl_color(labelcolor_);
          int tx = x + 5;
          int tw = W - 6;
          int d1 = tw/3;
          int d2 = tw-d1;
          int ty = y + d + (W+d2)/2-d1-2;
          for (int n = 0; n < 3; n++, ty++) {
            fl_line(tx, ty, tx+d1, ty+d1);
            fl_line(tx+d1, ty+d1, tx+tw-1, ty+d1-d2+1);
          }
        }
      }
      x += W + 3;
      w -= W + 3;
    }
  
    if (!fl_draw_shortcut) fl_draw_shortcut = 1;
    l.draw(x+3, y, w>6 ? w-6 : 0, h, FL_ALIGN_LEFT);
    fl_draw_shortcut = 0;
  }
/+=

  // popup menus without using an Fl_Menu_ widget:
  Fl_Menu_Item* popup(
    int X, int Y,
    char *title = 0,
    Fl_Menu_Item* picked=0,
    Fl_Menu_  = 0) const;
=+/
  Fl_Menu_Item* pulldown(int X, int Y, int W, int H,
      Fl_Menu_Item* picked = null,
      Fl_Menu_  m = null,
      Fl_Menu_Item* title = null,
      int menubar=0) {
    /+==== ====+/
   return null;
  }
/+=
  Fl_Menu_Item* test_shortcut() const;
=+/
  Fl_Menu_Item* find_shortcut(int* ip=null) {
    Fl_Menu_Item* m = first();
    if (m) for (int ii = 0; m.text; m = m.next(), ii++) {
      if (m.activevisible()) {
        if (Fl.test_shortcut(m.shortcut_)
           || Fl_Widget.test_shortcut(m.text)) {
          if (ip) *ip=ii;
          return m;
        }
      }
    }
    return null;
  }

  void do_callback(Fl_Widget o) {callback_(o, user_data_);}
  void do_callback(Fl_Widget o, void* arg) {callback_(o, arg);}
  void do_callback(Fl_Widget o, int arg) {callback_(o, cast(void*)arg);}
/+=
  // back-compatability, do not use:
  int checked() {return flags&FL_MENU_VALUE;}
  void check() {flags |= FL_MENU_VALUE;}
  void uncheck() {flags &= ~FL_MENU_VALUE;}
  int add(char*, int shortcut, Fl_Callback , void* =0, int = 0);
  int add(char*a, char* b, Fl_Callback  c,
	  void* d = 0, int e = 0) {
    return add(a,fl_old_shortcut(b),c,d,e);}
=+/
  int size() {
    Fl_Menu_Item* m = this;
    int nest = 0;
    for (;;) {
      if (!m.text) {
        if (!nest) return (m-this+1);
        nest--;
      } else if (m.flags & FL_SUBMENU) {
        nest++;
      }
      m++;
    }
  }
}

alias Fl_Menu_Item Fl_Menu; // back compatability

const int FL_PUP_NONE	= 0;
const int FL_PUP_GREY	= FL_MENU_INACTIVE;
const int FL_PUP_GRAY	= FL_MENU_INACTIVE;
const int FL_MENU_BOX	= FL_MENU_TOGGLE;
const int FL_PUP_BOX	= FL_MENU_TOGGLE;
const int FL_MENU_CHECK	= FL_MENU_VALUE;
const int FL_PUP_CHECK	= FL_MENU_VALUE;
const int FL_PUP_RADIO	= FL_MENU_RADIO;
const int FL_PUP_INVISIBLE = FL_MENU_INVISIBLE;
const int FL_PUP_SUBMENU = FL_SUBMENU_POINTER;

//
// End of "$Id: menu_item.d 4288 2005-04-16 00:13:17Z mike $".
//
