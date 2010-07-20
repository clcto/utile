/*
 * Frame.cpp
 *   one frame/tile on the screen
 *
 * Copyright (c) 2010
 *   Carick Wienke <carick dot wienke at gmail dot com>
 */

#include <X11/Xlib.h>
#include <stdlib.h>
#include <vector>

#include "Frame.hpp"
#include "SmartWindow.hpp"

/* 
 * creates a new frame with the information passed
 *
 * x, y: the x and y locations
 * w, h: the width and height
 */
Frame::Frame( unsigned int x, unsigned int y, 
              unsigned int w, unsigned int h ):
   _xLoc( x ),
   _yLoc( y ),
   _width( w ),
   _height( h )
{/*{{{*/
   XSetWindowAttributes attr;
   attr.background_pixel = BlackPixel( utile::display, 0 );
   attr.border_pixel     = WhitePixel( utile::display, 0 );
   
   unsigned char bw = 1; 
   _background = XCreateWindow( 
                    utile::display, utile::root, 
                    _xLoc, _yLoc,
                    _width - 2*bw, 
                    _height - 2*bw,
                    bw, CopyFromParent,
                    InputOutput, CopyFromParent,
                    CWBackPixel | CWBorderPixel, &attr );
   XMapWindow( utile::display, _background );
}/*}}}*/

/*
 * adds a window to the frame
 *
 * newWin: window to add
 */
void Frame::addWindow( Window newWin )
{ /*{{{*/
   unsigned char bw = 1; //Global::config.borderWidth();

   XReparentWindow( utile::display, newWin, 
                    _background, 0, 0 );
   XMapWindow( utile::display, newWin );
   XResizeWindow( utile::display, newWin,
      _width - 2*bw, _height - 2*bw );
   
   SmartWindow sw( newWin, this );

   _windows.push_back( sw );
   _curWindow = _windows.size() - 1;
} /*}}}*/

void Frame::moveResize( unsigned int x, unsigned int y,
                        unsigned int w, unsigned int h )
{
   unsigned char bw = 1; // Global::config.borderWidth();

   XMoveResizeWindow( utile::display, _background, x, y, 
                      w - 2*bw, h - 2*bw );

   if( !_windows.empty() )
   {
      XMoveResizeWindow( utile::display, 
         _windows[ _curWindow ].getXWindow(), x, y, w, h );
   }

   _xLoc   =  x;
   _yLoc   =  y;
   _width  =  w;
   _height =  h;
}

unsigned int Frame::width()
{
   return _width;
}

unsigned int Frame::height()
{
   return _height;
}

unsigned int Frame::xLoc()
{
   return _xLoc;
}

unsigned int Frame::yLoc()
{
   return _yLoc;
}
