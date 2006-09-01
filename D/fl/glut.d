/+- This file was imported from C++ using a script
//
// "$Id: glut.H 5327 2006-08-17 13:49:46Z matt $"
//
// GLUT emulation header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2005 by Bill Spitzak and others.
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

// Emulation of GLUT using fltk.

// GLUT is Copyright (c) Mark J. Kilgard, 1994, 1995, 1996:
// "This program is freely distributable without licensing fees  and is
// provided without guarantee or warrantee expressed or  implied. This
// program is -not- in the public domain."

// Although I have copied the GLUT API, none of my code is based on
// any GLUT implementation details and is therefore covered by the LGPL.

// FLTK does not include the GLUT drawing functions (such as
// glutWireTeapot()) or the stroke fonts but the declarations for the
// drawing functions are included here because otherwise there is no
// way to get them along with this.  To use them you will have to
// link in the original GLUT library, put -lglut *after* -lfltk.

// Commented out lines indicate parts of GLUT that are not emulated.

version (!__glut_h__) {
#  define __glut_h__

#  include "gl.h"
//#  include <GL/glu.h>

////////////////////////////////////////////////////////////////
// GLUT is emulated using this window class and these static variables
// (plus several more static variables hidden in glut.C):

public import fl.fl;
public import fl.gl_window;

class Fl_Glut_Window : Fl_Gl_Window {
  void _init();
  int mouse_down;
protected:
  void draw();
  void draw_overlay();
  int handle(int);
public: // so the functions work
  int number;
  int menu[3];
  void make_current();
  void (*display)();
  void (*overlaydisplay)();
  void (*reshape)(int w, int h);
  void (*keyboard)(ubyte, int x, int y);
  void (*mouse)(int b, int state, int x, int y);
  void (*motion)(int x, int y);
  void (*passivemotion)(int x, int y);
  void (*entry)(int);
  void (*visibility)(int);
  void (*special)(int, int x, int y);
  Fl_Glut_Window(int w, int h, char *);
  Fl_Glut_Window(int x, int y, int w, int h, char *);
  ~Fl_Glut_Window();
};

extern Fl_Glut_Window  glut_window;	// the current window
extern int glut_menu;			// the current menu

// function pointers that are not per-window:
extern void (*glut_idle_function)();
extern void (*glut_menustate_function)(int);
extern void (*glut_menustatus_function)(int,int,int);

////////////////////////////////////////////////////////////////

//#  define GLUT_API_VERSION This does not match any version of GLUT exactly...

void glutInit(int *argcp, char **argv); // creates first window

void glutInitDisplayMode(uint mode);
// the FL_ symbols have the same value as the GLUT ones:
const int GLUT_RGB = FL_RGB; 
const int GLUT_RGBA = FL_RGB; 
const int GLUT_INDEX = FL_INDEX; 
const int GLUT_SINGLE = FL_SINGLE; 
const int GLUT_DOUBLE = FL_DOUBLE; 
const int GLUT_ACCUM = FL_ACCUM; 
const int GLUT_ALPHA = FL_ALPHA; 
const int GLUT_DEPTH = FL_DEPTH; 
const int GLUT_STENCIL = FL_STENCIL; 
const int GLUT_MULTISAMPLE = FL_MULTISAMPLE; 
const int GLUT_STEREO = FL_STEREO; 
// #  define GLUT_LUMINANCE		512

void glutInitWindowPosition(int x, int y);

void glutInitWindowSize(int w, int h);

void glutMainLoop();

int glutCreateWindow(char *title);
int glutCreateWindow(char *title);

int glutCreateSubWindow(int win, int x, int y, int width, int height);

void glutDestroyWindow(int win);

void glutPostRedisplay() {glut_window.redraw();}

void glutPostWindowRedisplay(int win);

void glutSwapBuffers();

int glutGetWindow() {return glut_window.number;}

void glutSetWindow(int win);

void glutSetWindowTitle(char *t) {glut_window.label(t);}

void glutSetIconTitle(char *t) {glut_window.iconlabel(t);}

void glutPositionWindow(int x, int y) {glut_window.position(x,y);}

void glutReshapeWindow(int w, int h) {glut_window.size(w,h);}

void glutPopWindow() {glut_window.show();}

//void glutPushWindow();

void glutIconifyWindow() {glut_window.iconize();}

void glutShowWindow() {glut_window.show();}

void glutHideWindow() {glut_window.hide();}

void glutFullScreen() {glut_window.fullscreen();}

void glutSetCursor(Fl_Cursor cursor) {glut_window.cursor(cursor);}
// notice that the numeric values are different than glut:
const int GLUT_CURSOR_RIGHT_ARROW = ((Fl_Cursor)2); 
const int GLUT_CURSOR_LEFT_ARROW = ((Fl_Cursor)67); 
const int GLUT_CURSOR_INFO = FL_CURSOR_HAND; 
const int GLUT_CURSOR_DESTROY = ((Fl_Cursor)45); 
const int GLUT_CURSOR_HELP = FL_CURSOR_HELP; 
const int GLUT_CURSOR_CYCLE = ((Fl_Cursor)26); 
const int GLUT_CURSOR_SPRAY = ((Fl_Cursor)63); 
const int GLUT_CURSOR_WAIT = FL_CURSOR_WAIT; 
const int GLUT_CURSOR_TEXT = FL_CURSOR_INSERT; 
const int GLUT_CURSOR_CROSSHAIR = FL_CURSOR_CROSS; 
const int GLUT_CURSOR_UP_DOWN = FL_CURSOR_NS; 
const int GLUT_CURSOR_LEFT_RIGHT = FL_CURSOR_WE; 
const int GLUT_CURSOR_TOP_SIDE = FL_CURSOR_N; 
const int GLUT_CURSOR_BOTTOM_SIDE = FL_CURSOR_S; 
const int GLUT_CURSOR_LEFT_SIDE = FL_CURSOR_W; 
const int GLUT_CURSOR_RIGHT_SIDE = FL_CURSOR_E; 
const int GLUT_CURSOR_TOP_LEFT_CORNER = FL_CURSOR_NW; 
const int GLUT_CURSOR_TOP_RIGHT_CORNER = FL_CURSOR_NE; 
const int GLUT_CURSOR_BOTTOM_RIGHT_CORNER = FL_CURSOR_SE; 
const int GLUT_CURSOR_BOTTOM_LEFT_CORNER = FL_CURSOR_SW; 
const int GLUT_CURSOR_INHERIT = FL_CURSOR_DEFAULT; 
const int GLUT_CURSOR_NONE = FL_CURSOR_NONE; 
const int GLUT_CURSOR_FULL_CROSSHAIR = FL_CURSOR_CROSS; 

//void glutWarpPointer(int x, int y);

void glutEstablishOverlay() {glut_window.make_overlay_current();}

void glutRemoveOverlay() {glut_window.hide_overlay();}

void glutUseLayer(GLenum layer) {
  layer ? glut_window.make_overlay_current() : glut_window.make_current();}
enum {GLUT_NORMAL, GLUT_OVERLAY};

void glutPostOverlayRedisplay() {glut_window.redraw_overlay();}

void glutShowOverlay() {glut_window.redraw_overlay();}

void glutHideOverlay() {glut_window.hide_overlay();}

int glutCreateMenu(void (*)(int));

void glutDestroyMenu(int menu);

int glutGetMenu() {return glut_menu;}

void glutSetMenu(int m) {glut_menu = m;}

void glutAddMenuEntry(char *label, int value);

void glutAddSubMenu(char *label, int submenu);

void glutChangeToMenuEntry(int item, char *label, int value);

void glutChangeToSubMenu(int item, char *label, int submenu);

void glutRemoveMenuItem(int item);

void glutAttachMenu(int b) {glut_window.menu[b] = glut_menu;}

void glutDetachMenu(int b) {glut_window.menu[b] = 0;}

void glutDisplayFunc(void (*f)()) {glut_window.display = f;}

void glutReshapeFunc(void (*f)(int w, int h)) {glut_window.reshape=f;}

void glutKeyboardFunc(void (*f)(ubyte key, int x, int y)) {
  glut_window.keyboard = f;}

void glutMouseFunc(void (*f)(int b, int state, int x, int y)) {
  glut_window.mouse = f;}
const int GLUT_LEFT_BUTTON = 0; 
const int GLUT_MIDDLE_BUTTON = 1; 
const int GLUT_RIGHT_BUTTON = 2; 
const int GLUT_DOWN = 0; 
const int GLUT_UP = 1; 

void glutMotionFunc(void (*f)(int x, int y)) {glut_window.motion= f;}

void glutPassiveMotionFunc(void (*f)(int x, int y)) {
  glut_window.passivemotion= f;}

void glutEntryFunc(void (*f)(int s)) {glut_window.entry = f;}
enum {GLUT_LEFT, GLUT_ENTERED};

void glutVisibilityFunc(void (*f)(int s)) {glut_window.visibility=f;}
enum {GLUT_NOT_VISIBLE, GLUT_VISIBLE};

void glutIdleFunc(void (*f)()) {Fl.set_idle(f);}

// Warning: this cast may not work on all machines:
void glutTimerFunc(uint msec, void (*f)(int), int value) {
  Fl.add_timeout(msec*.001, (void (*)(void *))f, (void *)value);
}

void glutMenuStateFunc(void (*f)(int state)) {
  glut_menustate_function = f;}

void glutMenuStatusFunc(void (*f)(int status, int x, int y)) {
  glut_menustatus_function = f;}
enum {GLUT_MENU_NOT_IN_USE, GLUT_MENU_IN_USE};

void glutSpecialFunc(void (*f)(int key, int x, int y)) {
  glut_window.special = f;}
const int GLUT_KEY_F1 = 1; 
const int GLUT_KEY_F2 = 2; 
const int GLUT_KEY_F3 = 3; 
const int GLUT_KEY_F4 = 4; 
const int GLUT_KEY_F5 = 5; 
const int GLUT_KEY_F6 = 6; 
const int GLUT_KEY_F7 = 7; 
const int GLUT_KEY_F8 = 8; 
const int GLUT_KEY_F9 = 9; 
const int GLUT_KEY_F10 = 10; 
const int GLUT_KEY_F11 = 11; 
const int GLUT_KEY_F12 = 12; 
// WARNING: Different values than GLUT uses:
const int GLUT_KEY_LEFT = FL_Left; 
const int GLUT_KEY_UP = FL_Up; 
const int GLUT_KEY_RIGHT = FL_Right; 
const int GLUT_KEY_DOWN = FL_Down; 
const int GLUT_KEY_PAGE_UP = FL_Page_Up; 
const int GLUT_KEY_PAGE_DOWN = FL_Page_Down; 
const int GLUT_KEY_HOME = FL_Home; 
const int GLUT_KEY_END = FL_End; 
const int GLUT_KEY_INSERT = FL_Insert; 

//void glutSpaceballMotionFunc(void (*)(int x, int y, int z));

//void glutSpaceballRotateFunc(void (*)(int x, int y, int z));

//void glutSpaceballButtonFunc(void (*)(int button, int state));

//void glutButtonBoxFunc(void (*)(int button, int state));

//void glutDialsFunc(void (*)(int dial, int value));

//void glutTabletMotionFunc(void (*)(int x, int y));

//void glutTabletButtonFunc(void (*)(int button, int state, int x, int y));

void glutOverlayDisplayFunc(void (*f)()) {
  glut_window.overlaydisplay = f;}

//void glutWindowStatusFunc(void (*)(int state));
//enum {GLUT_HIDDEN, GLUT_FULLY_RETAINED, GLUT_PARTIALLY_RETAINED,
//	GLUT_FULLY_COVERED};

//void glutSetColor(int, GLfloat red, GLfloat green, GLfloat blue);

//GLfloat glutGetColor(int ndx, int component);
//#define GLUT_RED			0
//#define GLUT_GREEN			1
//#define GLUT_BLUE			2

//void glutCopyColormap(int win);

// Warning: values are changed from GLUT!
// Also relies on the GL_ symbols having values greater than 100
int glutGet(GLenum type);
enum {
  GLUT_RETURN_ZERO = 0,
  GLUT_WINDOW_X,
  GLUT_WINDOW_Y,
  GLUT_WINDOW_WIDTH,
  GLUT_WINDOW_HEIGHT,
  GLUT_WINDOW_PARENT,
//GLUT_WINDOW_NUM_CHILDREN,
//GLUT_WINDOW_CURSOR,
  GLUT_SCREEN_WIDTH,
  GLUT_SCREEN_HEIGHT,
//GLUT_SCREEN_WIDTH_MM,
//GLUT_SCREEN_HEIGHT_MM,
  GLUT_MENU_NUM_ITEMS,
  GLUT_DISPLAY_MODE_POSSIBLE,
  GLUT_INIT_WINDOW_X,
  GLUT_INIT_WINDOW_Y,
  GLUT_INIT_WINDOW_WIDTH,
  GLUT_INIT_WINDOW_HEIGHT,
  GLUT_INIT_DISPLAY_MODE,
//GLUT_ELAPSED_TIME,
  GLUT_WINDOW_BUFFER_SIZE
};

const int GLUT_WINDOW_STENCIL_SIZE = GL_STENCIL_BITS; 
const int GLUT_WINDOW_DEPTH_SIZE = GL_DEPTH_BITS; 
const int GLUT_WINDOW_RED_SIZE = GL_RED_BITS; 
const int GLUT_WINDOW_GREEN_SIZE = GL_GREEN_BITS; 
const int GLUT_WINDOW_BLUE_SIZE = GL_BLUE_BITS; 
const int GLUT_WINDOW_ALPHA_SIZE = GL_ALPHA_BITS; 
const int GLUT_WINDOW_ACCUM_RED_SIZE = GL_ACCUM_RED_BITS; 
const int GLUT_WINDOW_ACCUM_GREEN_SIZE = GL_ACCUM_GREEN_BITS; 
const int GLUT_WINDOW_ACCUM_BLUE_SIZE = GL_ACCUM_BLUE_BITS; 
const int GLUT_WINDOW_ACCUM_ALPHA_SIZE = GL_ACCUM_ALPHA_BITS; 
const int GLUT_WINDOW_DOUBLEBUFFER = GL_DOUBLEBUFFER; 
const int GLUT_WINDOW_RGBA = GL_RGBA; 
const int GLUT_WINDOW_COLORMAP_SIZE = GL_INDEX_BITS; 
version (GL_SAMPLES_SGIS) {
const int GLUT_WINDOW_NUM_SAMPLES = GL_SAMPLES_SGIS; 
} else {
const int GLUT_WINDOW_NUM_SAMPLES = GLUT_RETURN_ZERO; 
}
const int GLUT_WINDOW_STEREO = GL_STEREO; 

//int glutDeviceGet(GLenum type);
//#define GLUT_HAS_KEYBOARD		600
//#define GLUT_HAS_MOUSE		601
//#define GLUT_HAS_SPACEBALL		602
//#define GLUT_HAS_DIAL_AND_BUTTON_BOX	603
//#define GLUT_HAS_TABLET		604
//#define GLUT_NUM_MOUSE_BUTTONS	605
//#define GLUT_NUM_SPACEBALL_BUTTONS	606
//#define GLUT_NUM_BUTTON_BOX_BUTTONS	607
//#define GLUT_NUM_DIALS		608
//#define GLUT_NUM_TABLET_BUTTONS	609

// WARNING: these values are different than GLUT uses:
const int GLUT_ACTIVE_SHIFT = FL_SHIFT; 
const int GLUT_ACTIVE_CTRL = FL_CTRL; 
const int GLUT_ACTIVE_ALT = FL_ALT; 
int glutGetModifiers() {return Fl.event_state() & (GLUT_ACTIVE_SHIFT | GLUT_ACTIVE_CTRL | GLUT_ACTIVE_ALT);}

int glutLayerGet(GLenum);
const int GLUT_OVERLAY_POSSIBLE = 800; 
//#define GLUT_LAYER_IN_USE		801
//#define GLUT_HAS_OVERLAY		802
const int GLUT_TRANSPARENT_INDEX = 803; 
const int GLUT_NORMAL_DAMAGED = 804; 
const int GLUT_OVERLAY_DAMAGED = 805; 

//int glutVideoResizeGet(GLenum param);
//#define GLUT_VIDEO_RESIZE_POSSIBLE	900
//#define GLUT_VIDEO_RESIZE_IN_USE	901
//#define GLUT_VIDEO_RESIZE_X_DELTA	902
//#define GLUT_VIDEO_RESIZE_Y_DELTA	903
//#define GLUT_VIDEO_RESIZE_WIDTH_DELTA	904
//#define GLUT_VIDEO_RESIZE_HEIGHT_DELTA 905
//#define GLUT_VIDEO_RESIZE_X		906
//#define GLUT_VIDEO_RESIZE_Y		907
//#define GLUT_VIDEO_RESIZE_WIDTH	908
//#define GLUT_VIDEO_RESIZE_HEIGHT	909

//void glutSetupVideoResizing();

//void glutStopVideoResizing();

//void glutVideoResize(int x, int y, int width, int height);

//void glutVideoPan(int x, int y, int width, int height);

////////////////////////////////////////////////////////////////
// Emulated GLUT drawing functions:

// Font argument must be a void* for compatability, so...
extern struct Glut_Bitmap_Font {ubyte font; int size;}
  glutBitmap9By15, glutBitmap8By13, glutBitmapTimesRoman10,
  glutBitmapTimesRoman24, glutBitmapHelvetica10, glutBitmapHelvetica12,
  glutBitmapHelvetica18;
const int GLUT_BITMAP_9_BY_15 = (&glutBitmap9By15); 
const int GLUT_BITMAP_8_BY_13 = (&glutBitmap8By13); 
const int GLUT_BITMAP_TIMES_ROMAN_10 = (&glutBitmapTimesRoman10); 
const int GLUT_BITMAP_TIMES_ROMAN_24 = (&glutBitmapTimesRoman24); 
const int GLUT_BITMAP_HELVETICA_10 = (&glutBitmapHelvetica10); 
const int GLUT_BITMAP_HELVETICA_12 = (&glutBitmapHelvetica12); 
const int GLUT_BITMAP_HELVETICA_18 = (&glutBitmapHelvetica18); 

void glutBitmapCharacter(void *font, int character);
int glutBitmapWidth(void *font, int character);
int glutBitmapLength(void *font, ubyte *string);

////////////////////////////////////////////////////////////////
// GLUT drawing functions.  These are NOT emulated but you can
// link in the glut library to get them.  This assumes the object
// files in GLUT remain as they currently are so that there are
// not symbol conflicts with the above.

extern "C" {

extern int APIENTRY glutExtensionSupported(char *name);

/* Stroke font constants (use these in GLUT program). */
version (WIN32) {
const int GLUT_STROKE_ROMAN = ((void*)0); 
const int GLUT_STROKE_MONO_ROMAN = ((void*)1); 
} else {
extern void *glutStrokeRoman;
const int GLUT_STROKE_ROMAN = (&glutStrokeRoman); 
extern void *glutStrokeMonoRoman;
const int GLUT_STROKE_MONO_ROMAN = (&glutStrokeMonoRoman); 
}

/* GLUT font sub-API */
extern void APIENTRY glutStrokeCharacter(void *font, int character);
extern int APIENTRY glutStrokeWidth(void *font, int character);

/* GLUT pre-built models sub-API */
extern void APIENTRY glutWireSphere(GLdouble radius, GLint slices, GLint stacks);
extern void APIENTRY glutSolidSphere(GLdouble radius, GLint slices, GLint stacks);
extern void APIENTRY glutWireCone(GLdouble base, GLdouble height, GLint slices, GLint stacks);
extern void APIENTRY glutSolidCone(GLdouble base, GLdouble height, GLint slices, GLint stacks);
extern void APIENTRY glutWireCube(GLdouble size);
extern void APIENTRY glutSolidCube(GLdouble size);
extern void APIENTRY glutWireTorus(GLdouble innerRadius, GLdouble outerRadius, GLint sides, GLint rings);
extern void APIENTRY glutSolidTorus(GLdouble innerRadius, GLdouble outerRadius, GLint sides, GLint rings);
extern void APIENTRY glutWireDodecahedron();
extern void APIENTRY glutSolidDodecahedron();
extern void APIENTRY glutWireTeapot(GLdouble size);
extern void APIENTRY glutSolidTeapot(GLdouble size);
extern void APIENTRY glutWireOctahedron();
extern void APIENTRY glutSolidOctahedron();
extern void APIENTRY glutWireTetrahedron();
extern void APIENTRY glutSolidTetrahedron();
extern void APIENTRY glutWireIcosahedron();
extern void APIENTRY glutSolidIcosahedron();

}

}                  /* !__glut_h__ */

//
// End of "$Id: glut.H 5327 2006-08-17 13:49:46Z matt $".
//
    End of automatic import -+/
