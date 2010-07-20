/*
 * eventnames.h
 *   maps the event type int to it's string
 *
 * From the Xlib Programming Manual
 */

#include <string>

static std::string event_str[] = 
{
/* 00-03 */ "", "", "KeyPress", "KeyRelease",
/* 04,05 */ "ButtonPress", "ButtonRelease",
/* 06,07 */ "MotionNotify", "EnterNotify",
/* 08-10 */ "LeaveNotify", "FocusIn", "FocusOut",
/* 11,12 */ "KeymapNotify", "Expose",
/* 13,14 */ "GraphicsExpose", "NoExpose",
/* 15,16 */ "VisibilityNotify", "CreateNotify",
/* 17,18 */ "DestroyNotify", "UnmapNotify",
/* 19-21 */ "MapNotify", "MapRequest", "ReparentNotify",
/* 22,23 */ "ConfigureNotify", "ConfigureRequest",
/* 24,25 */ "GravityNotify", "ResizeNotify",
/* 26,27 */ "CirculateNotify", "CirculateRequest",
/* 28,29 */ "PropertyNotify", "SelectionClear",
/* 30,31 */ "SelectionRequest", "SelectionNotify",
/* 32,33 */ "ColormapNotify", "ClientMessage",
/* 34    */ "MappingNotify"
};
