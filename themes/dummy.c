/* This file is just here to generate empty .po files under Windows.
   This is necessary because Windows does not allow us to duplicate
   symbols we are importing from the FLTK import libraries.  Themes
   only work under Windows when the application itself is dynamically
   linked to FLTK's libraries (DLLs) so this is OK because all symbols
   will be available anyway.  (It's OK for plugins to be used from
   statically linked apps as long as they don't use FLTK.)  If you
   don't know what I'm talking about then just trust me: FLTk themes
   only work for applications linked against FLTK DLLs and not when
   linked statically.
   
   This is probably also the most reliable way under Unix too.  YMMV.
   
   CET
*/
