/*
 * Group.h
 */

#ifndef GROUP_H_
#define GROUP_H_

#include <X11/Xlib.h>
#include "Frame.h"

class Page;

class Group
{
   public:
      Group();
      Group( const Page*, Window root,
             unsigned int, unsigned int, unsigned int, unsigned int,
             Group* parent = NULL, Frame* frame = NULL );
      Group* splitHorizontal();
      Group* splitVertical();
      void addWindow( Window w );
      void init( const Page*,Window root, unsigned int, 
                 unsigned int, unsigned int, unsigned int,
                 Group* parent = NULL, Frame* frame = NULL );

   private:
      Group* _children[2];
      Group* _parent;
      Frame* _frame;
      char   _bSplitVertical;
      Window _root;
      const Page*  _page;
};

#endif /* GROUP_H_ */
