
import std.c.osx.carbon.types;
import std.c.osx.carbon.windowmanager;
import std.c.osx.carbon.cgcontext;
import std.c.osx.carbon.cfstring;

// deprecated: don't use!

extern (C) {

void SysBeep(short duration);

void SetWTitle(WindowRef, char*);
Rect * GetPortBounds (
   CGrafPtr port,
   Rect * rect
);

size_t CGBitmapContextGetHeight(CGContextRef c);

OSStatus QDBeginCGContext (
   CGrafPtr port,
   CGContextRef * contextPtr
);

OSStatus QDEndCGContext (
   CGrafPtr port,
   CGContextRef * contextPtr
);

void DiffRgn (
   RgnHandle srcRgnA,
   RgnHandle srcRgnB,
   RgnHandle dstRgn
);

void SetPortClipRegion (
   CGrafPtr port,
   RgnHandle clipRgn
);

RgnHandle NewRgn ();

void SetRectRgn (
   RgnHandle rgn,
   short left,
   short top,
   short right,
   short bottom
);

void UnionRgn (
   RgnHandle srcRgnA,
   RgnHandle srcRgnB,
   RgnHandle dstRgn
);

void DisposeRgn (
   RgnHandle rgn
);

}

//alias uint UInt32;
alias ushort UInt16;
alias ubyte Boolean;
alias uint FourCharCode;
alias ushort[16] Bits16;
  
//alias int OSStatus;
//alias int OSErr;
//alias uint WindowClass;
alias uint WindowAttributes;
alias void* Ptr;
//alias void* WindowRef;
alias void* MenuRef;
alias void* EventTargetRef;
alias void* EventHandlerCallRef;
alias void* EventHandlerRef;
alias void* EventQueueRef;
alias void* KeyboardLayoutRef;
//alias void* GrafPtr;
//alias void* GWorldPtr;
//alias void* CGContextRef;
alias double EventTime;
alias EventTime EventTimeout;
alias ushort EventMask;
alias ushort EventKind;
alias FourCharCode AEEventClass;
alias FourCharCode AEEventID;
alias FourCharCode ResType;
alias uint EventClass;
alias FourCharCode EventParamName;
alias FourCharCode EventParamType;
alias short WindowPartCode;
/+
alias void* ITabHandle;
alias void* SProcHndl;
alias void* CProcHndl;
alias void* PixMapHandle;
alias void* Handle;
struct GDevice {
   short           gdRefNum;
   short           gdID;
   short           gdType;
   ITabHandle      gdITable;
   short           gdResPref;
   SProcHndl       gdSearchProc;
   CProcHndl       gdCompProc;
   short           gdFlags;
   PixMapHandle    gdPMap;
   long            gdRefCon;
   GDHandle        gdNextGD;
   Rect            gdRect;
   long            gdMode;
   short           gdCCBytes;
   short           gdCCDepth;
   Handle          gdCCXData;
   Handle          gdCCXMask;
}
alias GDevice * GDPtr;
alias GDPtr * GDHandle;
+/
alias short MenuID;

alias void* AppleEventRef;

alias OSErr function(AppleEventRef, AppleEventRef, int) AEEventHandlerProcPtr;
alias OSStatus function(EventHandlerCallRef, EventRef, void*) EventHandlerProcPtr;

alias AEEventHandlerProcPtr AEEventHandlerUPP;

alias EventHandlerProcPtr EventHandlerUPP;

const int noErr = 0;
const int eventNotHandledErr = -9874;

struct BitMap {
   Ptr baseAddr;
   short rowBytes;
   Rect bounds;
};
alias BitMap* BitMapPtr;

//struct Point {
//   short    v;
//   short    h;
//};

/+struct CGSize {
   float width;
   float height;
};+/
//alias CGSize HISize;

struct Cursor {
   Bits16 data;
   Bits16 mask;
   Point hotSpot;
};
alias Cursor* CursPtr;
alias CursPtr* CursHandle;

struct ProcessSerialNumber {
   uint highLongOfPSN;
   uint lowLongOfPSN;
};

enum {
   kCoreEventClass = ('a'<<24)|('e'<<16)|('v'<<8)|'t'
};

enum {
   kEventParamWindowFeatures 		= ('w'<<24)|('f'<<16)|('t'<<8)|'r',
   kEventParamWindowDefPart 		= ('w'<<24)|('d'<<16)|('p'<<8)|'c',
   kEventParamWindowPartCode 		= ('w'<<24)|('p'<<16)|('a'<<8)|'r',
   kEventParamCurrentBounds 		= ('c'<<24)|('r'<<16)|('c'<<8)|'t',
   kEventParamOriginalBounds 		= ('o'<<24)|('r'<<16)|('c'<<8)|'t',
   kEventParamPreviousBounds 		= ('p'<<24)|('r'<<16)|('c'<<8)|'t',
   kEventParamClickActivation 		= ('c'<<24)|('l'<<16)|('a'<<8)|'c',
   kEventParamWindowRegionCode 		= ('w'<<24)|('s'<<16)|('h'<<8)|'p',
   kEventParamWindowDragHiliteFlag 	= ('w'<<24)|('d'<<16)|('h'<<8)|'f',
   kEventParamWindowModifiedFlag 	= ('w'<<24)|('m'<<16)|('f'<<8)|'f',
   kEventParamWindowProxyGWorldPtr 	= ('w'<<24)|('p'<<16)|('g'<<8)|'w',
   kEventParamWindowProxyImageRgn 	= ('w'<<24)|('p'<<16)|('i'<<8)|'r',
   kEventParamWindowProxyOutlineRgn 	= ('w'<<24)|('p'<<16)|('o'<<8)|'r',
   kEventParamWindowStateChangedFlags 	= ('w'<<24)|('s'<<16)|('c'<<8)|'f',
   kEventParamWindowTitleFullWidth 	= ('w'<<24)|('t'<<16)|('f'<<8)|'w',
   kEventParamWindowTitleTextWidth 	= ('w'<<24)|('t'<<16)|('t'<<8)|'w',
   kEventParamWindowGrowRect 		= ('g'<<24)|('r'<<16)|('c'<<8)|'t',
   kEventParamPreviousDockRect 		= ('p'<<24)|('d'<<16)|('r'<<8)|'c',
   kEventParamPreviousDockDevice 	= ('p'<<24)|('d'<<16)|('g'<<8)|'d',
   kEventParamCurrentDockRect 		= ('c'<<24)|('d'<<16)|('r'<<8)|'c',
   kEventParamCurrentDockDevice 	= ('c'<<24)|('d'<<16)|('g'<<8)|'d',
   kEventParamWindowTransitionAction 	= ('w'<<24)|('t'<<16)|('a'<<8)|'c',
   kEventParamWindowTransitionEffect 	= ('w'<<24)|('t'<<16)|('e'<<8)|'f',
   typeWindowRegionCode 		= ('w'<<24)|('s'<<16)|('h'<<8)|'p',
   typeWindowDefPartCode 		= ('w'<<24)|('d'<<16)|('p'<<8)|'t',
   typeClickActivationResult 		= ('c'<<24)|('l'<<16)|('a'<<8)|'c',
   typeWindowTransitionAction 		= ('w'<<24)|('t'<<16)|('a'<<8)|'c',
   typeWindowTransitionEffect 		= ('w'<<24)|('t'<<16)|('e'<<8)|'f'
};

enum {
   kAEOpenApplication            = ('o'<<24)|('a'<<16)|('p'<<8)|'p',
   kAEReopenApplication          = ('r'<<24)|('a'<<16)|('p'<<8)|'p',
   kAEOpenDocuments              = ('o'<<24)|('d'<<16)|('o'<<8)|'c',
   kAEPrintDocuments             = ('p'<<24)|('d'<<16)|('o'<<8)|'c',
   kAEOpenContents               = ('o'<<24)|('c'<<16)|('o'<<8)|'n',
   kAEQuitApplication            = ('q'<<24)|('u'<<16)|('i'<<8)|'t',
   kAEAnswer                     = ('a'<<24)|('n'<<16)|('s'<<8)|'r',
   kAEApplicationDied            = ('o'<<24)|('b'<<16)|('i'<<8)|'t',
   kAEShowPreferences            = ('p'<<24)|('r'<<16)|('e'<<8)|'f'
};

alias ushort EventMouseButton;
enum {
   kEventMouseButtonPrimary = 1,
   kEventMouseButtonSecondary = 2,
   kEventMouseButtonTertiary = 3
};

enum {
   kEventClassMouse 		= ('m'<<24)|('o'<<16)|('u'<<8)|'s',
   kEventClassKeyboard 		= ('k'<<24)|('e'<<16)|('y'<<8)|'b',
   kEventClassTextInput 	= ('t'<<24)|('e'<<16)|('x'<<8)|'t',
   kEventClassApplication 	= ('a'<<24)|('p'<<16)|('p'<<8)|'l',
   kEventClassAppleEvent 	= ('e'<<24)|('p'<<16)|('p'<<8)|'c',
   kEventClassMenu 		= ('m'<<24)|('e'<<16)|('n'<<8)|'u',
   kEventClassWindow 		= ('w'<<24)|('i'<<16)|('n'<<8)|'d',
   kEventClassControl 		= ('c'<<24)|('n'<<16)|('t'<<8)|'l',
   kEventClassCommand 		= ('c'<<24)|('m'<<16)|('d'<<8)|'s',
   kEventClassTablet 		= ('t'<<24)|('b'<<16)|('l'<<8)|'t',
   kEventClassVolume 		= ('v'<<24)|('o'<<16)|('l'<<8)|' ',
   kEventClassAppearance 	= ('a'<<24)|('p'<<16)|('p'<<8)|'m',
   kEventClassService 		= ('s'<<24)|('e'<<16)|('r'<<8)|'v',
   kEventClassToolbar 		= ('t'<<24)|('b'<<16)|('a'<<8)|'r',
   kEventClassToolbarItem 	= ('t'<<24)|('b'<<16)|('i'<<8)|'t',
   kEventClassToolbarItemView 	= ('t'<<24)|('b'<<16)|('i'<<8)|'v',
   kEventClassAccessibility 	= ('a'<<24)|('c'<<16)|('c'<<8)|'e',
   kEventClassSystem 		= ('m'<<24)|('a'<<16)|('c'<<8)|'s',
   kEventClassInk 		= ('i'<<24)|('n'<<16)|('k'<<8)|' ',
   kEventClassTSMDocumentAccess = ('t'<<24)|('d'<<16)|('a'<<8)|'c'
};

enum {
   kEventWindowUpdate = 1,
   kEventWindowDrawContent = 2
};

enum {
   kEventWindowActivated = 5,
   kEventWindowDeactivated = 6,
   kEventWindowHandleActivate = 91,
   kEventWindowHandleDeactivate = 92,
   kEventWindowGetClickActivation = 7,
   kEventWindowGetClickModality = 8
};

enum {
   kEventWindowClickDragRgn = 32,
   kEventWindowClickResizeRgn = 33,
   kEventWindowClickCollapseRgn = 34,
   kEventWindowClickCloseRgn = 35,
   kEventWindowClickZoomRgn = 36,
   kEventWindowClickContentRgn = 37,
   kEventWindowClickProxyIconRgn = 38,
   kEventWindowClickToolbarButtonRgn = 41,
   kEventWindowClickStructureRgn = 42
};

enum {
   kEventWindowShowing = 22,
   kEventWindowHiding = 23,
   kEventWindowShown = 24,
   kEventWindowHidden = 25,
   kEventWindowCollapsing = 86,
   kEventWindowCollapsed = 67,
   kEventWindowExpanding = 87,
   kEventWindowExpanded = 70,
   kEventWindowZoomed = 76,
   kEventWindowBoundsChanging = 26,
   kEventWindowBoundsChanged = 27,
   kEventWindowResizeStarted = 28,
   kEventWindowResizeCompleted = 29,
   kEventWindowDragStarted = 30,
   kEventWindowDragCompleted = 31,
   kEventWindowClosed = 73
};

enum {
   kEventWindowCollapse = 66,
   kEventWindowCollapseAll = 68,
   kEventWindowExpand = 69,
   kEventWindowExpandAll = 71,
   kEventWindowClose = 72,
   kEventWindowCloseAll = 74,
   kEventWindowZoom = 75,
   kEventWindowZoomAll = 77,
   kEventWindowContextualMenuSelect = 78,
   kEventWindowPathSelect = 79,
   kEventWindowGetIdealSize = 80,
   kEventWindowGetMinimumSize = 81,
   kEventWindowGetMaximumSize = 82,
   kEventWindowConstrain = 83,
   kEventWindowHandleContentClick = 85,
   kEventWindowTransitionStarted = 88,
   kEventWindowTransitionCompleted = 89,
   kEventWindowGetDockTileMenu = 90,
   kEventWindowProxyBeginDrag = 128,
   kEventWindowProxyEndDrag = 129,
   kEventWindowToolbarSwitchMode = 150
};

enum {
   kEventMouseDown = 1,
   kEventMouseUp = 2,
   kEventMouseMoved = 5,
   kEventMouseDragged = 6,
   kEventMouseEntered = 8,
   kEventMouseExited = 9,
   kEventMouseWheelMoved = 10
};

enum {
   kEventRawKeyDown = 1,
   kEventRawKeyRepeat = 2,
   kEventRawKeyUp = 3,
   kEventRawKeyModifiersChanged = 4,
   kEventHotKeyPressed = 5,
   kEventHotKeyReleased = 6
};

enum {
   nullEvent = 0,
   mouseDown = 1,
   mouseUp = 2,
   keyDown = 3,
   keyUp = 4,
   autoKey = 5,
   updateEvt = 6,
   diskEvt = 7,
   activateEvt = 8,
   osEvt = 15,
   kHighLevelEvent = 23
};

enum {
   kEventProcessCommand = 1,
   kEventCommandProcess = 1,
   kEventCommandUpdateStatus = 2
};

enum {
   mDownMask = 1 << mouseDown,
   mUpMask = 1 << mouseUp,
   keyDownMask = 1 << keyDown,
   keyUpMask = 1 << keyUp,
   autoKeyMask = 1 << autoKey,
   updateMask = 1 << updateEvt,
   diskMask = 1 << diskEvt,
   activMask = 1 << activateEvt,
   highLevelEventMask = 0x0400,
   osMask = 1 << osEvt,
   everyEvent = 0xFFFF
};
/+
enum {
   kAlertWindowClass = 1,
   kMovableAlertWindowClass = 2,
   kModalWindowClass = 3,
   kMovableModalWindowClass = 4,
   kFloatingWindowClass = 5,
   kDocumentWindowClass = 6,
   kUtilityWindowClass = 8,
   kHelpWindowClass = 10,
   kSheetWindowClass = 11,
   kToolbarWindowClass = 12,
   kPlainWindowClass = 13,
   kOverlayWindowClass = 14,
   kSheetAlertWindowClass = 15,
   kAltPlainWindowClass = 16,
   kDrawerWindowClass = 20,
   kAllWindowClasses = 0xFFFFFFFF
};

typedef UInt16 WindowRegionCode;
enum {
   kWindowTitleBarRgn = 0,
   kWindowTitleTextRgn = 1,
   kWindowCloseBoxRgn = 2,
   kWindowZoomBoxRgn = 3,
   kWindowDragRgn = 5,
   kWindowGrowRgn = 6,
   kWindowCollapseBoxRgn = 7,
   kWindowTitleProxyIconRgn = 8,
   kWindowStructureRgn = 32,
   kWindowContentRgn = 33,
   kWindowUpdateRgn = 34,
   kWindowOpaqueRgn = 35,
   kWindowGlobalPortRgn = 40,
   kWindowToolbarButtonRgn = 41
};

enum {
   kWindowNoAttributes = 0,
   kWindowCloseBoxAttribute = (1L << 0),
   kWindowHorizontalZoomAttribute = (1L << 1),
   kWindowVerticalZoomAttribute = (1L << 2),
   kWindowFullZoomAttribute = (kWindowVerticalZoomAttribute | kWindowHorizontalZoomAttribute),
   kWindowCollapseBoxAttribute = (1L << 3),
   kWindowResizableAttribute = (1L << 4),
   kWindowSideTitlebarAttribute = (1L << 5),
   kWindowToolbarButtonAttribute = (1L << 6),
   kWindowMetalAttribute = (1L << 8),
   kWindowNoTitleBarAttribute = (1L << 9),
   kWindowMetalNoContentSeparatorAttribute = (1L << 11),
   kWindowDoesNotCycleAttribute = (1L << 15),
   kWindowNoUpdatesAttribute = (1L << 16),
   kWindowNoActivatesAttribute = (1L << 17),
   kWindowOpaqueForEventsAttribute = (1L << 18),
   kWindowCompositingAttribute = (1L << 19),
   kWindowFrameworkScaledAttribute = (1L << 20),
   kWindowNoShadowAttribute = (1L << 21),
   kWindowAsyncDragAttribute = (1L << 23),
   kWindowHideOnSuspendAttribute = (1L << 24),
   kWindowStandardHandlerAttribute = (1L << 25),
   kWindowHideOnFullScreenAttribute = (1L << 26),
   kWindowInWindowMenuAttribute = (1L << 27),
   kWindowLiveResizeAttribute = (1L << 28),
   kWindowIgnoreClicksAttribute = (1L << 29),
   kWindowApplicationScaledAttribute = (1L << 30),
   kWindowNoConstrainAttribute = cast(uint)(1L << 31),
   kWindowStandardDocumentAttributes = (kWindowCloseBoxAttribute | kWindowFullZoomAttribute 
| kWindowCollapseBoxAttribute | kWindowResizableAttribute),
   kWindowStandardFloatingAttributes = (kWindowCloseBoxAttribute | kWindowCollapseBoxAttribute)
};

typedef UInt32 WindowPositionMethod;
enum {
   kWindowCenterOnMainScreen = 1,
   kWindowCenterOnParentWindow = 2,
   kWindowCenterOnParentWindowScreen = 3,
   kWindowCascadeOnMainScreen = 4,
   kWindowCascadeOnParentWindow = 5,
   kWindowCascadeOnParentWindowScreen = 6,
   kWindowCascadeStartAtParentWindowScreen = 10,
   kWindowAlertPositionOnMainScreen = 7,
   kWindowAlertPositionOnParentWindow = 8,
   kWindowAlertPositionOnParentWindowScreen = 9
};
+/
/+struct Rect {
   short    top;
   short    left;
   short    bottom;
   short    right;
};+/

struct EventTypeSpec {
   UInt32 eventClass;
   UInt32 eventKind;
};

/+
struct EventRecord {
   EventKind what;
   uint message;
   uint when;
   Point where;
   EventModifiers modifiers;
};
+/

enum {
   kEventParamMouseLocation 		= ('m'<<24)|('l'<<16)|('o'<<8)|'c',
   kEventParamWindowMouseLocation 	= ('w'<<24)|('m'<<16)|('o'<<8)|'u',
   kEventParamMouseButton 		= ('m'<<24)|('b'<<16)|('t'<<8)|'n',
   kEventParamClickCount 		= ('c'<<24)|('c'<<16)|('n'<<8)|'t',
   kEventParamMouseWheelAxis 		= ('m'<<24)|('w'<<16)|('a'<<8)|'x',
   kEventParamMouseWheelDelta 		= ('m'<<24)|('w'<<16)|('d'<<8)|'l',
   kEventParamMouseDelta 		= ('m'<<24)|('d'<<16)|('t'<<8)|'a',
   kEventParamMouseChord 		= ('c'<<24)|('h'<<16)|('o'<<8)|'r',
   kEventParamTabletEventType 		= ('t'<<24)|('b'<<16)|('l'<<8)|'t',
   kEventParamMouseTrackingRef 		= ('m'<<24)|('t'<<16)|('r'<<8)|'f',
   typeMouseButton 			= ('m'<<24)|('b'<<16)|('t'<<8)|'n',
   typeMouseWheelAxis 			= ('m'<<24)|('w'<<16)|('a'<<8)|'x',
   typeMouseTrackingRef 		= ('m'<<24)|('t'<<16)|('r'<<8)|'f'
};

enum {
  typePixelMap                  = ('c'<<24)|('p'<<16)|('i'<<8)|'x', /*  0x63706978  */
  typePixMapMinus               = ('t'<<24)|('p'<<16)|('m'<<8)|'m', /*  0x74706d6d  */
  typePolygon                   = ('c'<<24)|('p'<<16)|('g'<<8)|'n', /*  0x6370676e  */
  typePropInfo                  = ('p'<<24)|('i'<<16)|('n'<<8)|'f', /*  0x70696e66  */
  typePtr                       = ('p'<<24)|('t'<<16)|('r'<<8)|' ', /*  0x70747220  */
  typeQDPoint                   = ('Q'<<24)|('D'<<16)|('p'<<8)|'t', /*  0x51447074  */
  typeQDRegion                  = ('Q'<<24)|('r'<<16)|('g'<<8)|'n', /*  0x51447074  */
  typeRectangle                 = ('c'<<24)|('r'<<16)|('e'<<8)|'c', /*  0x63726563  */
  typeRGB16                     = ('t'<<24)|('r'<<16)|('1'<<8)|'6', /*  0x74723136  */
  typeRGB96                     = ('t'<<24)|('r'<<16)|('9'<<8)|'6', /*  0x74723936  */
  typeRGBColor                  = ('c'<<24)|('R'<<16)|('G'<<8)|'B', /*  0x63524742  */
  typeRotation                  = ('t'<<24)|('r'<<16)|('o'<<8)|'t', /*  0x74726f74  */
  typeRoundedRectangle          = ('c'<<24)|('r'<<16)|('r'<<8)|'c', /*  0x63727263  */
  typeRow                       = ('c'<<24)|('r'<<16)|('o'<<8)|'w', /*  0x63726f77  */
  typeScrapStyles               = ('s'<<24)|('t'<<16)|('y'<<8)|'l', /*  0x7374796c  */
  typeScript                    = ('s'<<24)|('c'<<16)|('p'<<8)|'t', /*  0x73637074  */
  typeStyledText                = ('S'<<24)|('T'<<16)|('X'<<8)|'T', /*  0x53545854  */
  typeSuiteInfo                 = ('s'<<24)|('u'<<16)|('i'<<8)|'n', /*  0x7375696e  */
  typeTable                     = ('c'<<24)|('t'<<16)|('b'<<8)|'l', /*  0x6374626c  */
  typeTextStyles                = ('t'<<24)|('s'<<16)|('t'<<8)|'y', /*  0x74737479  */
  typeBoolean                   = ('b'<<24)|('o'<<16)|('o'<<8)|'l',
  typeChar                      = ('T'<<24)|('E'<<16)|('X'<<8)|'T',
  typeSInt16                    = ('s'<<24)|('h'<<16)|('o'<<8)|'r',
  typeSInt32                    = ('l'<<24)|('o'<<16)|('n'<<8)|'g',
  typeUInt32                    = ('m'<<24)|('a'<<16)|('g'<<8)|'n',
  typeSInt64                    = ('c'<<24)|('o'<<16)|('m'<<8)|'p',
  typeIEEE32BitFloatingPoint    = ('s'<<24)|('i'<<16)|('n'<<8)|'g',
  typeIEEE64BitFloatingPoint    = ('d'<<24)|('o'<<16)|('u'<<8)|'b',
  type128BitFloatingPoint       = ('l'<<24)|('d'<<16)|('b'<<8)|'l',
  typeDecimalStruct             = ('d'<<24)|('e'<<16)|('c'<<8)|'m',
  typeAEList                    = ('l'<<24)|('i'<<16)|('s'<<8)|'t',
  typeAERecord                  = ('r'<<24)|('e'<<16)|('c'<<8)|'o',
  typeAppleEvent                = ('a'<<24)|('e'<<16)|('v'<<8)|'t',
  typeEventRecord               = ('e'<<24)|('v'<<16)|('r'<<8)|'c',
  typeTrue                      = ('t'<<24)|('r'<<16)|('u'<<8)|'e',
  typeFalse                     = ('f'<<24)|('a'<<16)|('l'<<8)|'s',
  typeAlias                     = ('a'<<24)|('l'<<16)|('i'<<8)|'s',
  typeEnumerated                = ('e'<<24)|('n'<<16)|('u'<<8)|'m',
  typeType                      = ('t'<<24)|('y'<<16)|('p'<<8)|'e',
  typeAppParameters             = ('a'<<24)|('p'<<16)|('p'<<8)|'a',
  typeProperty                  = ('p'<<24)|('r'<<16)|('o'<<8)|'p',
  typeFSS                       = ('f'<<24)|('s'<<16)|('s'<<8)|' ',
  typeFSRef                     = ('f'<<24)|('s'<<16)|('r'<<8)|'f',
  typeFileURL                   = ('f'<<24)|('u'<<16)|('r'<<8)|'l',
  typeKeyword                   = ('k'<<24)|('e'<<16)|('y'<<8)|'w',
  typeSectionH                  = ('s'<<24)|('e'<<16)|('c'<<8)|'t',
  typeWildCard                  = ('*'<<24)|('*'<<16)|('*'<<8)|'*',
  typeApplSignature             = ('s'<<24)|('i'<<16)|('g'<<8)|'n',
  typeQDRectangle               = ('q'<<24)|('d'<<16)|('r'<<8)|'t',
  typeFixed                     = ('f'<<24)|('i'<<16)|('x'<<8)|'d',
  typeProcessSerialNumber       = ('p'<<24)|('s'<<16)|('n'<<8)|' ',
  typeApplicationURL            = ('a'<<24)|('p'<<16)|('r'<<8)|'l',
  typeNull                      = ('n'<<24)|('u'<<16)|('l'<<8)|'l' /* null or nonexistent data */
};

/+
enum {
   inDesk = 0,
   inNoWindow = 0,
   inMenuBar = 1,
   inSysWindow = 2,
   inContent = 3,
   inDrag = 4,
   inGrow = 5,
   inGoAway = 6,
   inZoomIn = 7,
   inZoomOut = 8,
   inCollapseBox = 11,
   inProxyIcon = 12,
   inToolbarButton = 13,
   inStructure = 15
};
+/
enum {
   kEventKeyModifierNumLockBit = 16,
   kEventKeyModifierFnBit = 17
};

enum {
   kEventKeyModifierNumLockMask = 1L << kEventKeyModifierNumLockBit,
   kEventKeyModifierFnMask = 1L << kEventKeyModifierFnBit
};
enum {
   activeFlagBit = 0,
   btnStateBit = 7,
   cmdKeyBit = 8,
   shiftKeyBit = 9,
   alphaLockBit = 10,
   optionKeyBit = 11,
   controlKeyBit = 12,
   rightShiftKeyBit = 13,
   rightOptionKeyBit = 14,
   rightControlKeyBit = 15
};
typedef UInt16 EventModifiers;

enum {
   activeFlag = 1 << activeFlagBit,
   btnState = 1 << btnStateBit,
   cmdKey = 1 << cmdKeyBit,
   shiftKey = 1 << shiftKeyBit,
   alphaLock = 1 << alphaLockBit,
   optionKey = 1 << optionKeyBit,
   controlKey = 1 << controlKeyBit,
   rightShiftKey = 1 << rightShiftKeyBit,
   rightOptionKey = 1 << rightOptionKeyBit,
   rightControlKey = 1 << rightControlKeyBit
};

typedef UInt32 EventAttributes;
enum {
  kEventAttributeNone           = 0,
  kEventAttributeUserEvent      = 1 << 0,
  kEventAttributeMonitored      = 1 << 3
};

typedef SInt16 EventPriority;
enum {
  kEventPriorityLow             = 0,
  kEventPriorityStandard        = 1,
  kEventPriorityHigh            = 2
};

typedef UInt16 EventMouseWheelAxis;
enum {
  kEventMouseWheelAxisX         = 0,
  kEventMouseWheelAxisY         = 1
};

enum {
  kEventParamTSMSendRefCon      = ('t'<<24)|('s'<<16)|('r'<<8)|'c', /*    typeLongInteger*/
  kEventParamTSMSendComponentInstance = ('t'<<24)|('s'<<16)|('c'<<8)|'i' /*    typeComponentInstance*/
};

enum {
  typeSMInt                     = typeSInt16,
  typeShortInteger              = typeSInt16,
  typeInteger                   = typeSInt32,
  typeLongInteger               = typeSInt32,
  typeMagnitude                 = typeUInt32,
  typeComp                      = typeSInt64,
  typeSMFloat                   = typeIEEE32BitFloatingPoint,
  typeShortFloat                = typeIEEE32BitFloatingPoint,
  typeFloat                     = typeIEEE64BitFloatingPoint,
  typeLongFloat                 = typeIEEE64BitFloatingPoint,
  typeExtended                  = ('e'<<24)|('x'<<16)|('t'<<8)|'e'
};

enum {
  smVersion                     = 0,    /*Script Manager version number*/
  smMunged                      = 2,    /*Globals change count*/
  smEnabled                     = 4,    /*Count of enabled scripts, incl Roman*/
  smBidirect                    = 6,    /*At least one bidirectional script*/
  smFontForce                   = 8,    /*Force font flag*/
  smIntlForce                   = 10,   /*Force intl flag*/
  smForced                      = 12,   /*Script was forced to system script*/
  smDefault                     = 14,   /*Script was defaulted to Roman script*/
  smPrint                       = 16,   /*Printer action routine*/
  smSysScript                   = 18,   /*System script*/
  smLastScript                  = 20,   /*Last keyboard script*/
  smKeyScript                   = 22,   /*Keyboard script*/
  smSysRef                      = 24,   /*System folder refNum*/
  smKeyCache                    = 26,   /*obsolete*/
  smKeySwap                     = 28,   /*Swapping table handle*/
  smGenFlags                    = 30,   /*General flags long*/
  smOverride                    = 32,   /*Script override flags*/
  smCharPortion                 = 34,   /*Ch vs SpExtra proportion*/
                                        /* New for System 7.0: */
  smDoubleByte                  = 36,   /*Flag for double-byte script installed*/
  smKCHRCache                   = 38,   /*Returns pointer to KCHR cache*/
  smRegionCode                  = 40,   /*Returns current region code (verXxx)*/
  smKeyDisableState             = 42    /*Returns current keyboard disable state*/
};

enum {
  kEventParamKeyCode            = ('k'<<24)|('c'<<16)|('o'<<8)|'d', /* typeUInt32*/
  kEventParamKeyMacCharCodes    = ('k'<<24)|('c'<<16)|('h'<<8)|'r', /* typeChar*/
  kEventParamKeyModifiers       = ('k'<<24)|('m'<<16)|('o'<<8)|'d', /* typeUInt32*/
  kEventParamKeyUnicodes        = ('k'<<24)|('u'<<16)|('n'<<8)|'i', /* typeUnicodeText*/
  kEventParamKeyboardType       = ('k'<<24)|('b'<<16)|('d'<<8)|'t', /* typeUInt32*/
  typeEventHotKeyID             = ('h'<<24)|('k'<<16)|('i'<<8)|'d' /* EventHotKeyID*/
};

typedef UInt32 KeyboardLayoutPropertyTag;
enum {
  kKLKCHRData                   = 0,
  kKLuchrData                   = 1,
  kKLIdentifier                 = 2,
  kKLIcon                       = 3,
  kKLLocalizedName              = 4,
  kKLName                       = 5,
  kKLGroupIdentifier            = 6,
  kKLKind                       = 7,
  kKLLanguageCode               = 9
};



extern (C) {

void LocalToGlobal(Point * pt);
OSStatus KLGetCurrentKeyboardLayout(KeyboardLayoutRef * oKeyboardLayout);
OSStatus KLGetKeyboardLayoutProperty(
  KeyboardLayoutRef           iKeyboardLayout,
  KeyboardLayoutPropertyTag   iPropertyTag,
  void **               oValue);

Handle GetResource( ResType   theType, short     theID);
int GetScriptManagerVariable(short selector);
UInt32 
KeyTranslate(
  void *  transData,
  UInt16        keycode,
  UInt32 *      state);
/+
OSStatus CreateNewWindow (
   WindowClass windowClass,
   WindowAttributes attributes,
   Rect *contentBounds,
   WindowRef * outWindow
);
+/
//void ShowWindow ( WindowRef window);

/+OSStatus SetWindowResizeLimits (
   WindowRef inWindow,
   HISize* inMinLimits,
   HISize* inMaxLimits
);+/
EventQueueRef GetCurrentEventQueue();
OSStatus ReceiveNextEvent (
   UInt32 inNumTypes,
   EventTypeSpec * inList,
   EventTimeout inTimeout,
   Boolean inPullEvent,
   EventRef * outEvent
);

OSStatus PostEventToQueue( EventQueueRef   inQueue, EventRef        inEvent, EventPriority   inPriority);
void FlushEvents ( EventMask whichMask, EventMask stopMask);

void ReleaseEvent ( EventRef inEvent);

void MoreMasters();
void ClearMenuBar();
void DrawMenuBar();

void AppendResMenu (
   MenuRef theMenu,
   ResType theType
);

MenuRef GetMenuHandle (
   MenuID menuID
);

OSErr AEInstallEventHandler (
   AEEventClass theAEEventClass,
   AEEventID theAEEventID,
   AEEventHandlerUPP handler,
   long handlerRefcon,
   Boolean isSysHandler
);

OSStatus InstallEventHandler (
   EventTargetRef inTarget,
   EventHandlerUPP inHandler,
   uint inNumTypes,
   EventTypeSpec* inList,
   void* inUserData,
   EventHandlerRef* outRef
);

EventTargetRef GetWindowEventTarget ( WindowRef inWindow);
EventTargetRef GetApplicationEventTarget ();

OSStatus InstallWindowEventHandler( 
  WindowRef target, EventHandlerUPP handler, uint numTypes, 
  EventTypeSpec* list, void* userData, EventHandlerRef* outHandlerRef ) 
{
  return InstallEventHandler( 
    GetWindowEventTarget(target), handler, numTypes,
    list, userData, outHandlerRef);
}

OSStatus InstallApplicationEventHandler( 
  EventHandlerUPP handler, uint numTypes, 
  EventTypeSpec* list, void* userData, EventHandlerRef* outHandlerRef ) 
{
  return InstallEventHandler( 
    GetApplicationEventTarget(), handler, numTypes, 
    list, userData, outHandlerRef);
}

OSErr AEProcessAppleEvent ( EventRecord* theEventRecord);
AEEventHandlerUPP NewAEEventHandlerUPP ( AEEventHandlerProcPtr userRoutine);
EventHandlerUPP NewEventHandlerUPP ( EventHandlerProcPtr userRoutine);

uint GetEventClass ( EventRef inEvent);
uint GetEventKind ( EventRef inEvent);
void SetEventMask ( EventMask value);
EventTargetRef GetEventDispatcherTarget ();
OSStatus CallNextEventHandler ( EventHandlerCallRef inCallRef, EventRef inEvent);
OSStatus SendEventToEventTarget ( EventRef inEvent, EventTargetRef inTarget);
Boolean ConvertEventRefToEventRecord ( EventRef inEvent, EventRecord * outEvent);
OSStatus GetEventParameter (
   EventRef inEvent,
   EventParamName inName,
   EventParamType inDesiredType,
   EventParamType* outActualType,
   uint inBufferSize,
   uint* outActualSize,
   void* outData
);
OSStatus CreateEvent(
  CFAllocatorRef    inAllocator,        /* can be NULL */
  UInt32            inClassID,
  UInt32            inKind,
  EventTime         inWhen,
  EventAttributes   inAttributes,
  EventRef *        outEvent);

Cursor* GetQDGlobalsArrow ( Cursor* arrow);
//RgnHandle NewRgn ();
void GetMouse ( Point * mouseLoc);
//void SetRectRgn ( RgnHandle rgn, short left, short top, short right, short bottom);
//WindowPartCode FindWindow ( Point thePoint, WindowRef* window);

OSErr GetCurrentProcess ( ProcessSerialNumber * PSN);
OSErr SetFrontProcess ( ProcessSerialNumber * PSN);

int MenuSelect ( Point startPt);
//Boolean IsWindowActive ( WindowRef inWindow);
void GetPort ( GrafPtr * port);
void SetPort ( GrafPtr port);
//GrafPtr GetWindowPort ( WindowRef window);
void SetOrigin ( short h, short v);
void GlobalToLocal ( Point * pt);
//void DisposeRgn ( RgnHandle rgn);
//void DisposeWindow ( WindowRef window);
//void HideWindow ( WindowRef window);
GDHandle GetDeviceList ();
GDHandle GetNextDevice ( GDHandle curDevice);
GDHandle GetMainDevice ();
//OSStatus GetAvailableWindowPositioningBounds ( GDHandle inDevice, Rect * outAvailableRect);
BitMap * GetQDGlobalsScreenBits ( BitMap * screenBits);
//WindowAttributes GetAvailableWindowAttributes ( WindowClass inClass);
//void MoveWindow ( WindowRef window, short hGlobal, short vGlobal, Boolean front);
//OSStatus SetWindowClass ( WindowRef window, WindowClass inClass);
/+OSStatus RepositionWindow (
   WindowRef window,
   WindowRef parentWindow,
   WindowPositionMethod method
);+/
/+OSStatus GetWindowBounds (
   WindowRef window,
   WindowRegionCode regionCode,
   Rect * globalBounds
);+/
UInt32 GetCurrentKeyModifiers ();

}


