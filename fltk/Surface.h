// "$Id: Surface.h"
//
// Copyright 1998-2007 by Bill Spitzak and others.
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

/*! \class fltk::Surface

This is generic base class for the Window, Offscreen, Printing 2D Graphic 
surfaces
This class will permit to use alpha blending in a 'best effort' way. 
It means that when no alpha blending support is available, simple copy
operations will be implemented by default

*/

#if !defined(FLTK_SURFACE_H)
#define FLTK_SURFACE_H

#include <fltk/FL_API.h>
#include <fltk/Rectangle.h>

namespace fltk {

class FL_API Surface  
{
public:
	// Construction / Destruction of a Surface
	//! Creates a surface and makes it the current one
	Surface(const Rectangle& dim) : dim_(dim) {}
	Surface(int w, int h) : dim_(Rectangle(w,h)) {}
	Surface(int x, int y, int w, int h) : dim_(Rectangle(x,y,w,h)) {}
	Surface() {} // for handling device context with no context creation (using existing context)

	virtual ~Surface();

	// Virtual (device dependent) API
	
	//! select the surface for drawing save previous graphical context, return true if successful
	virtual bool begin() {return true;} 
	//! restore previous graphical context, return true if successful
	virtual bool end()	 {return true;} 
	
	// copies the device content to fl gc
	virtual bool copy(int x,int y,int w,int h,int srcx,int srcy)=0; 
	// copies the device content to fl gc
	virtual bool copy_with_alpha(int x,int y,int w,int h,int srcx,int srcy); 

protected:
	// overrides this to true if device can handle alpha:
	virtual bool can_do_alpha_blending(); 

	Rectangle dim_;
};

} // fltk namespace

#endif // !defined(FLTK_SURFACE_H)
//
// End of "$Id"
//
