/+- This file was imported from C++ using a script
/*
 * "$Id: filename.H 4548 2005-08-29 20:16:36Z matt $"
 *
 * Filename header file for the Fast Light Tool Kit (FLTK).
 *
 * Copyright 1998-2005 by Bill Spitzak and others.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA.
 *
 * Please report all bugs and problems on the following page:
 *
 *     http://www.fltk.org/str.php
 */

version (!FL_FILENAME_H) {
#  define FL_FILENAME_H

public import fl.export;

const int FL_PATH_MAX = 256;  /* all buffers are this length */

const char *fl_filename_name(char *);
const char *fl_filename_ext(char *);
char *fl_filename_setext(char *to, int tolen, char *ext);
int fl_filename_expand(char *to, int tolen, char *from);
int fl_filename_absolute(char *to, int tolen, char *from);
int fl_filename_relative(char *to, int tolen, char *from);
int fl_filename_match(char *name, char *pattern);
int fl_filename_isdir(char *name);

version (__cplusplus) {
/*
 * Under WIN32, we include filename.H from numericsort.c; this should probably change...
 */

char *fl_filename_setext(char *to, char *ext) { return fl_filename_setext(to, FL_PATH_MAX, ext); }
int fl_filename_expand(char *to, char *from) { return fl_filename_expand(to, FL_PATH_MAX, from); }
int fl_filename_absolute(char *to, char *from) { return fl_filename_absolute(to, FL_PATH_MAX, from); }
int fl_filename_relative(char *to, char *from) { return fl_filename_relative(to, FL_PATH_MAX, from); }
} /* __cplusplus */


version (WIN32) && !defined(__CYGWIN__) && !defined(__WATCOMC__) {

struct dirent {char d_name[1];};

} else version (__APPLE__) && defined(__PROJECTBUILDER__) {

/* Apple's ProjectBuilder has the nasty habit of including recursively
 * down the file tree. To avoid re-including <FL/dirent.h> we must 
 * directly include the systems math file. (Plus, I could not find a 
 * predefined macro for ProjectBuilder builds, so we have to define it 
 * in the project)
 */
#    include <sys/types.h>
#    include "/usr/include/dirent.h"

} else version (__WATCOMC__) {
#    include <sys/types.h>
#    include <direct.h>

} else {
/*
 * WARNING: on some systems (very few nowadays?) <dirent.h> may not exist.
 * The correct information is in one of these files:
 *
 *     #include <sys/ndir.h>
 *     #include <sys/dir.h>
 *     #include <ndir.h>
 *
 * plus you must do the following #define:
 *
 *     #define dirent direct
 *
 * It would be best to create a <dirent.h> file that does this...
 */
#    include <sys/types.h>
#    include <dirent.h>
}

version (__cplusplus) {
extern "C" {
} /* __cplusplus */

int fl_alphasort(struct dirent **, struct dirent **);
int fl_casealphasort(struct dirent **, struct dirent **);
int fl_casenumericsort(struct dirent **, struct dirent **);
int fl_numericsort(struct dirent **, struct dirent **);

alias int (Fl_File_Sort_F)(struct dirent **, struct dirent **);

version (__cplusplus) {
}

/*
 * Portable "scandir" function.  Ugly but necessary...
 */

int fl_filename_list(char *d, struct dirent ***l,
                               Fl_File_Sort_F  s = fl_numericsort);
} /* __cplusplus */

/*
 * FLTK 1.0.x compatibility definitions...
 */

version (FLTK_1_0_COMPAT) {
const int filename_absolute = fl_filename_absolute; 
const int filename_expand = fl_filename_expand; 
const int filename_ext = fl_filename_ext; 
const int filename_isdir = fl_filename_isdir; 
const int filename_list = fl_filename_list; 
const int filename_match = fl_filename_match; 
const int filename_name = fl_filename_name; 
const int filename_relative = fl_filename_relative; 
const int filename_setext = fl_filename_setext; 
const int numericsort = fl_numericsort; 
} /* FLTK_1_0_COMPAT */


} /* FL_FILENAME_H */

/*
 * End of "$Id: filename.H 4548 2005-08-29 20:16:36Z matt $".
 */
    End of automatic import -+/
