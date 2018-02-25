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
             unsigned int x, unsigned int y,
             unsigned int w, unsigned int h,
             GroupNode* parent = nullptr, 
             std::unique_ptr<Frame>&& frame = nullptr );

      bool close();

      GroupNode* split( Split );
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

      Group*  _group;
      Window _root;
      GroupNode* _parent;
      std::unique_ptr<Frame> _frame;

      int _lastAccess;

      Split _split;
      std::array< std::unique_ptr<GroupNode>, 2> _children;
};

