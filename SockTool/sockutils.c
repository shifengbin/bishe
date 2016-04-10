#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "sockutils.h"

/*
*description:set file descriptor O_NONBLOCK
*int fd: file descriptor
*return value: 0 on success and -1 on error
*/
int setnonblock( int fd)
{
	int flags = fcntl( fd , F_GETFL); 
	if (flags < 0 )
		return -1;
	flags|=O_NONBLOCK;
	if ( fcntl( fd, F_SETFL , flags) < 0)
		return -1;
	return 0;
}
/*
* set block
*/
int setblock( int fd )
{
	int flags = fcntl( fd , F_GETFL); 
	if (flags < 0 )
		return -1;
	flags&=~O_NONBLOCK;
	if ( fcntl( fd, F_SETFL , flags) < 0)
		return -1;
	return 0;
}

/*
*description:test fd is able to read within sec 
*fd: file descriptor
*sec : time
*return 0 on fd is able to read,-1 and errno = ETIMEDOUT is timeout, -1 on error
*/
int read_timeout( int fd , int sec)
{
	fd_set fds;
	struct timeval t;
	int ret;
	
	if ( sec <= 0)
		return 0;

	FD_ZERO(&fds);
	FD_SET(fd,&fds);
	
	t.tv_sec = sec;
	t.tv_usec = 0;
	do
	{
		ret = select( fd+1 , &fds, NULL, NULL ,&t);
	}while(ret < 0 && errno == EINTR);

	if ( ret < 0 )
	{
		return -1;
	}else if (ret == 0)
	{
		errno = ETIMEDOUT;
		return -1;
	}

	return 0;
}
/*
*des: test fd is able to write
*return value: 0 on success, -1 and errno= ETIMEDOUT is timeout , -1 on error
*/
int write_timeout( int fd, int sec )
{
	fd_set fds;
	int ret;
	struct timeval t;	
	
	if ( sec <= 0)
		return 0;

	FD_ZERO(&fds);
	FD_SET( fd , &fds);
	
	t.tv_sec = sec;
	t.tv_usec = 0;
	
	do
	{
		ret = select( fd+1, NULL , &fds, NULL , &t);
	}while(ret < 0 && errno == EINTR);
		
	if (ret < 0)
	{
		return -1;
	}
	else if ( ret == 0)
	{
		errno = ETIMEDOUT;
		return -1;
	}
	return 0;
}


/*
*des:accept fd connect within sec
*fd :file descriptor
*addr:return client addr
*sec: time
*return value: return client fd on success, -1 and errno=ETIMEDOUT is timeout, -1*on error
*/
int accept_timeout( int fd , struct sockaddr_in *addr , int sec)
{
	fd_set fds;
	struct timeval t;
	int ret;
	socklen_t len = sizeof( struct sockaddr_in);
	
	if ( sec <= 0 )
		return 0;

	FD_ZERO(&fds);
	FD_SET(fd,&fds);
	
	t.tv_sec = sec;
	t.tv_usec = 0;

	do
	{
		ret = select( fd +1, &fds, NULL , NULL ,&t);
	}while( ret < 0 && errno == EINTR);

	if ( ret < 0)
	{
		return -1;
	}
	else if ( ret == 0)
	{
		errno = ETIMEDOUT;
		return -1;
	}
		
	memset( addr , 0 , sizeof( struct sockaddr_in));
	if ( (ret = accept( fd , (struct sockaddr*) addr,&len)) < 0 )
		return -1;
	 
	return ret;

}

/*
*des:connect within sec
*fd:file descriptor
*addr:connect addr
*sec:time
*return value: 0 on success ,-1 and errno=ETIMEDOUT is timeout, -1 on errno
*/
int connect_timeout( int fd , struct sockaddr_in *addr, int sec)
{
	fd_set fds;
	int ret;
	struct timeval t;
	
	if ( sec <= 0)
		return 0;	
	
	setnonblock(fd);

	ret = connect( fd , (struct sockaddr*) addr , sizeof( struct sockaddr_in));
	if ( ret < 0  && errno == EINPROGRESS)
	{
		FD_ZERO(&fds);
		FD_SET(fd,&fds);
		
		t.tv_sec = sec;
		t.tv_usec = 0;
		
		do
		{
			ret = select( fd+1 , NULL , &fds, NULL , &t);
		}while(ret < 0 && errno == EINTR );	
		
		if ( ret > 0)
		{
			int err;
			int len;
			if ( getsockopt( fd , SOL_SOCKET, SO_ERROR ,(void *)&err , &len) == 0 )
				ret = 0;
			else
				ret =  -1;
		}
		else if ( ret == 0)
		{
			errno = ETIMEDOUT;
			ret = -1;
		}
		else
		{
			ret = -1;
		}
		
	}

	setblock(fd);	

	return ret;
}

int readn( int fd , void *buf ,int bufsize, int size)
{
	int leftn = size;
	char *p = buf;
	int ret;
	
	if ( buf == NULL || bufsize < size || size < 0)
		return -1;

	if (size == 0 )
		return 0;

	while(leftn > 0)
	{
		ret = read( fd , p ,leftn);
		if ( ret <0 && errno == EINTR)
		{
			continue;
		}
		else if ( ret == 0 )
		{
			break;
		}
		else
		{
			leftn -= ret;
			p += ret;
		}
	
	}
	return size - leftn;
}
int writen( int fd , void * buf , int size)
{
	int leftn = size;
	char *p = buf;
	int ret;
	
	if ( buf == NULL || size < 0 )
		return -1;
	
	if ( size == 0)
		return 0;	

	while( leftn > 0)
	{
		ret = write( fd , p , leftn);
		if ( ret < 0 && errno == EINTR)
		{
			continue;
		}
		else 
		{
			leftn -= ret;
			p += ret;	
		}
	}

	return 0;
}
int readline( int fd , void *buf , int bufsize)
{
	int leftn = bufsize;
	char *p = buf;
	char *t = NULL;
	int ret;
	int readlen;
	if (buf == NULL)
		return -1;

	while( leftn > 0 )
	{
		ret = recv( fd , p , leftn , MSG_PEEK );
		if ( ret < 0 && errno == EINTR)
		{
			continue;
		}
		else if ( ret == 0 )
		{
			return -1;
		}
		
		if ( (t = strchr( p , '\n')) != NULL)
		{
			
			readlen = readn( fd, p , t - p +1, t -p +1);
			p[readlen] = '\0';	
			return 0;
		}

		readn( fd , p , ret , ret);
		leftn -= ret;
		p += ret;
	}
	return -1;
}
