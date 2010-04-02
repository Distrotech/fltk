//
// "$Id$"
//
// WIN32 image drawing code for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2009 by Bill Spitzak and others.
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

// I hope a simple and portable method of drawing color and monochrome
// images.  To keep this simple, only a single storage type is
// supported: 8 bit unsigned data, byte order RGB, and pixels are
// stored packed into rows with the origin at the top-left.  It is
// possible to alter the size of pixels with the "delta" argument, to
// add alpha or other information per pixel.  It is also possible to
// change the origin and direction of the image data by messing with
// the "delta" and "linedelta", making them negative, though this may
// defeat some of the shortcuts in translating the image for X.

// Unbelievably (since it conflicts with how most PC software works)
// Micro$oft picked a bottom-up and BGR storage format for their
// DIB images.  I'm pretty certain there is a way around this, but
// I can't find any other than the brute-force method of drawing
// each line as a separate image.  This may also need to be done
// if the delta is any amount other than 1, 3, or 4.

////////////////////////////////////////////////////////////////

#include <config.h>
#include <fltk3/run.h>
#include <fltk3/draw.h>
#include <fltk3/x.H>

#define MAXBUFFER 0x40000 // 256k

#if USE_COLORMAP

// error-diffusion dither into the FLTK colormap
static void dither(uchar* to, const uchar* from, int w, int delta) {
  static int ri, gi, bi, dir;
  int r=ri, g=gi, b=bi;
  int d, td;
  if (dir) {
    dir = 0;
    from = from+(w-1)*delta;
    to = to+(w-1);
    d = -delta;
    td = -1;
  } else {
    dir = 1;
    d = delta;
    td = 1;
  }
  for (; w--; from += d, to += td) {
    r += from[0]; if (r < 0) r = 0; else if (r>255) r = 255;
    int rr = r*FL_NUM_RED/256;
    r -= rr*255/(FL_NUM_RED-1);
    g += from[1]; if (g < 0) g = 0; else if (g>255) g = 255;
    int gg = g*FL_NUM_GREEN/256;
    g -= gg*255/(FL_NUM_GREEN-1);
    b += from[2]; if (b < 0) b = 0; else if (b>255) b = 255;
    int bb = b*FL_NUM_BLUE/256;
    b -= bb*255/(FL_NUM_BLUE-1);
    *to = uchar(FL_COLOR_CUBE+(bb*FL_NUM_RED+rr)*FL_NUM_GREEN+gg);
  }
  ri = r; gi = g; bi = b;
}

// error-diffusion dither into the FLTK colormap
static void monodither(uchar* to, const uchar* from, int w, int delta) {
  static int ri,dir;
  int r=ri;
  int d, td;
  if (dir) {
    dir = 0;
    from = from+(w-1)*delta;
    to = to+(w-1);
    d = -delta;
    td = -1;
  } else {
    dir = 1;
    d = delta;
    td = 1;
  }
  for (; w--; from += d, to += td) {
    r += *from; if (r < 0) r = 0; else if (r>255) r = 255;
    int rr = r*FL_NUM_GRAY/256;
    r -= rr*255/(FL_NUM_GRAY-1);
    *to = uchar(FL_GRAY_RAMP+rr);
  }
  ri = r;
}

#endif // USE_COLORMAP

static void innards(const uchar *buf, int X, int Y, int W, int H,
		    int delta, int linedelta, int depth,
		    Fl_Draw_Image_Cb cb, void* userdata)
{
  char indexed = 0;

#if USE_COLORMAP
  indexed = (fl_palette != 0);
#endif

  if (depth==0) depth = 3;
  if (indexed || !fl_can_do_alpha_blending()) 
    depth = (depth-1)|1;

  if (!linedelta) linedelta = W*delta;

  int x, y, w, h;
  fl_clip_box(X,Y,W,H,x,y,w,h);
  if (w<=0 || h<=0) return;
  if (buf) buf += (x-X)*delta + (y-Y)*linedelta;

  static U32 bmibuffer[256+12];
  BITMAPINFO &bmi = *((BITMAPINFO*)bmibuffer);
  if (!bmi.bmiHeader.biSize) {
    bmi.bmiHeader.biSize = sizeof(bmi)-4; // does it use this to determine type?
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biXPelsPerMeter = 0;
    bmi.bmiHeader.biYPelsPerMeter = 0;
    bmi.bmiHeader.biClrUsed = 0;
    bmi.bmiHeader.biClrImportant = 0;
  }
#if USE_COLORMAP
  if (indexed) {
    for (short i=0; i<256; i++) {
      *((short*)(bmi.bmiColors)+i) = i;
    }
  } else
#endif
  if (depth<3) {
    for (int i=0; i<256; i++) {
      bmi.bmiColors[i].rgbBlue = (uchar)i;
      bmi.bmiColors[i].rgbGreen = (uchar)i;
      bmi.bmiColors[i].rgbRed = (uchar)i;
      bmi.bmiColors[i].rgbReserved = (uchar)0; // must be zero
    }
  }
  bmi.bmiHeader.biWidth = w;
#if USE_COLORMAP
  bmi.bmiHeader.biBitCount = indexed ? 8 : depth*8;
  int pixelsize = indexed ? 1 : depth;
#else
  bmi.bmiHeader.biBitCount = depth*8;
  int pixelsize = depth;
#endif
  if (depth==2) { // special case: gray with alpha
    bmi.bmiHeader.biBitCount = 32;
    pixelsize = 4;
  }
  int linesize = (pixelsize*w+3)&~3;
  
  static U32* buffer;
  int blocking = h;
  {int size = linesize*h;
  if (size > MAXBUFFER) {
    size = MAXBUFFER;
    blocking = MAXBUFFER/linesize;
  }
  static long buffer_size;
  if (size > buffer_size) {
    delete[] buffer;
    buffer_size = size;
    buffer = new U32[(size+3)/4];
  }}
  bmi.bmiHeader.biHeight = blocking;
  static U32* line_buffer;
  if (!buf) {
    int size = W*delta;
    static int line_buf_size;
    if (size > line_buf_size) {
      delete[] line_buffer;
      line_buf_size = size;
      line_buffer = new U32[(size+3)/4];
    }
  }
  for (int j=0; j<h; ) {
    int k;
    for (k = 0; j<h && k<blocking; k++, j++) {
      const uchar* from;
      if (!buf) { // run the converter:
	cb(userdata, x-X, y-Y+j, w, (uchar*)line_buffer);
	from = (uchar*)line_buffer;
      } else {
	from = buf;
	buf += linedelta;
      }
      uchar *to = (uchar*)buffer+(blocking-k-1)*linesize;
#if USE_COLORMAP
      if (indexed) {
	if (depth<3)
	  monodither(to, from, w, delta);
	else 
	  dither(to, from, w, delta);
	to += w;
      } else
#endif
      {
        int i;
        switch (depth) {
          case 1: 
            for (i=w; i--; from += delta) *to++ = *from;
            break;
          case 2:
	    for (i=w; i--; from += delta, to += 4) {
	      uchar a = from[1];
	      uchar gray = (from[0]*a)>>8;
	      to[0] = gray;
	      to[1] = gray;
	      to[2] = gray;
	      to[3] = a;
            }
            break;
          case 3:
	    for (i=w; i--; from += delta, to += 3) {
	      uchar r = from[0];
	      to[0] = from[2];
	      to[1] = from[1];
	      to[2] = r;
            }
            break;          
          case 4:
	    for (i=w; i--; from += delta, to += 4) {
              uchar a = from[3];
	      uchar r = from[0];
	      to[0] = (from[2]*a)>>8;
	      to[1] = (from[1]*a)>>8;
	      to[2] = (r*a)>>8;
	      to[3] = from[3];
            }
            break;          
        }            
      }
    }
    if(Fl_Device::current()->type() == Fl_Device::gdi_printer) {
      // if print context, device and logical units are not equal, so SetDIBitsToDevice
      // does not do the expected job, whereas StretchDIBits does it.
      StretchDIBits(fl_gc, x, y+j-k, w, k, 0, 0, w, k,
		    (LPSTR)((uchar*)buffer+(blocking-k)*linesize),
		    &bmi,
#if USE_COLORMAP
		    indexed ? DIB_PAL_COLORS : DIB_RGB_COLORS
#else
		    DIB_RGB_COLORS
#endif
		    , SRCCOPY );
    }
    else {
      SetDIBitsToDevice(fl_gc, x, y+j-k, w, k, 0, 0, 0, k,
			(LPSTR)((uchar*)buffer+(blocking-k)*linesize),
			&bmi,
#if USE_COLORMAP
			indexed ? DIB_PAL_COLORS : DIB_RGB_COLORS
#else
			DIB_RGB_COLORS
#endif
			);
      }
  }
}

static int fl_abs(int v) { return v<0 ? -v : v; }

void Fl_Device::draw_image(const uchar* buf, int x, int y, int w, int h, int d, int l){
  if (fl_abs(d)&FL_IMAGE_WITH_ALPHA) {
    d ^= FL_IMAGE_WITH_ALPHA;
    innards(buf,x,y,w,h,d,l,fl_abs(d),0,0);
  } else {
    innards(buf,x,y,w,h,d,l,(d<3&&d>-3),0,0);
  }
}

void Fl_Device::draw_image(Fl_Draw_Image_Cb cb, void* data,
		   int x, int y, int w, int h,int d) {
  if (fl_abs(d)&FL_IMAGE_WITH_ALPHA) {
    d ^= FL_IMAGE_WITH_ALPHA;
    innards(0,x,y,w,h,d,0,(d<3&&d>-3),cb,data);
  } else {
    innards(0,x,y,w,h,d,0,(d<3&&d>-3),cb,data);
  }
}

void Fl_Device::draw_image_mono(const uchar* buf, int x, int y, int w, int h, int d, int l){
  if (fl_abs(d)&FL_IMAGE_WITH_ALPHA) {
    d ^= FL_IMAGE_WITH_ALPHA;
    innards(buf,x,y,w,h,d,l,1,0,0);
  } else {
    innards(buf,x,y,w,h,d,l,1,0,0);
  }
}

void Fl_Device::draw_image_mono(Fl_Draw_Image_Cb cb, void* data,
		   int x, int y, int w, int h,int d) {
  if (fl_abs(d)&FL_IMAGE_WITH_ALPHA) {
    d ^= FL_IMAGE_WITH_ALPHA;
    innards(0,x,y,w,h,d,0,1,cb,data);
  } else {
    innards(0,x,y,w,h,d,0,1,cb,data);
  }
}

void fl_rectf(int x, int y, int w, int h, uchar r, uchar g, uchar b) {
#if USE_COLORMAP
  // use the error diffusion dithering code to produce a much nicer block:
  if (fl_palette) {
    uchar c[3];
    c[0] = r; c[1] = g; c[2] = b;
    innards(c,x,y,w,h,0,0,0,0,0);
    return;
  }
#endif
  fl_color(r,g,b);
  fl_rectf(x,y,w,h);
}

//
// End of "$Id$".
//
