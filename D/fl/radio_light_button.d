/+- This file was imported from C++ using a script
//
// "$Id: radio_light_button.d 4288 2005-04-16 00:13:17Z mike $"
//
// Radio light button header file for the Fast Light Tool Kit (FLTK).
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
module fl.radio_light_button;


public import fl.light_button;

class Fl_Radio_Light_Button : Fl_Light_Button {
public:
    Fl_Radio_Light_Button(int X,int Y,int W,int H,char *l=0)
	: Fl_Light_Button(X,Y,W,H,l) {type(FL_RADIO_BUTTON);}
};

}

//
// End of "$Id: radio_light_button.d 4288 2005-04-16 00:13:17Z mike $".
//
    End of automatic import -+/
