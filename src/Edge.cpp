/*
 * Edge.cpp
 *
 * Copyright (c) 2018
 *   Carick Wienke <carick dot wienke at gmail dot com>
 */

#include "Edge.hpp"

Orientation perpendicular( Orientation input )
{
    return input == Orientation::Vertical ?
        Orientation::Horizontal :
        Orientation::Vertical;
}

const Edge Edge::Left { Orientation::Vertical, true };
const Edge Edge::Top { Orientation::Horizontal, true };
const Edge Edge::Right { Orientation::Vertical, false };
const Edge Edge::Bottom { Orientation::Horizontal, false };

Edge Edge::fromDirection( Direction side )
{
    switch( side )
    {
        case Direction::Right:  return Right;
        case Direction::Left:   return Left;
        case Direction::Up:     return Top;
        case Direction::Down:   return Bottom;
        
        default:
            throwBadDirection( side );
    }
}

int Edge::index() const { return _topOrLeft ? 0 : 1; }

Orientation Edge::parallel() const { return _orientation; }

Orientation Edge::perpendicular() const
{
    return ::perpendicular( _orientation );
}

Edge::Edge( Orientation orientation, bool topOrLeft ) :
    _orientation( orientation ),
    _topOrLeft( topOrLeft ) { }
