// "$Id: Offscreen.h"
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

/*! \class fltk::Offscreen

This is an offset drawing class surfaces
This class will permit to use alpha blending in a 'best effort' way. 
It means that when no alpha blending support is available, simple copy
operations will be implemented by default
*/

#if !defined(FLTK_OFFSCREEN_H)
#define FLTK_OFFSCREEN_H

#include <fltk/Surface.h>

// class Window;

namespace fltk {

class FL_API Offscreen : public Surface {
public:
		// ---------- Define device dependent type and data --------------------------
#if defined(WIN32)
 typedef HBITMAP GraphicData;
private:
	int num_saved_dc_;	  // for cleaning up our offscreen created dc

#elif defined(__APPLE__) && USE_QUARTZ
 typedef CGContextRef GraphicData;
#elif defined(__APPLE__) && !USE_QUARTZ
 typedef GWorldPtr GraphicData;
#else
 typedef void * GraphicData;
#endif

public:
	// fltk Offscreen Surface Construction / Destruction
	Offscreen(const Rectangle& dim) : Surface(dim) {create();}
	Offscreen(int w, int h): Surface(Rectangle(w, h)) {create();}
	Offscreen(int x, int y, int w, int h) : Surface(Rectangle(x,y, w, h)) {create();}
	Offscreen(GraphicData hgd); // do not create offscreen use this one instead, do not 
	virtual ~Offscreen();

	// Offscreen device dependent overriden method impl. :

	//! Select the offscreen surface for drawing & save previous graphical context
	bool begin(); 
	//! Restore previous graphical context
	bool end(); 

	//! Copies the device content to fl gc, return true if done successfully
	bool copy(int x,int y,int w,int h,int srcx,int srcy); 
	//! Copies the device content to fl gc with alpha if available, return true if done successfully
	bool copy_with_alpha(int x,int y,int w,int h,int srcx,int srcy); 

protected:
	bool can_do_alpha_blending();

private:
	void create();

	GraphicData graphic_data_;
	bool must_cleanup_;
	
	GSave* context_save_; // for proper begin() / end() context save / restore

};

} // End of fltk namespace

#endif // !defined(FLTK_OFFSCREEN_H)

//
// End of "$Id"
//
