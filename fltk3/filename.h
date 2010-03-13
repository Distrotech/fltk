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

/*
 * "$Id: filename.H 6986 2010-01-01 18:30:49Z greg.ercolano $"
 *
 * Filename header file for the Fast Light Tool Kit (FLTK).
 *
 * Copyright 1998-2009 by Bill Spitzak and others.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA.
 *
 * Please report all bugs and problems on the following page:
 *
 *     http://www.fltk.org/str.php
 */

#ifndef FL_FILENAME_H
#  define FL_FILENAME_H

#  include "FL_API.h"

/** \addtogroup filenames File names and URI utility functions 
    @{ */

#  define FL_PATH_MAX 256 /**< all path buffers should use this length */
/** Gets the file name from a path. 
    Similar to basename(3), exceptions shown below.
    \code
    #include <FL/filename.H>
    [..]
    const char *out;
    out = fl_filename_name("/usr/lib");     // out="lib"
    out = fl_filename_name("/usr/");        // out=""      (basename(3) returns "usr" instead)
    out = fl_filename_name("/usr");         // out="usr"
    out = fl_filename_name("/");            // out=""      (basename(3) returns "/" instead)
    out = fl_filename_name(".");            // out="."
    out = fl_filename_name("..");           // out=".."
    \endcode
    \return a pointer to the char after the last slash, or to \p filename if there is none.
 */
FL_EXPORT const char *fl_filename_name(const char * filename);
FL_EXPORT const char *fl_filename_ext(const char *buf);
FL_EXPORT char *fl_filename_setext(char *to, int tolen, const char *ext);
FL_EXPORT int fl_filename_expand(char *to, int tolen, const char *from);
FL_EXPORT int fl_filename_absolute(char *to, int tolen, const char *from);
FL_EXPORT int fl_filename_relative(char *to, int tolen, const char *from);
FL_EXPORT int fl_filename_match(const char *name, const char *pattern);
FL_EXPORT int fl_filename_isdir(const char *name);

#  if defined(__cplusplus) && !defined(FL_DOXYGEN)
/*
 * Under WIN32, we include filename.H from numericsort.c; this should probably change...
 */

inline char *fl_filename_setext(char *to, const char *ext) { return fl_filename_setext(to, FL_PATH_MAX, ext); }
inline int fl_filename_expand(char *to, const char *from) { return fl_filename_expand(to, FL_PATH_MAX, from); }
inline int fl_filename_absolute(char *to, const char *from) { return fl_filename_absolute(to, FL_PATH_MAX, from); }
inline int fl_filename_relative(char *to, const char *from) { return fl_filename_relative(to, FL_PATH_MAX, from); }
#  endif /* __cplusplus */


#  if defined(WIN32) && !defined(__CYGWIN__) && !defined(__WATCOMC__)

struct dirent {char d_name[1];};

#  elif defined(__APPLE__) && defined(__PROJECTBUILDER__)

/* Apple's ProjectBuilder has the nasty habit of including recursively
 * down the file tree. To avoid re-including <FL/dirent.h> we must 
 * directly include the systems math file. (Plus, I could not find a 
 * predefined macro for ProjectBuilder builds, so we have to define it 
 * in the project)
 */
#    include <sys/types.h>
#    include "/usr/include/dirent.h"

#  elif defined(__WATCOMC__)
#    include <sys/types.h>
#    include <direct.h>

#  else
/*
 * WARNING: on some systems (very few nowadays?) <dirent.h> may not exist.
 * The correct information is in one of these files:
 *
 *     #include <sys/ndir.h>
 *     #include <sys/dir.h>
 *     #include <ndir.h>
 *
 * plus you must do the following #define:
 *
 *     #define dirent direct
 *
 * It would be best to create a <dirent.h> file that does this...
 */
#    include <sys/types.h>
#    include <dirent.h>
#  endif

#  if defined (__cplusplus)
extern "C" {
#  endif /* __cplusplus */

#  if !defined(FL_DOXYGEN)
FL_EXPORT int fl_alphasort(struct dirent **, struct dirent **);
FL_EXPORT int fl_casealphasort(struct dirent **, struct dirent **);
FL_EXPORT int fl_casenumericsort(struct dirent **, struct dirent **);
FL_EXPORT int fl_numericsort(struct dirent **, struct dirent **);
#  endif

  typedef int (Fl_File_Sort_F)(struct dirent **, struct dirent **); /**< File sorting function. \see fl_filename_list() */

#  if defined(__cplusplus)
}

/*
 * Portable "scandir" function.  Ugly but necessary...
 */

FL_EXPORT int fl_filename_list(const char *d, struct dirent ***l,
                               Fl_File_Sort_F *s = fl_numericsort);

/*
 * Generic function to open a Uniform Resource Identifier (URI) using a
 * system-defined program (added in FLTK 1.1.8)
 */

FL_EXPORT int	fl_open_uri(const char *uri, char *msg = (char *)0,
		            int msglen = 0);

#    ifndef FL_DOXYGEN
/*
 * _fl_filename_isdir_quick() is a private function that checks for a
 * trailing slash and assumes that the passed name is a directory if
 * it finds one.  This function is used by Fl_File_Browser and
 * Fl_File_Chooser to avoid extra stat() calls, but is not supported
 * outside of FLTK...
 */
int _fl_filename_isdir_quick(const char *name);
#    endif

#  endif /* __cplusplus */

/*
 * FLTK 1.0.x compatibility definitions...
 */

#  ifdef FLTK_1_0_COMPAT
#    define filename_absolute	fl_filename_absolute
#    define filename_expand	fl_filename_expand
#    define filename_ext	fl_filename_ext
#    define filename_isdir	fl_filename_isdir
#    define filename_list	fl_filename_list
#    define filename_match	fl_filename_match
#    define filename_name	fl_filename_name
#    define filename_relative	fl_filename_relative
#    define filename_setext	fl_filename_setext
#    define numericsort		fl_numericsort
#  endif /* FLTK_1_0_COMPAT */


#endif /* FL_FILENAME_H */

/** @} */

/*
 * End of "$Id: filename.H 6986 2010-01-01 18:30:49Z greg.ercolano $".
 */

/* suggested twin class
// This is the Twin Class to fltk::filename
class filename : public fltk::filename {
public:
  filename(int x, int t, int w, int h, const char *label=0)
  : fltk::filename(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
/*
 * "$Id: filename.H 6986 2010-01-01 18:30:49Z greg.ercolano $"
 *
 * Filename header file for the Fast Light Tool Kit (FLTK).
 *
 * Copyright 1998-2009 by Bill Spitzak and others.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA.
 *
 * Please report all bugs and problems on the following page:
 *
 *     http://www.fltk.org/str.php
 */

#ifndef FL_FILENAME_H
#  define FL_FILENAME_H

#  include "Fl_Export.H"

/** \addtogroup filenames File names and URI utility functions 
    @{ */

#  define FL_PATH_MAX 256 /**< all path buffers should use this length */
/** Gets the file name from a path. 
    Similar to basename(3), exceptions shown below.
    \code
    #include <FL/filename.H>
    [..]
    const char *out;
    out = fl_filename_name("/usr/lib");     // out="lib"
    out = fl_filename_name("/usr/");        // out=""      (basename(3) returns "usr" instead)
    out = fl_filename_name("/usr");         // out="usr"
    out = fl_filename_name("/");            // out=""      (basename(3) returns "/" instead)
    out = fl_filename_name(".");            // out="."
    out = fl_filename_name("..");           // out=".."
    \endcode
    \return a pointer to the char after the last slash, or to \p filename if there is none.
 */
FL_EXPORT const char *fl_filename_name(const char * filename);
FL_EXPORT const char *fl_filename_ext(const char *buf);
FL_EXPORT char *fl_filename_setext(char *to, int tolen, const char *ext);
FL_EXPORT int fl_filename_expand(char *to, int tolen, const char *from);
FL_EXPORT int fl_filename_absolute(char *to, int tolen, const char *from);
FL_EXPORT int fl_filename_relative(char *to, int tolen, const char *from);
FL_EXPORT int fl_filename_match(const char *name, const char *pattern);
FL_EXPORT int fl_filename_isdir(const char *name);

#  if defined(__cplusplus) && !defined(FL_DOXYGEN)
/*
 * Under WIN32, we include filename.H from numericsort.c; this should probably change...
 */

inline char *fl_filename_setext(char *to, const char *ext) { return fl_filename_setext(to, FL_PATH_MAX, ext); }
inline int fl_filename_expand(char *to, const char *from) { return fl_filename_expand(to, FL_PATH_MAX, from); }
inline int fl_filename_absolute(char *to, const char *from) { return fl_filename_absolute(to, FL_PATH_MAX, from); }
inline int fl_filename_relative(char *to, const char *from) { return fl_filename_relative(to, FL_PATH_MAX, from); }
#  endif /* __cplusplus */


#  if defined(WIN32) && !defined(__CYGWIN__) && !defined(__WATCOMC__)

struct dirent {char d_name[1];};

#  elif defined(__APPLE__) && defined(__PROJECTBUILDER__)

/* Apple's ProjectBuilder has the nasty habit of including recursively
 * down the file tree. To avoid re-including <FL/dirent.h> we must 
 * directly include the systems math file. (Plus, I could not find a 
 * predefined macro for ProjectBuilder builds, so we have to define it 
 * in the project)
 */
#    include <sys/types.h>
#    include "/usr/include/dirent.h"

#  elif defined(__WATCOMC__)
#    include <sys/types.h>
#    include <direct.h>

#  else
/*
 * WARNING: on some systems (very few nowadays?) <dirent.h> may not exist.
 * The correct information is in one of these files:
 *
 *     #include <sys/ndir.h>
 *     #include <sys/dir.h>
 *     #include <ndir.h>
 *
 * plus you must do the following #define:
 *
 *     #define dirent direct
 *
 * It would be best to create a <dirent.h> file that does this...
 */
#    include <sys/types.h>
#    include <dirent.h>
#  endif

#  if defined (__cplusplus)
extern "C" {
#  endif /* __cplusplus */

#  if !defined(FL_DOXYGEN)
FL_EXPORT int fl_alphasort(struct dirent **, struct dirent **);
FL_EXPORT int fl_casealphasort(struct dirent **, struct dirent **);
FL_EXPORT int fl_casenumericsort(struct dirent **, struct dirent **);
FL_EXPORT int fl_numericsort(struct dirent **, struct dirent **);
#  endif

  typedef int (Fl_File_Sort_F)(struct dirent **, struct dirent **); /**< File sorting function. \see fl_filename_list() */

#  if defined(__cplusplus)
}

/*
 * Portable "scandir" function.  Ugly but necessary...
 */

FL_EXPORT int fl_filename_list(const char *d, struct dirent ***l,
                               Fl_File_Sort_F *s = fl_numericsort);

/*
 * Generic function to open a Uniform Resource Identifier (URI) using a
 * system-defined program (added in FLTK 1.1.8)
 */

FL_EXPORT int	fl_open_uri(const char *uri, char *msg = (char *)0,
		            int msglen = 0);

#    ifndef FL_DOXYGEN
/*
 * _fl_filename_isdir_quick() is a private function that checks for a
 * trailing slash and assumes that the passed name is a directory if
 * it finds one.  This function is used by Fl_File_Browser and
 * Fl_File_Chooser to avoid extra stat() calls, but is not supported
 * outside of FLTK...
 */
int _fl_filename_isdir_quick(const char *name);
#    endif

#  endif /* __cplusplus */

/*
 * FLTK 1.0.x compatibility definitions...
 */

#  ifdef FLTK_1_0_COMPAT
#    define filename_absolute	fl_filename_absolute
#    define filename_expand	fl_filename_expand
#    define filename_ext	fl_filename_ext
#    define filename_isdir	fl_filename_isdir
#    define filename_list	fl_filename_list
#    define filename_match	fl_filename_match
#    define filename_name	fl_filename_name
#    define filename_relative	fl_filename_relative
#    define filename_setext	fl_filename_setext
#    define numericsort		fl_numericsort
#  endif /* FLTK_1_0_COMPAT */


#endif /* FL_FILENAME_H */

/** @} */

/*
 * End of "$Id: filename.H 6986 2010-01-01 18:30:49Z greg.ercolano $".
 */
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
// "$Id: filename.h 6483 2008-10-22 07:01:02Z spitzak $"

/* Copyright 1998-2006 by Bill Spitzak and others.
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
 *
 * These functions are not in the fltk namespace because they really
 * should not be part of fltk. They are used by the file chooser.
 * THESE FUNCTIONS MAY BE CHANGED OR DELETED IN FUTURE VERSIONS. DO
 * NOT USE THEM, AS THEY ARE NOT AN OFFICIAL PART OF fltk!
 */

#ifndef fltk_filename_h
#define fltk_filename_h

#include "FL_API.h"

////////////////////////////////////////////////////////////////
#ifndef DOXYGEN
// dirent (what a pain)...

// FC: UNDER WIN32/VC6 long long is undefined, so use __int64 instead
//  for cross platform type compatibility though in fact VC6 uses 
//  a 32 bit long to calculate size in the stat struct so don't expect
//  to handle >4GB files here...
#if defined(_WIN32) && !defined(__CYGWIN__) && !defined(__MINGW32__) && (_MSC_VER==1200)
typedef unsigned __int64 FL_FILESIZE_T;
#else
typedef unsigned long long FL_FILESIZE_T;
#endif

#if defined(__WATCOMC__)

# include <sys/types.h>
# include "direct.h"

#elif defined(_WIN32) && !defined(__CYGWIN__) && !defined(__MINGW32__)
// Dummy version used on win32 that just holds a name:

struct dirent {char d_name[1];};

#elif defined(__linux)
// Newest Linux libc is broken when it emulates the 32-bit dirent, it
// generates errors when the data like the inode number does not fit, even
// though we are not going to look at anything other than the name. This
// code seems to force the 64-bit version to be used:

# ifndef _GNU_SOURCE
#  define _GNU_SOURCE
# endif
# include <features.h>
# include <sys/types.h>
# include <dirent.h>
# if defined(__GLIBC_PREREQ)
#  if __GLIBC_PREREQ(2,3)
#   define dirent dirent64
#   define scandir scandir64
#  endif
# endif

#else
// warning: on some systems (very few nowadays?) <dirent.h> may not exist.
// The correct information is in one of these three files:
//  #include <sys/ndir.h>
//  #include <sys/dir.h>
//  #include <ndir.h>
// plus you must do the following #define:
//  #define dirent direct
// I recommend you create a /usr/include/dirent.h containing the correct info

# include <sys/types.h>
# include <dirent.h>

#endif

#ifndef PATH_MAX
# ifdef _MAX_PATH
#  define PATH_MAX _MAX_PATH
# else
#  define PATH_MAX 1024
# endif
#endif

#endif
////////////////////////////////////////////////////////////////

namespace fltk {

/// \name fltk/filename.h
/// Some functions to manipulate filenames, to make portable programs.
//@{

FL_API int filename_absolute(char *to, int tolen, const char *from, const char* cwd=0);
FL_API int filename_relative(char *to, int tolen, const char *from, const char* cwd=0);
FL_API const char *filename_name(const char *);
inline char* filename_name(char* a) {return (char*)(filename_name((const char*)a));}
FL_API const char *filename_ext(const char *);
inline char* filename_ext(char* a) {return (char*)(filename_ext((const char*)a));}
FL_API bool filename_match(const char *, const char *pattern); // glob match
FL_API bool filename_exist(const char*);
FL_API bool filename_isdir(const char*);
FL_API FL_FILESIZE_T filename_size(const char *); // return size of file
FL_API long int filename_mtime(const char *); // return modification time

typedef int (File_Sort_F)(const dirent*const*, const dirent*const*);
FL_API int alphasort(const dirent*const*, const dirent*const*);
FL_API int casealphasort(const dirent*const*, const dirent*const*);
FL_API int casenumericsort(const dirent*const*, const dirent*const*);
FL_API int numericsort(const dirent*const*, const dirent*const*);
FL_API int filename_list(const char *d, dirent ***list, File_Sort_F *sort);
FL_API int filename_list(const char *d, dirent ***list); // uses numericsort

//@}

}

#endif

// End of "$Id: filename.h 6483 2008-10-22 07:01:02Z spitzak $".
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
