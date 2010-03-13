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
// "$Id: Fl_File_Browser.H 6614 2009-01-01 16:11:32Z matt $"
//
// FileBrowser definitions.
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
   Fl_File_Browser widget . */

//
// Include necessary header files...
//

#ifndef _Fl_File_Browser_H_
#  define _Fl_File_Browser_H_

#  include "Browser.h"
#  include "FileIcon.h"
#  include "filename.h"


//
// Fl_File_Browser class...
//

/** The Fl_File_Browser widget displays a list of filenames, optionally with file-specific icons. */
class FL_EXPORT Fl_File_Browser : public Fl_Browser
{
  int		filetype_;
  const char	*directory_;
  uchar		iconsize_;
  const char	*pattern_;

  int		full_height() const;
  int		item_height(void *) const;
  int		item_width(void *) const;
  void		item_draw(void *, int, int, int, int) const;
  int		incr_height() const { return (item_height(0)); }

public:
  enum { FILES, DIRECTORIES };

  /**
    The constructor creates the Fl_File_Browser widget at the specified position and size.
    The destructor destroys the widget and frees all memory that has been allocated.
  */
  Fl_File_Browser(int, int, int, int, const char * = 0);

  /**    Sets or gets the size of the icons. The default size is 20 pixels.  */
  uchar		iconsize() const { return (iconsize_); };
  /**    Sets or gets the size of the icons. The default size is 20 pixels.  */
  void		iconsize(uchar s) { iconsize_ = s; redraw(); };

  /**
    Sets or gets the filename filter. The pattern matching uses
    the fl_filename_match()
    function in FLTK.
  */
  void	filter(const char *pattern);
  /**
    Sets or gets the filename filter. The pattern matching uses
    the fl_filename_match()
    function in FLTK.
  */
  const char	*filter() const { return (pattern_); };

  /**
    Loads the specified directory into the browser. If icons have been
    loaded then the correct icon is associated with each file in the list.
    
    <P>The sort argument specifies a sort function to be used with
    fl_filename_list().
  */
  int		load(const char *directory, Fl_File_Sort_F *sort = fl_numericsort);

  Fl_Fontsize  textsize() const { return Fl_Browser::textsize(); };
  void		textsize(Fl_Fontsize s) { Fl_Browser::textsize(s); iconsize_ = (uchar)(3 * s / 2); };

  /**
    Sets or gets the file browser type, FILES or
    DIRECTORIES. When set to FILES, both
    files and directories are shown. Otherwise only directories are
    shown.
  */
  int		filetype() const { return (filetype_); };
  /**
    Sets or gets the file browser type, FILES or
    DIRECTORIES. When set to FILES, both
    files and directories are shown. Otherwise only directories are
    shown.
  */
  void		filetype(int t) { filetype_ = t; };
};

#endif // !_Fl_File_Browser_H_

//
// End of "$Id: Fl_File_Browser.H 6614 2009-01-01 16:11:32Z matt $".
//

/* suggested twin class
// This is the Twin Class to fltk::FileBrowser
class Fl_File_Browser : public fltk::FileBrowser {
public:
  Fl_File_Browser(int x, int t, int w, int h, const char *label=0)
  : fltk::FileBrowser(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
//
// "$Id: Fl_File_Browser.H 6614 2009-01-01 16:11:32Z matt $"
//
// FileBrowser definitions.
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
   Fl_File_Browser widget . */

//
// Include necessary header files...
//

#ifndef _Fl_File_Browser_H_
#  define _Fl_File_Browser_H_

#  include "Fl_Browser.H"
#  include "Fl_File_Icon.H"
#  include "filename.H"


//
// Fl_File_Browser class...
//

/** The Fl_File_Browser widget displays a list of filenames, optionally with file-specific icons. */
class FL_EXPORT Fl_File_Browser : public Fl_Browser
{
  int		filetype_;
  const char	*directory_;
  uchar		iconsize_;
  const char	*pattern_;

  int		full_height() const;
  int		item_height(void *) const;
  int		item_width(void *) const;
  void		item_draw(void *, int, int, int, int) const;
  int		incr_height() const { return (item_height(0)); }

public:
  enum { FILES, DIRECTORIES };

  /**
    The constructor creates the Fl_File_Browser widget at the specified position and size.
    The destructor destroys the widget and frees all memory that has been allocated.
  */
  Fl_File_Browser(int, int, int, int, const char * = 0);

  /**    Sets or gets the size of the icons. The default size is 20 pixels.  */
  uchar		iconsize() const { return (iconsize_); };
  /**    Sets or gets the size of the icons. The default size is 20 pixels.  */
  void		iconsize(uchar s) { iconsize_ = s; redraw(); };

  /**
    Sets or gets the filename filter. The pattern matching uses
    the fl_filename_match()
    function in FLTK.
  */
  void	filter(const char *pattern);
  /**
    Sets or gets the filename filter. The pattern matching uses
    the fl_filename_match()
    function in FLTK.
  */
  const char	*filter() const { return (pattern_); };

  /**
    Loads the specified directory into the browser. If icons have been
    loaded then the correct icon is associated with each file in the list.
    
    <P>The sort argument specifies a sort function to be used with
    fl_filename_list().
  */
  int		load(const char *directory, Fl_File_Sort_F *sort = fl_numericsort);

  Fl_Fontsize  textsize() const { return Fl_Browser::textsize(); };
  void		textsize(Fl_Fontsize s) { Fl_Browser::textsize(s); iconsize_ = (uchar)(3 * s / 2); };

  /**
    Sets or gets the file browser type, FILES or
    DIRECTORIES. When set to FILES, both
    files and directories are shown. Otherwise only directories are
    shown.
  */
  int		filetype() const { return (filetype_); };
  /**
    Sets or gets the file browser type, FILES or
    DIRECTORIES. When set to FILES, both
    files and directories are shown. Otherwise only directories are
    shown.
  */
  void		filetype(int t) { filetype_ = t; };
};

#endif // !_Fl_File_Browser_H_

//
// End of "$Id: Fl_File_Browser.H 6614 2009-01-01 16:11:32Z matt $".
//
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
//
// "$Id: FileBrowser.h 4926 2006-04-10 21:03:29Z fabien $"
//
// FileBrowser definitions.
//
// Copyright 1999-2006 by Michael Sweet.
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

#ifndef fltk_FileBrowser_h
#define fltk_FileBrowser_h

#include <fltk/Browser.h>
#include <fltk/FileIcon.h>
#include <fltk/filename.h>

namespace fltk {


//
// FileBrowser class...
//

class FL_API FileBrowser : public Browser
{
  int		filetype_;
  const char	*directory_;
  float		icon_size_;
  const char	*pattern_;

public:
  enum { FILES, DIRECTORIES };

  FileBrowser(int, int, int, int, const char * = 0);

  float		icon_size() const { 
    return (icon_size_ <0?  (2.0f* textsize()) : icon_size_); 
  }
  void 		icon_size(float f) { icon_size_ = f; redraw(); };

  void	filter(const char *pattern);
  const char	*filter() const { return (pattern_); };

  int		load(const char *directory, File_Sort_F *sort = (File_Sort_F*) fltk::numericsort);

  float		textsize() const { return (Browser::textsize()); };
  void		textsize(float s) { Browser::textsize(s); icon_size_ = (uchar)(3 * s / 2); };

  int		filetype() const { return (filetype_); };
  void		filetype(int t) { filetype_ = t; };
  const char *  directory() const {return directory_;}

  // adding or inserting a line into the fileBrowser
  void insert(int n, const char* label, FileIcon* icon);
  void insert(int n, const char* label, void* data){Menu::insert(n, label,data);}
  void add(const char * line, FileIcon* icon);

  // Showing or not showing the hidden files, that's the question:
public:
  // sets this flag if you want to see the hidden files in the browser
  void	    show_hidden(bool show) { show_hidden_= show; }
  bool	    show_hidden() const {return show_hidden_;}
private:
    bool		show_hidden_;
};

}

#endif // !_Fl_File_Browser_H_

//
// End of "$Id: FileBrowser.h 4926 2006-04-10 21:03:29Z fabien $".
//
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
