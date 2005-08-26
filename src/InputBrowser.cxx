//
// "$Id$"
//
// Input Browser (Combo Box) widget for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2001 by Bill Spitzak and others.
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
// Please report all bugs and problems to "fltk-bugs@fltk.org".
//

#include <fltk/InputBrowser.h>
#include <fltk/MenuWindow.h>
#include <fltk/Browser.h>
#include <fltk/Monitor.h>
#include <fltk/events.h>
#include <fltk/damage.h>
#include <fltk/Box.h>
#include <fltk/draw.h>

#include <stdio.h>
#include <string.h>

using namespace fltk;
static Input *ibinput;

static NamedStyle style("InputBrowser", 0, &InputBrowser::default_style);
NamedStyle* InputBrowser::default_style = &::style;

InputBrowser::InputBrowser(int x, int y, int w, int h, const char *l)
  : Menu(x, y, w, h, l),
    m_input(x, y, w, h)
{
  align(ALIGN_LEFT);
  style(default_style);

  if (m_input.parent()) m_input.parent()->remove(m_input);
  m_input.parent(this);
  m_input.callback((Callback_p)input_cb, this);
  m_input.when(fltk::WHEN_ENTER_KEY_CHANGED | fltk::WHEN_RELEASE); // FL_WHEN_CHANGED FL_WHEN_ENTER_KEY_ALWAYS
  
  over_now = false; over_last = true;
  
  minh_ = 10;
  maxw_ = 600;
  maxh_ = 400;
  
  win = 0; list = 0;
  
  ibinput = &m_input;
}

void
InputBrowser::input_cb(Input *w, InputBrowser *ib)
{
  ib->do_callback();
}

// these are only used when in grabbed state so only one exists at once
static MenuWindow *mw;
static InputBrowser *ib;
static Browser *browser;

class ComboWindow : public MenuWindow {
  public:
    int handle(int);
//    ComboWindow(int x, int y, int w, int h) : MenuWindow(x, y, w, h) { box(NO_BOX); }
    ComboWindow(int x, int y, int w, int h) : MenuWindow(x, y, w, h) { ; }
};

int
ComboWindow::handle(int event) {
  switch (event) {
  case MOVE:
  case DRAG:
  case RELEASE:
  case KEY:
    return browser->handle(event);
  }
  return MenuWindow::handle(event);
}


// Destructor needs to be after declaration of ComboWindow win
InputBrowser::~InputBrowser()
{
    m_input.parent(0);    
    if(win) delete win;
}


class ComboBrowser : public Browser {
  public:
    static NamedStyle *default_style;

    int handle(int);
    ComboBrowser(int x, int y, int w, int h);
    static void browser_cb(Widget *w, void *data);
};

extern void browser_glyph(int glyph, const Rectangle&);

static void revert_combostyle(Style *s) {
  s->box_ = BORDER_BOX;
  s->glyph_ = browser_glyph;
}

static NamedStyle combostyle("InputBrowserPopup", revert_combostyle, &Browser::default_style);
NamedStyle* ComboBrowser::default_style = &::combostyle;

ComboBrowser::ComboBrowser(int x, int y, int w, int h)
: Browser(x, y, w, h, 0) 
{
  style(default_style);
}

int
ComboBrowser::handle(int event) {
    if(event_key()==DownKey && (!item() || children()==1)) {
        item(child(0));
        fltk::focus(item());
    }   

    if((event==SHORTCUT||event==KEY) && !(ib->type()&InputBrowser::NONEDITABLE)) {
        if( (event_key()!=EscapeKey) &&
                (event_key()!=UpKey) &&
                (event_key()!=DownKey) &&
                (event_key()!=ReturnKey && !item()) )
            return ibinput->handle(KEY);
    }

    static bool was_wheel=false;
    if(was_wheel) {
        was_wheel=false;
        return 1;
    }

    switch (event) {
        case MOUSEWHEEL: {
                was_wheel=true;
                break;
            }

        case KEY:
        case SHORTCUT:
            if(event_key() == EscapeKey) {
                ib->hide_popup();
                return 1;
            }
            break;

        case PUSH: {
		if (!event_inside(Rectangle(0, 0, w(), h()))) {
			ib->hide_popup();
			// Rectangle below is InputBrowser area 
			if (event_inside(Rectangle(0, -ib->h(), ib->w(), 0))) ib->send(PUSH);
			return 1;
		}
		break;

            }

        case MOVE:
            event = DRAG;

        case RELEASE:
        case DRAG:
        // this causes a drag-in to the widget to work:
            if (event_inside(Rectangle(0, 0, w(), h()))) fltk::pushed(this);
	    else {
	    	fltk::pushed(this);
		return 0;
	    }

        default:
            break;
    }

  return Browser::handle(event);
}

void ComboBrowser::browser_cb(Widget*, void*) {
  // we get callbacks for all keys?
  if (event() != KEY && event() != RELEASE) return;
  if (event() == KEY
      && event_key() != ReturnKey
      && event_key() != KeypadEnter
      && event_key() != ' ')
    return;
  Widget *item = browser->item();
  
  if (!item) return;
  if (item->is_group()) return; // can't select a group!
  
  ib->item(item);
  ib->value(item->label());
  ib->redraw(DAMAGE_VALUE);
  ib->hide_popup();
  
  ib->do_callback();
}

// CET - FIXME - this doesn't seem to be working
// Use this to copy all the items out of one group into another:
class Share_List : public List {
public:
  Menu* other;
  int children(const Menu*, const int* indexes, int level) {
    return other->children(indexes, level);
  }
  Widget* child(const Menu*, const int* indexes, int level) {
    return other->child(indexes, level);
  }
  void flags_changed(const Menu*, Widget* widget) {
    other->list()->flags_changed(other,widget);
  }
} share_list; // only one instance of this.


int
InputBrowser::handle(int e) {
  int TX, TY = 0, TW, TH = h();
  if(type()&NONEDITABLE) {
      TX = 0;
      TW = w();
  } else {
      TX = m_input.x()+m_input.w();
      TW = w()-(m_input.x()+m_input.w());
  }
  if (event_inside(Rectangle(TX,TY,TW,TH)))
      over_now = true;
  else
      over_now = false;
  if((over_now != over_last) && highlight_color())
      redraw_highlight();
  //if (e == ENTER || e == LEAVE) redraw_highlight();

  if (e == FOCUS) fltk::focus(m_input);

  // Scroll using arrow keys
  if ((e == KEY) && (event_key() == UpKey || event_key() == DownKey)) {
    if (!win || !win->visible())
        popup();
//    else
    return win->handle(e);
  
  // all other keys should be sent to Input
  } else if ((event_inside(m_input) || e == KEY)
    && !(type()&NONEDITABLE) && !pushed() && e != MOUSEWHEEL)
  {
    if (e == PUSH) { fltk::pushed(m_input); fltk::focus(m_input); }
    return m_input.handle(e); // if this doesn't work, try send(e)
  }

  switch (e) {
    // Mouse wheel support
    case MOUSEWHEEL: {
      
      // prevent double events
      static bool was_wheel=false;
      if(was_wheel) {
          was_wheel=false;
          return 1;
      } else {
          was_wheel=true;
      }
      
      // horizontal wheel
      if (event_dy() == 0)
          break;
      
      // find next item in the list and replace the current
      int found=-1;
      for (int i=0; i<children(); i++) {
          Widget* w=child(i);
          if (!strncmp(value(), w->label(), strlen(value()))) {
              found=i; break;
          }
      }
      if (event_dy() < 0) {
          if (found==-1 || found==children()-1)
              found=0;
          else
              found++;
      } else if (event_dy() > 0) {
          if (found==-1 || found==0)
              found=children()-1;
          else
              found--;
      }
          m_input.value(child(found)->label());
      break;
    }
    
    case PUSH: {
      if (!win || !win->visible())
          popup();
      else
          hide_popup();
      return 1;
    }

    case FOCUS:
    case UNFOCUS:
      if (type()&NONEDITABLE) break;
      return m_input.handle(e);

    case ENTER: case MOVE: return 1;
  }
  return 0;
}

void
InputBrowser::draw() {
  drawstyle(style(),flags());
  minw_ = w();
  Rectangle r(w(),h()); box()->inset(r);
  int W1 = r.h()*4/5;
  if (damage()&(DAMAGE_ALL|DAMAGE_CHILD)) {
    if (damage()&DAMAGE_ALL) draw_frame();
    m_input.resize(r.x(), r.y(), r.w()-W1, r.h());
    m_input.set_damage(DAMAGE_ALL);
    m_input.copy_style(style()); // force it to use this style
    m_input.box(FLAT_BOX);
    
    // fix for relative coordinates
    push_matrix();
    translate(r.x(),r.y());
    
    m_input.draw();
    
    pop_matrix();
    m_input.set_damage(0);
  }
  if (damage()&(DAMAGE_ALL|DAMAGE_VALUE|DAMAGE_HIGHLIGHT)) {
    Flags f = flags() & ~FOCUSED | OUTPUT;
    if (win && win->visible()) f |= VALUE;
    if (over_now) f |= HIGHLIGHT;
    drawstyle(style(),f);
    
    // draw the little mark at the right:
    r.x(r.x()+r.w()-W1); r.w(W1);
    draw_glyph(GLYPH_DOWN_BUTTON, r);
    over_last = over_now;
  }
}

void
InputBrowser::hide_popup() {
  if (win && win->visible()) {
      fltk::exit_modal();
  }
}

void
InputBrowser::popup() {
    bool resize_only = false;

    if(!win || !win->visible()) 
    {
        Group::current(0);

        if(!win) {
            win = new ComboWindow(0,0,0,0); // this will be moved later
            win->set_override();

            win->begin();
            list = new ComboBrowser(0,0,0,0);
            list->box(UP_BOX);
            list->callback(ComboBrowser::browser_cb, this);
            list->when(WHEN_CHANGED | WHEN_RELEASE_ALWAYS | WHEN_ENTER_KEY_ALWAYS);        
            list->end();

            win->end();
            win->box(UP_BOX);

            mw = win;
            browser = list;
	    ib = this;
        }        

        share_list.other = this;
        list->list(&share_list);

        list->indented((type()&INDENTED) != 0);
        win->color(list->color());

    } else
        resize_only = true;

    list->layout();
    
      int W = list->width(); //+list->scrollbar.w();
      // magic constant 4 = border width/height (is there a way to calculate it?)
      int H = list->height() + 4;
      
      if (W > maxw_) W = maxw_;
      if (H > maxh_) H = maxh_;
      if (W < minw_) W = minw_;
      if (H < minh_) H = minh_;
      int X = event_x_root()-event_x();
      int Y = event_y_root()-event_y()+h();
      
      // I don't know what this code does, but it doesn't work
/*      const Monitor& monitor = Monitor::find(event_x_root(), event_y_root());
      int down = monitor.h() - Y;
      int up = event_y_root() - event_y();
      if (H > down) {
        if (up > down) {
          Y = event_y_root() - event_y() - H;
          if (Y < 0) { Y = 0; H = up; }
        } else {
          H = down;
        }
      }
      if (X + W > monitor.r()) {
        X = monitor.r() - W;
        if (X < 0) { X = 0; W = monitor.r(); }
      }*/
      
      win->resize(X, Y, W, H);
      list->Widget::resize(W, H);

      // find the currently selected item in the list
      list->value(0);
      for (int i=0; i<list->children(); i++) {
          Widget* w=list->child(i);
          if (!strncmp(value(), w->label(), strlen(value()))) {
              list->value(i);
              list->make_item_visible();
              break;
          }
      }

    if(resize_only) return;

    set_value();
    redraw(DAMAGE_VALUE);

    win->exec(0, true);
    win->hide();

    if(type()&NONEDITABLE) throw_focus();
    else fltk::focus(m_input);

    clear_value();
    redraw(DAMAGE_VALUE);
}

Widget* InputBrowser::item() const {
	return list->item();
}

Widget* InputBrowser::item(Widget* v) const {
	return list->item(v);
}


//222
// End of "$Id$".
//
