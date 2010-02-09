/*
 *  Fl_Printer.h
 *
 */
#include <FL/Fl.H>
#include <FL/x.H>
#include <FL/fl_draw.H>

/**
 * @brief Provides an OS-independent interface to printing under MSWindows and Mac OS X.
 *
 At present, this class is only implemented for MSWindows and Mac OS X.
 It allows to use all FLTK drawing, color, text, and clip functions, and to have them operate
 on printed page(s). There are two main ways to use it.
 <ul><li>Print any widget (standard, custom, window) as it appears on screen, with optional
 translation and scaling. This is done by calling print_widget().
 <li>Use a series of FLTK graphics commands (e.g., font, text, lines, colors, clip) to
 compose a page appropriately shaped for printing. 
 </ul>
 In both cases, begin by start_job(), start_page(), printable_rect() and origin() calls
 and finish by end_page() and end_job() calls.
 */
class Fl_Printer {
   int y_offset;
   int x_offset;
#ifdef __APPLE__
   float scale_x;
   float scale_y;
   PMPrintSession  printSession;
   PMPageFormat    pageFormat;
   PMPrintSettings printSettings;
#elif defined(WIN32)
   int   abortPrint;
   PRINTDLG      pd;
   HDC           hPr;
   int           prerr;
#endif
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
   and with origin at the top left of the page or of the printable page area.
   @return 0 iff OK
   */
  int start_page (void);
  
  /**
   @brief Computes the origin and size of the printable area of the page.
   *
   Values are in the same unit as that used by FLTK drawing functions,
   are unchanged by calls to origin(), but are changed by scale() calls.
   Values account for the user-selected paper type and print orientation.
   @return 0 iff OK.
   */
  int printable_rect(int *x, int *y, int *w, int *h);
  
  /**
   @brief Sets the position in page coordinates of the origin of graphics functions.
   *
   Arguments should be expressed relatively to the result of a previous printable_rect() call.
   That is, <tt>printable_rect(&x, &y, &w, &h); origin(x, y);</tt> sets the graphics origin at the
   top left of the page printable area.
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
   After a scale() call, do a printable_rect() call to get the new coordinates of the printable page area.
   Successive scale() calls don't combine their effects.
   @param scale_x Horizontal dimensions of plot are multiplied by this quantity.
   @param scale_y Same as above, vertically.
   */
  void scale (float scale_x, float scale_y);
  
  /**
   @brief Draws the widget on the printed page.
   *
   The widget's position on the printed page is determined by a previous call to origin()
   and by the optional delta_x and delta_y arguments.
   Its dimensions are in points unless there was a previous call to scale().
   @param[in] widget Any FLTK widget (e.g., standard, custom, window).
   @param[in] delta_x Optional horizontal offset for positioning the widget relatively
   to the current origin of graphics functions.
   @param[in] delta_y Same as above, vertically.
   */
  void print_widget(Fl_Widget* widget, int delta_x = 0, int delta_y = 0);
  
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
