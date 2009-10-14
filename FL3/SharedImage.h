//
// "$Id: Fl_Shared_Image.H 6614 2009-01-01 16:11:32Z matt $"
//
// Shared image header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2009 by Bill Spitzak and others.
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
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//

/* \file
 fltk::SharedImage class . */

#ifndef fltk3_shared_image_h
#define fltk3_shared_image_h

#include "../FL/Fl_Image.H"


// Test function for adding new formats
typedef Fl_Image *(*Fl_Shared_Handler)(const char *name, uchar *header,
                                       int headerlen);

namespace fltk {
  
  // Shared images class. 
  /**
   This class supports caching, loading,
   and drawing of image files. Most applications will also want to
   link against the fltk_images library and call the
   fltk::register_images()
   function to support standard image formats such as BMP, GIF, JPEG, and PNG.
   */
  class FL_EXPORT SharedImage : public ::Fl_Image {
  protected:
    
    static SharedImage **images_;	// Shared images
    static int	num_images_;		// Number of shared images
    static int	alloc_images_;		// Allocated shared images
    static Fl_Shared_Handler *handlers_;	// Additional format handlers
    static int	num_handlers_;		// Number of format handlers
    static int	alloc_handlers_;	// Allocated format handlers
    
    const char	*name_;			// Name of image file
    int		original_;		// Original image?
    int		refcount_;		// Number of times this image has been used
    Fl_Image	*image_;		// The image that is shared
    int		alloc_image_;		// Was the image allocated?
    
    static int	compare(SharedImage **i0, SharedImage **i1);
    
    // Use get() and release() to load/delete images in memory...
    SharedImage();
    SharedImage(const char *n, Fl_Image *img = 0);
    virtual ~SharedImage();
    void add();
    void update();
    
  public:
    /** Returns the filename of the shared image */
    const char	*name() { return name_; }
    /** Returns the number of references of this shared image. When reference is below 1, the image is deleted. */
    int		refcount() { return refcount_; }
    void		release();
    void		reload();
    
    virtual Fl_Image *copy(int W, int H);
    Fl_Image *copy() { return copy(w(), h()); }
    virtual void color_average(Fl_Color c, float i);
    virtual void desaturate();
    virtual void draw(int X, int Y, int W, int H, int cx, int cy);
    void draw(int X, int Y) { draw(X, Y, w(), h(), 0, 0); }
    virtual void uncache();
    
    static SharedImage *find(const char *n, int W = 0, int H = 0);
    static SharedImage *get(const char *n, int W = 0, int H = 0);
    static SharedImage **images();
    static int		num_images();
    static void		add_handler(Fl_Shared_Handler f);
    static void		remove_handler(Fl_Shared_Handler f);
  }; // class SharedImage
  
  //
  // The following function is provided in the fltk_images library and
  // registers all of the "extra" image file formats that are not part
  // of the core FLTK library...
  //
  
  FL_EXPORT extern void register_images();
  
}; // namespace fltk

#endif // !Fl_Shared_Image_H

//==============================================================================

/*! \class fltk::SharedImage
 
 Subclass of Image that can read a file or block of compressed data.
 This provides several useful functions:
 * Images are identified by filename. The static get() function will
 return an existing instance if it was called before with the same filename.
 The release() function will decrement the reference count and delete
 the image if nobody wants it any more.
 * An inline block of data may be provided that is the contents of the file,
 so the file does not have to exist and you can link the image directly
 into your program.
 * You may set a memory usage limit. If Image::mem_used() goes above
 this limit, it will call destroy() on least-recently-used images until
 it goes below this limit.
 * The get() function can determine the type of the file or block of
 data and create the correct subclass.
 
 */

#if 0

#include "Image.h"

namespace fltk {
  
  struct FL_IMAGES_API ImageType;
  
  
  class FL_API SharedImage : public Image {
    // fabien : introducing SharedImage handlers and uniform loading api inspired from 1.1.x
  public:
    /*! get an image of this name and dimensions , can be already loaded or not */
    static SharedImage *get(const char *n); // future impl. should care about W,H dims
    
    /*! a SharedImageHandler accepts handling a filename 
     by analizing its extension and/or eventually its header,
     if it handles it it returns a non null pointer on the loaded concrete image
     */
    /** fetch to the data/pixels unified buffer the image, return true if success. 
     this method() does NOT draw the image, it only prepares
     a generic buffer and its info, this method  should be used by all 
     non-progresive-reading read() methods so that we avoid redondant code
     */
    typedef SharedImage *(*Handler)(const char * filename, uchar *header, int headerlen);
    /*! adds a new handler for hanling a concrete type of image, typically one handler per image type should be registered */
    static void add_handler(Handler f);
    /*! removes a concrete handler */
    static void remove_handler(Handler f);
    
  private:
    static Handler *handlers_;		// Additional format handlers
    static int	num_handlers_;		// Number of format handlers
    static int	alloc_handlers_;	// Allocated format handlers
    
  protected:
    static const char* shared_image_root;
    
    static int image_used;
    static unsigned mem_usage_limit;
    
    SharedImage* l1;    // Left leaf in the binary tree
    SharedImage* l2;    // Right leaf in the binary tree
    const char* 	   name;  // Used to indentify the image, and as filename
    const uchar* datas; // If non zero, pointers on inlined compressed datas
    unsigned int     used;  // Last time used, for cache handling purpose
    int              refcount; // Number of time this image has been get
    
    SharedImage() { };  // Constructor is protected on purpose,
    // use the get function rather
    //~SharedImage();
    
    void find_less_used();
    static void check_mem_usage();
    
    /*! Return the filename obtained from the concatenation
     of the image root directory and this image name
     WARNING : the returned pointer will be
     available only until next call to get_filename */
    const char* get_filename() const;
    
    virtual bool fetch() = 0; // force fetch() to be defined by subclasses
    
    static void insert(SharedImage*& p, SharedImage* image);
    static SharedImage* find(SharedImage* image, const char* name);
    void remove_from_tree(SharedImage*& p, SharedImage* image);
    
  public:
    
    static SharedImage  *first_image;
    
    /*! Return an SharedImage, using the create function if an image with
     the given name doesn't already exist. Use datas, or read from the
     file with filename name if datas==0. */
    static SharedImage* get(SharedImage* (*create)(),
                            const char* name, const uchar* datas=0);
    
    /*! Reload the image, useful if it has changed on disk, or if the datas
     / in memory have changed (you can also give a new pointer on datas) */
    void reload(const uchar* datas=0);
    static void reload(const char* name, const uchar* datas=0);
    
    /*! Remove an image from the database and delete it if its refcount has
     fallen to zero
     Each remove() decrements the refcount, each get() increments it
     Return 1 if it has been really deleted. */
    int remove();
    static int remove(const char* name);
    
    /*! Clear the cache for this image and all of its children in the binary tree */
    void clear_cache();
    
    /*! Set the position where images are looked for on disk */
    static void set_root_directory(const char* d);
    
    /*! Expand a name relative to root to see what file it will read */
    static const char* get_filename(const char*);
    
    /*! Set the size of the cache (0 = unlimited is the default) */
    static void set_cache_size(unsigned l);
    
    void _draw(const Rectangle&) const;
    
  };
  
  ////////////////////////////////////////////////////////////////
  
  /*! Description of an Image file format */
  struct FL_IMAGES_API ImageType {
    // Name of the filetype as it appear in the source code LOWERCASE!!!
    const char* name;
    // Function to test the filetype
    bool (*test)(const uchar* datas, unsigned size);
    // Function to get/create an image of this type
    SharedImage* (*get)(const char* name, const uchar* datas);
  };
  extern FL_IMAGES_API ImageType image_filetypes[];
  
  /*! Try to guess the filetype
   Beware that calling this force you to link in all image types ! */
  FL_IMAGES_API ImageType* guess_image(const char* name, const uchar* datas=0);
  
  ////////////////////////////////////////////////////////////////
  
  // 
  // bmp and gif classes are build in libfltk2 so they are FL_API
  //
  
  class FL_API gifImage : public SharedImage {
    gifImage() { }
    static SharedImage* create() { return new gifImage; }
  public:
    static bool test(const uchar* datas, unsigned size=0);
    static SharedImage* get(const char* name, const uchar* datas = 0) {
      return SharedImage::get(create, name, datas);
    }
    bool fetch();
  };
  
  class FL_API bmpImage : public SharedImage {
    bmpImage() { }
    static SharedImage* create() { return new bmpImage; }
  public:
    static bool test(const uchar* datas, unsigned size=0);
    static SharedImage* get(const char* name, const uchar* datas = 0) {
      return SharedImage::get(create, name, datas);
    }
    bool fetch();
  };
  
  class FL_IMAGES_API xpmFileImage : public SharedImage {
    xpmFileImage() { }
    static SharedImage* create() { return new xpmFileImage; }
  public:
    static bool test(const uchar* datas, unsigned size=0);
    static SharedImage* get(const char* name, const uchar* datas = 0) {
      return SharedImage::get(create, name, datas);
    }
    bool fetch();
  };
  
  // 
  // jpeg and png classes are in libfltk2_images so they are FL_IMAGES_API
  //
  
  class FL_IMAGES_API jpegImage : public SharedImage {
    jpegImage() { }
    static SharedImage* create() { return new jpegImage; }
  public:
    static bool test(const uchar* datas, unsigned size=0);
    static SharedImage* get(const char* name, const uchar* datas = 0) {
      return SharedImage::get(create, name, datas);
    }
    bool fetch();
  };
  
  class FL_IMAGES_API pngImage : public SharedImage {
    pngImage() { }
    static SharedImage* create() { return new pngImage; } // Instantiate
  public:
    // Check the given buffer if it is in PNG format
    static bool test(const uchar* datas, unsigned size=0);
    static SharedImage* get(const char* name, const uchar* datas = 0) {
      return SharedImage::get(create, name, datas);
    }
    bool fetch();
  };
  
  extern FL_IMAGES_API void register_images(); // return always true only for automatic lib init purpose see images_core.cxx trick
  extern FL_IMAGES_API void unregister_images();
}

#endif

// End of "$Id: SharedImage.h 5738 2007-03-12 18:07:45Z spitzak $"
