/*
 * Command.hpp
 */

#ifndef COMMAND_HPP_
#define COMMAND_HPP_

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

#endif // COMMAND_HPP_
