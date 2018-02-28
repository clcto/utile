/*
 * Copyright (c) 2018
 *   Carick Wienke <carick dot wienke at gmail dot com> 
 */
#pragma once

#include "Direction.hpp"

enum class Orientation : bool
{
    Horizontal,
    Vertical
};

Orientation perpendicular( Orientation orientation );

class Edge
{
public:
    static Edge fromDirection( Direction side );

    static const Edge Right;
    static const Edge Left;
    static const Edge Top;
    static const Edge Bottom;

public:
    int index() const;
    Orientation parallel() const;
    Orientation perpendicular() const;

    Edge( const Edge& other ) = default;

private:
    Edge( Orientation orientation, bool topOrLeft );

    Orientation _orientation;
    bool _topOrLeft;
};
