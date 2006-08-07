
module std.c.osx.carbon.cfstring;

public import std.c.osx.carbon.types;


typedef void* CFAllocatorRef;
alias void* CFTypeRef;
typedef UInt32 CFStringEncoding;
typedef UInt32 ATSFontRef;
typedef OptionBits ATSOptionFlags;
alias float Float32;
typedef ushort UniChar;
alias UniChar* ConstUniCharArrayPtr;
alias UInt32 UniCharArrayOffset;
alias UInt32 UniCharCount;
typedef UInt32 FMFont;
alias FMFont ATSUFontID;
typedef UInt32 ByteCount;
typedef UInt32 ATSUAttributeTag;
alias void* ATSUAttributeValuePtr;
alias SInt32 Fixed;
typedef UInt32 ATSLineLayoutOptions;
alias Fixed ATSUTextMeasurement;

struct ATSFontMetrics {
  UInt32              versionno;
  Float32             ascent;
  Float32             descent;
  Float32             leading;
  Float32             avgAdvanceWidth;
  Float32             maxAdvanceWidth;
  Float32             minLeftSideBearing;
  Float32             minRightSideBearing;
  Float32             stemWidth;         
  Float32             stemHeight;       
  Float32             capHeight;   
  Float32             xHeight;
  Float32             italicAngle;
  Float32             underlinePosition;
  Float32             underlineThickness;
};

const CFStringEncoding kCFStringEncodingASCII = 0x0600;
const OptionBits kNilOptions = 0;
const ATSOptionFlags kATSOptionFlagsDefault = kNilOptions;
const UniCharArrayOffset kATSUFromTextBeginning = 0xffffffff;
const UniCharArrayOffset kATSUToTextEnd = 0xffffffff;
const UInt32 kATSUFontTag                  = 261;
const UInt32 kATSUSizeTag                  = 262;
const UInt32 kATSUFontMatrixTag            = 289;

enum {
  kATSLineNoLayoutOptions       = 0x00000000,
  kATSLineIsDisplayOnly         = 0x00000001, /* obsolete option*/
  kATSLineHasNoHangers          = 0x00000002,
  kATSLineHasNoOpticalAlignment = 0x00000004,
  kATSLineKeepSpacesOutOfMargin = 0x00000008,
  kATSLineNoSpecialJustification = 0x00000010,
  kATSLineLastNoJustification   = 0x00000020,
  kATSLineFractDisable          = 0x00000040,
  kATSLineImposeNoAngleForEnds  = 0x00000080,
  kATSLineFillOutToWidth        = 0x00000100,
  kATSLineTabAdjustEnabled      = 0x00000200,
  kATSLineIgnoreFontLeading     = 0x00000400,
  kATSLineApplyAntiAliasing     = 0x00000800,
  kATSLineNoAntiAliasing        = 0x00001000,
  kATSLineDisableNegativeJustification = 0x00002000,
  kATSLineDisableAutoAdjustDisplayPos = 0x00004000,
  kATSLineUseQDRendering        = 0x00008000,
  kATSLineDisableAllJustification = 0x00010000,
  kATSLineDisableAllGlyphMorphing = 0x00020000,
  kATSLineDisableAllKerningAdjustments = 0x00040000,
  kATSLineDisableAllBaselineAdjustments = 0x00080000,
  kATSLineDisableAllTrackingAdjustments = 0x00100000,
  kATSLineDisableAllLayoutOperations = kATSLineDisableAllJustification | kATSLineDisableAllGlyphMorphing 
    | kATSLineDisableAllKerningAdjustments | kATSLineDisableAllBaselineAdjustments 
    | kATSLineDisableAllTrackingAdjustments,
  kATSLineUseDeviceMetrics      = 0x01000000,
  kATSLineBreakToNearestCharacter = 0x02000000,
  kATSLineAppleReserved         = 0xFCE00000
};

enum {
  kATSULineLayoutOptionsTag     = 7L,
  kATSUCGContextTag             = 32767
};

static const Fixed fixed1 = 0x00010000;
Fixed  IntToFixed(int i)     { return cast(Fixed)(i<<16); }
float  FixedToFloat(Fixed i) { return (cast(float)(i))/fixed1; }
int    FixedToInt(Fixed a)   { return cast(int)((a+fixed1/2)>>16); }
Fixed  FloatToFixed(float a) { return cast(Fixed)(a*fixed1); }


extern (C) {

CFStringRef CFStringCreateWithCString(CFAllocatorRef alloc, char *cStr, CFStringEncoding encoding);
ATSFontRef ATSFontFindFromName(CFStringRef iName, ATSOptionFlags iOptions);
OSStatus ATSFontGetHorizontalMetrics(ATSFontRef iFont, ATSOptionFlags iOptions, ATSFontMetrics *oMetrics);
void CFRelease(CFTypeRef cf);
OSStatus ATSUCreateTextLayout(ATSUTextLayout * oTextLayout); 
OSStatus ATSUSetTextPointerLocation(
  ATSUTextLayout         iTextLayout, ConstUniCharArrayPtr   iText,
  UniCharArrayOffset     iTextOffset, UniCharCount           iTextLength,
  UniCharCount           iTextTotalLength);
OSStatus ATSUCreateStyle(ATSUStyle * oStyle);
OSStatus 
ATSUSetRunStyle(
  ATSUTextLayout       iTextLayout, ATSUStyle            iStyle,
  UniCharArrayOffset   iRunStart, UniCharCount         iRunLength);
FMFont FMGetFontFromATSFontRef(ATSFontRef iFont);
OSStatus 
ATSUSetAttributes(
  ATSUStyle                     iStyle,
  ItemCount                     iAttributeCount,
  ATSUAttributeTag        *iTag,
  ByteCount               *iValueSize,
  ATSUAttributeValuePtr   *iValue);
OSStatus ATSUSetLineControls(
  ATSUTextLayout                iTextLayout,
  UniCharArrayOffset            iLineStart,
  ItemCount                     iAttributeCount,
  ATSUAttributeTag        *iTag,
  ByteCount               *iValueSize,
  ATSUAttributeValuePtr   *iValue);
OSStatus 
ATSUGetUnjustifiedBounds(
  ATSUTextLayout         iTextLayout,
  UniCharArrayOffset     iLineStart,
  UniCharCount           iLineLength,
  ATSUTextMeasurement *  oTextBefore,
  ATSUTextMeasurement *  oTextAfter,
  ATSUTextMeasurement *  oAscent,
  ATSUTextMeasurement *  oDescent);
OSStatus ATSUDisposeTextLayout(ATSUTextLayout iTextLayout);
OSStatus ATSUDisposeStyle(ATSUStyle iStyle);
OSStatus 
ATSUSetLayoutControls(
  ATSUTextLayout                iTextLayout,
  ItemCount                     iAttributeCount,
  ATSUAttributeTag        *iTag,
  ByteCount               *iValueSize,
  ATSUAttributeValuePtr   *iValue);
OSStatus 
ATSUDrawText(
  ATSUTextLayout        iTextLayout,
  UniCharArrayOffset    iLineOffset,
  UniCharCount          iLineLength,
  ATSUTextMeasurement   iLocationX,
  ATSUTextMeasurement   iLocationY);

}

