//
// "$Id$"
//
// fltk3::HelpView widget routines.
//
// Copyright 1997-2010 by Easy Software Products.
// Image support by Matthias Melcher, Copyright 2000-2009.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//
// Contents:
//
//   fltk3::HelpView::add_block()       - Add a text block to the list.
//   fltk3::HelpView::add_link()        - Add a new link to the list.
//   fltk3::HelpView::add_target()      - Add a new target to the list.
//   fltk3::HelpView::compare_targets() - Compare two targets.
//   fltk3::HelpView::do_align()        - Compute the alignment for a line in
//                                     a block.
//   fltk3::HelpView::draw()            - Draw the fltk3::HelpView widget.
//   fltk3::HelpView::format()          - Format the help text.
//   fltk3::HelpView::format_table()    - Format a table...
//   fltk3::HelpView::free_data()       - Free memory used for the document.
//   fltk3::HelpView::get_align()       - Get an alignment attribute.
//   fltk3::HelpView::get_attr()        - Get an attribute value from the string.
//   fltk3::HelpView::get_color()       - Get an alignment attribute.
//   fltk3::HelpView::handle()          - Handle events in the widget.
//   fltk3::HelpView::fltk3::HelpView()    - Build a fltk3::HelpView widget.
//   fltk3::HelpView::~Fl_Help_View()   - Destroy a fltk3::HelpView widget.
//   fltk3::HelpView::load()            - Load the specified file.
//   fltk3::HelpView::resize()          - Resize the help widget.
//   fltk3::HelpView::topline()         - Set the top line to the named target.
//   fltk3::HelpView::topline()         - Set the top line by number.
//   fltk3::HelpView::value()           - Set the help text directly.
//   scrollbar_callback()            - A callback for the scrollbar.
//

//
// Include necessary header files...
//

#include <fltk3/HelpView.h>
#include <fltk3/Window.h>
#include <fltk3/Pixmap.h>
#include <fltk3/x.h>
#include <stdio.h>
#include <stdlib.h>
#include <fltk3/utf8.h>
#include <fltk3/filename.h>	// fltk3::open_uri()
#include "flstring.h"
#include <ctype.h>
#include <errno.h>
#include <math.h>

#if defined(WIN32) && ! defined(__CYGWIN__)
#  include <io.h>
#  include <direct.h>
#else
#  include <unistd.h>
#endif // WIN32

#define MAX_COLUMNS	200


//
// Typedef the C API sort function type the only way I know how...
//

extern "C"
{
  typedef int (*compare_func_t)(const void *, const void *);
}


//
// Local functions...
//

static int	quote_char(const char *);
static void	scrollbar_callback(fltk3::Widget *s, void *);
static void	hscrollbar_callback(fltk3::Widget *s, void *);

//
// global flag for image loading (see get_image).
//

static char initial_load = 0;

//
// Broken image...
//

static const char *broken_xpm[] =
		{
		  "16 24 4 1",
		  "@ c #000000",
		  "  c #ffffff",
		  "+ c none",
		  "x c #ff0000",
		  // pixels
		  "@@@@@@@+++++++++",
		  "@    @++++++++++",
		  "@   @+++++++++++",
		  "@   @++@++++++++",
		  "@    @@+++++++++",
		  "@     @+++@+++++",
		  "@     @++@@++++@",
		  "@ xxx  @@  @++@@",
		  "@  xxx    xx@@ @",
		  "@   xxx  xxx   @",
		  "@    xxxxxx    @",
		  "@     xxxx     @",
		  "@    xxxxxx    @",
		  "@   xxx  xxx   @",
		  "@  xxx    xxx  @",
		  "@ xxx      xxx @",
		  "@              @",
		  "@              @",
		  "@              @",
		  "@              @",
		  "@              @",
		  "@              @",
		  "@              @",
		  "@@@@@@@@@@@@@@@@",
		  NULL
		};

static fltk3::Pixmap broken_image(broken_xpm);

//
// Simple margin stack for fltk3::HelpView::format()...
//

struct fl_margins {
  int depth_;
  int margins_[100];

  fl_margins() { clear();  }

  int clear() {
//    puts("fl_margins::clear()");

    depth_ = 0;
    return margins_[0] = 4;
  }

  int current() { return margins_[depth_]; }

  int pop() {
//    printf("fl_margins::pop(): depth_=%d, xx=%d\n", depth_,
//           depth_ > 0 ? margins_[depth_ - 1] : 4);

    if (depth_ > 0) {
      depth_ --;
      return margins_[depth_];
    } else return 4;
  }

  int push(int indent) {
    int xx;

    xx = margins_[depth_] + indent;

//    printf("fl_margins::push(indent=%d): depth_=%d, xx=%d\n", indent,
//           depth_ + 1, xx);

    if (depth_ < 99) {
      depth_ ++;
      margins_[depth_] = xx;
    }

    return xx;
  }
};

//
// All the stuff needed to implement text selection in fltk3::HelpView
//

/* matt:
 * We are trying to keep binary compatibility with previous versions
 * of FLTK. This means that we are limited to adding static variables
 * only to not enlarge the fltk3::HelpView class. Lucky for us, only one
 * text can be selected system wide, so we can remember the selection
 * in a single set of variables.
 *
 * Still to do:
 * - &word; style characters mess up our count inside a word boundary
 * - we can only select words, no individual characters
 * - no dragging of the selection into another widget
 * - selection must be cleared if another widget get focus!
 * - write a comment for every new function
 */

/*
The following functions are also used to draw stuff and should be replaced with
local copies that are much faster when merely counting:

fltk3::color(fltk3::Color);
fltk3::rectf(int, int, int, int);
fltk3::push_clip(int, int, int, int);
fltk3::xyline(int, int, int);
fltk3::rect()
fltk3::line()
img->draw()
*/

// We don't put the offscreen buffer in the help view class because
// we'd need to include x.h in the header...
static fltk3::Offscreen fl_help_view_buffer;
int fltk3::HelpView::selection_first = 0;
int fltk3::HelpView::selection_last = 0;
int fltk3::HelpView::selection_push_first = 0;
int fltk3::HelpView::selection_push_last = 0;
int fltk3::HelpView::selection_drag_first = 0;
int fltk3::HelpView::selection_drag_last = 0;
int fltk3::HelpView::selected = 0;
int fltk3::HelpView::draw_mode = 0;
int fltk3::HelpView::mouse_x = 0;
int fltk3::HelpView::mouse_y = 0;
int fltk3::HelpView::current_pos = 0;
fltk3::HelpView *fltk3::HelpView::current_view = 0L;
fltk3::Color fltk3::HelpView::hv_selection_color;
fltk3::Color fltk3::HelpView::hv_selection_text_color;

/*
 * Limitation: if a word contains &code; notations, we will calculate a wrong length.
 *
 * This function must be optimized for speed!
 */
void fltk3::HelpView::hv_draw(const char *t, int x, int y)
{
  if (selected && current_view==this && current_pos<selection_last && current_pos>=selection_first) {
    fltk3::Color c = fltk3::color();
    fltk3::color(hv_selection_color);
    int w = (int)fltk3::width(t);
    if (current_pos+(int)strlen(t)<selection_last) 
      w += (int)fltk3::width(' ');
    fltk3::rectf(x, y+fltk3::descent()-fltk3::height(), w, fltk3::height());
    fltk3::color(hv_selection_text_color);
    fltk3::draw(t, x, y);
    fltk3::color(c);
  } else {
    fltk3::draw(t, x, y);
  }
  if (draw_mode) {
    int w = (int)fltk3::width(t);
    if (mouse_x>=x && mouse_x<x+w) {
      if (mouse_y>=y-fltk3::height()+fltk3::descent()&&mouse_y<=y+fltk3::descent()) {
        int f = current_pos;
        int l = f+strlen(t); // use 'quote_char' to calculate the true length of the HTML string
        if (draw_mode==1) {
          selection_push_first = f;
          selection_push_last = l;
        } else {
          selection_drag_first = f;
          selection_drag_last = l;
        }
      }
    }
  }
}


/** Adds a text block to the list. */
fltk3::HelpBlock *					// O - Pointer to new block
fltk3::HelpView::add_block(const char   *s,	// I - Pointer to start of block text
                	int           xx,	// I - X position of block
			int           yy,	// I - Y position of block
			int           ww,	// I - Right margin of block
			int           hh,	// I - Height of block
			unsigned char border)	// I - Draw border?
{
  fltk3::HelpBlock	*temp;				// New block


//  printf("add_block(s = %p, xx = %d, yy = %d, ww = %d, hh = %d, border = %d)\n",
//         s, xx, yy, ww, hh, border);

  if (nblocks_ >= ablocks_)
  {
    ablocks_ += 16;

    if (ablocks_ == 16)
      blocks_ = (fltk3::HelpBlock *)malloc(sizeof(fltk3::HelpBlock) * ablocks_);
    else
      blocks_ = (fltk3::HelpBlock *)realloc(blocks_, sizeof(fltk3::HelpBlock) * ablocks_);
  }

  temp = blocks_ + nblocks_;
  memset(temp, 0, sizeof(fltk3::HelpBlock));
  temp->start   = s;
  temp->end     = s;
  temp->x       = xx;
  temp->y       = yy;
  temp->w       = ww;
  temp->h       = hh;
  temp->border  = border;
  temp->bgcolor = bgcolor_;
  nblocks_ ++;

  return (temp);
}


/** Adds a new link to the list. */
void fltk3::HelpView::add_link(const char *n,	// I - Name of link
                      int        xx,	// I - X position of link
		      int        yy,	// I - Y position of link
		      int        ww,	// I - Width of link text
		      int        hh)	// I - Height of link text
{
  fltk3::HelpLink	*temp;			// New link
  char		*target;		// Pointer to target name


  if (nlinks_ >= alinks_)
  {
    alinks_ += 16;

    if (alinks_ == 16)
      links_ = (fltk3::HelpLink *)malloc(sizeof(fltk3::HelpLink) * alinks_);
    else
      links_ = (fltk3::HelpLink *)realloc(links_, sizeof(fltk3::HelpLink) * alinks_);
  }

  temp = links_ + nlinks_;

  temp->x       = xx;
  temp->y       = yy;
  temp->w       = xx + ww;
  temp->h       = yy + hh;

  strlcpy(temp->filename, n, sizeof(temp->filename));

  if ((target = strrchr(temp->filename, '#')) != NULL)
  {
    *target++ = '\0';
    strlcpy(temp->name, target, sizeof(temp->name));
  }
  else
    temp->name[0] = '\0';

  nlinks_ ++;
}


/** Adds a new target to the list. */
void fltk3::HelpView::add_target(const char *n,	// I - Name of target
			      int        yy)	// I - Y position of target
{
  fltk3::HelpTarget	*temp;			// New target


  if (ntargets_ >= atargets_)
  {
    atargets_ += 16;

    if (atargets_ == 16)
      targets_ = (fltk3::HelpTarget *)malloc(sizeof(fltk3::HelpTarget) * atargets_);
    else
      targets_ = (fltk3::HelpTarget *)realloc(targets_, sizeof(fltk3::HelpTarget) * atargets_);
  }

  temp = targets_ + ntargets_;

  temp->y = yy;
  strlcpy(temp->name, n, sizeof(temp->name));

  ntargets_ ++;
}

/** Compares two targets.*/
int							// O - Result of comparison
fltk3::HelpView::compare_targets(const fltk3::HelpTarget *t0,	// I - First target
                             const fltk3::HelpTarget *t1)	// I - Second target
{
  return (strcasecmp(t0->name, t1->name));
}

/** Computes the alignment for a line in a block.*/
int						// O - New line
fltk3::HelpView::do_align(fltk3::HelpBlock *block,	// I - Block to add to
                      int          line,	// I - Current line
		      int          xx,		// I - Current X position
		      int          a,		// I - Current alignment
		      int          &l)		// IO - Starting link
{
  int	offset;					// Alignment offset


  switch (a)
  {
    case RIGHT :	// Right align
	offset = block->w - xx;
	break;
    case CENTER :	// Center
	offset = (block->w - xx) / 2;
	break;
    default :		// Left align
	offset = 0;
	break;
  }

  block->line[line] = block->x + offset;

  if (line < 31)
    line ++;

  while (l < nlinks_)
  {
    links_[l].x += offset;
    links_[l].w += offset;
    l ++;
  }

  return (line);
}

/** Draws the fltk3::HelpView widget. */
void
fltk3::HelpView::draw()
{
  FLTK3_OBJECT_VCALLS_WRAPPER(draw(), Draw)
  int			i;		// Looping var
  const fltk3::HelpBlock	*block;		// Pointer to current block
  const char		*ptr,		// Pointer to text in block
			*attrs;		// Pointer to start of element attributes
  char			*s,		// Pointer into buffer
			buf[1024],	// Text buffer
			attr[1024];	// Attribute buffer
  int			xx, yy, ww, hh;	// Current positions and sizes
  int			line;		// Current line
  fltk3::Font               font;
  fltk3::Fontsize           fsize;          // Current font and size
  fltk3::Color              fcolor;         // current font color 
  int			head, pre,	// Flags for text
			needspace;	// Do we need whitespace?
  fltk3::Boxtype		b = box() ? box() : fltk3::DOWN_BOX;
					// Box to draw...
  int			underline,	// Underline text?
                        xtra_ww;        // Extra width for underlined space between words

  // Draw the scrollbar(s) and box first...
  ww = w();
  hh = h();
  i  = 0;

  draw_box(b, x(), y(), ww, hh, bgcolor_);

  if ( hscrollbar_.visible() || scrollbar_.visible() ) {
    int scrollsize = scrollbar_size_ ? scrollbar_size_ : fltk3::scrollbar_size();
    int hor_vis = hscrollbar_.visible();
    int ver_vis = scrollbar_.visible();
    // Scrollbar corner
    int scorn_x = x() + ww - (ver_vis?scrollsize:0) - fltk3::box_dw(b) + fltk3::box_dx(b);
    int scorn_y = y() + hh - (hor_vis?scrollsize:0) - fltk3::box_dh(b) + fltk3::box_dy(b);
    if ( hor_vis ) {
      if ( hscrollbar_.h() != scrollsize ) {		// scrollsize changed?
	hscrollbar_.resize(x(), scorn_y, scorn_x - x(), scrollsize);
	init_sizes();
      }
      draw_child(hscrollbar_);
      hh -= scrollsize;
    }
    if ( ver_vis ) {
      if ( scrollbar_.w() != scrollsize ) {		// scrollsize changed?
	scrollbar_.resize(scorn_x, y(), scrollsize, scorn_y - y());
	init_sizes();
      }
      draw_child(scrollbar_);
      ww -= scrollsize;
    }
    if ( hor_vis && ver_vis ) {
      // Both scrollbars visible? Draw little gray box in corner
      fltk3::color(fltk3::GRAY);
      fltk3::rectf(scorn_x, scorn_y, scrollsize, scrollsize);
    }
  }

  if (!value_)
    return;

  if (current_view == this && selected) {
    hv_selection_color      = fltk3::SELECTION_COLOR;
    hv_selection_text_color = fltk3::contrast(textcolor_, fltk3::SELECTION_COLOR);
  }
  current_pos = 0;

  // Clip the drawing to the inside of the box...
  fltk3::push_clip(x() + fltk3::box_dx(b), y() + fltk3::box_dy(b),
               ww - fltk3::box_dw(b), hh - fltk3::box_dh(b));
  fltk3::color(textcolor_);

  // Draw all visible blocks...
  for (i = 0, block = blocks_; i < nblocks_; i ++, block ++)
    if ((block->y + block->h) >= topline_ && block->y < (topline_ + h()))
    {
      line      = 0;
      xx        = block->line[line];
      yy        = block->y - topline_;
      hh        = 0;
      pre       = 0;
      head      = 0;
      needspace = 0;
      underline = 0;

      initfont(font, fsize, fcolor);

      for (ptr = block->start, s = buf; ptr < block->end;)
      {
	if ((*ptr == '<' || isspace((*ptr)&255)) && s > buf)
	{
	  if (!head && !pre)
	  {
            // Check width...
            *s = '\0';
            s  = buf;
            ww = (int)fltk3::width(buf);

            if (needspace && xx > block->x)
	      xx += (int)fltk3::width(' ');

            if ((xx + ww) > block->w)
	    {
	      if (line < 31)
	        line ++;
	      xx = block->line[line];
	      yy += hh;
	      hh = 0;
	    }

            hv_draw(buf, xx + x() - leftline_, yy + y());
	    if (underline) {
              xtra_ww = isspace((*ptr)&255)?(int)fltk3::width(' '):0;
              fltk3::xyline(xx + x() - leftline_, yy + y() + 1,
	                xx + x() - leftline_ + ww + xtra_ww);
            }
            current_pos = ptr-value_;

            xx += ww;
	    if ((fsize + 2) > hh)
	      hh = fsize + 2;

	    needspace = 0;
	  }
	  else if (pre)
	  {
	    while (isspace((*ptr)&255))
	    {
	      if (*ptr == '\n')
	      {
	        *s = '\0';
                s = buf;

                hv_draw(buf, xx + x() - leftline_, yy + y());
		if (underline) fltk3::xyline(xx + x() - leftline_, yy + y() + 1,
	                        	 xx + x() - leftline_ +
					     (int)fltk3::width(buf));

                current_pos = ptr-value_;
		if (line < 31)
	          line ++;
		xx = block->line[line];
		yy += hh;
		hh = fsize + 2;
	      }
	      else if (*ptr == '\t')
	      {
		// Do tabs every 8 columns...
		while (((s - buf) & 7))
	          *s++ = ' ';
	      }
	      else
	        *s++ = ' ';

              if ((fsize + 2) > hh)
	        hh = fsize + 2;

              ptr ++;
	    }

            if (s > buf)
	    {
	      *s = '\0';
	      s = buf;

              hv_draw(buf, xx + x() - leftline_, yy + y());
	      ww = (int)fltk3::width(buf);
	      if (underline) fltk3::xyline(xx + x() - leftline_, yy + y() + 1,
	                               xx + x() - leftline_ + ww);
              xx += ww;
              current_pos = ptr-value_;
	    }

	    needspace = 0;
	  }
	  else
	  {
            s = buf;

	    while (isspace((*ptr)&255))
              ptr ++;
            current_pos = ptr-value_;
	  }
	}

	if (*ptr == '<')
	{
	  ptr ++;

          if (strncmp(ptr, "!--", 3) == 0)
	  {
	    // Comment...
	    ptr += 3;
	    if ((ptr = strstr(ptr, "-->")) != NULL)
	    {
	      ptr += 3;
	      continue;
	    }
	    else
	      break;
	  }

	  while (*ptr && *ptr != '>' && !isspace((*ptr)&255))
            if (s < (buf + sizeof(buf) - 1))
	      *s++ = *ptr++;
	    else
	      ptr ++;

	  *s = '\0';
	  s = buf;

	  attrs = ptr;
	  while (*ptr && *ptr != '>')
            ptr ++;

	  if (*ptr == '>')
            ptr ++;

          // end of command reached, set the supposed start of printed eord here
          current_pos = ptr-value_;
	  if (strcasecmp(buf, "HEAD") == 0)
            head = 1;
	  else if (strcasecmp(buf, "BR") == 0)
	  {
	    if (line < 31)
	      line ++;
	    xx = block->line[line];
            yy += hh;
	    hh = 0;
	  }
	  else if (strcasecmp(buf, "HR") == 0)
	  {
	    fltk3::line(block->x + x(), yy + y(), block->w + x(),
	            yy + y());

	    if (line < 31)
	      line ++;
	    xx = block->line[line];
            yy += 2 * hh;
	    hh = 0;
	  }
	  else if (strcasecmp(buf, "CENTER") == 0 ||
        	   strcasecmp(buf, "P") == 0 ||
        	   strcasecmp(buf, "H1") == 0 ||
		   strcasecmp(buf, "H2") == 0 ||
		   strcasecmp(buf, "H3") == 0 ||
		   strcasecmp(buf, "H4") == 0 ||
		   strcasecmp(buf, "H5") == 0 ||
		   strcasecmp(buf, "H6") == 0 ||
		   strcasecmp(buf, "UL") == 0 ||
		   strcasecmp(buf, "OL") == 0 ||
		   strcasecmp(buf, "DL") == 0 ||
		   strcasecmp(buf, "LI") == 0 ||
		   strcasecmp(buf, "DD") == 0 ||
		   strcasecmp(buf, "DT") == 0 ||
		   strcasecmp(buf, "PRE") == 0)
	  {
            if (tolower(buf[0]) == 'h')
	    {
	      font  = fltk3::HELVETICA_BOLD;
	      fsize = textsize_ + '7' - buf[1];
	    }
	    else if (strcasecmp(buf, "DT") == 0)
	    {
	      font  = textfont_ | fltk3::ITALIC;
	      fsize = textsize_;
	    }
	    else if (strcasecmp(buf, "PRE") == 0)
	    {
	      font  = fltk3::COURIER;
	      fsize = textsize_;
	      pre   = 1;
	    }

            if (strcasecmp(buf, "LI") == 0)
	    {
//            fltk3::font(fltk3::SYMBOL, fsize); // The default SYMBOL font on my XP box is not Unicode...
              char buf[8];
              wchar_t b[] = {0x2022, 0x0};
//            buf[fl_unicode2utf(b, 1, buf)] = 0;
              unsigned dstlen = fltk3::utf8fromwc(buf, 8, b, 1);
              buf[dstlen] = 0;
              hv_draw(buf, xx - fsize + x() - leftline_, yy + y());
	    }

	    pushfont(font, fsize);
	  }
	  else if (strcasecmp(buf, "A") == 0 &&
	           get_attr(attrs, "HREF", attr, sizeof(attr)) != NULL)
	  {
	    fltk3::color(linkcolor_);
	    underline = 1;
	  }
	  else if (strcasecmp(buf, "/A") == 0)
	  {
	    fltk3::color(textcolor_);
	    underline = 0;
	  }
	  else if (strcasecmp(buf, "FONT") == 0)
	  {
	    if (get_attr(attrs, "COLOR", attr, sizeof(attr)) != NULL) {
	      textcolor_ = get_color(attr, textcolor_);
	    }

            if (get_attr(attrs, "FACE", attr, sizeof(attr)) != NULL) {
	      if (!strncasecmp(attr, "helvetica", 9) ||
	          !strncasecmp(attr, "arial", 5) ||
		  !strncasecmp(attr, "sans", 4)) font = fltk3::HELVETICA;
              else if (!strncasecmp(attr, "times", 5) ||
	               !strncasecmp(attr, "serif", 5)) font = fltk3::TIMES;
              else if (!strncasecmp(attr, "symbol", 6)) font = fltk3::SYMBOL;
	      else font = fltk3::COURIER;
            }

            if (get_attr(attrs, "SIZE", attr, sizeof(attr)) != NULL) {
              if (isdigit(attr[0] & 255)) {
	        // Absolute size
	        fsize = (int)(textsize_ * pow(1.2, atof(attr) - 3.0));
	      } else {
	        // Relative size
	        fsize = (int)(fsize * pow(1.2, atof(attr) - 3.0));
	      }
	    }

            pushfont(font, fsize);
	  }
	  else if (strcasecmp(buf, "/FONT") == 0)
	  {
	    popfont(font, fsize, textcolor_);
	  }
	  else if (strcasecmp(buf, "U") == 0)
	    underline = 1;
	  else if (strcasecmp(buf, "/U") == 0)
	    underline = 0;
	  else if (strcasecmp(buf, "B") == 0 ||
	           strcasecmp(buf, "STRONG") == 0)
	    pushfont(font |= fltk3::BOLD, fsize);
	  else if (strcasecmp(buf, "TD") == 0 ||
	           strcasecmp(buf, "TH") == 0)
          {
	    int tx, ty, tw, th;

	    if (tolower(buf[1]) == 'h')
	      pushfont(font |= fltk3::BOLD, fsize);
	    else
	      pushfont(font = textfont_, fsize);

            tx = block->x - 4 - leftline_;
	    ty = block->y - topline_ - fsize - 3;
            tw = block->w - block->x + 7;
	    th = block->h + fsize - 5;

            if (tx < 0)
	    {
	      tw += tx;
	      tx  = 0;
	    }

	    if (ty < 0)
	    {
	      th += ty;
	      ty  = 0;
	    }

            tx += x();
	    ty += y();

            if (block->bgcolor != bgcolor_)
	    {
	      fltk3::color(block->bgcolor);
              fltk3::rectf(tx, ty, tw, th);
              fltk3::color(textcolor_);
	    }

            if (block->border)
              fltk3::rect(tx, ty, tw, th);
	  }
	  else if (strcasecmp(buf, "I") == 0 ||
                   strcasecmp(buf, "EM") == 0)
	    pushfont(font |= fltk3::ITALIC, fsize);
	  else if (strcasecmp(buf, "CODE") == 0 ||
	           strcasecmp(buf, "TT") == 0)
	    pushfont(font = fltk3::COURIER, fsize);
	  else if (strcasecmp(buf, "KBD") == 0)
	    pushfont(font = fltk3::COURIER_BOLD, fsize);
	  else if (strcasecmp(buf, "VAR") == 0)
	    pushfont(font = fltk3::COURIER_ITALIC, fsize);
	  else if (strcasecmp(buf, "/HEAD") == 0)
            head = 0;
	  else if (strcasecmp(buf, "/H1") == 0 ||
		   strcasecmp(buf, "/H2") == 0 ||
		   strcasecmp(buf, "/H3") == 0 ||
		   strcasecmp(buf, "/H4") == 0 ||
		   strcasecmp(buf, "/H5") == 0 ||
		   strcasecmp(buf, "/H6") == 0 ||
		   strcasecmp(buf, "/B") == 0 ||
		   strcasecmp(buf, "/STRONG") == 0 ||
		   strcasecmp(buf, "/I") == 0 ||
		   strcasecmp(buf, "/EM") == 0 ||
		   strcasecmp(buf, "/CODE") == 0 ||
		   strcasecmp(buf, "/TT") == 0 ||
		   strcasecmp(buf, "/KBD") == 0 ||
		   strcasecmp(buf, "/VAR") == 0)
	    popfont(font, fsize, fcolor);
	  else if (strcasecmp(buf, "/PRE") == 0)
	  {
	    popfont(font, fsize, fcolor);
	    pre = 0;
	  }
	  else if (strcasecmp(buf, "IMG") == 0)
	  {
	    fltk3::SharedImage *img = 0;
	    int		width, height;
	    char	wattr[8], hattr[8];


            get_attr(attrs, "WIDTH", wattr, sizeof(wattr));
            get_attr(attrs, "HEIGHT", hattr, sizeof(hattr));
	    width  = get_length(wattr);
	    height = get_length(hattr);

	    if (get_attr(attrs, "SRC", attr, sizeof(attr))) {
	      img = get_image(attr, width, height);
	      if (!width) width = img->w();
	      if (!height) height = img->h();
	    }

	    if (!width || !height) {
              if (get_attr(attrs, "ALT", attr, sizeof(attr)) == NULL) {
	        strcpy(attr, "IMG");
              }
	    }

	    ww = width;

	    if (needspace && xx > block->x)
	      xx += (int)fltk3::width(' ');

	    if ((xx + ww) > block->w)
	    {
	      if (line < 31)
		line ++;

	      xx = block->line[line];
	      yy += hh;
	      hh = 0;
	    }

	    if (img) {
	      img->draw(xx + x() - leftline_,
	                yy + y() - fltk3::height() + fltk3::descent() + 2);
	    }

	    xx += ww;
	    if ((height + 2) > hh)
	      hh = height + 2;

	    needspace = 0;
	  }
	}
	else if (*ptr == '\n' && pre)
	{
	  *s = '\0';
	  s = buf;

          hv_draw(buf, xx + x() - leftline_, yy + y());

	  if (line < 31)
	    line ++;
	  xx = block->line[line];
	  yy += hh;
	  hh = fsize + 2;
	  needspace = 0;

	  ptr ++;
          current_pos = ptr-value_;
	}
	else if (isspace((*ptr)&255))
	{
	  if (pre)
	  {
	    if (*ptr == ' ')
	      *s++ = ' ';
	    else
	    {
	      // Do tabs every 8 columns...
	      while (((s - buf) & 7))
	        *s++ = ' ';
            }
	  }

          ptr ++;
          if (!pre) current_pos = ptr-value_;
	  needspace = 1;
	}
	else if (*ptr == '&')
	{
	  ptr ++;

          int qch = quote_char(ptr);

	  if (qch < 0)
	    *s++ = '&';
	  else {
            int l;
            l = fltk3::utf8encode((unsigned int) qch, s);
            if (l < 1) l = 1;
            s += l;
	    ptr = strchr(ptr, ';') + 1;
	  }

          if ((fsize + 2) > hh)
	    hh = fsize + 2;
	}
	else
	{
	  *s++ = *ptr++;

          if ((fsize + 2) > hh)
	    hh = fsize + 2;
        }
      }

      *s = '\0';

      if (s > buf && !pre && !head)
      {
	ww = (int)fltk3::width(buf);

        if (needspace && xx > block->x)
	  xx += (int)fltk3::width(' ');

	if ((xx + ww) > block->w)
	{
	  if (line < 31)
	    line ++;
	  xx = block->line[line];
	  yy += hh;
	  hh = 0;
	}
      }

      if (s > buf && !head)
      {
        hv_draw(buf, xx + x() - leftline_, yy + y());
	if (underline) fltk3::xyline(xx + x() - leftline_, yy + y() + 1,
	                         xx + x() - leftline_ + ww);
        current_pos = ptr-value_;
      }
    }

  fltk3::pop_clip();
}



/** Finds the specified string \p s at starting position \p p.

    \return the matching position or -1 if not found
*/
int						// O - Matching position or -1 if not found
fltk3::HelpView::find(const char *s,		// I - String to find
                   int        p)		// I - Starting position
{
  int		i,				// Looping var
		c;				// Current character
  fltk3::HelpBlock	*b;				// Current block
  const char	*bp,				// Block matching pointer
		*bs,				// Start of current comparison
		*sp;				// Search string pointer


  // Range check input and value...
  if (!s || !value_) return -1;

  if (p < 0 || p >= (int)strlen(value_)) p = 0;
  else if (p > 0) p ++;

  // Look for the string...
  for (i = nblocks_, b = blocks_; i > 0; i --, b ++) {
    if (b->end < (value_ + p))
      continue;

    if (b->start < (value_ + p)) bp = value_ + p;
    else bp = b->start;

    for (sp = s, bs = bp; *sp && *bp && bp < b->end; bp ++) {
      if (*bp == '<') {
        // skip to end of element...
	while (*bp && bp < b->end && *bp != '>') bp ++;
	continue;
      } else if (*bp == '&') {
        // decode HTML entity...
	if ((c = quote_char(bp + 1)) < 0) c = '&';
	else bp = strchr(bp + 1, ';') + 1;
      } else c = *bp;

      if (tolower(*sp) == tolower(c)) sp ++;
      else {
        // No match, so reset to start of search...
	sp = s;
	bs ++;
	bp = bs;
      }
    }

    if (!*sp) {
      // Found a match!
      topline(b->y - b->h);
      return (b->end - value_);
    }
  }

  // No match!
  return (-1);
}

/** Formats the help text. */
void fltk3::HelpView::format() {
  int		i;		// Looping var
  int		done;		// Are we done yet?
  fltk3::HelpBlock	*block,		// Current block
		*cell;		// Current table cell
  int		cells[MAX_COLUMNS],
				// Cells in the current row...
		row;		// Current table row (block number)
  const char	*ptr,		// Pointer into block
		*start,		// Pointer to start of element
		*attrs;		// Pointer to start of element attributes
  char		*s,		// Pointer into buffer
		buf[1024],	// Text buffer
		attr[1024],	// Attribute buffer
		wattr[1024],	// Width attribute buffer
		hattr[1024],	// Height attribute buffer
		linkdest[1024];	// Link destination
  int		xx, yy, ww, hh;	// Size of current text fragment
  int		line;		// Current line in block
  int		links;		// Links for current line
  fltk3::Font       font;
  fltk3::Fontsize   fsize;          // Current font and size
  fltk3::Color      fcolor;         // Current font color
  unsigned char	border;		// Draw border?
  int		talign,		// Current alignment
		newalign,	// New alignment
		head,		// In the <HEAD> section?
		pre,		// <PRE> text?
		needspace;	// Do we need whitespace?
  int		table_width,	// Width of table
		table_offset;	// Offset of table
  int		column,		// Current table column number
		columns[MAX_COLUMNS];
				// Column widths
  fltk3::Color	tc, rc;		// Table/row background color
  fltk3::Boxtype	b = box() ? box() : fltk3::DOWN_BOX;
				// Box to draw...
  fl_margins	margins;	// Left margin stack...


  // Reset document width...
  int scrollsize = scrollbar_size_ ? scrollbar_size_ : fltk3::scrollbar_size();
  hsize_ = w() - scrollsize - fltk3::box_dw(b);

  done = 0;
  while (!done)
  {
    // Reset state variables...
    done       = 1;
    nblocks_   = 0;
    nlinks_    = 0;
    ntargets_  = 0;
    size_      = 0;
    bgcolor_   = color();
    textcolor_ = textcolor();
    linkcolor_ = fltk3::contrast(fltk3::BLUE, color());

    tc = rc = bgcolor_;

    strcpy(title_, "Untitled");

    if (!value_)
      return;

    // Setup for formatting...
    initfont(font, fsize, fcolor);

    line         = 0;
    links        = 0;
    xx           = margins.clear();
    yy           = fsize + 2;
    ww           = 0;
    column       = 0;
    border       = 0;
    hh           = 0;
    block        = add_block(value_, xx, yy, hsize_, 0);
    row          = 0;
    head         = 0;
    pre          = 0;
    talign       = LEFT;
    newalign     = LEFT;
    needspace    = 0;
    linkdest[0]  = '\0';
    table_offset = 0;

    // Html text character loop
    for (ptr = value_, s = buf; *ptr;)
    {
      // End of word?
      if ((*ptr == '<' || isspace((*ptr)&255)) && s > buf)
      {
        // Get width of word parsed so far...
        *s = '\0';
        ww = (int)fltk3::width(buf);

	if (!head && !pre)
	{
          // Check width...
          if (ww > hsize_) {
	    hsize_ = ww;
	    done   = 0;
	    break;
	  }

          if (needspace && xx > block->x)
	    ww += (int)fltk3::width(' ');

  //        printf("line = %d, xx = %d, ww = %d, block->x = %d, block->w = %d\n",
  //	       line, xx, ww, block->x, block->w);

          if ((xx + ww) > block->w)
	  {
            line     = do_align(block, line, xx, newalign, links);
	    xx       = block->x;
	    yy       += hh;
	    block->h += hh;
	    hh       = 0;
	  }

          if (linkdest[0])
	    add_link(linkdest, xx, yy - fsize, ww, fsize);

	  xx += ww;
	  if ((fsize + 2) > hh)
	    hh = fsize + 2;

	  needspace = 0;
	}
	else if (pre)
	{
          // Add a link as needed...
          if (linkdest[0])
	    add_link(linkdest, xx, yy - hh, ww, hh);

	  xx += ww;
	  if ((fsize + 2) > hh)
	    hh = fsize + 2;

          // Handle preformatted text...
	  while (isspace((*ptr)&255))
	  {
	    if (*ptr == '\n')
	    {
              if (xx > hsize_) break;

              line     = do_align(block, line, xx, newalign, links);
              xx       = block->x;
	      yy       += hh;
	      block->h += hh;
	      hh       = fsize + 2;
	    }
	    else
              xx += (int)fltk3::width(' ');

            if ((fsize + 2) > hh)
	      hh = fsize + 2;

            ptr ++;
	  }

          if (xx > hsize_) {
	    hsize_ = xx;
	    done   = 0;
	    break;
	  }

	  needspace = 0;
	}
	else
	{
          // Handle normal text or stuff in the <HEAD> section...
	  while (isspace((*ptr)&255))
            ptr ++;
	}

	s = buf;
      }

      if (*ptr == '<')
      {
	// Handle html tags..
	start = ptr;
	ptr ++;

        if (strncmp(ptr, "!--", 3) == 0)
	{
	  // Comment...
	  ptr += 3;
	  if ((ptr = strstr(ptr, "-->")) != NULL)
	  {
	    ptr += 3;
	    continue;
	  }
	  else
	    break;
	}

	while (*ptr && *ptr != '>' && !isspace((*ptr)&255))
          if (s < (buf + sizeof(buf) - 1))
            *s++ = *ptr++;
	  else
	    ptr ++;

	*s = '\0';
	s = buf;

//        puts(buf);

	attrs = ptr;
	while (*ptr && *ptr != '>')
          ptr ++;

	if (*ptr == '>')
          ptr ++;

	if (strcasecmp(buf, "HEAD") == 0)
          head = 1;
	else if (strcasecmp(buf, "/HEAD") == 0)
          head = 0;
	else if (strcasecmp(buf, "TITLE") == 0)
	{
          // Copy the title in the document...
          for (s = title_;
	       *ptr != '<' && *ptr && s < (title_ + sizeof(title_) - 1);
	       *s++ = *ptr++);

	  *s = '\0';
	  s = buf;
	}
	else if (strcasecmp(buf, "A") == 0)
	{
          if (get_attr(attrs, "NAME", attr, sizeof(attr)) != NULL)
	    add_target(attr, yy - fsize - 2);

	  if (get_attr(attrs, "HREF", attr, sizeof(attr)) != NULL)
	    strlcpy(linkdest, attr, sizeof(linkdest));
	}
	else if (strcasecmp(buf, "/A") == 0)
          linkdest[0] = '\0';
	else if (strcasecmp(buf, "BODY") == 0)
	{
          bgcolor_   = get_color(get_attr(attrs, "BGCOLOR", attr, sizeof(attr)),
	                	 color());
          textcolor_ = get_color(get_attr(attrs, "TEXT", attr, sizeof(attr)),
	                	 textcolor());
          linkcolor_ = get_color(get_attr(attrs, "LINK", attr, sizeof(attr)),
	                	 fltk3::contrast(fltk3::BLUE, color()));
	}
	else if (strcasecmp(buf, "BR") == 0)
	{
          line     = do_align(block, line, xx, newalign, links);
          xx       = block->x;
	  block->h += hh;
          yy       += hh;
	  hh       = 0;
	}
	else if (strcasecmp(buf, "CENTER") == 0 ||
        	 strcasecmp(buf, "P") == 0 ||
        	 strcasecmp(buf, "H1") == 0 ||
		 strcasecmp(buf, "H2") == 0 ||
		 strcasecmp(buf, "H3") == 0 ||
		 strcasecmp(buf, "H4") == 0 ||
		 strcasecmp(buf, "H5") == 0 ||
		 strcasecmp(buf, "H6") == 0 ||
		 strcasecmp(buf, "UL") == 0 ||
		 strcasecmp(buf, "OL") == 0 ||
		 strcasecmp(buf, "DL") == 0 ||
		 strcasecmp(buf, "LI") == 0 ||
		 strcasecmp(buf, "DD") == 0 ||
		 strcasecmp(buf, "DT") == 0 ||
		 strcasecmp(buf, "HR") == 0 ||
		 strcasecmp(buf, "PRE") == 0 ||
		 strcasecmp(buf, "TABLE") == 0)
	{
          block->end = start;
          line       = do_align(block, line, xx, newalign, links);
	  newalign   = strcasecmp(buf, "CENTER") ? LEFT : CENTER;
          xx         = block->x;
          block->h   += hh;

          if (strcasecmp(buf, "UL") == 0 ||
	      strcasecmp(buf, "OL") == 0 ||
	      strcasecmp(buf, "DL") == 0)
          {
	    block->h += fsize + 2;
	    xx       = margins.push(4 * fsize);
	  }
          else if (strcasecmp(buf, "TABLE") == 0)
	  {
	    if (get_attr(attrs, "BORDER", attr, sizeof(attr)))
	      border = (uchar)atoi(attr);
	    else
	      border = 0;

            tc = rc = get_color(get_attr(attrs, "BGCOLOR", attr, sizeof(attr)), bgcolor_);

	    block->h += fsize + 2;

            format_table(&table_width, columns, start);

            if ((xx + table_width) > hsize_) {
#ifdef DEBUG
              printf("xx=%d, table_width=%d, hsize_=%d\n", xx, table_width,
	             hsize_);
#endif // DEBUG
	      hsize_ = xx + table_width;
	      done   = 0;
	      break;
	    }

            switch (get_align(attrs, talign))
	    {
	      default :
	          table_offset = 0;
	          break;

	      case CENTER :
	          table_offset = (hsize_ - table_width) / 2 - textsize_;
	          break;

	      case RIGHT :
	          table_offset = hsize_ - table_width - textsize_;
	          break;
	    }

	    column = 0;
	  }

          if (tolower(buf[0]) == 'h' && isdigit(buf[1]))
	  {
	    font  = fltk3::HELVETICA_BOLD;
	    fsize = textsize_ + '7' - buf[1];
	  }
	  else if (strcasecmp(buf, "DT") == 0)
	  {
	    font  = textfont_ | fltk3::ITALIC;
	    fsize = textsize_;
	  }
	  else if (strcasecmp(buf, "PRE") == 0)
	  {
	    font  = fltk3::COURIER;
	    fsize = textsize_;
	    pre   = 1;
	  }
	  else
	  {
	    font  = textfont_;
	    fsize = textsize_;
	  }

	  pushfont(font, fsize);

          yy = block->y + block->h;
          hh = 0;

          if ((tolower(buf[0]) == 'h' && isdigit(buf[1])) ||
	      strcasecmp(buf, "DD") == 0 ||
	      strcasecmp(buf, "DT") == 0 ||
	      strcasecmp(buf, "P") == 0)
            yy += fsize + 2;
	  else if (strcasecmp(buf, "HR") == 0)
	  {
	    hh += 2 * fsize;
	    yy += fsize;
	  }

          if (row)
	    block = add_block(start, xx, yy, block->w, 0);
	  else
	    block = add_block(start, xx, yy, hsize_, 0);

	  needspace = 0;
	  line      = 0;

	  if (strcasecmp(buf, "CENTER") == 0)
	    newalign = talign = CENTER;
	  else
	    newalign = get_align(attrs, talign);
	}
	else if (strcasecmp(buf, "/CENTER") == 0 ||
		 strcasecmp(buf, "/P") == 0 ||
		 strcasecmp(buf, "/H1") == 0 ||
		 strcasecmp(buf, "/H2") == 0 ||
		 strcasecmp(buf, "/H3") == 0 ||
		 strcasecmp(buf, "/H4") == 0 ||
		 strcasecmp(buf, "/H5") == 0 ||
		 strcasecmp(buf, "/H6") == 0 ||
		 strcasecmp(buf, "/PRE") == 0 ||
		 strcasecmp(buf, "/UL") == 0 ||
		 strcasecmp(buf, "/OL") == 0 ||
		 strcasecmp(buf, "/DL") == 0 ||
		 strcasecmp(buf, "/TABLE") == 0)
	{
          line       = do_align(block, line, xx, newalign, links);
          xx         = block->x;
          block->end = ptr;

          if (strcasecmp(buf, "/UL") == 0 ||
	      strcasecmp(buf, "/OL") == 0 ||
	      strcasecmp(buf, "/DL") == 0)
	  {
	    xx       = margins.pop();
	    block->h += fsize + 2;
	  }
          else if (strcasecmp(buf, "/TABLE") == 0) 
          {
	    block->h += fsize + 2;
            xx       = margins.current();
          }
	  else if (strcasecmp(buf, "/PRE") == 0)
	  {
	    pre = 0;
	    hh  = 0;
	  }
	  else if (strcasecmp(buf, "/CENTER") == 0)
	    talign = LEFT;

          popfont(font, fsize, fcolor);

	  //#if defined(__GNUC__)
          //#warning FIXME this isspace & 255 test will probably not work on a utf8 stream... And we use it everywhere!
	  //#endif /*__GNUC__*/
          while (isspace((*ptr)&255))
	    ptr ++;

          block->h += hh;
          yy       += hh;

          if (tolower(buf[2]) == 'l')
            yy += fsize + 2;

          if (row)
	    block = add_block(ptr, xx, yy, block->w, 0);
	  else
	    block = add_block(ptr, xx, yy, hsize_, 0);

	  needspace = 0;
	  hh        = 0;
	  line      = 0;
	  newalign  = talign;
	}
	else if (strcasecmp(buf, "TR") == 0)
	{
          block->end = start;
          line       = do_align(block, line, xx, newalign, links);
          xx         = block->x;
          block->h   += hh;

          if (row)
	  {
            yy = blocks_[row].y + blocks_[row].h;

	    for (cell = blocks_ + row + 1; cell <= block; cell ++)
	      if ((cell->y + cell->h) > yy)
		yy = cell->y + cell->h;

            block = blocks_ + row;

            block->h = yy - block->y + 2;

	    for (i = 0; i < column; i ++)
	      if (cells[i])
	      {
		cell = blocks_ + cells[i];
		cell->h = block->h;
	      }
	  }

          memset(cells, 0, sizeof(cells));

	  yy        = block->y + block->h - 4;
	  hh        = 0;
          block     = add_block(start, xx, yy, hsize_, 0);
	  row       = block - blocks_;
	  needspace = 0;
	  column    = 0;
	  line      = 0;

          rc = get_color(get_attr(attrs, "BGCOLOR", attr, sizeof(attr)), tc);
	}
	else if (strcasecmp(buf, "/TR") == 0 && row)
	{
          line       = do_align(block, line, xx, newalign, links);
          block->end = start;
	  block->h   += hh;
	  talign     = LEFT;

          xx = blocks_[row].x;
          yy = blocks_[row].y + blocks_[row].h;

	  for (cell = blocks_ + row + 1; cell <= block; cell ++)
	    if ((cell->y + cell->h) > yy)
	      yy = cell->y + cell->h;

          block = blocks_ + row;

          block->h = yy - block->y + 2;

	  for (i = 0; i < column; i ++)
	    if (cells[i])
	    {
	      cell = blocks_ + cells[i];
	      cell->h = block->h;
	    }

	  yy        = block->y + block->h /*- 4*/;
          block     = add_block(start, xx, yy, hsize_, 0);
	  needspace = 0;
	  row       = 0;
	  line      = 0;
	}
	else if ((strcasecmp(buf, "TD") == 0 ||
                  strcasecmp(buf, "TH") == 0) && row)
	{
          int	colspan;		// COLSPAN attribute


          line       = do_align(block, line, xx, newalign, links);
          block->end = start;
	  block->h   += hh;

          if (strcasecmp(buf, "TH") == 0)
	    font = textfont_ | fltk3::BOLD;
	  else
	    font = textfont_;

          fsize = textsize_;

          xx = blocks_[row].x + fsize + 3 + table_offset;
	  for (i = 0; i < column; i ++)
	    xx += columns[i] + 6;

          margins.push(xx - margins.current());

          if (get_attr(attrs, "COLSPAN", attr, sizeof(attr)) != NULL)
	    colspan = atoi(attr);
	  else
	    colspan = 1;

          for (i = 0, ww = -6; i < colspan; i ++)
	    ww += columns[column + i] + 6;

          if (block->end == block->start && nblocks_ > 1)
	  {
	    nblocks_ --;
	    block --;
	  }

	  pushfont(font, fsize);

	  yy        = blocks_[row].y;
	  hh        = 0;
          block     = add_block(start, xx, yy, xx + ww, 0, border);
	  needspace = 0;
	  line      = 0;
	  newalign  = get_align(attrs, tolower(buf[1]) == 'h' ? CENTER : LEFT);
	  talign    = newalign;

          cells[column] = block - blocks_;

	  column += colspan;

          block->bgcolor = get_color(get_attr(attrs, "BGCOLOR", attr,
	                                      sizeof(attr)), rc);
	}
	else if ((strcasecmp(buf, "/TD") == 0 ||
                  strcasecmp(buf, "/TH") == 0) && row)
	{
          line = do_align(block, line, xx, newalign, links);
          popfont(font, fsize, fcolor);
	  xx = margins.pop();
	  talign = LEFT;
	}
	else if (strcasecmp(buf, "FONT") == 0)
	{
          if (get_attr(attrs, "FACE", attr, sizeof(attr)) != NULL) {
	    if (!strncasecmp(attr, "helvetica", 9) ||
	        !strncasecmp(attr, "arial", 5) ||
		!strncasecmp(attr, "sans", 4)) font = fltk3::HELVETICA;
            else if (!strncasecmp(attr, "times", 5) ||
	             !strncasecmp(attr, "serif", 5)) font = fltk3::TIMES;
            else if (!strncasecmp(attr, "symbol", 6)) font = fltk3::SYMBOL;
	    else font = fltk3::COURIER;
          }

          if (get_attr(attrs, "SIZE", attr, sizeof(attr)) != NULL) {
            if (isdigit(attr[0] & 255)) {
	      // Absolute size
	      fsize = (int)(textsize_ * pow(1.2, atoi(attr) - 3.0));
	    } else {
	      // Relative size
	      fsize = (int)(fsize * pow(1.2, atoi(attr)));
	    }
	  }

          pushfont(font, fsize);
	}
	else if (strcasecmp(buf, "/FONT") == 0)
	  popfont(font, fsize, fcolor);
	else if (strcasecmp(buf, "B") == 0 ||
        	 strcasecmp(buf, "STRONG") == 0)
	  pushfont(font |= fltk3::BOLD, fsize);
	else if (strcasecmp(buf, "I") == 0 ||
        	 strcasecmp(buf, "EM") == 0)
	  pushfont(font |= fltk3::ITALIC, fsize);
	else if (strcasecmp(buf, "CODE") == 0 ||
	         strcasecmp(buf, "TT") == 0)
	  pushfont(font = fltk3::COURIER, fsize);
	else if (strcasecmp(buf, "KBD") == 0)
	  pushfont(font = fltk3::COURIER_BOLD, fsize);
	else if (strcasecmp(buf, "VAR") == 0)
	  pushfont(font = fltk3::COURIER_ITALIC, fsize);
	else if (strcasecmp(buf, "/B") == 0 ||
		 strcasecmp(buf, "/STRONG") == 0 ||
		 strcasecmp(buf, "/I") == 0 ||
		 strcasecmp(buf, "/EM") == 0 ||
		 strcasecmp(buf, "/CODE") == 0 ||
		 strcasecmp(buf, "/TT") == 0 ||
		 strcasecmp(buf, "/KBD") == 0 ||
		 strcasecmp(buf, "/VAR") == 0)
	  popfont(font, fsize, fcolor);
	else if (strcasecmp(buf, "IMG") == 0)
	{
	  fltk3::SharedImage	*img = 0;
	  int		width;
	  int		height;


          get_attr(attrs, "WIDTH", wattr, sizeof(wattr));
          get_attr(attrs, "HEIGHT", hattr, sizeof(hattr));
	  width  = get_length(wattr);
	  height = get_length(hattr);

	  if (get_attr(attrs, "SRC", attr, sizeof(attr))) {
	    img    = get_image(attr, width, height);
	    width  = img->w();
	    height = img->h();
	  }

	  ww = width;

          if (ww > hsize_) {
	    hsize_ = ww;
	    done   = 0;
	    break;
	  }

	  if (needspace && xx > block->x)
	    ww += (int)fltk3::width(' ');

	  if ((xx + ww) > block->w)
	  {
	    line     = do_align(block, line, xx, newalign, links);
	    xx       = block->x;
	    yy       += hh;
	    block->h += hh;
	    hh       = 0;
	  }

	  if (linkdest[0])
	    add_link(linkdest, xx, yy - height, ww, height);

	  xx += ww;
	  if ((height + 2) > hh)
	    hh = height + 2;

	  needspace = 0;
	}
      }
      else if (*ptr == '\n' && pre)
      {
	if (linkdest[0])
	  add_link(linkdest, xx, yy - hh, ww, hh);

        if (xx > hsize_) {
	  hsize_ = xx;
          done   = 0;
	  break;
	}

	line      = do_align(block, line, xx, newalign, links);
	xx        = block->x;
	yy        += hh;
	block->h  += hh;
	needspace = 0;
	ptr ++;
      }
      else if (isspace((*ptr)&255))
      {
	needspace = 1;
	if ( pre ) {
	  xx += (int)fltk3::width(' ');
        }
	ptr ++;
      }
      else if (*ptr == '&' && s < (buf + sizeof(buf) - 1))
      {
        // Handle html '&' codes, eg. "&amp;"
	ptr ++;

        int qch = quote_char(ptr);

	if (qch < 0)
	  *s++ = '&';
	else {
          int l;
          l = fltk3::utf8encode((unsigned int) qch, s);
          if (l < 1) l = 1;
          s += l;
	  ptr = strchr(ptr, ';') + 1;
	}

	if ((fsize + 2) > hh)
          hh = fsize + 2;
      }
      else
      {
	if (s < (buf + sizeof(buf) - 1))
          *s++ = *ptr++;
	else
          ptr ++;

	if ((fsize + 2) > hh)
          hh = fsize + 2;
      }
    }

    if (s > buf && !head)
    {
      *s = '\0';
      ww = (int)fltk3::width(buf);

  //    printf("line = %d, xx = %d, ww = %d, block->x = %d, block->w = %d\n",
  //	   line, xx, ww, block->x, block->w);

      if (ww > hsize_) {
	hsize_ = ww;
	done   = 0;
	break;
      }

      if (needspace && xx > block->x)
	ww += (int)fltk3::width(' ');

      if ((xx + ww) > block->w)
      {
	line     = do_align(block, line, xx, newalign, links);
	xx       = block->x;
	yy       += hh;
	block->h += hh;
	hh       = 0;
      }

      if (linkdest[0])
	add_link(linkdest, xx, yy - fsize, ww, fsize);

      xx += ww;
    }

    do_align(block, line, xx, newalign, links);

    block->end = ptr;
    size_      = yy + hh;
  }

//  printf("margins.depth_=%d\n", margins.depth_);

  if (ntargets_ > 1)
    qsort(targets_, ntargets_, sizeof(fltk3::HelpTarget),
          (compare_func_t)compare_targets);

  int dx = fltk3::box_dw(b) - fltk3::box_dx(b);
  int dy = fltk3::box_dh(b) - fltk3::box_dy(b);
  int ss = scrollbar_size_ ? scrollbar_size_ : fltk3::scrollbar_size();
  int dw = fltk3::box_dw(b) + ss;
  int dh = fltk3::box_dh(b);

  if (hsize_ > (w() - dw)) {
    hscrollbar_.show();

    dh += ss;

    if (size_ < (h() - dh)) {
      scrollbar_.hide();
      hscrollbar_.resize(x() + fltk3::box_dx(b), y() + h() - ss - dy,
                         w() - fltk3::box_dw(b), ss);
    } else {
      scrollbar_.show();
      scrollbar_.resize(x() + w() - ss - dx, y() + fltk3::box_dy(b),
                        ss, h() - ss - fltk3::box_dh(b));
      hscrollbar_.resize(x() + fltk3::box_dx(b), y() + h() - ss - dy,
                         w() - ss - fltk3::box_dw(b), ss);
    }
  } else {
    hscrollbar_.hide();

    if (size_ < (h() - dh)) scrollbar_.hide();
    else {
      scrollbar_.resize(x() + w() - ss - dx, y() + fltk3::box_dy(b),
                        ss, h() - fltk3::box_dh(b));
      scrollbar_.show();
    }
  }

  // Reset scrolling if it needs to be...
  if (scrollbar_.visible()) {
    int temph = h() - fltk3::box_dh(b);
    if (hscrollbar_.visible()) temph -= ss;
    if ((topline_ + temph) > size_) topline(size_ - temph);
    else topline(topline_);
  } else topline(0);

  if (hscrollbar_.visible()) {
    int tempw = w() - ss - fltk3::box_dw(b);
    if ((leftline_ + tempw) > hsize_) leftline(hsize_ - tempw);
    else leftline(leftline_);
  } else leftline(0);
}


/** Formats a table */
void
fltk3::HelpView::format_table(int        *table_width,	// O - Total table width
                           int        *columns,		// O - Column widths
	                   const char *table)		// I - Pointer to start of table
{
  int		column,					// Current column
		num_columns,				// Number of columns
		colspan,				// COLSPAN attribute
		width,					// Current width
		temp_width,				// Temporary width
		max_width,				// Maximum width
		incell,					// In a table cell?
		pre,					// <PRE> text?
		needspace;				// Need whitespace?
  char		*s,					// Pointer into buffer
		buf[1024],				// Text buffer
		attr[1024],				// Other attribute
		wattr[1024],				// WIDTH attribute
		hattr[1024];				// HEIGHT attribute
  const char	*ptr,					// Pointer into table
		*attrs,					// Pointer to attributes
		*start;					// Start of element
  int		minwidths[MAX_COLUMNS];			// Minimum widths for each column
  fltk3::Font       font;
  fltk3::Fontsize   fsize;				        // Current font and size
  fltk3::Color      fcolor;                                 // Currrent font color

  // Clear widths...
  *table_width = 0;
  for (column = 0; column < MAX_COLUMNS; column ++)
  {
    columns[column]   = 0;
    minwidths[column] = 0;
  }

  num_columns = 0;
  colspan     = 0;
  max_width   = 0;
  pre         = 0;
  needspace   = 0;
  fstack_.top(font, fsize, fcolor);

  // Scan the table...
  for (ptr = table, column = -1, width = 0, s = buf, incell = 0; *ptr;)
  {
    if ((*ptr == '<' || isspace((*ptr)&255)) && s > buf && incell)
    {
      // Check width...
      if (needspace)
      {
        *s++      = ' ';
	needspace = 0;
      }

      *s         = '\0';
      temp_width = (int)fltk3::width(buf);
      s          = buf;

      if (temp_width > minwidths[column])
        minwidths[column] = temp_width;

      width += temp_width;

      if (width > max_width)
        max_width = width;
    }

    if (*ptr == '<')
    {
      start = ptr;

      for (s = buf, ptr ++; *ptr && *ptr != '>' && !isspace((*ptr)&255);)
        if (s < (buf + sizeof(buf) - 1))
          *s++ = *ptr++;
	else
	  ptr ++;

      *s = '\0';
      s = buf;

      attrs = ptr;
      while (*ptr && *ptr != '>')
        ptr ++;

      if (*ptr == '>')
        ptr ++;

      if (strcasecmp(buf, "BR") == 0 ||
	  strcasecmp(buf, "HR") == 0)
      {
        width     = 0;
	needspace = 0;
      }
      else if (strcasecmp(buf, "TABLE") == 0 && start > table)
        break;
      else if (strcasecmp(buf, "CENTER") == 0 ||
               strcasecmp(buf, "P") == 0 ||
               strcasecmp(buf, "H1") == 0 ||
	       strcasecmp(buf, "H2") == 0 ||
	       strcasecmp(buf, "H3") == 0 ||
	       strcasecmp(buf, "H4") == 0 ||
	       strcasecmp(buf, "H5") == 0 ||
	       strcasecmp(buf, "H6") == 0 ||
	       strcasecmp(buf, "UL") == 0 ||
	       strcasecmp(buf, "OL") == 0 ||
	       strcasecmp(buf, "DL") == 0 ||
	       strcasecmp(buf, "LI") == 0 ||
	       strcasecmp(buf, "DD") == 0 ||
	       strcasecmp(buf, "DT") == 0 ||
	       strcasecmp(buf, "PRE") == 0)
      {
        width     = 0;
	needspace = 0;

        if (tolower(buf[0]) == 'h' && isdigit(buf[1]))
	{
	  font  = fltk3::HELVETICA_BOLD;
	  fsize = textsize_ + '7' - buf[1];
	}
	else if (strcasecmp(buf, "DT") == 0)
	{
	  font  = textfont_ | fltk3::ITALIC;
	  fsize = textsize_;
	}
	else if (strcasecmp(buf, "PRE") == 0)
	{
	  font  = fltk3::COURIER;
	  fsize = textsize_;
	  pre   = 1;
	}
	else if (strcasecmp(buf, "LI") == 0)
	{
	  width  += 4 * fsize;
	  font   = textfont_;
	  fsize  = textsize_;
	}
	else
	{
	  font  = textfont_;
	  fsize = textsize_;
	}

	pushfont(font, fsize);
      }
      else if (strcasecmp(buf, "/CENTER") == 0 ||
	       strcasecmp(buf, "/P") == 0 ||
	       strcasecmp(buf, "/H1") == 0 ||
	       strcasecmp(buf, "/H2") == 0 ||
	       strcasecmp(buf, "/H3") == 0 ||
	       strcasecmp(buf, "/H4") == 0 ||
	       strcasecmp(buf, "/H5") == 0 ||
	       strcasecmp(buf, "/H6") == 0 ||
	       strcasecmp(buf, "/PRE") == 0 ||
	       strcasecmp(buf, "/UL") == 0 ||
	       strcasecmp(buf, "/OL") == 0 ||
	       strcasecmp(buf, "/DL") == 0)
      {
        width     = 0;
	needspace = 0;

        popfont(font, fsize, fcolor);
      }
      else if (strcasecmp(buf, "TR") == 0 || strcasecmp(buf, "/TR") == 0 ||
               strcasecmp(buf, "/TABLE") == 0)
      {
//        printf("%s column = %d, colspan = %d, num_columns = %d\n",
//	       buf, column, colspan, num_columns);

        if (column >= 0)
	{
	  // This is a hack to support COLSPAN...
	  max_width /= colspan;

	  while (colspan > 0)
	  {
	    if (max_width > columns[column])
	      columns[column] = max_width;

	    column ++;
	    colspan --;
	  }
	}

	if (strcasecmp(buf, "/TABLE") == 0)
	  break;

	needspace = 0;
	column    = -1;
	width     = 0;
	max_width = 0;
	incell    = 0;
      }
      else if (strcasecmp(buf, "TD") == 0 ||
               strcasecmp(buf, "TH") == 0)
      {
//        printf("BEFORE column = %d, colspan = %d, num_columns = %d\n",
//	       column, colspan, num_columns);

        if (column >= 0)
	{
	  // This is a hack to support COLSPAN...
	  max_width /= colspan;

	  while (colspan > 0)
	  {
	    if (max_width > columns[column])
	      columns[column] = max_width;

	    column ++;
	    colspan --;
	  }
	}
	else
	  column ++;

        if (get_attr(attrs, "COLSPAN", attr, sizeof(attr)) != NULL)
	  colspan = atoi(attr);
	else
	  colspan = 1;

//        printf("AFTER column = %d, colspan = %d, num_columns = %d\n",
//	       column, colspan, num_columns);

        if ((column + colspan) >= num_columns)
	  num_columns = column + colspan;

	needspace = 0;
	width     = 0;
	incell    = 1;

        if (strcasecmp(buf, "TH") == 0)
	  font = textfont_ | fltk3::BOLD;
	else
	  font = textfont_;

        fsize = textsize_;

	pushfont(font, fsize);

        if (get_attr(attrs, "WIDTH", attr, sizeof(attr)) != NULL)
	  max_width = get_length(attr);
	else
	  max_width = 0;

//        printf("max_width = %d\n", max_width);
      }
      else if (strcasecmp(buf, "/TD") == 0 ||
               strcasecmp(buf, "/TH") == 0)
      {
	incell = 0;
        popfont(font, fsize, fcolor);
      }
      else if (strcasecmp(buf, "B") == 0 ||
               strcasecmp(buf, "STRONG") == 0)
	pushfont(font |= fltk3::BOLD, fsize);
      else if (strcasecmp(buf, "I") == 0 ||
               strcasecmp(buf, "EM") == 0)
	pushfont(font |= fltk3::ITALIC, fsize);
      else if (strcasecmp(buf, "CODE") == 0 ||
               strcasecmp(buf, "TT") == 0)
	pushfont(font = fltk3::COURIER, fsize);
      else if (strcasecmp(buf, "KBD") == 0)
	pushfont(font = fltk3::COURIER_BOLD, fsize);
      else if (strcasecmp(buf, "VAR") == 0)
	pushfont(font = fltk3::COURIER_ITALIC, fsize);
      else if (strcasecmp(buf, "/B") == 0 ||
	       strcasecmp(buf, "/STRONG") == 0 ||
	       strcasecmp(buf, "/I") == 0 ||
	       strcasecmp(buf, "/EM") == 0 ||
	       strcasecmp(buf, "/CODE") == 0 ||
	       strcasecmp(buf, "/TT") == 0 ||
	       strcasecmp(buf, "/KBD") == 0 ||
	       strcasecmp(buf, "/VAR") == 0)
	popfont(font, fsize, fcolor);
      else if (strcasecmp(buf, "IMG") == 0 && incell)
      {
	fltk3::SharedImage	*img = 0;
	int		iwidth, iheight;


        get_attr(attrs, "WIDTH", wattr, sizeof(wattr));
        get_attr(attrs, "HEIGHT", hattr, sizeof(hattr));
	iwidth  = get_length(wattr);
	iheight = get_length(hattr);

        if (get_attr(attrs, "SRC", attr, sizeof(attr))) {
	  img     = get_image(attr, iwidth, iheight);
	  iwidth  = img->w();
	  iheight = img->h();
	}

	if (iwidth > minwidths[column])
          minwidths[column] = iwidth;

        width += iwidth;
	if (needspace)
	  width += (int)fltk3::width(' ');

	if (width > max_width)
          max_width = width;

	needspace = 0;
      }
    }
    else if (*ptr == '\n' && pre)
    {
      width     = 0;
      needspace = 0;
      ptr ++;
    }
    else if (isspace((*ptr)&255))
    {
      needspace = 1;

      ptr ++;
    }
    else if (*ptr == '&' && s < (buf + sizeof(buf) - 1))
    {
      ptr ++;

      int qch = quote_char(ptr);

      if (qch < 0)
	*s++ = '&';
      else {
//        int l;
//        l = fltk3::utf8encode((unsigned int) qch, s);
//        if (l < 1) l = 1;
//        s += l;
	*s++ = qch;
	ptr = strchr(ptr, ';') + 1;
      }
    }
    else
    {
      if (s < (buf + sizeof(buf) - 1))
        *s++ = *ptr++;
      else
        ptr ++;
    }
  }

  // Now that we have scanned the entire table, adjust the table and
  // cell widths to fit on the screen...
  if (get_attr(table + 6, "WIDTH", attr, sizeof(attr)))
    *table_width = get_length(attr);
  else
    *table_width = 0;

#ifdef DEBUG
  printf("num_columns = %d, table_width = %d\n", num_columns, *table_width);
#endif // DEBUG

  if (num_columns == 0)
    return;

  // Add up the widths...
  for (column = 0, width = 0; column < num_columns; column ++)
    width += columns[column];

#ifdef DEBUG
  printf("width = %d, w() = %d\n", width, w());
  for (column = 0; column < num_columns; column ++)
    printf("    columns[%d] = %d, minwidths[%d] = %d\n", column, columns[column],
           column, minwidths[column]);
#endif // DEBUG

  // Adjust the width if needed...
  int scale_width = *table_width;

  int scrollsize = scrollbar_size_ ? scrollbar_size_ : fltk3::scrollbar_size();
  if (scale_width == 0) {
    if (width > (hsize_ - scrollsize)) scale_width = hsize_ - scrollsize;
    else scale_width = width;
  }

  if (width < scale_width) {
#ifdef DEBUG
    printf("Scaling table up to %d from %d...\n", scale_width, width);
#endif // DEBUG

    *table_width = 0;

    scale_width = (scale_width - width) / num_columns;

#ifdef DEBUG
    printf("adjusted scale_width = %d\n", scale_width);
#endif // DEBUG

    for (column = 0; column < num_columns; column ++) {
      columns[column] += scale_width;

      (*table_width) += columns[column];
    }
  }
  else if (width > scale_width) {
#ifdef DEBUG
    printf("Scaling table down to %d from %d...\n", scale_width, width);
#endif // DEBUG

    for (column = 0; column < num_columns; column ++) {
      width       -= minwidths[column];
      scale_width -= minwidths[column];
    }

#ifdef DEBUG
    printf("adjusted width = %d, scale_width = %d\n", width, scale_width);
#endif // DEBUG

    if (width > 0) {
      for (column = 0; column < num_columns; column ++) {
	columns[column] -= minwidths[column];
	columns[column] = scale_width * columns[column] / width;
	columns[column] += minwidths[column];
      }
    }

    *table_width = 0;
    for (column = 0; column < num_columns; column ++) {
      (*table_width) += columns[column];
    }
  }
  else if (*table_width == 0)
    *table_width = width;

#ifdef DEBUG
  printf("FINAL table_width = %d\n", *table_width);
  for (column = 0; column < num_columns; column ++)
    printf("    columns[%d] = %d\n", column, columns[column]);
#endif // DEBUG
}


/** Frees memory used for the document. */
void
fltk3::HelpView::free_data() {
  // Release all images...
  if (value_) {
    const char	*ptr,		// Pointer into block
		*attrs;		// Pointer to start of element attributes
    char	*s,		// Pointer into buffer
		buf[1024],	// Text buffer
		attr[1024],	// Attribute buffer
		wattr[1024],	// Width attribute buffer
		hattr[1024];	// Height attribute buffer

    for (ptr = value_; *ptr;)
    {
      if (*ptr == '<')
      {
	ptr ++;

        if (strncmp(ptr, "!--", 3) == 0)
	{
	  // Comment...
	  ptr += 3;
	  if ((ptr = strstr(ptr, "-->")) != NULL)
	  {
	    ptr += 3;
	    continue;
	  }
	  else
	    break;
	}

        s = buf;

	while (*ptr && *ptr != '>' && !isspace((*ptr)&255))
          if (s < (buf + sizeof(buf) - 1))
            *s++ = *ptr++;
	  else
	    ptr ++;

	*s = '\0';

	attrs = ptr;
	while (*ptr && *ptr != '>')
          ptr ++;

	if (*ptr == '>')
          ptr ++;

	if (strcasecmp(buf, "IMG") == 0)
	{
	  fltk3::SharedImage	*img;
	  int		width;
	  int		height;

          get_attr(attrs, "WIDTH", wattr, sizeof(wattr));
          get_attr(attrs, "HEIGHT", hattr, sizeof(hattr));
	  width  = get_length(wattr);
	  height = get_length(hattr);

	  if (get_attr(attrs, "SRC", attr, sizeof(attr))) {
	    // Get and release the image to free it from memory...
	    img = get_image(attr, width, height);
	    if ((void*)img != &broken_image) {
	      img->release();
	    }
	  }
	}
      }
      else
        ptr ++;
    }

    free((void *)value_);
    value_ = 0;
  }

  // Free all of the arrays...
  if (nblocks_) {
    free(blocks_);

    ablocks_ = 0;
    nblocks_ = 0;
    blocks_  = 0;
  }

  if (nlinks_) {
    free(links_);

    alinks_ = 0;
    nlinks_ = 0;
    links_  = 0;
  }

  if (ntargets_) {
    free(targets_);

    atargets_ = 0;
    ntargets_ = 0;
    targets_  = 0;
  }
}

/** Gets an alignment attribute. */
int					// O - Alignment
fltk3::HelpView::get_align(const char *p,	// I - Pointer to start of attrs
                        int        a)	// I - Default alignment
{
  char	buf[255];			// Alignment value


  if (get_attr(p, "ALIGN", buf, sizeof(buf)) == NULL)
    return (a);

  if (strcasecmp(buf, "CENTER") == 0)
    return (CENTER);
  else if (strcasecmp(buf, "RIGHT") == 0)
    return (RIGHT);
  else
    return (LEFT);
}


/** Gets an attribute value from the string. */
const char *					// O - Pointer to buf or NULL
fltk3::HelpView::get_attr(const char *p,		// I - Pointer to start of attributes
                      const char *n,		// I - Name of attribute
		      char       *buf,		// O - Buffer for attribute value
		      int        bufsize)	// I - Size of buffer
{
  char	name[255],				// Name from string
	*ptr,					// Pointer into name or value
	quote;					// Quote


  buf[0] = '\0';

  while (*p && *p != '>')
  {
    while (isspace((*p)&255))
      p ++;

    if (*p == '>' || !*p)
      return (NULL);

    for (ptr = name; *p && !isspace((*p)&255) && *p != '=' && *p != '>';)
      if (ptr < (name + sizeof(name) - 1))
        *ptr++ = *p++;
      else
        p ++;

    *ptr = '\0';

    if (isspace((*p)&255) || !*p || *p == '>')
      buf[0] = '\0';
    else
    {
      if (*p == '=')
        p ++;

      for (ptr = buf; *p && !isspace((*p)&255) && *p != '>';)
        if (*p == '\'' || *p == '\"')
	{
	  quote = *p++;

	  while (*p && *p != quote)
	    if ((ptr - buf + 1) < bufsize)
	      *ptr++ = *p++;
	    else
	      p ++;

          if (*p == quote)
	    p ++;
	}
	else if ((ptr - buf + 1) < bufsize)
	  *ptr++ = *p++;
	else
	  p ++;

      *ptr = '\0';
    }

    if (strcasecmp(n, name) == 0)
      return (buf);
    else
      buf[0] = '\0';

    if (*p == '>')
      return (NULL);
  }

  return (NULL);
}


/** Gets a color attribute. */
fltk3::Color				// O - Color value
fltk3::HelpView::get_color(const char *n,	// I - Color name
                        fltk3::Color   c)	// I - Default color value
{
  int	i;				// Looping var
  int	rgb, r, g, b;			// RGB values
  static const struct {			// Color name table
    const char *name;
    int r, g, b;
  }	colors[] = {
    { "black",		0x00, 0x00, 0x00 },
    { "red",		0xff, 0x00, 0x00 },
    { "green",		0x00, 0x80, 0x00 },
    { "yellow",		0xff, 0xff, 0x00 },
    { "blue",		0x00, 0x00, 0xff },
    { "magenta",	0xff, 0x00, 0xff },
    { "fuchsia",	0xff, 0x00, 0xff },
    { "cyan",		0x00, 0xff, 0xff },
    { "aqua",		0x00, 0xff, 0xff },
    { "white",		0xff, 0xff, 0xff },
    { "gray",		0x80, 0x80, 0x80 },
    { "grey",		0x80, 0x80, 0x80 },
    { "lime",		0x00, 0xff, 0x00 },
    { "maroon",		0x80, 0x00, 0x00 },
    { "navy",		0x00, 0x00, 0x80 },
    { "olive",		0x80, 0x80, 0x00 },
    { "purple",		0x80, 0x00, 0x80 },
    { "silver",		0xc0, 0xc0, 0xc0 },
    { "teal",		0x00, 0x80, 0x80 }
  };


  if (!n || !n[0]) return c;

  if (n[0] == '#') {
    // Do hex color lookup
    rgb = strtol(n + 1, NULL, 16);

    if (strlen(n) > 4) {
      r = rgb >> 16;
      g = (rgb >> 8) & 255;
      b = rgb & 255;
    } else {
      r = (rgb >> 8) * 17;
      g = ((rgb >> 4) & 15) * 17;
      b = (rgb & 15) * 17;
    }
    return (fltk3::rgb_color((uchar)r, (uchar)g, (uchar)b));
  } else {
    for (i = 0; i < (int)(sizeof(colors) / sizeof(colors[0])); i ++)
      if (!strcasecmp(n, colors[i].name)) {
        return fltk3::rgb_color(colors[i].r, colors[i].g, colors[i].b);
      }
    return c;
  }
}


/** Gets an inline image.

  The image reference count is maintained accordingly, such that
  the image can be released exactly once when the document is closed.

  \return a pointer to a cached fltk3::SharedImage, if the image can be loaded,
  	  otherwise a pointer to an internal fltk3::Pixmap (broken_image).

  \todo fltk3::HelpView::get_image() returns a pointer to the internal
  fltk3::Pixmap broken_image, but this is _not_ compatible with the
  return type fltk3::SharedImage (release() must not be called).
*/

/* Implementation note: (A.S. Apr 05, 2009)

  fltk3::HelpView::get_image() uses a static global flag (initial_load)
  to determine, if it is called from the initial loading of a document
  (load() or value()), or from resize() or draw().

  A better solution would be to manage all loaded images in an own
  structure like fltk3::HelpTarget (Fl_Help_Image ?) to avoid using this
  global flag, but this would break the ABI !

  This should be fixed in FLTK 1.3 !


  If initial_load is true, then fltk3::SharedImage::get() is called to
  load the image, and the reference count of the shared image is
  increased by one.

  If initial_load is false, then fltk3::SharedImage::find() is called to
  load the image, and the image is released immediately. This avoids
  increasing the reference count when calling get_image() from draw()
  or resize().

  Calling fltk3::SharedImage::find() instead of fltk3::SharedImage::get() avoids
  doing unnecessary i/o for "broken images" within each resize/redraw.

  Each image must be released exactly once in the destructor or before
  a new document is loaded: see free_data().
*/

fltk3::SharedImage *
fltk3::HelpView::get_image(const char *name, int W, int H) {
  const char	*localname;		// Local filename
  char		dir[FLTK3_PATH_MAX];	// Current directory
  char		temp[FLTK3_PATH_MAX],	// Temporary filename
		*tempptr;		// Pointer into temporary name
  fltk3::SharedImage *ip;			// Image pointer...

  // See if the image can be found...
  if (strchr(directory_, ':') != NULL && strchr(name, ':') == NULL) {
    if (name[0] == '/') {
      strlcpy(temp, directory_, sizeof(temp));

      if ((tempptr = strrchr(strchr(directory_, ':') + 3, '/')) != NULL) {
        strlcpy(tempptr, name, sizeof(temp) - (tempptr - temp));
      } else {
        strlcat(temp, name, sizeof(temp));
      }
    } else {
      snprintf(temp, sizeof(temp), "%s/%s", directory_, name);
    }

    if (link_) localname = (*link_)(this, temp);
    else localname = temp;
  } else if (name[0] != '/' && strchr(name, ':') == NULL) {
    if (directory_[0]) snprintf(temp, sizeof(temp), "%s/%s", directory_, name);
    else {
      fltk3::getcwd(dir, sizeof(dir));
      snprintf(temp, sizeof(temp), "file:%s/%s", dir, name);
    }

    if (link_) localname = (*link_)(this, temp);
    else localname = temp;
  } else if (link_) localname = (*link_)(this, name);
  else localname = name;

  if (!localname) return 0;

  if (strncmp(localname, "file:", 5) == 0) localname += 5;

  if (initial_load) {
    if ((ip = fltk3::SharedImage::get(localname, W, H)) == NULL) {
      ip = (fltk3::SharedImage *)&broken_image;
    }
  } else { // draw or resize
    if ((ip = fltk3::SharedImage::find(localname, W, H)) == NULL) {
      ip = (fltk3::SharedImage *)&broken_image;
    } else {
      ip->release();
    }
  }

  return ip;
}


/** Gets a length value, either absolute or %. */
int
fltk3::HelpView::get_length(const char *l) {	// I - Value
  int	val;					// Integer value

  if (!l[0]) return 0;

  val = atoi(l);
  if (l[strlen(l) - 1] == '%') {
    if (val > 100) val = 100;
    else if (val < 0) val = 0;

    int scrollsize = scrollbar_size_ ? scrollbar_size_ : fltk3::scrollbar_size();
    val = val * (hsize_ - scrollsize) / 100;
  }

  return val;
}


fltk3::HelpLink *fltk3::HelpView::find_link(int xx, int yy)
{
  int		i;
  fltk3::HelpLink	*linkp;
  for (i = nlinks_, linkp = links_; i > 0; i --, linkp ++) {
    if (xx >= linkp->x && xx < linkp->w &&
        yy >= linkp->y && yy < linkp->h)
      break;
  }
  return i ? linkp : 0L;
}

void fltk3::HelpView::follow_link(fltk3::HelpLink *linkp)
{
  char		target[32];	// Current target

  clear_selection();

  strlcpy(target, linkp->name, sizeof(target));

  set_changed();

  if (strcmp(linkp->filename, filename_) != 0 && linkp->filename[0])
  {
    char	dir[FLTK3_PATH_MAX];	// Current directory
    char	temp[FLTK3_PATH_MAX],	// Temporary filename
	      *tempptr;	// Pointer into temporary filename


    if (strchr(directory_, ':') != NULL &&
        strchr(linkp->filename, ':') == NULL)
    {
      if (linkp->filename[0] == '/')
      {
        strlcpy(temp, directory_, sizeof(temp));
        if ((tempptr = strrchr(strchr(directory_, ':') + 3, '/')) != NULL)
	  strlcpy(tempptr, linkp->filename, sizeof(temp));
	else
	  strlcat(temp, linkp->filename, sizeof(temp));
      }
      else
	snprintf(temp, sizeof(temp), "%s/%s", directory_, linkp->filename);
    }
    else if (linkp->filename[0] != '/' && strchr(linkp->filename, ':') == NULL)
    {
      if (directory_[0])
	snprintf(temp, sizeof(temp), "%s/%s", directory_, linkp->filename);
      else
      {
	  fltk3::getcwd(dir, sizeof(dir));
	snprintf(temp, sizeof(temp), "file:%s/%s", dir, linkp->filename);
      }
    }
    else
      strlcpy(temp, linkp->filename, sizeof(temp));

    if (linkp->name[0])
      snprintf(temp + strlen(temp), sizeof(temp) - strlen(temp), "#%s",
	       linkp->name);

    load(temp);
  }
  else if (target[0])
    topline(target);
  else
    topline(0);

  leftline(0);
}

/** Removes the current text selection. */
void fltk3::HelpView::clear_selection()
{
  if (current_view==this)
    clear_global_selection();
}
/** Selects all the text in the view. */
void fltk3::HelpView::select_all()
{
  clear_global_selection();
  if (!value_) return;
  current_view = this;
  selection_drag_last = selection_last = strlen(value_);
  selected = 1;
}

void fltk3::HelpView::clear_global_selection()
{
  if (selected) redraw();
  selection_push_first = selection_push_last = 0;
  selection_drag_first = selection_drag_last = 0;
  selection_first = selection_last = 0;
  selected = 0;
}

char fltk3::HelpView::begin_selection()
{
  clear_global_selection();

  if (!fl_help_view_buffer) fl_help_view_buffer = fl_create_offscreen(1, 1);

  mouse_x = fltk3::event_x();
  mouse_y = fltk3::event_y();
  draw_mode = 1;

    current_view = this;
    fl_begin_offscreen(fl_help_view_buffer);
    draw();
    fl_end_offscreen();

  draw_mode = 0;

  if (selection_push_last) return 1;
  else return 0;
}

char fltk3::HelpView::extend_selection()
{
  if (fltk3::event_is_click())
    return 0;

//  printf("old selection_first=%d, selection_last=%d\n",
//         selection_first, selection_last);

  int sf = selection_first, sl = selection_last;

  selected = 1;
  mouse_x = fltk3::event_x();
  mouse_y = fltk3::event_y();
  draw_mode = 2;

    fl_begin_offscreen(fl_help_view_buffer);
    draw();
    fl_end_offscreen();

  draw_mode = 0;

  if (selection_push_first < selection_drag_first) {
    selection_first = selection_push_first;
  } else {
    selection_first = selection_drag_first;
  }

  if (selection_push_last > selection_drag_last) {
    selection_last = selection_push_last;
  } else {
    selection_last = selection_drag_last;
  }

//  printf("new selection_first=%d, selection_last=%d\n",
//         selection_first, selection_last);

  if (sf!=selection_first || sl!=selection_last) {
//    puts("REDRAW!!!\n");
    return 1;
  } else {
//    puts("");
    return 0;
  }
}

// convert a command with up to four letters into an unsigned int
static unsigned int command(const char *cmd)
{
  unsigned int ret = (tolower(cmd[0])<<24);
  char c = cmd[1];
  if (c=='>' || c==' ' || c==0) return ret;
  ret |= (tolower(c)<<16);
  c = cmd[2];
  if (c=='>' || c==' ' || c==0) return ret;
  ret |= (tolower(c)<<8);
  c = cmd[3];
  if (c=='>' || c==' ' || c==0) return ret;
  ret |= tolower(c);
  c = cmd[4];
  if (c=='>' || c==' ' || c==0) return ret;
  return 0;
}

#define CMD(a, b, c, d) ((a<<24)|(b<<16)|(c<<8)|d)

void fltk3::HelpView::end_selection(int clipboard) 
{
  if (!selected || current_view!=this) 
    return;
  // convert the select part of our html text into some kind of somewhat readable ASCII
  // and store it in the selection buffer
  char p = 0, pre = 0;;
  int len = strlen(value_);
  char *txt = (char*)malloc(len+1), *d = txt;
  const char *s = value_, *cmd, *src;
  for (;;) {
    char c = *s++;
    if (c==0) break;
    if (c=='<') { // begin of some html command. Skip until we find a '>'
      cmd = s;
      for (;;) {
        c = *s++;
        if (c==0 || c=='>') break;
      }
      if (c==0) break;
      // do something with this command... .
      // the replacement string must not be longer that the command itself plus '<' and '>'
      src = 0;
      switch (command(cmd)) {
        case CMD('p','r','e', 0 ): pre = 1; break;
        case CMD('/','p','r','e'): pre = 0; break;
        case CMD('t','d', 0 , 0 ):
        case CMD('p', 0 , 0 , 0 ):
        case CMD('/','p', 0 , 0 ):
        case CMD('b','r', 0 , 0 ): src = "\n"; break;
        case CMD('l','i', 0 , 0 ): src = "\n * "; break;
        case CMD('/','h','1', 0 ):
        case CMD('/','h','2', 0 ):
        case CMD('/','h','3', 0 ):
        case CMD('/','h','4', 0 ):
        case CMD('/','h','5', 0 ):
        case CMD('/','h','6', 0 ): src = "\n\n"; break;
        case CMD('t','r', 0 , 0 ):
        case CMD('h','1', 0 , 0 ):
        case CMD('h','2', 0 , 0 ):
        case CMD('h','3', 0 , 0 ):
        case CMD('h','4', 0 , 0 ):
        case CMD('h','5', 0 , 0 ):
        case CMD('h','6', 0 , 0 ): src = "\n\n"; break;
        case CMD('d','t', 0 , 0 ): src = "\n "; break;
        case CMD('d','d', 0 , 0 ): src = "\n - "; break;
      }
      int n = s-value_;
      if (src && n>selection_first && n<=selection_last) {
        while (*src) {
          *d++ = *src++;
        }
        c = src[-1];
        p = isspace(c&255) ? ' ' : c;
      }
      continue;
    }
    if (c=='&') { // special characters
      int xx = quote_char(s);
      if (xx>=0) {
        c = (char)xx;
        for (;;) {
          char cc = *s++;
          if (!cc || cc==';') break;
        }
      }
    }
    int n = s-value_;
    if (n>selection_first && n<=selection_last) {
      if (!pre && isspace(c&255)) c = ' ';
      if (p!=' '||c!=' ')
        *d++ = c;
      p = c;
    }
  }
  *d = 0;
  fltk3::copy(txt, strlen(txt), clipboard);
  free(txt);
}

/** Handles events in the widget. */
int				// O - 1 if we handled it, 0 otherwise
fltk3::HelpView::handle(int event)	// I - Event to handle
{
  FLTK3_OBJECT_VCALLS_WRAPPER_RET(int, handle(event), Handle)
  static fltk3::HelpLink *linkp;   // currently clicked link

  int xx = fltk3::event_x() - x() + leftline_;
  int yy = fltk3::event_y() - y() + topline_;

  switch (event)
  {
    case fltk3::FOCUS:
      redraw();
      return 1;
    case fltk3::UNFOCUS:
      clear_selection();
      redraw();
      return 1;
    case fltk3::ENTER :
      fltk3::Group::handle(event);
      return 1;
    case fltk3::LEAVE :
      fltk3::cursor(fltk3::CURSOR_DEFAULT);
      break;
    case fltk3::MOVE:
      if (find_link(xx, yy)) fltk3::cursor(fltk3::CURSOR_HAND);
      else fltk3::cursor(fltk3::CURSOR_DEFAULT);
      return 1;
    case fltk3::PUSH:
      if (fltk3::Group::handle(event)) return 1;
      linkp = find_link(xx, yy);
      if (linkp) {
        fltk3::cursor(fltk3::CURSOR_HAND);
        return 1;
      }
      if (begin_selection()) {
        fltk3::cursor(fltk3::CURSOR_INSERT);
        return 1;
      }
      fltk3::cursor(fltk3::CURSOR_DEFAULT);
      return 1;
    case fltk3::DRAG:
      if (linkp) {
        if (fltk3::event_is_click()) {
          fltk3::cursor(fltk3::CURSOR_HAND);
        } else {
          fltk3::cursor(fltk3::CURSOR_DEFAULT); // should be "fltk3::CURSOR_CANCEL" if we had it
        }
        return 1;
      }
      if (current_view==this && selection_push_last) {
        if (extend_selection()) redraw();
        fltk3::cursor(fltk3::CURSOR_INSERT);
        return 1;
      }
      fltk3::cursor(fltk3::CURSOR_DEFAULT);
      return 1;
    case fltk3::RELEASE:
      if (linkp) {
        if (fltk3::event_is_click()) {
          follow_link(linkp);
        }
        fltk3::cursor(fltk3::CURSOR_DEFAULT);
        linkp = 0;
        return 1;
      }
      if (current_view==this && selection_push_last) {
        end_selection();
        return 1;
      }
      return 1;
    case fltk3::SHORTCUT: {
      if (fltk3::event_state() == fltk3::COMMAND) {
        switch ( fltk3::event_key() ) {
          case 'a': select_all(); redraw(); return 1;
          case 'c':
          case 'x': end_selection(1); return 1;
        }
      }
      break; }
  }
  return (fltk3::Group::handle(event));
}

/** 
  The constructor creates the fltk3::HelpView widget at the specified
  position and size.
*/
fltk3::HelpView::HelpView(int        xx,	// I - Left position
                	   int        yy,	// I - Top position
			   int        ww,	// I - Width in pixels
			   int        hh,	// I - Height in pixels
			   const char *l)
    : fltk3::Group(xx, yy, ww, hh, l),
      scrollbar_(xx + ww - fltk3::scrollbar_size(), yy,
                 fltk3::scrollbar_size(), hh - fltk3::scrollbar_size()),
      hscrollbar_(xx, yy + hh - fltk3::scrollbar_size(),
                  ww - fltk3::scrollbar_size(), fltk3::scrollbar_size())
{
  color(fltk3::BACKGROUND2_COLOR, fltk3::SELECTION_COLOR);

  title_[0]     = '\0';
  defcolor_     = fltk3::FOREGROUND_COLOR;
  bgcolor_      = fltk3::BACKGROUND_COLOR;
  textcolor_    = fltk3::FOREGROUND_COLOR;
  linkcolor_    = fltk3::SELECTION_COLOR;
  textfont_     = fltk3::TIMES;
  textsize_     = 12;
  value_        = NULL;

  ablocks_      = 0;
  nblocks_      = 0;
  blocks_       = (fltk3::HelpBlock *)0;

  link_         = (fltk3::HelpFunc *)0;

  alinks_       = 0;
  nlinks_       = 0;
  links_        = (fltk3::HelpLink *)0;

  atargets_     = 0;
  ntargets_     = 0;
  targets_      = (fltk3::HelpTarget *)0;

  directory_[0] = '\0';
  filename_[0]  = '\0';

  topline_      = 0;
  leftline_     = 0;
  size_         = 0;
  hsize_        = 0;
  scrollbar_size_ = 0;

  scrollbar_.value(0, hh, 0, 1);
  scrollbar_.step(8.0);
  scrollbar_.show();
  scrollbar_.callback(scrollbar_callback);

  hscrollbar_.value(0, ww, 0, 1);
  hscrollbar_.step(8.0);
  hscrollbar_.show();
  hscrollbar_.callback(hscrollbar_callback);
  hscrollbar_.type(fltk3::HORIZONTAL);
  end();

  resize(xx, yy, ww, hh);
}


/** Destroys the fltk3::HelpView widget.

  The destructor destroys the widget and frees all memory that has been
  allocated for the current document.
*/
fltk3::HelpView::~HelpView()
{
  clear_selection();
  free_data();
}


/** Loads the specified file.

  This method loads the specified file or URL.
*/
int				// O - 0 on success, -1 on error
fltk3::HelpView::load(const char *f)// I - Filename to load (may also have target)
{
  FILE		*fp;		// File to read from
  long		len;		// Length of file
  char		*target;	// Target in file
  char		*slash;		// Directory separator
  const char	*localname;	// Local filename
  char		error[1024];	// Error buffer
  char		newname[FLTK3_PATH_MAX];	// New filename buffer

  // printf("load(%s)\n",f); fflush(stdout);

  if (strncmp(f, "ftp:", 4) == 0 ||
      strncmp(f, "http:", 5) == 0 ||
      strncmp(f, "https:", 6) == 0 ||
      strncmp(f, "ipp:", 4) == 0 ||
      strncmp(f, "mailto:", 7) == 0 ||
      strncmp(f, "news:", 5) == 0) {
    char urimsg[FLTK3_PATH_MAX];
    if ( fltk3::open_uri(f, urimsg, sizeof(urimsg)) == 0 ) {
      clear_selection();

      strlcpy(newname, f, sizeof(newname));
      if ((target = strrchr(newname, '#')) != NULL)
	*target++ = '\0';

      if (link_)
	localname = (*link_)(this, newname);
      else
	localname = filename_;

      if (!localname)
	return (0);

      free_data();

      strlcpy(filename_, newname, sizeof(filename_));
      strlcpy(directory_, newname, sizeof(directory_));

      // Note: We do not support Windows backslashes, since they are illegal
      //       in URLs...
      if ((slash = strrchr(directory_, '/')) == NULL)
	directory_[0] = '\0';
      else if (slash > directory_ && slash[-1] != '/')
	*slash = '\0';

      snprintf(error, sizeof(error),
	       "<HTML><HEAD><TITLE>Error</TITLE></HEAD>"
	       "<BODY><H1>Error</H1>"
	       "<P>Unable to follow the link \"%s\" - "
	       "%s.</P></BODY>",
	       f, urimsg);
      value(error);
      //return(-1);
    }
    return(0);
  }

  clear_selection();

  strlcpy(newname, f, sizeof(newname));
  if ((target = strrchr(newname, '#')) != NULL)
    *target++ = '\0';

  if (link_)
    localname = (*link_)(this, newname);
  else
    localname = filename_;

  if (!localname)
    return (0);

  free_data();

  strlcpy(filename_, newname, sizeof(filename_));
  strlcpy(directory_, newname, sizeof(directory_));

  // Note: We do not support Windows backslashes, since they are illegal
  //       in URLs...
  if ((slash = strrchr(directory_, '/')) == NULL)
    directory_[0] = '\0';
  else if (slash > directory_ && slash[-1] != '/')
    *slash = '\0';

  if (strncmp(localname, "file:", 5) == 0)
    localname += 5;	// Adjust for local filename...

  if ((fp = fltk3::fopen(localname, "rb")) != NULL)
  {
    fseek(fp, 0, SEEK_END);
    len = ftell(fp);
    rewind(fp);

    value_ = (const char *)calloc(len + 1, 1);
    if (fread((void *)value_, 1, len, fp)==0) { /* use default 0 */ }
    fclose(fp);
  }
  else
  {
    snprintf(error, sizeof(error),
	     "<HTML><HEAD><TITLE>Error</TITLE></HEAD>"
	     "<BODY><H1>Error</H1>"
	     "<P>Unable to follow the link \"%s\" - "
	     "%s.</P></BODY>",
	     localname, strerror(errno));
    value_ = strdup(error);
  }

  initial_load = 1;
  format();
  initial_load = 0;

  if (target)
    topline(target);
  else
    topline(0);

  return (0);
}


/** Resizes the help widget. */

void
fltk3::HelpView::resize(int xx,	// I - New left position
                     int yy,	// I - New top position
		     int ww,	// I - New width
		     int hh)	// I - New height
{
  fltk3::Boxtype		b = box() ? box() : fltk3::DOWN_BOX;
					// Box to draw...


  fltk3::Widget::resize(xx, yy, ww, hh);

  int scrollsize = scrollbar_size_ ? scrollbar_size_ : fltk3::scrollbar_size();
  scrollbar_.resize(x() + w() - scrollsize - fltk3::box_dw(b) + fltk3::box_dx(b),
                    y() + fltk3::box_dy(b), scrollsize, h() - scrollsize - fltk3::box_dh(b));
  hscrollbar_.resize(x() + fltk3::box_dx(b),
                     y() + h() - scrollsize - fltk3::box_dh(b) + fltk3::box_dy(b),
                     w() - scrollsize - fltk3::box_dw(b), scrollsize);

  format();
}


/** Scrolls the text to the indicated position, given a named destination.

  \param[in] n target name
*/
void
fltk3::HelpView::topline(const char *n)	// I - Target name
{
  fltk3::HelpTarget key,			// Target name key
		*target;		// Pointer to matching target


  if (ntargets_ == 0)
    return;

  strlcpy(key.name, n, sizeof(key.name));

  target = (fltk3::HelpTarget *)bsearch(&key, targets_, ntargets_, sizeof(fltk3::HelpTarget),
                                 (compare_func_t)compare_targets);

  if (target != NULL)
    topline(target->y);
}


/** Scrolls the text to the indicated position, given a pixel line.

  If the given pixel value \p top is out of range, then the text is
  scrolled to the top or bottom of the document, resp.

  \param[in] top top line number in pixels (0 = start of document)
*/
void
fltk3::HelpView::topline(int top)	// I - Top line number
{
  if (!value_)
    return;

  int scrollsize = scrollbar_size_ ? scrollbar_size_ : fltk3::scrollbar_size();
  if (size_ < (h() - scrollsize) || top < 0)
    top = 0;
  else if (top > size_)
    top = size_;

  topline_ = top;

  scrollbar_.value(topline_, h() - scrollsize, 0, size_);

  do_callback();

  redraw();
}


/** Scrolls the text to the indicated position, given a pixel column.

  If the given pixel value \p left is out of range, then the text is
  scrolled to the left or right side of the document, resp.

  \param[in] left left column number in pixels (0 = left side)
*/
void
fltk3::HelpView::leftline(int left)	// I - Left position
{
  if (!value_)
    return;

  int scrollsize = scrollbar_size_ ? scrollbar_size_ : fltk3::scrollbar_size();
  if (hsize_ < (w() - scrollsize) || left < 0)
    left = 0;
  else if (left > hsize_)
    left = hsize_;

  leftline_ = left;

  hscrollbar_.value(leftline_, w() - scrollsize, 0, hsize_);

  redraw();
}


/** Sets the current help text buffer to the string provided and reformats the text.

  The provided character string \p val is copied internally and will be
  freed when value() is called again, or when the widget is destroyed.

  If \p val is NULL, then the widget is cleared.
*/
void
fltk3::HelpView::value(const char *val)	// I - Text to view
{
  clear_selection();
  free_data();
  set_changed();

  if (!val)
    return;

  value_ = strdup(val);

  initial_load = 1;
  format();
  initial_load = 0;

  topline(0);
  leftline(0);
}


#ifdef ENC
# undef ENC
#endif
// part b in the table seems to be mac_roman - beku
# define ENC(a, b) a


/** Returns the character code associated with a quoted char. */
static int			// O - Code or -1 on error
quote_char(const char *p) {	// I - Quoted string
  int	i;			// Looping var
  static struct {
    const char	*name;
    int		namelen;
    int		code;
  }	*nameptr,		// Pointer into name array
	names[] = {		// Quoting names
    { "Aacute;", 7, ENC(193,231) },
    { "aacute;", 7, ENC(225,135) },
    { "Acirc;",  6, ENC(194,229) },
    { "acirc;",  6, ENC(226,137) },
    { "acute;",  6, ENC(180,171) },
    { "AElig;",  6, ENC(198,174) },
    { "aelig;",  6, ENC(230,190) },
    { "Agrave;", 7, ENC(192,203) },
    { "agrave;", 7, ENC(224,136) },
    { "amp;",    4, ENC('&','&') },
    { "Aring;",  6, ENC(197,129) },
    { "aring;",  6, ENC(229,140) },
    { "Atilde;", 7, ENC(195,204) },
    { "atilde;", 7, ENC(227,139) },
    { "Auml;",   5, ENC(196,128) },
    { "auml;",   5, ENC(228,138) },
    { "brvbar;", 7, ENC(166, -1) },
    { "bull;",   5, ENC(149,165) },
    { "Ccedil;", 7, ENC(199,199) },
    { "ccedil;", 7, ENC(231,141) },
    { "cedil;",  6, ENC(184,252) },
    { "cent;",   5, ENC(162,162) },
    { "copy;",   5, ENC(169,169) },
    { "curren;", 7, ENC(164, -1) },
    { "deg;",    4, ENC(176,161) },
    { "divide;", 7, ENC(247,214) },
    { "Eacute;", 7, ENC(201,131) },
    { "eacute;", 7, ENC(233,142) },
    { "Ecirc;",  6, ENC(202,230) },
    { "ecirc;",  6, ENC(234,144) },
    { "Egrave;", 7, ENC(200,233) },
    { "egrave;", 7, ENC(232,143) },
    { "ETH;",    4, ENC(208, -1) },
    { "eth;",    4, ENC(240, -1) },
    { "Euml;",   5, ENC(203,232) },
    { "euml;",   5, ENC(235,145) },
    { "euro;",   5, ENC(128,219) },
    { "frac12;", 7, ENC(189, -1) },
    { "frac14;", 7, ENC(188, -1) },
    { "frac34;", 7, ENC(190, -1) },
    { "gt;",     3, ENC('>','>') },
    { "Iacute;", 7, ENC(205,234) },
    { "iacute;", 7, ENC(237,146) },
    { "Icirc;",  6, ENC(206,235) },
    { "icirc;",  6, ENC(238,148) },
    { "iexcl;",  6, ENC(161,193) },
    { "Igrave;", 7, ENC(204,237) },
    { "igrave;", 7, ENC(236,147) },
    { "iquest;", 7, ENC(191,192) },
    { "Iuml;",   5, ENC(207,236) },
    { "iuml;",   5, ENC(239,149) },
    { "laquo;",  6, ENC(171,199) },
    { "lt;",     3, ENC('<','<') },
    { "macr;",   5, ENC(175,248) },
    { "micro;",  6, ENC(181,181) },
    { "middot;", 7, ENC(183,225) },
    { "nbsp;",   5, ENC(' ',' ') },
    { "not;",    4, ENC(172,194) },
    { "Ntilde;", 7, ENC(209,132) },
    { "ntilde;", 7, ENC(241,150) },
    { "Oacute;", 7, ENC(211,238) },
    { "oacute;", 7, ENC(243,151) },
    { "Ocirc;",  6, ENC(212,239) },
    { "ocirc;",  6, ENC(244,153) },
    { "Ograve;", 7, ENC(210,241) },
    { "ograve;", 7, ENC(242,152) },
    { "ordf;",   5, ENC(170,187) },
    { "ordm;",   5, ENC(186,188) },
    { "Oslash;", 7, ENC(216,175) },
    { "oslash;", 7, ENC(248,191) },
    { "Otilde;", 7, ENC(213,205) },
    { "otilde;", 7, ENC(245,155) },
    { "Ouml;",   5, ENC(214,133) },
    { "ouml;",   5, ENC(246,154) },
    { "para;",   5, ENC(182,166) },
    { "premil;", 7, ENC(137,228) },
    { "plusmn;", 7, ENC(177,177) },
    { "pound;",  6, ENC(163,163) },
    { "quot;",   5, ENC('\"','\"') },
    { "raquo;",  6, ENC(187,200) },
    { "reg;",    4, ENC(174,168) },
    { "sect;",   5, ENC(167,164) },
    { "shy;",    4, ENC(173,'-') },
    { "sup1;",   5, ENC(185, -1) },
    { "sup2;",   5, ENC(178, -1) },
    { "sup3;",   5, ENC(179, -1) },
    { "szlig;",  6, ENC(223,167) },
    { "THORN;",  6, ENC(222, -1) },
    { "thorn;",  6, ENC(254, -1) },
    { "times;",  6, ENC(215,'x') },
    { "trade;",  6, ENC(153,170) },
    { "Uacute;", 7, ENC(218,242) },
    { "uacute;", 7, ENC(250,156) },
    { "Ucirc;",  6, ENC(219,243) },
    { "ucirc;",  6, ENC(251,158) },
    { "Ugrave;", 7, ENC(217,244) },
    { "ugrave;", 7, ENC(249,157) },
    { "uml;",    4, ENC(168,172) },
    { "Uuml;",   5, ENC(220,134) },
    { "uuml;",   5, ENC(252,159) },
    { "Yacute;", 7, ENC(221, -1) },
    { "yacute;", 7, ENC(253, -1) },
    { "yen;",    4, ENC(165,180) },
    { "Yuml;",   5, ENC(159,217) },
    { "yuml;",   5, ENC(255,216) }
  };

  if (!strchr(p, ';')) return -1;
  if (*p == '#') {
    if (*(p+1) == 'x' || *(p+1) == 'X') return strtol(p+2, NULL, 16);
    else return atoi(p+1);
  }
  for (i = (int)(sizeof(names) / sizeof(names[0])), nameptr = names; i > 0; i --, nameptr ++)
    if (strncmp(p, nameptr->name, nameptr->namelen) == 0)
      return nameptr->code;

  return -1;
}


/** The vertical scrollbar callback. */
static void
scrollbar_callback(fltk3::Widget *s, void *)
{
  ((fltk3::HelpView *)(s->parent()))->topline(int(((fltk3::Scrollbar*)s)->value()));
}


/** The horizontal scrollbar callback. */
static void
hscrollbar_callback(fltk3::Widget *s, void *)
{
  ((fltk3::HelpView *)(s->parent()))->leftline(int(((fltk3::Scrollbar*)s)->value()));
}


//
// End of "$Id$".
//
