/*
 * Command.hpp
 * Copyright (c) 2010-2018
 *   Carick Wienke <carick dot wienke at gmail dot com> 
 */

#pragma once

#include <string>
#include <vector>

class Command
{
   public:
      virtual ~Command() { }
      virtual void execute( const std::vector<std::string>& params ) = 0;

   protected:
      std::string defaults;
      std::string usage;
};

