#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#include "../SockTool/SockTool.h"
#include "../Hex2I/Hex2I.h"
#include "./HTTP.h"

int isHex( char *num)
{
	while( *num != '\r' )
	{
		if ( *num >='0' && *num <= '9' || *num >= 'a' && *num <='f' ||*num>='A' && *num <='F')
		{
			;
		}else
		{
			return 0;
		}
		num++;
	}
	if ( *(num+1) == '\n')
	{
		return 1;
	}
	return 0;
}



pthread_mutex_t HTTP::lock = PTHREAD_MUTEX_INITIALIZER ;
HTTP::HTTP( int fd )
{
	char buf[1024*1024] = { 0 };
	char *temp = NULL;
	char *next = NULL;
	int n = 0;
	this->header.length = 0;
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
		//----debug---
		puts(buf);
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
		//---debug---
		puts(buf);
                if ( !strncmp(buf,"\r\n",2) )
                {
                        break;
                }
                memset( buf , 0 , sizeof( buf ));
        }
	if ( this->header.state/100 == 2 )
	{
		pthread_mutex_lock(&lock);
		this->body = (char *)malloc( BODYSIZE );
		memset( this->body , 0 , BODYSIZE);
		pthread_mutex_unlock(&lock);
	}
	else
	{
		this->body = NULL;
		return;
	}
	memset( buf, 0 , sizeof(buf));
	if( this->header.length <= 0 )
	{
        	for( ;; )
        	{
                	SockTool::readLine( fd, buf , sizeof(buf) );
			if ( !strncmp(buf, "\r\n",2) )
			{
				continue;
			}
			if ( isHex(buf) )
			{
				n = hex2i(buf);
				if ( n == 0 )
				{
					break;
				}
				continue;
			}
			strcat( this->body , buf );
			memset(buf ,0, sizeof(buf));
/*                	if ( (temp = strstr( buf , "\r")) != NULL )
                	{
                        	*temp = '\0';
                	}
                	n = hex2i(buf) + 2;
			//---debug---
			printf("Length:%s=%d\n",buf,n);

                	if ( n == 2 )
                	{
                        	break;
                	}
//			SockTool::readLine( fd , buf , sizeof(buf) );
			memset( buf, 0 , sizeof( buf ));
                	SockTool::readN(fd , buf , sizeof( buf ),n );
                	if ( (temp = strstr( buf , "\r")) != NULL ) 
			{
                        	*temp = '\0';
                	}
			//---debug---
			printf("BUF:\n%s\n",buf);
                	strcat( this->body , buf);
                	memset( buf , 0 , sizeof( buf ));*/
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
