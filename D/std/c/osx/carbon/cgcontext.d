
private import std.c.osx.carbon.types;
private import std.c.osx.carbon.cgpath;

// ---- Constants

enum CGBlendMode {
   kCGBlendModeNormal,
   kCGBlendModeMultiply,
   kCGBlendModeScreen,
   kCGBlendModeOverlay,
   kCGBlendModeDarken,
   kCGBlendModeLighten,
   kCGBlendModeColorDodge,
   kCGBlendModeColorBurn,
   kCGBlendModeSoftLight,
   kCGBlendModeHardLight,
   kCGBlendModeDifference,
   kCGBlendModeExclusion,
   kCGBlendModeHue,
   kCGBlendModeSaturation,
   kCGBlendModeColor,
   kCGBlendModeLuminosity 
};

enum CGInterpolationQuality {
   kCGInterpolationDefault,
   kCGInterpolationNone,
   kCGInterpolationLow,
   kCGInterpolationHigh
};

enum CGLineCap {
   kCGLineCapButt,
   kCGLineCapRound,
   kCGLineCapSquare
};

enum CGLineJoin {
   kCGLineJoinMiter,
   kCGLineJoinRound,
   kCGLineJoinBevel
};

enum CGTextDrawingMode {
   kCGTextFill,
   kCGTextStroke,
   kCGTextFillStroke,
   kCGTextInvisible,
   kCGTextFillClip,
   kCGTextStrokeClip,
   kCGTextFillStrokeClip,
   kCGTextClip
};

enum CGTextEncoding {
   kCGEncodingFontSpecific,
   kCGEncodingMacRoman
};

// ---- Data Types

typedef void* CGContext; // actually derived from CFTypeRef!
typedef CGContext* CGContextRef;

// ---- Functions

extern (C) {

void CGContextAddArc (
   CGContextRef context,
   float x,
   float y,
   float radius,
   float startAngle,
   float endAngle,
   int clockwise
);

void CGContextAddArcToPoint (
   CGContextRef context,
   float x1,
   float y1,
   float x2,
   float y2,
   float radius
);

void CGContextAddCurveToPoint (
   CGContextRef context,
   float cp1x,
   float cp1y,
   float cp2x,
   float cp2y,
   float x,
   float y
);

void CGContextAddEllipseInRect(
   CGContextRef context, 
   CGRect rect
);

void CGContextAddLines (
   CGContextRef context,
   CGPoint *points,
   size_t count
);

void CGContextAddLineToPoint (
   CGContextRef context,
   float x,
   float y
);

void CGContextAddPath (
  CGContextRef context,    
  CGPathRef path
);

void CGContextAddQuadCurveToPoint (
   CGContextRef context,
   float cpx,
   float cpy,
   float x,
   float y
);

void CGContextAddRect (
   CGContextRef context,
   CGRect rect
);

void CGContextAddRects (
   CGContextRef context,
   CGRect *rects,
   size_t count
);

void CGContextBeginPage (
   CGContextRef context,
   CGRect * mediaBox
);

void CGContextBeginPath (
   CGContextRef context
);

void CGContextBeginTransparencyLayer (
   CGContextRef context, 
   CFDictionaryRef auxiliaryInfo
);

void CGContextClearRect (
   CGContextRef context,
   CGRect rect
);

void CGContextClip (
   CGContextRef context
);

void CGContextClipToMask(
  CGContextRef c, 
  CGRect rect, 
  CGImageRef mask
);

void CGContextClipToRect (
   CGContextRef context,
   CGRect rect
);

void CGContextClipToRects (
   CGContextRef context,
   CGRect *rects,
   size_t count
);

void CGContextClosePath (
   CGContextRef context
);

void CGContextConcatCTM (
   CGContextRef context,
   CGAffineTransform transform
);

CGPoint CGContextConvertPointToDeviceSpace(
   CGContextRef c, 
   CGPoint point
);

CGPoint CGContextConvertPointToUserSpace(
   CGContextRef c, 
   CGPoint point
);

CGRect CGContextConvertRectToDeviceSpace(
   CGContextRef c, 
   CGRect rect
);

CGRect CGContextConvertRectToUserSpace(
   CGContextRef c, 
   CGRect rect
);

CGSize CGContextConvertSizeToDeviceSpace(
   CGContextRef c, 
   CGSize size
);

CGSize CGContextConvertSizeToUserSpace(
   CGContextRef c, 
   CGSize size
);

void CGContextDrawImage (
   CGContextRef context,
   CGRect rect,
   CGImageRef image
);

void CGContextDrawPath (
   CGContextRef context,
   CGPathDrawingMode mode
);

void CGContextDrawPDFDocument (
   CGContextRef context,
   CGRect rect,
   CGPDFDocumentRef document,
   int page
);

void CGContextDrawPDFPage (
   CGContextRef context, 
   CGPDFPageRef page
);

void CGContextDrawShading (
  CGContextRef context,
  CGShadingRef shading
);

void CGContextEndPage (
   CGContextRef context
);

void CGContextEndTransparencyLayer (
   CGContextRef context
);

void CGContextEOClip (
   CGContextRef context
);

void CGContextEOFillPath (
   CGContextRef context
);

void CGContextFillEllipseInRect(
   CGContextRef context, 
   CGRect rect
);

void CGContextFillPath (
   CGContextRef context
);

void CGContextFillRect (
   CGContextRef context,
   CGRect rect
);

void CGContextFillRects (
   CGContextRef context,
   CGRect *rects,
   size_t count
);

void CGContextFlush (
   CGContextRef context
);

CGRect CGContextGetClipBoundingBox (
   CGContextRef context
);

CGAffineTransform CGContextGetCTM (
   CGContextRef context
);

CGInterpolationQuality CGContextGetInterpolationQuality (
   CGContextRef context
);

CGRect CGContextGetPathBoundingBox (
   CGContextRef context
);

CGPoint CGContextGetPathCurrentPoint (
   CGContextRef context
);

CGAffineTransform CGContextGetTextMatrix (
   CGContextRef context
);

CGPoint CGContextGetTextPosition (
   CGContextRef context
);

CGAffineTransform CGContextGetUserSpaceToDeviceSpaceTransform(
   CGContextRef c
);

int CGContextIsPathEmpty (
   CGContextRef context
);

void CGContextMoveToPoint (
   CGContextRef context,
   float x,
   float y
);

bool CGContextPathContainsPoint(
   CGContextRef context, 
   CGPoint point, 
   CGPathDrawingMode mode
);

void CGContextRelease (
   CGContextRef context
);

void CGContextReplacePathWithStrokedPath(
   CGContextRef c 
);

void CGContextRestoreGState (
   CGContextRef context
);

CGContextRef CGContextRetain (
   CGContextRef context
);

void CGContextRotateCTM (
   CGContextRef context,
   float angle
);

void CGContextSaveGState (
   CGContextRef context
);

void CGContextScaleCTM (
   CGContextRef context,
   float sx,
   float sy
);

void CGContextSelectFont (
   CGContextRef context,
   char * name,
   float size,
   CGTextEncoding textEncoding
);

void CGContextSetAllowsAntialiasing(
   CGContextRef context, 
   bool allowsAntialiasing
);

void CGContextSetAlpha (
   CGContextRef context,
   float alpha
);

void CGContextSetBlendMode(
   CGContextRef context, 
   CGBlendMode mode
);

void CGContextSetCharacterSpacing (
   CGContextRef context,
   float spacing
);

void CGContextSetCMYKFillColor (
   CGContextRef context,
   float cyan,
   float magenta,
   float yellow,
   float black,
   float alpha
);

void CGContextSetCMYKStrokeColor (
   CGContextRef context,
   float cyan,
   float magenta,
   float yellow,
   float black,
   float alpha
);

void CGContextSetFillColor(
   CGContextRef context,
   float *components
);

void CGContextSetFillColorSpace (
   CGContextRef context,
   CGColorSpaceRef colorspace
);

void CGContextSetFillColorWithColor (
   CGContextRef context, 
   CGColorRef color
);

void CGContextSetFillPattern (
   CGContextRef context,
   CGPatternRef pattern,
   float *components
);

void CGContextSetFlatness (
   CGContextRef context,
   float flatness
);

void CGContextSetFont (
   CGContextRef context,
   CGFontRef font
);

void CGContextSetFontSize (
   CGContextRef context,
   float size
);

void CGContextSetGrayFillColor (
   CGContextRef context,
   float gray,
   float alpha
);

void CGContextSetGrayStrokeColor (
   CGContextRef context,
   float gray,
   float alpha
);

void CGContextSetInterpolationQuality (
   CGContextRef context, 
   CGInterpolationQuality quality
);

void CGContextSetLineCap (
   CGContextRef context,
   CGLineCap cap
);

void CGContextSetLineDash (
   CGContextRef context,
   float phase,
   float *lengths,
   size_t count
);

void CGContextSetLineJoin (
   CGContextRef context,
   CGLineJoin join
);

void CGContextSetLineWidth (
   CGContextRef context,
   float width
);

void CGContextSetMiterLimit (
   CGContextRef context,
   float limit
);

void CGContextSetPatternPhase (
  CGContextRef context,
  CGSize phase
);

void CGContextSetRenderingIntent (
   CGContextRef context,
   CGColorRenderingIntent intent
);

void CGContextSetRGBFillColor (
   CGContextRef context,
   float red,
   float green,
   float blue,
   float alpha
);

void CGContextSetRGBStrokeColor (
   CGContextRef context,
   float red,
   float green,
   float blue,
   float alpha
);

void CGContextSetShadow (
   CGContextRef context, 
   CGSize offset, 
   float blur
);

void CGContextSetShadowWithColor (
   CGContextRef context, 
   CGSize offset, 
   float blur, 
   CGColorRef color
);

void CGContextSetShouldAntialias (
   CGContextRef context,
   bool shouldAntialias
);

void CGContextSetShouldSmoothFonts (
  CGContextRef context,
  bool shouldSmoothFonts
);

void CGContextSetStrokeColor(
   CGContextRef context,
   float *components
);

void CGContextSetStrokeColorSpace (
   CGContextRef context,
   CGColorSpaceRef colorspace
);

void CGContextSetStrokeColorWithColor (
   CGContextRef context, 
   CGColorRef color
);

void CGContextSetStrokePattern (
   CGContextRef context,
   CGPatternRef pattern,
   float *components
);

void CGContextSetTextDrawingMode (
   CGContextRef context,
   CGTextDrawingMode mode
);

void CGContextSetTextMatrix (
   CGContextRef context,
   CGAffineTransform transform
);

void CGContextSetTextPosition (
   CGContextRef context,
   float x,
   float y
);

void CGContextShowGlyphs (
   CGContextRef context,
   CGGlyph *glyphs,
   size_t count
);

void CGContextShowGlyphsAtPoint (
   CGContextRef context,
   float x,
   float y,
   CGGlyph *glyphs,
   size_t count
);

void CGContextShowGlyphsWithAdvances (
   CGContextRef context, 
   CGGlyph *glyphs, 
   CGSize *advances, 
   size_t count
);

void CGContextShowText (
   CGContextRef context,
   char * bytes,
   size_t length
);

void CGContextShowTextAtPoint (
   CGContextRef context,
   float x,
   float y,
   char * bytes,
   size_t length
);

void CGContextStrokeEllipseInRect(
   CGContextRef context, 
   CGRect rect
);

void CGContextStrokePath (
   CGContextRef context
);

void CGContextStrokeRect (
   CGContextRef context,
   CGRect rect
);

void CGContextStrokeRectWithWidth (
   CGContextRef context,
   CGRect rect,
   float width
);

void CGContextSynchronize (
   CGContextRef context
);

void CGContextTranslateCTM (
   CGContextRef context,
   float tx,
   float ty
);

}

