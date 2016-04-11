#ifndef HEX2I_H
#define HEX2I_H
#include <string.h>


int hex2i( const char *hex )
{
	int ret = 0;
	int index = strlen( hex ) - 1;
	int temp = 0;
	int per = 1;
	int i;
	for( i = index; i>= 0; i--)
	{
		if( hex[i] >= 'a' && hex[i] <= 'f' )
		{
			temp = hex[i] - 'a' + 10;
		}
		else if ( hex[i] >= 'A' && hex[i] <= 'F' )
		{
			temp = hex[i] - 'A' + 10;
		}
		else if ( hex[i] >= '0' && hex[i] <= '9' )
		{
			temp = hex[i] - '0';	
		}
		else
		{
			ret = 0;
			per = 1;
			continue;
		}
		ret += ( per * temp );
		per*=16;
		
	}
	return ret;
}


#endif
