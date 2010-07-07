/*
 * Group.cpp
 */

#include <X11/Xlib.h>
#include "Frame.h"
#include "Group.h"

using namespace std;

Group::Group(){}

Group::Group( const Page* pg, Window r, 
              unsigned int x, unsigned int y, 
              unsigned int w, unsigned int h,
              Group* p, Frame* f)
{/*{{{*/
   init( pg, r, x, y, w, h, p, f );
}/*}}}*/

void Group::init( const Page* pg,Window r, 
                  unsigned int x, unsigned int y, 
                  unsigned int w, unsigned int h,
                  Group* p, Frame* f)
{/*{{{*/
   // copy data
   _page = pg;
   _parent = p;
   _frame  = f;
   _root   = r;

   if( !_frame )
      _frame = new Frame( x, y, w, h );
   else
      _frame->moveResize( x, y, w, h );

   _children[0] = NULL;
   _children[1] = NULL;
}/*}}}*/


Group* Group::splitHorizontal()
{/*{{{*/
   int w  = _frame->width();
   int h  = _frame->height();
   int x  = _frame->xLoc();
   int y  = _frame->yLoc();

   _children[0] = new Group( _page, _root, x, y, w/2, h, this, _frame );
   _children[1] = new Group( _page, _root, x+w/2, y, w/2, h, this );
   _bSplitVertical = 0;
   _frame = NULL;
   return _children[0];
}/*}}}*/

Group* Group::splitVertical()
{/*{{{*/
   return NULL;
}/*}}}*/

void Group::addWindow( Window w )
{/*{{{*/
   if( _frame )
      _frame->addWindow( w );
}/*}}}*/
