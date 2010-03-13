//
// "$Id$"
//

// 123 TODO: remove stray comments
// 123 TODO: add namespace statements
// 123 TODO: replace class name, constructors and destructor
// 123 TODO: add friend statement for Twin Class
// 123 TODO: add 'compat(FLTK2)' to constructors
// 123 TODO: add twin class with all constructors
// 123 TODO: change all arguments to the FLTK2 class name
// 123 TODO: change the source code to use the new class names
// 123 TODO: add casting to return values
// 123 TODO: move all FLTK2-only functions to the FLTK3 section and implement them
// 123 TODO: remove the FLTK1 and FLTK2 sections in the headers
// 123 TODO: 


/* suggested twin class
// This is the Twin Class to fltk::layout
class Fl_Layout : public fltk::layout {
public:
  Fl_Layout(int x, int t, int w, int h, const char *label=0)
  : fltk::layout(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
#ifndef fltk_layout_h
#define fltk_layout_h

namespace fltk {

/*!
  Values of the bits stored in Widget::layout_damage().

  When a widget resized or moved (or when it is initially created),
  flags are set in Widget::layout_damage() to indicate the layout is
  damaged. This will cause the virtual function Widget::layout() to be
  called just before fltk attempts to draw the windows on the screen.
  This is useful because often calculating the new layout is quite
  expensive, this expense is now deferred until the user will actually
  see the new size.

  Some Group widgets such as fltk::PackedGroup will also use the
  virtual Widget::layout() function to find out how big a widget
  should be.  A Widget is allowed to change it's own dimensions in
  layout() (except it is not allowed to change it if called a second
  time with no changes other than it's x/y position). This allows
  widgets to resize to fit their contents.

  The layout bits are turned on by calling Widget::relayout().
*/
enum {
  LAYOUT_X	= 0x01, /*!< Widget::x() changed by resize() */
  LAYOUT_Y	= 0x02, /*!< Widget::y() changed by resize() */
  LAYOUT_XY	= 0x03, /*!< Same as LAYOUT_X|LAYOUT_Y */
  LAYOUT_W	= 0x04,	/*!< Widget::w() changed by resize() */
  LAYOUT_H	= 0x08,	/*!< Widget::h() changed by resize() */
  LAYOUT_WH	= 0x0C, /*!< Same as LAYOUT_W|LAYOUT_H */
  LAYOUT_XYWH	= 0x0F, /*!< Same as LAYOUT_XY|LAYOUT_WH */
  LAYOUT_CHILD	= 0x10, /*!< Widget::layout() needs to be called on a child of this group widget. */
  LAYOUT_USER   = 0x20, /*!< The moving/resizing is being caused by the user and not internal code. */
  LAYOUT_DAMAGE	= 0x80	/*!< Widget::relayout() was called. */
};

}

#endif
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
