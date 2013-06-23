//
// "$Id: gl_start.cxx 8991 2011-08-22 15:21:44Z matt $"
//
// OpenGL context routines for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2010 by Bill Spitzak and others.
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

// You MUST use gl_visual() to select the default visual before doing
// show() of any windows.  Mesa will crash if you try to use a visual
// not returned by glxChooseVisual.

// This does not work with fltk3::DoubleWindow's!  It will try to draw
// into the front buffer.  Depending on the system this will either
// crash or do nothing (when pixmaps are being used as back buffer
// and GL is being done by hardware), work correctly (when GL is done
// with software, such as Mesa), or draw into the front buffer and
// be erased when the buffers are swapped (when double buffer hardware
// is being used)

#include <config.h>

#if HAVE_GL

#include <fltk3/run.h>
#include <fltk3/Window.h>
#include <fltk3/x.h>
#include <fltk3/draw.h>
#include "GLChoice.h"

static GLContext context;
static int clip_state_number=-1;
static int pw, ph;

#ifdef WIN32
static fltk3::GLChoice* gl_choice;
#endif

#ifdef __APPLE__
static fltk3::GLChoice* gl_choice;
#endif

fltk3::Region XRectangleRegion(int x, int y, int w, int h); // in fltk3::rect.cxx

/** Creates an OpenGL context */
void gl_start() {
  if (!context) {
#if defined(USE_X11)
    context = fl_create_gl_context(fl_visual);
#elif defined(WIN32)
    if (!gl_choice) fltk3::gl_visual(0);
    context = fl_create_gl_context(fltk3::Window::current(), gl_choice);
#elif defined(__APPLE_QUARTZ__)
    // warning: the Quartz version should probably use Core GL (CGL) instead of AGL
    context = fl_create_gl_context(fltk3::Window::current(), gl_choice);
#else
#  error Unsupported platform
#endif
  }
  fl_set_gl_context(fltk3::Window::current(), context);
#if !defined(WIN32) && !defined(__APPLE__)
  glXWaitX();
#endif
  if (pw != fltk3::Window::current()->w() || ph != fltk3::Window::current()->h()) {
    pw = fltk3::Window::current()->w();
    ph = fltk3::Window::current()->h();
    glLoadIdentity();
    glViewport(0, 0, pw, ph);
    glOrtho(0, pw, 0, ph, -1, 1);
    glDrawBuffer(GL_FRONT);
  }
  if (clip_state_number != fltk3::graphics_driver->fl_clip_state_number) {
    clip_state_number = fltk3::graphics_driver->fl_clip_state_number;
    int x, y, w, h;
    if (fltk3::clip_box(0, 0, fltk3::Window::current()->w(), fltk3::Window::current()->h(),
		    x, y, w, h)) {
      fltk3::clip_region(XRectangleRegion(x,y,w,h));
      glScissor(x, fltk3::Window::current()->h()-(y+h), w, h);
      glEnable(GL_SCISSOR_TEST);
    } else {
      glDisable(GL_SCISSOR_TEST);
    }
  }
}

/** Releases an OpenGL context */
void gl_finish() {
  glFlush();
#if !defined(WIN32) && !defined(__APPLE__)
  glXWaitGL();
#endif
}

int fltk3::gl_visual(int mode, int *alist) {
  fltk3::GLChoice *c = fltk3::GLChoice::find(mode,alist);
  if (!c) return 0;
#if defined(USE_X11)
  fl_visual = c->vis;
  fl_colormap = c->colormap;
#elif defined(WIN32)
  gl_choice = c;
#elif defined(__APPLE_QUARTZ__)
  // warning: the Quartz version should probably use Core GL (CGL) instead of AGL
  gl_choice = c;
#else
#  error Unsupported platform
#endif
  return 1;
}
#endif

//
// End of "$Id: gl_start.cxx 8991 2011-08-22 15:21:44Z matt $".
//
