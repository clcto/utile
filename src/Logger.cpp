/*
 * Logger.cpp
 */

#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
#include <cstdlib>
#include "Logger.hpp"

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

void Logger::write( LogLevel level, string format, ... )
{
      // get the variadic variables
   va_list ap;
   va_start( ap, format );
   
   format += '\n';

   write( level, format, ap );

   va_end( ap );
}

void Logger::write( LogLevel level,
                    string format,
                    va_list ap )
{
   if( level <= _maxLogLevel )
   {
      char* formatted;
      int size = vasprintf( &formatted, format.c_str(), ap );

      if( size > 0 )
      {
         string message = logPrefix( level );
         message += formatted;

         if( _logFile.is_open() )
         {
            _logFile << message;
            _logFile.flush();
         }
         else
            cerr << message;

         free( formatted );
      }
   }
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
         return "! fatal: ";
      case LogLevel_Error:
         return "* error: ";
      case LogLevel_Warning:
         return "$  warn: ";
      case LogLevel_Info:
         return "+  info: ";
      case LogLevel_Trace:
         return "= trace: ";
      case LogLevel_Debug:
         return ". debug: ";
      default:
         return " ????? : ";
   }
}
