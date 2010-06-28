/*
 * main.c
 *  Starts the window manager
 *
 *  Created on: Jun 19, 2010
 *      Author: carick
 */

#include <stdlib.h>
#include <iostream>
#include <X11/Xlib.h>
#include "Frame.h"
#include "Config.h"
#include "Global.h"
#include "Group.h"

#define MODIFIER (Mod4Mask)

using namespace std;

void processKeyPress( XKeyEvent keyEvent );
KeyCode setInputKey( const char* key );

int main( int argc, char** argv )
{
      // tries to open the display. quit if it fails
   Global::display = XOpenDisplay( NULL );
   if( !Global::display )
   {
      cerr << "Unable to open display.\n"
             << "Make sure X is running.\n";
      return EXIT_FAILURE;
   }

      // get the root window on the screen.
      // this will only work for one screen,
      // but multiple screen support is to be added later.
   Global::rootWindow = DefaultRootWindow( Global::display );
   
   Global::config.initialize();

   system( "dmenu_run | exec&" );

   XSelectInput( Global::display, Global::rootWindow, 
                 SubstructureRedirectMask );

   Global::splitHorizKey = setInputKey( "h" );

   Global::curGroup =
       new Group( 0, 0, DisplayWidth( Global::display, 0 ), 
                        DisplayHeight( Global::display, 0 ) );

   XEvent event;
   for( ;; )
   {
      XNextEvent( Global::display, &event );
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

/*
 * grabs the input for the key with the modmask set
 * in the Global::config.h and returns the key code for the
 * key
 */
KeyCode setInputKey( const char* key )
{
   KeyCode keycode;
   keycode = XKeysymToKeycode( Global::display, 
                               XStringToKeysym(key) );
   XGrabKey( Global::display, keycode, MODIFIER, 
             Global::rootWindow, True, 
      GrabModeAsync, GrabModeAsync );
   return keycode;
}

void processKeyPress( XKeyEvent keyEvent )
{
   if( keyEvent.keycode == Global::splitHorizKey )
      Global::curGroup = Global::curGroup->splitHorizontal();
}
