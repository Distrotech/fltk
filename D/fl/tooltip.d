//
// "$Id: tooltip.d 4288 2005-04-16 00:13:17Z mike $"
//
// Tooltip header file for the Fast Light Tool Kit (FLTK).
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
public import fl.enumerations;
public import fl.widget;
private import fl.menu_window;
private import fl.draw;

static char recursion = 0;
static char* tip = null;
static Fl_TooltipBox window = null;
static int X,Y,W,H;
static char recent_tooltip = 0;
static const int MAX_WIDTH = 400; 


class Fl_Tooltip {

private:

  static void recent_timeout(void* d) {
    recent_tooltip = 0;
  }

  static void tooltip_timeout(void* d) {
    if (recursion) return;
    recursion = 1;
    if (!tip || !*tip) {
      if (window) window.hide();
    } else {
      //if (Fl.grab()) return;
      if (!window) window = new Fl_TooltipBox;
      // this cast bypasses the normal Fl_Window label() code:
      (cast(Fl_Widget)window).label(tip);
      window.layout();
      window.redraw();
  //    printf("tooltip_timeout: Showing window %p with tooltip \"%s\"...\n",
  //           window, tip ? tip : "(null)");
      window.show();
    }
  
    Fl.remove_timeout(&recent_timeout);
    recent_tooltip = 1;
    recursion = 0;
  }

public:

  static float delay() { return delay_; }
  static void delay(float f) { delay_ = f; }
  static float hoverdelay() { return hoverdelay_; }
  static void hoverdelay(float f) { hoverdelay_ = f; }
  static int enabled() { return enabled_; }
  static void enable(int b = 1) { enabled_ = b;}
  static void disable() { enabled_ = 0; }

  static void function(Fl_Widget w) enter = &enter_;
  static void enter_area(Fl_Widget wid, int x,int y,int w,int h, char* t) {
    if (recursion) return;
    if (!t || !*t || !enabled()) {
      exit_(null);
      return;
    }
    // do nothing if it is the same:
    if (wid is widget_ /*&& x==X && y==Y && w==W && h==H*/ && t is tip) return;
    Fl.remove_timeout(&tooltip_timeout);
    Fl.remove_timeout(&recent_timeout);
    // remember it:
    widget_ = wid; X = x; Y = y; W = w; H = h; tip = t;
    // popup the tooltip immediately if it was recently up:
    if (recent_tooltip) {
      if (window) window.hide();
      Fl.add_timeout(hoverdelay(), &tooltip_timeout);
    } else if (delay() < .1) {
      version (WIN32) {
        // possible fix for the Windows titlebar, it seems to want the
        // window to be destroyed, moving it messes up the parenting:
        if (window && window.visible()) window.hide();
      } // WIN32
      tooltip_timeout(null);
    } else {
      if (window && window.visible()) window.hide();
      Fl.add_timeout(delay(), &tooltip_timeout);
    }
  }
  
  static void function(Fl_Widget w) exit = &exit_;
  static Fl_Widget current() {return widget_;}
  static void current(Fl_Widget w) {
    exit_(null);
    // find the enclosing group with a tooltip:
    Fl_Widget tw = w;
    for (;;) {
      if (!tw) return;
      if (tw.tooltip()) break;
      tw = tw.parent();
    }
    // act just like Fl_Tooltip.enter_() except we can remember a zero:
    widget_ = w;
  }

  static int font() { return font_; }
  static int size() { return size_; }
  static void font(int i) { font_ = i; }
  static void size(int s) { size_ = s; }
  static void color(uint c) { color_ = c; }
  static Fl_Color color() { return color_; }
  static void textcolor(uint c) { textcolor_ = c; }
  static Fl_Color textcolor() { return textcolor_; }

  // These should not be public, but Fl_Widget.tooltip() needs them...
  static void enter_(Fl_Widget  w) {
    Fl_Widget  tw = w;
    for (;;) {
      if (!tw) {exit_(null); return;}
      if (tw is widget_) return;
      if (tw.tooltip()) break;
      tw = tw.parent();
    }
    enter_area(w, 0, 0, w.w(), w.h(), tw.tooltip());
  }
  static void exit_(Fl_Widget w) {
    if (!widget_ || w is window) return;
    widget_ = null;
    Fl.remove_timeout(&tooltip_timeout);
    Fl.remove_timeout(&recent_timeout);
    if (window && window.visible()) window.hide();
    if (recent_tooltip) {
      if (Fl.event_state() & FL_BUTTONS) recent_tooltip = 0;
      else Fl.add_timeout(Fl_Tooltip.hoverdelay(), &recent_timeout);
    }
  }

private:

  static float delay_ = 1.0;
  static float hoverdelay_ = 0.2;
  static int enabled_ = 1;
  static uint color_ = 27*8-1;
  static uint textcolor_ = FL_BLACK;
  static int font_ = FL_HELVETICA;
  static int size_ = FL_NORMAL_SIZE;
  static Fl_Widget widget_ = null;
}


class Fl_TooltipBox : Fl_Menu_Window {
  this() {
    super(0, 0);
    set_override();
    end();
  }
  void draw() {
    draw_box(FL_BORDER_BOX, 0, 0, w(), h(), Fl_Tooltip.color());
    fl_color(Fl_Tooltip.textcolor());
    fl_font(Fl_Tooltip.font(), Fl_Tooltip.size());
    fl_draw(tip, 3, 3, w()-6, h()-6, FL_ALIGN_LEFT|FL_ALIGN_WRAP);
  }
  void layout() {
    fl_font(Fl_Tooltip.font(), Fl_Tooltip.size());
    int ww, hh;
    ww = MAX_WIDTH;
    fl_measure(tip, ww, hh, FL_ALIGN_LEFT|FL_ALIGN_WRAP|FL_ALIGN_INSIDE);
    ww += 6; hh += 6;
  
    // find position on the screen of the widget:
    int ox = Fl.event_x_root();
    //int ox = X+W/2;
    int oy = Y + H+2;
    for (Fl_Widget p = Fl_Tooltip.current(); p; p = p.window()) {
      //ox += p.x();
      oy += p.y();
    }
    int scr_x, scr_y, scr_w, scr_h;
    Fl.screen_xywh(scr_x, scr_y, scr_w, scr_h);
    if (ox+ww > scr_x+scr_w) ox = scr_x+scr_w - ww;
    if (ox < scr_x) ox = scr_x;
    if (H > 30) {
      oy = Fl.event_y_root()+13;
      if (oy+hh > scr_y+scr_h) oy -= 23+hh;
    } else {
      if (oy+hh > scr_y+scr_h) oy -= (4+hh+H);
    }
    if (oy < scr_y) oy = scr_y;
  
    resize(ox, oy, ww, hh);
  }
  void show() {
    if (tip) super.show();
  }
}

//
// End of "$Id: tooltip.d 4288 2005-04-16 00:13:17Z mike $".
//
