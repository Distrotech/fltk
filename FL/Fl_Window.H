//
// "$Id$"
//
// Window header file for the Fast Light Tool Kit (FLTK).
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
   Fl_Window widget . */

#ifndef FLTK1_Window_H
#define FLTK1_Window_H

#include <fltk3/Window.h>
#include "Fl_Group.H"

#if 0 // TODO: FLTK123

#define FL_WINDOW 0xF0
#define FL_DOUBLE_WINDOW 0xF1

class Fl_X;


#endif // TODO: FLTK123

class FL_EXPORT Fl_Window : public Fl_Group {

protected:

  // in Wrapper: virtual void draw();
  
  // TODO: FLTK123  virtual void flush();
  void force_position(int force) {
    ((fltk3::Window*)_p)->force_position(force); 
  }
  int force_position() const {
    return ((fltk3::Window*)_p)->force_position(); 
  }
  
public:

  Fl_Window(int w, int h, const char* title= 0) {
    _p = new fltk3::Window(w, h, title); 
    _p->wrapper(this);
  }
  Fl_Window(int x, int y, int w, int h, const char* title = 0) {
    _p = new fltk3::Window(x, y, w, h, title);
    _p->wrapper(this);
  }
  virtual Fl_Window* as_window() { 
    return this; 
  }
  // in Wrapper: virtual ~Fl_Window();  
  // in Wrapper: virtual int handle(int);
  // in Wrapper: virtual void resize(int,int,int,int);
  // in Wrapper: virtual void show();
  // in Wrapper: virtual void hide();
  void show(int argc, char **argv) { 
    ((fltk3::Window*)_p)->show(argc, argv); 
  }
  void border(int b) {
    ((fltk3::Window*)_p)->border(b); 
  }
  void clear_border() {
    ((fltk3::Window*)_p)->clear_border(); 
  }
  unsigned int border() const {
    return ((fltk3::Window*)_p)->border(); 
  }
  void set_override() {
    ((fltk3::Window*)_p)->set_override(); 
  }
  unsigned int override() {
    return ((fltk3::Window*)_p)->override(); 
  }
  void set_modal() {
    ((fltk3::Window*)_p)->set_modal(); 
  }
  unsigned int modal() {
    return ((fltk3::Window*)_p)->modal(); 
  }
  void set_non_modal() {
    ((fltk3::Window*)_p)->set_non_modal(); 
  }
  unsigned int non_modal() const {
    return ((fltk3::Window*)_p)->non_modal(); 
  }
  void set_menu_window() {
    ((fltk3::Window*)_p)->set_menu_window(); 
  }
  unsigned int menu_window() const {
    return ((fltk3::Window*)_p)->menu_window(); 
  }
  void set_tooltip_window() {
    ((fltk3::Window*)_p)->set_tooltip_window(); 
  }
  unsigned int tooltip_window() const {
    return ((fltk3::Window*)_p)->tooltip_window(); 
  }
  void hotspot(int x, int y, int offscreen = 0) {
    ((fltk3::Window*)_p)->hotspot(x, y, offscreen); 
  }
  void hotspot(const Fl_Widget *w, int offscreen = 0) {
    ((fltk3::Window*)_p)->hotspot((fltk3::Widget*)((Fl_Widget*)w)->_p, offscreen); 
  }
  void hotspot(const Fl_Widget& p, int offscreen = 0) {
    hotspot(&p, offscreen);
  }
  void free_position() {
    ((fltk3::Window*)_p)->free_position(); 
  }
  void size_range(int a, int b, int c=0, int d=0, int e=0, int f=0, int g=0) {
    ((fltk3::Window*)_p)->size_range(a, b, c, d, e, f, g); 
  }
  const char* label() const {
    return ((fltk3::Window*)_p)->label(); 
  }
  const char* iconlabel() const {
    return ((fltk3::Window*)_p)->iconlabel(); 
  }
  void label(const char *l) {
    ((fltk3::Window*)_p)->label(l); 
  }
  void iconlabel(const char *il) {
    ((fltk3::Window*)_p)->iconlabel(il); 
  }
  void label(const char* label, const char* iconlabel) {
    ((fltk3::Window*)_p)->label(label, iconlabel); 
  }
  void copy_label(const char* a) {
    ((fltk3::Window*)_p)->copy_label(a); 
  }
  const char* xclass() const {
    return ((fltk3::Window*)_p)->xclass(); 
  }
  void xclass(const char* c) {
    ((fltk3::Window*)_p)->xclass(c); 
  }
  const void* icon() const {
    return ((fltk3::Window*)_p)->icon(); 
  }
  void icon(const void * ic) {
    ((fltk3::Window*)_p)->icon(ic); 
  }
  int shown() {
    return ((fltk3::Window*)_p)->shown(); 
  }
  void fullscreen() {
    ((fltk3::Window*)_p)->fullscreen(); 
  }
  void fullscreen_off(int x, int y, int w, int h) {
    ((fltk3::Window*)_p)->fullscreen_off(x, y, w, h); 
  }
  void iconize() {
    ((fltk3::Window*)_p)->iconize(); 
  }
  int x_root() const {
    return ((fltk3::Window*)_p)->x_root(); 
  }
  int y_root() const {
    return ((fltk3::Window*)_p)->y_root(); 
  }
  void make_current() {
    ((fltk3::Window*)_p)->make_current(); 
  }
  void cursor(Fl_Cursor a, Fl_Color b=FL_BLACK, Fl_Color c=FL_WHITE) {
    ((fltk3::Window*)_p)->cursor((fltk3::Cursor)a, (fltk3::Color)b, (fltk3::Color)c); 
  }
  void default_cursor(Fl_Cursor a, Fl_Color b=FL_BLACK, Fl_Color c=FL_WHITE) {
    ((fltk3::Window*)_p)->default_cursor((fltk3::Cursor)a, (fltk3::Color)b, (fltk3::Color)c); 
  }  
  static Fl_Window *current() {
    return (Fl_Window*)( fltk3::Window::current()->wrapper() );
  }
  static void default_callback(Fl_Window *w, void* v) {
    fltk3::Window::default_callback((fltk3::Window*)((Fl_Widget*)w)->_p,v);
  }
  static void default_xclass(const char *c) {
    fltk3::Window::default_xclass(c);
  }
  static const char *default_xclass() {
    return fltk3::Window::default_xclass();
  }
  
};

#endif

//
// End of "$Id$".
//
