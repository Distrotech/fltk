//
// "$Id$"
//

// 123 TODO: remove stray comments
// 123 TODO: add namespace statements
// 123 TODO: replace class name, constructors and destructor
// 123 TODO: add friend statement for Twin Class
// 123 TODO: add 'compat(FLTK2)' to constructors
// 123 TODO: add twin class with all constructors
// 123 TODO: change all arguments to the FLTK2 class name
// 123 TODO: change the source code to use the new class names
// 123 TODO: add casting to return values
// 123 TODO: move all FLTK2-only functions to the FLTK3 section and implement them
// 123 TODO: remove the FLTK1 and FLTK2 sections in the headers
// 123 TODO: 


/* suggested twin class
// This is the Twin Class to fltk::damage
class Fl_Damage : public fltk::damage {
public:
  Fl_Damage(int x, int t, int w, int h, const char *label=0)
  : fltk::damage(x, y, w, h, label), compat_(FLTK1) { }
};
*/

// ----- FLTK1 -----------------------------------------------------------------
#if 0
#endif
// ----- FLTK2 -----------------------------------------------------------------
#if 0
#ifndef fltk_damage_h
#define fltk_damage_h

namespace fltk {

/*!
  Values of the bits stored in Widget::damage().

  When redrawing your widgets you should look at the damage bits to
  see what parts of your widget need redrawing. The Widget::handle()
  method can then set individual damage bits to limit the amount of
  drawing that needs to be done, and the Widget::draw() method can
  test these bits to decide what to draw:

\code
MyClass::handle(int event) {
  ...
  if (change_to_part1) damage(1);
  if (change_to_part2) damage(2);
  if (change_to_part3) damage(4);
}

MyClass::draw() {
  if (damage() & fltk::DAMAGE_ALL) {
    ... draw frame/box and other static stuff ...
  }
  if (damage() & (fltk::DAMAGE_ALL | 1)) draw_part1();
  if (damage() & (fltk::DAMAGE_ALL | 2)) draw_part2();
  if (damage() & (fltk::DAMAGE_ALL | 4)) draw_part3();
}
\endcode

  Except for DAMAGE_ALL, each widget is allowed to assign any meaning
  to any of the bits it wants. The enumerations are just to provide
  suggested meanings.
*/
enum {
  DAMAGE_VALUE		= 0x01,
  DAMAGE_PUSHED		= 0x02,
  DAMAGE_SCROLL		= 0x04,
  DAMAGE_OVERLAY	= 0x04, // reused value
  DAMAGE_HIGHLIGHT	= 0x08,
  DAMAGE_CHILD		= 0x10,
  DAMAGE_CHILD_LABEL	= 0x20,
  DAMAGE_EXPOSE		= 0x40,
  DAMAGE_CONTENTS	= 0x40, // reused value
  DAMAGE_ALL		= 0x80
};

}

#endif
#endif
// ----- END -------------------------------------------------------------------
//
// End of "$Id$"
//
