#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>

using namespace std;

class Config
{
   public:
      Config();
      void initialize();
      unsigned char borderWidth();

   private:
      string removeLeadingWhiteSpace( const string& str );
      int splitCmdParams( const string& str, string* split );
      void strTrim( string& str );
      
      
      char *userconf, *sysconf;
      unsigned char d_borderWidth, _borderWidth;
};

#endif /* CONFIG_H_ */
