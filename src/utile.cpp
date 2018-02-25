/*
 * utile.cpp
 * Copyright (c) 2010-2018
 *   Carick Wienke <carick dot wienke at gmail dot com>
 */
#include "Frame.hpp"
#include "GroupNode.hpp"
#include "Group.hpp"
#include "utile.hpp"
#include "eventnames.hpp"
#include "Direction.hpp"
#include "Commands.hpp"

#include <X11/Xlib.h>

#include <stdlib.h>
#include <iostream>

Display* utile::display;
Window   utile::root;
std::string   utile::launcher;
Logger   utile::log;

std::map< std::string, std::unique_ptr<Command> > utile::commands;
std::map< KeyCombo, std::vector<std::string> > utile::bindings;
std::map< std::string, unsigned int> utile::masks;
std::map< std::string, XColor > utile::colors;
std::unique_ptr<Group> utile::groups;


int main( int argc, char** argv )
{
   return utile::run();
}  

int utile::run()
{
   log.open( LogLevel::Debug );
   log.write( LogLevel::Info, "utile started." );

      // try to open the display. quit if it fails
   display = XOpenDisplay( NULL );
   if( !display )
   {
      log.write( LogLevel::Fatal,
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

   if( !readConfig() )
       return EXIT_FAILURE;

   groups = std::make_unique<Group>( utile::root );

   XSelectInput( display, utile::root, 
                 SubstructureRedirectMask | SubstructureNotifyMask | StructureNotifyMask );

   XEvent event;
   for( ;; )
   {
      XNextEvent( display, &event );

      log.write( LogLevel::Debug, "Received Event: %s", 
                 event_str[ event.type ].c_str() );

      switch( event.type )
      {
         case MapRequest:
            groups->getCur()->addWindow( event.xmaprequest.window ); 
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
   log.write( LogLevel::Trace, "Initializing commands" );

   commands.emplace( "mod", std::make_unique<ModCmd>() );
   commands.emplace( "bind", std::make_unique<BindCmd>() );
   commands.emplace( "launcher", std::make_unique<LauncherCmd>() );
   commands.emplace( "run", std::make_unique<RunCmd>() );
   commands.emplace( "quit", std::make_unique<QuitCmd>() );
   commands.emplace( "split", std::make_unique<SplitCmd>() );
   commands.emplace( "close", std::make_unique<CloseCmd>() );
   commands.emplace( "color", std::make_unique<ColorCmd>() );
   commands.emplace( "border", std::make_unique<BorderCmd>() );
   commands.emplace( "select", std::make_unique<SelectCmd>() );
   commands.emplace( "resize", std::make_unique<ResizeCmd>() );
}

void utile::initMasks()
{
   log.write( LogLevel::Trace, "Initializing default mods" );
   masks[ "Shift" ] = ShiftMask;
   masks[ "Ctrl"  ] = ControlMask;
   masks[ "Mod1"  ] = Mod1Mask;
   masks[ "Mod2"  ] = Mod2Mask;
   masks[ "Mod3"  ] = Mod3Mask;
   masks[ "Mod4"  ] = Mod4Mask;
   masks[ "Mod5"  ] = Mod5Mask;
   masks[ "none"  ] = 0;
}

bool utile::readConfig()
{
   log.write( LogLevel::Trace, "Started reading init file" );
   std::string usr_conf;
   usr_conf  = getenv( "HOME" );
   usr_conf += "/.utile/utile.rc";

   char* sys_conf = (char*) "/etc/utile/utile.rc";

   std::ifstream usrFile( usr_conf.c_str() );
   std::ifstream sysFile( sys_conf );
   
   if( usrFile )
   {
      log.write( LogLevel::Debug, "Reading user init file" );
      parseFile( usrFile );
   }
   else if( sysFile )
   {
      log.write( LogLevel::Debug, "Reading system init file" );
      parseFile( sysFile );
   }
   else
   {
       log.write( LogLevel::Error, "No init file found." );
       return false;
   }

   log.write( LogLevel::Trace, "Finished reading init files" );
   return true;
}

void utile::parseFile( std::ifstream& file )
{
   std::string line;
   std::vector<std::string> tokLine;

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
         auto iter = utile::commands.find( tokLine[ 0 ] );
         if( iter != std::end( commands ) )
         {
            auto& cmd = iter->second;
            cmd->execute( tokLine );  
         }
       
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

   std::vector<std::string> strCmd = bindings[ kc ];

   const auto& iter = commands.find( strCmd[0] );
   if( iter != commands.end() )
   {
      auto& cmd = iter->second;
      cmd->execute(strCmd);
   }
   else
   {
      log.write( LogLevel::Warning, "Invalid command:" );
      log.write( LogLevel::Warning, strCmd[0] );
   }
}

void utile::split( Split s, float percent )
{
   groups->split( s );
}

void utile::close()
{
   utile::log.write( LogLevel::Trace, "utile::close()" );
   groups->close();
}

// modify this! g->remove( win )
void utile::remove( Window win )
{
   groups->getCur()->remove( win );
}

void utile::select( Direction direction )
{
   groups->select( direction );
}

void utile::resize( Direction side, int pixels )
{
   groups->resize( side, pixels );
}

/* GLOBAL STRING FUNCTIONS ============= */


std::vector<std::string> tokenize( const std::string& input,
                         const std::string& delims )
{
   std::vector<std::string> tokens;

      // get the start and end of the first token
   auto tokenStart = input.find_first_not_of( delims, 0 );
   auto tokenEnd   = input.find_first_of( delims, tokenStart );

   while( !( tokenStart == std::string::npos && 
             tokenEnd   == std::string::npos ) )
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
std::string trim( const std::string& input, const std::string& delims )
{
   auto start = input.find_first_not_of( delims );
   auto end   = input.find_last_not_of(  delims );

   if( end > start )
      return input.substr( start, end - start + 1);
   else
      return "";
}
