/+- This file was imported from C++ using a script
//
// "$Id: return_button.d 4288 2005-04-16 00:13:17Z mike $"
//
// Return button header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2005 by Bill Spitzak and others.
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

module fl.return_button;

public import fl.button;

class Fl_Return_Button : Fl_Button {
protected:
  void draw();
public:
  int handle(int);
  Fl_Return_Button(int X, int Y, int W, int H,char *l=0)
    : Fl_Button(X,Y,W,H,l) {}
};

}

//
// End of "$Id: return_button.d 4288 2005-04-16 00:13:17Z mike $".
//
    End of automatic import -+/
/+- This file was imported from C++ using a script
//
// "$Id: return_button.d 5190 2006-06-09 16:16:34Z mike $"
//
// Return button widget for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2005 by Bill Spitzak and others.
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

#include <FL/Fl.H>
private import fl.return_button;
private import fl.draw;

int fl_return_arrow(int x, int y, int w, int h) {
  int size = w; if (h<size) size = h;
  int d = (size+2)/4; if (d<3) d = 3;
  int t = (size+9)/12; if (t<1) t = 1;
  int x0 = x+(w-2*d-2*t-1)/2;
  int x1 = x0+d;
  int y0 = y+h/2;
  fl_color(FL_LIGHT3);
  fl_line(x0, y0, x1, y0+d);
  fl_yxline(x1, y0+d, y0+t, x1+d+2*t, y0-d);
  fl_yxline(x1, y0-t, y0-d);
  fl_color(fl_gray_ramp(0));
  fl_line(x0, y0, x1, y0-d);
  fl_color(FL_DARK3);
  fl_xyline(x1+1, y0-t, x1+d, y0-d, x1+d+2*t);
  return 1;
}

void Fl_Return_Button.draw() {
  if (type() == FL_HIDDEN_BUTTON) return;
  draw_box(value() ? (down_box()?down_box():fl_down(box())) : box(),
	   value() ? selection_color() : color());
  int W = h();
  if (w()/3 < W) W = w()/3;
  fl_return_arrow(x()+w()-W-4, y(), W, h());
  draw_label(x(), y(), w()-W+4, h());
  if (Fl.focus() == this) draw_focus();
}

int Fl_Return_Button.handle(int event) {
  if (event == FL_SHORTCUT &&
      (Fl.event_key() == FL_Enter || Fl.event_key() == FL_KP_Enter)) {
    do_callback();
    return 1;
  } else
    return Fl_Button.handle(event);
}

//
// End of "$Id: return_button.d 5190 2006-06-09 16:16:34Z mike $".
//
    End of automatic import -+/
