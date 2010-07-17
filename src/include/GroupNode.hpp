/*
 * GroupNode.h
 */

#ifndef GROUP_NODE_H_
#define GROUP_NODE_H_

#include <X11/Xlib.h>
#include "Frame.hpp"

class Group;

class GroupNode
{
   public:
      GroupNode();
      GroupNode( const Group*, Window root,
             unsigned int, unsigned int, unsigned int, unsigned int,
             GroupNode* parent = NULL, Frame* frame = NULL );
      GroupNode* splitHorizontal();
      GroupNode* splitVertical();
      void addWindow( Window w );
      void init( const Group*,Window root, unsigned int, 
                 unsigned int, unsigned int, unsigned int,
                 GroupNode* parent = NULL, Frame* frame = NULL );

   private:
      GroupNode* _children[2];
      GroupNode* _parent;
      Frame* _frame;
      char   _bSplitVertical;
      Window _root;
      const Group*  _page;
};

#endif /* GROUP_NODE_H_ */
