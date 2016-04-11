#include "SockTool.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "../Hex2I/Hex2I.h"


int main()
{
	char *temp = NULL;
	int n = 0;
	char buf[1024*1024] = { 0 };
	struct sockaddr_in addr;
	int fd = socket( AF_INET , SOCK_STREAM , 0 );
	memset( &addr , 0 , sizeof( addr ));
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons( 80 );
	addr.sin_addr.s_addr = inet_addr("115.159.231.141");
	SockTool::connectTimeout( fd , &addr, 10 );
	sprintf(buf,"GET / HTTP/1.1\r\nHost: bj.58.com\r\n\r\n");
	SockTool::writeN(fd , buf , strlen( buf ) );
	memset( buf , 0 , sizeof( buf ));

	for(;;)
	{
		SockTool::readLine( fd , buf , 1024 );
//		puts(buf);
		if ( !strncmp(buf,"\r\n",2) )
		{
//			puts("-------header end--------");
			break;
		}
		memset( buf , 0 , sizeof( buf ));
	}

//	sleep(2);
//	puts("body");
	for( ;; )
	{
		SockTool::readLine( fd, buf , 1024 );
		if ( (temp = strstr( buf , "\r")) != NULL )
		{
			*temp = '\0';
		}
//		puts(buf);		
		n = hex2i(buf) + 2;

//		printf("read: %d\n",n);

		if ( n == 2 )
		{
			break;
		}
		SockTool::readN(fd , buf , sizeof( buf ),n );
		if ( (temp = strstr( buf , "\r")) != NULL )
		{
			*temp = '\0';
		}
		printf(buf);
		memset( buf , 0 , sizeof( buf ));
//		sleep(1);
	}
}
