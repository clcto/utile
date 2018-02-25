/*
 * Group.hpp
 * Copyright (c) 2010-2018
 *   Carick Wienke <carick dot wienke at gmail dot com> 
 */

#pragma once


#include <X11/Xlib.h>
#include <string>

#include "GroupNode.hpp"
#include "utile.hpp"
#include "Split.hpp"
#include "Direction.hpp"

class Group
{
   public:
      Group( Window root, const std::string& layoutname = "default" );
      GroupNode* getCur();
      void split( Split s );
      void close();
      void select( Direction );
      void resize( Direction side, int pixels );

   private:
      Window     _rootWindow;
      std::unique_ptr<GroupNode> _rootNode;
      GroupNode* _curNode;
     
      void runLayout( const std::string& layoutname ); 
};
