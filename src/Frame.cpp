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
{
   XSetWindowAttributes attr;
   XColor purple;
   purple.red = 0xFFFF;
   purple.blue = 0xFFFF;
   purple.green = 0;
   XAllocColor( utile::display, DefaultColormap( utile::display, 0 ), &purple );
   attr.background_pixel = BlackPixel( utile::display, 0 );
   //attr.border_pixel     = WhitePixel( utile::display, 0 );
   attr.border_pixel = purple.pixel;
   
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
   XSelectInput( utile::display, _background, SubstructureRedirectMask );
}

/*
 * adds a window to the frame
 *
 * newWin: window to add
 */
void Frame::addWindow( Window newWin )
{ 
   unsigned char bw = 1; //Global::config.borderWidth();

   XSelectInput( utile::display, newWin,
      StructureNotifyMask );

   XReparentWindow( utile::display, newWin, 
                    _background, 0, 0 );
   XMapWindow( utile::display, newWin );
   XResizeWindow( utile::display, newWin,
      _width - 2*bw, _height - 2*bw );
   
   SmartWindow sw( newWin, this );

   _windows.push_back( sw );
   _curWindow = _windows.size() - 1;
} 

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

bool Frame::close()
{
   utile::log.write( LogLevel_Trace, "Frame::close()\ncur: %d size: %d", _curWindow, _windows.size() );
   if( _curWindow >= 0 && _curWindow < _windows.size() )
   {
      _windows[ _curWindow ].close();
      _windows.erase( _windows.begin() + _curWindow );
      --_curWindow;
      return false;
   }
   else
   {
      // close the frame itself and return true

      // temporary
      return false;
   }
}

void Frame::remove( Window win )
{
   utile::log.write( LogLevel_Trace, "Frame::remove( %d )",
                     win );

   for( vector<SmartWindow>::iterator it = _windows.begin();
        it < _windows.end(); ++it )
   {
      if( (*it) == win )
      {
         _windows.erase( it );
         --_curWindow;
      }
   }
}
