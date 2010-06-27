#ifndef E_GLOBALS_H_
#define E_GLOBALS_H_

#include <X11/Xlib.h>
#include "Group.h"
#include "Config.h"

extern Display *g_display;
extern Window   g_rootWindow;
extern KeyCode  g_splitHorizKey;
extern Group   *g_curGroup;
extern Config   config;

#endif
