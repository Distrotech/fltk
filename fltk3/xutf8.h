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

/* "$Id: Xutf8.h 6942 2009-11-18 12:22:51Z AlbrechtS $"
 *
 * Author: Jean-Marc Lienher ( http://oksid.ch )
 * Copyright 2000-2003 by O'ksi'D.
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

#ifndef _Xutf8_h
#define _Xutf8_h

#  ifdef __cplusplus
extern "C" {
#  endif

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xlocale.h>
#include <X11/Xutil.h>

typedef struct {
	int nb_font;
	char **font_name_list;
	int *encodings;
	XFontStruct **fonts;
	Font fid;
	int ascent;
	int descent;
	int *ranges;
} XUtf8FontStruct;

XUtf8FontStruct *
XCreateUtf8FontStruct (
	Display         *dpy, 
	const char      *base_font_name_list); 

void
XUtf8DrawString(
        Display         	*display,
        Drawable        	d,
        XUtf8FontStruct  *font_set,
        GC              	gc,
        int             	x,
        int             	y,
        const char      	*string,
        int             	num_bytes);

void
XUtf8DrawRtlString(
        Display         	*display,
        Drawable        	d,
        XUtf8FontStruct  *font_set,
        GC              	gc,
        int             	x,
        int             	y,
        const char      	*string,
        int             	num_bytes);

void
XUtf8DrawImageString(
        Display         *display,
        Drawable        d,
        XUtf8FontStruct         *font_set,
        GC              gc,
        int             x,
        int             y,
        const char      *string,
        int             num_bytes);

int
XUtf8TextWidth(
        XUtf8FontStruct  *font_set,
        const char      	*string,
        int             	num_bytes);
int 
XUtf8UcsWidth(
	XUtf8FontStruct  *font_set,
	unsigned int            ucs);

int
XGetUtf8FontAndGlyph(
        XUtf8FontStruct  *font_set,
        unsigned int            ucs,
        XFontStruct     **fnt,
        unsigned short  *id);
	
void
XFreeUtf8FontStruct(
        Display         	*dpy,
        XUtf8FontStruct 	*font_set);


int 
XConvertUtf8ToUcs( 
	const unsigned char 	*buf, 
	int 			len, 
	unsigned int 		*ucs);

int 
XConvertUcsToUtf8(
	unsigned int 		ucs, 
	char 			*buf);

int 
XUtf8CharByteLen(
	const unsigned char 	*buf, 
	int 			len);

int 
XCountUtf8Char(
	const unsigned char *buf, 
	int len);

int 
XFastConvertUtf8ToUcs( 
	const unsigned char 	*buf, 
	int 			len, 
	unsigned int 		*ucs);

long 
XKeysymToUcs(
	KeySym 	keysym);

int
XUtf8LookupString(
    XIC                 ic,
    XKeyPressedEvent*   event,
    char*               buffer_return,
    int                 bytes_buffer,
    KeySym*             keysym,
    Status*             status_return);

unsigned short 
XUtf8IsNonSpacing(
	unsigned int ucs);

unsigned short
XUtf8IsRightToLeft(
        unsigned int ucs);


int 
XUtf8Tolower(
        int ucs);

int 
XUtf8Toupper(
        int ucs);


#  ifdef __cplusplus
}
#  endif

#endif

/*
 *  End of "$Id: Xutf8.h 6942 2009-11-18 12:22:51Z AlbrechtS $".
 */ 

/* suggested twin class
// This is the Twin Class to fltk::xutf8
class Xutf8 : public fltk::xutf8 {
public:
  Xutf8(int x, int t, int w, int h, const char *label=0)
  : fltk::xutf8(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
/* "$Id: Xutf8.h 6942 2009-11-18 12:22:51Z AlbrechtS $"
 *
 * Author: Jean-Marc Lienher ( http://oksid.ch )
 * Copyright 2000-2003 by O'ksi'D.
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

#ifndef _Xutf8_h
#define _Xutf8_h

#  ifdef __cplusplus
extern "C" {
#  endif

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xlocale.h>
#include <X11/Xutil.h>

typedef struct {
	int nb_font;
	char **font_name_list;
	int *encodings;
	XFontStruct **fonts;
	Font fid;
	int ascent;
	int descent;
	int *ranges;
} XUtf8FontStruct;

XUtf8FontStruct *
XCreateUtf8FontStruct (
	Display         *dpy, 
	const char      *base_font_name_list); 

void
XUtf8DrawString(
        Display         	*display,
        Drawable        	d,
        XUtf8FontStruct  *font_set,
        GC              	gc,
        int             	x,
        int             	y,
        const char      	*string,
        int             	num_bytes);

void
XUtf8DrawRtlString(
        Display         	*display,
        Drawable        	d,
        XUtf8FontStruct  *font_set,
        GC              	gc,
        int             	x,
        int             	y,
        const char      	*string,
        int             	num_bytes);

void
XUtf8DrawImageString(
        Display         *display,
        Drawable        d,
        XUtf8FontStruct         *font_set,
        GC              gc,
        int             x,
        int             y,
        const char      *string,
        int             num_bytes);

int
XUtf8TextWidth(
        XUtf8FontStruct  *font_set,
        const char      	*string,
        int             	num_bytes);
int 
XUtf8UcsWidth(
	XUtf8FontStruct  *font_set,
	unsigned int            ucs);

int
XGetUtf8FontAndGlyph(
        XUtf8FontStruct  *font_set,
        unsigned int            ucs,
        XFontStruct     **fnt,
        unsigned short  *id);
	
void
XFreeUtf8FontStruct(
        Display         	*dpy,
        XUtf8FontStruct 	*font_set);


int 
XConvertUtf8ToUcs( 
	const unsigned char 	*buf, 
	int 			len, 
	unsigned int 		*ucs);

int 
XConvertUcsToUtf8(
	unsigned int 		ucs, 
	char 			*buf);

int 
XUtf8CharByteLen(
	const unsigned char 	*buf, 
	int 			len);

int 
XCountUtf8Char(
	const unsigned char *buf, 
	int len);

int 
XFastConvertUtf8ToUcs( 
	const unsigned char 	*buf, 
	int 			len, 
	unsigned int 		*ucs);

long 
XKeysymToUcs(
	KeySym 	keysym);

int
XUtf8LookupString(
    XIC                 ic,
    XKeyPressedEvent*   event,
    char*               buffer_return,
    int                 bytes_buffer,
    KeySym*             keysym,
    Status*             status_return);

unsigned short 
XUtf8IsNonSpacing(
	unsigned int ucs);

unsigned short
XUtf8IsRightToLeft(
        unsigned int ucs);


int 
XUtf8Tolower(
        int ucs);

int 
XUtf8Toupper(
        int ucs);


#  ifdef __cplusplus
}
#  endif

#endif

/*
 *  End of "$Id: Xutf8.h 6942 2009-11-18 12:22:51Z AlbrechtS $".
 */ 
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
