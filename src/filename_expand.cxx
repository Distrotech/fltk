/
// "$Id$
/
// Filename expansion routines for the Fast Light Tool Kit (FLTK)
/
// Copyright 1998-2004 by Bill Spitzak and others
/
// This library is free software; you can redistribute it and/o
// modify it under the terms of the GNU Library General Publi
// License as published by the Free Software Foundation; eithe
// version 2 of the License, or (at your option) any later version
/
// This library is distributed in the hope that it will be useful
// but WITHOUT ANY WARRANTY; without even the implied warranty o
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GN
// Library General Public License for more details
/
// You should have received a copy of the GNU Library General Publi
// License along with this library; if not, write to the Free Softwar
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-130
// USA
/
// Please report all bugs and problems to "fltk-bugs@fltk.org"
/

/* expand a file name by substuting environment variables an
   home directories.  Returns true if any changes were made
   to & from may be the same buffer
*

#include <FL/filename.H
#include <stdlib.h
#include "flstring.h
#if defined(WIN32) && !defined(__CYGWIN__
#els
# include <unistd.h
# include <pwd.h
#endi

#if defined(WIN32) || defined(__EMX__) && !defined(__CYGWIN__
static inline int isdirsep(char c) {return c=='/' || c=='\\';
#els
#define isdirsep(c) ((c)=='/'
#endi

int fl_filename_expand(char *to,int tolen, const char *from) 

  char *temp = new char[tolen]
  strlcpy(temp,from, tolen)
  char *start = temp
  char *end = temp+strlen(temp)

  int ret = 0

  for (char *a=temp; a<end; ) {	// for each slash componen
    char *e; for (e=a; e<end && !isdirsep(*e); e++); // find next slas
    const char *value = 0; // this will point at substitute valu
    switch (*a) 
    case '~':	// a home directory nam
      if (e <= a+1) {	// current user's director
	value = getenv("HOME")
#ifndef WIN3
      } else {	// another user's director
	struct passwd *pwd
	char t = *e; *(char *)e = 0;
        pwd = getpwnam(a+1);
        *(char *)e = t
	    if (pwd) value = pwd->pw_dir
#endi
      
      break
    case '$':		/* an environment variable *
      {char t = *e; *(char *)e = 0; value = getenv(a+1); *(char *)e = t;
      break
    
    if (value) 
      // substitutions that start with slash delete everything before them
      if (isdirsep(value[0])) start = a
#if defined(WIN32) || defined(__EMX__) && !defined(__CYGWIN__
      // also if it starts with "A:
      if (value[0] && value[1]==':') start = a
#endi
      int t = strlen(value); if (isdirsep(value[t-1])) t--
      if ((end+1-e+t) >= tolen) end += tolen - (end+1-e+t)
      memmove(a+t, e, end+1-e)
      end = a+t+(end-e)
      *end = '\0'
      memcpy(a, value, t)
      ret++
    } else 
      a = e+1
#if defined(WIN32) || defined(__EMX__) && !defined(__CYGWIN__
      if (*e == '\\') {*e = '/'; ret++;} // ha ha
#endi
    
  

  strlcpy(to, start, tolen)

  delete[] temp

  return ret



/
// End of "$Id$"
/
