//
// "$Id: Fl_Double_Window.cxx 5679 2007-02-08 20:50:01Z mike $"
//
// Double-buffered window code for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2007 by Bill Spitzak and others.
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

#include <config.h>
//#include <FL/Fl.H>
#include <fltk/Window.h>
#include <FL/x.H>
//#include <FL/fl_draw.H>
#include <fltk/Offscreen.h>

// off-screen pixmaps: create, destroy, draw into, copy to window
using namespace fltk;

// Construction  / Destruction
Offscreen::Offscreen(GraphicData hgd): Surface() {
	must_cleanup_ = false;
}

#ifdef WIN32
extern HDC fltk::dc;

Offscreen::~Offscreen() {
	if (must_cleanup_ && this->graphic_data_) {
		DeleteObject(this->graphic_data_);
	}
}

void Offscreen::create() {
	graphic_data_ = CreateCompatibleBitmap(fltk::dc, dim_.w(), dim_.h());
	must_cleanup_ = true;
}


// Code used to switch output to an off-screen window.  See macros in
// win32.H which save the old state in local variables.

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
bool Offscreen::can_do_alpha_blending() {
	static bool been_here = false;
	static bool can_do = false;
	
	if (been_here) been_here = true; else return can_do;
	
	// load the library that implements alpha blending
	HMODULE hMod = LoadLibrary("MSIMG32.DLL");
	// give up if that doesn't exist (Win95?)
	if (!hMod) return false;
	// now find the blending function inside that dll
	fl_alpha_blend = (fl_alpha_blend_func)GetProcAddress(hMod, "AlphaBlend");
	// give up if we can't find it (Win95)
	if (!fl_alpha_blend) return false;
	// we have the  call, but does our display support alpha blending?
	HDC dc = 0L;//fltk::dc;
	// get the current or the desktop's device context
	if (!dc) dc = GetDC(0L);
	if (!dc) return false;
	// check the device capabilities flags. However GetDeviceCaps
	// does not return anything useful, so we have to do it manually:
	
	HBITMAP bm = CreateCompatibleBitmap(dc, 1, 1);
	HDC new_gc = CreateCompatibleDC(dc);
	int save = SaveDC(new_gc);
	SelectObject(new_gc, bm);
	COLORREF set = SetPixel(new_gc, 0, 0, 0x01010101);
	BOOL alpha_ok = fl_alpha_blend(dc, 0, 0, 1, 1, new_gc, 0, 0, 1, 1, blendfunc);
	RestoreDC(new_gc, save);
	DeleteDC(new_gc);
	DeleteObject(bm);
	
	if (!fltk::dc) ReleaseDC(0L, dc);
	if (alpha_ok) can_do = true;
	return can_do;
}

static HDC fl_makeDC(Offscreen::GraphicData  graphical_data) {
	HDC new_gc = CreateCompatibleDC(fltk::dc);
	SetTextAlign(new_gc, TA_BASELINE|TA_LEFT);
	SetBkMode(new_gc, TRANSPARENT);
	
	// do we need this in fltk 2 ? :
	//#if USE_COLORMAP
	//  if (fl_palette) SelectPalette(new_gc, fl_palette, FALSE);
	//#endif
	SelectObject(new_gc, graphical_data);
	return new_gc;
}


bool Offscreen::begin() {
	context_save_ = new GSave(); // push matrix, clip, save context handles (like dc)
	fltk::dc=fl_makeDC(graphic_data_); 
	num_saved_dc_ = SaveDC(fltk::dc); 
	return true;
}

bool Offscreen::end() {
	RestoreDC(fltk::dc, num_saved_dc_); 
	DeleteDC(fltk::dc); 
	
	delete context_save_; // restore prev dc, clip, matrix & context
	context_save_ = 0;
	
	return true;
}

bool Offscreen::copy(int x,int y,int w,int h,int srcx,int srcy) {
	if (!this->graphic_data_) return false;
	
	HDC new_gc = CreateCompatibleDC(fltk::dc);
	int save = SaveDC(new_gc);
	SelectObject(new_gc, (HBITMAP) this->graphic_data_);
	BitBlt(fltk::dc, x, y, w, h, new_gc, srcx, srcy, SRCCOPY);
	RestoreDC(new_gc, save);
	DeleteDC(new_gc);
	return true;
}

bool Offscreen::copy_with_alpha(int x, int y, int w, int h, int srcx, int srcy) {
	if (!this->graphic_data_) return false;
	
	HDC new_gc = CreateCompatibleDC(fltk::dc);
	int save = SaveDC(new_gc);
	SelectObject(new_gc, this->graphic_data_);
	BOOL alpha_ok = 0;
	// first try to alpha blend
	if (can_do_alpha_blending())
		alpha_ok = fl_alpha_blend(fltk::dc, x, y, w, h, new_gc, srcx, srcy, w, h, blendfunc);
	// if that failed (it shouldn,t), still copy the bitmap over, but now alpha is 1
	if (!alpha_ok)
		BitBlt(fltk::dc, x, y, w, h, new_gc, srcx, srcy, SRCCOPY);
	RestoreDC(new_gc, save);
	DeleteDC(new_gc);
	return true;
}
// end if defined(WIN32) =======================================================
#elif defined(__APPLE__) 
#if USE_QUARTZ
bool Offscreen::can_do_alpha_blending() {return true;}
// TODO: handle both copy / copy alpha here, should probably be factorized around a kCGImageXXXX parameter: 
void Offscreen::create () {
	int w = dim_.w(), h = dim_.h();
	void *data = calloc(w*h,4);
	CGColorSpaceRef lut = CGColorSpaceCreateDeviceRGB();
	graphic_data_ = CGBitmapContextCreate(
		data, w, h, 8, w*4, lut, kCGImageAlphaNoneSkipLast);
	CGColorSpaceRelease(lut);
	//return (GraphicData)graphic_data_;
}
// create (alpha)
#if 0
void Offscreen::create () {
	int w = dim_.w(), h = dim_.h();
	void *data = calloc(w*h,4);
	CGColorSpaceRef lut = CGColorSpaceCreateDeviceRGB();
	graphic_data_ = CGBitmapContextCreate(
		data, w, h, 8, w*4, lut, kCGImageAlphaPremultipliedLast);
	CGColorSpaceRelease(lut);
	//return (GraphicData)graphic_data_;
}
#endif

Offscreen::~Offscreen () {
  if (!graphic_data_) return;
  void *data = CGBitmapContextGetData(graphic_data_);
  CGContextRelease(graphic_data_);
  if (data) free(data);
}

bool Offscreen::begin() {
  if (!graphic_data_) return false;
  context_save_ = new GSave(); // push matrix, clip, save context handles
  int w = CGBitmapContextGetWidth(graphic_data_);
  int h = CGBitmapContextGetHeight(graphic_data_);
  draw_into(graphic_data_, w, h);
  return true;
}

bool Offscreen::end() {
  if (!graphic_data_) return false;
  stop_drawing(0);  
  delete context_save_; context_save_=0; // restore context
  return true;
}

// equivalent code may already exist in Image class: 
static void q_begin_image(CGRect &rect, int cx, int cy, int w, int h) {
  CGContextSaveGState(quartz_gc);
  CGAffineTransform mx = CGContextGetCTM(quartz_gc);
  CGRect r2 = rect;
  r2.origin.x -= 0.5f;
  r2.origin.y -= 0.5f;
  CGContextClipToRect(quartz_gc, r2);
  mx.d = -1.0; mx.tx = -mx.tx;
  CGContextConcatCTM(quartz_gc, mx);
  rect.origin.x = rect.origin.x - cx;
  rect.origin.y = (mx.ty+0.5f) - rect.origin.y - h + cy;
  rect.size.width = w;
  rect.size.height = h;
}
static void q_end_image() {
  CGContextRestoreGState(quartz_gc);
}

bool Offscreen::copy(int x,int y,int w,int h,int srcx,int srcy) {
  CGContextRef src = (CGContextRef) graphic_data_;
  void *data = CGBitmapContextGetData(src);
  int sw = CGBitmapContextGetWidth(src);
  int sh = CGBitmapContextGetHeight(src);
  CGImageAlphaInfo alpha = CGBitmapContextGetAlphaInfo(src);
  CGColorSpaceRef lut = CGColorSpaceCreateDeviceRGB();
  CGDataProviderRef src_bytes = CGDataProviderCreateWithData( 0L, data, sw*sh*4, 0L);
  CGImageRef img = CGImageCreate( sw, sh, 8, 4*8, 4*sw, lut, alpha,
					src_bytes, 0L, false, kCGRenderingIntentDefault);
  CGRect rect = { { x, y }, { w, h } };
  // fl_push_clip();
	
  q_begin_image(rect, srcx, srcy, sw, sh);
  CGContextDrawImage(quartz_gc, rect, img);
  q_end_image();
  
  CGImageRelease(img);
  CGColorSpaceRelease(lut);
  CGDataProviderRelease(src_bytes);
  return true;
}
// temporary for testing the lib, will be re-implemented:
bool Offscreen::copy_with_alpha(int x, int y, int w, int h, int srcx, int srcy) {
  return copy(x, y, w, h, srcx, srcy);
}

#else // QD
// TODO : finish the work for the optional QD impl.:
bool Offscreen::can_do_alpha_blending() {return false;}

void Offscreen::create() {
	GraphicData gw;
	Rect bounds;
	bounds.left=0; bounds.right=dim_.w(); bounds.top=0; bounds.bottom=dim_.h;
	QDErr err = NewGWorld(&gw, 0, &bounds, 0L, 0L, 0); // 'useTempMem' should not be used (says the Carbon port manual)
	if ( err == -108 )
    { }
	//    fl_message( "The application memory is low. Please increase the initial memory assignment.\n" ); 
	if (err!=noErr || gw==0L) return 0L;
}

bool Offscreen::copy(int x,int y,int w,int h, int srcx,int srcy) {
	Rect src;
	if ( !graphic_data_ ) return;
	src.top = srcy; src.left = srcx; src.bottom = srcy+h; src.right = srcx+w;
	Rect dst;
	GrafPtr dstPort; GetPort(&dstPort);
	dst.top = y; dst.left = x; dst.bottom = y+h; dst.right = x+w;
	RGBColor rgb, oldbg, oldfg;
	GetForeColor(&oldfg);
	GetBackColor(&oldbg);
	rgb.red = 0xffff; rgb.green = 0xffff; rgb.blue = 0xffff;
	RGBBackColor( &rgb );
	rgb.red = 0x0000; rgb.green = 0x0000; rgb.blue = 0x0000;
	RGBForeColor( &rgb );
	CopyBits(GetPortBitMapForCopyBits(graphic_data_), GetPortBitMapForCopyBits(dstPort), &src, &dst, srcCopy, 0L);
	RGBBackColor(&oldbg);
	RGBForeColor(&oldfg);
	return true;
}

static void fl_delete_offscreen(GraphicData graphic_data) {
	DisposeGWorld(graphic_data);
}

static GrafPtr prevPort;
static GDHandle prevGD;

bool Offscreen::begin() {
	context_save_ = new GSave(); // push matrix, clip, save context handles (like dc)
	GetGWorld( &prevPort, &prevGD );

	if ( graphic_data_)
	{
		SetGWorld( graphic_data_, 0 ); // sets the correct port
		PixMapHandle pm = GetGWorldPixMap(graphic_data_);
		Boolean ret = LockPixels(pm);
		if ( ret == false )
		{
			Rect rect;
			GetPortBounds( graphic_data_, &rect );
			UpdateGWorld( &graphic_data_, 0, &rect, 0, 0, 0 );
			pm = GetGWorldPixMap( graphic_data_ );
			LockPixels( pm );
		}
		fl_window = 0;
		return true;
	}
	return false;
}

bool Offscreen::end() {
	GraphicData currPort;
	GDHandle currGD;
	GetGWorld( &currPort, &currGD );
	PixMapHandle pm = GetGWorldPixMap(currPort);
	UnlockPixels(pm);
	
	delete this->context_save_;
	return true;
}
#endif
// end if defined(__APPLE__ && QD)  =======================================================
#else // X11
// maybe someone feels inclined to implement alpha blending on X11?
#endif

//
// End of "$Id"
//
