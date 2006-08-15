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

private import fl.menu_;
private import fl.menu;
private import fl.draw;
private import fl.group;
private import fl.window;

static const int LEADING = 4;
static Fl_Menu_ button;
static menustate* p;

enum { // values for flags:
  FL_MENU_INACTIVE = 1,
  FL_MENU_TOGGLE= 2,
  FL_MENU_VALUE = 4,
  FL_MENU_RADIO = 8,
  FL_MENU_INVISIBLE = 0x10,
  FL_SUBMENU_POINTER = 0x20,
  FL_SUBMENU = 0x40,
  FL_MENU_DIVIDER = 0x80,
  FL_MENU_HORIZONTAL = 0x100
};

struct Fl_Menu_Item {

  char[]   text;	// label()
  int      shortcut_;
  Fl_Callback callback_;
  void*    user_data_;
  int      flags;
  Fl_Labeltype labeltype_;
  Fl_Font  labelfont_;
  ubyte    labelsize_;
  Fl_Color labelcolor_;

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

  Fl_Menu_Item* first() { 
    return next(0); 
  } 

  // methods on menu items:
  char[] label() {
    return text;
  }

  void label(char[] a) {
    text=a;
  }

  void label(Fl_Labeltype a, char[] b) {
    labeltype_ = a; text = b;
  }

  Fl_Labeltype labeltype() {
    return labeltype_;
  }

  void labeltype(Fl_Labeltype a) {
    labeltype_ = a;
  }

  Fl_Color labelcolor() {
    return labelcolor_;
  }

  void labelcolor(Fl_Color a) {
    labelcolor_ = a;
  }

  Fl_Font labelfont() {
    return labelfont_;
  }

  void labelfont(Fl_Font a) {
    labelfont_ = a;
  }

  ubyte labelsize() {
    return labelsize_;
  }

  void labelsize(ubyte a) {
    labelsize_ = a;
  }

  Fl_Callback callback() {
    return callback_;
  }

  void callback(Fl_Callback c, void* p) {
    callback_=c; user_data_=p;
  }

  void callback(Fl_Callback c) {
    callback_=c;
  }

  void callback(Fl_Callback0 c) {
    callback_=cast(Fl_Callback)c;
  }

  void callback(Fl_Callback1 c, int p=0) {
    callback_=cast(Fl_Callback)c; 
    user_data_=cast(void*)p;
  }

  void* user_data() {
    return user_data_;
  }

  void user_data(void* v) {
    user_data_ = v;
  }

  int argument() { 
    return cast(int)user_data_;
  }

  void argument(int v) {
    user_data_ = cast(void*)v;
  }

  int shortcut() {
    return shortcut_;
  }

  void shortcut(int s) {
    shortcut_ = s;
  }

  int submenu() {
    return flags&(FL_SUBMENU|FL_SUBMENU_POINTER);
  }

  int checkbox() {
    return flags&FL_MENU_TOGGLE;
  }

  int radio() {
    return flags&FL_MENU_RADIO;
  }

  int value() {
    return flags&FL_MENU_VALUE;
  }

  void set() {
    flags |= FL_MENU_VALUE;
  }

  void clear() {
    flags &= ~FL_MENU_VALUE;
  }

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

  int visible() {
    return !(flags&FL_MENU_INVISIBLE);
  }

  void show() {
    flags &= ~FL_MENU_INVISIBLE;
  }

  void hide() {
    flags |= FL_MENU_INVISIBLE;
  }

  int active() {
    return !(flags&FL_MENU_INACTIVE);
  }

  void activate() { 
    flags &= ~FL_MENU_INACTIVE;
  }

  void deactivate() {
    flags |= FL_MENU_INACTIVE;
  }

  int activevisible() {
    return !(flags&0x11);
  }

  // compatibility for FLUID so it can set the image of a menu item...
  void image(Fl_Image a) {
    a.label(this);
  }

  // used by menubar:
  int measure(int* hp, Fl_Menu_ m) {
    Fl_Label l;
    l.value   = text;
    l.image   = null;
    l.deimage = null;
    l.type    = labeltype_;
    l.font    = (labelsize_ || labelfont_) ? labelfont_ : (m ? m.textfont() : FL_HELVETICA);
    l.size    = labelsize_ ? labelsize_ : (m ? m.textsize() : FL_NORMAL_SIZE);
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
    l.font    = (labelsize_ || labelfont_) ? labelfont_ : (m ? m.textfont() : FL_HELVETICA);
    l.size    = labelsize_ ? labelsize_ : (m ? m.textsize() : FL_NORMAL_SIZE);
    l.color   = labelcolor_ ? labelcolor_ : m ? m.textcolor() : FL_FOREGROUND_COLOR;
    if (!active()) l.color = fl_inactive(l.color);
    Fl_Color color = m ? m.color() : FL_GRAY;
    if (selected) {
      Fl_Color r = m ? m.selection_color() : FL_SELECTION_COLOR;
      Fl_Boxtype b = (m && m.down_box()) ? m.down_box() : FL_FLAT_BOX;
      if (fl_contrast(r,color)!=r) { // back compatability boxtypes
        if (selected == 2) { // menu title
          r = color;
          b = m ? m.box() : FL_UP_BOX;
        } else {
          r = cast(Fl_Color)(FL_COLOR_CUBE-1); // white
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

  // popup menus without using an Fl_Menu_ widget:
  Fl_Menu_Item* popup(int X, int Y, char[] title=null, Fl_Menu_Item* picked=null, Fl_Menu_ but=null) {
    static Fl_Menu_Item dummy; // static so it is all zeros
    dummy.text = title;
    return pulldown(X, Y, 0, 0, picked, but, title ? &dummy : null);
  }

  Fl_Menu_Item* pulldown(
    int X, int Y, int W, int H,
    Fl_Menu_Item* initial_item=null, Fl_Menu_ pbutton=null, Fl_Menu_Item* t=null, int menubar=0) 
  {
    Fl_Group.current(null); // fix possible user error...
  
    button = pbutton;
    if (pbutton) {
      for (Fl_Window w = pbutton.window(); w; w = w.window()) {
        X += w.x();
        Y += w.y();
      }
    } else {
      X += Fl.event_x_root()-Fl.event_x();
      Y += Fl.event_y_root()-Fl.event_y();
    }
    menuwindow mw = new menuwindow(this, X, Y, W, H, initial_item, t, menubar);
    Fl.grab(mw);
    menustate pp; p = &pp;
    pp.p[0] = mw;
    pp.nummenus = 1;
    pp.menubar = menubar;
    pp.state = INITIAL_STATE;
        
    menuwindow fakemenu = null; // kludge for buttons in menubar
  
    // preselected item, pop up submenus if necessary:
    if (initial_item && mw.selected >= 0) {
      setitem(0, mw.selected);
      goto STARTUP;
    }
  
    pp.current_item = null; pp.menu_number = 0; pp.item_number = -1;
    if (menubar) {
      // find the initial menu
      if (!mw.handle(FL_DRAG)) {
        Fl.release();
        return null;
      }
    }
    initial_item = pp.current_item;
    if (initial_item) goto STARTUP;
  
    // the main loop, runs until p.state goes to DONE_STATE:
    for (;;) {
  
      // make sure all the menus are shown:
      {for (int k = menubar; k < pp.nummenus; k++)
        if (!pp.p[k].shown()) {
          if (pp.p[k].title) pp.p[k].title.show();
          pp.p[k].show();
        }
      }
  
      // get events:
      {Fl_Menu_Item* oldi = pp.current_item;
      Fl.wait();
      if (pp.state == DONE_STATE) break; // done.
      if (pp.current_item == oldi) continue;}
      // only do rest if item changes:
  
      delete fakemenu; fakemenu = null; // turn off "menubar button"
  
      if (!pp.current_item) { // pointing at nothing
        // turn off selection in deepest menu, but don't erase other menus:
        pp.p[pp.nummenus-1].set_selected(-1);
        continue;
      }
  
      delete fakemenu; fakemenu = null;
      initial_item = null; // stop the startup code
      pp.p[pp.menu_number].autoscroll(pp.item_number);
  
    STARTUP:
      menuwindow cw = pp.p[pp.menu_number];
      Fl_Menu_Item* m = pp.current_item;
      if (!m.activevisible()) { // pointing at inactive item
        cw.set_selected(-1);
        initial_item = null; // turn off startup code
        continue;
      }
      cw.set_selected(pp.item_number);
  
      if (m==initial_item) initial_item=null; // stop the startup code if item found
      if (m.submenu()) {
        Fl_Menu_Item* title = m;
        Fl_Menu_Item* menutable;
        if (m.flags&FL_SUBMENU) menutable = m+1;
        else menutable = cast(Fl_Menu_Item*)(m.user_data_); /+= =+/
        // figure out where new menu goes:
        int nX, nY;
        if (!pp.menu_number && pp.menubar) {      // menu off a menubar:
          nX = cw.x() + cw.titlex(pp.item_number);
          nY = cw.y() + cw.h();
          initial_item = null;
        } else {
          nX = cw.x() + cw.w();
          nY = cw.y() + pp.item_number * cw.itemheight;
          title = null;
        }
        if (initial_item) { // bring up submenu containing initial item:
          menuwindow n = new menuwindow(menutable,X,Y,W,H,initial_item,title,0,0,cw.x());
          pp.p[pp.nummenus++] = n;
          // move all earlier menus to line up with this new one:
          if (n.selected>=0) {
            int dy = n.y()-nY;
            int dx = n.x()-nX;
            for (int menu = 0; menu <= pp.menu_number; menu++) {
              menuwindow tt = pp.p[menu];
              int nx = tt.x()+dx; if (nx < 0) {nx = 0; dx = -tt.x();}
              int ny = tt.y()+dy; if (ny < 0) {ny = 0; dy = -tt.y();}
              tt.position(nx, ny);
            }
            setitem(pp.nummenus-1, n.selected);
            goto STARTUP;
          }
        } else if (pp.nummenus > pp.menu_number+1 &&
                   pp.p[pp.menu_number+1].menu == menutable) {
          // the menu is already up:
          while (pp.nummenus > pp.menu_number+2) delete pp.p[--pp.nummenus];
          pp.p[pp.nummenus-1].set_selected(-1);
        } else {
          // delete all the old menus and create new one:
          while (pp.nummenus > pp.menu_number+1) delete pp.p[--pp.nummenus];
          pp.p[pp.nummenus++] = new menuwindow(menutable, nX, nY,
                                            title?1:0, 0, null, title, 0, menubar, cw.x());
        }
      } else { // !m.submenu():
        while (pp.nummenus > pp.menu_number+1) delete pp.p[--pp.nummenus];
        if (!pp.menu_number && pp.menubar) {
          // kludge so "menubar buttons" turn "on" by using menu title:
          fakemenu = new menuwindow(null,
                                    cw.x()+cw.titlex(pp.item_number),
                                    cw.y()+cw.h(), 0, 0,
                                    null, m, 0, 1);
          fakemenu.title.show();
        }
      }
    }
    Fl_Menu_Item* m = pp.current_item;
    Fl.release();
    delete fakemenu;
    while (pp.nummenus>1) delete pp.p[--pp.nummenus];
    mw.hide();
    return m;
  }

/+=
  const Fl_Menu_Item* test_shortcut() const;
  const Fl_Menu_Item* find_shortcut(int *ip=0) const;
=+/
  void do_callback(Fl_Widget o) {
    callback_(o, user_data_);
  }

  void do_callback(Fl_Widget o,void* arg) {
    callback_(o, arg);
  }

  void do_callback(Fl_Widget o, int arg) {
    callback_(o, cast(void*)arg);
  }

  // back-compatability, do not use:
  int checked() {
    return flags&FL_MENU_VALUE;
  }

  void check() {
    flags |= FL_MENU_VALUE;
  }

  void uncheck() {
    flags &= ~FL_MENU_VALUE;
  }
/+=
  int add(char[] a, int shortcut, Fl_Callback c, void* d=0, int e= 0);
  int add(const char*a, const char* b, Fl_Callback* c,
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

enum {	// back-compatability enum:
  FL_PUP_NONE	= 0,
  FL_PUP_GREY	= FL_MENU_INACTIVE,
  FL_PUP_GRAY	= FL_MENU_INACTIVE,
  FL_MENU_BOX	= FL_MENU_TOGGLE,
  FL_PUP_BOX	= FL_MENU_TOGGLE,
  FL_MENU_CHECK	= FL_MENU_VALUE,
  FL_PUP_CHECK	= FL_MENU_VALUE,
  FL_PUP_RADIO	= FL_MENU_RADIO,
  FL_PUP_INVISIBLE = FL_MENU_INVISIBLE,
  FL_PUP_SUBMENU = FL_SUBMENU_POINTER
};

static void setitem(Fl_Menu_Item* i, int m, int n) {
  p.current_item = i;
  p.menu_number = m;
  p.item_number = n;
}

static void setitem(int m, int n) {
  menustate* pp = p;
  pp.current_item = (n >= 0) ? pp.p[m].menu.next(n) : null;
  pp.menu_number = m;
  pp.item_number = n;
}

//
// End of "$Id: menu_item.d 4288 2005-04-16 00:13:17Z mike $".
//
