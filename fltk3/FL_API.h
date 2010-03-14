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
 * "$Id: Fl_Export.H 6614 2009-01-01 16:11:32Z matt $"
 *
 * WIN32 DLL export .
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

#ifndef Fl_Export_H
#  define Fl_Export_H

/*
 * The following is only used when building DLLs under WIN32...
 */

#  if defined(FL_DLL) && (defined(_MSC_VER) || defined(__MWERKS__) || defined(__BORLANDC__) || __GNUC__ >= 3)
#    ifdef FL_LIBRARY
#      define FL_EXPORT	__declspec(dllexport)
#    else
#      define FL_EXPORT	__declspec(dllimport)
#    endif /* FL_LIBRARY */
#  else
#    define FL_EXPORT
#  endif /* FL_DLL */


#if _MSC_VER > 1000
# pragma once
// suppress vc2005 warnings: 
// C4312 because we have no problem to cast a smaller type to a greater (potentially 64bit) one
// and C4996 (deprecated C-lib calls like strcpy that should be _strcpy, etc ...)
# pragma warning(disable:4312 4996)
#endif

#if !defined(DOXYGEN) && defined(_WIN32) && defined(FL_SHARED)
#  ifdef FL_LIBRARY
#    define FL_API	__declspec(dllexport)
#  else
#    define FL_API	__declspec(dllimport)
#  endif
#  ifdef FL_IMAGES_LIBRARY
#    define FL_IMAGES_API	__declspec(dllexport)
#  else
#    define FL_IMAGES_API	__declspec(dllimport)
#  endif
#  ifdef FL_GLUT_LIBRARY
#    define FL_GLUT_API		__declspec(dllexport)
#  else
#    define FL_GLUT_API		__declspec(dllimport)
#  endif
#  ifdef FL_FORMS_LIBRARY
#    define FL_FORMS_API	__declspec(dllexport)
#  else
#    define FL_FORMS_API	__declspec(dllimport)
#  endif
#  ifdef FL_GL_LIBRARY
#    define FL_GL_API		__declspec(dllexport)
#  else
#    define FL_GL_API		__declspec(dllimport)
#  endif
#else
#  define FL_API
#  define FL_IMAGES_API
#  define FL_GLUT_API
#  define FL_FORMS_API
#  define FL_GL_API
#endif

// typedef unsigned char uchar;

#endif /* !Fl_Export_H */


// ----- FLTK1 -----------------------------------------------------------------
#if 0
/*
 * "$Id: Fl_Export.H 6614 2009-01-01 16:11:32Z matt $"
 *
 * WIN32 DLL export .
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

#ifndef Fl_Export_H
#  define Fl_Export_H

/*
 * The following is only used when building DLLs under WIN32...
 */

#  if defined(FL_DLL) && (defined(_MSC_VER) || defined(__MWERKS__) || defined(__BORLANDC__) || __GNUC__ >= 3)
#    ifdef FL_LIBRARY
#      define FL_EXPORT	__declspec(dllexport)
#    else
#      define FL_EXPORT	__declspec(dllimport)
#    endif /* FL_LIBRARY */
#  else
#    define FL_EXPORT
#  endif /* FL_DLL */

#endif /* !Fl_Export_H */

/*
 * End of "$Id: Fl_Export.H 6614 2009-01-01 16:11:32Z matt $".
 */
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
// "$Id: FL_API.h 5448 2006-09-19 01:14:07Z spitzak $"
//
// This file is included by all FLTK header files. Originally it was to
// get that damn dllimport/export stuff on Windows. It now also turns
// off warnings on Windows so that you can use stdc functions, and
// defines the uchar type that is used by FLTK a lot.
//
// Copyright 1998-2006 by Bill Spitzak and others.
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
#ifndef FL_API

#if _MSC_VER > 1000
# pragma once
// suppress vc2005 warnings: 
// C4312 because we have no problem to cast a smaller type to a greater (potentially 64bit) one
// and C4996 (deprecated C-lib calls like strcpy that should be _strcpy, etc ...)
# pragma warning(disable:4312 4996)
#endif

#if !defined(DOXYGEN) && defined(_WIN32) && defined(FL_SHARED)
#  ifdef FL_LIBRARY
#    define FL_API	__declspec(dllexport)
#  else
#    define FL_API	__declspec(dllimport)
#  endif
#  ifdef FL_IMAGES_LIBRARY
#    define FL_IMAGES_API	__declspec(dllexport)
#  else
#    define FL_IMAGES_API	__declspec(dllimport)
#  endif
#  ifdef FL_GLUT_LIBRARY
#    define FL_GLUT_API		__declspec(dllexport)
#  else
#    define FL_GLUT_API		__declspec(dllimport)
#  endif
#  ifdef FL_FORMS_LIBRARY
#    define FL_FORMS_API	__declspec(dllexport)
#  else
#    define FL_FORMS_API	__declspec(dllimport)
#  endif
#  ifdef FL_GL_LIBRARY
#    define FL_GL_API		__declspec(dllexport)
#  else
#    define FL_GL_API		__declspec(dllimport)
#  endif
#else
#  define FL_API
#  define FL_IMAGES_API
#  define FL_GLUT_API
#  define FL_FORMS_API
#  define FL_GL_API
#endif

typedef unsigned char uchar;

#endif

//
// End of "$Id: FL_API.h 5448 2006-09-19 01:14:07Z spitzak $".
//
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
