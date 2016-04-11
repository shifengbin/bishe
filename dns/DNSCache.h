#ifndef DNSCACHE_H
#define DNSCACHE_H
#include <netinet/in.h>
#include "../HashList/HashLink.h"
#include "dns.h"


class DNSCache
{
	private:
		static DNSCache *dnsCa;
		HashLink hl;
		DNSCache(){}
	public:
		static DNSCache* getDNSCache()
		{
			if ( dnsCa == NULL )
			{
				dnsCa = new DNSCache(); 
			}
			return dnsCa;
		}

		struct sockaddr_in* DNS(  char *host , char *port)
		{
			struct sockaddr_in *saddr = NULL;
			if ((saddr = (struct sockaddr_in*)hl.get( host ))== NULL)
			{
				saddr = dns( host , port );
				if (saddr != NULL )
				{
					hl.set(host,saddr);
					return saddr;
				}
				return NULL;
			}
			else
			{
				return saddr;
			}
		}

};
DNSCache* DNSCache::dnsCa = NULL;
#endif
