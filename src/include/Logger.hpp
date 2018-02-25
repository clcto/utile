/*
 * Logger.hpp
 * Copyright (c) 2010-2018
 *   Carick Wienke <carick dot wienke at gmail dot com> 
 */

#pragma once

#include <string>
#include <fstream>
#include <stdarg.h>

enum class LogLevel
{
   Fatal = 0,
   Error,
   Warning,
   Info,
   Trace,
   Debug,
};

class Logger
{
   public:
      Logger();
      ~Logger();
      bool open( LogLevel = LogLevel::Debug );
      void write( LogLevel, const std::string&, ... );
      void setLogLevel( LogLevel );
   
   private:
     std::string logPrefix( LogLevel level );
     void write( LogLevel, const std::string&, va_list );

     std::ofstream _logFile;
     LogLevel _maxLogLevel;
};
