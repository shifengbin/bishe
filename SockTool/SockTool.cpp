#include <pthread.h>
#include "sockutils.h"
#include "./SockTool.h"

pthread_mutex_t SockTool::lock = PTHREAD_MUTEX_INITIALIZER;
int SockTool::setNonBlock( int fd )
{
	return setnonblock(fd);
}

int SockTool::setBlock( int fd )
{
	return setblock(fd);
}

int SockTool::readTimeout( int fd, int sec )
{
	return read_timeout( fd , sec );
}

int SockTool::writeTimeout( int fd , int sec )
{
	return write_timeout( fd , sec );
}

int SockTool::acceptTimeout( int fd , struct sockaddr_in *addr , int sec )
{
	return acceptTimeout( fd , addr , sec );
}

int SockTool::connectTimeout( int fd, struct sockaddr_in *addr, int sec )
{
	int ret;
	pthread_mutex_lock(&lock);
	ret = connect_timeout( fd, addr , sec );
	pthread_mutex_unlock(&lock);
	return ret;
}

int SockTool::readN( int fd , void *buf ,int bufsize, int size)
{
	return readn( fd , buf , bufsize , size);
}

int SockTool::writeN( int fd, void *buf, int size)
{
	return writen( fd , buf , size);
}

int SockTool::readLine( int fd, void *buf, int bufsize )
{
	return readline( fd , buf , bufsize );
}

