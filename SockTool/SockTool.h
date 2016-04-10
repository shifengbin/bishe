#ifndef SOCKTOOL_H
#define SOCKTOOL_H

#include "sockutils.h"

class SockTool
{
public:
	static int setNonBlock( int fd )
	{
		return setnonblock(fd);
	}
	
	static int setBlock( int fd )
	{
		return setblock(fd);
	}
	
	static int readTimeout( int fd, int sec )
	{
		return read_timeout( fd , sec );
	}
	
	static int writeTimeout( int fd , int sec )
	{
		return write_timeout( fd , sec );
	}
	
	static int acceptTimeout( int fd , struct sockaddr_in *addr , int sec )
	{
		return acceptTimeout( fd , addr , sec );
	}

	static int connectTimeout( int fd, struct sockaddr_in *addr, int sec )
	{
		return connect_timeout( fd, addr , sec );
	}

	static int readN( int fd , void *buf ,int bufsize, int size)
	{
		return readn( fd , buf , bufsize , size);
	}

	static int writeN( int fd, void *buf, int size)
	{
		return writen( fd , buf , size);
	}

	static int readLine( int fd, void *buf, int bufsize )
	{
		return readline( fd , buf , bufsize );
	}

};
#endif
