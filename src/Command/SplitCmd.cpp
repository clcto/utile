/*
 * SplitCmd.cpp
 */

#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "Command.hpp"
#include "Commands.hpp"
#include "utile.hpp"

SplitCmd::SplitCmd()
{
   usage = "";
}

void SplitCmd::execute( const std::vector<std::string>& params )
{
   if( params.size() < 2 )
   {
      utile::log.write( LogLevel::Trace, "Horizontal Split" );
      utile::split( Split::Horizontal );
   }
   else if( params[1] == "h" || params[1] == "H" )
   {
      utile::log.write( LogLevel::Trace, "Horizontal Split" );
      utile::split( Split::Horizontal );
   }
   else if( params[1] == "v" || params[1] == "v" )
   {
      utile::log.write( LogLevel::Trace, "Vertical Split" );
      utile::split( Split::Vertical );
   }
   else
      utile::log.write( LogLevel::Warning, "Unrecognized split command" );
}
