/*
 * Commands.h
 */

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <string>

using namespace std;

class ModCmd : public Command
{
   public:
      ModCmd();
      void Execute( string params );   
      void ExecuteDefault();   
};

class BindCmd : public Command
{
   public:
      BindCmd();
};

#endif // COMMANDS_H_
