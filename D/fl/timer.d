/+- This file was imported from C++ using a script
//
// "$Id: timer.d 4288 2005-04-16 00:13:17Z mike $"
//
// Timer header file for the Fast Light Tool Kit (FLTK).
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

module fl.timer;


module fl.widget;
public import fl.widget;
}

// values for type():
const int FL_NORMAL_TIMER = 0; 
const int FL_VALUE_TIMER = 1; 
const int FL_HIDDEN_TIMER = 2; 

class Fl_Timer : Fl_Widget {
  static void stepcb(void *);
  void step();
  char on, direction_;
  double delay, total;
  int lastsec,lastusec;
protected:
  void draw();
public:
  int handle(int);
  Fl_Timer(ubyte t,int x,int y,int w,int h, char *l);
  ~Fl_Timer();
  void value(double);
  double value() {return delay>0.0?delay:0.0;}
  char direction() {return direction_;}
  void direction(char d) {direction_ = d;}
  char suspended() {return !on;}
  void suspended(char d);
};

}

//
// End of "$Id: timer.d 4288 2005-04-16 00:13:17Z mike $".
//

    End of automatic import -+/
