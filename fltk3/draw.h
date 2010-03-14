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
// "$Id: fl_draw.H 6955 2009-12-07 22:04:55Z matt $"
//
// Portable drawing function header file for the Fast Light Tool Kit (FLTK).
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

/**
  \file fl_draw.H
  \brief utility header to pull drawing functions together
*/

#ifndef fl_draw_H
#define fl_draw_H

#include "enumerations.h"  // for the color names
#include "Window.h"	   // for fl_set_spot()

// Image class...
class Fl_Image;

// Label flags...
FL_EXPORT extern char fl_draw_shortcut;

/** \addtogroup fl_attributes
    @{
*/
// Colors:
FL_EXPORT void	fl_color(Fl_Color i); // select indexed color
/** for back compatibility - use fl_color(Fl_Color c) instead */
inline void fl_color(int c) {fl_color((Fl_Color)c);}
FL_EXPORT void	fl_color(uchar r, uchar g, uchar b); // select actual color
extern FL_EXPORT Fl_Color fl_color_;
/**
  Returns the last fl_color() that was set.
  This can be used for state save/restore.
*/
inline Fl_Color fl_color() {return fl_color_;}
/** @} */

/** \addtogroup fl_drawings
    @{
*/
// clip:
FL_EXPORT void fl_push_clip(int x, int y, int w, int h);
/** The fl_clip() name is deprecated and will be removed from future releases */
#define fl_clip fl_push_clip
FL_EXPORT void fl_push_no_clip();
FL_EXPORT void fl_pop_clip();
FL_EXPORT int fl_not_clipped(int x, int y, int w, int h);
FL_EXPORT int fl_clip_box(int, int, int, int, int& x, int& y, int& w, int& h);

// points:
FL_EXPORT void fl_point(int x, int y);

// line type:
FL_EXPORT void fl_line_style(int style, int width=0, char* dashes=0);
enum {
  FL_SOLID	= 0,		///< line style: <tt>___________</tt>
  FL_DASH	= 1,		///< line style: <tt>_ _ _ _ _ _</tt>
  FL_DOT	= 2,		///< line style: <tt>. . . . . .</tt>
  FL_DASHDOT	= 3,		///< line style: <tt>_ . _ . _ .</tt>
  FL_DASHDOTDOT	= 4,		///< line style: <tt>_ . . _ . .</tt>

  FL_CAP_FLAT	= 0x100,	///< cap style: end is flat
  FL_CAP_ROUND	= 0x200,	///< cap style: end is round
  FL_CAP_SQUARE	= 0x300,	///< cap style: end wraps end point

  FL_JOIN_MITER	= 0x1000,	///< join style: line join extends to a point
  FL_JOIN_ROUND	= 0x2000,	///< join style: line join is rounded
  FL_JOIN_BEVEL	= 0x3000	///< join style: line join is tidied
};

// rectangles tweaked to exactly fill the pixel rectangle:
FL_EXPORT void fl_rect(int x, int y, int w, int h);
/** Draws a 1-pixel border \e inside the given bounding box */
inline void fl_rect(int x, int y, int w, int h, Fl_Color c) {fl_color(c); fl_rect(x,y,w,h);}
FL_EXPORT void fl_rectf(int x, int y, int w, int h);
/** Colors a rectangle that exactly fills the given bounding box */
inline void fl_rectf(int x, int y, int w, int h, Fl_Color c) {fl_color(c); fl_rectf(x,y,w,h);}

/**
  Color a rectangle with "exactly" the passed <tt>r,g,b</tt> color.
  On screens with less than 24 bits of color this is done by drawing a
  solid-colored block using fl_draw_image() so that the correct color
  shade is produced.
  */
/* note: doxygen comment here to avoid triplication in os-speciic files */
FL_EXPORT void fl_rectf(int x, int y, int w, int h, uchar r, uchar g, uchar b);

// line segments:
FL_EXPORT void fl_line(int x, int y, int x1, int y1);
FL_EXPORT void fl_line(int x, int y, int x1, int y1, int x2, int y2);

// closed line segments:
FL_EXPORT void fl_loop(int x, int y, int x1, int y1, int x2, int y2);
FL_EXPORT void fl_loop(int x, int y, int x1, int y1, int x2, int y2, int x3, int y3);

// filled polygons
FL_EXPORT void fl_polygon(int x, int y, int x1, int y1, int x2, int y2);
FL_EXPORT void fl_polygon(int x, int y, int x1, int y1, int x2, int y2, int x3, int y3);

// draw rectilinear lines, horizontal segment first:
FL_EXPORT void fl_xyline(int x, int y, int x1);
FL_EXPORT void fl_xyline(int x, int y, int x1, int y2);
FL_EXPORT void fl_xyline(int x, int y, int x1, int y2, int x3);

// draw rectilinear lines, vertical segment first:
FL_EXPORT void fl_yxline(int x, int y, int y1);
FL_EXPORT void fl_yxline(int x, int y, int y1, int x2);
FL_EXPORT void fl_yxline(int x, int y, int y1, int x2, int y3);

// circular lines and pie slices (code in fl_arci.C):
FL_EXPORT void fl_arc(int x, int y, int w, int h, double a1, double a2);
FL_EXPORT void fl_pie(int x, int y, int w, int h, double a1, double a2);
/** fl_chord declaration is a place holder - the function does not yet exist */
FL_EXPORT void fl_chord(int x, int y, int w, int h, double a1, double a2); // nyi

// scalable drawing code (code in fl_vertex.C and fl_arc.C):
FL_EXPORT void fl_push_matrix();
FL_EXPORT void fl_pop_matrix();
FL_EXPORT void fl_scale(double x, double y);
FL_EXPORT void fl_scale(double x);
FL_EXPORT void fl_translate(double x, double y);
FL_EXPORT void fl_rotate(double d);
FL_EXPORT void fl_mult_matrix(double a, double b, double c, double d, double x,double y);
FL_EXPORT void fl_begin_points();
FL_EXPORT void fl_begin_line();
FL_EXPORT void fl_begin_loop();
FL_EXPORT void fl_begin_polygon();
FL_EXPORT void fl_vertex(double x, double y);
FL_EXPORT void fl_curve(double X0, double Y0, double X1, double Y1, double X2, double Y2, double X3, double Y3);
FL_EXPORT void fl_arc(double x, double y, double r, double start, double a);
FL_EXPORT void fl_circle(double x, double y, double r);
FL_EXPORT void fl_end_points();
FL_EXPORT void fl_end_line();
FL_EXPORT void fl_end_loop();
FL_EXPORT void fl_end_polygon();
FL_EXPORT void fl_begin_complex_polygon();
FL_EXPORT void fl_gap();
FL_EXPORT void fl_end_complex_polygon();
// get and use transformed positions:
FL_EXPORT double fl_transform_x(double x, double y);
FL_EXPORT double fl_transform_y(double x, double y);
FL_EXPORT double fl_transform_dx(double x, double y);
FL_EXPORT double fl_transform_dy(double x, double y);
FL_EXPORT void fl_transformed_vertex(double x, double y);
/** @} */

/** \addtogroup  fl_attributes
    @{ */
/* NOTE: doxygen comments here to avoid triplication in os-specific sources */
/**
  Sets the current font, which is then used in various drawing routines.
  You may call this outside a draw context if necessary to call fl_width(),
  but on X this will open the display.

  The font is identified by a \p face and a \p size.
  The size of the font is measured in pixels and not "points".
  Lines should be spaced \p size pixels apart or more.
*/

// Fonts:
FL_EXPORT void fl_font(Fl_Font face, Fl_Fontsize size);
extern FL_EXPORT Fl_Font fl_font_; ///< current font index

/**
  Returns the \p face set by the most recent call to fl_font().
  This can be used to save/restore the font.
*/
inline Fl_Font fl_font() {return fl_font_;}
/** current font size */
extern FL_EXPORT Fl_Fontsize fl_size_;
/**
  Returns the \p size set by the most recent call to fl_font().
  This can be used to save/restore the font.
*/
inline Fl_Fontsize fl_size() {return fl_size_;}

// information you can get about the current font:
/**
  Returns the recommended minimum line spacing for the current font.
  You can also use the value of \p size passed to fl_font()
*/
FL_EXPORT int   fl_height();	// using "size" should work ok
FL_EXPORT int fl_height(int font, int size);
/**
  Returns the recommended distance above the bottom of a fl_height() tall box to
  draw the text at so it looks centered vertically in that box.
*/
FL_EXPORT int   fl_descent();
/** Return the typographical width of a nul-terminated string */
FL_EXPORT double fl_width(const char* txt);
/** Return the typographical width of a sequence of \p n characters */
FL_EXPORT double fl_width(const char* txt, int n);
/** Return the typographical width of a single character :
    \note if a valid fl_gc is NOT found then it uses the first window gc,
    or the screen gc if no fltk window is available when called. */
FL_EXPORT double fl_width(unsigned int);
/** Determine the minimum pixel dimensions of a nul-terminated string.

Usage: given a string "txt" drawn using fl_draw(txt, x, y) you would determine
its pixel extents on the display using fl_text_extents(txt, dx, dy, wo, ho)
such that a bounding box that exactly fits around the text could be drawn with
fl_rect(x+dx, y+dy, wo, ho). Note the dx, dy values hold the offset of the first
"colored in" pixel of the string, from the draw origin.
*/
FL_EXPORT void fl_text_extents(const char*, int& dx, int& dy, int& w, int& h); // NO fltk symbol expansion will be performed
/** Determine the minimum pixel dimensions of a sequence of \p n characters.
\see fl_text_extents(const char*, int& dx, int& dy, int& w, int& h)
*/
FL_EXPORT void fl_text_extents(const char*, int n, int& dx, int& dy, int& w, int& h);

// font encoding:
// Note: doxygen comments here to avoid duplication for os-sepecific cases
/**
  convert text from Windows/X11 latin1 charcter set to local encoding.
  \param[in] t character string (latin1 encoding)
  \param[in] n optional number of characters to convert (default is all)
  \returns pointer to internal buffer containing converted characters
  */
FL_EXPORT const char *fl_latin1_to_local(const char *t, int n=-1);
/**
  convert text from local encoding to Windowx/X11 latin1 character set.
  \param[in] t character string (local encoding)
  \param[in] n optional number of characters to convert (default is all)
  \returns pointer to internal buffer containing converted characters
  */
FL_EXPORT const char *fl_local_to_latin1(const char *t, int n=-1);
/**
  convert text from Mac Roman charcter set to local encoding.
  \param[in] t character string (Mac Roman encoding)
  \param[in] n optional number of characters to convert (default is all)
  \returns pointer to internal buffer containing converted characters
  */
FL_EXPORT const char *fl_mac_roman_to_local(const char *t, int n=-1);
/**
  convert text from local encoding to Mac Roman character set.
  \param[in] t character string (local encoding)
  \param[in] n optional number of characters to convert (default is all)
  \returns pointer to internal buffer containing converted characters
  */
FL_EXPORT const char *fl_local_to_mac_roman(const char *t, int n=-1);
/** @} */

/** \addtogroup  fl_drawings
    @{ */
/**
  Draws a nul-terminated string starting at the given location.

  Text is aligned to the left and to the baseline of the font.
  To align to the bottom, subtract fl_descent() from \p y.
  To align to the top, subtract fl_descent() and add fl_height().
  This version of fl_draw provides direct access to the text drawing
  function of the underlying OS. It does not apply any special handling
  to control characters.
*/
FL_EXPORT void fl_draw(const char* str, int x, int y);
/**
  Draws a nul-terminated string starting at the given location and 
  rotating \p angle degrees counterclockwise.
  This version of fl_draw provides direct access to the text drawing
  function of the underlying OS and suported for Xft, Win32 and MacOS
  fltk subset.
*/
FL_EXPORT void fl_draw(int angle,const char* str, int x, int y);
/**
  Draws an array of \p n characters starting at the given location.
*/
FL_EXPORT void fl_draw(const char* str, int n, int x, int y);
/**
  Draws an array of \p n characters starting at the given location,
  rotating \p angle degrees counterclockwise.
*/
FL_EXPORT void fl_draw(int angle,const char* str, int n, int x, int y);
/**
  Draws an array of \p n characters right to left starting at given location.
*/
FL_EXPORT void fl_rtl_draw(const char*, int n, int x, int y);
FL_EXPORT void fl_measure(const char* str, int& x, int& y,
                          int draw_symbols = 1);
FL_EXPORT void fl_draw(const char* str, int x, int y, int w, int h,
                       Fl_Align align,
                       Fl_Image* img=0, int draw_symbols = 1);
FL_EXPORT void fl_draw(const char* str, int x, int y, int w, int h,
                       Fl_Align align,
                       void (*callthis)(const char *,int,int,int),
                       Fl_Image* img=0, int draw_symbols = 1);

// boxtypes:
FL_EXPORT void fl_frame(const char* s, int x, int y, int w, int h);
FL_EXPORT void fl_frame2(const char* s, int x, int y, int w, int h);
FL_EXPORT void fl_draw_box(Fl_Boxtype, int x, int y, int w, int h, Fl_Color);

// images:
/**
  signature of image generation callback function.
  \param[in]  data  user data passed to function
  \param[in]  x,y,w position and width of scan line in image
  \param[out] buf   buffer for generated image data. You must copy \p w
                    pixels from scanline \p y, starting at pixel \p x
		    to this buffer.
  */
typedef void (*Fl_Draw_Image_Cb)(void* data,int x,int y,int w,uchar* buf);

/**
  Draw an 8-bit per color RGB or luminance image.
  \param[in] buf points at the "r" data of the top-left pixel.
                 Color data must be in <tt>r,g,b</tt> order.
  \param[in] X,Y position where to put top-left corner of image
  \param[in] W,H size of the image
  \param[in] D   delta to add to the pointer between pixels. it may be
                 any value greater than or equal to 3, or it can be
		 negative to flip the image horizontally
  \param[in] L   delta to add to the pointer between lines (if 0 is
                 passed it uses \p W * \p D), and may be larger than
		 \p W * \p D to crop data, or negative to flip the
		 image vertically

  It is highly recommended that you put the following code before the
  first <tt>show()</tt> of \e any window in your program to get rid of
  the dithering if possible:
  \code
  Fl::visual(FL_RGB);
  \endcode
  Gray scale (1-channel) images may be drawn. This is done if
  <tt>abs(D)</tt> is less than 3, or by calling fl_draw_image_mono().
  Only one 8-bit sample is used for each pixel, and on screens with
  different numbers of bits for red, green, and blue only gray colors
  are used. Setting \p D greater than 1 will let you display one channel
  of a color image.

  \par Note:
  The X version does not support all possible visuals. If FLTK cannot
  draw the image in the current visual it will abort. FLTK supports
  any visual of 8 bits or less, and all common TrueColor visuals up
  to 32 bits.
  */
FL_EXPORT void fl_draw_image(const uchar* buf, int X,int Y,int W,int H, int D=3, int L=0);

/**
  Draw a gray-scale (1 channel) image.
  \see fl_draw_image(const uchar* buf, int X,int Y,int W,int H, int D, int L)
  */
FL_EXPORT void fl_draw_image_mono(const uchar* buf, int X,int Y,int W,int H, int D=1, int L=0);

/**
  Draw image using callback function to generate image data.
  You can generate the image as it is being drawn, or do arbitrary
  decompression of stored data, provided it can be decompressed to
  individual scan lines easily.
  \param[in] cb   callback function to generate scan line data
  \param[in] data user data passed to callback function
  \param[in] X,Y
  \param[in] W,H
  \param[in] D
  \see fl_draw_image(const uchar* buf, int X,int Y,int W,int H, int D, int L)

  The callback function \p cb is called with the <tt>void*</tt> \p data
  user data pointer to allow access to a structure of information about
  the image, and the \p x, \p y, and \p w of the scan line desired from
  the image. 0,0 is the upper-left corner of the image, not \p X, \p Y.
  A pointer to a buffer to put the data into is passed. You must copy
  \p w pixels from scanline \p y, starting at pixel \p x, to this buffer.

  Due to cropping, less than the whole image may be requested. So \p x
  may be greater than zero, the first \p y may be greater than zero,
  and \p w may be less than \p W. The buffer is long enough to store
  the entire \p W * \p D pixels, this is for convenience with some
  decompression schemes where you must decompress the entire line at
  once: decompress it into the buffer, and then if \p x is not zero,
  copy the data over so the \p x'th pixel is at the start of the buffer.

  You can assume the \p y's will be consecutive, except the first one
  may be greater than zero.

  If \p D is 4 or more, you must fill in the unused bytes with zero.
  */
FL_EXPORT void fl_draw_image(Fl_Draw_Image_Cb cb, void* data, int X,int Y,int W,int H, int D=3);

/**
  Draw gray-scale image using callback function to generate image data.
  \see fl_draw_image(Fl_Draw_Image_Cb cb, void* data, int X,int Y,int W,int H, int D)
  */
FL_EXPORT void fl_draw_image_mono(Fl_Draw_Image_Cb cb, void* data, int X,int Y,int W,int H, int D=1);

/**
  Checks whether platform supports true alpha blending for RGBA images.
  \returns 1 if true alpha blending supported by platform
  \returns 0 not supported so FLTK will use screen door transparency
  */
/* note: doxygen comment here to avoid triplication in os-speciic files */
FL_EXPORT char fl_can_do_alpha_blending();

/**
  Read an RGB(A) image from the current window or off-screen buffer.
  \param[in] p     pixel buffer, or NULL to allocate one
  \param[in] X,Y   position of top-left of image to read
  \param[in] W,H   width and height of image to read
  \param[in] alpha alpha value for image (0 fr none)
  \returns pointer to pixel buffer, or NULL if allocation failed.

  The \p p argument points to a buffer that can hold the image and must
  be at least \p W*H*3 bytes when reading RGB images, or \p W*H*4 bytes
  when reading RGBA images. If NULL, fl_read_image() will create an
  array of the proper suze which can be freed using <tt>delete[]</tt>.

  The \p alpha parameter controls whether an alpha channel is created
  and the value that is placed in the alpha channel. If 0, no alpha
  channel is generated.
  */
/* note: doxygen comment here to avoid triplication in os-speciic files */
FL_EXPORT uchar *fl_read_image(uchar *p,int X,int Y,int W,int H,int alpha=0);

// pixmaps:
FL_EXPORT int fl_draw_pixmap(/*const*/ char* const* data, int x,int y,Fl_Color=FL_GRAY);
FL_EXPORT int fl_draw_pixmap(const char* const* cdata, int x,int y,Fl_Color=FL_GRAY);
FL_EXPORT int fl_measure_pixmap(/*const*/ char* const* data, int &w, int &h);
FL_EXPORT int fl_measure_pixmap(const char* const* cdata, int &w, int &h);

// other:
FL_EXPORT void fl_scroll(int X, int Y, int W, int H, int dx, int dy,
                         void (*draw_area)(void*, int,int,int,int), void* data);
FL_EXPORT const char* fl_shortcut_label(unsigned int shortcut);
FL_EXPORT const char* fl_shortcut_label(unsigned int shortcut, const char **eom);
FL_EXPORT void fl_overlay_rect(int x,int y,int w,int h);
FL_EXPORT void fl_overlay_clear();
FL_EXPORT void fl_cursor(Fl_Cursor, Fl_Color fg=FL_BLACK, Fl_Color bg=FL_WHITE);
FL_EXPORT const char* fl_expand_text(const char* from, char* buf, int maxbuf,
                                     double maxw, int& n, double &width,
                                     int wrap, int draw_symbols = 0);

// XIM:
/** \todo provide user documentation for fl_set_status function */
FL_EXPORT void fl_set_status(int X, int Y, int W, int H);
/** \todo provide user documentation for fl_set_spot function */
FL_EXPORT void fl_set_spot(int font, int size, int X, int Y, int W, int H, fltk::Window *win=0);
/** \todo provide user documentation for fl_reset_spot function*/
FL_EXPORT void fl_reset_spot(void);



// XForms symbols:
FL_EXPORT int fl_draw_symbol(const char* label,int x,int y,int w,int h, Fl_Color);
FL_EXPORT int fl_add_symbol(const char* name, void (*drawit)(Fl_Color), int scalable);
/** @} */

#endif

//
// End of "$Id: fl_draw.H 6955 2009-12-07 22:04:55Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::draw
class fl_draw : public fltk::draw {
public:
  fl_draw(int x, int t, int w, int h, const char *label=0)
  : fltk::draw(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: fl_draw.H 6955 2009-12-07 22:04:55Z matt $"
//
// Portable drawing function header file for the Fast Light Tool Kit (FLTK).
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

/**
  \file fl_draw.H
  \brief utility header to pull drawing functions together
*/

#ifndef fl_draw_H
#define fl_draw_H

#include "Enumerations.H"  // for the color names
#include "Fl_Window.H"	   // for fl_set_spot()

// Image class...
class Fl_Image;

// Label flags...
FL_EXPORT extern char fl_draw_shortcut;

/** \addtogroup fl_attributes
    @{
*/
// Colors:
FL_EXPORT void	fl_color(Fl_Color i); // select indexed color
/** for back compatibility - use fl_color(Fl_Color c) instead */
inline void fl_color(int c) {fl_color((Fl_Color)c);}
FL_EXPORT void	fl_color(uchar r, uchar g, uchar b); // select actual color
extern FL_EXPORT Fl_Color fl_color_;
/**
  Returns the last fl_color() that was set.
  This can be used for state save/restore.
*/
inline Fl_Color fl_color() {return fl_color_;}
/** @} */

/** \addtogroup fl_drawings
    @{
*/
// clip:
FL_EXPORT void fl_push_clip(int x, int y, int w, int h);
/** The fl_clip() name is deprecated and will be removed from future releases */
#define fl_clip fl_push_clip
FL_EXPORT void fl_push_no_clip();
FL_EXPORT void fl_pop_clip();
FL_EXPORT int fl_not_clipped(int x, int y, int w, int h);
FL_EXPORT int fl_clip_box(int, int, int, int, int& x, int& y, int& w, int& h);

// points:
FL_EXPORT void fl_point(int x, int y);

// line type:
FL_EXPORT void fl_line_style(int style, int width=0, char* dashes=0);
enum {
  FL_SOLID	= 0,		///< line style: <tt>___________</tt>
  FL_DASH	= 1,		///< line style: <tt>_ _ _ _ _ _</tt>
  FL_DOT	= 2,		///< line style: <tt>. . . . . .</tt>
  FL_DASHDOT	= 3,		///< line style: <tt>_ . _ . _ .</tt>
  FL_DASHDOTDOT	= 4,		///< line style: <tt>_ . . _ . .</tt>

  FL_CAP_FLAT	= 0x100,	///< cap style: end is flat
  FL_CAP_ROUND	= 0x200,	///< cap style: end is round
  FL_CAP_SQUARE	= 0x300,	///< cap style: end wraps end point

  FL_JOIN_MITER	= 0x1000,	///< join style: line join extends to a point
  FL_JOIN_ROUND	= 0x2000,	///< join style: line join is rounded
  FL_JOIN_BEVEL	= 0x3000	///< join style: line join is tidied
};

// rectangles tweaked to exactly fill the pixel rectangle:
FL_EXPORT void fl_rect(int x, int y, int w, int h);
/** Draws a 1-pixel border \e inside the given bounding box */
inline void fl_rect(int x, int y, int w, int h, Fl_Color c) {fl_color(c); fl_rect(x,y,w,h);}
FL_EXPORT void fl_rectf(int x, int y, int w, int h);
/** Colors a rectangle that exactly fills the given bounding box */
inline void fl_rectf(int x, int y, int w, int h, Fl_Color c) {fl_color(c); fl_rectf(x,y,w,h);}

/**
  Color a rectangle with "exactly" the passed <tt>r,g,b</tt> color.
  On screens with less than 24 bits of color this is done by drawing a
  solid-colored block using fl_draw_image() so that the correct color
  shade is produced.
  */
/* note: doxygen comment here to avoid triplication in os-speciic files */
FL_EXPORT void fl_rectf(int x, int y, int w, int h, uchar r, uchar g, uchar b);

// line segments:
FL_EXPORT void fl_line(int x, int y, int x1, int y1);
FL_EXPORT void fl_line(int x, int y, int x1, int y1, int x2, int y2);

// closed line segments:
FL_EXPORT void fl_loop(int x, int y, int x1, int y1, int x2, int y2);
FL_EXPORT void fl_loop(int x, int y, int x1, int y1, int x2, int y2, int x3, int y3);

// filled polygons
FL_EXPORT void fl_polygon(int x, int y, int x1, int y1, int x2, int y2);
FL_EXPORT void fl_polygon(int x, int y, int x1, int y1, int x2, int y2, int x3, int y3);

// draw rectilinear lines, horizontal segment first:
FL_EXPORT void fl_xyline(int x, int y, int x1);
FL_EXPORT void fl_xyline(int x, int y, int x1, int y2);
FL_EXPORT void fl_xyline(int x, int y, int x1, int y2, int x3);

// draw rectilinear lines, vertical segment first:
FL_EXPORT void fl_yxline(int x, int y, int y1);
FL_EXPORT void fl_yxline(int x, int y, int y1, int x2);
FL_EXPORT void fl_yxline(int x, int y, int y1, int x2, int y3);

// circular lines and pie slices (code in fl_arci.C):
FL_EXPORT void fl_arc(int x, int y, int w, int h, double a1, double a2);
FL_EXPORT void fl_pie(int x, int y, int w, int h, double a1, double a2);
/** fl_chord declaration is a place holder - the function does not yet exist */
FL_EXPORT void fl_chord(int x, int y, int w, int h, double a1, double a2); // nyi

// scalable drawing code (code in fl_vertex.C and fl_arc.C):
FL_EXPORT void fl_push_matrix();
FL_EXPORT void fl_pop_matrix();
FL_EXPORT void fl_scale(double x, double y);
FL_EXPORT void fl_scale(double x);
FL_EXPORT void fl_translate(double x, double y);
FL_EXPORT void fl_rotate(double d);
FL_EXPORT void fl_mult_matrix(double a, double b, double c, double d, double x,double y);
FL_EXPORT void fl_begin_points();
FL_EXPORT void fl_begin_line();
FL_EXPORT void fl_begin_loop();
FL_EXPORT void fl_begin_polygon();
FL_EXPORT void fl_vertex(double x, double y);
FL_EXPORT void fl_curve(double X0, double Y0, double X1, double Y1, double X2, double Y2, double X3, double Y3);
FL_EXPORT void fl_arc(double x, double y, double r, double start, double a);
FL_EXPORT void fl_circle(double x, double y, double r);
FL_EXPORT void fl_end_points();
FL_EXPORT void fl_end_line();
FL_EXPORT void fl_end_loop();
FL_EXPORT void fl_end_polygon();
FL_EXPORT void fl_begin_complex_polygon();
FL_EXPORT void fl_gap();
FL_EXPORT void fl_end_complex_polygon();
// get and use transformed positions:
FL_EXPORT double fl_transform_x(double x, double y);
FL_EXPORT double fl_transform_y(double x, double y);
FL_EXPORT double fl_transform_dx(double x, double y);
FL_EXPORT double fl_transform_dy(double x, double y);
FL_EXPORT void fl_transformed_vertex(double x, double y);
/** @} */

/** \addtogroup  fl_attributes
    @{ */
/* NOTE: doxygen comments here to avoid triplication in os-specific sources */
/**
  Sets the current font, which is then used in various drawing routines.
  You may call this outside a draw context if necessary to call fl_width(),
  but on X this will open the display.

  The font is identified by a \p face and a \p size.
  The size of the font is measured in pixels and not "points".
  Lines should be spaced \p size pixels apart or more.
*/

// Fonts:
FL_EXPORT void fl_font(Fl_Font face, Fl_Fontsize size);
extern FL_EXPORT Fl_Font fl_font_; ///< current font index

/**
  Returns the \p face set by the most recent call to fl_font().
  This can be used to save/restore the font.
*/
inline Fl_Font fl_font() {return fl_font_;}
/** current font size */
extern FL_EXPORT Fl_Fontsize fl_size_;
/**
  Returns the \p size set by the most recent call to fl_font().
  This can be used to save/restore the font.
*/
inline Fl_Fontsize fl_size() {return fl_size_;}

// information you can get about the current font:
/**
  Returns the recommended minimum line spacing for the current font.
  You can also use the value of \p size passed to fl_font()
*/
FL_EXPORT int   fl_height();	// using "size" should work ok
FL_EXPORT int fl_height(int font, int size);
/**
  Returns the recommended distance above the bottom of a fl_height() tall box to
  draw the text at so it looks centered vertically in that box.
*/
FL_EXPORT int   fl_descent();
/** Return the typographical width of a nul-terminated string */
FL_EXPORT double fl_width(const char* txt);
/** Return the typographical width of a sequence of \p n characters */
FL_EXPORT double fl_width(const char* txt, int n);
/** Return the typographical width of a single character :
    \note if a valid fl_gc is NOT found then it uses the first window gc,
    or the screen gc if no fltk window is available when called. */
FL_EXPORT double fl_width(unsigned int);
/** Determine the minimum pixel dimensions of a nul-terminated string.

Usage: given a string "txt" drawn using fl_draw(txt, x, y) you would determine
its pixel extents on the display using fl_text_extents(txt, dx, dy, wo, ho)
such that a bounding box that exactly fits around the text could be drawn with
fl_rect(x+dx, y+dy, wo, ho). Note the dx, dy values hold the offset of the first
"colored in" pixel of the string, from the draw origin.
*/
FL_EXPORT void fl_text_extents(const char*, int& dx, int& dy, int& w, int& h); // NO fltk symbol expansion will be performed
/** Determine the minimum pixel dimensions of a sequence of \p n characters.
\see fl_text_extents(const char*, int& dx, int& dy, int& w, int& h)
*/
FL_EXPORT void fl_text_extents(const char*, int n, int& dx, int& dy, int& w, int& h);

// font encoding:
// Note: doxygen comments here to avoid duplication for os-sepecific cases
/**
  convert text from Windows/X11 latin1 charcter set to local encoding.
  \param[in] t character string (latin1 encoding)
  \param[in] n optional number of characters to convert (default is all)
  \returns pointer to internal buffer containing converted characters
  */
FL_EXPORT const char *fl_latin1_to_local(const char *t, int n=-1);
/**
  convert text from local encoding to Windowx/X11 latin1 character set.
  \param[in] t character string (local encoding)
  \param[in] n optional number of characters to convert (default is all)
  \returns pointer to internal buffer containing converted characters
  */
FL_EXPORT const char *fl_local_to_latin1(const char *t, int n=-1);
/**
  convert text from Mac Roman charcter set to local encoding.
  \param[in] t character string (Mac Roman encoding)
  \param[in] n optional number of characters to convert (default is all)
  \returns pointer to internal buffer containing converted characters
  */
FL_EXPORT const char *fl_mac_roman_to_local(const char *t, int n=-1);
/**
  convert text from local encoding to Mac Roman character set.
  \param[in] t character string (local encoding)
  \param[in] n optional number of characters to convert (default is all)
  \returns pointer to internal buffer containing converted characters
  */
FL_EXPORT const char *fl_local_to_mac_roman(const char *t, int n=-1);
/** @} */

/** \addtogroup  fl_drawings
    @{ */
/**
  Draws a nul-terminated string starting at the given location.

  Text is aligned to the left and to the baseline of the font.
  To align to the bottom, subtract fl_descent() from \p y.
  To align to the top, subtract fl_descent() and add fl_height().
  This version of fl_draw provides direct access to the text drawing
  function of the underlying OS. It does not apply any special handling
  to control characters.
*/
FL_EXPORT void fl_draw(const char* str, int x, int y);
/**
  Draws a nul-terminated string starting at the given location and 
  rotating \p angle degrees counterclockwise.
  This version of fl_draw provides direct access to the text drawing
  function of the underlying OS and suported for Xft, Win32 and MacOS
  fltk subset.
*/
FL_EXPORT void fl_draw(int angle,const char* str, int x, int y);
/**
  Draws an array of \p n characters starting at the given location.
*/
FL_EXPORT void fl_draw(const char* str, int n, int x, int y);
/**
  Draws an array of \p n characters starting at the given location,
  rotating \p angle degrees counterclockwise.
*/
FL_EXPORT void fl_draw(int angle,const char* str, int n, int x, int y);
/**
  Draws an array of \p n characters right to left starting at given location.
*/
FL_EXPORT void fl_rtl_draw(const char*, int n, int x, int y);
FL_EXPORT void fl_measure(const char* str, int& x, int& y,
                          int draw_symbols = 1);
FL_EXPORT void fl_draw(const char* str, int x, int y, int w, int h,
                       Fl_Align align,
                       Fl_Image* img=0, int draw_symbols = 1);
FL_EXPORT void fl_draw(const char* str, int x, int y, int w, int h,
                       Fl_Align align,
                       void (*callthis)(const char *,int,int,int),
                       Fl_Image* img=0, int draw_symbols = 1);

// boxtypes:
FL_EXPORT void fl_frame(const char* s, int x, int y, int w, int h);
FL_EXPORT void fl_frame2(const char* s, int x, int y, int w, int h);
FL_EXPORT void fl_draw_box(Fl_Boxtype, int x, int y, int w, int h, Fl_Color);

// images:
/**
  signature of image generation callback function.
  \param[in]  data  user data passed to function
  \param[in]  x,y,w position and width of scan line in image
  \param[out] buf   buffer for generated image data. You must copy \p w
                    pixels from scanline \p y, starting at pixel \p x
		    to this buffer.
  */
typedef void (*Fl_Draw_Image_Cb)(void* data,int x,int y,int w,uchar* buf);

/**
  Draw an 8-bit per color RGB or luminance image.
  \param[in] buf points at the "r" data of the top-left pixel.
                 Color data must be in <tt>r,g,b</tt> order.
  \param[in] X,Y position where to put top-left corner of image
  \param[in] W,H size of the image
  \param[in] D   delta to add to the pointer between pixels. it may be
                 any value greater than or equal to 3, or it can be
		 negative to flip the image horizontally
  \param[in] L   delta to add to the pointer between lines (if 0 is
                 passed it uses \p W * \p D), and may be larger than
		 \p W * \p D to crop data, or negative to flip the
		 image vertically

  It is highly recommended that you put the following code before the
  first <tt>show()</tt> of \e any window in your program to get rid of
  the dithering if possible:
  \code
  Fl::visual(FL_RGB);
  \endcode
  Gray scale (1-channel) images may be drawn. This is done if
  <tt>abs(D)</tt> is less than 3, or by calling fl_draw_image_mono().
  Only one 8-bit sample is used for each pixel, and on screens with
  different numbers of bits for red, green, and blue only gray colors
  are used. Setting \p D greater than 1 will let you display one channel
  of a color image.

  \par Note:
  The X version does not support all possible visuals. If FLTK cannot
  draw the image in the current visual it will abort. FLTK supports
  any visual of 8 bits or less, and all common TrueColor visuals up
  to 32 bits.
  */
FL_EXPORT void fl_draw_image(const uchar* buf, int X,int Y,int W,int H, int D=3, int L=0);

/**
  Draw a gray-scale (1 channel) image.
  \see fl_draw_image(const uchar* buf, int X,int Y,int W,int H, int D, int L)
  */
FL_EXPORT void fl_draw_image_mono(const uchar* buf, int X,int Y,int W,int H, int D=1, int L=0);

/**
  Draw image using callback function to generate image data.
  You can generate the image as it is being drawn, or do arbitrary
  decompression of stored data, provided it can be decompressed to
  individual scan lines easily.
  \param[in] cb   callback function to generate scan line data
  \param[in] data user data passed to callback function
  \param[in] X,Y
  \param[in] W,H
  \param[in] D
  \see fl_draw_image(const uchar* buf, int X,int Y,int W,int H, int D, int L)

  The callback function \p cb is called with the <tt>void*</tt> \p data
  user data pointer to allow access to a structure of information about
  the image, and the \p x, \p y, and \p w of the scan line desired from
  the image. 0,0 is the upper-left corner of the image, not \p X, \p Y.
  A pointer to a buffer to put the data into is passed. You must copy
  \p w pixels from scanline \p y, starting at pixel \p x, to this buffer.

  Due to cropping, less than the whole image may be requested. So \p x
  may be greater than zero, the first \p y may be greater than zero,
  and \p w may be less than \p W. The buffer is long enough to store
  the entire \p W * \p D pixels, this is for convenience with some
  decompression schemes where you must decompress the entire line at
  once: decompress it into the buffer, and then if \p x is not zero,
  copy the data over so the \p x'th pixel is at the start of the buffer.

  You can assume the \p y's will be consecutive, except the first one
  may be greater than zero.

  If \p D is 4 or more, you must fill in the unused bytes with zero.
  */
FL_EXPORT void fl_draw_image(Fl_Draw_Image_Cb cb, void* data, int X,int Y,int W,int H, int D=3);

/**
  Draw gray-scale image using callback function to generate image data.
  \see fl_draw_image(Fl_Draw_Image_Cb cb, void* data, int X,int Y,int W,int H, int D)
  */
FL_EXPORT void fl_draw_image_mono(Fl_Draw_Image_Cb cb, void* data, int X,int Y,int W,int H, int D=1);

/**
  Checks whether platform supports true alpha blending for RGBA images.
  \returns 1 if true alpha blending supported by platform
  \returns 0 not supported so FLTK will use screen door transparency
  */
/* note: doxygen comment here to avoid triplication in os-speciic files */
FL_EXPORT char fl_can_do_alpha_blending();

/**
  Read an RGB(A) image from the current window or off-screen buffer.
  \param[in] p     pixel buffer, or NULL to allocate one
  \param[in] X,Y   position of top-left of image to read
  \param[in] W,H   width and height of image to read
  \param[in] alpha alpha value for image (0 fr none)
  \returns pointer to pixel buffer, or NULL if allocation failed.

  The \p p argument points to a buffer that can hold the image and must
  be at least \p W*H*3 bytes when reading RGB images, or \p W*H*4 bytes
  when reading RGBA images. If NULL, fl_read_image() will create an
  array of the proper suze which can be freed using <tt>delete[]</tt>.

  The \p alpha parameter controls whether an alpha channel is created
  and the value that is placed in the alpha channel. If 0, no alpha
  channel is generated.
  */
/* note: doxygen comment here to avoid triplication in os-speciic files */
FL_EXPORT uchar *fl_read_image(uchar *p,int X,int Y,int W,int H,int alpha=0);

// pixmaps:
FL_EXPORT int fl_draw_pixmap(/*const*/ char* const* data, int x,int y,Fl_Color=FL_GRAY);
FL_EXPORT int fl_draw_pixmap(const char* const* cdata, int x,int y,Fl_Color=FL_GRAY);
FL_EXPORT int fl_measure_pixmap(/*const*/ char* const* data, int &w, int &h);
FL_EXPORT int fl_measure_pixmap(const char* const* cdata, int &w, int &h);

// other:
FL_EXPORT void fl_scroll(int X, int Y, int W, int H, int dx, int dy,
                         void (*draw_area)(void*, int,int,int,int), void* data);
FL_EXPORT const char* fl_shortcut_label(unsigned int shortcut);
FL_EXPORT const char* fl_shortcut_label(unsigned int shortcut, const char **eom);
FL_EXPORT void fl_overlay_rect(int x,int y,int w,int h);
FL_EXPORT void fl_overlay_clear();
FL_EXPORT void fl_cursor(Fl_Cursor, Fl_Color fg=FL_BLACK, Fl_Color bg=FL_WHITE);
FL_EXPORT const char* fl_expand_text(const char* from, char* buf, int maxbuf,
                                     double maxw, int& n, double &width,
                                     int wrap, int draw_symbols = 0);

// XIM:
/** \todo provide user documentation for fl_set_status function */
FL_EXPORT void fl_set_status(int X, int Y, int W, int H);
/** \todo provide user documentation for fl_set_spot function */
FL_EXPORT void fl_set_spot(int font, int size, int X, int Y, int W, int H, fltk::Window *win=0);
/** \todo provide user documentation for fl_reset_spot function*/
FL_EXPORT void fl_reset_spot(void);



// XForms symbols:
FL_EXPORT int fl_draw_symbol(const char* label,int x,int y,int w,int h, Fl_Color);
FL_EXPORT int fl_add_symbol(const char* name, void (*drawit)(Fl_Color), int scalable);
/** @} */

#endif

//
// End of "$Id: fl_draw.H 6955 2009-12-07 22:04:55Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
// "$Id: draw.h 6233 2008-09-14 07:54:06Z spitzak $"
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

/*
  The FLTK drawing library, used by all widgets to draw themselves.

  These functions can only be called when FLTK is setup to draw
  things. This is only true:
  - Inside the Widget::draw() virtual function.
  - Inside the Symbol::draw() virtual function.
  - After calling Widget::make_current(), before calling wait() or flush().
  Calling the drawing functions at other times produces undefined results,
  including crashing.
*/

#ifndef fltk_draw_h
#define fltk_draw_h

#include "Flags.h" // for alignment values
#include "Color.h"
#include "Rectangle.h"
#include "PixelType.h"

namespace fltk {

/// \name fltk/draw.h
//@{

struct Font;
class Style;

class FL_API GSave {
  void* data[4]; // hopefully big enough for everybody...
 public:
  GSave();
  ~GSave();
};

// Transformation
FL_API void push_matrix();
FL_API void pop_matrix();
FL_API void scale(float x, float y);
FL_API void scale(float x);
FL_API void translate(float x, float y);
FL_API void translate(int x, int y);
FL_API void rotate(float d);
FL_API void concat(float, float, float, float, float, float);
FL_API void load_identity();

// get and use transformed positions:
FL_API void transform(float& x, float& y);
FL_API void transform_distance(float& x, float& y);
FL_API void transform(int& x, int& y);
FL_API void transform(const Rectangle& from, Rectangle& to);
FL_API void transform(int& x, int& y, int& w, int& h);

// Clipping
FL_API void push_clip(const Rectangle&);
//! Same as push_clip(Rectangle(x,y,w,h)) but faster:
FL_API void push_clip(int X,int Y, int W, int H);
FL_API void clipout(const Rectangle&);
FL_API void pop_clip();
FL_API void push_no_clip();
FL_API bool not_clipped(const Rectangle&);
FL_API int intersect_with_clip(Rectangle&);

FL_API void setcolor(Color);
FL_API void setcolor_alpha(Color, float alpha);
extern FL_API Color current_color_;
inline Color getcolor() {return current_color_;}

extern FL_API Color current_bgcolor_;
inline void setbgcolor(Color c) {current_bgcolor_ = c;}
inline Color getbgcolor() {return current_bgcolor_;}

extern FL_API const Style* drawstyle_;
void FL_API drawstyle(const Style* s, Flags);
inline const Style* drawstyle() {return drawstyle_;}

extern FL_API Flags drawflags_;
inline void setdrawflags(Flags f) {drawflags_ = f;}
inline Flags drawflags() {return drawflags_;}
inline Flags drawflags(Flags f) {return drawflags_ & f;}

// line type:
FL_API void line_style(int, float width=0, const char* dashes=0);
enum {
  SOLID	= 0,
  DASH	= 1,
  DOT	= 2,
  DASHDOT	= 3,
  DASHDOTDOT	= 4,

  CAP_FLAT	= 0x100,
  CAP_ROUND	= 0x200,
  CAP_SQUARE	= 0x300,

  JOIN_MITER	= 0x1000,
  JOIN_ROUND	= 0x2000,
  JOIN_BEVEL	= 0x3000
};
extern FL_API int line_style_;
inline FL_API int line_style() {return line_style_;}
extern FL_API float line_width_;
inline FL_API float line_width() {return line_width_;}
extern FL_API const char* line_dashes_;
inline FL_API const char* line_dashes() {return line_dashes_;}

// Path construction
FL_API void newpath();
FL_API void addvertex(float x, float y);
FL_API void addvertex(int x, int y);
FL_API void addvertices(int n, const float v[][2]);
FL_API void addvertices(int n, const int v[][2]);
FL_API void addvertices_transformed(int n, const float v[][2]);
FL_API void addcurve(float,float, float,float, float,float, float,float);
FL_API void addarc(float x,float y,float w,float h, float a1, float a2);
FL_API void addpie(const Rectangle& r, float a, float a2);
FL_API void addchord(const Rectangle& r,float a,float a2);
FL_API void closepath();

// Shapes and lines
FL_API void strokepath();
FL_API void fillpath();
FL_API void fillstrokepath(Color);

FL_API void fillrect(int, int, int, int);
inline void fillrect(const Rectangle& r) {fillrect(r.x(),r.y(),r.w(),r.h());}
FL_API void strokerect(int, int, int, int);
inline void strokerect(const Rectangle& r) {strokerect(r.x(),r.y(),r.w(),r.h());}
FL_API void drawline(int x0, int y0, int x1, int y1);
FL_API void drawline(float x0, float y0, float x1, float y1);
FL_API void drawpoint(int x, int y);
FL_API void drawpoint(float x, float y);

// Text
FL_API void setfont(Font*, float size);
FL_API void setfont(const char*, float size);
FL_API void setfont(const char*, int attributes, float size);

// change the encoding used to draw bytes (depreciated)
extern FL_API const char* encoding_;
inline const char* get_encoding() {return encoding_;}
FL_API void set_encoding(const char*);

// information you can get about the current font+size+encoding:
extern FL_API Font* current_font_;
extern FL_API float current_size_; // should be 2x2 transformation matrix
inline Font* getfont() {return current_font_;}
inline float getsize() {return current_size_;}

// measure things in the current font:
FL_API float getwidth(const char*);
FL_API float getwidth(const char*, int length);
FL_API float getascent();
FL_API float getdescent();

// draw using current font:
FL_API void drawtext_transformed(const char*, int n, float x, float y);
FL_API void drawtext(const char*, float x, float y);
FL_API void drawtext(const char*, int length, float x, float y);

// the label text formatter:
FL_API void measure(const char*, int& w, int& h, Flags = 0);
FL_API void measure(float (*getwidth)(const char*, int),const char*, float& w, float& h, Flags = 0);
FL_API void drawtext(const char*, const Rectangle&, Flags);
FL_API void drawtext(void (*textfunction)(const char*,int,float,float),
		     float (*getwidth)(const char*, int),
		     const char* str, const Rectangle& r, Flags flags);

// set where \t characters go in label text formatter:
extern FL_API const int* column_widths_;
inline const int* column_widths() {return column_widths_;}
inline void column_widths(const int* i) {column_widths_ = i;}
// see also Symbol.h for @-sign commands

// Images
FL_API void drawimage(const uchar*, PixelType, const Rectangle&);
FL_API void drawimage(const uchar*, PixelType, const Rectangle&, int linedelta);

typedef const uchar* (*DrawImageCallback)(void* data, int x, int y, int w, uchar* buffer);
FL_API void drawimage(DrawImageCallback, void*, PixelType, const Rectangle&);

FL_API uchar *readimage(uchar *p, PixelType, const Rectangle&);
FL_API uchar *readimage(uchar *p, PixelType, const Rectangle&, int linedelta);

FL_API void scrollrect(const Rectangle&, int dx, int dy,
		       void (*draw_area)(void*, const Rectangle&), void*);

#ifndef DOXYGEN /* depreciated: */
FL_API void drawframe(const char* s, int x, int y, int w, int h);
FL_API void drawframe2(const char* s, int x, int y, int w, int h);
FL_API void overlay_rect(int,int,int,int);
FL_API void overlay_clear();
#endif

//@}

}

#endif

//
// End of "$Id: draw.h 6233 2008-09-14 07:54:06Z spitzak $".
//
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
