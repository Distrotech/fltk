//
// "$Id$"
//
// MacOS-Cocoa specific code for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2011 by Bill Spitzak and others.
//
// This library is free software. Distribution and use rights are outlined in
// the file "COPYING" which should have been included with this file.  If this
// file is missing or damaged, see the license at:
//
//     http://www.fltk.org/COPYING.php
//
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//

//// From the inner edge of a MetroWerks CodeWarrior CD:
// (without permission)
//
// "Three Compiles for 68Ks under the sky,
// Seven Compiles for PPCs in their fragments of code,
// Nine Compiles for Mortal Carbon doomed to die,
// One Compile for Mach-O Cocoa on its Mach-O throne,
// in the Land of MacOS X where the Drop-Shadows lie.
// 
// One Compile to link them all, One Compile to merge them,
// One Compile to copy them all and in the bundle bind them,
// in the Land of MacOS X where the Drop-Shadows lie."

#ifdef __APPLE__

#define CONSOLIDATE_MOTION 0
extern "C" {
#include <pthread.h>
}


#include <fltk3/run.h>
#include <fltk3/filename.h>
#include <fltk3/x.h>
#include <fltk3/Window.h>
#include <fltk3/Tooltip.h>
#include <fltk3/SysMenuBar.h>
#include <fltk3/Printer.h>
#include <fltk3/Input_.h>
#include <fltk3/TextDisplay.h>
#include <stdio.h>
#include <stdlib.h>
#include "flstring.h"
#include <unistd.h>
#include <stdarg.h>

#import <Cocoa/Cocoa.h>

#ifndef NSINTEGER_DEFINED // appears with 10.5 in NSObjCRuntime.h
#if defined(__LP64__) && __LP64__
typedef long NSInteger;
typedef unsigned long NSUInteger;
#else
typedef long NSInteger;
typedef unsigned int NSUInteger;
#endif
#endif


// #define DEBUG_SELECT		// UNCOMMENT FOR SELECT()/THREAD DEBUGGING
#ifdef DEBUG_SELECT
#include <stdio.h>		// testing
#define DEBUGMSG(msg)		if ( msg ) fprintf(stderr, msg);
#define DEBUGPERRORMSG(msg)	if ( msg ) perror(msg)
#define DEBUGTEXT(txt)		txt
#else
#define DEBUGMSG(msg)
#define DEBUGPERRORMSG(msg)
#define DEBUGTEXT(txt)		NULL
#endif /*DEBUG_SELECT*/

// external functions
extern void fl_fix_focus();
extern fltk3::Offscreen fl_create_offscreen_with_alpha(int w, int h);

// forward definition of functions in this file
// converting cr lf converter function
static void convert_crlf(char * string, size_t len);
static void createAppleMenu(void);
static fltk3::Region MacRegionMinusRect(fltk3::Region r, int x,int y,int w,int h);
static void cocoaMouseHandler(NSEvent *theEvent);

static fltk3::QuartzGraphicsDriver fl_quartz_driver;
static fltk3::DisplayDevice fl_quartz_display(&fl_quartz_driver);
FLTK3_EXPORT fltk3::GraphicsDriver *fltk3::graphics_driver = (fltk3::GraphicsDriver*)&fl_quartz_driver; // the current target device of graphics operations
fltk3::SurfaceDevice* fltk3::SurfaceDevice::_surface = (fltk3::SurfaceDevice*)&fl_quartz_display; // the current target surface of graphics operations
fltk3::DisplayDevice *fltk3::DisplayDevice::_display = &fl_quartz_display; // the platform display

// public variables
CGContextRef fl_gc = 0;
void *fl_default_cursor;		// this is really a NSCursor*
void *fl_capture = 0;			// (NSWindow*) we need this to compensate for a missing(?) mouse capture
bool fl_show_iconic;                    // true if called from iconize() - shows the next created window in collapsed state
//int fl_disable_transient_for;           // secret method of removing TRANSIENT_FOR
Window fl_window;
fltk3::Window *fltk3::Window::current_;
int fl_mac_os_version = 0;		// the version number of the running Mac OS X (e.g., 100604 for 10.6.4)

// forward declarations of variables in this file
static int got_events = 0;
static fltk3::Window* resize_from_system;
static int main_screen_height; // height of menubar-containing screen used to convert between Cocoa and FLTK global screen coordinates

#if CONSOLIDATE_MOTION
static fltk3::Window* send_motion;
extern fltk3::Window* fl_xmousewin;
#endif

enum { FLTKTimerEvent = 1, FLTKDataReadyEvent };


/* fltk-utf8 placekeepers */
void fltk3::reset_spot()
{
}

void fltk3::set_spot(int font, int size, int X, int Y, int W, int H, fltk3::Window *win)
{
}

void fltk3::set_status(int x, int y, int w, int h)
{
}

/*
 * Mac keyboard lookup table
 * See also the inverse converter vktab in Fl_get_key_mac.cxx
 */
static unsigned short macKeyLookUp[128] =
{
  'a', 's', 'd', 'f', 'h', 'g', 'z', 'x',
  'c', 'v', '^', 'b', 'q', 'w', 'e', 'r',
  
  'y', 't', '1', '2', '3', '4', '6', '5',
  '=', '9', '7', '-', '8', '0', ']', 'o',
  
  'u', '[', 'i', 'p', fltk3::EnterKey, 'l', 'j', '\'',
  'k', ';', '\\', ',', '/', 'n', 'm', '.',
  
  fltk3::TabKey, ' ', '`', fltk3::BackSpaceKey, 
  fltk3::KPEnterKey, fltk3::EscapeKey, fltk3::MetaRKey, fltk3::MetaLKey,
  fltk3::ShiftLKey, fltk3::CapsLockKey, fltk3::AltLKey, fltk3::ControlLKey, 
  fltk3::ShiftRKey, fltk3::AltRKey, fltk3::ControlRKey, 0/*fltk3::FKey*/,
  
  0, fltk3::KPKey+'.', fltk3::RightKey, fltk3::KPKey+'*', 0, fltk3::KPKey+'+', fltk3::LeftKey, fltk3::NumLockKey,
  fltk3::DownKey, 0, 0, fltk3::KPKey+'/', fltk3::KPEnterKey, fltk3::UpKey, fltk3::KPKey+'-', 0,
  
  0, fltk3::KPKey+'=', fltk3::KPKey+'0', fltk3::KPKey+'1', fltk3::KPKey+'2', fltk3::KPKey+'3', fltk3::KPKey+'4', fltk3::KPKey+'5',
  fltk3::KPKey+'6', fltk3::KPKey+'7', 0, fltk3::KPKey+'8', fltk3::KPKey+'9', 0, 0, 0,
  
  fltk3::FKey+5, fltk3::FKey+6, fltk3::FKey+7, fltk3::FKey+3, fltk3::FKey+8, fltk3::FKey+9, 0, fltk3::FKey+11,
  0, fltk3::FKey+13, fltk3::FKey+16, fltk3::FKey+14, 0, fltk3::FKey+10, fltk3::MenuKey, fltk3::FKey+12,
  
  0, fltk3::FKey+15, fltk3::HelpKey, fltk3::HomeKey, fltk3::PageUpKey, fltk3::DeleteKey, fltk3::FKey+4, fltk3::EndKey,
  fltk3::FKey+2, fltk3::PageDownKey, fltk3::FKey+1, fltk3::LeftKey, fltk3::RightKey, fltk3::DownKey, fltk3::UpKey, 0/*FL_Power*/,
};

/*
 * convert the current mouse chord into the FLTK modifier state
 */
static unsigned int mods_to_e_state( NSUInteger mods )
{
  long state = 0;
  if ( mods & NSCommandKeyMask ) state |= fltk3::META;
  if ( mods & NSAlternateKeyMask ) state |= fltk3::ALT;
  if ( mods & NSControlKeyMask ) state |= fltk3::CTRL;
  if ( mods & NSShiftKeyMask ) state |= fltk3::SHIFT;
  if ( mods & NSAlphaShiftKeyMask ) state |= fltk3::CAPS_LOCK;
  unsigned int ret = ( fltk3::e_state & 0xff000000 ) | state;
  fltk3::e_state = ret;
  //printf( "State 0x%08x (%04x)\n", fltk3::e_state, mods );
  return ret;
}

// these pointers are set by the fltk3::lock() function:
static void nothing() {}
void (*fl_lock_function)() = nothing;
void (*fl_unlock_function)() = nothing;

//
// Select interface -- how it's implemented:
//     When the user app configures one or more file descriptors to monitor
//     with fltk3::add_fd(), we start a separate thread to select() the  data,
//     sending a custom OSX 'FLTK data ready event' to the parent  thread's
//     RunApplicationLoop(), so that it triggers the data  ready  callbacks
//     in the parent thread.                               -erco 04/04/04
//     
#define POLLIN  1
#define POLLOUT 4
#define POLLERR 8

// Class to handle select() 'data ready'
class DataReady
{
  struct FD
  {
    int fd;
    short events;
    void (*cb)(int, void*);
    void* arg;
  };
  int nfds, fd_array_size;
  FD *fds;
  pthread_t tid;		// select()'s thread id
  
  // Data that needs to be locked (all start with '_')
  pthread_mutex_t _datalock;	// data lock
  fd_set _fdsets[3];		// r/w/x sets user wants to monitor
  int _maxfd;			// max fd count to monitor
  int _cancelpipe[2];		// pipe used to help cancel thread
  
public:
  DataReady()
  {
    nfds = 0;
    fd_array_size = 0;
    fds = 0;
    tid = 0;
    
    pthread_mutex_init(&_datalock, NULL);
    FD_ZERO(&_fdsets[0]); FD_ZERO(&_fdsets[1]); FD_ZERO(&_fdsets[2]);
    _cancelpipe[0] = _cancelpipe[1] = 0;
    _maxfd = -1;
  }
  
  ~DataReady()
  {
    CancelThread(DEBUGTEXT("DESTRUCTOR\n"));
    if (fds) { free(fds); fds = 0; }
    nfds = 0;
  }
  
  // Locks
  //    The convention for locks: volatile vars start with '_',
  //    and must be locked before use. Locked code is prefixed 
  //    with /*LOCK*/ to make painfully obvious esp. in debuggers. -erco
  //
  void DataLock() { pthread_mutex_lock(&_datalock); }
  void DataUnlock() { pthread_mutex_unlock(&_datalock); }
  
  // Accessors
  int IsThreadRunning() { return(tid ? 1 : 0); }
  int GetNfds() { return(nfds); }
  int GetCancelPipe(int ix) { return(_cancelpipe[ix]); }
  fd_set GetFdset(int ix) { return(_fdsets[ix]); }
  
  // Methods
  void AddFD(int n, int events, void (*cb)(int, void*), void *v);
  void RemoveFD(int n, int events);
  int CheckData(fd_set& r, fd_set& w, fd_set& x);
  void HandleData(fd_set& r, fd_set& w, fd_set& x);
  static void* DataReadyThread(void *self);
  void StartThread(void);
  void CancelThread(const char *reason);
};

static DataReady dataready;

void DataReady::AddFD(int n, int events, void (*cb)(int, void*), void *v)
{
  RemoveFD(n, events);
  int i = nfds++;
  if (i >= fd_array_size) 
  {
    fl_open_display(); // necessary for NSApp to be defined and the event loop to work
    FD *temp;
    fd_array_size = 2*fd_array_size+1;
    if (!fds) { temp = (FD*)malloc(fd_array_size*sizeof(FD)); }
    else { temp = (FD*)realloc(fds, fd_array_size*sizeof(FD)); }
    if (!temp) return;
    fds = temp;
  }
  fds[i].cb  = cb;
  fds[i].arg = v;
  fds[i].fd  = n;
  fds[i].events = events;
  DataLock();
  /*LOCK*/  if (events & POLLIN)  FD_SET(n, &_fdsets[0]);
  /*LOCK*/  if (events & POLLOUT) FD_SET(n, &_fdsets[1]);
  /*LOCK*/  if (events & POLLERR) FD_SET(n, &_fdsets[2]);
  /*LOCK*/  if (n > _maxfd) _maxfd = n;
  DataUnlock();
}

// Remove an FD from the array
void DataReady::RemoveFD(int n, int events)
{
  int i,j;
  _maxfd = -1; // recalculate maxfd on the fly
  for (i=j=0; i<nfds; i++) {
    if (fds[i].fd == n) {
      int e = fds[i].events & ~events;
      if (!e) continue; // if no events left, delete this fd
      fds[i].events = e;
    }
    if (fds[i].fd > _maxfd) _maxfd = fds[i].fd;
    // move it down in the array if necessary:
    if (j<i) {
      fds[j] = fds[i];
    }
    j++;
  }
  nfds = j;
  DataLock();
  /*LOCK*/  if (events & POLLIN)  FD_CLR(n, &_fdsets[0]);
  /*LOCK*/  if (events & POLLOUT) FD_CLR(n, &_fdsets[1]);
  /*LOCK*/  if (events & POLLERR) FD_CLR(n, &_fdsets[2]);
  DataUnlock();
}

// CHECK IF USER DATA READY, RETURNS r/w/x INDICATING WHICH IF ANY
int DataReady::CheckData(fd_set& r, fd_set& w, fd_set& x)
{
  int ret;
  DataLock();
  /*LOCK*/  timeval t = { 0, 1 };		// quick check
  /*LOCK*/  r = _fdsets[0], w = _fdsets[1], x = _fdsets[2];
  /*LOCK*/  ret = ::select(_maxfd+1, &r, &w, &x, &t);
  DataUnlock();
  if ( ret == -1 ) {
    DEBUGPERRORMSG("CheckData(): select()");
  }
  return(ret);
}

// HANDLE DATA READY CALLBACKS
void DataReady::HandleData(fd_set& r, fd_set& w, fd_set& x)
{
  for (int i=0; i<nfds; i++) {
    int f = fds[i].fd;
    short revents = 0;
    if (FD_ISSET(f, &r)) revents |= POLLIN;
    if (FD_ISSET(f, &w)) revents |= POLLOUT;
    if (FD_ISSET(f, &x)) revents |= POLLERR;
    if (fds[i].events & revents) {
      DEBUGMSG("DOING CALLBACK: ");
      fds[i].cb(f, fds[i].arg);
      DEBUGMSG("DONE\n");
    }
  }
}

// DATA READY THREAD
//    This thread watches for changes in user's file descriptors.
//    Sends a 'data ready event' to the main thread if any change.
//
void* DataReady::DataReadyThread(void *o)
{
  DataReady *self = (DataReady*)o;
  NSAutoreleasePool *localPool;
  localPool = [[NSAutoreleasePool alloc] init]; 
  while ( 1 ) {					// loop until thread cancel or error
    // Thread safe local copies of data before each select()
    self->DataLock();
    /*LOCK*/  int maxfd = self->_maxfd;
    /*LOCK*/  fd_set r = self->GetFdset(0);
    /*LOCK*/  fd_set w = self->GetFdset(1);
    /*LOCK*/  fd_set x = self->GetFdset(2);
    /*LOCK*/  int cancelpipe = self->GetCancelPipe(0);
    /*LOCK*/  if ( cancelpipe > maxfd ) maxfd = cancelpipe;
    /*LOCK*/  FD_SET(cancelpipe, &r);		// add cancelpipe to fd's to watch
    /*LOCK*/  FD_SET(cancelpipe, &x);
    self->DataUnlock();
    // timeval t = { 1000, 0 };	// 1000 seconds;
    timeval t = { 2, 0 };	// HACK: 2 secs prevents 'hanging' problem
    int ret = ::select(maxfd+1, &r, &w, &x, &t);
    pthread_testcancel();	// OSX 10.0.4 and older: needed for parent to cancel
    switch ( ret ) {
      case 0:	// NO DATA
        continue;
      case -1:	// ERROR
      {
        DEBUGPERRORMSG("CHILD THREAD: select() failed");
        return(NULL);		// error? exit thread
      }
      default:	// DATA READY
      {
        if (FD_ISSET(cancelpipe, &r) || FD_ISSET(cancelpipe, &x)) 	// cancel?
	  { return(NULL); }						// just exit
        DEBUGMSG("CHILD THREAD: DATA IS READY\n");
        NSPoint pt={0,0};
        NSEvent *event = [NSEvent otherEventWithType:NSApplicationDefined location:pt 
				       modifierFlags:0
                                           timestamp:0
                                        windowNumber:0 context:NULL 
					     subtype:FLTKDataReadyEvent data1:0 data2:0];
        [NSApp postEvent:event atStart:NO];
        return(NULL);		// done with thread
      }
    }
  }
}

// START 'DATA READY' THREAD RUNNING, CREATE INTER-THREAD PIPE
void DataReady::StartThread(void)
{
  CancelThread(DEBUGTEXT("STARTING NEW THREAD\n"));
  DataLock();
  /*LOCK*/  pipe(_cancelpipe);	// pipe for sending cancel msg to thread
  DataUnlock();
  DEBUGMSG("*** START THREAD\n");
  pthread_create(&tid, NULL, DataReadyThread, (void*)this);
}

// CANCEL 'DATA READY' THREAD, CLOSE PIPE
void DataReady::CancelThread(const char *reason)
{
  if ( tid ) {
    DEBUGMSG("*** CANCEL THREAD: ");
    DEBUGMSG(reason);
    if ( pthread_cancel(tid) == 0 ) {		// cancel first
      DataLock();
      /*LOCK*/  write(_cancelpipe[1], "x", 1);	// wake thread from select
      DataUnlock();
      pthread_join(tid, NULL);			// wait for thread to finish
    }
    tid = 0;
    DEBUGMSG("(JOINED) OK\n");
  }
  // Close pipe if open
  DataLock();
  /*LOCK*/  if ( _cancelpipe[0] ) { close(_cancelpipe[0]); _cancelpipe[0] = 0; }
  /*LOCK*/  if ( _cancelpipe[1] ) { close(_cancelpipe[1]); _cancelpipe[1] = 0; }
  DataUnlock();
}

void fltk3::add_fd( int n, int events, void (*cb)(int, void*), void *v )
{
  dataready.AddFD(n, events, cb, v);
}

void fltk3::add_fd(int fd, void (*cb)(int, void*), void* v)
{
  dataready.AddFD(fd, POLLIN, cb, v);
}

void fltk3::remove_fd(int n, int events)
{
  dataready.RemoveFD(n, events);
}

void fltk3::remove_fd(int n)
{
  dataready.RemoveFD(n, -1);
}

/*
 * Check if there is actually a message pending!
 */
int fl_ready()
{
  NSEvent *retval = [NSApp nextEventMatchingMask:NSAnyEventMask untilDate:[NSDate dateWithTimeIntervalSinceNow:0]
				    inMode:NSDefaultRunLoopMode dequeue:NO];
  return retval != nil;
}


static void processFLTKEvent(void) {
  fl_lock_function();
  dataready.CancelThread(DEBUGTEXT("DATA READY EVENT\n"));
  
  // CHILD THREAD TELLS US DATA READY
  //     Check to see what's ready, and invoke user's cb's
  //
  fd_set r,w,x;
  switch(dataready.CheckData(r,w,x)) {
    case 0:	// NO DATA
      break;
    case -1:	// ERROR
      break;
    default:	// DATA READY
      dataready.HandleData(r,w,x);
      break;
  }
  fl_unlock_function();
  return;
}


/*
 * break the current event loop
 */
static void breakMacEventLoop()
{
  fl_lock_function();
  
  NSPoint pt={0,0};
  NSEvent *event = [NSEvent otherEventWithType:NSApplicationDefined location:pt 
				 modifierFlags:0
                                     timestamp:0
                                  windowNumber:0 context:NULL 
				       subtype:FLTKTimerEvent data1:0 data2:0];
  [NSApp postEvent:event atStart:NO];
  fl_unlock_function();
}

//
// MacOS X timers
//

struct MacTimeout {
  fltk3::TimeoutHandler callback;
  void* data;
  CFRunLoopTimerRef timer;
  char pending; 
};
static MacTimeout* mac_timers;
static int mac_timer_alloc;
static int mac_timer_used;

static void realloc_timers()
{
  if (mac_timer_alloc == 0) {
    mac_timer_alloc = 8;
    fl_open_display(); // needed because the timer creates an event
  }
  mac_timer_alloc *= 2;
  MacTimeout* new_timers = new MacTimeout[mac_timer_alloc];
  memset(new_timers, 0, sizeof(MacTimeout)*mac_timer_alloc);
  memcpy(new_timers, mac_timers, sizeof(MacTimeout) * mac_timer_used);
  MacTimeout* delete_me = mac_timers;
  mac_timers = new_timers;
  delete [] delete_me;
}

static void delete_timer(MacTimeout& t)
{
  if (t.timer) {
    CFRunLoopRemoveTimer(CFRunLoopGetCurrent(),
		      t.timer,
		      kCFRunLoopDefaultMode);
    CFRelease(t.timer);
    memset(&t, 0, sizeof(MacTimeout));
  }
}

static void do_timer(CFRunLoopTimerRef timer, void* data)
{
  for (int i = 0;  i < mac_timer_used;  ++i) {
    MacTimeout& t = mac_timers[i];
    if (t.timer == timer  &&  t.data == data) {
      t.pending = 0;
      (*t.callback)(data);
      if (t.pending==0)
        delete_timer(t);
      break;
    }
  }
  breakMacEventLoop();
}

@interface FLWindow : NSWindow 
{
  @private
  fltk3::Window *w;
  BOOL containsGLsubwindow;
}
- (FLWindow*)initWithFl_W:(fltk3::Window *)flw 
	      contentRect:(NSRect)rect 
		styleMask:(NSUInteger)windowStyle;
- (fltk3::Window *)getFl_Window;
- (BOOL)containsGLsubwindow;
- (void)setContainsGLsubwindow:(BOOL)contains;
@end

@implementation FLWindow
- (FLWindow*)initWithFl_W:(fltk3::Window *)flw 
	      contentRect:(NSRect)rect 
		styleMask:(NSUInteger)windowStyle 
{
  self = [super initWithContentRect:rect styleMask:windowStyle backing:NSBackingStoreBuffered defer:NO];
  if (self) {
    w = flw;
    containsGLsubwindow = NO;
  }
  return self;
}
- (fltk3::Window *)getFl_Window;
{
  return w;
}
- (BOOL)containsGLsubwindow
{
  return containsGLsubwindow;
}
- (void)setContainsGLsubwindow:(BOOL)contains
{
  containsGLsubwindow = contains;
}
@end

@interface FLApplication : NSObject
+ (void)sendEvent:(NSEvent *)theEvent;
@end

/*
 * This function is the central event handler.
 * It reads events from the event queue using the given maximum time
 * Funny enough, it returns the same time that it got as the argument. 
 */
static double do_queued_events( double time = 0.0 ) 
{
  got_events = 0;
  
  // Check for re-entrant condition
  if ( dataready.IsThreadRunning() ) {
    dataready.CancelThread(DEBUGTEXT("AVOID REENTRY\n"));
  }
  
  // Start thread to watch for data ready
  if ( dataready.GetNfds() ) {
    dataready.StartThread();
  }
  
  fl_unlock_function();
  NSEvent *event = [NSApp nextEventMatchingMask:NSAnyEventMask 
                                      untilDate:[NSDate dateWithTimeIntervalSinceNow:time] 
                                         inMode:NSDefaultRunLoopMode dequeue:YES];  
  if (event != nil) {
    got_events = 1;
    [FLApplication sendEvent:event]; // will then call [NSApplication sendevent:]
  }
  fl_lock_function();
  
#if CONSOLIDATE_MOTION
  if (send_motion && send_motion == fl_xmousewin) {
    send_motion = 0;
    fltk3::handle(fltk3::MOVE, fl_xmousewin);
  }
#endif
  
  return time;
}

/*
 * This public function handles all events. It wait a maximum of 
 * 'time' seconds for an event. This version returns 1 if events
 * other than the timeout timer were processed.
 *
 * \todo there is no socket handling in this code whatsoever
 */
int fl_wait( double time ) 
{
  do_queued_events( time );
  return (got_events);
}

double fl_mac_flush_and_wait(double time_to_wait, char in_idle) {
  NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
  fltk3::flush();
  if (fltk3::idle && !in_idle) // 'idle' may have been set within flush()
    time_to_wait = 0.0;
  double retval = fl_wait(time_to_wait);
  [pool release];
  return retval;
}

// updates fltk3::e_x, fltk3::e_y, fltk3::e_x_root, and fltk3::e_y_root
static void update_e_xy_and_e_xy_root(NSWindow *nsw)
{
  NSPoint pt;
  pt = [nsw mouseLocationOutsideOfEventStream];
  fltk3::e_x = int(pt.x);
  fltk3::e_y = int([[nsw contentView] frame].size.height - pt.y);
  pt = [NSEvent mouseLocation];
  fltk3::e_x_root = int(pt.x);
  fltk3::e_y_root = int(main_screen_height - pt.y);
}

/*
 * Cocoa Mousewheel handler
 */
static void cocoaMouseWheelHandler(NSEvent *theEvent)
{
  // Handle the new "MightyMouse" mouse wheel events. Please, someone explain
  // to me why Apple changed the API on this even though the current API
  // supports two wheels just fine. Matthias,
  fl_lock_function();
  
  fltk3::Window *window = (fltk3::Window*)[(FLWindow*)[theEvent window] getFl_Window];
  if ( !window->shown() ) {
    fl_unlock_function();
    return;
  }
  fltk3::first_window(window);
  
  // Under OSX, single mousewheel increments are 0.1,
  // so make sure they show up as at least 1..
  //
  float dx = [theEvent deltaX]; if ( fabs(dx) < 1.0 ) dx = (dx > 0) ? 1.0 : -1.0;
  float dy = [theEvent deltaY]; if ( fabs(dy) < 1.0 ) dy = (dy > 0) ? 1.0 : -1.0;
  if ([theEvent deltaX] != 0) {
    fltk3::e_dx = (int)-dx;
    fltk3::e_dy = 0;
    if ( fltk3::e_dx) fltk3::handle( fltk3::MOUSEWHEEL, window );
  } else if ([theEvent deltaY] != 0) {
    fltk3::e_dx = 0;
    fltk3::e_dy = (int)-dy;
    if ( fltk3::e_dy) fltk3::handle( fltk3::MOUSEWHEEL, window );
  } else {
    fl_unlock_function();
    return;
  }
  
  fl_unlock_function();
  
  //  return noErr;
}

/*
 * Cocoa Mouse Button Handler
 */
static void cocoaMouseHandler(NSEvent *theEvent)
{
  static int keysym[] = { 0, fltk3::MouseButton+1, fltk3::MouseButton+3, fltk3::MouseButton+2 };
  static int px, py;
  static char suppressed = 0;
  
  fl_lock_function();
  
  fltk3::Window *window = (fltk3::Window*)[(FLWindow*)[theEvent window] getFl_Window];
  if ( !window->shown() ) {
    fl_unlock_function();
    return;
  }
  fltk3::Window *first = fltk3::first_window();
  if (first != window && !(first->modal() || first->non_modal())) fltk3::first_window(window);
  NSPoint pos = [theEvent locationInWindow];
  pos.y = window->h() - pos.y;
  NSInteger btn = [theEvent buttonNumber]  + 1;
  NSUInteger mods = [theEvent modifierFlags];  
  int sendEvent = 0;
  
  NSEventType etype = [theEvent type];
  if (etype == NSLeftMouseDown || etype == NSRightMouseDown || etype == NSOtherMouseDown) {
    if (btn == 1) fltk3::e_state |= fltk3::BUTTON1;
    else if (btn == 3) fltk3::e_state |= fltk3::BUTTON2;
    else if (btn == 2) fltk3::e_state |= fltk3::BUTTON3;
  }
  else if (etype == NSLeftMouseUp || etype == NSRightMouseUp || etype == NSOtherMouseUp) {
    if (btn == 1) fltk3::e_state &= ~fltk3::BUTTON1;
    else if (btn == 3) fltk3::e_state &= ~fltk3::BUTTON2;
    else if (btn == 2) fltk3::e_state &= ~fltk3::BUTTON3;
    }
    
  switch ( etype ) {
    case NSLeftMouseDown:
    case NSRightMouseDown:
    case NSOtherMouseDown:
      suppressed = 0;
      sendEvent = fltk3::PUSH;
      fltk3::e_is_click = 1; 
      px = (int)pos.x; py = (int)pos.y;
      if ([theEvent clickCount] > 1) 
        fltk3::e_clicks++;
      else
        fltk3::e_clicks = 0;
      // fall through
    case NSLeftMouseUp:
    case NSRightMouseUp:
    case NSOtherMouseUp:
      if (suppressed) {
        suppressed = 0;
        break;
      }
      if ( !window ) break;
      if ( !sendEvent ) {
        sendEvent = fltk3::RELEASE; 
      }
      fltk3::e_keysym = keysym[ btn ];
      // fall through
    case NSMouseMoved:
      suppressed = 0;
      if ( !sendEvent ) { 
        sendEvent = fltk3::MOVE; 
      }
      // fall through
    case NSLeftMouseDragged:
    case NSRightMouseDragged:
    case NSOtherMouseDragged: {
      if (suppressed) break;
      if ( !sendEvent ) {
        sendEvent = fltk3::MOVE; // fltk3::handle will convert into fltk3::DRAG
        if (fabs(pos.x-px)>5 || fabs(pos.y-py)>5) 
          fltk3::e_is_click = 0;
      }
      mods_to_e_state( mods );
      update_e_xy_and_e_xy_root([theEvent window]);
      fltk3::handle( sendEvent, window );
      }
      break;
    default:
      break;
  }
  
  fl_unlock_function();
  
  return;
}

@interface FLTextView : NSTextView 
// this subclass is needed under OS X <= 10.5 but not under >= 10.6 where the base class is enough
- (void)insertText:(id)aString;
- (void)doCommandBySelector:(SEL)aSelector;
@end
@implementation FLTextView
- (void)insertText:(id)aString
{
  [[[NSApp keyWindow] contentView] insertText:aString];
}
- (void)doCommandBySelector:(SEL)aSelector
{
  [[[NSApp keyWindow] contentView] doCommandBySelector:aSelector];
}
@end

/*
Handle cocoa keyboard events
Events during a character composition sequence:
 - keydown with deadkey -> [[theEvent characters] length] is 0
 - keyup -> [theEvent characters] contains the deadkey
 - keydown with next key -> [theEvent characters] contains the composed character
 - keyup -> [theEvent characters] contains the standard character
 */
static void cocoaKeyboardHandler(NSEvent *theEvent)
{
  NSUInteger mods;
  
  // get the modifiers
  mods = [theEvent modifierFlags];
  // get the key code
  UInt32 keyCode = 0, maskedKeyCode = 0;
  unsigned short sym = 0;
  keyCode = [theEvent keyCode];
  NSString *s = [theEvent characters];  
  if ( (mods & NSShiftKeyMask) && (mods & NSCommandKeyMask) ) {
    s = [s uppercaseString]; // US keyboards return lowercase letter in s if cmd-shift-key is hit
  }
  // extended keyboards can also send sequences on key-up to generate Kanji etc. codes.
  // Some observed prefixes are 0x81 to 0x83, followed by an 8 bit keycode.
  // In this mode, there seem to be no key-down codes
  // printf("%08x %08x %08x\n", keyCode, mods, key);
  maskedKeyCode = keyCode & 0x7f;

  if ([theEvent type] == NSKeyUp) {
    fltk3::e_state &= 0xbfffffff; // clear the deadkey flag
  }

  mods_to_e_state( mods ); // process modifier keys
  sym = macKeyLookUp[maskedKeyCode];
  if (sym < 0xff00) { // a "simple" key
    // find the result of this key without modifier
    NSString *sim = [theEvent charactersIgnoringModifiers];
    UniChar one;
    CFStringGetCharacters((CFStringRef)sim, CFRangeMake(0, 1), &one);
    // charactersIgnoringModifiers doesn't ignore shift, remove it when it's on
    if(one >= 'A' && one <= 'Z') one += 32;
    if (one > 0 && one <= 0x7f && (sym<'0' || sym>'9') ) sym = one;
  }
  fltk3::e_keysym = fltk3::e_original_keysym = sym;

  //NSLog(@"cocoaKeyboardHandler: keycode=%08x keysym=%08x mods=%08x symbol=%@ (%@)",
  //  keyCode, sym, mods, [theEvent characters], [theEvent charactersIgnoringModifiers]);

  // If there is text associated with this key, it will be filled in later.
  fltk3::e_length = 0;
  fltk3::e_text = (char*)"";
}


/*
 * Open callback function to call...
 */

static void	(*open_cb)(const char *) = 0;

/*
 * Install an open documents event handler...
 */
void fl_open_callback(void (*cb)(const char *)) {
  fl_open_display();
  open_cb = cb;
}


@interface FLDelegate : NSObject 
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6
<NSWindowDelegate, NSApplicationDelegate>
#endif
- (void)windowDidMove:(NSNotification *)notif;
- (void)windowDidResize:(NSNotification *)notif;
- (void)windowDidResignKey:(NSNotification *)notif;
- (void)windowDidBecomeKey:(NSNotification *)notif;
- (void)windowDidBecomeMain:(NSNotification *)notif;
- (void)windowDidDeminiaturize:(NSNotification *)notif;
- (void)windowDidMiniaturize:(NSNotification *)notif;
- (BOOL)windowShouldClose:(id)fl;
- (void)anyWindowWillClose:(NSNotification *)notif;
- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication*)sender;
- (void)applicationDidBecomeActive:(NSNotification *)notify;
- (void)applicationDidChangeScreenParameters:(NSNotification *)aNotification;
- (void)applicationWillResignActive:(NSNotification *)notify;
- (void)applicationWillHide:(NSNotification *)notify;
- (void)applicationWillUnhide:(NSNotification *)notify;
- (id)windowWillReturnFieldEditor:(NSWindow *)sender toObject:(id)client;
- (BOOL)application:(NSApplication *)theApplication openFile:(NSString *)filename;
@end
@implementation FLDelegate
- (void)windowDidMove:(NSNotification *)notif
{
  fl_lock_function();
  FLWindow *nsw = (FLWindow*)[notif object];
  fltk3::Window *window = [nsw getFl_Window];
  NSPoint pt, pt2; 
  pt.x = 0;
  pt.y = [[nsw contentView] frame].size.height;
  pt2 = [nsw convertBaseToScreen:pt];
  update_e_xy_and_e_xy_root(nsw);
  resize_from_system = window;
  window->position((int)pt2.x, (int)(main_screen_height - pt2.y));
  if ([nsw containsGLsubwindow] ) {
    [nsw display];// redraw window after moving if it contains OpenGL subwindows
  }
  fl_unlock_function();
}
- (void)windowDidResize:(NSNotification *)notif
{
  fl_lock_function();
  FLWindow *nsw = (FLWindow*)[notif object];
  fltk3::Window *window = [nsw getFl_Window];
  NSRect r = [[nsw contentView] frame];
  NSPoint pt, pt2; 
  pt.x = 0;
  pt.y = [[nsw contentView] frame].size.height;
  pt2 = [nsw convertBaseToScreen:pt];
  resize_from_system = window;
  update_e_xy_and_e_xy_root(nsw);
  window->resize((int)pt2.x, 
                 (int)(main_screen_height - pt2.y),
		 (int)r.size.width,
		 (int)r.size.height);
  fl_unlock_function();
}
- (void)windowDidResignKey:(NSNotification *)notif
{
  fl_lock_function();
  FLWindow *nsw = (FLWindow*)[notif object];
  fltk3::Window *window = [nsw getFl_Window];
  fltk3::handle( fltk3::UNFOCUS, window);
  fl_unlock_function();
}
- (void)windowDidBecomeKey:(NSNotification *)notif
{
  fl_lock_function();
  FLWindow *nsw = (FLWindow*)[notif object];
  fltk3::Window *w = [nsw getFl_Window];
  if ( w->border() || (!w->modal() && !w->tooltip_window()) ) fltk3::handle( fltk3::FOCUS, w);
  fl_unlock_function();
}
- (void)windowDidBecomeMain:(NSNotification *)notif
{
  fl_lock_function();
  FLWindow *nsw = (FLWindow*)[notif object];
  fltk3::Window *window = [nsw getFl_Window];
  fltk3::first_window(window);
  update_e_xy_and_e_xy_root(nsw);
  fl_unlock_function();
}
- (void)windowDidDeminiaturize:(NSNotification *)notif
{
  fl_lock_function();
  FLWindow *nsw = (FLWindow*)[notif object];
  fltk3::Window *window = [nsw getFl_Window];
  fltk3::handle(fltk3::SHOW, window);
  update_e_xy_and_e_xy_root(nsw);
  fl_unlock_function();
}
- (void)windowDidMiniaturize:(NSNotification *)notif
{
  fl_lock_function();
  FLWindow *nsw = (FLWindow*)[notif object];
  fltk3::Window *window = [nsw getFl_Window];
  fltk3::handle(fltk3::HIDE, window);
  fl_unlock_function();
}
- (BOOL)windowShouldClose:(id)fl
{
  fl_lock_function();
  fltk3::handle( fltk3::CLOSE, [fl getFl_Window] ); // this might or might not close the window
  fl_unlock_function();
  return NO; // the system doesn't need to send [fl close] because FLTK does it when needed
}
- (void)anyWindowWillClose:(NSNotification *)notif
{
  fl_lock_function();
  if ([[notif object] isKeyWindow]) {
    // If the closing window is the key window,
    // find a bordered top-level window to become the new key window
    fltk3::Window *w = fltk3::first_window();
    while (w && (w->parent() || !w->border() || !w->visible())) {
      w = fltk3::next_window(w);
    }
    if (w) {
      [Fl_X::i(w)->xid makeKeyWindow];
    }
  }
  fl_unlock_function();
}
- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication*)sender
{
  fl_lock_function();
  NSApplicationTerminateReply reply = NSTerminateNow;
  while ( Fl_X::first ) {
    Fl_X *x = Fl_X::first;
    fltk3::handle( fltk3::CLOSE, x->w );
    fltk3::do_widget_deletion();
    if ( Fl_X::first == x ) {
      reply = NSTerminateCancel; // FLTK has not closed all windows, so we return to the main program now
      break;
    }
  }
  fl_unlock_function();
  return reply;
}
/**
 * Cocoa organizes the Z depth of windows on a global priority. FLTK however
 * expects the window manager to organize Z level by application. The trickery
 * below will change Z order during activation and deactivation.
 */
- (void)applicationDidBecomeActive:(NSNotification *)notify
{
  fl_lock_function();
  Fl_X *x;
  FLWindow *top = 0, *topModal = 0, *topNonModal = 0;
  for (x = Fl_X::first;x;x = x->next) {
    FLWindow *cw = x->xid;
    fltk3::Window *win = x->w;
    if (win && cw && [cw isVisible]) {
      if (win->modal()) {
        [cw setLevel:NSModalPanelWindowLevel];
        if (topModal) 
          [cw orderWindow:NSWindowBelow relativeTo:[topModal windowNumber]];
        else
          topModal = cw;
      } else if (win->non_modal()) {
        [cw setLevel:NSFloatingWindowLevel];
        if (topNonModal) 
          [cw orderWindow:NSWindowBelow relativeTo:[topNonModal windowNumber]];
        else
          topNonModal = cw;
      } else {
        if (top) 
          ;
        else
          top = cw;
      }
    }
  }
  fl_unlock_function();
}
- (void)applicationDidChangeScreenParameters:(NSNotification *)unused
{ // react to changes in screen numbers and positions
  main_screen_height = [[[NSScreen screens] objectAtIndex:0] frame].size.height;
  fltk3::call_screen_init();
  // FLTK windows have already been notified they were moved,
  // but they had the old main_screen_height, so they must be notified again.
  NSArray *windows = [NSApp windows];
  int count = [windows count];
  for (int i = 0; i < count; i++) {
    NSWindow *win = [windows objectAtIndex:i];
    if ([win isKindOfClass:[FLWindow class]]) {
      [[NSNotificationCenter defaultCenter] postNotificationName:NSWindowDidMoveNotification object:win];
    }
  }
  fltk3::handle(fltk3::SCREEN_CONFIGURATION_CHANGED, NULL);
}
- (void)applicationWillResignActive:(NSNotification *)notify
{
  fl_lock_function();
  Fl_X *x;
  FLWindow *top = 0;
  // sort in all regular windows
  for (x = Fl_X::first;x;x = x->next) {
    FLWindow *cw = x->xid;
    fltk3::Window *win = x->w;
    if (win && cw) {
      if (win->modal()) {
      } else if (win->non_modal()) {
      } else {
        if (!top) top = cw;
      }
    }
  }
  // now sort in all modals
  for (x = Fl_X::first;x;x = x->next) {
    FLWindow *cw = x->xid;
    fltk3::Window *win = x->w;
    if (win && cw && [cw isVisible]) {
      if (win->modal()) {
        [cw setLevel:NSNormalWindowLevel];
        if (top) [cw orderWindow:NSWindowAbove relativeTo:[top windowNumber]];
      }
    }
  }
  // finally all non-modals
  for (x = Fl_X::first;x;x = x->next) {
    FLWindow *cw = x->xid;
    fltk3::Window *win = x->w;
    if (win && cw && [cw isVisible]) {
      if (win->non_modal()) {
        [cw setLevel:NSNormalWindowLevel];
        if (top) [cw orderWindow:NSWindowAbove relativeTo:[top windowNumber]];
      }
    }
  }
  fl_unlock_function();
}
- (void)applicationWillHide:(NSNotification *)notify
{
  fl_lock_function();
  Fl_X *x;
  for (x = Fl_X::first;x;x = x->next) {
    fltk3::Window *window = x->w;
    if ( !window->parent() ) fltk3::handle( fltk3::HIDE, window);
    }
  fl_unlock_function();
}
- (void)applicationWillUnhide:(NSNotification *)notify
{
  fl_lock_function();
  Fl_X *x;
  for (x = Fl_X::first;x;x = x->next) {
    fltk3::Window *w = x->w;
    if ( !w->parent() ) {
      fltk3::handle( fltk3::SHOW, w);
      }
  }
  fl_unlock_function();
}
- (id)windowWillReturnFieldEditor:(NSWindow *)sender toObject:(id)client
{
  if (fl_mac_os_version < 100600) {
    static FLTextView *view = nil;
    if (!view) {
      NSRect rect={{0,0},{20,20}};
      view = [[FLTextView alloc] initWithFrame:rect];
    }
    return view;
  }
  return nil;
}
- (BOOL)application:(NSApplication *)theApplication openFile:(NSString *)filename
{
  if (open_cb) {
    fl_lock_function();
    (*open_cb)([filename UTF8String]);
    fl_unlock_function();
    return YES;
  }
  return NO;
}
@end

@implementation FLApplication
+ (void)sendEvent:(NSEvent *)theEvent
{
  NSEventType type = [theEvent type];  
  if (type == NSLeftMouseDown) {
    fl_lock_function();
    fltk3::Window *grab = fltk3::grab();
    if (grab) {
      FLWindow *win = (FLWindow *)[theEvent window];
      if ( [win isKindOfClass:[FLWindow class]] && grab != [win getFl_Window]) {
	// a click event out of a menu window, so we should close this menu
	// done here to catch also clicks on window title bar/resize box 
	cocoaMouseHandler(theEvent);
      }
    }
    fl_unlock_function();
  } else if (type == NSApplicationDefined) {
    if ([theEvent subtype] == FLTKDataReadyEvent) {
      processFLTKEvent();
    }
    return;
  } else if (type == NSKeyUp) {
    // The default sendEvent turns key downs into performKeyEquivalent when
    // modifiers are down, but swallows the key up if the modifiers include
    // command.  This one makes all modifiers consistent by always sending key ups.
    // FLView treats performKeyEquivalent to keyDown, but performKeyEquivalent is
    // still needed for the system menu.
    [[NSApp keyWindow] sendEvent:theEvent];
    return;
    }
  [NSApp sendEvent:theEvent]; 
}
@end

extern "C" {
  OSErr CPSEnableForegroundOperation(ProcessSerialNumber *psn, UInt32 _arg2,
				     UInt32 _arg3, UInt32 _arg4, UInt32 _arg5);
}

void fl_open_display() {
  static char beenHereDoneThat = 0;
  if ( !beenHereDoneThat ) {
    beenHereDoneThat = 1;

    BOOL need_new_nsapp = (NSApp == nil);
    if (need_new_nsapp) [NSApplication sharedApplication];
    NSAutoreleasePool *localPool;
    localPool = [[NSAutoreleasePool alloc] init]; // never released
    [NSApp setDelegate:[[FLDelegate alloc] init]];
    if (need_new_nsapp) [NSApp finishLaunching];

    // empty the event queue but keep system events for drag&drop of files at launch
    NSEvent *ign_event;
    do ign_event = [NSApp nextEventMatchingMask:(NSAnyEventMask & ~NSSystemDefinedMask)
					untilDate:[NSDate dateWithTimeIntervalSinceNow:0] 
					   inMode:NSDefaultRunLoopMode 
					  dequeue:YES];
    while (ign_event);
    
    fl_default_cursor = [NSCursor arrowCursor];

    // bring the application into foreground without a 'CARB' resource
    Boolean same_psn;
    ProcessSerialNumber cur_psn, front_psn;
    if ( !GetCurrentProcess( &cur_psn ) && !GetFrontProcess( &front_psn ) &&
         !SameProcess( &front_psn, &cur_psn, &same_psn ) && !same_psn ) {
      // only transform the application type for unbundled apps
      CFBundleRef bundle = CFBundleGetMainBundle();
      if ( bundle ) {
      	FSRef execFs;
      	CFURLRef execUrl = CFBundleCopyExecutableURL( bundle );
      	CFURLGetFSRef( execUrl, &execFs );
        
      	FSRef bundleFs;
      	GetProcessBundleLocation( &cur_psn, &bundleFs );
        
      	if ( !FSCompareFSRefs( &execFs, &bundleFs ) )
          bundle = NULL;
        
        CFRelease(execUrl);
      }
            
      if ( !bundle )
      {
        // Earlier versions of this code tried to use weak linking, however it
        // appears that this does not work on 10.2.  Since 10.3 and higher provide
        // both TransformProcessType and CPSEnableForegroundOperation, the following
        // conditional code compiled on 10.2 will still work on newer releases...
        OSErr err;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
        if (TransformProcessType != NULL) {
          err = TransformProcessType(&cur_psn, kProcessTransformToForegroundApplication);
        } else
#endif // MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_3
          err = CPSEnableForegroundOperation(&cur_psn, 0x03, 0x3C, 0x2C, 0x1103);
        if (err == noErr) {
          SetFrontProcess( &cur_psn );
        }
      }
    }
    if (![NSApp servicesMenu]) createAppleMenu();
    main_screen_height = [[[NSScreen screens] objectAtIndex:0] frame].size.height;
    [[NSNotificationCenter defaultCenter] addObserver:[NSApp delegate] 
					     selector:@selector(anyWindowWillClose:) 
						 name:NSWindowWillCloseNotification 
					       object:nil];
  }
}


/*
 * get rid of allocated resources
 */
void fl_close_display() {
}


// Gets the border sizes and the titlebar size
static void get_window_frame_sizes(int &bx, int &by, int &bt) {
  static bool first = true;
  static int top, left, bottom;
  if (first) {
    first = false;
    if (NSApp == nil) fl_open_display();
    NSRect inside = { {20,20}, {100,100} };
    NSRect outside = [NSWindow  frameRectForContentRect:inside styleMask:NSTitledWindowMask];
    left = int(outside.origin.x - inside.origin.x);
    bottom = int(outside.origin.y - inside.origin.y);
    top = int(outside.size.height - inside.size.height) - bottom;
    }
  bx = left;
  by = bottom;
  bt = top;
}

/*
 * smallest x coordinate in screen space of work area of menubar-containing display
 */
int fltk3::x() {
  return int([[[NSScreen screens] objectAtIndex:0] visibleFrame].origin.x);
}


/*
 * smallest y coordinate in screen space of work area of menubar-containing display
 */
int fltk3::y() {
  NSRect visible = [[[NSScreen screens] objectAtIndex:0] visibleFrame];
  return int(main_screen_height - (visible.origin.y + visible.size.height));
}


/*
 * width of work area of menubar-containing display
 */
int fltk3::w() {
  return int([[[NSScreen screens] objectAtIndex:0] visibleFrame].size.width);
}


/*
 * height of work area of menubar-containing display
 */
int fltk3::h() {
  return int([[[NSScreen screens] objectAtIndex:0] visibleFrame].size.height);
}

// computes the work area of the nth screen (screen #0 has the menubar)
void Fl_X::screen_work_area(int &X, int &Y, int &W, int &H, int n)
{
  NSRect r = [[[NSScreen screens] objectAtIndex:n] visibleFrame];
  X   = int(r.origin.x);
  Y   = main_screen_height - int(r.origin.y + r.size.height);
  W   = int(r.size.width);
  H   = int(r.size.height);
}

/*
 * get the current mouse pointer world coordinates
 */
void fltk3::get_mouse(int &x, int &y) 
{
  fl_open_display();
  NSPoint pt = [NSEvent mouseLocation];
  x = int(pt.x);
  y = int(main_screen_height - pt.y);
}


/*
 * Initialize the given port for redraw and call the window's flush() to actually draw the content
 */ 
void Fl_X::flush()
{
  w->flush();
  if (fl_gc) CGContextFlush(fl_gc);
}

/*
 * Gets called when a window is created, resized, or deminiaturized
 */    
static void handleUpdateEvent( fltk3::Window *window ) 
{
  if ( !window ) return;
  Fl_X *i = Fl_X::i( window );
  i->wait_for_expose = 0;

  if ( i->region ) {
    XDestroyRegion(i->region);
    i->region = 0;
  }
  
  for ( Fl_X *cx = i->xidChildren; cx; cx = cx->xidNext ) {
    if ( cx->region ) {
      XDestroyRegion(cx->region);
      cx->region = 0;
    }
    cx->w->clear_damage(fltk3::DAMAGE_ALL);
    cx->flush();
    cx->w->clear_damage();
  }
  window->clear_damage(fltk3::DAMAGE_ALL);
  i->flush();
  window->clear_damage();
}     


int Fl_X::fake_X_wm(const fltk3::Window* w,int &X,int &Y, int &bt,int &bx, int &by) {
  int W, H, xoff, yoff, dx, dy;
  int ret = bx = by = bt = 0;
  if (w->border() && !w->parent()) {
    if (w->maxw != w->minw || w->maxh != w->minh) {
      ret = 2;
    } else {
      ret = 1;
    }
    get_window_frame_sizes(bx, by, bt);
  }
  // The coordinates of the whole window, including non-client area
  xoff = bx;
  yoff = by + bt;
  dx = 2*bx;
  dy = 2*by + bt;
  X = w->x()-xoff;
  Y = w->y()-yoff;
  W = w->w()+dx;
  H = w->h()+dy;
  
  // Proceed to positioning the window fully inside the screen, if possible
  
  // let's get a little elaborate here. Mac OS X puts a lot of stuff on the desk
  // that we want to avoid when positioning our window, namely the Dock and the
  // top menu bar (and even more stuff in 10.4 Tiger). So we will go through the
  // list of all available screens and find the one that this window is most
  // likely to go to, and then reposition it to fit withing the 'good' area.
  //  Rect r;
  // find the screen, that the center of this window will fall into
  int R = X+W, B = Y+H; // right and bottom
  int cx = (X+R)/2, cy = (Y+B)/2; // center of window;
  NSScreen *gd = NULL;
  NSArray *a = [NSScreen screens]; int count = (int)[a count]; NSRect r; int i;
  for( i = 0; i < count; i++) {
    r = [[a objectAtIndex:i] frame];
    r.origin.y = main_screen_height - (r.origin.y + r.size.height); // use FLTK's multiscreen coordinates
    if (   cx >= r.origin.x && cx <= r.origin.x + r.size.width
        && cy >= r.origin.y && cy <= r.origin.y + r.size.height)
      break;
  }
  if (i < count) gd = [a objectAtIndex:i];
  
  // if the center doesn't fall on a screen, try the top left
  if (!gd) {
    for( i = 0; i < count; i++) {
      r = [[a objectAtIndex:i] frame];
      r.origin.y = main_screen_height - (r.origin.y + r.size.height); // use FLTK's multiscreen coordinates
      if (    X >= r.origin.x && X <= r.origin.x + r.size.width
          && Y >= r.origin.y  && Y <= r.origin.y + r.size.height)
        break;
    }
    if (i < count) gd = [a objectAtIndex:i];
  }
  // if that doesn't fall on a screen, try the top right
  if (!gd) {
    for( i = 0; i < count; i++) {
      r = [[a objectAtIndex:i] frame];
      r.origin.y = main_screen_height - (r.origin.y + r.size.height); // use FLTK's multiscreen coordinates
      if (    R >= r.origin.x && R <= r.origin.x + r.size.width
          && Y >= r.origin.y  && Y <= r.origin.y + r.size.height)
        break;
    }
    if (i < count) gd = [a objectAtIndex:i];
  }
  // if that doesn't fall on a screen, try the bottom left
  if (!gd) {
    for( i = 0; i < count; i++) {
      r = [[a objectAtIndex:i] frame];
      r.origin.y = main_screen_height - (r.origin.y + r.size.height); // use FLTK's multiscreen coordinates
      if (    X >= r.origin.x && X <= r.origin.x + r.size.width
          && Y+H >= r.origin.y  && Y+H <= r.origin.y + r.size.height)
        break;
    }
    if (i < count) gd = [a objectAtIndex:i];
  }
  // last resort, try the bottom right
  if (!gd) {
    for( i = 0; i < count; i++) {
      r = [[a objectAtIndex:i] frame];
      r.origin.y = main_screen_height - (r.origin.y + r.size.height); // use FLTK's multiscreen coordinates
      if (    R >= r.origin.x && R <= r.origin.x + r.size.width
          && Y+H >= r.origin.y  && Y+H <= r.origin.y + r.size.height)
        break;
    }
    if (i < count) gd = [a objectAtIndex:i];
  }
  // if we still have not found a screen, we will use the main
  // screen, the one that has the application menu bar.
  if (!gd) gd = [a objectAtIndex:0];
  if (gd) {
    r = [gd visibleFrame];
    r.origin.y = main_screen_height - (r.origin.y + r.size.height); // use FLTK's multiscreen coordinates
    if ( R > r.origin.x + r.size.width ) X -= int(R - (r.origin.x + r.size.width));
    if ( B > r.size.height + r.origin.y ) Y -= int(B - (r.size.height + r.origin.y));
    if ( X < r.origin.x ) X = int(r.origin.x);
    if ( Y < r.origin.y ) Y = int(r.origin.y);
  }
  
  // Return the client area's top left corner in (X,Y)
  X+=xoff;
  Y+=yoff;
  
  return ret;
}


fltk3::Window *fl_dnd_target_window = 0;

static void  q_set_window_title(NSWindow *nsw, const char * name, const char *mininame) {
  CFStringRef title = CFStringCreateWithCString(NULL, (name ? name : ""), kCFStringEncodingUTF8);
  if(!title) { // fallback when name contains malformed UTF-8
    int l = strlen(name);
    unsigned short* utf16 = new unsigned short[l + 1];
    l = fltk3::utf8toUtf16(name, l, utf16, l + 1);
    title = CFStringCreateWithCharacters(NULL, utf16, l);
    delete[] utf16;
    }
  [nsw setTitle:(NSString*)title];
  CFRelease(title);
  if (mininame && strlen(mininame)) {
    CFStringRef minititle = CFStringCreateWithCString(NULL, mininame, kCFStringEncodingUTF8);
    if (minititle) {
      [nsw setMiniwindowTitle:(NSString*)minititle];
      CFRelease(minititle);
    }
  }
}


@interface FLView : NSView <NSTextInput> 
{
  @private
  int next_compose_length;
  bool in_key_event;
}
+ (void)prepareEtext:(NSString*)aString;
- (id)init;
- (void)drawRect:(NSRect)rect;
- (BOOL)acceptsFirstResponder;
- (BOOL)acceptsFirstMouse:(NSEvent*)theEvent;
- (BOOL)performKeyEquivalent:(NSEvent*)theEvent;
- (void)mouseUp:(NSEvent *)theEvent;
- (void)rightMouseUp:(NSEvent *)theEvent;
- (void)otherMouseUp:(NSEvent *)theEvent;
- (void)mouseDown:(NSEvent *)theEvent;
- (void)rightMouseDown:(NSEvent *)theEvent;
- (void)otherMouseDown:(NSEvent *)theEvent;
- (void)mouseMoved:(NSEvent *)theEvent;
- (void)mouseDragged:(NSEvent *)theEvent;
- (void)rightMouseDragged:(NSEvent *)theEvent;
- (void)otherMouseDragged:(NSEvent *)theEvent;
- (void)scrollWheel:(NSEvent *)theEvent;
- (BOOL)handleKeyDown:(NSEvent *)theEvent;
- (void)keyDown:(NSEvent *)theEvent;
- (void)keyUp:(NSEvent *)theEvent;
- (void)flagsChanged:(NSEvent *)theEvent;
- (NSDragOperation)draggingEntered:(id < NSDraggingInfo >)sender;
- (NSDragOperation)draggingUpdated:(id < NSDraggingInfo >)sender;
- (BOOL)performDragOperation:(id <NSDraggingInfo>)sender;
- (void)draggingExited:(id < NSDraggingInfo >)sender;
- (NSDragOperation)draggingSourceOperationMaskForLocal:(BOOL)isLocal;
@end

@implementation FLView
- (id)init
{
  self = [super init];
  if (self) {
    next_compose_length = -1;
    in_key_event = false;
    }
  return self;
}
- (void)drawRect:(NSRect)rect
{
  fl_lock_function();
  FLWindow *cw = (FLWindow*)[self window];
  fltk3::Window *w = [cw getFl_Window];
  handleUpdateEvent(w);
  fl_unlock_function();
}

- (BOOL)acceptsFirstResponder
{   
  return YES;
}
- (BOOL)performKeyEquivalent:(NSEvent*)theEvent
{   
  //NSLog(@"performKeyEquivalent:");
  return [self handleKeyDown:theEvent];
}
- (BOOL)acceptsFirstMouse:(NSEvent*)theEvent
{   
  fltk3::Window *w = [(FLWindow*)[theEvent window] getFl_Window];
  fltk3::Window *first = fltk3::first_window();
  return (first == w || !first->modal());
}
- (void)mouseUp:(NSEvent *)theEvent {
  cocoaMouseHandler(theEvent);
}
- (void)rightMouseUp:(NSEvent *)theEvent {
  cocoaMouseHandler(theEvent);
}
- (void)otherMouseUp:(NSEvent *)theEvent {
  cocoaMouseHandler(theEvent);
}
- (void)mouseDown:(NSEvent *)theEvent {
  cocoaMouseHandler(theEvent);
}
- (void)rightMouseDown:(NSEvent *)theEvent {
  cocoaMouseHandler(theEvent);
}
- (void)otherMouseDown:(NSEvent *)theEvent {
  cocoaMouseHandler(theEvent);
}
- (void)mouseMoved:(NSEvent *)theEvent {
  cocoaMouseHandler(theEvent);
}
- (void)mouseDragged:(NSEvent *)theEvent {
  cocoaMouseHandler(theEvent);
}
- (void)rightMouseDragged:(NSEvent *)theEvent {
  cocoaMouseHandler(theEvent);
}
- (void)otherMouseDragged:(NSEvent *)theEvent {
  cocoaMouseHandler(theEvent);
}
- (void)scrollWheel:(NSEvent *)theEvent {
  cocoaMouseWheelHandler(theEvent);
}
- (BOOL)handleKeyDown:(NSEvent *)theEvent {
  //NSLog(@"handleKeyDown");
  fl_lock_function();

  fltk3::Window *window = (fltk3::Window*)[(FLWindow*)[theEvent window] getFl_Window];
  fltk3::first_window(window);

  next_compose_length = -1;
  // First let's process the raw key press
  cocoaKeyboardHandler(theEvent);

  unsigned int no_text_key = false;
  static const unsigned int notext[] = { // keys that don't emit text
    fltk3::BackSpaceKey, fltk3::PrintKey, fltk3::ScrollLockKey, fltk3::PauseKey,
    fltk3::InsertKey, fltk3::HomeKey, fltk3::PageUpKey, fltk3::DeleteKey, fltk3::EndKey, fltk3::PageDownKey,
    fltk3::LeftKey, fltk3::UpKey, fltk3::RightKey, fltk3::DownKey, 
    fltk3::MenuKey, fltk3::NumLockKey, fltk3::HelpKey 
  };
  static const int count = sizeof(notext)/sizeof(int);
  if (fltk3::e_keysym > fltk3::FKey && fltk3::e_keysym <= fltk3::FLastKey) no_text_key = true;
  else for (int i=0; i < count; i++) {
    if (notext[i] == fltk3::e_keysym) {
      no_text_key = true;
      break;
    }
  }
  if (!no_text_key && !(fltk3::e_state & fltk3::META) ) {
    // Don't send cmd-<key> to interpretKeyEvents because it beeps.
    // Then we can let the OS have a stab at it and see if it thinks it
    // should result in some text
    NSText *edit = [[theEvent window]  fieldEditor:YES forObject:nil];
    in_key_event = true;
    [edit interpretKeyEvents:[NSArray arrayWithObject:theEvent]];
    in_key_event = false;
  }
  //NSLog(@"to text=%@ l=%d", [NSString stringWithUTF8String:fltk3::e_text], fltk3::e_length);
  int handled = fltk3::handle(fltk3::KEYDOWN, window);
  // We have to update this after fltk3::handle as it says what to do on the
  // _next_ input
  if (next_compose_length != -1)
    fltk3::compose_state = next_compose_length;

  fl_unlock_function();
  return (handled ? YES : NO);
}
- (void)keyDown:(NSEvent *)theEvent {
  //NSLog(@"keyDown: ");
  [self handleKeyDown:theEvent];
}
- (void)keyUp:(NSEvent *)theEvent {
  //NSLog(@"keyUp: ");
  fl_lock_function();
  fltk3::Window *window = (fltk3::Window*)[(FLWindow*)[theEvent window] getFl_Window];
  fltk3::first_window(window);
  cocoaKeyboardHandler(theEvent);
  NSString *s = [theEvent characters];
  if ([s length] >= 1) [FLView prepareEtext:[s substringToIndex:1]];
  fltk3::handle(fltk3::KEYUP,window);
  fl_unlock_function();
}
- (void)flagsChanged:(NSEvent *)theEvent {
  //NSLog(@"flagsChanged: ");
  fl_lock_function();
  static UInt32 prevMods = 0;
  NSUInteger mods = [theEvent modifierFlags];
  fltk3::Window *window = (fltk3::Window*)[(FLWindow*)[theEvent window] getFl_Window];
  UInt32 tMods = prevMods ^ mods;
  int sendEvent = 0;
  if ( tMods )
  {
    unsigned short keycode = [theEvent keyCode];
    fltk3::e_keysym = fltk3::e_original_keysym = macKeyLookUp[keycode & 0x7f];
    if ( fltk3::e_keysym ) 
      sendEvent = ( prevMods<mods ) ? fltk3::KEYBOARD : fltk3::KEYUP;
    fltk3::e_length = 0;
    fltk3::e_text = (char*)"";
    prevMods = mods;
  }
  mods_to_e_state( mods );
  while (window->parent()) window = window->window();
  if (sendEvent) fltk3::handle(sendEvent,window);
  fl_unlock_function();
}
- (NSDragOperation)draggingEntered:(id < NSDraggingInfo >)sender
{
  fl_lock_function();
  fltk3::Window *target = [(FLWindow*)[self window] getFl_Window];
  update_e_xy_and_e_xy_root([self window]);
  fl_dnd_target_window = target;
  int ret = fltk3::handle( fltk3::DND_ENTER, target );
  breakMacEventLoop();
  fl_unlock_function();
  // if the DND started in the same application, fltk3::dnd() will not return until 
  // the DND operation is finished. The call below causes the drop indicator
  // to be drawn correctly (a full event handling would be better...)
  fltk3::flush();
  return ret ? NSDragOperationCopy : NSDragOperationNone;
}
- (NSDragOperation)draggingUpdated:(id < NSDraggingInfo >)sender
{
  fl_lock_function();
  fltk3::Window *target = [(FLWindow*)[self window] getFl_Window];
  update_e_xy_and_e_xy_root([self window]);
  fl_dnd_target_window = target;
  int ret = fltk3::handle( fltk3::DND_DRAG, target );
  breakMacEventLoop();
  fl_unlock_function();
  fltk3::flush();
  return ret ? NSDragOperationCopy : NSDragOperationNone;
}
- (BOOL)performDragOperation:(id <NSDraggingInfo>)sender 
{
  static char *DragData = NULL;
  fl_lock_function();
  fltk3::Window *target = [(FLWindow*)[self window] getFl_Window];
  if ( !fltk3::handle( fltk3::DND_RELEASE, target ) ) { 
    breakMacEventLoop();
    fl_unlock_function();
    return NO;
  }
  NSPasteboard *pboard;
  // NSDragOperation sourceDragMask;
  // sourceDragMask = [sender draggingSourceOperationMask];
  pboard = [sender draggingPasteboard];
  update_e_xy_and_e_xy_root([self window]);
  if (DragData) { free(DragData); DragData = NULL; }
  if ( [[pboard types] containsObject:NSFilenamesPboardType] ) {
    CFArrayRef files = (CFArrayRef)[pboard propertyListForType:NSFilenamesPboardType];
    CFStringRef all = CFStringCreateByCombiningStrings(NULL, files, CFSTR("\n"));
    int l = CFStringGetMaximumSizeForEncoding(CFStringGetLength(all), kCFStringEncodingUTF8);
    DragData = (char *)malloc(l + 1);
    CFStringGetCString(all, DragData, l + 1, kCFStringEncodingUTF8);
    CFRelease(all);
  }
  else if ( [[pboard types] containsObject:NSStringPboardType] ) {
    NSData *data = [pboard dataForType:NSStringPboardType];
    DragData = (char *)malloc([data length] + 1);
    [data getBytes:DragData];
    DragData[[data length]] = 0;
    convert_crlf(DragData, strlen(DragData));
  }
  else {
    breakMacEventLoop();
    fl_unlock_function();
    return NO;
  }
  fltk3::e_text = DragData;
  fltk3::e_length = strlen(DragData);
  int old_event = fltk3::e_number;
  fltk3::belowmouse()->handle(fltk3::e_number = fltk3::PASTE);
  fltk3::e_number = old_event;
  if (DragData) { free(DragData); DragData = NULL; }
  fltk3::e_text = NULL;
  fltk3::e_length = 0;
  fl_dnd_target_window = NULL;
  breakMacEventLoop();
  fl_unlock_function();
  return YES;
}
- (void)draggingExited:(id < NSDraggingInfo >)sender
{
  fl_lock_function();
  if ( fl_dnd_target_window ) {
    fltk3::handle( fltk3::DND_LEAVE, fl_dnd_target_window );
    fl_dnd_target_window = 0;
  }
  fl_unlock_function();
}
- (NSDragOperation)draggingSourceOperationMaskForLocal:(BOOL)isLocal
{
  return NSDragOperationGeneric;
}

+ (void)prepareEtext:(NSString*)aString {
  // fills fltk3::e_text with UTF-8 encoded aString using an adequate memory allocation
  static char *received_utf8 = NULL;
  static int lreceived = 0;
  char *p = (char*)[aString UTF8String];
  int l = strlen(p);
  if (l > 0) {
    if (lreceived == 0) {
      received_utf8 = (char*)malloc(l + 1);
      lreceived = l;
    }
    else if (l > lreceived) {
      received_utf8 = (char*)realloc(received_utf8, l + 1);
      lreceived = l;
    }
    strcpy(received_utf8, p);
    fltk3::e_text = received_utf8;
  }
  fltk3::e_length = l;
}

// These functions implement text input.
// Only two-stroke character composition works at this point.
// Needs much elaboration to fully support CJK text input,
// but this is the way to go.
- (void)doCommandBySelector:(SEL)aSelector {
}

- (void)insertText:(id)aString {
  NSString *received;
  if ([aString isKindOfClass:[NSAttributedString class]]) {
    received = [(NSAttributedString*)aString string];
  } else {
    received = (NSString*)aString;
  }
  //NSLog(@"insertText: received=%@",received);

  if (!in_key_event) fl_lock_function();
  [FLView prepareEtext:received];
  // We can get called outside of key events (e.g. from the character
  // palette). Transform such actions to fltk3::PASTE events.
  if (!in_key_event) {
    fltk3::Window *target = [(FLWindow*)[self window] getFl_Window];
    fltk3::handle(fltk3::PASTE, target);
    // for some reason, the window does not redraw until the next mouse move or button push
    // sending a 'redraw()' or 'awake()' does not solve the issue!
    fltk3::flush();
  }
  if (!in_key_event) fl_unlock_function();
}

- (void)setMarkedText:(id)aString selectedRange:(NSRange)newSelection  {
  NSString *received;
  if (newSelection.location == 0) {
    [self unmarkText];
    return;
  }
  if ([aString isKindOfClass:[NSAttributedString class]]) {
    received = [(NSAttributedString*)aString string];
  } else {
    received = (NSString*)aString;
  }
  //NSLog(@"setMarkedText: %@ %d %d",received,newSelection.location,newSelection.length);
  // This code creates the OS X behaviour of seeing dead keys as things
  // are being composed.
  next_compose_length = newSelection.location;
  [FLView prepareEtext:received];
  //NSLog(@"fltk3::e_text=%@ fltk3::e_length=%d next_compose_length=%d", received, fltk3::e_length, next_compose_length);
}

- (void)unmarkText {
  fl_lock_function();
  fltk3::compose_state = 0;
  fl_unlock_function();
  //NSLog(@"unmarkText");
}

- (NSRange)selectedRange {
  return NSMakeRange(NSNotFound, 0);
}

- (NSRange)markedRange {
  //NSLog(@"markedRange ?");
  return NSMakeRange(NSNotFound, fltk3::compose_state);
}

- (BOOL)hasMarkedText {
  //NSLog(@"hasMarkedText %s", fltk3::compose_state > 0?"YES":"NO");
  return (fltk3::compose_state > 0);
}

- (NSAttributedString *)attributedSubstringFromRange:(NSRange)aRange {
  //NSLog(@"attributedSubstringFromRange: %d %d",aRange.location,aRange.length);
  return nil;
}

- (NSArray *)validAttributesForMarkedText {
  return nil;
}

- (NSRect)firstRectForCharacterRange:(NSRange)aRange {
  NSRect glyphRect;
  fl_lock_function();
  fltk3::Widget *focus = fltk3::focus();
  fltk3::Window *wfocus = focus->window();
  while (wfocus->window()) wfocus = wfocus->window();
  glyphRect.size.width = 0;
  
  if (dynamic_cast<fltk3::TextDisplay*>(focus) != NULL) {
    int x, y;
    fltk3::TextDisplay *current = (fltk3::TextDisplay*)focus;
    current->position_to_xy( current->insert_position(), &x, &y );
    glyphRect.origin.x = (CGFloat)x;
    glyphRect.origin.y = (CGFloat)y + current->textsize();
    glyphRect.size.height = current->textsize();
  } else {
    glyphRect.origin.x = focus->x();
    glyphRect.origin.y = focus->y() + focus->h();
    glyphRect.size.height = 12;
  }
  // Convert the rect to screen coordinates
  glyphRect.origin.y = wfocus->h() - glyphRect.origin.y;
  glyphRect.origin = [[self window] convertBaseToScreen:glyphRect.origin];
  fl_unlock_function();
  return glyphRect;
}

- (NSUInteger)characterIndexForPoint:(NSPoint)aPoint {
  return 0;
}

- (NSInteger)conversationIdentifier {
  return (NSInteger)self;
}

@end


/*
 * go ahead, create that (sub)window
 */
void Fl_X::make(fltk3::Window* w)
{
  if ( w->parent() ) {		// create a subwindow
    fltk3::Group::current(0);
    // our subwindow needs this structure to know about its clipping. 
    Fl_X* x = new Fl_X;
    x->subwindow = true;
    x->other_xid = 0;
    x->region = 0;
    x->subRegion = 0;
    x->cursor = fl_default_cursor;
    x->gc = 0;			// stay 0 for Quickdraw; fill with CGContext for Quartz
    fltk3::Window *win = w->window();
    Fl_X *xo = Fl_X::i(win);
    if (xo) {
      x->xidNext = xo->xidChildren;
      x->xidChildren = 0L;
      xo->xidChildren = x;
      x->xid = win->i->xid;
      x->w = w; w->i = x;
      x->wait_for_expose = 0;
      {
	Fl_X *z = xo->next;	// we don't want a subwindow in Fl_X::first
	xo->next = x;
	x->next = z;
      }
      int old_event = fltk3::e_number;
      w->handle(fltk3::e_number = fltk3::SHOW);
      fltk3::e_number = old_event;
      w->redraw();		// force draw to happen
    }
    if (w->as_gl_window()) { // if creating a sub-GL-window
      while (win->window()) win = win->window();
      [Fl_X::i(win)->xid setContainsGLsubwindow:YES];
    }
    fl_show_iconic = 0;
  }
  else {			// create a desktop window
    fltk3::Group::current(0);
    fl_open_display();
    NSInteger winlevel = NSNormalWindowLevel;
    NSUInteger winstyle;
    if (w->border()) winstyle = NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask;
    else winstyle = NSBorderlessWindowMask;
    int xp = w->x();
    int yp = w->y();
    int wp = w->w();
    int hp = w->h();
    if (w->size_range_set) {
      if ( w->minh != w->maxh || w->minw != w->maxw) {
        winstyle |= NSResizableWindowMask;
      }
    } else {
      if (w->resizable()) {
        fltk3::Widget *o = w->resizable();
        int minw = o->w(); if (minw > 100) minw = 100;
        int minh = o->h(); if (minh > 100) minh = 100;
        w->size_range(w->w() - o->w() + minw, w->h() - o->h() + minh, 0, 0);
	winstyle |= NSResizableWindowMask;
      } else {
        w->size_range(w->w(), w->h(), w->w(), w->h());
      }
    }
    int xwm = xp, ywm = yp, bt, bx, by;
    
    if (!fake_X_wm(w, xwm, ywm, bt, bx, by)) {
      // menu windows and tooltips
      if (w->modal()||w->tooltip_window()) {
        winstyle = NSBorderlessWindowMask;
        winlevel = NSModalPanelWindowLevel;
      } else {
        winstyle = NSBorderlessWindowMask;
      }
    } else if (w->modal()) {
      winstyle &= ~NSMiniaturizableWindowMask;
      // winstyle &= ~(NSResizableWindowMask | NSMiniaturizableWindowMask);
      winlevel = NSModalPanelWindowLevel;
    }
    else if (w->non_modal()) {
      winlevel = NSFloatingWindowLevel;
    }
    
    if (by+bt) {
      wp += 2*bx;
      hp += 2*by+bt;
    }
    if (w->force_position()) {
      if (!fltk3::grab()) {
        xp = xwm; yp = ywm;
        w->x(xp);w->y(yp);
      }
      xp -= bx;
      yp -= by+bt;
    }
    
    if (w->non_modal() && Fl_X::first /*&& !fl_disable_transient_for*/) {
      // find some other window to be "transient for":
      fltk3::Window* w = Fl_X::first->w;
      while (w->parent()) w = w->window(); // todo: this code does not make any sense! (w!=w??)
    }
        
    Fl_X* x = new Fl_X;
    x->subwindow = false;
    x->other_xid = 0; // room for doublebuffering image map. On OS X this is only used by overlay windows
    x->region = 0;
    x->subRegion = 0;
    x->cursor = fl_default_cursor;
    x->xidChildren = 0;
    x->xidNext = 0;
    x->gc = 0;
	  
    NSRect crect;
    crect.origin.x = w->x(); 
    crect.origin.y = main_screen_height - (w->y() + w->h());
    crect.size.width=w->w(); 
    crect.size.height=w->h();
    FLWindow *cw = [[FLWindow alloc] initWithFl_W:w 
				      contentRect:crect  
					styleMask:winstyle];
    [cw setFrameOrigin:crect.origin];
    [cw setHasShadow:YES];
    [cw setAcceptsMouseMovedEvents:YES];
    x->xid = cw;
    x->w = w; w->i = x;
    x->wait_for_expose = 1;
    x->next = Fl_X::first;
    Fl_X::first = x;
    FLView *myview = [[FLView alloc] init];
    [cw setContentView:myview];
    [cw setLevel:winlevel];
    
    q_set_window_title(cw, w->label(), w->iconlabel());
    if (!w->force_position()) {
      if (w->modal()) {
        [cw center];
      } else if (w->non_modal()) {
        [cw center];
      } else {
        static NSPoint delta = NSZeroPoint;
        delta = [cw cascadeTopLeftFromPoint:delta];
      }
    }
    if(w->menu_window()) { // make menu windows slightly transparent
      [cw setAlphaValue:0.97];
    }
    // Install DnD handlers 
    [myview registerForDraggedTypes:[NSArray arrayWithObjects:
                                     NSStringPboardType,  NSFilenamesPboardType, nil]];
    if ( ! Fl_X::first->next ) {	
      // if this is the first window, we need to bring the application to the front
      ProcessSerialNumber psn = { 0, kCurrentProcess };
      SetFrontProcess( &psn );
    }
    
    if (w->size_range_set) w->size_range_();
    
    if ( w->border() || (!w->modal() && !w->tooltip_window()) ) {
      fltk3::Tooltip::enter(0);
    }
    w->set_visible();
    if ( w->border() || (!w->modal() && !w->tooltip_window()) ) fltk3::handle(fltk3::FOCUS, w);
    fltk3::first_window(w);
    [cw setDelegate:[NSApp delegate]];
    if (fl_show_iconic) { 
      fl_show_iconic = 0;
      [cw miniaturize:nil];
    } else {
      [cw makeKeyAndOrderFront:nil];
    }
    
    crect = [[cw contentView] frame];
    w->w(int(crect.size.width));
    w->h(int(crect.size.height));
    crect = [cw frame];
    w->x(int(crect.origin.x));
    w->y(int(main_screen_height - (crect.origin.y + w->h())));
    
    int old_event = fltk3::e_number;
    w->handle(fltk3::e_number = fltk3::SHOW);
    fltk3::e_number = old_event;
    
    if (w->modal()) { fltk3::modal_ = w; fl_fix_focus(); }
  }
}


/*
 * Tell the OS what window sizes we want to allow
 */
void fltk3::Window::size_range_() {
  int bx, by, bt;
  get_window_frame_sizes(bx, by, bt);
  size_range_set = 1;
  NSSize minSize = { minw, minh + bt };
  NSSize maxSize = { maxw?maxw:32000, maxh?maxh + bt:32000 };
  if (i && i->xid) {
    [i->xid setMinSize:minSize];
    [i->xid setMaxSize:maxSize];
  }
}


/*
 * returns pointer to the filename, or null if name ends with ':'
 */
const char *fltk3::filename_name( const char *name ) 
{
  const char *p, *q;
  if (!name) return (0);
  for ( p = q = name ; *p ; ) {
    if ( ( p[0] == ':' ) && ( p[1] == ':' ) ) {
      q = p+2;
      p++;
    }
    else if (p[0] == '/') {
      q = p + 1;
    }
    p++;
  }
  return q;
}


/*
 * set the window title bar name
 */
void fltk3::Window::label(const char *name, const char *mininame) {
  fltk3::Widget::label(name);
  iconlabel_ = mininame;
  if (shown() || i) {
    q_set_window_title(i->xid, name, mininame);
  }
}


/*
 * make a window visible
 */
void fltk3::Window::show() {
  image(fltk3::scheme_bg_);
  if (fltk3::scheme_bg_) {
    labeltype(fltk3::NORMAL_LABEL);
    align(fltk3::ALIGN_CENTER | fltk3::ALIGN_INSIDE | fltk3::ALIGN_CLIP);
  } else {
    labeltype(fltk3::NO_LABEL);
  }
  fltk3::Tooltip::exit(this);
  if (!shown() || !i) {
    Fl_X::make(this);
  } else {
    if ( !parent() ) {
      if ([i->xid isMiniaturized]) {
	i->w->redraw();
	[i->xid deminiaturize:nil];
      }
      if (!fl_capture) {
	[i->xid makeKeyAndOrderFront:nil];
      }
    }
  }
}


/*
 * resize a window
 */
void fltk3::Window::resize(int X,int Y,int W,int H) {
  if (W<=0) W = 1; // OS X does not like zero width windows
  if (H<=0) H = 1;
  int is_a_resize = (W != w() || H != h());
  //  printf("fltk3::Window::resize(X=%d, Y=%d, W=%d, H=%d), is_a_resize=%d, resize_from_system=%p, this=%p\n",
  //         X, Y, W, H, is_a_resize, resize_from_system, this);
  if (X != x() || Y != y()) set_flag(FORCE_POSITION);
  else if (!is_a_resize) {
    resize_from_system = 0;
    return;
    }
  if ( (resize_from_system!=this) && (!parent()) && shown()) {
    if (is_a_resize) {
      if (resizable()) {
        if (W<minw) minw = W; // user request for resize takes priority
        if (maxw && W>maxw) maxw = W; // over a previously set size_range
        if (H<minh) minh = H;
        if (maxh && H>maxh) maxh = H;
        size_range(minw, minh, maxw, maxh);
      } else {
        size_range(W, H, W, H);
      }
      int bx, by, bt;
      if ( ! this->border() ) bt = 0;
      else get_window_frame_sizes(bx, by, bt);
      NSRect dim;
      dim.origin.x = X;
      dim.origin.y = main_screen_height - (Y + H);
      dim.size.width = W;
      dim.size.height = H + bt;
      [i->xid setFrame:dim display:YES]; // calls windowDidResize
    } else {
      NSPoint pt; 
      pt.x = X; 
      pt.y = main_screen_height - (Y + h());
      [i->xid setFrameOrigin:pt]; // calls windowDidMove
    }
    return;
  }
  resize_from_system = 0;
  if (is_a_resize) {
    fltk3::Group::resize(X,Y,W,H);
    if (shown()) { 
      redraw(); 
    }
  } else {
    x(X); y(Y); 
  }
}


/*
 * make all drawing go into this window (called by subclass flush() impl.)
 */
void fltk3::Window::make_current() 
{
  Fl_X::q_release_context();
  fl_window = i->xid;
  current_ = this;
  
  int xp = 0, yp = 0;
  fltk3::Window *win = this;
  while ( win ) {
    if ( !win->window() )
      break;
    xp += win->x();
    yp += win->y();
    win = (fltk3::Window*)win->window();
  }
  
  NSView *current_focus = [NSView focusView]; 
  // sometimes current_focus is set to a non-FLTK view: don't touch that
  if ( [current_focus isKindOfClass:[FLView class]] ) [current_focus unlockFocus];
  [[i->xid contentView]  lockFocus];
  i->gc = (CGContextRef)[[NSGraphicsContext currentContext] graphicsPort];
  fl_gc = i->gc;
  fltk3::Region fl_window_region = XRectangleRegion(0,0,w(),h());
  if ( ! this->window() ) {
    for ( Fl_X *cx = i->xidChildren; cx; cx = cx->xidNext ) {	// clip-out all sub-windows
      fltk3::Window *cw = cx->w;
      fltk3::Region from = fl_window_region;
      fl_window_region = MacRegionMinusRect(from, cw->x(), cw->y(), cw->w(), cw->h() );
      XDestroyRegion(from);
    }
  }
  
  // antialiasing must be deactivated because it applies to rectangles too
  // and escapes even clipping!!!
  // it gets activated when needed (e.g., draw text)
  CGContextSetShouldAntialias(fl_gc, false);  
  CGFloat hgt = [[fl_window contentView] frame].size.height;
  CGContextTranslateCTM(fl_gc, 0.5, hgt-0.5f);
  CGContextScaleCTM(fl_gc, 1.0f, -1.0f); // now 0,0 is top-left point of the window
  win = this;
  while(win && win->window()) { // translate to subwindow origin if this is a subwindow context
    CGContextTranslateCTM(fl_gc, win->x(), win->y());
    win = win->window();
  }
  //apply window's clip
  CGContextClipToRects(fl_gc, fl_window_region->rects, fl_window_region->count );
  XDestroyRegion(fl_window_region);
// this is the context with origin at top left of (sub)window clipped out of its subwindows if any
  CGContextSaveGState(fl_gc); 
#if defined(FLTK_USE_CAIRO)
  if (fltk3::cairo_autolink_context()) fltk3::cairo_make_current(this); // capture gc changes automatically to update the cairo context adequately
#endif
  fltk3::clip_region( 0 );
  
#if defined(FLTK_USE_CAIRO)
  // update the cairo_t context
  if (fltk3::cairo_autolink_context()) fltk3::cairo_make_current(this);
#endif
}

// helper function to manage the current CGContext fl_gc
extern void fl_quartz_restore_line_style_();

// FLTK has only one global graphics state. This function copies the FLTK state into the
// current Quartz context
void Fl_X::q_fill_context() {
  if (!fl_gc) return;
  if ( ! fl_window) { // a bitmap context
    size_t hgt = CGBitmapContextGetHeight(fl_gc);
    CGContextTranslateCTM(fl_gc, 0.5, hgt-0.5f);
    CGContextScaleCTM(fl_gc, 1.0f, -1.0f); // now 0,0 is top-left point of the context
    }
  fltk3::color(fltk3::graphics_driver->color());
  fl_quartz_restore_line_style_();
}

// The only way to reset clipping to its original state is to pop the current graphics
// state and restore the global state.
void Fl_X::q_clear_clipping() {
  if (!fl_gc) return;
  CGContextRestoreGState(fl_gc);
  CGContextSaveGState(fl_gc);
}

// Give the Quartz context back to the system
void Fl_X::q_release_context(Fl_X *x) {
  if (x && x->gc!=fl_gc) return;
  if (!fl_gc) return;
  CGContextRestoreGState(fl_gc); // matches the CGContextSaveGState of make_current
  fl_gc = 0;
#if defined(FLTK_USE_CAIRO)
  if (fltk3::cairo_autolink_context()) fltk3::cairo_make_current((fltk3::Window*) 0); // capture gc changes automatically to update the cairo context adequately
#endif
}

void Fl_X::q_begin_image(CGRect &rect, int cx, int cy, int w, int h) {
  CGContextSaveGState(fl_gc);
  CGRect r2 = rect;
  r2.origin.x -= 0.5f;
  r2.origin.y -= 0.5f;
  CGContextClipToRect(fl_gc, r2);
  // move graphics context to origin of vertically reversed image 
  CGContextTranslateCTM(fl_gc, rect.origin.x - cx - 0.5, rect.origin.y - cy + h - 0.5);
  CGContextScaleCTM(fl_gc, 1, -1);
  rect.origin.x = rect.origin.y = 0;
  rect.size.width = w;
  rect.size.height = h;
}

void Fl_X::q_end_image() {
  CGContextRestoreGState(fl_gc);
}


////////////////////////////////////////////////////////////////
// Copy & Paste fltk implementation.
////////////////////////////////////////////////////////////////

static void convert_crlf(char * s, size_t len)
{
  // turn all \r characters into \n:
  for (size_t x = 0; x < len; x++) if (s[x] == '\r') s[x] = '\n';
}

// fltk 1.3 clipboard support constant definitions:
const CFStringRef	flavorNames[] = {
  CFSTR("public.utf16-plain-text"), 
  CFSTR("public.utf8-plain-text"),
  CFSTR("com.apple.traditional-mac-plain-text") };
const CFStringEncoding encodings[] = { 
  kCFStringEncodingUnicode, 
  kCFStringEncodingUTF8, 
  kCFStringEncodingMacRoman};
const size_t handledFlavorsCount = sizeof(encodings)/sizeof(CFStringEncoding);

// clipboard variables definitions :
char *fl_selection_buffer[2];
int fl_selection_length[2];
static int fl_selection_buffer_length[2];

static PasteboardRef myPasteboard = 0;
static void allocatePasteboard() {
  if (!myPasteboard)
    PasteboardCreate(kPasteboardClipboard, &myPasteboard);
}


/*
 * create a selection
 * owner: widget that created the selection
 * stuff: pointer to selected data
 * size of selected data
 */
void fltk3::copy(const char *stuff, int len, int clipboard) {
  if (!stuff || len<0) return;
  if (len+1 > fl_selection_buffer_length[clipboard]) {
    delete[] fl_selection_buffer[clipboard];
    fl_selection_buffer[clipboard] = new char[len+100];
    fl_selection_buffer_length[clipboard] = len+100;
  }
  memcpy(fl_selection_buffer[clipboard], stuff, len);
  fl_selection_buffer[clipboard][len] = 0; // needed for direct paste
  fl_selection_length[clipboard] = len;
  if (clipboard) {
    allocatePasteboard();
    OSStatus err = PasteboardClear(myPasteboard);
    if (err!=noErr) return; // clear did not work, maybe not owner of clipboard.
    PasteboardSynchronize(myPasteboard);
    CFDataRef text = CFDataCreate(kCFAllocatorDefault, (UInt8*)fl_selection_buffer[1], len);
    if (text==NULL) return; // there was a pb creating the object, abort.
    err=PasteboardPutItemFlavor(myPasteboard, (PasteboardItemID)1, CFSTR("public.utf8-plain-text"), text, 0);
    CFRelease(text);
  }
}

// Call this when a "paste" operation happens:
void fltk3::paste(fltk3::Widget &receiver, int clipboard) {
  if (clipboard) {
    // see if we own the selection, if not go get it:
    fl_selection_length[1] = 0;
    OSStatus err = noErr;
    Boolean found = false;
    CFDataRef flavorData = NULL;
    CFStringEncoding encoding = 0;
    
    allocatePasteboard();
    PasteboardSynchronize(myPasteboard);
    ItemCount nFlavor = 0, i, j;
    err = PasteboardGetItemCount(myPasteboard, &nFlavor);
    if (err==noErr) {
      for (i=1; i<=nFlavor; i++) {
        PasteboardItemID itemID = 0;
        CFArrayRef flavorTypeArray = NULL;
        found = false;
        err = PasteboardGetItemIdentifier(myPasteboard, i, &itemID);
        if (err!=noErr) continue;
        err = PasteboardCopyItemFlavors(myPasteboard, itemID, &flavorTypeArray);
        if (err!=noErr) {
          if (flavorTypeArray) {CFRelease(flavorTypeArray); flavorTypeArray = NULL;}
          continue;
        }
        CFIndex flavorCount = CFArrayGetCount(flavorTypeArray);
        for (j = 0; j < handledFlavorsCount; j++) {
          for (CFIndex flavorIndex=0; flavorIndex<flavorCount; flavorIndex++) {
            CFStringRef flavorType = (CFStringRef)CFArrayGetValueAtIndex(flavorTypeArray, flavorIndex);
            if (UTTypeConformsTo(flavorType, flavorNames[j])) {
              err = PasteboardCopyItemFlavorData( myPasteboard, itemID, flavorNames[j], &flavorData );
              if (err != noErr) continue;
              encoding = encodings[j];
              found = true;
              break;
            }
          }
          if (found) break;
        }
        if (flavorTypeArray) {CFRelease(flavorTypeArray); flavorTypeArray = NULL;}
        if (found) break;
      }
      if (found) {
        CFIndex len = CFDataGetLength(flavorData);
        CFStringRef mycfs = CFStringCreateWithBytes(NULL, CFDataGetBytePtr(flavorData), len, encoding, false);
        CFRelease(flavorData);
        len = CFStringGetMaximumSizeForEncoding(CFStringGetLength(mycfs), kCFStringEncodingUTF8) + 1;
        if ( len >= fl_selection_buffer_length[1] ) {
          fl_selection_buffer_length[1] = len;
          delete[] fl_selection_buffer[1];
          fl_selection_buffer[1] = new char[len];
        }
        CFStringGetCString(mycfs, fl_selection_buffer[1], len, kCFStringEncodingUTF8);
        CFRelease(mycfs);
        len = strlen(fl_selection_buffer[1]);
        fl_selection_length[1] = len;
        convert_crlf(fl_selection_buffer[1],len); // turn all \r characters into \n:
      }
    }
  }
  fltk3::e_text = fl_selection_buffer[clipboard];
  fltk3::e_length = fl_selection_length[clipboard];
  if (!fltk3::e_text) fltk3::e_text = (char *)"";
  receiver.handle(fltk3::PASTE);
}

void fltk3::add_timeout(double time, fltk3::TimeoutHandler cb, void* data)
{
  // check, if this timer slot exists already
  for (int i = 0; i < mac_timer_used; ++i) {
    MacTimeout& t = mac_timers[i];
    // if so, simply change the fire interval
    if (t.callback == cb  &&  t.data == data) {
      CFRunLoopTimerSetNextFireDate(t.timer, CFAbsoluteTimeGetCurrent() + time );
      t.pending = 1;
      return;
    }
  }
  // no existing timer to use. Create a new one:
  int timer_id = -1;
  // find an empty slot in the timer array
  for (int i = 0; i < mac_timer_used; ++i) {
    if ( !mac_timers[i].timer ) {
      timer_id = i;
      break;
    }
  }
  // if there was no empty slot, append a new timer
  if (timer_id == -1) {
    // make space if needed
    if (mac_timer_used == mac_timer_alloc) {
      realloc_timers();
    }
    timer_id = mac_timer_used++;
  }
  // now install a brand new timer
  MacTimeout& t = mac_timers[timer_id];
  CFRunLoopTimerContext context = {0, data, NULL,NULL,NULL};
  CFRunLoopTimerRef timerRef = CFRunLoopTimerCreate(kCFAllocatorDefault, 
						    CFAbsoluteTimeGetCurrent() + time,
						    1E30,  
						    0,
						    0,
						    do_timer,
						    &context
						    );
  if (timerRef) {
    CFRunLoopAddTimer(CFRunLoopGetCurrent(),
		      timerRef,
		      kCFRunLoopDefaultMode);
    t.callback = cb;
    t.data     = data;
    t.timer    = timerRef;
    t.pending  = 1;
  }
}

void fltk3::repeat_timeout(double time, fltk3::TimeoutHandler cb, void* data)
{
  // currently, repeat_timeout does not subtract the trigger time of the previous timer event as it should.
  add_timeout(time, cb, data);
}

int fltk3::has_timeout(fltk3::TimeoutHandler cb, void* data)
{
  for (int i = 0; i < mac_timer_used; ++i) {
    MacTimeout& t = mac_timers[i];
    if (t.callback == cb  &&  t.data == data && t.pending) {
      return 1;
    }
  }
  return 0;
}

void fltk3::remove_timeout(fltk3::TimeoutHandler cb, void* data)
{
  for (int i = 0; i < mac_timer_used; ++i) {
    MacTimeout& t = mac_timers[i];
    if (t.callback == cb  && ( t.data == data || data == NULL)) {
      delete_timer(t);
    }
  }
}

int Fl_X::unlink(Fl_X *start) {
  if (start) {
    Fl_X *pc = start;
    while (pc) {
      if (pc->xidNext == this) {
        pc->xidNext = xidNext;
        return 1;
      }
      if (pc->xidChildren) {
        if (pc->xidChildren == this) {
          pc->xidChildren = xidNext;
          return 1;
        }
        if (unlink(pc->xidChildren))
          return 1;
      }
      pc = pc->xidNext;
    }
  } else {
    for ( Fl_X *pc = Fl_X::first; pc; pc = pc->next ) {
      if (unlink(pc))
        return 1;
    }
  }  
  return 0;
}

void Fl_X::relink(fltk3::Window *w, fltk3::Window *wp) {
  Fl_X *x = Fl_X::i(w);
  Fl_X *p = Fl_X::i(wp);
  if (!x || !p) return;
  // first, check if 'x' is already registered as a child of 'p'
  for (Fl_X *i = p->xidChildren; i; i=i->xidNext) {
    if (i == x) return;
  }
  // now add 'x' as the first child of 'p'
  x->xidNext = p->xidChildren;
  p->xidChildren = x;
}

void Fl_X::destroy() {
  // subwindows share their xid with their parent window, so should not close it
  if (!subwindow && w && !w->parent() && xid) {
    NSView *topview = [xid contentView]; 
    if ( [NSView focusView] == topview ) {
      [topview unlockFocus];
    }
    [topview release];
    [xid close];
  }
}

void Fl_X::map() {
  if (w && xid) {
    [xid orderFront:nil];
  }
  //+ link to window list
  if (w && w->parent()) {
    Fl_X::relink(w, w->window() );
    w->redraw();
  }
}

void Fl_X::unmap() {
  if (w && !w->parent() && xid) {
    [xid orderOut:nil];
  }
  if (w && Fl_X::i(w)) 
    Fl_X::i(w)->unlink();
}


// removes x,y,w,h rectangle from region r and returns result as a new fltk3::Region
static fltk3::Region MacRegionMinusRect(fltk3::Region r, int x,int y,int w,int h)
{
  fltk3::Region outr = (fltk3::Region)malloc(sizeof(*outr));
  outr->rects = (CGRect*)malloc(4 * r->count * sizeof(CGRect));
  outr->count = 0;
  CGRect rect = fl_cgrectmake_cocoa(x, y, w, h);
  for( int i = 0; i < r->count; i++) {
    CGRect A = r->rects[i];
    CGRect test = CGRectIntersection(A, rect);
    if (CGRectIsEmpty(test)) {
      outr->rects[(outr->count)++] = A;
    }
    else {
      const CGFloat verylarge = 100000.;
      CGRect side = CGRectMake(0,0,rect.origin.x,verylarge);// W side
      test = CGRectIntersection(A, side);
      if ( ! CGRectIsEmpty(test)) {
        outr->rects[(outr->count)++] = test;
      }
      side = CGRectMake(0,rect.origin.y + rect.size.height,verylarge,verylarge);// N side
      test = CGRectIntersection(A, side);
      if ( ! CGRectIsEmpty(test)) {
        outr->rects[(outr->count)++] = test;
      }
      side = CGRectMake(rect.origin.x + rect.size.width, 0, verylarge, verylarge);// E side
      test = CGRectIntersection(A, side);
      if ( ! CGRectIsEmpty(test)) {
        outr->rects[(outr->count)++] = test;
      }
      side = CGRectMake(0, 0, verylarge, rect.origin.y);// S side
      test = CGRectIntersection(A, side);
      if ( ! CGRectIsEmpty(test)) {
        outr->rects[(outr->count)++] = test;
      }
    }
  }
  if (outr->count == 0) {
    free(outr->rects);
    free(outr);
    outr = XRectangleRegion(0,0,0,0);
  }
  else outr->rects = (CGRect*)realloc(outr->rects, outr->count * sizeof(CGRect));
  return outr;
}

// intersects current and x,y,w,h rectangle and returns result as a new fltk3::Region
fltk3::Region Fl_X::intersect_region_and_rect(fltk3::Region current, int x,int y,int w, int h)
{
  if (current == NULL) return XRectangleRegion(x,y,w,h);
  CGRect r = fl_cgrectmake_cocoa(x, y, w, h);
  fltk3::Region outr = (fltk3::Region)malloc(sizeof(*outr));
  outr->count = current->count;
  outr->rects =(CGRect*)malloc(outr->count * sizeof(CGRect));
  int j = 0;
  for(int i = 0; i < current->count; i++) {
    CGRect test = CGRectIntersection(current->rects[i], r);
    if (!CGRectIsEmpty(test)) outr->rects[j++] = test;
  }
  if (j) {
    outr->count = j;
    outr->rects = (CGRect*)realloc(outr->rects, outr->count * sizeof(CGRect));
  }
  else {
    XDestroyRegion(outr);
    outr = XRectangleRegion(0,0,0,0);
  }
  return outr;
}

void Fl_X::collapse() {
  [xid miniaturize:nil];
}

static NSImage *CGBitmapContextToNSImage(CGContextRef c)
// the returned NSImage is autoreleased
{
  unsigned char *pdata = (unsigned char *)CGBitmapContextGetData(c);
  NSBitmapImageRep *imagerep = [[NSBitmapImageRep alloc] initWithBitmapDataPlanes:&pdata
                                                                       pixelsWide:CGBitmapContextGetWidth(c)
                                                                       pixelsHigh:CGBitmapContextGetHeight(c)
                                                                    bitsPerSample:8
                                                                  samplesPerPixel:4
                                                                         hasAlpha:YES
                                                                         isPlanar:NO
                                                                   colorSpaceName:NSDeviceRGBColorSpace
                                                                      bytesPerRow:CGBitmapContextGetBytesPerRow(c)
                                                                     bitsPerPixel:CGBitmapContextGetBitsPerPixel(c)];
  NSImage* image = [[NSImage alloc] initWithData: [imagerep TIFFRepresentation]];
  [imagerep release];
  return [image autorelease];
}

static NSCursor *PrepareCursor(NSCursor *cursor, CGContextRef (*f)() )
{
  if (cursor == nil) {
    CGContextRef c = f();
    NSImage *image = CGBitmapContextToNSImage(c);
    fl_delete_offscreen( (fltk3::Offscreen)c ); 
    NSPoint pt = {[image size].width/2, [image size].height/2};
    cursor = [[NSCursor alloc] initWithImage:image hotSpot:pt];
  }
  return cursor;
}

void Fl_X::set_cursor(fltk3::Cursor c)
{
  NSCursor *icrsr;
  switch (c) {
    case fltk3::CURSOR_CROSS:  icrsr = [NSCursor crosshairCursor]; break;
    case fltk3::CURSOR_WAIT:
      static NSCursor *watch = nil;
      watch = PrepareCursor(watch,  &Fl_X::watch_cursor_image);
      icrsr = watch;
      break;
    case fltk3::CURSOR_INSERT: icrsr = [NSCursor IBeamCursor]; break;
    case fltk3::CURSOR_N:      icrsr = [NSCursor resizeUpCursor]; break;
    case fltk3::CURSOR_S:      icrsr = [NSCursor resizeDownCursor]; break;
    case fltk3::CURSOR_NS:     icrsr = [NSCursor resizeUpDownCursor]; break;
    case fltk3::CURSOR_HELP:   
      static NSCursor *help = nil;
      help = PrepareCursor(help,  &Fl_X::help_cursor_image);
      icrsr = help;
      break;
    case fltk3::CURSOR_HAND:   icrsr = [NSCursor pointingHandCursor]; break;
    case fltk3::CURSOR_MOVE:   icrsr = [NSCursor openHandCursor]; break;
    case fltk3::CURSOR_NE:
    case fltk3::CURSOR_SW:
    case fltk3::CURSOR_NESW:   
      static NSCursor *nesw = nil;
      nesw = PrepareCursor(nesw,  &Fl_X::nesw_cursor_image);
      icrsr = nesw;
      break;
    case fltk3::CURSOR_E:      icrsr = [NSCursor resizeRightCursor]; break;
    case fltk3::CURSOR_W:      icrsr = [NSCursor resizeLeftCursor]; break;
    case fltk3::CURSOR_WE:     icrsr = [NSCursor resizeLeftRightCursor]; break;
    case fltk3::CURSOR_SE:
    case fltk3::CURSOR_NW:
    case fltk3::CURSOR_NWSE:   
      static NSCursor *nwse = nil;
      nwse = PrepareCursor(nwse,  &Fl_X::nwse_cursor_image);
      icrsr = nwse;
      break;
    case fltk3::CURSOR_NONE:   
      static NSCursor *none = nil;
      none = PrepareCursor(none,  &Fl_X::none_cursor_image);
      icrsr = none; 
      break;
    case fltk3::CURSOR_ARROW:
    case fltk3::CURSOR_DEFAULT:
    default:			   icrsr = [NSCursor arrowCursor];
      break;
  }
  [icrsr set];
  cursor = icrsr;
}

@interface FLaboutItemTarget : NSObject 
- (void)showPanel;
- (void)printPanel;
@end
@implementation FLaboutItemTarget
- (void)showPanel
{
  NSDictionary *options;
  options = [NSDictionary dictionaryWithObjectsAndKeys:
             [[[NSAttributedString alloc] 
               initWithString:[NSString stringWithFormat:@" GUI with FLTK %d.%d", 
                               FL_MAJOR_VERSION, FL_MINOR_VERSION ]] autorelease], @"Credits",
             nil];
  [NSApp orderFrontStandardAboutPanelWithOptions:options];
}
//#include <fltk3/PostScript.h>
- (void)printPanel
{
  fltk3::Printer printer;
  //fltk3::PostScriptFileDevice printer;
  int w, h, ww, wh;
  fltk3::Window *win = fltk3::first_window();
  if(!win) return;
  if( printer.start_job(1) ) return;
  if( printer.start_page() ) return;
  fl_lock_function();
  // scale the printer device so that the window fits on the page
  float scale = 1;
  printer.printable_rect(&w, &h);
  ww = win->decorated_w();
  wh = win->decorated_h();
  if (ww>w || wh>h) {
    scale = (float)w/win->w();
    if ((float)h/wh < scale) scale = (float)h/wh;
    printer.scale(scale);
    printer.printable_rect(&w, &h);
  }
//#define ROTATE 1
#ifdef ROTATE
  printer.scale(scale * 0.8, scale * 0.8);
  printer.printable_rect(&w, &h);
  printer.origin(w/2, h/2 );
  printer.rotate(20.);
#else
  printer.origin(w/2, h/2);
#endif
  printer.print_window( win, - ww/2, - wh/2 );
  printer.end_page();
  printer.end_job();
  fl_unlock_function();
}
@end

static void createAppleMenu(void)
{
  static BOOL donethat = NO;
  if (donethat) return;
  donethat = YES;
  NSMenu *mainmenu, *services, *appleMenu;
  NSMenuItem *menuItem;
  NSString *title;

  NSString *nsappname = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleName"];
  if (nsappname == nil)
    nsappname = [[NSProcessInfo processInfo] processName];
  appleMenu = [[NSMenu alloc] initWithTitle:@""];
  /* Add menu items */
  title = [[NSString stringWithUTF8String:Fl_Mac_App_Menu::about] stringByAppendingString:nsappname];
  menuItem = [appleMenu addItemWithTitle:title action:@selector(showPanel) keyEquivalent:@""];
  FLaboutItemTarget *about = [[FLaboutItemTarget alloc] init];
  [menuItem setTarget:about];
  [appleMenu addItem:[NSMenuItem separatorItem]];
  // Print front window
  if (strlen(Fl_Mac_App_Menu::print) > 0) {
    menuItem = [appleMenu 
		addItemWithTitle:[NSString stringWithUTF8String:Fl_Mac_App_Menu::print] 
		action:@selector(printPanel) 
		keyEquivalent:@""];
    [menuItem setTarget:about];
    [appleMenu setAutoenablesItems:NO];
    [menuItem setEnabled:YES];
    [appleMenu addItem:[NSMenuItem separatorItem]];
    }
  // Services Menu
  services = [[NSMenu alloc] init];
  menuItem = [appleMenu 
	      addItemWithTitle:[NSString stringWithUTF8String:Fl_Mac_App_Menu::services] 
	      action:nil 
	      keyEquivalent:@""];
  [appleMenu setSubmenu:services forItem:menuItem];
  [appleMenu addItem:[NSMenuItem separatorItem]];
  // Hide AppName
  title = [[NSString stringWithUTF8String:Fl_Mac_App_Menu::hide] stringByAppendingString:nsappname];
  [appleMenu addItemWithTitle:title 
		       action:@selector(hide:) 
		keyEquivalent:@"h"];
  // Hide Others
  menuItem = [appleMenu 
	      addItemWithTitle:[NSString stringWithUTF8String:Fl_Mac_App_Menu::hide_others] 
	      action:@selector(hideOtherApplications:) 
	      keyEquivalent:@"h"];
  [menuItem setKeyEquivalentModifierMask:(NSAlternateKeyMask|NSCommandKeyMask)];
  // Show All
  [appleMenu addItemWithTitle:[NSString stringWithUTF8String:Fl_Mac_App_Menu::show] 
		       action:@selector(unhideAllApplications:) keyEquivalent:@""];
  [appleMenu addItem:[NSMenuItem separatorItem]];
  // Quit AppName
  title = [[NSString stringWithUTF8String:Fl_Mac_App_Menu::quit] 
	   stringByAppendingString:nsappname];
  [appleMenu addItemWithTitle:title 
		       action:@selector(terminate:) 
		keyEquivalent:@"q"];
  /* Put menu into the menubar */
  menuItem = [[NSMenuItem alloc] initWithTitle:@"" action:nil keyEquivalent:@""];
  [menuItem setSubmenu:appleMenu];
  mainmenu = [[NSMenu alloc] initWithTitle:@""];
  [mainmenu addItem:menuItem];
  if (fl_mac_os_version < 100600) {
    //	[NSApp setAppleMenu:appleMenu];
    //	to avoid compiler warning raised by use of undocumented setAppleMenu	:
    [NSApp performSelector:@selector(setAppleMenu:) withObject:appleMenu];
  }
  [NSApp setServicesMenu:services];
  [NSApp setMainMenu:mainmenu];
  [services release];
  [mainmenu release];
  [appleMenu release];
  [menuItem release];
}


void Fl_X::set_key_window()
{
  [xid makeKeyWindow];
}

static NSImage *imageFromText(const char *text, int *pwidth, int *pheight)
{
  const char *p, *q;
  int width = 0, height, w2, ltext = strlen(text);
  fltk3::font(fltk3::HELVETICA, 10);
  p = text;
  int nl = 0;
  while((q=strchr(p, '\n')) != NULL) { 
    nl++; 
    w2 = int(fltk3::width(p, q - p));
    if (w2 > width) width = w2;
    p = q + 1; 
  }
  if (text[ ltext - 1] != '\n') {
    nl++;
    w2 = int(fltk3::width(p));
    if (w2 > width) width = w2;
  }
  height = nl * fltk3::height() + 3;
  width += 6;
  fltk3::Offscreen off = fl_create_offscreen_with_alpha(width, height);
  fl_begin_offscreen(off);
  CGContextSetRGBFillColor( (CGContextRef)off, 0,0,0,0);
  fltk3::rectf(0,0,width,height);
  fltk3::color(fltk3::BLACK);
  p = text;
  int y = fltk3::height();
  while(TRUE) {
    q = strchr(p, '\n');
    if (q) {
      fltk3::draw(p, q - p, 3, y);
    } else {
      fltk3::draw(p, 3, y);
      break;
    }
    y += fltk3::height();
    p = q + 1;
  }
  fl_end_offscreen();
  NSImage* image = CGBitmapContextToNSImage( (CGContextRef)off );
  fl_delete_offscreen( off );
  *pwidth = width;
  *pheight = height;
  return image;
}

static NSImage *defaultDragImage(int *pwidth, int *pheight)
{
  const int width = 16, height = 16;
  fltk3::Offscreen off = fl_create_offscreen_with_alpha(width, height);
  fl_begin_offscreen(off);
  CGContextSetRGBFillColor( (CGContextRef)off, 0,0,0,0);
  fltk3::rectf(0,0,width,height);
  CGContextSetRGBStrokeColor( (CGContextRef)off, 0,0,0,0.6);
  fltk3::rect(0,0,width,height);
  fltk3::rect(2,2,width-4,height-4);
  fl_end_offscreen();
  NSImage* image = CGBitmapContextToNSImage( (CGContextRef)off );
  fl_delete_offscreen( off );
  *pwidth = width;
  *pheight = height;
  return image;
}

int fltk3::dnd(void)
{
  CFDataRef text = CFDataCreate(kCFAllocatorDefault, (UInt8*)fl_selection_buffer[0], fl_selection_length[0]);
  if (text==NULL) return false;
  NSAutoreleasePool *localPool;
  localPool = [[NSAutoreleasePool alloc] init]; 
  NSPasteboard *mypasteboard = [NSPasteboard pasteboardWithName:NSDragPboard];
  [mypasteboard declareTypes:[NSArray arrayWithObjects:@"public.utf8-plain-text", nil] owner:nil];
  [mypasteboard setData:(NSData*)text forType:@"public.utf8-plain-text"];
  CFRelease(text);
  fltk3::Widget *w = fltk3::pushed();
  fltk3::Window *win = w->window();
  if (win == NULL) {
    win = (fltk3::Window*)w;
  } else { 
    while(win->window()) win = win->window();
  }
  NSView *myview = [Fl_X::i(win)->xid contentView];
  NSEvent *theEvent = [NSApp currentEvent];
  
  int width, height;
  NSImage *image;
  if ( dynamic_cast<fltk3::Input_*>(w) != NULL ||  dynamic_cast<fltk3::TextDisplay*>(w) != NULL) {
    fl_selection_buffer[0][ fl_selection_length[0] ] = 0;
    image = imageFromText(fl_selection_buffer[0], &width, &height);
  } else {
    image = defaultDragImage(&width, &height);
  }
  
  static NSSize offset={0,0};
  NSPoint pt = [theEvent locationInWindow];
  pt.x -= width/2;
  pt.y -= height/2;
  [myview dragImage:image  at:pt  offset:offset 
              event:theEvent  pasteboard:mypasteboard  
             source:myview  slideBack:YES];
  if ( w ) {
    int old_event = fltk3::e_number;
    w->handle(fltk3::e_number = fltk3::RELEASE);
    fltk3::e_number = old_event;
    fltk3::pushed( 0 );
  }
  [localPool release];
  return true;
}

unsigned char *Fl_X::bitmap_from_window_rect(fltk3::Window *win, int x, int y, int w, int h, int *bytesPerPixel)
// delete the returned pointer after use
{
  while(win->window()) {
    x += win->x();
    y += win->y();
    win = win->window();
  }
  CGFloat epsilon = 0;
  if (fl_mac_os_version >= 100600) epsilon = 0.001;
  // The epsilon offset is absolutely necessary under 10.6. Without it, the top pixel row and
  // left pixel column are not read, and bitmap is read shifted by one pixel in both directions. 
  // Under 10.5, we want no offset.
  NSRect rect = NSMakeRect(x - epsilon, y - epsilon, w, h);
  NSBitmapImageRep *bitmap = [[NSBitmapImageRep alloc] initWithFocusedViewRect:rect];
  *bytesPerPixel = [bitmap bitsPerPixel]/8;
  int bpp = (int)[bitmap bytesPerPlane];
  int bpr = (int)[bitmap bytesPerRow];
  int hh = bpp/bpr; // sometimes hh = h-1 for unclear reason
  int ww = bpr/(*bytesPerPixel); // sometimes ww = w-1
  unsigned char *data = new unsigned char[w * h *  *bytesPerPixel];
  if (w == ww) {
    memcpy(data, [bitmap bitmapData], w * hh *  *bytesPerPixel);
  } else {
    unsigned char *p = [bitmap bitmapData];
    unsigned char *q = data;
    for(int i = 0;i < hh; i++) {
      memcpy(q, p, *bytesPerPixel * ww);
      p += bpr;
      q += w * *bytesPerPixel;
      }
  }
  [bitmap release];
  return data;
}

static void imgProviderReleaseData (void *info, const void *data, size_t size)
{
  delete[] (unsigned char *)data;
}

CGImageRef Fl_X::CGImage_from_window_rect(fltk3::Window *win, int x, int y, int w, int h)
// CFRelease the returned CGImageRef after use
{
  int bpp;
  unsigned char *bitmap = bitmap_from_window_rect(win, x, y, w, h, &bpp);
  CGImageRef img;
  CGColorSpaceRef lut = CGColorSpaceCreateDeviceRGB();
  CGDataProviderRef provider = CGDataProviderCreateWithData(NULL, bitmap, w*h*bpp, imgProviderReleaseData);
  img = CGImageCreate(w, h, 8, 8*bpp, w*bpp, lut,
                      bpp == 3 ? kCGImageAlphaNone : kCGImageAlphaLast,
                      provider, NULL, false, kCGRenderingIntentDefault);
  CGColorSpaceRelease(lut);
  CGDataProviderRelease(provider);
  return img;
}

WindowRef Fl_X::window_ref()
{
  return (WindowRef)[xid windowRef];
}

// so a CGRect matches exactly what is denoted x,y,w,h for clipping purposes
CGRect fl_cgrectmake_cocoa(int x, int y, int w, int h) {
  return CGRectMake(x, y, w > 0 ? w - 0.9 : 0, h > 0 ? h - 0.9 : 0);
}

Window fl_xid(const fltk3::Window* w)
{
  Fl_X *temp = Fl_X::i(w);
  return temp ? temp->xid : 0;
}

int fltk3::Window::decorated_w()
{
  if (!shown() || parent() || !border() || !visible()) return w();
  int bx, by, bt;
  get_window_frame_sizes(bx, by, bt);
  return w() + 2 * bx;
}

int fltk3::Window::decorated_h()
{
  if (!shown() || parent() || !border() || !visible()) return h();
  int bx, by, bt;
  get_window_frame_sizes(bx, by, bt);
  return h() + bt + by;
}

void fltk3::PagedDevice::print_window(fltk3::Window *win, int x_offset, int y_offset)
{
  if (!win->shown() || win->parent() || !win->border() || !win->visible()) {
    this->print_widget(win, x_offset, y_offset);
    return;
  }
  int bx, by, bt;
  get_window_frame_sizes(bx, by, bt);
  fltk3::DisplayDevice::display_device()->set_current(); // send win to front and make it current
  win->show();
  fl_gc = NULL;
  fltk3::check();
  win->make_current();
  this->set_current(); // back to the fltk3::PagedDevice
  if (this->class_name() == fltk3::Printer::class_id) {
    // capture as transparent image the window title bar from screen
    CGImageRef img = Fl_X::CGImage_from_window_rect(win, 0, -bt, win->w(), bt);
    CGRect rect = { { x_offset, y_offset }, { win->w(), bt } }; // print the title bar
    Fl_X::q_begin_image(rect, 0, 0, win->w(), bt);
    CGContextDrawImage(fl_gc, rect, img);
    Fl_X::q_end_image();
    CGImageRelease(img);
  }
  else {
    // capture the window title bar from screen
    uchar *top_image = fltk3::read_image(NULL, 0, -bt, win->w(), bt);
    if (top_image) { // print the title bar
      fltk3::draw_image(top_image, x_offset, y_offset, win->w(), bt, 3);
      delete[] top_image;
    }
  }
  this->print_widget(win, x_offset, y_offset + bt); // print the window inner part
}

#include <dlfcn.h>

/* Returns the address of a Carbon function after dynamically loading the Carbon library if needed.
 Supports old Mac OS X versions that may use a couple of Carbon calls:
 GetKeys used by OS X 10.3 or before (in fltk3::get_key())
 PMSessionPageSetupDialog and PMSessionPrintDialog used by 10.4 or before (in fltk3::Printer::start_job())
 GetWindowPort used by 10.4 or before (in fltk3::GLChoice.cxx)
 */
void *Fl_X::get_carbon_function(const char *function_name) {
  static void *carbon = NULL;
  void *f = NULL;
  if (!carbon) {
    carbon = dlopen("/System/Library/Frameworks/Carbon.framework/Carbon", RTLD_LAZY);
  }
  if (carbon) {
    f = dlsym(carbon, function_name);
  }
  return f;
}
  
#endif // __APPLE__

//
// End of "$Id$".
//
