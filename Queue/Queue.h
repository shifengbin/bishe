#ifndef QUEUE_H
#define QUEUE_H

#ifndef NULL
#define NULL ((void*)0)
#endif

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
    Queue();
    ~Queue();
    int pushHead( T *node );
    int pushTail( T *node );
    int isEmpty();
    int getCount();
    T*  pop();
private:
    Node<T> *head;
    Node<T> *tail;
    int length;
};



template <typename T>
Queue<T>::Queue()
{
    head = NULL;
    tail = NULL;
    length = 0;
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
    temp = new Node<T>;
    temp->node = node;
    temp->next = head;
    head = temp;
    if ( tail == NULL)
    {
        tail = head;
    }
    length++;
}

template <typename T>
int Queue<T>::pushTail( T *node )
{
    Node<T> *temp = NULL;
    if ( node  == NULL)
    {
        return -1;
    }
    temp = new Node<T>;
    temp->node = node;
    if ( tail == NULL )
    {
        tail = temp;
        head = temp;
    }
    else
    {
        tail->next = temp;
        tail = temp;
    }
    length++;
}

template <typename T>
T*  Queue<T>::pop()
{
    if ( head == NULL || length == 0)
    {
        return NULL;
    }
    T *temp = head->node;
    Node<T> *del = head;
    head = head->next;
    delete del;
    length--;
    return temp;
}

#endif // QUEUE_H
