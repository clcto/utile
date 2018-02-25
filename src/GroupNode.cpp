/*
 * GroupNode.cpp
 * Copyright (c) 2010-2018
 *   Carick Wienke <carick dot wienke at gmail dot com>
 */

#include <X11/Xlib.h>
#include "Frame.hpp"
#include "GroupNode.hpp"

#include <exception>

GroupNode::GroupNode(){}

GroupNode::GroupNode( Group* group, Window root,
              unsigned int x, unsigned int y, 
              unsigned int w, unsigned int h,
              GroupNode* parent,
              std::unique_ptr<Frame>&& frame ) :
   _group( group ),
   _root( root ),
   _parent( parent ),
   _frame( std::move( frame ) ),
   _lastAccess( 0 )
{
   if( !_frame )
      _frame = std::make_unique<Frame>( x, y, w, h );
   else
      _frame->moveResize( x, y, w, h );

   _children[0] = nullptr;
   _children[1] = nullptr;
}

void GroupNode::setActive( bool active )
{
   if( _frame )
   {
      _frame->setActive( active );
      if( active )
         fixLastAccess();
   }
}

GroupNode* GroupNode::split( Split s )
{
   if( _children[0] || _children[1] )
   {
      utile::log.write( LogLevel::Error,
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
      case Split::Vertical:
         _children[0] = 
            std::make_unique<GroupNode>( _group, _root, x, y, 
                           w/2, h, this, std::move( _frame ) );
         _children[1] =
            std::make_unique<GroupNode>( _group, _root, x+w/2, 
                           y, w/2, h, this );
            break;

      case Split::Horizontal:
         _children[0] = 
            std::make_unique<GroupNode>( _group, _root, x, y, 
                           w, h/2, this, std::move( _frame ) );
         _children[1] =
            std::make_unique<GroupNode>( _group, _root, x, 
                           y+h/2, w, h/2, this );
            break;
   }
         
   _split = s;
   _frame = NULL;
   _lastAccess = 0;
   return _children[0].get();
}

void GroupNode::addWindow( Window w )
{
   if( _frame )
      _frame->addWindow( w );
}

bool GroupNode::close()
{
   utile::log.write( LogLevel::Trace, "GroupNode::close()" );
   if( _frame )
      return _frame->close();
   else
      return false;
}

void GroupNode::remove( Window win )
{
   utile::log.write( LogLevel::Trace, "GroupNode::remove( %d )",
                     win );
   if( _frame )
      _frame->remove( win );
}

GroupNode* GroupNode::getNode( Direction d )
{
   switch( d )
   {
      case Direction_Right:
         utile::log.write( LogLevel::Debug, "right" );
         return right();
      case Direction_Left:
         utile::log.write( LogLevel::Debug, "left" );
         return left();
      case Direction_Down:
         utile::log.write( LogLevel::Debug, "down" );
         return down();
      case Direction_Up:
         utile::log.write( LogLevel::Debug, "up" );
         return up();
      default:
         throw std::runtime_error( "Unexpected Direction" );
   }
}

GroupNode* GroupNode::right()
{
   if( !_parent )
   {
      switch( _split )
      {
         case Split::Horizontal:
            return _children[ _lastAccess ].get();
         case Split::Vertical:
            return _children[0].get();
      }
   }

   GroupNode* node;

   switch( _parent->_split )
   {
      case Split::Horizontal:
         node = _parent->right();
         break;
      case Split::Vertical:
         if( this == _parent->_children[0].get() )
            node = _parent->_children[1].get();
         else
            node = _parent->right();
         break;
      default:
         utile::log.write( LogLevel::Error,
            "GroupNode::right(): caught an unexpected "
            "value in switch (%d)", _parent->_split );
         return NULL;
   }

   while( !node->_frame )
   {
      switch( node->_split )
      {
         case Split::Horizontal:
            node = node->_children[ node->_lastAccess ].get();
            break;
         case Split::Vertical:
            node = node->_children[0].get();
            break;
      }
   }

   return node;
}

GroupNode* GroupNode::left()
{
   if( !_parent )
   {
      switch( _split )
      {
         case Split::Horizontal:
            return _children[ _lastAccess ].get();
         case Split::Vertical:
            return _children[1].get();
      }
   }

   GroupNode* node;

   switch( _parent->_split )
   {
      case Split::Horizontal:
         node = _parent->left();
         break;
      case Split::Vertical:
         if( this == _parent->_children[1].get() )
            node = _parent->_children[0].get();
         else
            node = _parent->left();
         break;
      default:
         utile::log.write( LogLevel::Error,
            "GroupNode::left(): caught an unexpected "
            "value in switch (%d)", _parent->_split );
         return NULL;
   }

   while( !node->_frame )
   {
      switch( node->_split )
      {
         case Split::Horizontal:
            node = node->_children[ node->_lastAccess ].get();
            break;
         case Split::Vertical:
            node = node->_children[1].get();
            break;
      }
   }

   return node;
}

GroupNode* GroupNode::down()
{
   if( !_parent )
   {
      switch( _split )
      {
         case Split::Vertical:
            return _children[ _lastAccess ].get();
         case Split::Horizontal:
            return _children[0].get();
      }
   }

   GroupNode* node;

   switch( _parent->_split )
   {
      case Split::Vertical:
         node = _parent->down();
         break;
      case Split::Horizontal:
         if( this == _parent->_children[0].get() )
            node = _parent->_children[1].get();
         else
            node = _parent->down();
         break;
      default:
         utile::log.write( LogLevel::Error,
            "GroupNode::down(): caught an unexpected "
            "value in switch (%d)", _parent->_split );
         return NULL;
   }

   while( !node->_frame )
   {
      switch( node->_split )
      {
         case Split::Vertical:
            node = node->_children[ node->_lastAccess ].get();
            break;
         case Split::Horizontal:
            node = node->_children[0].get();
            break;
      }
   }

   return node;
}

GroupNode* GroupNode::up()
{
   if( !_parent )
   {
      switch( _split )
      {
         case Split::Vertical:
            return _children[ _lastAccess ].get();
         case Split::Horizontal:
            return _children[1].get();
      }
   }

   GroupNode* node;

   switch( _parent->_split )
   {
      case Split::Vertical:
         node = _parent->up();
         break;
      case Split::Horizontal:
         if( this == _parent->_children[1].get() )
            node = _parent->_children[0].get();
         else
            node = _parent->up();
         break;
      default:
         utile::log.write( LogLevel::Error,
            "GroupNode::up(): caught an unexpected "
            "value in switch (%d)", _parent->_split );
         return NULL;
   }

   while( !node->_frame )
   {
      switch( node->_split )
      {
         case Split::Vertical:
            node = node->_children[ node->_lastAccess ].get();
            break;
         case Split::Horizontal:
            node = node->_children[1].get();
            break;
      }
   }

   return node;
}

void GroupNode::fixLastAccess()
{
   if( _parent )
      _parent->fixLastAccess( this );
}

void GroupNode::fixLastAccess( GroupNode* child )
{
   if( child == _children[0].get() )
      _lastAccess = 0;
   else if( child == _children[1].get() )
      _lastAccess = 1;

   if( _parent )
      _parent->fixLastAccess( this );
}
