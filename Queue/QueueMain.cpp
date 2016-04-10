#include <stdio.h>
#include "Queue.h"

using namespace std;

int main()
{

    Queue<int> q(HEAD);
    for( int i = 0; i < 10 ; i++)
    {
        q.push( new int(i));
    }


    printf("%d\n",q.getCount());
    int *p;
    p = q.pop();
    for( ; p != NULL; p=q.pop() )
    {
        printf("%d:%d\n",q.getCount(),*p);
    }

    printf("%d\n",q.isEmpty());

    return 0;
}

