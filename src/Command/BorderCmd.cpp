/*
 * BorderCmd.cpp
 */

#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "Command.hpp"
#include "Commands.hpp"
#include "utile.hpp"

using namespace std;

BorderCmd::BorderCmd()
{
   usage = "";
}

void BorderCmd::execute( vector<string> params )
{
   utile::log.write( LogLevel_Info, "Executing Border Cmd" );


}
