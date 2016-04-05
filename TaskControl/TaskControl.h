#ifndef __TASKCONTROL_H__
#define __TASKCONTROL_H__
#include <pthread.h>
#include "threadpool.h"
#include "../Queue/Queue.h"
#include "../URL/URL.h"

typedef void callback(void *);

class TaskControl
{
public:
	TaskControl( int  num , callback fun );
	~TaskControl();
	int addTask( URL *url );
	int isAllDone();
	int getCurrentRunNum();
	
private:
	ThreadPool *handle;
	callback *fun;
};


TaskControl::TaskControl( int num ,callback fun )
{
	initThreadPool( &(this->handle) , num );
	this->fun = fun;
}


TaskControl::~TaskControl()
{
	destroyThreadPool( &(this->handle) );
}


int TaskControl::addTask( URL *url )
{
	return addTask( this->handle, this->fun , url );
}


int TaskControl::isAllDone()
{
	return isTaskAllDone( this->handle );
}

int TaskControl::getCurrentRunNum()
{
	return getCurrentRunNum( this->handle );
}

#endif
