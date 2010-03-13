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
// This is the Twin Class to fltk::error
class Fl_Error : public fltk::error {
public:
  Fl_Error(int x, int t, int w, int h, const char *label=0)
  : fltk::error(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
/*! \file
  Functions to report errors and possibly kill the program.
  You can change these pointers from their default values so that
  fltk calls your code instead.
*/

#ifndef fltk_error_h
#define fltk_error_h

#include "FL_API.h"

namespace fltk {

/// \name fltk/error.h
//@{

extern FL_API void (*warning)(const char*, ...);
extern FL_API void (*error)(const char*, ...);
extern FL_API void (*fatal)(const char*, ...);

//@}

}
#endif
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
