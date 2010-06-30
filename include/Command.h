/*
 * Command.h
 */

#ifndef COMMAND_H_
#define COMMAND_H_

#include <string>
#include <vector>

using namespace std;

class Command
{
   protected:
      string defaults;
      string usage;
   
   public:
      virtual void execute( vector<string> args ) = 0;
};

#endif // COMMAND_H_
