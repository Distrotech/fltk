//
// "$Id: window.d 4421 2005-07-15 09:34:53Z matt $"
//
// Window header file for the Fast Light Tool Kit (FLTK).
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

module fl.window;

public import fl.group;
private import fl.enumerations;
private import fl.tooltip;
private import fl.draw;
private import fl.fl;
private import fl.x;
version (__APPLE__) {
  private import fl.mac;
}


class Fl_Window : Fl_Group {
package:
/+=
  friend class Fl_X;
=+/
  package Fl_X i; // points at the system-specific stuff
  char* iconlabel_;
  char* xclass_;
  void* icon_;
  // size_range stuff:
  short minw, minh, maxw, maxh;
  ubyte dw, dh, aspect, size_range_set;
  // cursor stuff
  Fl_Cursor cursor_default;
  Fl_Color cursor_fg, cursor_bg;
  
  /**
   * Tell the OS what window sizes we want to allow
   */
  void size_range_() {
    size_range_set = 1;
    HISize minSize;
    minSize.width = minw; minSize.height = minh;
    HISize maxSize;
    maxSize.width = maxw?maxw:32000;
    maxSize.height = maxh?maxh:32000;
    if (i && i.xid)
      SetWindowResizeLimits(i.xid, &minSize, &maxSize);
  }

  // values for flags():
  const int FL_MODAL = 64;
  const int FL_NOBORDER = 8;
  const int FL_FORCE_POSITION = 16;
  const int FL_NON_MODAL = 32;
  const int FL_OVERRIDE = 256;

  void _Fl_Window() { // constructor innards
    type(FL_WINDOW);
    box(FL_FLAT_BOX);
    if (Fl.scheme_bg_) {
      labeltype(FL_NORMAL_LABEL);
      alignment(FL_ALIGN_CENTER | FL_ALIGN_INSIDE | FL_ALIGN_CLIP);
      image(Fl.scheme_bg_);
    } else {
      labeltype(FL_NO_LABEL);
    }
    i = null;
    xclass_ = null;
    icon_ = null;
    iconlabel_ = null;
    resizable(null);
    size_range_set = 0;
    minw = maxw = minh = maxh = 0;
    callback(&default_callback);
  }

protected:
/+=
  static Fl_Window  current_;
=+/
  void draw() {
    char *savelabel = label();
    int saveflags = flags();
    int savex = x(); x(0);
    int savey = y(); y(0);
    // Make sure we don't draw the window title in the window background...
    clear_flag(COPIED_LABEL); // do not free copied labels!
    Fl_Widget.label(null);
    super.draw();
    if (!parent() && resizable() && (!size_range_set || minh!=maxh || minw!=maxw)) {
      int dx = Fl.box_dw(box())-Fl.box_dx(box());
      int dy = Fl.box_dh(box())-Fl.box_dy(box());
      if (dx<=0) dx = 1;
      if (dy<=0) dy = 1;
      int x1 = w()-dx-1, x2 = x1, y1 = h()-dx-1, y2 = y1;
      Fl_Color c[4];
      c[0] = color();
      c[1] = fl_color_average(color(), FL_WHITE, 0.7f);
      c[2] = fl_color_average(color(), FL_BLACK, 0.6f);
      c[3] = fl_color_average(color(), FL_BLACK, 0.8f);
      int i;
      for (i=dx; i<12; i++) {
        fl_color(c[i&3]);
        fl_line(x1--, y1, x2, y2--);
      }
    }
    // Restore the label...
    Fl_Widget.label(savelabel);
    set_flag(saveflags);
    y(savey);
    x(savex);
  }

  package void flush() {
    make_current();
    fl_clip_region(i.region); i.region = null;
    draw();
  }

public:
  this(int X,int Y,int W, int H, char* l=null) {
    super(X, Y, W, H, l);
    cursor_default = FL_CURSOR_DEFAULT;
    cursor_fg      = FL_BLACK;
    cursor_bg      = FL_WHITE;
  
    _Fl_Window();
    set_flag(FL_FORCE_POSITION);
  }

  this(int W, int H, char* l=null) {
    Fl_Group.current(null);
    super(0, 0, W, H, l);
    cursor_default = FL_CURSOR_DEFAULT;
    cursor_fg      = FL_BLACK;
    cursor_bg      = FL_WHITE;
  
    _Fl_Window();
    clear_visible();
  }

  ~this() {
    hide();
  }

  int handle(int ev) {
    if (parent()) {
      switch (ev) {
      case FL_SHOW:
        if (!shown()) show();
        else {
          version (__APPLE__) {
            MacMapWindow(this, fl_xid(this));
          } else {
            XMapWindow(fl_display, fl_xid(this)); // extra map calls are harmless
          } // __APPLE__
        }
        break;
      case FL_HIDE:
        if (shown()) {
          // Find what really turned invisible, if is was a parent window
          // we do nothing.  We need to avoid unnecessary unmap calls
          // because they cause the display to blink when the parent is
          // remapped.  However if this or any intermediate non-window
          // widget has really had hide() called directly on it, we must
          // unmap because when the parent window is remapped we don't
          // want to reappear.
          if (visible()) {
           Fl_Widget  p = parent(); for (;p.visible();p = p.parent()) {}
           if (p.type() >= FL_WINDOW) break; // don't do the unmap
          }
          version (__APPLE__) {
            MacUnmapWindow(this, fl_xid(this));
          } else {
            XUnmapWindow(fl_display, fl_xid(this));
          } // __APPLE__
        }
        break;
      }
    }
  
    return super.handle(ev);
  }

  void resize(int X,int Y,int W,int H) {
    if (W<=0) W = 1; // OS X does not like zero width windows
    if (H<=0) H = 1;
    int is_a_resize = (W != w() || H != h());
    if (X != x() || Y != y()) set_flag(FL_FORCE_POSITION);
    else if (!is_a_resize) return;
    if ( !(resize_from_system is this) && (!parent()) && shown()) {
      if (is_a_resize) {
        if (resizable()) {
          if (W<minw) minw = W; // user request for resize takes priority
          if (W>maxw) maxw = W; // over a previously set size_range
          if (H<minh) minh = H;
          if (H>maxh) maxh = H;
          size_range(minw, minh, maxw, maxh);
        } else {
          size_range(W, H, W, H);
        }
        Rect dim; dim.left=X; dim.top=Y; dim.right=X+W; dim.bottom=Y+H;
        SetWindowBounds(i.xid, kWindowContentRgn, &dim);
        Rect all; all.top=-32000; all.bottom=32000; all.left=-32000; all.right=32000;
        InvalWindowRect( i.xid, &all );    
      } else {
        MoveWindow(i.xid, X, Y, 0);
      }
    }
    resize_from_system = null;
    if (is_a_resize) {
      Fl_Group.resize(X,Y,W,H);
      if (shown()) { 
        redraw(); 
      }
    } else {
      x(X); y(Y); 
    }
  }
/+=
  void border(int b);
=+/
  void clear_border()	{set_flag(FL_NOBORDER);}
  int border() {return !(flags() & FL_NOBORDER);}
  void set_override()	{set_flag(FL_NOBORDER|FL_OVERRIDE);}
  int get_override()  { return flags()&FL_OVERRIDE; }
  void set_modal()	{set_flag(FL_MODAL);}
  int modal() {return flags() & FL_MODAL;}
  void set_non_modal()	{set_flag(FL_NON_MODAL);}
  int non_modal() {return flags() & (FL_NON_MODAL|FL_MODAL);}
/+=
  void hotspot(int x, int y, int offscreen = 0);
=+/
  void hotspot(Fl_Widget p, int offscreen = 0) {
    /+== ==+/
  }
/+=
  void free_position()	{clear_flag(FL_FORCE_POSITION);}
=+/
  void size_range(int a, int b, int c=0, int d=0, int e=0, int f=0, int g=0) {
    minw=a; minh=b; maxw=c; maxh=d; dw=e; dh=f; aspect=g; size_range_();}
/+=
  char* label() {return Fl_Widget.label();}
  char* iconlabel() {return iconlabel_;}
  void label(char*);
  void iconlabel(char*);
  void label(char* label, char* iconlabel);
  void copy_label(char* a);
  char* xclass() {return xclass_;}
  void xclass(char* c)	{xclass_ = c;}
  void* icon() {return icon_;}
  void icon(void * ic)	{icon_ = ic;}
=+/

  int shown() {return !(i is null);}
  void show() {
    image(Fl.scheme_bg_);
    if (Fl.scheme_bg_) {
      labeltype(FL_NORMAL_LABEL);
      alignment(FL_ALIGN_CENTER | FL_ALIGN_INSIDE | FL_ALIGN_CLIP);
    } else {
      labeltype(FL_NO_LABEL);
    }
    Fl_Tooltip.exit(this);
    if (!shown() || !i) {
      Fl_X.make(this);
    } else {
        if ( !parent() ) {
          if ( IsWindowCollapsed( i.xid ) ) CollapseWindow( i.xid, false );
          if (!fl_capture) {
            BringToFront(i.xid);
            SelectWindow(i.xid);
          }
        }
    }
  }

  void show(char[][] args) {
    /+= =+/
    show();
  }

  void hide() {
    clear_visible();
    if (!shown()) return;
  
    // remove from the list of windows:
    Fl_X ip = i, pp = Fl_X.first;
    if (ip is pp) {
      Fl_X.first = ip.next;
    } else {
      while (pp) {
        if (ip is pp.next) {
          pp.next = ip.next;
          break;
        }
        pp = pp.next;
      }
      if (!pp) return;
    }
    version (__APPLE__) {
      MacUnlinkWindow(ip);
    }
    i = null;
  
    // recursively remove any subwindows:
    for (Fl_X wi = Fl_X.first; wi;) {
      Fl_Window  W = wi.w;
      if (W.window() is this) {
        W.hide();
        W.set_visible();
        wi = Fl_X.first;
      } else wi = wi.next;
    }
  
    if (this is Fl.modal_) { // we are closing the modal window, find next one:
      Fl_Window  W;
      for (W = Fl.first_window(); W; W = Fl.next_window(W))
        if (W.modal()) break;
      Fl.modal_ = W;
    }
  
    // Make sure no events are sent to this window:
    fl_throw_focus(this);
    handle(FL_HIDE);
  
    version (WIN32) {
      // this little trick keeps the current clipboard alive, even if we are about
      // to destroy the window that owns the selection.
      if (GetClipboardOwner()==ip.xid) {
        Fl_Window  w1 = Fl.first_window();
        if (w1 && OpenClipboard(fl_xid(w1))) {
          EmptyClipboard();
          SetClipboardData(CF_TEXT, NULL);
          CloseClipboard();
        }
      }
      // Send a message to myself so that I'll get out of the event loop...
      PostMessage(ip.xid, WM_APP, 0, 0);
      if (ip.private_dc) fl_release_dc(ip.xid, ip.private_dc);
        if (ip.xid == fl_window && fl_gc) {
          fl_release_dc(fl_window, fl_gc);
          fl_window = (HWND)-1;
          fl_gc = 0;
        }
    } else version (__APPLE__) {
      Fl_X.q_release_context(ip);
      if ( ip.xid is fl_window && !parent() )
        fl_window = null;
    }
    
    if (ip.region) XDestroyRegion(ip.region);
  
    version (WIN32) {
      // this little trickery seems to avoid the popup window stacking problem
      HWND p = GetForegroundWindow();
      if (p==GetParent(ip.xid)) {
        ShowWindow(ip.xid, SW_HIDE);
        ShowWindow(p, SW_SHOWNA);
      }
      XDestroyWindow(fl_display, ip.xid);
    } else version (__APPLE__) {
      MacDestroyWindow(this, ip.xid);
    } else version (USE_XFT) {
      fl_destroy_xft_draw(ip.xid);
    } else {
      XDestroyWindow(fl_display, ip.xid);
    }
      
    version (WIN32) {
      // Try to stop the annoying "raise another program" behavior
      if (non_modal() && Fl.first_window() && Fl.first_window().shown())
        Fl.first_window().show();
    }
    delete ip;
  }
  
/+=
  void show(int, char**);
  void fullscreen();
  void fullscreen_off(int,int,int,int);
  void iconize();
=+/
  int x_root() {
    Fl_Window p = window();
    if (p) return p.x_root() + x();
    return x();
  }
  
  int y_root() {
    Fl_Window p = window();
    if (p) return p.y_root() + y();
    return y();
  }

/+=
  static Fl_Window  current();
=+/
  /**
   * make all drawing go into this window (called by subclass flush() impl.)
   */
  void make_current()
  {
    OSStatus err;
    Fl_X.q_release_context();
  
    if ( !fl_window_region )
      fl_window_region = NewRgn();
    fl_window = i.xid;
    current_ = this;
    
    SetPort( GetWindowPort(i.xid) ); // \todo check for the handling of doublebuffered windows
    
    int xp = 0, yp = 0;
    Fl_Window win = this;
    while ( win ) 
    { 
      if ( !win.window() )
        break;
      xp += win.x();
      yp += win.y();
      win = win.window();
    }
    SetOrigin( -xp, -yp );
        
    SetRectRgn( fl_window_region, 0, 0, w(), h() );
    
    // \todo for performance reasons: we don't have to create this unless the child windows moved
    for ( Fl_X cx = i.xidChildren; cx; cx = cx.xidNext )
    {
      Fl_Window cw = cx.w;
      if (!cw.visible_r()) continue;
      Fl_Region r = NewRgn();
      SetRectRgn( r, cw.x() - xp, cw.y() - yp,
                     cw.x() + cw.w() - xp, cw.y() + cw.h() - yp );
      DiffRgn( fl_window_region, r, fl_window_region );
      DisposeRgn( r );
    }
    
    err = QDBeginCGContext(GetWindowPort(i.xid), &i.gc);
    fl_gc = i.gc;
    CGContextSaveGState(fl_gc);
    Fl_X.q_fill_context();
  
    fl_clip_region( null );
    SetPortClipRegion( GetWindowPort(i.xid), fl_window_region );
  } 

  // for back-compatability only:
  void cursor(Fl_Cursor c, Fl_Color fg=cast(uint)FL_BLACK, Fl_Color bg=cast(uint)FL_WHITE) {
    /+=== ===+/
  }

  void default_cursor(Fl_Cursor c, Fl_Color fg=cast(uint)FL_BLACK, Fl_Color bg=cast(uint)FL_WHITE) {
    /+=== ===+/
  }

  static void default_callback(Fl_Widget win, void* v) {
    Fl.atclose(cast(Fl_Window)win, v);
  }
}
/+=
}

//
// End of "$Id: window.d 4421 2005-07-15 09:34:53Z matt $".
//
    End of automatic import -+/
/+- This file was imported from C++ using a script
//
// "$Id: window.d 5251 2006-06-28 10:23:33Z matt $"
//
// Window widget class for the Fast Light Tool Kit (FLTK).
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

// The Fl_Window is a window in the fltk library.
// This is the system-independent portions.  The huge amount of 
// crap you need to do to communicate with X is in Fl_x.cxx, the
// equivalent (but totally different) crap for MSWindows is in Fl_win32.cxx

#include <FL/Fl.H>
private import fl.window;
#include <stdlib.h>
private import fl.flstring;

version (__APPLE_QUARTZ__) {
private import fl.draw;
}




}

void Fl_Window.label(char *name) {
  label(name, iconlabel());
}

void Fl_Window.copy_label(char *a) {
  if (flags() & COPIED_LABEL) {
    free((void *)label());
    clear_flag(COPIED_LABEL);
  }
  if (a) a = strdup(a);
  label(a, iconlabel());
  set_flag(COPIED_LABEL);
}


void Fl_Window.iconlabel(char *iname) {
  ubyte saveflags = flags();
  label(label(), iname);
  set_flag(saveflags);
}


Fl_Window  Fl_Window.current() {
  return current_;
}


//
// End of "$Id: window.d 5251 2006-06-28 10:23:33Z matt $".
//
    End of automatic import -+/
