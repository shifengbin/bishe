#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>

#include "configparser.h"
#include "../Persistence/Persistence.h"


#define BUFSIZE 1024
#define URLS "URLS"
#define MODE "MODE"
#define END  "END"
#define DURATION "DURATION="
#define TIMEOUT  "TIMEOUT="
#define JOBNUM   "JOBNUM="
#define DEEPTH   "DEEPTH="
#define METHOD   "METHOD="

#define CONFIG_FILENAME "config.cfg"

ConfigParser *ConfigParser::config = NULL;

ModePair *ConfigParser::getMode(int index)
{
    return this->modes[index];
}

bool ConfigParser::getMethod()
{
    return this->method;
}

int ConfigParser::getDeepth()
{
    return this->deepth;
}

int ConfigParser::getJobNum()
{
    return this->jobnum;
}

int ConfigParser::getTimeout()
{
    return this->timeout;
}

int ConfigParser::getDuration()
{
    return this->duration;
}

ConfigParser *ConfigParser::getConfigParser()
{
    if (ConfigParser::config == NULL)
    {
        ConfigParser::config = new ConfigParser(CONFIG_FILENAME);
    }
    return ConfigParser::config;
}

void ConfigParser::init()
{

    this->duration = 10;
    this->timeout  = 10;
    this->jobnum   = 8;
    this->deepth   = 3;
    this->method   = 1;
    memset(this->modes, 0 , sizeof(ModePair*)*MODESIZE);
}

ConfigParser::~ConfigParser()
{
    for( int  i = 0; i < MODESIZE ; i++ )
    {
        if (this->modes[i] != NULL)
        {
            delete this->modes[i];
        }
    }
    delete ConfigParser::config;
}

ConfigParser::ConfigParser(const char *filename)
{

    if ( filename == NULL )
        return;
    init();
    char buf[BUFSIZE];
    char sql[BUFSIZE] = { 0 };
    char *pre;
    char *next;
    Persistence *db;

    FILE *fp = fopen( filename , "r" );

    if (fp == NULL)
    {
        return;
    }

    db = Persistence::getPersistence();
    db->exec("create table URL(id integer primary key,urlstr varchar(100),type int,deep int default 0,state int default 0)");

    while(fgets( buf , BUFSIZE , fp) != NULL)
    {


        if ( !strncmp( buf , DURATION , strlen( DURATION ) ) )
        {
            this->duration = atoi(buf+strlen(DURATION));
        }

        else if ( !strncmp( buf , TIMEOUT , strlen(TIMEOUT) ) )
        {
            this->timeout = atoi( buf + strlen( TIMEOUT ));
        }

        else if ( !strncmp( buf , JOBNUM , strlen( JOBNUM )) )
        {
            this->jobnum = atoi( buf + strlen( JOBNUM ));
        }

        else if ( !strncmp( buf  , DEEPTH , strlen(DEEPTH)) )
        {
            this->deepth = atoi( buf + strlen( DEEPTH ));
        }

        else if ( !strncmp( buf  , METHOD , strlen( METHOD )) )
        {
            this->method = atoi( buf + strlen( METHOD ));
        }

        else if ( !strncmp( buf, URLS, strlen(URLS)) )
        {
            while( fgets( buf , BUFSIZE , fp )!= NULL)
            {
                if( !strncmp( buf , END , strlen(END)))
                {
                    break;
                }

                if ( (pre = strstr( buf , ":")) != NULL)
                {
                    //应该写入数据库
                    *pre = '\0';
		    pre++;
//                    std::cout <<"URL:"<<buf<<" TYPE:"<<atoi(pre)<<std::endl;
		    sprintf( sql ,"insert into URL(urlstr,type) values('%s',%d)",buf,atoi(pre));
		    
		    db->exec(sql);
                }
            }

        }

        else if ( !strncmp( buf ,MODE , strlen(MODE) ))
        {
            while( fgets( buf , BUFSIZE , fp ) != NULL )
            {
                if( !strncmp( buf , END , strlen(END)))
                {
                    break;
                }

                if ( (pre = strstr( buf , ":" )) != NULL &&
                     (next = strstr( pre + 1 ,":")) != NULL)
                {
                    *pre = '\0';
                    pre++;
                    *next = '\0';
                    next++;
		    if ( this->modes[atoi(buf)] == NULL )
                    {
			this->modes[atoi(buf)] = new ModePair(pre,atoi(next));
		    }
                }
            }
        }

        memset(buf , 0 , BUFSIZE);
    }

	fclose(fp);
}
