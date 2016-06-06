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
void save( char  *body)
{
	int fd = open( "file.html", O_CREAT|O_WRONLY|O_APPEND,0666);
	write(fd , body , strlen(body));
	close(fd);
}
void output( char *host , char *body , int type)
{
	char *regexstr = "<tr\\s+logr=[\\d\\D]*?>[\\d\\D]*?</tr>";
	char *temp = NULL;
	regex_t reg;
	regmatch_t pmatch;
	int len = 0;

	if (regcomp(&reg,regexstr,0)!=0)
	{
		puts("comp err");
		return;
	}
	temp = body;
	for(;;)
	{
		if (regexec(&reg, temp ,1,&pmatch,0 ) == REG_NOMATCH)
		{
			puts("no match");
			break;
		}
		else
		{
			puts("match");
			len = pmatch.rm_eo - pmatch.rm_so;
			temp = temp + pmatch.rm_so;
			*(temp+len) = 0;
			save(temp);
			temp+=len+1;
			printf("%d\n",len);
		}
	}
	regfree(&reg);
	return;
}

int main()
{
	char *buf = malloc( 1024*1024 *3 );
	int fd = open("chuzu.html",O_RDONLY);
	int len = read(fd , buf , 1024*1024*3);
	buf[len] = 0;
	output("",buf,1);
	close(fd);
	return 0;
}
