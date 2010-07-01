/*
 * Page.h
 */

#ifndef PAGE_H_
#define PAGE_H_

#include <X11/Xlib.h>
#include <string>

#include "Group.h"

class Page
{
   public:
      Page( Window root, string layoutname = "default" );

   private:
      Window _rootWindow;
      Group  _rootGroup;
     
      void runLayout( string ); 
};

#endif
