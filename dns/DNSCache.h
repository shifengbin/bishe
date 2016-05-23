#ifndef DNSCACHE_H
#define DNSCACHE_H
#include <netinet/in.h>
#include "../HashList/HashLink.h"
#include "dns.h"
#include <unistd.h>
#include <pthread.h>


class DNSCache
{
	private:
		static DNSCache *dnsCa;
		HashLink hl;
		pthread_mutex_t lock;
		DNSCache();
	public:
		static DNSCache* getDNSCache();
		struct sockaddr_in* DNS(  char *host , char *port);
};
#endif
