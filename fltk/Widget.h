// "$Id: Widget.h 6518 2008-11-11 22:31:26Z spitzak $"
//
// Copyright 1998-2006 by Bill Spitzak and others.
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

#ifndef fltk2_Widget_h
#define fltk2_Widget_h

#include <fltk3/Wrapper.h>
#include <fltk3/Widget.h>
#include "Style.h"
#include "Rectangle.h"
#include "Font.h"
#include "Box.h"
#include "LabelType.h"


namespace fltk {

  class FL_API Group;
  class FL_API Widget;
  class FL_API Window;

#if 0 // TODO: FLTK123
class FL_API Symbol;
class FL_API AssociationType;
class FL_API AssociationFunctor;
struct Cursor;
#endif // TODO: FLTK123

typedef void (Callback )(Widget*, void*);
typedef Callback* Callback_p;
typedef void (Callback0)(Widget*);
typedef void (Callback1)(Widget*, long);

#if 0 // TODO: FLTK123

#ifdef FLTK_1_WIDGET  // back-compatability section:
FL_API Font* font(int);
#endif
  
#endif // TODO: FLTK123
  
  // TODO: this should be derived from Rectangle!
  class FL_API Widget : public fltk3::WidgetWrapper {
  
public:
    
    // TODO: this should be derived from Rectangle!
    int x() {
      return ((fltk3::Widget*)_p)->x();
    }
    int y() {
      return ((fltk3::Widget*)_p)->y();
    }
    int w() {
      return ((fltk3::Widget*)_p)->w();
    }
    int h() {
      return ((fltk3::Widget*)_p)->h();
    }
    

    Widget() {}
    Widget(int x, int y, int w, int h, const char *l=0) {
      _p = new fltk3::Widget(x, y, w, h, l);
      _p->wrapper(this);
    }
    // in Wrapper: virtual ~Widget();
    // in Wrapper: virtual void draw();
    // in Wrapper: virtual int handle(int);
    void box(Box *f) {
      ((fltk3::Widget*)_p)->box(f->fltk3_id);
    }
    Box *box() const {
      return fltk2_box_list + ((fltk3::Widget*)_p)->box();
    }    
    Box *buttonbox() const {
      // TODO: not in F3  return fltk2_box_list + ((fltk3::Widget*)_p)->buttonbox();
      return 0;
    }
    void buttonbox(Box *f) {
      // TODO: not in F3  ((fltk3::Widget*)_p)->buttonbox(f->fltk3_id);
    }
    void labelfont(Font *f) {
      ((fltk3::Widget*)_p)->labelfont(f->fltk3_id);
    }
    Font *labelfont() const {
      return fltk2_font_list + ((fltk3::Widget*)_p)->labelfont();
    }
    void labeltype(LabelType *l) {
      ((fltk3::Widget*)_p)->labeltype(l->fltk3_id);
    }
    void labelsize(float a) {
      ((fltk3::Widget*)_p)->labelsize((fltk3::Fontsize)a);
    }
    Group* parent() const { 
      return (Group*)( ((fltk3::Widget*)_p)->parent()->wrapper() );
    }
    void parent(Group* w) {
      ((fltk3::Widget*)_p)->parent( (fltk3::Group*)( ((Widget*)w)->_p ) );
    }
    Window* window() const {
      return (Window*)( ((fltk3::Widget*)_p)->window()->wrapper() );
    }
    uchar type() const {
      // TODO: synchronize the type variables!
      return ((fltk3::Widget*)_p)->type();
    }
    void type(uchar t) {
      // TODO: synchronize the type variables!
      ((fltk3::Widget*)_p)->type(t);
    }
    const char* label() const {
      return ((fltk3::Widget*)_p)->label();
    }
    void label(const char* a) {
      ((fltk3::Widget*)_p)->label(a);
    }
    void copy_label(const char* a) {
      ((fltk3::Widget*)_p)->copy_label(a);
    }
    const char *tooltip() const	{
      return ((fltk3::Widget*)_p)->tooltip();
    }
    void tooltip(const char *t)	{
      ((fltk3::Widget*)_p)->tooltip(t);
    }
    Callback_p callback() const	{
      return (Callback_p)((fltk3::Widget*)_p)->callback();
    }
    void callback(Callback* cb, void* p) { 
      ((fltk3::Widget*)_p)->callback( (fltk3::Callback*)cb, p );
    }
    void callback(Callback* cb) {
      ((fltk3::Widget*)_p)->callback( (fltk3::Callback*)cb );
    }
    void callback(Callback0* cb)	{
      ((fltk3::Widget*)_p)->callback( (fltk3::Callback0*)cb );
    }
    void callback(Callback1* cb, long p=0) {
      ((fltk3::Widget*)_p)->callback( (fltk3::Callback1*)cb, p );
    }
    void do_callback() {
      ((fltk3::Widget*)_p)->do_callback();
    }
    void do_callback(Widget* o,void* arg=0) { 
      ((fltk3::Widget*)_p)->do_callback( (fltk3::Widget*)( ((Widget*)o)->_p ), arg );
    }
    void do_callback(Widget* o,long arg) { 
      ((fltk3::Widget*)_p)->do_callback( (fltk3::Widget*)( ((Widget*)o)->_p ), arg );
    }    
    void color(Color c) {
      ((fltk3::Widget*)_p)->color((fltk3::Color)c);
    }
    void clear_flag(unsigned f) {
      // TODO: FLTK123 - support more flags!
      unsigned int f3type = ((fltk3::Widget*)_p)->type();
      if (f&LAYOUT_VERTICAL) f3type |= 1;
      ((fltk3::Widget*)_p)->type(f3type);
    }

#if 0 // TODO: FLTK123
    static void default_callback(Widget*, void*);
  int	send(int event);
  virtual void layout();
  const Style* style() const { return style_; }
  void	style(const Style* s) { style_ = s; }
  void	style(const Style& s) { style_ = &s; }
  bool	copy_style(const Style* s);
  static NamedStyle* default_style;
  static Symbol* default_glyph;
  enum WidgetVisualType {
    RESERVED_TYPE      = 0x64,
    TOGGLE    = RESERVED_TYPE+1,
    RADIO     = RESERVED_TYPE+2,
    GROUP_TYPE         = 0xe0,
    WINDOW_TYPE        = 0xf0
  };
  bool	is_group() const	{ return type_ >= GROUP_TYPE; }
  bool	is_window() const	{ return type_ >= WINDOW_TYPE; }
  bool  resize(int x,int y,int w,int h);
  bool	position(int x, int y)	;
  bool	resize(int w, int h)	;
  void  get_absolute_rect( Rectangle *rect ) const;
  const Symbol* image() const	{ return image_; }
  void	image(const Symbol* a)	{ image_ = a; }
  void	image(const Symbol& a)	{ image_ = &a; }
  unsigned shortcut() const	;
  void	shortcut(unsigned key)	;
  bool	add_shortcut(unsigned key);
  bool	remove_shortcut(unsigned key);
  void  remove_shortcuts()	;
  unsigned label_shortcut() const;
  bool	test_label_shortcut() const;
  bool	test_shortcut() const	;
  bool  test_shortcut(bool) const;
  void*	user_data() const	{ return user_data_; }
  void	user_data(void* v)	{ user_data_ = v; }
  long	argument() const	{ return (long)user_data_; }
  void	argument(long v)	{ user_data_ = (void*)v; }
  uchar when() const		{ return when_; }
  void	when(uchar i)		{ when_ = i; }
  bool	contains(const Widget*) const;
  bool	inside(const Widget* o) const { return o && o->contains(this); }
  bool	pushed() const		;
  bool	focused() const		;
  bool	belowmouse() const	;
  Flags	flags() const		{ return flags_; }
  void	flags(Flags f)  	{ flags_ = f; }
  void	set_flag(unsigned f)	{ flags_ |= f; }
  void	invert_flag(unsigned f)	{ flags_ ^= f; }
  void	set_flag(unsigned f,bool b) { flags_ = (flags_&~f)|(b?f:0); }
  bool	flag(unsigned f) const	{ return (flags_ & f) != 0; }
  bool	any_of(unsigned f) const{ return (flags_ & f) != 0; }
  bool	all_of(unsigned f) const{ return (flags_ & f) == f; }
  bool	state() const 		{ return flag(STATE); }
  bool  state(bool);
  bool	set()			{ return state(true); }
  bool	clear()			{ return state(false); }
  void	setonly();
  Flags	align() const		{ return flags_&ALIGN_MASK; }
  void	align(unsigned a)	{ flags_ = (flags_ & (~ALIGN_MASK)) | a; }
  bool	visible() const		{ return !flag(INVISIBLE); }
  bool	visible_r() const	;
  void	show()			;
  void	hide()			;
  void	set_visible()		{ clear_flag(INVISIBLE); }
  void	clear_visible()		{ set_flag(INVISIBLE); }
  bool	active() const		{ return !flag(INACTIVE); }
  bool	active_r() const	;
  void	activate()		;
  void	activate(int b)		{ if (b) activate(); else deactivate(); }
  void	deactivate()		;
  bool	output() const		{ return flag(OUTPUT); }
  void	set_output()		{ set_flag(OUTPUT); }
  void	clear_output()		{ clear_flag(OUTPUT); }
  bool	takesevents() const	{ return !any_of(OUTPUT|INVISIBLE|INACTIVE); }
  bool	changed() const		{ return flag(CHANGED); }
  void	set_changed()		{ set_flag(CHANGED); }
  void	clear_changed()		{ clear_flag(CHANGED); }
  bool	selected() const	{ return flag(SELECTED); }
  void	set_selected()		{ set_flag(SELECTED); }
  void	clear_selected()	{ clear_flag(SELECTED); }
  bool	click_to_focus()	{ return flag(CLICK_TO_FOCUS); }
  void  set_click_to_focus()	{ set_flag(CLICK_TO_FOCUS); }
  void	clear_click_to_focus()	{ clear_flag(CLICK_TO_FOCUS); }
  bool	tab_to_focus()		{ return flag(TAB_TO_FOCUS); }
  void  set_tab_to_focus()	{ set_flag(TAB_TO_FOCUS); }
  void	clear_tab_to_focus()	{ clear_flag(TAB_TO_FOCUS|CLICK_TO_FOCUS); }
  bool  horizontal() const	{ return !flag(LAYOUT_VERTICAL);}
  bool	vertical() const	{ return flag(LAYOUT_VERTICAL);}
  void	set_horizontal()	{ clear_flag(LAYOUT_VERTICAL); }
  void	set_vertical()		{ set_flag(LAYOUT_VERTICAL); }
  bool	take_focus()		;
  void	throw_focus()		;
  void	redraw()		;
  void	redraw(uchar c)		;
  void	redraw_label()		;
  void	redraw_highlight()	;
  void	redraw(const Rectangle&);
  uchar	damage() const		{ return damage_; }
  void	set_damage(uchar c)	{ damage_ = c; } // should be called damage(c)
  void  relayout()		;
  void	relayout(uchar damage)	;
  uchar layout_damage() const	{ return layout_damage_; }
  void	layout_damage(uchar c)	{ layout_damage_ = c; }
  void	add_timeout(float)	;
  void	repeat_timeout(float)	;
  void  remove_timeout()	;
  void	make_current() const	;
  void	draw_background() const	;
  void  draw_frame() const	;
  void  draw_box() const	;
  void  draw_box(const Rectangle& r) const ; // multiple boxes drawing for a single Widget
  void	draw_label() const	;
  void  draw_label(const Rectangle&, Flags) const ;
  void  draw_glyph(int, const Rectangle&) const ;
  void	cursor(Cursor*) const	;
  void	measure_label(int&, int&) const ;
  Symbol* glyph()		const;
  Font*	textfont()		const;
  LabelType* labeltype()	const;
  Color	color()			const;
  Color	textcolor()		const;
  Color	selection_color()	const;
  Color	selection_textcolor()	const;
  Color	buttoncolor()		const;
  Color	labelcolor()		const;
  Color	highlight_color()	const;
  Color	highlight_textcolor()	const;
  float labelsize()		const;
  float textsize()		const;
  float leading()		const;
  unsigned char scrollbar_align() const;
  unsigned char scrollbar_width() const;
  void glyph(Symbol*)		;
  void textfont(Font*)		;
  void textcolor(Color a)	;
  void selection_color(Color)	;
  void selection_textcolor(Color);
  void buttoncolor(Color)	;
  void labelcolor(Color)	;
  void highlight_color(Color)	;
  void highlight_textcolor(Color);
  void textsize(float a)	;
  void leading(float a)		;
  void scrollbar_align(unsigned char);
  void scrollbar_width(unsigned char);
  void  add(const AssociationType&, void* data);
  void  set(const AssociationType&, void* data);
  void* get(const AssociationType&) const;
  void* foreach(const AssociationType&, AssociationFunctor&) const;
  bool  remove(const AssociationType&, void* data);
  bool  find(const AssociationType&, void* data) const;
#endif // TODO: FLTK123
};

enum { // Widget::when() values
  WHEN_NEVER		= 0,
  WHEN_CHANGED		= 1,
  WHEN_RELEASE		= 4,
  WHEN_RELEASE_ALWAYS	= 6,
  WHEN_ENTER_KEY	= 8,
  WHEN_ENTER_KEY_ALWAYS	=10,
  WHEN_ENTER_KEY_CHANGED=11,
  WHEN_NOT_CHANGED	= 2 // modifier bit to disable changed() test
};

}

#endif

//
// End of "$Id: Widget.h 6518 2008-11-11 22:31:26Z spitzak $".
//
