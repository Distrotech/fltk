/+- This file was imported from C++ using a script
//
// "$Id: get_system_colors.d 5190 2006-06-09 16:16:34Z mike $"
//
// System color support for the Fast Light Tool Kit (FLTK).
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

#include <FL/Fl.H>
private import fl.draw;
#include <FL/x.H>
#include <FL/math.h>
private import fl.flstring;
#include <stdio.h>
#include <stdlib.h>
private import fl.pixmap;
private import fl.tiled_image;
#include "tile.xpm"

version (__APPLE__) && defined(__MWERKS__) {
extern "C" int putenv(char*);
} // __APPLE__ && __MWERKS__

version (WIN32) && !defined(__CYGWIN__) {
// Visual C++ 2005 incorrectly displays a warning about the use of POSIX APIs
// on Windows, which is supposed to be POSIX compliant...
const int putenv = _putenv; 
} // WIN32 && !__CYGWIN__

version (WIN32) || defined(__APPLE__) {

#  include <stdio.h>
// simulation of XParseColor:
int fl_parse_color(char* p, ubyte& r, ubyte& g, ubyte& b) {
  if (*p == '#') p++;
  int n = strlen(p);
  int m = n/3;
  char *pattern = 0;
  switch(m) {
  case 1: pattern = "%1x%1x%1x"; break;
  case 2: pattern = "%2x%2x%2x"; break;
  case 3: pattern = "%3x%3x%3x"; break;
  case 4: pattern = "%4x%4x%4x"; break;
  default: return 0;
  }
  int R,G,B; if (sscanf(p,pattern,&R,&G,&B) != 3) return 0;
  switch(m) {
  case 1: R *= 0x11; G *= 0x11; B *= 0x11; break;
  case 3: R >>= 4; G >>= 4; B >>= 4; break;
  case 4: R >>= 8; G >>= 8; B >>= 8; break;
  }
  r = (ubyte)R; g = (ubyte)G; b = (ubyte)B;
  return 1;
}
} else {
// Wrapper around XParseColor...
int fl_parse_color(char* p, ubyte& r, ubyte& g, ubyte& b) {
  XColor x;
  if (!fl_display) fl_open_display();
  if (XParseColor(fl_display, fl_colormap, p, &x)) {
    r = (ubyte)(x.red>>8);
    g = (ubyte)(x.green>>8);
    b = (ubyte)(x.blue>>8);
    return 1;
  } else return 0;
}
} // WIN32 || __APPLE__

version (WIN32) {
static void
getsyscolor(int what, char* arg, void (*func)(ubyte,ubyte,ubyte))
{
  if (arg) {
    ubyte r,g,b;
    if (!fl_parse_color(arg, r,g,b))
      Fl.error("Unknown color: %s", arg);
    else
      func(r,g,b);
  } else {
    DWORD x = GetSysColor(what);
    func(ubyte(x&255), ubyte(x>>8), ubyte(x>>16));
  }
}

void Fl.get_system_colors() {
  if (!fl_bg2_set) getsyscolor(COLOR_WINDOW,	fl_bg2,Fl.background2);
  if (!fl_fg_set) getsyscolor(COLOR_WINDOWTEXT,	fl_fg, Fl.foreground);
  if (!fl_bg_set) getsyscolor(COLOR_BTNFACE,	fl_bg, Fl.background);
  getsyscolor(COLOR_HIGHLIGHT,	0,     set_selection_color);
}

} else version (__APPLE__) {
} else {

// Read colors that KDE writes to the xrdb database.

// XGetDefault does not do the expected thing: it does not like
// periods in either word. Therefore it cannot match class.Text.background.
// However *.Text.background is matched by pretending the program is "Text".
// But this will also match *.background if there is no *.Text.background
// entry, requiring users to put in both (unless they want the text fields
// the same color as the windows).

static void
getsyscolor(char *key1, char* key2, char *arg, char *defarg, void (*func)(ubyte,ubyte,ubyte))
{
  if (!arg) {
    arg = XGetDefault(fl_display, key1, key2);
    if (!arg) arg = defarg;
  }
  XColor x;
  if (!XParseColor(fl_display, fl_colormap, arg, &x))
    Fl.error("Unknown color: %s", arg);
  else
    func(x.red>>8, x.green>>8, x.blue>>8);
}

void Fl.get_system_colors()
{
  fl_open_display();
  char* key1 = 0;
  if (Fl.first_window()) key1 = Fl.first_window()->xclass();
  if (!key1) key1 = "fltk";
  if (!fl_bg2_set) getsyscolor("Text","background",	fl_bg2,	"#ffffff", Fl.background2);
  if (!fl_fg_set) getsyscolor(key1,  "foreground",	fl_fg,	"#000000", Fl.foreground);
  if (!fl_bg_set) getsyscolor(key1,  "background",	fl_bg,	"#c0c0c0", Fl.background);
  getsyscolor(key1,  "selectBackground",0,	"#000080", set_selection_color);
}

}


//// Simple implementation of 2.0 Fl.scheme() interface...
const int D1 = BORDER_WIDTH; 
const int D2 = (BORDER_WIDTH+BORDER_WIDTH); 

extern void	fl_up_box(int, int, int, int, Fl_Color);
extern void	fl_down_box(int, int, int, int, Fl_Color);
extern void	fl_thin_up_box(int, int, int, int, Fl_Color);
extern void	fl_thin_down_box(int, int, int, int, Fl_Color);
extern void	fl_round_up_box(int, int, int, int, Fl_Color);
extern void	fl_round_down_box(int, int, int, int, Fl_Color);

extern void	fl_up_frame(int, int, int, int, Fl_Color);
extern void	fl_down_frame(int, int, int, int, Fl_Color);
extern void	fl_thin_up_frame(int, int, int, int, Fl_Color);
extern void	fl_thin_down_frame(int, int, int, int, Fl_Color);

const char	*Fl.scheme_ = (char *)0;
Fl_Image	 Fl.scheme_bg_ = (Fl_Image  )0;

static Fl_Pixmap	tile(tile_xpm);

int Fl.scheme(char *s) {
  if (!s) {
    if ((s = getenv("FLTK_SCHEME")) == NULL) {
#if !defined(WIN32) && !defined(__APPLE__)
      char* key = 0;
      if (Fl.first_window()) key = Fl.first_window()->xclass();
      if (!key) key = "fltk";
      fl_open_display();
      s = XGetDefault(fl_display, key, "scheme");
} // !WIN32 && !__APPLE__
    }
  }

  if (s) {
    if (!strcasecmp(s, "none") || !strcasecmp(s, "base") || !*s) s = 0;
    else s = strdup(s);
  }
  if (scheme_) free((void*)scheme_);
  scheme_ = s;

  // Save the new scheme in the FLTK_SCHEME env var so that child processes
  // inherit it...
  static char e[1024];
  strcpy(e,"FLTK_SCHEME=");
  if (s) strlcat(e,s,sizeof(e));
  putenv(e);

  // Load the scheme...
  return reload_scheme();
}

int Fl.reload_scheme() {
  Fl_Window  win;

  if (scheme_ && !strcasecmp(scheme_, "plastic")) {
    // Update the tile image to match the background color...
    ubyte r, g, b;
    int nr, ng, nb;
    int i;
//    static ubyte levels[3] = { 0xff, 0xef, 0xe8 };
    // OSX 10.3 and higher use a background with less contrast...
    static ubyte levels[3] = { 0xff, 0xf8, 0xf4 };

    get_color(FL_GRAY, r, g, b);

//    printf("FL_GRAY = 0x%02x 0x%02x 0x%02x\n", r, g, b);

    for (i = 0; i < 3; i ++) {
      nr = levels[i] * r / 0xe8;
      if (nr > 255) nr = 255;

      ng = levels[i] * g / 0xe8;
      if (ng > 255) ng = 255;

      nb = levels[i] * b / 0xe8;
      if (nb > 255) nb = 255;

      sprintf(tile_cmap[i], "%c c #%02x%02x%02x", "Oo."[i], nr, ng, nb);
//      puts(tile_cmap[i]);
    }

    tile.uncache();

    if (!scheme_bg_) scheme_bg_ = new Fl_Tiled_Image(&tile, w(), h());

    // Load plastic buttons, etc...
    set_boxtype(FL_UP_FRAME,        FL_PLASTIC_UP_FRAME);
    set_boxtype(FL_DOWN_FRAME,      FL_PLASTIC_DOWN_FRAME);
    set_boxtype(FL_THIN_UP_FRAME,   FL_PLASTIC_UP_FRAME);
    set_boxtype(FL_THIN_DOWN_FRAME, FL_PLASTIC_DOWN_FRAME);

    set_boxtype(FL_UP_BOX,          FL_PLASTIC_UP_BOX);
    set_boxtype(FL_DOWN_BOX,        FL_PLASTIC_DOWN_BOX);
    set_boxtype(FL_THIN_UP_BOX,     FL_PLASTIC_THIN_UP_BOX);
    set_boxtype(FL_THIN_DOWN_BOX,   FL_PLASTIC_THIN_DOWN_BOX);
    set_boxtype(_FL_ROUND_UP_BOX,   FL_PLASTIC_ROUND_UP_BOX);
    set_boxtype(_FL_ROUND_DOWN_BOX, FL_PLASTIC_ROUND_DOWN_BOX);
  } else {
    // Use the standard FLTK look-n-feel...
    if (scheme_bg_) {
      delete scheme_bg_;
      scheme_bg_ = (Fl_Image  )0;
    }

    set_boxtype(FL_UP_FRAME,        fl_up_frame, D1, D1, D2, D2);
    set_boxtype(FL_DOWN_FRAME,      fl_down_frame, D1, D1, D2, D2);
    set_boxtype(FL_THIN_UP_FRAME,   fl_thin_up_frame, 1, 1, 2, 2);
    set_boxtype(FL_THIN_DOWN_FRAME, fl_thin_down_frame, 1, 1, 2, 2);

    set_boxtype(FL_UP_BOX,          fl_up_box, D1, D1, D2, D2);
    set_boxtype(FL_DOWN_BOX,        fl_down_box, D1, D1, D2, D2);
    set_boxtype(FL_THIN_UP_BOX,     fl_thin_up_box, 1, 1, 2, 2);
    set_boxtype(FL_THIN_DOWN_BOX,   fl_thin_down_box, 1, 1, 2, 2);
    set_boxtype(_FL_ROUND_UP_BOX,   fl_round_up_box, 3, 3, 6, 6);
    set_boxtype(_FL_ROUND_DOWN_BOX, fl_round_down_box, 3, 3, 6, 6);
  }

  // Set (or clear) the background tile for all windows...
  for (win = first_window(); win; win = next_window(win)) {
    win.labeltype(scheme_bg_ ? FL_NORMAL_LABEL : FL_NO_LABEL);
    win.alignment(FL_ALIGN_CENTER | FL_ALIGN_INSIDE | FL_ALIGN_CLIP);
    win.image(scheme_bg_);
    win.redraw();
  }

  return 1;
}


//
// End of "$Id: get_system_colors.d 5190 2006-06-09 16:16:34Z mike $".
//
    End of automatic import -+/
