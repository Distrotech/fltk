// generated by Fast Light User Interface Designer (fluid) version 2.0002

#include "inactive.h"

fltk::Group* the_group;

static void cb_active(fltk::Button*, void*) {
  the_group->activate();
}

static void cb_inactive(fltk::Button*, void*) {
  the_group->deactivate();
}

#include <fltk/run.h>

int main (int argc, char **argv) {

  fltk::Window* w;
   {fltk::Window* o = new fltk::Window(395, 274);
    w = o;
    o->begin();
     {fltk::Group* o = the_group = new fltk::Group(5, 6, 384, 233, "activate()/deactivate() called on this Fl_Group");
      o->box(fltk::ENGRAVED_BOX);
      o->align(fltk::ALIGN_TOP|fltk::ALIGN_INSIDE);
      o->begin();
      new fltk::Button(25, 27, 105, 21, "button");
       {fltk::Group* o = new fltk::Group(25, 74, 105, 102, "Child group");
        o->begin();
         {fltk::CheckButton* o = new fltk::CheckButton(0, 0, 105, 25, "red");
          o->type(fltk::CheckButton::RADIO);
          o->selection_color((fltk::Color)1);
          o->selection_textcolor((fltk::Color)1);
          o->labelcolor((fltk::Color)1);
          o->highlight_textcolor((fltk::Color)1);
        }
         {fltk::CheckButton* o = new fltk::CheckButton(0, 25, 105, 25, "green");
          o->type(fltk::CheckButton::RADIO);
          o->selection_color((fltk::Color)2);
          o->selection_textcolor((fltk::Color)2);
          o->labelcolor((fltk::Color)2);
          o->highlight_textcolor((fltk::Color)2);
        }
         {fltk::CheckButton* o = new fltk::CheckButton(0, 50, 105, 25, "blue");
          o->type(fltk::CheckButton::RADIO);
          o->selection_color((fltk::Color)4);
          o->selection_textcolor((fltk::Color)4);
          o->labelcolor((fltk::Color)4);
          o->highlight_textcolor((fltk::Color)4);
        }
         {fltk::CheckButton* o = new fltk::CheckButton(0, 75, 105, 25, "white");
          o->type(fltk::CheckButton::RADIO);
          o->selection_color((fltk::Color)7);
          o->selection_textcolor((fltk::Color)55);
          o->labelcolor((fltk::Color)7);
          o->highlight_textcolor((fltk::Color)55);
        }
        o->end();
      }
       {fltk::Slider* o = new fltk::Slider(140, 25, 24, 146, "Fl_Slider");
        o->set_vertical();
        o->value(0.5);
      }
       {fltk::Input* o = new fltk::Input(170, 27, 195, 21);
        o->static_value("Fl_Input");
      }
       {fltk::InputBrowser* o = new fltk::InputBrowser(255, 59, 110, 21, "input browser");
        o->begin();
         {fltk::Item* o = new fltk::Item("Moe");
          o->set_vertical();
        }
         {fltk::Item* o = new fltk::Item("Larry");
          o->set_vertical();
        }
         {fltk::Item* o = new fltk::Item("Curly");
          o->set_vertical();
        }
        o->end();
        o->text("Shemp");
      }
       {fltk::Widget* o = new fltk::Widget(215, 134, 145, 86, "Fl_Box");
        o->box(fltk::ENGRAVED_BOX);
        o->labelfont(fltk::HELVETICA_BOLD_ITALIC);
        o->labeltype(fltk::SHADOW_LABEL);
        o->labelsize(38);
      }
       {fltk::ValueInput* o = new fltk::ValueInput(230, 91, 135, 32, "value:");
        o->textfont(fltk::COURIER_BOLD);
        o->textcolor((fltk::Color)4);
        o->textsize(24);
        o->maximum(10000);
        o->step(1);
        o->tooltip("This Fl_Value_Output widget has a tooltip.");
      }
       {fltk::Scrollbar* o = new fltk::Scrollbar(15, 191, 180, 19, "scrollbar");
        o->maximum(100);
      }
      o->end();
      fltk::Group::current()->resizable(o);
    }
     {fltk::Button* o = new fltk::Button(5, 244, 190, 25, "active");
      o->type(fltk::Button::RADIO);
      o->set();
      o->callback((fltk::Callback*)cb_active);
    }
     {fltk::Button* o = new fltk::Button(205, 244, 184, 25, "inactive");
      o->type(fltk::Button::RADIO);
      o->callback((fltk::Callback*)cb_inactive);
    }
    o->end();
  }
  w->show(argc, argv);
  return  fltk::run();
}