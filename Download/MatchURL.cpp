#include <pcre2posix.h>
#include <string.h>
#include <stdio.h>

#include "MatchURL.h"
#include "../bloom/BloomFilter.h"

int isAbsoluteURL( const char *url)
{
	return !(strstr( url , "//" ) == NULL);
}

void GetURLFromBody( ModePair *pattern , char *host ,  char *body)
{
	regex_t reg,http;
	regmatch_t pmatch;
	char url[512] = { 0 };
	char *regexstr = NULL;
	char *temp;
	char chr;
	char *c;
	int len;
	if ( pattern == NULL || body == NULL )
	{
		puts("pattern or body is NULL");
		return ;
	}
	regexstr = pattern->getMode();
//	puts(body);
//	puts(regexstr);
	if (regcomp(&reg,regexstr,0)!=0)
	{
		puts("Regular Experssion Error");
		return ;
	}
	temp = body;	
	for(;;)
	{
		if (regexec(&reg,temp,1,&pmatch,0) == REG_NOMATCH)
		{
//			puts("NO Match");
			break;
		}
		else
		{
			temp = temp + pmatch.rm_so;
			len = pmatch.rm_eo - pmatch.rm_so;
			//write(STDOUT_FILENO,temp+6,len-7);
			c = temp +len -1;
			chr = *c;
			*c = '\0';
			if ( isAbsoluteURL( temp + 6 ) )	
			{
				sprintf(url,"%s",temp);
			}
			else
			{
				sprintf(url,"http://%s%s",host,temp);
			}
			///--------------store database
			if ( !Bloom::isExist(url+6) )
			{
				Bloom::addFilter(url+6);
				puts(url+6);
			}
			///--------------
			*c = chr;
			temp+=len;
		}
	}
	return;
}
