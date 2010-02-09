/*
 *  Fl_Printer.cxx
 *  FLTK
 *
 */

#ifdef __APPLE__
#include <src/Fl_Printer_mac.mm>
#elif defined(WIN32)
#include <src/Fl_Printer_win32.cxx>
#endif

static int is_child(Fl_Widget *child, Fl_Widget *parent, int *px, int *py)
//returns 1 iff child is a subwindow of parent
//in that case puts in px,py the offset of child relatively to parent
{
  *px = child->x();
  *py = child->y();
  if (parent->parent() != NULL) { // if parent is not the topmost window
    *px -= parent->x(); // subtract parent's offset in its window
    *py -= parent->y();
    }
  while(1) {
    child = child->parent();
    if (child == NULL) return 0;
    if (child->parent() != NULL && child->type() >= FL_WINDOW) {
      *px += child->x();
      *py += child->y();
      }
    if (child == parent) return 1;
  }
}

void Fl_Printer::print_widget(Fl_Widget* widget, int delta_x, int delta_y) 
{ 
  int old_x, old_y, x_offset, y_offset;
  Fl_Window *win, *target;
  if ( ! widget->visible() ) return;
  widget->damage(FL_DAMAGE_ALL); 
  if (delta_x || delta_y) {
    origin(&old_x, &old_y);
    origin(old_x + delta_x, old_y + delta_y);
    }
  widget->draw();
  if (delta_x || delta_y) origin(old_x, old_y);
  // set target to the window where widget lies
  if (widget->type() < FL_WINDOW) target = widget->window(); 
  else target = (Fl_Window*)widget;
  // find all windows that are one level within widget, and print them
  win = Fl::first_window();
  while(win) {
    if (win->visible() && win->window() == target && is_child(win, widget, &x_offset, &y_offset) ) {
      print_widget(win, delta_x + x_offset, delta_y + y_offset);
    }
    win = Fl::next_window(win);
  }
}

void Fl_Printer::origin(int *x, int *y)
{
  if (x) *x = x_offset;
  if (y) *y = y_offset;
}


