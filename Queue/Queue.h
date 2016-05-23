#ifndef QUEUE_H
#define QUEUE_H


#define HEAD  1
#define TAIL  0

#include <pthread.h>

template <typename T>

class Node
{
public:
    T *node;
    Node<T> *next;
};

template <typename T>
class Queue
{
public:
    Queue( int );
    ~Queue();
    int pushHead( T *node );
    int pushTail( T *node );
    int isEmpty();
    int getCount();
    T*  pop();
    int push( T *node );
private:
    Node<T> *head;
    Node<T> *tail;
    int method;
    int length;
    pthread_mutex_t lock;
};



template <typename T>
Queue<T>::Queue( int method )
{
    head = NULL;
    tail = NULL;
    length = 0;
    this->method = method;
    pthread_mutex_init( &lock , NULL );
}

template <typename T>
Queue<T>::~Queue()
{
    while (length)
    {
        pop();
    }
}

template <typename T>
int Queue<T>::isEmpty()
{
    return !length;
}

template <typename T>
int Queue<T>::getCount()
{
    return length;
}

template <typename T>
int Queue<T>::pushHead( T *node )
{
    Node<T> *temp = NULL;
    if ( node == NULL)
    {
        return -1;
    }

    pthread_mutex_lock( &lock );
    temp = new Node<T>;
    temp->node = node;
    temp->next = head;
    head = temp;
    if ( tail == NULL)
    {
	temp->next = NULL;
        tail = head;
    }
    length++;
    pthread_mutex_unlock(&lock);
}

template <typename T>
int Queue<T>::pushTail( T *node )
{
    Node<T> *temp = NULL;
    if ( node  == NULL)
    {
        return -1;
    }
    pthread_mutex_lock(&lock);
    temp = new Node<T>;
    temp->node = node;
    temp->next = NULL;
    if ( tail == NULL && head == NULL )
    {
        tail = temp;
        head = temp;
    }
    else if ( tail != NULL )
    {
        tail->next = temp;
        tail = temp;
    }
    length++;
    pthread_mutex_unlock(&lock);
}

template <typename T>
T*  Queue<T>::pop()
{
    if ( head == NULL || length <= 0)
    {
	tail = head = NULL;
        return NULL;
    }
    pthread_mutex_lock(&lock);
    T *temp = head->node;
    Node<T> *del = head;
    head = head->next;
    delete del;
    length--;
    pthread_mutex_unlock(&lock);
    return temp;
}

template <typename T>
int Queue<T>::push( T *node )
{
	if ( method == TAIL )
	{
		return pushTail( node );
	}
	else
	{
		return pushHead( node );
	}
}

#endif // QUEUE_H
