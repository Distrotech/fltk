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

/*	gl.h

	GL to OpenGL translator.
	If you include this, you might be able to port old GL programs.
	There are also much better emulators available on the net.

*/

#include <FL/gl.h>
#include "gl_draw.H"

inline void clear() {glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);}
#define RGBcolor(r,g,b) glColor3ub(r,g,b)
#define bgnline() glBegin(GL_LINE_STRIP)
#define bgnpolygon() glBegin(GL_POLYGON)
#define bgnclosedline() glBegin(GL_LINE_LOOP)
#define endline() glEnd()
#define endpolygon() glEnd()
#define endclosedline() glEnd()
#define v2f(v) glVertex2fv(v)
#define v2s(v) glVertex2sv(v)
#define cmov(x,y,z) glRasterPos3f(x,y,z)
#define charstr(s) gl_draw(s)
#define fmprstr(s) gl_draw(s)
typedef float Matrix[4][4];
inline void pushmatrix() {glPushMatrix();}
inline void popmatrix() {glPopMatrix();}
inline void multmatrix(Matrix m) {glMultMatrixf((float *)m);}
inline void color(int n) {glIndexi(n);}
inline void rect(int x,int y,int r,int t) {gl_rect(x,y,r-x,t-y);}
inline void rectf(int x,int y,int r,int t) {glRectf(x,y,r+1,t+1);}
inline void recti(int x,int y,int r,int t) {gl_rect(x,y,r-x,t-y);}
inline void rectfi(int x,int y,int r,int t) {glRecti(x,y,r+1,t+1);}
inline void rects(int x,int y,int r,int t) {gl_rect(x,y,r-x,t-y);}
inline void rectfs(int x,int y,int r,int t) {glRects(x,y,r+1,t+1);}

/* suggested twin class
// This is the Twin Class to fltk::gl2opengl
class gl2opengl : public fltk::gl2opengl {
public:
  gl2opengl(int x, int t, int w, int h, const char *label=0)
  : fltk::gl2opengl(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
/*	gl.h

	GL to OpenGL translator.
	If you include this, you might be able to port old GL programs.
	There are also much better emulators available on the net.

*/

#include <FL/gl.h>
#include "gl_draw.H"

inline void clear() {glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);}
#define RGBcolor(r,g,b) glColor3ub(r,g,b)
#define bgnline() glBegin(GL_LINE_STRIP)
#define bgnpolygon() glBegin(GL_POLYGON)
#define bgnclosedline() glBegin(GL_LINE_LOOP)
#define endline() glEnd()
#define endpolygon() glEnd()
#define endclosedline() glEnd()
#define v2f(v) glVertex2fv(v)
#define v2s(v) glVertex2sv(v)
#define cmov(x,y,z) glRasterPos3f(x,y,z)
#define charstr(s) gl_draw(s)
#define fmprstr(s) gl_draw(s)
typedef float Matrix[4][4];
inline void pushmatrix() {glPushMatrix();}
inline void popmatrix() {glPopMatrix();}
inline void multmatrix(Matrix m) {glMultMatrixf((float *)m);}
inline void color(int n) {glIndexi(n);}
inline void rect(int x,int y,int r,int t) {gl_rect(x,y,r-x,t-y);}
inline void rectf(int x,int y,int r,int t) {glRectf(x,y,r+1,t+1);}
inline void recti(int x,int y,int r,int t) {gl_rect(x,y,r-x,t-y);}
inline void rectfi(int x,int y,int r,int t) {glRecti(x,y,r+1,t+1);}
inline void rects(int x,int y,int r,int t) {gl_rect(x,y,r-x,t-y);}
inline void rectfs(int x,int y,int r,int t) {glRects(x,y,r+1,t+1);}
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
/*	gl.h

	GL to OpenGL translator.
	If you include this, you might be able to port old GL programs.
	There are also much better emulators available on the net.

*/

#include <fltk/gl.h>
#include "gl_draw.h"

inline void clear() {glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);}
#define RGBcolor(r,g,b) glColor3ub(r,g,b)
#define bgnline() glBegin(GL_LINE_STRIP)
#define bgnpolygon() glBegin(GL_POLYGON)
#define bgnclosedline() glBegin(GL_LINE_LOOP)
#define endline() glEnd()
#define endpolygon() glEnd()
#define endclosedline() glEnd()
#define v2f(v) glVertex2fv(v)
#define v2s(v) glVertex2sv(v)
#define cmov(x,y,z) glRasterPos3f(x,y,z)
#define charstr(s) gl_draw(s)
#define fmprstr(s) gl_draw(s)
typedef float Matrix[4][4];
inline void pushmatrix() {glPushMatrix();}
inline void popmatrix() {glPopMatrix();}
inline void multmatrix(Matrix m) {glMultMatrixf((float *)m);}
inline void color(int n) {glIndexi(n);}
inline void rect(int x,int y,int r,int t) {gl_rect(x,y,r-x,t-y);}
inline void rectf(int x,int y,int r,int t) {glRectf(x,y,r+1,t+1);}
inline void recti(int x,int y,int r,int t) {gl_rect(x,y,r-x,t-y);}
inline void rectfi(int x,int y,int r,int t) {glRecti(x,y,r+1,t+1);}
inline void rects(int x,int y,int r,int t) {gl_rect(x,y,r-x,t-y);}
inline void rectfs(int x,int y,int r,int t) {glRects(x,y,r+1,t+1);}
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
