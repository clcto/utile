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

   _rootGroupNode.init( this, _rootWindow, 0, 0, width, height );
}/*}}}*/

void Group::runLayout( string layoutname )
{/*{{{*/
   
}/*}}}*/

void Group::setCurFrame( Frame* f )
{/*{{{*/
   _curFrame = f;
}/*}}}*/

Frame* Group::getCurFrame()
{/*{{{*/
   return _curFrame;
}/*}}}*/
