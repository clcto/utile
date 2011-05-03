/*
 * Frame.hpp
 */

#ifndef FRAME_HPP_
#define FRAME_HPP_

#include <X11/Xlib.h>
#include <vector>
#include "SmartWindow.hpp"
#include "utile.hpp"

using namespace std;

class SmartWindow;

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
      void setActive( bool );
      
      static void setInactive( XColor );
      static void setActive( XColor );

   private:
      vector<SmartWindow> _windows;
      unsigned char       _curWindow;
      Window              _background;
      uint                _xLoc,  _yLoc;
      uint                _width, _height;

      static XColor inactive_border, active_border;
};

#endif /* FRAME_HPP_ */
