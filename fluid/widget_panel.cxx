// generated by Fast Light User Interface Designer (fluid) version 2.0000

#include "widget_panel.h"

Fl_Tabs *panel_tabs=(Fl_Tabs *)0;

Fl_Box *image_label=(Fl_Box *)0;

Fl_Light_Button *include_image_button=(Fl_Light_Button *)0;

Fl_Input *v_input[4]={(Fl_Input *)0};

Fl_Box *callback_label=(Fl_Box *)0;

Fl_Light_Button *overlaybutton=(Fl_Light_Button *)0;

Fl_Window* make_widget_panel() {
  Fl_Window* w;
  { Fl_Window* o = new Fl_Window(380, 375);
    w = o;
    ((Fl_Window*)(o))->hotspot(o);
    { Fl_Tabs* o = panel_tabs = new Fl_Tabs(10, 10, 360, 320);
      o->callback((Fl_Callback*)propagate_tabs);
      { Fl_Group* o = new Fl_Group(10, 35, 360, 295, "GUI");
        o->callback((Fl_Callback*)propagate_group);
        o->hide();
        { Fl_Input* o = new Fl_Input(90, 45, 270, 20, "Label:");
          o->callback((Fl_Callback*)label_cb);
          o->when(FL_WHEN_CHANGED);
          o->tooltip("Text displayed on or next to the widget");
        }
        { Fl_Box* o = image_label = new Fl_Box(19, 70, 71, 20, "Image:");
		  o->clear_flag(FL_ALIGN_MASK);
          o->set_flag(FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
        }
        { Fl_Button* o = new Fl_Button(90, 70, 180, 20, "Image name");
          o->box(FL_THIN_DOWN_BOX);
          o->color((Fl_Color)55);
          o->callback((Fl_Callback*)image_cb);
		  o->clear_flag(FL_ALIGN_MASK);
          o->set_flag(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
          o->tooltip("Select an image to label the widget");
        }
        { Fl_Light_Button* o = include_image_button = new Fl_Light_Button(270, 70, 90, 20, "image inlined");
          o->label_size(10);
          o->callback((Fl_Callback*)image_inlined_cb);
          o->set_flag(132|FL_ALIGN_INSIDE);
          o->tooltip("Include the datas of the image inlined in \nthe code or keep it in an externa\
l file");
        }
        { Fl_Box* o = new Fl_Box(20, 100, 70, 20, "Alignment:");
          o->clear_flag(FL_ALIGN_MASK);
          o->set_flag(FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
        }
        { Fl_Button* o = new Fl_Button(90, 100, 45, 20, "tiled");
          o->type(1);
          o->callback((Fl_Callback*)align_cb, (void*)(FL_ALIGN_TILED));
          o->tooltip("Draw the image tiled");
        }
        { Fl_Button* o = new Fl_Button(135, 100, 45, 20, "clip");
          o->type(1);
          o->callback((Fl_Callback*)align_cb, (void*)(FL_ALIGN_CLIP));
          o->tooltip("Turn on clipping to the widget\'s area when drawing\nlabel.  This is slower s\
o it should be left off if label will fit");
        }
        { Fl_Button* o = new Fl_Button(180, 100, 45, 20, "wrap");
          o->type(1);
          o->callback((Fl_Callback*)align_cb, (void*)(FL_ALIGN_WRAP));
          o->tooltip("Word-wrap the label");
        }
        { Fl_Button* o = new Fl_Button(260, 100, 20, 20, "@-1<-");
          o->type(1);
          o->label_type(FL_SYMBOL_LABEL);
          o->callback((Fl_Callback*)align_cb, (void*)(FL_ALIGN_LEFT));
          o->tooltip("Places label on the left of the widget");
        }
        { Fl_Button* o = new Fl_Button(280, 100, 20, 20, "@-1->");
          o->type(1);
          o->label_type(FL_SYMBOL_LABEL);
          o->callback((Fl_Callback*)align_cb, (void*)(FL_ALIGN_RIGHT));
          o->tooltip("Places label on the right of the widget");
        }
        { Fl_Button* o = new Fl_Button(300, 100, 20, 20, "@-18");
          o->type(1);
          o->label_type(FL_SYMBOL_LABEL);
          o->callback((Fl_Callback*)align_cb, (void*)(FL_ALIGN_TOP));
          o->tooltip("Places label on the top of the widget");
        }
        { Fl_Button* o = new Fl_Button(320, 100, 20, 20, "@-12");
          o->type(1);
          o->label_type(FL_SYMBOL_LABEL);
          o->callback((Fl_Callback*)align_cb, (void*)(FL_ALIGN_BOTTOM));
          o->tooltip("Places label on the bottom of the widget");
        }
        { Fl_Button* o = new Fl_Button(340, 100, 20, 20, "@-3square");
          o->type(1);
          o->label_type(FL_SYMBOL_LABEL);
          o->callback((Fl_Callback*)align_cb, (void*)(FL_ALIGN_INSIDE));
          o->tooltip("Places label inside the widget");
        }
        { Fl_Input* o = new Fl_Input(90, 130, 90, 20, "X Class:");
          o->callback((Fl_Callback*)xclass_cb);
          o->when(FL_WHEN_CHANGED);
          o->tooltip("The X class name which should be used for this widget.  This can be used to c\
hoose icons.");
        }
        { Fl_Light_Button* o = new Fl_Light_Button(180, 130, 55, 20, "Border");
          o->label_size(10);
          o->callback((Fl_Callback*)border_cb);
          o->tooltip("Enable the window manager border");
        }
        { Fl_Light_Button* o = new Fl_Light_Button(235, 130, 55, 20, "Modal");
          o->label_size(10);
          o->callback((Fl_Callback*)modal_cb);
          o->tooltip("This window will stay on top of others in the\napplication and will prevent e\
vents from going to other windows.");
        }
        { Fl_Light_Button* o = new Fl_Light_Button(290, 130, 70, 20, "Nonmodal");
          o->label_size(10);
          o->callback((Fl_Callback*)non_modal_cb);
          o->tooltip("This window will stay on top of others in the application.");
        }
        { Fl_Value_Input* o = new Fl_Value_Input(90, 135, 55, 20, "Value:");
          o->label_size(10);
          o->callback((Fl_Callback*)value_cb);
		  o->clear_flag(FL_ALIGN_MASK);
          o->set_flag(FL_ALIGN_TOP | FL_ALIGN_LEFT);
          o->hide();
          o->tooltip("The initial value (integer) of this widget");
        }
        { Fl_Value_Input* o = new Fl_Value_Input(145, 135, 55, 20, "Minimum:");
          o->label_size(10);
          o->callback((Fl_Callback*)min_cb);
		  o->clear_flag(FL_ALIGN_MASK);
          o->set_flag(FL_ALIGN_TOP | FL_ALIGN_LEFT);
          o->hide();
          o->tooltip("The minimum value for this valuator");
        }
        { Fl_Value_Input* o = new Fl_Value_Input(200, 135, 55, 20, "Maximum:");
          o->label_size(10);
          o->value(1);
          o->callback((Fl_Callback*)max_cb);
		  o->clear_flag(FL_ALIGN_MASK);
          o->set_flag(FL_ALIGN_TOP | FL_ALIGN_LEFT);
          o->hide();
          o->tooltip("The maximum value for this valuator");
        }
        { Fl_Value_Input* o = new Fl_Value_Input(255, 135, 55, 20, "Size:");
          o->label_size(10);
          o->callback((Fl_Callback*)slider_size_cb);
		  o->clear_flag(FL_ALIGN_MASK);
          o->set_flag(FL_ALIGN_TOP | FL_ALIGN_LEFT);
          o->hide();
          o->tooltip("The size of the scroller");
        }
        { Fl_Value_Input* o = new Fl_Value_Input(310, 135, 50, 20, "Step:");
          o->label_size(10);
          o->callback((Fl_Callback*)step_cb);
		  o->clear_flag(FL_ALIGN_MASK);
          o->set_flag(FL_ALIGN_TOP | FL_ALIGN_LEFT);
          o->hide();
          o->tooltip("Amount to change this valuator when mouse moves 1 pixel");
        }
        { Fl_Group* o = new Fl_Group(90, 155, 270, 25, "Attributes:");
          o->callback((Fl_Callback*)propagate_group);
		  o->clear_flag(FL_ALIGN_MASK);
          o->set_flag(FL_ALIGN_TOP | FL_ALIGN_LEFT);
          { Fl_Light_Button* o = new Fl_Light_Button(90, 160, 70, 20, "Visible");
            o->label_size(10);
            o->callback((Fl_Callback*)visible_cb);
            o->tooltip("Determines whether the widget is initially visible");
          }
          { Fl_Light_Button* o = new Fl_Light_Button(160, 160, 65, 20, "Active");
            o->label_size(10);
            o->callback((Fl_Callback*)active_cb);
            o->tooltip("Determines whether the widget is initially active (enabled)");
          }
          { Fl_Light_Button* o = new Fl_Light_Button(225, 160, 70, 20, "Resizable");
            o->label_size(10);
            o->callback((Fl_Callback*)resizable_cb);
            o->when(FL_WHEN_CHANGED);
            o->tooltip("If on, this widget and all it\'s parents are resizable.  When the parent resi\
zes it moves/resizes all it\'s children so that this widget\'s edges remain th\
e same distance from all four sides of the parent.  If this is off this widget\
 will not resize, unless it overlaps a resizable sibling.");
          }
          { Fl_Light_Button* o = new Fl_Light_Button(295, 160, 65, 20, "Hotspot");
            o->label_size(10);
            o->callback((Fl_Callback*)hotspot_cb);
            o->when(FL_WHEN_CHANGED);
            o->tooltip("Positions the window so this widget is under the mouse.  This is done when sh\
ow() is called.");
          }
          o->end();
        }
        { Shortcut_Button* o = new Shortcut_Button(90, 185, 270, 20, "Shortcut:");
          o->box(FL_THIN_DOWN_BOX);
          o->color((Fl_Color)7);
          o->selection_color((Fl_Color)7);
          o->callback((Fl_Callback*)shortcut_in_cb);
		  o->clear_flag(FL_ALIGN_MASK);
          o->set_flag(FL_ALIGN_LEFT);
          o->tooltip("To set a shortcut click here, then type the key combination you want.  To del\
ete the shortcut type backspace.  To stop setting the shortcut click the mouse\
 on some other field.");
        }
        { Fl_Input* o = new Fl_Input(90, 210, 270, 110, "Tooltip:");
          o->type(4);
          o->callback((Fl_Callback*)tooltip_cb);
          o->tooltip("The pop up tooltip which should be used for the widget.");
        }
        { Fl_Box* o = new Fl_Box(90, 210, 270, 110, "resizable");
          o->hide();
          o->deactivate();
          Fl_Group::current()->resizable(o);
        }
        o->end();
        Fl_Group::current()->resizable(o);
      }
      { Fl_Group* o = new Fl_Group(10, 35, 360, 295, "Style");
        o->callback((Fl_Callback*)propagate_group);
        o->hide();
        { Fl_Choice* o = new Fl_Choice(95, 45, 260, 25, "Box:");
          o->callback((Fl_Callback*)box_cb);
          o->tooltip("Type of box to draw around the widget");
          o->menu(boxmenu);
        }
        { Fl_Choice* o = new Fl_Choice(95, 70, 260, 25, "Glyph Box:");
          o->callback((Fl_Callback*)glyph_box_cb);
          o->tooltip("Type of box to draw around the glyph on the widget");
          o->menu(boxmenu);
        }
        { Fl_Choice* o = new Fl_Choice(95, 95, 260, 25, "Label Type:");
          o->callback((Fl_Callback*)labeltype_cb);
          o->tooltip("How to draw the label");
          o->menu(labeltypemenu);
        }
        { Fl_Choice* o = new Fl_Choice(95, 120, 215, 25, "Label Font:");
          o->callback((Fl_Callback*)labelfont_cb);
          o->tooltip("Font to use for the label");
          o->menu(fontmenu);
        }
        { Fl_Value_Input* o = new Fl_Value_Input(310, 120, 46, 25);
          o->maximum(100);
          o->step(1);
          o->value(14);
          o->callback((Fl_Callback*)labelsize_cb);
          o->tooltip("Size of the font to use for the label");
        }
        { Fl_Choice* o = new Fl_Choice(95, 145, 215, 25, "Text Font:");
          o->callback((Fl_Callback*)textfont_cb);
          o->tooltip("Font to use for text displayed inside the widget");
          o->menu(fontmenu);
        }
        { Fl_Value_Input* o = new Fl_Value_Input(310, 145, 46, 25);
          o->maximum(100);
          o->step(1);
          o->value(14);
          o->callback((Fl_Callback*)textsize_cb);
          o->tooltip("Size of the font to use for text displayed inside the widget");
        }
        { Fl_Light_Button* o = new Fl_Light_Button(95, 180, 130, 25, "Color");
          o->label_size(10);
          o->callback((Fl_Callback*)color_cb);
          o->tooltip("The background color of the widget");
          o->type(0);
        }
        { Fl_Light_Button* o = new Fl_Light_Button(225, 180, 130, 25, "Label Color");
          o->label_size(10);
          o->callback((Fl_Callback*)labelcolor_cb);
          o->tooltip("Color to draw the label");
          o->type(0);
        }
        { Fl_Light_Button* o = new Fl_Light_Button(95, 205, 130, 25, "Highlight Color");
          o->label_size(10);
          o->callback((Fl_Callback*)highlightcolor_cb);
          o->tooltip("Color to use to draw the widget highlighted.  The black color in the upper-le\
ft of the color chooser disables highlighting");
          o->type(0);
        }
        { Fl_Light_Button* o = new Fl_Light_Button(225, 205, 130, 25, "Highlight Label Color");
          o->label_size(10);
          o->callback((Fl_Callback*)highlight_label_color_cb);
          o->tooltip("Color to draw the label when the widget is highlighted");
          o->type(0);
        }
        { Fl_Box* o = new Fl_Box(30, 220, 65, 20, "Colors:");
		  o->clear_flag(FL_ALIGN_MASK);
          o->set_flag(FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
        }
        { Fl_Light_Button* o = new Fl_Light_Button(95, 230, 130, 25, "Selection Color");
          o->label_size(10);
          o->callback((Fl_Callback*)color2_cb);
          o->tooltip("Color to draw selected portions (usage varies)");
          o->type(0);
        }
        { Fl_Light_Button* o = new Fl_Light_Button(225, 230, 130, 25, "Selected Text Color");
          o->label_size(10);
          o->callback((Fl_Callback*)selected_textcolor_cb);
          o->tooltip("Color to draw selected text inside the widget");
          o->type(0);
        }
        { Fl_Box* o = new Fl_Box(30, 235, 290, 30, "resizable");
          o->hide();
          o->deactivate();
          Fl_Group::current()->resizable(o);
        }
        { Fl_Light_Button* o = new Fl_Light_Button(95, 255, 130, 25, "Off Color");
          o->label_size(10);
          o->callback((Fl_Callback*)color3_cb);
          o->tooltip("Color to draw checkmarks when off");
          o->type(0);
        }
        { Fl_Light_Button* o = new Fl_Light_Button(225, 255, 130, 25, "Text Color");
          o->label_size(10);
          o->callback((Fl_Callback*)textcolor_cb);
          o->tooltip("Color to draw text displayed inside the widget");
          o->type(0);
        }
        { Fl_Button* o = new Fl_Button(95, 295, 130, 25, "Use Default Style");
          o->callback((Fl_Callback*)default_cb);
          o->tooltip("Resets the style to this widget\'s default values");
        }
        o->end();
      }
      { Fl_Group* o = new Fl_Group(10, 35, 360, 295, "C++");
        o->callback((Fl_Callback*)propagate_group);
        o->hide();
        { Fl_Input* o = new Fl_Input(90, 45, 175, 20, "Class:");
          o->callback((Fl_Callback*)subclass_cb, (void*)(4));
          o->when(FL_WHEN_CHANGED);
          o->tooltip("This allows you to name a user-defined class that this widget is an instance \
of, rather than an fltk built-in class. You will need to add a #include declar\
ation so that the definition of your class is included in the fluid output.");
        }
        { Fl_Choice* o = new Fl_Choice(265, 45, 95, 20);
          o->callback((Fl_Callback*)subtype_cb);
          o->tooltip("Selects a value for type() for this widget");
        }
        { Fl_Input* o = new Fl_Input(90, 70, 217, 20, "Name:");
          o->callback((Fl_Callback*)name_cb);
          o->when(FL_WHEN_CHANGED);
          o->tooltip("The variable or member name in which to store a pointer to this widget.");
        }
        { Fl_Light_Button* o = new Fl_Light_Button(307, 70, 53, 20, "public");
          o->label_size(10);
          o->callback((Fl_Callback*)name_public_cb);
          o->when(FL_WHEN_CHANGED);
          o->tooltip("Make the variable public");
        }
        { Fl_Input* o = v_input[0] = new Fl_Input(90, 95, 270, 20, "Extra Code:");
          o->callback((Fl_Callback*)v_input_cb, (void*)(0));
          o->tooltip("Extra code to be exectuted when the widget is created");
        }
        { Fl_Input* o = v_input[1] = new Fl_Input(90, 115, 270, 20);
          o->callback((Fl_Callback*)v_input_cb, (void*)(1));
          o->tooltip("Extra code to be exectuted when the widget is created");
        }
        { Fl_Input* o = v_input[2] = new Fl_Input(90, 135, 270, 20);
          o->callback((Fl_Callback*)v_input_cb, (void*)(2));
          o->tooltip("Extra code to be exectuted when the widget is created");
        }
        { Fl_Input* o = v_input[3] = new Fl_Input(90, 155, 270, 20);
          o->callback((Fl_Callback*)v_input_cb, (void*)(3));
          o->tooltip("Extra code to be exectuted when the widget is created");
        }
        { Fl_Box* o = callback_label = new Fl_Box(20, 180, 70, 20, "Callback:");
  		  o->clear_flag(FL_ALIGN_MASK);
          o->set_flag(FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
        }
        { Fl_Input* o = new Fl_Input(90, 180, 270, 95);
          o->type(4);
          o->callback((Fl_Callback*)callback_cb);
          o->tooltip("The name of the callback function, or code body of the callback function");
        }
        { Fl_Box* o = new Fl_Box(90, 200, 175, 65, "resizable");
          o->hide();
          o->deactivate();
          Fl_Group::current()->resizable(o);
        }
        { Fl_Input* o = new Fl_Input(90, 280, 137, 20, "User Data:");
          o->callback((Fl_Callback*)user_data_cb);
          o->tooltip("Value passed as the second argument to the callback.  This must be of the typ\
e given below.");
        }
        { Fl_Choice* o = new Fl_Choice(265, 280, 95, 20, "When:");
          o->label_size(10);
          o->callback((Fl_Callback*)when_cb);
          o->when(FL_WHEN_NEVER);
          o->tooltip("What actions cause the callback to be called.");
          o->menu(whenmenu);
        }
        { Fl_Input* o = new Fl_Input(90, 300, 137, 20, "Type:");
          o->callback((Fl_Callback*)user_data_type_cb);
          o->tooltip("Type of the user data (must \\\"long\\\" or a pointer type)");
        }
        { Fl_Light_Button* o = new Fl_Light_Button(265, 300, 95, 20, "no change");
          o->label_size(10);
          o->callback((Fl_Callback*)when_button_cb);
          o->when(FL_WHEN_NEVER);
          o->tooltip("Further modifies When so that the callback is done even if the widget\'s valu\
e has not changed.");
        }
        o->end();
      }
      o->end();
      Fl_Group::current()->resizable(o);
    }
    { Fl_Group* o = new Fl_Group(95, 340, 275, 25);
      { Fl_Light_Button* o = overlaybutton = new Fl_Light_Button(95, 340, 90, 25, "&Overlays");
        o->callback((Fl_Callback*)overlay_cb);
        o->tooltip("Turns overlays (red outlines)  of the selected  widgets on or off");
        o->value(!overlays_invisible);
      }
      { Fl_Return_Button* o = new Fl_Return_Button(225, 340, 65, 25, "OK");
        o->callback((Fl_Callback*)ok_cb);
        o->tooltip("Closes this attribute window");
      }
      { Fl_Button* o = new Fl_Button(300, 340, 70, 25, "Cancel");
        o->callback((Fl_Callback*)cancel_cb);
      }
      o->end();
    }
    o->end();
  }
  return w;
}
