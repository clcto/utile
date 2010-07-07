/*
 * Page.h
 */

#ifndef PAGE_H_
#define PAGE_H_

#include <X11/Xlib.h>
#include <string>

#include "Group.h"

using namespace std;

class Page
{
   public:
      Page( Window root, string layoutname = "default" );
      void setCurGroup( Group* );
      Group* getCurGroup();

   private:
      Window  _rootWindow;
      Group   _rootGroup;
      Group*  _curGroup;
     
      void runLayout( string ); 
};

#endif
