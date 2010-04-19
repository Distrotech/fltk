//
// "$Id$"
//
// implementation of Fl_Clipboard_Writer class for the Fast Light Tool Kit (FLTK).
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
#if defined(WIN32) || defined(__APPLE__) || defined(FL_DOXYGEN)

#ifdef __APPLE__
#include "Fl_Clipboard_Device_mac.cxx"
#elif defined(WIN32)
#include "Fl_Clipboard_Device_win32.cxx"
#endif

#include <FL/Fl_Printer.H>

const char *Fl_Clipboard_Device::device_type = "Fl_Clipboard_Device";

#if !(defined(WIN32) || defined(__APPLE__))
// not implemented yet
int Fl_Clipboard_Device::start(int w, int h) {}
int Fl_Clipboard_Device::stop(void) {}
void Fl_Clipboard_Device::translate(int x, int y) {}
void Fl_Clipboard_Device::untranslate(void) {}
#endif

void Fl_Clipboard_Device::set_current(void)
{
#ifdef __APPLE__
  fl_gc = (CGContextRef)gc;
#elif defined(WIN32)
  fl_gc = (HDC)gc;
#else
  fl_gc = (_XGC*)0;
#endif
  this->Fl_Surface_Device::set_current();
}

void Fl_Clipboard_Device::copy_widget(Fl_Widget* widget, int delta_x, int delta_y) 
{ 
  int new_x, new_y, is_window;
  if ( ! widget->visible() ) return;
  is_window = (widget->as_window() != NULL);
  widget->damage(FL_DAMAGE_ALL);
  // set origin to the desired top-left position of the widget
  new_x = delta_x;
  new_y = delta_y;
  if (!is_window) {
    new_x -= widget->x();
    new_y -= widget->y();
  }
  if (new_x != 0 || new_y != 0) {
    translate(new_x, new_y );
  }
#ifndef WIN32 // doesn't  work on WIN32. Why ?
  // if widget is a window, clip all drawings to the window area
  if (is_window) fl_push_clip(0, 0, widget->w(), widget->h() );
#endif
  // we do some trickery to recognize OpenGL windows and draw them via a plugin
  int drawn_by_plugin = 0;
  if (widget->as_gl_window()) {
     Fl_Plugin_Manager pm("fltk:device");  
     Fl_Device_Plugin *pi = (Fl_Device_Plugin*)pm.plugin("opengl.device.fltk.org");
     if (pi) {
       int height = 0;
#ifdef __APPLE__
       int width;
       this->bounds(&width, &height);
#endif
       drawn_by_plugin = pi->print(widget, 0, 0, height);
       }
  }
  if (!drawn_by_plugin) {
    widget->draw();
  }
#ifndef WIN32
  if (is_window) fl_pop_clip();
#endif
  // find subwindows of widget and print them
  traverse(widget);
  // reset origin to where it was
  if (new_x != 0 || new_y != 0) {
    untranslate();
  }
}

void Fl_Clipboard_Device::traverse(Fl_Widget *widget)
{
  Fl_Group *g = widget->as_group();
  if (!g) return;
  int n = g->children();
  for (int i = 0; i < n; i++) {
    Fl_Widget *c = g->child(i);
    if ( !c->visible() ) continue;
    if ( c->as_window() ) {
      copy_widget(c, c->x(), c->y());
    }
    else traverse(c);
  }
}

#endif

//
// End of "$Id$".
//

