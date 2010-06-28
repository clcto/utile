/*
 * Command.h
 */

#ifndef COMMAND_H_
#define COMMAND_H_

#include <string>

using namespace std;

class Command
{
   protected:
      string defaults;
      string usage;
   
   public:
      virtual void ExecuteDefault() = 0;
      virtual void Execute( string params ) = 0;
};

#endif // COMMAND_H_
