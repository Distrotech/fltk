//
// "$Id: Fl_FormsBitmap.h,v 1.1 2001/07/23 09:50:04 spitzak Exp $"
//
// Forms bitmap header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-1999 by Bill Spitzak and others.
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
// Please report all bugs and problems to "fltk-bugs@easysw.com".
//

#ifndef Fl_FormsBitmap_H
#define Fl_FormsBitmap_H

#include <fltk/Fl_Bitmap.h>

class FL_FORMS_API Fl_FormsBitmap : public Fl_Widget {
    Fl_Bitmap *b;
protected:
    void draw();
public:
    Fl_FormsBitmap(Fl_Boxtype, int, int, int, int, const char * = 0);
    void set(int W, int H, const uchar *bits);
    void bitmap(Fl_Bitmap *B) {b = B;}
    Fl_Bitmap *bitmap() const {return b;}
};

#endif

//
// End of "$Id: Fl_FormsBitmap.h,v 1.1 2001/07/23 09:50:04 spitzak Exp $".
//
