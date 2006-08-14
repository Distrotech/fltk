//
// "$Id: input.d 4288 2005-04-16 00:13:17Z mike $"
//
// Input header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2005 by Bill Spitzak and others.
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

module fl.input;

public import fl.input_;
public import fl.fl;

class Fl_Input : Fl_Input_ {

private:
  int handle_key() {
  
    char ascii = Fl.event_text()[0];
  
    int repeat_num=1;
  
    int del;
    if (Fl.compose(del)) {
  
      // Insert characters into numeric fields after checking for legality:
      if (input_type() == FL_FLOAT_INPUT || input_type() == FL_INT_INPUT) {
        Fl.compose_reset(); // ignore any foreign letters...
  
        // initialize the list of legal characters inside a floating point number
/+-
  #ifdef HAVE_LOCALECONV
        if (!legal_fp_chars) {
          int len = strlen(standard_fp_chars);
          struct lconv *lc = localeconv();
          if (lc) {
            if (lc->decimal_point) len += strlen(lc->decimal_point);
            if (lc->mon_decimal_point) len += strlen(lc->mon_decimal_point);
            if (lc->positive_sign) len += strlen(lc->positive_sign);
            if (lc->negative_sign) len += strlen(lc->negative_sign);
          }
          // the following line is not a true memory leak because the array is only
          // allocated once if required, and automatically freed when the program quits
          char *chars = (char*)malloc(len+1);
	  legal_fp_chars = chars;
          strcpy(chars, standard_fp_chars);
          if (lc) {
            if (lc->decimal_point) strcat(chars, lc->decimal_point);
            if (lc->mon_decimal_point) strcat(chars, lc->mon_decimal_point);
            if (lc->positive_sign) strcat(chars, lc->positive_sign);
            if (lc->negative_sign) strcat(chars, lc->negative_sign);
          }
        }
  #endif // HAVE_LOCALECONV
  -+/
        // This is complex to allow "0xff12" hex to be typed:
        if (!caret() && (ascii == '+' || ascii == '-') ||
	    (ascii >= '0' && ascii <= '9') ||
	    (caret()==1 && index(0)=='0' && (ascii=='x' || ascii == 'X')) ||
	    (caret()>1 && index(0)=='0' && (index(1)=='x'||index(1)=='X')
	     && (ascii>='A'&& ascii<='F' || ascii>='a'&& ascii<='f')) ||
	    input_type()==FL_FLOAT_INPUT && ascii && strchr(legal_fp_chars, ascii)) {
	  if (readonly()) fl_beep();
	  else replace(caret(), mark(), &ascii, 1);
        }
        return 1;
      }
  
      if (del || Fl.event_length()) {
        if (readonly()) fl_beep();
        else replace(caret(), del ? caret()-del : mark(),
	             Fl.event_text(), Fl.event_length());
      }
      return 1;
    }

    switch (Fl.event_key()) {
    case FL_Insert:
      if (Fl.event_state() & FL_CTRL) ascii = ctrl('C');
      else if (Fl.event_state() & FL_SHIFT) ascii = ctrl('V');
      break;
    case FL_Delete:
      if (Fl.event_state() & FL_SHIFT) ascii = ctrl('X');
      else ascii = ctrl('D');
      break;    
    case FL_Left:
      ascii = ctrl('B'); break;
    case FL_Right:
      ascii = ctrl('F'); break;
    case FL_Page_Up:
      fl_font(textfont(),textsize()); //ensure current font is set to ours
      repeat_num=h()/fl_height(); // number of lines to scroll
      if (!repeat_num) repeat_num=1;
    case FL_Up:
      ascii = ctrl('P'); break;
    case FL_Page_Down:
      fl_font(textfont(),textsize());
      repeat_num=h()/fl_height();
      if (!repeat_num) repeat_num=1;
    case FL_Down:
      ascii = ctrl('N'); break;
    case FL_Home:
      if (Fl.event_state() & FL_CTRL) {
        shift_position(0);
        return 1;
      }
      ascii = ctrl('A');
      break;
    case FL_End:
      if (Fl.event_state() & FL_CTRL) {
        shift_position(size());
        return 1;
      }
      ascii = ctrl('E'); break;
      
    case FL_BackSpace:
      ascii = ctrl('H'); break;
    case FL_Enter:
    case FL_KP_Enter:
      if (when() & FL_WHEN_ENTER_KEY) {
        caret(size(), 0);
        maybe_do_callback();
        return 1;
      } else if (input_type() == FL_MULTILINE_INPUT && !readonly())
        return replace(caret(), mark(), "\n", 1);
      else 
        return 0;	// reserved for shortcuts
    case FL_Tab:
      if (Fl.event_state(FL_CTRL|FL_SHIFT) || input_type()!=FL_MULTILINE_INPUT || readonly()) return 0;
      return replace(caret(), mark(), &ascii, 1);
/+=
  #ifdef __APPLE__
    case 'c' :
    case 'v' :
    case 'x' :
    case 'z' :
  //    printf("'%c' (0x%02x) pressed with%s%s%s%s\n", ascii, ascii,
  //           Fl::event_state(FL_SHIFT) ? " FL_SHIFT" : "",
  //           Fl::event_state(FL_CTRL) ? " FL_CTRL" : "",
  //           Fl::event_state(FL_ALT) ? " FL_ALT" : "",
  //           Fl::event_state(FL_META) ? " FL_META" : "");
      if (Fl::event_state(FL_META)) ascii -= 0x60;
  //    printf("using '%c' (0x%02x)...\n", ascii, ascii);
      break;
  #endif // __APPLE__
=+/
    default: break;
    }
  
    int i;
    switch (ascii) {
    case 'A'^0x40:
      return shift_position(line_start(caret())) + NORMAL_INPUT_MOVE;
    case 'B'^0x40:
      return shift_position(caret()-1) + NORMAL_INPUT_MOVE;
    case 'C'^0x40: // copy
      return copy(1);
    case 'D'^0x40:
    case '?'^0x40:
      if (readonly()) {
        fl_beep();
        return 1;
      }
      if (mark() != caret()) return cut();
      else return cut(1);
    case 'E'^0x40:
      return shift_position(line_end(caret())) + NORMAL_INPUT_MOVE;
    case 'F'^0x40:
      return shift_position(caret()+1) + NORMAL_INPUT_MOVE;
    case 'H'^0x40:
      if (readonly()) {
        fl_beep();
        return 1;
      }
      if (mark() != caret()) cut();
      else cut(-1);
      return 1;
    case 'K'^0x40:
      if (readonly()) {
        fl_beep();
        return 1;
      }
      if (caret()>=size()) return 0;
      i = line_end(caret());
      if (i == caret() && i < size()) i++;
      cut(caret(), i);
      return copy_cuts();
    case 'N'^0x40:
      i = caret();
      if (line_end(i) >= size()) return NORMAL_INPUT_MOVE;
      while (repeat_num--) {  
        i = line_end(i);
        if (i >= size()) break;
        i++;
      }
      shift_up_down_position(i);
      return 1;
    case 'P'^0x40:
      i = caret();
      if (!line_start(i)) return NORMAL_INPUT_MOVE;
      while(repeat_num--) {
        i = line_start(i);
        if (!i) break;
        i--;
      }
      shift_up_down_position(line_start(i));
      return 1;
    case 'U'^0x40:
      if (readonly()) {
        fl_beep();
        return 1;
      }
      return cut(0, size());
    case 'V'^0x40:
    case 'Y'^0x40:
      if (readonly()) {
        fl_beep();
        return 1;
      }
      Fl.paste(this, 1);
      return 1;
    case 'X'^0x40:
    case 'W'^0x40:
      if (readonly()) {
        fl_beep();
        return 1;
      }
      copy(1);
      return cut();
    case 'Z'^0x40:
    case '_'^0x40:
      if (readonly()) {
        fl_beep();
        return 1;
      }
      return undo();
    case 'I'^0x40:
    case 'J'^0x40:
    case 'L'^0x40:
    case 'M'^0x40:
      if (readonly()) {
        fl_beep();
        return 1;
      }
      // insert a few selected control characters literally:
      if (input_type() != FL_FLOAT_INPUT && input_type() != FL_INT_INPUT)
        return replace(caret(), mark(), &ascii, 1);
    default: break;
    }
 
    return 0;
  }

  int shift_position(int p) {
    return caret(p, Fl.event_state(FL_SHIFT) ? mark() : p);
  }

  int shift_up_down_position(int p) {
    return up_down_position(p, Fl.event_state(FL_SHIFT));
  }

public:

  void draw() {
    if (input_type() == FL_HIDDEN_INPUT) return;
    Fl_Boxtype b = box();
    if (damage() & FL_DAMAGE_ALL) draw_box(b, color());
    super.drawtext(x()+Fl.box_dx(b), y()+Fl.box_dy(b),
		        w()-Fl.box_dw(b), h()-Fl.box_dh(b));
  }

  int handle(Fl_Event event) {
    static int dnd_save_position, dnd_save_mark, drag_start = -1, newpos;
    static Fl_Widget dnd_save_focus;
    switch (event) {
    case FL_FOCUS:
      switch (Fl.event_key()) {
      case FL_Right:
        caret(0);
        break;
      case FL_Left:
        caret(size());
        break;
      case FL_Down:
        up_down_position(0);
        break;
      case FL_Up:
        up_down_position(line_start(size()));
        break;
      case FL_Tab:
      case 0xfe20: // XK_ISO_Left_Tab
        caret(size(),0);
        break;
      default:
        caret(caret(),mark());// turns off the saved up/down arrow position
        break;
      }
      break;
  
    case FL_KEYBOARD:
      if (Fl.event_key() == FL_Tab && mark() != caret()) {
        // Set the current cursor position to the end of the selection...
        if (mark() > caret())
          caret(mark());
        else
          caret(caret());
        return (1);
      } else return handle_key();
  
    case FL_PUSH:
/+=
      if (Fl.dnd_text_ops()) {
        int oldpos = caret(), oldmark = mark();
        Fl_Boxtype b = box();
        super.handle_mouse(
	  x()+Fl.box_dx(b), y()+Fl.box_dy(b),
	  w()-Fl.box_dw(b), h()-Fl.box_dh(b), 0);
        newpos = caret(); 
        caret( oldpos, oldmark );
        if (Fl.focus()==this && !Fl.event_state(FL_SHIFT) && input_type()!=FL_SECRET_INPUT &&
	    (newpos >= mark() && newpos < caret() ||
	    newpos >= caret() && newpos < mark())) {
	  // user clicked in the selection, may be trying to drag
	  drag_start = newpos;
	  return 1;
        }
        drag_start = -1;
      }
  =+/
      if (!(Fl.focus() is this)) {
        Fl.focus(this);
        handle(FL_FOCUS);
      }
      break;
  
    case FL_DRAG:
/+=
      if (Fl.dnd_text_ops()) {
        if (drag_start >= 0) {
	  if (Fl.event_is_click()) return 1; // debounce the mouse
	  // save the position because sometimes we don't get DND_ENTER:
	  dnd_save_position = caret();
	  dnd_save_mark = mark();
	  // drag the data:
	  copy(0); Fl.dnd();
	  return 1;
        }
      }
=+/
      break;
  
    case FL_RELEASE:
      if (Fl.event_button() == 2) {
/+=
        Fl.event_is_click(0); // stop double click from picking a word
        Fl.paste(this, 0);
=+/
      } else if (!Fl.event_is_click()) {
        // copy drag-selected text to the clipboard.
        copy(0);
      } else if (Fl.event_is_click() && drag_start >= 0) {
        // user clicked in the field and wants to reset the cursor position...
        caret(drag_start, drag_start);
        drag_start = -1;
      } else if (Fl.event_clicks()) {
        // user double or triple clicked to select word or whole text
        copy(0);
      }
      // For output widgets, do the callback so the app knows the user
      // did something with the mouse...
      if (readonly()) do_callback();
      return 1;
  /+=
    case FL_DND_ENTER:
      Fl.belowmouse(this); // send the leave events first
      dnd_save_position = caret();
      dnd_save_mark = mark();
      dnd_save_focus = Fl.focus();
      if (dnd_save_focus != this) {
        Fl.focus(this);
        handle(FL_FOCUS);
      }
      // fall through:
    case FL_DND_DRAG: 
      //int p = mouse_position(X, Y, W, H);
  #if DND_OUT_XXXX
      if (Fl::focus()==this && (p>=dnd_save_position && p<=dnd_save_mark ||
		        p>=dnd_save_mark && p<=dnd_save_position)) {
        caret(dnd_save_position, dnd_save_mark);
        return 0;
      }
  #endif
      {
        Fl_Boxtype b = box();
        Fl_Input_::handle_mouse(
	  x()+Fl::box_dx(b), y()+Fl::box_dy(b),
	  w()-Fl::box_dw(b), h()-Fl::box_dh(b), 0);
      }
      return 1;
  
    case FL_DND_LEAVE:
      caret(dnd_save_position, dnd_save_mark);
  #if DND_OUT_XXXX
      if (!focused())
  #endif
      if (dnd_save_focus != this) {
        Fl::focus(dnd_save_focus);
        handle(FL_UNFOCUS);
      }
      return 1;
  
    case FL_DND_RELEASE:
      take_focus();
      return 1;
  
=+/
    default:
      break;
    }
    Fl_Boxtype b = box();
    return super.handletext(event,
	  x()+Fl.box_dx(b), y()+Fl.box_dy(b),
	  w()-Fl.box_dw(b), h()-Fl.box_dh(b));
  }

  this(int x, int y, int w, int h, char[] l=null) {
    super(x, y, w, h, l);
  }
};

// If you define this symbol as zero you will get the peculiar fltk
// behavior where moving off the end of an input field will move the
// cursor into the next field:
// define it as 1 to prevent cursor movement from going to next field:
static const int NORMAL_INPUT_MOVE = 0;

static int ctrl(int x) {
  return ((x)^0x40);
}

// List of characters that are legal in a floating point input field.
// This text string is created at run-time to take the current locale
// into account (for example, continental Europe uses a comma instead
// of a decimal point). For back compatibility reasons, we always 
// allow the decimal point.
/+=
#ifdef HAVE_LOCALECONV
static const char *standard_fp_chars = ".eE+-"; 
static const char *legal_fp_chars = 0L;
#else=+/
static char *legal_fp_chars = ".eE+-\0"; 
/+#endif+/



//
// End of "$Id: input.d 5190 2006-06-09 16:16:34Z mike $".
//
