/+- This file was imported from C++ using a script
//
// "$Id: fl_shortcut.cxx 5190 2006-06-09 16:16:34Z mike $"
//
// Shortcut support routines for the Fast Light Tool Kit (FLTK).
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

// Code to test and parse fltk shortcut numbers.
//
// A shortcut is a keysym or'd with shift flags.  In the simplest
// sense a shortcut is matched if the shift state is exactly as
// given and the key returning that keysym is pressed.
//
// To make it easier to match some things it is more complex:
//
// Only FL_META, FL_ALT, FL_SHIFT, and FL_CTRL must be "off".  A
// zero in the other shift flags indicates "dont care".
//
// It also checks against the first character of Fl::event_text(),
// and zero for FL_SHIFT means "don't care".
// This allows punctuation shortcuts like "#" to work (rather than
// calling it "shift+3")
-+/

public import fl.fl;
public import fl.enumerations;

public import std.string;

/+-
#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Button.H>
#include <FL/fl_draw.H>
#include <ctype.h>
#include "flstring.h"
#if !defined(WIN32) && !defined(__APPLE__)
#include <FL/x.H>
#endif

#if defined(WIN32) || defined(__APPLE__) // if not X
// This table must be in numeric order by fltk (X) keysym number:
struct Keyname {int key; const char* name;};
static Keyname table[] = {
  {' ', "Space"},
  {FL_BackSpace, "Backspace"},
  {FL_Tab,	"Tab"},
  {0xff0b/*XK_Clear*/, "Clear"},
  {FL_Enter,	"Enter"}, // X says "Enter"
  {FL_Pause,	"Pause"},
  {FL_Scroll_Lock, "Scroll_Lock"},
  {FL_Escape,	"Escape"},
  {FL_Home,	"Home"},
  {FL_Left,	"Left"},
  {FL_Up,	"Up"},
  {FL_Right,	"Right"},
  {FL_Down,	"Down"},
  {FL_Page_Up,	"Page_Up"}, // X says "Prior"
  {FL_Page_Down,"Page_Down"}, // X says "Next"
  {FL_End,	"End"},
  {FL_Print,	"Print"},
  {FL_Insert,	"Insert"},
  {FL_Menu,	"Menu"},
  {FL_Num_Lock,	"Num_Lock"},
  {FL_KP_Enter,	"KP_Enter"},
  {FL_Shift_L,	"Shift_L"},
  {FL_Shift_R,	"Shift_R"},
  {FL_Control_L,"Control_L"},
  {FL_Control_R,"Control_R"},
  {FL_Caps_Lock,"Caps_Lock"},
  {FL_Meta_L,	"Meta_L"},
  {FL_Meta_R,	"Meta_R"},
  {FL_Alt_L,	"Alt_L"},
  {FL_Alt_R,	"Alt_R"},
  {FL_Delete,	"Delete"}
};
#endif

const char * fl_shortcut_label(int shortcut) {
  static char buf[20];
  char *p = buf;
  if (!shortcut) {*p = 0; return buf;}
  // fix upper case shortcuts
  int v = shortcut & 0xffff;
#ifdef __APPLE__
  if (v > 32 && v < 0x7f || v >= 0x80 && v <= 0xff) {
#else
  if (v > 32 && v < 0x7f || v >= 0xa0 && v <= 0xff) {
#endif
    if (isupper(v)) {
      shortcut |= FL_SHIFT;
    }
  }
#ifdef __APPLE__
  // \todo Mac :  we might want to change the symbols for Mac users - consider drawing Apple Symbols... .
  if (shortcut & FL_SHIFT) {strcpy(p,"Shift+"); p += 6;} //: Mac hollow up arrow
  if (shortcut & FL_META)  {strcpy(p,"Cmd+"); p += 4;}  //: Mac 'Apple' key
  if (shortcut & FL_ALT)   {strcpy(p,"Option+"); p += 7;}   //: Mac 'Alt/Option' or fancy switch symbol
  if (shortcut & FL_CTRL)  {strcpy(p,"Ctrl+"); p += 5;}  //: Mac ctrl key
#else
  if (shortcut & FL_META) {strcpy(p,"Meta+"); p += 5;}
  if (shortcut & FL_ALT) {strcpy(p,"Alt+"); p += 4;}
  if (shortcut & FL_SHIFT) {strcpy(p,"Shift+"); p += 6;}
  if (shortcut & FL_CTRL) {strcpy(p,"Ctrl+"); p += 5;}
#endif // __APPLE__
  int key = shortcut & 0xFFFF;
#if defined(WIN32) || defined(__APPLE__) // if not X
  if (key >= FL_F && key <= FL_F_Last) {
    *p++ = 'F';
    if (key > FL_F+9) *p++ = (key-FL_F)/10+'0';
    *p++ = (key-FL_F)%10 + '0';
  } else {
    // binary search the table for a match:
    int a = 0;
    int b = sizeof(table)/sizeof(*table);
    while (a < b) {
      int c = (a+b)/2;
      if (table[c].key == key) {
	if (p > buf) {strcpy(p,table[c].name); return buf;}
	return table[c].name;
      }
      if (table[c].key < key) a = c+1;
      else b = c;
    }
    if (key >= FL_KP && key <= FL_KP_Last) {
      // mark keypad keys with KP_ prefix
      strcpy(p,"KP_"); p += 3;
      *p++ = uchar(key & 127);
    } else {
      // if none found, use the keystroke as a match:
      *p++ = uchar(toupper(key & 255));
    }
  }
  *p = 0;
  return buf;
#else
  const char* q;
  if (key == FL_Enter || key == '\r') q="Enter";  // don't use Xlib's "Return":
  else if (key > 32 && key < 0x100) q = 0;
  else q = XKeysymToString(key);
  if (!q) {*p++ = uchar(toupper(key & 255)); *p = 0; return buf;}
  if (p > buf) {strcpy(p,q); return buf;} else return q;
#endif
}

// Emulation of XForms named shortcuts
#include <stdlib.h>
-+/
int fl_old_shortcut(char[] s) {
  if (!s || !s.length) return 0;
  int n = 0, i = 0, len = s.length;
  if (i<len && s[i] == '#') {n |= FL_ALT; i++;}
  if (i<len && s[i] == '+') {n |= FL_SHIFT; i++;}
  if (i<len && s[i] == '^') {n |= FL_CTRL; i++;}
  if (i<len+1) return n | atoi(s[i..$]); // allow 0xf00 to get any key
  return n | s[i];
}

//
// End of "$Id: fl_shortcut.cxx 5190 2006-06-09 16:16:34Z mike $".
//
