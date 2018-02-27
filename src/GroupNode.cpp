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
              int x, int y, int w, int h,
              GroupNode* parent,
              std::unique_ptr<Frame>&& frame ) :
   _group( group ),
   _root( root ),
   _parent( parent ),
   _frame( std::move( frame ) ),
   _lastAccess( 0 ),
   _xLoc( x ),
   _yLoc( y ),
   _width( w ),
   _height( h )
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
   _frame = nullptr;
   _lastAccess = 0;
   return _children[0].get();
}

void GroupNode::resize( Direction side, int pixels )
{
    auto resizeRoot = findParentSplit( side );
    if( !resizeRoot )
    {
        utile::log.write( LogLevel::Info, 
            "Could not find split to resize" );
        return;
    }

    // todo: check if resizing too much
    doResize( side, pixels );

    // traverse up the tree until we reach the root of the resize,
    // resizing the other child if it affected by the resize
    auto travChild = this;
    auto travParent = travChild->_parent;
    while( travParent != resizeRoot )
    {
        // the other child is affected by the resize
        // if and only if
        //   we are resizing perpendicular to the split
        //
        // this is true because we haven't reached the root of the resize yet

        auto perpendicularSplit =
            side == Direction::Right || side == Direction::Left ?
                Split::Horizontal :
                Split::Vertical;
        if( travParent->_split == perpendicularSplit )
        {
            travParent->otherChild( travChild )->doResize( side, pixels );
        }

        travChild = travParent;
        travParent = travChild->_parent;
    }

    // have to invert the side/pixels when resizing the other side
    // of the resize root to keep the screen tiled.
    auto oppositeSide = opposite( side );
    auto invertedPixels = -pixels;

    resizeRoot->otherChild( travChild )->doResize( oppositeSide, invertedPixels );
}

void GroupNode::doResize( Direction side, int pixels )
{
    // update current size
    if( side == Direction::Up || side == Direction::Down )
    {
        _height += pixels;
        if( side == Direction::Up )
            _yLoc -= pixels;
    }

    if( side == Direction::Right || side == Direction::Left )
    {
        _width += pixels;
        if( side == Direction::Left )
            _xLoc -= pixels;
    }

    // if we are a leaf, just resize
    if( _frame )
    {
        _frame->moveResize( _xLoc, _yLoc, _width, _height );
    }
    else // we have children, tell them to resize
    {
        // if we are resizing parallel to the split
        // then we scale the resize, just half for each child
        // 
        // otherwise (if resizing perpendicular), all
        // children get the same resize

        auto parallelSplit =
            side == Direction::Right || side == Direction::Left ?
                Split::Vertical :
                Split::Horizontal;
                 
        if( _split == parallelSplit )
        {
            const auto firstChildResize = pixels / 2;
            _children[ 0 ]->doResize( side, firstChildResize );

            const auto secondChildResize = pixels - firstChildResize;
            _children[ 1 ]->doResize( side, secondChildResize );
        }
        else
        {
            for( auto& child : _children )
            {
                child->doResize( side, pixels );
            }
        }
    }
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
      case Direction::Right:
         utile::log.write( LogLevel::Debug, "right" );
         return right();
      case Direction::Left:
         utile::log.write( LogLevel::Debug, "left" );
         return left();
      case Direction::Down:
         utile::log.write( LogLevel::Debug, "down" );
         return down();
      case Direction::Up:
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
         return nullptr;
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
         return nullptr;
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
         return nullptr;
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
         return nullptr;
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

GroupNode* GroupNode::findParentSplit( Direction side )
{

    // Horizontal Split
    //    +-----------+
    //    |     0     |
    //    |-----------|
    //    |     1     |
    //    +-----------+
    //
    // Vertical Split
    //    +-----------+
    //    |     |     |
    //    +  0  |  1  +
    //    |     |     |
    //    +-----------+
    auto splitType =
        side == Direction::Left || side == Direction::Right ?
            Split::Vertical :
            Split::Horizontal;
    auto childIndex = 
        side == Direction::Right || side == Direction::Down ?
            0 :
            1;

    auto curChild = this;
    auto curNode = curChild->_parent;
    while( curNode )
    {
        // if the node is split the way we are expecting and 
        // and the child that we are searching from is at the correct index
        //    ie. when finding the node that has the split to the left
        //        of the current node, then if we are split vectically
        //        and the child is index 1, then the current node has the split
        //        then if the parent 
        if( curNode->_split == splitType &&
            curChild == curNode->_children[ childIndex ].get() )
        {
            return curNode;
        }

        // didn't find it, keep going up the tree
        curChild = curNode;
        curNode = curChild->_parent;
    }

    // didn't find it, must be null to exit the previous loop.
    return curNode;
}

GroupNode* GroupNode::otherChild( GroupNode* child )
{
    if( child == _children[ 0 ].get() )
        return _children[ 1 ].get();
    else if( child == _children[ 1 ].get() )
        return _children[ 0 ].get();

    throw std::invalid_argument( "child provided is not one of the node's children" );
}


