/*
 * Group.cpp
 *   a group of frames
 *   aka: virtual desktop, workspace
 * 
 * Copyright (c) 2010-2018
 *   Carick Wienke <carick dot wienke at gmail dot com>
 */

#include "Group.hpp"

/*
 * Constructor, creates the group
 *
 * root: the root window of the screen to be placed on
 * layoutname: the layout of tiles to use
 */
Group::Group( Window root, const std::string& layoutname ):
   _rootWindow( root )
{
   unsigned int width  = DisplayWidth(  utile::display, 0 );
   unsigned int height = DisplayHeight( utile::display, 0 );

   _rootNode = std::make_unique<GroupNode>( this, _rootWindow, 
                       0, 0, width, height);
   _curNode = _rootNode.get();
   _curNode->setActive( true );
}

/*
 * opens the layout file and executes the
 * commands on the group that calls it
 */
void Group::runLayout( const std::string& layoutname )
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
   utile::log.write( LogLevel::Trace, "Group::close()" );
   _curNode->close();
}

void Group::select( Direction d )
{
   utile::log.write( LogLevel::Debug, "trying to get next node" );
   GroupNode* tmp = _curNode->getNode( d );
   utile::log.write( LogLevel::Debug, "got node next to me" );
   if( tmp )
   {
      utile::log.write( LogLevel::Debug, "and it is not null" );
      _curNode->setActive( false );
      _curNode = tmp;
      _curNode->setActive( true );
   }
}

void Group::resize( Direction side, int pixels )
{
    utile::log.write( LogLevel::Debug, "resizing" );
    
}
