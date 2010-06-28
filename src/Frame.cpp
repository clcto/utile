/*
 * Frame.cpp
 */

#include <X11/Xlib.h>
#include <stdlib.h>
#include <vector>

#include "Frame.h"
#include "Config.h"
#include "Global.h"
#include "SmartWindow.h"

Frame::Frame( Display* d, unsigned int x, unsigned int y, 
              unsigned int w, unsigned int h ):
   _disp( d ),
   _xLoc( x ),
   _yLoc( y ),
   _width( w ),
   _height( h )
{
   XSetWindowAttributes attr;
   attr.background_pixel = BlackPixel( _disp, 0 );
   attr.border_pixel     = WhitePixel( _disp, 0 );
   
   unsigned char bw = Global::config.borderWidth();
   _background = XCreateWindow( 
                    _disp, Global::rootWindow, 
                    _xLoc, _yLoc,
                    _width - 2*bw, 
                    _height - 2*bw,
                    bw, CopyFromParent,
                    InputOutput, CopyFromParent,
                    CWBackPixel | CWBorderPixel, &attr );
   XMapWindow( _disp, _background );
}

void Frame::addWindow( Window newWin )
{
   unsigned char bw = Global::config.borderWidth();

   XReparentWindow( _disp, newWin, _background, 0, 0 );
   XMapWindow( _disp, newWin );
   XResizeWindow( _disp, newWin,
      _width - 2*bw, _height - 2*bw );
   
   SmartWindow sw( newWin, this );

   _windows.push_back( sw );
   _curWindow = _windows.size() - 1;
}

void Frame::moveResize( unsigned int x, unsigned int y,
                        unsigned int w, unsigned int h )
{
   unsigned char bw = Global::config.borderWidth();

   XMoveResizeWindow( _disp, _background, x, y, 
                      w - 2*bw, h - 2*bw );

   if( !_windows.empty() )
   {
      XMoveResizeWindow( _disp, 
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
