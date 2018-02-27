/*
 * Copyright (c) 2010-2018
 *   Carick Wienke <carick dot wienke at gmail dot com> 
 */
#pragma once

#include <string>

enum class Direction {
   Right,
   Left,
   Up,
   Down
};

// string functions
Direction parseDirection( const std::string& input );
std::string toString( Direction direction );

Direction opposite( Direction direction );
