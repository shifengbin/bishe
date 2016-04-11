#include <stdio.h>
#include <stdlib.h>

#include "HashLink.h"

int main(void)
{
    int a ;
    int *data;
    char buf[10] = { 0 };
    int i;
    HashLink hl;
    for( i = 0 ; i < 20 ; i++)
    {
        sprintf( buf, "%c" , 'a'+i);
        data = (int*)malloc( sizeof(int));
        *data = i;
        a = hl.set(buf ,data);
        printf("insert:%s length:%d return:%d\n",buf,hl.getSize(),a);
    }
    for( i = 0 ; i < 50 ; i++)
    {
        sprintf( buf, "%c" , 'a'+i);
        data = (int*)hl.get(buf );
        if( data != NULL)
            printf("key:%s  getdata:%d \n",buf,*data);
        else
            printf("key:%s  getdata:NULL \n",buf);
    }

    for( i = 0 ; i < 50 ; i++)
    {
        sprintf( buf, "%c" , 'a'+i%20);
        data = (int*)hl.remove(buf );
        if ( data != NULL )
            printf("key:%s  getdata:%d \n",buf,*data);

    }


    return 0;
}

