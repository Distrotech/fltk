// generated by Fast Light User Interface Designer (fluid) version 1.0100


#include "preferences.h"
#include <stdlib.h>
#include <FL/filename.H>
void readPrefs();
void writePrefs();

static void closeWindowCB( Fl_Widget*, void* ) {
  delete myWindow;
}

static void saveAndCloseWindowCB( Fl_Widget*, void* ) {
  writePrefs();
  delete myWindow;
}

Fl_Window *myWindow=(Fl_Window *)0;

Fl_Input *wAlarm=(Fl_Input *)0;

Fl_Choice *wAmPm=(Fl_Choice *)0;

Fl_Menu_Item menu_wAmPm[] = {
 {"a.m.", 0,  0, 0, 0, 0, 0, 14, 0},
 {"p.m.", 0,  0, 0, 0, 0, 0, 14, 0},
 {0}
};

Fl_Choice *wWear=(Fl_Choice *)0;

Fl_Menu_Item menu_wWear[] = {
 {"shoes", 0,  0, 0, 0, 0, 0, 14, 0},
 {"sandals", 0,  0, 0, 0, 0, 0, 14, 0},
 {"flip flops", 0,  0, 0, 0, 0, 0, 14, 0},
 {"bare foot", 0,  0, 0, 0, 0, 0, 14, 0},
 {0}
};

Fl_Round_Button *wLeft=(Fl_Round_Button *)0;

Fl_Round_Button *wRight=(Fl_Round_Button *)0;

Fl_Check_Button *wShower=(Fl_Check_Button *)0;

Fl_Check_Button *wShave=(Fl_Check_Button *)0;

Fl_Check_Button *wBrush=(Fl_Check_Button *)0;

Fl_Choice *wDrink=(Fl_Choice *)0;

Fl_Menu_Item menu_wDrink[] = {
 {"coffee", 0,  0, 0, 0, 0, 0, 14, 0},
 {"tea", 0,  0, 0, 0, 0, 0, 14, 0},
 {"juice", 0,  0, 0, 0, 0, 0, 14, 0},
 {0}
};

Fl_Check_Button *wMilk=(Fl_Check_Button *)0;

Fl_Choice *wBread=(Fl_Choice *)0;

Fl_Menu_Item menu_wBread[] = {
 {"wheat", 0,  0, 0, 0, 0, 0, 14, 0},
 {"white", 0,  0, 0, 0, 0, 0, 14, 0},
 {"rye", 0,  0, 0, 0, 0, 0, 14, 0},
 {"sour doh", 0,  0, 0, 0, 0, 0, 14, 0},
 {0}
};

Fl_Check_Button *wButter=(Fl_Check_Button *)0;

Fl_Input *wEggs=(Fl_Input *)0;

Fl_Value_Slider *wMinutes=(Fl_Value_Slider *)0;

Fl_Input *wPaper=(Fl_Input *)0;

int main(int argc, char **argv) {
  Fl_Window* w;
  { Fl_Window* o = myWindow = new Fl_Window(298, 311, "My Preferences");
    w = o;
    o->callback((Fl_Callback*)closeWindowCB);
    { Fl_Button* o = new Fl_Button(210, 275, 75, 25, "Cancel");
      o->callback((Fl_Callback*)closeWindowCB);
    }
    { Fl_Button* o = new Fl_Button(125, 275, 75, 25, "OK");
      o->callback((Fl_Callback*)saveAndCloseWindowCB);
    }
    { Fl_Group* o = new Fl_Group(20, 30, 115, 225, "Get Up:");
      o->box(FL_ENGRAVED_FRAME);
      o->align(FL_ALIGN_TOP_LEFT);
      { Fl_Input* o = wAlarm = new Fl_Input(25, 55, 45, 20, "Alarm at:");
        o->align(FL_ALIGN_TOP_LEFT);
      }
      { Fl_Choice* o = wAmPm = new Fl_Choice(75, 55, 55, 20);
        o->down_box(FL_BORDER_BOX);
        o->menu(menu_wAmPm);
      }
      { Fl_Choice* o = wWear = new Fl_Choice(25, 100, 105, 20, "Wear:");
        o->down_box(FL_BORDER_BOX);
        o->align(FL_ALIGN_TOP_LEFT);
        o->menu(menu_wWear);
      }
      { Fl_Round_Button* o = wLeft = new Fl_Round_Button(35, 120, 95, 25, "left side");
        o->down_box(FL_ROUND_DOWN_BOX);
      }
      { Fl_Round_Button* o = wRight = new Fl_Round_Button(35, 140, 95, 25, "right side");
        o->down_box(FL_ROUND_DOWN_BOX);
      }
      new Fl_Box(38, 160, 95, 20, "of the bed");
      { Fl_Check_Button* o = wShower = new Fl_Check_Button(25, 180, 105, 25, "shower");
        o->down_box(FL_DOWN_BOX);
      }
      { Fl_Check_Button* o = wShave = new Fl_Check_Button(25, 200, 105, 25, "shave");
        o->down_box(FL_DOWN_BOX);
      }
      { Fl_Check_Button* o = wBrush = new Fl_Check_Button(25, 220, 105, 25, "brush teeth");
        o->down_box(FL_DOWN_BOX);
      }
      o->end();
    }
    { Fl_Group* o = new Fl_Group(160, 30, 115, 225, "Breakfast::");
      o->box(FL_ENGRAVED_FRAME);
      o->align(FL_ALIGN_TOP_LEFT);
      { Fl_Choice* o = wDrink = new Fl_Choice(165, 50, 105, 20, "Drink:");
        o->down_box(FL_BORDER_BOX);
        o->align(FL_ALIGN_TOP_LEFT);
        o->menu(menu_wDrink);
      }
      { Fl_Check_Button* o = wMilk = new Fl_Check_Button(170, 70, 100, 25, "with milk");
        o->down_box(FL_DOWN_BOX);
      }
      { Fl_Choice* o = wBread = new Fl_Choice(165, 110, 105, 20, "Bread:");
        o->down_box(FL_BORDER_BOX);
        o->align(FL_ALIGN_TOP_LEFT);
        o->menu(menu_wBread);
      }
      { Fl_Check_Button* o = wButter = new Fl_Check_Button(170, 130, 100, 25, "with butter");
        o->down_box(FL_DOWN_BOX);
      }
      { Fl_Input* o = wEggs = new Fl_Input(165, 163, 30, 20, "eggs");
        o->type(2);
        o->align(FL_ALIGN_RIGHT);
      }
      { Fl_Value_Slider* o = wMinutes = new Fl_Value_Slider(175, 185, 70, 20, "min.");
        o->type(1);
        o->minimum(2);
        o->maximum(6);
        o->value(3.1);
        o->align(FL_ALIGN_RIGHT);
      }
      { Fl_Input* o = wPaper = new Fl_Input(165, 225, 105, 20, "Newspaper:");
        o->align(FL_ALIGN_TOP_LEFT);
      }
      o->end();
    }
    o->end();
  }
  readPrefs();
  w->show(argc, argv);
  return Fl::run();
}

void readPrefs() {
  char boolValue;
int intValue;
char buffer[80];
double doubleValue;

Fl_Preferences app( Fl_Preferences::USER, "fltk.org", "test/preferences" );

  char path[ FL_PATH_MAX ];
  app.getUserdataPath( path );

  Fl_Preferences bed( app, "Bed" );
    bed.get( "alarm", buffer, "8:00", 80 );
    wAlarm->value( buffer );

    bed.get( "ampm", intValue, 0 );
    wAmPm->value( intValue );

    bed.get( "wear", intValue, 1 );
    wWear->value( intValue );

    int side;
    bed.get( "side", side, 2 );
    if ( side == 1 ) wLeft->value( 1 );
    if ( side == 2 ) wRight->value( 1 );

    int todo;
    bed.get( "todoFlags", todo, 0x05 );
    if ( todo & 0x01 ) wShower->value( 1 );
    if ( todo & 0x02 ) wShave->value( 1 );
    if ( todo & 0x04 ) wBrush->value( 1 );

  Fl_Preferences eat( app, "Breakfast" );

    eat.get( "drink", intValue, 1 );
    wDrink->value( intValue );

    eat.get( "wMilk", boolValue, 0 );
    wMilk->value( boolValue );

    eat.get( "bread", intValue, 0 );
    wBread->value( intValue );

    eat.get( "wButter", boolValue, 1 );
    wButter->value( boolValue );

    eat.get( "nEggs", intValue, 2 );
    sprintf( buffer, "%d", intValue );
    wEggs->value( buffer );

    eat.get( "minutes", doubleValue, 3.2 );
    wMinutes->value( doubleValue );

    char *flexBuffer;
    eat.get( "newspaper", flexBuffer, "NY Tymes" );
    wPaper->value( flexBuffer );
    if ( flexBuffer ) free( flexBuffer );

    eat.get( "foo", buffer, "bar", 80 );
}

void writePrefs() {
  Fl_Preferences app( Fl_Preferences::USER, "fltk.org", "test/preferences" );

  Fl_Preferences bed( app, "Bed" );

    bed.set( "alarm", wAlarm->value() );
    bed.set( "ampm", wAmPm->value() );

    bed.set( "wear", wWear->value() );

    int side = 0;
    if ( wLeft->value() ) side = 1;
    if ( wRight->value() ) side = 2;
    bed.set( "side", side );

    int todo = 0;
    if ( wShower->value() ) todo |= 0x01;
    if ( wShave->value() ) todo |= 0x02;
    if ( wBrush->value() ) todo |= 0x04;
    bed.set( "todoFlags", todo );

  Fl_Preferences eat( app, "Breakfast" );

    eat.set( "drink", wDrink->value() );
    eat.set( "wMilk", wMilk->value() );
    eat.set( "bread", wBread->value() );
    eat.set( "wButter", wButter->value() );

    eat.set( "nEggs", wEggs->value() );
    eat.set( "minutes", wMinutes->value() );

    eat.set( "newspaper", wPaper->value() );

    eat.set( "foo", "bar\nfly\rBackslash: \\ and bell: \007 and delete: \177\n" );

}
