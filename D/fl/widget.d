//
// "$Id: widget.d 4421 2005-07-15 09:34:53Z matt $"
//
// Widget header file for the Fast Light Tool Kit (FLTK).
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

module fl.widget;

public import fl.enumerations;

private import fl.x;
private import fl.fl;
private import fl.group;
private import fl.window;
private import fl.image;
private import fl.draw;
private import fl.tooltip;
private import fl.labeltype;

typedef void function(Fl_Widget, void*) Fl_Callback;
typedef Fl_Callback* Fl_Callback_p;
typedef void function(Fl_Widget) Fl_Callback0;
typedef void function(Fl_Widget, int) Fl_Callback1;

struct Fl_Label {
  char[] value;
  Fl_Image image;
  Fl_Image deimage;
  Fl_Labeltype type;
  Fl_Font font;
  ubyte size;
  Fl_Color color;

  // draw label with arbitrary alignment in arbitrary box:
  void draw(int X, int Y, int W, int H, Fl_Align aln) {
    if (!value && !image) return;
    table[type](*this, X, Y, W, H, aln);
  }
  
  void measure(inout int W, inout int H) {
    if (!value && !image) {
      W = H = 0;
      return;
    }
  
    Fl_Label_Measure_F f = measure_lut[type]; 
    if (!f) f = &fl_normal_measure;
    f(*this, W, H);
  }

};

class Fl_Widget {
/+-
  friend class Fl_Group;
-+/
  Fl_Group parent_;
  Fl_Callback callback_;
  void* user_data_;
  short x_, y_, w_, h_;
  Fl_Label label_;
  int flags_;
  Fl_Color color_;
  Fl_Color color2_;
  Fl_Type type_;
  Fl_Damage damage_;
  Fl_Boxtype box_;
  Fl_Align align_;
  Fl_When when_;

  char[] tooltip_;

public:

  this(int X, int Y, int W, int H, char[] L=null) {
    x_ = X; y_ = Y; w_ = W; h_ = H;
  
    label_.value = L;
    label_.image = null;
    label_.deimage = null;
    label_.type	 = FL_NORMAL_LABEL;
    label_.font	 = FL_HELVETICA;
    label_.size	 = FL_NORMAL_SIZE;
    label_.color = FL_FOREGROUND_COLOR;
    tooltip_     = null;
    callback_	 = &default_callback;
    user_data_ 	 = null;
    type_	 = 0;
    flags_	 = VISIBLE_FOCUS;
    damage_	 = 0;
    box_	 = FL_NO_BOX;
    color_	 = FL_GRAY;
    color2_	 = FL_GRAY;
    align_	 = FL_ALIGN_CENTER;
    when_	 = FL_WHEN_RELEASE;
  
    parent_ = null;
    if (Fl_Group.current()) Fl_Group.current().add(this);
  }
  
  void x(int v) {
    x_ = v;
  }

  void y(int v) {
    y_ = v;
  }

  void w(int v) {
    w_ = v;
  }

  void h(int v) {
    h_ = v;
  }

  public int flags() {
    return flags_;
  }

  void set_flag(int c) {
    flags_ |= c;
  }

  void clear_flag(int c) {
    flags_ &= ~c;
  }

  enum {INACTIVE=1, INVISIBLE=2, OUTPUT=4, SHORTCUT_LABEL=64,
        CHANGED=128, VISIBLE_FOCUS=512, COPIED_LABEL = 1024};

  void draw_box() {
    Fl_Boxtype t = box_;
    if (!t) return;
    draw_box(t, x_, y_, w_, h_, color_);
  }
  
  void draw_box(Fl_Boxtype b, Fl_Color c) {
    draw_box(b, x_, y_, w_, h_, c);
  }
  
  void draw_box(Fl_Boxtype b, int X, int Y, int W, int H, Fl_Color c) {
    draw_it_active = active_r();
    fl_box_table[b].f(X, Y, W, H, c);
    draw_it_active = 1;
  }

  void draw_focus() {
    draw_focus(box(),x(),y(),w(),h());
  }

  // draw a focus box for the widget...
  void draw_focus(Fl_Boxtype B, int X, int Y, int W, int H) {
    if (!Fl.visible_focus()) return;
    switch (B) {
      case FL_DOWN_BOX:
      case FL_DOWN_FRAME:
      case FL_THIN_DOWN_BOX:
      case FL_THIN_DOWN_FRAME:
        X ++;
        Y ++;
      default:
        break;
    }
  
    fl_color(fl_contrast(FL_BLACK, color()));
  
  /+  #if defined(WIN32) || defined(__APPLE_QD__)
    // Windows 95/98/ME do not implement the dotted line style, so draw
    // every other pixel around the focus area...
    //
    // Also, QuickDraw (MacOS) does not support line styles specifically,
    // and the hack we use in fl_line_style() will not draw horizontal lines
    // on odd-numbered rows...
    int i, xx, yy;
  
    X += Fl::box_dx(B);
    Y += Fl::box_dy(B);
    W -= Fl::box_dw(B) + 2;
    H -= Fl::box_dh(B) + 2;
  
    for (xx = 0, i = 1; xx < W; xx ++, i ++) if (i & 1) fl_point(X + xx, Y);
    for (yy = 0; yy < H; yy ++, i ++) if (i & 1) fl_point(X + W, Y + yy);
    for (xx = W; xx > 0; xx --, i ++) if (i & 1) fl_point(X + xx, Y + H);
    for (yy = H; yy > 0; yy --, i ++) if (i & 1) fl_point(X, Y + yy);
  #else +/
    fl_line_style(FL_DOT);
    fl_rect(X + Fl.box_dx(B), Y + Fl.box_dy(B),
            W - Fl.box_dw(B) - 1, H - Fl.box_dh(B) - 1);
    fl_line_style(FL_SOLID);
  /+ #endif // WIN32 +/
  }

  void draw_label() {
    int X = x_+Fl.box_dx(box());
    int W = w_-Fl.box_dw(box());
    if (W > 11 && alignment()&(FL_ALIGN_LEFT|FL_ALIGN_RIGHT)) {X += 3; W -= 6;}
    draw_label(X, y_+Fl.box_dy(box()), W, h_-Fl.box_dh(box()));
  }

  void draw_label(int X, int Y, int W, int H) {
    draw_label(X,Y,W,H,alignment());
  }

public:
  // Destruction does not remove from any parent group!  And groups when
  // destroyed destroy all their children.  This is convienent and fast.
  // However, it is only legal to destroy a "root" such as an Fl_Window,
  // and automatic destructors may be called.
  ~this() {
    Fl.clear_widget_pointer(this);
    /+? if (flags() & COPIED_LABEL) free((void *)(label_.value)); ?+/
    parent_ = null; // Don't throw focus to a parent widget.
    fl_throw_focus(this);
  }

  void draw() {
    /+ assert(0); +/
  }

  int handle(Fl_Event event) {
    return 0;
  }

  Fl_Group parent() { 
    return parent_; 
  }

  void parent(Fl_Group p) { 
    parent_ = p; 
  }

  Fl_Type type() { 
    return type_; 
  }

  void type(Fl_Type t) { 
    type_ = t; 
  }

  int x() { 
    return x_; 
  }

  int y() { 
    return y_; 
  }

  int w() { 
    return w_; 
  }

  int h() { 
    return h_; 
  }

  void resize(int X, int Y, int W, int H) {
    x_ = X; y_ = Y; w_ = W; h_ = H;
  }

  // this is useful for parent widgets to call to resize children:
  int damage_resize(int X, int Y, int W, int H) {
    if (x() == X && y() == Y && w() == W && h() == H) 
      return 0;
    resize(X, Y, W, H);
    redraw();
    return 1;
  }

  void position(int X, int Y) {
    resize(X,Y,w_,h_);
  }

  void size(int W, int H) {
    resize(x_,y_,W,H);
  }

  Fl_Align alignment() {
    return align_;
  }

  void alignment(Fl_Align a) {
    align_ = a;
  }

  Fl_Boxtype box() {
    return box_;
  }

  void box(Fl_Boxtype a) {
    box_ = a;
  }

  Fl_Color color() {
    return color_;
  }

  void color(Fl_Color a) {
    color_ = a;
  }

  Fl_Color selection_color() {
    return color2_; 
  }

  void selection_color(Fl_Color a) {
    color2_ = a;
  }

  void color(Fl_Color a, Fl_Color b) {
    color_=a; 
    color2_=b;
  }

  char[] label() {
    return label_.value;
  }

  void label(char[] a) {
    if (flags() & COPIED_LABEL) {
      // reassigning a copied label remains the same copied label
      if (label_.value == a)
        return;
      /+? "D" should do this: free((void *)(label_.value)); ?+/
      clear_flag(COPIED_LABEL);
    }
    label_.value=a.dup; /+? I believe we need this? ?+/
    redraw_label();
  }

  void copy_label(char[] a) {
    /+? if (flags() & COPIED_LABEL) free((void *)(label_.value)); ?+/
    if (a) {
      set_flag(COPIED_LABEL);
      label_.value = a.dup;
    } else {
      clear_flag(COPIED_LABEL);
      label_.value = null;
    }
    redraw_label();
  }

  void label(Fl_Labeltype a, char[] b) {
    label_.type = a; 
    label_.value = b;
  }

  Fl_Labeltype labeltype() {
    return label_.type;
  }

  void labeltype(Fl_Labeltype a) {
    label_.type = a;
  }
  
  Fl_Color labelcolor() {
    return label_.color;
  }

  void labelcolor(Fl_Color a) {
    label_.color=a;
  }

  Fl_Font labelfont() {
    return label_.font;
  }

  void labelfont(Fl_Font a) {
    label_.font = a;
  }

  ubyte labelsize() {
    return label_.size;
  }

  void labelsize(ubyte a) {
    label_.size = a;
  }

  Fl_Image image() {
    return label_.image;
  }

  void image(Fl_Image a) {
    label_.image=a;
  }

  Fl_Image deimage() {
    return label_.deimage;
  }

  void deimage(Fl_Image a) {
    label_.deimage=a;
  }

  char[] tooltip() {
    return tooltip_;
  }

  void tooltip(char[] tt) {
    static char beenhere = 0;
    if (!beenhere) {
      beenhere          = 1;
      Fl_Tooltip.enter = &Fl_Tooltip.enter_;
      Fl_Tooltip.exit  = &Fl_Tooltip.exit_;
    }
    tooltip_ = tt;
  }

  Fl_Callback callback() {
    return callback_;
  }

  void callback(Fl_Callback c, void* p) {
    callback_ = c; 
    user_data_ = p;
  }

  void callback(Fl_Callback c) {
    callback_ = c;
  }

  void callback(Fl_Callback0 c) {
    callback_ = cast(Fl_Callback)c;
  }

  void callback(Fl_Callback1 c, int p=0) {
    callback_ = cast(Fl_Callback)c; 
    user_data_ = cast(void*)p;
  }

  void* user_data() {
    return user_data_;
  }

  void user_data(void* v) { 
    user_data_ = v;
  }

  int argument() {
    return cast(int)user_data_;
  }

  void argument(int v) {
    user_data_ = cast(void*)v;
  }

  Fl_When when() {
    return when_;
  }

  void when(Fl_When i) {
    when_ = i;
  }

  int visible() {
    return !(flags_&INVISIBLE);
  }

  int visible_r() {
    for (Fl_Widget o = this; o; o = o.parent())
      if (!o.visible()) return 0;
    return 1;
  }

  void show() {
    if (!visible()) {
      clear_flag(INVISIBLE);
      if (visible_r()) {
        redraw();
        redraw_label();
        handle(FL_SHOW);
        if (inside(Fl.focus())) 
          Fl.focus().take_focus();
      }
    }
  }

  void hide() {
    if (visible_r()) {
      set_flag(INVISIBLE);
      for (Fl_Widget p = parent(); p; p = p.parent())
        if (p.box() || !p.parent()) {
          p.redraw(); 
          break;
      }
      handle(FL_HIDE);
      fl_throw_focus(this);
    } else {
      set_flag(INVISIBLE);
    }
  }

  void set_visible() {
    flags_ &= ~INVISIBLE;
  }

  void clear_visible() {
    flags_ |= INVISIBLE;
  }

  int active() {
    return !(flags_&INACTIVE);
  }
  int active_r() {
    for (Fl_Widget o = this; o; o = o.parent())
      if (!o.active()) return 0;
    return 1;
  }

  void activate() {
    if (!active()) {
      clear_flag(INACTIVE);
      if (active_r()) {
        redraw();
        redraw_label();
        handle(FL_ACTIVATE);
        if (inside(Fl.focus())) Fl.focus().take_focus();
      }
    }
  }
  
  void deactivate() {
    if (active_r()) {
      set_flag(INACTIVE);
      redraw();
      redraw_label();
      handle(FL_DEACTIVATE);
      fl_throw_focus(this);
    } else {
      set_flag(INACTIVE);
    }
  }

  int output() {
    return (flags_&OUTPUT);
  }

  void set_output() {
    flags_ |= OUTPUT;
  }

  void clear_output() {
    flags_ &= ~OUTPUT;
  }

  int takesevents() {
    return !(flags_&(INACTIVE|INVISIBLE|OUTPUT));
  }

  int changed() {
    return flags_&CHANGED;
  }

  void set_changed() {
    flags_ |= CHANGED;
  }

  void clear_changed() {
    flags_ &= ~CHANGED;
  }

  int take_focus() {
    if (!takesevents()) return 0;
    if (!visible_focus()) return 0;
    if (!handle(FL_FOCUS)) return 0; // see if it wants it
    if (contains(Fl.focus())) return 1; // it called Fl::focus for us
    Fl.focus(this);
    return 1;
  }

  void set_visible_focus() { 
    flags_ |= VISIBLE_FOCUS; 
  }

  void clear_visible_focus() { 
    flags_ &= ~VISIBLE_FOCUS; 
  }

  void visible_focus(int v) { 
    if (v) 
      set_visible_focus(); 
    else 
      clear_visible_focus(); 
  }

  int  visible_focus() { 
    return flags_ & VISIBLE_FOCUS; 
  }

private:

  static void default_callback(Fl_Widget o, void* v) {
    Fl.obj_queue[Fl.obj_head++] = o;
    if (Fl.obj_head >= Fl.QUEUE_SIZE) Fl.obj_head = 0;
    if (Fl.obj_head == Fl.obj_tail) {
      Fl.obj_tail++;
      if (Fl.obj_tail >= Fl.QUEUE_SIZE) Fl.obj_tail = 0;
    }
  }

public:

  void do_callback() {
    callback_(this, user_data_); 
    Fl_Callback cb = &default_callback;
    if (callback_ != cb)  
      clear_changed();
  }

  void do_callback(Fl_Widget o, void* arg=null) {
    callback_(o,arg); 
    Fl_Callback cb = &default_callback;
    if (callback_ != cb)  
      clear_changed();
  }

  void do_callback(Fl_Widget o, long arg) {
    callback_(o, cast(void*)arg); 
    Fl_Callback cb = &default_callback;
    if (callback_ != cb)  
      clear_changed();
  }

  int test_shortcut(char[] l) {
    char c = Fl.event_text()[0];
    if (!c || !l) return 0;
    bool mayBeShortcut = false;
    foreach(s; l) {
      if (mayBeShortcut) {
        if (s=='&') {
          mayBeShortcut = false;
        } else {
          if (s==c)
            return 1;
          else
            return 0;
        }
      } else {
        if (s=='&')
          mayBeShortcut = true;
      }
    }
    return 0;
  }
  
  int test_shortcut() {
    if (!(flags()&SHORTCUT_LABEL)) return 0;
    return test_shortcut(label());
  }

  int contains(Fl_Widget o) {
    for (; o; o = o.parent_) 
      if (o == this) return 1;
    return 0;
  }

  int inside(Fl_Widget o) {
    if (!o)
      return 0;
    else 
      return o.contains(this);
  }

  void redraw() {
    damage(FL_DAMAGE_ALL);
  }

  void redraw_label() {
    if (window()) {
      if (box() == FL_NO_BOX) {
        // Widgets with the FL_NO_BOX boxtype need a parent to
        // redraw, since it is responsible for redrawing the
        // background...
        int X = x() > 0 ? x() - 1 : 0;
        int Y = y() > 0 ? y() - 1 : 0;
        window().damage(FL_DAMAGE_ALL, X, Y, w() + 2, h() + 2);
      }
  
      if (alignment() && !(alignment() & FL_ALIGN_INSIDE) && window().shown()) {
        // If the label is not inside the widget, compute the location of
        // the label and redraw the window within that bounding box...
        int W = 0, H = 0;
        label_.measure(W, H);
        W += 5; // Add a little to the size of the label to cover overflow
        H += 5;
  
        if (alignment() & FL_ALIGN_BOTTOM) {
          window().damage(FL_DAMAGE_EXPOSE, x(), y() + h(), w(), H);
        } else if (alignment() & FL_ALIGN_TOP) {
          window().damage(FL_DAMAGE_EXPOSE, x(), y() - H, w(), H);
        } else if (alignment() & FL_ALIGN_LEFT) {
          window().damage(FL_DAMAGE_EXPOSE, x() - W, y(), W, h());
        } else if (alignment() & FL_ALIGN_RIGHT) {
          window().damage(FL_DAMAGE_EXPOSE, x() + w(), y(), W, h());
        } else {
          window().damage(FL_DAMAGE_ALL);
        }
      } else {
        // The label is inside the widget, so just redraw the widget itself...
        damage(FL_DAMAGE_ALL);
      }
    } 
  }

  Fl_Damage damage() {
    return damage_;
  }

  void clear_damage(Fl_Damage c=0) {
    damage_ = c;
  }

  void damage(Fl_Damage fl) {
    if (type() < FL_WINDOW) {
      // damage only the rectangle covered by a child widget:
      damage(fl, x(), y(), w(), h());
    } else {
      // damage entire window by deleting the region:
      Fl_X i = Fl_X.i(cast(Fl_Window)this);
      if (!i) return; // window not mapped, so ignore it
      if (i.region) {
        XDestroyRegion(i.region); 
        i.region = null;
      }
      damage_ |= fl;
      Fl.damage(FL_DAMAGE_CHILD);
    }
  }

  void damage(Fl_Damage fl, int X, int Y, int W, int H) {
    Fl_Widget wi = this;
    // mark all parent widgets between this and window with FL_DAMAGE_CHILD:
    while (wi.type() < FL_WINDOW) {
      wi.damage_ |= fl;
      wi = wi.parent();
      if (!wi) return;
      fl = FL_DAMAGE_CHILD;
    }
    Fl_X i = Fl_X.i(cast(Fl_Window)wi);
    if (!i) return; // window not mapped, so ignore it

    // clip the damage to the window and quit if none:
    if (X < 0) {W += X; X = 0;}
    if (Y < 0) {H += Y; Y = 0;}
    if (W > wi.w()-X) W = wi.w()-X;
    if (H > wi.h()-Y) H = wi.h()-Y;
    if (W <= 0 || H <= 0) return;

    if (!X && !Y && W==wi.w() && H==wi.h()) {
      // if damage covers entire window delete region:
      wi.damage(fl);
      return;
    }
    if (wi.damage()) {
      // if we already have damage we must merge with existing region:
      if (i.region) {
/+
  #ifdef WIN32
        Fl_Region R = XRectangleRegion(X, Y, W, H);
        CombineRgn(i->region, i->region, R, RGN_OR);
        XDestroyRegion(R);
  #elif defined(__APPLE_QD__)
        Fl_Region R = NewRgn();
        SetRectRgn(R, X, Y, X+W, Y+H);
        UnionRgn(R, i->region, i->region);
        DisposeRgn(R);
  #elif defined(__APPLE_QUARTZ__)
+/
        Fl_Region R = NewRgn();
        SetRectRgn(R, X, Y, X+W, Y+H);
        UnionRgn(R, i.region, i.region);
        DisposeRgn(R);
/+
  #else
        XRectangle R;
        R.x = X; R.y = Y; R.width = W; R.height = H;
        XUnionRectWithRegion(&R, i->region, i->region);
  #endif
+/
      }
      wi.damage_ |= fl;
    } else {
      // create a new region:
      if (i.region) XDestroyRegion(i.region);
      i.region = XRectangleRegion(X,Y,W,H);
      wi.damage_ = fl;
    }
    Fl.damage(FL_DAMAGE_CHILD);
  }

  void measure_label(inout int xx, inout int yy) {
    label_.measure(xx,yy);
  }

  void draw_label(int X, int Y, int W, int H, Fl_Align a) { 
    if (flags()&SHORTCUT_LABEL) fl_draw_shortcut = 1;
    Fl_Label l1 = label_;
    if (!active_r()) {
      l1.color = fl_inactive(l1.color);
      if (l1.deimage) l1.image = l1.deimage;
    }
    l1.draw(X,Y,W,H,a);
    fl_draw_shortcut = 0;
  } 

  Fl_Window window() {
    for (Fl_Widget o = parent(); o; o = o.parent())
      if (o.type() >= FL_WINDOW) 
        return cast(Fl_Window)o;
    return null;
  }

  // back compatability only:
  Fl_Color color2() {
    return color2_;
  }

  void color2(Fl_Color a) {
    color2_ = a;
  }

  final void w_show() { Fl_Widget.show(); }
  final void w_hide() { Fl_Widget.hide(); }
}

//
// End of "$Id: widget.d 4421 2005-07-15 09:34:53Z matt $".
//
