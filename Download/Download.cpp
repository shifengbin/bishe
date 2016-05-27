#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <fcntl.h>

#include "../URL/URL.h"
#include "../dns/DNSCache.h"
#include "../parserurl/URLParser.h"
#include "../ModelTool/ModelTool.h"
#include "../SockTool/SockTool.h"
#include "../ConfigParser/configparser.h"
#include "../HTTP/HTTP.h"
#include "Download.h"




void download( void * args)
{
	
	URL *tURL = (URL*)args;
	char header[1024] = { 0 };
	int sock;
	struct sockaddr_in *saddr = NULL;
	char *host = NULL;
	char *port = NULL;
	char *res = NULL;
	int tRet = 0;
	int ffd;
	HTTP *respond = NULL;
	ConfigParser *config = ConfigParser::getConfigParser();

	tURL->setStateToDB(1);

	DNSCache *dnsch = DNSCache::getDNSCache();
	if ( tURL == NULL )
	{
		return;
	}
	
	host = URLParser::getHost( tURL->getURLStr() );
	port = URLParser::getPort( tURL->getURLStr() );
	res =  URLParser::getRes( tURL->getURLStr() );
	if ( host == NULL || port == NULL || res == NULL )
	{
		puts("host or port or res is NULL");
		goto ret;
	}
	printf("Host:%s\nPort:%s\nRes:%s\n",host,port,res);
	sprintf( header,"GET %s HTTP/1.1\r\nHost: %s\r\nUser-Agent: Mozilla/5.0 (Linux; U; Android 4.0.3; zh-cn; M032 Build/IML74K) AppleWebKit/533.1 (KHTML, like Gecko)Version/4.0 MQQBrowser/4.1 Mobile Safari/533.1\r\n\r\n",res,host);
	//puts(header);
	saddr = dnsch->DNS( host, port );

	if (saddr == NULL )
	{
		puts("DNS ERROR");
		goto ret;
	}
	puts(inet_ntoa(saddr->sin_addr));	
	sock = socket( AF_INET , SOCK_STREAM , 0 );
	if ( sock == -1 )
	{
		puts("create socket error");
		goto ret;
	}
	
	tRet = SockTool::connectTimeout( sock , saddr , config->getTimeout());
	if ( tRet == -1 )
	{
		puts("timeout");
		goto retc;
	}

	SockTool::writeN( sock , header , strlen( header) );
	respond = new HTTP(sock);
	if ( respond == NULL )
	{
		puts("get respond error");
		goto retc;
	}
	tURL->setStateToDB(respond->getState());
//	puts(respond->getBody());
//	output( respond->getBody());
	ffd = open( "aa.html" , O_CREAT|O_WRONLY|O_APPEND,0666);
	write( ffd , respond->getBody(),strlen(respond->getBody()));
	close(ffd);
	puts("Output");
	if ( respond != NULL )
	{
		delete respond;
	}
	
retc:
	close(sock);
ret:
	if ( host != NULL )
	{
		URLParser::deleteMemery((void*)host);
	}
	if ( port != NULL )
	{
		URLParser::deleteMemery((void*) port );
	}
	if ( res != NULL )
	{
		URLParser::deleteMemery((void*) res );
	}
	if ( tURL != NULL )
	{
		URLParser::deleteMemery((void*) tURL );
	}
	return;
}

