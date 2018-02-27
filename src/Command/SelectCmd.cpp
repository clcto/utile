/*
 * SelectCmd.cpp
 */

#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "Command.hpp"
#include "Commands.hpp"
#include "utile.hpp"

SelectCmd::SelectCmd()
{
    usage = "";
}

void SelectCmd::execute( const std::vector<std::string>& params )
{
    utile::log.write( LogLevel::Info, "Executing select command" );

    if( params.size() < 2 )
    {
        throw std::invalid_argument( "too few arguments to select command" );
    }

    utile::log.write( LogLevel::Debug, "direction '%s'", params[1].c_str() );
    auto direction = parseDirection( params[1] );
    utile::select( direction );
}
