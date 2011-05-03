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

using namespace std;

ColorCmd::ColorCmd()
{
   usage = "";
}

void ColorCmd::execute( vector<string> params )
{
   utile::log.write( LogLevel_Info, "Executing Color Cmd" );

   if( params.size() >= 6 )
   {
      unsigned short red = 0, green = 0, blue = 0;
      stringstream ss;
      if( params[1].compare( "hex" ) == 0 )
         ss.setf( ios::hex, ios::basefield );
      else if( params[1].compare( "dec" ) == 0 )
         ss.setf( ios::dec, ios::basefield );
      else
      {
         utile::log.write( LogLevel_Warning, "Invalid base type '%s'", params[1].c_str() );
         return;
      }

      ss.str( params[2] );
      ss >> red;
      if( ss.fail() )
      {
         utile::log.write( LogLevel_Warning, "Invalid Value '%s'", params[2].c_str() );
         return;
      }

      ss.clear();
      ss.str( params[3] );
      ss >> green;
      if( ss.fail() )
      {
         utile::log.write( LogLevel_Warning, "Invalid Value '%s'", params[3].c_str() );
         return;
      }

      ss.clear();
      ss.str( params[4] );
      ss >> blue;
      if( ss.fail() )
      {
         utile::log.write( LogLevel_Warning, "Invalid Value '%s'", params[4].c_str() );
         return;
      }

      XColor c;
      c.red = red;
      c.green = green;
      c.blue = blue;

      XAllocColor( utile::display, DefaultColormap( utile::display, 0 ), &c );

      utile::log.write( LogLevel_Debug, "%s: %d %d %d", params[5].c_str(),
                        c.red,
                        c.green,
                        c.blue );
      utile::colors[ params[5] ] = c;
   }
   else
      utile::log.write( LogLevel_Warning, "Too few arguments" );


}
