//
// "$Id$"
//
// mac implementation of Fl_Clipboard_Writer class for the Fast Light Tool Kit (FLTK).
//
// Copyright 2010 by Bill Spitzak and others.
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
// Please report all bugs and problems to:
//
//     http://www.fltk.org/str.php
//

#ifdef __APPLE__

#include <FL/Fl_Clipboard_Writer.H>
#include <FL/x.H>
#include <FL/fl_draw.H>
#include <QuickTime/ImageCompression.h>

static size_t MyPutBytes (void* info, const void* buffer, size_t count)
{
  CFDataAppendBytes ((CFMutableDataRef) info, (const UInt8 *)buffer, count);
  return count;
}

int Fl_Clipboard_Writer::start(int w, int h)
{
  Fl_X::q_release_context();
  width = w;
  height = h;
  //prepare to draw in pdf context
  CGRect bounds = CGRectMake(0, 0, w, h );	
  pdfdata_ = CFDataCreateMutable(NULL, 0);
  CGDataConsumerRef myconsumer;
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
  if(CGDataConsumerCreateWithCFData != NULL) {
    myconsumer = CGDataConsumerCreateWithCFData (pdfdata_);
    }
  else
#endif
    {
    static CGDataConsumerCallbacks callbacks = { MyPutBytes, NULL };
    myconsumer = CGDataConsumerCreate ((void*) pdfdata_, &callbacks);
    }
  fl_gc = CGPDFContextCreate (myconsumer, &bounds, NULL);
  CGDataConsumerRelease (myconsumer);
  if (fl_gc == NULL) return 1;
  CGContextBeginPage (fl_gc, NULL);
  CGContextTranslateCTM(fl_gc, 0, h);
  CGContextScaleCTM(fl_gc, 1.0f, -1.0f);
  CGContextSaveGState(fl_gc);
  fl_window = (void *)1; // TODO: something better
  fl_clip_region(0);
  fl_line_style(FL_SOLID);
  gc = fl_gc;
  return 0;
}

int Fl_Clipboard_Writer::stop(void)
{
  int w, h;
  CGContextRestoreGState(fl_gc);
  // first, write the pdf data to the clipboard
  w = width; h = height;
  CGContextEndPage (fl_gc);
  CGContextRelease (fl_gc);
  PasteboardRef clipboard = NULL;
  PasteboardCreate (kPasteboardClipboard, &clipboard);
  PasteboardClear(clipboard);
  PasteboardPutItemFlavor (clipboard, (PasteboardItemID)1, 
			   CFSTR("com.adobe.pdf"), // kUTTypePDF
			   pdfdata_, kPasteboardFlavorNoFlags);
    
  // second, transform this PDF to a bitmap image and put it as PICT/tiff in clipboard
  CGDataProviderRef prov = CGDataProviderCreateWithData(NULL, CFDataGetBytePtr(pdfdata_), CFDataGetLength(pdfdata_), NULL);
  CGPDFDocumentRef pdfdoc = CGPDFDocumentCreateWithProvider(prov);
  CGDataProviderRelease(prov);
  CGColorSpaceRef space = CGColorSpaceCreateWithName(/*kCGColorSpaceGenericRGB*/ kCGColorSpaceUserRGB);
  const int scale = 2;
  w *= scale; h *= scale;
  void *mem = malloc(w * h * sizeof(int));
  fl_gc = CGBitmapContextCreate(mem, w, h, 8, w * 4, space, kCGImageAlphaPremultipliedFirst /*| kCGBitmapByteOrder32Host*/);
  CFRelease(space);
  if (fl_gc == NULL) { free(mem); return 1; }
  CGRect rect = CGRectMake(0, 0, w, h);
  CGContextSetRGBFillColor(fl_gc,  1,1,1,1);//need to clear background
  CGContextFillRect(fl_gc, rect);
  CGContextDrawPDFDocument(fl_gc, rect, pdfdoc, 1);
  CGPDFDocumentRelease(pdfdoc);
  CFRelease(pdfdata_);
#if MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_4
  if(CGImageDestinationCreateWithData != NULL) {
    CFMutableDataRef pictdata = CFDataCreateMutable(NULL, 0);
#if __LP64__
    CFStringRef  uti = CFSTR("public.tiff");
#else
    CFStringRef  uti = CFSTR("com.apple.pict");
#endif
    CGImageRef image = CGBitmapContextCreateImage(fl_gc);
    CGImageDestinationRef dest = CGImageDestinationCreateWithData(pictdata, uti, 1, NULL);
    CGImageDestinationAddImage(dest, image, NULL);
    CGImageDestinationFinalize(dest);
    CGImageRelease(image);
    CFRelease(dest);
#if !__LP64__
    CFRange range = CFRangeMake(0, 512);
    CFDataDeleteBytes(pictdata, range);// The PICT clipboard REQUIRES only the image data, not the header.
#endif
    PasteboardPutItemFlavor(clipboard, (PasteboardItemID)1, uti, pictdata, kPasteboardFlavorNoFlags );
    CFRelease (pictdata);
    }
  else
#endif
  { // other way for < 10.4 that uses QuickTime:
    GraphicsExportComponent exporter;
    OSErr err = OpenADefaultComponent(GraphicsExporterComponentType, /*kQTFileTypePicture*/ 'PICT', &exporter);
    err = GraphicsExportSetInputCGBitmapContext(exporter, fl_gc);
    Handle dataHandle = NewHandle(0);
    err = GraphicsExportSetOutputHandle(exporter, dataHandle);
    unsigned long size;
    err = GraphicsExportDoExport(exporter, &size);
    err = CloseComponent(exporter); 
    if(GetHandleSize(dataHandle) > 512) {
      HLock(dataHandle);
      // The clipboard REQUIRES only the image data, not the header.
      CFDataRef pictdata = CFDataCreate(NULL, (const UInt8 *)*dataHandle + 512, GetHandleSize(dataHandle) - 512);
      HUnlock(dataHandle);
      PasteboardPutItemFlavor(clipboard, (PasteboardItemID)1, 
			      CFSTR("com.apple.pict"),
			      pictdata,
			      kPasteboardFlavorNoFlags ); 
      CFRelease (pictdata);    
    }
    DisposeHandle(dataHandle);
  }
  CFRelease (clipboard);    
  CGContextRelease(fl_gc);
  fl_gc = NULL;
  free(mem);
  return 0;
}

void Fl_Clipboard_Writer::translate(int x, int y)
{
  CGContextSaveGState(fl_gc);
  CGContextTranslateCTM(fl_gc, x, y );
  CGContextSaveGState(fl_gc);
}

void Fl_Clipboard_Writer::untranslate(void)
{
  CGContextRestoreGState(fl_gc);
  CGContextRestoreGState(fl_gc);
}

#endif // __APPLE__

//
// End of "$Id$".
//
