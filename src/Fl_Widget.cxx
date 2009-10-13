//
// "$Id$"
//
// Base widget class for the Fast Light Tool Kit (FLTK).
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

#include <FL/Fl.H>
#include <FL3/Widget.h>
#include <FL/Fl_Group.H>
#include <FL/Fl_Tooltip.H>
#include <FL/fl_draw.H>
#include <stdlib.h>
#include "flstring.h"


////////////////////////////////////////////////////////////////
// for compatibility with Forms, all widgets without callbacks are
// inserted into a "queue" when they are activated, and the forms
// compatibility interaction functions (fl_do_events, etc.) will
// read one widget at a time from this queue and return it:

const int QUEUE_SIZE = 20;

static fltk::Widget *obj_queue[QUEUE_SIZE];
static int obj_head, obj_tail;

void fltk::Widget::default_callback(fltk::Widget *o, void * /*v*/) {
#if 0
  // This is necessary for strict forms compatibility but is confusing.
  // Use the parent's callback if this widget does not have one.
  for (fltk::Widget *p = o->parent(); p; p = p->parent())
    if (p->callback() != default_callback) {
      p->do_callback(o,v);
      return;
    }
#endif
  obj_queue[obj_head++] = o;
  if (obj_head >= QUEUE_SIZE) obj_head = 0;
  if (obj_head == obj_tail) {
    obj_tail++;
    if (obj_tail >= QUEUE_SIZE) obj_tail = 0;
  }
}
/**
    All fltk::Widgets that don't have a callback defined use a
    default callback that puts a pointer to the widget in this queue,
    and this method reads the oldest widget out of this queue.
*/
fltk::Widget *fltk::readqueue() {
  if (obj_tail==obj_head) return 0;
  fltk::Widget *o = obj_queue[obj_tail++];
  if (obj_tail >= QUEUE_SIZE) obj_tail = 0;
  return o;
}
    
////////////////////////////////////////////////////////////////

/** Default font size for widgets */
Fl_Fontsize FL_NORMAL_SIZE = 14;

fltk::Widget::Widget(int X, int Y, int W, int H, const char* L) {

  x_ = X; y_ = Y; w_ = W; h_ = H;

  label_.value	 = L;
  label_.image   = 0;
  label_.deimage = 0;
  label_.type	 = FL_NORMAL_LABEL;
  label_.font	 = FL_HELVETICA;
  label_.size	 = FL_NORMAL_SIZE;
  label_.color	 = FL_FOREGROUND_COLOR;
  tooltip_       = 0;
  callback_	 = default_callback;
  user_data_ 	 = 0;
  type_		 = 0;
  flags_	 = VISIBLE_FOCUS;
  damage_	 = 0;
  box_		 = FL_NO_BOX;
  color_	 = FL_GRAY;
  color2_	 = FL_GRAY;
  align_	 = FL_ALIGN_CENTER;
  when_		 = FL_WHEN_RELEASE;

  parent_ = 0;
  if (fltk::Group::current()) fltk::Group::current()->add(this);
}

void fltk::Widget::resize(int X, int Y, int W, int H) {
  x_ = X; y_ = Y; w_ = W; h_ = H;
}

// this is useful for parent widgets to call to resize children:
int fltk::Widget::damage_resize(int X, int Y, int W, int H) {
  if (x() == X && y() == Y && w() == W && h() == H) return 0;
  resize(X, Y, W, H);
  redraw();
  return 1;
}

int fltk::Widget::take_focus() {
  if (!takesevents()) return 0;
  if (!visible_focus()) return 0;
  if (!handle(FL_FOCUS)) return 0; // see if it wants it
  if (contains(fltk::focus())) return 1; // it called fltk::focus for us
  fltk::focus(this);
  return 1;
}

extern void fl_throw_focus(fltk::Widget*); // in Fl_x.cxx

/**
   Destroys the widget, taking care of throwing focus before if any.
   Destruction removes the widget from any parent group! And groups when
   destroyed destroy all their children. This is convenient and fast.
*/
fltk::Widget::~Widget() {
  fltk::clear_widget_pointer(this);
  if (flags() & COPIED_LABEL) free((void *)(label_.value));
  // remove from parent group
  if (parent_) parent_->remove(this);
#ifdef DEBUG_DELETE
  if (parent_) { // this should never happen
    printf("*** fltk::Widget: parent_->remove(this) failed [%p,%p]\n",parent_,this);
  }
#endif // DEBUG_DELETE
  parent_ = 0; // Don't throw focus to a parent widget.
  fl_throw_focus(this);
}

/** Draws a focus box for the widget at the given position and size */
void
fltk::Widget::draw_focus(Fl_Boxtype B, int X, int Y, int W, int H) const {
  if (!fltk::visible_focus()) return;
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

#if defined(USE_X11) || defined(__APPLE_QUARTZ__)
  fl_line_style(FL_DOT);
  fl_rect(X + fltk::box_dx(B), Y + fltk::box_dy(B),
          W - fltk::box_dw(B) - 1, H - fltk::box_dh(B) - 1);
  fl_line_style(FL_SOLID);
#elif defined(WIN32) 
  // Windows 95/98/ME do not implement the dotted line style, so draw
  // every other pixel around the focus area...
  //
  // Also, QuickDraw (MacOS) does not support line styles specifically,
  // and the hack we use in fl_line_style() will not draw horizontal lines
  // on odd-numbered rows...
  int i, xx, yy;

  X += fltk::box_dx(B);
  Y += fltk::box_dy(B);
  W -= fltk::box_dw(B) + 2;
  H -= fltk::box_dh(B) + 2;

  for (xx = 0, i = 1; xx < W; xx ++, i ++) if (i & 1) fl_point(X + xx, Y);
  for (yy = 0; yy < H; yy ++, i ++) if (i & 1) fl_point(X + W, Y + yy);
  for (xx = W; xx > 0; xx --, i ++) if (i & 1) fl_point(X + xx, Y + H);
  for (yy = H; yy > 0; yy --, i ++) if (i & 1) fl_point(X, Y + yy);
#else
# error unsupported platform
#endif // WIN32
}


void fltk::Widget::activate() {
  if (!active()) {
    clear_flag(INACTIVE);
    if (active_r()) {
      redraw();
      redraw_label();
      handle(FL_ACTIVATE);
      if (inside(fltk::focus())) fltk::focus()->take_focus();
    }
  }
}

void fltk::Widget::deactivate() {
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

int fltk::Widget::active_r() const {
  for (const fltk::Widget* o = this; o; o = o->parent())
    if (!o->active()) return 0;
  return 1;
}

void fltk::Widget::show() {
  if (!visible()) {
    clear_flag(INVISIBLE);
    if (visible_r()) {
      redraw();
      redraw_label();
      handle(FL_SHOW);
      if (inside(fltk::focus())) fltk::focus()->take_focus();
    }
  }
}

void fltk::Widget::hide() {
  if (visible_r()) {
    set_flag(INVISIBLE);
    for (fltk::Widget *p = parent(); p; p = p->parent())
      if (p->box() || !p->parent()) {p->redraw(); break;}
    handle(FL_HIDE);
    fl_throw_focus(this);
  } else {
    set_flag(INVISIBLE);
  }
}

int fltk::Widget::visible_r() const {
  for (const fltk::Widget* o = this; o; o = o->parent())
    if (!o->visible()) return 0;
  return 1;
}

// return true if widget is inside (or equal to) this:
// Returns false for null widgets.
int fltk::Widget::contains(const fltk::Widget *o) const {
  for (; o; o = o->parent_) if (o == this) return 1;
  return 0;
}


void
fltk::Widget::label(const char *a) {
  if (flags() & COPIED_LABEL) {
    // reassigning a copied label remains the same copied label
    if (label_.value == a)
      return;
    free((void *)(label_.value));
    clear_flag(COPIED_LABEL);
  }
  label_.value=a;
  redraw_label();
}


void
fltk::Widget::copy_label(const char *a) {
  if (flags() & COPIED_LABEL) free((void *)(label_.value));
  if (a) {
    set_flag(COPIED_LABEL);
    label_.value=strdup(a);
  } else {
    clear_flag(COPIED_LABEL);
    label_.value=(char *)0;
  }
  redraw_label();
}

/** Calls the widget callback.

  Causes a widget to invoke its callback function with arbitrary arguments.

  \param[in] o call the callback with \p o as the widget argument
  \param[in] arg use \p arg as the user data argument
  \see callback()
*/
void
fltk::Widget::do_callback(fltk::Widget* o,void* arg) {
  Fl_Widget_Tracker wp(o);
  callback_(o,arg); 
  if (wp.deleted()) return;
  if (callback_ != default_callback) 
    clear_changed();
}

void fltk::Widget::draw() {
  draw_box();
  draw_label();
}

int fltk::Widget::handle(int event) {
  if (event == FL_ENTER || event == FL_LEAVE) return 1;
  else return 0;
}

//
// End of "$Id$".
//
