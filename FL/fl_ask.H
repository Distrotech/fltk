//
// "$Id$"
//
// Standard dialog header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2009 by Bill Spitzak and others.
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

#ifndef fl_ask_H
#  define fl_ask_H

#  include "Enumerations.H"

#include "../FL3/ask.h"

#define FL_BEEP_DEFAULT       fltk::BEEP_DEFAULT
#define FL_BEEP_MESSAGE       fltk::BEEP_MESSAGE
#define FL_BEEP_ERROR         fltk::BEEP_ERROR
#define FL_BEEP_QUESTION      fltk::BEEP_QESTION
#define FL_BEEP_PASSWORD      fltk::BEEP_PASSWORD
#define FL_BEEP_NOTIFICATION  fltk::BEEP_NOTIFICATION

#define fl_beep fltk::beep
#define fl_message fltk::message
#define fl_alert fltk::alert
#define fl_ask fltk::ask
#define fl_choice fltk::choice
#define fl_input fltk::input
#define fl_password fltk::password

#define fl_message_icon fltk::message_icon
#define fl_message_font fltk::message_font

#define fl_no fltk::no
#define fl_yes fltk::yes
#define fl_ok fltk::ok
#define fl_cancel fltk::cancel
#define fl_close fltk::close

#endif // !fl_ask_H

//
// End of "$Id$".
//
