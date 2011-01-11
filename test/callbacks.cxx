// callback.cxx FLTK3

#include <fltk3/run.h>
#include <fltk3/Window.h>
#include <fltk3/Slider.h>
#include <fltk3/Button.h>
#include <fltk3/IntInput.h>
#include <stdlib.h>

using namespace fltk3;

IntInput* intinput;

void copy_callback(Widget*, void* v) {
  Slider* slider = (Slider*)v;
  slider->value(strtol(intinput->value(), 0, 0));
}

void down_callback(Widget*, void* v) {
  Slider* slider = (Slider*)v;
  slider->value(slider->value()-1);
  char buf[20]; sprintf(buf, "%d", (int)slider->value());
  intinput->value(buf);
}

void up_callback(Widget*, void* v) {
  Slider* slider = (Slider*)v;
  slider->value(slider->value()+1);
  char buf[20]; sprintf(buf, "%d", (int)slider->value());
  intinput->value(buf);
}

void slider_callback(Widget* w, void*) {
  Slider* slider = (Slider*)w;
  char buf[20]; sprintf(buf, "%d", (int)slider->value());
  intinput->value(buf);
}

void exit_callback(Widget *, void *) {
  exit(0);
}

int main(int argc, char ** argv) {
  Window window(320, 90);
  window.begin();
  IntInput intinput(10,10,100,20);
  ::intinput = &intinput;
  intinput.value("0");
  Button copy_button(110, 10, 100, 20, "copy to slider");
  Slider slider(10,35,300,20);
  slider.type(FL_HOR_NICE_SLIDER);
  slider.callback(slider_callback);
  copy_button.callback(copy_callback, &slider);
  slider.range(-10,10);
  slider.step(1);
  slider.value(0);
  Button down_button(50,60,50,20,"down");
  down_button.callback(down_callback, &slider);
  Button up_button(150,60,50,20,"up");
  up_button.callback(up_callback, &slider);
  Button exit_button(250,60,50,20,"exit");
  exit_button.callback(exit_callback);
  window.end();
  window.show(argc,argv);
  return run();
}
