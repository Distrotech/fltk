//
// "$Id: fl_plastic_box.cxx,v 1.2 2002/12/09 04:52:30 spitzak Exp $"
//
// "Plastic" drawing routines for the Fast Light Tool Kit (FLTK).
//
// These box types provide a cross between Aqua and KDE buttons; kindof
// like translucent plastic buttons...
//
// Copyright 2001-2002 by Michael Sweet.
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

// This has been removed from the namespace version of fltk. It should
// be put into a theme.

#include <fltk/Box.h>
#include <fltk/Style.h>
#include <fltk/draw.h>
#include <string.h>
using namespace fltk;

extern void fl_to_inactive(const char* s, char* to);

static inline Color shade_color(uchar gc, Color bc) {
  return lerp(gc+(BLACK-'A'), bc, 0.75f);
}

#if 0 // this code is not used in fltk 2.0
static void shade_frame(int x, int y, int w, int h, const char *c, Color bc) {
  uchar *g = gray_ramp();
  int b = strlen(c) / 4 + 1;

  for (x += b, y += b, w -= 2 * b + 1, h -= 2 * b + 1; b > 1; b --)
  {
    // Draw lines around the perimeter of the button, 4 colors per
    // circuit.
    setcolor(shade_color(*c++, bc));
    drawline(x, y + h + b, x + w - 1, y + h + b, x + w + b - 1, y + h);
    setcolor(shade_color(*c++, bc));
    drawline(x + w + b - 1, y + h, x + w + b - 1, y, x + w - 1, y - b);
    setcolor(shade_color(*c++, bc));
    drawline(x + w - 1, y - b, x, y - b, x - b, y);
    setcolor(shade_color(*c++, bc));
    drawline(x - b, y, x - b, y + h, x, y + h + b);
  }
}
#endif

// Diamond with an edge pattern like FrameBox:
class PlasticBox : public FrameBox {
public:
  void draw(int,int,int,int, Color, Flags=0) const;
  PlasticBox(const char* n, const char* s, const FrameBox* d=0)
    : FrameBox(n, s, d) { fills_rectangle_ = 0; }
};

void PlasticBox::draw(int x, int y, int w, int h, Color bc, Flags f) const
{
  const char* c = (f & VALUE) ? down->data() : data();
  char buf[26]; if (f&INACTIVE && Style::draw_boxes_inactive) {
    fl_to_inactive(c, buf); c = buf;}

  int		i, j;
  int		clen = strlen(c) - 1;
  int		chalf = clen / 2;
  int		cstep = 1;

  if (h < (w * 2)) {
    // Horizontal shading...
    if (clen >= h) cstep = 2;

    for (i = 0, j = 0; j < chalf; i ++, j += cstep) {
      // Draw the top line and points...
      setcolor(shade_color(c[i], bc));
      drawline(x + 1, y + i, x + w - 1, y + i);

      setcolor(shade_color(c[i] - 2, bc));
      draw_point(x, y + i + 1);
      draw_point(x + w - 1, y + i + 1);

      // Draw the bottom line and points...
      setcolor(shade_color(c[clen - i], bc));
      drawline(x + 1, y + h - 1 - i, x + w - 1, y + h - 1 - i);

      setcolor(shade_color(c[clen - i] - 2, bc));
      draw_point(x, y + h - i);
      draw_point(x + w - 1, y + h - i);
    }

    // Draw the interior and sides...
    i = chalf / cstep;

    setcolor(shade_color(c[chalf], bc));
    fillrect(x + 1, y + i, w - 2, h - 2 * i);

    setcolor(shade_color(c[chalf] - 2, bc));
    drawline(x, y + i, x, y + h - i);
    drawline(x + w - 1, y + i, x + w - 1, y + h - i);
  } else {
    // Vertical shading...
    if (clen >= w) cstep = 2;

    for (i = 0, j = 0; j < chalf; i ++, j += cstep) {
      // Draw the left line and points...
      setcolor(shade_color(c[i], bc));
      drawline(x + i, y + 1, x + i, y + h - 1);

      setcolor(shade_color(c[i] - 2, bc));
      draw_point(x + i + 1, y);
      draw_point(x + i + 1, y + h - 1);

      // Draw the right line and points...
      setcolor(shade_color(c[clen - i], bc));
      drawline(x + w - 1 - i, y + 1, x + w - 1 - i, y + h - 1);

      setcolor(shade_color(c[clen - i] - 2, bc));
      draw_point(x + w - 1 - i, y);
      draw_point(x + w - 1 - i, y + h - 1);
    }

    // Draw the interior, top, and bottom...
    i = chalf / cstep;

    setcolor(shade_color(c[chalf], bc));
    fillrect(x + i, y + 1, w - 2 * i, h - 2);

    setcolor(shade_color(c[chalf - 2], bc));
    drawline(x + i, y, x + w - i, y);
    drawline(x + i, y + h - 1, x + w - i, y + h);
  }
}

static PlasticBox plasticDownBox(0, "STUVWWWVT");
Box* const fl_PLASTIC_DOWN_BOX = &plasticDownBox;
static PlasticBox plasticUpBox(0, "TXSPPQQRSSTTUVS", &plasticDownBox);
Box* const fl_PLASTIC_UP_BOX = &plasticUpBox;

// up_frame =  "MNFKKLNO"
// down_frame = "LLRRTTLL"

//
// End of "$Id: fl_plastic_box.cxx,v 1.2 2002/12/09 04:52:30 spitzak Exp $".
//
