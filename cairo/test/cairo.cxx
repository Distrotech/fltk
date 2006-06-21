//
// "$Id: arc.cxx 5115 2006-05-12 16:00:00Z fabien $"
//
// Arc drawing test program for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2006 by Bill Spitzak and others.
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
//

#include <config.h>
#include <fltk/run.h>
#include <fltk/x.h>
#include <fltk/DoubleBufferWindow.h>
#include <fltk/ValueSlider.h>
#include <fltk/draw.h>
#include <fltk/math.h>

using namespace fltk;

class CairoWindow : public Window {
public:
    CairoWindow(int w, int h) : Window(w,h),draw_cb_(0) {}

    void draw() {
	if (!draw_cb_) return;
	// prepare for cairo context
	cairo_surface_t * surface = create_surface();
	cairo_t* cr = ::cairo_create(surface);

	draw_cb_(*this, surface, cr); // enjoy cairo features here !
	
	// release cairo context
	cairo_destroy(cr);
	cairo_surface_destroy (surface);
    }

    cairo_surface_t * create_surface() 
	// comments:
	// 1. not portable: will have to be fusioned with xlib version
	// 2. needs the access addon in Window of the backbuffer method
	//   so I temporarily added a backbuffer() method to Window
	{return cairo_win32_surface_create((HDC)backbuffer());}

    typedef void (*draw_cb) (CairoWindow& self, cairo_surface_t* surface,cairo_t* def);
    void set_draw_cb(draw_cb  cb){draw_cb_=cb;}
private:
    draw_cb draw_cb_;
};

// put your stuff here
void my_cairo_draw_cb(CairoWindow& window, cairo_surface_t* surface,cairo_t* cr) {
	
    //HDC dc= created_window()->bdc ;
    double xc = 0.5;
    double yc = 0.5;
    double radius = 0.4;
    double angle1 = 45.0  * (M_PI/180.0);  /* angles are specified */
    double angle2 = 180.0 * (M_PI/180.0);  /* in radians           */
    
    cairo_scale (cr, window.w()/2, window.h()/2);
    cairo_translate(cr, 0.2,0.2);
    cairo_set_source_rgba (cr, 1, 1, 1, 1);
    cairo_paint(cr);
    
    cairo_arc (cr, xc, yc, radius, angle1, angle2);
    cairo_stroke (cr);
    
    /* draw helping lines */
    cairo_set_source_rgba (cr, 1,0.2,0.2,0.6);
    cairo_arc (cr, xc, yc, 0.05, 0, 2*M_PI);
    cairo_fill (cr);
    cairo_set_line_width (cr, 0.03);
    cairo_arc (cr, xc, yc, radius, angle1, angle1);
    cairo_line_to (cr, xc, yc);
    cairo_arc (cr, xc, yc, radius, angle2, angle2);
    cairo_line_to (cr, xc, yc);
    cairo_stroke (cr);

}

int main(int argc, char** argv) {
    CairoWindow window(300,300);
    window.resizable(&window);
    window.show(argc,argv);
    window.set_draw_cb(my_cairo_draw_cb);
    
    return fltk::run();
}


//
// End of "$Id: arc.cxx 5115 2006-05-12 16:00:00Z fabien $".
//
