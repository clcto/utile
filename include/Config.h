#ifndef CONFIG_H_
#define CONFIG_H_

class Config
{
   public:
      Config();
      void read();

      map< KeyCombo, Command* > bindings;

   private:
      const char* userconf = "~/.config/utile/utile.rc";
      const char* sysconf  = "/etc/utile/utile.rc";
};

#endif
