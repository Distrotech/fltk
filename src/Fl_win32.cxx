//
// "$Id: Fl_win32.cxx,v 1.76 1999/11/28 09:19:27 bill Exp $"
//
// WIN32-specific code for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-1999 by Bill Spitzak and others.
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

// This file contains win32-specific code for fltk which is always linked
// in.  Search other files for "WIN32" or filenames ending in _win32.C
// for other system-specific code.

#include <config.h>
#include <FL/Fl.H>
#include <FL/win32.H>
#include <FL/Fl_Window.H>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <limits.H>
#include <time.h>
#include <winsock.h>
#include <ctype.h>


#ifndef PATH_MAX
#define PATH_MAX 128
#endif


//
// WM_SYNCPAINT is an "undocumented" message, which is finally defined in
// VC++ 6.0.
//
#ifndef WM_SYNCPAINT
#  define WM_SYNCPAINT 0x0088
#endif /* !WM_SYNCPAINT */

#ifndef WM_MOUSELEAVE
#  define WM_MOUSELEAVE 0x02a3
#endif

#ifndef WM_MOUSEWHEEL
#  define WM_MOUSEWHEEL 0x020a
#endif

////////////////////////////////////////////////////////////////
// interface to poll/select call:

// fd's are only implemented for sockets.  Microsoft Windows does not
// have a unified IO system, so it doesn't support select() on files,
// devices, or pipes...  Also, unlike UNIX the Windows select() call
// doesn't use the nfds parameter, so we don't need to keep track of
// the maximum FD number...

static fd_set fdsets[3];
#define POLLIN 1
#define POLLOUT 4
#define POLLERR 8

static int nfds = 0;
static int fd_array_size = 0;
static struct FD {
  int fd;
  short events;
  void (*cb)(int, void*);
  void* arg;
} *fd = 0;

void Fl::add_fd(int n, int events, void (*cb)(int, void*), void *v) {
  remove_fd(n,events);
  int i = nfds++;
  if (i >= fd_array_size) {
    fd_array_size = 2*fd_array_size+1;
    fd = (FD*)realloc(fd, fd_array_size*sizeof(FD));
  }
  fd[i].fd = n;
  fd[i].events = events;
  fd[i].cb = cb;
  fd[i].arg = v;
  if (events & POLLIN) FD_SET(n, &fdsets[0]);
  if (events & POLLOUT) FD_SET(n, &fdsets[1]);
  if (events & POLLERR) FD_SET(n, &fdsets[2]);
}

void Fl::add_fd(int fd, void (*cb)(int, void*), void* v) {
  Fl::add_fd(fd, POLLIN, cb, v);
}

void Fl::remove_fd(int n, int events) {
  int i,j;
  for (i=j=0; i<nfds; i++) {
    if (fd[i].fd == n) {
      int e = fd[i].events & ~events;
      if (!e) continue; // if no events left, delete this fd
      fd[i].events = e;
    }
    // move it down in the array if necessary:
    if (j<i) {
      fd[j]=fd[i];
    }
    j++;
  }
  nfds = j;
  if (events & POLLIN) FD_CLR(n, &fdsets[0]);
  if (events & POLLOUT) FD_CLR(n, &fdsets[1]);
  if (events & POLLERR) FD_CLR(n, &fdsets[2]);
}

void Fl::remove_fd(int n) {
  remove_fd(n, -1);
}

MSG fl_msg;

int fl_ready() {
  if (PeekMessage(&fl_msg, NULL, 0, 0, PM_NOREMOVE)) return 1;

  timeval t;
  t.tv_sec = 0;
  t.tv_usec = 0;
  fd_set fdt[3];
  fdt[0] = fdsets[0];
  fdt[1] = fdsets[1];
  fdt[2] = fdsets[2];
  return ::select(0,&fdt[0],&fdt[1],&fdt[2],&t);
}

// these pointers are set by the Fl::lock() function:
static void nothing() {}
void (*fl_lock_function)() = nothing;
void (*fl_unlock_function)() = nothing;

static void* message;

void* Fl::thread_message() {
  void* r = message;
  message = 0;
  return r;
}

double fl_wait(int timeout_flag, double time) {
  int have_message = 0;
  int timerid;

  fl_unlock_function();

  if (nfds) {
    // For WIN32 we need to poll for socket input FIRST, since
    // the event queue is not something we can select() on...
    timeval t;
    t.tv_sec = 0;
    t.tv_usec = 0;

    fd_set fdt[3];
    fdt[0] = fdsets[0];
    fdt[1] = fdsets[1];
    fdt[2] = fdsets[2];

    if (::select(0,&fdt[0],&fdt[1],&fdt[2],&t)) {
      // We got something - do the callback!
      for (int i = 0; i < nfds; i ++) {
	int f = fd[i].fd;
	short revents = 0;
	if (FD_ISSET(f,&fdt[0])) revents |= POLLIN;
	if (FD_ISSET(f,&fdt[1])) revents |= POLLOUT;
	if (FD_ISSET(f,&fdt[2])) revents |= POLLERR;
	if (fd[i].events & revents) fd[i].cb(f, fd[i].arg);
      }
    }
  }

  // get the first message by waiting the correct amount of time:
  if (!timeout_flag) {
    // If we are monitoring sockets we need to check them periodically,
    // so set a timer in this case...
    if (nfds) {
      // First see if there is a message waiting...
      have_message = PeekMessage(&fl_msg, NULL, 0, 0, PM_REMOVE);
      if (!have_message) {
	// If not then set a 1ms timer...
	timerid = SetTimer(NULL, 0, 1, NULL);
	have_message = GetMessage(&fl_msg, NULL, 0, 0) >= 0;
	KillTimer(NULL, timerid);
      }
    } else {
      // Wait for a message...
      have_message = GetMessage(&fl_msg, NULL, 0, 0) >= 0;
    }
  } else {
    // Perform the requested timeout...
    have_message = PeekMessage(&fl_msg, NULL, 0, 0, PM_REMOVE);
    if (!have_message && time > 0.0) {
      int t = (int)(time * 1000.0);
      if (t <= 0) t = 1;
      timerid = SetTimer(NULL, 0, t, NULL);
      have_message = GetMessage(&fl_msg, NULL, 0, 0) >= 0;
      KillTimer(NULL, timerid);
    }
  }
  fl_lock_function();

  // execute it, them execute any other messages that become ready during it:
  while (have_message) {
    if (fl_msg.message == WM_USER)  // Used for awaking wait() from another thread
      message = (void*)fl_msg.wParam;
    else
      DispatchMessage(&fl_msg);
    have_message = PeekMessage(&fl_msg, NULL, 0, 0, PM_REMOVE);
  }

  return time;
}

////////////////////////////////////////////////////////////////

int Fl::x()
{
  RECT r;

  SystemParametersInfo(SPI_GETWORKAREA, 0, &r, 0);
  return r.left;
}

int Fl::y()
{
  RECT r;

  SystemParametersInfo(SPI_GETWORKAREA, 0, &r, 0);
  return r.top;
}

int Fl::w()
{
  RECT r;

  SystemParametersInfo(SPI_GETWORKAREA, 0, &r, 0);
  return r.right - r.left;
}

int Fl::h()
{
  RECT r;

  SystemParametersInfo(SPI_GETWORKAREA, 0, &r, 0);
  return r.bottom - r.top;
}

void Fl::get_mouse(int &x, int &y) {
  POINT p;
  GetCursorPos(&p);
  x = p.x;
  y = p.y;
}

// Borland 5 and VC5 are too old to have this new (post Win95) stuff
#if defined(BORLAND5) || defined(VC5)
#define TME_LEAVE 2
typedef struct tagTRACKMOUSEEVENT {
  DWORD cbSize;
  DWORD dwFlags;
  HWND  hwndTrack;
  DWORD dwHoverTime;
} TRACKMOUSEEVENT, *LPTRACKMOUSEEVENT;
extern "C" BOOL WINAPI TrackMouseEvent(LPTRACKMOUSEEVENT);
#endif

static TRACKMOUSEEVENT mouseevent = {
  sizeof(TRACKMOUSEEVENT),
  TME_LEAVE
};

////////////////////////////////////////////////////////////////

static int mouse_event(Fl_Window *window, int what, int button,
			WPARAM wParam, LPARAM lParam)
{
  static int px, py, pmx, pmy;
  POINT pt;
  Fl::e_x = pt.x = (signed short)LOWORD(lParam);
  Fl::e_y = pt.y = (signed short)HIWORD(lParam);
  ClientToScreen(fl_xid(window), &pt);
  Fl::e_x_root = pt.x;
  Fl::e_y_root = pt.y;
  while (window->parent()) {
    Fl::e_x += window->x();
    Fl::e_y += window->y();
    window = window->window();
  }

  ulong state = Fl::e_state & 0xff0000; // keep shift key states
#if 0
  // mouse event reports some shift flags, perhaps save them?
  if (wParam & MK_SHIFT) state |= FL_SHIFT;
  if (wParam & MK_CONTROL) state |= FL_CTRL;
#endif
  if (wParam & MK_LBUTTON) state |= FL_BUTTON1;
  if (wParam & MK_MBUTTON) state |= FL_BUTTON2;
  if (wParam & MK_RBUTTON) state |= FL_BUTTON3;
  Fl::e_state = state;

  switch (what) {
  case 1: // double-click
    if (Fl::e_is_click) {Fl::e_clicks++; goto J1;}
  case 0: // single-click
    Fl::e_clicks = 0;
  J1:
    if (!Fl::grab()) SetCapture(fl_xid(window));
    Fl::e_keysym = FL_Button + button;
    Fl::e_is_click = 1;
    px = pmx = Fl::e_x_root; py = pmy = Fl::e_y_root;
    return Fl::handle(FL_PUSH,window);

  case 2: // release:
    if (!Fl::grab()) ReleaseCapture();
    Fl::e_keysym = FL_Button + button;
    return Fl::handle(FL_RELEASE,window);

  case 3: // move:
  default: // avoid compiler warning
    // MSWindows produces extra events even if mouse does not move, ignore em:
    if (Fl::e_x_root == pmx && Fl::e_y_root == pmy) return 1;
    pmx = Fl::e_x_root; pmy = Fl::e_y_root;
    if (abs(Fl::e_x_root-px)>5 || abs(Fl::e_y_root-py)>5) Fl::e_is_click = 0;

    // look for mouse leave events
    mouseevent.hwndTrack = fl_xid(window);
    TrackMouseEvent(&mouseevent);

    return Fl::handle(FL_MOVE,window);
  }
}

// convert a MSWindows VK_x to an Fltk (X) Keysym:
// See also the inverse converter in Fl_get_key_win32.C
// This table is in numeric order by VK:
static const struct {unsigned short vk, fltk, extended;} vktab[] = {
  {VK_BACK,	FL_BackSpace},
  {VK_TAB,	FL_Tab},
  {VK_CLEAR,	FL_KP+'5',	0xff0b/*XK_Clear*/},
  {VK_RETURN,	FL_Enter,	FL_KP_Enter},
  {VK_SHIFT,	FL_Shift_L,	FL_Shift_R},
  {VK_CONTROL,	FL_Control_L,	FL_Control_R},
  {VK_MENU,	FL_Alt_L,	FL_Alt_R},
  {VK_PAUSE,	FL_Pause},
  {VK_CAPITAL,	FL_Caps_Lock},
  {VK_ESCAPE,	FL_Escape},
  {VK_SPACE,	' '},
  {VK_PRIOR,	FL_KP+'9',	FL_Page_Up},
  {VK_NEXT,	FL_KP+'3',	FL_Page_Down},
  {VK_END,	FL_KP+'1',	FL_End},
  {VK_HOME,	FL_KP+'7',	FL_Home},
  {VK_LEFT,	FL_KP+'4',	FL_Left},
  {VK_UP,	FL_KP+'8',	FL_Up},
  {VK_RIGHT,	FL_KP+'6',	FL_Right},
  {VK_DOWN,	FL_KP+'2',	FL_Down},
  {VK_SNAPSHOT,	FL_Print},	// does not work on NT
  {VK_INSERT,	FL_KP+'0',	FL_Insert},
  {VK_DELETE,	FL_KP+'.',	FL_Delete},
  {VK_LWIN,	FL_Meta_L},
  {VK_RWIN,	FL_Meta_R},
  {VK_APPS,	FL_Menu},
  {VK_MULTIPLY,	FL_KP+'*'},
  {VK_ADD,	FL_KP+'+'},
  {VK_SUBTRACT,	FL_KP+'-'},
  {VK_DECIMAL,	FL_KP+'.'},
  {VK_DIVIDE,	FL_KP+'/'},
  {VK_NUMLOCK,	FL_Num_Lock},
  {VK_SCROLL,	FL_Scroll_Lock},
  {0xba,	';'},
  {0xbb,	'='},
  {0xbc,	','},
  {0xbd,	'-'},
  {0xbe,	'.'},
  {0xbf,	'/'},
  {0xc0,	'`'},
  {0xdb,	'['},
  {0xdc,	'\\'},
  {0xdd,	']'},
  {0xde,	'\''}
};
static int ms2fltk(int vk, int extended) {
  static unsigned short vklut[256];
  static unsigned short extendedlut[256];
  if (!vklut[1]) { // init the table
    unsigned int i;
    for (i = 0; i < 256; i++) vklut[i] = tolower(i);
    for (i=VK_F1; i<=VK_F16; i++) vklut[i] = i+(FL_F-(VK_F1-1));
    for (i=VK_NUMPAD0; i<=VK_NUMPAD9; i++) vklut[i] = i+(FL_KP+'0'-VK_NUMPAD0);
    for (i = 0; i < sizeof(vktab)/sizeof(*vktab); i++) {
      vklut[vktab[i].vk] = vktab[i].fltk;
      extendedlut[vktab[i].vk] = vktab[i].extended;
    }
    for (i = 0; i < 256; i++) if (!extendedlut[i]) extendedlut[i] = vklut[i];
  }
  return extended ? extendedlut[vk] : vklut[vk];
}

#if USE_COLORMAP
extern HPALETTE fl_select_palette(void); // in fl_color_win32.C
#endif

static Fl_Window* resize_from_system;

static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  static char buffer[2];
  static int cnt=0;

  if(uMsg == WM_SYNCPAINT) {
    if(cnt) {
      InvalidateRect(fl_window,0,FALSE);
      cnt = 0;
    } else cnt = 1;
  } else if (uMsg == WM_PAINT) cnt = 0;

  fl_msg.message = uMsg;

  Fl_Window *window = fl_find(hWnd);

  if (window) switch (uMsg) {

  case WM_QUIT: // this should not happen?
    Fl::fatal("WM_QUIT message");

  case WM_CLOSE: // user clicked close box
    Fl::handle(FL_CLOSE, window);
    return 0;

  case WM_PAINT: {

    // This might be a better alternative, where we fully ignore NT's
    // "facilities" for painting. MS expects applications to paint according
    // to a very restrictive paradigm, and this is the way I found of
    // working around it. In a sense, we are using WM_PAINT simply as an
    // "exposure alert", like the X event.

    Fl_X *i = Fl_X::i(window);
    i->wait_for_expose = 0;
    // if region == entire window we should delete i->region, else
    if (window->damage()) {
      if (i->region) {
	InvalidateRgn(hWnd,i->region,FALSE);
	GetUpdateRgn(hWnd,i->region,0);
      }
    } else {
      if (!i->region) i->region = CreateRectRgn(0,0,0,0);
      GetUpdateRgn(hWnd,i->region,0);
    }
    window->clear_damage(window->damage()|FL_DAMAGE_EXPOSE);
    i->flush();
    window->clear_damage();
    // This convinces MSWindows we have painted whatever they wanted
    // us to paint, and stops it from sending WM_PAINT messages.
    ValidateRgn(hWnd,NULL);
    } break;

  case WM_LBUTTONDOWN:  mouse_event(window, 0, 1, wParam, lParam); return 0;
  case WM_LBUTTONDBLCLK:mouse_event(window, 1, 1, wParam, lParam); return 0;
  case WM_LBUTTONUP:    mouse_event(window, 2, 1, wParam, lParam); return 0;
  case WM_MBUTTONDOWN:  mouse_event(window, 0, 2, wParam, lParam); return 0;
  case WM_MBUTTONDBLCLK:mouse_event(window, 1, 2, wParam, lParam); return 0;
  case WM_MBUTTONUP:    mouse_event(window, 2, 2, wParam, lParam); return 0;
  case WM_RBUTTONDOWN:  mouse_event(window, 0, 3, wParam, lParam); return 0;
  case WM_RBUTTONDBLCLK:mouse_event(window, 1, 3, wParam, lParam); return 0;
  case WM_RBUTTONUP:    mouse_event(window, 2, 3, wParam, lParam); return 0;
  case WM_MOUSEMOVE:    mouse_event(window, 3, 0, wParam, lParam); return 0;

  case WM_MOUSELEAVE:
    Fl::handle(FL_LEAVE, window);
    break;

  case WM_SETFOCUS:
    Fl::handle(FL_FOCUS, window);
    break;

  case WM_KILLFOCUS:
    Fl::handle(FL_UNFOCUS, window);
    Fl::flush(); // it never returns to main loop when deactivated...
    break;

  case WM_SHOWWINDOW:
    if (!window->parent())
      Fl::handle(wParam ? FL_SHOW : FL_HIDE, window);
    break;

  case WM_KEYDOWN:
  case WM_SYSKEYDOWN:
    // save the keysym until we figure out the characters:
    Fl::e_keysym = ms2fltk(wParam,lParam&(1<<24));
  case WM_KEYUP:
  case WM_SYSKEYUP:
    TranslateMessage(&fl_msg); // always returns 1!!!
    // TranslateMessage is supposed to return true only if it turns
    // into another message, but it seems to always return 1 on my
    // NT machine.  So I will instead peek to see if there is a
    // character message in the queue, I hope this can only happen
    // if the translation worked:
    if (PeekMessage(&fl_msg, hWnd, WM_CHAR, WM_SYSDEADCHAR, 1)) {
      uMsg = fl_msg.message;
      wParam = fl_msg.wParam;
      lParam = fl_msg.lParam;
    }
    // fall through to the character case:
  case WM_DEADCHAR:
  case WM_SYSDEADCHAR:
  case WM_CHAR:
  case WM_SYSCHAR:
    {ulong state = Fl::e_state & 0xff000000; // keep the mouse button state
     // if GetKeyState is expensive we might want to comment some of these out:
      if (GetKeyState(VK_SHIFT)&~1) state |= FL_SHIFT;
      if (GetKeyState(VK_CAPITAL)) state |= FL_CAPS_LOCK;
      if (GetKeyState(VK_CONTROL)&~1) state |= FL_CTRL;
      // Alt gets reported for the Alt-GR switch on foreign keyboards.
      // so we need to check the event as well to get it right:
      if ((lParam&(1<<29)) //same as GetKeyState(VK_MENU)
	&& uMsg != WM_CHAR) state |= FL_ALT;
      if (GetKeyState(VK_NUMLOCK)) state |= FL_NUM_LOCK;
      if (GetKeyState(VK_LWIN)&~1 || GetKeyState(VK_RWIN)&~1) state |= FL_META;
      if (GetKeyState(VK_SCROLL)) state |= FL_SCROLL_LOCK;
      Fl::e_state = state;}
    if (lParam & (1<<31)) goto DEFAULT; // ignore up events after fixing shift
    if (uMsg == WM_CHAR || uMsg == WM_SYSCHAR) {
      buffer[0] = char(wParam);
      Fl::e_length = 1;
    } else if (Fl::e_keysym >= FL_KP && Fl::e_keysym <= FL_KP_Last) {
      buffer[0] = Fl::e_keysym-FL_KP;
      Fl::e_length = 1;
    } else {
      buffer[0] = 0;
      Fl::e_length = 0;
    }
    Fl::e_text = buffer;
    // for (int i = lParam&0xff; i--;)
    while (window->parent()) window = window->window();
    if (Fl::handle(FL_KEYBOARD,window)) return 0;
    break;

  case WM_MOUSEWHEEL: {
    static int total;
    Fl::e_dy = -(SHORT)(HIWORD(wParam))/10; // turns 120 into 12 pixels...
    if (Fl::handle(FL_VIEWCHANGE, window)) return 0;
    break;

  case WM_GETMINMAXINFO:
    Fl_X::i(window)->set_minmax((LPMINMAXINFO)lParam);
    break;

  case WM_SIZE:
    if (!window->parent()) {
      if (wParam == SIZE_MINIMIZED || wParam == SIZE_MAXHIDE) {
	Fl::handle(FL_HIDE, window);
      } else {
	Fl::handle(FL_SHOW, window);
	resize_from_system = window;
	window->resize(window->x(),window->y(),LOWORD(lParam),HIWORD(lParam));
        window->layout();
      }
    }
    break;

  case WM_MOVE:
    resize_from_system = window;
    window->resize(LOWORD(lParam), HIWORD(lParam), window->w(), window->h());
    break;

  case WM_SETCURSOR:
    if (LOWORD(lParam) == HTCLIENT) {
      while (window->parent()) window = window->window();
      SetCursor(Fl_X::i(window)->cursor);
      return 0;
    }
    break;

#if USE_COLORMAP
  case WM_QUERYNEWPALETTE :
    fl_GetDC(hWnd);
    if (fl_select_palette()) InvalidateRect(hWnd, NULL, FALSE);
    break;

  case WM_PALETTECHANGED:
    fl_GetDC(hWnd);
    if ((HWND)wParam != hWnd && fl_select_palette()) UpdateColors(fl_gc);
    break;

  case WM_CREATE :
    fl_GetDC(hWnd);
    fl_select_palette();
    break;
#endif

  case WM_SYSCOLORCHANGE:
    Fl::loadscheme();
    break;

  default:
  DEFAULT:
    if (Fl::handle(0,0)) return 0;
    break;
  }

  return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

////////////////////////////////////////////////////////////////
// Sets the 4 return values to the thickness of the window border, so
// that window positions can be adjusted to match the X method of
// placing the contents at an absolute position.  The return value
// is also the value to put in the window style.

int Fl_X::borders(const Fl_Window* w, int& dx, int& dy, int& dw, int& dh) {
  if (!w->border()) {
    dx = dy = dw = dh = 0;
    return WS_POPUP;
  } else if (w->maxw != w->minw || w->maxh != w->minh) { // resizable
    dx = GetSystemMetrics(SM_CXSIZEFRAME);
    dw = 2*dx;
    int bt = GetSystemMetrics(SM_CYCAPTION);
    int by = GetSystemMetrics(SM_CYSIZEFRAME);
    dy = bt+by;
    dh = bt+2*by;
    return WS_THICKFRAME | WS_MAXIMIZEBOX | WS_CAPTION;
  } else {
    dx = GetSystemMetrics(SM_CXFIXEDFRAME);
    dw = 2*dx;
    int bt = GetSystemMetrics(SM_CYCAPTION);
    int by = GetSystemMetrics(SM_CYFIXEDFRAME);
    dy = bt+by;
    dh = bt+2*by;
    return WS_DLGFRAME | WS_CAPTION;
  }
}

////////////////////////////////////////////////////////////////

void Fl_Window::layout() {
  UINT flags = SWP_NOSENDCHANGING | SWP_NOZORDER;
  if (ox() != x() || oy() != y()) set_flag(FL_FORCE_POSITION);
  else flags |= SWP_NOMOVE;
  if (ow() == w() && oh() == h()) {
    Fl_Widget*const* a = array();
    Fl_Widget*const* e = a+children();
    while (a < e) {
      Fl_Widget* o = *a++;
      if (o->damage() & FL_DAMAGE_LAYOUT) o->layout();
    }
    Fl_Widget::layout();
    set_old_size();
    if (flags & SWP_NOMOVE) return;
    flags |= SWP_NOSIZE;
  } else {
    Fl_Group::layout();
    if (i) {redraw(); /*i->wait_for_expose = 1;*/}
  }
  if (this == resize_from_system) {
    resize_from_system = 0;
  } else if (i) {
    int dx, dy, dw, dh; Fl_X::borders(this, dx, dy, dw, dh);
    SetWindowPos(i->xid, 0, x()-dx, y()-dy, w()+dw, h()+dh, flags);
  }
}

////////////////////////////////////////////////////////////////
// Innards of Fl_Window::create():

#include <FL/Fl_Window.H>
int fl_show_iconic;		// true if called from iconize()
int fl_disable_transient_for;	// secret method of removing TRANSIENT_FOR
const Fl_Window* fl_modal_for;	// set by show(parent) or exec()
const Fl_Window* fl_mdi_window;	// set by show_inside()
HCURSOR fl_default_cursor;

Fl_X* Fl_X::create(Fl_Window* w) {

  const char* class_name = "FLTK"; // create a "FLTK" WNDCLASS

  WNDCLASSEX wc;
  // Documentation states a device context consumes about 800 bytes
  // of memory... so who cares? If 800 bytes per window is what it
  // takes to speed things up, I'm game.
  //wc.style = CS_HREDRAW | CS_VREDRAW | CS_CLASSDC | CS_DBLCLKS;
  wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;
  wc.lpfnWndProc = (WNDPROC)WndProc;
  wc.cbClsExtra = wc.cbWndExtra = 0;
  wc.hInstance = fl_display;
  if (!w->icon())
    w->icon((void *)LoadIcon(NULL, IDI_APPLICATION));
  wc.hIcon = wc.hIconSm = (HICON)w->icon();
  if (!fl_default_cursor) fl_default_cursor = LoadCursor(NULL, IDC_ARROW);
  wc.hCursor = fl_default_cursor;
  //uchar r,g,b; Fl::get_color(FL_GRAY,r,g,b);
  //wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(r,g,b));
  wc.hbrBackground = NULL;
  wc.lpszMenuName = NULL;
  wc.lpszClassName = class_name;
  wc.cbSize = sizeof(WNDCLASSEX);
  RegisterClassEx(&wc);

  HWND parent;
  DWORD style;
  DWORD styleEx;

  int xp = w->x();
  int yp = w->y();

  int dx, dy, dw, dh;
  if (w->parent()) {
    style = WS_CHILD;
    styleEx = WS_EX_WINDOWEDGE | WS_EX_CONTROLPARENT;
    parent = fl_xid(w->window());
    dx=dy=dw=dh=0;
  } else {
    style = WS_CLIPCHILDREN | WS_CLIPSIBLINGS | borders(w, dx, dy, dw, dh);
    styleEx = WS_EX_LEFT | WS_EX_WINDOWEDGE | WS_EX_CONTROLPARENT;
    // we don't want an entry in the task list for menuwindows or tooltips!
    if (style&WS_POPUP) styleEx |= WS_EX_TOOLWINDOW;
    if (!(w->flags() & Fl_Window::FL_FORCE_POSITION)) {
      xp = yp = CW_USEDEFAULT;
    } else {
      xp = w->x()-dx;
      yp = w->y()-dy;
    }
    if (fl_modal_for && !fl_disable_transient_for) {
      parent = fl_modal_for->i->xid;
    } else {
      parent = fl_mdi_window ? fl_mdi_window->i->xid : 0;
      if (w->border()) style |= WS_SYSMENU | WS_MINIMIZEBOX;
    }
  }

  Fl_X* x = new Fl_X;
  x->other_xid = 0;
  x->w = w; w->i = x;
  x->region = 0;
  x->private_dc = 0;
  x->cursor = fl_default_cursor;
  x->xid = CreateWindowEx(
    styleEx,
    class_name, w->label(), style,
    xp, yp, w->w()+dw, w->h()+dh,
    parent,
    NULL, // menu
    fl_display,
    NULL // creation parameters
    );
//  x->mapped = 1;
  x->wait_for_expose = 1;
  x->next = Fl_X::first;
  Fl_X::first = x;

  w->redraw(); // force draw to happen
  // If we've captured the mouse, we dont want do activate any
  // other windows from the code, or we loose the capture.
  // Also, we don't want to activate the window for tooltips.
  ShowWindow(x->xid, fl_show_iconic ? SW_SHOWMINNOACTIVE :
	     (Fl::grab() || style&WS_POPUP) ? SW_SHOWNOACTIVATE :
	     SW_SHOWNORMAL);
  fl_show_iconic = 0;
  return x;
}

////////////////////////////////////////////////////////////////

HINSTANCE fl_display = GetModuleHandle(NULL);

void Fl_Window::size_range_() {
  size_range_set = 1;
}

void Fl_X::set_minmax(LPMINMAXINFO minmax)
{
  int dx, dy, dw, dh; borders(w, dx, dy, dw, dh);

  minmax->ptMinTrackSize.x = w->minw + dw;
  minmax->ptMinTrackSize.y = w->minh + dh;
  if (w->maxw) {
    minmax->ptMaxTrackSize.x = w->maxw + dw;
    minmax->ptMaxSize.x = w->maxw + dw;
  }
  if (w->maxh) {
    minmax->ptMaxTrackSize.y = w->maxh + dw;
    minmax->ptMaxSize.y = w->maxh + dw;
  }
}

////////////////////////////////////////////////////////////////

#include <FL/filename.H> // need so FL_EXPORT filename_name works

// returns pointer to the filename, or null if name ends with '/'
const char *filename_name(const char *name) {
  const char *p,*q;
  q = name;
  if (q[0] && q[1]==':') q += 2; // skip leading drive letter
  for (p = q; *p; p++) if (*p == '/' || *p == '\\') q = p+1;
  return q;
}

void Fl_Window::label(const char *name,const char *iname) {
  Fl_Widget::label(name);
  iconlabel_ = iname;
  if (i && !parent()) {
    if (!name) name = "";
    SetWindowText(i->xid, name);
    // if (!iname) iname = filename_name(name);
    // should do something with iname here...
  }
}

////////////////////////////////////////////////////////////////
// Implement the virtual functions for the base Fl_Window class:

// If the box is a filled rectangle, we can make the redisplay *look*
// faster by using X's background pixel erasing.  We can make it
// actually *be* faster by drawing the frame only, this is done by
// setting fl_boxcheat, which is seen by code in fl_drawbox.C:
// For WIN32 it looks like all windows share a background color, so
// I use FL_GRAY for this and only do this cheat for windows that are
// that color.
// Actually it is totally disabled.
// Fl_Widget *fl_boxcheat;
//static inline int can_boxcheat(uchar b) {return (b==1 || (b&2) && b<=15);}

void Fl_Window::create() {
  Fl_X::create(this);
}

Fl_Window *Fl_Window::current_;
// the current context
HDC fl_gc = 0;
// the current window handle, initially set to -1 so we can correctly
// allocate fl_GetDC(0)
HWND fl_window = (HWND)-1;

// Here we ensure only one GetDC is ever in place.
HDC fl_GetDC(HWND w) {
  if (fl_gc) {
    if (w == fl_window) return fl_gc;
    ReleaseDC(fl_window, fl_gc);
  }
  fl_gc = GetDC(w);
  fl_window = w;
  // calling GetDC seems to always reset these: (?)
  SetTextAlign(fl_gc, TA_BASELINE|TA_LEFT);
  SetBkMode(fl_gc, TRANSPARENT);
  return fl_gc;
}

// make X drawing go into this window (called by subclass flush() impl.)
void Fl_Window::make_current() {
  fl_GetDC(fl_xid(this));

#if USE_COLORMAP
  // Windows maintains a hardware and software color palette; the
  // SelectPalette() call updates the current soft->hard mapping
  // for all drawing calls, so we must select it here before any
  // code does any drawing...

  fl_select_palette();
#endif // USE_COLORMAP

  current_ = this;
  fl_clip_region(0);
}

//
// End of "$Id: Fl_win32.cxx,v 1.76 1999/11/28 09:19:27 bill Exp $".
//
