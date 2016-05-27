#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#include "../SockTool/SockTool.h"
#include "../Hex2I/Hex2I.h"
#include "./HTTP.h"

pthread_mutex_t HTTP::lock = PTHREAD_MUTEX_INITIALIZER ;
HTTP::HTTP( int fd )
{
	char buf[1024*100] = { 0 };
	char *temp = NULL;
	char *next = NULL;
	int n = 0;
	SockTool::readLine( fd, buf ,1024 );
	//get http state
	if ( ( temp = strstr( buf , " ")) != NULL )
	{
		temp++;
		if ( (next = strstr( temp , " ")) != NULL )
		{
			*next = '\0';
			this->header.state = atoi( temp );
		}
		memset( buf, 0 , sizeof(buf));
	}
	//get other of http header
	for(;;)
        {
                SockTool::readLine( fd , buf , sizeof(buf) );
		if ( !strncasecmp( buf , "Transfer-Encoding:",strlen("Transfer-Encoding:")) )
		{
			this->header.length = -1;
		}
		else if ( !strncasecmp( buf , "Content-Length:",strlen("Content-Length:")) )
		{
			if ( (temp = strstr( buf , " ")) != NULL )
			{
				this->header.length = atoi( temp );
			}
			else if ( (temp = strstr( buf , ":")) != NULL )
			{
				this->header.length = atoi( temp );
			}
		}
                if ( !strncmp(buf,"\r\n",2) )
                {
                        break;
                }
                memset( buf , 0 , sizeof( buf ));
        }
	if ( this->header.state/200 == 1 )
	{
		pthread_mutex_lock(&lock);
		this->body = (char *)malloc( BODYSIZE );
		pthread_mutex_unlock(&lock);
	}
	else
	{
		this->body = NULL;
		return;
	}
	if( this->header.length < 0 )
	{
        	for( ;; )
        	{
                	SockTool::readLine( fd, buf , sizeof(buf) );
                	if ( (temp = strstr( buf , "\r")) != NULL )
                	{
                        	*temp = '\0';
                	}
                	n = hex2i(buf) + 2;


                	if ( n == 2 )
                	{
                        	break;
                	}
                	SockTool::readN(fd , buf , sizeof( buf ),n );
                	if ( (temp = strstr( buf , "\r")) != NULL ) 
			{
                        	*temp = '\0';
                	}
                	strcat( this->body , buf);
                	memset( buf , 0 , sizeof( buf ));
        	}
	}
	else
	{
		SockTool::readN(fd , this->body , BODYSIZE ,this->header.length );
	}
}

HTTP::~HTTP()
{
	if ( this->body != NULL )
	{
		pthread_mutex_lock(&lock);
		free( this->body );
		pthread_mutex_unlock(&lock);
	}
}
int HTTP::getState()
{
	return this->header.state;
}
int HTTP::getLength()
{
	return this->header.length;
}
char *HTTP::getBody()
{
	return this->body;
}
