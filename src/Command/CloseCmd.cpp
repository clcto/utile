/*
 * CloseCmd.cpp
 */

#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "Command.hpp"
#include "Commands.hpp"
#include "utile.hpp"

CloseCmd::CloseCmd()
{
   usage = "";
}

void CloseCmd::execute( const std::vector<std::string>& params )
{
   utile::log.write( LogLevel::Trace, "Executing Close" );
   utile::close();
}
