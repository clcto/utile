/*
 * ModCmd.cpp
 */

#include "../include/Command.h"
#include "../include/Commands.h"

#include <string>

using namespace std;

ModCmd::ModCmd()
{
   usage = 
      "mod <name> <masks>\n"
      "  name  - the new name given to the mask\n"
      "  masks - a comma separated list of masks.\n\n"
      "Examples:\n"
      "  mod super Mod4Mask\n"
      "  mod default super,Mod1Mask\n";
}

// no default case. do nothing
void ModCmd::ExecuteDefault()
{
}

void ModCmd::Execute( string params )
{
}
