/*
 * GroupNode.cpp
 */

#include <X11/Xlib.h>
#include "Frame.hpp"
#include "GroupNode.hpp"

using namespace std;

GroupNode::GroupNode(){}

GroupNode::GroupNode( Group* g, Window r, 
              unsigned int x, unsigned int y, 
              unsigned int w, unsigned int h,
              GroupNode* p, Frame* f)
{
   init( g, r, x, y, w, h, p, f );
}

void GroupNode::init( Group* g, Window r, 
                  unsigned int x, unsigned int y, 
                  unsigned int w, unsigned int h,
                  GroupNode* p, Frame* f)
{
   // copy data
   _group   = g;
   _parent = p;
   _frame  = f;
   _root   = r;

   if( !_frame )
      _frame = new Frame( x, y, w, h );
   else
      _frame->moveResize( x, y, w, h );

   _children[0] = NULL;
   _children[1] = NULL;
}


GroupNode* GroupNode::splitHorizontal()
{
   int w  = _frame->width();
   int h  = _frame->height();
   int x  = _frame->xLoc();
   int y  = _frame->yLoc();

   _children[0] = new GroupNode( _group, _root, x, y, w/2, h, this, _frame );
   _children[1] = new GroupNode( _group, _root, x+w/2, y, w/2, h, this );
   _bSplitVertical = 0;
   _frame = NULL;
   return _children[0];
}

GroupNode* GroupNode::splitVertical()
{
   return NULL;
}

void GroupNode::addWindow( Window w )
{
   if( _frame )
      _frame->addWindow( w );
}
