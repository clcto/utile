/*
 * RunCmd.cpp
 */

#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "Command.hpp"
#include "Commands.hpp"
#include "utile.hpp"

using namespace std;

RunCmd::RunCmd()
{
   usage = "";
}

void RunCmd::execute( vector<string> params )
{
   utile::log.write( LogLevel_Trace, "Executing run command" );
   if( !utile::launcher.empty() )
   {
      utile::log.write( LogLevel_Trace, "launcher not empty" );
      string command;
      
      command  = "exec `print-path | ";
      command += utile::launcher;
      command += "` &";

      system( command.c_str() );
   }
}
