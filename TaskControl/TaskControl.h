#ifndef __TASKCONTROL_H__
#define __TASKCONTROL_H__
#include <pthread.h>
#include "threadpool.h"
#include "../Queue/Queue.h"
#include "../URL/URL.h"

typedef void (*mycallback)(void *);

class TaskControl
{
public:
	TaskControl( int  num , mycallback fun );
	~TaskControl();
	int addTaskToQueue( URL *url );
	int isAllTaskDone();
	int getCurrentRun();
	
private:
	ThreadPool *handle;
	mycallback fun;
};


TaskControl::TaskControl( int num , mycallback fun )
{
	initThreadPool( &(this->handle) , num );
	this->fun = fun;
}


TaskControl::~TaskControl()
{
	destroyThreadPool( &(this->handle) );
}


int TaskControl::addTaskToQueue( URL *url )
{
	return addTask( this->handle, this->fun , url );
}


int TaskControl::isAllTaskDone()
{
	return isTaskAllDone( this->handle );
}

int TaskControl::getCurrentRun()
{
	return getCurrentRunNum( this->handle );
}

#endif
