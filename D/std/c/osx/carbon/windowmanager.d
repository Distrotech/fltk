
private import std.c.osx.carbon.types;

// ---- Constants

alias  UInt32 WindowClass;
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

alias UInt32 WindowAttributes;
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

enum {
   kWindowDocumentDefProcResID = 64,
   kWindowDialogDefProcResID = 65,
   kWindowUtilityDefProcResID = 66,
   kWindowUtilitySideTitleDefProcResID = 67,
   kWindowSheetDefProcResID = 68,
   kWindowSimpleDefProcResID = 69,
   kWindowSheetAlertDefProcResID = 70
};

enum {
   kWindowDocumentProc = 1024,
   kWindowGrowDocumentProc = 1025,
   kWindowVertZoomDocumentProc = 1026,
   kWindowVertZoomGrowDocumentProc = 1027,
   kWindowHorizZoomDocumentProc = 1028,
   kWindowHorizZoomGrowDocumentProc = 1029,
   kWindowFullZoomDocumentProc = 1030,
   kWindowFullZoomGrowDocumentProc = 1031
};

enum {
   kWindowPlainDialogProc = 1040,
   kWindowShadowDialogProc = 1041,
   kWindowModalDialogProc = 1042,
   kWindowMovableModalDialogProc = 1043,
   kWindowAlertProc = 1044,
   kWindowMovableAlertProc = 1045
};

enum {
   kWindowMovableModalGrowProc = 1046
};

enum {
   kWindowFloatProc = 1057,
   kWindowFloatGrowProc = 1059,
   kWindowFloatVertZoomProc = 1061,
   kWindowFloatVertZoomGrowProc = 1063,
   kWindowFloatHorizZoomProc = 1065,
   kWindowFloatHorizZoomGrowProc = 1067,
   kWindowFloatFullZoomProc = 1069,
   kWindowFloatFullZoomGrowProc = 1071
};

enum {
   kWindowFloatSideProc = 1073,
   kWindowFloatSideGrowProc = 1075,
   kWindowFloatSideVertZoomProc = 1077,
   kWindowFloatSideVertZoomGrowProc = 1079,
   kWindowFloatSideHorizZoomProc = 1081,
   kWindowFloatSideHorizZoomGrowProc = 1083,
   kWindowFloatSideFullZoomProc = 1085,
   kWindowFloatSideFullZoomGrowProc = 1087
};

enum {
   kWindowSheetProc = 1088,
   kWindowSheetAlertProc = 1120
};

enum {
   kWindowSimpleProc = 1104,
   kWindowSimpleFrameProc = 1105
};

enum {
   kWindowIsCollapsedState = (1 << 0L)
};

enum {
   kWindowCanGrow = (1 << 0),
   kWindowCanZoom = (1 << 1),
   kWindowCanCollapse = (1 << 2),
   kWindowIsModal = (1 << 3),
   kWindowCanGetWindowRegion = (1 << 4),
   kWindowIsAlert = (1 << 5),
   kWindowHasTitleBar = (1 << 6),
   kWindowSupportsDragHilite = (1 << 7),
   kWindowSupportsModifiedBit = (1 << 8),
   kWindowCanDrawInCurrentPort = (1 << 9),
   kWindowCanSetupProxyDragImage = (1 << 10),
   kWindowCanMeasureTitle = (1 << 11),
   kWindowWantsDisposeAtProcessDeath = (1 << 12),
   kWindowSupportsGetGrowImageRegion = (1 << 13),
   kWindowIsOpaque = (1 << 14),
   kWindowDefSupportsColorGrafPort = 0x40000002
};

typedef SInt16 WindowPartCode;
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

typedef UInt32 WindowModality;
enum {
   kWindowModalityNone = 0,
   kWindowModalitySystemModal = 1,
   kWindowModalityAppModal = 2,
   kWindowModalityWindowModal = 3
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

enum {
   kWindowNoPosition = 0x0000,
   kWindowDefaultPosition = 0x0000,
   kWindowCenterMainScreen = 0x280A,
   kWindowAlertPositionMainScreen = 0x300A,
   kWindowStaggerMainScreen = 0x380A,
   kWindowCenterParentWindow = 0xA80A,
   kWindowAlertPositionParentWindow = 0xB00A,
   kWindowStaggerParentWindow = 0xB80A,
   kWindowCenterParentWindowScreen = 0x680A,
   kWindowAlertPositionParentWindowScreen = 0x700A,
   kWindowStaggerParentWindowScreen = 0x780A
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

typedef UInt32 WindowLatentVisibility;
enum {
   kWindowLatentVisibleFloater = 1 << 0,
   kWindowLatentVisibleSuspend = 1 << 1,
   kWindowLatentVisibleFullScreen = 1 << 2,
   kWindowLatentVisibleAppHidden = 1 << 3,
   kWindowLatentVisibleCollapsedOwner = 1 << 4,
   kWindowLatentVisibleCollapsedGroup = 1 << 5
};

enum {
   kWindowDefinitionVersionOne = 1,
   kWindowDefinitionVersionTwo = 2
};

enum {
   kDocumentWindowVariantCode = 0,
   kModalDialogVariantCode = 1,
   kPlainDialogVariantCode = 2,
   kShadowDialogVariantCode = 3,
   kMovableModalDialogVariantCode = 5,
   kAlertVariantCode = 7,
   kMovableAlertVariantCode = 9,
   kSideFloaterVariantCode = 8
};

typedef UInt32 WindowTransitionAction;
enum {
   kWindowShowTransitionAction = 1,
   kWindowHideTransitionAction = 2,
   kWindowMoveTransitionAction = 3,
   kWindowResizeTransitionAction = 4
};

typedef UInt32 WindowTransitionEffect;
enum {
   kWindowZoomTransitionEffect = 1,
   kWindowSheetTransitionEffect = 2,
   kWindowSlideTransitionEffect = 3,
   kWindowFadeTransitionEffect = 4,
   kWindowGenieTransitionEffect = 5
};

typedef UInt32 WindowActivationScope;
enum {
   kWindowActivationScopeNone = 0,
   kWindowActivationScopeIndependent = 1,
   kWindowActivationScopeAll = 2
};

typedef UInt32 WindowConstrainOptions;
enum {
   kWindowConstrainMayResize = (1L << 0),
   kWindowConstrainMoveRegardlessOfFit = (1L << 1),
   kWindowConstrainAllowPartial = (1L << 2),
   kWindowConstrainCalcOnly = (1L << 3),
   kWindowConstrainUseTransitionWindow = (1L << 4),
   kWindowConstrainStandardOptions = kWindowConstrainMoveRegardlessOfFit
};

enum {
   dialogKind = 2,
   userKind = 8,
   kDialogWindowKind = 2,
   kApplicationWindowKind = 8
};

enum {
   kNextWindowGroup = true,
   kPreviousWindowGroup = false
};

typedef UInt32 WindowGroupAttributes;
enum {
   kWindowGroupAttrSelectAsLayer = 1 << 0,
   kWindowGroupAttrMoveTogether = 1 << 1,
   kWindowGroupAttrLayerTogether = 1 << 2,
   kWindowGroupAttrSharedActivation = 1 << 3,
   kWindowGroupAttrHideOnCollapse = 1 << 4,
   kWindowGroupAttrFixedLevel = 1 << 5
};

enum {
   kWindowGroupAttrSelectable = kWindowGroupAttrSelectAsLayer,
   kWindowGroupAttrPositionFixed = kWindowGroupAttrMoveTogether,
   kWindowGroupAttrZOrderFixed = kWindowGroupAttrLayerTogether
};

typedef UInt32 WindowGroupContentOptions;
enum {
   kWindowGroupContentsReturnWindows = 1 << 0,
   kWindowGroupContentsRecurse = 1 << 1,
   kWindowGroupContentsVisible = 1 << 2
};

enum {
   kFirstWindowOfClass = -1,
   kLastWindowOfClass = 0
};

typedef UInt32 WindowDefType;
enum {
   kWindowDefProcPtr = 0,
   kWindowDefObjectClass = 1,
   kWindowDefProcID = 2,
   kWindowDefHIView = 3
};

enum {
   kWindowDefProcType = ('W'<<24)|('D'<<16)|('E'<<8)|'F'
};

typedef SInt16 WindowDefPartCode;
enum {
   wNoHit = 0,
   wInContent = 1,
   wInDrag = 2,
   wInGrow = 3,
   wInGoAway = 4,
   wInZoomIn = 5,
   wInZoomOut = 6,
   wInCollapseBox = 9,
   wInProxyIcon = 10,
   wInToolbarButton = 11,
   wInStructure = 13
};

enum {
   kWindowMsgDraw = 0,
   kWindowMsgHitTest = 1,
   kWindowMsgCalculateShape = 2,
   kWindowMsgInitialize = 3,
   kWindowMsgCleanUp = 4,
   kWindowMsgDrawGrowOutline = 5,
   kWindowMsgDrawGrowBox = 6
};

enum {
   kWindowMsgGetFeatures = 7,
   kWindowMsgGetRegion = 8
};

enum {
   kWindowMsgDragHilite = 9,
   kWindowMsgModified = 10,
   kWindowMsgDrawInCurrentPort = 11,
   kWindowMsgSetupProxyDragImage = 12,
   kWindowMsgStateChanged = 13,
   kWindowMsgMeasureTitle = 14
};

enum {
   kWindowMsgGetGrowImageRegion = 19
};

typedef UInt32 WindowDrawerState;
enum {
   kWindowDrawerOpening = 1,
   kWindowDrawerOpen = 2,
   kWindowDrawerClosing = 3,
   kWindowDrawerClosed = 4
};

enum {
   kWindowEdgeDefault = 0,
   kWindowEdgeTop = 1 << 0,
   kWindowEdgeLeft = 1 << 1,
   kWindowEdgeBottom = 1 << 2,
   kWindowEdgeRight = 1 << 3
};

enum {
   kWindowMenuIncludeRotate = 1 << 0
};

typedef OptionBits WindowPaintProcOptions;
enum {
   kWindowPaintProcOptionsNone = 0
};

enum {
   wContentColor = 0,
   wFrameColor = 1,
   wTextColor = 2,
   wHiliteColor = 3,
   wTitleBarColor = 4
};

enum {
   deskPatID = 16
};

typedef UInt32 ScrollWindowOptions;
enum {
   kScrollWindowNoOptions = 0,
   kScrollWindowInvalidate = (1L << 0),
   kScrollWindowEraseToPortBackground = (1L << 1)
};

enum {
   kStoredWindowSystemTag 		= ('a'<<24)|('p'<<16)|('p'<<8)|'l',
   kStoredBasicWindowDescriptionID 	= ('s'<<24)|('b'<<16)|('a'<<8)|'s',
   kStoredWindowPascalTitleID 		= ('s'<<24)|('2'<<16)|('5'<<8)|'5',
   kStoredWindowTitleCFStringID 	= ('c'<<24)|('f'<<16)|('s'<<8)|'t'
};

enum {
   kStandardWindowDefinition = 0,
   kRoundWindowDefinition = 1,
   kFloatingWindowDefinition = 124
};

typedef OptionBits HIWindowAvailability;
enum {
   kHIWindowExposeHidden = 1 << 0
};

typedef UInt32 HIWindowScaleMode;
enum {
   kHIWindowScaleModeUnscaled = 0,
   kHIWindowScaleModeMagnified = 1,
   kHIWindowScaleModeFrameworkScaled = 2,
   kHIWinodwScaleModeApplicationScaled = 3
};

enum {
  kWindowGroupLevelActive = 1,
  kWindowGroupLevelInactive = 2,
  kWindowGroupLevelPromoted = 3,
};

// ---- Data Types

struct BasicWindowDescription {
   UInt32 descriptionSize;
   Rect windowContentRect;
   Rect windowZoomRect;
   UInt32 windowRefCon;
   UInt32 windowStateFlags;
   WindowPositionMethod windowPositionMethod;
   UInt32 windowDefinitionVersion;
   union windowDefinition {
     struct versionOne {
       SInt16 windowDefProc;
       Boolean windowHasCloseBox;
     };
     struct versionTwo {
       WindowClass windowClass;
       WindowAttributes windowAttributes;
     };
   };
};

alias GrafPtr CGrafPtr;

//typedef GDPtr * GDHandle;

alias CGrafPtr GWorldPtr;

struct GetGrowImageRegionRec {
   Rect growRect;
   RgnHandle growImageRegion;
};

struct GetWindowRegionRec {
   RgnHandle winRgn;
   WindowRegionCode regionCode;
};
typedef GetWindowRegionRec * GetWindowRegionPtr;

alias WindowRef HIWindowRef;

struct MeasureWindowTitleRec {
   SInt16 fullTitleWidth;
   SInt16 titleTextWidth;
   Boolean isUnicodeTitle;
   Boolean unused;
};
typedef MeasureWindowTitleRec * MeasureWindowTitleRecPtr;

alias OSType PropertyCreator;

alias OSType PropertyTag;

typedef PicPtr * PicPatHandle;

typedef PixPatPtr * PixPatHandle;

struct RGBColor {
   ushort red;
   ushort green;
   ushort blue;
};
typedef RGBColor * RGBColorPtr;

struct SetupWindowProxyDragImageRec {
   GWorldPtr imageGWorld;
   RgnHandle imageRgn;
   RgnHandle outlineRgn;
};

struct TransitionWindowOptions {
   UInt32 d_version;
   EventTime duration;
   WindowRef window;
   void * userData;
};

struct WindowDefSpec {
   WindowDefType defType;
   union u {
     WindowDefUPP defProc;
     void * classRef;
     short procID;
     void * rootView;
   };
};
typedef WindowDefSpec * WindowDefSpecPtr;

alias WindowDefProcPtr WindowDefUPP;

typedef void * WindowGroupRef;

alias WindowPaintProcPtr WindowPaintUPP;

typedef void * WindowPtr;

alias WindowPtr WindowRef;

struct WStateData {
   Rect userState;
   Rect stdState;
};
typedef WStateData * WStateDataPtr;

typedef long (*WindowDefProcPtr) (
   short varCode,
   WindowRef window,
   short message,
   long param
);

typedef OSStatus (*WindowPaintProcPtr)
(
   GDHandle device,
   GrafPtr qdContext,
   WindowRef window,
   RgnHandle inClientPaintRgn,
   RgnHandle outSystemPaintRgn,
   void * refCon
); 

// ---- Functions

extern (C) {

OSStatus ActivateWindow (
   WindowRef inWindow,
   Boolean inActivate
);

WindowRef ActiveNonFloatingWindow ();

Boolean AreFloatingWindowsVisible ();

void BeginUpdate (
   WindowRef window
);

OSStatus BeginWindowProxyDrag (
   WindowRef window,
   DragReference * outNewDrag,
   RgnHandle outDragOutlineRgn
);

void BringToFront (
   WindowRef window
);

OSStatus ChangeWindowAttributes (
   WindowRef window,
   WindowAttributes setTheseAttributes,
   WindowAttributes clearTheseAttributes
);

OSStatus ChangeWindowGroupAttributes (
   WindowGroupRef inGroup,
   WindowGroupAttributes setTheseAttributes,
   WindowGroupAttributes clearTheseAttributes
);

OSStatus ChangeWindowPropertyAttributes (
   WindowRef window,
   OSType propertyCreator,
   OSType propertyTag,
   UInt32 attributesToSet,
   UInt32 attributesToClear
);

OSStatus CloneWindow (
   WindowRef window
);

OSStatus CloseDrawer (
   WindowRef inDrawerWindow,
   Boolean inAsync
);

OSStatus CollapseAllWindows (
   Boolean collapse
);

OSStatus CollapseWindow (
   WindowRef window,
   Boolean collapse
);

OSStatus ConstrainWindowToScreen (
   WindowRef inWindowRef,
   WindowRegionCode inRegionCode,
   WindowConstrainOptions inOptions,
   Rect * inScreenRect,
   Rect * outStructure
);

OSStatus CopyWindowAlternateTitle (
   WindowRef inWindow,
   CFStringRef * outTitle
);

OSStatus CopyWindowGroupName (
   WindowGroupRef inGroup,
   CFStringRef * outName
);

OSStatus CopyWindowTitleAsCFString (
   WindowRef inWindow,
   CFStringRef * outString
);

ItemCount CountWindowGroupContents (
   WindowGroupRef inGroup,
   WindowGroupContentOptions inOptions
);

OSStatus CreateCustomWindow (
   WindowDefSpec * def,
   WindowClass windowClass,
   WindowAttributes attributes,
   Rect * contentBounds,
   WindowRef * outWindow
);

OSStatus CreateNewWindow (
   WindowClass windowClass,
   WindowAttributes attributes,
   Rect * contentBounds,
   WindowRef * outWindow
);

OSStatus CreateQDContextForCollapsedWindowDockTile (
   WindowRef inWindow,
   CGrafPtr * outContext
);

OSStatus CreateStandardWindowMenu (
   OptionBits inOptions,
   MenuRef * outMenu
);

OSStatus CreateWindowFromCollection (
   Collection collection,
   WindowRef * outWindow
);

OSStatus CreateWindowFromResource (
   SInt16 resID,
   WindowRef * outWindow
);

OSStatus CreateWindowGroup (
   WindowGroupAttributes inAttributes,
   WindowGroupRef * outGroup
);

void DebugPrintAllWindowGroups ();

void DebugPrintWindowGroup (
   WindowGroupRef inGroup
);

OSStatus DisableScreenUpdates ();

void DisposeWindow (
   WindowRef window
);

void DisposeWindowDefUPP (
   WindowDefUPP userUPP
);

void DisposeWindowPaintUPP (
   WindowPaintUPP userUPP
);

void DragWindow (
   WindowRef window,
   Point startPt,
   Rect * boundsRect
);

OSStatus EnableScreenUpdates ();

void EndUpdate (
   WindowRef window
);

OSStatus EndWindowProxyDrag (
   WindowRef window,
   DragReference theDrag
);

WindowPartCode FindWindow (
   Point thePoint,
   WindowRef * window
);

OSStatus FindWindowOfClass (
   Point * where,
   WindowClass inWindowClass,
   WindowRef * outWindow,
   WindowPartCode * outWindowPart
);

WindowRef FrontNonFloatingWindow ();

WindowRef FrontWindow ();

WindowAttributes GetAvailableWindowAttributes (
   WindowClass inClass
);

OSStatus GetAvailableWindowPositioningBounds (
   GDHandle inDevice,
   Rect * outAvailableRect
);

OSStatus GetAvailableWindowPositioningRegion (
   GDHandle inDevice,
   RgnHandle ioRgn
);

OptionBits GetDrawerCurrentEdge (
   WindowRef inDrawerWindow
);

OSStatus GetDrawerOffsets (
   WindowRef inDrawerWindow,
   float * outLeadingOffset,
   float * outTrailingOffset
);

WindowRef GetDrawerParent (
   WindowRef inDrawerWindow
);

OptionBits GetDrawerPreferredEdge (
   WindowRef inDrawerWindow
);

WindowDrawerState GetDrawerState (
   WindowRef inDrawerWindow
);

WindowRef GetFrontWindowOfClass (
   WindowClass inWindowClass,
   Boolean mustBeVisible
);

OSStatus GetIndexedWindow (
   WindowGroupRef inGroup,
   UInt32 inIndex,
   WindowGroupContentOptions inOptions,
   WindowRef * outWindow
);

WindowRef GetNextWindow (
   WindowRef window
);

WindowRef GetNextWindowOfClass (
   WindowRef inWindow,
   WindowClass inWindowClass,
   Boolean mustBeVisible
);

WindowRef GetPreviousWindow (
   WindowRef inWindow
);

OSStatus GetSheetWindowParent (
   WindowRef inSheet,
   WindowRef * outParentWindow
);

OSStatus GetWindowActivationScope (
   WindowRef inWindow,
   WindowActivationScope * outScope
);

OSStatus GetWindowAlpha (
   WindowRef inWindow,
   float * outAlpha
);

OSStatus GetWindowAttributes (
   WindowRef window,
   WindowAttributes * outAttributes
);

OSStatus GetWindowBounds (
   WindowRef window,
   WindowRegionCode regionCode,
   Rect * globalBounds
);

OSStatus GetWindowClass (
   WindowRef window,
   WindowClass * outClass
);

OSStatus GetWindowContentColor (
   WindowRef window,
   RGBColor * color
);

OSStatus GetWindowContentPattern (
   WindowRef window,
   PixPatHandle outPixPat
);

MenuRef GetWindowDockTileMenu (
   WindowRef inWindow
);

OSStatus GetWindowFeatures (
   WindowRef window,
   UInt32 * outFeatures
);

WindowRef GetWindowFromPort (
   CGrafPtr port
);

OSStatus GetWindowGreatestAreaDevice (
   WindowRef inWindow,
   WindowRegionCode inRegion,
   GDHandle * outGreatestDevice,
   Rect * outGreatestDeviceRect
);

WindowGroupRef GetWindowGroup (
   WindowRef inWindow
);

OSStatus GetWindowGroupAttributes (
   WindowGroupRef inGroup,
   WindowGroupAttributes * outAttributes
);

OSStatus GetWindowGroupContents (
   WindowGroupRef inGroup,
   WindowGroupContentOptions inOptions,
   ItemCount inAllowedItems,
   ItemCount * outNumItems,
   void ** outItems
);

OSStatus GetWindowGroupLevel (
   WindowGroupRef inGroup,
   SInt32 * outLevel
);

OSStatus GetWindowGroupLevel (
   WindowGroupRef inGroup,
   UInt32 * inLevelType,
   CGWindowLevel * outLevel
);

WindowGroupRef GetWindowGroupOfClass (
   WindowClass windowClass
);

WindowRef GetWindowGroupOwner (
   WindowGroupRef inGroup
);

WindowGroupRef GetWindowGroupParent (
   WindowGroupRef inGroup
);

ItemCount GetWindowGroupRetainCount (
   WindowGroupRef inGroup
);

WindowGroupRef GetWindowGroupSibling (
   WindowGroupRef inGroup,
   Boolean inNextGroup
);

OSStatus GetWindowIdealUserState (
   WindowRef inWindow,
   Rect * outUserState
);

OSStatus GetWindowIndex (
   WindowRef inWindow,
   WindowGroupRef inStartGroup,
   WindowGroupContentOptions inOptions,
   UInt32 * outIndex
);

short GetWindowKind (
   WindowRef window
);

OSStatus GetWindowModality (
   WindowRef inWindow,
   WindowModality * outModalKind,
   WindowRef * outUnavailableWindow
);

OSStatus GetWindowOwnerCount (
   WindowRef window,
   UInt32 * outCount
);

PicHandle GetWindowPic (
   WindowRef window
);

CGrafPtr GetWindowPort (
   WindowRef window
);

Rect * GetWindowPortBounds (
   WindowRef window,
   Rect * bounds
);

OSStatus GetWindowProperty (
   WindowRef window,
   PropertyCreator propertyCreator,
   PropertyTag propertyTag,
   UInt32 bufferSize,
   UInt32 * actualSize,
   void * propertyBuffer
);

OSStatus GetWindowPropertyAttributes (
   WindowRef window,
   OSType propertyCreator,
   OSType propertyTag,
   UInt32 * attributes
);

OSStatus GetWindowPropertySize (
   WindowRef window,
   PropertyCreator creator,
   PropertyTag tag,
   UInt32 * size
);

OSStatus GetWindowProxyAlias (
   WindowRef window,
   AliasHandle * d_alias
);

OSStatus GetWindowProxyIcon (
   WindowRef window,
   IconRef * outIcon
);

OSStatus GetWindowRegion (
   WindowRef window,
   WindowRegionCode inRegionCode,
   RgnHandle ioWinRgn
);

OSStatus GetWindowResizeLimits (
   WindowRef inWindow,
   HISize * outMinLimits,
   HISize * outMaxLimits
);

ItemCount GetWindowRetainCount (
   WindowRef inWindow
);

Rect * GetWindowStandardState (
   WindowRef window,
   Rect * rect
);

CGrafPtr GetWindowStructurePort (
   WindowRef inWindow
);

OSStatus GetWindowStructureWidths (
   WindowRef inWindow,
   Rect * outRect
);

OSStatus GetWindowToolbar (
   WindowRef inWindow,
   HIToolbarRef * outToolbar
);

Rect * GetWindowUserState (
   WindowRef window,
   Rect * rect
);

OSStatus GetWindowWidgetHilite (
   WindowRef inWindow,
   WindowDefPartCode * outHilite
);

long GetWRefCon (
   WindowRef window
);

OSStatus HideFloatingWindows ();

OSStatus HideSheetWindow (
   WindowRef inSheet
);

void HideWindow (
   WindowRef window
);

OSStatus HiliteWindowFrameForDrag (
   WindowRef window,
   Boolean hilited
);

OSStatus HIWindowChangeAvailability (
   HIWindowRef inWindow,
   HIWindowAvailability inSetAvailability,
   HIWindowAvailability inClearAvailability
);

OSStatus HIWindowChangeClass (
   WindowRef window,
   WindowClass inClass
);

OSStatus HIWindowChangeFeatures (
   HIWindowRef inWindow,
   UInt64 inSetThese,
   UInt64 inClearThese
);

OSStatus HIWindowFlush (
   WindowRef window
);

OSStatus HIWindowGetAvailability (
   HIWindowRef inWindow,
   HIWindowAvailability * outAvailability
);

OSStatus HIWindowGetProxyFSRef (
   WindowRef inWindow,
   FSRef * outRef
);

OSStatus HIWindowGetScaleMode (
   HIWindowRef inWindow,
   HIWindowScaleMode * outMode,
   float * outScaleFactor
);

OSStatus HIWindowInvalidateShadow (
   HIWindowRef inWindow
);

Boolean HIWindowIsDocumentModalTarget (
   HIWindowRef inWindow,
   HIWindowRef * outOwner
);

OSStatus HIWindowSetProxyFSRef (
   WindowRef inWindow,
   FSRef * inRef
);

OSStatus InstallWindowContentPaintProc (
   WindowRef window,
   WindowPaintUPP paintProc,
   WindowPaintProcOptions options,
   void * refCon
);

OSStatus InvalWindowRect (
   WindowRef window,
   Rect * bounds
);

OSStatus InvalWindowRgn (
   WindowRef window,
   RgnHandle region
);

long InvokeWindowDefUPP (
   short varCode,
   WindowRef window,
   short message,
   long param,
   WindowDefUPP userUPP
);

OSStatus InvokeWindowPaintUPP (
   GDHandle device,
   GrafPtr qdContext,
   WindowRef window,
   RgnHandle inClientPaintRgn,
   RgnHandle outSystemPaintRgn,
   void * refCon,
   WindowPaintUPP userUPP
);

Boolean IsValidWindowClass (
   WindowClass inClass
);

Boolean IsValidWindowPtr (
   WindowRef possibleWindow
);

Boolean IsWindowActive (
   WindowRef inWindow
);

Boolean IsWindowCollapsable (
   WindowRef window
);

Boolean IsWindowCollapsed (
   WindowRef window
);

Boolean IsWindowContainedInGroup (
   WindowRef inWindow,
   WindowGroupRef inGroup
);

Boolean IsWindowHilited (
   WindowRef window
);

Boolean IsWindowInStandardState (
   WindowRef inWindow,
   Point * inIdealSize,
   Rect * outIdealStandardState
);

Boolean IsWindowLatentVisible (
   WindowRef inWindow,
   WindowLatentVisibility * outLatentVisible
);

Boolean IsWindowModified (
   WindowRef window
);

Boolean IsWindowPathSelectClick (
   WindowRef window,
   EventRecord * event
);

Boolean IsWindowPathSelectEvent (
   WindowRef window,
   EventRef inEvent
);

Boolean IsWindowToolbarVisible (
   WindowRef inWindow
);

Boolean IsWindowUpdatePending (
   WindowRef window
);

Boolean IsWindowVisible (
   WindowRef window
);

void MoveWindow (
   WindowRef window,
   short hGlobal,
   short vGlobal,
   Boolean front
);

OSStatus MoveWindowStructure (
   WindowRef window,
   short hGlobal,
   short vGlobal
);

WindowDefUPP NewWindowDefUPP (
   WindowDefProcPtr userRoutine
);

WindowPaintUPP NewWindowPaintUPP (
   WindowPaintProcPtr userRoutine
);

OSStatus OpenDrawer (
   WindowRef inDrawerWindow,
   OptionBits inEdge,
   Boolean inAsync
);

long PinRect (
   Rect * theRect,
   Point thePt
);

OSStatus RegisterWindowDefinition (
   SInt16 inResID,
   WindowDefSpec * inDefSpec
);

OSStatus ReleaseQDContextForCollapsedWindowDockTile (
   WindowRef inWindow,
   CGrafPtr inContext
);

OSStatus ReleaseWindow (
   WindowRef inWindow
);

OSStatus ReleaseWindowGroup (
   WindowGroupRef inGroup
);

OSStatus RemoveWindowProperty (
   WindowRef window,
   PropertyCreator propertyCreator,
   PropertyTag propertyTag
);

OSStatus RemoveWindowProxy (
   WindowRef window
);

OSStatus RepositionWindow (
   WindowRef window,
   WindowRef parentWindow,
   WindowPositionMethod method
);

OSStatus ReshapeCustomWindow (
   WindowRef window
);

Boolean ResizeWindow (
   WindowRef inWindow,
   Point inStartPoint,
   Rect * inSizeConstraints,
   Rect * outNewContentRect
);

OSStatus RetainWindow (
   WindowRef inWindow
);

OSStatus RetainWindowGroup (
   WindowGroupRef inGroup
);

OSStatus ScrollWindowRect (
   WindowRef inWindow,
   Rect * inScrollRect,
   SInt16 inHPixels,
   SInt16 inVPixels,
   ScrollWindowOptions inOptions,
   RgnHandle outExposedRgn
);

OSStatus ScrollWindowRegion (
   WindowRef inWindow,
   RgnHandle inScrollRgn,
   SInt16 inHPixels,
   SInt16 inVPixels,
   ScrollWindowOptions inOptions,
   RgnHandle outExposedRgn
);

void SelectWindow (
   WindowRef window
);

void SendBehind (
   WindowRef window,
   WindowRef behindWindow
);

OSStatus SendWindowGroupBehind (
   WindowGroupRef inGroup,
   WindowGroupRef behindGroup
);

OSStatus SetDrawerOffsets (
   WindowRef inDrawerWindow,
   float inLeadingOffset,
   float inTrailingOffset
);

OSStatus SetDrawerParent (
   WindowRef inDrawerWindow,
   WindowRef inParent
);

OSStatus SetDrawerPreferredEdge (
   WindowRef inDrawerWindow,
   OptionBits inEdge
);

void SetPortWindowPort (
   WindowRef window
);

OSStatus SetThemeTextColorForWindow (
   WindowRef inWindow,
   Boolean inActive,
   SInt16 inDepth,
   Boolean inColorDev
);

OSStatus SetThemeWindowBackground (
   WindowRef inWindow,
   ThemeBrush inBrush,
   Boolean inUpdate
);

OSStatus SetWindowActivationScope (
   WindowRef inWindow,
   WindowActivationScope inScope
);

OSStatus SetWindowAlpha (
   WindowRef inWindow,
   float inAlpha
);

OSStatus SetWindowAlternateTitle (
   WindowRef inWindow,
   CFStringRef inTitle
);

OSStatus SetWindowBounds (
   WindowRef window,
   WindowRegionCode regionCode,
   Rect * globalBounds
);

OSStatus SetWindowClass (
   WindowRef window,
   WindowClass inClass
);

OSStatus SetWindowContentColor (
   WindowRef window,
   RGBColor * color
);

OSStatus SetWindowContentPattern (
   WindowRef window,
   PixPatHandle pixPat
);

OSStatus SetWindowDockTileMenu (
   WindowRef inWindow,
   MenuRef inMenu
);

OSStatus SetWindowGroup (
   WindowRef inWindow,
   WindowGroupRef inNewGroup
);

OSStatus SetWindowGroupLevel (
   WindowGroupRef inGroup,
   SInt32 inLevel
);

OSStatus SetWindowGroupLevelOfType (
   WindowGroupRef inGroup,
   UInt32 * inLevelType,
   CGWindowLevel inLevel
);

OSStatus SetWindowGroupName (
   WindowGroupRef inGroup,
   CFStringRef inName
);

OSStatus SetWindowGroupOwner (
   WindowGroupRef inGroup,
   WindowRef inWindow
);

OSStatus SetWindowGroupParent (
   WindowGroupRef inGroup,
   WindowGroupRef inNewGroup
);

OSStatus SetWindowIdealUserState (
   WindowRef inWindow,
   Rect * inUserState
);

void SetWindowKind (
   WindowRef window,
   short kind
);

OSStatus SetWindowModality (
   WindowRef inWindow,
   WindowModality inModalKind,
   WindowRef inUnavailableWindow
);

OSStatus SetWindowModified (
   WindowRef window,
   Boolean modified
);

void SetWindowPic (
   WindowRef window,
   PicHandle pic
);

OSStatus SetWindowProperty (
   WindowRef window,
   PropertyCreator propertyCreator,
   PropertyTag propertyTag,
   UInt32 propertySize,
   void * propertyBuffer
);

OSStatus SetWindowProxyAlias (
   WindowRef inWindow,
   AliasHandle inAlias
);

OSStatus SetWindowProxyCreatorAndType (
   WindowRef window,
   OSType fileCreator,
   OSType fileType,
   SInt16 vRefNum
);

OSStatus SetWindowProxyIcon (
   WindowRef window,
   IconRef icon
);

OSStatus SetWindowResizeLimits (
   WindowRef inWindow,
   HISize * inMinLimits,
   HISize * inMaxLimits
);

void SetWindowStandardState (
   WindowRef window,
   Rect * rect
);

OSStatus SetWindowTitleWithCFString (
   WindowRef inWindow,
   CFStringRef inString
);

OSStatus SetWindowToolbar (
   WindowRef inWindow,
   HIToolbarRef inToolbar
);

void SetWindowUserState (
   WindowRef window,
   Rect * rect
);

void SetWRefCon (
   WindowRef window,
   long data
);

OSStatus ShowHideWindowToolbar (
   WindowRef inWindow,
   Boolean inShow,
   Boolean inAnimate
);

OSStatus ShowSheetWindow (
   WindowRef inSheet,
   WindowRef inParentWindow
);

void ShowWindow (
   WindowRef window
);

void SizeWindow (
   WindowRef window,
   short w,
   short h,
   Boolean fUpdate
);

OSStatus StoreWindowIntoCollection (
   WindowRef window,
   Collection collection
);

OSStatus ToggleDrawer (
   WindowRef inDrawerWindow
);

Boolean TrackBox (
   WindowRef window,
   Point thePt,
   WindowPartCode partCode
);

Boolean TrackGoAway (
   WindowRef window,
   Point thePt
);

OSStatus TrackWindowProxyDrag (
   WindowRef window,
   Point startPt
);

OSStatus TrackWindowProxyFromExistingDrag (
   WindowRef window,
   Point startPt,
   DragReference drag,
   RgnHandle inDragOutlineRgn
);

OSStatus TransitionWindow (
   WindowRef inWindow,
   WindowTransitionEffect inEffect,
   WindowTransitionAction inAction,
   Rect * inRect
);

OSStatus TransitionWindowAndParent (
   WindowRef inWindow,
   WindowRef inParentWindow,
   WindowTransitionEffect inEffect,
   WindowTransitionAction inAction,
   Rect * inRect
);

OSStatus TransitionWindowWithOptions (
   WindowRef inWindow,
   WindowTransitionEffect inEffect,
   WindowTransitionAction inAction,
   HIRect * inBounds,
   Boolean inAsync,
   TransitionWindowOptions * inOptions
);

OSStatus UpdateCollapsedWindowDockTile (
   WindowRef inWindow
);

OSStatus ValidWindowRect (
   WindowRef window,
   Rect * bounds
);

OSStatus ValidWindowRgn (
   WindowRef window,
   RgnHandle region
);

OSStatus WindowPathSelect (
   WindowRef window,
   MenuRef menu,
   SInt32 * outMenuResult
);

void ZoomWindow (
   WindowRef window,
   WindowPartCode partCode,
   Boolean front
);

OSStatus ZoomWindowIdeal (
   WindowRef inWindow,
   WindowPartCode inPartCode,
   Point * ioIdealSize
);

}

