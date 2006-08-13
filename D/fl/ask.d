//
// "$Id: fl_ask.H 4279 2005-04-13 19:35:28Z mike $"
//
// Standard dialog header file for the Fast Light Tool Kit (FLTK).
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

module fl.ask;

public import fl.enumerations;
public import fl.fl;
public import fl.box;
public import fl.button;
public import fl.return_button;
public import fl.window;
public import fl.input;
public import fl.secret_input;
public import fl.draw;

private import std.c.osx.carbon.carbon;
private import std.stdio;
private import std.stdarg;
private import std.c.string;

enum {
  FL_BEEP_DEFAULT = 0,
  FL_BEEP_MESSAGE,
  FL_BEEP_ERROR,
  FL_BEEP_QUESTION,
  FL_BEEP_PASSWORD,
  FL_BEEP_NOTIFICATION
};

void fl_message_font(Fl_Font f, ubyte s) {
  fl_message_font_ = f; 
  fl_message_size_ = s;
}

static Fl_Window message_form;
static Fl_Box message;
static Fl_Box icon;
static Fl_Button[3] button;
static Fl_Input input;
static char[] iconlabel = "?";
Fl_Font fl_message_font_ = FL_HELVETICA;
ubyte fl_message_size_ = 14;

static Fl_Window makeform() {
  if (message_form) {
    message_form.size(410,103);
    return message_form;
  }
  // make sure that the dialog does not become the child of some 
  // current group
  Fl_Group previously_current_group = Fl_Group.current();
  Fl_Group.current(null);
  // create a new top level window
  Fl_Window w = message_form = new Fl_Window(410,103,"");
  // w->clear_border();
  // w->box(FL_UP_BOX);
  message = new Fl_Box(60, 25, 340, 20);
  message.alignment(FL_ALIGN_LEFT|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);
  input = new Fl_Input(60, 37, 340, 23);
  input.hide();
  {
    Fl_Box o = icon = new Fl_Box(10, 10, 50, 50);
    o.box(FL_THIN_UP_BOX);
    o.labelfont(FL_TIMES_BOLD);
    o.labelsize(34);
    o.color(FL_WHITE);
    o.labelcolor(FL_BLUE);
  }
  button[0] = new Fl_Button(310, 70, 90, 23);
  button[0].shortcut(FL_Escape);
  button[0].alignment(FL_ALIGN_INSIDE|FL_ALIGN_WRAP);
  button[1] = new Fl_Return_Button(210, 70, 90, 23);
  button[1].alignment(FL_ALIGN_INSIDE|FL_ALIGN_WRAP);
  button[2] = new Fl_Button(110, 70, 90, 23);
  button[2].alignment(FL_ALIGN_INSIDE|FL_ALIGN_WRAP);
  w.resizable(new Fl_Box(60,10,110-60,27));
  w.end();
  w.set_modal();
  Fl_Group.current(previously_current_group);
  return w;
}

/*
 * 'resizeform()' - Resize the form and widgets so that they hold everything
 *                  that is asked of them...
 */

void resizeform() {
/+=
  int	i;
  int	message_w, message_h;
  int	icon_size;
  int	button_w[3], button_h[3];
  int	x, w, h, max_w, max_h;

  fl_font(fl_message_font_, fl_message_size_);
  message_w = message_h = 0;
  fl_measure(message->label(), message_w, message_h);

  message_w += 10;
  message_h += 10;
  if (message_w < 340)
    message_w = 340;
  if (message_h < 30)
    message_h = 30;

  fl_font(button[0]->labelfont(), button[0]->labelsize());

  memset(button_w, 0, sizeof(button_w));
  memset(button_h, 0, sizeof(button_h));

  for (max_h = 25, i = 0; i < 3; i ++)
    if (button[i]->visible())
    {
      fl_measure(button[i]->label(), button_w[i], button_h[i]);

      if (i == 1)
        button_w[1] += 20;

      button_w[i] += 30;
      button_h[i] += 10;

      if (button_h[i] > max_h)
        max_h = button_h[i];
    }

  if (input->visible()) icon_size = message_h + 25;
  else icon_size = message_h;

  max_w = message_w + 10 + icon_size;
  w     = button_w[0] + button_w[1] + button_w[2] - 10;

  if (w > max_w)
    max_w = w;

  message_w = max_w - 10 - icon_size;

  w = max_w + 20;
  h = max_h + 30 + icon_size;

  message_form->size(w, h);
  message_form->size_range(w, h, w, h);

  message->resize(20 + icon_size, 10, message_w, message_h);
  icon->resize(10, 10, icon_size, icon_size);
  icon->labelsize((uchar)(icon_size - 10));
  input->resize(20 + icon_size, 10 + message_h, message_w, 25);

  for (x = w, i = 0; i < 3; i ++)
    if (button_w[i])
    {
      x -= button_w[i];
      button[i]->resize(x, h - 10 - max_h, button_w[i] - 10, max_h);

//      printf("button %d (%s) is %dx%d+%d,%d\n", i, button[i]->label(),
//             button[i]->w(), button[i]->h(),
//	     button[i]->x(), button[i]->y());
    }
=+/
}

static int innards(char[] fmt, void *ap,
  char[] b0,
  char[] b1,
  char[] b2)
{
  makeform();
  char[1024] buffer;

  fmt ~= 0; // make it a "C" string
  vsnprintf(buffer.ptr, 1024, fmt.ptr, cast(char*)ap);
  message.label(buffer[0..strlen(buffer)]);
  message.labelfont(fl_message_font_);
  message.labelsize(fl_message_size_);
  if (b0) {button[0].show(); button[0].label(b0); button[1].position(210,70);}
  else {button[0].hide(); button[1].position(310,70);}
  if (b1) {button[1].show(); button[1].label(b1);}
  else button[1].hide();
  if (b2) {button[2].show(); button[2].label(b2);}
  else button[2].hide();
  char[] prev_icon_label = icon.label().dup;
  if (!prev_icon_label) icon.label(iconlabel);

  resizeform();

  if (button[1].visible() && !input.visible()) 
    button[1].take_focus();
  message_form.hotspot(button[0]);
  message_form.show();
  int r;
  for (;;) {
    Fl_Widget o = Fl.readqueue();
    if (!o) Fl.wait();
    else if (o == button[0]) {r = 0; break;}
    else if (o == button[1]) {r = 1; break;}
    else if (o == button[2]) {r = 2; break;}
    else if (o == message_form) {r = 0; break;}
  }
  message_form.hide();
  icon.label(prev_icon_label);
  return r;
}

// pointers you can use to change FLTK to a foreign language:
char[] fl_no = "No";
char[] fl_yes= "Yes";
char[] fl_ok = "OK";
char[] fl_cancel= "Cancel";
char[] fl_close= "Close";

// fltk functions:
void fl_beep(int type=FL_BEEP_DEFAULT) {
/+-#ifdef WIN32
  switch (type) {
    case FL_BEEP_QUESTION :
    case FL_BEEP_PASSWORD :
      MessageBeep(MB_ICONQUESTION);
      break;
    case FL_BEEP_MESSAGE :
      MessageBeep(MB_ICONASTERISK);
      break;
    case FL_BEEP_NOTIFICATION :
      MessageBeep(MB_ICONASTERISK);
      break;
    case FL_BEEP_ERROR :
      MessageBeep(MB_ICONERROR);
      break;
    default :
      MessageBeep(0xFFFFFFFF);
      break;
  }
#elif defined(__APPLE__)-+/
  version (Apple) {
    switch (type) {
      case FL_BEEP_DEFAULT :
      case FL_BEEP_ERROR :
        SysBeep(30);
        break;
      default :
        break;
    }
  }
/+-#else
  switch (type) {
    case FL_BEEP_DEFAULT :
    case FL_BEEP_ERROR :
      if (!fl_display) fl_open_display();

      XBell(fl_display, 100);
      break;
    default :
      if (!fl_display) fl_open_display();

      XBell(fl_display, 50);
      break;
  }
#endif // WIN32-+/
}

void fl_message(char[] fmt, ...) {
  fl_beep(FL_BEEP_MESSAGE);
  iconlabel = "i";
  innards(fmt, _argptr, null, fl_close, null);
  iconlabel = "?";
}

void fl_alert(char[] fmt, ...) {
  fl_beep(FL_BEEP_ERROR);
  iconlabel = "!";
  innards(fmt, _argptr, null, fl_close, null);
  iconlabel = "?";
}

int fl_ask(char[] fmt, ...) {
  fl_beep(FL_BEEP_QUESTION);
  int r = innards(fmt, _argptr, fl_no, fl_yes, null);
  return r;
}

int fl_choice(char[] fmt, char[] b0, char[] b1, char[] b2, ...) {
  fl_beep(FL_BEEP_QUESTION);
  int r = innards(fmt, _argptr, b0, b1, b2);
  return r;
}

Fl_Widget fl_message_icon() {
  makeform(); 
  return icon;
}

static char[] input_innards(char[] fmt, void* ap, char[] defstr, Fl_Type type) {
  makeform();
  message.position(60,10);
  input.type(type);
  input.show();
  input.value(defstr);
  input.take_focus();

  int r = innards(fmt, ap, fl_cancel, fl_ok, null);
  input.hide();
  message.position(60,25);
  return r ? input.value() : null;
}

char[] fl_input(char[] fmt, char[] defstr, ...) {
  fl_beep(FL_BEEP_QUESTION);
  char[] r = input_innards(fmt, _argptr, defstr, FL_NORMAL_INPUT);
  return r;
}

char[] fl_password(char[] fmt, char[] defstr, ...) {
  fl_beep(FL_BEEP_PASSWORD);
  char[] r = input_innards(fmt, _argptr, defstr, FL_SECRET_INPUT);
  return r;
}

//
// End of "$Id: fl_ask.cxx 5190 2006-06-09 16:16:34Z mike $".
//
