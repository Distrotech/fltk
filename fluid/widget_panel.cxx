// generated by Fast Light User Interface Designer (fluid) version 2.00

#include "widget_panel.h"

Fl_Tabs *panel_tabs=(Fl_Tabs *)0;

Fl_Box *image_label=(Fl_Box *)0;

Fl_Light_Button *include_image_button=(Fl_Light_Button *)0;

Fl_Input *v_input[4]={(Fl_Input *)0};

Fl_Box *callback_label=(Fl_Box *)0;

Fl_Light_Button *overlaybutton=(Fl_Light_Button *)0;

Fl_Window* make_widget_panel() {
  Fl_Window* w;
  { Fl_Window* o = new Fl_Window(360, 335);
    w = o;
    w->hotspot(o);
    { Fl_Tabs* o = panel_tabs = new Fl_Tabs(0, 0, 358, 320);
      o->callback((Fl_Callback*)propagate_tabs);
      { Fl_Group* o = new Fl_Group(0, 0, 358, 295, "GUI");
        o->callback((Fl_Callback*)propagate_group);
        { Fl_Input* o = new Fl_Input(80, 10, 270, 20, "Label:");
          o->callback((Fl_Callback*)label_cb);
          o->when(FL_WHEN_CHANGED);
          o->tooltip("Text displayed on or next to the widget");
        }
        { Fl_Button* o = new Fl_Button(145, 60, 50, 20, "clip");
          o->type(1);
          o->box(FL_THIN_UP_BOX);
          o->label_size(12);
          o->callback((Fl_Callback*)align_cb, (void*)(FL_ALIGN_CLIP));
          o->tooltip("Turn on clipping to the widget's area when drawing
label.  This is slower so it should be left off if label will fit");
        }
        { Fl_Button* o = new Fl_Button(195, 60, 50, 20, "wrap");
          o->type(1);
          o->box(FL_THIN_UP_BOX);
          o->label_size(12);
          o->callback((Fl_Callback*)align_cb, (void*)(FL_ALIGN_WRAP));
          o->tooltip("Word-wrap the label");
        }
        { Fl_Button* o = new Fl_Button(250, 60, 20, 20, "@-1<-");
          o->type(1);
          o->box(FL_THIN_UP_BOX);
          o->label_type(FL_SYMBOL_LABEL);
          o->callback((Fl_Callback*)align_cb, (void*)(FL_ALIGN_LEFT));
          o->tooltip("Places label on the left of the widget");
        }
        { Fl_Button* o = new Fl_Button(270, 60, 20, 20, "@-1->");
          o->type(1);
          o->box(FL_THIN_UP_BOX);
          o->label_type(FL_SYMBOL_LABEL);
          o->callback((Fl_Callback*)align_cb, (void*)(FL_ALIGN_RIGHT));
          o->tooltip("Places label on the right of the widget");
        }
        { Fl_Button* o = new Fl_Button(290, 60, 20, 20, "@-18");
          o->type(1);
          o->box(FL_THIN_UP_BOX);
          o->label_type(FL_SYMBOL_LABEL);
          o->callback((Fl_Callback*)align_cb, (void*)(FL_ALIGN_TOP));
          o->tooltip("Places label on the top of the widget");
        }
        { Fl_Button* o = new Fl_Button(310, 60, 20, 20, "@-12");
          o->type(1);
          o->box(FL_THIN_UP_BOX);
          o->label_type(FL_SYMBOL_LABEL);
          o->callback((Fl_Callback*)align_cb, (void*)(FL_ALIGN_BOTTOM));
          o->tooltip("Places label on the bottom of the widget");
        }
        { Fl_Button* o = new Fl_Button(330, 60, 20, 20, "@-3square");
          o->type(1);
          o->box(FL_THIN_UP_BOX);
          o->label_type(FL_SYMBOL_LABEL);
          o->callback((Fl_Callback*)align_cb, (void*)(FL_ALIGN_INSIDE));
          o->tooltip("Places label inside the widget");
        }
        { Fl_Box* o = image_label = new Fl_Box(9, 35, 71, 20, "Image:");
          o->align(FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
        }
        { Fl_Button* o = new Fl_Button(80, 35, 270, 20, "Image name");
          o->box(FL_THIN_DOWN_BOX);
          o->color((Fl_Color)55);
          o->callback((Fl_Callback*)image_cb);
          o->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
          o->tooltip("Select an image to label the widget");
        }
        { Fl_Group* o = new Fl_Group(10, 130, 342, 20);
          o->callback((Fl_Callback*)propagate_group);
          { Fl_Light_Button* o = new Fl_Light_Button(10, 130, 70, 20, "Nonmodal");
            o->selection_color((Fl_Color)1);
            o->label_size(10);
            o->callback((Fl_Callback*)non_modal_cb);
            o->tooltip("This window will stay on top of others in the application.");
          }
          { Fl_Light_Button* o = new Fl_Light_Button(80, 130, 70, 20, "visible");
            o->selection_color((Fl_Color)1);
            o->label_size(10);
            o->callback((Fl_Callback*)visible_cb);
            o->tooltip("Determines whether the widget is initially visible");
          }
          { Fl_Light_Button* o = new Fl_Light_Button(80, 130, 70, 20, "Modal");
            o->selection_color((Fl_Color)1);
            o->label_size(10);
            o->callback((Fl_Callback*)modal_cb);
            o->tooltip("This window will stay on top of others in the
application and will prevent events from going to other windows.");
          }
          { Fl_Light_Button* o = new Fl_Light_Button(150, 130, 70, 20, "active");
            o->selection_color((Fl_Color)1);
            o->label_size(10);
            o->callback((Fl_Callback*)active_cb);
            o->tooltip("Determines whether the widget is initially active (enabled)");
          }
          { Fl_Light_Button* o = new Fl_Light_Button(150, 130, 70, 20, "Border");
            o->selection_color((Fl_Color)1);
            o->label_size(10);
            o->callback((Fl_Callback*)border_cb);
            o->tooltip("Enable the window manager border");
          }
          { Fl_Light_Button* o = new Fl_Light_Button(220, 130, 65, 20, "Resizable");
            o->selection_color((Fl_Color)1);
            o->label_size(10);
            o->callback((Fl_Callback*)resizable_cb);
            o->when(FL_WHEN_CHANGED);
            o->tooltip("If on, this widget and all it's parents are resizable.  When the parent resizes it moves/resizes all it's children so that this widget's edges remain the same distance from all four sides of the parent.  If this is off this widget will not resize, unless it overlaps a resizable sibling.");
          }
          { Fl_Light_Button* o = new Fl_Light_Button(285, 130, 67, 20, "Hotspot");
            o->selection_color((Fl_Color)1);
            o->label_size(10);
            o->callback((Fl_Callback*)hotspot_cb);
            o->when(FL_WHEN_CHANGED);
            o->tooltip("Positions the window so this widget is under the mouse.  This is done when show() is called.");
          }
          o->end();
        }
        { Shortcut_Button* o = new Shortcut_Button(80, 160, 270, 20, "Shortcut:");
          o->box(FL_THIN_DOWN_BOX);
          o->color((Fl_Color)7);
          o->selection_color((Fl_Color)7);
          o->callback((Fl_Callback*)shortcut_in_cb);
          o->align(FL_ALIGN_LEFT);
          o->tooltip("To set a shortcut click here, then type the key combination you want.  To delete the shortcut type backspace.  To stop setting the shortcut click the mouse on some other field.");
        }
        { Fl_Input* o = new Fl_Input(80, 100, 270, 20, "X Class:");
          o->callback((Fl_Callback*)xclass_cb);
          o->when(FL_WHEN_CHANGED);
          o->tooltip("The X class name which should be used for this widget.  This can be used to choose icons.");
        }
        { Fl_Input* o = new Fl_Input(80, 185, 270, 100, "Tooltip:");
          o->type(4);
          o->callback((Fl_Callback*)tooltip_cb);
          o->tooltip("The pop up tooltip which should be used for the widget.");
        }
        { Fl_Box* o = new Fl_Box(80, 185, 270, 80, "resizable");
          o->hide();
          o->deactivate();
          Fl_Group::current()->resizable(o);
        }
        { Fl_Value_Input* o = new Fl_Value_Input(10, 100, 70, 20, "Size:");
          o->label_size(10);
          o->callback((Fl_Callback*)slider_size_cb);
          o->align(FL_ALIGN_TOP_LEFT);
          o->tooltip("The size of the scroller");
        }
        { Fl_Value_Input* o = new Fl_Value_Input(80, 100, 70, 20, "Minimum:");
          o->label_size(10);
          o->callback((Fl_Callback*)min_cb);
          o->align(FL_ALIGN_TOP_LEFT);
          o->tooltip("The minimum value for this valuator");
        }
        { Fl_Value_Input* o = new Fl_Value_Input(150, 100, 67, 20, "Maximum:");
          o->label_size(10);
          o->value(1);
          o->callback((Fl_Callback*)max_cb);
          o->align(FL_ALIGN_TOP_LEFT);
          o->tooltip("The maximum value for this valuator");
        }
        { Fl_Value_Input* o = new Fl_Value_Input(217, 100, 66, 20, "Step:");
          o->label_size(10);
          o->callback((Fl_Callback*)step_cb);
          o->align(FL_ALIGN_TOP_LEFT);
          o->tooltip("Amount to change this valuator when mouse moves 1 pixel");
        }
        { Fl_Value_Input* o = new Fl_Value_Input(283, 100, 67, 20, "Value:");
          o->label_size(10);
          o->callback((Fl_Callback*)value_cb);
          o->align(FL_ALIGN_TOP_LEFT);
          o->tooltip("The initial value (integer) of this widget");
        }
        { Fl_Button* o = new Fl_Button(95, 60, 50, 20, "tiled");
          o->type(1);
          o->box(FL_THIN_UP_BOX);
          o->label_size(12);
          o->callback((Fl_Callback*)align_cb, (void*)(FL_ALIGN_TILED));
          o->tooltip("Draw the image tiled");
        }
        { Fl_Light_Button* o = include_image_button = new Fl_Light_Button(10, 60, 80, 20, "image inlined");
          o->box(FL_THIN_UP_BOX);
          o->label_size(10);
          o->callback((Fl_Callback*)image_inlined_cb);
          o->align(132|FL_ALIGN_INSIDE);
          o->tooltip("Include the datas of the image inlined in 
the code or keep it in an external file");
        }
        o->end();
        Fl_Group::current()->resizable(o);
      }
      { Fl_Group* o = new Fl_Group(0, 0, 358, 295, "Style");
        o->callback((Fl_Callback*)propagate_group);
        o->hide();
        { Fl_Choice* o = new Fl_Choice(90, 45, 220, 20, "Label Type:");
          o->box(FL_THIN_UP_BOX);
          o->text_size(12);
          o->callback((Fl_Callback*)labeltype_cb);
          o->tooltip("How to draw the label");
          o->menu(labeltypemenu);
        }
        { Fl_Choice* o = new Fl_Choice(90, 65, 174, 20, "Label Font:");
          o->box(FL_THIN_UP_BOX);
          o->callback((Fl_Callback*)labelfont_cb);
          o->tooltip("Font to use for the label");
          o->menu(fontmenu);
        }
        { Fl_Value_Input* o = new Fl_Value_Input(264, 65, 46, 20);
          o->maximum(100);
          o->step(1);
          o->value(14);
          o->callback((Fl_Callback*)labelsize_cb);
          o->tooltip("Size of the font to use for the label");
        }
        { Fl_Choice* o = new Fl_Choice(90, 85, 174, 20, "Text Font:");
          o->box(FL_THIN_UP_BOX);
          o->callback((Fl_Callback*)textfont_cb);
          o->tooltip("Font to use for text displayed inside the widget");
          o->menu(fontmenu);
        }
        { Fl_Value_Input* o = new Fl_Value_Input(264, 85, 46, 20);
          o->maximum(100);
          o->step(1);
          o->value(14);
          o->callback((Fl_Callback*)textsize_cb);
          o->tooltip("Size of the font to use for text displayed inside the widget");
        }
        { Fl_Choice* o = new Fl_Choice(90, 15, 220, 20, "Box:");
          o->box(FL_THIN_UP_BOX);
          o->callback((Fl_Callback*)box_cb);
          o->tooltip("Type of box to draw around the widget");
          o->menu(boxmenu);
        }
        { Fl_Light_Button* o = new Fl_Light_Button(20, 120, 145, 20, "Color");
          o->box(FL_THIN_UP_BOX);
          o->label_size(10);
          o->callback((Fl_Callback*)color_cb);
          o->tooltip("The background color of the widget");
          o->type(0);
        }
        { Fl_Light_Button* o = new Fl_Light_Button(165, 120, 145, 20, "Label Color");
          o->box(FL_THIN_UP_BOX);
          o->label_size(10);
          o->callback((Fl_Callback*)labelcolor_cb);
          o->tooltip("Color to draw the label");
          o->type(0);
        }
        { Fl_Light_Button* o = new Fl_Light_Button(20, 160, 145, 20, "Selection Color");
          o->box(FL_THIN_UP_BOX);
          o->label_size(10);
          o->callback((Fl_Callback*)color2_cb);
          o->tooltip("Color to draw selected portions (usage varies)");
          o->type(0);
        }
        { Fl_Light_Button* o = new Fl_Light_Button(165, 180, 145, 20, "Text Color");
          o->box(FL_THIN_UP_BOX);
          o->label_size(10);
          o->callback((Fl_Callback*)textcolor_cb);
          o->tooltip("Color to draw text displayed inside the widget");
          o->type(0);
        }
        { Fl_Light_Button* o = new Fl_Light_Button(20, 140, 145, 20, "Highlight Color");
          o->box(FL_THIN_UP_BOX);
          o->label_size(10);
          o->callback((Fl_Callback*)highlightcolor_cb);
          o->tooltip("Color to use to draw the widget highlighted.  The black color in the upper-left of the color chooser disables highlighting");
          o->type(0);
        }
        { Fl_Light_Button* o = new Fl_Light_Button(165, 160, 145, 20, "Selected Text Color");
          o->box(FL_THIN_UP_BOX);
          o->label_size(10);
          o->callback((Fl_Callback*)selected_textcolor_cb);
          o->tooltip("Color to draw selected text inside the widget");
          o->type(0);
        }
        { Fl_Light_Button* o = new Fl_Light_Button(20, 180, 145, 20, "Off color");
          o->box(FL_THIN_UP_BOX);
          o->label_size(10);
          o->callback((Fl_Callback*)color3_cb);
          o->tooltip("Color to draw checkmarks when off");
          o->type(0);
        }
        { Fl_Button* o = new Fl_Button(20, 255, 88, 25, "Default Style");
          o->callback((Fl_Callback*)default_cb);
          o->tooltip("Resets the style to this widget's default values");
        }
        { Fl_Light_Button* o = new Fl_Light_Button(165, 140, 145, 20, "Highlight Label Color");
          o->box(FL_THIN_UP_BOX);
          o->label_size(10);
          o->callback((Fl_Callback*)highlight_label_color_cb);
          o->tooltip("Color to draw the label when the widget is highlighted");
          o->type(0);
        }
        { Fl_Box* o = new Fl_Box(20, 200, 290, 30, "resizable");
          o->hide();
          o->deactivate();
          Fl_Group::current()->resizable(o);
        }
        o->end();
      }
      { Fl_Group* o = new Fl_Group(0, 0, 358, 295, "C++");
        o->callback((Fl_Callback*)propagate_group);
        o->hide();
        { Fl_Input* o = new Fl_Input(80, 35, 217, 20, "Name:");
          o->callback((Fl_Callback*)name_cb);
          o->when(FL_WHEN_CHANGED);
          o->tooltip("The variable or member name in which to store a pointer to this widget.");
        }
        { Fl_Light_Button* o = new Fl_Light_Button(297, 35, 53, 20, "public");
          o->box(FL_THIN_UP_BOX);
          o->label_size(10);
          o->callback((Fl_Callback*)name_public_cb);
          o->when(FL_WHEN_CHANGED);
          o->tooltip("Make the variable public");
        }
        { Fl_Input* o = v_input[0] = new Fl_Input(80, 60, 270, 20, "Extra Code:");
          o->callback((Fl_Callback*)v_input_cb, (void*)(0));
          o->tooltip("Extra code to be exectuted when the widget is created");
        }
        { Fl_Input* o = v_input[1] = new Fl_Input(80, 80, 270, 20);
          o->callback((Fl_Callback*)v_input_cb, (void*)(1));
          o->tooltip("Extra code to be exectuted when the widget is created");
        }
        { Fl_Input* o = v_input[2] = new Fl_Input(80, 100, 270, 20);
          o->callback((Fl_Callback*)v_input_cb, (void*)(2));
          o->tooltip("Extra code to be exectuted when the widget is created");
        }
        { Fl_Input* o = v_input[3] = new Fl_Input(80, 120, 270, 20);
          o->callback((Fl_Callback*)v_input_cb, (void*)(3));
          o->tooltip("Extra code to be exectuted when the widget is created");
        }
        { Fl_Box* o = callback_label = new Fl_Box(10, 145, 70, 20, "Callback:");
          o->align(FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
        }
        { Fl_Input* o = new Fl_Input(80, 145, 270, 95);
          o->type(4);
          o->callback((Fl_Callback*)callback_cb);
          o->tooltip("The name of the callback function, or code body of the callback function");
        }
        { Fl_Input* o = new Fl_Input(80, 245, 137, 20, "User Data:");
          o->callback((Fl_Callback*)user_data_cb);
          o->tooltip("Value passed as the second argument to the callback.  This must be of the type given below.");
        }
        { Fl_Choice* o = new Fl_Choice(255, 245, 95, 20, "When:");
          o->box(FL_THIN_UP_BOX);
          o->label_size(10);
          o->callback((Fl_Callback*)when_cb);
          o->when(FL_WHEN_NEVER);
          o->tooltip("What actions cause the callback to be called.");
          o->menu(whenmenu);
        }
        { Fl_Input* o = new Fl_Input(80, 265, 137, 20, "Type:");
          o->callback((Fl_Callback*)user_data_type_cb);
          o->tooltip("Type of the user data (must \"long\" or a pointer type)");
        }
        { Fl_Light_Button* o = new Fl_Light_Button(255, 265, 95, 20, "no change");
          o->box(FL_THIN_UP_BOX);
          o->selection_color((Fl_Color)1);
          o->label_size(10);
          o->callback((Fl_Callback*)when_button_cb);
          o->when(FL_WHEN_NEVER);
          o->tooltip("Further modifies When so that the callback is done even if the widget's value has not changed.");
        }
        { Fl_Box* o = new Fl_Box(80, 165, 175, 65, "resizable");
          o->hide();
          o->deactivate();
          Fl_Group::current()->resizable(o);
        }
        { Fl_Input* o = new Fl_Input(80, 10, 175, 20, "Class:");
          o->callback((Fl_Callback*)subclass_cb, (void*)(4));
          o->when(FL_WHEN_CHANGED);
          o->tooltip("This allows you to name a user-defined class that this widget is an instance of, rather than an fltk built-in class. You will need to add a #include declaration so that the definition of your class is included in the fluid output.");
        }
        { Fl_Choice* o = new Fl_Choice(255, 10, 95, 20);
          o->box(FL_THIN_UP_BOX);
          o->callback((Fl_Callback*)subtype_cb);
          o->tooltip("Selects a value for type() for this widget");
        }
        o->end();
      }
      o->end();
      Fl_Group::current()->resizable(o);
    }
    { Fl_Group* o = new Fl_Group(125, 304, 234, 26);
      { Fl_Light_Button* o = overlaybutton = new Fl_Light_Button(202, 305, 78, 25, "&Overlays");
        o->selection_color((Fl_Color)1);
        o->callback((Fl_Callback*)overlay_cb);
        o->tooltip("Turns overlays (red outlines)  of the selected  widgets on or off");
        o->value(!overlays_invisible);
      }
      { Fl_Button* o = new Fl_Button(125, 304, 69, 26, "Cancel");
        o->callback((Fl_Callback*)cancel_cb);
        o->hide();
      }
      { Fl_Return_Button* o = new Fl_Return_Button(292, 305, 67, 25, "Close");
        o->callback((Fl_Callback*)ok_cb);
        o->tooltip("Closes this attribute window");
      }
      o->end();
    }
    o->end();
  }
  return w;
}
