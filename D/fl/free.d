/+- This file was imported from C++ using a script
//
// "$Id: free.d 4288 2005-04-16 00:13:17Z mike $"
//
// Forms free header file for the Fast Light Tool Kit (FLTK).
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

module fl.free;


module fl.widget;
public import fl.widget;
}

const int FL_NORMAL_FREE = 1; 
const int FL_SLEEPING_FREE = 2; 
const int FL_INPUT_FREE = 3; 
const int FL_CONTINUOUS_FREE = 4; 
const int FL_ALL_FREE = 5; 

alias int (*FL_HANDLEPTR)(Fl_Widget  , int , float, float, char);

class Fl_Free : Fl_Widget {
    FL_HANDLEPTR hfunc;
    static void step(void *);
protected:
    void draw();
public:
    int handle(int);
    Fl_Free(ubyte t,int x,int y,int w,int h,char *l,FL_HANDLEPTR hdl);
    ~Fl_Free();
};

// old event names for compatability:
const int FL_MOUSE = FL_DRAG; 
const int FL_DRAW = 100; 		// NOT USED
const int FL_STEP = 101; 
const int FL_FREEMEM = 102; 		// NOT USED
const int FL_FREEZE = 103; 		// NOT USED
const int FL_THAW = 104; 		// NOT USED

}

//
// End of "$Id: free.d 4288 2005-04-16 00:13:17Z mike $".
//
    End of automatic import -+/
