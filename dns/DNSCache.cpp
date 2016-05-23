#include <netinet/in.h>
#include "../HashList/HashLink.h"
#include "dns.h"
#include "DNSCache.h"

DNSCache *DNSCache::dnsCa = NULL;

DNSCache::DNSCache()
{
	pthread_mutex_init( &lock , NULL);
}

DNSCache* DNSCache::getDNSCache()
{
	if ( dnsCa == NULL )
	{
		dnsCa = new DNSCache(); 
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
	if ((saddr = (struct sockaddr_in*)hl.get( host ))== NULL)
	{
		pthread_mutex_lock(&lock);
		saddr = dns( host , port );
		if (saddr != NULL )
		{
			hl.set(host,saddr);
			pthread_mutex_unlock(&lock);
			return saddr;
		}
		pthread_mutex_unlock(&lock);
		return NULL;
	}
	else
	{
		return saddr;
	}
}
