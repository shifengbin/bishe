#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

struct sockaddr_in *dns( char *hostname ,char *port)
{
	struct addrinfo *ai=NULL;
	struct addrinfo i;
	struct sockaddr_in *p = NULL;
	int ret;
	if (hostname == NULL|| port == NULL)
	{
		return NULL;
	}
	memset(&i,0 ,sizeof(struct addrinfo));
	i.ai_family = AF_INET;
	i.ai_flags = AI_PASSIVE;
	i.ai_socktype = SOCK_STREAM;
	ret = getaddrinfo(hostname,port,&i,&ai);
	if (ret != 0 && ai == NULL)
	{
		puts(gai_strerror(ret));
		return NULL;
	}
	p = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));
	if (p==NULL)
	{
		freeaddrinfo(ai);
		return NULL;
	}
	memset(p, 0 , sizeof(struct sockaddr_in));
	memcpy(p,ai->ai_addr,sizeof(struct sockaddr_in));
	
	freeaddrinfo(ai);
	return p;
	
}
/*
int main(int argc , char *argv[])
{
	char buf[20] = { 0 };
	struct sockaddr_in *p;
	p = dns(argv[1],"80");

	inet_ntop(AF_INET , &p->sin_addr, buf,sizeof(buf));
	
	puts(buf);	
	return 0;
}*/
