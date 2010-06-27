/*
 * Command.h
 */

class Command
{
   protected:
      string defaults;
      string usage;

      void ExecuteDefault() = 0;
      void Execute( string params ) = 0;
}
