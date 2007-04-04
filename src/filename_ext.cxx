// "$Id$"

/* Copyright 1998-2006 by Bill Spitzak and others.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * Please report all bugs and problems to "fltk-bugs@fltk.org".
 */

#include <fltk/filename.h>
#include <fltk/string.h>

/*!
  Returns a pointer to the last period in filename_name(f), or a
  pointer to the trailing nul if none. Notice that this points \e at
  the period, not after it!
*/
const char *fltk::filename_ext(const char *buf) {
  const char *q = 0;
  const char *p = buf;
  for (p=buf; *p; p++) {
    if (*p == '/') q = 0;
#if defined(_WIN32) || defined(__EMX__)
    else if (*p == '\\') q = 0;
#endif
    else if (*p == '.') q = p;
  }
  return q ? q : p;
}
 
//! add or replace a new extension to a filename, you must provide a correct string size, ext must include '.'
FL_API void fltk::filename_setext(char * fname, size_t size, const char * new_ext) {
  if (!fname || !new_ext || size <=strlen(new_ext)) return; // no room to do the job
  size_t l = strlen(fname) ;
  char * ext = fname + (l>0 ? l-1 :0);
  if (*ext=='\0' || *ext=='/' || *ext=='\\' || *ext==':') return; // dont do the job if there's no filename
  for (char* p = ext; *p; p--) {
    if (*p=='/' || *p=='\\' || *p==':') break; // no extension found
    else if (*p=='.') {
      ext=p;
      break;
    }
  }
  size_t maxsize = size - (ext-fname);
  strlcpy(ext,new_ext,maxsize); // NUL termination strcat
}

//
// End of "$Id$".
//
