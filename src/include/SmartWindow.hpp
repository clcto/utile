/*
 * SmartWindow.h
 */

#ifndef SMARTWINDOW_H_
#define SMARTWINDOW_H_

#include <X11/Xlib.h>
#include "Frame.hpp"

class Frame;

class SmartWindow
{
	public:
      SmartWindow( Window& w, Frame* const f = NULL );
      void moveTo( Frame *f );
      Window getXWindow();

	private:
      Window _window;
      Frame* _frame;
};

#endif /* SMARTWINDOW_H_ */
