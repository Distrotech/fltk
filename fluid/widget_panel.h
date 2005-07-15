// generated by Fast Light User Interface Designer (fluid) version 2.0100

#ifndef widget_panel_h
#define widget_panel_h
#include <fltk/Window.h>
#include <fltk/TabGroup.h>
extern void propagate_tabs(fltk::TabGroup*, void*);
extern fltk::TabGroup* panel_tabs;
#include <fltk/Group.h>
extern void propagate_group(fltk::Group*, void*);
#include <fltk/Input.h>
extern void user_class_cb(fltk::Input*, void*);
#include <fltk/Choice.h>
extern void subtype_cb(fltk::Choice*, void*);
extern void label_cb(fltk::Input*, void*);
#include <fltk/Widget.h>
extern fltk::Widget* image_label;
#include <fltk/Button.h>
extern void image_cb(fltk::Button*, void*);
#include <fltk/CheckButton.h>
extern void image_inlined_cb(fltk::CheckButton*, void*);
extern fltk::CheckButton* include_image_button;
extern void align_cb(fltk::Button*, void*);
#include <fltk/ValueInput.h>
extern void x_cb(fltk::ValueInput*, void*);
extern fltk::ValueInput* widget_x;
extern void y_cb(fltk::ValueInput*, void*);
extern fltk::ValueInput* widget_y;
extern void width_cb(fltk::ValueInput*, void*);
extern fltk::ValueInput* widget_width;
extern void height_cb(fltk::ValueInput*, void*);
extern fltk::ValueInput* widget_height;
extern void set_xy_cb(fltk::CheckButton*, void*);
extern fltk::CheckButton* set_xy;
extern void slider_size_cb(fltk::ValueInput*, void*);
extern void border_cb(fltk::CheckButton*, void*);
extern void modal_cb(fltk::CheckButton*, void*);
extern void non_modal_cb(fltk::CheckButton*, void*);
extern void value_cb(fltk::ValueInput*, void*);
extern void min_cb(fltk::ValueInput*, void*);
extern void max_cb(fltk::ValueInput*, void*);
extern void step_cb(fltk::ValueInput*, void*);
extern void line_cb(fltk::ValueInput*, void*);
extern void visible_cb(fltk::CheckButton*, void*);
extern void active_cb(fltk::CheckButton*, void*);
extern void resizable_cb(fltk::CheckButton*, void*);
extern void hotspot_cb(fltk::CheckButton*, void*);
#include "Shortcut_Button.h"
extern void shortcut_in_cb(Shortcut_Button*, void*);
#include <fltk/WordwrapInput.h>
extern void tooltip_cb(fltk::WordwrapInput*, void*);
extern void box_cb(fltk::Choice*, void*);
#include <fltk/LightButton.h>
extern void color_cb(fltk::LightButton*, void*);
extern void text_color_cb(fltk::LightButton*, void*);
extern void selection_color_cb(fltk::LightButton*, void*);
extern void selected_text_color_cb(fltk::LightButton*, void*);
extern void button_box_cb(fltk::Choice*, void*);
extern void button_color_cb(fltk::LightButton*, void*);
extern void label_color_cb(fltk::LightButton*, void*);
extern void highlight_color_cb(fltk::LightButton*, void*);
extern void highlight_label_color_cb(fltk::LightButton*, void*);
extern void label_style_cb(fltk::Choice*, void*);
extern void label_font_cb(fltk::Choice*, void*);
extern void label_size_cb(fltk::ValueInput*, void*);
extern void text_font_cb(fltk::Choice*, void*);
extern void text_size_cb(fltk::ValueInput*, void*);
extern void default_cb(fltk::Button*, void*);
extern void name_cb(fltk::Input*, void*);
extern void name_public_cb(fltk::CheckButton*, void*);
#include <fltk/MultiLineInput.h>
extern void extra_code_input_cb(fltk::MultiLineInput*, void*);
extern fltk::MultiLineInput* extra_code_input;
extern void callback_cb(fltk::MultiLineInput*, void*);
extern void user_data_cb(fltk::Input*, void*);
extern void when_cb(fltk::Choice*, void*);
extern void user_data_type_cb(fltk::Input*, void*);
extern bool overlays_invisible;
extern void overlay_cb(fltk::CheckButton*, void*);
extern fltk::CheckButton* overlaybutton;
#include <fltk/ReturnButton.h>
extern void ok_cb(fltk::ReturnButton*, void*);
extern void cancel_cb(fltk::Button*, void*);
fltk::Window* make_widget_panel();
#endif
