/*
 * BindCmd.cpp
 */

#include "Command.h"
#include "Commands.h"
#include "utile.h"

#include <X11/Xlib.h>
#include <string>

using namespace std;

BindCmd::BindCmd()
{
   usage = "";
}

void BindCmd::execute( vector<string> params )
{
   if( params.size() >=4 )
   {
      unsigned int modMasks = 0;
      KeyCode tmpCode = 
            XKeysymToKeycode( utile::display,
            XStringToKeysym( params[2].c_str() ) );
      
      vector<string> strMasks = tokenize( params[1], "," );

      for( unsigned int i = 0; i < strMasks.size(); ++i )
         modMasks |= utile::masks[ strMasks[i] ];


      XGrabKey( utile::display, tmpCode, modMasks,
                utile::root, True, GrabModeAsync,
                GrabModeAsync );

         // remove the first "BindCmd" paramaters
         //    from the vector and store the 
         //    binded command
      params.erase( params.begin(), params.begin()+3 );
      
      KeyCombo tmpCombo;
      tmpCombo.modifiers = modMasks;
      tmpCombo.key       = tmpCode;

      utile::bindings[ tmpCombo ] = params;
   }
}
