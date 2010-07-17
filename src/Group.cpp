/*
 * Group.cpp
 */

#include "Group.hpp"
#include "utile.hpp"

Group::Group( Window root, string layoutname ):
   _rootWindow( root )
{/*{{{*/
   unsigned int width  = DisplayWidth(  utile::display, 0 );
   unsigned int height = DisplayHeight( utile::display, 0 );

   _rootNode = new GroupNode( this, _rootWindow, 
                       0, 0, width, height );
   _curNode = _rootNode;
}/*}}}*/

void Group::runLayout( string layoutname )
{/*{{{*/
   
}/*}}}*/

void Group::setCur( GroupNode* n )
{/*{{{*/
   _curNode = n;
}/*}}}*/

GroupNode* Group::getCur()
{/*{{{*/
   return _curNode;
}/*}}}*/
