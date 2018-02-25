/*
 * RunCmd.cpp
 */

#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "Command.hpp"
#include "Commands.hpp"
#include "utile.hpp"

RunCmd::RunCmd()
{
   usage = "";
}

void RunCmd::execute( const std::vector<std::string>& params )
{
   utile::log.write( LogLevel::Trace, "Executing run command" );

   if( params.size() > 1 )
   {
      std::string cmd = "";
      
      for( uint i = 1; i < params.size(); ++i )
      {
         cmd += params[i];
         cmd += " ";
      }

      cmd += "&";

      utile::log.write( LogLevel::Trace, "system( %s )", cmd.c_str() );
      system( cmd.c_str() );
   }

   else if( !utile::launcher.empty() )
   {
      utile::log.write( LogLevel::Trace, "launcher not empty" );
      std::string command;
      
      command  = "exec `print-path | ";
      command += utile::launcher;
      command += "` &";

      system( command.c_str() );
   }
}
