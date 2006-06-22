// generated by Fast Light User Interface Designer (fluid) version 2.0100

#ifndef coding_style_h
#define coding_style_h
extern int gbrace_style;
extern int gno_space_parens;
extern int gbrace_functions;
extern int gindent_tabs;
extern int gtab_size;
extern int galways_return_parens;
extern int gindent_code;
extern void save_coding_style();
extern void write_code_block(char *pBlock);
extern void load_coding_style();
extern const char *get_opening_brace(int is_function);
extern const char *get_indent_string(int level);
#include <fltk/Widget.h>
extern void show_coding_style_cb(fltk::Widget *, void *);
extern void write_includes_from_code(char*);
#include <fltk/Window.h>
#include <fltk/TabGroup.h>
#include <fltk/Group.h>
#include <fltk/Widget.h>
#include <fltk/RadioButton.h>
#include <fltk/CheckButton.h>
#include <fltk/ValueInput.h>
#include <fltk/Button.h>
fltk::Window* make_codingstyle_window();
void load_codingstyle_window();
#endif
