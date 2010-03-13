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
// This is the Twin Class to fltk::FL_VERSION
class FL_VERSION : public fltk::FL_VERSION {
public:
  FL_VERSION(int x, int t, int w, int h, const char *label=0)
  : fltk::FL_VERSION(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
/*! \file

The FLTK version number. Allows you to write conditionally compiled
code for different versions of FLTK. This file may be included by C
code in case you need it there.

FL_VERSION is a macro double that describes the major, minor, and
patch version numbers. The integer value is the major number. One
digit is used for the minor number, and three for the "patch" number
which is increased for each binary differnt release (it can go to 999).

Because double cannot be used in #if statements, the integer
numbers are in the FL_MAJOR_VERSION, FL_MINOR_VERSION, and
FL_PATCH_VERSION macro constants.

*/

#ifndef FL_VERSION

# define FL_MAJOR_VERSION 2 //!< The major release number, 1 or 2
# define FL_MINOR_VERSION 1 //!< The minor release number, 0-9
# define FL_PATCH_VERSION 0 //!< The patch number, 0-999
# define FL_VERSION	  2.1000

#if defined(__cplusplus) || defined(DOXYGEN) /* Allow this file to be included by C code */
#include "FL_API.h"
namespace fltk {

/*!
  Returns the value of FL_VERSION that FLTK was compiled with.
  This can be compared to the FL_VERSION macro to see if the shared
  library of fltk your program linked with is up to date.
*/
FL_API double version();

}
#endif

#endif
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
