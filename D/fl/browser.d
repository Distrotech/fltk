//
// "$Id: browser.d 4288 2005-04-16 00:13:17Z mike $"
//
// Browser header file for the Fast Light Tool Kit (FLTK).
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

// Forms-compatable browser.  Probably useful for other
// lists of textual data.  Notice that the line numbers
// start from 1, and 0 means "no line".

module fl.browser;

/+=
public import fl.browser_;

struct FL_BLINE;

class Fl_Browser : Fl_Browser_ {

  FL_BLINE *first;		// the array of lines
  FL_BLINE *last;
  FL_BLINE *cache;
  int cacheline;		// line number of cache
  int lines;                	// Number of lines
  int full_height_;
  int* column_widths_;
  char format_char_;		// alternative to @-sign
  char column_char_;		// alternative to tab

protected:

  // required routines for Fl_Browser_ subclass:
  void* item_first() ;
  void* item_next(void*) ;
  void* item_prev(void*) ;
  int item_selected(void*) ;
  void item_select(void*, int);
  int item_height(void*) ;
  int item_width(void*) ;
  void item_draw(void*, int, int, int, int) ;
  int full_height() ;
  int incr_height() ;

  FL_BLINE* find_line(int) ;
  FL_BLINE* _remove(int) ;
  void insert(int, FL_BLINE*);
  int lineno(void*) ;
  void swap(FL_BLINE *a, FL_BLINE *b);

public:

  void remove(int);
  void add(char*, void* = 0);
  void insert(int, char*, void* = 0);
  void move(int to, int from);
  int  load(char* filename);
  void swap(int a, int b);
  void clear();

  int size() {return lines;}
  void size(int W, int H) { Fl_Widget.size(W, H); }

  int topline() ;
  enum Fl_Line_Position { TOP, BOTTOM, MIDDLE };
  void lineposition(int, Fl_Line_Position);
  void topline(int l) { lineposition(l, TOP); }
  void bottomline(int l) { lineposition(l, BOTTOM); }
  void middleline(int l) { lineposition(l, MIDDLE); }

  int select(int, int=1);
  int selected(int) ;
  void show(int n);
  void show() {Fl_Widget.show();}
  void hide(int n);
  void hide() {Fl_Widget.hide();}
  int visible(int n) ;

  int value() ;
  void value(int v) {select(v);}
  char* text(int) ;
  void text(int, char*);
  void* data(int) ;
  void data(int, void* v);

  Fl_Browser(int, int, int, int, char* = 0);
  ~Fl_Browser() { clear(); }

  char format_char() {return format_char_;}
  void format_char(char c) {format_char_ = c;}
  char column_char() {return column_char_;}
  void column_char(char c) {column_char_ = c;}
  int* column_widths() {return column_widths_;}
  void column_widths(int* l) {column_widths_ = l;}

  int displayed(int n) {return Fl_Browser_.displayed(find_line(n));}
  void make_visible(int n) {
  	if (n < 1) Fl_Browser_.display(find_line(1));
	else if (n > lines) Fl_Browser_.display(find_line(lines));
	else Fl_Browser_.display(find_line(n));
  }

  // for back compatability only:
  void replace(int a, char* b) {text(a, b);}
  void display(int, int=1);
};

}

//
// End of "$Id: browser.d 4288 2005-04-16 00:13:17Z mike $".
//
    End of automatic import -+/
/+- This file was imported from C++ using a script
//
// "$Id: browser.d 5190 2006-06-09 16:16:34Z mike $"
//
// Browser widget for the Fast Light Tool Kit (FLTK).
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
private import fl.browser;
private import fl.draw;
private import fl.flstring;
#include <stdlib.h>
#include <math.h>

// I modified this from the original Forms data to use a linked list
// so that the number of items in the browser and size of those items
// is unlimited.  The only problem is that the old browser used an
// index number to identify a line, and it is slow to convert from/to
// a pointer.  I use a cache of the last match to try to speed this
// up.

// Also added the ability to "hide" a line.  This set's it's height to
// zero, so the Fl_Browser_ cannot pick it.

const int SELECTED = 1; 
const int NOTDISPLAYED = 2; 

struct FL_BLINE {	// data is in a linked list of these
  FL_BLINE* prev;
  FL_BLINE* next;
  void* data;
  short length;		// sizeof(txt)-1, may be longer than string
  char flags;		// selected, displayed
  char txt[1];		// start of allocated array
};

void* Fl_Browser.item_first() {return first;}

void* Fl_Browser.item_next(void* l) {return ((FL_BLINE*)l)->next;}

void* Fl_Browser.item_prev(void* l) {return ((FL_BLINE*)l)->prev;}

int Fl_Browser.item_selected(void* l) {
  return ((FL_BLINE*)l)->flags&SELECTED;}

void Fl_Browser.item_select(void* l, int v) {
  if (v) ((FL_BLINE*)l)->flags |= SELECTED;
  else ((FL_BLINE*)l)->flags &= ~SELECTED;
}

FL_BLINE* Fl_Browser.find_line(int line) {
  int n; FL_BLINE* l;
  if (line == cacheline) return cache;
  if (cacheline && line > (cacheline/2) && line < ((cacheline+lines)/2)) {
    n = cacheline; l = cache;
  } else if (line <= (lines/2)) {
    n = 1; l = first;
  } else {
    n = lines; l = last;
  }
  for (; n < line && l; n++) l = l.next;
  for (; n > line && l; n--) l = l.prev;
  ((Fl_Browser )this)->cacheline = line;
  ((Fl_Browser )this)->cache = l;
  return l;
}

int Fl_Browser.lineno(void* v) {
  FL_BLINE* l = (FL_BLINE*)v;
  if (!l) return 0;
  if (l == cache) return cacheline;
  if (l == first) return 1;
  if (l == last) return lines;
  if (!cache) {
    ((Fl_Browser )this)->cache = first;
    ((Fl_Browser )this)->cacheline = 1;
  }
  // assumme it is near cache, search both directions:
  FL_BLINE* b = cache.prev;
  int bnum = cacheline-1;
  FL_BLINE* f = cache.next;
  int fnum = cacheline+1;
  int n = 0;
  for (;;) {
    if (b == l) {n = bnum; break;}
    if (f == l) {n = fnum; break;}
    if (b) {b = b.prev; bnum--;}
    if (f) {f = f.next; fnum++;}
  }
  ((Fl_Browser )this)->cache = l;
  ((Fl_Browser )this)->cacheline = n;
  return n;
}

FL_BLINE* Fl_Browser._remove(int line) {
  FL_BLINE* ttt = find_line(line);
  deleting(ttt);

  cacheline = line-1;
  cache = ttt.prev;
  lines--;
  full_height_ -= item_height(ttt);
  if (ttt.prev) ttt.prev.next = ttt.next;
  else first = ttt.next;
  if (ttt.next) ttt.next.prev = ttt.prev;
  else last = ttt.prev;

  return(ttt);
}

void Fl_Browser.remove(int line) {
  if (line < 1 || line > lines) return;
  free(_remove(line));
}

void Fl_Browser.insert(int line, FL_BLINE* t) {
  if (!first) {
    t.prev = t.next = 0;
    first = last = t;
  } else if (line <= 1) {
    inserting(first, t);
    t.prev = 0;
    t.next = first;
    t.next.prev = t;
    first = t;
  } else if (line > lines) {
    t.prev = last;
    t.prev.next = t;
    t.next = 0;
    last = t;
  } else {
    FL_BLINE* n = find_line(line);
    inserting(n, t);
    t.next = n;
    t.prev = n.prev;
    t.prev.next = t;
    n.prev = t;
  }
  cacheline = line;
  cache = t;
  lines++;
  full_height_ += item_height(t);
  redraw_line(t);
}

void Fl_Browser.insert(int line, char* newtext, void* d) {
  int l = strlen(newtext);
  FL_BLINE* t = (FL_BLINE*)malloc(sizeof(FL_BLINE)+l);
  t.length = (short)l;
  t.flags = 0;
  strcpy(t.txt, newtext);
  t.data = d;
  insert(line, t);
}

void Fl_Browser.move(int to, int from) {
  if (from < 1 || from > lines) return;
  insert(to, _remove(from));
}

void Fl_Browser.text(int line, char* newtext) {
  if (line < 1 || line > lines) return;
  FL_BLINE* t = find_line(line);
  int l = strlen(newtext);
  if (l > t.length) {
    FL_BLINE* n = (FL_BLINE*)malloc(sizeof(FL_BLINE)+l);
    replacing(t, n);
    cache = n;
    n.data = t.data;
    n.length = (short)l;
    n.flags = t.flags;
    n.prev = t.prev;
    if (n.prev) n.prev.next = n; else first = n;
    n.next = t.next;
    if (n.next) n.next.prev = n; else last = n;
    free(t);
    t = n;
  }
  strcpy(t.txt, newtext);
  redraw_line(t);
}

void Fl_Browser.data(int line, void* d) {
  if (line < 1 || line > lines) return;
  find_line(line)->data = d;
}

int Fl_Browser.item_height(void* lv) {
  FL_BLINE* l = (FL_BLINE*)lv;
  if (l.flags & NOTDISPLAYED) return 0;

  int hmax = 2; // use 2 to insure we don't return a zero!

  if (!l.txt[0]) {
    // For blank lines set the height to exactly 1 line!
    fl_font(textfont(), textsize());
    int hh = fl_height();
    if (hh > hmax) hmax = hh;
  }
  else {
    int* i = column_widths();
    // do each column separately as they may all set different fonts:
    for (char* str = l.txt; str && *str; str++) {
      Fl_Font font = textfont(); // default font
      int tsize = textsize(); // default size
      while (*str==format_char()) {
	str++;
	switch (*str++) {
	case 'l': case 'L': tsize = 24; break;
	case 'm': case 'M': tsize = 18; break;
	case 's': tsize = 11; break;
	case 'b': font = (Fl_Font)(font|FL_BOLD); break;
	case 'i': font = (Fl_Font)(font|FL_ITALIC); break;
	case 'f': case 't': font = FL_COURIER; break;
	case 'B':
	case 'C': strtol(str, &str, 10); break;// skip a color number
	case 'F': font = (Fl_Font)strtol(str,&str,10); break;
	case 'S': tsize = strtol(str,&str,10); break;
	case 0: case '@': str--;
	case '.': goto END_FORMAT;
	}
      }
      END_FORMAT:
      char* ptr = str;
      if (ptr && *i++) str = strchr(str, column_char());
      else str = NULL;
      if((!str && *ptr) || (str && ptr < str)) {
	fl_font(font, tsize); int hh = fl_height();
	if (hh > hmax) hmax = hh;
      }
      if (!str || !*str) break;
    }
  }

  return hmax; // previous version returned hmax+2!
}

int Fl_Browser.item_width(void* v) {
  char* str = ((FL_BLINE*)v)->txt;
  int* i = column_widths();
  int ww = 0;

  while (*i) { // add up all tab-seperated fields
    char* e;
    e = strchr(str, column_char());
    if (!e) break; // last one occupied by text
    str = e+1;
    ww += *i++;
  }

  // OK, we gotta parse the string and find the string width...
  int tsize = textsize();
  Fl_Font font = textfont();
  int done = 0;

  while (*str == format_char_ && str[1] && str[1] != format_char_) {
    str ++;
    switch (*str++) {
    case 'l': case 'L': tsize = 24; break;
    case 'm': case 'M': tsize = 18; break;
    case 's': tsize = 11; break;
    case 'b': font = (Fl_Font)(font|FL_BOLD); break;
    case 'i': font = (Fl_Font)(font|FL_ITALIC); break;
    case 'f': case 't': font = FL_COURIER; break;
    case 'B':
    case 'C': strtol(str, &str, 10); break;// skip a color number
    case 'F': font = (Fl_Font)strtol(str, &str, 10); break;
    case 'S': tsize = strtol(str, &str, 10); break;
    case '.':
      done = 1;
      break;
    case '@':
      str--;
      done = 1;
    }

    if (done)
      break;
  }

  if (*str == format_char_ && str[1])
    str ++;

  fl_font(font, tsize);
  return ww + int(fl_width(str)) + 6;
}

int Fl_Browser.full_height() {
  return full_height_;
}

int Fl_Browser.incr_height() {
  return textsize()+2;
}

void Fl_Browser.item_draw(void* v, int X, int Y, int W, int H) {
  char* str = ((FL_BLINE*)v)->txt;
  int* i = column_widths();

  while (W > 6) {	// do each tab-seperated field
    int w1 = W;	// width for this field
    char* e = 0; // pointer to end of field or null if none
    if (*i) { // find end of field and temporarily replace with 0
      e = strchr(str, column_char());
      if (e) {*e = 0; w1 = *i++;}
    }
    int tsize = textsize();
    Fl_Font font = textfont();
    Fl_Color lcol = textcolor();
    Fl_Align talign = FL_ALIGN_LEFT;
    // check for all the @-lines recognized by XForms:
    while (*str == format_char() && *++str && *str != format_char()) {
      switch (*str++) {
      case 'l': case 'L': tsize = 24; break;
      case 'm': case 'M': tsize = 18; break;
      case 's': tsize = 11; break;
      case 'b': font = (Fl_Font)(font|FL_BOLD); break;
      case 'i': font = (Fl_Font)(font|FL_ITALIC); break;
      case 'f': case 't': font = FL_COURIER; break;
      case 'c': talign = FL_ALIGN_CENTER; break;
      case 'r': talign = FL_ALIGN_RIGHT; break;
      case 'B': 
	if (!(((FL_BLINE*)v)->flags & SELECTED)) {
	  fl_color((Fl_Color)strtol(str, &str, 10));
	  fl_rectf(X, Y, w1, H);
	} else strtol(str, &str, 10);
        break;
      case 'C':
	lcol = (Fl_Color)strtol(str, &str, 10);
	break;
      case 'F':
	font = (Fl_Font)strtol(str, &str, 10);
	break;
      case 'N':
	lcol = FL_INACTIVE_COLOR;
	break;
      case 'S':
	tsize = strtol(str, &str, 10);
	break;
      case '-':
	fl_color(FL_DARK3);
	fl_line(X+3, Y+H/2, X+w1-3, Y+H/2);
	fl_color(FL_LIGHT3);
	fl_line(X+3, Y+H/2+1, X+w1-3, Y+H/2+1);
	break;
      case 'u':
      case '_':
	fl_color(lcol);
	fl_line(X+3, Y+H-1, X+w1-3, Y+H-1);
	break;
      case '.':
	goto BREAK;
      case '@':
	str--; goto BREAK;
      }
    }
  BREAK:
    fl_font(font, tsize);
    if (((FL_BLINE*)v)->flags & SELECTED)
      lcol = fl_contrast(lcol, selection_color());
    if (!active_r()) lcol = fl_inactive(lcol);
    fl_color(lcol);
    fl_draw(str, X+3, Y, w1-6, H, e ? Fl_Align(talign|FL_ALIGN_CLIP) : talign, 0, 0);
    if (!e) break; // no more fields...
    *e = column_char(); // put the seperator back
    X += w1;
    W -= w1;
    str = e+1;
  }
}

static int no_columns[1] = {0};

Fl_Browser.Fl_Browser(int X, int Y, int W, int H, char*l)
  : Fl_Browser_(X, Y, W, H, l) {
  column_widths_ = no_columns;
  lines = 0;
  full_height_ = 0;
  cacheline = 0;
  format_char_ = '@';
  column_char_ = '\t';
  first = last = cache = 0;
}

void Fl_Browser.lineposition(int line, Fl_Line_Position pos) {
  if (line<1) line = 1;
  if (line>lines) line = lines;
  int p = 0;

  FL_BLINE* l;
  for (l=first; l && line>1; l = l.next) {
    line--; p += item_height(l);
  }
  if (l && (pos == BOTTOM)) p += item_height (l);

  int final = p, X, Y, W, H;
  bbox(X, Y, W, H);

  switch(pos) {
    case TOP: break;
    case BOTTOM: final -= H; break;
    case MIDDLE: final -= H/2; break;
  }
  
  if (final > (full_height() - H)) final = full_height() -H;
  position(final);
}

int Fl_Browser.topline() {
  return lineno(top());
}

void Fl_Browser.clear() {
  for (FL_BLINE* l = first; l;) {
    FL_BLINE* n = l.next;
    free(l);
    l = n;
  }
  full_height_ = 0;
  first = 0;
  lines = 0;
  new_list();
}

void Fl_Browser.add(char* newtext, void* d) {
  insert(lines+1, newtext, d);
  //Fl_Browser_.display(last);
}

const char* Fl_Browser.text(int line) {
  if (line < 1 || line > lines) return 0;
  return find_line(line)->txt;
}

void* Fl_Browser.data(int line) {
  if (line < 1 || line > lines) return 0;
  return find_line(line)->data;
}

int Fl_Browser.select(int line, int v) {
  if (line < 1 || line > lines) return 0;
  return Fl_Browser_.select(find_line(line), v);
}

int Fl_Browser.selected(int line) {
  if (line < 1 || line > lines) return 0;
  return find_line(line)->flags & SELECTED;
}

void Fl_Browser.show(int line) {
  FL_BLINE* t = find_line(line);
  if (t.flags & NOTDISPLAYED) {
    t.flags &= ~NOTDISPLAYED;
    full_height_ += item_height(t);
    if (Fl_Browser_.displayed(t)) redraw_lines();
  }
}

void Fl_Browser.hide(int line) {
  FL_BLINE* t = find_line(line);
  if (!(t.flags & NOTDISPLAYED)) {
    full_height_ -= item_height(t);
    t.flags |= NOTDISPLAYED;
    if (Fl_Browser_.displayed(t)) redraw_lines();
  }
}

void Fl_Browser.display(int line, int v) {
  if (line < 1 || line > lines) return;
  if (v) show(line); else hide(line);
}

int Fl_Browser.visible(int line) {
  if (line < 1 || line > lines) return 0;
  return !(find_line(line)->flags&NOTDISPLAYED);
}

int Fl_Browser.value() {
  return lineno(selection());
}

// SWAP TWO LINES
void Fl_Browser.swap(FL_BLINE *a, FL_BLINE *b) {

  if ( a == b || !a || !b) return;          // nothing to do
  swapping(a, b);
  FL_BLINE *aprev  = a.prev;
  FL_BLINE *anext  = a.next;
  FL_BLINE *bprev  = b.prev;
  FL_BLINE *bnext  = b.next;
  if ( b.prev == a ) { 		// A ADJACENT TO B
     if ( aprev ) aprev.next = b; else first = b;
     b.next = a;
     a.next = bnext;
     b.prev = aprev;
     a.prev = b;
     if ( bnext ) bnext.prev = a; else last = a;
  } else if ( a.prev == b ) {		// B ADJACENT TO A
     if ( bprev ) bprev.next = a; else first = a;
     a.next = b;
     b.next = anext;
     a.prev = bprev;
     b.prev = a;
     if ( anext ) anext.prev = b; else last = b;
  } else {				// A AND B NOT ADJACENT
     // handle prev's
     b.prev = aprev;
     if ( anext ) anext.prev = b; else last = b;
     a.prev = bprev;
     if ( bnext ) bnext.prev = a; else last = a;
     // handle next's
     if ( aprev ) aprev.next = b; else first = b;
     b.next = anext;
     if ( bprev ) bprev.next = a; else first = a;
     a.next = bnext;
  }
  // Disable cache -- we played around with positions
  cacheline = 0;
  cache = 0;
}

void Fl_Browser.swap(int ai, int bi) {
  if (ai < 1 || ai > lines || bi < 1 || bi > lines) return;
  FL_BLINE* a = find_line(ai);
  FL_BLINE* b = find_line(bi);
  swap(a,b);
}

//
// End of "$Id: browser.d 5190 2006-06-09 16:16:34Z mike $".
//
    End of automatic import -+/
