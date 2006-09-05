//
// "$Id: menu_window.d 4288 2005-04-16 00:13:17Z mike $"
//
// Menu window header file for the Fast Light Tool Kit (FLTK).
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

module fl.menu_window;

public import fl.single_window;

class Fl_Menu_Window : Fl_Single_Window {
private:
  const int NO_OVERLAY = 128;

public:

  void show() {
    version (HAVE_OVERLAY) {
      if (!shown() && overlay() && fl_find_overlay_visual()) {
        XInstallColormap(fl_display, fl_overlay_colormap);
        fl_background_pixel = cast(int)fl_transparent_pixel;
        Fl_X.make_xid(this, fl_overlay_visual, fl_overlay_colormap);
        fl_background_pixel = -1;
      } else {
        super.show();
      }
    } else {
      super.show();
    }
  }

  void erase() {
    version (HAVE_OVERLAY) {
      if (!gc || !shown()) return;
      //XSetForeground(fl_display, gc, 0);
      //XFillRectangle(fl_display, fl_xid(this), gc, 0, 0, w(), h());
      XClearWindow(fl_display, fl_xid(this));
    }
  }

  void flush() {
    version (HAVE_OVERLAY) {
      if (!fl_overlay_visual || !overlay()) {Fl_Single_Window.flush(); return;}
      Fl_X  myi = Fl_X.i(this);
      fl_window = myi.xid;
      if (!gc) gc = XCreateGC(fl_display, myi.xid, 0, 0);
      fl_gc = gc;
      fl_overlay = 1;
      fl_clip_region(myi.region); myi.region = 0; current_ = this;
      draw();
      fl_overlay = 0;
    } else {
      super.flush();
    }
  }

  void hide() {
    erase();
    super.hide();
  }

  int overlay() {return !(flags()&NO_OVERLAY);}
  void set_overlay() {clear_flag(NO_OVERLAY);}
  void clear_overlay() {set_flag(NO_OVERLAY);}

  ~this() {
    hide();
  }

  this(int W, int H, char *l=null) {
    super(W,H,l);
    image(null);
  }
  this(int X, int Y, int W, int H, char *l=null) {
    super(X,Y,W,H,l);
    image(null); 
  }
}

//
// End of "$Id: menu_window.d 4288 2005-04-16 00:13:17Z mike $".
//
