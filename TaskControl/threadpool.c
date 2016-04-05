#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "threadpool.h"

typedef struct Task{
	void (*task)(void*);	 // callback function
	void *arg;		 // arg of callback function
	struct Task *next;	 // next task 
}ThreadPoolTask;

typedef struct ThreadPool_t
{
	pthread_mutex_t lock;
	pthread_cond_t cond;
	pthread_t *ids;
	int count;
	ThreadPoolTask head;
	int isdestroy;
}ThreadPool_t;


static void *work( void* arg)
{
	ThreadPool_t * pool = ( ThreadPool_t*)arg;
	ThreadPoolTask *t;	
//	printf("start:%x\n",pthread_self());
	while(1)
	{
		pthread_mutex_lock(&(pool->lock));
		while(pool->head.next== NULL && !pool->isdestroy)
		{
			pthread_cond_wait(&(pool->cond),&(pool->lock));
		}
		pool->count++;
		if( pool->isdestroy)
		{
			pthread_mutex_unlock(&(pool->lock));
			break;
		}
		

		t = pool->head.next;
		pool->head.next = t->next;

		pthread_mutex_unlock(&(pool->lock));
		
		//printf("Task:%x\n",pthread_self());
		// run task
		t->task(t->arg);
		free(t);
		//task end
		pthread_mutex_lock( &(pool->lock) );
		pool->count--;
		pthread_mutex_unlock( &(pool->lock ) );
	}
//	printf("threadend:%x\n",pthread_self());
	return (void*)0;
}

/*
* description: initialize thread pool
* tp:thread pool handle
* poolsize: count of thread 
* return value: 0 on success,-1 on failed
*/
int initThreadPool( ThreadPool **tp , int poolsize)
{
	ThreadPool_t *p;
	int i;
	if (tp == NULL || poolsize < 1)
	{
		return -1;
	}

	p = (ThreadPool_t *)malloc( sizeof( ThreadPool_t) + sizeof(pthread_t)*poolsize);

	if ( p == NULL)
	{
		return -1;
	}
	
//	p->lock = PTHREAD_MUTEX_INITIALIZER;
//	p->cond = PTHREAD_COND_INITIALIZER;
	pthread_mutex_init(&(p->lock),NULL);
	pthread_cond_init(&(p->cond),NULL);
	p->ids = (pthread_t*)(p + 1);
	p->count = 0;
	p->head.next = NULL;
	p->isdestroy = 0;
	
	for( i = 0 ; i < poolsize ; i++ )
	{
		pthread_create( &(p->ids[i]) , NULL , work , p);
	}

	*tp = p;
	
	return 0;
}

/*
* description:destroy thread pool
* tp: handle of thread pool
* return value: 0 in success , -1 on failed
*/
int destroyThreadPool( ThreadPool **tp  )
{
	ThreadPool_t *p = (ThreadPool_t *)*tp;
	int i;
	if ( tp == NULL )
		return -1;
	if ( p == NULL)
		return 0;
	p->isdestroy = 1;
	pthread_cond_broadcast(&(p->cond));
	
	for( i = 0; i < p->count; i++)
	{
		pthread_join(p->ids[i],NULL);
	}

	pthread_mutex_destroy(&(p->lock));
	pthread_cond_destroy(&(p->cond));
	
	free(p);
	*tp = NULL;
	return 0;
}

/*
* description: add task to thread pool
* tp: handle of thread pool
* task:user want to execute task
* return value: 0 on success , -1 on failed
*/
int addTask( ThreadPool *tp , void (*func)(void*) , void*arg)
{
	ThreadPool_t *p = (ThreadPool_t*) tp;
	ThreadPoolTask *mtask,*t;
	if ( p == NULL || func == NULL )
		return -1;

	t = (ThreadPoolTask*)malloc(sizeof(ThreadPoolTask));
	if ( t  == NULL)
		return -1;
	t->task = func;
	t->arg = arg;

	mtask = &(p->head);
	pthread_mutex_lock(&(p->lock));
	while(	mtask->next != NULL)
	{
		mtask = mtask->next;
	}
	t->next = NULL;
	mtask->next = t;
	pthread_mutex_unlock(&(p->lock));
	
	pthread_cond_signal(&(p->cond));
	
	return 0;
}

/*
* description:if task is all finished return true;
*/
int isTaskAllDone(ThreadPool *tp)
{
	return (((ThreadPool_t*)tp)->head.next == NULL);

}
/*
*get current thread run num;
*/
int getCurrentRunNum( ThreadPool *pool)
{
	return ((ThreadPool_t*)pool)->count;
}
