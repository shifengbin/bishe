#ifndef SOCKTOOL_H
#define SOCKTOOL_H
#include "sockutils.h"

class SockTool
{
private:
	static pthread_mutex_t lock;
public:
	static int setNonBlock( int fd );
	static int setBlock( int fd );
	static int readTimeout( int fd, int sec );
	static int writeTimeout( int fd , int sec );
	static int acceptTimeout( int fd , struct sockaddr_in *addr , int sec );
	static int connectTimeout( int fd, struct sockaddr_in *addr, int sec );
	static int readN( int fd , void *buf ,int bufsize, int size);
	static int writeN( int fd, void *buf, int size);
	static int readLine( int fd, void *buf, int bufsize );

};
#endif
