//
// "$Id: RadioItem.h,v 1.1 2002/12/09 04:47:59 spitzak Exp $"
//
// This widget makes a radio item in a popup or pulldown Menu.
// It's behavior in a Browser or other group is undefined.
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
// Please report all bugs and problems to "fltk-bugs@easysw.com".
//

#ifndef fltk_RadioItem_h
#define fltk_RadioItem_h

#include "Item.h"

namespace fltk {

class RadioItem : public Item {
public:
  RadioItem(const char* l = 0) : Item(l) {type(RADIO);}
};

}

#endif
