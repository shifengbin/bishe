#include "../SockTool/SockTool.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "../Hex2I/Hex2I.h"
#include "HTTP.h"


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
	addr.sin_addr.s_addr = inet_addr("220.181.112.244");
	SockTool::connectTimeout( fd , &addr, 10 );
	sprintf(buf,"GET / HTTP/1.1\r\nHost: www.baidu.com\r\n\r\n");
	SockTool::writeN(fd , buf , strlen( buf ) );
	memset( buf , 0 , sizeof( buf ));
	HTTP *t = new HTTP(fd);
	printf("state:%d length:%d\n",t->getState(),t->getLength());
	puts(t->getBody());

	return 0;
}
