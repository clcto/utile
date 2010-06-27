#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <X11/Xlib.h>
#include "Group.h"
#include "Config.h"

class Global
{
   static Display *display;
   static Window   rootWindow;
   static KeyCode  splitHorizKey;
   static Group   *curGroup;
   static Config   config;
}

#endif
