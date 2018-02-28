/*
 * Direction.cpp
 *
 * Copyright (c) 2018
 *  Carick Wienke (carick dot wienke at gmail dot com)
 */

#include "Direction.hpp"

#include <string>
#include <algorithm>
#include <sstream>

namespace {
    bool isRight( const std::string& input )
    {
        static std::string values[] = { "r", "R", "right" };
        auto found = std::find( std::begin( values ), std::end( values ), input );
        return found != std::end( values );
    }

    bool isLeft( const std::string& input )
    {
        const static std::string values[] = { "l", "L", "left" };
        auto found = std::find( std::begin( values ), std::end( values ), input );
        return found != std::end( values );
    }

    bool isUp( const std::string& input )
    {
        const static std::string values[] = { "u", "U", "up" };
        auto found = std::find( std::begin( values ), std::end( values ), input );
        return found != std::end( values );
    }

    bool isDown( const std::string& input )
    {
        const static std::string values[] = { "d", "D", "down" };
        auto found = std::find( std::begin( values ), std::end( values ), input );
        return found != std::end( values );
    }

    template <typename I>
    auto as_printable_int( I i ) -> decltype( +i ) { return +i; }

    template <typename E>
    auto enum_as_printable_int( E e ) -> decltype( 
        as_printable_int( static_cast< typename std::underlying_type<E>::type >( e ) ) )
    {
        using underlying = typename std::underlying_type<E>::type;
        return as_printable_int( static_cast< underlying >( e ) );
    }
}

[[ noreturn ]]
void throwBadDirection( Direction direction )
{
    std::ostringstream ss;
    auto value = enum_as_printable_int( direction );
    ss << "Direction value not recognized: " << value;
    throw std::invalid_argument( ss.str() );
}

Direction parseDirection( const std::string& input )
{
    if( isRight( input ) )      return Direction::Right;
    else if( isLeft( input ) )  return Direction::Left;
    else if( isUp( input ) )    return Direction::Up;
    else if( isDown( input ) )  return Direction::Down;


    std::ostringstream ss;
    ss << "Direction string value not recognized: \"" << input << '"';
    throw std::invalid_argument( ss.str() );
}

std::string toString( Direction direction )
{
    std::string ret;
    switch( direction )
    {
        case Direction::Right:
            ret = "Right";
            break;
        case Direction::Left:
            ret = "Left";
            break;
        case Direction::Up:
            ret = "Up";
            break;
        case Direction::Down:
            ret = "Down";
            break;

        default:
            throwBadDirection( direction );
    }

    return ret;
}

Direction opposite( Direction direction )
{
    switch( direction )
    {
        case Direction::Right:  return Direction::Left;
        case Direction::Left:   return Direction::Right;

        case Direction::Up:     return Direction::Down;
        case Direction::Down:   return Direction::Up;

        default:
            throwBadDirection( direction );
    }
}

