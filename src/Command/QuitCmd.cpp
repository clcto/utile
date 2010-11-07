/*
 * QuitCmd.cpp
 */

#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "Command.hpp"
#include "Commands.hpp"
#include "utile.hpp"

using namespace std;

QuitCmd::QuitCmd()
{
   usage = "";
}

void QuitCmd::execute( vector<string> params )
{
   utile::log.write( LogLevel_Info, "Exitting" );
   exit(0);
}
