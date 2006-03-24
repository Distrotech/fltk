// generated by Fast Light User Interface Designer (fluid) version 2.0002

#include "alignment_panel.h"

fltk::Window* alignment_window;

fltk::Input* horizontal_input;

fltk::Input* vertical_input;

fltk::Input* snap_input;

fltk::Input* header_file_input;

fltk::Input* code_file_input;

fltk::CheckButton* include_H_from_C_button;

static void cb_Close(fltk::Button*, void*) {
  alignment_window->hide();
}

fltk::Window* make_alignment_window() {
  fltk::Window* w;
   {fltk::Window* o = alignment_window = new fltk::Window(210, 310, "fluid Preferences");
    w = o;
    o->begin();
     {fltk::Group* o = new fltk::Group(10, 20, 190, 100, "Alignment:");
      o->box(fltk::ENGRAVED_BOX);
      o->align(fltk::ALIGN_TOP|fltk::ALIGN_LEFT);
      o->begin();
       {fltk::Input* o = horizontal_input = new fltk::Input(80, 10, 100, 22, "Horizontal:");
        o->callback((fltk::Callback*)alignment_cb, (void*)(1));
        o->when(fltk::WHEN_RELEASE|fltk::WHEN_ENTER_KEY);
      }
       {fltk::Input* o = vertical_input = new fltk::Input(80, 40, 100, 22, "Vertical:");
        o->callback((fltk::Callback*)alignment_cb, (void*)(2));
        o->when(fltk::WHEN_RELEASE|fltk::WHEN_ENTER_KEY);
      }
       {fltk::Input* o = snap_input = new fltk::Input(80, 70, 100, 22, "Snap:");
        o->callback((fltk::Callback*)alignment_cb, (void*)(3));
        o->when(fltk::WHEN_RELEASE|fltk::WHEN_ENTER_KEY);
      }
      o->end();
    }
     {fltk::Group* o = new fltk::Group(10, 140, 190, 130, "Output File Names:");
      o->box(fltk::ENGRAVED_BOX);
      o->align(fltk::ALIGN_TOP|fltk::ALIGN_LEFT);
      o->begin();
       {fltk::Widget* o = new fltk::Widget(10, 10, 170, 30, "Use \"name.ext\" to set name or just \".ext\" to set only extension.");
        o->box(fltk::NO_BOX);
        o->labelsize(11);
        o->align(fltk::ALIGN_LEFT|fltk::ALIGN_INSIDE|fltk::ALIGN_WRAP);
      }
       {fltk::Input* o = header_file_input = new fltk::Input(90, 40, 90, 22, "Header File:");
        o->callback((fltk::Callback*)header_input_cb, (void*)(1));
        o->when(fltk::WHEN_CHANGED);
      }
       {fltk::Input* o = code_file_input = new fltk::Input(90, 70, 90, 22, "Code File:");
        o->callback((fltk::Callback*)code_input_cb, (void*)(1));
        o->when(fltk::WHEN_CHANGED);
      }
       {fltk::CheckButton* o = include_H_from_C_button = new fltk::CheckButton(10, 98, 170, 22, "#include \"header\" in code");
        o->value(1);
        o->callback((fltk::Callback*)include_H_from_C_button_cb);
      }
      o->end();
    }
     {fltk::Button* o = new fltk::Button(140, 280, 60, 22, "Close");
      o->callback((fltk::Callback*)cb_Close);
    }
    o->end();
    o->set_non_modal();
  }
  return  w;
}
