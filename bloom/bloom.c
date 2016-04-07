#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "bloom.h"

#define BLOOM_SIZE 10000
#define BLOOM_BIT_SIZE (BLOOM_SIZE*sizeof(int));
static int bloom[BLOOM_SIZE] = { 0 };
static int seeds[8] = {3,5,7,9,11,13,15,17};
static unsigned int hash( char *str , int seed)
{
	char *temp = str;
	unsigned int ret = 0;
	while( temp != NULL && *temp !='\0')
	{
		ret = ret*seed + *temp;
		temp++;
	}
	return ret % BLOOM_BIT_SIZE;
}
void add( char *str )
{
	int i = 0;
	unsigned h = 0;
	for( i = 0; i< 8; i++)
	{
		h = hash( str , seeds[i]);
		bloom[h/sizeof(int)] |= 1<<(h%sizeof(int));
	}
}

int search( char *str)
{
	int  i = 0;
	unsigned int h = 0;
	for( i = 0; i< 8; i++)
	{
		h = hash( str, seeds[i]);
		if ( (bloom[h/sizeof(int)] & 1<<(h%sizeof(int))) == 0)
			return 0;

	}
	return 1;
}

/*
   int main()
   {
   int flag;
   char buf[1024] = { 0 };
   for(;;)
   {
   memset( buf , 0 , sizeof( buf ));
   scanf("%s",buf);
   flag = search(buf);
   if(!flag)
   {
   add(buf);
   }
   printf("%s:%s\n",buf,flag?"true":"false");
   }
   return 0;
   }*/
