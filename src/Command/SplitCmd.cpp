/*
 * SplitCmd.cpp
 */

#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "Command.hpp"
#include "Commands.hpp"
#include "utile.hpp"

using namespace std;

SplitCmd::SplitCmd()
{
   usage = "";
}

void SplitCmd::execute( vector<string> params )
{
   if( params.size() < 2 )
   {
      utile::log.write( LogLevel_Trace, "Horizontal Split" );
      utile::split( Split_Horizontal );
   }
   else if( params[1] == "h" || params[1] == "H" )
   {
      utile::log.write( LogLevel_Trace, "Horizontal Split" );
      utile::split( Split_Horizontal );
   }
   else if( params[1] == "v" || params[1] == "v" )
   {
      utile::log.write( LogLevel_Trace, "Vertical Split" );
      utile::split( Split_Vertical );
   }
   else
      utile::log.write( LogLevel_Warning, "Unrecognized split command" );
}
