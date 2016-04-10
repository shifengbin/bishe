#ifndef __SOCKUTILS_H__
#define __SOCKUTILS_H__

#ifdef __cplusplus
extern "C"{
#endif

#include <sys/socket.h>
#include <netinet/in.h>


/*
*description:set file descriptor O_NONBLOCK
*int fd: file descriptor
*return value: 0 on success and -1 on error
*/
int setnonblock( int fd);
/*
* set block
*/
int setblock( int fd );

/*
*description:test fd is able to read within sec 
*fd: file descriptor
*sec : time
*return 0 on fd is able to read,-1 and errno = ETIMEDOUT is timeout, -1 on error
*/
int read_timeout( int fd , int sec);
/*
*des: test fd is able to write
*return value: 0 on success, -1 and errno= ETIMEDOUT is timeout , -1 on error
*/
int write_timeout( int fd, int sec );


/*
*des:accept fd connect within sec
*fd :file descriptor
*addr:return client addr
*sec: time
*return value: return client fd on success, -1 and errno=ETIMEDOUT is timeout, -1*on error
*/
int accept_timeout( int fd , struct sockaddr_in *addr , int sec);

/*
*des:connect within sec
*fd:file descriptor
*addr:connect addr
*sec:time
*return value: 0 on success ,-1 and errno=ETIMEDOUT is timeout, -1 on errno
*/
int connect_timeout( int fd , struct sockaddr_in *addr, int sec);

/*
*des:read size of bytes from fd  to buf
*size:need to read size
*bufsize:size of buf
*return value:-1 on error, left of bytes on success
*/
int readn( int fd , void *buf ,int bufsize, int size);

/*
*des:write size of bytes from buf to fd
*size:need to write
*return:-1 on error, return left of write
*/
int writen( int fd , void * buf , int size);

/*
*des:read a line from fd
*bufsize:size of buf
*return value:-1 on error,0 on success
*/
int readline( int fd , void *buf , int bufsize);

#ifdef __cplusplus
}
#endif

#endif
