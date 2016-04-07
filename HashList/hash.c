#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
int main()
{
	char buf[1024] = { 0 };
	while(1)
	{
		scanf("%s",buf);
		printf("%u\n",hash(buf,strlen(buf)));
		memset(buf , 0 , sizeof(buf));
	}
	return 0;
}
*/
