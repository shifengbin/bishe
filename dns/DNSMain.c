#include <stdio.h>
#include "dns.h"
#include <sys/socket.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	struct sockaddr_in *addr = NULL;
	char ip[INET_ADDRSTRLEN] = { 0 };
	
	if ( argc !=2 )
	{
		puts("info:app host");
		return -1;
	}
	addr = dns(argv[1],"80");	

	if ( addr != NULL)	
	{
		inet_ntop( AF_INET , &(addr->sin_addr) ,  ip , INET_ADDRSTRLEN);
		puts(ip);
	}

	if ( addr != NULL )
		free( addr );
	return 0;
}
