/*
 * SmartWindow.hpp
 * Copyright (c) 2010-2018
 *   Carick Wienke <carick dot wienke at gmail dot com> 
 */

#pragma once

#include <X11/Xlib.h>

class Frame;

class SmartWindow
{
	public:
      SmartWindow( Window& w, Frame * const f = NULL );
      void moveTo( Frame *f );
      Window getXWindow();
      void close();

      bool operator==( Window w ) const;

	private:
      Window _window;
      Frame* _frame;
};
