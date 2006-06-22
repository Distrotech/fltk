// fltk_theme.cxx

#include <config.h>

/*! \fn bool fltk_theme();

  This is the default value of fltk::theme().

  This is declared as a "C" function to allow it to be replaced with
  a function from a loaded plugin. If you are statically linking fltk
  you can also override this by declaring a fltk_theme() function in
  your own code (some Unix systems, but not Linux, will do this even
  if fltk is a shared library).

  <b>Unix/Linux/X11:</b>

  This attempts to read information from the KDE files
  "~/.kde/share/config/kdeglobals" and "/usr/share/config/kdeglobals".
  If these exist it also installs an event handler to listen for KDE
  style-change events and call fltk::reload_theme() on them. Fltk does
  not even bother trying to look at the xrdb databases, nobody seems
  to use that any more.

  <b>Windows:</b>

  On Windows it will read colors and fonts using GetSysColor() and
  SystemParametersInfo(). FLTK will call fltk::reload_theme() when a
  WM_SYSCOLORCHANGE, WM_DISPLAYCHANGE, or WM_SETTINGCHANGE event
  happens, even if you replace fltk_theme(), so your replacement
  should be prepared for this.

*/

#include <fltk/FL_API.h>

extern "C" FL_API bool fltk_theme();

#if USE_X11

/* Maybe _WIN32 should use the Windows version anyway? It would work! */
# include "x11/fltk_theme.cxx"

#elif defined(_WIN32)

# include "win32/fltk_theme.cxx"

#elif USE_QUARTZ

//+++ implement Quartz support for themes
extern "C" bool fltk_theme() {return false; /* true? */}

#else

extern "C" bool fltk_theme() {return false; /* true? */}

#endif
