#ifndef URLPARSER_H
#define URLPARSER_H

#include <pthread.h>

class URLParser
{
private:
	static pthread_mutex_t lock;
	static pthread_mutex_t lockd;
public:
	
	static char *getHost( char *url );
	static char *getPort( char *url );
	static char *getRes( char *url );
	static void deleteMemery( void * );
};
#endif
