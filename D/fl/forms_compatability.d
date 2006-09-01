//
// "$Id: forms_compatability.cxx 5190 2006-06-09 16:16:34Z mike $"
//
// Forms compatibility functions for the Fast Light Tool Kit (FLTK).
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

// Forms library compatability functions.
// Many more functions are defined as inlines in forms.h!

module fl.forms_compatibility;

/+=
#include <FL/forms.H>
#include <stdlib.h>
=+/

char fl_flip = 2;
/+=
void fl_end_form() {
  while (Fl_Group.current()) Fl_Group.current()->forms_end();
}

static int initargc;
static char **initargv;

void fl_initialize(int *argc, char **argv, char *, FL_CMD_OPT *, int) {
  initargc = *argc;
  initargv = new char*[*argc+1];
  int i,j;
  for (i=0; i<=*argc; i++) initargv[i] = argv[i];
  for (i=j=1; i<*argc; ) {
    if (Fl.arg(*argc,argv,i));
    else argv[j++] = argv[i++];
  }
  argv[j] = 0;
  *argc = j;
  if (fl_flip==2) fl_flip = 0;
}

char fl_modal_next; // set by fl_freeze_forms()

void fl_show_form(Fl_Window  f,int place,int b,char *n) {

  f.label(n);
  if (!b) f.clear_border();
  if (fl_modal_next || b==FL_TRANSIENT) {f.set_modal(); fl_modal_next = 0;}

  if (place & FL_PLACE_MOUSE) f.hotspot(f);

  if (place & FL_PLACE_CENTER) {
    int scr_x, scr_y, scr_w, scr_h;
    Fl.screen_xywh(scr_x, scr_y, scr_w, scr_h);
    f.position(scr_x+(scr_w-f.w())/2, scr_y+(scr_h-f.h())/2);
  }

  if (place & FL_PLACE_FULLSCREEN)
    f.fullscreen();

  if (place & (FL_PLACE_POSITION | FL_PLACE_GEOMETRY))
    f.position(
      (f.x() < 0) ? Fl.w()-f.w()+f.x()-1 : f.x(),
      (f.y() < 0) ? Fl.h()-f.h()+f.y()-1 : f.y());

// if (place & FL_PLACE_ASPECT) {
// this is not yet implemented
// it can be done by setting size_range().

  if (place == FL_PLACE_FREE || place == FL_PLACE_SIZE)
    f.free_position();

  if (place == FL_PLACE_FREE || place & FL_FREE_SIZE)
    if (!f.resizable()) f.resizable(f);

  if (initargc) {f.show(initargc,initargv); initargc = 0;}
  else f.show();
}

Fl_Widget  fl_do_forms(void) {
  Fl_Widget  obj;
  while (!(obj = Fl.readqueue())) if (!Fl.wait()) exit(0);
  return obj;
}

Fl_Widget  fl_check_forms() {
  Fl.check();
  return Fl.readqueue();
}

void fl_set_graphics_mode(int /*r*/,int /*d*/) {}

void Fl_FormsText.draw() {
  draw_box();
  alignment(alignment()|FL_ALIGN_INSIDE); // questionable method of compatability
  draw_label();
}

// Create a forms button by selecting correct fltk subclass:

private import fl.return_button;
private import fl.repeat_button;

Fl_Button  fl_add_button(ubyte t,int x,int y,int w,int h,char *l) {
  Fl_Button  b;
  switch (t) {
  case FL_RETURN_BUTTON:
  case FL_HIDDEN_RET_BUTTON:
    b = new Fl_Return_Button(x,y,w,h,l);
    break;
  case FL_TOUCH_BUTTON:
    b = new Fl_Repeat_Button(x,y,w,h,l);
    break;
  default:
    b = new Fl_Button(x,y,w,h,l);
  }
  switch (t) {
  case FL_TOGGLE_BUTTON:
  case FL_RADIO_BUTTON:
    b.type(t);
    break;
  case FL_HIDDEN_BUTTON:
  case FL_HIDDEN_RET_BUTTON:
    b.type(FL_HIDDEN_BUTTON);
    break;
  case FL_INOUT_BUTTON:
    b.when(FL_WHEN_CHANGED);
    break;
  }
  return b;
}

void fl_show_message(char *q1,char *q2,char *q3) {
  fl_message("%s\n%s\n%s", q1?q1:"", q2?q2:"", q3?q3:"");
}

void fl_show_alert(char *q1,char *q2,char *q3,int) {
  fl_alert("%s\n%s\n%s", q1?q1:"", q2?q2:"", q3?q3:"");
}

int fl_show_question(char *q1,char *q2,char *q3) {
  return fl_choice("%s\n%s\n%s", "No", "Yes", 0L, q1?q1:"", q2?q2:"", q3?q3:"");
}

int fl_show_choice(
  char *q1,
  char *q2,
  char *q3,
  int, // number of buttons, ignored
  char *b0,
  char *b1,
  char *b2) {
  return fl_choice("%s\n%s\n%s", q1?q1:"", q2?q2:"", q3?q3:"", b0,b1,b2)+1;
}

char *fl_show_simple_input(char *str1, char *defstr) {
  char *r = fl_input(str1, defstr);
  return (char *)(r ? r : defstr);
}

//
// End of "$Id: forms_compatability.cxx 5190 2006-06-09 16:16:34Z mike $".
//
    End of automatic import -+/
