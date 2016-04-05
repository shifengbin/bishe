#include <stdio.h>
#include "threadpool.h"

#define TNUM 100
void fun( void * a)
{
	sleep(1);
	printf("hello\n");
}
int main()
{
	ThreadPool *handle;
	int i;
	initThreadPool(&handle,15);
	sleep(2);

	for( i = 0 ; i < TNUM ; i++)
        {
                addTask(handle,fun,NULL);
        }
        sleep(1);
	
	while( getCurrentRunNum( handle ) )
	{
		sleep(1);
	}
	destroyThreadPool( &handle );


//	pause();

	return 0;
}
