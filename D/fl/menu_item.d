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
private import fl.window;
private import fl.group;
private import fl.menu_;
private import fl.menu;
private import fl.menu_window;
private import fl.labeltype;
private import fl.draw;
private import fl.shortcut;

const int FL_MENU_INACTIVE = 1;
const int FL_MENU_TOGGLE= 2;
const int FL_MENU_VALUE = 4;
const int FL_MENU_RADIO = 8;
const int FL_MENU_INVISIBLE = 0x10;
const int FL_SUBMENU_POINTER = 0x20;
const int FL_SUBMENU = 0x40;
const int FL_MENU_DIVIDER = 0x80;
const int FL_MENU_HORIZONTAL = 0x100;

static Fl_Menu_ button;

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
  Fl_Menu_Item* pulldown(
      int X, int Y, int W, int H,
      Fl_Menu_Item* initial_item=null,
      Fl_Menu_ pbutton=null,
      Fl_Menu_Item* t=null,
      int menubar=0)
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
        delete mw;
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
      if (pp.current_item is oldi) continue;}
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
  
      if (m is initial_item) initial_item=null; // stop the startup code if item found
      if (m.submenu()) {
        Fl_Menu_Item* title = m;
        Fl_Menu_Item* menutable;
        if (m.flags&FL_SUBMENU) menutable = m+1;
        else menutable = cast(Fl_Menu_Item*)m.user_data_;
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
                   pp.p[pp.menu_number+1].menu is menutable) {
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
    delete mw;
    return m;
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

const int INITIAL_STATE = 0;    // no mouse up or down since popup() called
const int PUSH_STATE = 1;       // mouse has been pushed on a normal item
const int DONE_STATE = 2;       // exit the popup, the current item was picked
const int MENU_PUSH_STATE = 3;  // mouse has been pushed on a menu title

struct menustate {
  Fl_Menu_Item* current_item; // what mouse is pointing at
  int menu_number; // which menu it is in
  int item_number; // which item in that menu, -1 if none
  menuwindow p[20]; // pointers to menus
  int nummenus;
  int menubar; // if true p[0] is a menubar
  int state;
  int is_inside(int mx, int my) {
    int i;
    for (i=nummenus-1; i>=0; i--) {
      if (p[i].is_inside(mx, my))
        return 1;
    }
    return 0;
  }
}

static menustate* p;


class menutitle : Fl_Menu_Window {
  void draw() {
    menu.draw(0, 0, w(), h(), button, 2);
  }
public:
  Fl_Menu_Item* menu;
  this(int X, int Y, int W, int H, Fl_Menu_Item* L) {
    super(X, Y, W, H, null);
    end();
    set_modal();
    clear_border();
    menu = L;
    if (L.labelcolor_ || Fl.scheme() || L.labeltype_ > FL_NO_LABEL) clear_overlay();
  }
}


class menuwindow : Fl_Menu_Window {
private:
/+=
  void draw();
  void drawentry(Fl_Menu_Item*, int i, int erase);
=+/
public:
  menutitle title;

  int handle(int e) {
    menustate* pp = p;
    switch (e) {
/+=
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
=+/
    case FL_ENTER:
    case FL_MOVE:
    case FL_PUSH:
    case FL_DRAG: {
      int mx = Fl.event_x_root();
      int my = Fl.event_y_root();
      int item=0; int mymenu = pp.nummenus-1;
      // Clicking or dragging outside menu cancels it...
      if ((!pp.menubar || mymenu) && !pp.is_inside(mx, my)) {
        setitem(null, -1, 0);
        if (e==FL_PUSH)
          pp.state = DONE_STATE;
        return 1;
      }
      for (mymenu = pp.nummenus-1; ; mymenu--) {
        item = pp.p[mymenu].find_selected(mx, my);
        if (item >= 0) break;
        if (mymenu <= 0) return 0;
      }
      if (my == 0 && item > 0) setitem(mymenu, item - 1);
      else setitem(mymenu, item);
      if (e == FL_PUSH) {
        if (pp.current_item && pp.current_item.submenu() // this is a menu title
            && item != pp.p[mymenu].selected // and it is not already on
            && !pp.current_item.callback_) // and it does not have a callback
          pp.state = MENU_PUSH_STATE;
        else
          pp.state = PUSH_STATE;
      }} return 1;
/+=
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
=+/
    default:
      break;
    }
    return super.handle(e);
  }

  int itemheight;       // zero == menubar
  int numitems;
  int selected;
  int drawn_selected;   // last redraw has this selected
  Fl_Menu_Item* menu;

  this(Fl_Menu_Item* m, int X, int Y, int Wp, int Hp,
       Fl_Menu_Item* picked, Fl_Menu_Item* t, 
       int menubar=0, int menubar_title=0, int right_edge=0) {
    super(X, Y, Wp, Hp, null);
    int scr_x, scr_y, scr_w, scr_h;
    int tx = X, ty = Y;
  
    Fl.screen_xywh(scr_x, scr_y, scr_w, scr_h);
    if (!right_edge || right_edge > scr_x+scr_w) right_edge = scr_x+scr_w;
    end();
    set_modal();
    clear_border();
    menu = m;
    if (m) m = m.first(); // find the first item that needs to be rendered
    drawn_selected = -1;
    if (button) {
      box(button.box());
      if (box() == FL_NO_BOX || box() == FL_FLAT_BOX) box(FL_UP_BOX);
    } else {
      box(FL_UP_BOX);
    }
    color(button && !Fl.scheme() ? button.color() : FL_GRAY);
    selected = -1;
    {int j = 0;
    if (m) for (Fl_Menu_Item* m1=m; ; m1 = m1.next(), j++) {
      if (picked) {
        if (m1 is picked) {selected = j; picked = null;}
        else if (m1 > picked) {selected = j-1; picked = null; Wp = Hp = 0;}
      }
      if (!m1.text) break;
    }
    numitems = j;}
  
    if (menubar) {
      itemheight = 0;
      title = null;
      return;
    }
  
    itemheight = 1;
  
    int hotKeysw = 0;
    int Wtitle = 0;
    int Htitle = 0;
    if (t) Wtitle = t.measure(&Htitle, button) + 12;
    int W = 0;
    if (m) for (; m.text; m = m.next()) {
      int hh; int w1 = m.measure(&hh, button);
      if (hh+LEADING>itemheight) itemheight = hh+LEADING;
      if (m.flags&(FL_SUBMENU|FL_SUBMENU_POINTER)) w1 += 14;
      if (w1 > W) W = w1;
      if (m.shortcut_) {
        w1 = cast(int)(fl_width(fl_shortcut_label(m.shortcut_))) + 8;
        if (w1 > hotKeysw) hotKeysw = w1;
      }
      if (m.labelcolor_ || Fl.scheme() || m.labeltype_ > FL_NO_LABEL) clear_overlay();
    }
    if (selected >= 0 && !Wp) X -= W/2;
    int BW = Fl.box_dx(box());
    W += hotKeysw+2*BW+7;
    if (Wp > W) W = Wp;
    if (Wtitle > W) W = Wtitle;
  
    if (X < scr_x) X = scr_x; if (X > scr_x+scr_w-W) X= scr_x+scr_w-W;
    x(X); w(W);
    h((numitems ? itemheight*numitems-LEADING : 0)+2*BW+3);
    if (selected >= 0)
      Y = Y+(Hp-itemheight)/2-selected*itemheight-BW;
    else {
      Y = Y+Hp;
      // if the menu hits the bottom of the screen, we try to draw
      // it above the menubar instead. We will not adjust any menu
      // that has a selected item.
      if (Y+h()>scr_y+scr_h && Y-h()>=scr_y) {
        if (Hp>1) 
          // if we know the height of the Fl_Menu_, use it
          Y = Y-Hp-h();
        else if (t)
          // assume that the menubar item height relates to the first
          // menuitem as well
          Y = Y-itemheight-h()-Fl.box_dh(box());
        else
          // draw the menu to the right
          Y = Y-h()+itemheight+Fl.box_dy(box());
      }
    }
    if (m) y(Y); else {y(Y-2); w(1); h(1);}
  
    if (t) {
      if (menubar_title) {
        int dy = Fl.box_dy(button.box())+1;
        int ht = button.h()-dy*2;
        title = new menutitle(tx, ty-ht-dy, Wtitle, ht, t);
      } else {
        int dy = 2;
        int ht = Htitle+2*BW+3;
        title = new menutitle(X, Y-ht-dy, Wtitle, ht, t);
      }
    } else
      title = null;
  }

  ~this() {
    hide();
    delete title;
  }
  void set_selected(int n) {
    if (n != selected) {selected = n; damage(FL_DAMAGE_CHILD);}
  }
  
  int find_selected(int mx, int my) {
    if (!menu || !menu.text) return -1;
    mx -= x();
    my -= y();
    if (my < 0 || my >= h()) return -1;
    if (!itemheight) { // menubar
      int xx = 3; int n = 0;
      Fl_Menu_Item* m = menu ? menu.first() : null;
      for (; ; m = m.next(), n++) {
        if (!m.text) return -1;
        xx += m.measure(null, button) + 16;
        if (xx > mx) break;
      }
      return n;
    }
    if (mx < Fl.box_dx(box()) || mx >= w()) return -1;
    int n = (my-Fl.box_dx(box())-1)/itemheight;
    if (n < 0 || n>=numitems) return -1;
    return n;
  }

  int titlex(int n) {
    Fl_Menu_Item* m;
    int xx = 3;
    for (m=menu.first(); n--; m = m.next()) xx += m.measure(null, button) + 16;
    return xx;
  }

  void autoscroll(int n) {
    int scr_x, scr_y, scr_w, scr_h;
    int Y = y()+Fl.box_dx(box())+2+n*itemheight;
  
    Fl.screen_xywh(scr_x, scr_y, scr_w, scr_h);
    if (Y <= scr_y) Y = scr_y-Y+10;
    else {
      Y = Y+itemheight-scr_h-scr_y;
      if (Y < 0) return;
      Y = -Y-10;
    }
    Fl_Menu_Window.position(x(), y()+Y);
    // y(y()+Y); // don't wait for response from X
  }

/+=
  void position(int x, int y);
=+/
  int is_inside(int mx, int my) {
    if ( mx < x_root() || mx >= x_root() + w() ||
         my < y_root() || my >= y_root() + h()) {
      return 0;
    }
    return 1;
  }
}

static void setitem(Fl_Menu_Item* i, int m, int n) {
  p.current_item = i;
  p.menu_number = m;
  p.item_number = n;
}

static void setitem(int m, int n) {
  menustate pp = *p;
  pp.current_item = (n >= 0) ? pp.p[m].menu.next(n) : null;
  pp.menu_number = m;
  pp.item_number = n;
}

static int forward(int menu) { // go to next item in menu menu if possible
  menustate pp = *p;
  // Fl_Menu_Button can geberate menu=-1. This line fixes it and selectes the first item.
  if (menu==-1) 
    menu = 0;
  menuwindow m = (pp.p[menu]);
  int item = (menu is pp.menu_number) ? pp.item_number : m.selected;
  while (++item < m.numitems) {
    Fl_Menu_Item* m1 = m.menu.next(item);
    if (m1.activevisible()) {setitem(m1, menu, item); return 1;}
  }
  return 0;
}


//
// End of "$Id: menu_item.d 4288 2005-04-16 00:13:17Z mike $".
//
