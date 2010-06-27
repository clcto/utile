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
#include "include/Frame.h"
#include "include/Config.h"
#include "include/globals.h"
#include "include/Group.h"

#define MODIFIER (Mod4Mask)

using namespace std;

void processKeyPress( XKeyEvent keyEvent );
KeyCode setInputKey( const char* key );

int main( int argc, char** argv )
{
      // tries to open the display. quit if it fails
   g_display = XOpenDisplay( NULL );
   if( !g_display )
   {
      cerr << "Unable to open display.\n"
             << "Make sure X is running.\n";
      return EXIT_FAILURE;
   }

      // get the root window on the screen.
      // this will only work for one screen,
      // but multiple screen support is to be added later.
   g_rootWindow = DefaultRootWindow( g_display );
   
   config.initialize();

   system( "dmenu_run | exec&" );

   XSelectInput( g_display, g_rootWindow, SubstructureRedirectMask );

   g_splitHorizKey = setInputKey( "h" );

   g_curGroup = new Group( 0, 0, DisplayWidth( g_display, 0 ), 
                                DisplayHeight( g_display, 0 ) );

   XEvent event;
   for( ;; )
   {
      XNextEvent( g_display, &event );
      switch( event.type )
      {
         case MapRequest:
            g_curGroup->addWindow( event.xmaprequest.window );
            break;
         case KeyPress:
            processKeyPress( event.xkey );
            break;
            
      }
   }

}

/*
 * grabs the input for the key with the modmask set
 * in the config.h and returns the key code for the
 * key
 */
KeyCode setInputKey( const char* key )
{
   KeyCode keycode;
   keycode = XKeysymToKeycode( g_display, XStringToKeysym(key) );
   XGrabKey( g_display, keycode, MODIFIER, g_rootWindow, True, 
      GrabModeAsync, GrabModeAsync );
   return keycode;
}

void processKeyPress( XKeyEvent keyEvent )
{
   if( keyEvent.keycode == g_splitHorizKey )
      g_curGroup = g_curGroup->splitHorizontal();
}
