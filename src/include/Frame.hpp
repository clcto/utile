/*
 * Frame.hpp
 * Copyright (c) 2010-2018
 *   Carick Wienke <carick dot wienke at gmail dot com> 
 */

#pragma once

#include <X11/Xlib.h>
#include <vector>
#include "SmartWindow.hpp"
#include "utile.hpp"

class Frame
{
   public:
      Frame( uint x, uint y, uint w, uint h );
      void addWindow( Window newWin );
      void moveResize( uint x, uint y,
                       uint w, uint h );
      bool close();

      uint width();
      uint height();
      uint xLoc();
      uint yLoc();

      void remove( Window w );
      void setActive( bool value );
      
      static void setInactive( XColor );
      static void setActive( XColor );

   private:
      std::vector<SmartWindow> _windows;
      unsigned char       _curWindow;
      Window              _background;
      uint                _xLoc,  _yLoc;
      uint                _width, _height;

      static XColor inactive_border, active_border;
};
