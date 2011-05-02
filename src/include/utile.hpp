/*
 * utile.hpp
 */

#ifndef UTILE_HPP_
#define UTILE_HPP_

#include <X11/Xlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "Command.hpp"
#include "Commands.hpp"
#include "Logger.hpp"
#include "Group.hpp"
#include "Split.hpp"

class Group;

using namespace std;

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


      static Display *display;
      static Window   root;
      static string   launcher;
      static map< string, Command* > commands;
      static map< KeyCombo, vector<string> > bindings;
      static map< string, unsigned int> masks;
      static map< string, XColor > colors;
      static Logger log;
      static Group* g;

   private:
      static void initCommands();
      static void initMasks();
      static void readConfig();
      static void parseFile( ifstream& );
      static void processKeyPress( const XKeyEvent& );
      static void remove( Window w );
      
};

vector<string> tokenize( const string& input,
                     const string& delimiters = " \n\t" );

/*
 * returns a new string with the 
 * leading and following delim characters removed
 */
string trim( const string& input,
             const string& delims = " \n\t" );

#endif /* UTILE_HPP_ */
