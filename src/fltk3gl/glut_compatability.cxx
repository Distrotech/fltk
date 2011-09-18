//
// "$Id: glut_compatability.cxx 8991 2011-08-22 15:21:44Z matt $"
//
// GLUT emulation routines for the Fast Light Tool Kit (FLTK).
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

// Emulation of Glut using fltk.

// GLUT is Copyright (c) Mark J. Kilgard, 1994, 1995, 1996.
// "This program is freely distributable without licensing fees  and is
// provided without guarantee or warrantee expressed or  implied. This
// program is -not- in the public domain."

// Although I have copied the GLUT API, none of my code is based on
// any Glut implementation details and is therefore covered by the LGPL.

#include "../fltk3/flstring.h"
#if HAVE_GL

#  include <fltk3gl/glut.h>
#  ifdef HAVE_GLXGETPROCADDRESSARB
#    define GLX_GLXEXT_LEGACY
#    include <GL/glx.h>
#  endif // HAVE_GLXGETPROCADDRESSARB
#  ifdef HAVE_DLFCN_H
#    include <dlfcn.h>
#  endif // HAVE_DLFCN_H
#  define MAXWINDOWS 32
#include <fltk3/Wrapper.h>

static fltk3::GlutWindow *windows[MAXWINDOWS+1];

static void (*glut_idle_func)() = 0; // global glut idle function

fltk3::GlutWindow *glut_window;
int glut_menu;
void (*glut_menustate_function)(int);
void (*glut_menustatus_function)(int,int,int);

static void default_reshape(int w, int h) {glViewport(0,0,w,h);}
static void default_display() {}

void fltk3::GlutWindow::make_current() {
  glut_window = this;
  if (shown()) GLWindow::make_current();
}

static int indraw;
void fltk3::GlutWindow::draw() {
  glut_window = this;
  indraw = 1;
  if (!valid()) {reshape(w(),h()); valid(1);}
  display();
  indraw = 0;
}

void glutSwapBuffers() {
  if (!indraw) glut_window->swap_buffers();
}

void fltk3::GlutWindow::draw_overlay() {
  glut_window = this;
  if (!valid()) {reshape(w(),h()); valid(1);}
  overlaydisplay();
}

static void domenu(int, int, int);

int fltk3::GlutWindow::handle(int event) {
  make_current();
  int ex = fltk3::event_x();
  int ey = fltk3::event_y();
  int button;
  switch (event) {

  case fltk3::PUSH:
    if (keyboard || special) fltk3::focus(this);
    button = fltk3::event_button()-1;
    if (button<0) button = 0;
    if (button>2) button = 2;
    if (menu[button]) {domenu(menu[button],ex,ey); return 1;}
    mouse_down |= 1<<button;
    if (mouse) {mouse(button,GLUT_DOWN,ex,ey); return 1;}
    if (motion) return 1;
    break;

  case fltk3::MOUSEWHEEL:
    button = fltk3::event_dy();
    while (button < 0) {if (mouse) mouse(3,GLUT_DOWN,ex,ey); ++button;}
    while (button > 0) {if (mouse) mouse(4,GLUT_DOWN,ex,ey); --button;}
    return 1;

  case fltk3::RELEASE:
    for (button = 0; button < 3; button++) if (mouse_down & (1<<button)) {
      if (mouse) mouse(button,GLUT_UP,ex,ey);
    }
    mouse_down = 0;
    return 1;

  case fltk3::ENTER:
    if (entry) {entry(GLUT_ENTERED); return 1;}
    if (passivemotion) return 1;
    break;

  case fltk3::LEAVE:
    if (entry) {entry(GLUT_LEFT); return 1;}
    if (passivemotion) return 1;
    break;

  case fltk3::DRAG:
    if (motion) {motion(ex, ey); return 1;}
    break;

  case fltk3::MOVE:
    if (passivemotion) {passivemotion(ex, ey); return 1;}
    break;

  case fltk3::FOCUS:
    if (keyboard || special) return 1;
    break;

  case fltk3::SHORTCUT:
    if (!keyboard && !special) break;

  case fltk3::KEYBOARD:
    if (fltk3::event_text()[0]) {
      if (keyboard) {keyboard(fltk3::event_text()[0],ex,ey); return 1;}
      break;
    } else {
      if (special) {
	unsigned k = fltk3::event_key();
	if (k > fltk3::FKey && k <= fltk3::FLastKey) k -= fltk3::FKey;
	special(k,ex,ey);
	return 1;
      }
      break;
    }

  case fltk3::HIDE:
    if (visibility) visibility(GLUT_NOT_VISIBLE);
    break;

  case fltk3::SHOW:
    if (visibility) visibility(GLUT_VISIBLE);
    break;
  }

  return GLWindow::handle(event);
}

static int glut_mode = GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH;

void fltk3::GlutWindow::_init() {
  for (number=1; number<MAXWINDOWS; number++) if (!windows[number]) break;
  windows[number] = this;
  menu[0] = menu[1] = menu[2] = 0;
  reshape = default_reshape;
  display = default_display;
  overlaydisplay = default_display;
  keyboard = 0;
  mouse = 0;
  motion = 0;
  passivemotion = 0;
  entry = 0;
  visibility = 0;
  special = 0;
  mouse_down = 0;
  mode(glut_mode);
}

/** Creates a glut window, registers to the glut windows list.*/
fltk3::GlutWindow::GlutWindow(int W, int H, const char *t) :
  fltk3::GLWindow(W,H,t) {_init();}

/** Creates a glut window, registers to the glut windows list.*/
fltk3::GlutWindow::GlutWindow(int X,int Y,int W,int H, const char *t) :
  fltk3::GLWindow(X,Y,W,H,t) {_init();}

static int initargc;
static char **initargv;

void glutInit(int *argc, char **argv) {
  initargc = *argc;
  initargv = new char*[*argc+1];
  int i,j;
  for (i=0; i<=*argc; i++) initargv[i] = argv[i];
  for (i=j=1; i<*argc; ) {
    if (fltk3::arg(*argc,argv,i));
    else argv[j++] = argv[i++];
  }
  argv[j] = 0;
  *argc = j;
}

void glutInitDisplayMode(unsigned int mode) {
  glut_mode = mode;
}

void glutMainLoop() {fltk3::run();}

////////////////////////////////////////////////////////////////

static int initx=0, inity=0, initw=300, inith=300, initpos=0;

void glutInitWindowPosition(int x, int y) {
  initx = x; inity = y; initpos = 1;
}

void glutInitWindowSize(int w, int h) {
  initw = w; inith = h;
}

int glutCreateWindow(char *title) {
  return glutCreateWindow((const char*)title);
}

int glutCreateWindow(const char *title) {
  fltk3::GlutWindow *W;
  if (initpos) {
    W = new fltk3::GlutWindow(initx,inity,initw,inith,title);
    initpos = 0;
  } else {
    W = new fltk3::GlutWindow(initw,inith,title);
  }
  W->resizable(W);
  if (initargc) {
    W->show(initargc,initargv);
    initargc = 0;
  } else {
    W->show();
  }
  W->valid(0);
  W->context_valid(0);
  W->make_current();
  return W->number;
}

int glutCreateSubWindow(int win, int x, int y, int w, int h) {
  fltk3::GlutWindow *W = new fltk3::GlutWindow(x,y,w,h,0);
  windows[win]->add(W);
  if (windows[win]->shown()) W->show();
  W->make_current();
  return W->number;
}
/** Destroys the glut window, first unregister it from the glut windows list */
fltk3::GlutWindow::~GlutWindow() {
  if (glut_window == this) glut_window = 0;
  windows[number] = 0;
}

void glutDestroyWindow(int win) {
  // should destroy children!!!
  delete windows[win];
}

void glutPostWindowRedisplay(int win) {
  windows[win]->redraw();
}

void glutSetWindow(int win) {
  windows[win]->make_current();
}

////////////////////////////////////////////////////////////////
#include <fltk3/MenuItem.h>

struct menu {
  void (*cb)(int);
  fltk3::MenuItem *m;
  int size;
  int alloc;
};

#define MAXMENUS 32
static menu menus[MAXMENUS+1];

static void domenu(int n, int ex, int ey) {
  glut_menu = n;
  menu *m = &menus[n];
  if (glut_menustate_function) glut_menustate_function(1);
  if (glut_menustatus_function) glut_menustatus_function(1,ex,ey);
  const fltk3::MenuItem* g = m->m->popup(fltk3::event_x(), fltk3::event_y(), 0);
  if (g && g->callback_) ((void (*)(int))(g->callback_))(int(g->argument()));
  if (glut_menustatus_function) glut_menustatus_function(0,ex,ey);
  if (glut_menustate_function) glut_menustate_function(0);
}

int glutCreateMenu(void (*cb)(int)) {
  int i;
  for (i=1; i<MAXMENUS; i++) if (!menus[i].cb) break;
  menu *m = &menus[i];
  m->cb = cb;
  return glut_menu = i;
}

void glutDestroyMenu(int n) {
  menu *m = &menus[n];
  delete[] m->m;
  m->m = 0;
  m->cb = 0;
  m->size = m->alloc = 0;
}

static fltk3::MenuItem* additem(menu *m) {
  if (m->size+1 >= m->alloc) {
    m->alloc = m->size*2+10;
    fltk3::MenuItem* nm = new fltk3::MenuItem[m->alloc];
    for (int i=0; i<m->size; i++) nm[i] = m->m[i];
    delete[] m->m;
    m->m = nm;
  }
  int n = m->size++;
  m->m[n+1].text = 0;
  fltk3::MenuItem* i = &(m->m[n]);
  i->shortcut_ = 0;
  i->flags = 0;
  i->labeltype_ = i->labelfont_ = i->labelsize_ = i->labelcolor_ = 0;
  return i;
}

void glutAddMenuEntry(char *label, int value) {
  menu *m = &menus[glut_menu];
  fltk3::MenuItem* i = additem(m);
  i->text = label;
  i->callback_ = (fltk3::Callback*)(m->cb);
  i->user_data_ = (void *)value;
}

void glutAddSubMenu(char *label, int submenu) {
  menu *m = &menus[glut_menu];
  fltk3::MenuItem* i = additem(m);
  i->text = label;
  i->callback_ = 0;
  i->user_data_ = (void *)(menus[submenu].m);
  i->flags = fltk3::SUBMENU;
}

void glutChangeToMenuEntry(int item, char *label, int value) {
  menu *m = &menus[glut_menu];
  fltk3::MenuItem* i = &m->m[item-1];
  i->text = label;
  i->callback_ = (fltk3::Callback*)(m->cb);
  i->user_data_ = (void *)value;
  i->flags = 0;
}

void glutChangeToSubMenu(int item, char *label, int submenu) {
  menu *m = &menus[glut_menu];
  fltk3::MenuItem* i = &m->m[item-1];
  i->text = label;
  i->callback_ = 0;
  i->user_data_ = (void *)(menus[submenu].m);
  i->flags = fltk3::SUBMENU;
}

void glutRemoveMenuItem(int item) {
  menu *m = &menus[glut_menu];
  if (item > m->size || item < 1) return;
  for (int i = item-1; i <= m->size; i++) m->m[i] = m->m[i+1];
  m->size--;
}

////////////////////////////////////////////////////////////////

int glutGet(GLenum type) {
  switch (type) {
  case GLUT_RETURN_ZERO: return 0;
  case GLUT_WINDOW_X: return glut_window->x();
  case GLUT_WINDOW_Y: return glut_window->y();
  case GLUT_WINDOW_WIDTH: return glut_window->w();
  case GLUT_WINDOW_HEIGHT: return glut_window->h();
  case GLUT_WINDOW_PARENT:
    if (glut_window->parent())
      return ((fltk3::GlutWindow *)(glut_window->parent()))->number;
    else
      return 0;
//case GLUT_WINDOW_NUM_CHILDREN:
//case GLUT_WINDOW_CURSOR: return 
  case GLUT_SCREEN_WIDTH: return fltk3::w();
  case GLUT_SCREEN_HEIGHT: return fltk3::h();
//case GLUT_SCREEN_WIDTH_MM:
//case GLUT_SCREEN_HEIGHT_MM:
  case GLUT_MENU_NUM_ITEMS: return menus[glut_menu].size;
  case GLUT_DISPLAY_MODE_POSSIBLE: return fltk3::GLWindow::can_do(glut_mode);
  case GLUT_INIT_WINDOW_X: return initx;
  case GLUT_INIT_WINDOW_Y: return inity;
  case GLUT_INIT_WINDOW_WIDTH: return initw;
  case GLUT_INIT_WINDOW_HEIGHT: return inith;
  case GLUT_INIT_DISPLAY_MODE: return glut_mode;
//case GLUT_ELAPSED_TIME:
  case GLUT_WINDOW_BUFFER_SIZE:
    if (glutGet(GLUT_WINDOW_RGBA))
      return glutGet(GLUT_WINDOW_RED_SIZE)+
	glutGet(GLUT_WINDOW_GREEN_SIZE)+
	glutGet(GLUT_WINDOW_BLUE_SIZE)+
	glutGet(GLUT_WINDOW_ALPHA_SIZE);
    else
      return glutGet(GLUT_WINDOW_COLORMAP_SIZE);
  case GLUT_VERSION: return 20400;
  default: {GLint p; glGetIntegerv(type, &p); return p;}
  }
}

int glutLayerGet(GLenum type) {
  switch (type) {
  case GLUT_OVERLAY_POSSIBLE: return glut_window->can_do_overlay();
//case GLUT_LAYER_IN_USE:
//case GLUT_HAS_OVERLAY:
  case GLUT_TRANSPARENT_INDEX: return 0; // true for SGI
  case GLUT_NORMAL_DAMAGED: return glut_window->damage();
  case GLUT_OVERLAY_DAMAGED: return 1; // kind of works...
  default: return 0;
  }
}

int glutDeviceGet(GLenum type) {
  switch (type) {
    case GLUT_HAS_KEYBOARD : return 1;
    case GLUT_HAS_MOUSE : return 1;
    case GLUT_NUM_MOUSE_BUTTONS : return 3;
    default : return 0;
  }
}

// Get extension function address...
GLUTproc glutGetProcAddress(const char *procName) {
#  ifdef WIN32
  return (GLUTproc)wglGetProcAddress((LPCSTR)procName);

#  elif defined(HAVE_DLSYM) && defined(HAVE_DLFCN_H)
  char symbol[1024];

  snprintf(symbol, sizeof(symbol), "_%s", procName);

#    ifdef RTLD_DEFAULT
  return (GLUTproc)dlsym(RTLD_DEFAULT, symbol);

#    else // No RTLD_DEFAULT support, so open the current a.out symbols...
  static void *rtld_default = 0;

  if (!rtld_default) rtld_default = dlopen(0, RTLD_LAZY);

  if (rtld_default) return (GLUTproc)dlsym(rtld_default, symbol);
  else return 0;

#    endif // RTLD_DEFAULT

#  elif defined(HAVE_GLXGETPROCADDRESSARB)
  return (GLUTproc)glXGetProcAddressARB((const GLubyte *)procName);

#  else
  return (GLUTproc)0;
#  endif // WIN32
}

// Parse the GL_EXTENSIONS string to see if the named extension is
// supported.
//
// This code was copied from FreeGLUT 2.4.0 which carries the
// following notice:
//
//     Copyright (c) 1999-2000 Pawel W. Olszta. All Rights Reserved.
int glutExtensionSupported( const char* extension )
{
  if (!extension || strchr(extension, ' ')) return 0;

  const char *extensions, *start;
  const int len = strlen( extension );
  
  start = extensions = (const char *) glGetString(GL_EXTENSIONS);

  if (!extensions) return 0;

  for (;;) {
    const char *p = strstr(extensions, extension);
    if (!p) return 0;  /* not found */
    /* check that the match isn't a super string */
    if ((p == start || p[-1] == ' ') &&
        (p[len] == ' ' || p[len] == 0)) return 1;
    /* skip the false match and continue */
    extensions = p + len;
  }
}

// Add a mechanism to handle adding/removing the glut idle function
// without depending on the (deprecated) set_idle method.
void glutIdleFunc(void (*f)())
{
  // no change
  if(glut_idle_func == f) return;
  // remove current idle
  if(glut_idle_func) fltk3::remove_idle((void (*)(void *))glut_idle_func);
  // install new idle func - if one was passed
  if(f) fltk3::add_idle((void (*)(void *))f);
  // record new idle func - even if it is NULL
  glut_idle_func = f;
} // glutIdleFunc

#endif // HAVE_GL

//
// End of "$Id: glut_compatability.cxx 8991 2011-08-22 15:21:44Z matt $".
//
