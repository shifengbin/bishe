#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "ModelTool.h"

typedef int (*ADD)(int,int);
ADD pFun;
Model *m;
void fun( int sig )
{
	if ( sig == SIGRTMIN )
	{
		if ( m != NULL )
		{
			delete m;
			m = NULL;
		}
		m = new Model("./add.so");
        	pFun = (ADD)(m->getMethod("add"));
        	printf("is open:%d\n",m->isOpenSuccess());
	}

}
int main()
{
	signal(SIGRTMIN,fun);
	m = new Model("./add.so");
       	pFun = (ADD)(m->getMethod("add"));
       	printf("is open:%d\n",m->isOpenSuccess());
	for(;;)
	{
		if ( pFun != NULL )
			printf("%d\n",pFun(1,2));
		sleep(1);
	}
	return 0;
}
