//
// "$Id"
// types.h : platform dependend types that need to be used in includes
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


#ifndef fltk_types_h
# define fltk_types_h

// 1. minimum platform dependent declarations should appear here
namespace fltk {
#if defined(WIN32) && !defined(__MINGW32__)
  typedef __int8	    Integer8;
  typedef __int16	    Integer16;
  typedef __int32	    Integer32;
  typedef __int64	    Integer64;
  
  typedef unsigned __int8   Unsigned8;
  typedef unsigned __int16  Unsigned16;
  typedef unsigned __int32  Unsigned32;
  typedef unsigned __int64  Unsigned64;
#elif defined(__MINGW32__)
#include <sys/types.h>
typedef unsigned Unsigned32;

#else // unixes or unix-like os
#include <sys/types.h>
typedef int8_t	    Integer8;
typedef int16_t	    Integer16;
typedef int32_t	    Integer32;
typedef int64_t	    Integer64;

typedef unsigned Integer8   Unsigned8;
typedef unsigned Integer16  Unsigned16;
typedef unsigned Integer32  Unsigned32;
typedef unsigned Integer64  Unsigned64;

#endif

// now define secure types doing arithmetics on pointers
#if defined(__LP64__) || defined(WIN64) || defined(__alpha__) || defined(_CRAY)
# define FLTK_ARCH64
  typedef Unsigned64	    PointerValue;
#else
# define FLTK_ARCH32
  typedef Unsigned32	    PointerValue;
#endif

}

#endif
//
// End of "$Id"
//
