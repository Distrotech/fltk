//
// "$Id: enumerations.h 5271 2006-07-27 19:26:11Z mike $"
//
// Enumerations for the Fast Light Tool Kit (FLTK).
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

module fl.enumerations;

private import fl.color;

/+=
//
// The FLTK version number; this is changed slightly from the beta versions
// because the old "double" definition would not allow for conditional
// compilation...
//
// FL_VERSION is a double that describes the major and minor version numbers.
// Version 1.1 is actually stored as 1.01 to allow for more than 9 minor
// releases.
//
// The FL_MAJOR_VERSION, FL_MINOR_VERSION, and FL_PATCH_VERSION constants
// give the integral values for the major, minor, and patch releases
// respectively.
//

const int FL_MAJOR_VERSION = 1; 
const int FL_MINOR_VERSION = 1; 
const int FL_PATCH_VERSION = 8; 
const int FL_VERSION = ((double)FL_MAJOR_VERSION + \; 
				 (double)FL_MINOR_VERSION * 0.01 + \
				 (double)FL_PATCH_VERSION * 0.0001)

=+/

alias int Fl_Event;
const Fl_Event FL_NO_EVENT	= 0;
const Fl_Event FL_PUSH		= 1;
const Fl_Event FL_RELEASE	= 2;
const Fl_Event FL_ENTER		= 3;
const Fl_Event FL_LEAVE		= 4;
const Fl_Event FL_DRAG		= 5;
const Fl_Event FL_FOCUS		= 6;
const Fl_Event FL_UNFOCUS	= 7;
const Fl_Event FL_KEYDOWN	= 8;
const Fl_Event FL_KEYBOARD	= 8;
const Fl_Event FL_KEYUP		= 9;
const Fl_Event FL_CLOSE		= 10;
const Fl_Event FL_MOVE		= 11;
const Fl_Event FL_SHORTCUT	= 12;
const Fl_Event FL_DEACTIVATE	= 13;
const Fl_Event FL_ACTIVATE	= 14;
const Fl_Event FL_HIDE		= 15;
const Fl_Event FL_SHOW		= 16;
const Fl_Event FL_PASTE		= 17;
const Fl_Event FL_SELECTIONCLEAR= 18;
const Fl_Event FL_MOUSEWHEEL	= 19;
const Fl_Event FL_DND_ENTER	= 20;
const Fl_Event FL_DND_DRAG	= 21;
const Fl_Event FL_DND_LEAVE	= 22;
const Fl_Event FL_DND_RELEASE	= 23;

alias ubyte Fl_When;
const Fl_When FL_WHEN_NEVER	= 0;
const Fl_When FL_WHEN_CHANGED	= 1;
const Fl_When FL_WHEN_RELEASE	= 4;
const Fl_When FL_WHEN_RELEASE_ALWAYS= 6;
const Fl_When FL_WHEN_ENTER_KEY	= 8;
const Fl_When FL_WHEN_ENTER_KEY_ALWAYS=10;
const Fl_When FL_WHEN_ENTER_KEY_CHANGED=11;
const Fl_When FL_WHEN_NOT_CHANGED= 2; // modifier bit to disable changed() test

// Fl.event_key() and Fl.get_key(n) (use ascii letters for all other keys):
const int FL_Button = 0xfee8;  // use Fl_Button+FL_*_MOUSE
const int FL_BackSpace = 0xff08; 
const int FL_Tab = 0xff09; 
const int FL_Enter = 0xff0d; 
const int FL_Pause = 0xff13; 
const int FL_Scroll_Lock = 0xff14; 
const int FL_Escape = 0xff1b; 
const int FL_Home = 0xff50; 
const int FL_Left = 0xff51; 
const int FL_Up = 0xff52; 
const int FL_Right = 0xff53; 
const int FL_Down = 0xff54; 
const int FL_Page_Up = 0xff55; 
const int FL_Page_Down = 0xff56; 
const int FL_End = 0xff57; 
const int FL_Print = 0xff61; 
const int FL_Insert = 0xff63; 
const int FL_Menu = 0xff67;  // the "menu/apps" key on XFree86
const int FL_Help = 0xff68;  // the 'help' key on Mac keyboards
const int FL_Num_Lock = 0xff7f; 
const int FL_KP = 0xff80;  // use FL_KP+'x' for 'x' on numeric keypad
const int FL_KP_Enter = 0xff8d;  // same as Fl_KP+'\r'
const int FL_KP_Last = 0xffbd;  // use to range-check keypad
const int FL_F = 0xffbd;  // use FL_F+n for function key n
const int FL_F_Last = 0xffe0;  // use to range-check function keys
const int FL_Shift_L = 0xffe1; 
const int FL_Shift_R = 0xffe2; 
const int FL_Control_L = 0xffe3; 
const int FL_Control_R = 0xffe4; 
const int FL_Caps_Lock = 0xffe5; 
const int FL_Meta_L = 0xffe7;  // the left MSWindows key on XFree86
const int FL_Meta_R = 0xffe8;  // the right MSWindows key on XFree86
const int FL_Alt_L = 0xffe9; 
const int FL_Alt_R = 0xffea; 
const int FL_Delete = 0xffff; 

// Fl.event_button():
const int FL_LEFT_MOUSE = 1; 
const int FL_MIDDLE_MOUSE = 2; 
const int FL_RIGHT_MOUSE = 3; 

// Fl.event_state():
const int FL_SHIFT = 0x00010000; 
const int FL_CAPS_LOCK = 0x00020000; 
const int FL_CTRL = 0x00040000; 
const int FL_ALT = 0x00080000; 
const int FL_NUM_LOCK = 0x00100000;  // most X servers do this?
const int FL_META = 0x00400000;  // correct for XFree86
const int FL_SCROLL_LOCK = 0x00800000;  // correct for XFree86
const int FL_BUTTON1 = 0x01000000; 
const int FL_BUTTON2 = 0x02000000; 
const int FL_BUTTON3 = 0x04000000; 
const int FL_BUTTONS = 0x7f000000;  // All possible buttons

int FL_BUTTON(int n) {
  return (0x00800000<<(n));
}

version (__APPLE__) {
  const int FL_COMMAND = FL_META; 
} else {
  const int FL_COMMAND = FL_CTRL; 
} // __APPLE__

alias ubyte Fl_Boxtype;
const Fl_Boxtype FL_NO_BOX = 0;	
const Fl_Boxtype FL_FLAT_BOX = 1;
const Fl_Boxtype FL_UP_BOX = 2;		
const Fl_Boxtype FL_DOWN_BOX = 3;
const Fl_Boxtype FL_UP_FRAME = 4;		
const Fl_Boxtype FL_DOWN_FRAME = 5;
const Fl_Boxtype FL_THIN_UP_BOX = 6;	
const Fl_Boxtype FL_THIN_DOWN_BOX = 7;
const Fl_Boxtype FL_THIN_UP_FRAME = 8;	
const Fl_Boxtype FL_THIN_DOWN_FRAME = 9;
const Fl_Boxtype FL_ENGRAVED_BOX = 10;	
const Fl_Boxtype FL_EMBOSSED_BOX = 11;
const Fl_Boxtype FL_ENGRAVED_FRAME = 12;	
const Fl_Boxtype FL_EMBOSSED_FRAME = 13;
const Fl_Boxtype FL_BORDER_BOX = 14;	
const Fl_Boxtype FL_SHADOW_BOX = 15;
const Fl_Boxtype FL_BORDER_FRAME = 16;	
const Fl_Boxtype FL_SHADOW_FRAME = 17;
const Fl_Boxtype FL_ROUNDED_BOX = 18;	
const Fl_Boxtype FL_RSHADOW_BOX = 19;
const Fl_Boxtype FL_ROUNDED_FRAME = 20;	
const Fl_Boxtype FL_RFLAT_BOX = 21;
const Fl_Boxtype FL_ROUND_UP_BOX = 22;	
const Fl_Boxtype FL_ROUND_DOWN_BOX = 23;
const Fl_Boxtype FL_DIAMOND_UP_BOX = 24;	
const Fl_Boxtype FL_DIAMOND_DOWN_BOX = 25;
const Fl_Boxtype FL_OVAL_BOX = 26;		
const Fl_Boxtype FL_OSHADOW_BOX = 27;
const Fl_Boxtype FL_OVAL_FRAME = 28;	
const Fl_Boxtype FL_OFLAT_BOX = 29;
const Fl_Boxtype FL_PLASTIC_UP_BOX = 30;	
const Fl_Boxtype FL_PLASTIC_DOWN_BOX = 31;
const Fl_Boxtype FL_PLASTIC_UP_FRAME = 32;	
const Fl_Boxtype FL_PLASTIC_DOWN_FRAME = 33;
const Fl_Boxtype FL_PLASTIC_THIN_UP_BOX = 34;	
const Fl_Boxtype FL_PLASTIC_THIN_DOWN_BOX = 35;
const Fl_Boxtype FL_PLASTIC_ROUND_UP_BOX = 36;	
const Fl_Boxtype FL_PLASTIC_ROUND_DOWN_BOX = 37;
const Fl_Boxtype FL_FREE_BOXTYPE = 38;

// conversions of box types to other boxtypes:
Fl_Boxtype fl_down(Fl_Boxtype b) {return (b|1);}
Fl_Boxtype fl_frame(Fl_Boxtype b) {return (b|2);}

// back-compatability box types:
const Fl_Boxtype FL_FRAME = FL_ENGRAVED_FRAME; 
const Fl_Boxtype FL_FRAME_BOX = FL_ENGRAVED_BOX; 
const Fl_Boxtype FL_CIRCLE_BOX = FL_ROUND_DOWN_BOX; 
const Fl_Boxtype FL_DIAMOND_BOX = FL_DIAMOND_DOWN_BOX; 

alias ubyte Fl_Labeltype;
const Fl_Labeltype FL_NORMAL_LABEL = 0;
const Fl_Labeltype FL_NO_LABEL = 1;
const Fl_Labeltype FL_SHADOW_LABEL = 2;
const Fl_Labeltype FL_ENGRAVED_LABEL = 3;
const Fl_Labeltype FL_EMBOSSED_LABEL = 4;
const Fl_Labeltype FL_MULTI_LABEL = 5;
const Fl_Labeltype FL_ICON_LABEL = 6;
const Fl_Labeltype FL_IMAGE_LABEL = 7;
const Fl_Labeltype FL_FREE_LABELTYPE = 8;

alias ubyte Fl_Align;
const Fl_Align FL_ALIGN_CENTER		= 0;
const Fl_Align FL_ALIGN_TOP		= 1;
const Fl_Align FL_ALIGN_BOTTOM		= 2;
const Fl_Align FL_ALIGN_LEFT		= 4;
const Fl_Align FL_ALIGN_RIGHT		= 8;
const Fl_Align FL_ALIGN_INSIDE		= 16;
const Fl_Align FL_ALIGN_TEXT_OVER_IMAGE	= 32;
const Fl_Align FL_ALIGN_IMAGE_OVER_TEXT	= 0;
const Fl_Align FL_ALIGN_CLIP		= 64;
const Fl_Align FL_ALIGN_WRAP		= 128;
const Fl_Align FL_ALIGN_TOP_LEFT	= FL_ALIGN_TOP | FL_ALIGN_LEFT;
const Fl_Align FL_ALIGN_TOP_RIGHT	= FL_ALIGN_TOP | FL_ALIGN_RIGHT;
const Fl_Align FL_ALIGN_BOTTOM_LEFT	= FL_ALIGN_BOTTOM | FL_ALIGN_LEFT;
const Fl_Align FL_ALIGN_BOTTOM_RIGHT	= FL_ALIGN_BOTTOM | FL_ALIGN_RIGHT;
const Fl_Align FL_ALIGN_LEFT_TOP	= FL_ALIGN_TOP_LEFT;
const Fl_Align FL_ALIGN_RIGHT_TOP	= FL_ALIGN_TOP_RIGHT;
const Fl_Align FL_ALIGN_LEFT_BOTTOM	= FL_ALIGN_BOTTOM_LEFT;
const Fl_Align FL_ALIGN_RIGHT_BOTTOM	= FL_ALIGN_BOTTOM_RIGHT;
const Fl_Align FL_ALIGN_NOWRAP		= 0; // for back compatability

alias ubyte Fl_Font;
const Fl_Font FL_HELVETICA = 0;
const Fl_Font FL_HELVETICA_BOLD = 1;
const Fl_Font FL_HELVETICA_ITALIC = 2;
const Fl_Font FL_HELVETICA_BOLD_ITALIC = 3;
const Fl_Font FL_COURIER = 4;
const Fl_Font FL_COURIER_BOLD = 5;
const Fl_Font FL_COURIER_ITALIC = 6;
const Fl_Font FL_COURIER_BOLD_ITALIC = 7;
const Fl_Font FL_TIMES = 8;
const Fl_Font FL_TIMES_BOLD = 9;
const Fl_Font FL_TIMES_ITALIC = 10;
const Fl_Font FL_TIMES_BOLD_ITALIC = 11;
const Fl_Font FL_SYMBOL = 12;
const Fl_Font FL_SCREEN = 13;
const Fl_Font FL_SCREEN_BOLD = 14;
const Fl_Font FL_ZAPF_DINGBATS = 15;

const Fl_Font FL_FREE_FONT	= 16;	// first one to allocate
const Fl_Font FL_BOLD		= 1;	// add this to helvetica, courier, or times
const Fl_Font FL_ITALIC		= 2;	// add this to helvetica = ; courier, or times

const int FL_NORMAL_SIZE = 14;

alias uint Fl_Color;
  // These are used as default colors in widgets and altered as necessary
const Fl_Color FL_FOREGROUND_COLOR   = 0;
const Fl_Color FL_BACKGROUND2_COLOR  = 7;
const Fl_Color FL_INACTIVE_COLOR	= 8;
const Fl_Color FL_SELECTION_COLOR	= 15;

  // boxtypes generally limit themselves to these colors so
  // the whole ramp is not allocated:
const Fl_Color FL_GRAY0		= 32;	// 'A'
const Fl_Color FL_DARK3		= 39;	// 'H'
const Fl_Color FL_DARK2		= 45;   // 'N'
const Fl_Color FL_DARK1		= 47;	// 'P'
const Fl_Color FL_BACKGROUND_COLOR = 49;	// 'R' default background color
const Fl_Color FL_LIGHT1	= 50;	// 'S'
const Fl_Color FL_LIGHT2	= 52;	// 'U'
const Fl_Color FL_LIGHT3	= 54;	// 'W'

  // FLTK provides a 5x8x5 color cube that is used with colormap visuals
const Fl_Color FL_BLACK		= 56;
const Fl_Color FL_RED		= 88;
const Fl_Color FL_GREEN		= 63;
const Fl_Color FL_YELLOW	= 95;
const Fl_Color FL_BLUE		= 216;
const Fl_Color FL_MAGENTA	= 248;
const Fl_Color FL_CYAN		= 223;
const Fl_Color FL_DARK_RED	= 72;

const Fl_Color FL_DARK_GREEN	= 60;
const Fl_Color FL_DARK_YELLOW	= 76;
const Fl_Color FL_DARK_BLUE	= 136;
const Fl_Color FL_DARK_MAGENTA	= 152;
const Fl_Color FL_DARK_CYAN	= 140;

const Fl_Color FL_WHITE		= 255;

const Fl_Color FL_FREE_COLOR = 16; 
const int FL_NUM_FREE_COLOR = 16; 
const Fl_Color FL_GRAY_RAMP = 32; 
const int FL_NUM_GRAY = 24; 
const Fl_Color FL_GRAY = FL_BACKGROUND_COLOR; 
const Fl_Color FL_COLOR_CUBE = 56; 
const int FL_NUM_RED = 5; 
const int FL_NUM_GREEN = 8; 
const int FL_NUM_BLUE = 5; 
/+=
Fl_Color fl_inactive(Fl_Color c);
Fl_Color fl_contrast(Fl_Color fg, Fl_Color bg);
Fl_Color fl_color_average(Fl_Color c1, Fl_Color c2, float weight);
=+/

Fl_Color fl_lighter(Fl_Color c) { return fl_color_average(c, FL_WHITE, .67f); }
Fl_Color fl_darker(Fl_Color c) { return fl_color_average(c, FL_BLACK, .67f); }
Fl_Color fl_rgb_color(ubyte r, ubyte g, ubyte b) {
  if (!r && !g && !b) return FL_BLACK;
  else return (((((r << 8) | g) << 8) | b) << 8);
}
Fl_Color fl_rgb_color(ubyte g) {
  if (!g) return FL_BLACK;
  else return (((((g << 8) | g) << 8) | g) << 8);
}
Fl_Color fl_gray_ramp(int i) {return i+FL_GRAY_RAMP;}
Fl_Color fl_color_cube(int r, int g, int b) {
  return ((b*FL_NUM_RED + r) * FL_NUM_GREEN + g + FL_COLOR_CUBE);}

alias ubyte Fl_Cursor;
const Fl_Cursor FL_CURSOR_DEFAULT= 0;
const Fl_Cursor FL_CURSOR_ARROW	= 35;
const Fl_Cursor FL_CURSOR_CROSS	= 66;
const Fl_Cursor FL_CURSOR_WAIT	= 76;
const Fl_Cursor FL_CURSOR_INSERT= 77;
const Fl_Cursor FL_CURSOR_HAND	= 31;
const Fl_Cursor FL_CURSOR_HELP	= 47;
const Fl_Cursor FL_CURSOR_MOVE	= 27;
  // fltk provides bitmaps for these:
const Fl_Cursor FL_CURSOR_NS	= 78;
const Fl_Cursor FL_CURSOR_WE	= 79;
const Fl_Cursor FL_CURSOR_NWSE	= 80;
const Fl_Cursor FL_CURSOR_NESW	= 81;
const Fl_Cursor FL_CURSOR_NONE	= 255;
  // for back compatability (non MSWindows ones):
const Fl_Cursor FL_CURSOR_N	= 70;
const Fl_Cursor FL_CURSOR_NE	= 69;
const Fl_Cursor FL_CURSOR_E	= 49;
const Fl_Cursor FL_CURSOR_SE	= 8;
const Fl_Cursor FL_CURSOR_S	= 9;
const Fl_Cursor FL_CURSOR_SW	= 7;
const Fl_Cursor FL_CURSOR_W	= 36;
const Fl_Cursor FL_CURSOR_NW	= 68;

/+=
enum { // values for "when" passed to Fl.add_fd()
  FL_READ = 1,
  FL_WRITE = 4,
  FL_EXCEPT = 8
};

enum Fl_Mode { // visual types and Fl_Gl_Window.mode() (values match Glut)
  FL_RGB	= 0,
  FL_INDEX	= 1,
  FL_SINGLE	= 0,
  FL_DOUBLE	= 2,
  FL_ACCUM	= 4,
  FL_ALPHA	= 8,
  FL_DEPTH	= 16,
  FL_STENCIL	= 32,
  FL_RGB8	= 64,
  FL_MULTISAMPLE= 128,
  FL_STEREO     = 256,
  FL_FAKE_SINGLE = 512	// Fake single buffered windows using double-buffer
};
=+/
// damage masks

alias ubyte Fl_Damage;
const Fl_Damage FL_DAMAGE_CHILD    = 0x01;
const Fl_Damage FL_DAMAGE_EXPOSE   = 0x02;
const Fl_Damage FL_DAMAGE_SCROLL   = 0x04;
const Fl_Damage FL_DAMAGE_OVERLAY  = 0x08;
const Fl_Damage FL_DAMAGE_USER1    = 0x10;
const Fl_Damage FL_DAMAGE_USER2    = 0x20;
const Fl_Damage FL_DAMAGE_ALL      = 0x80;

// Widget types:
const int FL_RESERVED_TYPE = 100; 
const int FL_NORMAL_BUTTON = 0; 
const int FL_TOGGLE_BUTTON = 1; 
const int FL_RADIO_BUTTON = (FL_RESERVED_TYPE+2); 
const int FL_HIDDEN_BUTTON = 3;  // for Forms compatability
const ubyte FL_WINDOW = 0xF0;   // all subclasses have type() >= this
const ubyte FL_DOUBLE_WINDOW = 0xF1; 

/+=
// FLTK 1.0.x compatibility definitions...
version (FLTK_1_0_COMPAT) {
const int contrast = fl_contrast; 
const int down = fl_down; 
const int frame = fl_frame; 
const int inactive = fl_inactive; 
} // FLTK_1_0_COMPAT

}

//
// End of "$Id: Enumerations.H 5271 2006-07-27 19:26:11Z mike $".
//
    End of automatic import -+/
