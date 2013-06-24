//
// "$Id$"
//
// Definition of classes fltk3::GraphicsDriver, fltk3::SurfaceDevice, fltk3::DisplayDevice
// for the Fast Light Tool Kit (FLTK).
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
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//
/** \file quartz_graphcs_driver.h
 */

#ifndef FLTK3_OSX_QUARTZ_GRAPHICS_DRIVER_H
#define FLTK3_OSX_QUARTZ_GRAPHICS_DRIVER_H

#include <config.h>

#ifdef __APPLE__

#include <fltk3/Device.h>

namespace fltk3 {
  
  /**
   \brief The Mac OS X-specific graphics class.
   *
   This class is implemented only on the Mac OS X platform.
   */
  class FLTK3_EXPORT QuartzGraphicsDriver : public fltk3::GraphicsDriver {
  public:
    void color(fltk3::Color c);
    void color(uchar r, uchar g, uchar b);
    void draw(const char* str, int n, int x, int y);
    void draw(const char *str, int n, float x, float y);
    void draw(int angle, const char *str, int n, int x, int y);
    void rtl_draw(const char* str, int n, int x, int y);
    void font(fltk3::Font face, fltk3::Fontsize size);
    void draw(fltk3::Pixmap *pxm, int XP, int YP, int WP, int HP, int cx, int cy);
    void draw(fltk3::Bitmap *pxm, int XP, int YP, int WP, int HP, int cx, int cy);
    void draw(fltk3::RGBImage *img, int XP, int YP, int WP, int HP, int cx, int cy);
    void draw_image(const uchar* buf, int X,int Y,int W,int H, int D=3, int L=0);
    void draw_image(fltk3::DrawImageCb cb, void* data, int X,int Y,int W,int H, int D=3);
    void draw_image_mono(const uchar* buf, int X,int Y,int W,int H, int D=1, int L=0);
    void draw_image_mono(fltk3::DrawImageCb cb, void* data, int X,int Y,int W,int H, int D=1);
    double width(const char *str, int n);
    double width(unsigned int c);
    void text_extents(const char*, int n, int& dx, int& dy, int& w, int& h);
    int height();
    int descent();
    void end_points();
    void end_line();
    void end_polygon();
    void end_complex_polygon();
    void circle(double x, double y, double r);
    void arc(int x,int y,int w,int h,double a1,double a2);
    void pie(int x,int y,int w,int h,double a1,double a2);
    void rect(int x, int y, int w, int h);
    void rectf(int x, int y, int w, int h);
    void xyline(int x, int y, int x1);
    void xyline(int x, int y, int x1, int y2);
    void xyline(int x, int y, int x1, int y2, int x3);
    void yxline(int x, int y, int y1);
    void yxline(int x, int y, int y1, int x2);
    void yxline(int x, int y, int y1, int x2, int y3);
    void line(int x, int y, int x1, int y1);
    void line(int x, int y, int x1, int y1, int x2, int y2);
    void loop(int x, int y, int x1, int y1, int x2, int y2);
    void loop(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3);
    void polygon(int x0, int y0, int x1, int y1, int x2, int y2);
    void polygon(int x, int y, int x1, int y1, int x2, int y2, int x3, int y3);
    void point(int x, int y);
    void restore_clip();
    void push_clip(int x, int y, int w, int h);
    int not_clipped(int x, int y, int w, int h);
    int clip_box(int x, int y, int w, int h, int &X, int &Y, int &W, int &H);
    void line_style(int style, int width=0, char* dashes=0);
    void transformed_vertex(double xf, double yf);
    void copy_offscreen(int x, int y, int w, int h, fltk3::Offscreen pixmap, int srcx, int srcy);
    char can_do_alpha_blending();
    static fltk3::Offscreen create_offscreen_with_alpha(int w, int h);
  };
  
  class FLTK3_EXPORT PrinterQuartzGraphicsDriver : public QuartzGraphicsDriver {
  public:
    bool is_printer() { return true; }
    void rect(int x, int y, int w, int h);
    void xyline(int x, int y, int x1);
    void xyline(int x, int y, int x1, int y2);
    void xyline(int x, int y, int x1, int y2, int x3);
    void yxline(int x, int y, int y1);
    void yxline(int x, int y, int y1, int x2);
    void yxline(int x, int y, int y1, int x2, int y3);
    void line_style(int style, int width, char* dashes);
  };
  
}

#endif // __APPLE__

#endif // FLTK3_OSX_QUARTZ_GRAPHICS_DRIVER_H

//
// End of "$Id$".
//
