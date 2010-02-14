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
  int old_x, old_y, new_x, new_y, is_window;
  if ( ! widget->visible() ) return;
  is_window = (widget->as_window() != NULL);
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
  if (new_x != old_x + delta_x || new_y != old_y + delta_y) origin(old_x + delta_x, old_y + delta_y);
  // find subwindows of widget and print them
  traverse(widget);
  // reset origin to where it was
  if(delta_x || delta_y) origin(old_x, old_y);
}

void Fl_Printer::traverse(Fl_Widget *widget)
{
  Fl_Group *g = widget->as_group();
  if (!g) return;
  int is_window = (widget->as_window() != NULL);
  int n = g->children();
  for (int i = 0; i < n; i++) {
    Fl_Widget *c = g->child(i);
    if (c->as_window()) {
      // compute desired position of top-left of window c
      int x_offset = c->x() - (is_window ? 0 : widget->x());
      int y_offset = c->y() - (is_window ? 0 : widget->y());
      print_widget(c, x_offset, y_offset);
      }
    else traverse(c);
  }
}

void Fl_Printer::origin(int *x, int *y)
{
  if (x) *x = x_offset;
  if (y) *y = y_offset;
}

void Fl_Printer::print_window_part(const uchar *image_data, int w, int h)
{
  Fl_RGB_Image *image = new Fl_RGB_Image(image_data, w, h);
  image->draw(0, 0);
  add_image(image);
}

void Fl_Printer::add_image(Fl_Image *image)
{
  struct chain_elt *elt =  (struct chain_elt *)calloc(sizeof(struct chain_elt), 1);
  elt->image = image;
  if (image_list_) { elt->next = image_list_; }
  image_list_ = elt;
}

void Fl_Printer::delete_image_list()
{
  while(image_list_) {
    struct chain_elt *next = image_list_->next;
    delete image_list_->image;
    free(image_list_);
    image_list_ = next;
    }
}
