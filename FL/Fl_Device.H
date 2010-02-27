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
  virtual Fl_Device *set_current();
  static Fl_Device *current();
};
extern Fl_Device *fl_device;

class Fl_Display;

/**
 * @brief Provides an OS-independent interface to printing.
 *
 It allows to use all FLTK drawing, color, text, and clip functions, and to have them operate
 on printed page(s). There are two main, non exclusive, ways to use it.
 <ul><li>Print any widget (standard, custom, Fl_Window except Fl_Gl_Window) as it appears 
 on screen, with optional translation and scaling. This is done by calling print_widget() 
 or print_window_part().
 <li>Use a series of FLTK graphics commands (e.g., font, text, lines, colors, clip) to
 compose a page appropriately shaped for printing. 
 </ul>
 In both cases, begin by start_job(), start_page(), printable_rect() and origin() calls
 and finish by end_page() and end_job() calls.
 \see class Fl_Gl_Printer to print Fl_Gl_Window's.
 */
class Fl_Virtual_Printer : public Fl_Device {
private:
  struct chain_elt {
    Fl_Image *image;
    const uchar *data;
    struct chain_elt *next;
  };
  Fl_Display *current_display_;
  void add_image(Fl_Image *image, const uchar *data); // adds an image to the page image list
  void traverse(Fl_Widget *widget); // finds subwindows of widget and prints them
  /**
   @brief Translates the current graphics origin accounting for the current rotation.
   *
   This function is only useful after a rotate() call. Each translate() call must be matched by an untranslate() call.
   */
  virtual void translate(int x, int y);
  
  /**
   @brief Undoes the effect of a previous translate() call.
   */
  virtual void untranslate(void);
protected:
  int y_offset;
  int x_offset;
  struct chain_elt *image_list_; // chained list of Fl_Image's used in this page

  /** 
   @brief The constructor.
   */
  Fl_Virtual_Printer(void) { current_display_ = (Fl_Display*)fl_device;};
  void delete_image_list(); // deletes the page image list
public:
  
  /**
   @brief Starts a print job.
   *
   @param[in] pagecount the total number of pages of the job
   @param[out] frompage if non-null, *frompage is set to the first page the user wants printed
   @param[out] topage if non-null, *topage is set to the last page the user wants printed
   @return 0 iff OK
   */
  virtual int start_job(int pagecount, int *frompage = NULL, int *topage = NULL);
  
  /**
   @brief Starts a new printed page
   *
   The page coordinates are initially in points, i.e., 1/72 inch, 
   and with origin at the top left of the printable page area.
   @return 0 iff OK
   */
  virtual int start_page (void);
  
  /**
   @brief Computes the width and height of the printable area of the page.
   *
   Values are in the same unit as that used by FLTK drawing functions,
   are unchanged by calls to origin(), but are changed by scale() calls.
   Values account for the user-selected paper type and print orientation.
   @return 0 iff OK.
   */
  virtual int printable_rect(int *w, int *h);
  
  /**
   @brief Computes the dimensions of margins that lie between the printable page area and
   the full page.
   *
   Values are in the same unit as that used by FLTK drawing functions. They are changed
   by scale() calls.
   @param[out] left If non-null, *left is set to the left margin size.
   @param[out] top If non-null, *top is set to the top margin size.
   @param[out] right If non-null, *right is set to the right margin size.
   @param[out] bottom If non-null, *bottom is set to the bottom margin size.
   */
  virtual void margins(int *left, int *top, int *right, int *bottom);
  
  /**
   @brief Sets the position in page coordinates of the origin of graphics functions.
   *
   Arguments should be expressed relatively to the result of a previous printable_rect() call.
   That is, <tt>printable_rect(&w, &h); origin(w/2, 0);</tt> sets the graphics origin at the
   top center of the page printable area.
   Successive origin() calls don't combine their effects.
   @param[in] x Horizontal position in page coordinates of the desired origin of graphics functions.
   @param[in] y Same as above, vertically.
   */
  virtual void origin(int x, int y);
  
  /**
   @brief Computes the page coordinates of the current origin of graphics functions.
   *
   @param[out] x If non-null, *x is set to the horizontal page offset of graphics origin.
   @param[out] y Same as above, vertically.
   */
  void origin(int *x, int *y);
  
  /**
   @brief Changes the scaling of page coordinates.
   *
   This function also resets the origin of graphics functions at top left of printable page area.
   After a scale() call, do a printable_rect() call to get the new dimensions of the printable page area.
   Successive scale() calls don't combine their effects.
   @param scale_x Horizontal dimensions of plot are multiplied by this quantity.
   @param scale_y Same as above, vertically.
   */
  virtual void scale (float scale_x, float scale_y);
  
  /**
   @brief Rotates the graphics operations relatively to paper.
   *
   The rotation is centered on the current graphics origin. Successive rotate() calls don't combine their effects.
   On MSWindows, Fl_RGB_Image's don't rotate well; print_window_part() is an efficient workaround.
   @param angle Rotation angle in counterclockwise degrees.
   */
  virtual void rotate(float angle);
  
  /**
   @brief Draws the widget on the printed page.
   *
   The widget's position on the printed page is determined by the last call to origin()
   and by the optional delta_x and delta_y arguments.
   Its dimensions are in points unless there was a previous call to scale().
   <br>Under MSWindows, most printers don't allow interaction
   between what is being printed and what was previously printed at the same position on the page.
   Consequently, Fl_RGB_Image's are printed without transparency, Fl_Pixmap's are printed
   with black color where a transparent background is expected, fl_read_image() returns a
   white rectangle. A workaround is to use the print_window_part() call. 
   <br>Under Mac OS X, transparent RGB images and pixmaps are correctly reproduced
   on paper.
   @param[in] widget Any FLTK widget (e.g., standard, custom, window).
   @param[in] delta_x Optional horizontal offset for positioning the widget relatively
   to the current origin of graphics functions.
   @param[in] delta_y Same as above, vertically.
   */
  void print_widget(Fl_Widget* widget, int delta_x = 0, int delta_y = 0);
  
  /**
   @brief Prints a rectangular part of an on-screen window.
   *
   @param win The window from where to capture.
   @param x The rectangle left
   @param y The rectangle top
   @param w The rectangle width
   @param h The rectangle height
   @param delta_x Optional horizontal offset from current graphics origin where to print the captured rectangle.
   @param delta_y As above, vertically.
   */
  void print_window_part(Fl_Window *win, int x, int y, int w, int h, int delta_x = 0, int delta_y = 0);
  
  /**
   @brief To be called at the end of each page.
   *
   @return 0 iff OK.
   */
  virtual int end_page (void);
  
  /**
   @brief To be called at the end of a print job.
   */
  virtual void end_job (void);
  
  /**
   @brief Returns the display device currently in action.
   */
  Fl_Display *current_display() {return current_display_; };
};

#ifdef __APPLE__
class Fl_Quartz_Printer : public Fl_Virtual_Printer {
private:
  float scale_x;
  float scale_y;
  float angle; // rotation angle in radians
  PMPrintSession  printSession;
  PMPageFormat    pageFormat;
  PMPrintSettings printSettings;
  void translate(int x, int y);
  void untranslate(void);
public:
  Fl_Quartz_Printer(void) : Fl_Virtual_Printer() {};
  int start_job(int pagecount, int *frompage = NULL, int *topage = NULL);
  int start_page (void);
  int printable_rect(int *w, int *h);
  void margins(int *left, int *top, int *right, int *bottom);
  void origin(int x, int y);
  void scale (float scale_x, float scale_y);
  void rotate(float angle);
  int end_page (void);
  void end_job (void);
};
#endif

#ifdef WIN32
class Fl_GDI_Printer : public Fl_Virtual_Printer {
private:
  int   abortPrint;
  PRINTDLG      pd;
  HDC           hPr;
  int           prerr;
  int left_margin;
  int top_margin;
  void translate(int x, int y);
  void untranslate(void);
  void absolute_printable_rect(int *x, int *y, int *w, int *h);
public:
  Fl_GDI_Printer(void);
  int start_job(int pagecount, int *frompage = NULL, int *topage = NULL);
  int start_page (void);
  int printable_rect(int *w, int *h);
  void margins(int *left, int *top, int *right, int *bottom);
  void origin(int x, int y);
  void scale (float scale_x, float scale_y);
  void rotate(float angle);
  int end_page (void);
  void end_job (void);
};
#endif

#if ! (defined(WIN32) || defined(__APPLE__) )
const int NO_PAGE_FORMATS=30;
const int page_formats[NO_PAGE_FORMATS][2]={

// A* // index(Ai) = i
{2384, 3370}, //A0
{1684, 2384}, //A1
{1191, 1684}, //A2
{842, 1191},  //A3
{595, 842},   //A4
{420, 595},   //A5
{297, 420},   //A6
{210, 297},   //A7
{148, 210},   //A8
{105, 148},   //A9

// B* // index(Bi) = i+10
{2920, 4127}, //B0
{2064, 2920}, //B1
{1460, 2064}, //B2
{1032, 1460}, //B3
{729, 1032},  //B4
{516, 729},   //B5
{316, 516},   //B6
{258, 516},   //B7
{181, 258},   //B8
{127, 181},   //B9
{91,127},     //B10

// others (look at Fl_Printer.H} //
{462, 649},
{312, 623},
{541, 719},
{595, 935},
{1224, 790},
{612, 1009},
{612, 790},
{791, 1224},
{297, 683}

};

class Fl_PS_Printer : public Fl_Virtual_Printer {
  enum SHAPE{NONE=0, LINE, LOOP, POLYGON, POINTS};
  
  class Clip{
  public:
    int x, y, w, h;
    Clip *prev;
  };
  Clip * clip_;
  
  int lang_level_;
  int font_;
  int size_;
  Fl_Color color_;
  FILE *output;
  //int nPages;
  int gap_;
  int pages_;
  
  double width_;
  double height_;
  
  int shape_;
  int linewidth_;// need for clipping, lang level 1-2
  int linestyle_;//
  int interpolate_; //interpolation of images
  unsigned char cr_,cg_,cb_;
  char  linedash_[256];//should be enought
  void concat();  // transform ror scalable dradings...
  void reconcat(); //invert
  void recover(); //recovers the state afrer grestore (such as line styles...)
  void reset();
  
  uchar * mask;
  int mx; // width of mask;
  int my; // mask lines
  //Fl_Color bg_;
  int (*close_cmd_)(FILE *);
  int page_policy_;
  int nPages;
  int orientation_;

  float scale_x;
  float scale_y;
  float angle;
  void translate(int x, int y);
  void untranslate(void);
  
protected:
  double pw_, ph_;
  static const int page_formats[NO_PAGE_FORMATS][2];
    
  uchar bg_r, bg_g, bg_b;
  /*  int alpha_mask(const uchar * data, int w, int h, int D, int LD=0);
  */
  void draw(const char* s, int n, int x, int y) {transformed_draw(s,n,x,y); };
  void draw(int angle, const char *str, int n, int x, int y);
  void transformed_draw(const char* s, int n, double x, double y); //precise text placing
  void transformed_draw(const char* s, double x, double y);
/*  
  void draw_scalled_image(const uchar *data, double x, double y, double w, double h, int iw, int ih, int D=3, int LD=0);
  void draw_scalled_image_mono(const uchar *data, double x, double y, double w, double h, int iw, int ih, int D=3, int LD=0);
  void draw_scalled_image(Fl_Draw_Image_Cb call, void *data, double x, double y, double w, double h, int iw, int ih, int D);
  void draw_scalled_image_mono(Fl_Draw_Image_Cb call, void *data, double x, double y, double w, double h, int iw, int ih, int D);
*/
public:
    void page_policy(int p);
  int page_policy(){return page_policy_;};
  
  
  void close_command( int (*cmd)(FILE *)){close_cmd_=cmd;};
  FILE * file(){return output;};
  //void orientation (int o);
  
  //Fl_PS_Printer(FILE *o, int lang_level, int pages = 0); // ps (also multi-page) constructor
  //Fl_PS_Printer(FILE *o, int lang_level, int x, int y, int w, int h); //eps constructor
  ~Fl_PS_Printer();
  void interpolate(int i){interpolate_=i;};
  int interpolate(){return interpolate_;}
  
  void page(double pw, double ph, int media = 0);
  void page(int format);
  
  void Fl_PS_Printer::place(double x, double y, double tx, double ty, double scale = 1);
  
  Fl_PS_Printer(void);
  int start_job(int pagecount, int *frompage = NULL, int *topage = NULL);
  int start_page (void);
  int printable_rect(int *w, int *h);
  void margins(int *left, int *top, int *right, int *bottom);
  void origin(int x, int y);
  void scale (float scale_x, float scale_y);
  void rotate(float angle);
  int end_page (void);
  void end_job (void);
  
public:
  
  enum Page_Format{
    A0 = 0, 
    A1,
    A2,
    A3,
    A4,
    A5,
    A6,
    A7,
    A8,
    A9,
    B0,
    B1,
    B2,
    B3,
    B4,
    B5,
    B6,
    B7,
    B8,
    B9,
    B10,
    C5E,
    DLE,
    EXECUTIVE,
    FOLIO,
    LEDGER,
    LEGAL,
    LETTER,
    TABLOID,
    ENVELOPE,
    MEDIA = 0x1000
  };
  enum Page_Layout {PORTRAIT = 0, LANDSCAPE = 0x100, REVERSED = 0x200, ORIENTATION = 0x300};
  
protected:  // implementation of drawing methods
  
  void color(Fl_Color c);
  //void bg_color(Fl_Color bg);
  void color(uchar r, uchar g, uchar b);
  Fl_Color color(){return color_;};
  
  
  void push_clip(int x, int y, int w, int h);
  int clip_box(int x, int y, int w, int h, int &X, int &Y, int &W, int &H);
  int not_clipped(int x, int y, int w, int h);
  void push_no_clip();
  void pop_clip();
    
  void line_style(int style, int width=0, char* dashes=0);
  
  void rect(int x, int y, int w, int h);
  void rectf(int x, int y, int w, int h);

  void xyline(int x, int y, int x1);
  void xyline(int x, int y, int x1, int y2);
  void xyline(int x, int y, int x1, int y2, int x3);
  
  void yxline(int x, int y, int y1);
  void yxline(int x, int y, int y1, int x2);
  void yxline(int x, int y, int y1, int x2, int y3);
  
  void line(int x1, int y1, int x2, int y2);
  void line(int x1, int y1, int x2, int y2, int x3, int y3);  

  void loop(int x0, int y0, int x1, int y1, int x2, int y2);
  void loop(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3);
  void polygon(int x0, int y0, int x1, int y1, int x2, int y2);
  void polygon(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3);
  void point(int x, int y);

  void begin_points();
  void begin_line();
  void begin_loop();
  void begin_polygon();
  void vertex(double x, double y);
  void curve(double x, double y, double x1, double y1, double x2, double y2, double x3, double y3);
  void circle(double x, double y, double r);
  void arc(double x, double y, double r, double start, double a);
  void arc(int x, int y, int w, int h, double a1, double a2);
  void pie(int x, int y, int w, int h, double a1, double a2);
  void end_points();
  void end_line();
  void end_loop();
  void end_polygon();
  void begin_complex_polygon(){begin_polygon();};
  void gap(){gap_=1;};
  void end_complex_polygon(){end_polygon();};
  void transformed_vertex(double x, double y);


  void font(int face, int size);
  int font(){return font_;};
  int size(){return size_;};
  double Fl_PS_Printer::width(unsigned c);
  double Fl_PS_Printer::width(const char* s, int n);
  int Fl_PS_Printer::descent();
  int Fl_PS_Printer::height();
};
#endif

#ifdef __APPLE__
class Fl_Printer : public Fl_Quartz_Printer {
};
#elif defined(WIN32)
class Fl_Printer : public Fl_GDI_Printer {
};
#else
class Fl_Printer : public Fl_PS_Printer {
};
#endif

class Fl_Display : public Fl_Device {
};

#ifdef __APPLE__
class Fl_Quartz_Display : public Fl_Display {
public:
  Fl_Quartz_Display() {};
};
#elif defined(WIN32)
class Fl_GDI_Display : public Fl_Display {
public:
  Fl_GDI_Display() {};
};
#else
extern int   fl_height();
extern int   fl_descent();
extern double fl_width(unsigned int);
extern double fl_width(const char* txt, int n);
class Fl_Xlib_Display : public Fl_Display {
protected:
  friend class Fl_PS_Printer; //RK: temporary hack for font sizes
public:
  Fl_Xlib_Display() {};
};
#endif

#endif // Fl_Device_H
