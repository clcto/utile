/*
 * Page.cpp
 */

#include "Page.h"

Page::Page( Window root, string layoutname ):
   _rootWindow( root )
{
   unsigned int width  = DisplayWidth(  utile::display,
                                        _rootWindow     );
   unsigned int height = DisplayHeight( utile::display,
                                        _rootWindow     );  

   _rootGroup.init( _rootWindow, 0, 0, width, height );
}

     
void Page::runLayout( string layoutname )
{
   
}
