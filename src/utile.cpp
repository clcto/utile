/*
 * utile.cpp
 */

#include <stdlib.h>
#include <iostream>
#include <X11/Xlib.h>
#include "Frame.h"
#include "Group.h"
#include "utile.h"

using namespace std;

Display* utile::display;
Window   utile::root;

map< string, Command* >    utile::commands;
map< KeyCombo, vector<string> >  utile::bindings;
map< string, unsigned int> utile::masks;


int main( int argc, char** argv )
{
   return utile::run();
}  

int utile::run()
{
      // tries to open the displaylay. quit if it fails
   display = XOpenDisplay( NULL );
   if( !display )
   {
      cerr << "Unable to open displaylay.\n"
           << "Make sure X is running.\n";
      return EXIT_FAILURE;
   }

      // get the root window on the screen.
      // this will only work for one screen,
      // but multiple screen support is to be added later.
   root = DefaultRootWindow( display );
   
      // binds the commands strings to the commands they run
   initCommands();
      
      // initializes common masks
   initMasks();

   readConfig();

   XSelectInput( display, utile::root, 
                 SubstructureRedirectMask );

   XEvent event;
   for( ;; )
   {
      XNextEvent( display, &event );
      switch( event.type )
      {
         case MapRequest:
            //Global::curGroup->addWindow( 
            //                    event.xmaprequest.window );
            break;
         case KeyPress:
            processKeyPress( event.xkey );
            break;
            
      }
   }
}

void utile::initCommands()
{
   commands[ "mod"  ]     = new ModCmd();
   commands[ "modifier" ] = commands[ "mod" ];

   commands[ "bind" ] = new BindCmd();
}

void utile::initMasks()
{
   masks[ "Shift" ] = ShiftMask;
   masks[ "Ctrl"  ] = ControlMask;
   masks[ "Caps"  ] = ShiftLockMask;
   masks[ "Mod1"  ] = Mod1Mask;
   masks[ "Mod2"  ] = Mod2Mask;
   masks[ "Mod3"  ] = Mod3Mask;
   masks[ "Mod4"  ] = Mod4Mask;
   masks[ "Mod5"  ] = Mod5Mask;
   masks[ "none"  ] = 0;
}

void utile::readConfig()
{
   string usr_conf;
   usr_conf  = getenv( "HOME" );
   usr_conf += "/.config/utile/utile.rc";

   char* sys_conf = (char*) "/etc/utile/utile.rc";

   ifstream usrFile( usr_conf.c_str() );
   ifstream sysFile( sys_conf );
   
   if( usrFile )
      parseFile( usrFile );
   else if( sysFile )
      parseFile( sysFile );
}

void utile::parseFile( ifstream& file )
{
   string line;
   vector<string> tokLine;

      // read and process commands
   getline( file, line );
   while( ! file.eof() )
   {
      line = trim( line );
               
         // skip empty lines and comments
      if( !line.empty() && line[0] != '#' )
      {
         tokLine = tokenize( line );
            // we checked for an empty line above
            // so we will have atleast one token here
         utile::commands[ tokLine[0] ]->execute( tokLine );  
       
      }
      
      getline( file, line );
   }

   file.close();
}

bool KeyCombo::operator< ( const KeyCombo& kc ) const
{
   if( key < kc.key )
      return true;
   else if( key > kc.key )
      return false;
   else
      return modifiers < kc.modifiers;
}


void utile::processKeyPress( const XKeyEvent& ev )
{
   KeyCombo kc;
   kc.key       = ev.keycode;
   kc.modifiers = ev.state;

   vector<string> strCmd = bindings[ kc ];
   cerr << "String CMD: " << strCmd[0] << "\n";

   Command *cmd = commands[ strCmd[0] ];
   if( cmd )
      cmd->execute(strCmd);
}






/* GLOBAL STRING FUNCTIONS ============= */


vector<string> tokenize( const string& input,
                         const string& delims )
{
   vector<string> tokens;

   string::size_type tokenStart, tokenEnd;

      // get the start and end of the first token
   tokenStart = input.find_first_not_of( delims, 0 );
   tokenEnd   = input.find_first_of( delims, tokenStart );

   while( !( tokenStart == string::npos && 
             tokenEnd   == string::npos ) )
   {
         // add the token to the vector.
      tokens.push_back( input.substr( tokenStart, 
                                      tokenEnd - tokenStart ) );

      tokenStart = input.find_first_not_of( delims, tokenEnd );
      tokenEnd   = input.find_first_of(     delims, tokenStart );
   }

   return tokens;
}

/*
 * returns a new string with the 
 * leading and following delim characters removed
 */
string trim( const string& input, const string& delims )
{
   string::size_type start, end;

   start = input.find_first_not_of( delims );
   end   = input.find_last_not_of(  delims );

   if( end > start )
      return input.substr( start, end - start + 1);
   else
      return "";
}
