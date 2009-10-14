// "$Id: SharedImage.h 5738 2007-03-12 18:07:45Z spitzak $"
//
// Copyright 1998-2006 by Bill Spitzak and others.
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

/*! \class fltk::SharedImage

Subclass of Image that can read a file or block of compressed data.
This provides several useful functions:
* Images are identified by filename. The static get() function will
return an existing instance if it was called before with the same filename.
The release() function will decrement the reference count and delete
the image if nobody wants it any more.
* An inline block of data may be provided that is the contents of the file,
so the file does not have to exist and you can link the image directly
into your program.
* You may set a memory usage limit. If Image::mem_used() goes above
this limit, it will call destroy() on least-recently-used images until
it goes below this limit.
* The get() function can determine the type of the file or block of
data and create the correct subclass.

*/

#ifndef fltk_SharedImage_h
#define fltk_SharedImage_h

//#include "Image.h"

#include "../FL3/SharedImage.h"

#endif

// End of "$Id: SharedImage.h 5738 2007-03-12 18:07:45Z spitzak $"
