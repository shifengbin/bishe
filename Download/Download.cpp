#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>

#include "../URL/URL.h"
#include "../dns/DNSCache.h"
#include "../parserurl/URLParser.h"
#include "../ModelTool/ModelTool.h"
#include "../SockTool/SockTool.h"
#include "../ConfigParser/configparser.h"
#include "../HTTP/HTTP.h"
#include "Download.h"
#include "MatchURL.h"

//static int aaaa = 0;


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
	char filename[128] = { 0 };
	Model *model = NULL;	
	HTTP *respond = NULL;
	ConfigParser *config = ConfigParser::getConfigParser();

	tURL->setStateToDB(1);

	DNSCache *dnsch = DNSCache::getDNSCache();
	if ( tURL == NULL )
	{
		return;
	}
	
/*	if ( config->getMode(tURL->getType()) )
	{
		puts(config->getMode(tURL->getType())->getMode() );
	}
*/
	host = URLParser::getHost( tURL->getURLStr() );
	port = URLParser::getPort( tURL->getURLStr() );
	res =  URLParser::getRes( tURL->getURLStr() );
	if ( host == NULL || port == NULL || res == NULL )
	{
		puts("host or port or res is NULL");
		goto ret;
	}
	//puts(header);
//	printf("%s:%d\n",host,tURL->getDeep());
	sprintf( header,"GET %s HTTP/1.1\r\nHost: %s\r\n\r\n",res,host);
	saddr = dnsch->DNS( host, port );

	if (saddr == NULL )
	{
		puts("DNS ERROR");
		goto ret;
	}
//	puts(inet_ntoa(saddr->sin_addr));	
	sock = SockTool::Socket();
	if ( sock == -1 )
	{
		puts("create socket error");
		goto ret;
	}
		
	tRet = SockTool::connectTimeout( sock , saddr , config->getTimeout());
	if ( tRet == -1 )
	{
		//puts("timeout");
		perror("Connect");
		goto retc;
	}

	SockTool::writeN( sock , header , strlen( header) );
	respond = new HTTP(sock);
	if ( respond == NULL )
	{
		puts("get respond error");
		goto retc;
	}
//	puts(respond->getBody());
	tURL->setStateToDB(respond->getState());
//	printf("State:%d\n",respond->getState());

	model = Model::getModel();

	if ( respond->getState() / 100 == 2 )
	{
/*		sprintf(filename,"file%d.html",aaaa);
		aaaa++;
		//puts(filename);
		ffd = open( filename, O_CREAT|O_WRONLY,0666);
		write( ffd , respond->getBody(),strlen(respond->getBody()));
		close(ffd);
*/
		model->init();
		if ( model->output != NULL )
		{
	//		puts("Output`````````````````");
			model->output(host,respond->getBody(),tURL->getType());
		}
		else
		{
			puts("Output is NULL");
		}

		if ( config->getMode(tURL->getType())  )
	        {
			if( config->getMethod() && tURL->getDeep() <= config->getDeepth() )
			{
               			GetURLFromBody( config->getMode(tURL->getType()),host,respond->getBody(),tURL->getDeep());
			}
			else
			{
				GetURLFromBody( config->getMode(tURL->getType()),host,respond->getBody(),tURL->getDeep());
			}
       		}
		//puts(respond->getBody());
	}
	if ( respond != NULL )
	{
		delete respond;
	}
	
retc:
	SockTool::Close(sock);
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

