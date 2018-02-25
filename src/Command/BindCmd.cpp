/*
 * BindCmd.cpp
 */

#include "Command.hpp"
#include "Commands.hpp"
#include "utile.hpp"

#include <X11/Xlib.h>
#include <string>

BindCmd::BindCmd()
{
   usage = "";
}

void BindCmd::execute( const std::vector<std::string>& params )
{
   utile::log.write( LogLevel::Trace, "Executing bind command" );
   if( params.size() >=4 )
   {
      unsigned int modMasks = 0;
      KeyCode tmpCode = 
            XKeysymToKeycode( utile::display,
            XStringToKeysym( params[2].c_str() ) );
      
      std::vector<std::string> strMasks = tokenize( params[1], "," );

      for( unsigned int i = 0; i < strMasks.size(); ++i )
         modMasks |= utile::masks[ strMasks[i] ];


      XGrabKey( utile::display, tmpCode, modMasks,
                utile::root, True, GrabModeAsync,
                GrabModeAsync );

      
      KeyCombo tmpCombo;
      tmpCombo.modifiers = modMasks;
      tmpCombo.key       = tmpCode;

         // remove the first "BindCmd" paramaters
         //    from the vector and store the 
         //    binded command
      utile::bindings[ tmpCombo ] = 
          std::vector<std::string>( params.begin()+4, params.end() );
   }
}
