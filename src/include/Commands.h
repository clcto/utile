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

class BindCmd : public Command
{
   public:
      BindCmd();
      void execute( vector<string> args );   
};

#endif // COMMANDS_H_
