//
// "$Id$"
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

#ifndef Fl_Widget_H
#define Fl_Widget_H

#include "Enumerations.H"

class Fl_Widget;
class Fl_Window;
class Fl_Group;
class Fl_Image;

typedef void (Fl_Callback )(Fl_Widget*, void*);
typedef Fl_Callback* Fl_Callback_p; // needed for BORLAND
typedef void (Fl_Callback0)(Fl_Widget*);
typedef void (Fl_Callback1)(Fl_Widget*, long);

struct FL_EXPORT Fl_Label {
  const char* value;
  Fl_Image* image;
  Fl_Image* deimage;
  uchar type;
  uchar font;
  uchar size;
  unsigned color;
  void draw(int,int,int,int, Fl_Align) const ;
  void measure(int&, int&) const ;
};


/** 
 * Fl_Widget is the base class for all widgets in FLTK. You can't
 * create one of these because the constructor is not public.  However you
 * can subclass it.
 *
 * All "property" accessing methods, such as color(), 
 * parent(), or argument() are implemented as trivial inline
 * functions and thus are as fast and small as accessing fields in a
 * structure. Unless otherwise noted, the property setting methods such as
 * color(n) or label(s) are also trivial inline functions,
 * even if they change the widget's appearance.  It is up to the user code
 * to call redraw() after these.
 */
class FL_EXPORT Fl_Widget {
  friend class Fl_Group;

  Fl_Group* parent_;
  Fl_Callback* callback_;
  void* user_data_;
  short x_,y_,w_,h_;
  Fl_Label label_;
  int flags_;
  unsigned color_;
  unsigned color2_;
  uchar type_;
  uchar damage_;
  uchar box_;
  uchar align_;
  uchar when_;

  const char *tooltip_;

  // unimplemented copy ctor and assignment operator
  Fl_Widget(const Fl_Widget &);
  Fl_Widget& operator=(const Fl_Widget &);

protected:

  /**
   * Creates a widget at the given position and size. The
   * Fl_Widget is a protected constructor, but all derived
   * widgets have a matching public constructor. It takes a value for
   * x(), y(), w(), h(), and an
   * optional value for label().
   * 
   * \param[in] x, y, w, h position and size of the widget
   * \param[in] label pointer to the label text (will not be copied)
   */
  Fl_Widget(int x, int y, int w, int h, const char* label=0);

  void x(int v) {x_ = (short)v;}
  void y(int v) {y_ = (short)v;}
  void w(int v) {w_ = (short)v;}
  void h(int v) {h_ = (short)v;}

  int flags() const {return flags_;}
  void set_flag(int c) {flags_ |= c;}
  void clear_flag(int c) {flags_ &= ~c;}
  enum {INACTIVE=1, INVISIBLE=2, OUTPUT=4, SHORTCUT_LABEL=64,
        CHANGED=128, VISIBLE_FOCUS=512, COPIED_LABEL = 1024};

  void draw_box() const;
  void draw_box(Fl_Boxtype, Fl_Color) const;
  void draw_box(Fl_Boxtype, int,int,int,int, Fl_Color) const;
  void draw_focus() {draw_focus(box(),x(),y(),w(),h());}
  void draw_focus(Fl_Boxtype, int,int,int,int) const;
  void draw_label() const;
  void draw_label(int, int, int, int) const;

public:

  /**
   * Destroys the widget. Destroying single widgets is not very
   * common, and it is your responsibility to either
   * remove() them from any enclosing group or destroy that
   * group <I>immediately</I> after destroying the children. You
   * almost always want to destroy the parent group instead which
   * will destroy all of the child widgets and groups in that group.
   */
  virtual ~Fl_Widget();

  virtual void draw() = 0;

  /**
   * Handles the specified event. You normally don't call this
   * method directly, but instead let FLTK do it when the user
   * interacts with the widget
   * 
   * When implemented in a new widget, this function must return 0
   * if the widget does not use the event or 1 if it uses the
   * event.
   */
  virtual int handle(int);

  /**
   * Returns a pointer to the parent widget.  Usually this is a 
   * Fl_Group or Fl_Window. Returns
   * <tt>NULL</tt> if the widget has no parent.
   */
  Fl_Group* parent() const {return parent_;}

  /**
   * This function manipulates a pointer. Please use Fl_Group::add()
   * to set the parent od a widget.
   */
  void parent(Fl_Group* p) {parent_ = p;} // for hacks only, Fl_Group::add()

  /**
   * Returns the widget type value, which is used for Forms
   * compatability and to simulate RTTI.
   */
  uchar type() const {return type_;}
  void type(uchar t) {type_ = t;}

  /**
   * Returns the position of the upper-left corner of the widget
   * in its enclosing Fl_Window (<I>not</I> its parent if that is not
   * an Fl_Window).
   */
  int x() const {return x_;}

  /**
   * Returns the position of the upper-left corner of the widget
   * in its enclosing Fl_Window (<I>not</I> its parent if that is not
   * an Fl_Window).
   */
  int y() const {return y_;}

  /**
   * Returns the width of the widget.
   */
  int w() const {return w_;}

  /**
   * Returns the height of the widget.
   */
  int h() const {return h_;}

  /**
   * Change the size and position of the widget. This is a virtual
   * function so that the widget may implement its own handling of
   * resizing. The default version does <I>not</I> call the
   * <TT>redraw()</TT> method, but instead relies on the parent
   * widget to do so because the parent may know a faster way to
   * update the display, such as scrolling from the old position.
   * 
   * Some window managers under X11 call resize() a lot more
   * often than needed. Please verify that the position or size of
   * a widget did actually change before doing any extensiive calculations.
   */
  virtual void resize(int,int,int,int);

  int damage_resize(int,int,int,int);

  /**
   * position(x,y) is a shortcut for resize(x,y,w(),h()).
   */
  void position(int X,int Y) {resize(X,Y,w_,h_);}

  /**
   * size(w,h) is a shortcut for resize(x(),y(),w,h).
   */
  void size(int W,int H) {resize(x_,y_,W,H);}


  /**
   * Gets the label alignment, which controls how the
   * label is displayed next to or inside the widget. 
   */
  Fl_Align align() const {return (Fl_Align)align_;}

  /**
   * Sets the label alignment, which controls how the
   * label is displayed next to or inside the widget. The default
   * value is FL_ALIGN_CENTER, which centers the label
   * inside the widget. The value can be any of these constants
   * bitwise-OR'd together:
   *  * FL_ALIGN_BOTTOM
   *  * FL_ALIGN_CENTER
   *  * FL_ALIGN_CLIP
   *  * FL_ALIGN_INSIDE
   *  * FL_ALIGN_LEFT
   *  * FL_ALIGN_RIGHT
   *  * FL_ALIGN_TEXT_OVER_IMAGE
   *  * FL_ALIGN_TOP
   *  * FL_ALIGN_WRAP
   *
   * \param[in] a alignment
   */
  void align(uchar a) {align_ = a;}

  /**
   * Gets the box type for the widget.
   */
  Fl_Boxtype box() const {return (Fl_Boxtype)box_;}

  /**
   * <P>Sets the box type for the widget, which identifies a
   * routine that draws the background of the widget. See
   * Box Types for the available
   * types. The default depends on the widget, but is usually
   * FL_NO_BOX or FL_UP_BOX.
   *
   * \param[in] a box type identifier
   */
  void box(Fl_Boxtype a) {box_ = a;}

  /**
   * Gets the background color of the widget.
   */
  Fl_Color color() const {return (Fl_Color)color_;}

  /**
   * Sets the background color of the widget. The color is
   * passed to the box routine. The color is either an index into an
   * internal table of RGB colors or an RGB color value generated
   * using fl_rgb_color(). The default for most widgets is
   * FL_BACKGROUND_COLOR. See the enumeration list for
   * predefined colors. Use Fl::set_color() to
   * redefine colors.
   *
   * \param[in] a new background color
   */
  void color(unsigned a) {color_ = a;}

  /**
   * Gets the selection color.
   */
  Fl_Color selection_color() const {return (Fl_Color)color2_;}

  /**
   * Sets the selection color, which is defined for Forms
   * compatibility and is usually used to color the widget when it is
   * selected, although some widgets use this color for other
   * purposes. You can set both colors at once with
   * color(a,b).
   */
  void selection_color(unsigned a) {color2_ = a;}

  /**
   * Sets both the background and selection
   * colors. See the description of the selection_color()
   * method for more information.
   *
   * \param[in] a new background color
   * \param[in] b new selection color
   */
  void color(unsigned a, unsigned b) {color_=a; color2_=b;}

  /**
   * Get the current label pointer.
   */
  const char* label() const {return label_.value;}

  /**
   * Set the current label pointer. The label is shown
   * somewhere on or next to the widget. The passed pointer is stored
   * unchanged in the widget (the string is <I>not</I> copied), so if
   * you need to set the label to a formatted value, make sure the
   * buffer is <TT>static</TT>, global, or allocated. The 
   * copy_label() method * can be used to make a copy of the label string
   * automatically.
   *
   * \param[in] a new label as static ASCII text
   */
  void label(const char* a);

  /**
   * Sets the current label. Unlike Fl_Widget::label(), this method
   * allocates a copy of the label string instead of using the
   * original string pointer.
   *
   * \param[in] a new text for label
   */
  void copy_label(const char* a);
  void label(Fl_Labeltype a,const char* b) {label_.type = a; label_.value = b;}

  /**
   * Gets the labeltype which
   * identifies the function that draws the label of the widget. 
   */
  Fl_Labeltype labeltype() const {return (Fl_Labeltype)label_.type;}

  /**
   * Sets the labeltype which
   * identifies the function that draws the label of the widget. This
   * is generally used for special effects such as embossing or for
   * using the label() pointer as another form of data such
   * as an icon. The value FL_NORMAL_LABEL prints the label
   * as plain text.
   *
   * \param[in] a the new label type
   */
  void labeltype(Fl_Labeltype a) {label_.type = a;}

  /**
   * Gets the label color.
   */
  Fl_Color labelcolor() const {return (Fl_Color)label_.color;}

  /**
   * Sets the label color. The default color is FL_FOREGROUND_COLOR.
   */
  void labelcolor(unsigned a) {label_.color=a;}

  /**
   * Gets the font to use. 
   */
  Fl_Font labelfont() const {return (Fl_Font)label_.font;}

  /**
   * Sets the font to use. Fonts are identified by small
   * 8-bit indexes into a table.  See the
   * enumeration list for predefined typefaces. The default value uses a Helvetica
   * typeface (Arial for Microsoft&reg; Windows&reg;). The function Fl::set_font() can
   * define new typefaces.
   *
   * \param[in] a font identifier
   */
  void labelfont(uchar a) {label_.font=a;}

  /**
   * Gets the font size in pixels.
   */
  uchar labelsize() const {return label_.size;}

  /**
   * Sets the font size in pixels. The default size is 14 pixels.
   */
  void labelsize(uchar a) {label_.size=a;}

  /**
   * Gets the image to use as part of the widget label.
   * This image is used when drawing the widget in the active state.
   */
  Fl_Image* image() {return label_.image;}

  /**
   * Sets the image to use as part of the widget label.
   * This image is used when drawing the widget in the active state.
   *
   * \param[in] a the image
   */
  void image(Fl_Image* a) {label_.image=a;}

  /**
   * Sets the image to use as part of the widget label.
   * This image is used when drawing the widget in the active state.
   *
   * \param[in] a the image
   */
  void image(Fl_Image& a) {label_.image=&a;}

  /**
   * Gets the image to use as part of the widget label.
   * This image is used when drawing the widget in the inactive
   * state.
   */
  Fl_Image* deimage() {return label_.deimage;}

  /**
   * Sets the image to use as part of the widget label.
   * This image is used when drawing the widget in the inactive
   * state.
   */
  void deimage(Fl_Image* a) {label_.deimage=a;}

  /**
   * Sets the image to use as part of the widget label.
   * This image is used when drawing the widget in the inactive
   * state.
   */
  void deimage(Fl_Image& a) {label_.deimage=&a;}

  /**
   * Gets a string of text to display in a popup tooltip
   * window when the user hovers the mouse over the widget. 
   */
  const char *tooltip() const {return tooltip_;}

  /**
   * Sets a string of text to display in a popup tooltip
   * window when the user hovers the mouse over the widget. The
   * string is <I>not</I> copied, so make sure any formatted string
   * is stored in a <TT>static</TT>, global, or allocated buffer.
   * 
   * If no tooltip is set, the tooltip of the parent is inherited.
   * Setting a tooltip for a group and setting no tooltip for a child 
   * will show the group's tooltip instead. To avoid this behavior, 
   * you can set the child's tooltip to an empty string 
   * ("").
   */
  void tooltip(const char *t);

  /**
   * Gets the current callback function for the widget.
   */
  Fl_Callback_p callback() const {return callback_;}

  /**
   * Sets the current callback function for the widget.
   * Each widget has a single callback.
   *
   * \param[in] c pointer to callback function
   * \param[in] p user data pointer
   */
  void callback(Fl_Callback* c, void* p) {callback_=c; user_data_=p;}

  /**
   * Sets the current callback function for the widget.
   * Each widget has a single callback.
   *
   * \param[in] c pointer to callback function
   */
  void callback(Fl_Callback* c) {callback_=c;}

  /**
   * Sets the current callback function for the widget.
   * Each widget has a single callback.
   *
   * \param[in] c pointer to callback function
   */
  void callback(Fl_Callback0*c) {callback_=(Fl_Callback*)c;}

  /**
   * Gets or sets the current callback function for the widget.
   * Each widget has a single callback.
   *
   * \param[in] c pointer to callback function
   * \param[in] p user data integer
   */
  void callback(Fl_Callback1*c, long p=0) {callback_=(Fl_Callback*)c; user_data_=(void*)p;}

  /**
   * Gets the current user data argument that is passed to the callback function.
   */
  void* user_data() const {return user_data_;}

  /**
   * Sets the current user data (<TT>void *</TT>) argument
   * that is passed to the callback function.
   */
  void user_data(void* v) {user_data_ = v;}

  /**
   * Gets the current user data (<TT>long</TT>) argument
   * that is passed to the callback function. 
   */
  long argument() const {return (long)user_data_;}

  /**
   * Sets the current user data (<TT>long</TT>) argument
   * that is passed to the callback function. 
   * 
   * <B>Note:</B>
   *
   * This is implemented by casting the <TT>long</TT>
   * value to a <TT>void *</TT> and may not be portable on
   * some machines.
   *
   * \param[in] v arbitrary user data
   */
  void argument(long v) {user_data_ = (void*)v;}

  /**
   * Return a combination of flags which determine when the callback
   * is called.
   */
  Fl_When when() const {return (Fl_When)when_;}

  /**
   * Fl_Widget::when() is a set of bitflags used by
   * subclasses of Fl_Widget to decide when to do the
   * callback.  If the value is zero then the callback is never
   * done.  Other values are described in the individual widgets. 
   * This field is in the base class so that you can scan a panel and
   * do_callback() on all the ones that don't do their own
   * callbacks in response to an "OK" button.
   */
  void when(uchar i) {when_ = i;}

  /**
   * The visible() method returns true if the
   * widget is set to be visible.
   */
  int visible() const {return !(flags_&INVISIBLE);}

  /**
   * The visible_r() method
   * returns true if the widget and all of its parents are visible. A
   * widget is only visible if visible() is true on it
   * <I>and all of its parents</I>. 
   */
  int visible_r() const;

  /**
   * Show the widget.
   * 
   * Changing it will send FL_SHOW
   * events to the widget. Do not change it if the parent is not
   * visible, as this will send false FL_SHOW 
   * events to the widget. <TT>redraw()</TT> is called if necessary on
   * this or the parent.
   */
  void show();

  /**
   * Changing it will send FL_HIDE
   * events to the widget. Do not change it if the parent is not
   * visible, as this will send false FL_HIDE
   * events to the widget. redraw() is called if necessary on
   * this or the parent.
   */
  void hide();

  /**
   * Makes the widget visible; you must still redraw the parent
   * widget to see a change in the window. Normally you want to use
   * the show() method instead.
   */
  void set_visible() {flags_ &= ~INVISIBLE;}

  /**
   * Hides the widget; you must still redraw the parent to see a
   * change in the window. Normally you want to use the 
   * hide() method instead.
   */
  void clear_visible() {flags_ |= INVISIBLE;}

  /**
   * Fl_Widget::active() returns whether the widget is
   * active. 
   */
  int active() const {return !(flags_&INACTIVE);}

  /**
   * Fl_Widget::active_r() returns whether the
   * widget and all of its parents are active. 
   */
  int active_r() const;

  /**
   * Changing this value will send 
   * FL_ACTIVATE to the widget if active_r() is false.
   *
   * Inactive widgets
   * will be drawn "grayed out", e.g. with less contrast than the 
   * active widget. Inactive widgets will not receive any keyboard or
   * mouse button events. Other events (including FL_ENTER,
   * FL_MOVE, FL_LEAVE, FL_SHORTCUT, and 
   * others) will still be sent. A widget is only active if 
   * active() is true on it <I>and all of its parents</I>.
   */
  void activate();

  /**
   * Changing this value will send 
   * FL_DEACTIVATE to the widget if active_r() is true.
   *
   * Currently you cannot deactivate Fl_Window widgets.
   */
  void deactivate();

  /**
   * Returns non-zero if this widget is used for output only.
   */
  int output() const {return (flags_&OUTPUT);}

  /**
   * output() means the same as !active() except
   * it does not change how the widget is drawn. The widget will not
   * receive any events. This is useful for making scrollbars or
   * buttons that work as displays rather than input devices.
   */
  void set_output() {flags_ |= OUTPUT;}

  /**
   * output() means the same as !active() except
   * it does not change how the widget is drawn. The widget will not
   * receive any events. This is useful for making scrollbars or
   * buttons that work as displays rather than input devices.
   */
  void clear_output() {flags_ &= ~OUTPUT;}

  /**
   * This is the same as <TT>(active() && !output()
   * && visible())</TT> but is faster.
   */
  int takesevents() const {return !(flags_&(INACTIVE|INVISIBLE|OUTPUT));}

  /**
   * Fl_Widget::changed() is a flag that is turned on
   * when the user changes the value stored in the widget.  This is
   * only used by subclasses of Fl_Widget that store values,
   * but is in the base class so it is easier to scan all the widgets
   * in a panel and do_callback() on the changed ones in
   * response to an "OK" button.
   * 
   * Most widgets turn this flag off when they do the callback, and when
   * the program sets the stored value.
   */
  int changed() const {return flags_&CHANGED;}
  void set_changed() {flags_ |= CHANGED;}
  void clear_changed() {flags_ &= ~CHANGED;}

  /**
   * Tries to make this widget be the Fl::focus() widget, by first
   * sending it an FL_FOCUS event, and if it returns non-zero,
   * setting Fl::focus() to this widget.  You should use this
   * method to assign the focus to an widget.  Returns true if the widget
   * accepted the focus.
   */
  int take_focus();

  /**
   * Enables keyboard focus navigation with this widget; note,
   * however, that this will not necessarily mean that the widget
   * will accept focus, but for widgets that can accept focus, this
   * method enables it if it has been disabled.
   */
  void set_visible_focus() { flags_ |= VISIBLE_FOCUS; }

  /**
   * Disables keyboard focus navigation with this widget;
   * normally, all widgets participate in keyboard focus navigation.
   */
  void clear_visible_focus() { flags_ &= ~VISIBLE_FOCUS; }

  /**
   * Modifies keyboard focus navigation. 
   * \see set_visible_focus() and clear_visible_focus(). 
   */
  void visible_focus(int v) { if (v) set_visible_focus(); else clear_visible_focus(); }

  /**
   * This returns non-zero if this widget will participate in keyboard focus navigation.
   */
  int  visible_focus() { return flags_ & VISIBLE_FOCUS; }

  /**
   * The default callback, which puts a pointer to the widget on
   * the queue returned by Fl::readqueue(). You
   * may want to call this from your own callback.
   */
  static void default_callback(Fl_Widget*, void*);

  /**
   * Causes a widget to invoke its callback function.
   */
  void do_callback() {callback_(this,user_data_); if (callback_ != default_callback) clear_changed();}

  /**
   * Causes a widget to invoke its callback function with arbitrary arguments.
   */
  void do_callback(Fl_Widget* o,void* arg=0) {
    callback_(o,arg); if (callback_ != default_callback) clear_changed();}

  /**
   * Causes a widget to invoke its callback function with arbitrary arguments.
   */
  void do_callback(Fl_Widget* o,long arg) {
    callback_(o,(void*)arg); if (callback_ != default_callback) clear_changed();}

  int test_shortcut();
  static int test_shortcut(const char*);

  /**
   * Returns 1 if <TT>b</TT> is a child of this widget, or is
   * equal to this widget. Returns 0 if <TT>b</TT> is <TT>NULL</TT>.
   */
  int contains(const Fl_Widget*) const ;

  /**
   * Returns 1 if this widget is a child of <TT>a</TT>, or is
   * equal to <TT>a</TT>. Returns 0 if <TT>a</TT> is <TT>NULL</TT>.
   *
   * \param[in] o a widget which may be the parent
   */
  int inside(const Fl_Widget* o) const {return o ? o->contains(this) : 0;}

  /**
   * Marks the widget as needing its draw() routine called.
   */
  void redraw();

  /**
   * Marks the widget or the parent as needing a redraw for the
   * label area of a widget.
   */
  void redraw_label();

  /**
   * This returns non-zero if draw() needs to be
   * called. The damage value is actually a bit field that the widget
   * subclass can use to figure out what parts to draw.
   */
  uchar damage() const {return damage_;}

  void clear_damage(uchar c = 0) {damage_ = c;}

  /**
   * Set the damage bits for the widget.
   *
   * \param[in] c damage flags or'd
   */
  void damage(uchar c);

  /**
   * Set the damage bits for the widget and damages the widget within the 
   * specified bounding box.
   *
   * \param[in] c damage flags
   * \param[in] x, y, w, h damaged area
   */
  void damage(uchar c, int x, int y, int w, int h);

  void draw_label(int, int, int, int, Fl_Align) const;
  void measure_label(int& xx, int& yy) {label_.measure(xx,yy);}

  /**
   * Returns a pointer to the primary Fl_Window widget.
   * Returns <TT>NULL</TT> if no window is associated with this
   * widget.  Note: for an Fl_Window widget, this returns
   * its <I>parent</I> window (if any), not <I>this</I> window.
   */
  Fl_Window* window() const ;

  // back compatability only:
  Fl_Color color2() const {return (Fl_Color)color2_;}
  void color2(unsigned a) {color2_ = a;}
};

// reserved type numbers (necessary for my cheapo RTTI) start here.
// grep the header files for "RESERVED_TYPE" to find the next available
// number.
#define FL_RESERVED_TYPE 100

#endif

//
// End of "$Id$".
//
