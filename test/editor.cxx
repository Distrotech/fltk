//
// "$Id: editor.cxx,v 1.7 2000/09/07 08:52:35 spitzak Exp $"
//
// A simple text editor program for the Fast Light Tool Kit (FLTK).
//
// This program is described in Chapter 4 of the FLTK Programmer's Guide.
//
// Copyright 1998-1999 by Bill Spitzak and others.
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
// Please report all bugs and problems to "fltk-bugs@easysw.com".
//

//
// Include necessary headers...
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_ask.H>
#include <FL/fl_file_chooser.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Editor.H>


int                changed = 0;
char               filename[256] = "";
char               title[256];
Fl_Text_Buffer     *textbuf;


void save_cb();
void saveas_cb();
void find2_cb(Fl_Widget*, void*);
void replall_cb(Fl_Widget*, void*);
void replace2_cb(Fl_Widget*, void*);
void replcan_cb(Fl_Widget*, void*);

class EditorWindow : public Fl_Double_Window {
  public:
    EditorWindow(int w, int h, const char* t);
    ~EditorWindow();

    Fl_Window          *replace_dlg;
    Fl_Input           *replace_find;
    Fl_Input           *replace_with;
    Fl_Button          *replace_all;
    Fl_Return_Button   *replace_next;
    Fl_Button          *replace_cancel;

    Fl_Text_Editor     *editor;
    char               search[256];
};

EditorWindow::EditorWindow(int w, int h, const char* t) : Fl_Double_Window(w, h, t) {
  replace_dlg = new Fl_Window(300, 105, "Replace");
    replace_find = new Fl_Input(70, 10, 210, 25, "Find:");
	replace_find->clear_flag(FL_ALIGN_MASK);
    replace_find->set_flag(FL_ALIGN_LEFT);

    replace_with = new Fl_Input(70, 40, 210, 25, "Replace:");
	replace_with->clear_flag(FL_ALIGN_MASK);
    replace_with->set_flag(FL_ALIGN_LEFT);

    replace_all = new Fl_Button(10, 70, 90, 25, "Replace All");
    replace_all->callback((Fl_Callback *)replall_cb, this);

    replace_next = new Fl_Return_Button(105, 70, 120, 25, "Replace Next");
    replace_next->callback((Fl_Callback *)replace2_cb, this);

    replace_cancel = new Fl_Button(230, 70, 60, 25, "Cancel");
    replace_cancel->callback((Fl_Callback *)replcan_cb, this);
  replace_dlg->end();
  replace_dlg->set_non_modal();
  editor = 0;
  *search = (char)0;
}

EditorWindow::~EditorWindow() {
  delete replace_dlg;
}

int check_save(void) {
  if (!changed) return 1;

  if (fl_ask("The current file has not been saved.\n"
             "Would you like to save it now?"))
  {
    save_cb(); // Save the file...
    return !changed;
  } else {
    return 1;
  }
}

void load_file(char *newfile) {
  FILE *fp;
  char buffer[8192];

  fp = fopen(newfile, "r");
  if (fp != NULL) {
    // Was able to open file; let's read from it...
    strcpy(filename, newfile);
    textbuf->select(0, textbuf->length());
    textbuf->remove_selection();
    while (fgets(buffer, sizeof(buffer), fp))
      textbuf->append(buffer);

    fclose(fp);
    changed = 0;
    textbuf->call_modify_callbacks();
  } else {
    // Couldn't open file - say so...
    fl_alert("Unable to open \'%s\' for reading!", newfile);
  }
}

void save_file(char *newfile) {
  FILE *fp;

  fp = fopen(newfile, "w");
  if (fp != NULL) {
    // Was able to create file; let's write to it...
    strcpy(filename, newfile);

    const char* line;
    for (int pos = 0;
         pos < textbuf->length() &&
         ( line = textbuf->line_text(pos) );
         pos = textbuf->line_end(pos) + 1)
    {
      int r = fprintf(fp, "%s\n", line);
      free((void*)line);
      if (r < 1) {
        fl_alert("Unable to write file!");
        fclose(fp);
        return;
      }
    }

    fclose(fp);
    changed = 0;
    textbuf->call_modify_callbacks();
  } else {
    // Couldn't open file - say so...
    fl_alert("Unable to create \'%s\' for writing!");
  }
}

void copy_cb(Fl_Widget*, void* v) {
  EditorWindow* e = (EditorWindow*)v;
  Fl_Text_Editor::kf_copy(0, e->editor);
}

void cut_cb(Fl_Widget*, void* v) {
  EditorWindow* e = (EditorWindow*)v;
  Fl_Text_Editor::kf_cut(0, e->editor);
}

void delete_cb(Fl_Widget*, void*) {
  textbuf->remove_selection();
}

void find_cb(Fl_Widget* w, void* v) {
  EditorWindow* e = (EditorWindow*)v;
  const char *val;

  val = fl_input("Search String:", e->search);
  if (val != NULL) {
    // User entered a string - go find it!
    strcpy(e->search, val);
    find2_cb(w, v);
  }
}

void find2_cb(Fl_Widget* w, void* v) {
  EditorWindow* e = (EditorWindow*)v;
  if (e->search[0] == '\0') {
    // Search string is blank; get a new one...
    find_cb(w, v);
    return;
  }

  int pos = e->editor->insert_position();
  int found = textbuf->search_forward(pos, e->search, &pos);
  if (found) {
    // Found a match; select and update the position...
    textbuf->select(pos, pos+strlen(e->search));
    e->editor->insert_position(pos+strlen(e->search));
    e->editor->show_insert_position();
  }
  else fl_alert("No occurrences of \'%s\' found!", e->search);
}

void set_title(Fl_Window* w) {
  if (filename[0] == '\0') strcpy(title, "Untitled");
  else {
    char *slash;
    slash = strrchr(filename, '/');
#ifdef WIN32
    if (slash == NULL) slash = strrchr(filename, '\\');
#endif
    if (slash != NULL) strcpy(title, slash + 1);
    else strcpy(title, filename);
  }

  if (changed) strcat(title, " (modified)");

  w->label(title);
}

void changed_cb(int, int nInserted, int nDeleted,int, const char*, void* v) {
  if (nInserted || nDeleted) changed = 1;
  set_title((Fl_Window*)v);
}

void new_cb(Fl_Widget*, void*) {
  if (changed && !check_save())
    return;

  filename[0] = '\0';
  textbuf->select(0, textbuf->length());
  textbuf->remove_selection();
  changed = 0;
  textbuf->call_modify_callbacks();
}

void open_cb(Fl_Widget*, void*) {
  char *newfile;

  if (changed)
    if (!check_save()) return;

  newfile = fl_file_chooser("Open File?", "*", filename);
  if (newfile != NULL) load_file(newfile);
}

void paste_cb(Fl_Widget*, void* v) {
  EditorWindow* e = (EditorWindow*)v;
  Fl_Text_Editor::kf_paste(0, e->editor);
}

int num_windows = 0;

void close_cb(Fl_Widget*, void* v) {
  Fl_Window* w = (Fl_Window*)v;
  if (num_windows == 1 && changed && !check_save())
    return;

  w->hide();
  textbuf->remove_modify_callback(changed_cb, w);
  delete w;
  num_windows--;
}

void quit_cb(Fl_Widget*, void*) {
  if (changed && !check_save())
    return;

  exit(0);
}

void replace_cb(Fl_Widget*, void* v) {
  EditorWindow* e = (EditorWindow*)v;
  e->replace_dlg->show(e);
}

void replace2_cb(Fl_Widget*, void* v) {
  EditorWindow* e = (EditorWindow*)v;
  const char *find = e->replace_find->value();
  const char *replace = e->replace_with->value();

  if (find[0] == '\0') {
    // Search string is blank; get a new one...
    e->replace_dlg->show();
    return;
  }

  e->replace_dlg->hide();

  int pos = e->editor->insert_position();
  int found = textbuf->search_forward(pos, find, &pos);

  if (found) {
    // Found a match; update the position and replace text...
    textbuf->select(pos, pos+strlen(find));
    textbuf->remove_selection();
    textbuf->insert(pos, replace);
    textbuf->select(pos, pos+strlen(replace));
    e->editor->insert_position(pos+strlen(replace));
    e->editor->show_insert_position();
  }
  else fl_alert("No occurrences of \'%s\' found!", find);
}

void replall_cb(Fl_Widget*, void* v) {
  EditorWindow* e = (EditorWindow*)v;
  const char *find = e->replace_find->value();
  const char *replace = e->replace_with->value();

  find = e->replace_find->value();
  if (find[0] == '\0') {
    // Search string is blank; get a new one...
    e->replace_dlg->show();
    return;
  }

  e->replace_dlg->hide();

  e->editor->insert_position(0);
  int times = 0;

  // Loop through the whole string
  for (int found = 1; found;) {
    int pos = e->editor->insert_position();
    found = textbuf->search_forward(pos, find, &pos);

    if (found) {
      // Found a match; update the position and replace text...
      textbuf->select(pos, pos+strlen(find));
      textbuf->remove_selection();
      textbuf->insert(pos, replace);
      e->editor->insert_position(pos+strlen(replace));
      e->editor->show_insert_position();
      times++;
    }
  }

  if (times) fl_message("Replaced %d occurrences.", times);
  else fl_alert("No occurrences of \'%s\' found!", find);
}

void replcan_cb(Fl_Widget*, void* v) {
  EditorWindow* e = (EditorWindow*)v;
  e->replace_dlg->hide();
}

void save_cb() {
  if (filename[0] == '\0') {
    // No filename - get one!
    saveas_cb();
    return;
  }
  else save_file(filename);
}

void saveas_cb() {
  char *newfile;

  newfile = fl_file_chooser("Save File As?", "*", filename);
  if (newfile != NULL) save_file(newfile);
}

void undo_cb(Fl_Widget*, void*) {
  fl_alert("Undo not implemented!");
}

Fl_Window* new_view();

void view_cb(Fl_Widget*, void*) {
  Fl_Window* w = new_view();
  w->show();
}

Fl_Menu_Item menuitems[] = {
  { "&File", 0, 0, 0, FL_SUBMENU },
    { "&New",        0, (Fl_Callback *)new_cb },
    { "&Open...",    FL_CTRL + 'o', (Fl_Callback *)open_cb, 0, FL_MENU_DIVIDER },
    { "&Save",       FL_CTRL + 's', (Fl_Callback *)save_cb },
    { "Save &As...", FL_CTRL + FL_SHIFT + 's', (Fl_Callback *)saveas_cb, 0, FL_MENU_DIVIDER },
    { "New &View", FL_ALT + 'v', (Fl_Callback *)view_cb, 0 },
    { "&Close View", FL_CTRL + 'w', 0, 0, FL_MENU_DIVIDER },
    { "E&xit", FL_CTRL + 'q', (Fl_Callback *)quit_cb, 0 },
    { 0 },

  { "&Edit", 0, 0, 0, FL_SUBMENU },
    { "&Undo",       FL_CTRL + 'z', (Fl_Callback *)undo_cb, 0, FL_MENU_DIVIDER },
    { "Cu&t",        FL_CTRL + 'x', 0 },
    { "&Copy",       FL_CTRL + 'c', 0 },
    { "&Paste",      FL_CTRL + 'v', 0 },
    { "&Delete",     0, (Fl_Callback *)delete_cb },
    { 0 },

  { "&Search", 0, 0, 0, FL_SUBMENU },
    { "&Find...",       FL_CTRL + 'f', 0 },
    { "F&ind Again",    FL_CTRL + 'g', 0 },
    { "&Replace...",    FL_CTRL + 'r', 0 },
    { "Re&place Again", FL_CTRL + 't', 0 },
    { 0 },

  { 0 }
};

Fl_Window* new_view() {
  EditorWindow* w = new EditorWindow(512, 384, title);
    w->begin();
    Fl_Menu_Bar* m = new Fl_Menu_Bar(0, 0, 512, 30);
    m->menu(menuitems);
    m->find("&File/&Close View")->callback(close_cb, w);
    m->find("&Edit/Cu&t")->callback(cut_cb, w);
    m->find("&Edit/&Copy")->callback(copy_cb, w);
    m->find("&Edit/&Paste")->callback(paste_cb, w);
    m->find("&Search/&Find...")->callback(find_cb, w);
    m->find("&Search/F&ind Again")->callback(find2_cb, w);
    m->find("&Search/&Replace...")->callback(replace_cb, w);
    m->find("&Search/Re&place Again")->callback(replace2_cb, w);
    w->editor = new Fl_Text_Editor(0, 30, 512, 354);
    w->editor->buffer(textbuf);
    //w->editor->text_font(FL_COURIER);
  w->end();
  w->resizable(w->editor);
  w->callback((Fl_Callback *)close_cb, w);
  textbuf->add_modify_callback(changed_cb, w);
  textbuf->call_modify_callbacks();
  num_windows++;
  return w;
}

int main(int argc, char **argv) {
  textbuf = new Fl_Text_Buffer;
  if (argc > 1) load_file(argv[1]);

  Fl_Window* window = new_view();

  window->show(1, argv);
  return Fl::run();
}

//
// End of "$Id: editor.cxx,v 1.7 2000/09/07 08:52:35 spitzak Exp $".
//
