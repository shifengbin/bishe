#ifndef __MYLOG_H__
#define __MYLOG_H__

#ifdef __cplusplus
extern "C" {
#endif

enum LEVEL{
	DEBUG ,
	WARNING,
	ERROR
};

/*
*des:write log
*fd:file descriptor
*filter:filter level
*level:current level
*str:you want to write
*len:length of str
*return value: -1 on failed or 0 on success
*/
int writelog( int fd , int filter,int level, const char *str); 

void mylog( int level , const char *str);

#ifdef __cplusplus
}
#endif

#endif
