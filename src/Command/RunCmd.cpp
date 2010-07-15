/*
 * RunCmd.cpp
 */

#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "Command.h"
#include "Commands.h"
#include "utile.h"

using namespace std;

RunCmd::RunCmd()
{
   usage = "";
}

void RunCmd::execute( vector<string> params )
{
   if( !utile::launcher.empty() )
   {
      string command;
      /*
      command  = "prog='print-path|";
      command += utile::launcher;
      command += "' && exec $prog";
      */
      
      command  = "exec `print-path|";
      command += utile::launcher;
      command += "`";
      system( command.c_str() );
   }
}
