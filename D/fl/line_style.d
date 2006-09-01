//
// "$Id: fl_line_style.cxx 5190 2006-06-09 16:16:34Z mike $"
//
// Line style code for the Fast Light Tool Kit (FLTK).
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

module fl.line_style;

private import fl.fl;
private import fl.x;
private import fl.draw;
private import fl.flstring;

version (__APPLE__) {
  private import std.c.osx.carbon.carbon;
  private import std.c.osx.qd.quickdraw;

  float fl_quartz_line_width_ = 1.0f;
  static CGLineCap fl_quartz_line_cap_ = CGLineCap.kCGLineCapButt;
  static CGLineJoin fl_quartz_line_join_ = CGLineJoin.kCGLineJoinMiter;
  static float* fl_quartz_line_pattern = null;
  static int fl_quartz_line_pattern_size = 0;
  void fl_quartz_restore_line_style_() {
    CGContextSetLineWidth(fl_gc, fl_quartz_line_width_);
    CGContextSetLineCap(fl_gc, fl_quartz_line_cap_);
    CGContextSetLineJoin(fl_gc, fl_quartz_line_join_);
    CGContextSetLineDash(fl_gc, 0, fl_quartz_line_pattern, fl_quartz_line_pattern_size);
  }
}

void fl_line_style(int style, int width=0, char* dashes=null) {
  version (WIN32) {
    // According to Bill, the "default" cap and join should be the
    // "fastest" mode supported for the platform.  I don't know why
    // they should be different (same graphics cards, etc., right?) MRS
    static DWORD Cap[4]= {PS_ENDCAP_FLAT, PS_ENDCAP_FLAT, PS_ENDCAP_ROUND, PS_ENDCAP_SQUARE};
    static DWORD Join[4]={PS_JOIN_ROUND, PS_JOIN_MITER, PS_JOIN_ROUND, PS_JOIN_BEVEL};
    int s1 = PS_GEOMETRIC | Cap[(style>>8)&3] | Join[(style>>12)&3];
    DWORD a[16]; int n = 0;
    if (dashes && dashes[0]) {
      s1 |= PS_USERSTYLE;
      for (n = 0; n < 16 && *dashes; n++) a[n] = *dashes++;
    } else {
      s1 |= style & 0xff; // allow them to pass any low 8 bits for style
    }
    if ((style || n) && !width) width = 1; // fix cards that do nothing for 0?
    LOGBRUSH penbrush = {BS_SOLID,fl_RGB(),0}; // can this be fl_brush()?
    HPEN newpen = ExtCreatePen(s1, width, &penbrush, n, n ? a : 0);
    if (!newpen) {
      Fl.error("fl_line_style(): Could not create GDI pen object.");
      return;
    }
    HPEN oldpen = cast(HPEN)SelectObject(fl_gc, newpen);
    DeleteObject(oldpen);
    DeleteObject(fl_current_xmap.pen);
    fl_current_xmap.pen = newpen;
  } else version (__APPLE__) {
    static CGLineCap Cap[4] = [ CGLineCap.kCGLineCapButt, CGLineCap.kCGLineCapButt, 
                                     CGLineCap.kCGLineCapRound, CGLineCap.kCGLineCapSquare ];
    static CGLineJoin Join[4] = [ CGLineJoin.kCGLineJoinMiter, CGLineJoin.kCGLineJoinMiter, 
                                      CGLineJoin.kCGLineJoinRound, CGLineJoin.kCGLineJoinBevel ];
    if (width<1) width = 1;
    fl_quartz_line_width_ = cast(float)width; 
    fl_quartz_line_cap_ = Cap[(style>>8)&3];
    fl_quartz_line_join_ = Join[(style>>12)&3];
    char *d = dashes; 
    static float pattern[16];
    if (d && *d) {
      float *p = pattern;
      while (*d) { *p++ = cast(float)*d++; }
      fl_quartz_line_pattern = pattern;
      fl_quartz_line_pattern_size = d-dashes;
    } else if (style & 0xff) {
      char dash, dot, gap;
      // adjust lengths to account for cap:
      if (style & 0x200) {
        dash = cast(char)(2*width);
        dot = 1; 
        gap = cast(char)(2*width-1);
      } else {
        dash = cast(char)(3*width);
        dot = gap = cast(char)(width);
      }
      float *p = pattern;
      switch (style & 0xff) {
      case FL_DASH:       *p++ = dash; *p++ = gap; break;
      case FL_DOT:        *p++ = dot; *p++ = gap; break;
      case FL_DASHDOT:    *p++ = dash; *p++ = gap; *p++ = dot; *p++ = gap; break;
      case FL_DASHDOTDOT: *p++ = dash; *p++ = gap; *p++ = dot; *p++ = gap; *p++ = dot; *p++ = gap; break;
      }
      fl_quartz_line_pattern_size = p-pattern.ptr;
      fl_quartz_line_pattern = pattern;
    } else {
      fl_quartz_line_pattern = null; fl_quartz_line_pattern_size = 0;
    }
    fl_quartz_restore_line_style_();
  } else {
    int ndashes = dashes ? strlen(dashes) : 0;
    // emulate the WIN32 dash patterns on X
    char buf[7];
    if (!ndashes && (style&0xff)) {
      int w = width ? width : 1;
      char dash, dot, gap;
      // adjust lengths to account for cap:
      if (style & 0x200) {
        dash = cast(char)(2*w);
        dot = 1; // unfortunately 0 does not work
        gap = cast(char)(2*w-1);
      } else {
        dash = cast(char)(3*w);
        dot = gap = cast(char)(w);
      }
      char* p = dashes = buf;
      switch (style & 0xff) {
      case FL_DASH:	*p++ = dash; *p++ = gap; break;
      case FL_DOT:	*p++ = dot; *p++ = gap; break;
      case FL_DASHDOT:	*p++ = dash; *p++ = gap; *p++ = dot; *p++ = gap; break;
      case FL_DASHDOTDOT: *p++ = dash; *p++ = gap; *p++ = dot; *p++ = gap; *p++ = dot; *p++ = gap; break;
      }
      ndashes = p-buf.ptr;
    }
    static int Cap[4] = [CapButt, CapButt, CapRound, CapProjecting];
    static int Join[4] = [JoinMiter, JoinMiter, JoinRound, JoinBevel];
    XSetLineAttributes(fl_display, fl_gc, width, 
  		     ndashes ? LineOnOffDash : LineSolid,
  		     Cap[(style>>8)&3], Join[(style>>12)&3]);
    if (ndashes) XSetDashes(fl_display, fl_gc, 0, dashes, ndashes);
  }
}


//
// End of "$Id: fl_line_style.cxx 5190 2006-06-09 16:16:34Z mike $".
//
