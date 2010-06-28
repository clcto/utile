/*
 * Group.cpp
 */

#include <X11/Xlib.h>
#include "Frame.h"
#include "Group.h"

using namespace std;

/*
 * at some point this will take in a 
 * layout... but now lets just make one
 * frame fullscreen
 */
Group::Group( unsigned int x, unsigned int y, 
              unsigned int w, unsigned int h,
              Group* p, Frame* f):
   _parent(p), _frame(f)
{
   if( !_frame )
      _frame = new Frame( x, y, w, h );
   else
      _frame->moveResize( x, y, w, h );

   _children[0] = NULL;
   _children[1] = NULL;
}

Group* Group::splitHorizontal()
{
   int w  = _frame->width();
   int h  = _frame->height();
   int x  = _frame->xLoc();
   int y  = _frame->yLoc();

   _children[0] = new Group( x,     y, w/2, h, this, _frame );
   _children[1] = new Group( x+w/2, y, w/2, h, this );
   _bSplitVertical = 0;
   _frame = NULL;
   return _children[0];
}

Group* Group::splitVertical()
{
   return NULL;
}

void Group::addWindow( Window w )
{
   if( _frame )
      _frame->addWindow( w );
}
