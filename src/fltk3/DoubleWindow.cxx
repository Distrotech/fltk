//
// "$Id$"
//
// Double-buffered window code for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2012 by Bill Spitzak and others.
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
#include <fltk3/run.h>
#include <fltk3/DoubleWindow.h>
#include <fltk3/Printer.h>
#include <fltk3/x.h>
#include <fltk3/draw.h>


// On systems that support double buffering "naturally" the base
// fltk3::Window class will probably do double-buffer and this subclass
// does nothing.

#if USE_XDBE

#include <X11/extensions/Xdbe.h>

static int use_xdbe;

static int can_xdbe() {
  static int tried;
  if (!tried) {
    tried = 1;
    int event_base, error_base;
    if (!XdbeQueryExtension(fl_display, &event_base, &error_base)) return 0;
    Drawable root = RootWindow(fl_display,fl_screen);
    int numscreens = 1;
    XdbeScreenVisualInfo *a = XdbeGetVisualInfo(fl_display,&root,&numscreens);
    if (!a) return 0;
    for (int j = 0; j < a->count; j++) {
      if (a->visinfo[j].visual == fl_visual->visualid
	  /*&& a->visinfo[j].perflevel > 0*/) {
        use_xdbe = 1; break;
      }
    }
    XdbeFreeVisualInfo(a);
  }
  return use_xdbe;
}
#endif


fltk3::DoubleWindow::DoubleWindow(int W, int H, const char *l) 
: fltk3::Window(W,H,l), 
  force_doublebuffering_(0) 
{
  type(DOUBLE_WINDOW); 
}


fltk3::DoubleWindow::DoubleWindow(int X, int Y, int W, int H, const char *l)
: fltk3::Window(X,Y,W,H,l), 
  force_doublebuffering_(0) 
{ 
  type(DOUBLE_WINDOW); 
}


void fltk3::DoubleWindow::show() {
  Window::show();
}

/** \addtogroup fl_drawings
 @{
 */
/** Copy a rectangular area of the given offscreen buffer into the current drawing destination.
 \param x,y	position where to draw the copied rectangle
 \param w,h	size of the copied rectangle
 \param pixmap  offscreen buffer containing the rectangle to copy
 \param srcx,srcy origin in offscreen buffer of rectangle to copy
 */
void fltk3::copy_offscreen(int x, int y, int w, int h, fltk3::Offscreen pixmap, int srcx, int srcy) {
  fltk3::graphics_driver->copy_offscreen(x, y, w, h, pixmap, srcx, srcy);
}
/** @} */

void fltk3::GraphicsDriver::copy_offscreen(int x, int y, int w, int h, fltk3::Offscreen pixmap, int srcx, int srcy) {
  fl_begin_offscreen(pixmap);
  uchar *img = fltk3::read_image(NULL, srcx, srcy, w, h, 0);
  fl_end_offscreen();
  fltk3::draw_image(img, x, y, w, h, 3, 0);
  delete[] img;
}

#if defined(USE_X11)

#elif defined(WIN32)

extern void fltk3::restore_clip();

#elif defined(__APPLE_QUARTZ__) || defined(FLTK3_DOXYGEN)

/** \addtogroup fl_drawings
 @{
 */

/** 
  Creation of an offscreen graphics buffer.
 \param w,h     width and height in pixels of the buffer.
 \return    the created graphics buffer.
 */
fltk3::Offscreen fl_create_offscreen(int w, int h) {
  void *data = calloc(w*h,4);
  CGColorSpaceRef lut = CGColorSpaceCreateDeviceRGB();
  CGContextRef ctx = CGBitmapContextCreate(
    data, w, h, 8, w*4, lut, kCGImageAlphaNoneSkipLast);
  CGColorSpaceRelease(lut);
  return (fltk3::Offscreen)ctx;
}

/**  Deletion of an offscreen graphics buffer.
 \param ctx     the buffer to be deleted.
 */
void fl_delete_offscreen(fltk3::Offscreen ctx) {
  if (!ctx) return;
  void *data = CGBitmapContextGetData((CGContextRef)ctx);
  CFIndex count = CFGetRetainCount(ctx);
  CGContextRelease((CGContextRef)ctx);
  if(count == 1) free(data);
}

const int stack_max = 16;
static int stack_ix = 0;
static CGContextRef stack_gc[stack_max];
static Window stack_window[stack_max];
static fltk3::SurfaceDevice *_ss;

/**  Send all subsequent drawing commands to this offscreen buffer.
 \param ctx     the offscreen buffer.
 */
void fl_begin_offscreen(fltk3::Offscreen ctx) {
  _ss = fltk3::SurfaceDevice::surface(); 
  fltk3::DisplayDevice::display_device()->set_current();
  if (stack_ix<stack_max) {
    stack_gc[stack_ix] = fl_gc;
    stack_window[stack_ix] = fl_window;
  } else 
    fprintf(stderr, "FLTK CGContext Stack overflow error\n");
  stack_ix++;

  fl_gc = (CGContextRef)ctx;
  fl_window = 0;
  CGContextSaveGState(fl_gc);
  fltk3::push_no_clip();
}

/** Quit sending drawing commands to the current offscreen buffer.
 */
void fl_end_offscreen() {
  Fl_X::q_release_context();
  fltk3::pop_clip();
  if (stack_ix>0)
    stack_ix--;
  else
    fprintf(stderr, "FLTK CGContext Stack underflow error\n");
  if (stack_ix<stack_max) {
    fl_gc = stack_gc[stack_ix];
    fl_window = stack_window[stack_ix];
  }
  _ss->set_current();
}

/** @} */

namespace fltk3 {
  extern void restore_clip();
}

#else
# error unsupported platform
#endif

/**
  Forces the window to be redrawn.
*/
void fltk3::DoubleWindow::flush() {flush(0);}

/**
  Forces the window to be redrawn.
  \param[in] eraseoverlay non-zero to erase overlay, zero to ignore

  fltk3::OverlayWindow relies on flush(1) copying the back buffer to the
  front everywhere, even if damage() == 0, thus erasing the overlay,
  and leaving the clip region set to the entire window.
*/
void fltk3::DoubleWindow::flush(int eraseoverlay) {
  make_current(); // make sure fl_gc is non-zero
  Fl_X *myi = Fl_X::i(this);
  if (!myi) return; // window not yet created
  if (!myi->other_xid) {
#if USE_XDBE
    if (can_xdbe()) {
      myi->other_xid = XdbeAllocateBackBufferName(fl_display, fl_xid(this), XdbeCopied);
      myi->backbuffer_bad = 1;
    } else
#endif
#if defined(USE_X11) || defined(WIN32)
    myi->other_xid = fl_create_offscreen(w(), h());
    set_damage(fltk3::DAMAGE_ALL);
#elif defined(__APPLE_QUARTZ__)
    if (force_doublebuffering_) {
      myi->other_xid = fl_create_offscreen(w(), h());
      set_damage(fltk3::DAMAGE_ALL);
    }
#else
# error unsupported platform
#endif
  }
#if USE_XDBE
  if (use_xdbe) {
    if (myi->backbuffer_bad || eraseoverlay) {
      // Make sure we do a complete redraw...
      if (myi->region) {XDestroyRegion(myi->region); myi->region = 0;}
      set_damage(fltk3::DAMAGE_ALL);
      myi->backbuffer_bad = 0;
    }

    // Redraw as needed...
    if (damage()) {
      fltk3::clip_region(myi->region); myi->region = 0;
      fl_window = myi->other_xid;
      draw();
      fl_window = myi->xid;
    }

    // Copy contents of back buffer to window...
    XdbeSwapInfo s;
    s.swap_window = fl_xid(this);
    s.swap_action = XdbeCopied;
    XdbeSwapBuffers(fl_display, &s, 1);
    return;
  } else
#endif
    if (damage() & ~fltk3::DAMAGE_EXPOSE) {
    fltk3::clip_region(myi->region); myi->region = 0;
#ifdef WIN32
    HDC _sgc = fl_gc;
    fl_gc = fl_makeDC(myi->other_xid);
    int save = SaveDC(fl_gc);
    fltk3::restore_clip(); // duplicate region into new gc
    draw();
    RestoreDC(fl_gc, save);
    DeleteDC(fl_gc);
    fl_gc = _sgc;
    //# if defined(FLTK_USE_CAIRO)
    //if fltk3::cairo_autolink_context() fltk3::cairo_make_current(this); // capture gc changes automatically to update the cairo context adequately
    //# endif
#elif defined(__APPLE__)
    if ( myi->other_xid ) {
      fl_begin_offscreen( myi->other_xid );
      fltk3::clip_region( 0 );   
      draw();
      fl_end_offscreen();
    } else {
      draw();
    }
#else // X:
    fl_window = myi->other_xid;
    draw();
    fl_window = myi->xid;
#endif
  }
  if (eraseoverlay) fltk3::clip_region(0);
  // on Irix (at least) it is faster to reduce the area copied to
  // the current clip region:
  int X,Y,W,H; fltk3::clip_box(0,0,w(),h(),X,Y,W,H);
  if (myi->other_xid) fltk3::copy_offscreen(X, Y, W, H, myi->other_xid, X, Y);
}

void fltk3::DoubleWindow::resize(int X,int Y,int W,int H) {
  int ow = w();
  int oh = h();
  Window::resize(X,Y,W,H);
#if USE_XDBE
  if (use_xdbe) {
    Fl_X* myi = Fl_X::i(this);
    if (myi && myi->other_xid && (ow < w() || oh < h())) {
      // STR #2152: Deallocate the back buffer to force creation of a new one.
      XdbeDeallocateBackBufferName(fl_display,myi->other_xid);
      myi->other_xid = 0;
    }
    return;
  }
#endif
  Fl_X* myi = Fl_X::i(this);
  if (myi && myi->other_xid && (ow != w() || oh != h())) {
    fl_delete_offscreen(myi->other_xid);
    myi->other_xid = 0;
  }
}

void fltk3::DoubleWindow::hide() {
  Fl_X* myi = Fl_X::i(this);
  if (myi && myi->other_xid) {
#if USE_XDBE
    if (!use_xdbe)
#endif
      fl_delete_offscreen(myi->other_xid);
  }
  Window::hide();
}

/**
  The destructor <I>also deletes all the children</I>. This allows a
  whole tree to be deleted at once, without having to keep a pointer to
  all the children in the user code.
*/
fltk3::DoubleWindow::~DoubleWindow() {
  hide();
}

//
// End of "$Id$".
//
