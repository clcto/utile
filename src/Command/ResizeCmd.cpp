/*
 * ResizeCmd.cpp
 */

#include "Command.hpp"
#include "Commands.hpp"
#include "utile.hpp"

#include <exception>
#include <stdlib.h>
#include <iostream>
#include <string.h>

ResizeCmd::ResizeCmd()
{
   usage = "";
}

void ResizeCmd::execute( const std::vector<std::string>& params )
{
    if( params.size() < 2 )
    {
        utile::log.write( LogLevel::Warning, "Not enough parameters to resize command" );
        return;
    }

    auto direction = parseDirection( params[1] );

    auto pixels = 20;
    if( params.size() >= 3 )
        pixels = std::stoi( params[ 2 ] );

    utile::resize( direction, pixels );
}
