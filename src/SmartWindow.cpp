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

void SmartWindow::close()
{
   utile::log.write( LogLevel_Trace, "SmartWindow::close()" );
   XEvent delEv;
   delEv.type = ClientMessage;
   delEv.xclient.window = _window;
   delEv.xclient.message_type = 
      XInternAtom( utile::display, "WM_PROTOCOLS", True );
   delEv.xclient.format = 32;
   delEv.xclient.data.l[0] = 
      XInternAtom( utile::display, "WM_DELETE_WINDOW", True );
   delEv.xclient.data.l[1] = CurrentTime;
   XSendEvent( utile::display, _window, False, NoEventMask, &delEv );
}

bool SmartWindow::operator==( Window w )
{
   return _window == w;
}
