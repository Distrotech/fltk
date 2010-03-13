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
// This is the Twin Class to fltk::string
class string : public fltk::string {
public:
  string(int x, int t, int w, int h, const char *label=0)
  : fltk::string(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
/* "$Id: string.h 5961 2007-10-17 20:54:58Z spitzak $"
 *
 * Copyright 1998-2006 by Bill Spitzak and others.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * Please report all bugs and problems to "fltk-bugs@fltk.org".
 */

/*! \file

  Provides definitions for C string manipulation functions so that
  portable programs may be written. None of these functions are in
  the fltk namespace.

  In most cases the functions are provided by your operation system,
  or are simple renames of operating system functions.

  This file is designed to work on Windows, Linux, and BSD systems.
  It may need to be edited to work on other systems. Please try
  to do this by adding #if statements so this file remains portable.

  Some versions of fltk wrote this file using autoconf. I never liked
  this because I could not share the header file between systems, so
  I have reverted to a constant version.
*/

#ifndef fltk_string_h
#define fltk_string_h

#ifndef DOXYGEN

# include <string.h>
# include <stdarg.h> /* for va_list */
# include <stdio.h> /* for sprintf, vsprintf, snprintf and vsnprintf */

/* Windows has equivalent functions, but being Microsoft they added
   gratuitoius changes to the names to stop code from being portable: */
#if (defined(_WIN32) && !defined(__CYGWIN__)) || defined(__EMX__)
# define strcasecmp(s,t)	_stricmp(s, t)
# define strncasecmp(s,t,n)	_strnicmp(s, t, n)
# define vsnprintf		_vsnprintf
# define snprintf		_snprintf
#endif

#ifdef __cplusplus
extern "C" {
#endif

#endif

#include "FL_API.h"

FL_API extern char* newstring(const char *);

#if defined(DOXYGEN) || defined(__MWERKS__)
FL_API extern int strcasecmp(const char *, const char *);
FL_API extern int strncasecmp(const char *, const char *, size_t);
#endif

#if defined(DOXYGEN) || !defined(__linux) && !defined(_WIN32) && !defined(__FreeBSD__) && !defined(__APPLE__)
FL_API extern int snprintf(char *, size_t, const char *, ...);
FL_API extern int vsnprintf(char *, size_t, const char *, va_list ap);
#endif

#if defined(DOXYGEN) || !defined(__FreeBSD__) && !defined(__APPLE__)
FL_API extern size_t strlcat(char *, const char *, size_t);
FL_API extern size_t strlcpy(char *, const char *, size_t);
#endif

#ifdef __cplusplus
}
#endif

#endif

/*
 * End of "$Id: string.h 5961 2007-10-17 20:54:58Z spitzak $".
 */
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
