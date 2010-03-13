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
// "$Id: gl.h 6749 2009-04-09 20:44:31Z engelsman $"
//
// OpenGL header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2009 by Bill Spitzak and others.
//
// You must include this instead of GL/gl.h to get the Microsoft
// APIENTRY stuff included (from <windows.h>) prior to the OpenGL
// header files.
//
// This file also provides "missing" OpenGL functions, and
// gl_start() and gl_finish() to allow OpenGL to be used in any window
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

/** \file gl.h
 *  This file defines wrapper functions for OpenGL in FLTK
 *
 *  To use OpenGL from within an FLTK application you MUST use gl_visual()
 *  to select the default visual before doing show() on any windows. Mesa
 *  will crash if yoy try to use a visual not returned by glxChooseVidual.
 *
 *  This does not work with Fl_Double_Window's!  It will try to draw
 *  into the front buffer.  Depending on the system this will either
 *  crash or do nothing (when pixmaps are being used as back buffer
 *  and GL is being done by hardware), work correctly (when GL is done
 *  with software, such as Mesa), or draw into the front buffer and
 *  be erased when the buffers are swapped (when double buffer hardware
 *  is being used)
 */

#ifndef FL_gl_H
#  define FL_gl_H

#  include "Enumerations.H" // for color names
#  ifdef WIN32
#    include <windows.h>
#  endif
#  ifndef APIENTRY
#    if defined(__CYGWIN__)
#      define APIENTRY __attribute__ ((__stdcall__))
#    else
#      define APIENTRY
#    endif
#  endif

#  ifdef __APPLE__
#    include <OpenGL/gl.h>
#  else
#    include <GL/gl.h>
#  endif

FL_EXPORT void gl_start();
FL_EXPORT void gl_finish();

FL_EXPORT void gl_color(Fl_Color i);
/** back compatability */
inline void gl_color(int c) {gl_color((Fl_Color)c);}

FL_EXPORT void gl_rect(int x,int y,int w,int h);
/**
  Fills the given rectangle with the current color.
  \see gl_rect(int x, int y, int w, int h)
  */
inline void gl_rectf(int x,int y,int w,int h) {glRecti(x,y,x+w,y+h);}

FL_EXPORT void gl_font(int fontid, int size);
FL_EXPORT int  gl_height();
FL_EXPORT int  gl_descent();
FL_EXPORT double gl_width(const char *);
FL_EXPORT double gl_width(const char *, int n);
FL_EXPORT double gl_width(uchar);

FL_EXPORT void gl_draw(const char*);
FL_EXPORT void gl_draw(const char*, int n);
FL_EXPORT void gl_draw(const char*, int x, int y);
FL_EXPORT void gl_draw(const char*, float x, float y);
FL_EXPORT void gl_draw(const char*, int n, int x, int y);
FL_EXPORT void gl_draw(const char*, int n, float x, float y);
FL_EXPORT void gl_draw(const char*, int x, int y, int w, int h, Fl_Align);
FL_EXPORT void gl_measure(const char*, int& x, int& y);

FL_EXPORT void gl_draw_image(const uchar *, int x,int y,int w,int h, int d=3, int ld=0);

#endif // !FL_gl_H

//
// End of "$Id: gl.h 6749 2009-04-09 20:44:31Z engelsman $".
//

/* suggested twin class
// This is the Twin Class to fltk::gl
class gl : public fltk::gl {
public:
  gl(int x, int t, int w, int h, const char *label=0)
  : fltk::gl(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: gl.h 6749 2009-04-09 20:44:31Z engelsman $"
//
// OpenGL header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2009 by Bill Spitzak and others.
//
// You must include this instead of GL/gl.h to get the Microsoft
// APIENTRY stuff included (from <windows.h>) prior to the OpenGL
// header files.
//
// This file also provides "missing" OpenGL functions, and
// gl_start() and gl_finish() to allow OpenGL to be used in any window
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

/** \file gl.h
 *  This file defines wrapper functions for OpenGL in FLTK
 *
 *  To use OpenGL from within an FLTK application you MUST use gl_visual()
 *  to select the default visual before doing show() on any windows. Mesa
 *  will crash if yoy try to use a visual not returned by glxChooseVidual.
 *
 *  This does not work with Fl_Double_Window's!  It will try to draw
 *  into the front buffer.  Depending on the system this will either
 *  crash or do nothing (when pixmaps are being used as back buffer
 *  and GL is being done by hardware), work correctly (when GL is done
 *  with software, such as Mesa), or draw into the front buffer and
 *  be erased when the buffers are swapped (when double buffer hardware
 *  is being used)
 */

#ifndef FL_gl_H
#  define FL_gl_H

#  include "Enumerations.H" // for color names
#  ifdef WIN32
#    include <windows.h>
#  endif
#  ifndef APIENTRY
#    if defined(__CYGWIN__)
#      define APIENTRY __attribute__ ((__stdcall__))
#    else
#      define APIENTRY
#    endif
#  endif

#  ifdef __APPLE__
#    include <OpenGL/gl.h>
#  else
#    include <GL/gl.h>
#  endif

FL_EXPORT void gl_start();
FL_EXPORT void gl_finish();

FL_EXPORT void gl_color(Fl_Color i);
/** back compatability */
inline void gl_color(int c) {gl_color((Fl_Color)c);}

FL_EXPORT void gl_rect(int x,int y,int w,int h);
/**
  Fills the given rectangle with the current color.
  \see gl_rect(int x, int y, int w, int h)
  */
inline void gl_rectf(int x,int y,int w,int h) {glRecti(x,y,x+w,y+h);}

FL_EXPORT void gl_font(int fontid, int size);
FL_EXPORT int  gl_height();
FL_EXPORT int  gl_descent();
FL_EXPORT double gl_width(const char *);
FL_EXPORT double gl_width(const char *, int n);
FL_EXPORT double gl_width(uchar);

FL_EXPORT void gl_draw(const char*);
FL_EXPORT void gl_draw(const char*, int n);
FL_EXPORT void gl_draw(const char*, int x, int y);
FL_EXPORT void gl_draw(const char*, float x, float y);
FL_EXPORT void gl_draw(const char*, int n, int x, int y);
FL_EXPORT void gl_draw(const char*, int n, float x, float y);
FL_EXPORT void gl_draw(const char*, int x, int y, int w, int h, Fl_Align);
FL_EXPORT void gl_measure(const char*, int& x, int& y);

FL_EXPORT void gl_draw_image(const uchar *, int x,int y,int w,int h, int d=3, int ld=0);

#endif // !FL_gl_H

//
// End of "$Id: gl.h 6749 2009-04-09 20:44:31Z engelsman $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
// "$Id: gl.h 6233 2008-09-14 07:54:06Z spitzak $"
// Copyright 1998-2006 by Bill Spitzak and others.
//
// You must include this instead of GL/gl.h to get the Microsoft
// APIENTRY stuff included (from <windows.h>) prior to the OpenGL
// header files.
//
// This file also provides "missing" OpenGL functions, and
// gl_start() and gl_finish() to allow OpenGL to be used in any window
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

/*! \file
  Portably include the OpenGL header files, and define a few OpenGL
  drawing functions provided by fltk. You may want to use the
  OpenGL Extension Wrangler (glew), which will make it much easier
  to call modern OpenGL extensions. If so, include glew.h before
  this file, or define USE_GLEW to 1 before including this.
*/

#ifndef gl_draw_H
#define gl_draw_H

#ifndef DOXYGEN
#include "Color.h"
#include "Flags.h"

#if USE_GLEW
# include <GL/glew.h>
#elif defined(__GLEW_H__)
  /* do nothing if they included glew.h */
#else

# define GL_GLEXT_PROTOTYPES 1
# ifdef _WIN32
#  include <windows.h>
#  undef OPAQUE
#  undef DELETE
#  undef ERROR
#  undef IN
#  undef OUT
#  undef POINT
#  undef far
#  undef max
#  undef min
#  undef near
#  include <GL/gl.h>
# elif defined(__APPLE__)
#  ifndef APIENTRY
#   define APIENTRY
#  endif
#  include <OpenGL/gl.h>
# else
#  include <GL/gl.h>
# endif

# if !defined(GL_VERSION_1_4) || defined(DOXYGEN)
FL_GL_API void glWindowPos2i(int x, int y);
# endif

#endif
#endif

namespace fltk {

struct Font;

/// \name fltk/gl.h
//@{

FL_GL_API void glstart();
FL_GL_API void glfinish();

FL_GL_API void glsetcolor(Color);

FL_GL_API void glstrokerect(int x,int y,int w,int h);
inline void glfillrect(int x,int y,int w,int h) {glRecti(x,y,x+w,y+h);}

FL_GL_API void glsetfont(Font* f, float size);
FL_GL_API float glgetascent();
FL_GL_API float glgetdescent();
FL_GL_API float glgetwidth(const char *);
FL_GL_API float glgetwidth(const char *, int n);

FL_GL_API void gldrawtext(const char*);
FL_GL_API void gldrawtext(const char*, int n);
FL_GL_API void gldrawtext(const char*, float x, float y, float z = 0);
FL_GL_API void gldrawtext(const char*, int n, float x, float y, float z = 0);

FL_GL_API void gldrawimage(const uchar *, int x,int y,int w,int h, int d=3, int ld=0);

//@}

}
#endif

//
// End of "$Id: gl.h 6233 2008-09-14 07:54:06Z spitzak $".
//
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
