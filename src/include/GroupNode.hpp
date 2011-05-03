/*
 * GroupNode.hpp
 */

#ifndef GROUP_NODE_HPP_
#define GROUP_NODE_HPP_

#include <X11/Xlib.h>
#include "Frame.hpp"
#include "Split.hpp"
#include "Direction.hpp"

class Group;

class GroupNode
{
   public:
      GroupNode();
      GroupNode( Group*, Window root,
             unsigned int, unsigned int, unsigned int, unsigned int,
             GroupNode* parent = NULL, Frame* frame = NULL );
      GroupNode* split( Split );
      void addWindow( Window w );
      void init( Group*,Window root, unsigned int, 
                 unsigned int, unsigned int, unsigned int,
                 GroupNode* parent = NULL, Frame* frame = NULL );
      bool close();
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

      GroupNode* _children[2];
      GroupNode* _parent;
      Split _split;
      Frame* _frame;
      Window _root;
      Group*  _group;
      int _lastAccess;
};

#endif /* GROUP_NODE_HPP_ */
