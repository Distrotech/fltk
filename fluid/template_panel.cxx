//
// "$Id$"
//
// FLUID template support for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2010 by Bill Spitzak and others.
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

// generated by Fast Light User Interface Designer (fluid) version 1.0300

#include "template_panel.h"
#include <stdio.h>
#include <stdlib.h>
#include "../src/flstring.h"
#include <errno.h>
#include <fltk3/filename.h>
#include <fltk3/ask.h>
#include <fltk3/SharedImage.h>
#include <fltk3/Preferences.h>
#if defined(WIN32) && !defined(__CYGWIN__)
#include <io.h>
#else
#include <unistd.h>
#endif // WIN32 && !__CYGWIN__
extern fltk3::Preferences fluid_prefs;

fltk3::DoubleWindow *template_panel=(fltk3::DoubleWindow *)0;

static void cb_template_panel(fltk3::DoubleWindow*, void*) {
  fltk3::SharedImage *img = (fltk3::SharedImage *)template_preview->image();
if (img) img->release();
template_preview->image(0);

template_browser->deselect();
template_name->value("");
template_instance->value("");
template_panel->hide();
}

fltk3::Browser *template_browser=(fltk3::Browser *)0;

static void cb_template_browser(fltk3::Browser*, void*) {
  if (fltk3::event_clicks()) {
  template_panel->hide();
  return;
}
fltk3::SharedImage *img = (fltk3::SharedImage *)template_preview->image();
if (img) img->release();
template_preview->image(0);
template_preview->redraw();

int item = template_browser->value();

if (item <= 1) template_instance->deactivate();
else template_instance->activate();

if (item < 1) {
  template_submit->deactivate();
  template_delete->deactivate();
  return;
}

template_submit->activate();

const char *flfile = (const char *)template_browser->data(item);
if (!flfile) {
  template_delete->deactivate();
  return;
}

template_name->value(template_browser->text(item));

template_delete->activate();

char pngfile[1024], *ext;

strlcpy(pngfile, flfile, sizeof(pngfile));
if ((ext = strrchr(pngfile, '.')) == NULL) return;
strcpy(ext, ".png");

img = fltk3::SharedImage::get(pngfile);

if (img) {
  template_preview->image(img);
  template_preview->redraw();
};
}

fltk3::Box *template_preview=(fltk3::Box *)0;

fltk3::Input *template_name=(fltk3::Input *)0;

static void cb_template_name(fltk3::Input*, void*) {
  if (strlen(template_name->value())) {
  template_submit->activate();
  if (fltk3::event_key() == fltk3::EnterKey) template_panel->hide();
} else template_submit->deactivate();
}

fltk3::Input *template_instance=(fltk3::Input *)0;

fltk3::Button *template_delete=(fltk3::Button *)0;

static void cb_Cancel(fltk3::Button*, void*) {
  fltk3::SharedImage *img = (fltk3::SharedImage *)template_preview->image();
if (img) img->release();
template_preview->image(0);

template_browser->deselect();
template_name->value("");
template_instance->value("");
template_panel->hide();
}

fltk3::ReturnButton *template_submit=(fltk3::ReturnButton *)0;

static void cb_template_submit(fltk3::ReturnButton*, void*) {
  fltk3::SharedImage *img = (fltk3::SharedImage *)template_preview->image();
if (img) img->release();
template_preview->image(0);

template_panel->hide();
}

fltk3::DoubleWindow* make_template_panel() {
  { template_panel = new fltk3::DoubleWindow(460, 355, "New/Save Template");
    template_panel->callback((fltk3::Callback*)cb_template_panel);
    { template_browser = new fltk3::Browser(10, 28, 180, 250, "Available Templates:");
      template_browser->type(2);
      template_browser->labelfont(1);
      template_browser->callback((fltk3::Callback*)cb_template_browser);
      template_browser->align(fltk3::Align(fltk3::ALIGN_TOP_LEFT));
      template_browser->when(3);
    } // fltk3::Browser* template_browser
    { template_preview = new fltk3::Box(200, 28, 250, 250);
      template_preview->box(fltk3::THIN_DOWN_BOX);
      template_preview->align(fltk3::Align(69|fltk3::ALIGN_INSIDE));
      fltk3::Group::current()->resizable(template_preview);
    } // fltk3::Box* template_preview
    { template_name = new fltk3::Input(124, 288, 326, 25, "Template Name:");
      template_name->labelfont(1);
      template_name->textfont(4);
      template_name->callback((fltk3::Callback*)cb_template_name);
      template_name->when(3);
    } // fltk3::Input* template_name
    { template_instance = new fltk3::Input(124, 288, 326, 25, "Instance Name:");
      template_instance->labelfont(1);
      template_instance->textfont(4);
      template_instance->hide();
    } // fltk3::Input* template_instance
    { fltk3::Group* o = new fltk3::Group(10, 323, 440, 25);
      { template_delete = new fltk3::Button(10, 323, 133, 25, "Delete Template");
        template_delete->callback((fltk3::Callback*)template_delete_cb);
      } // fltk3::Button* template_delete
      { fltk3::Box* o = new fltk3::Box(153, 323, 126, 25);
        fltk3::Group::current()->resizable(o);
      } // fltk3::Box* o
      { fltk3::Button* o = new fltk3::Button(289, 323, 72, 25, "Cancel");
        o->callback((fltk3::Callback*)cb_Cancel);
      } // fltk3::Button* o
      { template_submit = new fltk3::ReturnButton(371, 323, 79, 25, "Save");
        template_submit->callback((fltk3::Callback*)cb_template_submit);
      } // fltk3::ReturnButton* template_submit
      o->end();
    } // fltk3::Group* o
    template_panel->set_modal();
    template_panel->end();
  } // fltk3::DoubleWindow* template_panel
  return template_panel;
}

void template_clear() {
  int i;
  void *filename;
  
  for (i = 1; i <= template_browser->size(); i ++) {
    if ((filename = template_browser->data(i)) != NULL) free(filename);
  }
  
  template_browser->deselect();
  template_browser->clear();
}

void template_delete_cb(fltk3::Button *, void *) {
  int item = template_browser->value();
  if (item < 1) return;
  
  const char *name = template_browser->text(item);
  const char *flfile = (const char *)template_browser->data(item);
  if (!flfile) return;
  
  if (!fltk3::choice("Are you sure you want to delete the template \"%s\"?",
                 "Cancel", "Delete", 0, name)) return;
  
  if (unlink(flfile)) {
    fltk3::alert("Unable to delete template \"%s\":\n%s", name, strerror(errno));
    return;
  }
  
  template_browser->remove(item);
  template_browser->do_callback();
}

void template_load() {
  int i;
  char name[1024], filename[1024], path[1024], *ptr;
  struct dirent **files;
  int num_files;
  
  fluid_prefs.getUserdataPath(path, sizeof(path));
  strlcat(path, "templates", sizeof(path));
  
  num_files = fl_filename_list(path, &files);
  
  for (i = 0; i < num_files; i ++) {
    if (fl_filename_match(files[i]->d_name, "*.fl")) {
      // Format the name as the filename with "_" replaced with " "
      // and without the trailing ".fl"...
      strlcpy(name, files[i]->d_name, sizeof(name));
      *strstr(name, ".fl") = '\0';
  
      for (ptr = name; *ptr; ptr ++) {
        if (*ptr == '_') *ptr = ' ';
      }
  
      // Add the template to the browser...
      snprintf(filename, sizeof(filename), "%s/%s", path, files[i]->d_name);
      template_browser->add(name, strdup(filename));
    }
  
    free(files[i]);
  }
  
  if (num_files > 0) free(files);
}

//
// End of "$Id$".
//
