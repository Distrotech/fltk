//
// "$Id: fl_font_win32.cxx,v 1.39 2001/11/08 08:13:49 spitzak Exp $"
//
// _WIN32 font selection routines for the Fast Light Tool Kit (FLTK).
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

#include <fltk/x.h>
#include "Fl_FontSize.h"

#include <ctype.h>
#include <stdlib.h>

Fl_FontSize *fl_fontsize;

Fl_FontSize::Fl_FontSize(const char* name, int size, int charset) {
  fl_fontsize = this;

  int weight = FW_NORMAL;
  int italic = 0;
  // may be efficient, but this is non-obvious
  switch (*name++) {
  case 'I': italic = 1; break;
  case 'P': italic = 1;
  case 'B': weight = FW_BOLD; break;
  case ' ': break;
  default: name--;
  }

  HFONT font = CreateFont(
    -size,	    // use "char size"
    0,		    // logical average character width
    0,		    // angle of escapement
    0,		    // base-line orientation angle
    weight,
    italic,
    FALSE,		// underline attribute flag
    FALSE,		// strikeout attribute flag
    charset,		// character set identifier
    OUT_DEFAULT_PRECIS, // output precision
    CLIP_DEFAULT_PRECIS,// clipping precision
    DEFAULT_QUALITY,	// output quality
    DEFAULT_PITCH,	// pitch and family
    name		// pointer to typeface name string
  );

  if (!fl_gc) fl_gc = GetDC(0);
  SelectObject(fl_gc, font);
  GetTextMetrics(fl_gc, &fl_fontsize->metr);
  //BOOL ret = GetCharWidthFloat(fl_gc, metr.tmFirstChar, metr.tmLastChar, font->width+metr.tmFirstChar);
  //...would be the right call, but is not implemented into Window95! (WinNT?)
  //GetCharWidth(fl_gc, 0, 255, fl_fontsize->width);

  this->font = (void*)font;
#if HAVE_GL
  listbase = 0;
#endif
  minsize = maxsize = size;
  this->charset = charset;
}

#if HAVE_GL
Fl_FontSize::~Fl_FontSize() {
// Delete list created by gl_draw().  This is not done by this code
// as it will link in GL unnecessarily.  There should be some kind
// of "free" routine pointer, or a subclass?
// if (listbase) {
//  int base = font->min_char_or_byte2;
//  int size = font->max_char_or_byte2-base+1;
//  int base = 0; int size = 256;
//  glDeleteLists(listbase+base,size);
// }
  if (this == fl_fontsize) fl_fontsize = 0;
  DeleteObject((HFONT)font);
}
#endif

////////////////////////////////////////////////////////////////

// The predefined fonts that fltk has:  bold:       italic:
Fl_Font_ fl_fonts[] = {
{" Arial",				fl_fonts+1, fl_fonts+2},
{"BArial", 				fl_fonts+1, fl_fonts+3},
{"IArial",				fl_fonts+3, fl_fonts+2},
{"PArial",				fl_fonts+3, fl_fonts+3},
{" Courier New",			fl_fonts+5, fl_fonts+6},
{"BCourier New",			fl_fonts+5, fl_fonts+7},
{"ICourier New",			fl_fonts+7, fl_fonts+6},
{"PCourier New",			fl_fonts+7, fl_fonts+7},
{" Times New Roman",			fl_fonts+9, fl_fonts+10},
{"BTimes New Roman",			fl_fonts+9, fl_fonts+11},
{"ITimes New Roman",			fl_fonts+11,fl_fonts+10},
{"PTimes New Roman",			fl_fonts+11,fl_fonts+11},
{" Symbol",				fl_fonts+12,fl_fonts+12},
{" Terminal",				fl_fonts+14,fl_fonts+14},
{"BTerminal",				fl_fonts+14,fl_fonts+14},
{" Wingdings",				fl_fonts+15,fl_fonts+15},
};

////////////////////////////////////////////////////////////////
// Public interface:

#define current_font ((HFONT)(fl_fontsize->font))
HFONT fl_xfont() {return current_font;}

// we need to decode the encoding somehow!
static int charset = DEFAULT_CHARSET;

void fl_font(Fl_Font font, unsigned size) {
  if (font == fl_font_ && size == fl_size_ &&
      fl_fontsize->charset == charset) return;
  fl_font_ = font; fl_size_ = size;

  Fl_FontSize* f;
  // search the fontsizes we have generated already:
  for (f = (Fl_FontSize *)font->first; f; f = f->next)
    if (f->minsize <= size && f->maxsize >= size &&
	f->charset == charset) break;
  if (!f) {
    f = new Fl_FontSize(font->name_, size, charset);
    f->next = (Fl_FontSize *)font->first;
    ((Fl_Font_*)font)->first = f;
  }
  fl_fontsize = f;
}

int fl_height() {
  return (fl_fontsize->metr.tmAscent + fl_fontsize->metr.tmDescent);
}

int fl_descent() { return fl_fontsize->metr.tmDescent; }
  
int fl_width(const char* c, int n) {
  SIZE size;
  if (!fl_gc) fl_gc = GetDC(0);
  SelectObject(fl_gc, current_font);
  GetTextExtentPoint(fl_gc, c, n, &size);
  return size.cx;
}

void fl_draw(const char *str, int n, int x, int y) {
  SetTextColor(fl_gc, fl_colorref);
  HGDIOBJ oldfont = SelectObject(fl_gc, current_font);
  TextOut(fl_gc, x+fl_x_, y+fl_y_, str, n);
  SelectObject(fl_gc, oldfont);
}

// Encodings is NYI. We need a way to translate the ISO encoding names
// to Win32 encoding enumerations.
void fl_encoding(const char* f) {
  if (f != fl_encoding_) {
    fl_encoding_ = f;
    // charset = decode_the_encoding(f);
    //if (fl_font_) fl_font(fl_font_, fl_size_);
  }
}

//
// End of "$Id: fl_font_win32.cxx,v 1.39 2001/11/08 08:13:49 spitzak Exp $".
//
