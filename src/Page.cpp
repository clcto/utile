/*
 * Page.cpp
 */

#include "Page.h"
#include "utile.h"

Page::Page( Window root, string layoutname ):
   _rootWindow( root )
{/*{{{*/
   unsigned int width  = DisplayWidth(  utile::display, 0 );
   unsigned int height = DisplayHeight( utile::display, 0 );

   _rootGroup.init( this, _rootWindow, 0, 0, width, height );
}/*}}}*/

void Page::runLayout( string layoutname )
{/*{{{*/
   
}/*}}}*/

void Page::setCurFrame( Frame* f )
{/*{{{*/
   _curFrame = f;
}/*}}}*/

Frame* Page::getCurFrame()
{/*{{{*/
   return _curFrame;
}/*}}}*/
