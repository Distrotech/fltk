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
// "$Id: Fl_Text_Buffer.H 6822 2009-07-04 00:24:26Z fabien $"
//
// Header file for Fl_Text_Buffer class.
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
   Fl_Text_Buffer, Fl_Text_Selection widget . */

#ifndef FL_TEXT_BUFFER_H
#define FL_TEXT_BUFFER_H

/* Maximum length in characters of a tab or control character expansion
   of a single buffer character */
#define FL_TEXT_MAX_EXP_CHAR_LEN 20

#include "FL_API.h"

/** \class Fl_Text_Selection
    This is an internal class for Fl_Text_Buffer to manage text selections.
    
    \todo	members must be documented
 */
class FL_EXPORT Fl_Text_Selection {
  friend class Fl_Text_Buffer;

  public:
    void set(int start, int end);
    void set_rectangular(int start, int end, int rectStart, int rectEnd);
    void update(int pos, int nDeleted, int nInserted);
    char rectangular() const { return mRectangular; }
    int start() const { return mStart; }
    int end() const { return mEnd; }
    int rect_start() const { return mRectStart; }
    int rect_end() const { return mRectEnd; }
    /**
       Returns a non-zero number if any text has been selected, or 0
       if no text is selected.
    */
    char selected() const { return mSelected; }
    void selected(char b) { mSelected = b; }
    int includes(int pos, int lineStartPos, int dispIndex) const;
    int position(int* start, int* end) const;
    int position(int* start, int* end, int* isRect, int* rectStart, int* rectEnd) const;


  protected:
    char mSelected;
    char mRectangular;
    int mStart;
    int mEnd;
    int mRectStart;
    int mRectEnd;
};

typedef void (*Fl_Text_Modify_Cb)(int pos, int nInserted, int nDeleted,
                                  int nRestyled, const char* deletedText,
                                  void* cbArg);
typedef void (*Fl_Text_Predelete_Cb)(int pos, int nDeleted, void* cbArg);

/**
  The Fl_Text_Buffer class is used by the Fl_Text_Display
  and Fl_Text_Editor to manage complex text data and is based upon the
  excellent NEdit text editor engine - see http://www.nedit.org/.
*/
/**
  The Fl_Text_Buffer class is used by the 
  Fl_Text_Display
  and 
  Fl_Text_Editor
  to manage complex text data and is based upon the
  excellent NEdit text editor engine - see
  http://www.nedit.org/.
*/
class FL_EXPORT Fl_Text_Buffer {
  public:
    Fl_Text_Buffer(int requestedSize = 0, int preferredGapSize = 1024);
    ~Fl_Text_Buffer();

  /**    Returns the number of characters in the buffer.  */
    int length() const { return mLength; }
    char* text() const;
    void text(const char* text);
    char* text_range(int start, int end) const;
    char character(int pos) const;
    char* text_in_rectangle(int start, int end, int rectStart, int rectEnd) const;
    void insert(int pos, const char* text);
  /**    Appends the text string to the end of the buffer.  */
    void append(const char* t) { insert(length(), t); }
    void remove(int start, int end);
    void replace(int start, int end, const char *text);
    void copy(Fl_Text_Buffer* fromBuf, int fromStart, int fromEnd, int toPos);
    int undo(int *cp=0);
    void canUndo(char flag=1);
    int insertfile(const char *file, int pos, int buflen = 128*1024);
    /**
      Appends the named file to the end of the buffer. Returns 0 on 
      success, non-zero on error (strerror() contains reason).  1 indicates 
      open for read failed (no data loaded). 2 indicates error occurred 
      while reading data (data was partially loaded).
    */
    int appendfile(const char *file, int buflen = 128*1024)
      { return insertfile(file, length(), buflen); }
    /** Loads a text file into the buffer */
    int loadfile(const char *file, int buflen = 128*1024)
      { select(0, length()); remove_selection(); return appendfile(file, buflen); }
    int outputfile(const char *file, int start, int end, int buflen = 128*1024);
    /** Saves a text file from the current buffer */
    int savefile(const char *file, int buflen = 128*1024)
      { return outputfile(file, 0, length(), buflen); }

    void insert_column(int column, int startPos, const char* text,
                       int* charsInserted, int* charsDeleted);

    void replace_rectangular(int start, int end, int rectStart, int rectEnd,
                             const char* text);

    void overlay_rectangular(int startPos, int rectStart, int rectEnd,
                             const char* text, int* charsInserted,
                             int* charsDeleted);

    void remove_rectangular(int start, int end, int rectStart, int rectEnd);
    void clear_rectangular(int start, int end, int rectStart, int rectEnd);
    /** Gets the tab width.  */
    int tab_distance() const { return mTabDist; }
    void tab_distance(int tabDist);
    void select(int start, int end);
    /** Returns a non 0 value if text has been selected, 0 otherwise */
    int selected() const { return mPrimary.selected(); }
    void unselect();
    void select_rectangular(int start, int end, int rectStart, int rectEnd);
    int selection_position(int* start, int* end);

    int selection_position(int* start, int* end, int* isRect, int* rectStart,
                           int* rectEnd);

    char* selection_text();
    void remove_selection();
    void replace_selection(const char* text);
    void secondary_select(int start, int end);
     /** Returns a non 0 value if text has been selected in the secondary
       text selection, 0 otherwise */
    int secondary_selected() { return mSecondary.selected(); }
     /** Clears any selection in the secondary text selection object. */
    void secondary_unselect();

    void secondary_select_rectangular(int start, int end, int rectStart,
                                      int rectEnd);

    int secondary_selection_position(int* start, int* end);
    int secondary_selection_position(int* start, int* end, int* isRect,
                                     int* rectStart, int* rectEnd);

    char* secondary_selection_text();
    void remove_secondary_selection();
    void replace_secondary_selection(const char* text);
    void highlight(int start, int end);
    /**
      Returns the highlighted text. When you are done with the
      text, free it using the free() function.
    */
    int highlight() { return mHighlight.selected(); }
    void unhighlight();
    void highlight_rectangular(int start, int end, int rectStart, int rectEnd);

    int highlight_position(int* start, int* end);
    int highlight_position(int* start, int* end, int* isRect, int* rectStart,
                           int* rectEnd);

    char* highlight_text();
    void add_modify_callback(Fl_Text_Modify_Cb bufModifiedCB, void* cbArg);
    void remove_modify_callback(Fl_Text_Modify_Cb bufModifiedCB, void* cbArg);

    /**
       Calls all modify callbacks that have been registered using
       the add_modify_callback()
       method.
    */
    void call_modify_callbacks() { call_modify_callbacks(0, 0, 0, 0, 0); }

    void add_predelete_callback(Fl_Text_Predelete_Cb bufPredelCB, void* cbArg);
    void remove_predelete_callback(Fl_Text_Predelete_Cb predelCB, void* cbArg);

   /**
     Calls the stored pre-delete callback procedure(s) for this buffer to update 
     the changed area(s) on the screen and any other listeners.
   */
   void call_predelete_callbacks() { call_predelete_callbacks(0, 0); }

    char* line_text(int pos) const;
    int line_start(int pos) const;
    int line_end(int pos) const;
    int word_start(int pos) const;
    int word_end(int pos) const;
    int expand_character(int pos, int indent, char *outStr) const;

    static int expand_character(char c, int indent, char* outStr, int tabDist,
                                char nullSubsChar);

    static int character_width(char c, int indent, int tabDist, char nullSubsChar);
    int count_displayed_characters(int lineStartPos, int targetPos) const;
    int skip_displayed_characters(int lineStartPos, int nChars);
    int count_lines(int startPos, int endPos) const;
    int skip_lines(int startPos, int nLines);
    int rewind_lines(int startPos, int nLines);
    int findchar_forward(int startPos, char searchChar, int* foundPos) const;
    int findchar_backward(int startPos, char searchChar, int* foundPos) const;
    int findchars_forward(int startPos, const char* searchChars, int* foundPos) const;
    int findchars_backward(int startPos, const char* searchChars, int* foundPos) const;

    int search_forward(int startPos, const char* searchString, int* foundPos,
                       int matchCase = 0) const;

    int search_backward(int startPos, const char* searchString, int* foundPos,
                        int matchCase = 0) const;

    int substitute_null_characters(char* string, int length);
    void unsubstitute_null_characters(char* string);
    /**    Returns the current nul substitution character.  */
    char null_substitution_character() const { return mNullSubsChar; }
    /**    Returns the primary selection.  */
    const Fl_Text_Selection* primary_selection() const { return &mPrimary; }
    /**    Returns the primary selection.  */
    Fl_Text_Selection* primary_selection() { return &mPrimary; }
    /**    Returns the secondary selection.  */
    const Fl_Text_Selection* secondary_selection() const { return &mSecondary; }
    /**    Returns the current highlight selection.  */
    const Fl_Text_Selection* highlight_selection() const { return &mHighlight; }

  protected:
    void call_modify_callbacks(int pos, int nDeleted, int nInserted,
                               int nRestyled, const char* deletedText) const;
    void call_predelete_callbacks(int pos, int nDeleted) const;

    int insert_(int pos, const char* text);
    void remove_(int start, int end);

    void remove_rectangular_(int start, int end, int rectStart, int rectEnd,
                             int* replaceLen, int* endPos);

    void insert_column_(int column, int startPos, const char* insText,
                        int* nDeleted, int* nInserted, int* endPos);

    void overlay_rectangular_(int startPos, int rectStart, int rectEnd,
                              const char* insText, int* nDeleted,
                              int* nInserted, int* endPos);

    void redisplay_selection(Fl_Text_Selection* oldSelection,
                             Fl_Text_Selection* newSelection) const;

    void move_gap(int pos);
    void reallocate_with_gap(int newGapStart, int newGapLen);
    char* selection_text_(Fl_Text_Selection* sel) const;
    void remove_selection_(Fl_Text_Selection* sel);
    void replace_selection_(Fl_Text_Selection* sel, const char* text);

    void rectangular_selection_boundaries(int lineStartPos, int rectStart,
                                          int rectEnd, int* selStart,
                                          int* selEnd) const;

    void update_selections(int pos, int nDeleted, int nInserted);

    Fl_Text_Selection mPrimary;   /**< highlighted areas */
    Fl_Text_Selection mSecondary; /**< highlighted areas */
    Fl_Text_Selection mHighlight; /**< highlighted areas */
    int mLength;                /**< length of the text in the buffer (the length
                                   of the buffer itself must be calculated:
                                   gapEnd - gapStart + length) */
    char* mBuf;                 /**< allocated memory where the text is stored */
    int mGapStart;              /**< points to the first character of the gap */
    int mGapEnd;                /**< points to the first char after the gap */
    // The hardware tab distance used by all displays for this buffer,
    // and used in computing offsets for rectangular selection operations.
    int mTabDist;               /**< equiv. number of characters in a tab */
    int mUseTabs;               /**< True if buffer routines are allowed to use
                                   tabs for padding in rectangular operations */
    int mNModifyProcs;          /**< number of modify-redisplay procs attached */
    Fl_Text_Modify_Cb*          /**< procedures to call when buffer is */
    mModifyProcs;               /**< modified to redisplay contents */
    void** mCbArgs;             /**< caller arguments for modifyProcs above */
    int mNPredeleteProcs;	/**< number of pre-delete procs attached */
    Fl_Text_Predelete_Cb*	/**< procedure to call before text is deleted */
	 mPredeleteProcs;	/**< from the buffer; at most one is supported. */
    void **mPredeleteCbArgs;	/**< caller argument for pre-delete proc above */
    int mCursorPosHint;         /**< hint for reasonable cursor position after
                                   a buffer modification operation */
    char mNullSubsChar;         /**< NEdit is based on C null-terminated strings,
                                   so ascii-nul characters must be substituted
                                   with something else.  This is the else, but
                                   of course, things get quite messy when you
                                   use it */
    char mCanUndo;		/**< if this buffer is used for attributes, it must
				   not do any undo calls */
    int mPreferredGapSize;	/**< the default allocation for the text gap is 1024
                                   bytes and should only be increased if frequent
                                   and large changes in buffer size are expected */
};

#endif

//
// End of "$Id: Fl_Text_Buffer.H 6822 2009-07-04 00:24:26Z fabien $".
//

/* suggested twin class
// This is the Twin Class to fltk::TextBuffer
class Fl_Text_Buffer : public fltk::TextBuffer {
public:
  Fl_Text_Buffer(int x, int t, int w, int h, const char *label=0)
  : fltk::TextBuffer(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Text_Buffer.H 6822 2009-07-04 00:24:26Z fabien $"
//
// Header file for Fl_Text_Buffer class.
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
   Fl_Text_Buffer, Fl_Text_Selection widget . */

#ifndef FL_TEXT_BUFFER_H
#define FL_TEXT_BUFFER_H

/* Maximum length in characters of a tab or control character expansion
   of a single buffer character */
#define FL_TEXT_MAX_EXP_CHAR_LEN 20

#include "Fl_Export.H"

/** \class Fl_Text_Selection
    This is an internal class for Fl_Text_Buffer to manage text selections.
    
    \todo	members must be documented
 */
class FL_EXPORT Fl_Text_Selection {
  friend class Fl_Text_Buffer;

  public:
    void set(int start, int end);
    void set_rectangular(int start, int end, int rectStart, int rectEnd);
    void update(int pos, int nDeleted, int nInserted);
    char rectangular() const { return mRectangular; }
    int start() const { return mStart; }
    int end() const { return mEnd; }
    int rect_start() const { return mRectStart; }
    int rect_end() const { return mRectEnd; }
    /**
       Returns a non-zero number if any text has been selected, or 0
       if no text is selected.
    */
    char selected() const { return mSelected; }
    void selected(char b) { mSelected = b; }
    int includes(int pos, int lineStartPos, int dispIndex) const;
    int position(int* start, int* end) const;
    int position(int* start, int* end, int* isRect, int* rectStart, int* rectEnd) const;


  protected:
    char mSelected;
    char mRectangular;
    int mStart;
    int mEnd;
    int mRectStart;
    int mRectEnd;
};

typedef void (*Fl_Text_Modify_Cb)(int pos, int nInserted, int nDeleted,
                                  int nRestyled, const char* deletedText,
                                  void* cbArg);
typedef void (*Fl_Text_Predelete_Cb)(int pos, int nDeleted, void* cbArg);

/**
  The Fl_Text_Buffer class is used by the Fl_Text_Display
  and Fl_Text_Editor to manage complex text data and is based upon the
  excellent NEdit text editor engine - see http://www.nedit.org/.
*/
/**
  The Fl_Text_Buffer class is used by the 
  Fl_Text_Display
  and 
  Fl_Text_Editor
  to manage complex text data and is based upon the
  excellent NEdit text editor engine - see
  http://www.nedit.org/.
*/
class FL_EXPORT Fl_Text_Buffer {
  public:
    Fl_Text_Buffer(int requestedSize = 0, int preferredGapSize = 1024);
    ~Fl_Text_Buffer();

  /**    Returns the number of characters in the buffer.  */
    int length() const { return mLength; }
    char* text() const;
    void text(const char* text);
    char* text_range(int start, int end) const;
    char character(int pos) const;
    char* text_in_rectangle(int start, int end, int rectStart, int rectEnd) const;
    void insert(int pos, const char* text);
  /**    Appends the text string to the end of the buffer.  */
    void append(const char* t) { insert(length(), t); }
    void remove(int start, int end);
    void replace(int start, int end, const char *text);
    void copy(Fl_Text_Buffer* fromBuf, int fromStart, int fromEnd, int toPos);
    int undo(int *cp=0);
    void canUndo(char flag=1);
    int insertfile(const char *file, int pos, int buflen = 128*1024);
    /**
      Appends the named file to the end of the buffer. Returns 0 on 
      success, non-zero on error (strerror() contains reason).  1 indicates 
      open for read failed (no data loaded). 2 indicates error occurred 
      while reading data (data was partially loaded).
    */
    int appendfile(const char *file, int buflen = 128*1024)
      { return insertfile(file, length(), buflen); }
    /** Loads a text file into the buffer */
    int loadfile(const char *file, int buflen = 128*1024)
      { select(0, length()); remove_selection(); return appendfile(file, buflen); }
    int outputfile(const char *file, int start, int end, int buflen = 128*1024);
    /** Saves a text file from the current buffer */
    int savefile(const char *file, int buflen = 128*1024)
      { return outputfile(file, 0, length(), buflen); }

    void insert_column(int column, int startPos, const char* text,
                       int* charsInserted, int* charsDeleted);

    void replace_rectangular(int start, int end, int rectStart, int rectEnd,
                             const char* text);

    void overlay_rectangular(int startPos, int rectStart, int rectEnd,
                             const char* text, int* charsInserted,
                             int* charsDeleted);

    void remove_rectangular(int start, int end, int rectStart, int rectEnd);
    void clear_rectangular(int start, int end, int rectStart, int rectEnd);
    /** Gets the tab width.  */
    int tab_distance() const { return mTabDist; }
    void tab_distance(int tabDist);
    void select(int start, int end);
    /** Returns a non 0 value if text has been selected, 0 otherwise */
    int selected() const { return mPrimary.selected(); }
    void unselect();
    void select_rectangular(int start, int end, int rectStart, int rectEnd);
    int selection_position(int* start, int* end);

    int selection_position(int* start, int* end, int* isRect, int* rectStart,
                           int* rectEnd);

    char* selection_text();
    void remove_selection();
    void replace_selection(const char* text);
    void secondary_select(int start, int end);
     /** Returns a non 0 value if text has been selected in the secondary
       text selection, 0 otherwise */
    int secondary_selected() { return mSecondary.selected(); }
     /** Clears any selection in the secondary text selection object. */
    void secondary_unselect();

    void secondary_select_rectangular(int start, int end, int rectStart,
                                      int rectEnd);

    int secondary_selection_position(int* start, int* end);
    int secondary_selection_position(int* start, int* end, int* isRect,
                                     int* rectStart, int* rectEnd);

    char* secondary_selection_text();
    void remove_secondary_selection();
    void replace_secondary_selection(const char* text);
    void highlight(int start, int end);
    /**
      Returns the highlighted text. When you are done with the
      text, free it using the free() function.
    */
    int highlight() { return mHighlight.selected(); }
    void unhighlight();
    void highlight_rectangular(int start, int end, int rectStart, int rectEnd);

    int highlight_position(int* start, int* end);
    int highlight_position(int* start, int* end, int* isRect, int* rectStart,
                           int* rectEnd);

    char* highlight_text();
    void add_modify_callback(Fl_Text_Modify_Cb bufModifiedCB, void* cbArg);
    void remove_modify_callback(Fl_Text_Modify_Cb bufModifiedCB, void* cbArg);

    /**
       Calls all modify callbacks that have been registered using
       the add_modify_callback()
       method.
    */
    void call_modify_callbacks() { call_modify_callbacks(0, 0, 0, 0, 0); }

    void add_predelete_callback(Fl_Text_Predelete_Cb bufPredelCB, void* cbArg);
    void remove_predelete_callback(Fl_Text_Predelete_Cb predelCB, void* cbArg);

   /**
     Calls the stored pre-delete callback procedure(s) for this buffer to update 
     the changed area(s) on the screen and any other listeners.
   */
   void call_predelete_callbacks() { call_predelete_callbacks(0, 0); }

    char* line_text(int pos) const;
    int line_start(int pos) const;
    int line_end(int pos) const;
    int word_start(int pos) const;
    int word_end(int pos) const;
    int expand_character(int pos, int indent, char *outStr) const;

    static int expand_character(char c, int indent, char* outStr, int tabDist,
                                char nullSubsChar);

    static int character_width(char c, int indent, int tabDist, char nullSubsChar);
    int count_displayed_characters(int lineStartPos, int targetPos) const;
    int skip_displayed_characters(int lineStartPos, int nChars);
    int count_lines(int startPos, int endPos) const;
    int skip_lines(int startPos, int nLines);
    int rewind_lines(int startPos, int nLines);
    int findchar_forward(int startPos, char searchChar, int* foundPos) const;
    int findchar_backward(int startPos, char searchChar, int* foundPos) const;
    int findchars_forward(int startPos, const char* searchChars, int* foundPos) const;
    int findchars_backward(int startPos, const char* searchChars, int* foundPos) const;

    int search_forward(int startPos, const char* searchString, int* foundPos,
                       int matchCase = 0) const;

    int search_backward(int startPos, const char* searchString, int* foundPos,
                        int matchCase = 0) const;

    int substitute_null_characters(char* string, int length);
    void unsubstitute_null_characters(char* string);
    /**    Returns the current nul substitution character.  */
    char null_substitution_character() const { return mNullSubsChar; }
    /**    Returns the primary selection.  */
    const Fl_Text_Selection* primary_selection() const { return &mPrimary; }
    /**    Returns the primary selection.  */
    Fl_Text_Selection* primary_selection() { return &mPrimary; }
    /**    Returns the secondary selection.  */
    const Fl_Text_Selection* secondary_selection() const { return &mSecondary; }
    /**    Returns the current highlight selection.  */
    const Fl_Text_Selection* highlight_selection() const { return &mHighlight; }

  protected:
    void call_modify_callbacks(int pos, int nDeleted, int nInserted,
                               int nRestyled, const char* deletedText) const;
    void call_predelete_callbacks(int pos, int nDeleted) const;

    int insert_(int pos, const char* text);
    void remove_(int start, int end);

    void remove_rectangular_(int start, int end, int rectStart, int rectEnd,
                             int* replaceLen, int* endPos);

    void insert_column_(int column, int startPos, const char* insText,
                        int* nDeleted, int* nInserted, int* endPos);

    void overlay_rectangular_(int startPos, int rectStart, int rectEnd,
                              const char* insText, int* nDeleted,
                              int* nInserted, int* endPos);

    void redisplay_selection(Fl_Text_Selection* oldSelection,
                             Fl_Text_Selection* newSelection) const;

    void move_gap(int pos);
    void reallocate_with_gap(int newGapStart, int newGapLen);
    char* selection_text_(Fl_Text_Selection* sel) const;
    void remove_selection_(Fl_Text_Selection* sel);
    void replace_selection_(Fl_Text_Selection* sel, const char* text);

    void rectangular_selection_boundaries(int lineStartPos, int rectStart,
                                          int rectEnd, int* selStart,
                                          int* selEnd) const;

    void update_selections(int pos, int nDeleted, int nInserted);

    Fl_Text_Selection mPrimary;   /**< highlighted areas */
    Fl_Text_Selection mSecondary; /**< highlighted areas */
    Fl_Text_Selection mHighlight; /**< highlighted areas */
    int mLength;                /**< length of the text in the buffer (the length
                                   of the buffer itself must be calculated:
                                   gapEnd - gapStart + length) */
    char* mBuf;                 /**< allocated memory where the text is stored */
    int mGapStart;              /**< points to the first character of the gap */
    int mGapEnd;                /**< points to the first char after the gap */
    // The hardware tab distance used by all displays for this buffer,
    // and used in computing offsets for rectangular selection operations.
    int mTabDist;               /**< equiv. number of characters in a tab */
    int mUseTabs;               /**< True if buffer routines are allowed to use
                                   tabs for padding in rectangular operations */
    int mNModifyProcs;          /**< number of modify-redisplay procs attached */
    Fl_Text_Modify_Cb*          /**< procedures to call when buffer is */
    mModifyProcs;               /**< modified to redisplay contents */
    void** mCbArgs;             /**< caller arguments for modifyProcs above */
    int mNPredeleteProcs;	/**< number of pre-delete procs attached */
    Fl_Text_Predelete_Cb*	/**< procedure to call before text is deleted */
	 mPredeleteProcs;	/**< from the buffer; at most one is supported. */
    void **mPredeleteCbArgs;	/**< caller argument for pre-delete proc above */
    int mCursorPosHint;         /**< hint for reasonable cursor position after
                                   a buffer modification operation */
    char mNullSubsChar;         /**< NEdit is based on C null-terminated strings,
                                   so ascii-nul characters must be substituted
                                   with something else.  This is the else, but
                                   of course, things get quite messy when you
                                   use it */
    char mCanUndo;		/**< if this buffer is used for attributes, it must
				   not do any undo calls */
    int mPreferredGapSize;	/**< the default allocation for the text gap is 1024
                                   bytes and should only be increased if frequent
                                   and large changes in buffer size are expected */
};

#endif

//
// End of "$Id: Fl_Text_Buffer.H 6822 2009-07-04 00:24:26Z fabien $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id: TextBuffer.h 5432 2006-09-16 02:03:04Z spitzak $"
//
// Header file for TextBuffer class.
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

#ifndef _fltk_TextBuffer_h_
#define _fltk_TextBuffer_h_

#include "FL_API.h"

namespace fltk {

/* Maximum length in characters of a tab or control character expansion
   of a single buffer character */
#define TEXT_MAX_EXP_CHAR_LEN 20

class FL_API TextSelection {
public:
  TextSelection();

  void set(int start, int end);
  void set_rectangular(int start, int end, int rectstart, int rectend);
  void update(int pos, int ndeleted, int ninserted);
  bool rectangular() const { return rectangular_; }
  int start() const	    { return start_; }
  int end() const	      { return end_; }
  int rectstart() const { return rectstart_; }
  int rectend() const   { return rectend_; }
  bool selected() const { return selected_; }
  void selected(bool b) { selected_ = b; }
  bool zerowidth() const { return zerowidth_; }
  void zerowidth(bool b) { zerowidth_ = b; }
  bool includes(int pos, int lineStartPos, int dispIndex);
  int position(int* start, int* end);
  int position(int* start, int* end, int* isrect, int* rectstart, int* rectend);

protected:
  bool selected_;	/*!< True if the selection is active */
  bool rectangular_;	/*!< True if the selection is rectangular */
  bool zerowidth_;	/*!< Width 0 selections aren't "real" selections, but
                             they can be useful when creating rectangular
                             selections from the keyboard. */
  int start_;		/*!< Pos. of start of selection, or if rectangular
                             start of line containing it. */
  int end_;		/*!< Pos. of end of selection, or if rectangular
                             end of line containing it. */
  int rectstart_;	/*!< Indent of left edge of rect. selection */
  int rectend_;		/*!< Indent of right edge of rect. selection */
};


typedef void (*Text_Modify_Cb)(	int pos, int nInserted, int nDeleted,
				int nRestyled, const char* deletedText,
				void* cbArg);

typedef void (*Text_Predelete_Cb)(int pos, int nDeleted, void* cbArg);

/** TextBuffer */
class FL_API TextBuffer {
public:
  TextBuffer(int requestedsize = 0);
  ~TextBuffer();

  int length() const { return length_; }

  const char *text();
  void text(const char* text);

  char character(int pos);
  char *text_range(int start, int end);
  char *text_in_rectangle(int start, int end, int rectStart, int rectEnd);

  void insert(int pos, const char *text);
  void append(const char *t) { insert(length(), t); }
  void remove(int start, int end);
  void replace(int start, int end, const char *text);
  void copy(TextBuffer *from_buf, int from_start, int from_end, int to_pos);

  int undo(int *cp = 0);
  void canUndo(char flag = 1);

  int insertfile(const char *file, int pos, int buflen = 128*1024);
  int appendfile(const char *file, int buflen = 128*1024)
        { return insertfile(file, length(), buflen); }
  int loadfile(const char *file, int buflen = 128*1024)
        { select(0, length()); remove_selection(); return appendfile(file, buflen); }
  int outputfile(const char *file, int start, int end, int buflen = 128*1024);
  int savefile(const char *file, int buflen = 128*1024)
        { return outputfile(file, 0, length(), buflen); }

  void insert_column(int column, int startpos, const char *text,
                     int *chars_inserted, int *chars_deleted);

  void replace_rectangular(int start, int end, int rectstart, int rectend,
                           const char *text);

  void overlay_rectangular(int startpos, int rectStart, int rectEnd,
                           const char* text, int* charsInserted,
                           int* charsDeleted);

  void remove_rectangular(int start, int end, int rectStart, int rectEnd);
  void clear_rectangular(int start, int end, int rectStart, int rectEnd);
  int tab_distance() const { return tabdist_; }
  void tab_distance(int tabDist);
  
  void select(int start, int end);
  bool selected() const { return primary_.selected(); }
  void unselect();
  
  void select_rectangular(int start, int end, int rectStart, int rectEnd);
  int selection_position(int* start, int* end);

  int selection_position(int* start, int* end, int* isRect, int* rectStart,
                         int* rectEnd);

  char *selection_text();
  void remove_selection();
  void replace_selection(const char* text);
  void secondary_select(int start, int end);
  void secondary_unselect();

  void secondary_select_rectangular(int start, int end, int rectStart,
                                    int rectEnd);

  int secondary_selection_position(int* start, int* end, int* isRect,
                                   int* rectStart, int* rectEnd);

  char *secondary_selection_text();
  void remove_secondary_selection();
  void replace_secondary_selection(const char* text);
  void highlight(int start, int end);
  void unhighlight();
  void highlight_rectangular(int start, int end, int rectStart, int rectEnd);

  int highlight_position(int* start, int* end, int* isRect, int* rectStart,
                         int* rectEnd);

  char *highlight_text();
  void add_modify_callback(Text_Modify_Cb bufModifiedCB, void* cbArg);
  void remove_modify_callback(Text_Modify_Cb bufModifiedCB, void* cbArg);

  void call_modify_callbacks() { call_modify_callbacks(0, 0, 0, 0, 0); }

  void add_predelete_callback(Text_Predelete_Cb bufPredelCB, void* cbArg);
  void remove_predelete_callback(Text_Predelete_Cb predelCB, void* cbArg);

  void call_predelete_callbacks() { call_predelete_callbacks(0, 0); }

  char* line_text(int pos);
  int line_start(int pos);
  int line_end(int pos);
  int word_start(int pos);
  int word_end(int pos);
  int expand_character(int pos, int indent, char *outStr);

  static int expand_character(char c, int indent, char* outStr, int tabDist,
                              char nullSubsChar);

  static int character_width(char c, int indent, int tabDist, char nullSubsChar);
  int count_displayed_characters(int lineStartPos, int targetPos);
  int count_displayed_characters_utf(int lineStartPos, int targetPos);
  int skip_displayed_characters(int lineStartPos, int nChars);
  int skip_displayed_characters_utf(int lineStartPos, int nChars);
  int count_lines(int startPos, int endPos);
  int skip_lines(int startPos, int nLines);
  int rewind_lines(int startPos, int nLines);
  
  bool findchar_forward(int startPos, char searchChar, int* foundPos);
  bool findchar_backward(int startPos, char searchChar, int* foundPos);

  bool findchars_forward(int startpos, const char *searchChars, int *foundPos);
  bool findchars_backward(int startpos, const char *searchChars, int *foundPos);

  bool search_forward(int startPos, const char* searchString, int* foundPos,
                      bool matchCase = false);

  bool search_backward(int startPos, const char* searchString, int* foundPos,
                       bool matchCase = false);

  char null_substitution_character() { return nullsubschar_; }
  TextSelection* primary_selection() { return &primary_; }
  TextSelection* secondary_selection() { return &secondary_; }
  TextSelection* highlight_selection() { return &highlight_; }

protected:
  void call_modify_callbacks(int pos, int nDeleted, int nInserted,
                             int nRestyled, const char* deletedText);
  void call_predelete_callbacks(int pos, int nDeleted);

  int insert_(int pos, const char* text);
  void remove_(int start, int end);

  void remove_rectangular_(int start, int end, int rectStart, int rectEnd,
                           int* replaceLen, int* endPos);

  void insert_column_(int column, int startPos, const char* insText,
                      int* nDeleted, int* nInserted, int* endPos);

  void overlay_rectangular_(int startPos, int rectStart, int rectEnd,
                            const char* insText, int* nDeleted,
                            int* nInserted, int* endPos);

  void redisplay_selection(TextSelection* oldSelection,
                           TextSelection* newSelection);

  void move_gap(int pos);
  void reallocate_with_gap(int newGapStart, int newGapLen);
  char *selection_text_(TextSelection *sel);
  void remove_selection_(TextSelection *sel);
  void replace_selection_(TextSelection *sel, const char* text);

  void rectangular_selection_boundaries(int lineStartPos, int rectStart,
                                        int rectEnd, int* selStart,
                                        int* selEnd);

  void update_selections(int pos, int nDeleted, int nInserted);

  TextSelection primary_;		/* highlighted areas */
  TextSelection secondary_;
  TextSelection highlight_;

  int length_;    /*!< length of the text in the buffer (the length
                       of the buffer itself must be calculated:
                       gapend - gapstart + length) */
  char *buf_;     /*!< allocated memory where the text is stored */
  int gapstart_;  /*!< points to the first character of the gap */
  int gapend_;    /*!< points to the first char after the gap */
  
  int tabdist_;		/*!< equiv. number of characters in a tab */
  bool usetabs_;	/*!< True if buffer routines are allowed to use
    				           tabs for padding in rectangular operations */
  
  int nmodifyprocs_;            /*!< number of modify-redisplay procs attached */
  Text_Modify_Cb *modifyprocs_;	/*   modified to redisplay contents */
  void **modifycbargs_;		  /*!< caller arguments for modifyprocs_ above */

  int npredeleteprocs_;	              /*!< number of pre-delete procs attached */
  Text_Predelete_Cb	*predeleteprocs_; /*   procedure to call before text is deleted */
 	                                    /*   from the buffer; at most one is supported. */
  void **prepeletecbargs_;	          /*!< caller argument for pre-delete proc above */
  
  int cursorposhint_; /*!< hint for reasonable cursor position after
    				               a buffer modification operation */
  char nullsubschar_;	/*!< TextBuffer is based on C null-terminated strings,
    	    	    	    	   so ascii-nul characters must be substituted
				                   with something else.  This is the else, but
				                   of course, things get quite messy when you
				                   use it */

  char mCanUndo;		  /*!< if this buffer is used for attributes, it must
				                   not do any undo calls */
};

} /* namespace fltk */

#endif

//
// End of "$Id: TextBuffer.h 5432 2006-09-16 02:03:04Z spitzak $".
//

#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
