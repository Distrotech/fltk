// generated by Fast Light User Interface Designer (fluid) version 2.0100

#ifndef CubeViewUI_h
#define CubeViewUI_h
#include <fltk/Window.h>
#include <fltk/Group.h>
#include <fltk/ValueSlider.h>
#include <fltk/ThumbWheel.h>
#include <stdio.h>
#include <fltk/Slider.h>
#include <fltk/InvisibleBox.h>
#include "CubeView.h"

class CubeViewUI  {
public:
  CubeViewUI();
private:
  fltk::Window *mainWindow;
public:
      fltk::ValueSlider *zoom;
private:
      inline void cb_zoom_i(fltk::ValueSlider*, void*);
      static void cb_zoom(fltk::ValueSlider*, void*);
public:
      fltk::Group *VChange;
        fltk::ThumbWheel *vrot;
private:
        inline void cb_vrot_i(fltk::ThumbWheel*, void*);
        static void cb_vrot(fltk::ThumbWheel*, void*);
public:
        fltk::Slider *ypan;
private:
        inline void cb_ypan_i(fltk::Slider*, void*);
        static void cb_ypan(fltk::Slider*, void*);
public:
      fltk::Group *HChange;
        fltk::Slider *xpan;
private:
        inline void cb_xpan_i(fltk::Slider*, void*);
        static void cb_xpan(fltk::Slider*, void*);
public:
        fltk::ThumbWheel *hrot;
private:
        inline void cb_hrot_i(fltk::ThumbWheel*, void*);
        static void cb_hrot(fltk::ThumbWheel*, void*);
public:
      fltk::Group *MainView;
        fltk::InvisibleBox *cframe;
        CubeView *cube;
  void show();
};
#endif
