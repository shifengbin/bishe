#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <pcre2posix.h>


void save(char *cityName ,  char  *body)
{


	regex_t reg;
	regmatch_t pmatch;
	char *href = "href=\\\"http.*?\\\"";//get info url reg
	char ref[255] = { 0 };
	char *temp = body;
	
	int len = 0;
	if ( body == NULL || strlen(body) == 0 )
	{
		return;
	}

	if ( regcomp(&reg , href , 0) !=0 )
	{
		return;
	}
	// get info url
	if ( regexec( &reg , body , 1, &pmatch,0) == REG_NOMATCH )
	{
		return;
	}

	len = pmatch.rm_eo - pmatch.rm_so;
	temp+=pmatch.rm_so;
	*(temp+len-1) = 0;	
	sprintf(ref , "%s",temp);
	temp+=len;
///////////////////////
	puts(cityName);
	puts(ref);	
//////////////////////
	regfree(&reg);
	
}
void output( char *host , char *body , int type)
{
	char *regexstr = "<tr\\s+logr=[\\d\\D]*?>[\\d\\D]*?</tr>";//get house info
	char *cityreg = "locallist\\\":\\[\\{\\\"dispid\\\":\\\"\\d*\\\",\\\"name\\\":\\\".*?\\\"";//get city
	char *temp = NULL;//temp var
	char *ctmp = NULL;// city temp var
	char cityName[50] ={ 0 };//city name
	regex_t reg;//get house info reg
	regex_t cityr;//get city info reg
	regmatch_t pmatch;//reg return value
	int len = 0;
	puts(cityreg);
	if (regcomp(&reg,regexstr,0)!=0 || regcomp(&cityr,cityreg,0)!=0 )
	{
		puts("comp err");
		return;
	}
	temp = body;
	if ( regexec(&cityr,temp,1,&pmatch,0) == REG_NOMATCH )
	{
	//	puts("No City");
		sprintf(cityName,"%s","other");
	}
	else
	{
		temp+=pmatch.rm_so;
		len = pmatch.rm_eo-pmatch.rm_so;
		*(temp+len-1)=0;
		ctmp = temp+len-1;
		while( *ctmp !='\"'&& ctmp > temp )
		{
			ctmp--;
		}
		if ( ctmp == temp )
		{
			sprintf(cityName,"%s","other");
		}
		else
		{
			ctmp++;
			sprintf(cityName,"%s",ctmp);
		}
//		save(cityName);
		temp+=len+1;
	}

	puts(cityName);

	for(;;)
	{
		if (regexec(&reg, temp ,1,&pmatch,0 ) == REG_NOMATCH)
		{
//			puts("no match");
			break;
		}
		else
		{
//			puts("match");
			len = pmatch.rm_eo - pmatch.rm_so;
			temp = temp + pmatch.rm_so;
			*(temp+len) = 0;
			save( cityName, temp);
			temp+=len+1;
		//	printf("%d\n",len);
		}
	}
	regfree(&reg);
	regfree(&cityr);
	return;
}

int main()
{
	char *buf = malloc( 1024*1024 *3 );
	int fd = open("chuzu.html",O_RDONLY);
	int len = read(fd , buf , 1024*1024*3);
	buf[len] = 0;
	output("",buf,1);
	close(fd);
	return 0;
}
