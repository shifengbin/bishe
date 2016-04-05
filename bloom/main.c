#include "bloom.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
}
