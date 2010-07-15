/*
 * Page.h
 */

#ifndef PAGE_H_
#define PAGE_H_

#include <X11/Xlib.h>
#include <string>

#include "GroupNode.h"

using namespace std;

class Page
{
   public:
      Page( Window root, string layoutname = "default" );
      void setCurFrame( Frame* );
      Frame* getCurFrame();

   private:
      Window    _rootWindow;
      GroupNode _rootGroupNode;
      Frame*    _curFrame;
     
      void runLayout( string ); 
};

#endif
