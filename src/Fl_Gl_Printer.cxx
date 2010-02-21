/*
 *  Fl_Gl_Printer.cxx
 */

#include "FL/Fl_Gl_Printer.H"
#include "Fl_Gl_Choice.H"
#ifndef __APPLE__
#include "FL/fl_draw.H"
#endif

void Fl_Gl_Printer::print_gl_window(Fl_Gl_Window *glw, int x, int y)
{
#ifdef WIN32
  HDC save_gc = fl_gc;
  const int bytesperpixel = 3;
#elif defined(__APPLE__)
  CGContextRef save_gc = fl_gc;
  const int bytesperpixel = 4;
#else
  _XGC *save_gc = fl_gc;		// FIXME Linux/Unix
  const int bytesperpixel = 3;
#endif
  glw->redraw();
  Fl::check();
  glw->make_current();
  // select front buffer as our source for pixel data
  glReadBuffer(GL_FRONT);
  // Read OpenGL context pixels directly.
  // For extra safety, save & restore OpenGL states that are changed
  glPushClientAttrib(GL_CLIENT_PIXEL_STORE_BIT);
  glPixelStorei(GL_PACK_ALIGNMENT, 4); /* Force 4-byte alignment */
  glPixelStorei(GL_PACK_ROW_LENGTH, 0);
  glPixelStorei(GL_PACK_SKIP_ROWS, 0);
  glPixelStorei(GL_PACK_SKIP_PIXELS, 0);
  // Read a block of pixels from the frame buffer
  int mByteWidth = glw->w() * bytesperpixel;                
  mByteWidth = (mByteWidth + 3) & ~3;    // Align to 4 bytes
  uchar *baseAddress = (uchar*)malloc(mByteWidth * glw->h());
  glReadPixels(0, 0, glw->w(), glw->h(), 
#ifdef WIN32
	       GL_RGB, GL_UNSIGNED_BYTE,
#elif defined(__APPLE__)
	       GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV,
#else // FIXME Linux/Unix
	       GL_RGB, GL_UNSIGNED_BYTE,
#endif
	       baseAddress);
  glPopClientAttrib();
  fl_gc = save_gc;
#ifdef WIN32
  fl_isprintcontext = true;
  fl_draw_image(baseAddress + (glw->h() - 1) * mByteWidth, x, y , glw->w(), glw->h(), bytesperpixel, - mByteWidth);
#elif defined(__APPLE__)
  CGColorSpaceRef cSpace = CGColorSpaceCreateWithName (kCGColorSpaceGenericRGB);  
  CGContextRef bitmap = CGBitmapContextCreate(baseAddress, glw->w(), glw->h(), 8, mByteWidth, cSpace,  
#if __BIG_ENDIAN__
	  kCGImageAlphaNoneSkipFirst | kCGBitmapByteOrder32Big /* XRGB Big Endian */);
#else
	  kCGImageAlphaNoneSkipFirst | kCGBitmapByteOrder32Little /* XRGB Little Endian */);
#endif
  if(bitmap == NULL) return;
  CFRelease(cSpace);
  // Make an image out of our bitmap
  CGImageRef image = CGBitmapContextCreateImage(bitmap);
  if(image == NULL) return;
  CFRelease(bitmap);
  CGContextSaveGState(fl_gc);
  int w, h;
  this->printable_rect(&w, &h);
  CGContextTranslateCTM(fl_gc, 0, h);
  CGContextScaleCTM(fl_gc, 1.0f, -1.0f);
  CGRect rect = { { x, h - y - glw->h() }, { glw->w(), glw->h() } };
  Fl_X::q_begin_image(rect, 0, 0, glw->w(), glw->h());
  CGContextDrawImage(fl_gc, rect, image);
  Fl_X::q_end_image();
  CGContextRestoreGState(fl_gc);
  CFRelease(image);
  free(baseAddress);
#else // FIXME Linux/Unix
  fl_draw_image(baseAddress + (glw->h() - 1) * mByteWidth, x, y , glw->w(), glw->h(), bytesperpixel, - mByteWidth);
#endif // WIN32
}
