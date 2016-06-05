#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <pcre2posix.h>


/*
   static int num = 0;
   void output( char *host,char *body,int type )
   {
   if ( type != 3 )
   return;
   char filename[100] = { 0 };
   int fd;
   num++;
   sprintf( filename, "file%d%s%d",num,host,type);
   fd = open( filename , O_CREAT | O_WRONLY ,0666);
   if ( fd < 0 )
   return;
   write( fd , body , strlen( body ));
   close(fd);

   }
 */

void output( char *host , char *body , int type)
{
	char *regexstr = "<a.*?href=(\\\"|\').*?(\\\"|\").*?>.*?</a>";
	regex_t reg;
	regmatch_t pmatch;

	if (regcomp(&reg,regexstr,0)!=0)
	{
		puts("comp err");
		return;
	}

	if (regexec(&reg,body,1,&pmatch,0 ) == REG_NOMATCH)
	{
		puts("no match");
	}
	else
	{

	}
	regfree(&reg);
}

