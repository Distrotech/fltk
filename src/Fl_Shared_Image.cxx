//
// "$Id: Fl_Shared_Image.cxx,v 1.23.2.7 2002/01/06 17:51:12 easysw Exp $"
//
// Shared image code for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2002 by Bill Spitzak and others.
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
// Please report all bugs and problems to "fltk-bugs@fltk.org".
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <FL/Fl.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_BMP_Image.H>
#include <FL/Fl_GIF_Image.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_PNM_Image.H>
#include <FL/Fl_XBM_Image.H>
#include <FL/Fl_XPM_Image.H>


//
// Global class vars...
//

Fl_Shared_Image **Fl_Shared_Image::images_ = 0;	// Shared images
int	Fl_Shared_Image::num_images_ = 0;	// Number of shared images
int	Fl_Shared_Image::alloc_images_ = 0;	// Allocated shared images


//
// Typedef the C API sort function type the only way I know how...
//

extern "C" {
  typedef int (*compare_func_t)(const void *, const void *);
}


//
// 'Fl_Shared_Image::compare()' - Compare two shared images...
//

int
Fl_Shared_Image::compare(Fl_Shared_Image **i0,		// I - First image
                         Fl_Shared_Image **i1) {	// I - Second image
  int i = strcmp((*i0)->name(), (*i1)->name());

  if (i) return i;
  else if (((*i0)->w() == 0 && (*i1)->original_) ||
           ((*i1)->w() == 0 && (*i0)->original_)) return 0;
  else if ((*i0)->w() != (*i1)->w()) return (*i0)->w() - (*i1)->w();
  else return (*i0)->h() - (*i1)->h();
}


//
// 'Fl_Shared_Image::Fl_Shared_Image()' - Basic constructor.
//

Fl_Shared_Image::Fl_Shared_Image() : Fl_Image(0,0,0) {
  name_        = 0;
  refcount_    = 1;
  original_    = 0;
  image_       = 0;
  alloc_image_ = 0;
}


//
// 'Fl_Shared_Image::Fl_Shared_Image()' - Add an image to the image cache.
//

Fl_Shared_Image::Fl_Shared_Image(const char *n,		// I - Filename
                                 Fl_Image   *img)	// I - Image
  : Fl_Image(0,0,0) {
  name_ = new char[strlen(n) + 1];
  strcpy((char *)name_, n);

  refcount_    = 1;
  image_       = img;
  alloc_image_ = 0;
  original_    = 1;

  if (!img) reload();
  else update();
}


//
// 'Fl_Shared_Image::add()' - Add a shared image to the array.
//

void
Fl_Shared_Image::add() {
  Fl_Shared_Image	**temp;		// New image pointer array...

  if (num_images_ >= alloc_images_) {
    // Allocate more memory...
    temp = new Fl_Shared_Image *[alloc_images_ + 32];

    if (alloc_images_) {
      memcpy(temp, images_, alloc_images_ * sizeof(Fl_Shared_Image *));

      delete[] images_;
    }

    images_       = temp;
    alloc_images_ += 32;
  }

  images_[num_images_] = this;
  num_images_ ++;

  if (num_images_ > 1) {
    qsort(images_, num_images_, sizeof(Fl_Shared_Image *),
          (compare_func_t)compare);
  }
}


//
// 'Fl_Shared_Image::update()' - Update the dimensions of the shared images.
//

void
Fl_Shared_Image::update() {
  if (image_) {
    w(image_->w());
    h(image_->h());
    d(image_->d());
    data(image_->data(), image_->count());
  }
}


//
// 'Fl_Shared_Image::~Fl_Shared_Image()' - Destroy a shared image...
//

Fl_Shared_Image::~Fl_Shared_Image() {
  if (name_) delete[] (char *)name_;
  if (alloc_image_) delete image_;
}


//
// 'Fl_Shared_Image::release()' - Release and possibly destroy a shared image.
//

void
Fl_Shared_Image::release() {
  int	i;	// Looping var...

  refcount_ --;
  if (refcount_ > 0) return;

  for (i = 0; i < num_images_; i ++)
    if (images_[i] == this) {
      num_images_ --;

      if (i < num_images_) {
        memcpy(images_ + i, images_ + i + 1,
               (num_images_ - i) * sizeof(Fl_Shared_Image *));
      }

      break;
    }

  delete this;

  if (num_images_ == 0 && images_) {
    delete[] images_;

    images_       = 0;
    alloc_images_ = 0;
  }
}


//
// 'Fl_Shared_Image::reload()' - Reload the shared image...
//

void
Fl_Shared_Image::reload() {
  // Load image from disk...
  FILE		*fp;		// File pointer
  uchar		header[16];	// Buffer for auto-detecting files
  Fl_Image	*img;		// New image

  if (!name_) return;

  if ((fp = fopen(name_, "rb")) != NULL) {
    fread(header, 1, sizeof(header), fp);
    fclose(fp);
  } else {
    memset(header, 0, sizeof(header));
  }

  // Load the image as appropriate...
  if (memcmp(header, "GIF87a", 6) == 0 ||
      memcmp(header, "GIF89a", 6) == 0)
    img = new Fl_GIF_Image(name_);
  else if (memcmp(header, "\211PNG", 4) == 0)
    img = new Fl_PNG_Image(name_);
  else if (memcmp(header, "\377\330\377", 3) == 0 &&	// Start-of-Image
	   header[3] >= 0xe0 && header[3] <= 0xef)	// APPn
    img = new Fl_JPEG_Image(name_);
  else if (memcmp(header, "BM", 2) == 0)	// BMP file
    img = new Fl_BMP_Image(name_);
  else if (header[0] == 'P' && header[1] >= '1' && header[1] <= '6') // Portable anymap
    img = new Fl_PNM_Image(name_);
  else if (memcmp(header, "#define", 7) == 0) // XBM file
    img = new Fl_XBM_Image(name_);
  else if (memcmp(header, "/* XPM */", 9) == 0) // XPM file
    img = new Fl_XPM_Image(name_);
  else
    img = 0;

  if (img) {
    if (alloc_image_) delete image_;

    image_       = img;
    alloc_image_ = 1;

    if ((img->w() != w() && w()) || (img->h() != h() && h())) {
      // Make sure the reloaded image is the same size as the existing one.
      Fl_Image *temp = img->copy(w(), h());
      delete img;
      img = temp;
    }

    update();
  }
}


//
// 'Fl_Shared_Image::copy()' - Copy and resize a shared image...
//

Fl_Image *
Fl_Shared_Image::copy(int W, int H) {
  Fl_Image		*temp_image;	// New image file
  Fl_Shared_Image	*temp_shared;	// New shared image

  // Make a copy of the image we're sharing...
  if (!image_) temp_image = 0;
  else temp_image = image_->copy(W, H);

  // Then make a new shared image...
  temp_shared = new Fl_Shared_Image();

  temp_shared->name_ = new char[strlen(name_) + 1];
  strcpy((char *)temp_shared->name_, name_);

  temp_shared->refcount_    = 1;
  temp_shared->image_       = temp_image;
  temp_shared->alloc_image_ = 0;

  temp_shared->update();

  return temp_shared;
}


//
// 'Fl_Shared_Image::color_average()' - Blend colors...
//

void
Fl_Shared_Image::color_average(Fl_Color c,	// I - Color to blend with
                               float    i) {	// I - Blend fraction
  if (!image_) return;

  image_->color_average(c, i);
  update();
}


//
// 'Fl_Shared_Image::desaturate()' - Convert the image to grayscale...
//

void
Fl_Shared_Image::desaturate() {
  if (!image_) return;

  image_->desaturate();
  update();
}


//
// 'Fl_Shared_Image::draw()' - Draw a shared image...
//

void
Fl_Shared_Image::draw(int X, int Y, int W, int H, int cx, int cy) {
  if (image_) image_->draw(X, Y, W, H, cx, cy);
  else Fl_Image::draw(X, Y, W, H, cx, cy);
}


//
// 'Fl_Shared_Image::find()' - Find a shared image...
//

Fl_Shared_Image *
Fl_Shared_Image::find(const char *n, int W, int H) {
  Fl_Shared_Image	*key,		// Image key
			**match;	// Matching image

  if (num_images_) {
    key = new Fl_Shared_Image();
    key->name_ = new char[strlen(n) + 1];
    strcpy((char *)key->name_, n);
    key->w(W);
    key->h(H);

    match = (Fl_Shared_Image **)bsearch(&key, images_, num_images_,
                                        sizeof(Fl_Shared_Image *),
                                        (compare_func_t)compare);

    delete key;

    if (match) {
      (*match)->refcount_ ++;
      return *match;
    }
  }

  return 0;
}


//
// 'Fl_Shared_Image::get()' - Get a shared image...
//

Fl_Shared_Image *
Fl_Shared_Image::get(const char *n, int W, int H) {
  Fl_Shared_Image	*temp;		// Image

  if ((temp = find(n, W, H)) != NULL) return temp;

  if ((temp = find(n)) == NULL) {
    temp = new Fl_Shared_Image(n);

    if (!temp->image_) {
      delete temp;
      return NULL;
    }

    temp->add();
  }

  if ((temp->w() != W || temp->h() != H) && W && H) {
    temp = (Fl_Shared_Image *)temp->copy(W, H);
    temp->add();
  }

  return temp;
}


//
// End of "$Id: Fl_Shared_Image.cxx,v 1.23.2.7 2002/01/06 17:51:12 easysw Exp $".
//
