/*
 * Frame.h
 */

#ifndef FRAME_H_
#define FRAME_H_

#include <X11/Xlib.h>
#include <vector>
#include "SmartWindow.hpp"
#include "utile.hpp"

using namespace std;

class SmartWindow;

class Frame
{
	public:
      Frame( unsigned int x, unsigned int y, 
             unsigned int w, unsigned int h );
      void addWindow( Window newWin );
      void moveResize( unsigned int x, unsigned int y,
                       unsigned int w, unsigned int h );
      unsigned int width();
      unsigned int height();
      unsigned int xLoc();
      unsigned int yLoc();

	private:
      vector<SmartWindow> _windows;
      unsigned char       _curWindow;
      Window              _background;
		unsigned int        _xLoc,  _yLoc;
		unsigned int        _width, _height;
};

#endif /* FRAME_H_ */
