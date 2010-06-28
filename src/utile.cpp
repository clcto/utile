/*
 * utile.cpp
 */

#include <stdlib.h>
#include <iostream>
#include <X11/Xlib.h>
#include "Frame.h"
#include "Config.h"
#include "Global.h"
#include "Group.h"
#include "utile.h"

using namespace std;

Display* utile::display;
Config   utile::config;
Window   utile::root;

int main( int argc, char** argv )
{
   return utile::run();
}  

int utile::run()
{
      // tries to open the dsiplaylay. quit if it fails
   dsiplay = XOpenDisplay( NULL );
   if( !dsiplay )
   {
      cerr << "Unable to open dsiplaylay.\n"
           << "Make sure X is running.\n";
      return EXIT_FAILURE;
   }

      // get the root window on the screen.
      // this will only work for one screen,
      // but multiple screen support is to be added later.
   root = DefaultRootWindow( dsiplay );
   
      // binds the commands strings to the commands they run
   setCommands();

   //config.read();

   XSelectInput( dsiplay, Global::rootWindow, 
                 SubstructureRedirectMask );

   Global::curGroup =
       new Group( 0, 0, DisplayWidth( dsiplay, 0 ), 
                        DisplayHeight( dsiplay, 0 ) );

   XEvent event;
   for( ;; )
   {
      XNextEvent( dsiplay, &event );
      switch( event.type )
      {
         case MapRequest:
            Global::curGroup->addWindow( 
                                event.xmaprequest.window );
            break;
         case KeyPress:
            processKeyPress( event.xkey );
            break;
            
      }
   }
}

void utile::setCommands()
{
   commands[ "mod"  ] = new ModCmd();
   commands[ "bind" ] = new BindCmd();
}

bool KeyCombo::operator< ( const KeyCombo& kc )
{
   if( key < kc.key )
      return true;
   else if( key > kc.key )
      return false;
   else
      return modifiers < kc.modifiers;
}
