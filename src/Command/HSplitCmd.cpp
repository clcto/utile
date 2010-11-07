/*
 * HSplitCmd.cpp
 */

#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "Command.hpp"
#include "Commands.hpp"
#include "utile.hpp"

using namespace std;

HSplitCmd::HSplitCmd()
{
   usage = "";
}

void HSplitCmd::execute( vector<string> params )
{
   utile::log.write( LogLevel_Trace, "Horizontal Split" );
   utile::split( Split_Horizontal );
}
