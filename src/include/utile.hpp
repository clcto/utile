/*
 * utile.hpp
 */

#pragma once

#include "Direction.hpp"
#include "Logger.hpp"
#include "Split.hpp"

#include <X11/Xlib.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <memory>

class Group;
class Command;

class KeyCombo
{
   public:
      unsigned int modifiers;
      KeyCode      key;
      bool operator< ( const KeyCombo& kc ) const;
};

class utile
{
   public:
      static int run();
      static void split( Split s, float size = 0.5 );
      static void close();
      static void select( Direction direction );
      static void resize( Direction side, int pixels );


      static Display* display;
      static Window root;
      static std::string launcher;
      static std::map< std::string, std::unique_ptr<Command> > commands;
      static std::map< KeyCombo, std::vector<std::string> > bindings;
      static std::map< std::string, unsigned int> masks;
      static std::map< std::string, XColor > colors;
      static Logger log;

   private:
      static void initCommands();
      static void initMasks();
      static bool readConfig();
      static void parseFile( std::ifstream& );
      static void processKeyPress( const XKeyEvent& );
      static void remove( Window w );


      static std::unique_ptr<Group> groups;
      
};

std::vector<std::string> tokenize( const std::string& input,
                     const std::string& delimiters = " \n\t" );

/*
 * returns a new string with the 
 * leading and following delim characters removed
 */
std::string trim( const std::string& input,
             const std::string& delims = " \n\t" );
