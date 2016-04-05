#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parserurl.h"

/*
 * these function is the end must free the result
 */
//function http(s)://xxx.xxx.xxx/xxx ==> xxx.xxx.xxx/xxx
char *removehttp(char *url)
{
	char *u = url;
	char *ru;
	int len = 0;

	if (url == NULL)
		return NULL;


	if ( (u = strstr(url , "//")) != NULL)
	{
		ru = (char*)malloc(strlen(u+1));
		if ( ru== NULL)
			return NULL;
		memset( ru , 0 , strlen(u+1));
		memcpy( ru , u+2 , strlen(u+2));
	}
	else
	{
		ru = (char*)malloc(strlen(url)+1);
		memset( ru , 0 ,strlen(url)+1);
		memcpy( ru , url, strlen(url));
	}
	return ru;
}

//get host 
//www.baidu.com/index.html ==> www.baidu.com
char *gethost( char *url)
{
	char *hosts,*hoste;
	char *rhttp ;
	if( url == NULL)
		return NULL;

	if ((hosts = strstr(url,"//")) == NULL)
	{
		return NULL;
	}
	hosts+=2;
	if ((hoste = strstr( hosts,":")) == NULL)
	{
		if((hoste = strstr(hosts,"/")) == NULL)
		{
			rhttp = (char*)malloc(strlen(hosts)+1);
			if ( rhttp == NULL)
				return NULL;
			memset(rhttp, 0 , strlen(hosts)+1);
			memcpy(rhttp, hosts,strlen(hosts));
			return rhttp;
		}
	}
	int len = hoste - hosts;
	rhttp = (char *)malloc(len + 1);
	memset( rhttp, 0 , len+1);
	memcpy( rhttp, hosts, len);
	return rhttp;
}

//http://www.xxx.xxx:dd/xxx ==>dd
char *getport( char *url)
{
	char *c,*p;
	char *port;
	char *rh;
	if (url == NULL)
		return NULL;
	rh = removehttp(url);

	if ((c = strchr(rh,':'))== NULL)
	{
		free(rh);
		if ( strncmp(url, "https",5) == 0 )
		{
			port = (char *)malloc(4);
			if (port == NULL)
				return NULL;
			sprintf( port , "443");
		}
		else if ((strncmp(url,"http",4) == 0) ||(strncmp(url, "//",2)==0) )
		{
			port = (char *)malloc(3);
			if (port == NULL)
				return NULL;
			sprintf(port, "80");
		}
		else 
		{
			return NULL;
		}
	}
	else
	{
		c++;
		if ( (p = strchr(c,'/')) == NULL)
		{
			port = (char*)malloc(strlen(c)+1);	
			if (port == NULL)	
				return NULL;
			memset(port , 0 , strlen(c)+1);
			memcpy(port , c , strlen(c));
		}
		else
		{
			port = (char*)malloc(p-c+1);
			if ( port == NULL)
				return NULL;
			memset( port , 0 , p-c+1);
			memcpy( port , c , p-c);
		}
	}
	return port;
}

//http://www.xxx.xxx/dsf/saa ==> /dsf/saa
char *getres( char *url )
{
	char *u;
	char *find;
	char *ret;
	int len;

	if (url == NULL)
		return NULL;

	u = removehttp(url);
	if ( (find = strchr(u,'/')) == NULL)
	{
		free(u);
		ret = (char *)malloc(2);
		if (ret == NULL )
			return NULL;
		sprintf( ret , "/");
		return ret;
	}
	len = strlen(find);
	ret = (char *)malloc(len+1);
	if ( ret == NULL )
	{
		free(u);
		return NULL;
	}
	sprintf(ret , "%s", find);
	free(u);
	return ret;
}

URL *parserURL( URL *u , char *url)
{
	URL *ret;
	char *host;
	char *port;
	char *res;

	if (url == NULL)
		return NULL;
	host = gethost(url);
	port = getport(url);
	res =  getres(url);

	if (host == NULL )
	{
		if ( u == NULL || u->host == NULL)
			return NULL;
		host = (char *)malloc(strlen(u->host)+1);
		sprintf(host , "%s", u->host);
	}
	if (port == NULL )
	{
		if ( u == NULL || u->port == NULL)
			return NULL;
		port = (char *)malloc(strlen(u->port)+1);
		sprintf( port , "%s" , u->port);
	}
	ret = (URL*)malloc(sizeof(URL));
	if (ret == NULL )
	{
		if ( host == NULL)
			free(host);
		if ( port == NULL)
			free(port);
		if ( res == NULL )
			free(res);
		return NULL;
	}
	ret->host = host;
	ret->port = port;
	ret->res  = res;
	return ret;
}
/*
int main()
{
	URL *ret ,*ret2;
	char *p =  "http://s1.qhimg.com:8080/index.html";
	char *t = "/aaa/bbb";
	ret = parserURL(NULL,p);
	if (ret != NULL)
	{
		puts(ret->host);
		puts(ret->port);
		puts(ret->res);
	}

	ret2 = parserURL( ret , t );

	if (ret2 != NULL)
	{
		puts(ret2->host);
		puts(ret2->port);
		puts(ret2->res);
	}

	return 0;
}
*/
