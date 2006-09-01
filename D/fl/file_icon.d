/+- This file was imported from C++ using a script
//
// "$Id: file_icon.d 4288 2005-04-16 00:13:17Z mike $"
//
// Fl_File_Icon definitions.
//
// Copyright 1999-2005 by Michael Sweet.
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

//
// Include necessary header files...
//

version (!_Fl_Fl_File_Icon_H_) {
#  define _Fl_Fl_File_Icon_H_

public import fl.fl;


//
// Special color value for the icon color.
//

const int FL_ICON_COLOR = (Fl_Color)0xffffffff; 


//
// Fl_File_Icon class...
//

class Fl_File_Icon			//// Icon data
{
  static Fl_File_Icon  first_;	// Pointer to first icon/filetype
  Fl_File_Icon	 next_;		// Pointer to next icon/filetype
  char	*pattern_;	// Pattern string
  int		type_;		// Match only if directory or file?
  int		num_data_;	// Number of data elements
  int		alloc_data_;	// Number of allocated elements
  short		*data_;		// Icon data

  public:

  enum				// File types
  {
    ANY,			// Any kind of file
    PLAIN,			// Only plain files
    FIFO,			// Only named pipes
    DEVICE,			// Only character and block devices
    LINK,			// Only symbolic links
    DIRECTORY			// Only directories
  };

  enum				// Data opcodes
  {
    END,			// End of primitive/icon
    COLOR,			// Followed by color value (2 shorts)
    LINE,			// Start of line
    CLOSEDLINE,			// Start of closed line
    POLYGON,			// Start of polygon
    OUTLINEPOLYGON,		// Followed by outline color (2 shorts)
    VERTEX			// Followed by scaled X,Y
  };

  Fl_File_Icon(char *p, int t, int nd = 0, short *d = 0);
  ~Fl_File_Icon();

  short		*add(short d);
  short		*add_color(Fl_Color c)
		{ short *d = add((short)COLOR); add((short)(c >> 16)); add((short)c); return (d); }
  short		*add_vertex(int x, int y)
		{ short *d = add((short)VERTEX); add((short)x); add((short)y); return (d); }
  short		*add_vertex(float x, float y)
		{ short *d = add((short)VERTEX); add((short)(x * 10000.0));
		  add((short)(y * 10000.0)); return (d); }
  void		clear() { num_data_ = 0; }
  void		draw(int x, int y, int w, int h, Fl_Color ic, int active = 1);
  void		label(Fl_Widget  w);
  static void	labeltype(Fl_Label  o, int x, int y, int w, int h, Fl_Align a);
  void		load(char *f);
  int		load_fti(char *fti);
  int		load_image(char *i);
  Fl_File_Icon	 next() { return (next_); }
  char	*pattern() { return (pattern_); }
  int		size() { return (num_data_); }
  int		type() { return (type_); }
  short		*value() { return (data_); }

  static Fl_File_Icon  find(char *filename, int filetype = ANY);
  static Fl_File_Icon  first() { return (first_); }
  static void	load_system_icons(void);
};

} // !_Fl_Fl_File_Icon_H_

//
// End of "$Id: file_icon.d 4288 2005-04-16 00:13:17Z mike $".
//
    End of automatic import -+/
/+- This file was imported from C++ using a script
//
// "$Id: file_icon.d 5190 2006-06-09 16:16:34Z mike $"
//
// Fl_File_Icon routines.
//
// KDE icon code donated by Maarten De Boer.
//
// Copyright 1999-2005 by Michael Sweet.
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
//   Fl_File_Icon.Fl_File_Icon()       - Create a new file icon.
//   Fl_File_Icon::~Fl_File_Icon()      - Remove a file icon.
//   Fl_File_Icon.add()               - Add data to an icon.
//   Fl_File_Icon.find()              - Find an icon based upon a given file.
//   Fl_File_Icon.draw()              - Draw an icon.
//   Fl_File_Icon.label()             - Set the widgets label to an icon.
//   Fl_File_Icon.labeltype()         - Draw the icon label.
//

//
// Include necessary header files...
//

#include <stdio.h>
#include <stdlib.h>
private import fl.flstring;
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#if (defined(WIN32) && ! defined(__CYGWIN__)) || defined(__EMX__)
#  include <io.h>
const int F_OK = 0; 
} else {
#  include <unistd.h>
} /* WIN32 || __EMX__ */

private import fl.file_icon;
private import fl.widget;
private import fl.draw;
#include <FL/filename.H>


//
// Define missing POSIX/XPG4 macros as needed...
//

version (!S_ISDIR) {
#  define S_ISBLK(m) (((m) & S_IFMT) == S_IFBLK)
#  define S_ISCHR(m) (((m) & S_IFMT) == S_IFCHR)
#  define S_ISDIR(m) (((m) & S_IFMT) == S_IFDIR)
#  define S_ISFIFO(m) (((m) & S_IFMT) == S_IFIFO)
#  define S_ISLNK(m) (((m) & S_IFMT) == S_IFLNK)
} /* !S_ISDIR */


//
// Icon cache...
//

Fl_File_Icon	 Fl_File_Icon.first_ = (Fl_File_Icon  )0;


//
// 'Fl_File_Icon.Fl_File_Icon()' - Create a new file icon.
//

Fl_File_Icon.Fl_File_Icon(char *p,	/* I - Filename pattern */
                	   int        t,	/* I - File type */
			   int        nd,	/* I - Number of data values */
			   short      *d)	/* I - Data values */
{
  // Initialize the pattern and type...
  pattern_ = p;
  type_    = t;

  // Copy icon data as needed...
  if (nd)
  {
    num_data_   = nd;
    alloc_data_ = nd + 1;
    data_       = (short *)calloc(sizeof(short), nd + 1);
    memcpy(data_, d, nd * sizeof(short));
  }
  else
  {
    num_data_   = 0;
    alloc_data_ = 0;
  }

  // And add the icon to the list of icons...
  next_  = first_;
  first_ = this;
}


//
// 'Fl_File_Icon::~Fl_File_Icon()' - Remove a file icon.
//

Fl_File_Icon::~Fl_File_Icon()
{
  Fl_File_Icon	 current,	// Current icon in list
		*prev;		// Previous icon in list


  // Find the icon in the list...
  for (current = first_, prev = (Fl_File_Icon  )0;
       current != this && current != (Fl_File_Icon  )0;
       prev = current, current = current.next_);

  // Remove the icon from the list as needed...
  if (current)
  {
    if (prev)
      prev.next_ = current.next_;
    else
      first_ = current.next_;
  }

  // Free any memory used...
  if (alloc_data_)
    free(data_);
}


//
// 'Fl_File_Icon.add()' - Add data to an icon.
//

short *				// O - Pointer to new data value
Fl_File_Icon.add(short d)	// I - Data to add
{
  short	*dptr;			// Pointer to new data value


  // Allocate/reallocate memory as needed
  if ((num_data_ + 1) >= alloc_data_)
  {
    alloc_data_ += 128;

    if (alloc_data_ == 128)
      dptr = (short *)malloc(sizeof(short) * alloc_data_);
    else
      dptr = (short *)realloc(data_, sizeof(short) * alloc_data_);

    if (dptr == NULL)
      return (NULL);

    data_ = dptr;
  }

  // Store the new data value and return
  data_[num_data_++] = d;
  data_[num_data_]   = END;

  return (data_ + num_data_ - 1);
}


//
// 'Fl_File_Icon.find()' - Find an icon based upon a given file.
//

Fl_File_Icon  				// O - Matching file icon or NULL
Fl_File_Icon.find(char *filename,// I - Name of file */
                   int        filetype)	// I - Enumerated file type
{
  Fl_File_Icon	 current;		// Current file in list
version (!WIN32) {
  struct stat	fileinfo;		// Information on file
} // !WIN32
  char	*name;			// Base name of filename


  // Get file information if needed...
  if (filetype == ANY)
  {
version (WIN32) {
    if (filename[strlen(filename) - 1] == '/')
      filetype = DIRECTORY;
    else if (fl_filename_isdir(filename))
      filetype = DIRECTORY;
    else
      filetype = PLAIN;
} else {
    if (!stat(filename, &fileinfo))
    {
      if (S_ISDIR(fileinfo.st_mode))
        filetype = DIRECTORY;
version (S_IFIFO) {
      else if (S_ISFIFO(fileinfo.st_mode))
        filetype = FIFO;
} // S_IFIFO
version (S_ICHR) && defined(S_IBLK) {
      else if (S_ISCHR(fileinfo.st_mode) || S_ISBLK(fileinfo.st_mode))
        filetype = DEVICE;
} // S_ICHR && S_IBLK
version (S_ILNK) {
      else if (S_ISLNK(fileinfo.st_mode))
        filetype = LINK;
} // S_ILNK
      else
        filetype = PLAIN;
    }
    else
      filetype = PLAIN;
} // WIN32
  }

  // Look at the base name in the filename
  name = fl_filename_name(filename);

  // Loop through the available file types and return any match that
  // is found...
  for (current = first_; current != (Fl_File_Icon  )0; current = current.next_)
    if ((current.type_ == filetype || current.type_ == ANY) &&
        (fl_filename_match(filename, current.pattern_) ||
	 fl_filename_match(name, current.pattern_)))
      break;

  // Return the match (if any)...
  return (current);
}


//
// 'Fl_File_Icon.draw()' - Draw an icon.
//

void
Fl_File_Icon.draw(int      x,		// I - Upper-lefthand X
        	   int      y,		// I - Upper-lefthand Y
		   int      w,		// I - Width of bounding box
		   int      h,		// I - Height of bounding box
        	   Fl_Color ic,		// I - Icon color...
        	   int      active)	// I - Active or inactive?
{
  Fl_Color	c,		// Current color
		oc;		// Outline color
  short		*d,		// Pointer to data
		*dend;		// End of data...
  short		*prim;		// Pointer to start of primitive...
  double	scale;		// Scale of icon


  // Don't try to draw a NULL array!
  if (num_data_ == 0)
    return;

  // Setup the transform matrix as needed...
  scale = w < h ? w : h;

  fl_push_matrix();
  fl_translate((float)x + 0.5 * ((float)w - scale),
               (float)y + 0.5 * ((float)h + scale));
  fl_scale(scale, -scale);

  // Loop through the array until we see an unmatched END...
  d    = data_;
  dend = data_ + num_data_;
  prim = NULL;
  c    = ic;

  if (active)
    fl_color(c);
  else
    fl_color(fl_inactive(c));

  while (d < dend)
    switch (*d)
    {
      case END :
          if (prim)
            switch (*prim)
	    {
	      case LINE :
		  fl_end_line();
		  break;

	      case CLOSEDLINE :
		  fl_end_loop();
		  break;

	      case POLYGON :
		  fl_end_complex_polygon();
		  break;

	      case OUTLINEPOLYGON :
		  fl_end_complex_polygon();

        	  oc = (Fl_Color)((((ushort *)prim)[1] << 16) | 
	                	  ((ushort *)prim)[2]);
                  if (active)
		  {
                    if (oc == FL_ICON_COLOR)
		      fl_color(ic);
		    else
		      fl_color(oc);
		  }
		  else
		  {
                    if (oc == FL_ICON_COLOR)
		      fl_color(fl_inactive(ic));
		    else
		      fl_color(fl_inactive(oc));
		  }

		  fl_begin_loop();

		  prim += 3;
		  while (*prim == VERTEX)
		  {
		    fl_vertex(prim[1] * 0.0001, prim[2] * 0.0001);
		    prim += 3;
		  }

        	  fl_end_loop();
		  fl_color(c);
		  break;
	    }

          prim = NULL;
	  d ++;
	  break;

      case COLOR :
          c = (Fl_Color)((((ushort *)d)[1] << 16) | 
	                   ((ushort *)d)[2]);

          if (c == FL_ICON_COLOR)
	    c = ic;

          if (!active)
	    c = fl_inactive(c);

          fl_color(c);
	  d += 3;
	  break;

      case LINE :
          prim = d;
	  d ++;
	  fl_begin_line();
	  break;

      case CLOSEDLINE :
          prim = d;
	  d ++;
	  fl_begin_loop();
	  break;

      case POLYGON :
          prim = d;
	  d ++;
	  fl_begin_complex_polygon();
	  break;

      case OUTLINEPOLYGON :
          prim = d;
	  d += 3;
	  fl_begin_complex_polygon();
	  break;

      case VERTEX :
          if (prim)
	    fl_vertex(d[1] * 0.0001, d[2] * 0.0001);
	  d += 3;
	  break;

      default : // Ignore invalid data...
          d ++;
    }

  // If we still have an open primitive, close it...
  if (prim)
    switch (*prim)
    {
      case LINE :
	  fl_end_line();
	  break;

      case CLOSEDLINE :
	  fl_end_loop();
	  break;

      case POLYGON :
	  fl_end_polygon();
	  break;

      case OUTLINEPOLYGON :
	  fl_end_polygon();

          oc = (Fl_Color)((((ushort *)prim)[1] << 16) | 
	                  ((ushort *)prim)[2]);
          if (active)
	  {
            if (oc == FL_ICON_COLOR)
	      fl_color(ic);
	    else
	      fl_color(oc);
	  }
	  else
	  {
            if (oc == FL_ICON_COLOR)
	      fl_color(fl_inactive(ic));
	    else
	      fl_color(fl_inactive(oc));
	  }

	  fl_begin_loop();

	  prim += 3;
	  while (*prim == VERTEX)
	  {
	    fl_vertex(prim[1] * 0.0001, prim[2] * 0.0001);
	    prim += 3;
	  }

          fl_end_loop();
	  fl_color(c);
	  break;
    }

  // Restore the transform matrix
  fl_pop_matrix();
}


//
// 'Fl_File_Icon.label()' - Set the widget's label to an icon.
//

void
Fl_File_Icon.label(Fl_Widget  w)	// I - Widget to label
{
  Fl.set_labeltype(_FL_ICON_LABEL, labeltype, 0);
  w.label(_FL_ICON_LABEL, (char*)this);
}


//
// 'Fl_File_Icon.labeltype()' - Draw the icon label.
//

void
Fl_File_Icon.labeltype(Fl_Label  o,	// I - Label data
                	int            x,	// I - X position of label
			int            y,	// I - Y position of label
			int            w,	// I - Width of label
			int            h,	// I - Height of label
			Fl_Align       a)	// I - Label alignment (not used)
{
  Fl_File_Icon  icon;			// Pointer to icon data


  (void)a;

  icon = (Fl_File_Icon  )(o.value);
  if (icon) icon.draw(x, y, w, h, (Fl_Color)(o.color));
}


//
// End of "$Id: file_icon.d 5190 2006-06-09 16:16:34Z mike $".
//
    End of automatic import -+/
