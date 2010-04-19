//
// "$Id$"
//
// declaration of Fl_Clipboard_Device class for the Fast Light Tool Kit (FLTK).
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

#ifndef FL_CLIPBOARD_DEVICE_H
#define FL_CLIPBOARD_DEVICE_H

#include <FL/Fl_Device.H>

/**
 \brief Sends all graphics requests to the clipboard.
 
 Presently implemented for the MSWindows and Mac OS X platforms only.
 */
class Fl_Clipboard_Device : public Fl_Surface_Device {
private:
#ifdef __APPLE__
  int width, height;
  CFMutableDataRef pdfdata_;
#endif
  /** \brief the clipboard's graphics context, if there's one, NULL otherwise */
//  void *gc;
  void traverse(Fl_Widget *widget);
  void translate(int x, int y);
  void untranslate(void);
public:
  static const char *device_type;
#ifdef __APPLE__
  inline void bounds(int *pwidth, int *pheight) {*pwidth = width; *pheight = height; }
#endif
  /** \brief The constructor */
  Fl_Clipboard_Device() : Fl_Surface_Device(fl_device) {type_ = device_type;};
  /** \brief To be called before any graphics request.
   \param w The width in pixels of the clipboard drawing surface
   \param h The height in pixels of the clipboard drawing surface
   */
  int start(int w, int h);
  /** \brief Copies a widget to the clipboard 
   \param widget A FLTK widget of any kind
   \param delta_x Horizontal offset for position of the widget top-left angle.
   \param delta_y Vertical offset for position of the widget top-left angle.
   */
  void copy_widget(Fl_Widget* widget, int delta_x = 0, int delta_y = 0);
  /** \brief To be called after all graphics requests were done */
  int stop();
  void set_current();
};

#endif // FL_CLIPBOARD_DEVICE_H

//
// End of "$Id$".
//
