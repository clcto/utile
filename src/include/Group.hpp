/*
 * Group.hpp
 */

#ifndef GROUP_HPP_
#define GROUP_HPP_

#include <X11/Xlib.h>
#include <string>

#include "GroupNode.hpp"

using namespace std;

class Group
{
   public:
      Group( Window root, string layoutname = "default" );
      void setCur( GroupNode* );
      GroupNode* getCur();

   private:
      Window     _rootWindow;
      GroupNode* _rootNode;
      GroupNode* _curNode;
     
      void runLayout( string ); 
};

#endif /* GROUP_HPP_ */
