#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>


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

/*
void output( char *host , char *body , int type)
{
		
}*/
