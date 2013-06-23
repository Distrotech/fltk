//
// "$Id$"
//
// Print panel for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2010 by Bill Spitzak and others.
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

//
// This is a temporary file.  It is only for development and will
// probably be removed later.
//

#ifndef print_panel_h
#define print_panel_h
#include <fltk3/run.h>
#include <fltk3/DoubleWindow.h>
#include <fltk3/Group.h>
#include <fltk3/Choice.h>
#include <fltk3/Button.h>
#include <fltk3/Box.h>
#include <fltk3/RoundButton.h>
#include <fltk3/Input.h>
#include <fltk3/Spinner.h>
#include <fltk3/CheckButton.h>
#include <fltk3/ReturnButton.h>
#include <fltk3/Progress.h>
#include <fltk3/IntInput.h>
#include <fltk3/Preferences.h>

fltk3::DoubleWindow* make_print_panel();
static void print_cb(fltk3::ReturnButton *, void *); 
void print_load();
static void print_update_status();

extern fltk3::Preferences print_prefs;
extern fltk3::DoubleWindow *print_panel;
extern fltk3::Group *print_panel_controls;
extern fltk3::Choice *print_choice;
extern fltk3::Button *print_properties;
extern fltk3::Widget *print_status;
extern fltk3::RoundButton *print_all;
extern fltk3::RoundButton *print_pages;
extern fltk3::RoundButton *print_selection;
extern fltk3::CheckButton *print_collate_button;
extern fltk3::Group *print_collate_group[2];
extern fltk3::Progress *print_progress;
extern fltk3::DoubleWindow *print_properties_panel;
extern fltk3::Choice *print_page_size;
extern fltk3::IntInput *print_from;
extern fltk3::IntInput *print_to;
extern fltk3::Spinner *print_copies;
extern fltk3::Button *print_output_mode[4];
extern int print_start;

#endif

//
// End of "$Id$".
//
