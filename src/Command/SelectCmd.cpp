/*
 * SelectCmd.cpp
 */

#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "Command.hpp"
#include "Commands.hpp"
#include "utile.hpp"

SelectCmd::SelectCmd()
{
   usage = "";
}

void SelectCmd::execute( const std::vector<std::string>& params )
{
   utile::log.write( LogLevel::Info, "Executing select command" );

   if( params.size() < 2 )
   {
      utile::log.write( LogLevel::Warning, "too few arguments" );
      return;
   }

      utile::log.write( LogLevel::Debug, "direction '%s'", params[1].c_str() );
   if( !params[1].compare( "u" ) || !params[1].compare( "up" ) )
      utile::select( Direction_Up );
   else if( !params[1].compare( "d" ) || !params[1].compare( "down" ) )
      utile::select( Direction_Down );
   else if( !params[1].compare( "l" ) || !params[1].compare( "left" ) )
      utile::select( Direction_Left );
   else if( !params[1].compare( "r" ) || !params[1].compare( "right" ) )
      utile::select( Direction_Right );
   else
      utile::log.write( LogLevel::Warning, "invalid direction '%s'", params[1].c_str() );
}
