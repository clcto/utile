/*
 * Frame.cpp
 */

#include <X11/Xlib.h>
#include <stdlib.h>
#include <vector>

#include "include/Frame.h"
#include "include/Config.h"
#include "include/e_globals.h"
#include "include/SmartWindow.h"

Frame::Frame( unsigned int x, unsigned int y, 
              unsigned int w, unsigned int h ):
   _xLoc( x ),
   _yLoc( y ),
   _width( w ),
   _height( h )
{
   XSetWindowAttributes attr;
   attr.background_pixel = BlackPixel( g_display, 0 );
   attr.border_pixel     = WhitePixel( g_display, 0 );
   
   unsigned char bw = config.borderWidth();
   _background = XCreateWindow( g_display, g_rootWindow, 
                    _xLoc, _yLoc,
                    _width - 2*bw, 
                    _height - 2*bw,
                    bw, CopyFromParent,
                    InputOutput, CopyFromParent,
                    CWBackPixel | CWBorderPixel, &attr );
   XMapWindow( g_display, _background );
}

void Frame::addWindow( Window newWin )
{
   unsigned char bw = config.borderWidth();

   XReparentWindow( g_display, newWin, _background, 0, 0 );
   XMapWindow( g_display, newWin );
   XResizeWindow( g_display, newWin,
      _width - 2*bw, _height - 2*bw );
   
   SmartWindow sw( newWin, this );

   _windows.push_back( sw );
   _curWindow = _windows.size() - 1;
}

void Frame::moveResize( unsigned int x, unsigned int y,
                        unsigned int w, unsigned int h )
{
   unsigned char bw = config.borderWidth();

   XMoveResizeWindow( g_display, _background, x, y, 
                      w - 2*bw, h - 2*bw );

   if( !_windows.empty() )
   {
      XMoveResizeWindow( g_display, 
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
