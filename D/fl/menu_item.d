/+- This file was imported from C++ using a script
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

version (__APPLE__) && defined(check) {
#    undef check
}

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

extern int fl_old_shortcut(char*);

class Fl_Menu_;

struct Fl_Menu_Item {
  char *text;	// label()
  int shortcut_;
  Fl_Callback  callback_;
  void *user_data_;
  int flags;
  ubyte labeltype_;
  ubyte labelfont_;
  ubyte labelsize_;
  uint labelcolor_;

  // advance N items, skipping submenus:
  Fl_Menu_Item *next(int=1) const;
  Fl_Menu_Item *next(int i=1) {
    return (Fl_Menu_Item*)(((Fl_Menu_Item*)this)->next(i));}
  Fl_Menu_Item *first() { return next(0); }
  Fl_Menu_Item *first() { return next(0); }

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
  void* user_data() {return user_data_;}
  void user_data(void* v) {user_data_ = v;}
  int argument() {return (int)user_data_;}
  void argument(int v) {user_data_ = (void*)v;}
  int shortcut() {return shortcut_;}
  void shortcut(int s) {shortcut_ = s;}
  int submenu() {return flags&(FL_SUBMENU|FL_SUBMENU_POINTER);}
  int checkbox() {return flags&FL_MENU_TOGGLE;}
  int radio() {return flags&FL_MENU_RADIO;}
  int value() {return flags&FL_MENU_VALUE;}
  void set() {flags |= FL_MENU_VALUE;}
  void clear() {flags &= ~FL_MENU_VALUE;}
  void setonly();
  int visible() {return !(flags&FL_MENU_INVISIBLE);}
  void show() {flags &= ~FL_MENU_INVISIBLE;}
  void hide() {flags |= FL_MENU_INVISIBLE;}
  int active() {return !(flags&FL_MENU_INACTIVE);}
  void activate() {flags &= ~FL_MENU_INACTIVE;}
  void deactivate() {flags |= FL_MENU_INACTIVE;}
  int activevisible() {return !(flags&0x11);}

  // compatibility for FLUID so it can set the image of a menu item...
  void image(Fl_Image  a) {a.label(this);}
  void image(Fl_Image  a) {a.label(this);}

  // used by menubar:
  int measure(int* h, Fl_Menu_ ) const;
  void draw(int x, int y, int w, int h, Fl_Menu_ , int t=0) const;

  // popup menus without using an Fl_Menu_ widget:
  Fl_Menu_Item* popup(
    int X, int Y,
    char *title = 0,
    Fl_Menu_Item* picked=0,
    Fl_Menu_  = 0) const;
  Fl_Menu_Item* pulldown(
    int X, int Y, int W, int H,
    Fl_Menu_Item* picked = 0,
    Fl_Menu_  = 0,
    Fl_Menu_Item* title = 0,
    int menubar=0) const;
  Fl_Menu_Item* test_shortcut() const;
  Fl_Menu_Item* find_shortcut(int *ip=0) const;

  void do_callback(Fl_Widget  o) {callback_(o, user_data_);}
  void do_callback(Fl_Widget  o,void* arg) {callback_(o, arg);}
  void do_callback(Fl_Widget  o,int arg) {callback_(o, (void*)arg);}

  // back-compatability, do not use:
  int checked() {return flags&FL_MENU_VALUE;}
  void check() {flags |= FL_MENU_VALUE;}
  void uncheck() {flags &= ~FL_MENU_VALUE;}
  int add(char*, int shortcut, Fl_Callback , void* =0, int = 0);
  int add(char*a, char* b, Fl_Callback  c,
	  void* d = 0, int e = 0) {
    return add(a,fl_old_shortcut(b),c,d,e);}
  int size() ;
};

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

}

//
// End of "$Id: menu_item.d 4288 2005-04-16 00:13:17Z mike $".
//
    End of automatic import -+/
