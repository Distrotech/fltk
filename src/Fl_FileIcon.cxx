//
// "$Id: Fl_FileIcon.cxx,v 1.2 1999/10/28 01:02:12 vincent Exp $"
//
// Fl_FileIcon routines for the Fast Light Tool Kit (FLTK).
//
// Copyright 1997-1999 by Easy Software Products.
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
// Please report all bugs and problems to "fltk-bugs@easysw.com".
//
// Contents:
//
//   Fl_FileIcon::Fl_FileIcon()       - Create a new file icon.
//   Fl_FileIcon::~Fl_FileIcon()      - Remove a file icon.
//   Fl_FileIcon::add()               - Add data to an icon.
//   Fl_FileIcon::find()              - Find an icon based upon a given file.
//   Fl_FileIcon::draw()              - Draw an icon.
//   Fl_FileIcon::label()             - Set the widgets label to an icon.
//   Fl_FileIcon::labeltype()         - Draw the icon label.
//   Fl_FileIcon::load()              - Load an icon file...
//   Fl_FileIcon::load_fti()          - Load an SGI-format FTI file...
//   Fl_FileIcon::load_xpm()          - Load an XPM icon file...
//   Fl_FileIcon::load_system_icons() - Load the standard system icons/filetypes.
//

//
// Include necessary header files...
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#if defined(WIN32) || defined(__EMX__)
#  include <io.h>
extern "C" int access(const char *, int);
#  define F_OK 0
#else
#  include <unistd.h>
#endif /* WIN32 || __EMX__ */

#include <FL/Fl_FileIcon.h>
#include <FL/Fl_Widget.H>
#include <FL/fl_draw.H>
#include <FL/filename.H>


//
// Define missing POSIX/XPG4 macros as needed...
//

#ifndef S_ISDIR
#  define S_ISBLK(m) (((m) & S_IFMT) == S_IFBLK)
#  define S_ISCHR(m) (((m) & S_IFMT) == S_IFCHR)
#  define S_ISDIR(m) (((m) & S_IFMT) == S_IFDIR)
#  define S_ISFIFO(m) (((m) & S_IFMT) == S_IFIFO)
#  define S_ISLNK(m) (((m) & S_IFMT) == S_IFLNK)
#endif /* !S_ISDIR */


//
// Icon cache...
//

Fl_FileIcon	*Fl_FileIcon::first_ = (Fl_FileIcon *)0;


//
// 'Fl_FileIcon::Fl_FileIcon()' - Create a new file icon.
//

Fl_FileIcon::Fl_FileIcon(const char *p,	/* I - Filename pattern */
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
// 'Fl_FileIcon::~Fl_FileIcon()' - Remove a file icon.
//

Fl_FileIcon::~Fl_FileIcon()
{
  Fl_FileIcon	*current,	// Current icon in list
		*prev;		// Previous icon in list


  // Find the icon in the list...
  for (current = first_, prev = (Fl_FileIcon *)0;
       current != this && current != (Fl_FileIcon *)0;
       prev = current, current = current->next_);

  // Remove the icon from the list as needed...
  if (current)
  {
    if (prev)
      prev->next_ = current->next_;
    else
      first_ = current->next_;
  }

  // Free any memory used...
  if (alloc_data_)
    free(data_);
}


//
// 'Fl_FileIcon::add()' - Add data to an icon.
//

short *			// O - Pointer to new data value
Fl_FileIcon::add(short d)	// I - Data to add
{
  short	*dptr;		// Pointer to new data value


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
// 'Fl_FileIcon::find()' - Find an icon based upon a given file.
//

Fl_FileIcon *				// O - Matching file icon or NULL
Fl_FileIcon::find(const char *filename,	// I - Name of file */
                  int        filetype)	// I - Enumerated file type
{
  Fl_FileIcon	*current;		// Current file in list
  struct stat	fileinfo;		// Information on file


  // Get file information if needed...
  if (filetype == ANY)
    if (!stat(filename, &fileinfo))
    {
      if (S_ISDIR(fileinfo.st_mode))
        filetype = DIRECTORY;
#ifdef S_IFIFO
      else if (S_ISFIFO(fileinfo.st_mode))
        filetype = FIFO;
#endif // S_IFIFO
#if defined(S_ICHR) && defined(S_IBLK)
      else if (S_ISCHR(fileinfo.st_mode) || S_ISBLK(fileinfo.st_mode))
        filetype = DEVICE;
#endif // S_ICHR && S_IBLK
#ifdef S_ILNK
      else if (S_ISLNK(fileinfo.st_mode))
        filetype = LINK;
#endif // S_ILNK
      else
        filetype = PLAIN;
    }

  // Loop through the available file types and return any match that
  // is found...
  for (current = first_; current != (Fl_FileIcon *)0; current = current->next_)
    if ((current->type_ == filetype || current->type_ == ANY) &&
        filename_match(filename, current->pattern_))
      break;

  // Return the match (if any)...
  return (current);
}


//
// 'Fl_FileIcon::draw()' - Draw an icon.
//

void
Fl_FileIcon::draw(int      x,	// I - Upper-lefthand X
                  int      y,	// I - Upper-lefthand Y
	          int      w,	// I - Width of bounding box
	          int      h,	// I - Height of bounding box
                  Fl_Color ic)	// I - Icon color...
{
  Fl_Color	c;		// Current color
  short		*d;		// Pointer to data
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
  prim = NULL;
  c    = ic;
  fl_color(c);

  while (*d != END || prim)
    switch (*d)
    {
      case END :
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

                if (prim[1] == 256)
		  fl_color(ic);
		else
		  fl_color((Fl_Color)prim[1]);
		fl_begin_loop();

		prim += 2;
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
          if (d[1] == 256)
	    c = ic;
	  else
	    c = (Fl_Color)d[1];
          fl_color(c);
	  d += 2;
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
	  fl_begin_polygon();
	  break;

      case OUTLINEPOLYGON :
          prim = d;
	  d += 2;
	  fl_begin_polygon();
	  break;

      case VERTEX :
          if (prim)
	    fl_vertex(d[1] * 0.0001, d[2] * 0.0001);
	  d += 3;
	  break;
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

          if (prim[1] == 256)
	    fl_color(ic);
	  else
	    fl_color((Fl_Color)prim[1]);
	  fl_begin_loop();

	  prim += 2;
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


#if 0 // All the label type stuff has changed!  How do we do it now????
//
// 'Fl_FileIcon::label()' - Set the widget's label to an icon.
//

void
Fl_FileIcon::label(Fl_Widget *w)	// I - Widget to label
{
  Fl::set_labeltype(_FL_ICON_LABEL, labeltype, 0);
  w->label(_FL_ICON_LABEL, (const char*)this);
}


//
// 'Fl_FileIcon::labeltype()' - Draw the icon label.
//

void
Fl_FileIcon::labeltype(const Fl_Label *o,	// I - Label data
                       int            x,	// I - X position of label
		       int            y,	// I - Y position of label
		       int            w,	// I - Width of label
		       int            h,	// I - Height of label
		       Fl_Align       a)	// I - Label alignment (not used)
{
  FileIcon *icon;			// Pointer to icon data


  icon = (FileIcon *)(o->value);

  icon->draw(x, y, w, h, (Fl_Color)(o->color));
}
#endif // 0


//
// 'Fl_FileIcon::load()' - Load an icon file...
//

void
Fl_FileIcon::load(const char *f)	// I - File to read from
{
  const char	*ext;			// File extension


  if ((ext = filename_ext(f)) == NULL)

  if (strcmp(ext, "fti") == 0)
    load_fti(f);
  else if (strcmp(ext, "xpm") == 0)
    load_xpm(f);
#if 0
  else if (strcmp(ext, "png") == 0)
    load_png(f);
#endif /* 0 */
}


//
// 'Fl_FileIcon::load_fti()' - Load an SGI-format FTI file...
//

void
Fl_FileIcon::load_fti(const char *fti)	// I - File to read from
{
  FILE	*fp;			// File pointer
  int	ch;			// Current character
  char	command[255],		// Command string ("vertex", etc.)
	params[255],		// Parameter string ("10.0,20.0", etc.)
	*ptr;			// Pointer into strings
  short	*outline;		// Outline polygon


  // Try to open the file...
  if ((fp = fopen(fti, "r")) == NULL)
    return;

  // Read the entire file, adding data as needed...
  outline = NULL;

  while ((ch = getc(fp)) != EOF)
  {
    // Skip whitespace
    if (isspace(ch))
      continue;

    // Skip comments starting with "#"...
    if (ch == '#')
    {
      while ((ch = getc(fp)) != EOF)
        if (ch == '\n')
	  break;

      if (ch == EOF)
        break;
      else
        continue;
    }

    // OK, this character better be a letter...
    if (!isalpha(ch))
      break;

    // Scan the command name...
    ptr    = command;
    *ptr++ = ch;

    while ((ch = getc(fp)) != EOF)
    {
      if (ch == '(')
        break;
      else if ((ptr - command) < int(sizeof(command) - 1))
        *ptr++ = ch;
    }

    *ptr++ = '\0';

    // Make sure we stopped on a parenthesis...
    if (ch != '(')
      break;

    // Scan the parameters...
    ptr = params;

    while ((ch = getc(fp)) != EOF)
    {
      if (ch == ')')
        break;
      else if ((ptr - params) < int(sizeof(params) - 1))
        *ptr++ = ch;
    }

    *ptr++ = '\0';

    // Make sure we stopped on a parenthesis...
    if (ch != ')')
      break;

    // Make sure the next character is a semicolon...
    if ((ch = getc(fp)) != ';')
      break;

    // Now process the command...
    if (strcmp(command, "color") == 0)
    {
      // Set the color; for negative colors blend the two primaries to
      // produce a composite color.  Also, the following symbolic color
      // names are understood:
      //
      //     name           FLTK color
      //     -------------  ----------
      //     iconcolor      256; mapped to the icon color in Fl_FileIcon::draw()
      //     shadowcolor    FL_DARK3
      //     outlinecolor   FL_BLACK
      if (strcmp(params, "iconcolor") == 0)
        add_color(256);
      else if (strcmp(params, "shadowcolor") == 0)
        add_color(FL_DARK3);
      else if (strcmp(params, "outlinecolor") == 0)
        add_color(FL_BLACK);
      else
      {
        short c = atoi(params);	// Color value


        if (c < 0)
	{
	  // Composite color; compute average...
	  c = -c;
	  add_color(fl_color_average((Fl_Color)(c >> 4),
	                             (Fl_Color)(c & 15), 0.5f));
	}
	else
	  add_color(c);
      }
    }
    else if (strcmp(command, "bgnline") == 0)
      add(LINE);
    else if (strcmp(command, "bgnclosedline") == 0)
      add(CLOSEDLINE);
    else if (strcmp(command, "bgnpolygon") == 0)
      add(POLYGON);
    else if (strcmp(command, "bgnoutlinepolygon") == 0)
    {
      add(OUTLINEPOLYGON);
      outline = add(0);
    }
    else if (strcmp(command, "endoutlinepolygon") == 0 &&
             outline != NULL)
    {
      // Set the outline color; see above for valid values...
      if (strcmp(params, "iconcolor") == 0)
        *outline = 256;
      else if (strcmp(params, "shadowcolor") == 0)
        *outline = FL_DARK3;
      else if (strcmp(params, "outlinecolor") == 0)
        *outline = FL_BLACK;
      else
      {
        short c = atoi(params);	// Color value


        if (c < 0)
	{
	  // Composite color; compute average...
	  c = -c;
	  *outline = fl_color_average((Fl_Color)(c >> 4), (Fl_Color)(c & 15), 0.5);
	}
	else
	  *outline = c;
      }

      outline = NULL;
      add(END);
    }
    else if (strncmp(command, "end", 3) == 0)
      add(END);
    else if (strcmp(command, "vertex") == 0)
    {
      float x, y;		// Coordinates of vertex


      if (sscanf(params, "%f,%f", &x, &y) != 2)
        break;

      add_vertex((short)(x * 100.0 + 0.5), (short)(y * 100.0 + 0.5));
    }
    else
      break;
  }

  // Close the file and return...
  fclose(fp);

#ifdef DEBUG
  printf("Icon File \"%s\":\n", fti);
  for (int i = 0; i < num_data_; i ++)
    printf("    %d,\n", data_[i]);
#endif /* DEBUG */
}


//
// 'Fl_FileIcon::load_xpm()' - Load an XPM icon file...
//

void
Fl_FileIcon::load_xpm(const char *xpm)	// I - File to read from
{
  FILE		*fp;			// File pointer
  int		i, j;			// Looping vars
  int		ch;			// Current character
  int		bg;			// Background color
  char		line[1024],		// Line from file
		val[16],		// Color value
		*ptr=NULL;		// Pointer into line
  int		x, y;			// X & Y in image
  int		startx=0;		// Starting X coord
  int		width, height;		// Width and height of image
  int		ncolors;		// Number of colors
  short		colors[256];		// Colors
  int		red, green, blue;	// Red, green, and blue values


  // Try to open the file...
  if ((fp = fopen(xpm, "r")) == NULL)
    return;

  // Read the file header until we find the first string...
  while (fgets(line, sizeof(line), fp) != NULL)
    if ((ptr = strchr(line, '\"')) != NULL)
      break;

  if (ptr == NULL)
  {
    // Nothing to load...
    fclose(fp);
    return;
  }

  // Get the size of the image...
  sscanf(ptr + 1, "%d%d%d", &width, &height, &ncolors);

  // Now read the colormap...
  memset(colors, 0, sizeof(colors));
  bg = ' ';

  for (i = 0; i < ncolors; i ++)
  {
    while (fgets(line, sizeof(line), fp) != NULL)
      if ((ptr = strchr(line, '\"')) != NULL)
	break;

    if (ptr == NULL)
    {
      // Nothing to load...
      fclose(fp);
      return;
    }

    // Get the color's character
    ptr ++;
    ch = *ptr++;

    // Get the color value...
    if ((ptr = strstr(ptr, "c ")) == NULL)
    {
      // No color; make this black...
      colors[ch] = FL_BLACK;
    }
    else if (ptr[2] == '#')
    {
      // Read the RGB triplet...
      ptr += 3;
      for (j = 0; j < 12; j ++)
        if (!isxdigit(ptr[j]))
	  break;

      switch (j)
      {
        case 0 :
	    bg = ch;
	default :
	    red = green = blue = 0;
	    break;

        case 3 :
	    val[0] = ptr[0];
	    val[1] = '\0';
	    red = 255 * strtol(val, NULL, 16) / 15;

	    val[0] = ptr[1];
	    val[1] = '\0';
	    green = 255 * strtol(val, NULL, 16) / 15;

	    val[0] = ptr[2];
	    val[1] = '\0';
	    blue = 255 * strtol(val, NULL, 16) / 15;
	    break;

        case 6 :
        case 9 :
        case 12 :
	    j /= 3;

	    val[0] = ptr[0];
	    val[1] = ptr[1];
	    val[2] = '\0';
	    red = strtol(val, NULL, 16);

	    val[0] = ptr[j + 0];
	    val[1] = ptr[j + 1];
	    val[2] = '\0';
	    green = strtol(val, NULL, 16);

	    val[0] = ptr[2 * j + 0];
	    val[1] = ptr[2 * j + 1];
	    val[2] = '\0';
	    blue = strtol(val, NULL, 16);
	    break;
      }

      if (red == green && green == blue)
        colors[ch] = FL_GRAY_RAMP + (FL_NUM_GRAY - 1) * red / 255;
      else
        colors[ch] = fl_color_cube((FL_NUM_RED - 1) * red / 255,
	                           (FL_NUM_GREEN - 1) * green / 255,
				   (FL_NUM_BLUE - 1) * blue / 255);
    }
    else
    {
      // Read a color name...
      if (strncmp(ptr + 2, "white", 5) == 0)
        colors[ch] = FL_WHITE;
      else if (strncmp(ptr + 2, "black", 5) == 0)
        colors[ch] = FL_BLACK;
      else if (strncmp(ptr + 2, "none", 4) == 0)
      {
        colors[ch] = FL_BLACK;
	bg = ch;
      }
      else
        colors[ch] = FL_GRAY;
    }
  }

  // Read the image data...
  for (y = height - 1; y >= 0; y --)
  {
    while (fgets(line, sizeof(line), fp) != NULL)
      if ((ptr = strchr(line, '\"')) != NULL)
	break;

    if (ptr == NULL)
    {
      // Nothing to load...
      fclose(fp);
      return;
    }

    ch = bg;
    ptr ++;

    for (x = 0; x < width; x ++, ptr ++)
      if (*ptr != ch)
      {
	if (ch != bg)
	{
          add_color(colors[ch]);
	  add(POLYGON);
	  add_vertex(startx * 9000 / width + 1000, y * 9000 / height + 500);
	  add_vertex(x * 9000 / width + 1000,      y * 9000 / height + 500);
	  add_vertex(x * 9000 / width + 1000,      (y + 1) * 9000 / height + 500);
	  add_vertex(startx * 9000 / width + 1000, (y + 1) * 9000 / height + 500);
	  add(END);
        }

	ch     = *ptr;
	startx = x;
      }

    if (ch != bg)
    {
      add_color(colors[ch]);
      add(POLYGON);
      add_vertex(startx * 9000 / width + 1000, y * 9000 / height + 500);
      add_vertex(x * 9000 / width + 1000,      y * 9000 / height + 500);
      add_vertex(x * 9000 / width + 1000,      (y + 1) * 9000 / height + 500);
      add_vertex(startx * 9000 / width + 1000, (y + 1) * 9000 / height + 500);
      add(END);
    }
  }

  // Close the file and return...
  fclose(fp);

#ifdef DEBUG
  printf("Icon File \"%s\":\n", xpm);
  for (i = 0; i < num_data_; i ++)
    printf("    %d,\n", data_[i]);
#endif /* DEBUG */
}


//
// 'Fl_FileIcon::load_system_icons()' - Load the standard system icons/filetypes.

void
Fl_FileIcon::load_system_icons(void)
{
  Fl_FileIcon	*icon;		// New icons
  static int	init = 0;	// Have the icons been initialized?
  static short	plain[] =	// Plain file icon
		{
		  1, 39, 4, 6, 3883, 22, 6, 2200, 912, 6, 6055, 2878,
		  6, 7782, 2020, 0, 1, 256, 5, 0, 6, 2200, 1987, 6,
		  2200, 7950, 6, 6001, 9893, 6, 6001, 3920, 0, 5, 0, 6,
		  3069, 1553, 6, 3069, 7483, 6, 6870, 9459, 6, 6870,
		  3497, 0, 5, 0, 6, 3959, 1151, 6, 3959, 7048, 6, 7739,
		  8992, 6, 7739, 3084,
		  Fl_FileIcon::END
		};
  static short	dir[] =		// Directory icon
		{
		  1, 256, 5, 256, 6, 2842, 7300, 6, 2683, 6823, 6,
		  4525, 7767, 6, 4366, 8176, 0, 5, 256, 6, 7697, 4185,
		  6, 7282, 3977, 6, 7320, 8660, 6, 7697, 8847, 0, 5,
		  256, 6, 7282, 3977, 6, 2114, 1387, 6, 1727, 1581, 6,
		  1727, 6322, 6, 2683, 6823, 6, 4525, 7767, 6, 7322,
		  9165, 0, 1, 39, 4, 6, 2637, 0, 6, 1500, 569, 6, 7186,
		  3411, 6, 8323, 2843, 0, 1, 0, 3, 6, 7282, 3977, 6,
		  2114, 1387, 6, 2114, 6050, 6, 2944, 6482, 6, 3149,
		  6106, 6, 4707, 6880, 6, 4764, 7391, 6, 7697, 8847, 6,
		  7697, 4185, 0, 2, 6, 2114, 1387, 6, 1727, 1581, 6,
		  1727, 6322, 6, 2683, 6823, 6, 2842, 7300, 6, 4366,
		  8176, 6, 4525, 7767, 6, 7322, 9165, 6, 7320, 8660,
		  Fl_FileIcon::END
		};


  // Add symbols if they haven't been added already...
  if (!init)
  {
#if 0
    if (!access("/usr/share/pixmaps", F_OK))
    {
      // Load GNOME icons from PNG files in /usr/share/pixmaps...
    }
    else if (!access("/usr/share/icons", F_OK))
    {
      // Load KDE icons...
    }
    else
#endif /* 0 */
    if (!access("/usr/dt/appconfig/icons", F_OK))
    {
      // Load CDE icons...
      icon = new Fl_FileIcon("*", Fl_FileIcon::PLAIN);
      icon->load_xpm("/usr/dt/appconfig/icons/C/Dtdata.m.pm");

      icon = new Fl_FileIcon("*", Fl_FileIcon::DIRECTORY);
      icon->load_xpm("/usr/dt/appconfig/icons/C/DtdirB.m.pm");

      icon = new Fl_FileIcon("core", Fl_FileIcon::PLAIN);
      icon->load_xpm("/usr/dt/appconfig/icons/C/Dtcore.m.pm");

      icon = new Fl_FileIcon("*.{bmp|bw|gif|jpg|pbm|pcd|pgm|ppm|png|ras|rgb|tif|xbm|xpm}", Fl_FileIcon::PLAIN);
      icon->load_xpm("/usr/dt/appconfig/icons/C/Dtimage.m.pm");

      icon = new Fl_FileIcon("*.{eps|pdf|ps}", Fl_FileIcon::PLAIN);
      icon->load_xpm("/usr/dt/appconfig/icons/C/Dtps.m.pm");

      icon = new Fl_FileIcon("*.ppd", Fl_FileIcon::PLAIN);
      icon->load_xpm("/usr/dt/appconfig/icons/C/DtPrtpr.m.pm");
    }
    else if (!access("/usr/lib/filetype", F_OK))
    {
      // Load SGI icons...
      icon = new Fl_FileIcon("*", Fl_FileIcon::PLAIN);
      icon->load_fti("/usr/lib/filetype/iconlib/generic.doc.fti");

      icon = new Fl_FileIcon("*", Fl_FileIcon::DIRECTORY);
      icon->load_fti("/usr/lib/filetype/iconlib/generic.folder.closed.fti");

      icon = new Fl_FileIcon("core", Fl_FileIcon::PLAIN);
      icon->load_fti("/usr/lib/filetype/default/iconlib/CoreFile.fti");

      icon = new Fl_FileIcon("*.{bmp|bw|gif|jpg|pbm|pcd|pgm|ppm|png|ras|rgb|tif|xbm|xpm}", Fl_FileIcon::PLAIN);
      icon->load_fti("/usr/lib/filetype/system/iconlib/ImageFile.fti");

      if (!access("/usr/lib/filetype/install/iconlib/acroread.doc.fti", F_OK))
      {
	icon = new Fl_FileIcon("*.{eps|ps}", Fl_FileIcon::PLAIN);
	icon->load_fti("/usr/lib/filetype/system/iconlib/PostScriptFile.closed.fti");

	icon = new Fl_FileIcon("*.pdf", Fl_FileIcon::PLAIN);
	icon->load_fti("/usr/lib/filetype/install/iconlib/acroread.doc.fti");
      }
      else
      {
	icon = new Fl_FileIcon("*.{eps|pdf|ps}", Fl_FileIcon::PLAIN);
	icon->load_fti("/usr/lib/filetype/system/iconlib/PostScriptFile.closed.fti");
      }

      if (!access("/usr/lib/filetype/install/iconlib/html.fti", F_OK))
      {
	icon = new Fl_FileIcon("*.{htm|html|shtml}", Fl_FileIcon::PLAIN);
        icon->load_fti("/usr/lib/filetype/iconlib/generic.doc.fti");
	icon->load_fti("/usr/lib/filetype/install/iconlib/html.fti");
      }

      if (!access("/usr/lib/filetype/install/iconlib/color.ps.idle.fti", F_OK))
      {
	icon = new Fl_FileIcon("*.ppd", Fl_FileIcon::PLAIN);
	icon->load_fti("/usr/lib/filetype/install/iconlib/color.ps.idle.fti");
      }
    }
    else
    {
      // Create the default icons...
      new Fl_FileIcon("*", Fl_FileIcon::PLAIN, sizeof(plain) / sizeof(plain[0]), plain);
      new Fl_FileIcon("*", Fl_FileIcon::DIRECTORY, sizeof(dir) / sizeof(dir[0]), dir);
    }

    // Mark things as initialized...
    init = 1;
  }
}


//
// End of "$Id: Fl_FileIcon.cxx,v 1.2 1999/10/28 01:02:12 vincent Exp $".
//
