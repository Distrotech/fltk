// generated by Fast Light User Interface Designer (fluid) version 2.0002

#include "coding_style.h"
static int brace_style;
static int no_space_parens;
static int brace_functions;
static int indent_tabs;
static int tab_size;
static int always_return_parens;
static int indent_code;

static void use_coding_style() {
  gbrace_style = brace_style;
  gno_space_parens = no_space_parens;
  gbrace_functions = brace_functions;
  gindent_tabs = indent_tabs;
  gtab_size = tab_size;
  galways_return_parens = always_return_parens;
}

static fltk::RadioButton* pStyle1;

static void cb_pStyle1(fltk::RadioButton* o, void*) {
  if(o->value())
     brace_style = 1;
}

static fltk::RadioButton* pStyle2;

static void cb_pStyle2(fltk::RadioButton* o, void*) {
  if(o->value())
     brace_style = 2;
}

static fltk::RadioButton* pStyle3;

static void cb_pStyle3(fltk::RadioButton* o, void*) {
  if(o->value())
     brace_style = 3;
}

static fltk::CheckButton* pNoSpaceParens;

static void cb_pNoSpaceParens(fltk::CheckButton* o, void*) {
  no_space_parens = o->value();;
}

static fltk::CheckButton* pBraceFuncs;

static void cb_pBraceFuncs(fltk::CheckButton* o, void*) {
  brace_functions = o->value();
}

static fltk::ValueInput* pTabSize;

static void cb_pTabSize(fltk::ValueInput* o, void*) {
  tab_size = (int)o->value();
}

static fltk::CheckButton* pIndentTabs;

static void cb_pIndentTabs(fltk::CheckButton* o, void*) {
  indent_tabs = o->value();
  if(o->value())
      pTabSize->hide();
  else
     pTabSize->show();
}

static fltk::CheckButton* pIndentCode;

static void cb_pIndentCode(fltk::CheckButton* o, void*) {
  indent_code = o->value();
}

static fltk::CheckButton* pReturnParens;

static void cb_pReturnParens(fltk::CheckButton* o, void*) {
  always_return_parens = o->value();
}

static void cb_Cancel(fltk::Button* o, void*) {
  o->window()->hide();
}

static void cb_Save(fltk::Button* o, void*) {
  use_coding_style();
  save_coding_style();
  o->window()->hide();
}

static void cb_Use(fltk::Button* o, void*) {
  use_coding_style();
  o->window()->hide();
}

fltk::Window* make_codingstyle_window() {
  fltk::Window* w;
   {fltk::Window* o = new fltk::Window(310, 255);
    w = o;
    o->begin();
     {fltk::TabGroup* o = new fltk::TabGroup(0, 0, 303, 220);
      o->box(fltk::EMBOSSED_BOX);
      o->begin();
       {fltk::Group* o = new fltk::Group(0, 25, 303, 195, "Brace Style");
        o->begin();
         {fltk::Group* o = new fltk::Group(14, 22, 282, 122, "Brace Style");
          o->box(fltk::ENGRAVED_BOX);
          o->align(fltk::ALIGN_TOP|fltk::ALIGN_LEFT);
          o->begin();
           {fltk::Widget* o = new fltk::Widget(20, 6, 47, 20, "if ( x ) {");
            o->box(fltk::NO_BOX);
            o->align(fltk::ALIGN_LEFT|fltk::ALIGN_INSIDE);
          }
           {fltk::Widget* o = new fltk::Widget(20, 25, 45, 20, "++y;");
            o->box(fltk::NO_BOX);
            o->align(fltk::ALIGN_RIGHT|fltk::ALIGN_INSIDE);
          }
           {fltk::Widget* o = new fltk::Widget(20, 41, 36, 20, "}");
            o->box(fltk::NO_BOX);
            o->align(fltk::ALIGN_LEFT|fltk::ALIGN_INSIDE);
          }
           {fltk::Widget* o = new fltk::Widget(114, 6, 47, 20, "if ( x )");
            o->box(fltk::NO_BOX);
            o->align(fltk::ALIGN_LEFT|fltk::ALIGN_INSIDE);
          }
           {fltk::Widget* o = new fltk::Widget(114, 25, 36, 20, "{");
            o->box(fltk::NO_BOX);
            o->align(fltk::ALIGN_LEFT|fltk::ALIGN_INSIDE);
          }
           {fltk::Widget* o = new fltk::Widget(115, 42, 46, 20, "++y;");
            o->box(fltk::NO_BOX);
            o->align(fltk::ALIGN_RIGHT|fltk::ALIGN_INSIDE);
          }
           {fltk::Widget* o = new fltk::Widget(114, 59, 36, 20, "}");
            o->box(fltk::NO_BOX);
            o->align(fltk::ALIGN_LEFT|fltk::ALIGN_INSIDE);
          }
           {fltk::RadioButton* o = pStyle1 = new fltk::RadioButton(16, 84, 66, 25, "Style 1");
            o->value(1);
            o->callback((fltk::Callback*)cb_pStyle1);
          }
           {fltk::Widget* o = new fltk::Widget(201, 6, 47, 20, "if ( x )");
            o->box(fltk::NO_BOX);
            o->align(fltk::ALIGN_LEFT|fltk::ALIGN_INSIDE);
          }
           {fltk::Widget* o = new fltk::Widget(201, 25, 36, 20, "{");
            o->box(fltk::NO_BOX);
            o->align(fltk::ALIGN_RIGHT|fltk::ALIGN_INSIDE);
          }
           {fltk::Widget* o = new fltk::Widget(227, 42, 34, 22, "++y;");
            o->box(fltk::NO_BOX);
            o->align(fltk::ALIGN_RIGHT|fltk::ALIGN_INSIDE);
          }
           {fltk::Widget* o = new fltk::Widget(201, 59, 36, 20, "}");
            o->box(fltk::NO_BOX);
            o->align(fltk::ALIGN_RIGHT|fltk::ALIGN_INSIDE);
          }
           {fltk::RadioButton* o = pStyle2 = new fltk::RadioButton(109, 84, 66, 25, "Style 2");
            o->callback((fltk::Callback*)cb_pStyle2);
          }
           {fltk::RadioButton* o = pStyle3 = new fltk::RadioButton(200, 84, 66, 25, "Style 3");
            o->callback((fltk::Callback*)cb_pStyle3);
          }
          o->end();
        }
         {fltk::CheckButton* o = pNoSpaceParens = new fltk::CheckButton(15, 147, 195, 22, "No space before parentheses");
          o->callback((fltk::Callback*)cb_pNoSpaceParens);
        }
         {fltk::CheckButton* o = pBraceFuncs = new fltk::CheckButton(15, 170, 174, 22, "Apply to function braces");
          o->value(1);
          o->callback((fltk::Callback*)cb_pBraceFuncs);
        }
        o->end();
      }
       {fltk::Group* o = new fltk::Group(0, 25, 303, 183, "Other");
        o->hide();
        o->begin();
         {fltk::Group* o = new fltk::Group(11, 22, 218, 90, "Indentation");
          o->box(fltk::ENGRAVED_BOX);
          o->align(fltk::ALIGN_TOP|fltk::ALIGN_LEFT);
          o->begin();
           {fltk::ValueInput* o = pTabSize = new fltk::ValueInput(129, 33, 31, 22, "Tab size for indents");
            o->maximum(12);
            o->value(2);
            o->callback((fltk::Callback*)cb_pTabSize);
          }
           {fltk::CheckButton* o = pIndentTabs = new fltk::CheckButton(13, 7, 114, 22, "Indent with tabs");
            o->callback((fltk::Callback*)cb_pIndentTabs);
          }
           {fltk::CheckButton* o = pIndentCode = new fltk::CheckButton(14, 58, 151, 22, "Indent code blocks");
            o->callback((fltk::Callback*)cb_pIndentCode);
          }
          o->end();
        }
         {fltk::CheckButton* o = pReturnParens = new fltk::CheckButton(10, 120, 220, 22, "Always use parentheses on return");
          o->callback((fltk::Callback*)cb_pReturnParens);
        }
        o->end();
      }
      o->end();
    }
     {fltk::Button* o = new fltk::Button(106, 223, 59, 25, "Cancel");
      o->callback((fltk::Callback*)cb_Cancel);
    }
     {fltk::Button* o = new fltk::Button(171, 223, 59, 25, "Save");
      o->callback((fltk::Callback*)cb_Save);
    }
     {fltk::Button* o = new fltk::Button(236, 223, 59, 25, "Use");
      o->callback((fltk::Callback*)cb_Use);
    }
    o->end();
    o->resizable(o);
  }
  return  w;
}

void load_codingstyle_window() {
  brace_style = gbrace_style;
  no_space_parens = gno_space_parens;
  brace_functions = gbrace_functions;  
  indent_tabs = gindent_tabs;
  tab_size = gtab_size;
  always_return_parens = galways_return_parens;
  indent_code = gindent_code;
  pStyle1->value(gbrace_style == 1);
  pStyle2->value(gbrace_style == 2);
  pStyle3->value(gbrace_style == 3);
  pNoSpaceParens->value(gno_space_parens);
  pBraceFuncs->value(gbrace_functions);
  pIndentTabs->value(gindent_tabs);
  pTabSize->value(gtab_size);
  pReturnParens->value(galways_return_parens);
  if(gindent_tabs)
     pTabSize->hide();
  else
     pTabSize->show();
  pIndentCode->value(gindent_code);
}
