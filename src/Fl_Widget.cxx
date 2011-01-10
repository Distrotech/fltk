//
// "$Id$"
//
// Base widget class for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2010 by Bill Spitzak and others.
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

#include <fltk3/run.h>
#include <fltk3/Widget.h>
#include <fltk3/Wrapper.h>
#include <fltk3/Group.H>
#include <fltk3/Fl_Tooltip.H>
#include <fltk3/fl_draw.H>
#include <stdlib.h>
#include "flstring.h"


////////////////////////////////////////////////////////////////
// for compatibility with Forms, all widgets without callbacks are
// inserted into a "queue" when they are activated, and the forms
// compatibility interaction functions (fl_do_events, etc.) will
// read one widget at a time from this queue and return it:

const int QUEUE_SIZE = 20;

static fltk3::Widget *obj_queue[QUEUE_SIZE];
static int obj_head, obj_tail;

void fltk3::Widget::default_callback(fltk3::Widget *o, void * /*v*/) {
#if 0
  // This is necessary for strict forms compatibility but is confusing.
  // Use the parent's callback if this widget does not have one.
  for (fltk3::Widget *p = o->parent(); p; p = p->parent())
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
    All Fl_Widgets that don't have a callback defined use a
    default callback that puts a pointer to the widget in this queue,
    and this method reads the oldest widget out of this queue.
*/
fltk3::Widget *fltk3::readqueue() {
  if (obj_tail==obj_head) return 0;
  fltk3::Widget *o = obj_queue[obj_tail++];
  if (obj_tail >= QUEUE_SIZE) obj_tail = 0;
  return o;
}
/*
    This static internal function removes all pending callbacks for a
    specific widget from the default callback queue (fltk3::readqueue()).
    It is only called from fltk3::Widget's destructor if the widget
    doesn't have an own callback.
    Note: There's no need to have this in the fltk3:: namespace.
*/
static void cleanup_readqueue(fltk3::Widget *w) {

  if (obj_tail==obj_head) return;
  
  // Read the entire queue and copy over all valid entries.
  // The new head will be determined after the last copied entry.

  int old_head = obj_head;	// save newest entry
  int entry = obj_tail;		// oldest entry
  obj_head = obj_tail;		// new queue start
  for (;;) {
    fltk3::Widget *o = obj_queue[entry++];
    if (entry >= QUEUE_SIZE) entry = 0;
    if (o != w) { // valid entry
      obj_queue[obj_head++] = o;
      if (obj_head >= QUEUE_SIZE) obj_head = 0;
    } // valid entry
    if (entry == old_head) break;
  }
  return;
}
////////////////////////////////////////////////////////////////

int fltk3::Widget::handle(int event) {
  FLTK3_OBJECT_VCALLS_WRAPPER_INT(handle(event), Handle);
  return 0;
}

/** Default font size for widgets */
fltk3::Fontsize fltk3::NORMAL_SIZE = 14;

fltk3::Widget::Widget(int X, int Y, int W, int H, const char* L) {

  x_ = X; y_ = Y; w_ = W; h_ = H;

  label_.value	 = L;
  label_.image   = 0;
  label_.deimage = 0;
  label_.type	 = fltk3::NORMAL_LABEL;
  label_.font	 = fltk3::HELVETICA;
  label_.size	 = fltk3::NORMAL_SIZE;
  label_.color	 = FL_FOREGROUND_COLOR;
  label_.align_	 = fltk3::ALIGN_CENTER;
  tooltip_       = 0;
  callback_	 = default_callback;
  user_data_ 	 = 0;
  type_		 = 0;
  flags_	 = VISIBLE_FOCUS;
  damage_	 = 0;
  box_		 = fltk3::NO_BOX;
  color_	 = FL_GRAY;
  color2_	 = FL_GRAY;
  when_		 = fltk3::WHEN_RELEASE;

  parent_ = 0;
  if (fltk3::Group::current()) fltk3::Group::current()->add(this);
}

void fltk3::Widget::resize(int X, int Y, int W, int H) {
  FLTK3_OBJECT_VCALLS_WRAPPER(resize(X, Y, W, H), Resize);
  x_ = X; y_ = Y; w_ = W; h_ = H;
}

// this is useful for parent widgets to call to resize children:
int fltk3::Widget::damage_resize(int X, int Y, int W, int H) {
  if (x() == X && y() == Y && w() == W && h() == H) return 0;
  resize(X, Y, W, H);
  redraw();
  return 1;
}

int fltk3::Widget::take_focus() {
  if (!takesevents()) return 0;
  if (!visible_focus()) return 0;
  if (!handle(FL_FOCUS)) return 0; // see if it wants it
  if (contains(fltk3::focus())) return 1; // it called fltk3::focus for us
  fltk3::focus(this);
  return 1;
}

extern void fl_throw_focus(fltk3::Widget*); // in Fl_x.cxx

/**
   Destroys the widget, taking care of throwing focus before if any.
   Destruction removes the widget from any parent group! And groups when
   destroyed destroy all their children. This is convenient and fast.
*/
fltk3::Widget::~Widget() {
  fltk3::clear_widget_pointer(this);
  if (flags() & COPIED_LABEL) free((void *)(label_.value));
  if (flags() & COPIED_TOOLTIP) free((void *)(tooltip_));
  // remove from parent group
  if (parent_) parent_->remove(this);
#ifdef DEBUG_DELETE
  if (parent_) { // this should never happen
    printf("*** fltk3::Widget: parent_->remove(this) failed [%p,%p]\n",parent_,this);
  }
#endif // DEBUG_DELETE
  parent_ = 0; // Don't throw focus to a parent widget.
  fl_throw_focus(this);
  // remove stale entries from default callback queue (fltk3::readqueue())
  if (callback_ == default_callback) cleanup_readqueue(this);
}

/** Draws a focus box for the widget at the given position and size */
void
fltk3::Widget::draw_focus(fltk3::Boxtype B, int X, int Y, int W, int H) const {
  if (!fltk3::visible_focus()) return;
  switch (B) {
    case fltk3::DOWN_BOX:
    case fltk3::DOWN_FRAME:
    case fltk3::THIN_DOWN_BOX:
    case fltk3::THIN_DOWN_FRAME:
      X ++;
      Y ++;
    default:
      break;
  }

  fl_color(fl_contrast(FL_BLACK, color()));

#if defined(USE_X11) || defined(__APPLE_QUARTZ__)
  fl_line_style(FL_DOT);
  fl_rect(X + fltk3::box_dx(B), Y + fltk3::box_dy(B),
          W - fltk3::box_dw(B) - 1, H - fltk3::box_dh(B) - 1);
  fl_line_style(FL_SOLID);
#elif defined(WIN32) 
  // Windows 95/98/ME do not implement the dotted line style, so draw
  // every other pixel around the focus area...
  //
  // Also, QuickDraw (MacOS) does not support line styles specifically,
  // and the hack we use in fl_line_style() will not draw horizontal lines
  // on odd-numbered rows...
  int i, xx, yy;

  X += fltk3::box_dx(B);
  Y += fltk3::box_dy(B);
  W -= fltk3::box_dw(B) + 2;
  H -= fltk3::box_dh(B) + 2;

  for (xx = 0, i = 1; xx < W; xx ++, i ++) if (i & 1) fl_point(X + xx, Y);
  for (yy = 0; yy < H; yy ++, i ++) if (i & 1) fl_point(X + W, Y + yy);
  for (xx = W; xx > 0; xx --, i ++) if (i & 1) fl_point(X + xx, Y + H);
  for (yy = H; yy > 0; yy --, i ++) if (i & 1) fl_point(X, Y + yy);
#else
# error unsupported platform
#endif // WIN32
}


void fltk3::Widget::activate() {
  if (!active()) {
    clear_flag(INACTIVE);
    if (active_r()) {
      redraw();
      redraw_label();
      handle(FL_ACTIVATE);
      if (inside(fltk3::focus())) fltk3::focus()->take_focus();
    }
  }
}

void fltk3::Widget::deactivate() {
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

int fltk3::Widget::active_r() const {
  for (const fltk3::Widget* o = this; o; o = o->parent())
    if (!o->active()) return 0;
  return 1;
}

void fltk3::Widget::show() {
  FLTK3_OBJECT_VCALLS_WRAPPER(show(), Show);
  if (!visible()) {
    clear_flag(INVISIBLE);
    if (visible_r()) {
      redraw();
      redraw_label();
      handle(FL_SHOW);
      if (inside(fltk3::focus())) fltk3::focus()->take_focus();
    }
  }
}

void fltk3::Widget::hide() {
  FLTK3_OBJECT_VCALLS_WRAPPER(hide(), Hide);
  if (pWrapper) {
    if ( !(pWrapper->pVCalls & Wrapper::pVCallWidgetHide) )
      ((WidgetWrapper*)pWrapper)->hide();
    if ( !(pWrapper->pVCalls & Wrapper::pVCallWidgetHide) )
      return;
    pWrapper->pVCalls &= ~Wrapper::pVCallWidgetHide;
  }
  if (visible_r()) {
    set_flag(INVISIBLE);
    for (fltk3::Widget *p = parent(); p; p = p->parent())
      if (p->box() || !p->parent()) {p->redraw(); break;}
    handle(FL_HIDE);
    fl_throw_focus(this);
  } else {
    set_flag(INVISIBLE);
  }
}

int fltk3::Widget::visible_r() const {
  for (const fltk3::Widget* o = this; o; o = o->parent())
    if (!o->visible()) return 0;
  return 1;
}

// return true if widget is inside (or equal to) this:
// Returns false for null widgets.
int fltk3::Widget::contains(const fltk3::Widget *o) const {
  for (; o; o = o->parent_) if (o == this) return 1;
  return 0;
}


void
fltk3::Widget::label(const char *a) {
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
fltk3::Widget::copy_label(const char *a) {
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
fltk3::Widget::do_callback(fltk3::Widget* o,void* arg) {
  Fl_Widget_Tracker wp(this);
  // FIXME: the other callbacks must know about wrappers as well.
  if (o && o->pWrapper) {
    callback_((fltk3::Widget*)o->pWrapper,arg);
  } else {
    callback_(o,arg);
  }
  if (wp.deleted()) return;
  if (callback_ != default_callback)
    clear_changed();
}

void fltk3::Widget::draw() {
  FLTK3_OBJECT_VCALLS_WRAPPER(draw(), Draw);
  draw_box();
  draw_label();
}


// ========================= Wrapper Support ===================================

fltk3::Object::~Object() {
  if ( pWrapper && !(pWrapper->pVCalls&Wrapper::pVCallDtor) ) {
    pWrapper->pVCalls |= Wrapper::pVCallDtor;
    delete pWrapper;
  }
}

fltk3::Wrapper::~Wrapper() {
  if ( !(pVCalls&pVCallDtor) ) {
    pVCalls |= pVCallDtor;
    delete _p;
  }
}

// =================== FLTK1 Compatibility Support =============================


// =================== FLTK2 Compatibility Support =============================

#include <fltk/Font.h>

fltk::Font fltk::fltk2_font_list[] = {
  { fltk3::HELVETICA },
  { fltk3::HELVETICA_BOLD },
  { fltk3::HELVETICA_ITALIC },
  { fltk3::HELVETICA_BOLD_ITALIC },
  { fltk3::COURIER },
  { fltk3::COURIER_BOLD },
  { fltk3::COURIER_ITALIC },
  { fltk3::COURIER_BOLD_ITALIC },
  { fltk3::TIMES },
  { fltk3::TIMES_BOLD },
  { fltk3::TIMES_ITALIC },
  { fltk3::TIMES_BOLD_ITALIC },
  { fltk3::SYMBOL },
  { fltk3::SCREEN },
  { fltk3::SCREEN_BOLD },
  { fltk3::ZAPF_DINGBATS }
};

fltk::Font *const fltk::HELVETICA             = fltk2_font_list+0;
fltk::Font *const fltk::HELVETICA_BOLD        = fltk2_font_list+1;
fltk::Font *const fltk::HELVETICA_ITALIC      = fltk2_font_list+2;
fltk::Font *const fltk::HELVETICA_BOLD_ITALIC = fltk2_font_list+3;
fltk::Font *const fltk::COURIER               = fltk2_font_list+4;
fltk::Font *const fltk::COURIER_BOLD          = fltk2_font_list+5;
fltk::Font *const fltk::COURIER_ITALIC        = fltk2_font_list+6;
fltk::Font *const fltk::COURIER_BOLD_ITALIC   = fltk2_font_list+7;
fltk::Font *const fltk::TIMES                 = fltk2_font_list+8;
fltk::Font *const fltk::TIMES_BOLD            = fltk2_font_list+9;
fltk::Font *const fltk::TIMES_ITALIC          = fltk2_font_list+10;
fltk::Font *const fltk::TIMES_BOLD_ITALIC     = fltk2_font_list+11;
fltk::Font *const fltk::SYMBOL                = fltk2_font_list+12;
fltk::Font *const fltk::SCREEN                = fltk2_font_list+13;
fltk::Font *const fltk::SCREEN_BOLD           = fltk2_font_list+14;
fltk::Font *const fltk::ZAPF_DINGBATS         = fltk2_font_list+15;

#include <fltk/Box.h>
#include <fltk/Symbol.h>

fltk::Symbol fltk::fltk2_box_list[] = {
  { fltk3::NO_BOX },
  { fltk3::FLAT_BOX },
  { fltk3::UP_BOX },
  { fltk3::DOWN_BOX },
  { fltk3::UP_FRAME },
  { fltk3::DOWN_FRAME },
  { fltk3::THIN_UP_BOX },
  { fltk3::THIN_DOWN_BOX },
  { fltk3::THIN_UP_FRAME },
  { fltk3::THIN_DOWN_FRAME },
  { fltk3::ENGRAVED_BOX },
  { fltk3::EMBOSSED_BOX },
  { fltk3::ENGRAVED_FRAME },
  { fltk3::EMBOSSED_FRAME },
  { fltk3::BORDER_BOX },
  { fltk3::SHADOW_BOX },
  { fltk3::BORDER_FRAME },
  { fltk3::SHADOW_FRAME }
};

fltk::Box *const fltk::NO_BOX           = fltk2_box_list+0;
fltk::Box *const fltk::FLAT_BOX         = fltk2_box_list+1;
fltk::Box *const fltk::UP_BOX           = fltk2_box_list+2;
fltk::Box *const fltk::DOWN_BOX         = fltk2_box_list+3;
fltk::Box *const fltk::UP_FRAME         = fltk2_box_list+4;
fltk::Box *const fltk::DOWN_FRAME       = fltk2_box_list+5;
fltk::Box *const fltk::THIN_UP_BOX      = fltk2_box_list+6;
fltk::Box *const fltk::THIN_DOWN_BOX    = fltk2_box_list+7;
fltk::Box *const fltk::THIN_UP_FRAME    = fltk2_box_list+8;
fltk::Box *const fltk::THIN_DOWN_FRAME  = fltk2_box_list+9;
fltk::Box *const fltk::ENGRAVED_BOX     = fltk2_box_list+10;
fltk::Box *const fltk::EMBOSSED_BOX     = fltk2_box_list+11;
fltk::Box *const fltk::ENGRAVED_FRAME   = fltk2_box_list+12;
fltk::Box *const fltk::EMBOSSED_FRAME   = fltk2_box_list+13;
fltk::Box *const fltk::BORDER_BOX       = fltk2_box_list+14;
fltk::Box *const fltk::SHADOW_BOX       = fltk2_box_list+15;
fltk::Box *const fltk::BORDER_FRAME     = fltk2_box_list+16;
fltk::Box *const fltk::SHADOW_FRAME     = fltk2_box_list+17;


#include <fltk/LabelType.h>

fltk::LabelType fltk::fltk2_labeltype_list[] = {
  { fltk3::NORMAL_LABEL },
  { fltk3::NO_LABEL },
  { fltk3::SHADOW_LABEL },
  { fltk3::ENGRAVED_LABEL },
  { fltk3::EMBOSSED_LABEL },
  { fltk3::MULTI_LABEL },
  { fltk3::ICON_LABEL },
  { fltk3::IMAGE_LABEL }
};

fltk::LabelType *const fltk::NO_LABEL       = fltk2_labeltype_list+1;
fltk::LabelType *const fltk::NORMAL_LABEL   = fltk2_labeltype_list+0;
fltk::LabelType *const fltk::SYMBOL_LABEL   = fltk2_labeltype_list+0;
fltk::LabelType *const fltk::SHADOW_LABEL   = fltk2_labeltype_list+2;
fltk::LabelType *const fltk::ENGRAVED_LABEL = fltk2_labeltype_list+3;
fltk::LabelType *const fltk::EMBOSSED_LABEL = fltk2_labeltype_list+4;

//
// End of "$Id$".
//
