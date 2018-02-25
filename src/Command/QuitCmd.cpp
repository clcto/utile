/*
 * QuitCmd.cpp
 */

#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "Command.hpp"
#include "Commands.hpp"
#include "utile.hpp"

QuitCmd::QuitCmd()
{
   usage = "";
}

void QuitCmd::execute( const std::vector<std::string>& params )
{
   utile::log.write( LogLevel::Info, "Exitting" );
   exit(0);
}
