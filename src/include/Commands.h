/*
 * Commands.h
 */

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include "Command.h"

using namespace std;

class ModCmd : public Command
{
   public:
      ModCmd();
      void execute( vector<string> args );   
};

class LauncherCmd : public Command
{
   public:
      LauncherCmd();
      void execute( vector<string> args );   
};

class BindCmd : public Command
{
   public:
      BindCmd();
      void execute( vector<string> args );   
};

class RunCmd : public Command
{
   public:
      RunCmd();
      void execute( vector<string> args );   
};

#endif // COMMANDS_H_
