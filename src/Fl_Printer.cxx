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

void Fl_Printer::print_widget(Fl_Widget* widget, int delta_x, int delta_y) 
{ 
  int old_x, old_y, new_x, new_y, x_offset, y_offset, is_topwindow, is_window;
  Fl_Window *win, *target;
  if ( ! widget->visible() ) return;
  is_window = widget->type() >= FL_WINDOW;
  is_topwindow = is_window && widget->window() == NULL;
  widget->damage(FL_DAMAGE_ALL);
  // set origin to the desired top-left position of the widget
  origin(&old_x, &old_y);
  new_x = old_x + delta_x;
  new_y = old_y + delta_y;
  if (!is_window) {
    new_x -= widget->x();
    new_y -= widget->y();
    }
  if (new_x != old_x || new_y != old_y) origin(new_x, new_y);
  // if widget is a window, clip all drawings to the window area
  if (is_window) fl_push_clip(0, 0, widget->w(), widget->h() );
  widget->draw();
  if (is_window) fl_pop_clip();
  // reset origin to where it was
  if(new_x != old_x || new_y != old_y) origin(old_x, old_y);
  // set target to the window where widget lies
  if (!is_window) target = widget->window(); 
  else target = (Fl_Window*)widget;
  // find all windows that are one level within widget, and print them
  win = Fl::first_window();
  while(win) {
    if (win->visible() && win->window() == target && widget->contains(win) ) {
      // compute desired position of top-left of win
      x_offset = win->x() - (is_window ? 0 : widget->x());
      y_offset = win->y() - (is_window ? 0 : widget->y());
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

void Fl_Printer::print_window_part(const uchar *image_data, int w, int h)
{
  Fl_RGB_Image *tmp_image = new Fl_RGB_Image(image_data, w, h);
  // the image is duplicated so the caller can free it, 
  // because it must be kept until the page is closed
  image = tmp_image->copy();
  delete tmp_image;
  image->draw(0, 0);
}
