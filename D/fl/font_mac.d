//
// "$Id: font_mac.d 5190 2006-06-09 16:16:34Z mike $"
//
// MacOS font selection routines for the Fast Light Tool Kit (FLTK).
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

module fl.font_mac;

private import std.c.osx.carbon.carbon;
private import fl.x;
private import fl.fl;
private import fl.window;

private import std.stdio;

class Fl_FontSize {
public:
  Fl_FontSize next;    // linked list for this Fl_Fontdesc
  this(char[] name, int Size) {
    next = null;
    listbase = 0;
    q_name = name.dup;
    size = Size;
    OSStatus err;
      // fill our structure with a few default values
    ascent = Size*3/4;
    descent = Size-ascent;
    q_width = Size*2/3;
    minsize = maxsize = Size;
      // now use ATS to get the actual Glyph size information
    CFStringRef cfname = CFStringCreateWithCString(null, name, kCFStringEncodingASCII);
    ATSFontRef font = ATSFontFindFromName(cfname, kATSOptionFlagsDefault);
    if (font) {
      ATSFontMetrics m;
      ATSFontGetHorizontalMetrics(font, kATSOptionFlagsDefault, &m);
      if (m.avgAdvanceWidth) q_width = cast(int)(m.avgAdvanceWidth*Size);
        // playing with the offsets a little to make standard sizes fit
      if (m.ascent) ascent  = cast(int)(m.ascent*Size-0.5f);
      if (m.descent) descent = -cast(int)(m.descent*Size-1.5f);
    }
    CFRelease(cfname);
      // now we allocate everything needed to render text in this font later
      // get us the default layout and style
    err = ATSUCreateTextLayout(&layout);
    UniChar mTxt[2]; mTxt[0] = 65; mTxt[1] = 0;
    err = ATSUSetTextPointerLocation(layout, mTxt, kATSUFromTextBeginning, 1, 1);
    err = ATSUCreateStyle(&style);
    err = ATSUSetRunStyle(layout, style, kATSUFromTextBeginning, kATSUToTextEnd);
      // now set the actual font, size and attributes. We also set the font matrix to 
      // render our font up-side-down, so when rendered through our inverted CGContext,
      // text will appear normal again.
    Fixed fsize = IntToFixed(Size);
    ATSUFontID fontID = FMGetFontFromATSFontRef(font);
    static CGAffineTransform font_mx = { 1, 0, 0, -1, 0, 0 };
    static ATSUAttributeTag sTag[] = [ kATSUFontTag, kATSUSizeTag, kATSUFontMatrixTag ];
    static ByteCount sBytes[] = [ ATSUFontID.sizeof, Fixed.sizeof, CGAffineTransform.sizeof ];
    static ATSUAttributeValuePtr sAttr[3];
      sAttr[0] = &fontID;
      sAttr[1] = &fsize;
      sAttr[2] = &font_mx;
    err = ATSUSetAttributes(style, 3, sTag, sBytes, sAttr);
      // next, make sure that Quartz will only render at integer coordinates
    static ATSLineLayoutOptions llo = kATSLineUseDeviceMetrics|kATSLineDisableAllLayoutOperations;
    static ATSUAttributeTag aTag[] = [ kATSULineLayoutOptionsTag ];
    static ByteCount aBytes[] = [ ATSLineLayoutOptions.sizeof ];
    static ATSUAttributeValuePtr aAttr[] = [ &llo ];
    err = ATSUSetLineControls (layout, kATSUFromTextBeginning, 1, aTag, aBytes, aAttr);
      // now we are finally ready to measure some letter to get the bounding box
    Fixed bBefore, bAfter, bAscent, bDescent;
    err = ATSUGetUnjustifiedBounds(layout, kATSUFromTextBeginning, 1, &bBefore, &bAfter, &bAscent, &bDescent);
      // Requesting a certain height font on Mac does not guarantee that ascent+descent
      // equal the requested height. I consider requesting noew fonts until that is the
      // case, but for now we simply make sure that our store ascent and descent add up 
      // as expected.
      // The font "Apple Chancery" is a pretty extreme example of overlapping letters.
    float fa = -FixedToFloat(bAscent), fd = -FixedToFloat(bDescent);
    if (fa>0.0f && fd>0.0f) {
      float f = Size/(fa+fd);
      ascent = cast(int)(fa*f+0.5f);
      descent = Size - ascent;
    }
    int w = FixedToInt(bAfter);
    if (w)  
      q_width = FixedToInt(bAfter);
  }
  ATSUTextLayout layout;
  ATSUStyle style;
  short ascent, descent, q_width;
  char[] q_name;
  int size;
  int minsize;          // smallest point size that should use this
  int maxsize;          // largest point size that should use this
  uint listbase;	// base of display list, 0 = none
  ~this() {
   // ++ todo: remove OpenGL font alocations
    if (this == fl_fontsize) fl_fontsize = null;
    ATSUDisposeTextLayout(layout);
    ATSUDisposeStyle(style);
  }
}

struct Fl_Fontdesc {
  char[] name;
  char[128] fontname;   // "Pretty" font name
  Fl_FontSize first;   // linked list of sizes of this style
  char** xlist;         // matched X font names
  int n;                // size of xlist, negative = don't free xlist!
};

Fl_FontSize fl_fontsize = null;

////////////////////////////////////////////////////////////////

static const Fl_Fontdesc built_in_table[] = [
  {"Arial"},
  {"Arial Bold"},
  {"Arial Italic"},
  {"Arial Bold Italic"},
  {"Courier New"},
  {"Courier New Bold"},
  {"Courier New Italic"},
  {"Courier New Bold Italic"},
  {"Times New Roman"},
  {"Times New Roman Bold"},
  {"Times New Roman Italic"},
  {"Times New Roman Bold Italic"},
  {"Symbol"},
  {"Monaco"},
  {"Andale Mono"}, // there is no bold Monaco font on standard Mac
  {"Webdings"},
];

static const UniChar utf16lut[128] = [
  0x00c4, 0x00c5, 0x00c7, 0x00c9, 0x00d1, 0x00d6, 0x00dc, 0x00e1, 
  0x00e0, 0x00e2, 0x00e4, 0x00e3, 0x00e5, 0x00e7, 0x00e9, 0x00e8, 
  0x00ea, 0x00eb, 0x00ed, 0x00ec, 0x00ee, 0x00ef, 0x00f1, 0x00f3, 
  0x00f2, 0x00f4, 0x00f6, 0x00f5, 0x00fa, 0x00f9, 0x00fb, 0x00fc, 
  0x2020, 0x00b0, 0x00a2, 0x00a3, 0x00a7, 0x2022, 0x00b6, 0x00df, 
  0x00ae, 0x00a9, 0x2122, 0x00b4, 0x00a8, 0x2260, 0x00c6, 0x00d8, 
  0x221e, 0x00b1, 0x2264, 0x2265, 0x00a5, 0x00b5, 0x2202, 0x2211, 
  0x220f, 0x03c0, 0x222b, 0x00aa, 0x00ba, 0x03a9, 0x00e6, 0x00f8, 
  0x00bf, 0x00a1, 0x00ac, 0x221a, 0x0192, 0x2248, 0x2206, 0x00ab, 
  0x00bb, 0x2026, 0x00a0, 0x00c0, 0x00c3, 0x00d5, 0x0152, 0x0153, 
  0x2013, 0x2014, 0x201c, 0x201d, 0x2018, 0x2019, 0x00f7, 0x25ca, 
  0x00ff, 0x0178, 0x2044, 0x20ac, 0x2039, 0x203a, 0xfb01, 0xfb02, 
  0x2021, 0x00b7, 0x201a, 0x201e, 0x2030, 0x00c2, 0x00ca, 0x00c1, 
  0x00cb, 0x00c8, 0x00cd, 0x00ce, 0x00cf, 0x00cc, 0x00d3, 0x00d4, 
  0xf8ff, 0x00d2, 0x00da, 0x00db, 0x00d9, 0x0131, 0x02c6, 0x02dc, 
  0x00af, 0x02d8, 0x02d9, 0x02da, 0x00b8, 0x02dd, 0x02db, 0x02c7, 
];
static UniChar[] utf16buf;

UniChar[] fl_macToUtf16(char[] txt)
{
  uint i, len = txt.length;
  utf16buf.length = len;
  char *src = txt.ptr;
  UniChar *dst = utf16buf;
  foreach(c; txt) {
    *dst++ = (c<128) ? cast(UniChar)c : utf16lut[c-128];
  }
  return utf16buf;
}

Fl_Fontdesc[] fl_fonts = built_in_table;

void fl_font(Fl_FontSize s) {
  fl_fontsize = s;
  // we will use fl_fontsize later to access the required style and layout
}

static Fl_FontSize find(int fnum, int size) {
  Fl_Fontdesc s = fl_fonts[fnum];
  if (!s.name) s = fl_fonts[0]; // use 0 if fnum undefined
  Fl_FontSize f;
  for (f = s.first; f; f = f.next)
    if (f.minsize <= size && f.maxsize >= size) return f;
  f = new Fl_FontSize(s.name, size);
  f.next = s.first;
  s.first = f;
  return f;
}

////////////////////////////////////////////////////////////////
// Public interface:

int fl_font_ = 0;
int fl_size_ = 0;

void fl_font(int fnum, int size) {
  fl_font_ = fnum;
  fl_size_ = size;
  fl_font(find(fnum, size));
}

int fl_height() {
  if (fl_fontsize) return fl_fontsize.ascent+fl_fontsize.descent;
  else return -1;
}

int fl_descent() {
  if (fl_fontsize) return fl_fontsize.descent;
  else return -1;
}

double fl_width(char[] txt) {
  uint n = txt.length;
  if (!fl_gc) {
    Fl_Window w = Fl.first_window();
    if (w) w.make_current();
    if (!fl_gc) {
      // We fall back to some internal QuickDraw port.
      // The result should be the same.
    }
  }
  if (!fl_fontsize) {
    fl_font(0, 12); // avoid a crash!
    if (!fl_fontsize)
      return 0.0; // user must select a font first!
  }
  OSStatus err;
    // convert to UTF-16 first
  UniChar[] uniStr = fl_macToUtf16(txt);
    // now collect our ATSU resources
  ATSUTextLayout layout = fl_fontsize.layout;
  err = ATSUSetTextPointerLocation(layout, uniStr.ptr, kATSUFromTextBeginning, n, n);
    // activate the current GC
  ByteCount iSize = CGContextRef.sizeof;
  ATSUAttributeTag iTag = kATSUCGContextTag;
  ATSUAttributeValuePtr iValuePtr = &fl_gc;
  ATSUSetLayoutControls(layout, 1, &iTag, &iSize, &iValuePtr);
    // now measure the bounding box
  Fixed bBefore, bAfter, bAscent, bDescent;
  err = ATSUGetUnjustifiedBounds(
    layout, kATSUFromTextBeginning, n, 
    &bBefore, &bAfter, &bAscent, &bDescent);
  return FixedToInt(bAfter);
}

double fl_width(char c) {
  char[1] txt = c;
  return fl_width(txt);
}

double fl_width(char* str, int len) {
  char[] dstr = str[0..len];
  return fl_width(dstr);
}

void fl_draw(char[] str, int x, int y) {
  OSStatus err;
    // convert to UTF-16 first 
  UniChar[] uniStr = fl_macToUtf16(str);
    // now collect our ATSU resources
  ATSUTextLayout layout = fl_fontsize.layout;

  ByteCount iSize = CGContextRef.sizeof;
  ATSUAttributeTag iTag = kATSUCGContextTag;
  ATSUAttributeValuePtr iValuePtr=&fl_gc;
  ATSUSetLayoutControls(layout, 1, &iTag, &iSize, &iValuePtr);

  uint n = uniStr.length;
  err = ATSUSetTextPointerLocation(layout, uniStr.ptr, kATSUFromTextBeginning, n, n);
  err = ATSUDrawText(layout, kATSUFromTextBeginning, n, FloatToFixed(x), FloatToFixed(y));
}

//
// End of "$Id: fl_font_mac.cxx 5190 2006-06-09 16:16:34Z mike $".
//
