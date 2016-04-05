#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H
#include "modepair.h"
#define MODESIZE 20
class ConfigParser
{
public:
    ~ConfigParser();
    static ConfigParser *getConfigParser();
    int getDuration();
    int getTimeout();
    int getJobNum();
    int getDeepth();
    bool getMethod();
    ModePair *getMode( int index );
private:
    static ConfigParser *config;
    int duration;
    int timeout;
    int jobnum;
    int deepth;
    bool method;
    ModePair *modes[MODESIZE];
    ConfigParser( const char *filename );
    ConfigParser();
    void init();
};



#endif // CONFIGPARSER_H
