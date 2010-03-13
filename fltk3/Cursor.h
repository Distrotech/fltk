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
// This is the Twin Class to fltk::Cursor
class Fl_Cursor : public fltk::Cursor {
public:
  Fl_Cursor(int x, int t, int w, int h, const char *label=0)
  : fltk::Cursor(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id"
//
// Mouse cursor support for the Fast Light Tool Kit (FLTK).

// This is likely to change!

#ifndef fltk_Cursor_h
#define fltk_Cursor_h

#include "FL_API.h"

namespace fltk {

struct Cursor; // this is not public

class Image;
Cursor* cursor(Image*, int x, int y);
extern FL_API Cursor* cursor(void *raw);

extern FL_API Cursor* const CURSOR_DEFAULT; // == NULL
extern FL_API Cursor* const CURSOR_ARROW;
extern FL_API Cursor* const CURSOR_CROSS;
extern FL_API Cursor* const CURSOR_WAIT;
extern FL_API Cursor* const CURSOR_INSERT;
extern FL_API Cursor* const CURSOR_HAND;
extern FL_API Cursor* const CURSOR_HELP;
extern FL_API Cursor* const CURSOR_MOVE;
extern FL_API Cursor* const CURSOR_NS;
extern FL_API Cursor* const CURSOR_WE;
extern FL_API Cursor* const CURSOR_NWSE;
extern FL_API Cursor* const CURSOR_NESW;
extern FL_API Cursor* const CURSOR_NO;
extern FL_API Cursor* const CURSOR_NONE;

}
#endif

// End of "$Id"
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
