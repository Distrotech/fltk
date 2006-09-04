//
// "$Id: fl.d 5188 2006-06-09 07:48:08Z matt $"
//
// Main header file for the Fast Light Tool Kit (FLTK).
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

module fl.fl;

private import fl.enumerations;
private import fl.x;
private import fl.window;
private import fl.widget;
private import fl.boxtype;
private import fl.labeltype;
private import fl.image;
private import fl.tooltip;
private import fl.draw;
private import std.ctype;
private import std.c.math;

version (__APPLE__) {
  private import fl.mac;
}

typedef void function(Fl_Label*, int,int,int,int, Fl_Align) Fl_Label_Draw_F;
typedef void function(Fl_Label*, inout int, inout int) Fl_Label_Measure_F;
typedef void function(int,int,int,int, Fl_Color) Fl_Box_Draw_F;

static char     fl_bg_set = 0;
static char     fl_bg2_set = 0;
static char     fl_fg_set = 0;

alias void function(void*) Fl_Timeout_Handler;

class Fl {

private:
  static char in_idle;
  const float FOREVER = 1e20; 

public: // should be private!

  static int e_number;
  static int e_x;
  static int e_y;
  static int e_x_root;
  static int e_y_root;
  static int e_dx;
  static int e_dy;
  static int e_state;
  static int e_clicks;
  static int e_is_click;
  static int e_keysym;
  static char* e_text = "\0";;
  static int e_length;
  static Fl_Widget belowmouse_;
  static Fl_Widget pushed_;
  static Fl_Widget focus_;
  static int damage_;
  static Fl_Widget  selection_owner_;
  static Fl_Window  modal_;
  static Fl_Window  grab_;
  static int compose_state;
  static int visible_focus_ = 1;
  static int dnd_text_ops_ = 1;

  static void damage(int d) { damage_ = d; }
  static void function() idle = null;
  static char* scheme_;
  static Fl_Image  scheme_bg_;
  static int e_original_keysym; // late addition

public:
  // API version number
  static double get_version() {
    return FL_VERSION;
  }

/+=
  // argument parsers:
  static int arg(int, char**, int&);
  static int args(int, char**, int&, int (*)(int,char**,int&) = 0);
  static char* help;
  static void args(int, char**);

  // things called by initialization:
  static void display(char*);
  static int visual(int);
  static int gl_visual(int, int *alist=0);
  static void own_colormap();
=+/
  private static void set_selection_color(ubyte r, ubyte g, ubyte b) {
    set_color(FL_SELECTION_COLOR,r,g,b);
  }

  static void get_system_colors() {
    version (__APPLE__) {
      fl_open_display();
    
      if (!fl_bg2_set) background2(0xff, 0xff, 0xff);
      if (!fl_fg_set) foreground(0, 0, 0);
      if (!fl_bg_set) background(0xd8, 0xd8, 0xd8);
      
      set_selection_color(0x00, 0x00, 0x80);
    }
  }

  static void foreground(ubyte r, ubyte g, ubyte b) {
    fl_fg_set = 1;
    set_color(FL_FOREGROUND_COLOR,r,g,b);
  }

  static void background(ubyte r, ubyte g, ubyte b) {
    fl_bg_set = 1;
  
    // replace the gray ramp so that FL_GRAY is this color
    if (!r) r = 1; else if (r==255) r = 254;
    double powr = log(r/255.0)/log((FL_GRAY-FL_GRAY_RAMP)/(FL_NUM_GRAY-1.0));
    if (!g) g = 1; else if (g==255) g = 254;
    double powg = log(g/255.0)/log((FL_GRAY-FL_GRAY_RAMP)/(FL_NUM_GRAY-1.0));
    if (!b) b = 1; else if (b==255) b = 254;
    double powb = log(b/255.0)/log((FL_GRAY-FL_GRAY_RAMP)/(FL_NUM_GRAY-1.0));
    for (int i = 0; i < FL_NUM_GRAY; i++) {
      double gray = i/(FL_NUM_GRAY-1.0);
      set_color(fl_gray_ramp(i),
                    cast(ubyte)(pow(gray,powr)*255+.5),
                    cast(ubyte)(pow(gray,powg)*255+.5),
                    cast(ubyte)(pow(gray,powb)*255+.5));
    }
  }

  static void background2(ubyte r, ubyte g, ubyte b) {
    fl_bg2_set = 1;
  
    set_color(FL_BACKGROUND2_COLOR,r,g,b);
    set_color(FL_FOREGROUND_COLOR,
                  get_color(fl_contrast(FL_FOREGROUND_COLOR,FL_BACKGROUND2_COLOR)));
  }

/+=
  // schemes:
  static int scheme(char*);
=+/
  static char* scheme() {return scheme_;}
/+=
  static int reload_scheme();

  // execution:
  static int wait();
=+/
  static double wait(double time_to_wait) {
    // delete all widgets that were listed during callbacks
    do_widget_deletion();
    version (WIN32) {
      return fl_wait(time_to_wait);
    } else version (__APPLE__) {
      flush();
      if (idle) {
        if (!in_idle) {
          in_idle = 1;
          idle();
          in_idle = 0;
        }
        // the idle function may turn off idle, we can then wait:
        if (idle) time_to_wait = 0.0;
      }
      return fl_wait(time_to_wait);
    } else {
      if (first_timeout) {
        elapse_timeouts();
        Timeout *t;
        while ((t = first_timeout)) {
          if (t.time > 0) break;
          // The first timeout in the array has expired.
          missed_timeout_by = t.time;
          // We must remove timeout from array before doing the callback:
          void (*cb)(void*) = t.cb;
          void *argp = t.arg;
          first_timeout = t.next;
          t.next = free_timeout;
          free_timeout = t;
          ++free_timeout_count;
          --first_timeout_count;
          // Now it is safe for the callback to do add_timeout:
          cb(argp);
        }
      } else {
        reset_clock = 1; // we are not going to check the clock
      }
      run_checks();
    //  if (idle && !fl_ready()) {
      if (idle) {
        if (!in_idle) {
          in_idle = 1;
          idle();
          in_idle = 0;
        }
        // the idle function may turn off idle, we can then wait:
        if (idle) time_to_wait = 0.0;
      }
      if (first_timeout && first_timeout.time < time_to_wait)
        time_to_wait = first_timeout.time;
      if (time_to_wait <= 0.0) {
        // do flush second so that the results of events are visible:
        int ret = fl_wait(0.0);
        flush();
        return ret;
      } else {
        // do flush first so that user sees the display:
        flush();
        return fl_wait(time_to_wait);
      }
    }
  }
/+=
  static int check();
  static int ready();
=+/
  static int run() {
    while (Fl_X.first) wait(FOREVER);
    return 0;
  }

  static Fl_Widget readqueue() {
    if (Fl_Widget.obj_tail == Fl_Widget.obj_head) return null;
    Fl_Widget o = Fl_Widget.obj_queue[Fl_Widget.obj_tail++];
    if (Fl_Widget.obj_tail >= Fl_Widget.QUEUE_SIZE) 
      Fl_Widget.obj_tail = 0;
    return o;
  }
  
  version (__APPLE__) {
    struct MacTimeout {
      Fl_Timeout_Handler callback;
      void* data;
      EventLoopTimerRef timer;
      EventLoopTimerUPP upp;
      char pending; 
    };
    static MacTimeout* mac_timers;
    static int mac_timer_alloc;
    static int mac_timer_used;
    private static void realloc_timers() {
      if (mac_timer_alloc == 0) {
        mac_timer_alloc = 8;
      }
      mac_timer_alloc *= 2;
      MacTimeout* new_timers = new MacTimeout[mac_timer_alloc];
      memset(new_timers, 0, MacTimeout.sizeof*mac_timer_alloc);
      memcpy(new_timers, mac_timers, MacTimeout.sizeof*mac_timer_used);
      MacTimeout* delete_me = mac_timers;
      mac_timers = new_timers;
      delete delete_me;
    }
    private static void delete_timer(inout MacTimeout* t) {     
      if (t.timer) {
        RemoveEventLoopTimer(t.timer);
        DisposeEventLoopTimerUPP(t.upp);
        memset(t, 0, MacTimeout.sizeof);
      }
    }
    private static void do_timer(EventLoopTimerRef timer, void* data)
    {
      for (int i = 0;  i < mac_timer_used;  ++i) {
        MacTimeout* t = mac_timers+i;
        if (t.timer == timer  &&  t.data == data) {
            t.pending = 0;
            t.callback(data);
            if (t.pending==0)
              delete_timer(t);
            break;
        }
      }
      Fl_X.breakMacEventLoop();
    }
  }

  static void add_timeout(double time, Fl_Timeout_Handler cb, void* data=null) {
    version (__APPLE__) {
      // check, if this timer slot exists already
      for (int i = 0;  i < mac_timer_used;  ++i) {
        MacTimeout* t = mac_timers+i;
        // if so, simply change the fire interval
        if (t.callback is cb  &&  t.data is data) {
          SetEventLoopTimerNextFireTime(t.timer, cast(EventTimerInterval)time);
          t.pending = 1;
          return;
        }
      } 
      // no existing timer to use. Create a new one:
      int timer_id = -1;
      // find an empty slot in the timer array
      for (int i = 0;  i < mac_timer_used;  ++i) {
        if ( !mac_timers[i].timer ) {
          timer_id = i;
          break;
        }
      }
      // if there was no empty slot, append a new timer
      if (timer_id == -1) {
        // make space if needed
        if (mac_timer_used == mac_timer_alloc) {
          realloc_timers();
        }
        timer_id = mac_timer_used++;
      }
      // now install a brand new timer
      MacTimeout* t = mac_timers+timer_id;
      EventTimerInterval fireDelay = cast(EventTimerInterval)time;
      EventLoopTimerUPP  timerUPP = NewEventLoopTimerUPP(&do_timer);
      EventLoopTimerRef  timerRef = null;
      OSStatus err = InstallEventLoopTimer(GetMainEventLoop(), fireDelay, 0, timerUPP, data, &timerRef);
      if (err == noErr) {
        t.callback = cb;
        t.data     = data;
        t.timer    = timerRef;
        t.upp      = timerUPP;
        t.pending  = 1;
      } else {
        if (timerRef) 
          RemoveEventLoopTimer(timerRef);
        if (timerUPP)
          DisposeEventLoopTimerUPP(timerUPP);
      }
    }
  }
  static void repeat_timeout(double time, Fl_Timeout_Handler cb, void* data=null) {
    add_timeout(time, cb, data);
  }

  static int has_timeout(Fl_Timeout_Handler cb, void* data=null) {
    version (__APPLE__) {
      for (int i = 0;  i < mac_timer_used;  ++i) {
        MacTimeout* t = mac_timers+i;
        if (t.callback is cb  &&  t.data is data && t.pending) {
          return 1;
        }
      }
    }
    return 0;
  }

  static void remove_timeout(Fl_Timeout_Handler cb, void* data=null) {
    version (__APPLE__) {
      for (int i = 0;  i < mac_timer_used;  ++i) {
        MacTimeout* t = mac_timers+i;
        if (t.callback is cb  && ( t.data is data || !data)) {
          delete_timer(t);
        }
      }
    }
  }
/+=
  static void add_check(Fl_Timeout_Handler, void* = 0);
  static int  has_check(Fl_Timeout_Handler, void* = 0);
  static void remove_check(Fl_Timeout_Handler, void* = 0);
  static void add_fd(int fd, int when, void (*cb)(int,void*),void* =0);
  static void add_fd(int fd, void (*cb)(int, void*), void* = 0);
  static void remove_fd(int, int when);
  static void remove_fd(int);
  static void add_idle(void (*cb)(void*), void* = 0);
  static int  has_idle(void (*cb)(void*), void* = 0);
  static void remove_idle(void (*cb)(void*), void* = 0);
=+/
  static int damage() {return damage_;}

  static void redraw() {
    for (Fl_X i = Fl_X.first; i; i = i.next) i.w.redraw();
  }

  static void flush() {
    if (damage()) {
      damage_ = 0;
      for (Fl_X i = Fl_X.first; i; i = i.next) {
        if (i.wait_for_expose) {damage_ = 1; continue;}
        Fl_Window wi = i.w;
        if (!wi.visible_r()) continue;
        if (wi.damage()) {i.flush(); wi.clear_damage();}
        // destroy damage regions for windows that don't use them:
        if (i.region) {XDestroyRegion(i.region); i.region = null;}
      }
    }
    version (WIN32) {
      GdiFlush();
    } else version (__APPLE__) {
      if (fl_gc)
        CGContextFlush(fl_gc);
    } else {
      if (fl_display) XFlush(fl_display);
    }
  }
  static void empty(char *a, ...) { } /+=== ===+/
  static void function(char*, ...) warning = &empty;
  static void function(char*, ...) error = &empty;
  static void function(char*, ...) fatal = &empty;

  static Fl_Window first_window() {
    Fl_X i = Fl_X.first;
    return i ? i.w : null;
  }

  static void first_window(Fl_Window window) {
    if (!window || !window.shown()) return;
    fl_find(fl_xid(window));
  }

  static Fl_Window next_window(Fl_Window window) {
    Fl_X i = Fl_X.i(window).next;
    return i ? i.w : null;
  }

  static Fl_Window  modal() {return modal_;}
  static Fl_Window  grab() {return grab_;}
/+=
  static void grab(Fl_Window );
=+/
  // event information:
  static int event()		{return e_number;}
  static int event_x()	{return e_x;}
  static int event_y()	{return e_y;}
  static int event_x_root()	{return e_x_root;}
  static int event_y_root()	{return e_y_root;}
  static int event_dx()	{return e_dx;}
  static int event_dy()	{return e_dy;}
/+=
  static void get_mouse(int &,int &);
=+/
  static int event_clicks()	{return e_clicks;}
  static void event_clicks(int i) {e_clicks = i;}
  static int event_is_click()	{return e_is_click;}
  static void event_is_click(int i) {e_is_click = i;} // only 0 works!
  static int event_button()	{return e_keysym-FL_Button;}
  static int event_state()	{return e_state;}
  static int event_state(int i) {return e_state&i;}
  static int event_key()	{return e_keysym;}
  static int event_original_key(){return e_original_keysym;}
/+=
  static int event_key(int);
  static int get_key(int);
=+/
  static char* event_text() {return e_text;}
  static int event_length() {return e_length;}
/+=
  static int compose(int &del);
=+/
  static void compose_reset() {compose_state = 0;}

  static int event_inside(int xx,int yy,int ww,int hh) {
    int mx = e_x - xx;
    int my = e_y - yy;
    return (mx >= 0 && mx < ww && my >= 0 && my < hh);
  }

  static int event_inside(Fl_Widget o) {
    int mx = e_x - o.x();
    int my = e_y - o.y();
    return (mx >= 0 && mx < o.w() && my >= 0 && my < o.h());
  }

  static int test_shortcut(int shortcut) {
    if (!shortcut) return 0;
   
    int v = shortcut & 0xffff;
    // most X11 use MSWindows Latin-1 if set to Western encoding, so 0x80 to 0xa0 are defined
    if (v > 32 && v < 0x7f || v >= 0x80 && v <= 0xff) {
      if (isupper(v)) {
        shortcut |= FL_SHIFT;
      }
    }
   
    int shift = Fl.event_state();
    // see if any required shift flags are off:
    if ((shortcut&shift) != (shortcut&0x7fff0000)) return 0;
    // record shift flags that are wrong:
    int mismatch = (shortcut^shift)&0x7fff0000;
    // these three must always be correct:
    if (mismatch&(FL_META|FL_ALT|FL_CTRL)) return 0;
    
    int key = shortcut & 0xffff;
   
    // if shift is also correct, check for exactly equal keysyms:
    if (!(mismatch&(FL_SHIFT)) && key == Fl.event_key()) return 1;
   
    // try matching ascii, ignore shift:
    if (key == event_text()[0]) return 1;
   
    // kludge so that Ctrl+'_' works (as opposed to Ctrl+'^_'):
    if ((shift&FL_CTRL) && key >= 0x3f && key <= 0x5F
        && event_text()[0]==(key^0x40)) return 1;
    return 0;
  }

  // event destinations:
  static int handle(int e, Fl_Window  window)
  {
    e_number = e;
    if (fl_local_grab) return fl_local_grab(e);
  
    Fl_Widget  wi = window;
  
    switch (e) {
    case FL_CLOSE:
      if (grab() || modal() && window != modal()) return 0;
      wi.do_callback();
      return 1;
  
    case FL_SHOW:
      wi.show(); // this calls Fl_Widget.show(), not Fl_Window.show()
      return 1;
  
    case FL_HIDE:
      wi.hide(); // this calls Fl_Widget.hide(), not Fl_Window.hide()
      return 1;

    case FL_PUSH:
      if (grab()) wi = grab();
      else if (modal() && !(wi is modal())) return 0;
      pushed_ = wi;
      Fl_Tooltip.current(wi);
      if (send(e, wi, window)) return 1;
      // raise windows that are clicked on:
      window.show();
      return 1;
/+==== DND handling
    case FL_DND_ENTER:
    case FL_DND_DRAG:
      dnd_flag = 1;
      break;
  
    case FL_DND_LEAVE:
      dnd_flag = 1;
      belowmouse(0);
      dnd_flag = 0;
      return 1;
  
    case FL_DND_RELEASE:
      wi = belowmouse();
      break;
====+/  
    case FL_MOVE:
    case FL_DRAG:
      fl_xmousewin = window; // this should already be set, but just in case.
      if (pushed()) {
        wi = pushed();
        if (grab()) wi = grab();
        e_number = e = FL_DRAG;
        break;
      }
      if (modal() && !(wi is modal())) wi = null;
      if (grab()) wi = grab();
      {Fl_Widget pbm = belowmouse();
      int ret = (wi && send(e, wi, window));
      if (!(pbm is belowmouse())) {
        Fl_Tooltip.enter(belowmouse());
      }
      return ret;}
  
    case FL_RELEASE: {
  //    printf("FL_RELEASE: window=%p, pushed() = %p, grab() = %p, modal() = %p\n",
  //           window, pushed(), grab(), modal());
  
      if (grab()) {
        wi = grab();
        pushed_ = null; // must be zero before callback is done!
      } else if (pushed()) {
        wi = pushed();
        pushed_ = null; // must be zero before callback is done!
      } else if (modal() && !(wi is modal())) return 0;
      int r = send(e, wi, window);
      fl_fix_focus();
      return r;}

    case FL_UNFOCUS:
      window = null;
    case FL_FOCUS:
      fl_xfocus = window;
      fl_fix_focus();
      return 1;
  
    case FL_KEYBOARD:
  
      Fl_Tooltip.enter(null);
  
      fl_xfocus = window; // this should not happen!  But maybe it does:
  
      // Try it as keystroke, sending it to focus and all parents:
      for (wi = grab() ? grab() : focus(); wi; wi = wi.parent())
        if (send(FL_KEYBOARD, wi, window)) return 1;
  
      // recursive call to try shortcut:
      if (handle(FL_SHORTCUT, window)) return 1;
  
      // and then try a shortcut with the case of the text swapped, by
      // changing the text and falling through to FL_SHORTCUT case:
      {ubyte* c = cast(ubyte*)event_text(); // cast away const
      if (!isalpha(*c)) return 0;
      *c = isupper(*c) ? tolower(*c) : toupper(*c);}
      e_number = e = FL_SHORTCUT;
  
    case FL_SHORTCUT:
      if (grab()) {wi = grab(); break;} // send it to grab window
  
      // Try it as shortcut, sending to mouse widget and all parents:
      wi = belowmouse(); if (!wi) {wi = modal(); if (!wi) wi = window;}
      for (; wi; wi = wi.parent()) if (send(FL_SHORTCUT, wi, window)) return 1;
  
      // try using add_handle() functions:
      if (send_handlers(FL_SHORTCUT)) return 1;
  
      // make Escape key close windows:
      if (event_key()==FL_Escape) {
        wi = modal(); if (!wi) wi = window;
        wi.do_callback();
        return 1;
      }
  
      return 0;

    case FL_ENTER:
      fl_xmousewin = window;
      fl_fix_focus();
      Fl_Tooltip.enter(belowmouse());
      return 1;
  
    case FL_LEAVE:
      if (!pushed_) {
        belowmouse(null);
        Fl_Tooltip.enter(null);
      }
      if (window is fl_xmousewin) {fl_xmousewin = null; fl_fix_focus();}
      return 1;
  
    case FL_MOUSEWHEEL:
      fl_xfocus = window; // this should not happen!  But maybe it does:
  
      // Try sending it to the grab and then the window:
      if (grab()) {
        if (send(FL_MOUSEWHEEL, grab(), window)) return 1;
      }
      if (send(FL_MOUSEWHEEL, window, window)) return 1;

    default:
      break;
    }
    if (wi && send(e, wi, window)) {
      dnd_flag = 0;
      return 1;
    }
    dnd_flag = 0;
    return send_handlers(e);
  }
  
  static Fl_Widget  belowmouse() {return belowmouse_;}

  static void belowmouse(Fl_Widget o) {
    if (grab()) return; // don't do anything while grab is on
    Fl_Widget p = belowmouse_;
    if (!(o is p)) {
      belowmouse_ = o;
      int old_event = e_number;
      e_number = dnd_flag ? FL_DND_LEAVE : FL_LEAVE;
      for (; p && !p.contains(o); p = p.parent()) {
        p.handle(e_number);
      }
      e_number = old_event;
    }
  }

  static Fl_Widget pushed() {return pushed_;}
  static void pushed(Fl_Widget o) { pushed_ = o; }
  static Fl_Widget focus() {return focus_;}

  static void focus(Fl_Widget o) {
    if (o && !o.visible_focus()) return;
    if (grab()) return; // don't do anything while grab is on
    Fl_Widget p = focus_;
    if (!(o is p)) {
      Fl.compose_reset();
      focus_ = o;
      // make sure that fl_xfocus is set to the top level window
      // of this widget, or fl_fix_focus will clear our focus again
      if (o) {
        Fl_Window win = null, w1 = o.window();
        while (w1) { win=w1; w1=win.window(); }
        if (win) fl_xfocus = win;
      }
      // take focus from the old focused window
      fl_oldfocus = null;
      int old_event = e_number;
      e_number = FL_UNFOCUS;
      for (; p; p = p.parent()) {
        p.handle(FL_UNFOCUS);
        fl_oldfocus = p;
      }
      e_number = old_event;
    }
  }
/+=
  static void add_handler(int (*h)(int));
  static void remove_handler(int (*h)(int));

  // cut/paste:
  static void copy(char* stuff, int len, int clipboard = 0);
  static void paste(Fl_Widget  receiver, int clipboard /*=0*/);
  static int dnd();
=+/
  // These are for back-compatability only:
  static Fl_Widget selection_owner() {return selection_owner_;}
  static void selection_owner(Fl_Widget owner) {selection_owner_ = owner;}
/+=
  static void selection(Fl_Widget  owner, char*, int len);
  static void paste(Fl_Widget  receiver);
=+/
  // screen size:
  version (WIN32) {
    static int x();
    static int y();
    static int w();
    static int h();
  } else version (__APPLE__) {
    static int x() {
      BitMap r;
      GetQDGlobalsScreenBits(&r);
      return r.bounds.left;
    }
    static int y() {
      BitMap r;
      GetQDGlobalsScreenBits(&r);
      return r.bounds.top + 20; // \todo 20 pixel menu bar?
    }
    static int w() {
      BitMap r;
      GetQDGlobalsScreenBits(&r);
      return r.bounds.right - r.bounds.left;
    }
    static int h() {
      BitMap r;
      GetQDGlobalsScreenBits(&r);
      return r.bounds.bottom - r.bounds.top - 20;
    }
  } else {
    static int x() {return 0;}
    static int y() {return 0;}
    static int w();
    static int h();
  } /* WIN32 || __APPLE__ */

  // multi-head support:
  private static int num_screens = 0;
  version (__APPLE__) {
    private static XRectangle screens[16];
    private static void screen_init() {
      GDHandle gd;
    
      for (gd = GetDeviceList(), num_screens = 0; gd; gd = GetNextDevice(gd)) {
        GDPtr gp = *gd;
        screens[num_screens].x      = gp.gdRect.left;
        screens[num_screens].y      = gp.gdRect.top;
        screens[num_screens].width  = gp.gdRect.right - gp.gdRect.left;
        screens[num_screens].height = gp.gdRect.bottom - gp.gdRect.top;
    
        num_screens ++;
        if (num_screens >= 16) break;
      }
    }
  }

  static int screen_count();
  static void screen_xywh(out int x, out int y, out int w, out int h) {
    screen_xywh(x, y, w, h, e_x_root, e_y_root);
  }
  static void screen_xywh(out int x, out int y, out int w, out int h, int mx, int my) {
    if (!num_screens) screen_init();
  
    version (WIN32) {
      if (num_screens > 1) {
        int i;
    
        for (i = 0; i < num_screens; i ++) {
          if (mx >= screens[i].left && mx < screens[i].right &&
              my >= screens[i].top && my < screens[i].bottom) {
            x = screens[i].left;
            y = screens[i].top;
            w = screens[i].right - screens[i].left;
            h = screens[i].bottom - screens[i].top;
            return;
          }
        }
      }
    } else version (__APPLE__) {
      if (num_screens > 1) {
        int i;
    
        for (i = 0; i < num_screens; i ++) {
          if (mx >= screens[i].x &&
              mx < (screens[i].x + screens[i].width) &&
              my >= screens[i].y &&
              my < (screens[i].y + screens[i].height)) {
            x = screens[i].x;
            y = screens[i].y;
            w = screens[i].width;
            h = screens[i].height;
            return;
          }
        }
      }
    } else version (HAVE_XINERAMA) {
      if (num_screens > 1) {
        int i;
    
        for (i = 0; i < num_screens; i ++) {
          if (mx >= screens[i].x_org &&
              mx < (screens[i].x_org + screens[i].width) &&
              my >= screens[i].y_org &&
              my < (screens[i].y_org + screens[i].height)) {
            x = screens[i].x_org;
            y = screens[i].y_org;
            w = screens[i].width;
            h = screens[i].height;
            return;
          }
        }
      }
    } // WIN32
    
    x = Fl.x();
    y = Fl.y();
    w = Fl.w();
    h = Fl.h();
  }

  static void screen_xywh(out int x, out int y, out int w, out int h, int n);

  // color map:
  static void set_color(Fl_Color i, ubyte red, ubyte green, ubyte blue) {
    set_color((i & 255),
          (red<<24)+(green<<16)+(blue<<8));
  }

  static void set_color(Fl_Color i, uint c) {
    if (fl_cmap[i] != c) {
      fl_cmap[i] = c;
    }
  }

  static uint get_color(Fl_Color i) {
    if (i & 0xffffff00) return (i);
    else return fl_cmap[i];
  }
/+=

  static void	get_color(Fl_Color, ubyte&, ubyte&, ubyte&);
  static void	free_color(Fl_Color, int overlay = 0);

  // fonts:
  static char* get_font(Fl_Font);
  static char* get_font_name(Fl_Font, int* attributes = 0);
  static int get_font_sizes(Fl_Font, int*& sizep);
  static void set_font(Fl_Font, char*);
  static void set_font(Fl_Font, Fl_Font);
  static Fl_Font set_fonts(char* = 0);

  // labeltypes:
  static void set_labeltype(Fl_Labeltype,Fl_Label_Draw_F ,Fl_Label_Measure_F );
  static void set_labeltype(Fl_Labeltype, Fl_Labeltype from);
=+/

  // boxtypes:
  static Fl_Box_Draw_F get_boxtype(Fl_Boxtype t) {
    return fl_box_table[t].f;
  }

  static void set_boxtype(Fl_Boxtype t, Fl_Box_Draw_F f,
                        ubyte a, ubyte b, ubyte c, ubyte d) {
    fl_box_table[t].f   = f;
    fl_box_table[t].set = 1;
    fl_box_table[t].dx  = a;
    fl_box_table[t].dy  = b;
    fl_box_table[t].dw  = c;
    fl_box_table[t].dh  = d;
  }

  static void set_boxtype(Fl_Boxtype t, Fl_Boxtype f) {
    fl_box_table[t] = fl_box_table[f];
  }

  static int box_dx(Fl_Boxtype t) {return fl_box_table[t].dx;}
  static int box_dy(Fl_Boxtype t) {return fl_box_table[t].dy;}
  static int box_dw(Fl_Boxtype t) {return fl_box_table[t].dw;}
  static int box_dh(Fl_Boxtype t) {return fl_box_table[t].dh;}
  static int draw_box_active() { return draw_it_active; }

/+=
  // back compatability:
  static void set_abort(void (*f)(char*,...)) {fatal = f;}
=+/
  static void function(Fl_Window ,void*) atclose = &default_atclose;
  static void default_atclose(Fl_Window window, void* v) {
    window.hide();
    Fl_Widget.default_callback(window, v); // put on Fl.read_queue()
  }

/+=
  static void set_atclose(void (*f)(Fl_Window ,void*)) {atclose = f;}
  static int event_shift() {return e_state&FL_SHIFT;}
  static int event_ctrl() {return e_state&FL_CTRL;}
  static int event_alt() {return e_state&FL_ALT;}
  static int event_buttons() {return e_state&0x7f000000;}
  static int event_button1() {return e_state&FL_BUTTON1;}
  static int event_button2() {return e_state&FL_BUTTON2;}
  static int event_button3() {return e_state&FL_BUTTON3;}
  static void set_idle(void (*cb)()) {idle = cb;}
  static void grab(Fl_Window win) {grab(&win);}
  static void release() {grab(0);}
=+/
  // Visible focus methods...
  static void visible_focus(int v) { visible_focus_ = v; }
  static int  visible_focus() { return visible_focus_; }
/+=
  // Drag-n-drop text operation methods...
  static void dnd_text_ops(int v) { dnd_text_ops_ = v; }
  static int  dnd_text_ops() { return dnd_text_ops_; }

  // Multithreading support:
  static void lock();
  static void unlock();
  static void awake(void* message = 0);
  static void* thread_message();

  // Widget deletion:
  static void delete_widget(Fl_Widget  w);
=+/
  static void do_widget_deletion() {
    if (!num_dwidgets) return;
    for (int i = 0; i < num_dwidgets; i ++)
      delete dwidgets[i];
    num_dwidgets = 0;
  }

  static Fl_Widget* widget_watch = null;
  static int num_widget_watch = 0;
  static int max_widget_watch = 0;
/+=
  static void watch_widget_pointer(Fl_Widget   w);
  static void release_widget_pointer(Fl_Widget   w);
  static void clear_widget_pointer(Fl_Widget  w);
=+/
  /+= D translation does not work like this! =+/
  static void clear_widget_pointer(Fl_Widget w) {
    if (!w) return;
    int i;
    for (i=0; i<num_widget_watch; ++i) {
      if (widget_watch[i] && widget_watch[i] is w) {
        widget_watch[i] = null;
      }
    }
  }
}


//
// End of "$Id: Fl.H 5188 2006-06-09 07:48:08Z matt $".
//
/+- This file was imported from C++ using a script
//
// "$Id: Fl.cxx 5379 2006-08-29 11:03:05Z matt $"
//
// Main event handling code for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2006 by Bill Spitzak and others.
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

// warning: the Apple Quartz version still uses some Quickdraw calls,
//          mostly to get around the single active context in QD and 
//          to implement clipping. This should be changed into pure
//          Quartz calls in the near future.

#include <FL/Fl.H>
private import fl.window;
#include <FL/x.H>
private import fl.tooltip;
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
private import fl.flstring;

version (DEBUG) {
#  include <stdio.h>
} // DEBUG

version (WIN32) {
#  include <ole2.h>
void fl_free_fonts(void);
HBRUSH fl_brush_action(int action);
void fl_cleanup_pens(void);
void fl_release_dc(HWND,HDC);
void fl_cleanup_dc_list(void);
} // WIN32

//
// Globals...
//

Fl_Widget	 Fl.belowmouse_,
		*Fl.pushed_,
		*Fl.focus_,
		*Fl.selection_owner_;
int		Fl.damage_,
		Fl.e_number,
		Fl.e_x,
		Fl.e_y,
		Fl.e_x_root,
		Fl.e_y_root,
		Fl.e_dx,
		Fl.e_dy,
		Fl.e_state,
		Fl.e_clicks,
		Fl.e_is_click,
		Fl.e_keysym,
                Fl.e_original_keysym;
char		*Fl.e_text = (char *)"";
int		Fl.e_length;

=+/
Fl_Window  fl_xfocus;	// which window X thinks has focus
Fl_Window  fl_xmousewin;// which window X thinks has FL_ENTER
/+=
Fl_Window  Fl.grab_;	// most recent Fl.grab()
Fl_Window  Fl.modal_;	// topmost modal() window



//
//
// timer support
//

version (WIN32) {

/// implementation in Fl_win32.cxx

} else version (__APPLE__) {

/// implementation in Fl_mac.cxx

} else {

//
// X11 timers
//


////////////////////////////////////////////////////////////////
// Timeouts are stored in a sorted list, so only the first one needs
// to be checked to see if any should be called.
  
struct Timeout {
  double time;
  void (*cb)(void*);
  void* arg;
  Timeout* next;
};
static Timeout* first_timeout, *free_timeout;
static int first_timeout_count, free_timeout_count;

#include <sys/time.h>

// I avoid the overhead of getting the current time when we have no
// timeouts by setting this flag instead of getting the time.
// In this case calling elapse_timeouts() does nothing, but records
// the current time, and the next call will actualy elapse time.
static char reset_clock = 1;

static void elapse_timeouts() {
  static struct timeval prevclock;
  struct timeval newclock;
  gettimeofday(&newclock, NULL);
  double elapsed = newclock.tv_sec - prevclock.tv_sec +
    (newclock.tv_usec - prevclock.tv_usec)/1000000.0;
  prevclock.tv_sec = newclock.tv_sec;
  prevclock.tv_usec = newclock.tv_usec;
  if (reset_clock) {
    reset_clock = 0;
  } else if (elapsed > 0) {
    for (Timeout* t = first_timeout; t; t = t.next) t.time -= elapsed;
  }
}

// Continuously-adjusted error value, this is a number <= 0 for how late
// we were at calling the last timeout. This appears to make repeat_timeout
// very accurate even when processing takes a significant portion of the
// time interval:
static double missed_timeout_by;

void Fl.add_timeout(double time, Fl_Timeout_Handler cb, void *argp) {
  elapse_timeouts();
  repeat_timeout(time, cb, argp);
}

void Fl.repeat_timeout(double time, Fl_Timeout_Handler cb, void *argp) {
  time += missed_timeout_by; if (time < -.05) time = 0;
  Timeout* t = free_timeout;
  if (t) {
      free_timeout = t.next;
      --free_timeout_count;
  } else {
      t = new Timeout;
  }
  t.time = time;
  t.cb = cb;
  t.arg = argp;
  // insert-sort the new timeout:
  Timeout** p = &first_timeout; 
  while (*p && (*p)->time <= time) p = &((*p)->next);
  t.next = *p;
  *p = t;
}

int Fl.has_timeout(Fl_Timeout_Handler cb, void *argp) {
  for (Timeout* t = first_timeout; t; t = t.next)
    if (t.cb == cb && t.arg == argp) return 1;
  return 0;
}

void Fl.remove_timeout(Fl_Timeout_Handler cb, void *argp) {
  // This version removes all matching timeouts, not just the first one.
  // This may change in the future.
  for (Timeout** p = &first_timeout; *p;) {
    Timeout* t = *p;
    if (t.cb == cb && (t.arg == argp || !argp)) {
      *p = t.next;
      t.next = free_timeout;
      free_timeout = t;
    } else {
      p = &(t.next);
    }
  }
}

}

////////////////////////////////////////////////////////////////
// Checks are just stored in a list. They are called in the reverse
// order that they were added (this may change in the future).
// This is a bit messy because I want to allow checks to be added,
// removed, and have wait() called from inside them, to do this
// next_check points at the next unprocessed one for the outermost
// call to Fl.wait().

struct Check {
  void (*cb)(void*);
  void* arg;
  Check* next;
};
static Check *first_check, *next_check, *free_check;

void Fl.add_check(Fl_Timeout_Handler cb, void *argp) {
  Check* t = free_check;
  if (t) free_check = t.next;
  else t = new Check;
  t.cb = cb;
  t.arg = argp;
  t.next = first_check;
  if (next_check == first_check) next_check = t;
  first_check = t;
}

void Fl.remove_check(Fl_Timeout_Handler cb, void *argp) {
  for (Check** p = &first_check; *p;) {
    Check* t = *p;
    if (t.cb == cb && t.arg == argp) {
      if (next_check == t) next_check = t.next;
      *p = t.next;
      t.next = free_check;
      free_check = t;
    } else {
      p = &(t.next);
    }
  }
}

#if !defined(__APPLE__)
static void run_checks()
{
  // checks are a bit messy so that add/remove and wait may be called
  // from inside them without causing an infinite loop:
  if (next_check == first_check) {
    while (next_check) {
      Check* checkp = next_check;
      next_check = checkp.next;
      (checkp.cb)(checkp.arg);
    }
    next_check = first_check;
  }
}
} // !__APPLE__


////////////////////////////////////////////////////////////////
// wait/run/check/ready:

void (*Fl.idle)(); // see Fl_add_idle.cxx for the add/remove functions

extern int fl_ready(); // in Fl_<platform>.cxx

}


version (WIN32) {
class Fl_Win32_At_Exit {
public:
  Fl_Win32_At_Exit() { }
  ~Fl_Win32_At_Exit() {
    fl_free_fonts();        // do some WIN32 cleanup
    fl_cleanup_pens();
    OleUninitialize();
    fl_brush_action(1);
    fl_cleanup_dc_list();
  }
};
static Fl_Win32_At_Exit win32_at_exit;
}



int Fl.wait() {
  if (!Fl_X.first) return 0;
  wait(FOREVER);
  return Fl_X.first != 0; // return true if there is a window
}

int Fl.check() {
  wait(0.0);
  return Fl_X.first != 0; // return true if there is a window
}

int Fl.ready() {
#if ! defined( WIN32 )  &&  ! defined(__APPLE__)
  if (first_timeout) {
    elapse_timeouts();
    if (first_timeout.time <= 0) return 1;
  } else {
    reset_clock = 1;
  }
}
  return fl_ready();
}

////////////////////////////////////////////////////////////////
// Window list management:

Fl_X  Fl_X.first;
=+/

Fl_Window fl_find(WindowRef xid) {
  Fl_X window;
  for (Fl_X pp = Fl_X.first; pp; pp = window.next) {
    window = pp;
    bool same;
    version (__APPLE__) {
      same =  (window.xid is xid && !window.w.window());
    } else {
      same = (window.xid is xid);
    } // __APPLE__
    if (same) {
      if (!(window is Fl_X.first) && !Fl.modal()) {
	// make this window be first to speed up searches
	// this is not done if modal is true to avoid messing up modal stack
	pp = window.next;
	window.next = Fl_X.first;
	Fl_X.first = window;
      }
      return window.w;
    }
  }
  return null;
}

////////////////////////////////////////////////////////////////
// Event handlers:

struct handler_link {
  int function(int) handle;
  handler_link *next;
};

static handler_link* handlers = null;
/+=
void Fl.add_handler(int (*ha)(int)) {
  handler_link *l = new handler_link;
  l.handle = ha;
  l.next = handlers;
  handlers = l;
}

void Fl.remove_handler(int (*ha)(int)) {
  handler_link *l, *p;

  // Search for the handler in the list...
  for (l = handlers, p = 0; l && l.handle != ha; p = l, l = l.next);

  if (l) {
    // Found it, so remove it from the list...
    if (p) p.next = l.next;
    else handlers = l.next;

    // And free the record...
    delete l;
  }
}
=+/
int function(int) fl_local_grab = null; // used by fl_dnd.cxx

static int send_handlers(int e) {
  for (handler_link *hl = handlers; hl; hl = hl.next)
    if (hl.handle(e)) return 1;
  return 0;
}

////////////////////////////////////////////////////////////////

Fl_Widget fl_oldfocus; // kludge for Fl_Group...
static char dnd_flag = 0; // make 'belowmouse' send DND_LEAVE instead of LEAVE

/+=

// Update modal(), focus() and other state according to system state,
// and send FL_ENTER, FL_LEAVE, FL_FOCUS, and/or FL_UNFOCUS events.
// This is the only function that produces these events in response
// to system activity.
// This is called whenever a window is added or hidden, and whenever
// X says the focus or mouse window have changed.
=+/

void fl_fix_focus() {
  if (Fl.grab()) return; // don't do anything while grab is on.

  // set focus based on Fl.modal() and fl_xfocus
  Fl_Widget w = fl_xfocus;
  if (w) {
    int saved = Fl.e_keysym;
    if (Fl.e_keysym < (FL_Button + FL_LEFT_MOUSE) ||
        Fl.e_keysym > (FL_Button + FL_RIGHT_MOUSE))
      Fl.e_keysym = 0; // make sure widgets don't think a keystroke moved focus
    while (w.parent()) w = w.parent();
    if (Fl.modal()) w = Fl.modal();
    if (!w.contains(Fl.focus()))
      if (!w.take_focus()) Fl.focus(w);
    Fl.e_keysym = saved;
  } else
    Fl.focus(null);

// MRS: Originally we checked the button state, but a user reported that it
//      broke click-to-focus in FLWM?!?
//  if (!(Fl.event_state() & 0x7f00000 /*FL_BUTTONS*/)) {
  if (!Fl.pushed()) {
    // set belowmouse based on Fl.modal() and fl_xmousewin:
    w = fl_xmousewin;
    if (w) {
      if (Fl.modal()) w = Fl.modal();
      if (!w.contains(Fl.belowmouse())) {
        int old_event = Fl.e_number;
	w.handle(Fl.e_number = FL_ENTER);
	Fl.e_number = old_event;
	if (!w.contains(Fl.belowmouse())) Fl.belowmouse(w);
      } else {
	// send a FL_MOVE event so the enter/leave state is up to date
	Fl.e_x = Fl.e_x_root-fl_xmousewin.x();
	Fl.e_y = Fl.e_y_root-fl_xmousewin.y();
        int old_event = Fl.e_number;
	w.handle(Fl.e_number = FL_MOVE);
	Fl.e_number = old_event;
      }
    } else {
      Fl.belowmouse(null);
      Fl_Tooltip.enter(null);
    }
  }
}

void fl_throw_focus(Fl_Widget o) {
  if (o.contains(Fl.pushed())) Fl.pushed_ = null;
  version (WIN32) {
  } else {
    if (o.contains(fl_selection_requestor)) fl_selection_requestor = null;
  }
  if (o.contains(Fl.belowmouse())) Fl.belowmouse_ = null;
  if (o.contains(Fl.focus())) Fl.focus_ = null;
  if (o == fl_xfocus) fl_xfocus = null;
  if (o == Fl_Tooltip.current()) Fl_Tooltip.current(null);
  if (o == fl_xmousewin) fl_xmousewin = null;
  Fl_Tooltip.exit(o);
  fl_fix_focus();
}

static int send(int event, Fl_Widget to, Fl_Window window) {
  int dx, dy;
  int old_event = Fl.e_number;
  if (window) {
    dx = window.x();
    dy = window.y();
  } else {
    dx = dy = 0;
  }
  for (Fl_Widget w = to; w; w = w.parent())
    if (w.type()>=FL_WINDOW) {dx -= w.x(); dy -= w.y();}
  int save_x = Fl.e_x; Fl.e_x += dx;
  int save_y = Fl.e_y; Fl.e_y += dy;
  int ret = to.handle(Fl.e_number = event);
  Fl.e_number = old_event;
  Fl.e_y = save_y;
  Fl.e_x = save_x;
  return ret;
}

/+=
////////////////////////////////////////////////////////////////
// Back compatability cut & paste functions for fltk 1.1 only:


void Fl.selection(Fl_Widget  owner, char* text, int len) {
  selection_owner_ = &owner;
  Fl.copy(text, len, 0);
}

void Fl.paste(Fl_Widget  receiver) {
  Fl.paste(receiver, 0);
}
=+/

static int num_dwidgets = 0, alloc_dwidgets = 0;
static Fl_Widget* dwidgets = null;

/+=
void
Fl.delete_widget(Fl_Widget  wi) {
  if (!wi) return;

  if (num_dwidgets >= alloc_dwidgets) {
    Fl_Widget	 *temp;

    temp = new Fl_Widget  [alloc_dwidgets + 10];
    if (alloc_dwidgets) {
      memcpy(temp, dwidgets, alloc_dwidgets * sizeof(Fl_Widget  ));
      delete[] dwidgets;
    }

    dwidgets = temp;
    alloc_dwidgets += 10;
  }

  dwidgets[num_dwidgets] = wi;
  num_dwidgets ++;
}

void Fl.watch_widget_pointer(Fl_Widget   w) 
{
  Fl_Widget  *wp = &w;
  int i;
  for (i=0; i<num_widget_watch; ++i) {
    if (widget_watch[i]==wp) return;
  }
  for (i=0; i<num_widget_watch; ++i) {
    if (widget_watch[i]==0L) {
      widget_watch[i] = wp;
      return;
    }
  }
  if (num_widget_watch==max_widget_watch) {
    max_widget_watch += 8;
    widget_watch = (Fl_Widget **)realloc(widget_watch, sizeof(Fl_Widget *)*max_widget_watch);
  }
  widget_watch[num_widget_watch++] = wp;
}

void Fl.release_widget_pointer(Fl_Widget   w)
{
  Fl_Widget  *wp = &w;
  int i;
  for (i=0; i<num_widget_watch; ++i) {
    if (widget_watch[i]==wp) {
      widget_watch[i] = 0L;
      return;
    }
  }
}



//
// End of "$Id: Fl.cxx 5379 2006-08-29 11:03:05Z matt $".
//
    End of automatic import -+/
