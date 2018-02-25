/*
 * LauncherCmd.cpp
 */

#include "Command.hpp"
#include "Commands.hpp"
#include "utile.hpp"

#include <X11/Xlib.h>
#include <string>

LauncherCmd::LauncherCmd()
{
   usage = "";
}

void LauncherCmd::execute( const std::vector<std::string>& params )
{
   utile::log.write( LogLevel::Trace,
                     "Executing launcher command" );
   if( params.size() >= 2 )
   {
      std::string cmd = "";
      for( uint i = 1; i < params.size(); ++i )
         cmd += params[i] + " ";

      utile::launcher = std::move( cmd );
   }
}
