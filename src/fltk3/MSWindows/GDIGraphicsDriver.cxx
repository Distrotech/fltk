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

#ifdef WIN32

#include "GDIGraphicsDriver.h"

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
#include <fltk3/math.h>

#include "../flstring.h"
#include "../font.h"

extern int fl_line_width_;


extern int fltk3_start(fltk3::RGBImage *img,
                       int XP, int YP, int WP, int HP,
                       int w, int h, int &cx, int &cy,
                       int &X, int &Y, int &W, int &H);


// --- Bitmap support ---

typedef struct {
  HGDIOBJ id;
} BitmapData;

extern int fltk3_start(fltk3::Bitmap *bm,
                       int XP, int YP, int WP, int HP,
                       int w, int h, int &cx, int &cy,
                       int &X, int &Y, int &W, int &H);

void fltk3::GDIGraphicsDriver::allocateMyPlatformData(fltk3::Bitmap* bm)
{
  bm->pPlatformData[myIndex] = calloc(1, sizeof(BitmapData));
}

void fltk3::GDIGraphicsDriver::freeMyPlatformData(fltk3::Bitmap* bm)
{
  free(bm->pPlatformData[myIndex]);
}

void fltk3::GDIGraphicsDriver::uncache(fltk3::Bitmap* bm)
{
  if (!bm->pPlatformData) allocatePlatformData(bm);
  BitmapData *pd = (BitmapData*)bm->pPlatformData[myIndex];
  if (pd->id) {
    fl_delete_bitmask((fltk3::Offscreen)pd->id);
    pd->id = 0;
  }
}



// 'fl_create_bitmap()' - Create a 1-bit bitmap for drawing...
static fltk3::Bitmask fl_create_bitmap(int w, int h, const uchar *data) {
  // we need to pad the lines out to words & swap the bits
  // in each byte.
  int w1 = (w+7)/8;
  int w2 = ((w+15)/16)*2;
  uchar* newarray = new uchar[w2*h];
  const uchar* src = data;
  uchar* dest = newarray;
  fltk3::Bitmask bm;
  static uchar reverse[16] =	/* Bit reversal lookup table */
  { 0x00, 0x88, 0x44, 0xcc, 0x22, 0xaa, 0x66, 0xee,
    0x11, 0x99, 0x55, 0xdd, 0x33, 0xbb, 0x77, 0xff };
  
  for (int y=0; y < h; y++) {
    for (int n = 0; n < w1; n++, src++)
      *dest++ = (uchar)((reverse[*src & 0x0f] & 0xf0) |
	                (reverse[(*src >> 4) & 0x0f] & 0x0f));
    dest += w2-w1;
  }
  
  bm = CreateBitmap(w, h, 1, 1, newarray);
  
  delete[] newarray;
  
  return bm;
}

// 'fl_create_bitmask()' - Create an N-bit bitmap for masking...
fltk3::Bitmask fl_create_bitmask(int w, int h, const uchar *data) {
  // this won't work when the user changes display mode during run or
  // has two screens with differnet depths
  fltk3::Bitmask bm;
  static uchar hiNibble[16] =
  { 0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0,
    0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0 };
  static uchar loNibble[16] =
  { 0x00, 0x08, 0x04, 0x0c, 0x02, 0x0a, 0x06, 0x0e,
    0x01, 0x09, 0x05, 0x0d, 0x03, 0x0b, 0x07, 0x0f };
  int np  = GetDeviceCaps(fl_gc, PLANES);	//: was always one on sample machines
  int bpp = GetDeviceCaps(fl_gc, BITSPIXEL);//: 1,4,8,16,24,32 and more odd stuff?
  int Bpr = (bpp*w+7)/8;			//: bytes per row
  int pad = Bpr&1, w1 = (w+7)/8, shr = ((w-1)&7)+1;
  if (bpp==4) shr = (shr+1)/2;
  uchar *newarray = new uchar[(Bpr+pad)*h];
  uchar *dst = newarray;
  const uchar *src = data;
  
  for (int i=0; i<h; i++) {
    // This is slooow, but we do it only once per pixmap
    for (int j=w1; j>0; j--) {
      uchar b = *src++;
      if (bpp==1) {
        *dst++ = (uchar)( hiNibble[b&15] ) | ( loNibble[(b>>4)&15] );
      } else if (bpp==4) {
        for (int k=(j==1)?shr:4; k>0; k--) {
          *dst++ = (uchar)("\377\360\017\000"[b&3]);
          b = b >> 2;
        }
      } else {
        for (int k=(j==1)?shr:8; k>0; k--) {
          if (b&1) {
            *dst++=0;
	    if (bpp>8) *dst++=0;
            if (bpp>16) *dst++=0;
	    if (bpp>24) *dst++=0;
	  } else {
	    *dst++=0xff;
	    if (bpp>8) *dst++=0xff;
	    if (bpp>16) *dst++=0xff;
	    if (bpp>24) *dst++=0xff;
	  }
          
	  b = b >> 1;
        }
      }
    }
    
    dst += pad;
  }
  
  bm = CreateBitmap(w, h, np, bpp, newarray);
  delete[] newarray;
  
  return bm;
}


void fl_delete_bitmask(fltk3::Bitmask bm) {
  DeleteObject((HGDIOBJ)bm);
}

void fltk3::GDIGraphicsDriver::arc(int x,int y,int w,int h,double a1,double a2) {
  if (w <= 0 || h <= 0) return;
  x += origin_x(); y += origin_y();
  int xa = x+w/2+int(w*cos(a1/180.0*M_PI));
  int ya = y+h/2-int(h*sin(a1/180.0*M_PI));
  int xb = x+w/2+int(w*cos(a2/180.0*M_PI));
  int yb = y+h/2-int(h*sin(a2/180.0*M_PI));
  if (fabs(a1 - a2) < 90) {
    if (xa == xb && ya == yb) SetPixel(fl_gc, xa, ya, fl_RGB());
    else Arc(fl_gc, x, y, x+w, y+h, xa, ya, xb, yb);
  } else Arc(fl_gc, x, y, x+w, y+h, xa, ya, xb, yb);
}

void fltk3::GDIGraphicsDriver::pie(int x,int y,int w,int h,double a1,double a2) {
  if (w <= 0 || h <= 0) return;
  x += origin_x(); y += origin_y();
  if (a1 == a2) return;
  int xa = x+w/2+int(w*cos(a1/180.0*M_PI));
  int ya = y+h/2-int(h*sin(a1/180.0*M_PI));
  int xb = x+w/2+int(w*cos(a2/180.0*M_PI));
  int yb = y+h/2-int(h*sin(a2/180.0*M_PI));
  SelectObject(fl_gc, fl_brush());
  if (fabs(a1 - a2) < 90) {
    if (xa == xb && ya == yb) {
      MoveToEx(fl_gc, x+w/2, y+h/2, 0L);
      LineTo(fl_gc, xa, ya);
      SetPixel(fl_gc, xa, ya, fl_RGB());
    } else Pie(fl_gc, x, y, x+w, y+h, xa, ya, xb, yb);
  } else Pie(fl_gc, x, y, x+w, y+h, xa, ya, xb, yb);
}


// implements fltk3::GDIGraphicsDriver::draw(fltk3::Bitmap*,...) with an extra parameter
// to distinguish betwen display and printer
void fltk3::GDIGraphicsDriver::draw_bitmap(fltk3::Bitmap *bm, int XP, int YP, int WP, int HP, int cx, int cy,
					   int to_display) {
  int X, Y, W, H;
  if (!bm->array) {
    bm->draw_empty(XP, YP);
    return;
  }
  if (fltk3_start(bm, XP, YP, WP, HP, bm->w(), bm->h(), cx, cy, X, Y, W, H)) {
    return;
  }
  if (!bm->pPlatformData) allocatePlatformData(bm);
  BitmapData *pd = (BitmapData*)bm->pPlatformData[myIndex];
  if (!pd->id) pd->id = fl_create_bitmap(bm->w(), bm->h(), bm->array);
  
  typedef BOOL (WINAPI* fl_transp_func)  (HDC,int,int,int,int,HDC,int,int,int,int,UINT);
  static fl_transp_func fl_TransparentBlt;
  HDC tempdc;
  int save;
  BOOL use_print_algo = false;
  if (!to_display) {
    static HMODULE hMod = NULL;
    if (!hMod) {
      hMod = LoadLibrary("MSIMG32.DLL");
      if (hMod) fl_TransparentBlt = (fl_transp_func)GetProcAddress(hMod, "TransparentBlt");
    }
    if (fl_TransparentBlt) use_print_algo = true;
  }
  if (use_print_algo) { // algorithm for bitmap output to printer
    fltk3::Color save_c = fltk3::color(); // save bitmap's desired color
    uchar r, g, b;
    fltk3::get_color(save_c, r, g, b);
    r = 255-r;
    g = 255-g;
    b = 255-b;
    fltk3::Color background = fltk3::rgb_color(r, g, b); // a color very different from the bitmap's
    fltk3::Offscreen tmp_id = fl_create_offscreen(W, H);
    fl_begin_offscreen(tmp_id);
    fltk3::color(background);
    fltk3::rectf(0,0,W,H); // use this color as offscreen background
    fltk3::color(save_c); // back to bitmap's color
    tempdc = CreateCompatibleDC(fl_gc);
    save = SaveDC(tempdc);
    SelectObject(tempdc, pd->id);
    SelectObject(fl_gc, fl_brush()); // use bitmap's desired color
    BitBlt(fl_gc, 0, 0, W, H, tempdc, 0, 0, 0xE20746L); // draw bitmap to offscreen
    fl_end_offscreen(); // offscreen data is in tmp_id
    SelectObject(tempdc, (HGDIOBJ)tmp_id); // use offscreen data
                                           // draw it to printer context with background color as transparent
    fl_TransparentBlt(fl_gc, X+origin_x(),Y+origin_y(),W,H, tempdc, cx, cy, bm->w(), bm->h(), RGB(r, g, b) );
    fl_delete_offscreen(tmp_id);
  }
  else { // algorithm for bitmap output to display
    tempdc = CreateCompatibleDC(fl_gc);
    save = SaveDC(tempdc);
    SelectObject(tempdc, pd->id);
    SelectObject(fl_gc, fl_brush());
    // secret bitblt code found in old MSWindows reference manual:
    BitBlt(fl_gc, X+origin_x(), Y+origin_y(), W, H, tempdc, cx, cy, 0xE20746L);
  }
  RestoreDC(tempdc, save);
  DeleteDC(tempdc);
}  


// Code used to switch output to an off-screen window.  See macros in
// win32.h which save the old state in local variables.

typedef struct { BYTE a; BYTE b; BYTE c; BYTE d; } FL_BLENDFUNCTION;
typedef BOOL (WINAPI* fl_alpha_blend_func)
(HDC,int,int,int,int,HDC,int,int,int,int,FL_BLENDFUNCTION);
static fl_alpha_blend_func fl_alpha_blend = NULL;
static FL_BLENDFUNCTION blendfunc = { 0, 0, 255, 1};

/*
 * This function checks if the version of MSWindows that we
 * curently run on supports alpha blending for bitmap transfers
 * and finds the required function if so.
 */
char fltk3::GDIGraphicsDriver::can_do_alpha_blending() {
  static char been_here = 0;
  static char can_do = 0;
  // do this test only once
  if (been_here) return can_do;
  been_here = 1;
  // load the library that implements alpha blending
  HMODULE hMod = LoadLibrary("MSIMG32.DLL");
  // give up if that doesn't exist (Win95?)
  if (!hMod) return 0;
  // now find the blending function inside that dll
  fl_alpha_blend = (fl_alpha_blend_func)GetProcAddress(hMod, "AlphaBlend");
  // give up if we can't find it (Win95)
  if (!fl_alpha_blend) return 0;
  // we have the call, but does our display support alpha blending?
  // get the desktop's device context
  HDC dc = GetDC(0L);
  if (!dc) return 0;
  // check the device capabilities flags. However GetDeviceCaps
  // does not return anything useful, so we have to do it manually:
  
  HBITMAP bm = CreateCompatibleBitmap(dc, 1, 1);
  HDC new_gc = CreateCompatibleDC(dc);
  int save = SaveDC(new_gc);
  SelectObject(new_gc, bm);
  /*COLORREF set = */ SetPixel(new_gc, 0, 0, 0x01010101);
  BOOL alpha_ok = fl_alpha_blend(dc, 0, 0, 1, 1, new_gc, 0, 0, 1, 1, blendfunc);
  RestoreDC(new_gc, save);
  DeleteDC(new_gc);
  DeleteObject(bm);
  ReleaseDC(0L, dc);
  
  if (alpha_ok) can_do = 1;
  return can_do;
}

HDC fl_makeDC(HBITMAP bitmap) {
  HDC new_gc = CreateCompatibleDC(fl_gc);
  SetTextAlign(new_gc, TA_BASELINE|TA_LEFT);
  SetBkMode(new_gc, TRANSPARENT);
#if USE_COLORMAP
  if (fl_palette) SelectPalette(new_gc, fl_palette, FALSE);
#endif
  SelectObject(new_gc, bitmap);
  return new_gc;
}

void fltk3::GDIGraphicsDriver::copy_offscreen(int x,int y,int w,int h,HBITMAP bitmap,int srcx,int srcy) {
  HDC new_gc = CreateCompatibleDC(fl_gc);
  int save = SaveDC(new_gc);
  SelectObject(new_gc, bitmap);
  BitBlt(fl_gc, x+origin_x(), y+origin_y(), w, h, new_gc, srcx, srcy, SRCCOPY);
  RestoreDC(new_gc, save);
  DeleteDC(new_gc);
}

void fltk3::GDIGraphicsDriver::copy_offscreen_with_alpha(int x,int y,int w,int h,HBITMAP bitmap,int srcx,int srcy) {
  HDC new_gc = CreateCompatibleDC(fl_gc);
  int save = SaveDC(new_gc);
  SelectObject(new_gc, bitmap);
  can_do_alpha_blending(); // make sure this is run
  BOOL alpha_ok = 0;
  // first try to alpha blend
  // if to printer, always try alpha_blend
  if ( is_printer() || can_do_alpha_blending() ) {
    if (fl_alpha_blend) alpha_ok = fl_alpha_blend(fl_gc, x+origin_x(), y+origin_y(), w, h, new_gc, srcx, srcy, w, h, blendfunc);
  }
  // if that failed (it shouldn't), still copy the bitmap over, but now alpha is 1
  if (!alpha_ok) {
    BitBlt(fl_gc, x+origin_x(), y+origin_y(), w, h, new_gc, srcx, srcy, SRCCOPY);
  }
  RestoreDC(new_gc, save);
  DeleteDC(new_gc);
}

void fltk3::GDIGraphicsDriver::draw(fltk3::RGBImage *img, int XP, int YP, int WP, int HP, int cx, int cy) {
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
    img->id_ = fl_create_offscreen(img->w(), img->h());
    fltk3::push_origin(); fltk3::origin(0,0);
    if ((img->d() == 2 || img->d() == 4) && can_do_alpha_blending()) {
      fl_begin_offscreen((fltk3::Offscreen)img->id_);
      fltk3::draw_image(img->array, 0, 0, img->w(), img->h(), img->d()|fltk3::IMAGE_WITH_ALPHA, img->ld());
      fl_end_offscreen();
    } else {
      fl_begin_offscreen((fltk3::Offscreen)img->id_);
      fltk3::draw_image(img->array, 0, 0, img->w(), img->h(), img->d(), img->ld());
      fl_end_offscreen();
      if (img->d() == 2 || img->d() == 4) {
        img->mask_ = fl_create_alphamask(img->w(), img->h(), img->d(), img->ld(), img->array);
      }
    }
    fltk3::pop_origin();
  }
  if (img->mask_) {
    HDC new_gc = CreateCompatibleDC(fl_gc);
    int save = SaveDC(new_gc);
    SelectObject(new_gc, (void*)img->mask_);
    BitBlt(fl_gc, X+origin_x(), Y+origin_y(), W, H, new_gc, cx, cy, SRCAND);
    SelectObject(new_gc, (void*)img->id_);
    BitBlt(fl_gc, X+origin_x(), Y+origin_y(), W, H, new_gc, cx, cy, SRCPAINT);
    RestoreDC(new_gc,save);
    DeleteDC(new_gc);
  } else if (img->d()==2 || img->d()==4) {
    copy_offscreen_with_alpha(X, Y, W, H, (fltk3::Offscreen)img->id_, cx, cy);
  } else {
    copy_offscreen(X, Y, W, H, (fltk3::Offscreen)img->id_, cx, cy);
  }
}

void fltk3::GDIGraphicsDriver::line_style(int style, int width, char* dashes) {
  // save line width in global variable for X11 clipping
  if (width == 0) fl_line_width_ = 1;
  else fl_line_width_ = width>0 ? width : -width;
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
    fltk3::error("fltk3::line_style(): Could not create GDI pen object.");
    return;
  }
  HPEN oldpen = (HPEN)SelectObject(fl_gc, newpen);
  DeleteObject(oldpen);
  DeleteObject(fl_current_xmap->pen);
  fl_current_xmap->pen = newpen;
}

void fltk3::GDIGraphicsDriver::draw(fltk3::Pixmap *pxm, int XP, int YP, int WP, int HP, int cx, int cy) {
  int X, Y, W, H;
  if (pxm->prepare(XP, YP, WP, HP, cx, cy, X, Y, W, H)) return;
  if (pxm->mask_) {
    HDC new_gc = CreateCompatibleDC(fl_gc);
    int save = SaveDC(new_gc);
    SelectObject(new_gc, (void*)pxm->mask_);
    BitBlt(fl_gc, X+origin_x(), Y+origin_y(), W, H, new_gc, cx, cy, SRCAND);
    SelectObject(new_gc, (void*)pxm->id_);
    BitBlt(fl_gc, X+origin_x(), Y+origin_y(), W, H, new_gc, cx, cy, SRCPAINT);
    RestoreDC(new_gc,save);
    DeleteDC(new_gc);
  } else {
    copy_offscreen(X, Y, W, H, (fltk3::Offscreen)pxm->id_, cx, cy);
  }
}

void fltk3::GDIPrinterGraphicsDriver::draw(fltk3::Pixmap *pxm, int XP, int YP, int WP, int HP, int cx, int cy) {
  int X, Y, W, H;
  if (pxm->prepare(XP, YP, WP, HP, cx, cy, X, Y, W, H)) return;
  typedef BOOL (WINAPI* fl_transp_func)  (HDC,int,int,int,int,HDC,int,int,int,int,UINT);
  static HMODULE hMod = NULL;
  static fl_transp_func fl_TransparentBlt = NULL;
  if (!hMod) {
    hMod = LoadLibrary("MSIMG32.DLL");
    if(hMod) fl_TransparentBlt = (fl_transp_func)GetProcAddress(hMod, "TransparentBlt");
  }
  if (fl_TransparentBlt) {
    HDC new_gc = CreateCompatibleDC(fl_gc);
    int save = SaveDC(new_gc);
    SelectObject(new_gc, (void*)pxm->id_);
    // print all of offscreen but its parts in background color
    fl_TransparentBlt(fl_gc, X+origin_x(), Y+origin_y(), W, H, new_gc, cx, cy, pxm->w(), pxm->h(), pxm->pixmap_bg_color );
    RestoreDC(new_gc,save);
    DeleteDC(new_gc);
  }
  else {
    copy_offscreen(X, Y, W, H, (fltk3::Offscreen)pxm->id_, cx, cy);
  }
}

void fltk3::GDIGraphicsDriver::rect(int x, int y, int w, int h) {
  if (w<=0 || h<=0) return;
  x += origin_x(); y += origin_y();
  MoveToEx(fl_gc, x, y, 0L);
  LineTo(fl_gc, x+w-1, y);
  LineTo(fl_gc, x+w-1, y+h-1);
  LineTo(fl_gc, x, y+h-1);
  LineTo(fl_gc, x, y);
}

void fltk3::GDIGraphicsDriver::rectf(int x, int y, int w, int h) {
  if (w<=0 || h<=0) return;
  x += origin_x(); y += origin_y();
  RECT rect;
  rect.left = x; rect.top = y;
  rect.right = x + w; rect.bottom = y + h;
  FillRect(fl_gc, &rect, fl_brush());
}


void fltk3::GDIGraphicsDriver::xyline(int x, int y, int x1) {
  x += origin_x(); y += origin_y(); x1 += origin_x();
  MoveToEx(fl_gc, x, y, 0L); LineTo(fl_gc, x1+1, y);
}

void fltk3::GDIGraphicsDriver::xyline(int x, int y, int x1, int y2) {
  x += origin_x(); y += origin_y(); x1 += origin_x(); y2 += origin_y();
  if (y2 < y) y2--;
  else y2++;
  MoveToEx(fl_gc, x, y, 0L);
  LineTo(fl_gc, x1, y);
  LineTo(fl_gc, x1, y2);
}

void fltk3::GDIGraphicsDriver::xyline(int x, int y, int x1, int y2, int x3) {
  x += origin_x(); y += origin_y(); x1 += origin_x(); y2 += origin_y(); x3 += origin_x();
  if(x3 < x1) x3--;
  else x3++;
  MoveToEx(fl_gc, x, y, 0L);
  LineTo(fl_gc, x1, y);
  LineTo(fl_gc, x1, y2);
  LineTo(fl_gc, x3, y2);
}

void fltk3::GDIGraphicsDriver::yxline(int x, int y, int y1) {
  x += origin_x(); y += origin_y(); y1 += origin_y();
  if (y1 < y) y1--;
  else y1++;
  MoveToEx(fl_gc, x, y, 0L); LineTo(fl_gc, x, y1);
}


void fltk3::GDIGraphicsDriver::yxline(int x, int y, int y1, int x2) {
  x += origin_x(); y += origin_y(); y1 += origin_y(); x2 += origin_x();
  if (x2 > x) x2++;
  else x2--;
  MoveToEx(fl_gc, x, y, 0L);
  LineTo(fl_gc, x, y1);
  LineTo(fl_gc, x2, y1);
}

void fltk3::GDIGraphicsDriver::yxline(int x, int y, int y1, int x2, int y3) {
  x += origin_x(); y += origin_y(); y1 += origin_y(); x2 += origin_x(); y3 += origin_y();
  if(y3<y1) y3--;
  else y3++;
  MoveToEx(fl_gc, x, y, 0L);
  LineTo(fl_gc, x, y1);
  LineTo(fl_gc, x2, y1);
  LineTo(fl_gc, x2, y3);
}


void fltk3::GDIGraphicsDriver::line(int x, int y, int x1, int y1) {
  x += origin_x(); y += origin_y(); x1 += origin_x(); y1 += origin_y();
  MoveToEx(fl_gc, x, y, 0L);
  LineTo(fl_gc, x1, y1);
  // Draw the last point *again* because the GDI line drawing
  // functions will not draw the last point ("it's a feature!"...)
  SetPixel(fl_gc, x1, y1, fl_RGB());
}


void fltk3::GDIGraphicsDriver::line(int x, int y, int x1, int y1, int x2, int y2) {
  x += origin_x(); y += origin_y(); x1 += origin_x(); y1 += origin_y(); x2 += origin_x(); y2 += origin_y();
  MoveToEx(fl_gc, x, y, 0L);
  LineTo(fl_gc, x1, y1);
  LineTo(fl_gc, x2, y2);
  // Draw the last point *again* because the GDI line drawing
  // functions will not draw the last point ("it's a feature!"...)
  SetPixel(fl_gc, x2, y2, fl_RGB());
}


void fltk3::GDIGraphicsDriver::loop(int x, int y, int x1, int y1, int x2, int y2) {
  x += origin_x(); y += origin_y(); x1 += origin_x(); y1 += origin_y(); x2 += origin_x(); y2 += origin_y();
  MoveToEx(fl_gc, x, y, 0L);
  LineTo(fl_gc, x1, y1);
  LineTo(fl_gc, x2, y2);
  LineTo(fl_gc, x, y);
}


void fltk3::GDIGraphicsDriver::loop(int x, int y, int x1, int y1, int x2, int y2, int x3, int y3) {
  x += origin_x(); y += origin_y(); x1 += origin_x(); y1 += origin_y();
  x2 += origin_x(); y2 += origin_y(); x3 += origin_x(); y3 += origin_y();
  MoveToEx(fl_gc, x, y, 0L);
  LineTo(fl_gc, x1, y1);
  LineTo(fl_gc, x2, y2);
  LineTo(fl_gc, x3, y3);
  LineTo(fl_gc, x, y);
}


void fltk3::GDIGraphicsDriver::polygon(int x, int y, int x1, int y1, int x2, int y2) {
  x += origin_x(); y += origin_y(); x1 += origin_x(); y1 += origin_y(); x2 += origin_x(); y2 += origin_y();
  XPoint p[3];
  p[0].x = x;  p[0].y = y;
  p[1].x = x1; p[1].y = y1;
  p[2].x = x2; p[2].y = y2;
  SelectObject(fl_gc, fl_brush());
  Polygon(fl_gc, p, 3);
}

void fltk3::GDIGraphicsDriver::polygon(int x, int y, int x1, int y1, int x2, int y2, int x3, int y3) {
  x += origin_x(); y += origin_y(); x1 += origin_x(); y1 += origin_y();
  x2 += origin_x(); y2 += origin_y(); x3 += origin_x(); y3 += origin_y();
  XPoint p[4];
  p[0].x = x;  p[0].y = y;
  p[1].x = x1; p[1].y = y1;
  p[2].x = x2; p[2].y = y2;
  p[3].x = x3; p[3].y = y3;
  SelectObject(fl_gc, fl_brush());
  Polygon(fl_gc, p, 4);
}

void fltk3::GDIGraphicsDriver::restore_clip() {
  fl_clip_state_number++;
  fltk3::Region r = clip_region();
  SelectClipRgn(fl_gc, r); //if r is NULL, clip is automatically cleared
}

void fltk3::GDIGraphicsDriver::push_clip(int x, int y, int w, int h) {
  x += origin_x(); y += origin_y();
  fltk3::Region r;
  if (w > 0 && h > 0) {
    r = XRectangleRegion(x,y,w,h);
    fltk3::Region current = clip_region();
    if (current) {
      CombineRgn(r,r,current,RGN_AND);
    }
  } else { // make empty clip region:
    r = CreateRectRgn(0,0,0,0);
  }
  region_stack_push(r);
  restore_clip();
}

int fltk3::GDIGraphicsDriver::not_clipped(int x, int y, int w, int h) {
  x += origin_x(); y += origin_y();
  if (x+w <= 0 || y+h <= 0) return 0;
  fltk3::Region r = clip_region();
  if (!r) return 1;
  RECT rect;
  if (is_printer()) { // in case of print context, convert coords from logical to device
    POINT pt[2] = { {x, y}, {x + w, y + h} };
    LPtoDP(fl_gc, pt, 2);
    rect.left = pt[0].x; rect.top = pt[0].y; rect.right = pt[1].x; rect.bottom = pt[1].y;
  } else {
    rect.left = x; rect.top = y; rect.right = x+w; rect.bottom = y+h;
  }
  return RectInRegion(r,&rect);
}


int fltk3::GDIGraphicsDriver::clip_box(int x, int y, int w, int h, int& X, int& Y, int& W, int& H){
  X = x; Y = y; W = w; H = h;
  fltk3::Region r = clip_region();
  if (!r) return 0;
  x += origin_x(); y += origin_y();
  X = x; Y = y;
  // The win32 API makes no distinction between partial and complete
  // intersection, so we have to check for partial intersection ourselves.
  // However, given that the regions may be composite, we have to do
  // some voodoo stuff...
  fltk3::Region rr = XRectangleRegion(x,y,w,h);
  fltk3::Region temp = CreateRectRgn(0,0,0,0);
  int ret;
  if (CombineRgn(temp, rr, r, RGN_AND) == NULLREGION) { // disjoint
    W = H = 0;
    ret = 2;
  } else if (EqualRgn(temp, rr)) { // complete
    ret = 0;
  } else {	// partial intersection
    RECT rect;
    GetRgnBox(temp, &rect);
    if (is_printer()) { // if print context, convert coords from device to logical
      POINT pt[2] = { {rect.left, rect.top}, {rect.right, rect.bottom} };
      DPtoLP(fl_gc, pt, 2);
      X = pt[0].x; Y = pt[0].y; W = pt[1].x - X; H = pt[1].y - Y;
    }
    else {
      X = rect.left; Y = rect.top; W = rect.right - X; H = rect.bottom - Y;
    }
    ret = 1;
  }
  DeleteObject(temp);
  DeleteObject(rr);
  X -= origin_x(); Y -= origin_y();
  return ret;
}


void fltk3::GDIGraphicsDriver::point(int x, int y) {
  x += origin_x(); y += origin_y();
  SetPixel(fl_gc, x, y, fl_RGB());
}


void fltk3::GDIGraphicsDriver::end_points() {
  int n = vertex_no();
  XPOINT *p = vertices();
  for (int i=0; i<n; i++) SetPixel(fl_gc, p[i].x, p[i].y, fl_RGB());
}


void fltk3::GDIGraphicsDriver::end_line() {
  int n = vertex_no();
  XPOINT *p = vertices();
  if (n < 2) {
    end_points();
    return;
  }
  if (n>1) Polyline(fl_gc, p, n);
}


void fltk3::GDIGraphicsDriver::end_polygon() {
  fixloop();
  int n = vertex_no();
  XPOINT *p = vertices();
  if (n < 3) {
    end_line();
    return;
  }
  if (n>2) {
    SelectObject(fl_gc, fl_brush());
    Polygon(fl_gc, p, n);
  }
}

void fltk3::GDIGraphicsDriver::begin_complex_polygon() {
  GraphicsDriver::begin_complex_polygon();
  numcount = 0;
}


void fltk3::GDIGraphicsDriver::gap() {
  while (n>gap_+2 && p[n-1].x == p[gap_].x && p[n-1].y == p[gap_].y) n--;
  if (n > gap_+2) {
    transformed_vertex((COORD_T)p[gap_].x-origin_x(), (COORD_T)p[gap_].y-origin_y());
    counts[numcount++] = n-gap_;
    gap_ = n;
  } else {
    n = gap_;
  }
}

void fltk3::GDIGraphicsDriver::end_complex_polygon() {
  gap();
  int n = vertex_no();
  XPOINT *p = vertices();
  if (n < 3) {
    end_line();
    return;
  }
  if (n>2) {
    SelectObject(fl_gc, fl_brush());
    PolyPolygon(fl_gc, p, counts, numcount);
  }
}


void fltk3::GDIGraphicsDriver::circle(double x, double y, double r) {
  int llx, lly, w, h;
  double xt, yt;
  prepare_circle(x, y, r, llx, lly, w, h, xt, yt);
  if (vertex_kind()==POLYGON) {
    SelectObject(fl_gc, fl_brush());
    Pie(fl_gc, llx+origin_x(), lly+origin_y(), llx+origin_x()+w, lly+origin_y()+h, 0,0, 0,0);
  } else
    Arc(fl_gc, llx+origin_x(), lly+origin_y(), llx+origin_x()+w, lly+origin_y()+h, 0,0, 0,0);
}


#endif

//
// End of "$Id$".
//
