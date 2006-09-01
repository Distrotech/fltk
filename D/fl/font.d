//
// "$Id: font.d 5334 2006-08-19 15:24:55Z matt $"
//
// Font definitions for the Fast Light Tool Kit (FLTK).
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

// Two internal fltk data structures:
//
// Fl_Fontdesc: an entry into the fl_font() table.  There is one of these
// for each fltk font number.
//
// Fl_FontSize: a structure for an actual system font, with junk to
// help choose it and info on character sizes.  Each Fl_Fontdesc has a
// linked list of these.  These are created the first time each system
// font/size combination is used.

module fl.font;

version (__APPLE__) {
  public import fl.font_mac;
  private import std.c.osx.carbon.carbon;
}

/+=
version (!FL_FONT_) {
#define FL_FONT_

#include <config.h>

#  if USE_XFT
alias struct _XftFont XftFont;
} // USE_XFT
=+/
/+= defined in the machine dependent source
class Fl_FontSize {
public:
  Fl_FontSize  next;	// linked list for this Fl_Fontdesc
  version (WIN32) {
    HFONT fid;
    int width[256];
    TEXTMETRIC metr;
    this(char* fontname, int size);
  } else version (__APPLE__) {
    this(char* fontname, int size);
    ATSUTextLayout layout;
    ATSUStyle style;
    short ascent, descent, q_width;
    short[256] width;
    bool knowWidths;
    char* q_name;
    int size;
  } else version (USE_XFT) {
    XftFont* font;
    char* encoding;
    int size;
    this(char* xfontname);
  } else {
    XFontStruct* font;	// X font information
    this(char* xfontname);
  }
  int minsize;		// smallest point size that should use this
  int maxsize;		// largest point size that should use this
  version(HAVE_GL) {
    uint listbase;// base of display list, 0 = none
  }
/+=
  ~Fl_FontSize();
=+/
}
=+/

/+=
extern Fl_FontSize  fl_fontsize; // the currently selected one
=+/

struct Fl_Fontdesc {
  char *name;
  char fontname[128];	// "Pretty" font name
  Fl_FontSize  first;	// linked list of sizes of this style
  version (WIN32) {
  } else {
    char **xlist;		// matched X font names
    int n;		// size of xlist, negative = don't free xlist!
  }
}

/+=
extern Fl_Fontdesc  fl_fonts; // the table

version (!WIN32) {
// functions for parsing X font names:
const char* fl_font_word(char *p, int n);
char *fl_find_fontsize(char *name);
}

}

//
// End of "$Id: font.d 5334 2006-08-19 15:24:55Z matt $".
//
    End of automatic import -+/
/+- This file was imported from C++ using a script
//
// "$Id: fl_font.cxx 5190 2006-06-09 16:16:34Z mike $"
//
// Font selection code for the Fast Light Tool Kit (FLTK).
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

// Select fonts from the FLTK font table.
private import fl.flstring;
#include <FL/Fl.H>
private import fl.draw;
#include <FL/x.H>
private import fl.font;

#include <stdio.h>
#include <stdlib.h>

version (WIN32) {
#  include "fl_font_win32.cxx"
} else version (__APPLE__) {
#  include "fl_font_mac.cxx"
#elif USE_XFT
#  include "fl_font_xft.cxx"
} else {
#  include "fl_font_x.cxx"
} // WIN32


double fl_width(char* c) {
  if (c) return fl_width(c, strlen(c));
  else return 0.0f;
}

void fl_draw(char* str, int x, int y) {
  fl_draw(str, strlen(str), x, y);
}


//
// End of "$Id: fl_font.cxx 5190 2006-06-09 16:16:34Z mike $".
//
    End of automatic import -+/
