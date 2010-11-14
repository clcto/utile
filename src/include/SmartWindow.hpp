/*
 * SmartWindow.hpp
 */

#ifndef SMARTWINDOW_HPP_
#define SMARTWINDOW_HPP_

#include <X11/Xlib.h>
#include "Frame.hpp"

class Frame;

class SmartWindow
{
	public:
      SmartWindow( Window& w, Frame* const f = NULL );
      void moveTo( Frame *f );
      Window getXWindow();
      void close();

      bool operator==( Window w );

	private:
      Window _window;
      Frame* _frame;
};

#endif /* SMARTWINDOW_HPP_ */
