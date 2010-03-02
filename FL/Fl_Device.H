/*
 *  Fl_Device.H
 *
 */

#ifndef Fl_Device_H
#define Fl_Device_H

#include <FL/x.H>
#ifdef WIN32
#include <Commdlg.h>
#elif defined(__APPLE__)
#else
#include <stdio.h>
#endif

/**
 @brief A pure virtual class subclassed to send graphics output to display, local files, or printers.
 */
class Fl_Device {
protected:
  friend void fl_rect(int x, int y, int w, int h);
  friend void fl_rectf(int x, int y, int w, int h);
  friend void fl_line_style(int style, int width, char* dashes);
  friend void fl_xyline(int x, int y, int x1);
  friend void fl_xyline(int x, int y, int x1, int y2);
  friend void fl_xyline(int x, int y, int x1, int y2, int x3);
  friend void fl_yxline(int x, int y, int y1);
  friend void fl_yxline(int x, int y, int y1, int x2);
  friend void fl_yxline(int x, int y, int y1, int x2, int y3);
  friend void fl_line(int x, int y, int x1, int y1);
  friend void fl_line(int x, int y, int x1, int y1, int x2, int y2);
  friend void fl_draw(const char *str, int n, int x, int y);
  friend void fl_draw(int angle, const char *str, int n, int x, int y);
  friend void fl_font(Fl_Font face, Fl_Fontsize size);
  friend void fl_color(Fl_Color c);
  friend void fl_color(uchar r, uchar g, uchar b);
  friend void fl_point(int x, int y);
  friend void fl_loop(int x0, int y0, int x1, int y1, int x2, int y2);
  friend void fl_loop(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3);
  friend void fl_polygon(int x0, int y0, int x1, int y1, int x2, int y2);
  friend void fl_polygon(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3);
  friend void fl_concat();
  friend void fl_reconcat();
  friend void fl_begin_points();
  friend void fl_begin_line();
  friend void fl_begin_loop();
  friend void fl_begin_polygon();
  friend void fl_vertex(double x, double y);
  friend void fl_curve(double x, double y, double x1, double y1, double x2, double y2, double x3, double y3);
  friend void fl_circle(double x, double y, double r);
  friend void fl_arc(double x, double y, double r, double start, double a);
  friend void fl_arc(int x, int y, int w, int h, double a1, double a2);
  friend void fl_pie(int x, int y, int w, int h, double a1, double a2);
  friend void fl_end_points();
  friend void fl_end_line();
  friend void fl_end_loop();
  friend void fl_end_polygon();
  friend void fl_transformed_vertex(double x, double y);
  friend void fl_push_clip(int x, int y, int w, int h);
  friend int fl_clip_box(int x, int y, int w, int h, int &X, int &Y, int &W, int &H);
  friend int fl_not_clipped(int x, int y, int w, int h);
  friend void fl_push_no_clip();
  friend void fl_pop_clip();
  friend void fl_begin_complex_polygon();
  friend void fl_gap();
  friend void fl_end_complex_polygon();
  virtual void rect(int x, int y, int w, int h);
  virtual void rectf(int x, int y, int w, int h);
  virtual void line_style(int style, int width=0, char* dashes=0);
  virtual void xyline(int x, int y, int x1);
  virtual void xyline(int x, int y, int x1, int y2);
  virtual void xyline(int x, int y, int x1, int y2, int x3);
  virtual void yxline(int x, int y, int y1);
  virtual void yxline(int x, int y, int y1, int x2);
  virtual void yxline(int x, int y, int y1, int x2, int y3);
  virtual void line(int x, int y, int x1, int y1);
  virtual void line(int x, int y, int x1, int y1, int x2, int y2);
  virtual void draw(const char *str, int n, int x, int y);
  virtual void draw(int angle, const char *str, int n, int x, int y);
  virtual void font(Fl_Font face, Fl_Fontsize size);
  virtual void color(Fl_Color c);
  virtual void color(uchar r, uchar g, uchar b);
  virtual void point(int x, int y);
  virtual void loop(int x0, int y0, int x1, int y1, int x2, int y2);
  virtual void loop(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3);
  virtual void polygon(int x0, int y0, int x1, int y1, int x2, int y2);
  virtual void polygon(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3);
  virtual void begin_points();
  virtual void begin_line();
  virtual void begin_loop();
  virtual void begin_polygon();
  virtual void vertex(double x, double y);
  virtual void curve(double x, double y, double x1, double y1, double x2, double y2, double x3, double y3);
  virtual void circle(double x, double y, double r);
  virtual void arc(double x, double y, double r, double start, double a);
  virtual void arc(int x, int y, int w, int h, double a1, double a2);
  virtual void pie(int x, int y, int w, int h, double a1, double a2);
  virtual void end_points();
  virtual void end_line();
  virtual void end_loop();
  virtual void end_polygon();
  virtual void begin_complex_polygon();
  virtual void gap();
  virtual void end_complex_polygon();
  virtual void transformed_vertex(double x, double y);
  virtual void push_clip(int x, int y, int w, int h);
  virtual int clip_box(int x, int y, int w, int h, int &X, int &Y, int &W, int &H);
  virtual int not_clipped(int x, int y, int w, int h);
  virtual void push_no_clip();
  virtual void pop_clip();
  
public:
  /**
   @brief Sets this device (display, local file, printer) as the target of future graphics calls.
   *
   @return  The current target device of graphics calls.
   */
  virtual Fl_Device *set_current();
  
  virtual ~Fl_Device() {};

  /**
   @brief    Returns the current target device of graphics calls.
   */
  static Fl_Device *current();
};
extern Fl_Device *fl_device;

/**
 @brief A virtual class subclassed for OS-specific display graphics.
 */
class Fl_Display : public Fl_Device {
  friend class Fl_PSfile_Device; //RK: temporary hack for font sizes
};

#if defined(__APPLE__) || defined(FL_DOXYGEN)
/**
 @brief The Mac OS X-specific display graphics class.
 */
class Fl_Quartz_Display : public Fl_Display {
public:
  Fl_Quartz_Display() {};
};
#endif
#if defined(WIN32) || defined(FL_DOXYGEN)
/**
 @brief The MSWindows-specific display graphics class.
 */
class Fl_GDI_Display : public Fl_Display {
public:
  Fl_GDI_Display() {};
};
#endif
#if !( defined(__APPLE__) || defined(WIN32)) || defined(FL_DOXYGEN)
/**
 @brief The X11-specific display graphics class.
 */
class Fl_Xlib_Display : public Fl_Display {
public:
  Fl_Xlib_Display() {};
};
#endif

#endif // Fl_Device_H
