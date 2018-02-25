/*
 * Logger.cpp
 *   writes messages to a file, allowing
 *   for messages to be ignored if they are
 *   at a lower level
 *
 * 2018.02.25:
 *   > modern c++ support
 *   > memory safety
 *
 * 2010.07.20:
 *   > opens a compiled in log file
 *   > writes formatted messages to file
 *   > if the log isn't opened and it is written to
 *     the message is logged to standard error
 *
 * Copyright (c) 2010-2018
 *   Carick Wienke <carick dot wienke at gmail dot com> 
 */

#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
#include <cstdlib>
#include "Logger.hpp"

/* 
 * Default constructor, does nothing
 */
Logger::Logger(){}

/*
 * Destructor: clean up resources, ofstream
 */
Logger::~Logger()
{
   if( _logFile.is_open() )
      _logFile.close();
}

/*
 * opens the file
 * Messages with a lower or equal level than
 *   passed will be logged. Others are ignored
 * 
 * returns whether opening the file is successful
 */
bool Logger::open( LogLevel level )
{
      // save the log level
   _maxLogLevel = level;
 
      // close the file if it is already open
   if( _logFile.is_open() )
      _logFile.close();

      // move the last log, allowing a user to
      // re-run the wm to view the old log file.
      // without this, the last log would be overwritten.
      // this is similar functionality to Xorg
   std::string home = getenv( "HOME" );

   std::string dir = home;
   dir.append( "/.utile" );

   struct stat st;
   if( stat( dir.c_str(), &st ) != 0 )
      mkdir( dir.c_str(), 0777 );

   std::string logbackup = dir;
   logbackup.append("/utile.log.old");

   std::string log = dir;
   log.append("/utile.log");

   rename( log.c_str(), logbackup.c_str() );
 
      // try to open the log
   _logFile.open( log.c_str() );

   if( !_logFile.is_open() )
   {
      std::cerr 
        << "Unable to open log file.\n"
        << "What is typically logged will be"
        << " output to standard error.\n";
      return false;
   }
   else
      return true;
}

/*
 * write a formatted message to the log.
 * 
 * level: the importance of the message
 * format: the format string, same of (*)printf
 * params: the parameters for the format, 
 *         these are not checked at compile time
 */
void Logger::write( LogLevel level, const std::string& format, ... )
{
      // get the variadic variables
   va_list ap;
   va_start( ap, format );
   
   write( level, format, ap );

      // close the va_list
   va_end( ap );
}

/*
 * set the log level
 *
 * level: the new lowest importance message to be logged
 */
void Logger::setLogLevel( LogLevel level )
{
   _maxLogLevel = level;
}

/* ---- PRIVATE METHODS ---- */

/*
 * private function to write to the log with
 * a va_list instead of "..."
 */
void Logger::write( LogLevel level,
                    const std::string& format,
                    va_list ap )
{
   if( level <= _maxLogLevel )
   {
      char* formatted;
      int size = vasprintf( &formatted, format.c_str(), ap );

      if( size > 0 )
      {
         auto message = logPrefix( level );
         message += formatted;

         if( _logFile.is_open() )
         {
            _logFile << message << std::endl;
         }
         else
            std::cerr << message << std::endl;

         free( formatted );
      }
   }
}

/*
 * converts level into a prefix of the message to be
 * written into the log
 */
std::string Logger::logPrefix( LogLevel level )
{
   switch( level )
   {
      case LogLevel::Fatal:
         return "! fatal: ";
      case LogLevel::Error:
         return "* error: ";
      case LogLevel::Warning:
         return "$  warn: ";
      case LogLevel::Info:
         return "+  info: ";
      case LogLevel::Trace:
         return "= trace: ";
      case LogLevel::Debug:
         return ". debug: ";
      default:
         write( LogLevel::Error, "Unknown LogLevel: %d", level );
         return " ????? : ";
   }
}
