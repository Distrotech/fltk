//
// "$Id$"
//
// implementation of fltk3::Device class for the Fast Light Tool Kit (FLTK).
//
// Copyright 2010-2011 by Bill Spitzak and others.
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
// Please report all bugs and problems to:
//
//     http://www.fltk.org/str.php
//

#include <config.h>

#ifdef __APPLE__

#include "quartz_graphics_driver.h"

#include <fltk3/run.h>
#include <fltk3/x.h>
#include <fltk3/draw.h>
#include <fltk3/Widget.h>
#include <fltk3/MenuItem.h>
#include <fltk3/Bitmap.h>
#include <fltk3/Printer.h>
#include <fltk3/Image.h>
#include <fltk3/DoubleWindow.h>
#include <fltk3/utf8.h>

#include "../flstring.h"
#include "../font.h"

extern int fl_line_width_;
extern unsigned fl_cmap[256];

float fl_quartz_line_width_ = 1.0f;
static enum CGLineCap fl_quartz_line_cap_ = kCGLineCapButt;
static enum CGLineJoin fl_quartz_line_join_ = kCGLineJoinMiter;
static CGFloat *fl_quartz_line_pattern = 0;
static int fl_quartz_line_pattern_size = 0;
void fl_quartz_restore_line_style_() {
  CGContextSetLineWidth(fl_gc, fl_quartz_line_width_);
  CGContextSetLineCap(fl_gc, fl_quartz_line_cap_);
  CGContextSetLineJoin(fl_gc, fl_quartz_line_join_);
  CGContextSetLineDash(fl_gc, 0, fl_quartz_line_pattern, fl_quartz_line_pattern_size);
}

extern Fl_Font_Descriptor* fltk3_find(fltk3::Font fnum, fltk3::Fontsize size);

extern int fltk3_start(fltk3::Bitmap *bm,
                       int XP, int YP, int WP, int HP,
                       int w, int h, int &cx, int &cy,
                       int &X, int &Y, int &W, int &H);

extern int fltk3_start(fltk3::RGBImage *img,
                       int XP, int YP, int WP, int HP,
                       int w, int h, int &cx, int &cy,
                       int &X, int &Y, int &W, int &H);


void fltk3::QuartzGraphicsDriver::draw(fltk3::Bitmap *bm, int XP, int YP, int WP, int HP, int cx, int cy) {
  int X, Y, W, H;
  if (!bm->array) {
    bm->draw_empty(XP, YP);
    return;
  }
  if (fltk3_start(bm, XP, YP, WP, HP, bm->w(), bm->h(), cx, cy, X, Y, W, H)) {
    return;
  }
  if (!bm->id_) bm->id_ = fl_create_bitmask(bm->w(), bm->h(), bm->array);
  if (bm->id_ && fl_gc) {
    CGRect rect = { { X+origin_x(), Y+origin_y()}, { W, H } };
    Fl_X::q_begin_image(rect, cx, cy, bm->w(), bm->h());
    CGContextDrawImage(fl_gc, rect, (CGImageRef)bm->id_);
    Fl_X::q_end_image();
  }
}


static void imgProviderReleaseData (void *info, const void *data, size_t size)
{
  delete[] (unsigned char *)data;
}


void fltk3::QuartzGraphicsDriver::draw(fltk3::RGBImage *img, int XP, int YP, int WP, int HP, int cx, int cy) {
  int X, Y, W, H;
  // Don't draw an empty image...
  if (!img->d() || !img->array) {
    img->draw_empty(XP, YP);
    return;
  }
  if (fltk3_start(img, XP, YP, WP, HP, img->w(), img->h(), cx, cy, X, Y, W, H)) {
    return;
  }
  if (!img->id_) {
    CGColorSpaceRef lut = 0;
    CGDataProviderReleaseDataCallback release_cb = NULL;
    const uchar* img_bytes = img->array;
    int ld = img->ld();
    if (is_printer()) {
      // when printing, duplicate the image data so it can be deleted later, at page end
      release_cb = imgProviderReleaseData;
      fltk3::RGBImage* img2 = (fltk3::RGBImage*)img->copy();
      img2->alloc_array = 0;
      img_bytes = img2->array;
      ld = 0;
      delete img2;
    }
    if (img->d()<=2)
      lut = CGColorSpaceCreateDeviceGray();
    else
      lut = CGColorSpaceCreateDeviceRGB();
    CGDataProviderRef src = CGDataProviderCreateWithData( NULL, img_bytes, img->w()*img->h()*img->d(), release_cb);
    img->id_ = CGImageCreate( img->w(), img->h(), 8, img->d()*8, ld?ld:img->w()*img->d(),
                             lut, (img->d()&1)?kCGImageAlphaNone:kCGImageAlphaLast,
                             src, 0L, false, kCGRenderingIntentDefault);
    CGColorSpaceRelease(lut);
    CGDataProviderRelease(src);
  }
  if (img->id_ && fl_gc) {
    CGRect rect = { { X+origin_x(), Y+origin_y() }, { W, H } };
    Fl_X::q_begin_image(rect, cx, cy, img->w(), img->h());
    CGContextDrawImage(fl_gc, rect, (CGImageRef)img->id_);
    Fl_X::q_end_image();
  }
}


char fltk3::QuartzGraphicsDriver::can_do_alpha_blending() {
  return 1;
}


fltk3::Offscreen fltk3::QuartzGraphicsDriver::create_offscreen_with_alpha(int w, int h) {
  void *data = calloc(w*h,4);
  CGColorSpaceRef lut = CGColorSpaceCreateDeviceRGB();
  CGContextRef ctx = CGBitmapContextCreate(
                                           data, w, h, 8, w*4, lut, kCGImageAlphaPremultipliedLast);
  CGColorSpaceRelease(lut);
  return (fltk3::Offscreen)ctx;
}


static void bmProviderRelease (void *src, const void *data, size_t size) {
  CFIndex count = CFGetRetainCount(src);
  CFRelease(src);
  if(count == 1) free((void*)data);
}


void fltk3::QuartzGraphicsDriver::copy_offscreen(int x,int y,int w,int h,fltk3::Offscreen osrc,int srcx,int srcy) {
  CGContextRef src = (CGContextRef)osrc;
  void *data = CGBitmapContextGetData(src);
  int sw = CGBitmapContextGetWidth(src);
  int sh = CGBitmapContextGetHeight(src);
  CGImageAlphaInfo alpha = CGBitmapContextGetAlphaInfo(src);
  CGColorSpaceRef lut = CGColorSpaceCreateDeviceRGB();
  // when output goes to a Quartz printercontext, release of the bitmap must be
  // delayed after the end of the print page
  CFRetain(src);
  CGDataProviderRef src_bytes = CGDataProviderCreateWithData( src, data, sw*sh*4, bmProviderRelease);
  CGImageRef img = CGImageCreate( sw, sh, 8, 4*8, 4*sw, lut, alpha,
				 src_bytes, 0L, false, kCGRenderingIntentDefault);
  CGRect rect = { { x+origin_x(), y+origin_y() }, { w, h } };
  Fl_X::q_begin_image(rect, srcx, srcy, sw, sh);
  CGContextDrawImage(fl_gc, rect, img);
  Fl_X::q_end_image();
  CGImageRelease(img);
  CGColorSpaceRelease(lut);
  CGDataProviderRelease(src_bytes);
}


void fltk3::QuartzGraphicsDriver::draw(fltk3::Pixmap *pxm, int XP, int YP, int WP, int HP, int cx, int cy) {
  int X, Y, W, H;
  if (pxm->prepare(XP, YP, WP, HP, cx, cy, X, Y, W, H)) return;
  copy_offscreen(X, Y, W, H, (fltk3::Offscreen)pxm->id_, cx, cy);
}


void fltk3::QuartzGraphicsDriver::arc(int x,int y,int w,int h,double a1,double a2) {
  if (w <= 0 || h <= 0) return;
  x += origin_x(); y += origin_y();
  a1 = (-a1)/180.0f*M_PI; a2 = (-a2)/180.0f*M_PI;
  float cx = x + 0.5f*w - 0.5f, cy = y + 0.5f*h - 0.5f;
  CGContextSetShouldAntialias(fl_gc, true);
  if (w!=h) {
    CGContextSaveGState(fl_gc);
    CGContextTranslateCTM(fl_gc, cx, cy);
    CGContextScaleCTM(fl_gc, w-1.0f, h-1.0f);
    CGContextAddArc(fl_gc, 0, 0, 0.5, a1, a2, 1);
    CGContextRestoreGState(fl_gc);
  } else {
    float r = (w+h)*0.25f-0.5f;
    CGContextAddArc(fl_gc, cx, cy, r, a1, a2, 1);
  }
  CGContextStrokePath(fl_gc);
  CGContextSetShouldAntialias(fl_gc, false);
}


void fltk3::QuartzGraphicsDriver::pie(int x,int y,int w,int h,double a1,double a2) {
  if (w <= 0 || h <= 0) return;
  x += origin_x(); y += origin_y();
  a1 = (-a1)/180.0f*M_PI; a2 = (-a2)/180.0f*M_PI;
  float cx = x + 0.5f*w - 0.5f, cy = y + 0.5f*h - 0.5f;
  CGContextSetShouldAntialias(fl_gc, true);
  if (w!=h) {
    CGContextSaveGState(fl_gc);
    CGContextTranslateCTM(fl_gc, cx, cy);
    CGContextScaleCTM(fl_gc, w, h);
    CGContextAddArc(fl_gc, 0, 0, 0.5, a1, a2, 1);
    CGContextAddLineToPoint(fl_gc, 0, 0);
    CGContextClosePath(fl_gc);
    CGContextRestoreGState(fl_gc);
  } else {
    float r = (w+h)*0.25f;
    CGContextAddArc(fl_gc, cx, cy, r, a1, a2, 1);
    CGContextAddLineToPoint(fl_gc, cx, cy);
    CGContextClosePath(fl_gc);
  }
  CGContextFillPath(fl_gc);
  CGContextSetShouldAntialias(fl_gc, false);
}


void fltk3::QuartzGraphicsDriver::transformed_vertex(double xf, double yf) {
  transformed_vertex0(COORD_T(xf), COORD_T(yf));
}


void fltk3::QuartzGraphicsDriver::end_points() {
  int n = vertex_no();
  XPOINT *p = vertices();
  if (fl_quartz_line_width_ > 1.5f) CGContextSetShouldAntialias(fl_gc, true);
  for (int i=0; i<n; i++) {
    CGContextMoveToPoint(fl_gc, p[i].x, p[i].y);
    CGContextAddLineToPoint(fl_gc, p[i].x, p[i].y);
    CGContextStrokePath(fl_gc);
  }
  if (fl_quartz_line_width_ > 1.5f) CGContextSetShouldAntialias(fl_gc, false);
}


void fltk3::QuartzGraphicsDriver::end_line() {
  int n = vertex_no();
  XPOINT *p = vertices();
  if (n < 2) {
    end_points();
    return;
  }
  if (n<=1) return;
  CGContextSetShouldAntialias(fl_gc, true);
  CGContextMoveToPoint(fl_gc, p[0].x, p[0].y);
  for (int i=1; i<n; i++)
    CGContextAddLineToPoint(fl_gc, p[i].x, p[i].y);
  CGContextStrokePath(fl_gc);
  CGContextSetShouldAntialias(fl_gc, false);
}


void fltk3::QuartzGraphicsDriver::end_polygon() {
  fixloop();
  int n = vertex_no();
  XPOINT *p = vertices();
  if (n < 3) {
    end_line();
    return;
  }
  if (n<=1) return;
  CGContextSetShouldAntialias(fl_gc, true);
  CGContextMoveToPoint(fl_gc, p[0].x, p[0].y);
  for (int i=1; i<n; i++)
    CGContextAddLineToPoint(fl_gc, p[i].x, p[i].y);
  CGContextClosePath(fl_gc);
  CGContextFillPath(fl_gc);
  CGContextSetShouldAntialias(fl_gc, false);
}


void fltk3::QuartzGraphicsDriver::end_complex_polygon() {
  gap();
  int n = vertex_no();
  XPOINT *p = vertices();
  if (n < 3) {
    end_line();
    return;
  }
  if (n<=1) return;
  CGContextSetShouldAntialias(fl_gc, true);
  CGContextMoveToPoint(fl_gc, p[0].x, p[0].y);
  for (int i=1; i<n; i++)
    CGContextAddLineToPoint(fl_gc, p[i].x, p[i].y);
  CGContextClosePath(fl_gc);
  CGContextFillPath(fl_gc);
  CGContextSetShouldAntialias(fl_gc, false);
}


void fltk3::QuartzGraphicsDriver::circle(double x, double y, double r) {
  int llx, lly, w, h;
  double xt, yt;
  prepare_circle(x, y, r, llx, lly, w, h, xt, yt);
  // Quartz warning: circle won't scale to current matrix!
  // Last argument must be 0 (counter-clockwise) or it draws nothing under __LP64__ !!!!
  CGContextSetShouldAntialias(fl_gc, true);
  CGContextAddArc(fl_gc, xt+origin_x(), yt+origin_y(), (w+h)*0.25f, 0, 2.0f*M_PI, 0);
  (vertex_kind() == POLYGON ? CGContextFillPath : CGContextStrokePath)(fl_gc);
  CGContextSetShouldAntialias(fl_gc, false);
}


void fltk3::QuartzGraphicsDriver::line_style(int style, int width, char* dashes) {
  // save line width in global variable for X11 clipping
  if (width == 0) fl_line_width_ = 1;
  else fl_line_width_ = width>0 ? width : -width;
  static enum CGLineCap Cap[4] = { kCGLineCapButt, kCGLineCapButt,
    kCGLineCapRound, kCGLineCapSquare };
  static enum CGLineJoin Join[4] = { kCGLineJoinMiter, kCGLineJoinMiter,
    kCGLineJoinRound, kCGLineJoinBevel };
  if (width<1) width = 1;
  fl_quartz_line_width_ = (float)width;
  fl_quartz_line_cap_ = Cap[(style>>8)&3];
  fl_quartz_line_join_ = Join[(style>>12)&3];
  char *d = dashes;
  static CGFloat pattern[16];
  if (d && *d) {
    CGFloat *p = pattern;
    while (*d) { *p++ = (float)*d++; }
    fl_quartz_line_pattern = pattern;
    fl_quartz_line_pattern_size = d-dashes;
  } else if (style & 0xff) {
    char dash, dot, gap;
    // adjust lengths to account for cap:
    if (style & 0x200) {
      dash = char(2*width);
      dot = 1;
      gap = char(2*width-1);
    } else {
      dash = char(3*width);
      dot = gap = char(width);
    }
    CGFloat *p = pattern;
    switch (style & 0xff) {
      case fltk3::DASH:       *p++ = dash; *p++ = gap; break;
      case fltk3::DOT:        *p++ = dot; *p++ = gap; break;
      case fltk3::DASHDOT:    *p++ = dash; *p++ = gap; *p++ = dot; *p++ = gap; break;
      case fltk3::DASHDOTDOT: *p++ = dash; *p++ = gap; *p++ = dot; *p++ = gap; *p++ = dot; *p++ = gap; break;
    }
    fl_quartz_line_pattern_size = p-pattern;
    fl_quartz_line_pattern = pattern;
  } else {
    fl_quartz_line_pattern = 0;
    fl_quartz_line_pattern_size = 0;
  }
  fl_quartz_restore_line_style_();
}

int fltk3::QuartzGraphicsDriver::height() {
  if (!font_descriptor()) font(fltk3::HELVETICA, fltk3::NORMAL_SIZE);
  Fl_Font_Descriptor *fontsize = font_descriptor();
  return fontsize->ascent + fontsize->descent;
}


int fltk3::QuartzGraphicsDriver::descent() {
  if (!font_descriptor()) font(fltk3::HELVETICA, fltk3::NORMAL_SIZE);
  Fl_Font_Descriptor *fontsize = font_descriptor();
  return fontsize->descent+1;
}


void fltk3::QuartzGraphicsDriver::color(fltk3::Color i) {
  fltk3::GraphicsDriver::color(i);
  int index;
  uchar r, g, b;
  if (i & 0xFFFFFF00) {
    // translate rgb colors into color index
    r = i>>24;
    g = i>>16;
    b = i>> 8;
  } else {
    // translate index into rgb:
    index = i;
    unsigned c = fl_cmap[i];
    r = c>>24;
    g = c>>16;
    b = c>> 8;
  }
  if (!fl_gc) return; // no context yet? We will assign the color later.
  float fr = r/255.0f;
  float fg = g/255.0f;
  float fb = b/255.0f;
  CGContextSetRGBFillColor(fl_gc, fr, fg, fb, 1.0f);
  CGContextSetRGBStrokeColor(fl_gc, fr, fg, fb, 1.0f);
}


void fltk3::QuartzGraphicsDriver::color(uchar r, uchar g, uchar b) {
  fltk3::GraphicsDriver::color( fltk3::rgb_color(r, g, b) );
  float fr = r/255.0f;
  float fg = g/255.0f;
  float fb = b/255.0f;
  CGContextSetRGBFillColor(fl_gc, fr, fg, fb, 1.0f);
  CGContextSetRGBStrokeColor(fl_gc, fr, fg, fb, 1.0f);
}

#define MAXBUFFER 0x40000 // 256k

static void dataReleaseCB(void *info, const void *data, size_t size)
{
  delete[] (uchar *)data;
}

/*
 * draw an image based on the input parameters
 *
 * buf:       image source data
 * X, Y:      position (in buffer?!)
 * W, H:      size of picture (in pixel?)
 * delta:     distance from pixel to pixel in buf in bytes
 * linedelta: distance from line to line in buf in bytes
 * mono:      if set, pixel is one byte - if zero, pixel is 3 byte
 * cb:        callback to copy image data into (RGB?) buffer
 *   buf:       pointer to first byte in image source
 *   x, y:      position in buffer
 *   w:         width (in bytes?)
 *   dst:       destination buffer
 * userdata:  ?
 */
static void innards(const uchar *buf, int X, int Y, int W, int H,
		    int delta, int linedelta, int mono,
		    fltk3::DrawImageCb cb, void* userdata)
{
  if (!linedelta) linedelta = W*delta;
  
  const void *array = buf;
  uchar *tmpBuf = 0;
  if (cb || fltk3::SurfaceDevice::surface() != fltk3::DisplayDevice::display_device()) {
    tmpBuf = new uchar[ H*W*delta ];
    if (cb) {
      for (int i=0; i<H; i++) {
	cb(userdata, 0, i, W, tmpBuf+i*W*delta);
      }
    } else {
      uchar *p = tmpBuf;
      for (int i=0; i<H; i++) {
	memcpy(p, buf+i*linedelta, W*delta);
	p += W*delta;
      }
    }
    array = (void*)tmpBuf;
    linedelta = W*delta;
  }
  // create an image context
  CGColorSpaceRef   lut = 0;
  if (delta<=2)
    lut = CGColorSpaceCreateDeviceGray();
  else
    lut = CGColorSpaceCreateDeviceRGB();
  // a release callback is necessary when the fl_gc is a print context because the image data
  // must be kept until the page is closed. Thus tmpBuf can't be deleted here. It's too early.
  CGDataProviderRef src = CGDataProviderCreateWithData( 0L, array, linedelta*H,
						       tmpBuf ? dataReleaseCB : NULL
						       );
  CGImageRef        img = CGImageCreate( W, H, 8, 8*delta, linedelta,
                                        lut, delta&1?kCGImageAlphaNone:kCGImageAlphaNoneSkipLast,
                                        //lut, delta&1?kCGImageAlphaNone:kCGImageAlphaLast,
                                        src, 0L, false, kCGRenderingIntentDefault);
  // draw the image into the destination context
  if (img) {
    CGRect rect = { { X, Y }, { W, H } };
    Fl_X::q_begin_image(rect, 0, 0, W, H);
    CGContextDrawImage(fl_gc, rect, img);
    Fl_X::q_end_image();
    // release all allocated resources
    CGImageRelease(img);
  }
  CGColorSpaceRelease(lut);
  CGDataProviderRelease(src);
  if (img) return; // else fall through to slow mode
                   // following the very save (and very slow) way to write the image into the give port
  CGContextSetShouldAntialias(fl_gc, false);
  if ( cb )
  {
    uchar *tmpBuf = new uchar[ W*4 ];
    for ( int i=0; i<H; i++ )
    {
      uchar *src = tmpBuf;
      cb( userdata, 0, i, W, tmpBuf );
      for ( int j=0; j<W; j++ )
      {
        if ( mono )
        { fltk3::color( src[0], src[0], src[0] ); }
        else
        { fltk3::color( src[0], src[1], src[2] ); }
        CGContextMoveToPoint(fl_gc, X+j, Y+i);
        CGContextAddLineToPoint(fl_gc, X+j, Y+i);
        CGContextStrokePath(fl_gc);
        src+=delta;
      }
    }
    delete[] tmpBuf;
  }
  else
  {
    for ( int i=0; i<H; i++ )
    {
      const uchar *src = buf+i*linedelta;
      for ( int j=0; j<W; j++ )
      {
        if ( mono )
          fltk3::color( src[0], src[0], src[0] );
        else
          fltk3::color( src[0], src[1], src[2] );
        CGContextMoveToPoint(fl_gc, X+j, Y+i);
        CGContextAddLineToPoint(fl_gc, X+j, Y+i);
        CGContextStrokePath(fl_gc);
        src += delta;
      }
    }
  }
  CGContextSetShouldAntialias(fl_gc, true);
}


void fltk3::QuartzGraphicsDriver::draw_image(const uchar* buf, int x, int y, int w, int h, int d, int l){
  innards(buf,x+origin_x(),y+origin_y(),w,h,d,l,(d<3&&d>-3),0,0);
}


void fltk3::QuartzGraphicsDriver::draw_image(fltk3::DrawImageCb cb, void* data,
                                             int x, int y, int w, int h,int d) {
  innards(0,x+origin_x(),y+origin_y(),w,h,d,0,(d<3&&d>-3),cb,data);
}


void fltk3::QuartzGraphicsDriver::draw_image_mono(const uchar* buf, int x, int y, int w, int h, int d, int l){
  innards(buf,x+origin_x(),y+origin_y(),w,h,d,l,1,0,0);
}


void fltk3::QuartzGraphicsDriver::draw_image_mono(fltk3::DrawImageCb cb, void* data,
                                                  int x, int y, int w, int h,int d) {
  innards(0,x+origin_x(),y+origin_y(),w,h,d,0,1,cb,data);
}


static Fl_Fontdesc built_in_table[] = {
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
};

static UniChar *utfWbuf = 0;
static unsigned utfWlen = 0;

static CGAffineTransform font_mx = { 1, 0, 0, -1, 0, 0 };
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
static CFMutableDictionaryRef attributes = NULL;
#endif

Fl_Font_Descriptor::Fl_Font_Descriptor(const char* name, fltk3::Fontsize Size) {
  next = 0;
#  if HAVE_GL
  listbase = 0;
#  endif
  
  //  knowWidths = 0;
  // OpenGL needs those for its font handling
  q_name = strdup(name);
  size = Size;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
  if (fl_mac_os_version >= 100500) {//unfortunately, CTFontCreateWithName != NULL on 10.4 also!
    CFStringRef str = CFStringCreateWithCString(NULL, name, kCFStringEncodingUTF8);
    fontref = CTFontCreateWithName(str, size, NULL);
    CGGlyph glyph[2];
    const UniChar A[2]={'W','.'};
    CTFontGetGlyphsForCharacters(fontref, A, glyph, 2);
    CGSize advances[2];
    double w;
    CTFontGetAdvancesForGlyphs(fontref, kCTFontHorizontalOrientation, glyph, advances, 2);
    w = advances[0].width;
    if ( abs(advances[0].width - advances[1].width) < 1E-2 ) {//this is a fixed-width font
                                                              // slightly rescale fixed-width fonts so the character width has an integral value
      CFRelease(fontref);
      CGFloat fsize = size / ( w/floor(w + 0.5) );
      fontref = CTFontCreateWithName(str, fsize, NULL);
      w = CTFontGetAdvancesForGlyphs(fontref, kCTFontHorizontalOrientation, glyph, NULL, 1);
    }
    CFRelease(str);
    ascent = (short)(CTFontGetAscent(fontref) + 0.5);
    descent = (short)(CTFontGetDescent(fontref) + 0.5);
    q_width = w + 0.5;
    for (unsigned i = 0; i < sizeof(width)/sizeof(float*); i++) width[i] = NULL;
    if (!attributes) {
      static CFNumberRef zero_ref;
      float zero = 0.;
      zero_ref = CFNumberCreate(NULL, kCFNumberFloat32Type, &zero);
      // deactivate kerning for all fonts, so that string width = sum of character widths
      // which allows fast fltk3::width() implementation.
      attributes = CFDictionaryCreateMutable(kCFAllocatorDefault,
                                             3,
                                             &kCFTypeDictionaryKeyCallBacks,
                                             &kCFTypeDictionaryValueCallBacks);
      CFDictionarySetValue (attributes, kCTKernAttributeName, zero_ref);
    }
    if (ascent == 0) { // this may happen with some third party fonts
      CFDictionarySetValue (attributes, kCTFontAttributeName, fontref);
      CFAttributedStringRef mastr = CFAttributedStringCreate(kCFAllocatorDefault, CFSTR("Wj"), attributes);
      CTLineRef ctline = CTLineCreateWithAttributedString(mastr);
      CFRelease(mastr);
      CGFloat fascent, fdescent;
      CTLineGetTypographicBounds(ctline, &fascent, &fdescent, NULL);
      CFRelease(ctline);
      ascent = (short)(fascent + 0.5);
      descent = (short)(fdescent + 0.5);
    }
  }
  else {
#endif
#if ! __LP64__
    OSStatus err;
    // fill our structure with a few default values
    ascent = Size*3/4;
    descent = Size-ascent;
    q_width = Size*2/3;
    // now use ATS to get the actual Glyph size information
    // say that our passed-in name is encoded as UTF-8, since this works for plain ASCII names too...
    CFStringRef cfname = CFStringCreateWithCString(0L, name, kCFStringEncodingUTF8);
    ATSFontRef font = ATSFontFindFromName(cfname, kATSOptionFlagsDefault);
    if (font) {
      ATSFontMetrics m = { 0 };
      ATSFontGetHorizontalMetrics(font, kATSOptionFlagsDefault, &m);
      if (m.avgAdvanceWidth) q_width = int(m.avgAdvanceWidth*Size);
      // playing with the offsets a little to make standard sizes fit
      if (m.ascent) ascent  = int(m.ascent*Size-0.5f);
      if (m.descent) descent = -int(m.descent*Size-1.5f);
    }
    CFRelease(cfname);
    // now we allocate everything needed to render text in this font later
    // get us the default layout and style
    err = ATSUCreateTextLayout(&layout);
    UniChar mTxt[2] = { 65, 0 };
    err = ATSUSetTextPointerLocation(layout, mTxt, kATSUFromTextBeginning, 1, 1);
    err = ATSUCreateStyle(&style);
    err = ATSUSetRunStyle(layout, style, kATSUFromTextBeginning, kATSUToTextEnd);
    // now set the actual font, size and attributes. We also set the font matrix to
    // render our font up-side-down, so when rendered through our inverted CGContext,
    // text will appear normal again.
    Fixed fsize = IntToFixed(Size);
    //  ATSUFontID fontID = FMGetFontFromATSFontRef(font);
    ATSUFontID fontID;
    ATSUFindFontFromName(name, strlen(name), kFontFullName, kFontMacintoshPlatform, kFontRomanScript, kFontEnglishLanguage, &fontID);
    
    // draw the font upside-down... Compensate for fltk/OSX origin differences
    ATSUAttributeTag sTag[] = { kATSUFontTag, kATSUSizeTag, kATSUFontMatrixTag };
    ByteCount sBytes[] = { sizeof(ATSUFontID), sizeof(Fixed), sizeof(CGAffineTransform) };
    ATSUAttributeValuePtr sAttr[] = { &fontID, &fsize, &font_mx };
    err = ATSUSetAttributes(style, 3, sTag, sBytes, sAttr);
    // next, make sure that Quartz will only render at integer coordinates
    ATSLineLayoutOptions llo = kATSLineUseDeviceMetrics | kATSLineDisableAllLayoutOperations;
    ATSUAttributeTag aTag[] = { kATSULineLayoutOptionsTag };
    ByteCount aBytes[] = { sizeof(ATSLineLayoutOptions) };
    ATSUAttributeValuePtr aAttr[] = { &llo };
    err = ATSUSetLineControls (layout, kATSUFromTextBeginning, 1, aTag, aBytes, aAttr);
    // now we are finally ready to measure some letter to get the bounding box
    Fixed bBefore, bAfter, bAscent, bDescent;
    err = ATSUGetUnjustifiedBounds(layout, kATSUFromTextBeginning, 1, &bBefore, &bAfter, &bAscent, &bDescent);
    // Requesting a certain height font on Mac does not guarantee that ascent+descent
    // equal the requested height. fltk3::height will reflect the actual height that we got.
    // The font "Apple Chancery" is a pretty extreme example of overlapping letters.
    float fa = -FixedToFloat(bAscent), fd = -FixedToFloat(bDescent);
    if (fa>0.0f && fd>0.0f) {
      //float f = Size/(fa+fd);
      ascent = int(fa); //int(fa*f+0.5f);
      descent = int(fd); //Size - ascent;
    }
    int w = FixedToInt(bAfter);
    if (w)
      q_width = FixedToInt(bAfter);
    
# define ENABLE_TRANSIENT_FONTS  1
    
# ifdef ENABLE_TRANSIENT_FONTS
    // Now, by way of experiment, try enabling Transient Font Matching, this will
    // cause ATSU to find a suitable font to render any chars the current font can't do...
    ATSUSetTransientFontMatching (layout, true);
# endif
#endif//__LP64__
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
  }
#endif
}

Fl_Font_Descriptor::~Fl_Font_Descriptor() {
  /*
   #if HAVE_GL
   // ++ todo: remove OpenGL font alocations
   // Delete list created by gl_draw().  This is not done by this code
   // as it will link in GL unnecessarily.  There should be some kind
   // of "free" routine pointer, or a subclass?
   // if (listbase) {
   //  int base = font->min_char_or_byte2;
   //  int size = font->max_char_or_byte2-base+1;
   //  int base = 0; int size = 256;
   //  glDeleteLists(listbase+base,size);
   // }
   #endif
   */
  if (this == fltk3::graphics_driver->font_descriptor()) fltk3::graphics_driver->font_descriptor(NULL);
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
  if (fl_mac_os_version >= 100500)  {
    CFRelease(fontref);
    for (unsigned i = 0; i < sizeof(width)/sizeof(float*); i++) {
      if (width[i]) free(width[i]);
    }
  }
#endif
}
static UniChar *mac_Utf8_to_Utf16(const char *txt, int len, int *new_len)
{
  unsigned wlen = fltk3::utf8toUtf16(txt, len, (unsigned short*)utfWbuf, utfWlen);
  if (wlen >= utfWlen)
  {
    utfWlen = wlen + 100;
    if (utfWbuf) free(utfWbuf);
    utfWbuf = (UniChar*)malloc((utfWlen)*sizeof(UniChar));
    wlen = fltk3::utf8toUtf16(txt, len, (unsigned short*)utfWbuf, utfWlen);
  }
  *new_len = wlen;
  return utfWbuf;
} // mac_Utf8_to_Utf16

Fl_Fontdesc* fltk3::fonts = built_in_table;

static Fl_Font_Descriptor* find(fltk3::Font fnum, fltk3::Fontsize size) {
  Fl_Fontdesc* s = fltk3::fonts+fnum;
  if (!s->name) s = fltk3::fonts; // use 0 if fnum undefined
  Fl_Font_Descriptor* f;
  for (f = s->first; f; f = f->next)
    if (f->size == size) return f;
  f = new Fl_Font_Descriptor(s->name, size);
  f->next = s->first;
  s->first = f;
  return f;
}

Fl_Font_Descriptor* fltk3_find(fltk3::Font fnum, fltk3::Fontsize size) {
  return ::find(fnum, size);
}


#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
// returns width of a pair of UniChar's in the surrogate range
static CGFloat surrogate_width(const UniChar *txt, Fl_Font_Descriptor *fontsize)
{
  CTFontRef font2 = fontsize->fontref;
  bool must_release = false;
  CGGlyph glyphs[2];
  bool b = CTFontGetGlyphsForCharacters(font2, txt, glyphs, 2);
  CGSize a;
  if(!b) { // the current font doesn't contain this char
    CFStringRef str = CFStringCreateWithCharactersNoCopy(NULL, txt, 2, kCFAllocatorNull);
    // find a font that contains it
    font2 = CTFontCreateForString(font2, str, CFRangeMake(0,2));
    must_release = true;
    CFRelease(str);
    b = CTFontGetGlyphsForCharacters(font2, txt, glyphs, 2);
  }
  if (b) CTFontGetAdvancesForGlyphs(font2, kCTFontHorizontalOrientation, glyphs, &a, 1);
  else a.width = fontsize->q_width;
  if(must_release) CFRelease(font2);
  return a.width;
}
#endif

static double fl_mac_width(const UniChar* txt, int n, Fl_Font_Descriptor *fontsize) {
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
  if (fl_mac_os_version >= 100500) {
    double retval = 0;
    UniChar uni;
    int i;
    for (i = 0; i < n; i++) { // loop over txt
      uni = txt[i];
      if (uni >= 0xD800 && uni <= 0xDBFF) { // handles the surrogate range
        retval += surrogate_width(&txt[i], fontsize);
        i++; // because a pair of UniChar's represent a single character
        continue;
      }
      const int block = 0x10000 / (sizeof(fontsize->width)/sizeof(float*)); // block size
                                                                            // r: index of the character block containing uni
      unsigned int r = uni >> 7; // change 7 if sizeof(width) is changed
      if (!fontsize->width[r]) { // this character block has not been hit yet
                                 //fprintf(stderr,"r=%d size=%d name=%s\n",r,fltk3::fontsize->size, fltk3::fontsize->q_name);
                                 // allocate memory to hold width of each character in the block
        fontsize->width[r] = (float*) malloc(sizeof(float) * block);
        UniChar ii = r * block;
        CGSize advance_size;
        CGGlyph glyph;
        for (int j = 0; j < block; j++) { // loop over the block
                                          // ii spans all characters of this block
          bool b = CTFontGetGlyphsForCharacters(fontsize->fontref, &ii, &glyph, 1);
          if (b)
            CTFontGetAdvancesForGlyphs(fontsize->fontref, kCTFontHorizontalOrientation, &glyph, &advance_size, 1);
          else
            advance_size.width = -1e9; // calculate this later
                                       // the width of one character of this block of characters
          fontsize->width[r][j] = advance_size.width;
          ii++;
        }
      }
      // sum the widths of all characters of txt
      double wdt = fontsize->width[r][uni & (block-1)];
      if (wdt == -1e9) {
        CGSize advance_size;
        CGGlyph glyph;
	CTFontRef font2 = fontsize->fontref;
	bool must_release = false;
	bool b = CTFontGetGlyphsForCharacters(font2, &uni, &glyph, 1);
	if (!b) { // the current font doesn't contain this char
          CFStringRef str = CFStringCreateWithCharactersNoCopy(NULL, &uni, 1, kCFAllocatorNull);
          // find a font that contains it
          font2 = CTFontCreateForString(font2, str, CFRangeMake(0,1));
          must_release = true;
          CFRelease(str);
          b = CTFontGetGlyphsForCharacters(font2, &uni, &glyph, 1);
        }
	if (b) CTFontGetAdvancesForGlyphs(font2, kCTFontHorizontalOrientation, &glyph, &advance_size, 1);
	else advance_size.width = 0.;
	// the width of the 'uni' character
	wdt = fontsize->width[r][uni & (block-1)] = advance_size.width;
	if (must_release) CFRelease(font2);
      }
      retval += wdt;
    }
    return retval;
  } else {
#endif
#if ! __LP64__
    OSStatus err;
    Fixed bBefore, bAfter, bAscent, bDescent;
    ATSUTextLayout layout;
    ByteCount iSize;
    ATSUAttributeTag iTag;
    ATSUAttributeValuePtr iValuePtr;
    
    // Here's my ATSU text measuring attempt... This seems to do the Right Thing
    // now collect our ATSU resources and measure our text string
    layout = fontsize->layout;
    // activate the current GC
    iSize = sizeof(CGContextRef);
    iTag = kATSUCGContextTag;
    iValuePtr = &fl_gc;
    ATSUSetLayoutControls(layout, 1, &iTag, &iSize, &iValuePtr);
    // now measure the bounding box
    err = ATSUSetTextPointerLocation(layout, txt, kATSUFromTextBeginning, n, n);
    err = ATSUGetUnjustifiedBounds(layout, kATSUFromTextBeginning, n, &bBefore, &bAfter, &bAscent, &bDescent);
    // If err is OK then return length, else return 0. Or something...
    int len = FixedToInt(bAfter);
    return len;
#endif
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
  }
#endif
  return 0;
}

#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
static CGColorRef flcolortocgcolor(fltk3::Color i)
{
  uchar r, g, b;
  fltk3::get_color(i, r, g, b);
  CGFloat components[4] = {r/255.0f, g/255.0f, b/255.0f, 1.};
  static CGColorSpaceRef cspace = NULL;
  if (cspace == NULL) {
    cspace = CGColorSpaceCreateWithName(kCGColorSpaceGenericRGB);
  }
  return CGColorCreate(cspace, components);
}
#endif

static void fl_mac_draw(const char *str, int n, float x, float y, fltk3::GraphicsDriver *driver) {
  x += driver->origin_x(); y += driver->origin_y();
  // convert to UTF-16 first
  UniChar *uniStr = mac_Utf8_to_Utf16(str, n, &n);
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
  if (fl_mac_os_version >= 100500) {
    CFStringRef str16 = CFStringCreateWithCharactersNoCopy(NULL, uniStr, n,  kCFAllocatorNull);
    if (str16 == NULL) return; // shd not happen
    CGColorRef color = flcolortocgcolor(driver->color());
    CFDictionarySetValue (attributes, kCTFontAttributeName, driver->font_descriptor()->fontref);
    CFDictionarySetValue (attributes, kCTForegroundColorAttributeName, color);
    CFAttributedStringRef mastr = CFAttributedStringCreate(kCFAllocatorDefault, str16, attributes);
    CFRelease(str16);
    CFRelease(color);
    CTLineRef ctline = CTLineCreateWithAttributedString(mastr);
    CFRelease(mastr);
    CGContextSetTextMatrix(fl_gc, font_mx);
    CGContextSetTextPosition(fl_gc, x, y);
    CGContextSetShouldAntialias(fl_gc, true);
    CTLineDraw(ctline, fl_gc);
    CGContextSetShouldAntialias(fl_gc, false);
    CFRelease(ctline);
  } else {
#endif
#if ! __LP64__
    OSStatus err;
    // now collect our ATSU resources
    ATSUTextLayout layout = driver->font_descriptor()->layout;
    
    ByteCount iSize = sizeof(CGContextRef);
    ATSUAttributeTag iTag = kATSUCGContextTag;
    ATSUAttributeValuePtr iValuePtr=&fl_gc;
    ATSUSetLayoutControls(layout, 1, &iTag, &iSize, &iValuePtr);
    
    err = ATSUSetTextPointerLocation(layout, uniStr, kATSUFromTextBeginning, n, n);
    CGContextSetShouldAntialias(fl_gc, true);
    err = ATSUDrawText(layout, kATSUFromTextBeginning, n, FloatToFixed(x), FloatToFixed(y));
    CGContextSetShouldAntialias(fl_gc, false);
#endif
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
  }
#endif
}



double fltk3::QuartzGraphicsDriver::width(const char* txt, int n) {
  int wc_len = n;
  UniChar *uniStr = mac_Utf8_to_Utf16(txt, n, &wc_len);
  if (!font_descriptor()) font(fltk3::HELVETICA, fltk3::NORMAL_SIZE);
  return fl_mac_width(uniStr, wc_len, font_descriptor());
}


double fltk3::QuartzGraphicsDriver::width(unsigned int wc) {
  if (!font_descriptor()) font(fltk3::HELVETICA, fltk3::NORMAL_SIZE);
  
  UniChar utf16[3];
  int l = 1;
  if (wc <= 0xFFFF) {
    *utf16 = wc;
  }
  else {
    //    char buf[4];
    //    l = fltk3::utf8encode(wc, buf);
    //    l = (int)fltk3::utf8toUtf16(buf, l, utf16, 3);
    l = (int)fltk3::ucs_to_Utf16(wc, utf16, 3);
  }
  return fl_mac_width(utf16, l, font_descriptor());
}


// text extent calculation
void fltk3::QuartzGraphicsDriver::text_extents(const char *str8, int n, int &dx, int &dy, int &w, int &h) {
  if (!font_descriptor()) font(fltk3::HELVETICA, fltk3::NORMAL_SIZE);
  Fl_Font_Descriptor *fontsize = font_descriptor();
  UniChar *txt = mac_Utf8_to_Utf16(str8, n, &n);
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
  if (fl_mac_os_version >= 100500) {
    CFStringRef str16 = CFStringCreateWithCharactersNoCopy(NULL, txt, n,  kCFAllocatorNull);
    CFDictionarySetValue (attributes, kCTFontAttributeName, fontsize->fontref);
    CFAttributedStringRef mastr = CFAttributedStringCreate(kCFAllocatorDefault, str16, attributes);
    CFRelease(str16);
    CTLineRef ctline = CTLineCreateWithAttributedString(mastr);
    CFRelease(mastr);
    CGContextSetTextPosition(fl_gc, 0, 0);
    CGContextSetShouldAntialias(fl_gc, true);
    CGRect rect = CTLineGetImageBounds(ctline, fl_gc);
    CGContextSetShouldAntialias(fl_gc, false);
    CFRelease(ctline);
    dx = floor(rect.origin.x + 0.5);
    dy = floor(- rect.origin.y - rect.size.height + 0.5);
    w = rect.size.width + 0.5;
    h = rect.size.height + 0.5;
  }
  else {
#endif
#if ! __LP64__
    OSStatus err;
    ATSUTextLayout layout;
    ByteCount iSize;
    ATSUAttributeTag iTag;
    ATSUAttributeValuePtr iValuePtr;
    
    // Here's my ATSU text measuring attempt... This seems to do the Right Thing
    // now collect our ATSU resources and measure our text string
    layout = fontsize->layout;
    // activate the current GC
    iSize = sizeof(CGContextRef);
    iTag = kATSUCGContextTag;
    iValuePtr = &fl_gc;
    ATSUSetLayoutControls(layout, 1, &iTag, &iSize, &iValuePtr);
    // now measure the bounding box
    err = ATSUSetTextPointerLocation(layout, txt, kATSUFromTextBeginning, n, n);
    Rect bbox;
    err = ATSUMeasureTextImage(layout, kATSUFromTextBeginning, n, 0, 0, &bbox);
    w = bbox.right - bbox.left;
    h = bbox.bottom - bbox.top;
    dx = bbox.left;
    dy = -bbox.bottom;
    //printf("r: %d l: %d t: %d b: %d w: %d h: %d\n", bbox.right, bbox.left, bbox.top, bbox.bottom, w, h);
#endif
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_5
  }
#endif
  return;
} // fltk3::text_extents


void fltk3::QuartzGraphicsDriver::draw(const char *str, int n, float x, float y) {
  // avoid a crash if no font has been selected by user yet !
  if (!font_descriptor()) font(fltk3::HELVETICA, fltk3::NORMAL_SIZE);
  fl_mac_draw(str, n, x, y, this);
}


void fltk3::QuartzGraphicsDriver::draw(const char* str, int n, int x, int y) {
  // avoid a crash if no font has been selected by user yet !
  if (!font_descriptor()) font(fltk3::HELVETICA, fltk3::NORMAL_SIZE);
  fl_mac_draw(str, n, (float)x-0.0f, (float)y+0.5f, this);
}


void fltk3::QuartzGraphicsDriver::draw(int angle, const char *str, int n, int x, int y) {
  CGContextSaveGState(fl_gc);
  CGContextTranslateCTM(fl_gc, x+origin_x(), y+origin_y());
  CGContextRotateCTM(fl_gc, - angle*(M_PI/180) );
  CGContextTranslateCTM(fl_gc, -origin_x(), -origin_y());
  draw(str, n, 0, 0);
  CGContextRestoreGState(fl_gc);
}


void fltk3::QuartzGraphicsDriver::rtl_draw(const char* c, int n, int x, int y) {
  int dx, dy, w, h;
  text_extents(c, n, dx, dy, w, h);
  draw(c, n, x - w - dx, y);
}


void fltk3::QuartzGraphicsDriver::font(fltk3::Font fnum, fltk3::Fontsize size) {
  if (fnum==-1) {
    fltk3::GraphicsDriver::font(0, 0);
    return;
  }
  fltk3::GraphicsDriver::font(fnum, size);
  this->font_descriptor( find(fnum, size) );
}

void fltk3::QuartzGraphicsDriver::rect(int x, int y, int w, int h) {
  if (w<=0 || h<=0) return;
  x += origin_x(); y += origin_y();
  CGRect rect = CGRectMake(x, y, w-1, h-1);
  CGContextStrokeRect(fl_gc, rect);
}

void fltk3::QuartzGraphicsDriver::rectf(int x, int y, int w, int h) {
  if (w<=0 || h<=0) return;
  x += origin_x(); y += origin_y();
  CGRect rect = CGRectMake(x, y, w-0.9, h-0.9);
  CGContextFillRect(fl_gc, rect);
}

void fltk3::QuartzGraphicsDriver::xyline(int x, int y, int x1) {
  x += origin_x(); y += origin_y(); x1 += origin_x();
  CGContextMoveToPoint(fl_gc, x, y);
  CGContextAddLineToPoint(fl_gc, x1, y);
  CGContextStrokePath(fl_gc);
}

void fltk3::QuartzGraphicsDriver::xyline(int x, int y, int x1, int y2) {
  x += origin_x(); y += origin_y(); x1 += origin_x(); y2 += origin_y();
  CGContextMoveToPoint(fl_gc, x, y);
  CGContextAddLineToPoint(fl_gc, x1, y);
  CGContextAddLineToPoint(fl_gc, x1, y2);
  CGContextStrokePath(fl_gc);
}

void fltk3::QuartzGraphicsDriver::xyline(int x, int y, int x1, int y2, int x3) {
  x += origin_x(); y += origin_y(); x1 += origin_x(); y2 += origin_y(); x3 += origin_x();
  CGContextMoveToPoint(fl_gc, x, y);
  CGContextAddLineToPoint(fl_gc, x1, y);
  CGContextAddLineToPoint(fl_gc, x1, y2);
  CGContextAddLineToPoint(fl_gc, x3, y2);
  CGContextStrokePath(fl_gc);
}

void fltk3::QuartzGraphicsDriver::yxline(int x, int y, int y1) {
  x += origin_x(); y += origin_y(); y1 += origin_y();
  CGContextMoveToPoint(fl_gc, x, y);
  CGContextAddLineToPoint(fl_gc, x, y1);
  CGContextStrokePath(fl_gc);
}

void fltk3::QuartzGraphicsDriver::yxline(int x, int y, int y1, int x2) {
  x += origin_x(); y += origin_y(); y1 += origin_y(); x2 += origin_x();
  CGContextMoveToPoint(fl_gc, x, y);
  CGContextAddLineToPoint(fl_gc, x, y1);
  CGContextAddLineToPoint(fl_gc, x2, y1);
  CGContextStrokePath(fl_gc);
}

void fltk3::QuartzGraphicsDriver::line(int x, int y, int x1, int y1) {
  if (fl_quartz_line_width_ > 1.5f) CGContextSetShouldAntialias(fl_gc, true);
  x += origin_x(); y += origin_y(); x1 += origin_x(); y1 += origin_y();
  CGContextMoveToPoint(fl_gc, x, y);
  CGContextAddLineToPoint(fl_gc, x1, y1);
  CGContextStrokePath(fl_gc);
  if (fl_quartz_line_width_ > 1.5f) CGContextSetShouldAntialias(fl_gc, false);
}

void fltk3::QuartzGraphicsDriver::line(int x, int y, int x1, int y1, int x2, int y2) {
  if (fl_quartz_line_width_ > 1.5f) CGContextSetShouldAntialias(fl_gc, true);
  x += origin_x(); y += origin_y(); x1 += origin_x(); y1 += origin_y(); x2 += origin_x(); y2 += origin_y();
  CGContextMoveToPoint(fl_gc, x, y);
  CGContextAddLineToPoint(fl_gc, x1, y1);
  CGContextAddLineToPoint(fl_gc, x2, y2);
  CGContextStrokePath(fl_gc);
  if (fl_quartz_line_width_ > 1.5f) CGContextSetShouldAntialias(fl_gc, false);
}

void fltk3::QuartzGraphicsDriver::loop(int x, int y, int x1, int y1, int x2, int y2) {
  x += origin_x(); y += origin_y(); x1 += origin_x(); y1 += origin_y(); x2 += origin_x(); y2 += origin_y();
  CGContextSetShouldAntialias(fl_gc, true);
  CGContextMoveToPoint(fl_gc, x, y);
  CGContextAddLineToPoint(fl_gc, x1, y1);
  CGContextAddLineToPoint(fl_gc, x2, y2);
  CGContextClosePath(fl_gc);
  CGContextStrokePath(fl_gc);
  CGContextSetShouldAntialias(fl_gc, false);
}

void fltk3::QuartzGraphicsDriver::loop(int x, int y, int x1, int y1, int x2, int y2, int x3, int y3) {
  x += origin_x(); y += origin_y(); x1 += origin_x(); y1 += origin_y();
  x2 += origin_x(); y2 += origin_y(); x3 += origin_x(); y3 += origin_y();
  CGContextSetShouldAntialias(fl_gc, true);
  CGContextMoveToPoint(fl_gc, x, y);
  CGContextAddLineToPoint(fl_gc, x1, y1);
  CGContextAddLineToPoint(fl_gc, x2, y2);
  CGContextAddLineToPoint(fl_gc, x3, y3);
  CGContextClosePath(fl_gc);
  CGContextStrokePath(fl_gc);
  CGContextSetShouldAntialias(fl_gc, false);
}

void fltk3::QuartzGraphicsDriver::polygon(int x, int y, int x1, int y1, int x2, int y2) {
  x += origin_x(); y += origin_y(); x1 += origin_x(); y1 += origin_y(); x2 += origin_x(); y2 += origin_y();
  CGContextSetShouldAntialias(fl_gc, true);
  CGContextMoveToPoint(fl_gc, x, y);
  CGContextAddLineToPoint(fl_gc, x1, y1);
  CGContextAddLineToPoint(fl_gc, x2, y2);
  CGContextClosePath(fl_gc);
  CGContextFillPath(fl_gc);
  CGContextSetShouldAntialias(fl_gc, false);
}


void fltk3::QuartzGraphicsDriver::polygon(int x, int y, int x1, int y1, int x2, int y2, int x3, int y3) {
  x += origin_x(); y += origin_y(); x1 += origin_x(); y1 += origin_y();
  x2 += origin_x(); y2 += origin_y(); x3 += origin_x(); y3 += origin_y();
  CGContextSetShouldAntialias(fl_gc, true);
  CGContextMoveToPoint(fl_gc, x, y);
  CGContextAddLineToPoint(fl_gc, x1, y1);
  CGContextAddLineToPoint(fl_gc, x2, y2);
  CGContextAddLineToPoint(fl_gc, x3, y3);
  CGContextClosePath(fl_gc);
  CGContextFillPath(fl_gc);
  CGContextSetShouldAntialias(fl_gc, false);
}

void fltk3::QuartzGraphicsDriver::point(int x, int y) {
  x += origin_x(); y += origin_y();
  CGContextFillRect(fl_gc, CGRectMake(x - 0.5, y - 0.5, 1, 1) );
}

void fltk3::QuartzGraphicsDriver::restore_clip() {
  fl_clip_state_number++;
  fltk3::Region r = clip_region();
  if ( fl_window || fl_gc) { // clipping for a true window or for an offscreen drawing world (CGBitmap)
    Fl_X::q_clear_clipping();
    Fl_X::q_fill_context();//flip coords if bitmap context
                           //apply program clip
    if (r) {
      CGContextClipToRects(fl_gc, r->rects, r->count);
    }
  }
}

void fltk3::QuartzGraphicsDriver::push_clip(int x, int y, int w, int h) {
  x += origin_x(); y += origin_y();
  fltk3::Region r;
  if (w > 0 && h > 0) {
    r = XRectangleRegion(x,y,w,h);
    fltk3::Region current = clip_region();
    if (current) {
      XDestroyRegion(r);
      r = Fl_X::intersect_region_and_rect(current, x,y,w,h);
    }
  } else { // make empty clip region:
    r = XRectangleRegion(0,0,0,0);
  }
  region_stack_push(r);
  restore_clip();
}

int fltk3::QuartzGraphicsDriver::not_clipped(int x, int y, int w, int h) {
  x += origin_x(); y += origin_y();
  if (x+w <= 0 || y+h <= 0) return 0;
  fltk3::Region r = clip_region();
  if (!r) return 1;
  CGRect arg = fl_cgrectmake_cocoa(x, y, w, h);
  for (int i = 0; i < r->count; i++) {
    CGRect test = CGRectIntersection(r->rects[i], arg);
    if (!CGRectIsEmpty(test)) return 1;
  }
  return 0;
}

int fltk3::QuartzGraphicsDriver::clip_box(int x, int y, int w, int h, int& X, int& Y, int& W, int& H){
  int ret;
  x += origin_x(); y += origin_y();
  X = x; Y = y; W = w; H = h;
  fltk3::Region r = clip_region();
  if (!r) {
    ret = 0;
  } else {
    CGRect arg = fl_cgrectmake_cocoa(x, y, w, h);
    CGRect u = CGRectMake(0,0,0,0);
    CGRect test;
    for(int i = 0; i < r->count; i++) {
      test = CGRectIntersection(r->rects[i], arg);
      if( ! CGRectIsEmpty(test) ) {
        if(CGRectIsEmpty(u)) u = test;
        else u = CGRectUnion(u, test);
      }
    }
    X = int(u.origin.x);
    Y = int(u.origin.y);
    W = int(u.size.width + 1);
    H = int(u.size.height + 1);
    if(CGRectIsEmpty(u)) W = H = 0;
    ret = ! CGRectEqualToRect(arg, u);
  }
  X -= origin_x(); Y -= origin_y();
  return ret;
}

void fltk3::QuartzGraphicsDriver::yxline(int x, int y, int y1, int x2, int y3) {
  x += origin_x(); y += origin_y(); y1 += origin_y(); x2 += origin_x(); y3 += origin_y();
  CGContextMoveToPoint(fl_gc, x, y);
  CGContextAddLineToPoint(fl_gc, x, y1);
  CGContextAddLineToPoint(fl_gc, x2, y1);
  CGContextAddLineToPoint(fl_gc, x2, y3);
  CGContextStrokePath(fl_gc);
}




void fltk3::PrinterQuartzGraphicsDriver::line_style(int style, int width, char* dashes) {
  QuartzGraphicsDriver::line_style(style, width, dashes);
  if ( style == fltk3::SOLID && dashes == NULL ) {  // when printing kCGLineCapSquare seems better for solid lines
    fl_quartz_line_cap_ = kCGLineCapSquare;
    CGContextSetLineCap(fl_gc, fl_quartz_line_cap_);
  }
}

void fltk3::PrinterQuartzGraphicsDriver::rect(int x, int y, int w, int h) {
  if (fl_quartz_line_width_ > 1.5f) CGContextSetShouldAntialias(fl_gc, true);
  QuartzGraphicsDriver::rect(x, y, w, h);
  if (fl_quartz_line_width_ > 1.5f) CGContextSetShouldAntialias(fl_gc, false);
}

void fltk3::PrinterQuartzGraphicsDriver::xyline(int x, int y, int x1) {
  if (fl_quartz_line_width_ > 1.5f) CGContextSetShouldAntialias(fl_gc, true);
  QuartzGraphicsDriver::xyline(x, y, x1);
  if (fl_quartz_line_width_ > 1.5f) CGContextSetShouldAntialias(fl_gc, false);
}

void fltk3::PrinterQuartzGraphicsDriver::xyline(int x, int y, int x1, int y2) {
  if (fl_quartz_line_width_ > 1.5f) CGContextSetShouldAntialias(fl_gc, true);
  QuartzGraphicsDriver::xyline(x, y, x1, y2);
  if (fl_quartz_line_width_ > 1.5f) CGContextSetShouldAntialias(fl_gc, false);
}

void fltk3::PrinterQuartzGraphicsDriver::xyline(int x, int y, int x1, int y2, int x3) {
  if (fl_quartz_line_width_ > 1.5f) CGContextSetShouldAntialias(fl_gc, true);
  QuartzGraphicsDriver::xyline(x, y, x1, y2, x3);
  if (fl_quartz_line_width_ > 1.5f) CGContextSetShouldAntialias(fl_gc, false);
}

void fltk3::PrinterQuartzGraphicsDriver::yxline(int x, int y, int y1) {
  if (fl_quartz_line_width_ > 1.5f) CGContextSetShouldAntialias(fl_gc, true);
  QuartzGraphicsDriver::yxline(x, y, y1);
  if (fl_quartz_line_width_ > 1.5f) CGContextSetShouldAntialias(fl_gc, false);
}

void fltk3::PrinterQuartzGraphicsDriver::yxline(int x, int y, int y1, int x2) {
  if (fl_quartz_line_width_ > 1.5f) CGContextSetShouldAntialias(fl_gc, true);
  QuartzGraphicsDriver::yxline(x, y, y1, x2);
  if (fl_quartz_line_width_ > 1.5f) CGContextSetShouldAntialias(fl_gc, false);
}

void fltk3::PrinterQuartzGraphicsDriver::yxline(int x, int y, int y1, int x2, int y3) {
  if (fl_quartz_line_width_ > 1.5f) CGContextSetShouldAntialias(fl_gc, true);
  QuartzGraphicsDriver::yxline(x, y, y1, x2, y3);
  if (fl_quartz_line_width_ > 1.5f) CGContextSetShouldAntialias(fl_gc, false);
}

#endif

//
// End of "$Id$".
//
