/*
 * Group.cpp
 *   a group of frames
 *   aka: virtual desktop, workspace
 * 
 * Copyright (c) 2010
 * Carick Wienke <carick dot wienke at gmail dot com>
 */

#include "Group.hpp"
#include "utile.hpp"

/*
 * Constructor, creates the group
 *
 * root: the root window of the screen to be placed on
 * layoutname: the layout of tiles to use
 */
Group::Group( Window root, string layoutname ):
   _rootWindow( root )
{/*{{{*/
   unsigned int width  = DisplayWidth(  utile::display, 0 );
   unsigned int height = DisplayHeight( utile::display, 0 );

   _rootNode = new GroupNode( this, _rootWindow, 
                       0, 0, width, height );
   _curNode = _rootNode;
}/*}}}*/

/*
 * opens the layout file and executes the
 * commands on the group that calls it
 */
void Group::runLayout( string layoutname )
{/*{{{*/
   
}/*}}}*/

/*
 * change the current GroupNode
 */
void Group::setCur( GroupNode* n )
{/*{{{*/
   _curNode = n;
}/*}}}*/

/*
 * returns the current GroupNode
 */
GroupNode* Group::getCur()
{/*{{{*/
   return _curNode;
}/*}}}*/
