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
// "$Id: Fl_Text_Display.H 6902 2009-09-27 11:06:56Z matt $"
//
// Header file for Fl_Text_Display class.
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
   Fl_Text_Display widget . */

#ifndef FL_TEXT_DISPLAY_H
#define FL_TEXT_DISPLAY_H

#include "draw.h"
#include "Group.h"
#include "Widget.h"
#include "Scrollbar.h"
#include "TextBuffer.h"

/**
  This is the FLTK text display widget. It allows the user to
  view multiple lines of text and supports highlighting and
  scrolling. The buffer that is displayed in the widget is managed
  by the Fl_Text_Buffer
  class.
*/
class FL_EXPORT Fl_Text_Display: public Fl_Group {
  public:
    /** text display cursor shapes enumeration */
    enum {
      NORMAL_CURSOR, CARET_CURSOR, DIM_CURSOR,
      BLOCK_CURSOR, HEAVY_CURSOR
    };

    enum {
      CURSOR_POS, CHARACTER_POS
    };

    /** drag types- they match Fl::event_clicks() so that single clicking to
        start a collection selects by character, double clicking selects by
        word and triple clicking selects by line.
    */
    enum {
      DRAG_CHAR = 0, DRAG_WORD = 1, DRAG_LINE = 2
    };
    friend void fl_text_drag_me(int pos, Fl_Text_Display* d);

    typedef void (*Unfinished_Style_Cb)(int, void *);

    /** style attributes - currently not implemented! */
    enum {
      ATTR_NONE = 0,
      ATTR_UNDERLINE = 1,
      ATTR_HIDDEN = 2
    };
    /** This structure associates the color,font,size of a string to draw
        with an attribute mask matching attr */
    struct Style_Table_Entry {
      Fl_Color	color;
      Fl_Font	font;
      int	size;
      unsigned	attr;
    };

    Fl_Text_Display(int X, int Y, int W, int H, const char *l = 0);
    ~Fl_Text_Display();

    virtual int handle(int e);
    void buffer(Fl_Text_Buffer* buf);
  /**
      Sets or gets the current text buffer associated with the text widget.
    Multiple text widgets can be associated with the same text buffer.
  */
    void buffer(Fl_Text_Buffer& buf) { buffer(&buf); }
    /**
      Gets the current text buffer associated with the text widget.
      Multiple text widgets can be associated with the same text buffer.
    */
    Fl_Text_Buffer* buffer() const { return mBuffer; }
    void redisplay_range(int start, int end);
    void scroll(int topLineNum, int horizOffset);
    void insert(const char* text);
    void overstrike(const char* text);
    void insert_position(int newPos);
    /** Gets the position of the text insertion cursor for text display */
    int insert_position() const { return mCursorPos; }
    int in_selection(int x, int y) const;
    void show_insert_position();
    int move_right();
    int move_left();
    int move_up();
    int move_down();
    int count_lines(int start, int end, bool start_pos_is_line_start) const;
    int line_start(int pos) const;
    int line_end(int pos, bool start_pos_is_line_start) const;
    int skip_lines(int startPos, int nLines, bool startPosIsLineStart);
    int rewind_lines(int startPos, int nLines);
    void next_word(void);
    void previous_word(void);
    void show_cursor(int b = 1);
    /**    Hides the text cursor */
    void hide_cursor() { show_cursor(0); }
    void cursor_style(int style);
    /**    Sets or gets the text cursor color.  */
    Fl_Color cursor_color() const {return mCursor_color;}
    /**    Sets or gets the text cursor color.  */
    void cursor_color(Fl_Color n) {mCursor_color = n;}
    /**    Sets or gets the width/height of the scrollbars.  */
    int scrollbar_width() const { return scrollbar_width_; }
    /**    Sets or gets the width/height of the scrollbars.  */
    void scrollbar_width(int W) { scrollbar_width_ = W; }
    /**    Gets the scrollbar alignment type */
    Fl_Align scrollbar_align() const { return scrollbar_align_; }
    /**    Sets the scrollbar alignment type */
    void scrollbar_align(Fl_Align a) { scrollbar_align_ = a; }
    /**    Moves the insert position to the beginning of the current word.  */
    int word_start(int pos) const { return buffer()->word_start(pos); }
    /**    Moves the insert position to the end of the current word.  */
    int word_end(int pos) const { return buffer()->word_end(pos); }

    
    void highlight_data(Fl_Text_Buffer *styleBuffer,
                        const Style_Table_Entry *styleTable,
                        int nStyles, char unfinishedStyle,
                        Unfinished_Style_Cb unfinishedHighlightCB,
                        void *cbArg);

    int position_style(int lineStartPos, int lineLen, int lineIndex,
                       int dispIndex) const;
    /** \todo FIXME : get set methods pointing on shortcut_ 
     have no effects as shortcut_ is unused in this class and derived! */
    int shortcut() const {return shortcut_;}
    /** \todo FIXME : get set methods pointing on shortcut_ 
     have no effects as shortcut_ is unused in this class and derived! */
    void shortcut(int s) {shortcut_ = s;}

    /**    Gets the default font used when drawing text in the widget.  */
    Fl_Font textfont() const {return textfont_;}
    /**    Sets the default font used when drawing text in the widget.  */
    void textfont(Fl_Font s) {textfont_ = s;}
    /**    Gets the default size of text in the widget.  */
    Fl_Fontsize textsize() const {return textsize_;}
    /**    Sets the default size of text in the widget.  */
    void textsize(Fl_Fontsize s) {textsize_ = s;}
    /**    Gets the default color of text in the widget.  */
    Fl_Color textcolor() const {return textcolor_;}
    /**    Sets the default color of text in the widget.  */
    void textcolor(Fl_Color n) {textcolor_ = n;}

    int wrapped_column(int row, int column) const;
    int wrapped_row(int row) const;
    void wrap_mode(int wrap, int wrap_margin);

    virtual void resize(int X, int Y, int W, int H);

  protected:
    // Most (all?) of this stuff should only be called from resize() or
    // draw().
    // Anything with "vline" indicates thats it deals with currently
    // visible lines.

    virtual void draw();
    void draw_text(int X, int Y, int W, int H);
    void draw_range(int start, int end);
    void draw_cursor(int, int);

    void draw_string(int style, int x, int y, int toX, const char *string,
                     int nChars);

    void draw_vline(int visLineNum, int leftClip, int rightClip,
                    int leftCharIndex, int rightCharIndex);

    void draw_line_numbers(bool clearAll);

    void clear_rect(int style, int x, int y, int width, int height);
    void display_insert();

    void offset_line_starts(int newTopLineNum);

    void calc_line_starts(int startLine, int endLine);

    void update_line_starts(int pos, int charsInserted, int charsDeleted,
                            int linesInserted, int linesDeleted, int *scrolled);

    void calc_last_char();

    int position_to_line( int pos, int* lineNum ) const;
    int string_width(const char* string, int length, int style) const;

    static void scroll_timer_cb(void*);

    static void buffer_predelete_cb(int pos, int nDeleted, void* cbArg);
    static void buffer_modified_cb(int pos, int nInserted, int nDeleted,
                                   int nRestyled, const char* deletedText,
                                   void* cbArg);

    static void h_scrollbar_cb(Fl_Scrollbar* w, Fl_Text_Display* d);
    static void v_scrollbar_cb( Fl_Scrollbar* w, Fl_Text_Display* d);
    void update_v_scrollbar();
    void update_h_scrollbar();
    int measure_vline(int visLineNum) const;
    int longest_vline() const;
    int empty_vlines() const;
    int vline_length(int visLineNum) const;
    int xy_to_position(int x, int y, int PosType = CHARACTER_POS) const;

    void xy_to_rowcol(int x, int y, int* row, int* column,
                      int PosType = CHARACTER_POS) const;

    int position_to_xy(int pos, int* x, int* y) const;
    void maintain_absolute_top_line_number(int state);
    int get_absolute_top_line_number() const;
    void absolute_top_line_number(int oldFirstChar);
    int maintaining_absolute_top_line_number() const;
    void reset_absolute_top_line_number();
    int position_to_linecol(int pos, int* lineNum, int* column) const;
    void scroll_(int topLineNum, int horizOffset);

    void extend_range_for_styles(int* start, int* end);

    void find_wrap_range(const char *deletedText, int pos, int nInserted,
                           int nDeleted, int *modRangeStart, int *modRangeEnd,
                           int *linesInserted, int *linesDeleted);
    void measure_deleted_lines(int pos, int nDeleted);
    void wrapped_line_counter(Fl_Text_Buffer *buf, int startPos, int maxPos,
                               int maxLines, bool startPosIsLineStart,
                               int styleBufOffset, int *retPos, int *retLines,
                               int *retLineStart, int *retLineEnd,
                               bool countLastLineMissingNewLine = true) const;
    void find_line_end(int pos, bool start_pos_is_line_start, int *lineEnd,
                         int *nextLineStart) const;
    int measure_proportional_character(char c, int colNum, int pos) const;
    int wrap_uses_character(int lineEndPos) const;
    int range_touches_selection(const Fl_Text_Selection *sel, int rangeStart,
                                 int rangeEnd) const;
#ifndef FL_DOXYGEN
    int damage_range1_start, damage_range1_end;
    int damage_range2_start, damage_range2_end;
    int mCursorPos;
    int mCursorOn;
    int mCursorOldY;		/* Y pos. of cursor for blanking */
    int mCursorToHint;		/* Tells the buffer modified callback
                                   where to move the cursor, to reduce
                                   the number of redraw calls */
    int mCursorStyle;           /* One of enum cursorStyles above */
    int mCursorPreferredCol;    /* Column for vert. cursor movement */
    int mNVisibleLines;         /* # of visible (displayed) lines */
    int mNBufferLines;          /* # of newlines in the buffer */
    Fl_Text_Buffer* mBuffer;    /* Contains text to be displayed */
    Fl_Text_Buffer* mStyleBuffer; /* Optional parallel buffer containing
                                     color and font information */
    int mFirstChar, mLastChar;  /* Buffer positions of first and last
                                   displayed character (lastChar points
                                   either to a newline or one character
                                   beyond the end of the buffer) */
    int mContinuousWrap;     	  /* Wrap long lines when displaying */
    int mWrapMargin; 	    	  /* Margin in # of char positions for
    	    	    	    	    	   wrapping in continuousWrap mode */
    int* mLineStarts;
    int mTopLineNum;            /* Line number of top displayed line
                                   of file (first line of file is 1) */
    int mAbsTopLineNum;			/* In continuous wrap mode, the line
    					   number of the top line if the text
					   were not wrapped (note that this is
					   only maintained as needed). */
    int mNeedAbsTopLineNum;	/* Externally settable flag to continue
    					   maintaining absTopLineNum even if
					   it isn't needed for line # display */
    int mHorizOffset;           /* Horizontal scroll pos. in pixels */
    int mTopLineNumHint;        /* Line number of top displayed line
                                   of file (first line of file is 1) */
    int mHorizOffsetHint;       /* Horizontal scroll pos. in pixels */
    int mNStyles;               /* Number of entries in styleTable */
    const Style_Table_Entry *mStyleTable; /* Table of fonts and colors for
                                   coloring/syntax-highlighting */
    char mUnfinishedStyle;      /* Style buffer entry which triggers
                                   on-the-fly reparsing of region */
    Unfinished_Style_Cb mUnfinishedHighlightCB; /* Callback to parse "unfinished" */
                                /* regions */
    void* mHighlightCBArg;      /* Arg to unfinishedHighlightCB */

    int mMaxsize;

    int mFixedFontWidth;        /* Font width if all current fonts are
                                   fixed and match in width, else -1 */
    int mSuppressResync;		/* Suppress resynchronization of line
                                           starts during buffer updates */
    int mNLinesDeleted;			/* Number of lines deleted during
					   buffer modification (only used
				           when resynchronization is suppressed) */
    int mModifyingTabDistance;	/* Whether tab distance is being
    					   modified */

    Fl_Color mCursor_color;

    Fl_Scrollbar* mHScrollBar;
    Fl_Scrollbar* mVScrollBar;
    int scrollbar_width_;
    Fl_Align scrollbar_align_;
    int dragPos, dragType, dragging;
    int display_insert_position_hint;
    struct { int x, y, w, h; } text_area;

    int shortcut_;

    Fl_Font textfont_;
    Fl_Fontsize textsize_;
    Fl_Color textcolor_;

	 // The following are not presently used from the original NEdit code,
	 // but are being put here so that future versions of Fl_Text_Display
	 // can implement line numbers without breaking binary compatibility.
    int mLineNumLeft, mLineNumWidth;
				/* Line number margin and width */
#endif
};

#endif

//
// End of "$Id: Fl_Text_Display.H 6902 2009-09-27 11:06:56Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::TextDisplay
class Fl_Text_Display : public fltk::TextDisplay {
public:
  Fl_Text_Display(int x, int t, int w, int h, const char *label=0)
  : fltk::TextDisplay(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_Text_Display.H 6902 2009-09-27 11:06:56Z matt $"
//
// Header file for Fl_Text_Display class.
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
   Fl_Text_Display widget . */

#ifndef FL_TEXT_DISPLAY_H
#define FL_TEXT_DISPLAY_H

#include "fl_draw.H"
#include "Fl_Group.H"
#include "Fl_Widget.H"
#include "Fl_Scrollbar.H"
#include "Fl_Text_Buffer.H"

/**
  This is the FLTK text display widget. It allows the user to
  view multiple lines of text and supports highlighting and
  scrolling. The buffer that is displayed in the widget is managed
  by the Fl_Text_Buffer
  class.
*/
class FL_EXPORT Fl_Text_Display: public Fl_Group {
  public:
    /** text display cursor shapes enumeration */
    enum {
      NORMAL_CURSOR, CARET_CURSOR, DIM_CURSOR,
      BLOCK_CURSOR, HEAVY_CURSOR
    };

    enum {
      CURSOR_POS, CHARACTER_POS
    };

    /** drag types- they match Fl::event_clicks() so that single clicking to
        start a collection selects by character, double clicking selects by
        word and triple clicking selects by line.
    */
    enum {
      DRAG_CHAR = 0, DRAG_WORD = 1, DRAG_LINE = 2
    };
    friend void fl_text_drag_me(int pos, Fl_Text_Display* d);

    typedef void (*Unfinished_Style_Cb)(int, void *);

    /** style attributes - currently not implemented! */
    enum {
      ATTR_NONE = 0,
      ATTR_UNDERLINE = 1,
      ATTR_HIDDEN = 2
    };
    /** This structure associates the color,font,size of a string to draw
        with an attribute mask matching attr */
    struct Style_Table_Entry {
      Fl_Color	color;
      Fl_Font	font;
      int	size;
      unsigned	attr;
    };

    Fl_Text_Display(int X, int Y, int W, int H, const char *l = 0);
    ~Fl_Text_Display();

    virtual int handle(int e);
    void buffer(Fl_Text_Buffer* buf);
  /**
      Sets or gets the current text buffer associated with the text widget.
    Multiple text widgets can be associated with the same text buffer.
  */
    void buffer(Fl_Text_Buffer& buf) { buffer(&buf); }
    /**
      Gets the current text buffer associated with the text widget.
      Multiple text widgets can be associated with the same text buffer.
    */
    Fl_Text_Buffer* buffer() const { return mBuffer; }
    void redisplay_range(int start, int end);
    void scroll(int topLineNum, int horizOffset);
    void insert(const char* text);
    void overstrike(const char* text);
    void insert_position(int newPos);
    /** Gets the position of the text insertion cursor for text display */
    int insert_position() const { return mCursorPos; }
    int in_selection(int x, int y) const;
    void show_insert_position();
    int move_right();
    int move_left();
    int move_up();
    int move_down();
    int count_lines(int start, int end, bool start_pos_is_line_start) const;
    int line_start(int pos) const;
    int line_end(int pos, bool start_pos_is_line_start) const;
    int skip_lines(int startPos, int nLines, bool startPosIsLineStart);
    int rewind_lines(int startPos, int nLines);
    void next_word(void);
    void previous_word(void);
    void show_cursor(int b = 1);
    /**    Hides the text cursor */
    void hide_cursor() { show_cursor(0); }
    void cursor_style(int style);
    /**    Sets or gets the text cursor color.  */
    Fl_Color cursor_color() const {return mCursor_color;}
    /**    Sets or gets the text cursor color.  */
    void cursor_color(Fl_Color n) {mCursor_color = n;}
    /**    Sets or gets the width/height of the scrollbars.  */
    int scrollbar_width() const { return scrollbar_width_; }
    /**    Sets or gets the width/height of the scrollbars.  */
    void scrollbar_width(int W) { scrollbar_width_ = W; }
    /**    Gets the scrollbar alignment type */
    Fl_Align scrollbar_align() const { return scrollbar_align_; }
    /**    Sets the scrollbar alignment type */
    void scrollbar_align(Fl_Align a) { scrollbar_align_ = a; }
    /**    Moves the insert position to the beginning of the current word.  */
    int word_start(int pos) const { return buffer()->word_start(pos); }
    /**    Moves the insert position to the end of the current word.  */
    int word_end(int pos) const { return buffer()->word_end(pos); }

    
    void highlight_data(Fl_Text_Buffer *styleBuffer,
                        const Style_Table_Entry *styleTable,
                        int nStyles, char unfinishedStyle,
                        Unfinished_Style_Cb unfinishedHighlightCB,
                        void *cbArg);

    int position_style(int lineStartPos, int lineLen, int lineIndex,
                       int dispIndex) const;
    /** \todo FIXME : get set methods pointing on shortcut_ 
     have no effects as shortcut_ is unused in this class and derived! */
    int shortcut() const {return shortcut_;}
    /** \todo FIXME : get set methods pointing on shortcut_ 
     have no effects as shortcut_ is unused in this class and derived! */
    void shortcut(int s) {shortcut_ = s;}

    /**    Gets the default font used when drawing text in the widget.  */
    Fl_Font textfont() const {return textfont_;}
    /**    Sets the default font used when drawing text in the widget.  */
    void textfont(Fl_Font s) {textfont_ = s;}
    /**    Gets the default size of text in the widget.  */
    Fl_Fontsize textsize() const {return textsize_;}
    /**    Sets the default size of text in the widget.  */
    void textsize(Fl_Fontsize s) {textsize_ = s;}
    /**    Gets the default color of text in the widget.  */
    Fl_Color textcolor() const {return textcolor_;}
    /**    Sets the default color of text in the widget.  */
    void textcolor(Fl_Color n) {textcolor_ = n;}

    int wrapped_column(int row, int column) const;
    int wrapped_row(int row) const;
    void wrap_mode(int wrap, int wrap_margin);

    virtual void resize(int X, int Y, int W, int H);

  protected:
    // Most (all?) of this stuff should only be called from resize() or
    // draw().
    // Anything with "vline" indicates thats it deals with currently
    // visible lines.

    virtual void draw();
    void draw_text(int X, int Y, int W, int H);
    void draw_range(int start, int end);
    void draw_cursor(int, int);

    void draw_string(int style, int x, int y, int toX, const char *string,
                     int nChars);

    void draw_vline(int visLineNum, int leftClip, int rightClip,
                    int leftCharIndex, int rightCharIndex);

    void draw_line_numbers(bool clearAll);

    void clear_rect(int style, int x, int y, int width, int height);
    void display_insert();

    void offset_line_starts(int newTopLineNum);

    void calc_line_starts(int startLine, int endLine);

    void update_line_starts(int pos, int charsInserted, int charsDeleted,
                            int linesInserted, int linesDeleted, int *scrolled);

    void calc_last_char();

    int position_to_line( int pos, int* lineNum ) const;
    int string_width(const char* string, int length, int style) const;

    static void scroll_timer_cb(void*);

    static void buffer_predelete_cb(int pos, int nDeleted, void* cbArg);
    static void buffer_modified_cb(int pos, int nInserted, int nDeleted,
                                   int nRestyled, const char* deletedText,
                                   void* cbArg);

    static void h_scrollbar_cb(Fl_Scrollbar* w, Fl_Text_Display* d);
    static void v_scrollbar_cb( Fl_Scrollbar* w, Fl_Text_Display* d);
    void update_v_scrollbar();
    void update_h_scrollbar();
    int measure_vline(int visLineNum) const;
    int longest_vline() const;
    int empty_vlines() const;
    int vline_length(int visLineNum) const;
    int xy_to_position(int x, int y, int PosType = CHARACTER_POS) const;

    void xy_to_rowcol(int x, int y, int* row, int* column,
                      int PosType = CHARACTER_POS) const;

    int position_to_xy(int pos, int* x, int* y) const;
    void maintain_absolute_top_line_number(int state);
    int get_absolute_top_line_number() const;
    void absolute_top_line_number(int oldFirstChar);
    int maintaining_absolute_top_line_number() const;
    void reset_absolute_top_line_number();
    int position_to_linecol(int pos, int* lineNum, int* column) const;
    void scroll_(int topLineNum, int horizOffset);

    void extend_range_for_styles(int* start, int* end);

    void find_wrap_range(const char *deletedText, int pos, int nInserted,
                           int nDeleted, int *modRangeStart, int *modRangeEnd,
                           int *linesInserted, int *linesDeleted);
    void measure_deleted_lines(int pos, int nDeleted);
    void wrapped_line_counter(Fl_Text_Buffer *buf, int startPos, int maxPos,
                               int maxLines, bool startPosIsLineStart,
                               int styleBufOffset, int *retPos, int *retLines,
                               int *retLineStart, int *retLineEnd,
                               bool countLastLineMissingNewLine = true) const;
    void find_line_end(int pos, bool start_pos_is_line_start, int *lineEnd,
                         int *nextLineStart) const;
    int measure_proportional_character(char c, int colNum, int pos) const;
    int wrap_uses_character(int lineEndPos) const;
    int range_touches_selection(const Fl_Text_Selection *sel, int rangeStart,
                                 int rangeEnd) const;
#ifndef FL_DOXYGEN
    int damage_range1_start, damage_range1_end;
    int damage_range2_start, damage_range2_end;
    int mCursorPos;
    int mCursorOn;
    int mCursorOldY;		/* Y pos. of cursor for blanking */
    int mCursorToHint;		/* Tells the buffer modified callback
                                   where to move the cursor, to reduce
                                   the number of redraw calls */
    int mCursorStyle;           /* One of enum cursorStyles above */
    int mCursorPreferredCol;    /* Column for vert. cursor movement */
    int mNVisibleLines;         /* # of visible (displayed) lines */
    int mNBufferLines;          /* # of newlines in the buffer */
    Fl_Text_Buffer* mBuffer;    /* Contains text to be displayed */
    Fl_Text_Buffer* mStyleBuffer; /* Optional parallel buffer containing
                                     color and font information */
    int mFirstChar, mLastChar;  /* Buffer positions of first and last
                                   displayed character (lastChar points
                                   either to a newline or one character
                                   beyond the end of the buffer) */
    int mContinuousWrap;     	  /* Wrap long lines when displaying */
    int mWrapMargin; 	    	  /* Margin in # of char positions for
    	    	    	    	    	   wrapping in continuousWrap mode */
    int* mLineStarts;
    int mTopLineNum;            /* Line number of top displayed line
                                   of file (first line of file is 1) */
    int mAbsTopLineNum;			/* In continuous wrap mode, the line
    					   number of the top line if the text
					   were not wrapped (note that this is
					   only maintained as needed). */
    int mNeedAbsTopLineNum;	/* Externally settable flag to continue
    					   maintaining absTopLineNum even if
					   it isn't needed for line # display */
    int mHorizOffset;           /* Horizontal scroll pos. in pixels */
    int mTopLineNumHint;        /* Line number of top displayed line
                                   of file (first line of file is 1) */
    int mHorizOffsetHint;       /* Horizontal scroll pos. in pixels */
    int mNStyles;               /* Number of entries in styleTable */
    const Style_Table_Entry *mStyleTable; /* Table of fonts and colors for
                                   coloring/syntax-highlighting */
    char mUnfinishedStyle;      /* Style buffer entry which triggers
                                   on-the-fly reparsing of region */
    Unfinished_Style_Cb mUnfinishedHighlightCB; /* Callback to parse "unfinished" */
                                /* regions */
    void* mHighlightCBArg;      /* Arg to unfinishedHighlightCB */

    int mMaxsize;

    int mFixedFontWidth;        /* Font width if all current fonts are
                                   fixed and match in width, else -1 */
    int mSuppressResync;		/* Suppress resynchronization of line
                                           starts during buffer updates */
    int mNLinesDeleted;			/* Number of lines deleted during
					   buffer modification (only used
				           when resynchronization is suppressed) */
    int mModifyingTabDistance;	/* Whether tab distance is being
    					   modified */

    Fl_Color mCursor_color;

    Fl_Scrollbar* mHScrollBar;
    Fl_Scrollbar* mVScrollBar;
    int scrollbar_width_;
    Fl_Align scrollbar_align_;
    int dragPos, dragType, dragging;
    int display_insert_position_hint;
    struct { int x, y, w, h; } text_area;

    int shortcut_;

    Fl_Font textfont_;
    Fl_Fontsize textsize_;
    Fl_Color textcolor_;

	 // The following are not presently used from the original NEdit code,
	 // but are being put here so that future versions of Fl_Text_Display
	 // can implement line numbers without breaking binary compatibility.
    int mLineNumLeft, mLineNumWidth;
				/* Line number margin and width */
#endif
};

#endif

//
// End of "$Id: Fl_Text_Display.H 6902 2009-09-27 11:06:56Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id: TextDisplay.h 5432 2006-09-16 02:03:04Z spitzak $"
//
// Header file for TextDisplay class.
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

#ifndef _fltk_TextDisplay_h_
#define _fltk_TextDisplay_h_

#include "draw.h"
#include "Group.h"
#include "Widget.h"
#include "Scrollbar.h"
#include "TextBuffer.h"
#include "Font.h"

namespace fltk {

typedef void (*UnfinishedStyleCb)(int, void *);

/** TextDisplay */
class FL_API TextDisplay: public Group {
public:
  enum {
    NORMAL_CURSOR, CARET_CURSOR, DIM_CURSOR,
    BLOCK_CURSOR, HEAVY_CURSOR
  };

  enum {
    CURSOR_POS, CHARACTER_POS
  };

  // drag types- they match fltk::event_clicks() so that single clicking to
  // start a collection selects by character, double clicking selects by
  // word and triple clicking selects by line.
  enum {
    DRAG_CHAR = 0, DRAG_WORD = 1, DRAG_LINE = 2
  };

  enum {
    ATTR_NONE = 0,
    ATTR_UNDERLINE = 1,
    ATTR_HIDDEN = 2
  };

  struct StyleTableEntry {
    Color	color;
    Font        *font;
    float       size;
    unsigned	attr;
  };

  TextDisplay(int X, int Y, int W, int H, const char *l = 0);
  ~TextDisplay();

  // Emulation of Input widget:
  int size() const { return buffer_->length(); }
  const char* text() const { return buffer_->text(); }
  void text( const char* v) { buffer_->text(v); }
  void static_text( const char* v) { buffer_->text(v); }
  char at(int i) const { return buffer_->character(i); }

  virtual int handle(int e);
  virtual void draw();
  virtual void layout();

  /** Associate 'buf' with display */
  void buffer(TextBuffer* buf);
  /** Associate 'buf' with display */
  void buffer(TextBuffer& buf) { buffer(&buf); }

  /** Return attached buffer */
  TextBuffer* buffer() { return buffer_; }
  /** Return attached buffer */
  const TextBuffer* buffer() const { return buffer_; }

  /** Append text to the end of the buffer */
  void append(const char *text) { insert_position(buffer()->length()); insert(text); }
  /** Insert text to current cursor position */
  void insert(const char *text);
  /** Overstrike text from current cursor position */
  void overstrike(const char *text);

  /** Set new cursor position */
  void insert_position(int newPos);
  /** Return current cursor position */
  int insert_position() const { return cursor_pos_; }
  /** Make cursor position visible in screen */
  void show_insert_position();

  /** Show cursor */
  void show_cursor(bool b = true);
  /** Hide cursor */
  void hide_cursor() { show_cursor(false); }
  /** Return cursor visibility state */
  bool cursor_on() const { return cursor_on_; }
  /** Set cursor style */
  void cursor_style(int style);

  /** Return cursor color */
  Color cursor_color() const { return cursor_color_;}
  /** Set cursor color */
  void cursor_color(Color n) { cursor_color_ = n; }

  /** Return begining of the word where 'pos' is located */
  int word_start(int pos) { return buffer()->word_start(pos); }
  /** Return end of the word where 'pos' is located */
  int word_end(int pos) { return buffer()->word_end(pos); }
  /** Go to next word */
  void next_word(void);
  /** Go to previous word */
  void previous_word(void);

  /** Set wrapping mode. wrap_margin is width to wrap at, zero means use w() */
  void wrap_mode(bool wrap, int wrap_margin=0);

  /** Set line number area width */
  void linenumber_width(int width);
  /** Return line number area width */
  int linenumber_width() const { return linenumwidth_; }

  /** Set new highlight data */
  void highlight_data(TextBuffer *styleBuffer,
		      StyleTableEntry *styleTable,
		      int nStyles, char unfinishedStyle,
		      UnfinishedStyleCb unfinishedHighlightCB,
		      void *cbArg);

  /** Move cursor right */
  bool move_right();
  /** Move cursor left */
  bool move_left();
  /** Move cursor down */
  bool move_up();
  /** Move cursor down */
  bool move_down();

  /** Redisplay text */
  void redisplay_range(int start, int end);

  /** Scroll to new position */
  void scroll(int topLineNum, int horizOffset);

  /** Returns true if position is inside selection */
  bool in_selection(int x, int y);

  /** Returns begining of the line where 'pos' is located */
  int line_start(int pos);

  /** Returns end of the line where 'pos' is located */
  int line_end(int pos, bool start_pos_is_line_start = false);

  /** Return number of visible lines */
  int visible_lines() const { return visiblelines_cnt_; }

  /** Return current visible topline */
  int top_line() const { return topline_num_; }

  /** Return current horizontal offset */
  int hor_offset() const { return horiz_offset_; }

  /** Find start of the next character, starting from 'pos'
   * If 'pos' points to start of character already, it is returned.
   * This is mainly used with UTF-8 strings
   */
  int find_next_char(int pos);

  /** Find start of the previous character, starting from 'pos'
   * If 'pos' points to start of character already, it is returned.
   * This is mainly used with UTF-8 strings
   */
  int find_prev_char(int pos);

  int xy_to_position(int X, int Y, int PosType = CHARACTER_POS);

  void xy_to_rowcol(int X, int Y, int *row, int *column, int PosType = CHARACTER_POS);

  bool position_to_xy(int pos, int *X, int *Y);

  int total_lines() {return count_lines(0, buffer_->length(), true);}

protected:
  void draw_text(int X, int Y, int W, int H);
  void draw_range(int start, int end);
  void draw_cursor(int, int);

  void draw_string(int style, int x, int y, int toX, const char *string,
		   int nChars);

  void draw_vline(int visLineNum, int leftClip, int rightClip,
		  int leftCharIndex, int rightCharIndex);

  void draw_line_numbers(bool clearAll);

  void clear_rect(int style, int x, int y, int width, int height);
  void display_insert();

  int count_lines(int start, int end, bool start_pos_is_line_start);
  int skip_lines(int startPos, int nLines, bool startPosIsLineStart);
  int rewind_lines(int startPos, int nLines);
  int position_style(int lineStartPos, int lineLen, int lineIndex, int dispIndex);

  int wrapped_column(int row, int column);
  int wrapped_row(int row);

  void offset_line_starts(int newTopLineNum);

  void calc_line_starts(int startLine, int endLine);

  void update_line_starts(int pos, int charsInserted, int charsDeleted,
			  int linesInserted, int linesDeleted, bool *scrolled);

  void calc_last_char();

  bool position_to_line(int pos, int* lineNum);
  int string_width(const char* string, int length, int style);

  static void buffer_predelete_cb(int pos, int nDeleted, void* cbArg);
  static void buffer_modified_cb(int pos, int nInserted, int nDeleted,
				 int nRestyled, const char* deletedText,
				 void* cbArg);

  static void h_scrollbar_cb(Scrollbar* w, TextDisplay* d);
  static void v_scrollbar_cb( Scrollbar* w, TextDisplay* d);
  void update_v_scrollbar();
  void update_h_scrollbar(int longestvline = 0);

  void blank_cursor_protrusions();
  int measure_vline(int visLineNum);
  int longest_vline();
  int empty_vlines();
  int vline_length(int visLineNum);

  void maintain_absolute_top_line_number(bool state);
  int get_absolute_top_line_number();
  void absolute_top_line_number(int oldFirstChar);
  int maintaining_absolute_top_line_number();
  void reset_absolute_top_line_number();
  bool position_to_linecol(int pos, int *lineNum, int *column);
  void scroll_(int topLineNum, int horizOffset);

  void extend_range_for_styles(int* start, int* end);

  void find_wrap_range(const char *deletedText, int pos, int nInserted,
			 int nDeleted, int *modRangeStart, int *modRangeEnd,
			 int *linesInserted, int *linesDeleted);
  void measure_deleted_lines(int pos, int nDeleted);
  void wrapped_line_counter(TextBuffer *buf, int startPos, int maxPos,
			     int maxLines, bool startPosIsLineStart,
			     int styleBufOffset, int *retPos, int *retLines,
			     int *retLineStart, int *retLineEnd,
			     bool countLastLineMissingNewLine = true);
  void find_line_end(int pos, bool start_pos_is_line_start, int *lineEnd,
		       int *nextLineStart);
  int measure_proportional_character(TextBuffer *buf, int bufpos, int colNum, int pos);
  int wrap_uses_character(int lineEndPos);
  int range_touches_selection(TextSelection *sel, int rangeStart, int rangeEnd);
  void text_drag_me(int pos);

  int damage_range1_start, damage_range1_end;
  int damage_range2_start, damage_range2_end;

  int cursor_pos_;
  bool cursor_on_;
  int cursor_oldx_;           /* X pos. of cursor for blanking */
  int cursor_oldy_;           /* Y pos. of cursor for blanking */
  int cursor_hint_;           /* Tells the buffer modified callback
				 where to move the cursor, to reduce
				 the number of redraw calls */
  int cursor_style_;          /* One of enum cursorStyles above */
  int cursor_preferred_col_;  /* Column for vert. cursor movement */
  int visiblelines_cnt_;      /* # of visible (displayed) lines */
  int bufferlines_cnt_;       /* # of newlines in the buffer */
  TextBuffer *buffer_;        /* Contains text to be displayed */
  TextBuffer *stylebuffer_;   /* Optional parallel buffer containing
				 color and font information */
  int firstchar_, lastchar_;  /* Buffer positions of first and last
				 displayed character (lastChar points
				 either to a newline or one character
				 beyond the end of the buffer) */
  bool own_buffer;	      /* True if buffer_ created by constructor */
  bool continuous_wrap_;      /* Wrap long lines when displaying */
  int wrapmargin_;            /* Margin in # of char positions for
				 wrapping in continuousWrap mode */
  int *linestarts_;
  int topline_num_;           /* Line number of top displayed line
				 of file (first line of file is 1) */
  int abs_topline_num_;       /* In continuous wrap mode, the line
				 number of the top line if the text
				 were not wrapped (note that this is
				 only maintained as needed). */
  bool need_abs_topline_num_; /* Externally settable flag to continue
				 maintaining absTopLineNum even if
				 it isn't needed for line # display */
  int horiz_offset_;          /* Horizontal scroll pos. in pixels */
  int numstyles_;             /* Number of entries in styleTable */
  const StyleTableEntry *styletable_; /* Table of fonts and colors for
					 coloring/syntax-highlighting */
  char unfinished_style_;     /* Style buffer entry which triggers
				 on-the-fly reparsing of region */
  UnfinishedStyleCb unfinished_highlight_cb_; /* Callback to parse "unfinished" */
					      /* regions */
  void *highlight_cbarg_;     /* Arg to unfinishedHighlightCB */
  int fixed_fontwidth_;       /* Font width if all current fonts are
				 fixed and match in width, else -1 */
  bool suppressresync_;       /* Suppress resynchronization of line
				 starts during buffer updates */
  int nlinesdeleted_;         /* Number of lines deleted during
				 buffer modification (only used
				 when resynchronization is suppressed) */

  int stdfontwidth_;
  int ascent_;
  int descent_;
  int maxsize_;

  Color cursor_color_;

  Scrollbar *hscrollbar;
  Scrollbar *vscrollbar;

  Rectangle text_area;

  int dragpos_, dragtype_, dragging_;
  int linenumleft_, linenumwidth_; /* Line number margin and width */
};

} /* namespace fltk */

#endif

//
// End of "$Id: TextDisplay.h 5432 2006-09-16 02:03:04Z spitzak $".
//

#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
