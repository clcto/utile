/*
 * Group.h
 */

#ifndef GROUP_H_
#define GROUP_H_

#include <X11/Xlib.h>
#include <string>

#include "GroupNode.h"

using namespace std;

class Group
{
   public:
      Group( Window root, string layoutname = "default" );
      void setCurFrame( Frame* );
      Frame* getCurFrame();

   private:
      Window    _rootWindow;
      GroupNode _rootGroupNode;
      Frame*    _curFrame;
     
      void runLayout( string ); 
};

#endif
