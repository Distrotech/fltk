//
// "$Id: Fl_Input.cxx,v 1.30 2000/02/22 00:58:10 bill Exp $"
//
// Input widget for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-1999 by Bill Spitzak and others.
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
// Please report all bugs and problems to "fltk-bugs@easysw.com".
//

// This is the "user interface", it decodes user actions into what to
// do to the text.  See also Fl_Input_.C, where the text is actually
// manipulated (and some ui, in particular the mouse, is done...).
// In theory you can replace this code with another subclass to change
// the keybindings.

#include <FL/Fl.H>
#include <FL/Fl_Input.H>
#include <FL/fl_draw.H>
#include <string.h>

void Fl_Input::draw() {
  if (damage() & FL_DAMAGE_ALL) draw_frame();
  int X = x(); int Y = y(); int W = w(); int H = h(); box()->inset(X,Y,W,H);
  Fl_Input_::drawtext(X,Y,W,H);
}

// kludge so shift causes selection to extend:
int Fl_Input::shift_position(int p) {
  return position(p, Fl::event_state(FL_SHIFT) ? mark() : p);
}
int Fl_Input::shift_up_down_position(int p) {
  return up_down_position(p, Fl::event_state(FL_SHIFT));
}

// If you define this symbol as zero you will get the peculiar fltk
// behavior where moving off the end of an input field will move the
// cursor into the next field:
// define it as 1 to prevent cursor movement from going to next field:
#define NORMAL_INPUT_MOVE 0

#define ctrl(x) (x^0x40)

int Fl_Input::handle_key() {

  char ascii = Fl::event_text()[0];

  int del;
  if (Fl::compose(del)) {

    // Insert characters into numeric fields after checking for legality:
    if (type() == FL_FLOAT_INPUT || type() == FL_INT_INPUT) {
      Fl::compose_reset(); // ignore any foreign letters...
      // This is complex to allow "0xff12" hex to be typed:
      if (!position() && (ascii == '+' || ascii == '-') ||
	  (ascii >= '0' && ascii <= '9') ||
	  (position()==1 && index(0)=='0' && (ascii=='x' || ascii == 'X')) ||
	  (position()>1 && index(0)=='0' && (index(1)=='x'||index(1)=='X')
	   && (ascii>='A'&& ascii<='F' || ascii>='a'&& ascii<='f')) ||
	  type()==FL_FLOAT_INPUT && ascii && strchr(".eE+-", ascii))
	replace(position(), mark(), &ascii, 1);
      return 1;
    }

    replace(position(), del ? position()-del : mark(),
	    Fl::event_text(), Fl::event_length());
    return 1;
  }

  switch (Fl::event_key()) {
  case FL_Left:
    ascii = ctrl('B'); break;
  case FL_Right:
    ascii = ctrl('F'); break;
  case FL_Up:
    ascii = ctrl('P'); break;
  case FL_Down:
    ascii = ctrl('N'); break;
  case FL_Delete:
    ascii = ctrl('D'); break;
  case FL_Home:
    ascii = ctrl('A'); break;
  case FL_End:
    ascii = ctrl('E'); break;
  case FL_Enter:
  case FL_KP_Enter:
    if (when() & FL_WHEN_ENTER_KEY) {
      position(size(), 0);
      maybe_do_callback();
      return 1;
    } else if (type() == FL_MULTILINE_INPUT)
      return replace(position(), mark(), "\n", 1);
    else 
      return 0;	// reserved for shortcuts
  case FL_Tab:
    if (Fl::event_state(FL_CTRL) || type()!=FL_MULTILINE_INPUT) return 0;
    return replace(position(), mark(), &ascii, 1);
  case FL_Control_R:
  case 0xff20: // Multi-Key
    ascii = ctrl('Q'); break;
  default:
    if (!ascii) return 0; // don't reset compose on shift keys
  }

  Fl::compose_reset();

  int i;
  switch (ascii) {
  case ctrl('A'):
    if (type() == FL_MULTILINE_INPUT)
      for (i=position(); i && index(i-1)!='\n'; i--) ;
    else
      i = 0;
    return shift_position(i) + NORMAL_INPUT_MOVE;
  case ctrl('B'):
    return shift_position(position()-1) + NORMAL_INPUT_MOVE;
  case ctrl('C'): // copy
    return copy();
  case ctrl('D'):
    if (mark() != position()) return cut();
    else return cut(1);
  case ctrl('E'):
    if (type() == FL_MULTILINE_INPUT)
      for (i=position(); index(i) && index(i)!='\n'; i++) ;
    else
      i = size();
    return shift_position(i) + NORMAL_INPUT_MOVE;
  case ctrl('F'):
    return shift_position(position()+1) + NORMAL_INPUT_MOVE;
  case ctrl('H'):
    if (mark() != position()) cut();
    else cut(-1);
    return 1;
  case ctrl('K'):
    if (position()>=size()) return 0;
    if (type() == FL_MULTILINE_INPUT) {
      if (index(position()) == '\n')
	i = position() + 1;
      else 
	for (i=position()+1; index(i) && index(i) != '\n'; i++);
    } else
      i = size();
    cut(position(), i);
    return copy_cuts();
  case ctrl('N'):
    if (type()!=FL_MULTILINE_INPUT) return 0;
    for (i=position(); index(i)!='\n'; i++)
      if (!index(i)) return NORMAL_INPUT_MOVE;
    shift_up_down_position(i+1);
    return 1;
  case ctrl('P'):
    if (type()!=FL_MULTILINE_INPUT) return 0;
    for (i = position(); i > 0 && index(i-1) != '\n'; i--) ;
    if (!i) return NORMAL_INPUT_MOVE;
    shift_up_down_position(i-1);
    return 1;
  case ctrl('U'):
    return cut(0, size());
  case ctrl('V'):
  case ctrl('Y'):
    Fl::paste(*this);
    return 1;
  case ctrl('X'):
  case ctrl('W'):
    copy();
    return cut();
  case ctrl('Z'):
  case ctrl('_'):
    return undo();
  }
  return 0;
}

int Fl_Input::handle(int event) {
  switch (event) {

  case FL_ENTER: return 1; // For tooltips
  case FL_FOCUS:
    switch (Fl::event_key()) {
    case FL_Right:
      position(0);
      break;
    case FL_Left:
      position(size());
      break;
    case FL_Down:
      up_down_position(0);
      break;
    case FL_Up:
      up_down_position(size());
      break;
    case FL_Tab:
      position(size(),0);
      break;
    }
    break;

  case FL_UNFOCUS:
    Fl::compose_reset();
    break;

  case FL_SHORTCUT:
    // Typing any characters when no text field is selected causes 
    // navigation to jump to the input field:
    if (Fl::event_text()[0]<=' ') return 0;
    position(size());
    take_focus();
  case FL_KEYBOARD:
    return handle_key();

  case FL_PUSH:
    if (!focused()) {
      take_focus();
      // Windoze-style: select everything on first click:
      if (type() != FL_MULTILINE_INPUT) {
        position(size(), 0); // select everything
        return 1;
      }
    }
    Fl::compose_reset();
    break;

  case FL_RELEASE:
    if (Fl::event_button() == 2) {
      Fl::event_is_click(0); // stop double click from picking a word
      Fl::paste(*this);
    } else if (!Fl::event_is_click()) {
      // copy drag-selected text to the clipboard.
      copy();
    }
    return 1;

  }
  int X = x(); int Y = y(); int W = w(); int H = h(); box()->inset(X,Y,W,H);
  return Fl_Input_::handletext(event,X,Y,W,H);
}

Fl_Input::Fl_Input(int x, int y, int w, int h, const char *l)
  : Fl_Input_(x, y, w, h, l)
{
  style(default_style);
}

//
// End of "$Id: Fl_Input.cxx,v 1.30 2000/02/22 00:58:10 bill Exp $".
//
