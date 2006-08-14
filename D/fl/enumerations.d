//
// "$Id: enumerations.d $"
//
// Enumerations for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2006 by Bill Spitzak and others.
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

//
// The FLTK version number; this is changed slightly from the beta versions
// because the old "const double" definition would not allow for conditional
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

module fl.enumerations;


const int FL_MAJOR_VERSION  = 1;
const int FL_MINOR_VERSION  = 1;
const int FL_PATCH_VERSION  = 7;
const double FL_VERSION     = FL_MAJOR_VERSION +
                              FL_MINOR_VERSION * 0.01 +
                              FL_PATCH_VERSION * 0.0001; 


typedef int Fl_Event;
const Fl_Event FL_NO_EVENT	= 0;
const Fl_Event FL_PUSH		= 1;
const Fl_Event FL_RELEASE	= 2;
const Fl_Event FL_ENTER		= 3;
const Fl_Event FL_LEAVE		= 4;
const Fl_Event FL_DRAG		= 5;
const Fl_Event FL_FOCUS		= 6;
const Fl_Event FL_UNFOCUS	= 7;
const Fl_Event FL_KEYDOWN	= 8;
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

const Fl_Event FL_KEYBOARD	= FL_KEYDOWN;


typedef ubyte Fl_When;
const Fl_When FL_WHEN_NEVER		= 0;
const Fl_When FL_WHEN_CHANGED		= 1;
const Fl_When FL_WHEN_NOT_CHANGED	= 2; // modifier bit to disable changed() test
const Fl_When FL_WHEN_RELEASE		= 4;
const Fl_When FL_WHEN_RELEASE_ALWAYS	= 6;
const Fl_When FL_WHEN_ENTER_KEY		= 8;
const Fl_When FL_WHEN_ENTER_KEY_ALWAYS	= 10;
const Fl_When FL_WHEN_ENTER_KEY_CHANGED	= 11;


// Fl.event_key() and Fl.get_key(n) (use ascii letters for all other keys):
const int FL_Button		= 0xfee8; // use Fl_Button+FL_*_MOUSE
const int FL_BackSpace		= 0xff08;
const int FL_Tab		= 0xff09;
const int FL_Enter		= 0xff0d;
const int FL_Pause		= 0xff13;
const int FL_Scroll_Lock	= 0xff14;
const int FL_Escape		= 0xff1b;
const int FL_Home		= 0xff50;
const int FL_Left		= 0xff51;
const int FL_Up			= 0xff52;
const int FL_Right		= 0xff53;
const int FL_Down		= 0xff54;
const int FL_Page_Up		= 0xff55;
const int FL_Page_Down		= 0xff56;
const int FL_End		= 0xff57;
const int FL_Print		= 0xff61;
const int FL_Insert		= 0xff63;
const int FL_Menu		= 0xff67; // the "menu/apps" key on XFree86
const int FL_Help		= 0xff68; // the 'help' key on Mac keyboards
const int FL_Num_Lock		= 0xff7f;
const int FL_KP			= 0xff80; // use FL_KP+'x' for 'x' on numeric keypad
const int FL_KP_Enter		= 0xff8d; // same as Fl_KP+'\r'
const int FL_KP_Last		= 0xffbd; // use to range-check keypad
const int FL_F			= 0xffbd; // use FL_F+n for function key n
const int FL_F_Last		= 0xffe0; // use to range-check function keys
const int FL_Shift_L		= 0xffe1;
const int FL_Shift_R		= 0xffe2;
const int FL_Control_L		= 0xffe3;
const int FL_Control_R		= 0xffe4;
const int FL_Caps_Lock		= 0xffe5;
const int FL_Meta_L		= 0xffe7; // the left MSWindows key on XFree86
const int FL_Meta_R		= 0xffe8; // the right MSWindows key on XFree86
const int FL_Alt_L		= 0xffe9;
const int FL_Alt_R		= 0xffea;
const int FL_Delete		= 0xffff;

// Fl::event_button():
const int FL_LEFT_MOUSE		= 1;
const int FL_MIDDLE_MOUSE	= 2;
const int FL_RIGHT_MOUSE	= 3;

// Fl::event_state():
const int FL_SHIFT		= 0x00010000;
const int FL_CAPS_LOCK		= 0x00020000;
const int FL_CTRL		= 0x00040000;
const int FL_ALT		= 0x00080000;
const int FL_NUM_LOCK		= 0x00100000; // most X servers do this?
const int FL_META		= 0x00400000; // correct for XFree86
const int FL_SCROLL_LOCK	= 0x00800000; // correct for XFree86
const int FL_BUTTON1		= 0x01000000;
const int FL_BUTTON2		= 0x02000000;
const int FL_BUTTON3		= 0x04000000;
const int FL_BUTTONS		= 0x7f000000; // All possible buttons
int FL_BUTTON(int n) 		{ return ( 0x00800000<<(n) ); }

version (apple) {
  const int FL_COMMAND = FL_META;
} else {
  const int FL_COMMAND = FL_CTRL;
}

typedef ubyte Fl_Boxtype;
const Fl_Boxtype FL_NO_BOX 		= 0;
const Fl_Boxtype FL_FLAT_BOX 		= 1;
const Fl_Boxtype FL_UP_BOX 		= 2;
const Fl_Boxtype FL_DOWN_BOX 		= 3;
const Fl_Boxtype FL_UP_FRAME 		= 4;
const Fl_Boxtype FL_DOWN_FRAME 		= 5;
const Fl_Boxtype FL_THIN_UP_BOX 	= 6;
const Fl_Boxtype FL_THIN_DOWN_BOX 	= 7;
const Fl_Boxtype FL_THIN_UP_FRAME 	= 8;	
const Fl_Boxtype FL_THIN_DOWN_FRAME 	= 9;
const Fl_Boxtype FL_ENGRAVED_BOX 	= 10;
const Fl_Boxtype FL_EMBOSSED_BOX 	= 11;
const Fl_Boxtype FL_ENGRAVED_FRAME 	= 12;	
const Fl_Boxtype FL_EMBOSSED_FRAME 	= 13;
const Fl_Boxtype FL_BORDER_BOX 		= 14;
const Fl_Boxtype FL_SHADOW_BOX 		= 15;
const Fl_Boxtype FL_BORDER_FRAME 	= 16;	
const Fl_Boxtype FL_SHADOW_FRAME 	= 17;
const Fl_Boxtype FL_ROUNDED_BOX 	= 18;	
const Fl_Boxtype FL_RSHADOW_BOX 	= 19;
const Fl_Boxtype FL_ROUNDED_FRAME 	= 20;	
const Fl_Boxtype FL_RFLAT_BOX 		= 21;
const Fl_Boxtype FL_ROUND_UP_BOX 	= 22;	
const Fl_Boxtype FL_ROUND_DOWN_BOX 	= 23;
const Fl_Boxtype FL_DIAMOND_UP_BOX 	= 24;
const Fl_Boxtype FL_DIAMOND_DOWN_BOX 	= 25;
const Fl_Boxtype FL_OVAL_BOX 		= 26;
const Fl_Boxtype FL_OSHADOW_BOX 	= 27;
const Fl_Boxtype FL_OVAL_FRAME	 	= 28;	
const Fl_Boxtype FL_OFLAT_BOX 		= 29;
const Fl_Boxtype FL_PLASTIC_UP_BOX 	= 30;	
const Fl_Boxtype FL_PLASTIC_DOWN_BOX 	= 31;
const Fl_Boxtype FL_PLASTIC_UP_FRAME 	= 32;
const Fl_Boxtype FL_PLASTIC_DOWN_FRAME = 33;
const Fl_Boxtype FL_PLASTIC_THIN_UP_BOX = 34;	
const Fl_Boxtype FL_PLASTIC_THIN_DOWN_BOX = 35;
const Fl_Boxtype FL_PLASTIC_ROUND_UP_BOX = 36;
const Fl_Boxtype FL_PLASTIC_ROUND_DOWN_BOX = 37;
const Fl_Boxtype FL_FREE_BOXTYPE 	= 38;

// conversions of box types to other boxtypes:
Fl_Boxtype fl_down(Fl_Boxtype b) 	{ return cast(Fl_Boxtype)(b|1); }
Fl_Boxtype fl_frame(Fl_Boxtype b) 	{ return cast(Fl_Boxtype)(b|2); }

// back-compatability box types:
const Fl_Boxtype FL_FRAME 	= FL_ENGRAVED_FRAME;
const Fl_Boxtype FL_FRAME_BOX 	= FL_ENGRAVED_BOX;
const Fl_Boxtype FL_CIRCLE_BOX 	= FL_ROUND_DOWN_BOX;
const Fl_Boxtype FL_DIAMOND_BOX = FL_DIAMOND_DOWN_BOX;

typedef ubyte Fl_Labeltype;
const Fl_Labeltype FL_NORMAL_LABEL	= 0;
const Fl_Labeltype FL_NO_LABEL		= 1;
const Fl_Labeltype FL_SHADOW_LABEL	= 2;
const Fl_Labeltype FL_ENGRAVED_LABEL	= 3;
const Fl_Labeltype FL_EMBOSSED_LABEL	= 4;
const Fl_Labeltype FL_MULTI_LABEL	= 5;
const Fl_Labeltype FL_ICON_LABEL	= 6;
const Fl_Labeltype FL_IMAGE_LABEL	= 7;
const Fl_Labeltype FL_FREE_LABELTYPE	= 8;


typedef ubyte Fl_Align;
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

typedef ushort Fl_Font;
const Fl_Font FL_HELVETICA		= 0;
const Fl_Font FL_HELVETICA_BOLD		= 1;
const Fl_Font FL_HELVETICA_ITALIC	= 2;
const Fl_Font FL_HELVETICA_BOLD_ITALIC	= 3;
const Fl_Font FL_COURIER		= 4;
const Fl_Font FL_COURIER_BOLD		= 5;
const Fl_Font FL_COURIER_ITALIC		= 6;
const Fl_Font FL_COURIER_BOLD_ITALIC	= 7;
const Fl_Font FL_TIMES			= 8;
const Fl_Font FL_TIMES_BOLD		= 9;
const Fl_Font FL_TIMES_ITALIC		= 10;
const Fl_Font FL_TIMES_BOLD_ITALIC	= 11;
const Fl_Font FL_SYMBOL			= 12;
const Fl_Font FL_SCREEN			= 13;
const Fl_Font FL_SCREEN_BOLD		= 14;
const Fl_Font FL_ZAPF_DINGBATS		= 15;

const Fl_Font FL_FREE_FONT		= 16;	// first one to allocate
const Fl_Font FL_BOLD			= 1;	// add this to helvetica, courier, or times
const Fl_Font FL_ITALIC			= 2;	// add this to helvetica, courier, or times

int FL_NORMAL_SIZE = 14;


typedef uint Fl_Color;
// These are used as default colors in widgets and altered as necessary
const Fl_Color FL_FOREGROUND_COLOR	= 0;
const Fl_Color FL_BACKGROUND2_COLOR	= 7;
const Fl_Color FL_INACTIVE_COLOR	= 8;
const Fl_Color FL_SELECTION_COLOR	= 15;

  // boxtypes generally limit themselves to these colors so
  // the whole ramp is not allocated:
const Fl_Color FL_GRAY0			= 32;	// 'A'
const Fl_Color FL_DARK3			= 39;	// 'H'
const Fl_Color FL_DARK2			= 45;   // 'N'
const Fl_Color FL_DARK1			= 47;	// 'P'
const Fl_Color FL_BACKGROUND_COLOR	= 49;	// 'R' default background color
const Fl_Color FL_LIGHT1		= 50;	// 'S'
const Fl_Color FL_LIGHT2		= 52;	// 'U'
const Fl_Color FL_LIGHT3		= 54;	// 'W'

  // FLTK provides a 5x8x5 color cube that is used with colormap visuals
const Fl_Color FL_BLACK			= 56;
const Fl_Color FL_RED			= 88;
const Fl_Color FL_GREEN			= 63;
const Fl_Color FL_YELLOW		= 95;
const Fl_Color FL_BLUE			= 216;
const Fl_Color FL_MAGENTA		= 248;
const Fl_Color FL_CYAN			= 223;
const Fl_Color FL_DARK_RED		= 72;

const Fl_Color FL_DARK_GREEN		= 60;
const Fl_Color FL_DARK_YELLOW		= 76;
const Fl_Color FL_DARK_BLUE		= 136;
const Fl_Color FL_DARK_MAGENTA		= 152;
const Fl_Color FL_DARK_CYAN		= 140;

const Fl_Color FL_WHITE			= 255;

const Fl_Color FL_FREE_COLOR		= 16;
const int      FL_NUM_FREE_COLOR	= 16;
const Fl_Color FL_GRAY_RAMP		= 32;
const int      FL_NUM_GRAY		= 24;
const Fl_Color FL_GRAY			= FL_BACKGROUND_COLOR;
const Fl_Color FL_COLOR_CUBE		= 56;
const int      FL_NUM_RED		= 5;
const int      FL_NUM_GREEN		= 8;
const int      FL_NUM_BLUE		= 5;

Fl_Color fl_inactive(Fl_Color c)
{
  return fl_color_average(c, FL_GRAY, .33f);
}

Fl_Color fl_contrast(Fl_Color fg, Fl_Color bg)
{
  uint c1, c2;      // RGB colors
  int l1, l2;       // Luminosities

  // Get the RGB values for each color...
  if (fg & 0xffffff00) c1 = cast(uint)fg;
  else c1 = fl_cmap[fg];

  if (bg & 0xffffff00) c2 = cast(uint)bg;
  else c2 = fl_cmap[bg];

  // Compute the luminosity...
  l1 = ((c1 >> 24) * 31 + ((c1 >> 16) & 255) * 61 + ((c1 >> 8) & 255) * 8) / 100;
  l2 = ((c2 >> 24) * 31 + ((c2 >> 16) & 255) * 61 + ((c2 >> 8) & 255) * 8) / 100;

  // Compare and return the contrasting color...
  if ((l1 - l2) > 127)      return fg;
  else if ((l2 - l1) > 127) return fg;
  else if (l2 > 127)        return FL_BLACK;
  else                      return FL_WHITE;
}

Fl_Color fl_color_average(Fl_Color color1, Fl_Color color2, float weight)
{
  uint rgb1;
  uint rgb2;
  ubyte r, g, b;

  if (color1 & 0xffffff00) rgb1 = color1;
  else rgb1 = fl_cmap[color1 & 255];

  if (color2 & 0xffffff00) rgb2 = color2;
  else rgb2 = fl_cmap[color2 & 255];

  r = cast(ubyte)((cast(ubyte)(rgb1>>24))*weight + (cast(ubyte)(rgb2>>24))*(1-weight));
  g = cast(ubyte)((cast(ubyte)(rgb1>>16))*weight + (cast(ubyte)(rgb2>>16))*(1-weight));
  b = cast(ubyte)((cast(ubyte)(rgb1>>8))*weight  + (cast(ubyte)(rgb2>>8))*(1-weight));

  return fl_rgb_color(r, g, b);
}

Fl_Color fl_lighter(Fl_Color c) 
{ 
  return fl_color_average(c, FL_WHITE, .67f); 
}

Fl_Color fl_darker(Fl_Color c) 
{
  return fl_color_average(c, FL_BLACK, .67f); 
}

Fl_Color fl_rgb_color(ubyte r, ubyte g, ubyte b) 
{
  if (!r && !g && !b) 
    return FL_BLACK;
  else 
    return cast(Fl_Color)(((((r << 8) | g) << 8) | b) << 8);
}

Fl_Color fl_rgb_color(ubyte g)
{
  if (!g) 
    return FL_BLACK;
  else 
    return cast(Fl_Color)(((((g << 8) | g) << 8) | g) << 8);
}

Fl_Color fl_color_cube(int r, int g, int b) 
{
  return cast(Fl_Color)((b*FL_NUM_RED + r) * FL_NUM_GREEN + g + FL_COLOR_CUBE);
}

typedef ubyte Fl_Cursor;
const Fl_Cursor FL_CURSOR_DEFAULT	= 0;
const Fl_Cursor FL_CURSOR_ARROW		= 35;
const Fl_Cursor FL_CURSOR_CROSS		= 66;
const Fl_Cursor FL_CURSOR_WAIT		= 76;
const Fl_Cursor FL_CURSOR_INSERT	= 77;
const Fl_Cursor FL_CURSOR_HAND		= 31;
const Fl_Cursor FL_CURSOR_HELP		= 47;
const Fl_Cursor FL_CURSOR_MOVE		= 27;
  // fltk provides bitmaps for these:
const Fl_Cursor FL_CURSOR_NS		= 78;
const Fl_Cursor FL_CURSOR_WE		= 79;
const Fl_Cursor FL_CURSOR_NWSE		= 80;
const Fl_Cursor FL_CURSOR_NESW		= 81;
const Fl_Cursor FL_CURSOR_NONE		= 255;
  // for back compatability (non MSWindows ones):
const Fl_Cursor FL_CURSOR_N		= 70;
const Fl_Cursor FL_CURSOR_NE		= 69;
const Fl_Cursor FL_CURSOR_E		= 49;
const Fl_Cursor FL_CURSOR_SE		= 8;
const Fl_Cursor FL_CURSOR_S		= 9;
const Fl_Cursor FL_CURSOR_SW		= 7;
const Fl_Cursor FL_CURSOR_W		= 36;
const Fl_Cursor FL_CURSOR_NW		= 68;

enum { // values for "when" passed to Fl::add_fd()
  FL_READ = 1,
  FL_WRITE = 4,
  FL_EXCEPT = 8
};

typedef ushort Fl_Mode;
const Fl_Mode FL_RGB		= 0;
const Fl_Mode FL_INDEX		= 1;
const Fl_Mode FL_SINGLE		= 0;
const Fl_Mode FL_DOUBLE		= 2;
const Fl_Mode FL_ACCUM		= 4;
const Fl_Mode FL_ALPHA		= 8;
const Fl_Mode FL_DEPTH		= 16;
const Fl_Mode FL_STENCIL	= 32;
const Fl_Mode FL_RGB8		= 64;
const Fl_Mode FL_MULTISAMPLE	= 128;
const Fl_Mode FL_STEREO     	= 256;
const Fl_Mode FL_FAKE_SINGLE 	= 512;	// Fake single buffered windows using double-buffer

// damage masks

typedef ubyte Fl_Damage;
const Fl_Damage FL_DAMAGE_CHILD    = 0x01;
const Fl_Damage FL_DAMAGE_EXPOSE   = 0x02;
const Fl_Damage FL_DAMAGE_SCROLL   = 0x04;
const Fl_Damage FL_DAMAGE_OVERLAY  = 0x08;
const Fl_Damage FL_DAMAGE_USER1    = 0x10;
const Fl_Damage FL_DAMAGE_USER2    = 0x20;
const Fl_Damage FL_DAMAGE_ALL      = 0x80;

// widgte types (basically a primitive RTTI)

typedef ubyte Fl_Type;
// reserved type numbers (necessary for my cheapo RTTI) start here.
// grep the header files for "RESERVED_TYPE" to find the next available
// number.
const Fl_Type FL_NORMAL_BUTTON = 0;
const Fl_Type FL_TOGGLE_BUTTON = 1;
const Fl_Type FL_RADIO_BUTTON = (FL_RESERVED_TYPE+2);
const Fl_Type FL_HIDDEN_BUTTON = 3;
const Fl_Type FL_RESERVED_TYPE = 100;
const Fl_Type FL_WINDOW = 0xf0;
const Fl_Type FL_DOUBLE_WINDOW = 0xf1;

const Fl_Color[256] fl_cmap = [
  0x00000000, 0xff000000, 0x00ff0000, 0xffff0000, 0x0000ff00, 0xff00ff00, 0x00ffff00, 0xffffff00,
  0x55555500, 0xc6717100, 0x71c67100, 0x8e8e3800, 0x7171c600, 0x8e388e00, 0x388e8e00, 0x00008000,
  0xa8a89800, 0xe8e8d800, 0x68685800, 0x98a8a800, 0xd8e8e800, 0x58686800, 0x9c9ca800, 0xdcdce800,
  0x5c5c6800, 0x9ca89c00, 0xdce8dc00, 0x5c685c00, 0x90909000, 0xc0c0c000, 0x50505000, 0xa0a0a000,
  0x00000000, 0x0d0d0d00, 0x1a1a1a00, 0x26262600, 0x31313100, 0x3d3d3d00, 0x48484800, 0x55555500,
  0x5f5f5f00, 0x6a6a6a00, 0x75757500, 0x80808000, 0x8a8a8a00, 0x95959500, 0xa0a0a000, 0xaaaaaa00,
  0xb5b5b500, 0xc0c0c000, 0xcbcbcb00, 0xd5d5d500, 0xe0e0e000, 0xeaeaea00, 0xf5f5f500, 0xffffff00,
  0x00000000, 0x00240000, 0x00480000, 0x006d0000, 0x00910000, 0x00b60000, 0x00da0000, 0x00ff0000,
  0x3f000000, 0x3f240000, 0x3f480000, 0x3f6d0000, 0x3f910000, 0x3fb60000, 0x3fda0000, 0x3fff0000,
  0x7f000000, 0x7f240000, 0x7f480000, 0x7f6d0000, 0x7f910000, 0x7fb60000, 0x7fda0000, 0x7fff0000,
  0xbf000000, 0xbf240000, 0xbf480000, 0xbf6d0000, 0xbf910000, 0xbfb60000, 0xbfda0000, 0xbfff0000,
  0xff000000, 0xff240000, 0xff480000, 0xff6d0000, 0xff910000, 0xffb60000, 0xffda0000, 0xffff0000,
  0x00003f00, 0x00243f00, 0x00483f00, 0x006d3f00, 0x00913f00, 0x00b63f00, 0x00da3f00, 0x00ff3f00,
  0x3f003f00, 0x3f243f00, 0x3f483f00, 0x3f6d3f00, 0x3f913f00, 0x3fb63f00, 0x3fda3f00, 0x3fff3f00,
  0x7f003f00, 0x7f243f00, 0x7f483f00, 0x7f6d3f00, 0x7f913f00, 0x7fb63f00, 0x7fda3f00, 0x7fff3f00,
  0xbf003f00, 0xbf243f00, 0xbf483f00, 0xbf6d3f00, 0xbf913f00, 0xbfb63f00, 0xbfda3f00, 0xbfff3f00,
  0xff003f00, 0xff243f00, 0xff483f00, 0xff6d3f00, 0xff913f00, 0xffb63f00, 0xffda3f00, 0xffff3f00,
  0x00007f00, 0x00247f00, 0x00487f00, 0x006d7f00, 0x00917f00, 0x00b67f00, 0x00da7f00, 0x00ff7f00,
  0x3f007f00, 0x3f247f00, 0x3f487f00, 0x3f6d7f00, 0x3f917f00, 0x3fb67f00, 0x3fda7f00, 0x3fff7f00,
  0x7f007f00, 0x7f247f00, 0x7f487f00, 0x7f6d7f00, 0x7f917f00, 0x7fb67f00, 0x7fda7f00, 0x7fff7f00,
  0xbf007f00, 0xbf247f00, 0xbf487f00, 0xbf6d7f00, 0xbf917f00, 0xbfb67f00, 0xbfda7f00, 0xbfff7f00,
  0xff007f00, 0xff247f00, 0xff487f00, 0xff6d7f00, 0xff917f00, 0xffb67f00, 0xffda7f00, 0xffff7f00,
  0x0000bf00, 0x0024bf00, 0x0048bf00, 0x006dbf00, 0x0091bf00, 0x00b6bf00, 0x00dabf00, 0x00ffbf00,
  0x3f00bf00, 0x3f24bf00, 0x3f48bf00, 0x3f6dbf00, 0x3f91bf00, 0x3fb6bf00, 0x3fdabf00, 0x3fffbf00,
  0x7f00bf00, 0x7f24bf00, 0x7f48bf00, 0x7f6dbf00, 0x7f91bf00, 0x7fb6bf00, 0x7fdabf00, 0x7fffbf00,
  0xbf00bf00, 0xbf24bf00, 0xbf48bf00, 0xbf6dbf00, 0xbf91bf00, 0xbfb6bf00, 0xbfdabf00, 0xbfffbf00,
  0xff00bf00, 0xff24bf00, 0xff48bf00, 0xff6dbf00, 0xff91bf00, 0xffb6bf00, 0xffdabf00, 0xffffbf00,
  0x0000ff00, 0x0024ff00, 0x0048ff00, 0x006dff00, 0x0091ff00, 0x00b6ff00, 0x00daff00, 0x00ffff00,
  0x3f00ff00, 0x3f24ff00, 0x3f48ff00, 0x3f6dff00, 0x3f91ff00, 0x3fb6ff00, 0x3fdaff00, 0x3fffff00,
  0x7f00ff00, 0x7f24ff00, 0x7f48ff00, 0x7f6dff00, 0x7f91ff00, 0x7fb6ff00, 0x7fdaff00, 0x7fffff00,
  0xbf00ff00, 0xbf24ff00, 0xbf48ff00, 0xbf6dff00, 0xbf91ff00, 0xbfb6ff00, 0xbfdaff00, 0xbfffff00,
  0xff00ff00, 0xff24ff00, 0xff48ff00, 0xff6dff00, 0xff91ff00, 0xffb6ff00, 0xffdaff00, 0xffffff00
];

//
// End of "$Id: enumerations.d $".
//
