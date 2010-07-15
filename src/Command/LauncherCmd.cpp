/*
 * LauncherCmd.cpp
 */

#include "Command.h"
#include "Commands.h"
#include "utile.h"

#include <X11/Xlib.h>
#include <string>

using namespace std;

LauncherCmd::LauncherCmd()
{
   usage = "";
}

void LauncherCmd::execute( vector<string> params )
{
   if( params.size() >= 2 )
   {
      string cmd = "";
      for( uint i = 1; i < params.size(); ++i )
         cmd += params[i] + " ";

      utile::launcher = cmd;
   }
}
