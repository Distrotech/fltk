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
// This is the Twin Class to fltk::InvisibleBox
class Fl_Invisible_Box : public fltk::InvisibleBox {
public:
  Fl_Invisible_Box(int x, int t, int w, int h, const char *label=0)
  : fltk::InvisibleBox(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id: InvisibleBox.h 5698 2007-02-19 05:40:36Z spitzak $"
//
// This is a box that is invisible due to not having a box. The
// label still prints so it can be used to position labels. Also
// this is useful as a resizable() widget.

#ifndef fltk_InvisibleBox_h
#define fltk_InvisibleBox_h

#include "Widget.h"

namespace fltk {

class FL_API InvisibleBox : public Widget {
public:
  InvisibleBox(int x, int y, int w, int h, const char *l=0);
  InvisibleBox(Box* b, int x, int y, int w, int h, const char *l);
  static NamedStyle* default_style;
  int handle(int);
  void draw();
};

}

#endif

//
// End of "$Id: InvisibleBox.h 5698 2007-02-19 05:40:36Z spitzak $".
//
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
