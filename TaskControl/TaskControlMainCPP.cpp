#include <stdio.h>
#include <unistd.h>
#include "TaskControl.h"

#define TNUM 100
void fun( void * a)
{
	sleep(1);
	printf("hello\n");
}
int main()
{
	TaskControl tc(5,fun);
	int i;
	sleep(2);

	for( i = 0 ; i < TNUM ; i++)
        {
                tc.addTaskToQueue(NULL);
        }
        sleep(1);
	
	while( tc.getCurrentRun() )
	{
		sleep(1);
	}


//	pause();

	return 0;
}
