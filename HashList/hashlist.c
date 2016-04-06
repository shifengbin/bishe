#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashlist.h"

/*
*计算字符串的hash值
*/
unsigned int hash( const char *str , int len)
{

        unsigned int ret = 0;
        unsigned int seed = 131;

        int i;
        for ( i = 0 ; i < len ; i++)
        {
                ret = ret * seed + str[i];
        }
        return ret;
}
/*
*初始化hashlist
*/
int   initHashList( HashList *list )
{
    if ( list == NULL )
    {
        return -1;
    }
    list->length = 0;
    memset( list->list , 0 , sizeof( list->list ));
    return 0;
}
/*
*销毁hashlist
*/
int   destroyHashList( HashList *list)
{
    int i = 0;
    HashNode *temp;
    if ( list == NULL )
    {
        return -1;
    }

    for( i = 0; i < LISTLENGTH ; i++ )
    {
        while( list->list[i].next != NULL )
        {
            temp = list->list[i].next;
            list->list[i].next = list->list[i].next->next;
            if (temp != NULL )
                free(temp);
        }
    }
    list->length = 0;
    return 0;
}
/*
*在hashlist中加入元素
*/
int   addElement( HashList *list, const char *key , void *value )
{
    int pos = 0;
    HashNode *temp = NULL;
    void *data = NULL;
    char *tkey = NULL;

    if ( list == NULL || key == NULL || value == NULL )
    {
        return -1;
    }

    data = getElement( list , key );
    if (data != NULL )
    {
        return -1;
    }

    pos = hash( key ,strlen(key)) % LISTLENGTH;

    temp = (HashNode*)malloc( sizeof( HashNode ) + strlen( key )+ 1 );

    if ( temp == NULL )
    {
        return -1;
    }
    tkey = (char *)(temp + 1);
    sprintf(tkey , "%s", key);
    temp->node = value;
    temp->key = tkey;
    temp->next = list->list[pos].next;
    list->list[pos].next = temp;
    list->length++;

    return 0;
}
/*
*获取hashlist中key为key的值
*/
void* getElement( HashList *list, const char *key)
{
    int pos = 0;
    HashNode *temp = NULL;

    if ( list == NULL || key == NULL )
    {
        return NULL;
    }

    pos = hash( key , strlen( key )) % LISTLENGTH;
    temp = list->list[pos].next;
    while( temp != NULL )
    {
        if ( !strcmp ( temp->key , key ))
        {
            return temp->node;
        }
        temp = temp->next;
    }

    return NULL;
}
/*
*删除list中key为key的元素并返回元素的值
*/
void* delElement( HashList *list, const char *key)
{
    int pos = 0;
    HashNode *temp = NULL;
    HashNode *pre = NULL;
    HashNode *del = NULL;
    void *data = NULL;
    if ( list == NULL || key == NULL )
    {
        return NULL;
    }

    pos = hash( key , strlen( key )) % LISTLENGTH;
    pre = &(list->list[pos]);
    temp = list->list[pos].next;
    while( temp != NULL )
    {
        if ( !strcmp ( temp->key , key ))
        {
            del = temp;
            data = temp->node;
            pre->next = del->next;
            free( del );
            list->length--;
            return data;
        }
        pre = temp;
        temp = temp->next;
    }
    return NULL;
}

int   getLength( HashList *list )
{
    if (list == NULL )
    {
        return -1;
    }
    return list->length;
}
