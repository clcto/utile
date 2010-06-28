#include "Config.h"
#include <ios>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

using namespace std;

Config::Config()
{
   userconf = (char*)"~/.config/wmrc";
   sysconf  = (char*)"/etc/wmrc";
   

   d_borderWidth    = 1;
   _borderWidth = 1;
}

void Config::initialize()
{
   string line;
   string splitLine[2];

   ifstream sysFile( sysconf );
     
   if( sysFile )
   {
      // read and process commands
      getline( sysFile, line );
      while( ! sysFile.eof() )
      {
         int n = splitCmdParams( line, splitLine );
         if( n == 1 )
            ;            
         else if( n == 2 )
            ;
         getline( sysFile, line );
      }
      sysFile.close();
   }
}

unsigned char Config::borderWidth()
{
   return _borderWidth;
}

string Config::removeLeadingWhiteSpace( const string& str )
{
   return str.substr( str.find_first_not_of( "\t " ) );
}

void Config::strTrim( string& str )
{
   int lowIndex = str.find_first_not_of( "\t " );
   int highIndex = str.find_last_not_of( "\t " );

   str = str.substr( lowIndex, highIndex - lowIndex + 1 );
}

int Config::splitCmdParams( const string& str, string split[2] )
{
   string tmpstr = removeLeadingWhiteSpace( str );
   unsigned int spaceIndex;
   
   if( tmpstr.empty() )
      return 0;

   spaceIndex = str.find_first_of( "\t " );

   if( spaceIndex >= tmpstr.size() ) // only one token
   {
      split[0] = tmpstr;
      return 1;
   }
   else
   {
      split[0] = tmpstr.substr( 0, spaceIndex );
      split[1] = tmpstr.substr( spaceIndex );
      strTrim( split[1] );
      return 2;
   }
}
