/*
 * Logger.cpp
 */

#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
#include <cstdlib>
#include "Logger.h"

Logger::Logger(){}

/*
 * Destructor: clean up resources, ofstream
 */
Logger::~Logger()
{
   if( _logFile.is_open() )
      _logFile.close();
}

bool Logger::open( LogLevel level )
{
   _maxLogLevel = level;

   if( _logFile.is_open() )
      _logFile.close();

   string home = getenv( "HOME" );

   string dir = home;
   dir.append( "/.utile" );

   struct stat st;
   if( stat( dir.c_str(), &st ) != 0 )
      mkdir( dir.c_str(), 0777 );

   string logbackup = dir;
   logbackup.append("/utile.log.old");

   string log = dir;
   log.append("/utile.log");

   rename( log.c_str(), logbackup.c_str() );

   _logFile.open( log.c_str() );

   if( !_logFile.is_open() )
   {
      cerr << "Unable to open log file.\n"
           << "What is typically logged will be"
           << " output to standard error.\n";
      return false;
   }
   else
      return true;
}

void Logger::write( LogLevel level, string message )
{
   if( level < _maxLogLevel && _logFile.is_open() )
   {
      _logFile << logPrefix( level ) << message << '\n';
      _logFile.flush();
   }
   else if( level < _maxLogLevel )
      cerr << logPrefix( level ) << message << '\n';
}

void Logger::setLogLevel( LogLevel level )
{
   _maxLogLevel = level;
}

string Logger::logPrefix( LogLevel level )
{
   switch( level )
   {
      case LogLevel_Fatal:
         return "<!! FATAL> ";
      case LogLevel_Error:
         return "<!  ERROR> ";
      case LogLevel_Warning:
         return "<*   WARN> ";
      case LogLevel_Info:
         return "<+   INFO> ";
      case LogLevel_Trace:
         return "<=  TRACE> ";
      case LogLevel_Debug:
         return "<-  DEBUG> ";
      default:
         return "< ?????? > ";
   }
}
