/*
 * Commands.hpp
 * Copyright (c) 2010-2018
 *   Carick Wienke <carick dot wienke at gmail dot com> 
 */

#pragma once

#include "Command.hpp"

class ModCmd : public Command
{
   public:
      ModCmd();
      void execute( const std::vector<std::string>& params );
};

class BindCmd : public Command
{
   public:
      BindCmd();
      void execute( const std::vector<std::string>& params );
};

class LauncherCmd : public Command
{
   public:
      LauncherCmd();
      void execute( const std::vector<std::string>& params );
};

class RunCmd : public Command
{
   public:
      RunCmd();
      void execute( const std::vector<std::string>& params );
};

class QuitCmd : public Command
{
   public:
      QuitCmd();
      void execute( const std::vector<std::string>& params );
};

class SplitCmd : public Command
{
   public:
      SplitCmd();
      void execute( const std::vector<std::string>& params );
};

class CloseCmd : public Command
{
   public:
      CloseCmd();
      void execute( const std::vector<std::string>& params );
};

class ColorCmd : public Command
{
   public:
      ColorCmd();
      void execute( const std::vector<std::string>& params );
};

class BorderCmd : public Command
{
   public:
      BorderCmd();
      void execute( const std::vector<std::string>& params );
};

class SelectCmd : public Command
{
   public:
      SelectCmd();
      void execute( const std::vector<std::string>& params );
};

class ResizeCmd : public Command
{
   public:
      ResizeCmd();
      void execute( const std::vector<std::string>& params );
};
