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

//
// "$Id: fl_ask.H 6614 2009-01-01 16:11:32Z matt $"
//
// Standard dialog header file for the Fast Light Tool Kit (FLTK).
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

#ifndef fl_ask_H
#  define fl_ask_H

#  include "Enumerations.H"

class Fl_Widget;
/** Different system beeps available. \relatesalso fl_beep(int) */
enum {
  FL_BEEP_DEFAULT = 0,
  FL_BEEP_MESSAGE,
  FL_BEEP_ERROR,
  FL_BEEP_QUESTION,
  FL_BEEP_PASSWORD,
  FL_BEEP_NOTIFICATION
};

#  ifdef __GNUC__
#    define __fl_attr(x) __attribute__ (x)
#    if __GNUC__ < 3
#      define __deprecated__
#    endif // __GNUC__ < 3
#  else
#    define __fl_attr(x)
#  endif // __GNUC__

FL_EXPORT void fl_beep(int type = FL_BEEP_DEFAULT);
FL_EXPORT void fl_message(const char *,...) __fl_attr((__format__ (__printf__, 1, 2)));
FL_EXPORT void fl_alert(const char *,...) __fl_attr((__format__ (__printf__, 1, 2)));
// fl_ask() is deprecated since it uses "Yes" and "No" for the buttons,
// which does not conform to the current FLTK Human Interface Guidelines.
// Use fl_choice() instead with the appropriate verbs instead.
FL_EXPORT int fl_ask(const char *,...) __fl_attr((__format__ (__printf__, 1, 2), __deprecated__));
FL_EXPORT int fl_choice(const char *q,const char *b0,const char *b1,const char *b2,...) __fl_attr((__format__ (__printf__, 1, 5)));
FL_EXPORT const char *fl_input(const char *label, const char *deflt = 0, ...) __fl_attr((__format__ (__printf__, 1, 3)));
FL_EXPORT const char *fl_password(const char *label, const char *deflt = 0, ...) __fl_attr((__format__ (__printf__, 1, 3)));

FL_EXPORT Fl_Widget *fl_message_icon();
extern FL_EXPORT Fl_Font fl_message_font_;
extern FL_EXPORT Fl_Fontsize fl_message_size_;
inline void fl_message_font(Fl_Font f, Fl_Fontsize s) {
  fl_message_font_ = f; fl_message_size_ = s;}

// pointers you can use to change FLTK to a foreign language:
extern FL_EXPORT const char* fl_no;
extern FL_EXPORT const char* fl_yes;
extern FL_EXPORT const char* fl_ok;
extern FL_EXPORT const char* fl_cancel;
extern FL_EXPORT const char* fl_close;
#endif // !fl_ask_H

//
// End of "$Id: fl_ask.H 6614 2009-01-01 16:11:32Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::ask
class fl_ask : public fltk::ask {
public:
  fl_ask(int x, int t, int w, int h, const char *label=0)
  : fltk::ask(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: fl_ask.H 6614 2009-01-01 16:11:32Z matt $"
//
// Standard dialog header file for the Fast Light Tool Kit (FLTK).
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

#ifndef fl_ask_H
#  define fl_ask_H

#  include "Enumerations.H"

class Fl_Widget;
/** Different system beeps available. \relatesalso fl_beep(int) */
enum {
  FL_BEEP_DEFAULT = 0,
  FL_BEEP_MESSAGE,
  FL_BEEP_ERROR,
  FL_BEEP_QUESTION,
  FL_BEEP_PASSWORD,
  FL_BEEP_NOTIFICATION
};

#  ifdef __GNUC__
#    define __fl_attr(x) __attribute__ (x)
#    if __GNUC__ < 3
#      define __deprecated__
#    endif // __GNUC__ < 3
#  else
#    define __fl_attr(x)
#  endif // __GNUC__

FL_EXPORT void fl_beep(int type = FL_BEEP_DEFAULT);
FL_EXPORT void fl_message(const char *,...) __fl_attr((__format__ (__printf__, 1, 2)));
FL_EXPORT void fl_alert(const char *,...) __fl_attr((__format__ (__printf__, 1, 2)));
// fl_ask() is deprecated since it uses "Yes" and "No" for the buttons,
// which does not conform to the current FLTK Human Interface Guidelines.
// Use fl_choice() instead with the appropriate verbs instead.
FL_EXPORT int fl_ask(const char *,...) __fl_attr((__format__ (__printf__, 1, 2), __deprecated__));
FL_EXPORT int fl_choice(const char *q,const char *b0,const char *b1,const char *b2,...) __fl_attr((__format__ (__printf__, 1, 5)));
FL_EXPORT const char *fl_input(const char *label, const char *deflt = 0, ...) __fl_attr((__format__ (__printf__, 1, 3)));
FL_EXPORT const char *fl_password(const char *label, const char *deflt = 0, ...) __fl_attr((__format__ (__printf__, 1, 3)));

FL_EXPORT Fl_Widget *fl_message_icon();
extern FL_EXPORT Fl_Font fl_message_font_;
extern FL_EXPORT Fl_Fontsize fl_message_size_;
inline void fl_message_font(Fl_Font f, Fl_Fontsize s) {
  fl_message_font_ = f; fl_message_size_ = s;}

// pointers you can use to change FLTK to a foreign language:
extern FL_EXPORT const char* fl_no;
extern FL_EXPORT const char* fl_yes;
extern FL_EXPORT const char* fl_ok;
extern FL_EXPORT const char* fl_cancel;
extern FL_EXPORT const char* fl_close;
#endif // !fl_ask_H

//
// End of "$Id: fl_ask.H 6614 2009-01-01 16:11:32Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id: ask.h 6233 2008-09-14 07:54:06Z spitzak $"
//
// Copyright 2008 by Bill Spitzak and others.
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
// Please report all bugs and problems to "fltk-bugs@fltk.org".

#ifndef fltk_ask_h
#define fltk_ask_h

#include "FL_API.h"
#include "Style.h"

namespace fltk {

class Widget;

/// \name fltk/ask.h
//@{

enum {
  BEEP_DEFAULT = 0,
  BEEP_MESSAGE,
  BEEP_ERROR,
  BEEP_QUESTION,
  BEEP_PASSWORD,
  BEEP_NOTIFICATION
};

FL_API void message(const char *, ...);
FL_API void alert(const char *, ...);
FL_API int  ask(const char *, ...);
FL_API int  choice(const char *q,
		  const char *b0, const char *b1, const char *b2, ...);
FL_API int  choice_alert(const char *q,
		  const char *b0, const char *b1, const char *b2, ...);
FL_API const char *input(const char *label, const char *deflt = 0, ...);
FL_API const char *password(const char *label, const char *deflt = 0, ...);
FL_API void beep(int type = BEEP_DEFAULT);
FL_API void beep_on_dialog(bool);
FL_API bool beep_on_dialog();

extern FL_API NamedStyle* icon_style;
extern FL_API NamedStyle* message_style;

extern FL_API const char* message_window_label;
extern FL_API float message_window_timeout;

extern FL_API bool message_window_scrollable;

// pointers you can use to change FLTK to a foreign language:
extern FL_API const char* no;
extern FL_API const char* yes;
extern FL_API const char* ok;
extern FL_API const char* cancel;

}

//@}

#endif

//
// End of "$Id: ask.h 6233 2008-09-14 07:54:06Z spitzak $".
//
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
