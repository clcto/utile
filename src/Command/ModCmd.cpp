/*
 * ModCmd.cpp
 */

#include <iostream>
#include <string.h>

#include "Command.h"
#include "Commands.h"
#include "utile.h"

using namespace std;

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

void ModCmd::execute( vector<string> params )
{
   if( params.size() >= 3 )
   {
      unsigned int numMask = 0;
      vector<string> strMasks;
      
      strMasks = tokenize( params[2], "," );

      for( unsigned int i = 0; i < strMasks.size(); ++i )
         numMask |= utile::masks[ strMasks[i] ];

      utile::masks[ params[1] ] = numMask;

      cerr << "Mask \'" << params[1]
           << "\' is bound to: " << utile::masks[ params[1] ]
           << '\n';
   }
}
