/*
 * Logger.h
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <fstream>

using namespace std;

/* pretty self-explanatory, I think */
enum LogLevel
{
   LogLevel_Fatal   = 0,
   LogLevel_Error   = 1,
   LogLevel_Warning = 2,
   LogLevel_Info    = 3,
   LogLevel_Trace   = 4,
   LogLevel_Debug   = 5
};

class Logger
{
   public:
      Logger();
      ~Logger();
      bool open( LogLevel = LogLevel_Debug );
      void write( LogLevel, string );
      void setLogLevel( LogLevel );
   
   private:
     static string logPrefix( LogLevel level );

     ofstream _logFile;
     LogLevel _maxLogLevel;
};

#endif
