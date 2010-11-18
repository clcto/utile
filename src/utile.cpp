/*
 * utile.cpp
 */

#include <stdlib.h>
#include <iostream>
#include <X11/Xlib.h>
#include "Frame.hpp"
#include "GroupNode.hpp"
#include "Group.hpp"
#include "utile.hpp"
#include "eventnames.hpp"
#include "Direction.hpp"

using namespace std;

Display* utile::display;
Window   utile::root;
string   utile::launcher;
Logger   utile::log;

map< string, Command* >    utile::commands;
map< KeyCombo, vector<string> >  utile::bindings;
map< string, unsigned int> utile::masks;
Group* utile::g;


int main( int argc, char** argv )
{
   return utile::run();
}  

int utile::run()
{
   log.open( LogLevel_Debug );
   log.write( LogLevel_Info, "utile started." );

      // tries to open the displaylay. quit if it fails
   display = XOpenDisplay( NULL );
   if( !display )
   {
      log.write( LogLevel_Fatal,
         "Unable to open display. "
         "Make sure X is running." );
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

   g = new Group( utile::root );
   g->split( Split_Horizontal );
   g->selectRight();
   g->selectRight();


   XSelectInput( display, utile::root, 
                 SubstructureRedirectMask | SubstructureNotifyMask | StructureNotifyMask );

   XEvent event;
   for( ;; )
   {
      XNextEvent( display, &event );

      log.write( LogLevel_Debug, "Received Event: %s", 
                 event_str[ event.type ].c_str() );

      switch( event.type )
      {
         case MapRequest:
            g->getCur()->addWindow( event.xmaprequest.window ); 
            break;
         case KeyPress:
            processKeyPress( event.xkey );
            break;
         case UnmapNotify:
            remove( event.xunmap.window );
            break;
      }
   }
}

void utile::initCommands()
{
   log.write( LogLevel_Trace, "Initializing commands" );
   commands[ "mod" ]      = new ModCmd();
   commands[ "bind" ]     = new BindCmd();
   commands[ "launcher" ] = new LauncherCmd();
   commands[ "run" ]      = new RunCmd();
   commands[ "quit" ]     = new QuitCmd();
   commands[ "split" ]    = new SplitCmd();
   commands[ "close" ]    = new CloseCmd();
}

void utile::initMasks()
{
   log.write( LogLevel_Trace, "Initializing default mods" );
   masks[ "Shift" ] = ShiftMask;
   masks[ "Ctrl"  ] = ControlMask;
   masks[ "Mod1"  ] = Mod1Mask;
   masks[ "Mod2"  ] = Mod2Mask;
   masks[ "Mod3"  ] = Mod3Mask;
   masks[ "Mod4"  ] = Mod4Mask;
   masks[ "Mod5"  ] = Mod5Mask;
   masks[ "none"  ] = 0;
}

void utile::readConfig()
{
   log.write( LogLevel_Trace, "Started reading init file" );
   string usr_conf;
   usr_conf  = getenv( "HOME" );
   usr_conf += "/.utile/utile.rc";

   char* sys_conf = (char*) "/etc/utile/utile.rc";

   ifstream usrFile( usr_conf.c_str() );
   ifstream sysFile( sys_conf );
   
   if( usrFile )
   {
      log.write( LogLevel_Debug, "Reading user init file" );
      parseFile( usrFile );
   }
   else if( sysFile )
   {
      log.write( LogLevel_Debug, "Reading system init file" );
      parseFile( sysFile );
   }
   else
      log.write( LogLevel_Debug, "No init files found" );

   log.write( LogLevel_Trace, "Finished reading init files" );
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
         Command* cmd = utile::commands[ tokLine[0] ];

         if( cmd )
            cmd->execute( tokLine );  
            // prevent the map from adding new items
         else
            utile::commands.erase( tokLine[0] );
       
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

   Command *cmd = commands[ strCmd[0] ];
   if( cmd )
      cmd->execute(strCmd);
   else
   {
      log.write( LogLevel_Warning, "Invalid command:" );
      log.write( LogLevel_Warning, strCmd[0] );

         // remove invalid commands
      commands.erase( strCmd[0] );
   }
}

void utile::split( Split s, float percent )
{
   g->split( s );
}

void utile::close()
{
   utile::log.write( LogLevel_Trace, "utile::close()" );
   g->close();
}

// modify this! g->remove( win )
void utile::remove( Window win )
{
   g->getCur()->remove( win );
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
