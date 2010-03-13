//
// "$Id$"
//

// 123 TODO: remove stray comments
// 123 TODO: add namespace statements
// 123 TODO: replace class name, constructors and destructor
// 123 TODO: add friend statement for Twin Class
// 123 TODO: add 'compat(FLTK2)' to constructors
// 123 TODO: add twin class with all constructors
// 123 TODO: change all arguments to the FLTK2 class name
// 123 TODO: change the source code to use the new class names
// 123 TODO: add casting to return values
// 123 TODO: move all FLTK2-only functions to the FLTK3 section and implement them
// 123 TODO: remove the FLTK1 and FLTK2 sections in the headers
// 123 TODO: 

//
// "$Id: Fl_File_Icon.H 6614 2009-01-01 16:11:32Z matt $"
//
// Fl_File_Icon definitions.
//
// Copyright 1999-2009 by Michael Sweet.
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

/* \file
   Fl_File_Icon widget . */

//
// Include necessary header files...
//

#ifndef _Fl_Fl_File_Icon_H_
#  define _Fl_Fl_File_Icon_H_

#  include "run.h"


//
// Special color value for the icon color.
//

#  define FL_ICON_COLOR (Fl_Color)0xffffffff	/**< icon color [background?]*/


//
// Fl_File_Icon class...
//

/** 
  The Fl_File_Icon class manages icon images that can be used 
  as labels in other widgets and as icons in the FileBrowser widget.
*/
class FL_EXPORT Fl_File_Icon			//// Icon data
{
  static Fl_File_Icon *first_;	// Pointer to first icon/filetype
  Fl_File_Icon	*next_;		// Pointer to next icon/filetype
  const char	*pattern_;	// Pattern string
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

  Fl_File_Icon(const char *p, int t, int nd = 0, short *d = 0);
  ~Fl_File_Icon();

  short		*add(short d);

  /**
    Adds a color value to the icon array, returning a pointer to it.
    \param[in] c color value
  */
  short		*add_color(Fl_Color c)
		{ short *d = add((short)COLOR); add((short)(c >> 16)); add((short)c); return (d); }

  /**
    Adds a vertex value to the icon array, returning a pointer to it.
    The integer version accepts coordinates from 0 to 10000.
    The origin (0.0) is in the lower-lefthand corner of the icon.
    \param[in] x, y vertex coordinates
  */
  short		*add_vertex(int x, int y)
		{ short *d = add((short)VERTEX); add((short)x); add((short)y); return (d); }

  /**
    Adds a vertex value to the icon array, returning a pointer to it.
    The floating point version goes from 0.0 to 1.0.
    The origin (0.0) is in the lower-lefthand corner of the icon.
    \param[in] x, y vertex coordinates
  */
  short		*add_vertex(float x, float y)
		{ short *d = add((short)VERTEX); add((short)(x * 10000.0));
		  add((short)(y * 10000.0)); return (d); }

  /** Clears all icon data from the icon.*/
  void		clear() { num_data_ = 0; }

  void		draw(int x, int y, int w, int h, Fl_Color ic, int active = 1);

  void		label(Fl_Widget *w);

  static void	labeltype(const Fl_Label *o, int x, int y, int w, int h, Fl_Align a);
  void		load(const char *f);
  int		load_fti(const char *fti);
  int		load_image(const char *i);

  /** Returns next file icon object. See Fl_File_Icon::first() */
  Fl_File_Icon	*next() { return (next_); }

  /** Returns the filename matching pattern for the icon.*/
  const char	*pattern() { return (pattern_); }

  /**  Returns the number of words of data used by the icon.*/
  int		size() { return (num_data_); }

  /**
    Returns the filetype associated with the icon, which can be one of the
    following:
  
    \li Fl_File_Icon::ANY, any kind of file.
    \li Fl_File_Icon::PLAIN, plain files.
    \li Fl_File_Icon::FIFO, named pipes.
    \li Fl_File_Icon::DEVICE, character and block devices.
    \li Fl_File_Icon::LINK, symbolic links.
    \li Fl_File_Icon::DIRECTORY, directories.
  */
  int		type() { return (type_); }

  /**  Returns the data array for the icon.*/
  short		*value() { return (data_); }

  static Fl_File_Icon *find(const char *filename, int filetype = ANY);

  /** Returns a pointer to the first icon in the list.*/
  static Fl_File_Icon *first() { return (first_); }
  static void	load_system_icons(void);
};

#endif // !_Fl_Fl_File_Icon_H_

//
// End of "$Id: Fl_File_Icon.H 6614 2009-01-01 16:11:32Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::FileIcon
class Fl_File_Icon : public fltk::FileIcon {
public:
  Fl_File_Icon(int x, int t, int w, int h, const char *label=0)
  : fltk::FileIcon(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_File_Icon.H 6614 2009-01-01 16:11:32Z matt $"
//
// Fl_File_Icon definitions.
//
// Copyright 1999-2009 by Michael Sweet.
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

/* \file
   Fl_File_Icon widget . */

//
// Include necessary header files...
//

#ifndef _Fl_Fl_File_Icon_H_
#  define _Fl_Fl_File_Icon_H_

#  include "Fl.H"


//
// Special color value for the icon color.
//

#  define FL_ICON_COLOR (Fl_Color)0xffffffff	/**< icon color [background?]*/


//
// Fl_File_Icon class...
//

/** 
  The Fl_File_Icon class manages icon images that can be used 
  as labels in other widgets and as icons in the FileBrowser widget.
*/
class FL_EXPORT Fl_File_Icon			//// Icon data
{
  static Fl_File_Icon *first_;	// Pointer to first icon/filetype
  Fl_File_Icon	*next_;		// Pointer to next icon/filetype
  const char	*pattern_;	// Pattern string
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

  Fl_File_Icon(const char *p, int t, int nd = 0, short *d = 0);
  ~Fl_File_Icon();

  short		*add(short d);

  /**
    Adds a color value to the icon array, returning a pointer to it.
    \param[in] c color value
  */
  short		*add_color(Fl_Color c)
		{ short *d = add((short)COLOR); add((short)(c >> 16)); add((short)c); return (d); }

  /**
    Adds a vertex value to the icon array, returning a pointer to it.
    The integer version accepts coordinates from 0 to 10000.
    The origin (0.0) is in the lower-lefthand corner of the icon.
    \param[in] x, y vertex coordinates
  */
  short		*add_vertex(int x, int y)
		{ short *d = add((short)VERTEX); add((short)x); add((short)y); return (d); }

  /**
    Adds a vertex value to the icon array, returning a pointer to it.
    The floating point version goes from 0.0 to 1.0.
    The origin (0.0) is in the lower-lefthand corner of the icon.
    \param[in] x, y vertex coordinates
  */
  short		*add_vertex(float x, float y)
		{ short *d = add((short)VERTEX); add((short)(x * 10000.0));
		  add((short)(y * 10000.0)); return (d); }

  /** Clears all icon data from the icon.*/
  void		clear() { num_data_ = 0; }

  void		draw(int x, int y, int w, int h, Fl_Color ic, int active = 1);

  void		label(Fl_Widget *w);

  static void	labeltype(const Fl_Label *o, int x, int y, int w, int h, Fl_Align a);
  void		load(const char *f);
  int		load_fti(const char *fti);
  int		load_image(const char *i);

  /** Returns next file icon object. See Fl_File_Icon::first() */
  Fl_File_Icon	*next() { return (next_); }

  /** Returns the filename matching pattern for the icon.*/
  const char	*pattern() { return (pattern_); }

  /**  Returns the number of words of data used by the icon.*/
  int		size() { return (num_data_); }

  /**
    Returns the filetype associated with the icon, which can be one of the
    following:
  
    \li Fl_File_Icon::ANY, any kind of file.
    \li Fl_File_Icon::PLAIN, plain files.
    \li Fl_File_Icon::FIFO, named pipes.
    \li Fl_File_Icon::DEVICE, character and block devices.
    \li Fl_File_Icon::LINK, symbolic links.
    \li Fl_File_Icon::DIRECTORY, directories.
  */
  int		type() { return (type_); }

  /**  Returns the data array for the icon.*/
  short		*value() { return (data_); }

  static Fl_File_Icon *find(const char *filename, int filetype = ANY);

  /** Returns a pointer to the first icon in the list.*/
  static Fl_File_Icon *first() { return (first_); }
  static void	load_system_icons(void);
};

#endif // !_Fl_Fl_File_Icon_H_

//
// End of "$Id: Fl_File_Icon.H 6614 2009-01-01 16:11:32Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id: FileIcon.h 5576 2007-01-03 00:20:28Z spitzak $"
//
// Fl_FileIcon definitions for the Fast Light Tool Kit (FLTK).
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
// Please report all bugs and problems to "fltk-bugs@fltk.org".
//

#ifndef fltk_FileIcon_h
#define fltk_FileIcon_h

#include "FL_API.h"
#include "Color.h"
#include "Symbol.h"

namespace fltk {

class Widget;

class FL_API FileIcon : public Symbol {
  static FileIcon *first_;	// Pointer to first icon/filetype
  FileIcon	*next_;		// Pointer to next icon/filetype
  const char	*pattern_;	// Pattern string
  int		type_;		// Match only if directory or file?
  int		num_data_;	// Number of data elements
  int		alloc_data_;	// Number of allocated elements
  short		*data_;		// Icon data
  int		w_,h_;
  bool          on_select_;     // true if in browser or menu
public:

  enum				// File types
  {
    ANY,			// Any kind of file
    PLAIN,			// Only plain files
    FIFO,			// Only named pipes
    DEVICE,			// Only character and block devices
    LINK,			// Only symbolic links
    DIRECTORY 			// Only directories
  };

  enum				// Data opcodes
  {
    END,			// End of primitive/icon
    COLOR,			// Followed by color index
    LINE,			// Start of line
    CLOSEDLINE,			// Start of closed line
    POLYGON,			// Start of polygon
    OUTLINEPOLYGON,		// Followed by outline color
    VERTEX			// Followed by scaled X,Y
  };

  FileIcon(const char *p, int t, int nd = 0, short *d = 0);
  FileIcon(const FileIcon& f) ; 
  ~FileIcon();

  short		*add(short d);
  short		*add_color(Color c)
		{ short *d = add((short)COLOR); add((short)(c >> 16)); add((short)c); return (d); }
  short		*add_vertex(int x, int y)
		{ short *d = add(VERTEX); add(x); add(y); return (d); }
  short		*add_vertex(float x, float y)
		{ short *d = add(VERTEX); add((int)(x * 10000.0));
		  add((int)(y * 10000.0)); return (d); }
  void		clear() { num_data_ = 0; }

  const Symbol* image() const {return image_;}

  void		load(const char *f);
  const char	*pattern() { return (pattern_); }
  int		size() { return (num_data_); }
  int		type() { return (type_); }
  short		*data() { return (data_); }

  static FileIcon *find(const char *filename, int filetype = ANY);
  static FileIcon *first() { return (first_); }
  static void	load_system_icons(void);

  void		value(Widget* i, bool on_select=false);

  // virtual image overloads
  void _measure(int& w, int& h) const;
  void _draw(const Rectangle& r) const;
private:
  void		image(const Symbol* direct_raster, bool owned=true) {image_=direct_raster;owned_image_=owned;}
  void		load_fti(const char *fti);
  const Symbol* image_;
  bool owned_image_;
};

}

#endif

//
// End of "$Id: FileIcon.h 5576 2007-01-03 00:20:28Z spitzak $".
//
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
