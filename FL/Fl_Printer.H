/*
 *  Fl_Printer.H
 *
 */

#ifndef Fl_Printer_H
#define Fl_Printer_H

#include <FL/Fl.H>
#include <FL/x.H>
#include <FL/Fl_Image.H>


/**
 * @brief Provides an OS-independent interface to printing under MSWindows and Mac OS X.
 *
 At present, this class is only implemented for MSWindows and Mac OS X.
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
class Fl_Printer {
  struct chain_elt {
    Fl_Image *image;
    const uchar *data;
    struct chain_elt *next;
  };
  int y_offset;
  int x_offset;
  struct chain_elt *image_list_; // chained list of Fl_Image's used in this page
#ifdef __APPLE__
  float scale_x;
  float scale_y;
  float angle; // rotation angle in radians
  PMPrintSession  printSession;
  PMPageFormat    pageFormat;
  PMPrintSettings printSettings;
#elif defined(WIN32)
  int   abortPrint;
  PRINTDLG      pd;
  HDC           hPr;
  int           prerr;
  int left_margin;
  int top_margin;
#endif
  
  void add_image(Fl_Image *image, const uchar *data); // adds an image to the page image list
  void delete_image_list(); // deletes the page image list
  void traverse(Fl_Widget *widget); // finds subwindows of widget and prints them
#ifdef WIN32
  void absolute_printable_rect(int *x, int *y, int *w, int *h);
#endif
private:
  /**
   @brief Translates the current graphics origin accounting for the current rotation.
   *
   This function is only useful after a rotate() call. Each translate() call must be matched by an untranslate() call.
   */
  void translate(int x, int y);
  
  /**
   @brief Undoes the effect of a previous translate() call.
   */
  void untranslate(void);
public:
  /** 
   @brief The constructor.
   */
  Fl_Printer(void);
  
  /**
   @brief Starts a print job.
   *
   @param[in] pagecount the total number of pages of the job
   @param[out] frompage if non-null, *frompage is set to the first page the user wants printed
   @param[out] topage if non-null, *topage is set to the last page the user wants printed
   @return 0 iff OK
   */
  int start_job(int pagecount, int *frompage = NULL, int *topage = NULL);
  
  /**
   @brief Starts a new printed page
   *
   The page coordinates are initially in points, i.e., 1/72 inch, 
   and with origin at the top left of the printable page area.
   @return 0 iff OK
   */
  int start_page (void);
  
  /**
   @brief Computes the width and height of the printable area of the page.
   *
   Values are in the same unit as that used by FLTK drawing functions,
   are unchanged by calls to origin(), but are changed by scale() calls.
   Values account for the user-selected paper type and print orientation.
   @return 0 iff OK.
   */
  int printable_rect(int *w, int *h);
  
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
   void margins(int *left, int *top, int *right, int *bottom);
  
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
  void origin(int x, int y);
  
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
  void scale (float scale_x, float scale_y);
  
  /**
   @brief Rotates the graphics operations relatively to paper.
   *
   The rotation is centered on the current graphics origin. Successive rotate() calls don't combine their effects.
   On MSWindows, Fl_RGB_Image's don't rotate well; print_window_part() is an efficient workaround.
   @param angle Rotation angle in counterclockwise degrees.
   */
   void rotate(float angle);
  
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
  int end_page (void);
  
  /**
   @brief To be called at the end of a print job.
   */
  void end_job (void);
    
};

#endif // Fl_Printer_H
