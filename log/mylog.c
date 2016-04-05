#include "mylog.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
/*
struct tm *localtime(const time_t *timep);
 struct tm {
               int tm_sec;          seconds 
               int tm_min;          minutes
               int tm_hour;         hours 
               int tm_mday;         day of the month 
               int tm_mon;          month 
               int tm_year;         year 
               int tm_wday;         day of the week 
               int tm_yday;         day in the year 
               int tm_isdst;        daylight saving time 
           };
       tm_sec    The number of seconds after the minute, normally in the range
                  0 to 59, but can be up to 60 to allow for leap seconds.
       tm_min    The number of minutes after the hour, in the range 0 to 59.
       tm_hour   The number of hours past midnight, in the range 0 to 23.
       tm_mday   The day of the month, in the range 1 to 31.
       tm_mon    The number of months since January, in the range 0 to 11.
       tm_year   The number of years since 1900.
       tm_wday   The number of days since Sunday, in the range 0 to 6.
       tm_yday   The number of days since January 1, in the range 0 to 365.
*/
/*
*des:write log
*fd:file descriptor
*filter:filter level
*level:current level
*str:you want to write
*len:length of str
*return value:-1 on failed , 0 on success
*/
int writelog( int fd , int filter,int level, const char *str)
{
	char buf[512] = { 0 };
	struct tm *ti;
	char a[][11]={	"[DEBUG]   ",
			"[WARNING] ",
			"[ERROR]   "};
	if ( level > ERROR || filter > ERROR || level < DEBUG || filter < DEBUG)
		return-1;
	if ( level < filter)
		return 0;
	time_t t;
	time(&t);
	ti = localtime(&t);
	
	sprintf(buf,"%s %4d/%02d/%02d %02d:%02d:%02d :%s\n", a[level],
					ti->tm_year+1900,
					ti->tm_mon+1 ,
					ti->tm_mday,
					ti->tm_hour,
					ti->tm_min,
					ti->tm_sec,
					str);
	write(fd , buf ,strlen(buf));
	
	return 0;
} 

void mylog( int level , const char *str)
{
	int fd = open( "spider.log" , O_CREAT|O_RDWR|O_APPEND,0666);
	if ( fd != -1)
	{
		writelog(fd , ERROR , level , str);
		close( fd );	
	}
}
