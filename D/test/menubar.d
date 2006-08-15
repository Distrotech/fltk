//
// "$Id: menubar.d 5200 2006-06-14 10:48:36Z matt $"
//
// Menubar test program for the Fast Light Tool Kit (FLTK).
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

public import fl.fl;
public import fl.box;
public import fl.window;
public import fl.menu_bar;
public import fl.toggle_button;
public import fl.menu_button;
public import fl.choice;
public import fl.draw;

private import std.string;
private import std.c.stdio;

void window_cb(Fl_Widget w, void* d) {
/+=
  puts("window callback called");
  ((Fl_Window *)w)->hide();
-+/
}

void test_cb(Fl_Widget w, void* d) {
/+=
  Fl_Menu_* mw = (Fl_Menu_*)w;
  const Fl_Menu_Item* m = mw->mvalue();
  if (!m)
    printf("NULL\n");
  else if (m->shortcut())
    printf("%s - %s\n", m->label(), fl_shortcut_label(m->shortcut()));
  else
    printf("%s\n", m->label());
-+/
}

void quit_cb(Fl_Widget w, void* d) {
/+=
  exit(0);
-+/
}

/+=
Fl_Menu_Item hugemenu[100];

Fl_Menu_Item menutable[] = [
  {"foo",0,null,null,FL_MENU_INACTIVE},
  {"&File",0,null,null,FL_SUBMENU},
    {"&Open",	FL_ALT+'o', null, null, FL_MENU_INACTIVE},
    {"&Close",	0 },
    {"&Quit",	FL_ALT+'q', &quit_cb, null, FL_MENU_DIVIDER},
    {"shortcut",'a'},
    {"shortcut",FL_SHIFT+'a'},
    {"shortcut",FL_CTRL+'a'},
    {"shortcut",FL_CTRL+FL_SHIFT+'a'},
    {"shortcut",FL_ALT+'a'},
    {"shortcut",FL_ALT+FL_SHIFT+'a'},
    {"shortcut",FL_ALT+FL_CTRL+'a'},
    {"shortcut",FL_ALT+FL_SHIFT+FL_CTRL+'a', null,null, FL_MENU_DIVIDER},
    {"shortcut",'\r'/*FL_Enter*/},
    {"shortcut",FL_CTRL+FL_Enter, null,null, FL_MENU_DIVIDER},
    {"shortcut",FL_F+1},
    {"shortcut",FL_SHIFT+FL_F+1},
    {"shortcut",FL_CTRL+FL_F+1},
    {"shortcut",FL_SHIFT+FL_CTRL+FL_F+1},
    {"shortcut",FL_ALT+FL_F+1},
    {"shortcut",FL_ALT+FL_SHIFT+FL_F+1},
    {"shortcut",FL_ALT+FL_CTRL+FL_F+1},
    {"shortcut",FL_ALT+FL_SHIFT+FL_CTRL+FL_F+1, null,null, FL_MENU_DIVIDER},
    {"&Submenus", FL_ALT+'S',	null, cast(void*)"Submenu1".ptr, FL_SUBMENU},
      {"A very long menu item"},
      {"&submenu",FL_CTRL+'S',	null, cast(void*)"submenu2".ptr, FL_SUBMENU},
	{"item 1"},
	{"item 2"},
	{"item 3"},
	{"item 4"},
	{null},
      {"after submenu"},
      {null},
    {null},
  {"&Edit",FL_F+2,null,null,FL_SUBMENU},
    {"Undo",	FL_ALT+'z'},
    {"Redo",	FL_ALT+'r',	null, null, FL_MENU_DIVIDER},
    {"Cut",	FL_ALT+'x'},
    {"Copy",	FL_ALT+'c'},
    {"Paste",	FL_ALT+'v'},
    {"Inactive",FL_ALT+'d',	null, null, FL_MENU_INACTIVE},
    {"Clear",	0,	null, null, FL_MENU_DIVIDER},
    {"Invisible",FL_ALT+'e',	null, null, FL_MENU_INVISIBLE},
    {"Preferences",0},
    {"Size",	0},
    {null},
  {"&Checkbox",FL_F+3,null,null,FL_SUBMENU},
    {"&Alpha",	FL_F+2,	null, cast(void *)1, FL_MENU_TOGGLE},
    {"&Beta",	0,	null, cast(void *)2, FL_MENU_TOGGLE},
    {"&Gamma",	0,	null, cast(void *)3, FL_MENU_TOGGLE},
    {"&Delta",	0,	null, cast(void *)4, FL_MENU_TOGGLE|FL_MENU_VALUE},
    {"&Epsilon",0,	null, cast(void *)5, FL_MENU_TOGGLE},
    {"&Pi",	0,	null, cast(void *)6, FL_MENU_TOGGLE},
    {"&Mu",	0,	null, cast(void *)7, FL_MENU_TOGGLE|FL_MENU_DIVIDER},
    {"Red",	0,	null, cast(void *)1, FL_MENU_TOGGLE, 0, 0, 0, 1},
    {"Black",	0,	null, cast(void *)1, FL_MENU_TOGGLE|FL_MENU_DIVIDER},
    {"00",	0,	null, cast(void *)1, FL_MENU_TOGGLE},
    {"000",	0,	null, cast(void *)1, FL_MENU_TOGGLE},
    {null},
  {"&Radio",0,null,null,FL_SUBMENU},
    {"&Alpha",	0,	null, cast(void *)1, FL_MENU_RADIO},
    {"&Beta",	0,	null, cast(void *)2, FL_MENU_RADIO},
    {"&Gamma",	0,	null, cast(void *)3, FL_MENU_RADIO},
    {"&Delta",	0,	null, cast(void *)4, FL_MENU_RADIO|FL_MENU_VALUE},
    {"&Epsilon",0,	null, cast(void *)5, FL_MENU_RADIO},
    {"&Pi",	0,	null, cast(void *)6, FL_MENU_RADIO},
    {"&Mu",	0,	null, cast(void *)7, FL_MENU_RADIO|FL_MENU_DIVIDER},
    {"Red",	0,	null, cast(void *)1, FL_MENU_RADIO},
    {"Black",	0,	null, cast(void *)1, FL_MENU_RADIO|FL_MENU_DIVIDER},
    {"00",	0,	null, cast(void *)1, FL_MENU_RADIO},
    {"000",	0,	null, cast(void *)1, FL_MENU_RADIO},
    {null},
  {"&Font",0,null,null,FL_SUBMENU /*, 0, FL_BOLD, 20*/},
    {"Normal",	0, null, null, 0, 0, 0, 14},
    {"Bold",	0, null, null, 0, 0, FL_BOLD, 14},
    {"Italic",	0, null, null, 0, 0, FL_ITALIC, 14},
    {"BoldItalic",0,null,null, 0, 0, FL_BOLD+FL_ITALIC, 14},
    {"Small",	0, null, null, 0, 0, FL_BOLD+FL_ITALIC, 10},
    {"Emboss",	0, null, null, 0, FL_EMBOSSED_LABEL},
    {"Engrave",	0, null, null, 0, FL_ENGRAVED_LABEL},
    {"Shadow",	0, null, null, 0, FL_SHADOW_LABEL},
    {"@->",	0, null, null, 0, FL_SYMBOL_LABEL},
    {null},
  {"E&mpty",0,null,null,FL_SUBMENU},
    {null},
  {"&Inactive", 0,	null, null, FL_MENU_INACTIVE|FL_SUBMENU},
    {"A very long menu item"},
    {"A very long menu item"},
    {null},
  {"Invisible",0,	null, null, FL_MENU_INVISIBLE|FL_SUBMENU},
    {"A very long menu item"},
    {"A very long menu item"},
    {null},
  {"&Huge", 0, null, cast(void*)hugemenu, FL_SUBMENU_POINTER},
  {"button",FL_F+4, null, null, FL_MENU_TOGGLE},
  {null}
];
=+/

/+-
Fl_Menu_Item pulldown[] = {
  {"Red",	FL_ALT+'r'},
  {"Green",	FL_ALT+'g'},
  {"Blue",	FL_ALT+'b'},
  {"Strange",	FL_ALT+'s', 0, 0, FL_MENU_INACTIVE},
  {"&Charm",	FL_ALT+'c'},
  {"Truth",	FL_ALT+'t'},
  {"Beauty",	FL_ALT+'b'},
  {0}
};
=+/
const int WIDTH = 600;
/+=
Fl_Menu_* menus[4];
=+/

int main(char[][] args) {
  //Fl::set_color(Fl_Color(15),0,0,128);
/+=
  for (int i=0; i<99; i++) {
    char buf[100];
    sprintf(buf,"item %d",i);
    hugemenu[i].text = toString(buf).dup;
  }
=+/
  Fl_Window window = new Fl_Window(WIDTH,400);
/+=
  window.callback(window_cb);
=+/
  Fl_Menu_Bar menubar = new Fl_Menu_Bar(0,0,WIDTH,30);
/+=
  menubar.menu(menutable);
  menubar.callback(test_cb);
  menus[0] = &menubar;
  Fl_Menu_Button mb1(100,100,120,25,"&menubutton"); mb1.menu(pulldown);
  mb1.tooltip("this is a menu button");
  mb1.callback(test_cb);
  menus[1] = &mb1;
  Fl_Choice ch(300,100,80,25,"&choice:"); ch.menu(pulldown);
  ch.tooltip("this is a choice menu");
  ch.callback(test_cb);
  menus[2] = &ch;
  Fl_Menu_Button mb(0,0,WIDTH,400,"&popup");
  mb.type(Fl_Menu_Button::POPUP3);
  mb.box(FL_NO_BOX);
  mb.menu(menutable);
  mb.remove(1); // delete the "File" submenu
  mb.callback(test_cb);
  menus[3] = &mb;
=+/
  Fl_Box b = new Fl_Box(200,200,200,100,"Press right button\nfor a pop-up menu");
  /+=window.resizable(mb);=+/
  window.size_range(300,400,0,400);
  window.end();
  window.show(args);
  return Fl.run();
}

//
// End of "$Id: menubar.d 5200 2006-06-14 10:48:36Z matt $".
//
