/*
 * ColorCmd.cpp
 */

#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <sstream>

#include "Command.hpp"
#include "Commands.hpp"
#include "utile.hpp"

ColorCmd::ColorCmd()
{
   usage = "";
}

void ColorCmd::execute( const std::vector<std::string>& params )
{
   utile::log.write( LogLevel::Info, "Executing Color Cmd" );

   if( params.size() >= 6 )
   {
      unsigned short red = 0, green = 0, blue = 0;
      std::stringstream ss;
      if( params[1].compare( "hex" ) == 0 )
         ss.setf( std::ios::hex, std::ios::basefield );
      else if( params[1].compare( "dec" ) == 0 )
         ss.setf( std::ios::dec, std::ios::basefield );
      else
      {
         utile::log.write( LogLevel::Warning, "Invalid base type '%s'", params[1].c_str() );
         return;
      }

      ss.str( params[2] );
      ss >> red;
      if( ss.fail() )
      {
         utile::log.write( LogLevel::Warning, "Invalid Value '%s'", params[2].c_str() );
         return;
      }

      ss.clear();
      ss.str( params[3] );
      ss >> green;
      if( ss.fail() )
      {
         utile::log.write( LogLevel::Warning, "Invalid Value '%s'", params[3].c_str() );
         return;
      }

      ss.clear();
      ss.str( params[4] );
      ss >> blue;
      if( ss.fail() )
      {
         utile::log.write( LogLevel::Warning, "Invalid Value '%s'", params[4].c_str() );
         return;
      }

      XColor c;
      c.red = red;
      c.green = green;
      c.blue = blue;

      XAllocColor( utile::display, DefaultColormap( utile::display, 0 ), &c );

      utile::log.write( LogLevel::Debug, "%s: %d %d %d", params[5].c_str(),
                        c.red,
                        c.green,
                        c.blue );
      utile::colors[ params[5] ] = c;
   }
   else
      utile::log.write( LogLevel::Warning, "Too few arguments" );


}
