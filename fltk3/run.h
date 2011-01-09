//
// "$Id$"
//
// Main header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2010 by Bill Spitzak and others.
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
    fltk3 namespace.
 */

#ifndef FLTK3_Run_H
#  define FLTK3_Run_H

#ifdef FLTK_HAVE_CAIRO
# include <fltk3/Fl_Cairo.H>
#endif

#  include "fl_utf8.h"
#  include "Enumerations.H"
#  ifndef Fl_Object
#    define Fl_Object fltk3::Widget	/**< for back compatibility - use fltk3::Widget! */
#  endif

#  ifdef check
#    undef check
#  endif


class Fl_Image;
struct Fl_Label;

namespace fltk3 {
  class Window;
  class Widget;
}


/** \defgroup  callback_functions Callback function typedefs
 \brief Typedefs defined in <fltk3/run.h> for callback or handler functions passed as function parameters.

    FLTK uses callback functions as parameters for some function calls, e.g. to
    set up global event handlers (fltk3::add_handler()), to add a timeout handler
    (fltk3::add_timeout()), and many more.

    The typedefs defined in this group describe the function parameters used to set
    up or clear the callback functions and should also be referenced to define the
    callback function to handle such events in the user's code.

    \see fltk3::add_handler(), fltk3::add_timeout(), fltk3::repeat_timeout(),
	 fltk3::remove_timeout() and others
  @{ */

/** signature of some label drawing functions passed as parameters */
typedef void (Fl_Label_Draw_F)(const Fl_Label *label, int x, int y, int w, int h, Fl_Align align);

/** signature of some label measurement functions passed as parameters */
typedef void (Fl_Label_Measure_F)(const Fl_Label *label, int &width, int &height);

/** signature of some box drawing functions passed as parameters */
typedef void (Fl_Box_Draw_F)(int x, int y, int w, int h, Fl_Color color);

/** signature of some timeout callback functions passed as parameters */
typedef void (*Fl_Timeout_Handler)(void *data);

/** signature of some wakeup callback functions passed as parameters */
typedef void (*Fl_Awake_Handler)(void *data);

/** signature of add_idle callback functions passed as parameters */
typedef void (*Fl_Idle_Handler)(void *data);

/** signature of set_idle callback functions passed as parameters */
typedef void (*Fl_Old_Idle_Handler)();

/** signature of add_fd functions passed as parameters */
typedef void (*Fl_FD_Handler)(int fd, void *data);

/** signature of add_handler functions passed as parameters */
typedef int (*Fl_Event_Handler)(int event);

/** signature of set_abort functions passed as parameters */
typedef void (*Fl_Abort_Handler)(const char *format,...);

/** signature of set_atclose functions passed as parameters */
typedef void (*Fl_Atclose_Handler)(fltk3::Window *window, void *data);

/** signature of args functions passed as parameters */
typedef int (*Fl_Args_Handler)(int argc, char **argv, int &i);

/** @} */ /* group callback_functions */


/**
  The Fl is the FLTK global (static) containing
  state information and global methods for the current application.
*/
namespace fltk3 {
  
// should be private!
#ifndef FL_DOXYGEN
  extern int e_number;
  extern int e_x;
  extern int e_y;
  extern int e_x_root;
  extern int e_y_root;
  extern int e_dx;
  extern int e_dy;
  extern int e_state;
  extern int e_clicks;
  extern int e_is_click;
  extern int e_keysym;
  extern char* e_text;
  extern int e_length;
  extern fltk3::Widget* belowmouse_;
  extern fltk3::Widget* pushed_;
  extern fltk3::Widget* focus_;
  extern int damage_;
  extern fltk3::Widget* selection_owner_;
  extern fltk3::Window* modal_;
  extern fltk3::Window* grab_;
  extern int compose_state;
#endif
  /**
    If true then flush() will do something.
  */
  inline void damage(int d) {damage_ = d;}

// public
  typedef enum {
      /// When switched on, moving the text cursor beyond the start or end of 
      /// a text in a text widget will change focus to the next text widgt. 
      /// When switched off, the cursor will stop at the end of the text. 
      /// Pressing Tab or Ctrl-Tab will advance the keyboard focus.
    OPTION_ARROW_FOCUS = 0,
      // When switched on, FLTK will use the file chooser dialog that comes 
      // with your operating system whenever possible. When switched off, FLTK
      // will present its own file chooser.
      // \todo implement me
    // OPTION_NATIVE_FILECHOOSER,
      // When Filechooser Preview is enabled, the FLTK or native file chooser
      // will show a preview of a selected file (if possible) before the user
      // decides to choose the file.
      // \todo implement me
    //OPTION_FILECHOOSER_PREVIEW,
      /// If visible focus is switched on, FLTK will draw a dotted rectangle 
      /// inside the widget that will receive the next keystroke. If switched
      /// off, no such indicator will be drawn and keyboard navigation
      /// is disabled.
    OPTION_VISIBLE_FOCUS,
      /// If text drag-and-drop is enabled, the user can select and drag text
      /// from any text widget. If disabled, no dragging is possible, however
      /// dropping text from other applications still works.
    OPTION_DND_TEXT,
      /// If tooltips are enabled, hovering the mouse over a widget with a 
      /// tooltip text will open a little tootip window until the mouse leaves
      /// the widget. If disabled, no tooltip is shown.
    OPTION_SHOW_TOOLTIPS,
      // don't change this, leave it always as the last element
    OPTION_LAST
  } Fl_Option;
  
// private
  extern unsigned char options_[OPTION_LAST];
  extern unsigned char options_read_;
  
// public
  /*
   Return a global setting for all FLTK applications, possibly overridden
   by a setting specifically for this application.
   */
  bool option(Fl_Option opt);
  
  /*
   Override an option while the application is running.
   */
  void option(Fl_Option opt, bool val);
  
  /**
    The currently executing idle callback function: DO NOT USE THIS DIRECTLY!
    
    This is now used as part of a higher level system allowing multiple
    idle callback functions to be called.
    \see add_idle(), remove_idle()
  */
  extern void (*idle)();

#ifndef FL_DOXYGEN
  extern Fl_Awake_Handler *awake_ring_;
  extern void **awake_data_;
  extern int awake_ring_size_;
  extern int awake_ring_head_;
  extern int awake_ring_tail_;
  extern const char* scheme_;
  extern Fl_Image* scheme_bg_;

  extern int e_original_keysym; // late addition
  extern int scrollbar_size_;
#endif


  int add_awake_handler_(Fl_Awake_Handler, void*);
  int get_awake_handler_(Fl_Awake_Handler&, void*&);

// public

  // API version number
  double version();

  // argument parsers:
  int arg(int argc, char **argv, int& i);
  int args(int argc, char **argv, int& i, Fl_Args_Handler cb = 0);
  void args(int argc, char **argv);
  /**
    Usage string displayed if fltk3::args() detects an invalid argument.
    This may be changed to point to customized text at run-time.
  */
  extern const char* const help;

  // things called by initialization:
  void display(const char*);
  int visual(int);
  /**
    This does the same thing as fltk3::visual(int) but also requires OpenGL
    drawing to work. This <I>must</I> be done if you want to draw in
    normal windows with OpenGL with gl_start() and gl_end().
    It may be useful to call this so your X windows use the same visual
    as an Fl_Gl_Window, which on some servers will reduce colormap flashing.

    See Fl_Gl_Window for a list of additional values for the argument.
  */
  int gl_visual(int, int *alist=0); // platform dependent
  void own_colormap();
  void get_system_colors();
  void foreground(uchar, uchar, uchar);
  void background(uchar, uchar, uchar);
  void background2(uchar, uchar, uchar);

  // schemes:
  int scheme(const char*);
  /** See void scheme(const char *name) */
  inline const char* scheme() {return scheme_;}
  /** 
    Called by scheme according to scheme name. 
    Loads or reloads the current scheme selection. 
    See void scheme(const char *name) 
  */
  int reload_scheme(); // platform dependent
  int scrollbar_size();
  void scrollbar_size(int W);

  // execution:
  int wait();
  double wait(double time);
  int check();
  int ready();
  int run();
  fltk3::Widget* readqueue();
  /**
  Adds a one-shot timeout callback.  The function will be called by
  fltk3::wait() at <i>t</i> seconds after this function is called.
  The optional void* argument is passed to the callback.
  
  You can have multiple timeout callbacks. To remove a timeout
  callback use fltk3::remove_timeout().
  
  If you need more accurate, repeated timeouts, use fltk3::repeat_timeout() to
  reschedule the subsequent timeouts.
  
  The following code will print "TICK" each second on
  stdout with a fair degree of accuracy:
  
  \code
     void callback(void*) {
       puts("TICK");
       fltk3::repeat_timeout(1.0, callback);
     }
  
     int main() {
       fltk3::add_timeout(1.0, callback);
       return fltk3::run();
     }
  \endcode
  */
  void add_timeout(double t, Fl_Timeout_Handler,void* = 0); // platform dependent
  /**
  Repeats a timeout callback from the expiration of the
  previous timeout, allowing for more accurate timing. You may only call
  this method inside a timeout callback.
  
  The following code will print "TICK" each second on
  stdout with a fair degree of accuracy:
  
  \code
     void callback(void*) {
       puts("TICK");
       fltk3::repeat_timeout(1.0, callback);
     }
  
     int main() {
       fltk3::add_timeout(1.0, callback);
       return fltk3::run();
     }
  \endcode
  */
  void repeat_timeout(double t, Fl_Timeout_Handler, void* = 0); // platform dependent
  int  has_timeout(Fl_Timeout_Handler, void* = 0);
  void remove_timeout(Fl_Timeout_Handler, void* = 0);
  void add_check(Fl_Timeout_Handler, void* = 0);
  int  has_check(Fl_Timeout_Handler, void* = 0);
  void remove_check(Fl_Timeout_Handler, void* = 0);
  /**
    Adds file descriptor fd to listen to.
    
    When the fd becomes ready for reading fltk3::wait() will call the
    callback and then return. The callback is passed the fd and the
    arbitrary void* argument.
    
    The second version takes a when bitfield, with the bits
    FL_READ, FL_WRITE, and FL_EXCEPT defined,
    to indicate when the callback should be done.
    
    There can only be one callback of each type for a file descriptor. 
    fltk3::remove_fd() gets rid of <I>all</I> the callbacks for a given
    file descriptor.
    
    Under UNIX <I>any</I> file descriptor can be monitored (files,
    devices, pipes, sockets, etc.). Due to limitations in Microsoft Windows,
    WIN32 applications can only monitor sockets.
  */
  void add_fd(int fd, int when, Fl_FD_Handler cb, void* = 0); // platform dependent
  /** See void add_fd(int fd, int when, Fl_FD_Handler cb, void* = 0) */
  void add_fd(int fd, Fl_FD_Handler cb, void* = 0); // platform dependent
  /** Removes a file descriptor handler. */
  void remove_fd(int, int when); // platform dependent
  /** Removes a file descriptor handler. */
  void remove_fd(int); // platform dependent

  void add_idle(Fl_Idle_Handler cb, void* data = 0);
  int  has_idle(Fl_Idle_Handler cb, void* data = 0);
  void remove_idle(Fl_Idle_Handler cb, void* data = 0);
  /** If true then flush() will do something. */
  inline int damage() {return damage_;}
  void redraw();
  void flush();
  /** \addtogroup group_comdlg
    @{ */
  /**
  FLTK calls fltk3::warning() to output a warning message.
  
  The default version on Windows returns \e without printing a warning
  message, because Windows programs normally don't have stderr (a console
  window) enabled.

  The default version on all other platforms prints the warning message to stderr.

  You can override the behavior by setting the function pointer to your
  own routine.

  fltk3::warning() means that there was a recoverable problem, the display may
  be messed up, but the user can probably keep working - all X protocol
  errors call this, for example. The default implementation returns after
  displaying the message.
   \note \#include <fltk3/run.h>
  */
  extern void (*warning)(const char*, ...);
  /**
  FLTK calls fltk3::error() to output a normal error message.
  
  The default version on Windows displays the error message in a MessageBox window.

  The default version on all other platforms prints the error message to stderr.

  You can override the behavior by setting the function pointer to your
  own routine.

  fltk3::error() means there is a recoverable error such as the inability to read
  an image file. The default implementation returns after displaying the message.
   \note \#include <fltk3/run.h>
  */
  extern void (*error)(const char*, ...);
  /**
  FLTK calls fltk3::fatal() to output a fatal error message.
  
  The default version on Windows displays the error message in a MessageBox window.

  The default version on all other platforms prints the error message to stderr.
  
  You can override the behavior by setting the function pointer to your
  own routine.

  fltk3::fatal() must not return, as FLTK is in an unusable state, however your
  version may be able to use longjmp or an exception to continue, as long as
  it does not call FLTK again. The default implementation exits with status 1
  after displaying the message.
   \note \#include <fltk3/run.h>
  */
  extern void (*fatal)(const char*, ...);
  /** @} */

  /** \defgroup  fl_windows Windows handling functions
      \brief Windows and standard dialogs handling declared in <fltk3/run.h>
    @{ */
  fltk3::Window* first_window();
  void first_window(fltk3::Window*);
  fltk3::Window* next_window(const fltk3::Window*);

  /**
    Returns the top-most modal() window currently shown.

    This is the most recently shown() window with modal() true, or NULL
    if there are no modal() windows shown().
    The modal() window has its handle() method called
    for all events, and no other windows will have handle()
    called (grab() overrides this).
  */
  inline fltk3::Window* modal() {return modal_;}
  /**
    This is used when pop-up menu systems are active.
    
    Send all events to the passed window no matter where the pointer or
    focus is (including in other programs). The window <I>does not have
    to be shown()</I> , this lets the handle() method of a
    "dummy" window override all event handling and allows you to
    map and unmap a complex set of windows (under both X and WIN32
    <I>some</I> window must be mapped because the system interface needs a
    window id).
    
    If grab() is on it will also affect show() of windows by doing
    system-specific operations (on X it turns on override-redirect).
    These are designed to make menus popup reliably
    and faster on the system.
    
    To turn off grabbing do fltk3::grab(0).
    
    <I>Be careful that your program does not enter an infinite loop
    while grab() is on.  On X this will lock up your screen!</I>
    To avoid this potential lockup, all newer operating systems seem to 
    limit mouse pointer grabbing to the time during which a mouse button 
    is held down. Some OS's may not support grabbing at all.
  */
  inline fltk3::Window* grab() {return grab_;}
  /** Selects the window to grab. See fltk3::Window* fltk3::grab() */
  void grab(fltk3::Window*); // platform dependent
  /** @} */

  /** \defgroup fl_events Events handling functions
	Fl class events handling API declared in <fltk3/run.h>
	@{
  */
  // event information:
  /**
    Returns the last event that was processed. This can be used
    to determine if a callback is being done in response to a
    keypress, mouse click, etc.
  */
  inline int event()		{return e_number;}
  /**
    Returns the mouse position of the event relative to the fltk3::Window
    it was passed to.
  */
  inline int event_x()	{return e_x;}
  /**
    Returns the mouse position of the event relative to the fltk3::Window
    it was passed to.
  */
  inline int event_y()	{return e_y;}
  /**
    Returns the mouse position on the screen of the event.  To find the
    absolute position of an fltk3::Window on the screen, use the
    difference between event_x_root(),event_y_root() and 
    event_x(),event_y().
  */
  inline int event_x_root()	{return e_x_root;}
  /**
    Returns the mouse position on the screen of the event.  To find the
    absolute position of an fltk3::Window on the screen, use the
    difference between event_x_root(),event_y_root() and 
    event_x(),event_y().
  */
  inline int event_y_root()	{return e_y_root;}
  /**
    Returns the current horizontal mouse scrolling associated with the
    FL_MOUSEWHEEL event. Right is positive.
  */
  inline int event_dx()	{return e_dx;}
  /**
    Returns the current vertical mouse scrolling associated with the
    FL_MOUSEWHEEL event. Down is positive.
  */
  inline int event_dy()	{return e_dy;}
  /**
    Return where the mouse is on the screen by doing a round-trip query to
    the server.  You should use fltk3::event_x_root() and 
    fltk3::event_y_root() if possible, but this is necessary if you are
    not sure if a mouse event has been processed recently (such as to
    position your first window).  If the display is not open, this will
    open it.
  */
  void get_mouse(int &,int &); // platform dependent
  /**
    Returns non zero if we had a double click event.
    \retval Non-zero if the most recent FL_PUSH or FL_KEYBOARD was a "double click".  
    \retval  N-1 for  N clicks. 
    A double click is counted if the same button is pressed
    again while event_is_click() is true.
    
   */
  inline int event_clicks()	{return e_clicks;}
  /**
    Manually sets the number returned by fltk3::event_clicks().  
    This can be used to set it to zero so that
    later code does not think an item was double-clicked.
    \param[in] i corresponds to no double-click if 0, i+1 mouse clicks otherwise
    \see int event_clicks()
  */
  inline void event_clicks(int i) {e_clicks = i;}
  /**
    The first form returns non-zero if the mouse has not moved far enough
    and not enough time has passed since the last FL_PUSH or 
    FL_KEYBOARD event for it to be considered a "drag" rather than a
    "click".  You can test this on FL_DRAG, FL_RELEASE,
    and FL_MOVE events.  The second form clears the value returned
    by fltk3::event_is_click().  Useful to prevent the <I>next</I>
    click from being counted as a double-click or to make a popup menu
    pick an item with a single click.  Don't pass non-zero to this.
  */
  inline int event_is_click()	{return e_is_click;}
  /**
    Only i=0 works! See int event_is_click(). 
  */
  inline void event_is_click(int i) {e_is_click = i;}
  /**
    Gets which particular mouse button caused the current event. 
    This returns garbage if the most recent event was not a FL_PUSH or FL_RELEASE event.
    \retval FL_LEFT_MOUSE \retval FL_MIDDLE_MOUSE \retval FL_RIGHT_MOUSE.
    \see fltk3::event_buttons()
  */
  inline int event_button()	{return e_keysym-FL_Button;}
  /**
    This is a bitfield of what shift states were on and what mouse buttons
    were held down during the most recent event. The second version
    returns non-zero if any of the passed bits are turned on.
    The legal bits are:
    
    \li FL_SHIFT
    \li FL_CAPS_LOCK
    \li FL_CTRL
    \li FL_ALT
    \li FL_NUM_LOCK
    \li FL_META
    \li FL_SCROLL_LOCK
    \li FL_BUTTON1
    \li FL_BUTTON2
    \li FL_BUTTON3
    
    X servers do not agree on shift states, and FL_NUM_LOCK, FL_META, and
    FL_SCROLL_LOCK may not work. The values were selected to match the
    XFree86 server on Linux. In addition there is a bug in the way X works
    so that the shift state is not correctly reported until the first event
    <I>after</I> the shift key is pressed or released.
  */
  inline int event_state()	{return e_state;}
  /** See int event_state() */
  inline int event_state(int i) {return e_state&i;}
  /**
    Gets which key on the keyboard was last pushed.

    The returned integer 'key code' is not necessarily a text
    equivalent for the keystroke. For instance: if someone presses '5' on the 
    numeric keypad with numlock on, fltk3::event_key() may return the 'key code'
    for this key, and NOT the character '5'. To always get the '5', use fltk3::event_text() instead.
    
    \returns an integer 'key code', or 0 if the last event was not a key press or release.
    \see int event_key(int), event_text(), compose(int&).
  */
  inline int event_key()	{return e_keysym;}
  /**
    Returns the keycode of the last key event, regardless of the NumLock state.
      
    If NumLock is deactivated, FLTK translates events from the 
    numeric keypad into the corresponding arrow key events. 
    event_key() returns the translated key code, whereas
    event_original_key() returns the keycode before NumLock translation.
  */
  inline int event_original_key(){return e_original_keysym;}
  /** 
    Returns true if the given \p key was held
    down (or pressed) <I>during</I> the last event.  This is constant until
    the next event is read from the server.
    
    fltk3::get_key(int) returns true if the given key is held down <I>now</I>.
    Under X this requires a round-trip to the server and is <I>much</I>
    slower than fltk3::event_key(int).
    
    Keys are identified by the <I>unshifted</I> values. FLTK defines a
    set of symbols that should work on most modern machines for every key
    on the keyboard:
    
    \li All keys on the main keyboard producing a printable ASCII
	character use the value of that ASCII character (as though shift,
	ctrl, and caps lock were not on). The space bar is 32.
    \li All keys on the numeric keypad producing a printable ASCII
	character use the value of that ASCII character plus FL_KP.
	The highest possible value is FL_KP_Last so you can
	range-check to see if something is  on the keypad.
    \li All numbered function keys use the number on the function key plus 
	FL_F.  The highest possible number is FL_F_Last, so you
	can range-check a value.
    \li Buttons on the mouse are considered keys, and use the button
	number (where the left button is 1) plus FL_Button.
    \li All other keys on the keypad have a symbol: FL_Escape,
	FL_BackSpace, FL_Tab, FL_Enter, FL_Print, FL_Scroll_Lock, FL_Pause,
	FL_Insert, FL_Home, FL_Page_Up, FL_Delete, FL_End, FL_Page_Down,
	FL_Left, FL_Up, FL_Right, FL_Down, FL_Shift_L, FL_Shift_R,
	FL_Control_L, FL_Control_R, FL_Caps_Lock, FL_Alt_L, FL_Alt_R,
	FL_Meta_L, FL_Meta_R, FL_Menu, FL_Num_Lock, FL_KP_Enter.  Be
	careful not to confuse these with the very similar, but all-caps,
	symbols used by fltk3::event_state().

    On X fltk3::get_key(FL_Button+n) does not work.
    
    On WIN32 fltk3::get_key(FL_KP_Enter) and fltk3::event_key(FL_KP_Enter) do not work.
  */
  int event_key(int key);
  /** 
    Returns true if the given \p key is held down <I>now</I>.  
    Under X this requires a round-trip to the server and is <I>much</I>
    slower than fltk3::event_key(int). \see event_key(int)
  */
  int get_key(int key); // platform dependent
  /** 
    Returns the text associated with the current event, including FL_PASTE or FL_DND_RELEASE events.
    This can be used in response to FL_KEYUP, FL_KEYDOWN, FL_PASTE, FL_DND_RELEASE.

    When responding to FL_KEYUP/FL_KEYDOWN, use this function instead of fltk3::event_key()
    to get the text equivalent of keystrokes suitable for inserting into strings 
    and text widgets.

    The returned string is guaranteed to be be NULL terminated.
    However, see fltk3::event_length() for the actual length of the string,
    in case the string itself contains NULLs that are part of the text data.

    \returns A NULL terminated text string equivalent of the last keystroke.
   */
  inline const char* event_text() {return e_text;}
  /**
    Returns the length of the text in fltk3::event_text(). There
    will always be a nul at this position in the text. However there may
    be a nul before that if the keystroke translates to a nul character or
    you paste a nul character.
  */
  inline int event_length() {return e_length;}

  int compose(int &del);
  /**
    If the user moves the cursor, be sure to call fltk3::compose_reset().
    The next call to fltk3::compose() will start out in an initial state. In
    particular it will not set "del" to non-zero. This call is very fast
    so it is ok to call it many times and in many places.
  */
  inline void compose_reset() {compose_state = 0;}
  int event_inside(int,int,int,int);
  int event_inside(const fltk3::Widget*);
  int test_shortcut(Fl_Shortcut);

  // event destinations:
  int handle(int, fltk3::Window*);
  /**  Gets the widget that is below the mouse. 
       \see  belowmouse(fltk3::Widget*) */
  inline fltk3::Widget* belowmouse() {return belowmouse_;}
  void belowmouse(fltk3::Widget*);
  /** Gets the widget that is being pushed.
      \see void pushed(fltk3::Widget*) */
  inline fltk3::Widget* pushed()	{return pushed_;}
  void pushed(fltk3::Widget*);
  /** Gets the current fltk3::focus() widget. \sa fltk3::focus(fltk3::Widget*) */
  inline fltk3::Widget* focus()	{return focus_;}
  void focus(fltk3::Widget*);
  void add_handler(Fl_Event_Handler h);
  void remove_handler(Fl_Event_Handler h);
  /** @} */

  /** \defgroup  fl_clipboard  Selection & Clipboard functions
	FLTK global copy/cut/paste functions declared in <fltk3/run.h>
   @{ */
  // cut/paste:
  /**
  Copies the data pointed to by \p stuff to the selection buffer 
  (\p destination is 0) or
  the clipboard (\p destination is 1); \p len is the number of relevant
  bytes in \p stuff.
  The selection buffer is used for
  middle-mouse pastes and for drag-and-drop selections. The 
  clipboard is used for traditional copy/cut/paste operations.
  */
  void copy(const char* stuff, int len, int destination = 0); // platform dependent
  /**
  Pastes the data from the selection buffer (\p source is 0) or the clipboard 
  (\p source is 1) into \p receiver.  
  Set things up so the receiver widget will be called with an FL_PASTE event some
  time in the future with the data from the specified \p source in fltk3::event_text()
  and the number of characters in fltk3::event_length().
  The receiver
  should be prepared to be called \e directly by this, or for
  it to happen \e later, or possibly <i>not at all</i>.  This
  allows the window system to take as long as necessary to retrieve
  the paste buffer (or even to screw up completely) without complex
  and error-prone synchronization code in FLTK.
   
  The selection buffer is used for middle-mouse pastes and for 
  drag-and-drop selections. The clipboard is used for traditional 
  copy/cut/paste operations.
  */
  void paste(fltk3::Widget &receiver, int source /*=0*/); // platform dependent
  /**
    Initiate a Drag And Drop operation. The selection buffer should be
    filled with relevant data before calling this method. FLTK will
    then initiate the system wide drag and drop handling. Dropped data
    will be marked as <i>text</i>.
   
    Create a selection first using:
    fltk3::copy(const char *stuff, int len, 0)
  */
  int dnd(); // platform dependent

  // These are for back-compatibility only:
  /**  back-compatibility only: Gets the widget owning the current selection  
       \see fltk3::Widget* selection_owner(fltk3::Widget*) */
  inline fltk3::Widget* selection_owner() {return selection_owner_;}
  void selection_owner(fltk3::Widget*);
  void selection(fltk3::Widget &owner, const char*, int len);
  void paste(fltk3::Widget &receiver);
/** @} */
/** \defgroup  fl_screen  Screen functions
	fl global screen functions declared in <fltk3/run.h>
     @{ */
  // screen size:
  /** Returns the origin of the current screen, where 0 indicates the left side of the screen. */
  int x(); // platform dependent
  /** Returns the origin of the current screen, where 0 indicates the top edge of the screen. */
  int y(); // platform dependent
  /** Returns the width of the screen in pixels. */
  int w(); // platform dependent
  /** Returns the height of the screen in pixels. */
  int h(); // platform dependent

  // multi-head support:
  int screen_count();
  /** 
      Gets the bounding box of a screen that contains the mouse pointer.
      \param[out]  X,Y,W,H the corresponding screen bounding box
      \see void screen_xywh(int &x, int &y, int &w, int &h, int mx, int my) 
  */
  void screen_xywh(int &X, int &Y, int &W, int &H, int mx, int my);
  inline void screen_xywh(int &X, int &Y, int &W, int &H) {
    screen_xywh(X, Y, W, H, e_x_root, e_y_root);
  }
  void screen_xywh(int &X, int &Y, int &W, int &H, int n);  
  void screen_dpi(float &h, float &v, int n=0);

  /**   @} */

  /** \defgroup  fl_attributes  Color & Font functions
	fl global color, font functions.
   These functions are declared in <fltk3/run.h> or <fltk3/fl_draw.H>. 
     @{ */
 
  // color map:
  void	set_color(Fl_Color, uchar, uchar, uchar);
  /**
    Sets an entry in the fl_color index table. You can set it to any
    8-bit RGB color. The color is not allocated until fl_color(i) is used.
  */
  void	set_color(Fl_Color i, unsigned c); // platform dependent
  unsigned get_color(Fl_Color i);
  void	get_color(Fl_Color i, uchar &red, uchar &green, uchar &blue);
  /**
    Frees the specified color from the colormap, if applicable.
    If overlay is non-zero then the color is freed from the
    overlay colormap.
  */
  void	free_color(Fl_Color i, int overlay = 0); // platform dependent

  // fonts:
  const char* get_font(fltk3::Font);
  /**
    Get a human-readable string describing the family of this face.  This
    is useful if you are presenting a choice to the user.  There is no
    guarantee that each face has a different name.  The return value points
    to a static buffer that is overwritten each call.
    
    The integer pointed to by \p attributes (if the pointer is not
    zero) is set to zero, fltk3::BOLD or fltk3::ITALIC or 
    fltk3::BOLD | fltk3::ITALIC.  To locate a "family" of fonts, search
    forward and back for a set with non-zero attributes, these faces along
    with the face with a zero attribute before them constitute a family.
  */
  const char* get_font_name(fltk3::Font, int* attributes = 0);
  /**
    Return an array of sizes in \p sizep.  The return value is the
    length of this array.  The sizes are sorted from smallest to largest
    and indicate what sizes can be given to fl_font() that will
    be matched exactly (fl_font() will pick the closest size for
    other sizes).  A zero in the first location of the array indicates a
    scalable font, where any size works, although the array may list sizes
    that work "better" than others.  Warning: the returned array
    points at a static buffer that is overwritten each call.  Under X this
    will open the display.
  */
  int get_font_sizes(fltk3::Font, int*& sizep);
  void set_font(fltk3::Font, const char*);
  void set_font(fltk3::Font, fltk3::Font);
  /**
    FLTK will open the display, and add every fonts on the server to the
    face table.  It will attempt to put "families" of faces together, so
    that the normal one is first, followed by bold, italic, and bold
    italic.
    
    The optional argument is a string to describe the set of fonts to
    add.  Passing NULL will select only fonts that have the
    ISO8859-1 character set (and are thus usable by normal text).  Passing
    "-*" will select all fonts with any encoding as long as they have
    normal X font names with dashes in them.  Passing "*" will list every
    font that exists (on X this may produce some strange output).  Other
    values may be useful but are system dependent.  With WIN32 NULL
    selects fonts with ISO8859-1 encoding and non-NULL selects
    all fonts.
    
    The return value is how many faces are in the table after this is done.
  */
  fltk3::Font set_fonts(const char* = 0); // platform dependent

  /**   @} */
 /** \defgroup  fl_drawings  Drawing functions
  FLTK global graphics and GUI drawing functions.
  These functions are declared in <fltk3/fl_draw.H>, 
  and in <fltk3/x.H> for offscreen buffer-related ones.
     @{ */
  // <Hack to re-order the 'Drawing functions' group>
 /** @} */

  // labeltypes:
  void set_labeltype(fltk3::Labeltype,Fl_Label_Draw_F*,Fl_Label_Measure_F*);
  /** Sets the functions to call to draw and measure a specific labeltype. */
  void set_labeltype(fltk3::Labeltype, fltk3::Labeltype from); // is it defined ?

  // boxtypes:
  Fl_Box_Draw_F *get_boxtype(fltk3::Boxtype);
  void set_boxtype(fltk3::Boxtype, Fl_Box_Draw_F*,uchar,uchar,uchar,uchar);
  void set_boxtype(fltk3::Boxtype, fltk3::Boxtype from);
  int box_dx(fltk3::Boxtype);
  int box_dy(fltk3::Boxtype);
  int box_dw(fltk3::Boxtype);
  int box_dh(fltk3::Boxtype);
  int draw_box_active();

  // back compatibility:
  /** \addtogroup fl_windows 
    @{ */
  /** For back compatibility, sets the void fltk3::fatal handler callback */
  inline void set_abort(Fl_Abort_Handler f) {fatal = f;}
  extern void (*atclose)(fltk3::Window*,void*);
  void default_atclose(fltk3::Window*,void*);
  /** For back compatibility, sets the fltk3::atclose handler callback. You
      can now simply change the callback for the window instead.
      \see fltk3::Window::callback(Fl_Callback*) */
  inline void set_atclose(Fl_Atclose_Handler f) {atclose = f;}
  /**   @} */

  /** \addtogroup fl_events 
    @{ */
  /** Returns non-zero if the Shift key is pressed. */
  inline int event_shift() {return e_state&FL_SHIFT;}
  /** Returns non-zero if the Control key is pressed. */
  inline int event_ctrl() {return e_state&FL_CTRL;}
  /** Returns non-zero if the FL_COMMAND key is pressed, either FL_CTRL or on OSX FL_META. */
  inline int event_command() {return e_state&FL_COMMAND;}
  /** Returns non-zero if the Alt key is pressed. */
  inline int event_alt() {return e_state&FL_ALT;}
  /**
    Returns the mouse buttons state bits; if non-zero, then at least one
    button is pressed now.  This function returns the button state at the 
    time of the event. During an FL_RELEASE event, the state 
    of the released button will be 0. To find out, which button 
    caused an FL_RELEASE event, you can use fltk3::event_button() instead.
    \return a bit mask value like { [FL_BUTTON1] | [FL_BUTTON2] | [FL_BUTTON3] }
  */
  inline int event_buttons() {return e_state&0x7f000000;}
  /**
    Returns non-zero if mouse button 1 is currently held down.
    For more details, see fltk3::event_buttons().
  */
  inline int event_button1() {return e_state&FL_BUTTON1;}
  /**
    Returns non-zero if button 2 is currently held down.
    For more details, see fltk3::event_buttons().
  */
  inline int event_button2() {return e_state&FL_BUTTON2;}
  /**
    Returns non-zero if button 3 is currently held down.
    For more details, see fltk3::event_buttons().
  */
  inline int event_button3() {return e_state&FL_BUTTON3;}
  /**   @} */

  /**
    Sets an idle callback.

    \deprecated This method is obsolete - use the add_idle() method instead.
  */
  inline void set_idle(Fl_Old_Idle_Handler cb) {idle = cb;}
  /** See fltk3::Window* grab() */
  inline void grab(fltk3::Window&win) {grab(&win);}
  /** Releases the current grabbed window, equals grab(0).
  \deprecated Use fltk3::grab(0) instead.
  \see fltk3::Window* grab() */
  inline void release() {grab(0);}

  // Visible focus methods...
  /**
    Gets or sets the visible keyboard focus on buttons and other
    non-text widgets. The default mode is to enable keyboard focus
    for all widgets.
  */
  inline void visible_focus(int v) { option(OPTION_VISIBLE_FOCUS, v);  }
  /**
    Gets or sets the visible keyboard focus on buttons and other
    non-text widgets. The default mode is to enable keyboard focus
    for all widgets.
  */
  inline int  visible_focus() { return option(OPTION_VISIBLE_FOCUS); }

  // Drag-n-drop text operation methods...
  /**
    Gets or sets whether drag and drop text operations are supported.
    This specifically affects whether selected text can
    be dragged from text fields or dragged within a text field as a
    cut/paste shortcut.
  */
  inline void dnd_text_ops(int v) { option(OPTION_DND_TEXT, v); }
  /**
    Gets or sets whether drag and drop text operations are
    supported. This specifically affects whether selected text can
    be dragged from text fields or dragged within a text field as a
    cut/paste shortcut.
  */
  inline int  dnd_text_ops() { return option(OPTION_DND_TEXT); }
  /** \defgroup fl_multithread Multithreading support functions
	fl multithreading support functions declared in <fltk3/run.h>
   @{ */

  // Multithreading support:
  void lock();
  void unlock();
  void awake(void* message = 0);
  /** See void awake(void* message=0). */
  int awake(Fl_Awake_Handler cb, void* message = 0);
  /**
    The thread_message() method returns the last message
    that was sent from a child by the awake() method.
    
    See also: multithreading
  */
  void* thread_message(); // platform dependent
  /** @} */

  /** \defgroup fl_del_widget Safe widget deletion support functions

    These functions, declared in <fltk3/run.h>, support deletion of widgets inside callbacks.

    fltk3::delete_widget() should be called when deleting widgets
    or complete widget trees (fltk3::Group, fltk3::Window, ...) inside
    callbacks.

    The other functions are intended for internal use. The preferred
    way to use them is by using the helper class Fl_Widget_Tracker.

    The following is to show how it works ...

    There are three groups of related methods:

      -# scheduled widget deletion
	- fltk3::delete_widget() schedules widgets for deletion
	- fltk3::do_widget_deletion() deletes all scheduled widgets
      -# widget watch list ("smart pointers")
	- fltk3::watch_widget_pointer() adds a widget pointer to the watch list
	- fltk3::release_widget_pointer() removes a widget pointer from the watch list
	- fltk3::clear_widget_pointer() clears a widget pointer \e in the watch list
      -# the class Fl_Widget_Tracker:
	- the constructor calls fltk3::watch_widget_pointer()
	- the destructor calls fltk3::release_widget_pointer()
	- the access methods can be used to test, if a widget has been deleted
	  \see Fl_Widget_Tracker.

   @{ */
  // Widget deletion:
  void delete_widget(fltk3::Widget *w);
  void do_widget_deletion();
  void watch_widget_pointer(fltk3::Widget *&w);
  void release_widget_pointer(fltk3::Widget *&w);
  void clear_widget_pointer(fltk3::Widget const *w);
  /** @} */

#ifdef FLTK_HAVE_CAIRO
  /** \defgroup group_cairo Cairo support functions and classes 
      @{ 
  */
// public:
  // Cairo support API
  cairo_t * cairo_make_current(fltk3::Window* w);
   /** when FLTK_HAVE_CAIRO is defined and cairo_autolink_context() is true, 
      any current window dc is linked to a current context.
      This is not the default, because it may not be necessary
      to add cairo support to all fltk supported windows.
      When you wish to associate a cairo context in this mode,
      you need to call explicitly in your draw() overridden method,
      FL::cairo_make_current(fltk3::Window*). This will create a cairo context
      but only for this Window. 
      Still in custom cairo application it is possible to handle 
      completely this process automatically by setting \p alink to true.
      In this last case, you don't need anymore to call fltk3::cairo_make_current().
      You can use fltk3::cairo_cc() to get the current cairo context anytime.
     \note Only available when configure has the --enable-cairo option
  */
  inline void cairo_autolink_context(bool alink) {cairo_state_.autolink(alink);}
  /** 
    Gets the current autolink mode for cairo support.
    \retval false if no cairo context autolink is made for each window. 
    \retval true if any fltk window is attached a cairo context when it 
    is current. \see void cairo_autolink_context(bool alink) 
    \note Only available when configure has the --enable-cairo option
 */
  inline bool cairo_autolink_context() {return cairo_state_.autolink();}
  /** Gets the current cairo context linked with a fltk window. */
  inline cairo_t * cairo_cc() { return cairo_state_.cc(); }
  /** Sets the current cairo context to \p c.
      Set \p own to true if you want fltk to handle this cc deletion.
     \note Only available when configure has the --enable-cairo option
*/
  inline void cairo_cc(cairo_t * c, bool own=false){ cairo_state_.cc(c, own); } 

// private:
  cairo_t * cairo_make_current(void* gc);
  cairo_t * cairo_make_current(void* gc, int W, int H);
  extern Fl_Cairo_State cairo_state_;
// public:
  /** @} */ 

#endif // FLTK_HAVE_CAIRO

};

/**
  This class should be used to control safe widget deletion.

  You can use an Fl_Widget_Tracker object to watch another widget, if you
  need to know, if this widget has been deleted during a callback.

  This simplifies the use of the "safe widget deletion" methods
  fltk3::watch_widget_pointer() and fltk3::release_widget_pointer() and
  makes their use more reliable, because the destructor autmatically
  releases the widget pointer from the widget watch list.

  It is intended to be used as an automatic (local/stack) variable,
  such that the automatic destructor is called when the object's
  scope is left. This ensures that no stale widget pointers are
  left in the widget watch list (see example below).
  
  You can also create Fl_Widget_Tracker objects with \c new, but then it
  is your responsibility to delete the object (and thus remove the
  widget pointer from the watch list) when it is not needed any more.

  Example:

  \code
    int MyClass::handle (int event) {

      if (...) {
	Fl_Widget_Tracker wp(this);	// watch myself
	do_callback();			// call the callback

	if (wp.deleted()) return 1;	// exit, if deleted

	// Now we are sure that the widget has not been deleted.
	// It is safe to access the widget

	clear_changed();		// access the widget
      }
    }
  \endcode

*/
class FL_EXPORT Fl_Widget_Tracker {

  fltk3::Widget* wp_;

public:

  Fl_Widget_Tracker(fltk3::Widget *wi);
  ~Fl_Widget_Tracker();

  /**
    Returns a pointer to the watched widget.

    This pointer is \c NULL, if the widget has been deleted.
  */
  fltk3::Widget *widget() {return wp_;}

  /**
    Returns 1, if the watched widget has been deleted.

    This is a convenience method. You can also use something like

    <tt>  if (wp.widget() == 0) // ...</tt>

    where \p wp is an Fl_Widget_Tracker object.
  */
  int deleted() {return wp_ == 0;}

  /**
    Returns 1, if the watched widget exists (has not been deleted).

    This is a convenience method. You can also use something like

    <tt>  if (wp.widget() != 0) // ...</tt>

    where \p wp is an Fl_Widget_Tracker object.
  */
  int exists()  {return wp_ != 0;}

};

 /** \defgroup  fl_unicode  Unicode and UTF-8 functions
	fl global Unicode and UTF-8 handling functions declared in <fltk3/fl_utf8.h>
     @{ */
 /** @} */

#endif // !Fl_H

//
// End of "$Id$".
//
