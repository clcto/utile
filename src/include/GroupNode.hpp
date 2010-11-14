/*
 * GroupNode.hpp
 */

#ifndef GROUP_NODE_HPP_
#define GROUP_NODE_HPP_

#include <X11/Xlib.h>
#include "Frame.hpp"

class Group;

class GroupNode
{
   public:
      GroupNode();
      GroupNode( Group*, Window root,
             unsigned int, unsigned int, unsigned int, unsigned int,
             GroupNode* parent = NULL, Frame* frame = NULL );
      GroupNode* splitHorizontal();
      GroupNode* splitVertical();
      void addWindow( Window w );
      void init( Group*,Window root, unsigned int, 
                 unsigned int, unsigned int, unsigned int,
                 GroupNode* parent = NULL, Frame* frame = NULL );
      bool close();
      void remove( Window w );

   private:
      GroupNode* _children[2];
      GroupNode* _parent;
      Frame* _frame;
      char   _bSplitVertical;
      Window _root;
      Group*  _group;
};

#endif /* GROUP_NODE_HPP_ */
