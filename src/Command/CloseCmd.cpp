/*
 * CloseCmd.cpp
 */

#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "Command.hpp"
#include "Commands.hpp"
#include "utile.hpp"

using namespace std;

CloseCmd::CloseCmd()
{
   usage = "";
}

void CloseCmd::execute( vector<string> params )
{
   utile::log.write( LogLevel_Trace, "Executing Close" );
   utile::close();
}
