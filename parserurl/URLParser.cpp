#include <stdlib.h>

#include "./URLParser.h"
#include "./parserurl.h"

pthread_mutex_t URLParser::lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t URLParser::lockd = PTHREAD_MUTEX_INITIALIZER;

char *URLParser::getHost( char *url )
{
	char *temp = NULL;
	pthread_mutex_lock( &lock );
	temp = gethost(url);	
	pthread_mutex_unlock( &lock );
	return temp;
	
}

char *URLParser::getPort( char *url )
{
	char *temp = NULL;
        pthread_mutex_lock( &lock );
        temp = getport(url);
        pthread_mutex_unlock( &lock );
        return temp;
}

char *URLParser::getRes( char *url )
{
	char *temp = NULL;
        pthread_mutex_lock( &lock );
        temp = getres(url);
        pthread_mutex_unlock( &lock );
        return temp;
}

void URLParser::deleteMemery( void *del)
{
	pthread_mutex_lock(&lockd);
	if ( del != NULL )
	{
		free(del);
	}
	pthread_mutex_unlock(&lockd);
}
