#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>

#include "DNSCache.h"

int main()
{
	char host[100] = { 0 };
	DNSCache *dc = DNSCache::getDNSCache();
	struct sockaddr_in *saddr;
	for(;;)
	{
		puts("input host");
		scanf("%s",host);
		saddr = dc->DNS(host,"80");
		if ( saddr != NULL )
			puts(inet_ntoa(saddr->sin_addr));	
	}
	return 0;
}
