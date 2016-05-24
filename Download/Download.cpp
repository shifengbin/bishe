#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "../URL/URL.h"
#include "../dns/DNSCache.h"
#include "../parserurl/parserurl.h"
#include "../ModelTool/ModelTool.h"
#include "../SockTool/SockTool.h"
#include "../ConfigParser/configparser.h"
#include "../HTTP/HTTP.h"
#include "Download.h"

static void (*output)(char *);
static int  isInit = 0;

void initModel()
{
	puts("initModel");

	Model *model = new Model("output.so");
	if ( model->isOpenSuccess() )
	{
		output = (void(*)(char*)) model->getMethod("output");
		isInit = 1;
	}
	delete model;
}

void loaddll( int sig )
{
	puts("loaddll");
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
/*
	
	URL *t = (URL*)args;
	DNSCache *dnsc = DNSCache::getDNSCache();
        char buf[16] = { 0 };
        struct sockaddr_in *saddr;
	signal( SIGRTMIN , loaddll );
	initModel();
        printf("%s\n",t->getURLStr());
        t->setStateToDB(1);
        saddr = dnsc->DNS(gethost(t->getURLStr()),getport( t->getURLStr() ));
        puts(inet_ntop( AF_INET , &(saddr->sin_addr) , buf , 16 ) );
	free(t);
        return ;
*/
	
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

	tURL->setStateToDB(1);

//	puts("Download");

	if ( !isInit )
	{
		initModel();
	}

	DNSCache *dnsch = DNSCache::getDNSCache();
	if ( tURL == NULL )
	{
		return;
	}
	
	host = gethost( tURL->getURLStr() );
	port = getport( tURL->getURLStr() );
	res = getres( tURL->getURLStr() );
	if ( host == NULL || port == NULL || res == NULL )
	{
		puts("host or port or res is NULL");
		goto ret;
	}
	sprintf( header,"GET %s HTTP/1.1\r\nHost: %s\r\nUser-Agent: Mozilla/5.0 (Linux; U; Android 4.0.3; zh-cn; M032 Build/IML74K) AppleWebKit/533.1 (KHTML, like Gecko)Version/4.0 MQQBrowser/4.1 Mobile Safari/533.1\r\n\r\n",res,host);
	puts(header);
	//printf("host:%s\nport:%s\nres:%s\n",host,port,res);
	saddr = dnsch->DNS( host, port );
	return;

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
	puts(respond->getBody());
//	output( respond->getBody());
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
	if ( tURL != NULL )
	{
		free( tURL );
	}
	return;
}

