/*
 * ModCmd.cpp
 */

#include <iostream>
#include <string.h>

#include "Command.hpp"
#include "Commands.hpp"
#include "utile.hpp"

ModCmd::ModCmd()
{
   usage = 
      "defines a new modmask by name.\n\n"
      "mod <name> <masks>\n"
      "  name  - the new name given to the mask\n"
      "  masks - a comma separated list of masks.\n\n"
      "Examples:\n"
      "  mod super Mod4Mask\n"
      "  mod default super,Mod1Mask\n";
}

void ModCmd::execute( const std::vector<std::string>& params )
{
   utile::log.write( LogLevel::Trace, "Executing mod command" );
   if( params.size() >= 3 )
   {
      unsigned int numMask = 0;
      std::vector<std::string> strMasks;
      
      strMasks = tokenize( params[2], "," );

      for( unsigned int i = 0; i < strMasks.size(); ++i )
         numMask |= utile::masks[ strMasks[i] ];

      utile::masks[ params[1] ] = numMask;
   }
}
