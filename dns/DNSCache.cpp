#include <stdio.h>
#include <netinet/in.h>
#include <pthread.h>
#include "../HashList/HashLink.h"
#include "dns.h"
#include "DNSCache.h"

DNSCache *DNSCache::dnsCa = NULL;

pthread_mutex_t DNSCache::lock = PTHREAD_MUTEX_INITIALIZER;

DNSCache::DNSCache()
{
}

DNSCache* DNSCache::getDNSCache()
{
	if ( dnsCa == NULL )
	{
		pthread_mutex_lock(&lock);
		dnsCa = new DNSCache(); 
		pthread_mutex_unlock(&lock);
	}
	return dnsCa;
}

struct sockaddr_in* DNSCache::DNS(  char *host , char *port)
{
	struct sockaddr_in *saddr = NULL;

	if ( host == NULL || port == NULL)
	{
		return NULL;
	}
	pthread_mutex_lock(&lock);
	if ((saddr = (struct sockaddr_in*)hl.get( host ))== NULL)
	{
		saddr = dns( host , port );
		if (saddr != NULL )
		{
			hl.set(host,saddr);
			//------debug
			puts("DNS CaCHED!");
			pthread_mutex_unlock(&lock);
			return saddr;
		}
		pthread_mutex_unlock(&lock);
		return NULL;
	}
	else
	{
		puts("Get Cache");
		pthread_mutex_unlock(&lock);
		return saddr;
	}
}
