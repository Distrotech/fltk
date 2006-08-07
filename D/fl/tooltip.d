//
// "$Id: tooltip.d 4288 2005-04-16 00:13:17Z mike $"
//
// Tooltip class file for the Fast Light Tool Kit (FLTK).
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

module fl.tooltip;

public import fl.fl;
public import fl.widget;

class Fl_Tooltip {
private:

  static void nothing(Fl_Widget w) { }

public:
  static float delay() { 
    return delay_; 
  }

  static void delay(float f) { 
    delay_ = f; 
  }

  static float hoverdelay() { 
    return hoverdelay_; 
  }

  static void hoverdelay(float f) { 
    hoverdelay_ = f;
  }

  static int enabled() { 
   return enabled_; 
  }

  static void enable(int b = 1) { 
    enabled_ = b;
  }

  static void disable() { 
    enabled_ = 0; 
  }

  static void function(Fl_Widget w) enter = &nothing;
/+-
  static void enter_area(Fl_Widget* w, int X, int Y, int W, int H, const char* tip);
-+/
  static void function(Fl_Widget w) exit = &nothing;

  static Fl_Widget current() {
    return widget_;
  }

  // Acts as though enter(widget) was done but does not pop up a
  // tooltip.  This is useful to prevent a tooltip from reappearing when
  // a modal overlapping window is deleted. FLTK does this automatically
  // when you click the mouse button.
  static void current(Fl_Widget w) {
    exit_(null);
    // find the enclosing group with a tooltip:
    Fl_Widget tw = w;
    for (;;) {
      if (!tw) return;
      if (tw.tooltip()) break;
      tw = tw.parent();
    }
    // act just like Fl_Tooltip::enter_() except we can remember a zero:
    widget_ = w;
  }
  
  static int font() { 
    return font_; 
  }

  static int size() { 
    return size_; 
  }

  static void font(Fl_Font i) { 
    font_ = i; 
  }

  static void size(int s) { 
    size_ = s; 
  }

  static void color(Fl_Color c) { 
    color_ = c; 
  }
 
  static Fl_Color color() { 
    return color_; 
  }

  static void textcolor(Fl_Color c) { 
    textcolor_ = c; 
  }
 
  static Fl_Color textcolor() { 
    return textcolor_; 
  }

  // If this widget or one of it's parents has a tooltip, enter it. This
  // will do nothing if this is the current widget (even if the mouse moved
  // out so an exit() was done and then moved back in). If no tooltip can
  // be found do Fl_Tooltip::exit_(). If you don't want this behavior (for instance
  // if you want the tooltip to reappear when the mouse moves back in)
  // call the fancier enter_area() below.
  static void enter_(Fl_Widget w) {
/+= later
    // find the enclosing group with a tooltip:
    Fl_Widget tw = w;
    for (;;) {
      if (!tw) {exit_(null); return;}
      if (tw == widget_) return;
      if (tw.tooltip()) break;
      tw = tw.parent();
    }
    enter_area(w, 0, 0, w.w(), w.h(), tw.tooltip());
=+/
  }

  // Hide any visible tooltip.
  static void exit_(Fl_Widget w) {
/+= later
    if (!widget_ || w == window) return;
    widget_ = null;
    Fl.remove_timeout(tooltip_timeout);
    Fl.remove_timeout(recent_timeout);
    if (window) window.hide();
    if (recent_tooltip) {
      if (Fl.event_state() & FL_BUTTONS) recent_tooltip = 0;
      else Fl.add_timeout(Fl_Tooltip.hoverdelay(), recent_timeout);
    }
=+/
  }

private:
  static float delay_;
  static float hoverdelay_;
  static int enabled_;
  static Fl_Color color_;
  static Fl_Color textcolor_;
  static Fl_Font font_;
  static int size_;
  static Fl_Widget widget_;
};


//
// End of "$Id: Fl_Tooltip.H 4288 2005-04-16 00:13:17Z mike $".
//

/+- This file was imported from C++ using a script
//
// "$Id: Fl_Tooltip.cxx 5190 2006-06-09 16:16:34Z mike $"
//
// Tooltip source file for the Fast Light Tool Kit (FLTK).
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

#include <FL/Fl_Tooltip.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Menu_Window.H>

#include <stdio.h>

float		Fl_Tooltip::delay_ = 1.0f;
float		Fl_Tooltip::hoverdelay_ = 0.2f;
int		Fl_Tooltip::enabled_ = 1;
unsigned	Fl_Tooltip::color_ = fl_color_cube(FL_NUM_RED - 1,
		                                   FL_NUM_GREEN - 1,
						   FL_NUM_BLUE - 2);
unsigned	Fl_Tooltip::textcolor_ = FL_BLACK;
int		Fl_Tooltip::font_ = FL_HELVETICA;
int		Fl_Tooltip::size_ = FL_NORMAL_SIZE;

#define MAX_WIDTH 400

static const char* tip;

class Fl_TooltipBox : public Fl_Menu_Window {
public:
  Fl_TooltipBox() : Fl_Menu_Window(0, 0) {
    set_override();
    end();
  }
  void draw();
  void layout();
  void show() {
    if (tip) Fl_Menu_Window::show();
  }
};

Fl_Widget* Fl_Tooltip::widget_ = 0;
static Fl_TooltipBox *window = 0;
static int X,Y,W,H;

void Fl_TooltipBox::layout() {
  fl_font(Fl_Tooltip::font(), Fl_Tooltip::size());
  int ww, hh;
  ww = MAX_WIDTH;
  fl_measure(tip, ww, hh, FL_ALIGN_LEFT|FL_ALIGN_WRAP|FL_ALIGN_INSIDE);
  ww += 6; hh += 6;

  // find position on the screen of the widget:
  int ox = Fl::event_x_root();
  //int ox = X+W/2;
  int oy = Y + H+2;
  for (Fl_Widget* p = Fl_Tooltip::current(); p; p = p->window()) {
    //ox += p->x();
    oy += p->y();
  }
  int scr_x, scr_y, scr_w, scr_h;
  Fl::screen_xywh(scr_x, scr_y, scr_w, scr_h);
  if (ox+ww > scr_x+scr_w) ox = scr_x+scr_w - ww;
  if (ox < scr_x) ox = scr_x;
  if (H > 30) {
    oy = Fl::event_y_root()+13;
    if (oy+hh > scr_y+scr_h) oy -= 23+hh;
  } else {
    if (oy+hh > scr_y+scr_h) oy -= (4+hh+H);
  }
  if (oy < scr_y) oy = scr_y;

  resize(ox, oy, ww, hh);
}

void Fl_TooltipBox::draw() {
  draw_box(FL_BORDER_BOX, 0, 0, w(), h(), Fl_Tooltip::color());
  fl_color(Fl_Tooltip::textcolor());
  fl_font(Fl_Tooltip::font(), Fl_Tooltip::size());
  fl_draw(tip, 3, 3, w()-6, h()-6, Fl_Align(FL_ALIGN_LEFT|FL_ALIGN_WRAP));
}

static char recent_tooltip;

static void recent_timeout(void*) {
#ifdef DEBUG
  puts("recent_timeout();");
#endif // DEBUG

  recent_tooltip = 0;
}

static char recursion;

static void tooltip_timeout(void*) {
#ifdef DEBUG
  puts("tooltip_timeout();");
#endif // DEBUG

  if (recursion) return;
  recursion = 1;
  if (!tip || !*tip) {
    if (window) window->hide();
  } else {
    //if (Fl::grab()) return;
    if (!window) window = new Fl_TooltipBox;
    // this cast bypasses the normal Fl_Window label() code:
    ((Fl_Widget*)window)->label(tip);
    window->layout();
    window->redraw();
//    printf("tooltip_timeout: Showing window %p with tooltip \"%s\"...\n",
//           window, tip ? tip : "(null)");
    window->show();
  }

  Fl::remove_timeout(recent_timeout);
  recent_tooltip = 1;
  recursion = 0;
}


// Get ready to display a tooltip. The widget and the xywh box inside
// it define an area the tooltip is for, this along with the current
// mouse position places the tooltip (the mouse is assummed to point
// inside or near the box).
void
Fl_Tooltip::enter_area(Fl_Widget* wid, int x,int y,int w,int h, const char* t)
{
#ifdef DEBUG
  printf("Fl_Tooltip::enter_area(wid=%p, x=%d, y=%d, w=%d, h=%d, t=\"%s\")\n",
         wid, x, y, w, h, t ? t : "(null)");
  printf("    recursion=%d, window=%p\n", recursion, window);
#endif // DEBUG

  if (recursion) return;
  if (!t || !*t || !enabled()) {
    exit_(0);
    return;
  }
  // do nothing if it is the same:
  if (wid==widget_ /*&& x==X && y==Y && w==W && h==H*/ && t==tip) return;
  Fl::remove_timeout(tooltip_timeout);
  Fl::remove_timeout(recent_timeout);
  // remember it:
  widget_ = wid; X = x; Y = y; W = w; H = h; tip = t;
  // popup the tooltip immediately if it was recently up:
  if (recent_tooltip) {
    if (window) window->hide();
    Fl::add_timeout(Fl_Tooltip::hoverdelay(), tooltip_timeout);
  } else if (Fl_Tooltip::delay() < .1) {
#ifdef WIN32
    // possible fix for the Windows titlebar, it seems to want the
    // window to be destroyed, moving it messes up the parenting:
    if (window) window->hide();
#endif // WIN32
    tooltip_timeout(0);
  } else {
    if (window) window->hide();
    Fl::add_timeout(Fl_Tooltip::delay(), tooltip_timeout);
  }

#ifdef DEBUG
  printf("    tip=\"%s\", window->shown()=%d\n", tip ? tip : "(null)",
         window ? window->shown() : 0);
#endif // DEBUG
}

//
// End of "$Id: Fl_Tooltip.cxx 5190 2006-06-09 16:16:34Z mike $".
//
    End of automatic import -+/
