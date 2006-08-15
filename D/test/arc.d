//
// "$Id: arc.d 5169 2006-05-31 18:33:05Z mike $"
//
// Arc drawing test program for the Fast Light Tool Kit (FLTK).
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

private import fl.fl;
private import fl.double_window;
private import fl.hor_value_slider;
private import fl.draw;

double[6] args = [140, 140, 50, 0, 360, 0];
char[6][] name = ["X", "Y", "R", "start", "end", "rotate"];

class Drawing : Fl_Widget {
  void draw() {
    fl_clip(x(),y(),w(),h());
    fl_color(FL_DARK3);
    fl_rectf(x(),y(),w(),h());
    fl_push_matrix();
    if (args[5]) {
      fl_translate(x()+w()/2.0, y()+h()/2.0);
      fl_rotate(args[5]);
      fl_translate(-(x()+w()/2.0), -(y()+h()/2.0));
    }
    fl_color(FL_WHITE);
    fl_translate(x(),y());
    fl_begin_complex_polygon();
    fl_arc(args[0],args[1],args[2],args[3],args[4]);
    fl_gap();
    fl_arc(140,140,20,0,-360);
    fl_end_complex_polygon();
    fl_color(FL_RED);
    fl_begin_line();
    fl_arc(args[0],args[1],args[2],args[3],args[4]);
    fl_end_line();
    fl_pop_matrix();
    fl_pop_clip();
  }
public:
  this(int X,int Y,int W,int H) { 
    super(X,Y,W,H);
  }
};

Drawing d;

void slider_cb(Fl_Widget o, void* v) {
  Fl_Slider s = cast(Fl_Slider)o;
  args[cast(int)v] = s.value();
  d.redraw();
}

int main(char[][] args) {
  Fl_Double_Window window = new Fl_Double_Window(300,500);
  Drawing drawing = new Drawing(10,10,280,280);
  d = drawing;

  int y = 300;
  for (int n = 0; n<6; n++) {
    Fl_Slider s = new Fl_Hor_Value_Slider(50,y,240,25,name[n]); y += 25;
    if (n<3) {s.minimum(0); s.maximum(300);}
    else if (n==5) {s.minimum(0); s.maximum(360);}
    else {s.minimum(-360); s.maximum(360);}
    s.step(1);
    /+=s.value(args[n]);=+/
    s.alignment(FL_ALIGN_LEFT);
    /+=s.callback(slider_cb, cast(void*)n);=+/
  }

  window.end();
  window.show(args);
  return Fl.run();
}


//
// End of "$Id: arc.d 5169 2006-05-31 18:33:05Z mike $".
//

