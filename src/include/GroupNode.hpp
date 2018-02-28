/*
 * GroupNode.hpp
 * Copyright (c) 2010-2018
 *   Carick Wienke <carick dot wienke at gmail dot com> 
 */

#pragma once

#include <X11/Xlib.h>
#include "Frame.hpp"
#include "Split.hpp"
#include "Direction.hpp"

class Group;

class GroupNode
{
   public:
      GroupNode();
      GroupNode( Group* group, Window root,
             int x, int y, int w, int h,
             GroupNode* parent = nullptr, 
             std::unique_ptr<Frame>&& frame = nullptr );

      bool close();

      GroupNode* split( Split );
      void resize( Direction side, int pixels );

      void addWindow( Window w );
      void remove( Window w );

      GroupNode* getNode( Direction );
      void setActive( bool );

   private:

      GroupNode* right();
      GroupNode* left();
      GroupNode* down();
      GroupNode* up();

      void fixLastAccess();
      void fixLastAccess( GroupNode* );

      GroupNode* findParentSplit( Edge side );
      void doResize( Direction side, int pixels );
      void doResize( int x, int y, int width, int height );

      GroupNode* otherChild( GroupNode* child );

      Group*  _group;
      Window _root;
      GroupNode* _parent;
      std::unique_ptr<Frame> _frame;

      int _lastAccess;

      Split _split;
      std::array< std::unique_ptr<GroupNode>, 2> _children;

      int _xLoc;
      int _yLoc;
      int _width;
      int _height;

      float _firstChildRatio;
};

