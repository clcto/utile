/*
 * LauncherCmd.cpp
 */

#include "Command.hpp"
#include "Commands.hpp"
#include "utile.hpp"

#include <X11/Xlib.h>
#include <string>

using namespace std;

LauncherCmd::LauncherCmd()
{
   usage = "";
}

void LauncherCmd::execute( vector<string> params )
{
   utile::log.write( LogLevel_Trace,
                     "Executing launcher command" );
   if( params.size() >= 2 )
   {
      string cmd = "";
      for( uint i = 1; i < params.size(); ++i )
         cmd += params[i] + " ";

      utile::launcher = cmd;
   }
}
