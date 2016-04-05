#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#ifdef __cplusplus
extern "C"{
#endif

typedef void ThreadPool;



/*
* description: initialize thread pool
* tp:thread pool handle
* poolsize: count of thread 
* return value: 0 on success,-1 on failed
*/
int initThreadPool( ThreadPool **tp , int poolsize);

/*
* description:destroy thread pool
* tp: handle of thread pool
* return value: 0 in success , -1 on failed
*/
int destroyThreadPool( ThreadPool **tp);

/*
* description: add task to thread pool
* tp: handle of thread pool
* task:user want to execute task
* return value: 0 on success , -1 on failed
*/
int addTask( ThreadPool *tp , void (*fun)(void*),void *arg); 

/*
* description:if task is all finished return true;
*/
int isTaskAllDone(ThreadPool *tp);
/*
*return Current Run Number
*/
int getCurrentRunNum( ThreadPool *p );
#ifdef __cplusplus
}
#endif

#endif
