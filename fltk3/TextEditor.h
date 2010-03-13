//
// "$Id$"
//

// 123 TODO: remove stray comments
// 123 TODO: add namespace statements
// 123 TODO: replace class name, constructors and destructor
// 123 TODO: add friend statement for Twin Class
// 123 TODO: add 'compat(FLTK2)' to constructors
// 123 TODO: add twin class with all constructors
// 123 TODO: change all arguments to the FLTK2 class name
// 123 TODO: change the source code to use the new class names
// 123 TODO: add casting to return values
// 123 TODO: move all FLTK2-only functions to the FLTK3 section and implement them
// 123 TODO: remove the FLTK1 and FLTK2 sections in the headers
// 123 TODO: 

//
// "$Id: Fl_Text_Editor.H 6893 2009-09-20 19:24:24Z greg.ercolano $"
//
// Header file for Fl_Text_Editor class.
//
// Copyright 2001-2009 by Bill Spitzak and others.
// Original code Copyright Mark Edel.  Permission to distribute under
// the LGPL for the FLTK library granted by Mark Edel.
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

/* \file
   Fl_Text_Editor widget . */


#ifndef FL_TEXT_EDITOR_H
#define FL_TEXT_EDITOR_H

#include "TextDisplay.h"

// key will match in any state
#define FL_TEXT_EDITOR_ANY_STATE  (-1L)

/**
  This is the FLTK text editor widget. It allows the user to
  edit multiple lines of text and supports highlighting and
  scrolling. The buffer that is displayed in the widget is managed
  by the Fl_Text_Buffer
  class.
*/
class FL_EXPORT Fl_Text_Editor : public Fl_Text_Display {
  public:
    /** Key function binding callback type */
    typedef int (*Key_Func)(int key, Fl_Text_Editor* editor);

    /** Simple linked list associating a key/state to a function */
    struct Key_Binding {
      int          key;		///< the key pressed
      int          state;	///< the state of key modifiers
      Key_Func     function;	///< associated function
      Key_Binding* next;	///< next key binding in the list
    };

    Fl_Text_Editor(int X, int Y, int W, int H, const char* l = 0);
    ~Fl_Text_Editor() { remove_all_key_bindings(); }
    virtual int handle(int e);
    /**
	Sets the current insert mode; if non-zero, new text
	is inserted before the current cursor position. Otherwise, new
	text replaces text at the current cursor position.
    */
    void insert_mode(int b) { insert_mode_ = b; }
    /**
	Gets the current insert mode; if non-zero, new text
	is inserted before the current cursor position. Otherwise, new
	text replaces text at the current cursor position.
    */
    int insert_mode() { return insert_mode_; }

    void add_key_binding(int key, int state, Key_Func f, Key_Binding** list);
    /** Adds a key of state "state" with the function "function" */
    void add_key_binding(int key, int state, Key_Func f)
      { add_key_binding(key, state, f, &key_bindings); }
    void remove_key_binding(int key, int state, Key_Binding** list);
    /** Removes the key binding associated with the key "key" of state "state". */
    void remove_key_binding(int key, int state)
      { remove_key_binding(key, state, &key_bindings); }
    void remove_all_key_bindings(Key_Binding** list);
    /** Removes all of the key bindings associated with the text editor or list. */
    void remove_all_key_bindings() { remove_all_key_bindings(&key_bindings); }
    void add_default_key_bindings(Key_Binding** list);
    Key_Func bound_key_function(int key, int state, Key_Binding* list);
    /**  Returns the function associated with a key binding. */
    Key_Func bound_key_function(int key, int state)
      { return bound_key_function(key, state, key_bindings); }
    /**  Sets the default key function for unassigned keys. */
    void default_key_function(Key_Func f) { default_key_function_ = f; }

    // functions for the built in default bindings
    static int kf_default(int c, Fl_Text_Editor* e);
    static int kf_ignore(int c, Fl_Text_Editor* e);
    static int kf_backspace(int c, Fl_Text_Editor* e);
    static int kf_enter(int c, Fl_Text_Editor* e);
    static int kf_move(int c, Fl_Text_Editor* e);
    static int kf_shift_move(int c, Fl_Text_Editor* e);
    static int kf_ctrl_move(int c, Fl_Text_Editor* e);
    static int kf_c_s_move(int c, Fl_Text_Editor* e);
    static int kf_meta_move(int c, Fl_Text_Editor* e);
    static int kf_m_s_move(int c, Fl_Text_Editor* e);
    static int kf_home(int, Fl_Text_Editor* e);
    static int kf_end(int c, Fl_Text_Editor* e);
    static int kf_left(int c, Fl_Text_Editor* e);
    static int kf_up(int c, Fl_Text_Editor* e);
    static int kf_right(int c, Fl_Text_Editor* e);
    static int kf_down(int c, Fl_Text_Editor* e);
    static int kf_page_up(int c, Fl_Text_Editor* e);
    static int kf_page_down(int c, Fl_Text_Editor* e);
    static int kf_insert(int c, Fl_Text_Editor* e);
    static int kf_delete(int c, Fl_Text_Editor* e);
    static int kf_copy(int c, Fl_Text_Editor* e);
    static int kf_cut(int c, Fl_Text_Editor* e);
    static int kf_paste(int c, Fl_Text_Editor* e);
    static int kf_select_all(int c, Fl_Text_Editor* e);
    static int kf_undo(int c, Fl_Text_Editor* e);

  protected:
    int handle_key();
    void maybe_do_callback();

#ifndef FL_DOXYGEN
    int insert_mode_;
    Key_Binding* key_bindings;
    static Key_Binding* global_key_bindings;
    Key_Func default_key_function_;
#endif
};

#endif

//
// End of "$Id: Fl_Text_Editor.H 6893 2009-09-20 19:24:24Z greg.ercolano $".
//


/* suggested twin class
// This is the Twin Class to fltk::TextEditor
class Fl_Text_Editor : public fltk::TextEditor {
public:
  Fl_Text_Editor(int x, int t, int w, int h, const char *label=0)
  : fltk::TextEditor(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Text_Editor.H 6893 2009-09-20 19:24:24Z greg.ercolano $"
//
// Header file for Fl_Text_Editor class.
//
// Copyright 2001-2009 by Bill Spitzak and others.
// Original code Copyright Mark Edel.  Permission to distribute under
// the LGPL for the FLTK library granted by Mark Edel.
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

/* \file
   Fl_Text_Editor widget . */


#ifndef FL_TEXT_EDITOR_H
#define FL_TEXT_EDITOR_H

#include "Fl_Text_Display.H"

// key will match in any state
#define FL_TEXT_EDITOR_ANY_STATE  (-1L)

/**
  This is the FLTK text editor widget. It allows the user to
  edit multiple lines of text and supports highlighting and
  scrolling. The buffer that is displayed in the widget is managed
  by the Fl_Text_Buffer
  class.
*/
class FL_EXPORT Fl_Text_Editor : public Fl_Text_Display {
  public:
    /** Key function binding callback type */
    typedef int (*Key_Func)(int key, Fl_Text_Editor* editor);

    /** Simple linked list associating a key/state to a function */
    struct Key_Binding {
      int          key;		///< the key pressed
      int          state;	///< the state of key modifiers
      Key_Func     function;	///< associated function
      Key_Binding* next;	///< next key binding in the list
    };

    Fl_Text_Editor(int X, int Y, int W, int H, const char* l = 0);
    ~Fl_Text_Editor() { remove_all_key_bindings(); }
    virtual int handle(int e);
    /**
	Sets the current insert mode; if non-zero, new text
	is inserted before the current cursor position. Otherwise, new
	text replaces text at the current cursor position.
    */
    void insert_mode(int b) { insert_mode_ = b; }
    /**
	Gets the current insert mode; if non-zero, new text
	is inserted before the current cursor position. Otherwise, new
	text replaces text at the current cursor position.
    */
    int insert_mode() { return insert_mode_; }

    void add_key_binding(int key, int state, Key_Func f, Key_Binding** list);
    /** Adds a key of state "state" with the function "function" */
    void add_key_binding(int key, int state, Key_Func f)
      { add_key_binding(key, state, f, &key_bindings); }
    void remove_key_binding(int key, int state, Key_Binding** list);
    /** Removes the key binding associated with the key "key" of state "state". */
    void remove_key_binding(int key, int state)
      { remove_key_binding(key, state, &key_bindings); }
    void remove_all_key_bindings(Key_Binding** list);
    /** Removes all of the key bindings associated with the text editor or list. */
    void remove_all_key_bindings() { remove_all_key_bindings(&key_bindings); }
    void add_default_key_bindings(Key_Binding** list);
    Key_Func bound_key_function(int key, int state, Key_Binding* list);
    /**  Returns the function associated with a key binding. */
    Key_Func bound_key_function(int key, int state)
      { return bound_key_function(key, state, key_bindings); }
    /**  Sets the default key function for unassigned keys. */
    void default_key_function(Key_Func f) { default_key_function_ = f; }

    // functions for the built in default bindings
    static int kf_default(int c, Fl_Text_Editor* e);
    static int kf_ignore(int c, Fl_Text_Editor* e);
    static int kf_backspace(int c, Fl_Text_Editor* e);
    static int kf_enter(int c, Fl_Text_Editor* e);
    static int kf_move(int c, Fl_Text_Editor* e);
    static int kf_shift_move(int c, Fl_Text_Editor* e);
    static int kf_ctrl_move(int c, Fl_Text_Editor* e);
    static int kf_c_s_move(int c, Fl_Text_Editor* e);
    static int kf_meta_move(int c, Fl_Text_Editor* e);
    static int kf_m_s_move(int c, Fl_Text_Editor* e);
    static int kf_home(int, Fl_Text_Editor* e);
    static int kf_end(int c, Fl_Text_Editor* e);
    static int kf_left(int c, Fl_Text_Editor* e);
    static int kf_up(int c, Fl_Text_Editor* e);
    static int kf_right(int c, Fl_Text_Editor* e);
    static int kf_down(int c, Fl_Text_Editor* e);
    static int kf_page_up(int c, Fl_Text_Editor* e);
    static int kf_page_down(int c, Fl_Text_Editor* e);
    static int kf_insert(int c, Fl_Text_Editor* e);
    static int kf_delete(int c, Fl_Text_Editor* e);
    static int kf_copy(int c, Fl_Text_Editor* e);
    static int kf_cut(int c, Fl_Text_Editor* e);
    static int kf_paste(int c, Fl_Text_Editor* e);
    static int kf_select_all(int c, Fl_Text_Editor* e);
    static int kf_undo(int c, Fl_Text_Editor* e);

  protected:
    int handle_key();
    void maybe_do_callback();

#ifndef FL_DOXYGEN
    int insert_mode_;
    Key_Binding* key_bindings;
    static Key_Binding* global_key_bindings;
    Key_Func default_key_function_;
#endif
};

#endif

//
// End of "$Id: Fl_Text_Editor.H 6893 2009-09-20 19:24:24Z greg.ercolano $".
//

#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id: TextEditor.h 4899 2006-04-04 13:53:37Z fabien $"
//
// Header file for TextEditor class.
//
// Copyright 2001-2006 by Bill Spitzak and others.
// Original code Copyright Mark Edel.  Permission to distribute under
// the LGPL for the FLTK library granted by Mark Edel.
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


#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

#include "TextDisplay.h"

namespace fltk {

// key will match in any state
#define TEXT_EDITOR_ANY_STATE  (-1L)

/** TextEditor */
class FL_API TextEditor : public TextDisplay {
public:
  typedef int (*Key_Func)(int key, TextEditor* editor);

  struct Key_Binding {
    int          key;
    int          state;
    Key_Func     function;
    Key_Binding* next;
  };

  static NamedStyle* default_style;

  TextEditor(int X, int Y, int W, int H, const char* l = 0);
  ~TextEditor();

  virtual int handle(int e);

  /** Set new insert mode. true=insert, false=overstrike */
  void insert_mode(bool b) { insert_mode_ = b; }
  /** Return current insert mode */
  bool insert_mode() const { return insert_mode_; }

  void add_key_binding(int key, int state, Key_Func f, Key_Binding** list);
  void add_key_binding(int key, int state, Key_Func f)
    { add_key_binding(key, state, f, &key_bindings); }
  void remove_key_binding(int key, int state, Key_Binding** list);
  void remove_key_binding(int key, int state)
    { remove_key_binding(key, state, &key_bindings); }
  void remove_all_key_bindings(Key_Binding** list);
  void remove_all_key_bindings() { remove_all_key_bindings(&key_bindings); }
  void add_default_key_bindings(Key_Binding** list);
  Key_Func bound_key_function(int key, int state, Key_Binding* list);
  Key_Func bound_key_function(int key, int state)
    { return bound_key_function(key, state, key_bindings); }
  void default_key_function(Key_Func f) { default_key_function_ = f; }

  // functions for the built in default bindings
  static int kf_default(int c, TextEditor* e);
  static int kf_ignore(int c, TextEditor* e);
  static int kf_backspace(int c, TextEditor* e);
  static int kf_enter(int c, TextEditor* e);
  static int kf_move(int c, TextEditor* e);
  static int kf_shift_move(int c, TextEditor* e);
  static int kf_ctrl_move(int c, TextEditor* e);
  static int kf_c_s_move(int c, TextEditor* e);
  static int kf_home(int, TextEditor* e);
  static int kf_end(int c, TextEditor* e);
  static int kf_left(int c, TextEditor* e);
  static int kf_up(int c, TextEditor* e);
  static int kf_right(int c, TextEditor* e);
  static int kf_down(int c, TextEditor* e);
  static int kf_page_up(int c, TextEditor* e);
  static int kf_page_down(int c, TextEditor* e);
  static int kf_insert(int c, TextEditor* e);
  static int kf_delete(int c, TextEditor* e);
  static int kf_copy(int c, TextEditor* e);
  static int kf_cut(int c, TextEditor* e);
  static int kf_paste(int c, TextEditor* e);
  static int kf_select_all(int c, TextEditor* e);
  static int kf_undo(int c, TextEditor* e);

protected:
  int handle_key();
  void maybe_do_callback();

  bool insert_mode_;
  Key_Binding* key_bindings;
  static Key_Binding* global_key_bindings;
  Key_Func default_key_function_;
};

} /* namespace fltk */

#endif

//
// End of "$Id: TextEditor.h 4899 2006-04-04 13:53:37Z fabien $".
//


#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
