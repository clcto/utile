/*
 * Group.cpp
 *   a group of frames
 *   aka: virtual desktop, workspace
 * 
 * Copyright (c) 2010
 * Carick Wienke <carick dot wienke at gmail dot com>
 */

#include "Group.hpp"

/*
 * Constructor, creates the group
 *
 * root: the root window of the screen to be placed on
 * layoutname: the layout of tiles to use
 */
Group::Group( Window root, string layoutname ):
   _rootWindow( root )
{
   unsigned int width  = DisplayWidth(  utile::display, 0 );
   unsigned int height = DisplayHeight( utile::display, 0 );

   _rootNode = new GroupNode( this, _rootWindow, 
                       0, 0, width, height);
   _curNode = _rootNode;
}

/*
 * opens the layout file and executes the
 * commands on the group that calls it
 */
void Group::runLayout( string layoutname )
{
   
}

#if 0
/*
 * change the current GroupNode
 */
void Group::setCur( GroupNode* n )
{
   _curNode = n;
}
#endif

/*
 * returns the current GroupNode
 */
GroupNode* Group::getCur()
{
   return _curNode;
}

void Group::split( Split s )
{
   _curNode = _curNode->split( s );
}

void Group::close()
{
   utile::log.write( LogLevel_Trace, "Group::close()" );
   _curNode->close();
}

void Group::select( Direction d )
{
   GroupNode* tmp = _curNode->getNode( d );
   if( tmp )
      _curNode = tmp;

   _curNode->fixLastAccess();
}
