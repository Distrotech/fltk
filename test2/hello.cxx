// hello.cxx (example1)

#include <fltk/Window.h>
#include <fltk/Widget.h>
#include <fltk/run.h>
using namespace fltk;

int main(int argc, char **argv) {
  Window *window = new Window(300, 180);
  window->begin();
  Widget *box = new Widget(20, 40, 260, 100, "Hello, World!");
  // FIXME: box->box(UP_BOX);
  // FIXME: box->labelfont(HELVETICA_BOLD_ITALIC);
  // FIXME: box->labelsize(36);
  // FIXME: box->labeltype(SHADOW_LABEL);
  window->end();
  window->show(argc, argv);
  return run();
}
