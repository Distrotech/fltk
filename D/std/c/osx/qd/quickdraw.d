

module std.c.osx.qd.quickdraw;

private import std.c.osx.carbon.types;
private import std.c.osx.carbon.cgcontext;

extern (C) {

void CopyRgn(RgnHandle srcRgn, RgnHandle dstRgn) ;
void SectRgn(RgnHandle srcRgnA, RgnHandle srcRgnB, RgnHandle dstRgn);
void SetEmptyRgn(RgnHandle rgn);
Boolean RectInRgn(Rect *r, RgnHandle rgn);
Rect *GetRegionBounds(RgnHandle region, Rect *bounds);
OSStatus ClipCGContextToRegion(CGContextRef gc, Rect *portRect, RgnHandle region);
}

