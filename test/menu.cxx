
#include <fltk/Fl.h>
#include <fltk/Fl_Item.h>
#include <fltk/Fl_Item_Group.h>
#include <fltk/Fl_Divider.h>
#include <fltk/Fl_Window.h>
#include <fltk/Fl_Box.h>
#include <fltk/Fl_Menu_Bar.h>
#include <fltk/Fl_Menu_Button.h>
#include <fltk/Fl_Input_Browser.h>
#include <fltk/Fl_Choice.h>
#include <fltk/Fl_Button.h>
#include <fltk/fl_draw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fltk/Fl_Hor_Slider.h>
#include <fltk/Fl_String_List.h>

#define WIDTH 600
#define HEIGHT 23

void callback(Fl_Widget* w, void*) {
  Fl_Menu_* menu = (Fl_Menu_*)w;
  Fl_Widget* item = menu->item();
  printf("Callback for %s, item is %s\n",
	 menu->label() ? menu->label() : "menu bar",
	 item->label() ? item->label() : "unnamed");
  item->do_callback();
}

const char* const strings[] = {
  "This","is","a","test","of","a","menu","defined","as a","Fl_String_List"
};
Fl_String_List thelist(strings, sizeof(strings)/sizeof(*strings));

void build_hierarchy() {
  Fl_Item_Group* g = new Fl_Item_Group("submenu&1");
  new Fl_Item("Item &1");
  new Fl_Item("Item &2");
  new Fl_Item("Item &3");
  new Fl_Item("Item &4");
  g->end();
  g = new Fl_Item_Group("submenu&2");
  (new Fl_Item("Item &1"))->label_size(10);
  (new Fl_Item("Item &2"))->label_size(14);
  (new Fl_Item("Item &3"))->label_size(18);
  (new Fl_Item("Item &4"))->label_size(22);
  //g->deactivate();
  Fl_Group* g1 = new Fl_Item_Group("&nested menu");
  new Fl_Item("Item &1");
  new Fl_Item("Item &2");
  Fl_Group* g2 = new Fl_Item_Group("deeper");
  (new Fl_Item("Very low level items"))->deactivate();
  (new Fl_Item("Are here on this menu"))->deactivate();
  new Fl_Item("In this test");
  new Fl_Item("Program");
  g2->end();
  g1->end();
  g->end();
}

void quit_cb(Fl_Widget*, void*) {exit(0);}

int main(int argc, char **argv) {
  Fl_Window window(WIDTH,400);
  Fl_Menu_Bar menubar(0,0,WIDTH,HEIGHT);
  menubar.callback(callback);
  menubar.begin();

  Fl_Item_Group file("&File");
  Fl_Item* o = new Fl_Item("Quit");
  o->shortcut(FL_ALT+'q');
  o->callback(quit_cb);
  new Fl_Divider();
  (new Fl_Hor_Slider(0,0,100,30))->value(.3);
  build_hierarchy();
  file.end();
  Fl_Item_Group edit("&Edit");
  (new Fl_Item("Undo"))->shortcut(FL_ALT+'z');
  (new Fl_Item("Cut"))->shortcut(FL_ALT+'x');
  (new Fl_Item("Copy"))->shortcut(FL_ALT+'c');
  (new Fl_Item("Paste"))->shortcut(FL_ALT+'v');
  build_hierarchy();
  edit.end();
  //edit.deactivate();
  Fl_Item_Group options("&Options");
  o = new Fl_Item("Red"); o->type(Fl_Item::RADIO); o->set_flag(FL_MENU_STAYS_UP);
  o = new Fl_Item("Green"); o->type(Fl_Item::RADIO); o->set_flag(FL_MENU_STAYS_UP);
  o = new Fl_Item("Blue"); o->type(Fl_Item::RADIO); o->set_flag(FL_MENU_STAYS_UP);
  o = new Fl_Item("Aqua"); o->type(Fl_Item::RADIO); o->set_flag(FL_MENU_STAYS_UP);
  o = new Fl_Item("Toggle 1"); o->type(Fl_Item::TOGGLE); o->set_flag(FL_MENU_STAYS_UP);
  o = new Fl_Item("Toggle 2"); o->type(Fl_Item::TOGGLE); o->set_flag(FL_MENU_STAYS_UP);
  o = new Fl_Item("Toggle 3"); o->type(Fl_Item::TOGGLE); o->set_flag(FL_MENU_STAYS_UP);
  o = new Fl_Item("Toggle 4"); o->type(Fl_Item::TOGGLE); o->set_flag(FL_MENU_STAYS_UP);
  options.end();
  Fl_Item item("&Item"); item.type(Fl_Item::TOGGLE);
  menubar.end();
  menubar.tooltip("This is a menu bar");

  Fl_Box box(0,HEIGHT,WIDTH,400-HEIGHT);
  box.color(FL_WHITE);
  box.box(FL_DOWN_BOX);
  box.tooltip("Press right button for a pop-up menu");

  Fl_Menu_Button mb(0,25,WIDTH,400-HEIGHT, "popup");
  mb.callback(callback);
  mb.begin();
  build_hierarchy();
  mb.end();
  mb.type(Fl_Menu_Button::POPUP3);

  Fl_Menu_Button mb1(10,50,100,25,"&menubutton");
  mb1.callback(callback);
  mb1.begin();
  build_hierarchy();
  mb1.end();
  mb1.tooltip("This is a menu button");

  Fl_Choice ch(220,50,100,25,"&choice:");
  ch.callback(callback);
  ch.begin();
  build_hierarchy();
  ch.end();
  ch.tooltip("This is a choice");

  Fl_Input_Browser ib(410,50,100,25,"input_&browser:");
  ib.type(Fl_Input_Browser::INDENTED);
  ib.callback(callback);
  ib.begin();
  build_hierarchy();
  ib.end();
  ib.tooltip("This is an Fl_Input_Browser");

  Fl_Button button(100,100,100,30,"button");

  window.resizable(box);
  window.size_range(300,20);
  window.end();
  window.show(argc, argv);

  const Fl_Screen_Info& info = Fl::info();
  printf("info x,y,w,h = %d, %d, %d, %d\n", info.x, info.y, info.w, info.h);
  printf("info width, height, depth = %d, %d, %d\n", info.width, info.height, info.depth);
  printf("info mm %d %d\n", info.width_mm, info.height_mm);
  //printf("info dpi %g %g\n", info.dpi_x, info.dpi_y);

  return Fl::run();
}
