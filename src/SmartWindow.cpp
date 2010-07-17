/*
 * SmartWindow.cpp
 */

#include <X11/Xlib.h>
#include "Frame.hpp"
#include "SmartWindow.hpp"

/*
 * creates a new smart window with window
 * (and frame) given
 */
SmartWindow::SmartWindow( Window& w, Frame* const f ):
   _window( w ), _frame( f ) {}

/*
 * moves the window to a new Frame
 */
void SmartWindow::moveTo( Frame *f )
{

}

/*
 * gets the Xlib Window this holds
 */
Window SmartWindow::getXWindow()
{
   return _window;
}
