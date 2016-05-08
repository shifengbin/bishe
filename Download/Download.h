#ifndef DOWNLOAD_H
#define DOWNLOAD_H
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../URL/URL.h"
#include "../dns/DNSCache.h"
#include "../parserurl/parserurl.h"
#include "../ModelTool/ModelTool.h"
#include "../SockTool/SockTool.h"
#include "../ConfigParser/configparser.h"
#include "../HTTP/HTTP.h"

#ifdef __cplusplus
extern "C" {
#endif

static void (*output)(char *);

void loaddll( int sig )
{
	Model *model = NULL;
	if ( sig == SIGRTMIN )
	{
		model = new Model("output.so");
		if ( model->isOpenSuccess() )
		{
			output =(void(*)(char*)) model->getMethod("output");
		}
			delete model;
	}
}

void download( void * args)
{
	
	URL *tURL = (URL*)args;
	char header[1024] = { 0 };
	ConfigParser *config = ConfigParser::getConfigParser();
	int sock;
	struct sockaddr_in *saddr = NULL;
	char *host = NULL;
	char *port = NULL;
	char *res = NULL;
	int tRet = 0;
	HTTP *respond = NULL;
	signal( SIGRTMIN , loaddll );
	DNSCache *dnsch = DNSCache::getDNSCache();
	if ( tURL == NULL )
	{
		return;
	}
	
	host = gethost( tURL->getURLStr() );
	port = getport( tURL->getURLStr() );
	res = getres( tURL->getURLStr() );

	saddr = dnsch->DNS( host, port );
	if (saddr == NULL )
	{
		goto ret;
	}
	
	sock = socket( AF_INET , SOCK_STREAM , 0 );
	if ( sock == -1 )
	{
		goto ret;
	}
	
	tRet = SockTool::connectTimeout( sock , saddr , config->getTimeout());
	if ( tRet == -1 )
	{
		goto retc;
	}
	sprintf( header,"GET %s HTTP/1.1\r\nHost: %s\r\nUser-Agent: Mozilla/5.0 (Linux; U; Android 4.0.3; zh-cn; M032 Build/IML74K) AppleWebKit/533.1 (KHTML, like Gecko)Version/4.0 MQQBrowser/4.1 Mobile Safari/533.1\r\n\r\n",res,host);
	SockTool::writeN( sock , header , strlen( header) );
	//output
	respond = new HTTP(sock);
	if ( respond == NULL )
	{
		goto retc;
	}
	tURL->setStateToDB(respond->getState());
	output( respond->getBody());
	delete respond;
retc:
	close(sock);
ret:
	if ( host != NULL )
	{
		free(host);
	}
	if ( port != NULL )
	{
		free( port );
	}
	if ( res != NULL )
	{
		free( res );
	}
	
	free( tURL );
	return;
}

#ifdef __cplusplus
}
#endif


#endif
