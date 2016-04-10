#include <stdio.h>
#include "BloomFilter.h"

int main()
{
	char buf[100] = { 0 };
	while(1)
	{
		scanf("%s",buf);
		if( !Bloom::isExist(buf) )
		{
			Bloom::addFilter(buf);
		}
		else
		{
			printf("%s is Exist\n",buf);
		}
	}
	return 0;
}
