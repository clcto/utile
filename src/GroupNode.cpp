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


GroupNode* GroupNode::split( Split s )
{
   if( _children[0] || _children[1] )
   {
      utile::log.write( LogLevel_Error,
         "Trying to split a group that is already "
         "split." );
      return this;
   }

   int w  = _frame->width();
   int h  = _frame->height();
   int x  = _frame->xLoc();
   int y  = _frame->yLoc();

   switch( s )
   {
      case Split_Horizontal:
         _children[0] = 
            new GroupNode( _group, _root, x, y, 
                           w/2, h, this, _frame );
         _children[1] =
            new GroupNode( _group, _root, x+w/2, 
                           y, w/2, h, this );
            break;

      case Split_Vertical:
         _children[0] = 
            new GroupNode( _group, _root, x, y, 
                           w, h/2, this, _frame );
         _children[1] =
            new GroupNode( _group, _root, x, 
                           y+h/2, w, h/2, this );
            break;
   }
         
   _split = s;
   _frame = NULL;
   return _children[0];
}

void GroupNode::addWindow( Window w )
{
   if( _frame )
      _frame->addWindow( w );
}

bool GroupNode::close()
{
   utile::log.write( LogLevel_Trace, "GroupNode::close()" );
   if( _frame )
      return _frame->close();
   else
      return false;
}

void GroupNode::remove( Window win )
{
   utile::log.write( LogLevel_Trace, "GroupNode::remove( %d )",
                     win );
   if( _frame )
      _frame->remove( win );
}

GroupNode* GroupNode::right()
{
   // this is not quite right
   // what do we do if we iterate up the
   //    tree and there is no "right"
   if( !_parent )
      return NULL;

   switch( _parent->_split )
   {
      case Split_Vertical:
         return _parent->right();
      case Split_Horizontal:
         if( this == _parent->_children[0] )
            return _parent->_children[1];
         else
            return _parent->right();
      default:
         utile::log.write( LogLevel_Error,
            "GroupNode::right(): caught an unexpected "
            "value in switch (%d)", _parent->_split );
         return NULL;
   }
}
