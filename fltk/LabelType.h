//
// "$Id: LabelType.h,v 1.4 2003/11/04 08:10:56 spitzak Exp $"
//
// A LabelType determines how to draw the text of the label. This
// is not used very much, it can be used to draw engraved or shadowed
// labels. You could also put in code that interprets the text of
// the label and draws anything you want with it.
//
// Copyright 1998-2003 by Bill Spitzak and others.
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

#ifndef fltk_LabelType_h
#define fltk_LabelType_h

#include "Style.h"
#include "Flags.h"

namespace fltk {

class FL_API LabelType {
public:
  virtual void draw(const char*, int,int,int,int, const Style*, Flags) const;
  const char* name;
  LabelType* next;
  static LabelType* first;
  LabelType(const char* n) : name(n), next(first) {first = this;}
  static LabelType* find(const char* name);
};

// You can use this to draw overlapping patterns
class FL_API EngravedLabel : public LabelType {
  const int* data;
public:
  void draw(const char*, int,int,int,int, const Style*, Flags) const;
  EngravedLabel(const char * n, const int p[][3])
    : LabelType(n), data((const int*)p) {}
};

}

#endif
