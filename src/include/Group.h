/*
 * Group.h
 */

#ifndef GROUP_H_
#define GROUP_H_

#include <X11/Xlib.h>
#include "Frame.h"

class Group
{
   public:
      Group( unsigned int, unsigned int, unsigned int, unsigned int,
             Group* parent = NULL, Frame* frame = NULL );
      Group* splitHorizontal();
      Group* splitVertical();
      void addWindow( Window w );

   private:
      Group* _children[2];
      Group* _parent;
      Frame* _frame;
      char   _bSplitVertical;
};

#endif /* GROUP_H_ */
