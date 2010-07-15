/*
 * utile.h
 */

#ifndef UTILE_H_
#define UTILE_H_

#include <X11/Xlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "Command.h"
#include "Commands.h"

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


      static Display *display;
      static Window   root;
      static string   launcher;
      static map< string, Command* > commands;
      static map< KeyCombo, vector<string> > bindings;
      static map< string, unsigned int> masks;

   private:
      static void initCommands();
      static void initMasks();
      static void readConfig();
      static void parseFile( ifstream& );
      static void processKeyPress( const XKeyEvent& );

};

vector<string> tokenize( const string& input,
                     const string& delimiters = " \n\t" );

/*
 * returns a new string with the 
 * leading and following delim characters removed
 */
string trim( const string& input,
             const string& delims = " \n\t" );

#endif
