
private import std.c.osx.carbon.types;

typedef void* CGPathRef;
typedef void* CGMuatblePathRef;

enum CGPathDrawingMode {
   kCGPathFill,
   kCGPathEOFill,
   kCGPathStroke,
   kCGPathFillStroke,
   kCGPathEOFillStroke
};


