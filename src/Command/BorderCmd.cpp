/*
 * BorderCmd.cpp
 */

#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "Command.hpp"
#include "Commands.hpp"
#include "utile.hpp"
#include "Frame.hpp"

BorderCmd::BorderCmd()
{
   usage = "";
}

void BorderCmd::execute( const std::vector<std::string>& params )
{
   utile::log.write( LogLevel::Info, "Executing border command" );

   if( params.size() < 3 )
   {
      utile::log.write( LogLevel::Warning, "too few arguments" );
      return;
   }

   if( utile::colors.count( params[2] ) == 0 )
   {
      utile::log.write( LogLevel::Warning, "undefined color '%s'", params[2].c_str() );
      return;
   }

   XColor c = utile::colors[ params[2] ];

   if( ! params[1].compare( "i" ) || ! params[1].compare( "inactive" ) )
      Frame::setInactive( c );
   else if( ! params[1].compare( "a" ) || ! params[1].compare( "active" ) )
      Frame::setActive( c );
   else
      utile::log.write( LogLevel::Warning, "unknown border option '%s'", params[1].c_str() );
}
