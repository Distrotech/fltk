//
// "$Id$"
//
// MSWin implementation of Fl_Clipboard_Writer class for the Fast Light Tool Kit (FLTK).
//
// Copyright 2010 by Bill Spitzak and others.
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
// Please report all bugs and problems to:
//
//     http://www.fltk.org/str.php
//

#ifdef WIN32

#include <FL/Fl_Clipboard_Writer.H>
#include <FL/x.H>
#include <FL/fl_draw.H>


int Fl_Clipboard_Writer::start(int w, int h)
{
  HDC oldflgc = fl_gc;
  int factor = 32; // empirically set
  RECT rect; rect.left = 0; rect.top = 0; rect.right=w*factor; rect.bottom=h*factor;
  fl_gc = CreateEnhMetaFile (NULL, NULL, &rect, NULL);
  if (fl_gc != NULL) {
    SetGraphicsMode(fl_gc, GM_ADVANCED); // to allow for translations
    SetTextAlign(fl_gc, TA_BASELINE|TA_LEFT);
    SetBkMode(fl_gc, TRANSPARENT);
  } 
  else {
    fl_gc = oldflgc;
    return 1;
  }
  fl_clip_region(0);
  fl_color(FL_BLACK);
  fl_line_style(FL_SOLID);
SelectObject(fl_gc, (HGDIOBJ)(fl_current_xmap->pen));
  gc = fl_gc;
  this->set_current();
  return 0;
}

int Fl_Clipboard_Writer::stop(void)
{
  int w, h;
  HENHMETAFILE hmf = CloseEnhMetaFile (fl_gc);
  if ( hmf != NULL ) {
    if ( OpenClipboard (NULL) ){
      EmptyClipboard ();
      SetClipboardData (CF_ENHMETAFILE, hmf);
      CloseClipboard ();
    }
    DeleteEnhMetaFile(hmf);
  }
  DeleteDC(fl_gc);
  Fl_Device::display_device()->set_current();
  fl_gc = NULL;
  return 0;
}

static int translate_stack_depth = 0;
const int translate_stack_max = 5;
static int translate_stack_x[translate_stack_max];
static int translate_stack_y[translate_stack_max];

static void do_translate(int x, int y)
{
  XFORM tr;
  tr.eM11 = tr.eM22 = 1;
  tr.eM12 = tr.eM21 = 0;
  tr.eDx =  x;
  tr.eDy =  y;
  ModifyWorldTransform(fl_gc, &tr, MWT_LEFTMULTIPLY);
}

void Fl_Clipboard_Writer::translate(int x, int y)
{
  do_translate(x, y);
  if (translate_stack_depth < translate_stack_max) {
    translate_stack_x[translate_stack_depth] = x;
    translate_stack_y[translate_stack_depth] = y;
    translate_stack_depth++;
  }
}

void Fl_Clipboard_Writer::untranslate(void)
{
  if (translate_stack_depth > 0) {
    translate_stack_depth--;
    do_translate( - translate_stack_x[translate_stack_depth], - translate_stack_y[translate_stack_depth] );
  }
}

#endif // WIN32

//
// End of "$Id$".
//
