//
// "$Id: Button.h 6917 2009-10-13 20:10:49Z matt $"
//
// Button header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2009 by Bill Spitzak and others.
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
 fltk::Button widget . */

#ifndef fltk3_button_h
#define fltk3_button_h

#include "Widget.h"

// values for type()
#define FL_NORMAL_BUTTON	0   /**< value() will be set to 1 during the press of the button and 
reverts back to 0 when the button is released */
#define FL_TOGGLE_BUTTON	1   ///< value() toggles between 0 and 1 at every click of the button
#define FL_RADIO_BUTTON		(FL_RESERVED_TYPE+2) /**< is set to 1 at button press, and all other
buttons in the same group with <tt>type() == FL_RADIO_BUTTON</tt>
are set to zero.*/
#define FL_HIDDEN_BUTTON	3   ///< for Forms compatibility

#ifndef FL_DOXYGEN
extern FL_EXPORT Fl_Shortcut fl_old_shortcut(const char*);
#endif

namespace fltk {
  
  /**
   \class fltk::Button
   \brief Buttons generate callbacks when they are clicked by the user.
   
   You control exactly when and how by changing the values for type() and
   when().  Buttons can also generate callbacks in response to \c FL_SHORTCUT
   events.  The button can either have an explicit shortcut(int s) value or a
   letter shortcut can be indicated in the label() with an '\&' character
   before it.  For the label shortcut it does not matter if \e Alt is held
   down, but if you have an input field in the same window, the user will have
   to hold down the \e Alt key so that the input field does not eat the event
   first as an \c FL_KEYBOARD event.
   
   \todo Refactor the doxygen comments for fltk::Button type() documentation.
   
   For an fltk::Button object, the type() call returns one of:
   \li \c FL_NORMAL_BUTTON (0): value() remains unchanged after button press.
   \li \c FL_TOGGLE_BUTTON: value() is inverted after button press.
   \li \c FL_RADIO_BUTTON: value() is set to 1 after button press, and all other
   buttons in the current group with <tt>type() == FL_RADIO_BUTTON</tt>
	 are set to zero.
   
   \todo Refactor the doxygen comments for fltk::Button when() documentation.
   
   For an fltk::Button object, the following when() values are useful, the default
   being \c FL_WHEN_RELEASE:
   \li \c 0: The callback is not done, instead changed() is turned on.
   \li \c FL_WHEN_RELEASE: The callback is done after the user successfully
   clicks the button, or when a shortcut is typed.
   \li \c FL_WHEN_CHANGED: The callback is done each time the value() changes
   (when the user pushes and releases the button, and as the mouse is
	 dragged around in and out of the button).
   */
  class FL_EXPORT Button : public Widget {
    
    int shortcut_;
    char value_;
    char oldval;
    uchar down_box_;
    
  protected:
    
    virtual void draw();
    
  public:
    
    virtual int handle(int);
    
    Button(int X, int Y, int W, int H, const char *L = 0);
    
    int value(int v);
    
    /**
     Returns the current value of the button (0 or 1).
     */
    char value() const {return value_;}
    
    /**
     Same as \c value(1).
     \see value(int v)
     */
    int set() {return value(1);}
    
    /**
     Same as \c value(0).
     \see value(int v)
     */
    int clear() {return value(0);}
    
    void setonly(); // this should only be called on FL_RADIO_BUTTONs
    
    /**
     Returns the current shortcut key for the button.
     \retval int
     */
    int shortcut() const {return shortcut_;}
    
    /**
     Sets the shortcut key to \c s.
     Setting this overrides the use of '\&' in the label().
     The value is a bitwise OR of a key and a set of shift flags, for example:
     <tt>FL_ALT | 'a'</tt>, or
     <tt>FL_ALT | (FL_F + 10)</tt>, or just
     <tt>'a'</tt>.
     A value of 0 disables the shortcut.
     
     The key can be any value returned by fltk::event_key(), but will usually be
     an ASCII letter.  Use a lower-case letter unless you require the shift key
     to be held down.
     
     The shift flags can be any set of values accepted by fltk::event_state().
     If the bit is on, that shift key must be pushed.  Meta, Alt, Ctrl, and
     Shift must be off if they are not in the shift flags (zero for the other
     bits indicates a "don't care" setting).
     \param[in] s bitwise OR of key and shift flags
     */
    void shortcut(int s) {shortcut_ = s;}
    
    /**
     Returns the current down box type, which is drawn when value() is non-zero.
     \retval Fl_Boxtype
     */
    Fl_Boxtype down_box() const {return (Fl_Boxtype)down_box_;}
    
    /**
     Sets the down box type. The default value of 0 causes FLTK to figure out
     the correct matching down version of box().
     \param[in] b down box type
     */
    void down_box(Fl_Boxtype b) {down_box_ = b;}
    
    /// (for backwards compatibility)
    void shortcut(const char *s) {shortcut(fl_old_shortcut(s));}
    
    /// (for backwards compatibility)
    Fl_Color down_color() const {return selection_color();}
    
    /// (for backwards compatibility)
    void down_color(unsigned c) {selection_color(c);}
  }; // class Button
  
}; // namespace fltk

#endif

//==============================================================================

#if 0

#ifndef fltk_Widget_h
#include "Widget.h"
#endif

namespace fltk {
  
  class FL_API Button : public Widget {
  public:
    enum {HIDDEN=3}; // back-comptability value to hide the button
    
    bool	value() const { return state(); }
    bool	value(bool v) { return state(v); }
    
    int handle(int);
    int handle(int event, const Rectangle&);
    Button(int,int,int,int,const char * = 0);
    static NamedStyle* default_style;
    
    virtual void draw();
    void draw(int glyph_width) const;
  };
  
}

#endif

//
// End of "$Id: Button.h 5433 2006-09-16 03:00:02Z spitzak $".
//
