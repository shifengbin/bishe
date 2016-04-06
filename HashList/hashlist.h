#ifndef __HASHLIST_H__
#define __HASHLIST_H__

#ifndef NULL
#define NULL ((void*)0)
#endif

#define LISTLENGTH 10

#ifdef __cplusplus
extern "C"{
#endif

typedef struct HashNode
{
        void *node;
        char *key;
        struct HashNode *next;
}HashNode;

typedef struct HashList
{
        HashNode list[LISTLENGTH];
        int length;
}HashList;

int   initHashList( HashList *list );
int   destroyHashList( HashList *list);
int   addElement( HashList *list, const char *key , void *value );
void* delElement( HashList *list, const char *key);
void* getElement( HashList *list, const char *key);
int   getLength( HashList *list );


#ifdef __cplusplus
}
#endif

#endif
