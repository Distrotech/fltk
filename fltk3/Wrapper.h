//
// "$Id: Wrapper.h 7365 2010-03-30 15:18:29Z matt $"
//
// Widget header file for the Fast Light Tool Kit (FLTK).
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

/* \file
   fltk3::Wrapper */

#ifndef FLTK3_Wrapper_H
#define FLTK3_Wrapper_H

namespace fltk3 {
  
  class Object; 

/**
 * \brief a base class for any kind of langage wrapper around FLTK3.
 */
  class Wrapper {
  protected:
    Object *_p;
  public:
    Wrapper() 
    : _p(0L) { }
    virtual ~Wrapper() { }
    
    unsigned int pVCalls;
    static const unsigned int pVCallWidgetDraw   = 1<<0;
    static const unsigned int pVCallWidgetHandle = 1<<1;
    static const unsigned int pVCallWidgetResize = 1<<2;
    static const unsigned int pVCallWidgetShow   = 1<<3;
    static const unsigned int pVCallWidgetHide   = 1<<4;
    
    virtual void draw() { /* call _p->draw() with a flag set */ }
  };
  
  
  class WidgetWrapper : public Wrapper {
  public:
    virtual ~WidgetWrapper() {}
    virtual void draw() {
      pVCalls |= pVCallWidgetDraw;
      ((fltk3::Widget*)_p)->draw();
      pVCalls &= ~pVCallWidgetDraw;
    }
    virtual int handle(int event) { 
      pVCalls |= pVCallWidgetHandle;
      int ret = ((fltk3::Widget*)_p)->handle(event);
      pVCalls &= ~pVCallWidgetHandle;
      return ret;
    }
    virtual void resize(int x, int y, int w, int h) {
      pVCalls |= pVCallWidgetResize;
      ((fltk3::Widget*)_p)->resize(x, y, w, h);
      pVCalls &= ~pVCallWidgetResize;
    }
    virtual void show() {
      pVCalls |= pVCallWidgetShow;
      ((fltk3::Widget*)_p)->show();
      pVCalls &= ~pVCallWidgetShow;
    }
    virtual void hide() {
      pVCalls |= pVCallWidgetHide;
      ((fltk3::Widget*)_p)->hide();
      pVCalls &= ~pVCallWidgetHide;
    }
  };
  
  
}; // namespace fltk3


#endif

//
// End of "$Id: Wrapper.h 7365 2010-03-30 15:18:29Z matt $".
//
