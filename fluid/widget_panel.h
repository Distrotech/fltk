// generated by Fast Light User Interface Designer (fluid) version 2.00

#ifndef widget_panel_h
#define widget_panel_h
#include "Shortcut_Button.h"
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Window.H>
extern Fl_Menu_Item boxmenu[];
extern Fl_Menu_Item fontmenu[];
extern Fl_Menu_Item labeltypemenu[];
extern Fl_Menu_Item whenmenu[];
extern void active_cb(Fl_Light_Button*, void*);
extern void align_cb(Fl_Button*, void*);
extern void border_cb(Fl_Light_Button*, void*);
extern void box_cb(Fl_Choice*, void*);
extern void callback_cb(Fl_Input*, void*);
extern void cancel_cb(Fl_Button*, void*);
extern void color2_cb(Fl_Light_Button*, void*);
extern void color3_cb(Fl_Light_Button*, void*);
extern void color_cb(Fl_Light_Button*, void*);
extern void default_cb(Fl_Button*, void*);
extern void down_box_cb(Fl_Choice*, void*);
extern void down_labelcolor_cb(Fl_Light_Button*, void*);
extern void highlight_box_cb(Fl_Choice*, void*);
extern void highlightcolor_cb(Fl_Light_Button*, void*);
extern void hotspot_cb(Fl_Light_Button*, void*);
extern void label_cb(Fl_Input*, void*);
extern void labelcolor_cb(Fl_Light_Button*, void*);
extern void labelfont_cb(Fl_Choice*, void*);
extern void labelsize_cb(Fl_Value_Input*, void*);
extern void labeltype_cb(Fl_Choice*, void*);
extern void max_cb(Fl_Value_Input*, void*);
extern void min_cb(Fl_Value_Input*, void*);
extern void modal_cb(Fl_Light_Button*, void*);
extern void name_cb(Fl_Input*, void*);
extern void name_public_cb(Fl_Light_Button*, void*);
extern void non_modal_cb(Fl_Light_Button*, void*);
extern void ok_cb(Fl_Return_Button*, void*);
extern void overlay_cb(Fl_Button*, void*);
extern void propagate_load(Fl_Group*, void*);
extern void resizable_cb(Fl_Light_Button*, void*);
extern void selected_textcolor_cb(Fl_Light_Button*, void*);
extern void shortcut_in_cb(Shortcut_Button*, void*);
extern void slider_size_cb(Fl_Value_Input*, void*);
extern void step_cb(Fl_Value_Input*, void*);
extern void style_cb(Fl_Button*, void*);
extern void style_ok_cb(Fl_Return_Button*, void*);
extern void subclass_cb(Fl_Input*, void*);
extern void subtype_cb(Fl_Choice*, void*);
extern void textcolor_cb(Fl_Light_Button*, void*);
extern void textfont_cb(Fl_Choice*, void*);
extern void textsize_cb(Fl_Value_Input*, void*);
extern void tooltip_cb(Fl_Input*, void*);
extern void user_data_cb(Fl_Input*, void*);
extern void user_data_type_cb(Fl_Input*, void*);
extern void v_input_cb(Fl_Input*, void*);
extern void value_cb(Fl_Value_Input*, void*);
extern void visible_cb(Fl_Light_Button*, void*);
extern void when_button_cb(Fl_Light_Button*, void*);
extern void when_cb(Fl_Choice*, void*);
extern void xclass_cb(Fl_Input*, void*);
extern Fl_Input *v_input[4];
extern Fl_Box *callback_label;
Fl_Window* make_widget_panel();
extern Fl_Input *v_input[4];
extern Fl_Box *callback_label;
Fl_Window* make_style_panel();
#endif
