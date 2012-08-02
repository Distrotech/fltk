//
// "$Id$"
//
// Widget panel for the Fast Light Tool Kit (FLTK).
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

// generated by Fast Light User Interface Designer (fluid) version 3.0000

#ifndef widget_panel_h
#define widget_panel_h
#include <fltk3/run.h>
/**
   Needed for Fl_Panel base class
*/
#include "Fl_Widget_Type.h"
#include "panel.h"
#include <fltk3/TabGroup.h>
#include <fltk3/Group.h>
#include <fltk3/Input.h>
extern void label_cb(fltk3::Input*, void*);
#include <fltk3/Choice.h>
extern fltk3::MenuItem labeltypemenu[];
extern void labeltype_cb(fltk3::Choice*, void*);
extern void image_cb(fltk3::Input*, void*);
#include <fltk3/Button.h>
extern void image_browse_cb(fltk3::Button*, void*);
extern void inactive_cb(fltk3::Input*, void*);
extern void inactive_browse_cb(fltk3::Button*, void*);
extern void align_cb(fltk3::Button*, void*);
extern void align_text_image_cb(fltk3::Choice*, void*);
extern void align_position_cb(fltk3::Choice*, void*);
#include <fltk3/Widget.h>
#include <fltk3/ValueInput.h>
extern void x_cb(fltk3::ValueInput*, void*);
extern fltk3::ValueInput *widget_x_input;
extern void y_cb(fltk3::ValueInput*, void*);
extern fltk3::ValueInput *widget_y_input;
extern void w_cb(fltk3::ValueInput*, void*);
extern fltk3::ValueInput *widget_w_input;
extern void h_cb(fltk3::ValueInput*, void*);
extern fltk3::ValueInput *widget_h_input;
#include <fltk3/LightButton.h>
extern void wc_relative_cb(fltk3::LightButton*, void*);
extern void slider_size_cb(fltk3::ValueInput*, void*);
extern void min_cb(fltk3::ValueInput*, void*);
extern void max_cb(fltk3::ValueInput*, void*);
extern void step_cb(fltk3::ValueInput*, void*);
extern void value_cb(fltk3::ValueInput*, void*);
extern void min_w_cb(fltk3::ValueInput*, void*);
extern void min_h_cb(fltk3::ValueInput*, void*);
extern void set_min_size_cb(fltk3::Button*, void*);
extern void max_w_cb(fltk3::ValueInput*, void*);
extern void max_h_cb(fltk3::ValueInput*, void*);
extern void set_max_size_cb(fltk3::Button*, void*);
#include "Shortcut_Button.h"
extern void shortcut_in_cb(Shortcut_Button*, void*);
extern void xclass_cb(fltk3::Input*, void*);
extern void border_cb(fltk3::LightButton*, void*);
extern void modal_cb(fltk3::LightButton*, void*);
extern void non_modal_cb(fltk3::LightButton*, void*);
extern void visible_cb(fltk3::LightButton*, void*);
extern void active_cb(fltk3::LightButton*, void*);
extern void resizable_cb(fltk3::LightButton*, void*);
extern void hotspot_cb(fltk3::LightButton*, void*);
extern void tooltip_cb(fltk3::Input*, void*);
extern fltk3::MenuItem fontmenu[];
extern void labelfont_cb(fltk3::Choice*, void*);
extern void labelsize_cb(fltk3::ValueInput*, void*);
extern void labelcolor_cb(fltk3::Button*, void*);
extern fltk3::MenuItem boxmenu[];
extern void box_cb(fltk3::Choice*, void*);
extern void color_cb(fltk3::Button*, void*);
extern void down_box_cb(fltk3::Choice*, void*);
extern void color2_cb(fltk3::Button*, void*);
extern void textfont_cb(fltk3::Choice*, void*);
extern void textsize_cb(fltk3::ValueInput*, void*);
extern void textcolor_cb(fltk3::Button*, void*);
extern void subclass_cb(fltk3::Input*, void*);
extern void subtype_cb(fltk3::Choice*, void*);
extern void name_cb(fltk3::Input*, void*);
extern void name_public_member_cb(fltk3::Choice*, void*);
extern void name_public_cb(fltk3::Choice*, void*);
extern void v_input_cb(fltk3::Input*, void*);
extern fltk3::Input *v_input[4];
#include "CodeEditor.h"
extern void callback_cb(CodeEditor*, void*);
extern void user_data_cb(fltk3::Input*, void*);
extern fltk3::MenuItem whenmenu[];
extern void when_cb(fltk3::Choice*, void*);
extern void user_data_type_cb(fltk3::Input*, void*);
extern void when_button_cb(fltk3::LightButton*, void*);
extern void overlay_cb(fltk3::Button*, void*);
extern void revert_cb(fltk3::Button*, void*);
#include <fltk3/ReturnButton.h>
extern void ok_cb(fltk3::ReturnButton*, void*);
extern void cancel_cb(fltk3::Button*, void*);
extern void live_mode_cb(fltk3::Button*, void*);
extern fltk3::Button *wLiveMode;
Fl_Panel* make_widget_panel();
extern fltk3::MenuItem menu_[];
extern fltk3::MenuItem menu_1[];
extern fltk3::MenuItem menu_2[];
extern fltk3::MenuItem menu_3[];
#endif

//
// End of "$Id$".
//
