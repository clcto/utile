/*
 * Commands.hpp
 */

#ifndef COMMANDS_HPP_
#define COMMANDS_HPP_

#include "Command.hpp"

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

class LauncherCmd : public Command
{
   public:
      LauncherCmd();
      void execute( vector<string> args );   
};

class RunCmd : public Command
{
   public:
      RunCmd();
      void execute( vector<string> args );   
};

#endif // COMMANDS_HPP_