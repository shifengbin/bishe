#ifndef __PAESERURL_H__
#define __PARSERURL_H__

#ifdef __cplusplus
extern "C"{
#endif

typedef struct URL{
	char *host;
	char *port;
	char *res;
	int type;
	int deep;
}URL;
/*
* these function is the end must free the result
*	error return NULL;
*/
//function http(s)://xxx.xxx.xxx/xxx ==> xxx.xxx.xxx/xxx
char *removehttp(char *url);

//get host 
//www.baidu.com/index.html ==> www.baidu.com
char *gethost( char *url);

//http://www.xxx.xxx:dd/xxx ==>dd
char *getport( char *url);

//http://www.xxx.xxx/dsf/saa ==> /dsf/saa
char *getres( char *url );

//get URL 
URL *parserURL( URL *u , char *url);

#ifdef __cplusplus
}
#endif

#endif
