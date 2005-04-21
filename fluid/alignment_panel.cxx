//
// "$Id$"
//
// Setting and shell dialogs for the Fast Light Tool Kit (FLTK).
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

// generated by Fast Light User Interface Designer (fluid) version 1.0107

#include "alignment_panel.h"

Fl_Double_Window *project_window=(Fl_Double_Window *)0;

static void cb_Close(Fl_Button*, void*) {
  project_window->hide();
}

Fl_Input *header_file_input=(Fl_Input *)0;

Fl_Input *code_file_input=(Fl_Input *)0;

Fl_Light_Button *include_H_from_C_button=(Fl_Light_Button *)0;

Fl_Choice *i18n_type_chooser=(Fl_Choice *)0;

Fl_Menu_Item menu_i18n_type_chooser[] = {
 {"None", 0,  0, 0, 0, FL_NORMAL_LABEL, 0, 11, 56},
 {"GNU gettext", 0,  0, 0, 0, FL_NORMAL_LABEL, 0, 11, 56},
 {"POSIX catgets", 0,  0, 0, 0, FL_NORMAL_LABEL, 0, 11, 56},
 {0,0,0,0,0,0,0,0,0}
};

Fl_Input *i18n_include_input=(Fl_Input *)0;

Fl_Input *i18n_file_input=(Fl_Input *)0;

Fl_Input *i18n_set_input=(Fl_Input *)0;

Fl_Input *i18n_function_input=(Fl_Input *)0;

Fl_Double_Window* make_project_window() {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = project_window = new Fl_Double_Window(345, 185, "Project Settings");
    w = o;
    { Fl_Button* o = new Fl_Button(293, 156, 42, 20, "Close");
      o->tooltip("Close this dialog.");
      o->labelsize(11);
      o->callback((Fl_Callback*)cb_Close);
    }
    { Fl_Tabs* o = new Fl_Tabs(10, 10, 325, 138);
      o->selection_color((Fl_Color)4);
      o->labelsize(11);
      { Fl_Group* o = new Fl_Group(10, 30, 325, 116, "Output");
        o->labelsize(11);
        { Fl_Box* o = new Fl_Box(20, 40, 304, 15, "Use \"name.ext\" to set name or just \".ext\" to set extension.");
          o->labelsize(11);
          o->align(132|FL_ALIGN_INSIDE);
        }
        { Fl_Input* o = header_file_input = new Fl_Input(96, 60, 228, 20, "Header File:");
          o->tooltip("The name of the generated header file.");
          o->box(FL_THIN_DOWN_BOX);
          o->labelfont(1);
          o->labelsize(11);
          o->textfont(4);
          o->textsize(11);
          o->callback((Fl_Callback*)header_input_cb, (void*)(1));
          o->when(FL_WHEN_CHANGED);
        }
        { Fl_Input* o = code_file_input = new Fl_Input(97, 85, 227, 20, "Code File:");
          o->tooltip("The name of the generated code file.");
          o->box(FL_THIN_DOWN_BOX);
          o->labelfont(1);
          o->labelsize(11);
          o->textfont(4);
          o->textsize(11);
          o->callback((Fl_Callback*)code_input_cb, (void*)(1));
          o->when(FL_WHEN_CHANGED);
        }
        { Fl_Light_Button* o = include_H_from_C_button = new Fl_Light_Button(166, 110, 158, 20, "Include Header from Code");
          o->tooltip("Include the header file from the code file.");
          o->value(1);
          o->labelsize(11);
          o->callback((Fl_Callback*)include_H_from_C_button_cb);
        }
        o->end();
      }
      { Fl_Group* o = new Fl_Group(10, 30, 325, 116, "Internationalization");
        o->labelsize(11);
        o->hide();
        { Fl_Choice* o = i18n_type_chooser = new Fl_Choice(80, 42, 100, 20, "Use:");
          o->tooltip("Type of internationalization to use.");
          o->box(FL_THIN_UP_BOX);
          o->down_box(FL_BORDER_BOX);
          o->labelfont(1);
          o->labelsize(11);
          o->textsize(11);
          o->callback((Fl_Callback*)i18n_type_cb);
          o->menu(menu_i18n_type_chooser);
        }
        { Fl_Input* o = i18n_include_input = new Fl_Input(80, 67, 245, 20, "#include:");
          o->tooltip("The include file for internationalization.");
          o->box(FL_THIN_DOWN_BOX);
          o->labelfont(1);
          o->labelsize(11);
          o->textfont(4);
          o->textsize(11);
          o->callback((Fl_Callback*)i18n_text_cb);
        }
        { Fl_Input* o = i18n_file_input = new Fl_Input(80, 92, 245, 20, "File:");
          o->tooltip("The name of the message catalog.");
          o->box(FL_THIN_DOWN_BOX);
          o->labelfont(1);
          o->labelsize(11);
          o->textfont(4);
          o->textsize(11);
          o->callback((Fl_Callback*)i18n_text_cb);
        }
        { Fl_Input* o = i18n_set_input = new Fl_Input(80, 117, 245, 20, "Set:");
          o->tooltip("The message set number.");
          o->type(2);
          o->box(FL_THIN_DOWN_BOX);
          o->labelfont(1);
          o->labelsize(11);
          o->textfont(4);
          o->textsize(11);
          o->callback((Fl_Callback*)i18n_text_cb);
        }
        { Fl_Input* o = i18n_function_input = new Fl_Input(80, 92, 245, 20, "Function:");
          o->tooltip("The function to call to internationalize the labels and tooltips.");
          o->box(FL_THIN_DOWN_BOX);
          o->labelfont(1);
          o->labelsize(11);
          o->textfont(4);
          o->textsize(11);
          o->callback((Fl_Callback*)i18n_text_cb);
        }
        o->end();
      }
      o->end();
    }
    o->set_modal();
    o->end();
  }
  return w;
}
Fl_Text_Buffer *shell_run_buffer;
void scheme_cb(Fl_Choice *, void *);

Fl_Double_Window *settings_window=(Fl_Double_Window *)0;

Fl_Choice *scheme_choice=(Fl_Choice *)0;

Fl_Menu_Item menu_scheme_choice[] = {
 {"Default", 0,  0, 0, 0, FL_NORMAL_LABEL, 0, 14, 56},
 {"None", 0,  0, 0, 0, FL_NORMAL_LABEL, 0, 14, 56},
 {"Plastic", 0,  0, 0, 0, FL_NORMAL_LABEL, 0, 14, 56},
 {0,0,0,0,0,0,0,0,0}
};

Fl_Check_Button *tooltips_button=(Fl_Check_Button *)0;

static void cb_tooltips_button(Fl_Check_Button*, void*) {
  Fl_Tooltip::enable(tooltips_button->value());
fluid_prefs.set("show_tooltips", tooltips_button->value());
}

Fl_Check_Button *completion_button=(Fl_Check_Button *)0;

static void cb_completion_button(Fl_Check_Button*, void*) {
  fluid_prefs.set("show_completion_dialogs", completion_button->value());
}

Fl_Check_Button *openlast_button=(Fl_Check_Button *)0;

static void cb_openlast_button(Fl_Check_Button*, void*) {
  fluid_prefs.set("open_previous_file", openlast_button->value());
}

Fl_Check_Button *prevpos_button=(Fl_Check_Button *)0;

static void cb_prevpos_button(Fl_Check_Button*, void*) {
  fluid_prefs.set("prev_window_pos", prevpos_button->value());
}

static void cb_Close1(Fl_Button*, void*) {
  settings_window->hide();
}

Fl_Spinner *recent_spinner=(Fl_Spinner *)0;

static void cb_recent_spinner(Fl_Spinner*, void*) {
  fluid_prefs.set("recent_files", recent_spinner->value());
load_history();
}

Fl_Double_Window* make_settings_window() {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = settings_window = new Fl_Double_Window(340, 225, "GUI Settings");
    w = o;
    { Fl_Choice* o = scheme_choice = new Fl_Choice(116, 10, 115, 25, "Scheme:");
      o->down_box(FL_BORDER_BOX);
      o->labelfont(1);
      o->callback((Fl_Callback*)scheme_cb);
      o->menu(menu_scheme_choice);
      int s;
      fluid_prefs.get("scheme", s, 0);
      scheme_choice->value(s);
      scheme_cb(0, 0);
    }
    { Fl_Group* o = new Fl_Group(116, 45, 215, 100, "Options:\n\n\n\n\n");
      o->labelfont(1);
      o->align(FL_ALIGN_LEFT);
      { Fl_Check_Button* o = tooltips_button = new Fl_Check_Button(116, 45, 113, 25, "Show Tooltips");
        o->down_box(FL_DOWN_BOX);
        o->callback((Fl_Callback*)cb_tooltips_button);
        int b;
        fluid_prefs.get("show_tooltips", b, 1);
        tooltips_button->value(b);
        Fl_Tooltip::enable(b);
      }
      { Fl_Check_Button* o = completion_button = new Fl_Check_Button(116, 70, 186, 25, "Show Completion Dialogs");
        o->down_box(FL_DOWN_BOX);
        o->callback((Fl_Callback*)cb_completion_button);
        int b;
        fluid_prefs.get("show_completion_dialogs", b, 1);
        completion_button->value(b);
      }
      { Fl_Check_Button* o = openlast_button = new Fl_Check_Button(116, 95, 215, 25, "Open Previous File on Startup");
        o->down_box(FL_DOWN_BOX);
        o->callback((Fl_Callback*)cb_openlast_button);
        int b;
        fluid_prefs.get("open_previous_file", b, 0);
        openlast_button->value(b);
      }
      { Fl_Check_Button* o = prevpos_button = new Fl_Check_Button(116, 120, 210, 25, "Remember Window Positions");
        o->down_box(FL_DOWN_BOX);
        o->callback((Fl_Callback*)cb_prevpos_button);
        int b;
        fluid_prefs.get("prev_window_pos", b, 1);
        prevpos_button->value(b);
      }
      o->end();
    }
    { Fl_Button* o = new Fl_Button(266, 190, 64, 25, "Close");
      o->tooltip("Close this dialog.");
      o->callback((Fl_Callback*)cb_Close1);
    }
    { Fl_Spinner* o = recent_spinner = new Fl_Spinner(116, 155, 40, 25, "# Recent Files:");
      o->labelfont(1);
      o->callback((Fl_Callback*)cb_recent_spinner);
      o->when(FL_WHEN_CHANGED);
      int c;
      fluid_prefs.get("recent_files", c, 5);
      recent_spinner->maximum(10);
      recent_spinner->value(c);
    }
    o->end();
  }
  return w;
}

Fl_Double_Window *shell_window=(Fl_Double_Window *)0;

Fl_Input *shell_command_input=(Fl_Input *)0;

static void cb_shell_command_input(Fl_Input*, void*) {
  fluid_prefs.set("shell_command", shell_command_input->value());
}

Fl_Check_Button *shell_writecode_button=(Fl_Check_Button *)0;

static void cb_shell_writecode_button(Fl_Check_Button*, void*) {
  fluid_prefs.set("shell_writecode", shell_writecode_button->value());
}

Fl_Check_Button *shell_writemsgs_button=(Fl_Check_Button *)0;

static void cb_shell_writemsgs_button(Fl_Check_Button*, void*) {
  fluid_prefs.set("shell_writemsgs", shell_writemsgs_button->value());
}

Fl_Check_Button *shell_savefl_button=(Fl_Check_Button *)0;

static void cb_shell_savefl_button(Fl_Check_Button*, void*) {
  fluid_prefs.set("shell_savefl", shell_savefl_button->value());
}

static void cb_Cancel(Fl_Button*, void*) {
  shell_window->hide();
}

Fl_Double_Window *shell_run_window=(Fl_Double_Window *)0;

Fl_Text_Display *shell_run_display=(Fl_Text_Display *)0;

Fl_Return_Button *shell_run_button=(Fl_Return_Button *)0;

static void cb_shell_run_button(Fl_Return_Button*, void*) {
  shell_run_window->hide();
}

Fl_Double_Window* make_shell_window() {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = shell_window = new Fl_Double_Window(365, 125, "Shell Command");
    w = o;
    { Fl_Input* o = shell_command_input = new Fl_Input(10, 27, 347, 25, "Command:");
      o->labelfont(1);
      o->callback((Fl_Callback*)cb_shell_command_input);
      o->align(FL_ALIGN_TOP_LEFT);
      char buf[1024];
      fluid_prefs.get("shell_command", buf, "", sizeof(buf));
      shell_command_input->value(buf);
    }
    { Fl_Check_Button* o = shell_writecode_button = new Fl_Check_Button(128, 61, 93, 19, "Write Code");
      o->down_box(FL_DOWN_BOX);
      o->callback((Fl_Callback*)cb_shell_writecode_button);
      int b;
      fluid_prefs.get("shell_writecode", b, 1);
      shell_writecode_button->value(b);
    }
    { Fl_Check_Button* o = shell_writemsgs_button = new Fl_Check_Button(231, 61, 126, 19, "Write Messages");
      o->down_box(FL_DOWN_BOX);
      o->callback((Fl_Callback*)cb_shell_writemsgs_button);
      int b;
      fluid_prefs.get("shell_writemsgs", b, 0);
      shell_writemsgs_button->value(b);
    }
    { Fl_Check_Button* o = shell_savefl_button = new Fl_Check_Button(10, 62, 108, 19, "Save .FL File");
      o->down_box(FL_DOWN_BOX);
      o->callback((Fl_Callback*)cb_shell_savefl_button);
      int b;
      fluid_prefs.get("shell_savefl", b, 1);
      shell_savefl_button->value(b);
    }
    { Fl_Return_Button* o = new Fl_Return_Button(132, 90, 143, 25, "Run Command");
      o->callback((Fl_Callback*)do_shell_command);
    }
    { Fl_Button* o = new Fl_Button(285, 90, 72, 25, "Cancel");
      o->callback((Fl_Callback*)cb_Cancel);
    }
    o->end();
  }
  { Fl_Double_Window* o = shell_run_window = new Fl_Double_Window(555, 430, "Shell Command Output");
    w = o;
    { Fl_Text_Display* o = shell_run_display = new Fl_Text_Display(10, 10, 535, 375);
      o->box(FL_DOWN_BOX);
      o->textfont(4);
      Fl_Group::current()->resizable(o);
      shell_run_buffer = new Fl_Text_Buffer();
      shell_run_display->buffer(shell_run_buffer);
    }
    { Fl_Return_Button* o = shell_run_button = new Fl_Return_Button(468, 395, 77, 25, "Close");
      o->callback((Fl_Callback*)cb_shell_run_button);
    }
    o->end();
  }
  return w;
}

Fl_Double_Window *grid_window=(Fl_Double_Window *)0;

Fl_Input *horizontal_input=(Fl_Input *)0;

Fl_Input *vertical_input=(Fl_Input *)0;

Fl_Input *snap_input=(Fl_Input *)0;

Fl_Check_Button *guides_toggle=(Fl_Check_Button *)0;

static void cb_Close2(Fl_Button*, void*) {
  grid_window->hide();
}

Fl_Double_Window* make_grid_window() {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = grid_window = new Fl_Double_Window(145, 185, "Grid");
    w = o;
    { Fl_Input* o = horizontal_input = new Fl_Input(88, 10, 47, 25, "Horizontal:");
      o->tooltip("Horizontal grid spacing.");
      o->type(2);
      o->box(FL_THIN_DOWN_BOX);
      o->labelfont(1);
      o->callback((Fl_Callback*)grid_cb, (void*)(1));
      o->when(FL_WHEN_RELEASE|FL_WHEN_ENTER_KEY);
    }
    { Fl_Input* o = vertical_input = new Fl_Input(88, 45, 47, 25, "Vertical:");
      o->tooltip("Vertical grid spacing.");
      o->type(2);
      o->box(FL_THIN_DOWN_BOX);
      o->labelfont(1);
      o->callback((Fl_Callback*)grid_cb, (void*)(2));
      o->when(FL_WHEN_RELEASE|FL_WHEN_ENTER_KEY);
    }
    { Fl_Input* o = snap_input = new Fl_Input(88, 80, 47, 25, "Snap:");
      o->tooltip("Snap to grid within this many pixels.");
      o->type(2);
      o->box(FL_THIN_DOWN_BOX);
      o->labelfont(1);
      o->callback((Fl_Callback*)grid_cb, (void*)(3));
      o->when(FL_WHEN_RELEASE|FL_WHEN_ENTER_KEY);
    }
    { Fl_Check_Button* o = guides_toggle = new Fl_Check_Button(27, 115, 108, 25, "Show Guides");
      o->tooltip("Show distance and alignment guides in overlay");
      o->down_box(FL_DOWN_BOX);
      o->callback((Fl_Callback*)guides_cb, (void*)(4));
    }
    { Fl_Button* o = new Fl_Button(76, 150, 59, 25, "Close");
      o->tooltip("Close this dialog.");
      o->callback((Fl_Callback*)cb_Close2);
    }
    o->end();
  }
  return w;
}

//
// End of "$Id$".
//
