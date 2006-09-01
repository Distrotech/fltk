/+- This file was imported from C++ using a script
//
// "$Id: forms.H 4288 2005-04-16 00:13:17Z mike $"
//
// Forms emulation header file for the Fast Light Tool Kit (FLTK).
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

version (!__FORMS_H__) {
#define __FORMS_H__

public import fl.fl;
public import fl.group;
public import fl.window;
public import fl.fl_draw;

alias Fl_Widget FL_OBJECT;
alias Fl_Window FL_FORM;

////////////////////////////////////////////////////////////////
// Random constants & symbols defined by forms.h file:

version (!NULL) {
const int NULL = 0; 
}
version (!FALSE) {
const int FALSE = 0; 
const int TRUE = 1; 
}

const int FL_ON = 1; 
const int FL_OK = 1; 
const int FL_VALID = 1; 
const int FL_PREEMPT = 1; 
const int FL_AUTO = 2; 
const int FL_WHEN_NEEDED = FL_AUTO; 
const int FL_OFF = 0; 
const int FL_NONE = 0; 
const int FL_CANCEL = 0; 
const int FL_INVALID = 0; 
const int FL_IGNORE = -1; 
const int FL_CLOSE = -2; 

const int FL_LCOL = FL_BLACK; 
const int FL_COL1 = FL_GRAY; 
const int FL_MCOL = FL_LIGHT1; 
const int FL_LEFT_BCOL = FL_LIGHT3;  // 53 is better match
const int FL_TOP_BCOL = FL_LIGHT2;  // 51
const int FL_BOTTOM_BCOL = FL_DARK2;   // 40
const int FL_RIGHT_BCOL = FL_DARK3;   // 36
const int FL_INACTIVE = FL_INACTIVE_COLOR; 
const int FL_INACTIVE_COL = FL_INACTIVE_COLOR; 
const int FL_FREE_COL1 = FL_FREE_COLOR; 
const int FL_FREE_COL2 = ((Fl_Color)(FL_FREE_COLOR+1)); 
const int FL_FREE_COL3 = ((Fl_Color)(FL_FREE_COLOR+2)); 
const int FL_FREE_COL4 = ((Fl_Color)(FL_FREE_COLOR+3)); 
const int FL_FREE_COL5 = ((Fl_Color)(FL_FREE_COLOR+4)); 
const int FL_FREE_COL6 = ((Fl_Color)(FL_FREE_COLOR+5)); 
const int FL_FREE_COL7 = ((Fl_Color)(FL_FREE_COLOR+6)); 
const int FL_FREE_COL8 = ((Fl_Color)(FL_FREE_COLOR+7)); 
const int FL_FREE_COL9 = ((Fl_Color)(FL_FREE_COLOR+8)); 
const int FL_FREE_COL10 = ((Fl_Color)(FL_FREE_COLOR+9)); 
const int FL_FREE_COL11 = ((Fl_Color)(FL_FREE_COLOR+10)); 
const int FL_FREE_COL12 = ((Fl_Color)(FL_FREE_COLOR+11)); 
const int FL_FREE_COL13 = ((Fl_Color)(FL_FREE_COLOR+12)); 
const int FL_FREE_COL14 = ((Fl_Color)(FL_FREE_COLOR+13)); 
const int FL_FREE_COL15 = ((Fl_Color)(FL_FREE_COLOR+14)); 
const int FL_FREE_COL16 = ((Fl_Color)(FL_FREE_COLOR+15)); 
const int FL_TOMATO = ((Fl_Color)(131)); 
const int FL_INDIANRED = ((Fl_Color)(164)); 
const int FL_SLATEBLUE = ((Fl_Color)(195)); 
const int FL_DARKGOLD = ((Fl_Color)(84)); 
const int FL_PALEGREEN = ((Fl_Color)(157)); 
const int FL_ORCHID = ((Fl_Color)(203)); 
const int FL_DARKCYAN = ((Fl_Color)(189)); 
const int FL_DARKTOMATO = ((Fl_Color)(113)); 
const int FL_WHEAT = ((Fl_Color)(174)); 

const int FL_ALIGN_BESIDE = FL_ALIGN_INSIDE; 

const int FL_PUP_TOGGLE = 2;  // FL_MENU_TOGGLE
const int FL_PUP_INACTIVE = 1;  // FL_MENU_INACTIVE
const int FL_NO_FRAME = FL_NO_BOX; 
const int FL_ROUNDED3D_UPBOX = FL_ROUND_UP_BOX; 
const int FL_ROUNDED3D_DOWNBOX = FL_ROUND_DOWN_BOX; 
const int FL_OVAL3D_UPBOX = FL_ROUND_UP_BOX; 
const int FL_OVAL3D_DOWNBOX = FL_ROUND_DOWN_BOX; 

const int FL_MBUTTON1 = 1; 
const int FL_LEFTMOUSE = 1; 
const int FL_MBUTTON2 = 2; 
const int FL_MIDDLEMOUSE = 2; 
const int FL_MBUTTON3 = 3; 
const int FL_RIGHTMOUSE = 3; 
const int FL_MBUTTON4 = 4; 
const int FL_MBUTTON5 = 5; 

const int FL_INVALID_STYLE = 255; 
const int FL_NORMAL_STYLE = FL_HELVETICA; 
const int FL_BOLD_STYLE = FL_HELVETICA_BOLD; 
const int FL_ITALIC_STYLE = FL_HELVETICA_ITALIC; 
const int FL_BOLDITALIC_STYLE = FL_HELVETICA_BOLD_ITALIC; 
const int FL_FIXED_STYLE = FL_COURIER; 
const int FL_FIXEDBOLD_STYLE = FL_COURIER_BOLD; 
const int FL_FIXEDITALIC_STYLE = FL_COURIER_ITALIC; 
const int FL_FIXEDBOLDITALIC_STYLE = FL_COURIER_BOLD_ITALIC; 
const int FL_TIMES_STYLE = FL_TIMES; 
const int FL_TIMESBOLD_STYLE = FL_TIMES_BOLD; 
const int FL_TIMESITALIC_STYLE = FL_TIMES_ITALIC; 
const int FL_TIMESBOLDITALIC_STYLE = FL_TIMES_BOLD_ITALIC; 

// hacks to change the labeltype() when passed to fl_set_object_lstyle():
const int FL_SHADOW_STYLE = (FL_SHADOW_LABEL<<8); 
const int FL_ENGRAVED_STYLE = (FL_ENGRAVED_LABEL<<8); 
const int FL_EMBOSSED_STYLE = (FL_EMBOSSED_LABEL<<0); 

// size values are different from XForms, match older Forms:
const int FL_TINY_SIZE = 8; 
const int FL_SMALL_SIZE = 11;  // 10
//#define FL_NORMAL_SIZE	14 // 12
const int FL_MEDIUM_SIZE = 18;  // 14
const int FL_LARGE_SIZE = 24;  // 18
const int FL_HUGE_SIZE = 32;  // 24
const int FL_DEFAULT_SIZE = FL_SMALL_SIZE; 
const int FL_TINY_FONT = FL_TINY_SIZE; 
const int FL_SMALL_FONT = FL_SMALL_SIZE; 
const int FL_NORMAL_FONT = FL_NORMAL_SIZE; 
const int FL_MEDIUM_FONT = FL_MEDIUM_SIZE; 
const int FL_LARGE_FONT = FL_LARGE_SIZE; 
const int FL_HUGE_FONT = FL_HUGE_SIZE; 
const int FL_NORMAL_FONT1 = FL_SMALL_FONT; 
const int FL_NORMAL_FONT2 = FL_NORMAL_FONT; 
const int FL_DEFAULT_FONT = FL_SMALL_FONT; 

const int FL_RETURN_END_CHANGED = FL_WHEN_RELEASE; 
const int FL_RETURN_CHANGED = FL_WHEN_CHANGED; 
const int FL_RETURN_END = FL_WHEN_RELEASE_ALWAYS; 
const int FL_RETURN_ALWAYS = (FL_WHEN_CHANGED|FL_WHEN_NOT_CHANGED); 

const int FL_BOUND_WIDTH = 3; 

alias int FL_Coord;
alias int FL_COLOR;

////////////////////////////////////////////////////////////////
// fltk interaction:

const int FL_CMD_OPT = void; 
extern void fl_initialize(int*, char*[], char*, FL_CMD_OPT*, int);
void fl_finish() {}

alias void (*FL_IO_CALLBACK) (int, void*);
void fl_add_io_callback(int fd, short w, FL_IO_CALLBACK cb, void* v) {
  Fl.add_fd(fd,w,cb,v);}
void fl_remove_io_callback(int fd, short, FL_IO_CALLBACK) {
  Fl.remove_fd(fd);} // removes all the callbacks!

// type of callback is different and no "id" number is returned:
void fl_add_timeout(int msec, void (*cb)(void*), void* v) {
  Fl.add_timeout(msec*.001, cb, v);}
void fl_remove_timeout(int) {}

// type of callback is different!
void fl_set_idle_callback(void (*cb)()) {Fl.set_idle(cb);}

Fl_Widget  fl_do_forms(void);
Fl_Widget  fl_check_forms();
Fl_Widget  fl_do_only_forms(void) {return fl_do_forms();}
Fl_Widget  fl_check_only_forms(void) {return fl_check_forms();}

// because of new redraw behavior, these are no-ops:
void fl_freeze_object(Fl_Widget ) {}
void fl_unfreeze_object(Fl_Widget ) {}
void fl_freeze_form(Fl_Window ) {}
void fl_unfreeze_form(Fl_Window ) {}
void fl_freeze_all_forms() {}
void fl_unfreeze_all_forms() {}

void fl_set_focus_object(Fl_Window , Fl_Widget  o) {Fl.focus(o);}
void fl_reset_focus_object(Fl_Widget  o) {Fl.focus(o);}
const int fl_set_object_focus = fl_set_focus_object; 

// void fl_set_form_atclose(Fl_Window w,int (*cb)(Fl_Window ,void*),void* v)
// void fl_set_atclose(int (*cb)(Fl_Window ,void*),void*)
// fl_set_form_atactivate/atdeactivate not implemented!

////////////////////////////////////////////////////////////////
// Fl_Widget:

void fl_set_object_boxtype(Fl_Widget  o, Fl_Boxtype a) {o.box(a);}
void fl_set_object_lsize(Fl_Widget  o,int s) {o.labelsize(s);}
void fl_set_object_lstyle(Fl_Widget  o,int a) {
  o.labelfont((ubyte)a); o.labeltype((Fl_Labeltype)(a>>8));}
void fl_set_object_lcol(Fl_Widget  o, uint a) {o.labelcolor(a);}
const int fl_set_object_lcolor = fl_set_object_lcol; 
void fl_set_object_lalign(Fl_Widget  o, Fl_Align a) {o.alignment(a);}
const int fl_set_object_align = fl_set_object_lalign; 
void fl_set_object_color(Fl_Widget  o,uint a,uint b) {o.color(a,b);}
void fl_set_object_label(Fl_Widget  o, char* a) {o.label(a); o.redraw();}
void fl_set_object_position(Fl_Widget o,int x,int y) {o.position(x,y);}
void fl_set_object_size(Fl_Widget  o, int w, int h) {o.size(w,h);}
void fl_set_object_geometry(Fl_Widget  o,int x,int y,int w,int h) {o.resize(x,y,w,h);}

void fl_get_object_geometry(Fl_Widget  o,int*x,int*y,int*w,int*h) {
  *x = o.x(); *y = o.y(); *w = o.w(); *h = o.h();}
void fl_get_object_position(Fl_Widget  o,int*x,int*y) {
  *x = o.x(); *y = o.y();}

alias void (*Forms_CB)(Fl_Widget , int);
void fl_set_object_callback(Fl_Widget o,Forms_CB c,int a) {o.callback(c,a);}
const int fl_set_call_back = fl_set_object_callback; 
void fl_call_object_callback(Fl_Widget  o) {o.do_callback();}
void fl_trigger_object(Fl_Widget  o) {o.do_callback();}
void fl_set_object_return(Fl_Widget  o, int v) {
  o.when((Fl_When)(v|FL_WHEN_RELEASE));}

void fl_redraw_object(Fl_Widget  o) {o.redraw();}
void fl_show_object(Fl_Widget  o) {o.show();}
void fl_hide_object(Fl_Widget  o) {o.hide();}
void fl_free_object(Fl_Widget  x) {delete x;}
void fl_delete_object(Fl_Widget  o) {((Fl_Group )(o.parent()))->remove(*o);}
void fl_activate_object(Fl_Widget  o) {o.activate();}
void fl_deactivate_object(Fl_Widget  o) {o.deactivate();}

void fl_add_object(Fl_Window  f, Fl_Widget  x) {f.add(x);}
void fl_insert_object(Fl_Widget  o, Fl_Widget  b) {
    ((Fl_Group )(b.parent()))->insert(*o,b);}

Fl_Window  FL_ObjWin(Fl_Widget  o) {return o.window();}

////////////////////////////////////////////////////////////////
// things that appered in the demos a lot that I don't emulate, but
// I did not want to edit out of all the demos...

int fl_get_border_width() {return 3;}
void fl_set_border_width(int) {}
void fl_set_object_dblbuffer(Fl_Widget , int) {}
void fl_set_form_dblbuffer(Fl_Window , int) {}

////////////////////////////////////////////////////////////////
// Fl_Window:

void fl_free_form(Fl_Window  x) {delete x;}
void fl_redraw_form(Fl_Window  f) {f.redraw();}

Fl_Window  fl_bgn_form(Fl_Boxtype b,int w,int h) {
  Fl_Window  g = new Fl_Window(w,h,0);
  g.box(b);
  return g;
}
void fl_end_form();
void fl_addto_form(Fl_Window  f) {f.begin();}
Fl_Group  fl_bgn_group() {return new Fl_Group(0,0,0,0,0);}
void fl_end_group() {Fl_Group.current()->forms_end();}
void fl_addto_group(Fl_Widget  o) {((Fl_Group  )o)->begin();}
const int resizebox = _ddfdesign_kludge(); 

void fl_scale_form(Fl_Window  f, double x, double y) {
  f.resizable(f); f.size(int(f.w()*x),int(f.h()*y));}
void fl_set_form_position(Fl_Window  f,int x,int y) {f.position(x,y);}
void fl_set_form_size(Fl_Window  f, int w, int h) {f.size(w,h);}
void fl_set_form_geometry(Fl_Window  f,int x,int y,int w,int h) {
  f.resize(x,y,w,h);}
const int fl_set_initial_placement = fl_set_form_geometry; 
void fl_adjust_form_size(Fl_Window ) {}

void fl_show_form(Fl_Window  f,int p,int b,char* n);
enum {	// "p" argument values:
  FL_PLACE_FREE = 0,	// make resizable
  FL_PLACE_MOUSE = 1,	// mouse centered on form
  FL_PLACE_CENTER = 2,	// center of the screen
  FL_PLACE_POSITION = 4,// fixed position, resizable
  FL_PLACE_SIZE = 8,	// fixed size, normal fltk behavior
  FL_PLACE_GEOMETRY =16,// fixed size and position
  FL_PLACE_ASPECT = 32,	// keep aspect ratio (ignored)
  FL_PLACE_FULLSCREEN=64,// fill screen
  FL_PLACE_HOTSPOT = 128,// enables hotspot
  FL_PLACE_ICONIC = 256,// iconic (ignored)
  FL_FREE_SIZE=(1<<14),	// force resizable
  FL_FIX_SIZE =(1<<15)	// force off resizable
};
const int FL_PLACE_FREE_CENTER = (FL_PLACE_CENTER|FL_FREE_SIZE); 
const int FL_PLACE_CENTERFREE = (FL_PLACE_CENTER|FL_FREE_SIZE); 
enum {	// "b" arguement values:
  FL_NOBORDER = 0,
  FL_FULLBORDER,
  FL_TRANSIENT
//FL_MODAL = (1<<8)	// not implemented yet in Forms
};
void fl_set_form_hotspot(Fl_Window  w,int x,int y) {w.hotspot(x,y);}
void fl_set_form_hotobject(Fl_Window  w, Fl_Widget  o) {w.hotspot(o);}
extern char fl_flip;	// in forms.C
void fl_flip_yorigin() {fl_flip = 1;}

const int fl_prepare_form_window = fl_show_form; 
void fl_show_form_window(Fl_Window ) {}

void fl_raise_form(Fl_Window  f) {f.show();}

void fl_hide_form(Fl_Window  f) {f.hide();}
void fl_pop_form(Fl_Window  f) {f.show();}

extern char fl_modal_next; // in forms.C
void fl_activate_all_forms() {}
void fl_deactivate_all_forms() {fl_modal_next = 1;}
void fl_deactivate_form(Fl_Window w) {w.deactivate();}
void fl_activate_form(Fl_Window w) {w.activate();}

void fl_set_form_title(Fl_Window  f, char* s) {f.label(s);}
void fl_title_form(Fl_Window  f, char* s) {f.label(s);}

alias void (*Forms_FormCB)(Fl_Widget );
void fl_set_form_callback(Fl_Window  f,Forms_FormCB c) {f.callback(c);}
const int fl_set_form_call_back = fl_set_form_callback; 

void fl_init() {}
void fl_set_graphics_mode(int,int);

int fl_form_is_visible(Fl_Window  f) {return f.visible();}

int fl_mouse_button() {return Fl.event_button();}
const int fl_mousebutton = fl_mouse_button; 

const int fl_free = free; 
const int fl_malloc = malloc; 
const int fl_calloc = calloc; 
const int fl_realloc = realloc; 

////////////////////////////////////////////////////////////////
// Drawing functions.  Only usable inside an Fl_Free object?

void fl_drw_box(Fl_Boxtype b,int x,int y,int w,int h,Fl_Color bgc,int=3) {
    fl_draw_box(b,x,y,w,h,bgc);}
void fl_drw_frame(Fl_Boxtype b,int x,int y,int w,int h,Fl_Color bgc,int=3) {
    fl_draw_box(b,x,y,w,h,bgc);}

void fl_drw_text(Fl_Align alignment, int x, int y, int w, int h,
		  Fl_Color fgcolor, int size, Fl_Font style,
		  char* s) {
  fl_font(style,size);
  fl_color(fgcolor);
  fl_draw(s,x,y,w,h,alignment);
}

// this does not work except for CENTER...
void fl_drw_text_beside(Fl_Align alignment, int x, int y, int w, int h,
		  Fl_Color fgcolor, int size, Fl_Font style,
		  char* s) {
  fl_font(style,size);
  fl_color(fgcolor);
  fl_draw(s,x,y,w,h,alignment);
}

void fl_set_font_name(Fl_Font n,char* s) {Fl.set_font(n,s);}

void fl_mapcolor(Fl_Color c, ubyte r, ubyte g, ubyte b) {Fl.set_color(c,r,g,b);}

#define fl_set_clipping(x,y,w,h) fl_clip(x,y,w,h)
#define fl_unset_clipping() fl_pop_clip()

////////////////////////////////////////////////////////////////
// Forms classes:

Fl_Widget  fl_add_new(Fl_Widget  p) {return p;}
Fl_Widget  fl_add_new(ubyte t,Fl_Widget  p) {p.type(t); return p;}

#define forms_constructor(type,name) \
type* name(ubyte t,int x,int y,int w,int h,char* l) { \
 return (type*)(fl_add_new(t, new type(x,y,w,h,l)));}
#define forms_constructort(type,name) \
type* name(ubyte t,int x,int y,int w,int h,char* l) { \
 return (type*)(fl_add_new(new type(t,x,y,w,h,l)));}
#define forms_constructorb(type,name) \
type* name(Fl_Boxtype t,int x,int y,int w,int h,char* l) { \
 return (type*)(fl_add_new(new type(t,x,y,w,h,l)));}

public import fl.formsbitmap;
const int FL_NORMAL_BITMAP = FL_NO_BOX; 
forms_constructorb(Fl_FormsBitmap, fl_add_bitmap)
void fl_set_bitmap_data(Fl_Widget  o, int w, int h, ubyte* b) {
    ((Fl_FormsBitmap )o)->set(w,h,b);
}

public import fl.formspixmap;
const int FL_NORMAL_PIXMAP = FL_NO_BOX; 
forms_constructorb(Fl_FormsPixmap, fl_add_pixmap)
void fl_set_pixmap_data(Fl_Widget  o, char*const* b) {
    ((Fl_FormsPixmap )o)->set(b);
}
//void fl_set_pixmap_file(Fl_Widget , char*);
void fl_set_pixmap_align(Fl_Widget  o,Fl_Align a,int,int) {o.alignment(a);}
//void fl_set_pixmap_colorcloseness(int, int, int);

public import fl.box;
forms_constructorb(Fl_Box, fl_add_box)

public import fl.browser;
forms_constructor(Fl_Browser, fl_add_browser)

void fl_clear_browser(Fl_Widget  o) {
    ((Fl_Browser )o)->clear();}
void fl_add_browser_line(Fl_Widget  o, char* s) {
    ((Fl_Browser )o)->add(s);}
void fl_addto_browser(Fl_Widget  o, char* s) {
    ((Fl_Browser )o)->add(s);} /* should also scroll to bottom */
//void fl_addto_browser_chars(Fl_Widget , char*)
//#define fl_append_browser fl_addto_browser_chars
void fl_insert_browser_line(Fl_Widget  o, int n, char* s) {
    ((Fl_Browser )o)->insert(n,s);}
void fl_delete_browser_line(Fl_Widget  o, int n) {
    ((Fl_Browser )o)->remove(n);}
void fl_replace_browser_line(Fl_Widget  o, int n, char* s) {
    ((Fl_Browser )o)->replace(n,s);}
char* fl_get_browser_line(Fl_Widget  o, int n) {
    return (char*)(((Fl_Browser )o)->text(n));}
int fl_load_browser(Fl_Widget  o, char* f) {
    return ((Fl_Browser )o)->load(f);}
void fl_select_browser_line(Fl_Widget  o, int n) {
    ((Fl_Browser )o)->select(n,1);}
void fl_deselect_browser_line(Fl_Widget  o, int n) {
    ((Fl_Browser )o)->select(n,0);}
void fl_deselect_browser(Fl_Widget  o) {
    ((Fl_Browser )o)->deselect();}
int fl_isselected_browser_line(Fl_Widget  o, int n) {
    return ((Fl_Browser )o)->selected(n);}
int fl_get_browser_topline(Fl_Widget  o) {
    return ((Fl_Browser )o)->topline();}
int fl_get_browser(Fl_Widget  o) {
    return ((Fl_Browser )o)->value();}
int fl_get_browser_maxline(Fl_Widget  o) {
    return ((Fl_Browser )o)->size();}
//linline int fl_get_browser_screenlines(Fl_Widget );
void fl_set_browser_topline(Fl_Widget  o, int n) {
    ((Fl_Browser )o)->topline(n);}
void fl_set_browser_fontsize(Fl_Widget  o, int s) {
    ((Fl_Browser )o)->textsize(s);}
void fl_set_browser_fontstyle(Fl_Widget  o, Fl_Font s) {
    ((Fl_Browser )o)->textfont(s);}
void fl_set_browser_specialkey(Fl_Widget  o, char c) {
    ((Fl_Browser )o)->format_char(c);}
//void fl_set_browser_vscrollbar(Fl_Widget , int);
//void fl_set_browser_hscrollbar(Fl_Widget , int);
//void fl_set_browser_leftslider(Fl_Widget , int);
//#define fl_set_browser_leftscrollbar fl_set_browser_leftslider
//void fl_set_browser_line_selectable(Fl_Widget , int, int);
//void fl_get_browser_dimension(Fl_Widget ,int*,int*,int*,int*);
//void fl_set_browser_dblclick_callback(Fl_Widget ,FL_CALLBACKPTR,int);
//void fl_set_browser_xoffset(Fl_Widget , FL_Coord);
//void fl_set_browser_scrollbarsize(Fl_Widget , int, int);
void fl_setdisplayed_browser_line(Fl_Widget  o, int n, int i) {
    ((Fl_Browser )o)->display(n,i);}
int fl_isdisplayed_browser_line(Fl_Widget  o, int n) {
    return ((Fl_Browser )o)->displayed(n);}

public import fl.button;

const int FL_NORMAL_BUTTON = 0; 
const int FL_TOUCH_BUTTON = 4; 
const int FL_INOUT_BUTTON = 5; 
const int FL_RETURN_BUTTON = 6; 
const int FL_HIDDEN_RET_BUTTON = 7; 
const int FL_PUSH_BUTTON = FL_TOGGLE_BUTTON; 
const int FL_MENU_BUTTON = 9; 

Fl_Button  fl_add_button(ubyte t,int x,int y,int w,int h,char* l);
int fl_get_button(Fl_Widget  b) {return ((Fl_Button )b)->value();}
void fl_set_button(Fl_Widget  b, int v) {((Fl_Button )b)->value(v);}
int fl_get_button_numb(Fl_Widget ) {return Fl.event_button();}
void fl_set_button_shortcut(Fl_Widget  b, char* s,int=0) {
    ((Fl_Button )b)->shortcut(s);}
//#define fl_set_object_shortcut(b,s) fl_set_button_shortcut(b,s)

public import fl.light_button;
forms_constructor(Fl_Light_Button, fl_add_lightbutton)

public import fl.round_button;
forms_constructor(Fl_Round_Button, fl_add_roundbutton)
forms_constructor(Fl_Round_Button, fl_add_round3dbutton)

public import fl.check_button;
forms_constructor(Fl_Check_Button, fl_add_checkbutton)

Fl_Widget  fl_add_bitmapbutton(int t,int x,int y,int w,int h,char* l) {Fl_Widget  o = fl_add_button(t,x,y,w,h,l); return o;}
void fl_set_bitmapbutton_data(Fl_Widget  o,int a,int b,ubyte* c) {
  (new Fl_Bitmap(c,a,b))->label(o);}  // does not delete old Fl_Bitmap!

Fl_Widget  fl_add_pixmapbutton(int t,int x,int y,int w,int h,char* l) {Fl_Widget  o = fl_add_button(t,x,y,w,h,l); return o;}
void fl_set_pixmapbutton_data(Fl_Widget  o, char*const* c) {
  (new Fl_Pixmap(c))->label(o);}  // does not delete old Fl_Pixmap!

// Fl_Canvas object not yet implemented!

public import fl.chart;

forms_constructor(Fl_Chart, fl_add_chart)
void fl_clear_chart(Fl_Widget  o) {
  ((Fl_Chart )o)->clear();}
void fl_add_chart_value(Fl_Widget  o,double v,char* s,ubyte c){
  ((Fl_Chart )o)->add(v,s,c);}
void fl_insert_chart_value(Fl_Widget  o, int i, double v, char* s, ubyte c) {
  ((Fl_Chart )o)->insert(i,v,s,c);}
void fl_replace_chart_value(Fl_Widget  o, int i, double v, char* s, ubyte c) {
  ((Fl_Chart )o)->replace(i,v,s,c);}
void fl_set_chart_bounds(Fl_Widget  o, double a, double b) {
  ((Fl_Chart )o)->bounds(a,b);}
void fl_set_chart_maxnumb(Fl_Widget  o, int v) {
  ((Fl_Chart )o)->maxsize(v);}
void fl_set_chart_autosize(Fl_Widget  o, int v) {
  ((Fl_Chart )o)->autosize(v);}
void fl_set_chart_lstyle(Fl_Widget  o, Fl_Font v) {
  ((Fl_Chart )o)->textfont(v);}
void fl_set_chart_lsize(Fl_Widget  o, int v) {
  ((Fl_Chart )o)->textsize(v);}
void fl_set_chart_lcolor(Fl_Widget  o, uint v) {
  ((Fl_Chart )o)->textcolor(v);}
const int fl_set_chart_lcol = fl_set_chart_lcolor; 

public import fl.choice;

const int FL_NORMAL_CHOICE = 0; 
const int FL_NORMAL_CHOICE2 = 0; 
const int FL_DROPLIST_CHOICE = 0; 

forms_constructor(Fl_Choice, fl_add_choice)
void fl_clear_choice(Fl_Widget  o) {
    ((Fl_Choice )o)->clear();}
void fl_addto_choice(Fl_Widget  o, char* s) {
    ((Fl_Choice )o)->add(s);}
void fl_replace_choice(Fl_Widget  o, int i, char* s) {
    ((Fl_Choice )o)->replace(i-1,s);}
void fl_delete_choice(Fl_Widget  o, int i) {
    ((Fl_Choice )o)->remove(i-1);}
void fl_set_choice(Fl_Widget  o, int i) {
    ((Fl_Choice )o)->value(i-1);}
// void fl_set_choice_text(Fl_Widget , char*);
int fl_get_choice(Fl_Widget  o) {
    return ((Fl_Choice )o)->value()+1;}
// char* fl_get_choice_item_text(Fl_Widget , int);
// int fl_get_choice_maxitems(Fl_Widget );
const char* fl_get_choice_text(Fl_Widget  o) {
    return ((Fl_Choice )o)->text();}
void fl_set_choice_fontsize(Fl_Widget  o, int x) {
    ((Fl_Choice )o)->textsize(x);}
void fl_set_choice_fontstyle(Fl_Widget  o, Fl_Font x) {
    ((Fl_Choice )o)->textfont(x);}
// void fl_set_choice_item_mode(Fl_Widget , int, uint);
// void fl_set_choice_item_shortcut(Fl_Widget , int, char*);

public import fl.clock;
forms_constructort(Fl_Clock, fl_add_clock)
void fl_get_clock(Fl_Widget  o, int* h, int* m, int* s) {
    *h = ((Fl_Clock )o)->hour();
    *m = ((Fl_Clock )o)->minute();
    *s = ((Fl_Clock )o)->second();
}

public import fl.counter;
forms_constructor(Fl_Counter, fl_add_counter)
void fl_set_counter_value(Fl_Widget  o, double v) {
    ((Fl_Counter )o)->value(v);}
void fl_set_counter_bounds(Fl_Widget  o, double a, double b) {
    ((Fl_Counter )o)->bounds(a,b);}
void fl_set_counter_step(Fl_Widget  o, double a, double b) {
    ((Fl_Counter )o)->step(a,b);}
void fl_set_counter_precision(Fl_Widget  o, int v) {
    ((Fl_Counter )o)->precision(v);}
void fl_set_counter_return(Fl_Widget  o, int v) {
    ((Fl_Counter )o)->when((Fl_When)(v|FL_WHEN_RELEASE));}
double fl_get_counter_value(Fl_Widget  o) {
    return ((Fl_Counter )o)->value();}
void fl_get_counter_bounds(Fl_Widget  o, float* a, float* b) {
  *a = float(((Fl_Counter )o)->minimum());
  *b = float(((Fl_Counter )o)->maximum());
}
//void fl_set_counter_filter(Fl_Widget ,char* (*)(Fl_Widget ,double,int));

// Cursor stuff cannot be emulated because it uses X stuff
void fl_set_cursor(Fl_Window  w, Fl_Cursor c) {w.cursor(c);}
const int FL_INVISIBLE_CURSOR = FL_CURSOR_NONE; 
const int FL_DEFAULT_CURSOR = FL_CURSOR_DEFAULT; 

public import fl.dial;

const int FL_DIAL_COL1 = FL_GRAY; 
const int FL_DIAL_COL2 = 37; 

forms_constructor(Fl_Dial, fl_add_dial)
void fl_set_dial_value(Fl_Widget  o, double v) {
  ((Fl_Dial )o)->value(v);}
double fl_get_dial_value(Fl_Widget  o) {
  return ((Fl_Dial )o)->value();}
void fl_set_dial_bounds(Fl_Widget  o, double a, double b) {
  ((Fl_Dial )o)->bounds(a, b);}
void fl_get_dial_bounds(Fl_Widget  o, float* a, float* b) {
  *a = float(((Fl_Dial )o)->minimum());
  *b = float(((Fl_Dial )o)->maximum());
}
void fl_set_dial_return(Fl_Widget  o, int i) {
  ((Fl_Dial )o)->when((Fl_When)(i|FL_WHEN_RELEASE));}
void fl_set_dial_angles(Fl_Widget  o, int a, int b) {
  ((Fl_Dial )o)->angles((short)a, (short)b);}
//void fl_set_dial_cross(Fl_Widget  o, int);
// void fl_set_dial_direction(Fl_Widget  o, ubyte d) {
//   ((Fl_Dial )o)->direction(d);}
void fl_set_dial_step(Fl_Widget  o, double v) {
  ((Fl_Dial )o)->step(v);}

// Frames:

Fl_Widget  fl_add_frame(Fl_Boxtype i,int x,int y,int w,int h,char* l) {
  return fl_add_box(i,x-3,y-3,w+6,h+6,l);}

// labelframe nyi
Fl_Widget  fl_add_labelframe(Fl_Boxtype i,int x,int y,int w,int h,char* l) {
  Fl_Widget  o = fl_add_box(i,x-3,y-3,w+6,h+6,l);
  o.alignment(FL_ALIGN_TOP_LEFT);
  return o;
}

public import fl.free;
Fl_Free 
fl_add_free(int t,double x,double y,double w,double h,char* l,
	    FL_HANDLEPTR hdl) {
 return (Fl_Free )(fl_add_new(
   new Fl_Free(t,int(x),int(y),int(w),int(h),l,hdl)));
}

public import fl.fl_ask;
public import fl.fl_show_colormap;

int fl_show_question(char* c, int = 0) {return fl_choice("%s",fl_no,fl_yes,0L,c);}
void fl_show_message(char *,char *,char *);
void fl_show_alert(char *,char *,char *,int=0);
int fl_show_question(char *,char *,char *);
const char *fl_show_input(char *l,char*d=0) {return fl_input(l,d);}
/*const*/ char *fl_show_simple_input(char *label, char *deflt = 0);
int fl_show_choice(
    char *m1,
    char *m2,
    char *m3,
    int numb,
    char *b0,
    char *b1,
    char *b2);

void fl_set_goodies_font(ubyte a, ubyte b) {fl_message_font(a,b);}
const int fl_show_messages = fl_message; 
int fl_show_choices(char* c,int n,char* b1,char* b2,
			   char* b3, int) {
  return fl_show_choice(0,c,0,n,b1,b2,b3);
}

public import fl.filename;
public import fl.file_chooser;
int do_matching(char* a, char* b) {return fl_filename_match(a,b);}

// Forms-compatable file chooser (implementation in fselect.C):
char* fl_show_file_selector(char* message,char* dir,
			    char* pat,char* fname);
char*	fl_get_directory();
char*	fl_get_pattern();
char*	fl_get_filename();

public import fl.input;
forms_constructor(Fl_Input, fl_add_input)
void fl_set_input(Fl_Widget  o, char* v) {
    ((Fl_Input )o)->value(v);}
void fl_set_input_return(Fl_Widget  o, int x) {
    ((Fl_Input )o)->when((Fl_When)(x | FL_WHEN_RELEASE));}
void fl_set_input_color(Fl_Widget  o, uint a, uint b) {
    ((Fl_Input )o)->textcolor(a);
    ((Fl_Input )o)->cursor_color(b);
}
// void fl_set_input_scroll(Fl_Widget , int);
void fl_set_input_cursorpos(Fl_Widget  o, int x, int /*y*/) {
  ((Fl_Input )o)->position(x);}
// void fl_set_input_selected(Fl_Widget , int);
// void fl_set_input_selected_range(Fl_Widget , int, int);
// void fl_set_input_maxchars(Fl_Widget , int);
// void fl_set_input_format(Fl_Widget , int, int);
// void fl_set_input_hscrollbar(Fl_Widget , int);
// void fl_set_input_vscrollbar(Fl_Widget , int);
// void fl_set_input_xoffset(Fl_Widget , int);
// void fl_set_input_topline(Fl_Widget , int);
// void fl_set_input_scrollbarsize(Fl_Widget , int, int);
// int fl_get_input_topline(Fl_Widget );
// int fl_get_input_screenlines(Fl_Widget );
int fl_get_input_cursorpos(Fl_Widget  o, int*x, int*y) {
  *x = ((Fl_Input )o)->position(); *y = 0; return *x;}
// int fl_get_input_numberoflines(Fl_Widget );
// void fl_get_input_format(Fl_Widget , int*, int*);
const char* fl_get_input(Fl_Widget  o) {return ((Fl_Input )o)->value();}

public import fl.menu_button;

// types are not implemented, they all act like FL_PUSH_MENU:
const int FL_TOUCH_MENU = 0; 
const int FL_PUSH_MENU = 1; 
const int FL_PULLDOWN_MENU = 2; 
forms_constructor(Fl_Menu_Button, fl_add_menu)

void fl_clear_menu(Fl_Widget  o) {
    ((Fl_Menu_Button )o)->clear();}
void fl_set_menu(Fl_Widget  o, char* s) {
    ((Fl_Menu_Button )o)->clear(); ((Fl_Menu_Button )o)->add(s);}
void fl_addto_menu(Fl_Widget  o, char* s) {
    ((Fl_Menu_Button )o)->add(s);}
void fl_replace_menu_item(Fl_Widget  o, int i, char* s) {
    ((Fl_Menu_Button )o)->replace(i-1,s);}
void fl_delete_menu_item(Fl_Widget  o, int i) {
    ((Fl_Menu_Button )o)->remove(i-1);}
void fl_set_menu_item_shortcut(Fl_Widget  o, int i, char* s) {
    ((Fl_Menu_Button )o)->shortcut(i-1,fl_old_shortcut(s));}
void fl_set_menu_item_mode(Fl_Widget  o, int i, int x) {
    ((Fl_Menu_Button )o)->mode(i-1,x);}
void fl_show_menu_symbol(Fl_Widget , int ) {
/*    ((Fl_Menu_Button )o)->show_menu_symbol(i); */}
// void fl_set_menu_popup(Fl_Widget , int);
int fl_get_menu(Fl_Widget  o) {
    return ((Fl_Menu_Button )o)->value()+1;}
const char* fl_get_menu_item_text(Fl_Widget  o, int i) {
    return ((Fl_Menu_Button )o)->text(i);}
int fl_get_menu_maxitems(Fl_Widget  o) {
    return ((Fl_Menu_Button )o)->size();}
int fl_get_menu_item_mode(Fl_Widget  o, int i) {
    return ((Fl_Menu_Button )o)->mode(i);}
const char* fl_get_menu_text(Fl_Widget  o) {
    return ((Fl_Menu_Button )o)->text();}

public import fl.positioner;
const int FL_NORMAL_POSITIONER = 0; 
forms_constructor(Fl_Positioner, fl_add_positioner)
void fl_set_positioner_xvalue(Fl_Widget  o, double v) {
    ((Fl_Positioner )o)->xvalue(v);}
double fl_get_positioner_xvalue(Fl_Widget  o) {
    return ((Fl_Positioner )o)->xvalue();}
void fl_set_positioner_xbounds(Fl_Widget  o, double a, double b) {
    ((Fl_Positioner )o)->xbounds(a,b);}
void fl_get_positioner_xbounds(Fl_Widget  o, float* a, float* b) {
  *a = float(((Fl_Positioner )o)->xminimum());
  *b = float(((Fl_Positioner )o)->xmaximum());
}
void fl_set_positioner_yvalue(Fl_Widget  o, double v) {
    ((Fl_Positioner )o)->yvalue(v);}
double fl_get_positioner_yvalue(Fl_Widget  o) {
    return ((Fl_Positioner )o)->yvalue();}
void fl_set_positioner_ybounds(Fl_Widget  o, double a, double b) {
    ((Fl_Positioner )o)->ybounds(a,b);}
void fl_get_positioner_ybounds(Fl_Widget  o, float* a, float* b) {
  *a = float(((Fl_Positioner )o)->yminimum());
  *b = float(((Fl_Positioner )o)->ymaximum());
}
void fl_set_positioner_xstep(Fl_Widget  o, double v) {
    ((Fl_Positioner )o)->xstep(v);}
void fl_set_positioner_ystep(Fl_Widget  o, double v) {
    ((Fl_Positioner )o)->ystep(v);}
void fl_set_positioner_return(Fl_Widget  o, int v) {
    ((Fl_Positioner )o)->when((Fl_When)(v|FL_WHEN_RELEASE));}

public import fl.slider;

const int FL_HOR_BROWSER_SLIDER = FL_HOR_SLIDER; 
const int FL_VERT_BROWSER_SLIDER = FL_VERT_SLIDER; 

forms_constructort(Fl_Slider, fl_add_slider)
const int FL_SLIDER_COL1 = FL_GRAY; 
void fl_set_slider_value(Fl_Widget  o, double v) {
    ((Fl_Slider )o)->value(v);}
double fl_get_slider_value(Fl_Widget  o) {
    return ((Fl_Slider )o)->value();}
void fl_set_slider_bounds(Fl_Widget  o, double a, double b) {
    ((Fl_Slider )o)->bounds(a, b);}
void fl_get_slider_bounds(Fl_Widget  o, float* a, float* b) {
  *a = float(((Fl_Slider )o)->minimum());
  *b = float(((Fl_Slider )o)->maximum());
}
void fl_set_slider_return(Fl_Widget  o, int i) {
    ((Fl_Slider )o)->when((Fl_When)(i|FL_WHEN_RELEASE));}
void fl_set_slider_step(Fl_Widget  o, double v) {
    ((Fl_Slider )o)->step(v);}
// void fl_set_slider_increment(Fl_Widget  o, double v, double);
void fl_set_slider_size(Fl_Widget  o, double v) {
    ((Fl_Slider )o)->slider_size(v);}

public import fl.value_slider;
forms_constructor(Fl_Value_Slider, fl_add_valslider)

void fl_set_slider_precision(Fl_Widget  o, int i) {
    ((Fl_Value_Slider )o)->precision(i);}
// filter function!

// The forms text object was the same as an Fl_Box except it inverted the
// meaning of FL_ALIGN_INSIDE.  Implementation in forms.cxx
class Fl_FormsText : Fl_Widget {
protected:
    void draw();
public:
    Fl_FormsText(Fl_Boxtype b, int X, int Y, int W, int H, char* l=0)
	: Fl_Widget(X,Y,W,H,l) {box(b); alignment(FL_ALIGN_LEFT);}
};
const int FL_NORMAL_TEXT = FL_NO_BOX; 
forms_constructorb(Fl_FormsText, fl_add_text)

public import fl.timer;
forms_constructort(Fl_Timer, fl_add_timer)
void fl_set_timer(Fl_Widget  o, double v) {((Fl_Timer )o)->value(v);}
double fl_get_timer(Fl_Widget  o) {return ((Fl_Timer )o)->value();}
void fl_suspend_timer(Fl_Widget  o) {((Fl_Timer )o)->suspended(1);}
void fl_resume_timer(Fl_Widget  o) {((Fl_Timer )o)->suspended(0);}
void fl_set_timer_countup(Fl_Widget  o,char d) {((Fl_Timer )o)->direction(d);}
void fl_gettime(int* sec, int* usec);

// Fl_XYPlot nyi


// stuff from DDForms:

int fl_double_click() {return Fl.event_clicks();}
void fl_draw() {Fl.flush();}

}	/* define __FORMS_H__ */

//
// End of "$Id: forms.H 4288 2005-04-16 00:13:17Z mike $".
//
    End of automatic import -+/
