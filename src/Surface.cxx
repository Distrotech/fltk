// Surface.cxx: implementation of the Surface class.
//
//////////////////////////////////////////////////////////////////////

#include "FLTK/Surface.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

using namespace fltk;

Surface::~Surface() {
	// Derived classes will have the responsibility to destroy
	// all device dependent data here.
}

/**
default behavior for this virtual method is false (= no alpha cap.)
Override this method to add alpha cap.
*/
bool Surface::can_do_alpha_blending() {
	return false;
}

/**
default behavior for this virtual method is calling copy() 
Override this method to add alpha cap.
*/
bool Surface::copy_with_alpha(int x,int y,int w,int h,int srcx,int srcy) {
	return this->copy(x, y, w, h, srcx, srcy);
}
