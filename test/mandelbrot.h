//
// "$Id: mandelbrot.h,v 1.3 1998/10/21 14:21:34 mike Exp $"
//
// Mandelbrot set header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998 by Bill Spitzak and others.
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

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>

class Drawing_Window;

class Drawing_Area : public Fl_Box {
  void draw();
public:
  uchar *buffer;
  int W,H;
  int nextline;
  int drawn;
  int julia;
  int iterations;
  int brightness;
  double jX, jY;
  double X,Y,scale;
  int sx, sy, sw, sh; // selection box
  void erase_box();
  int handle(int);
  void resize(int,int,int,int);
  void new_display();
  enum {
    MAX_BRIGHTNESS = 16,
    DEFAULT_BRIGHTNESS = 16,
    MAX_ITERATIONS = 14,
    DEFAULT_ITERATIONS = 7
  };
  Drawing_Area(int x,int y,int w,int h) : Fl_Box(x,y,w,h) {
    buffer = 0;
    W = w-6;
    H = h-8;
    nextline = 0;
    drawn = 0;
    julia = 0;
    X = Y = 0;
    scale = 4.0;
    iterations = 1<<DEFAULT_ITERATIONS;
    brightness = DEFAULT_BRIGHTNESS;
  }
  int idle();
};

class Drawing_Window {
public:
  Drawing_Area *d;
  Fl_Slider *gamma_slider;
  Fl_Input *x_input, *y_input, *w_input;
  Fl_Window *window;
  void update_label();
};

//
// End of "$Id: mandelbrot.h,v 1.3 1998/10/21 14:21:34 mike Exp $".
//
