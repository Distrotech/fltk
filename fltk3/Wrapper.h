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
    virtual void draw() { /* call _p->draw() with a flag set */ }
  };
  
  
  class WidgetWrapper : public Wrapper {
  public:
    virtual ~WidgetWrapper() {}
    virtual void draw() {
      pVCalls |= 1;
      ((fltk3::Widget*)_p)->draw();
      pVCalls &= ~1;
    }
    virtual int handle(int event) { 
      pVCalls |= 1;
      int ret = ((fltk3::Widget*)_p)->handle(event);
      pVCalls &= ~1;
      return ret;
    }
    virtual void resize(int x, int y, int w, int h) {
      pVCalls |= 1;
      ((fltk3::Widget*)_p)->resize(x, y, w, h);
      pVCalls &= ~1;
    }
    virtual void show() {
      pVCalls |= 1;
      ((fltk3::Widget*)_p)->show();
      pVCalls &= ~1;
    }
    virtual void hide() {
      pVCalls |= 1;
      ((fltk3::Widget*)_p)->hide();
      pVCalls &= ~1;
    }
  };
  
  
}; // namespace fltk3


#endif

//
// End of "$Id: Wrapper.h 7365 2010-03-30 15:18:29Z matt $".
//
