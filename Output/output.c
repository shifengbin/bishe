#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <pcre2posix.h>
#include <pthread.h>

#include "../Persistence/sqlite3.h"

static sqlite3 *db = NULL;
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t outlock = PTHREAD_MUTEX_INITIALIZER;
static char *err;

int initDB( char *dbfile )
{

	pthread_mutex_lock(&lock);
	while( db == NULL )
	{
		int ret = sqlite3_open( dbfile , &db );
		char *sql="create table house(id integer primary key,title char(200),city char(100), address char(100),type char(50),price char(8),infourl char(255),source char(50))";
		if ( ret != SQLITE_OK )
		{
			puts( "create database error");
			db = NULL;
			pthread_mutex_unlock(&lock);
			return -1;
		}
		ret = sqlite3_exec(db,sql,0,0,&err);
		if (ret != SQLITE_OK )
		{
			puts(sql);
			puts(err);
			pthread_mutex_unlock(&lock);
			return -1;
		}
	}
	pthread_mutex_unlock(&lock);
	return 0;
}


int saveToDB( char *title,char *city, char *address, char *type, char *price, char *infourl, char *source)
{
	pthread_mutex_lock(&lock);
	char sql[2048] = { 0 };
	sprintf(sql,"insert into house(title,city,address,type,price,infourl,source) values('%s','%s','%s','%s','%s','%s','%s')",title,city,address,type,price,infourl,source);
	int ret = sqlite3_exec(db,sql,0,0,&err);
	if (ret != SQLITE_OK )
	{
		puts(sql);
		pthread_mutex_unlock(&lock);
		return -1;
	}
	pthread_mutex_unlock(&lock);
	return 0;
}

void save(char *host,char *cityName ,  char  *body)
{


	regex_t reg;
	regex_t titlereg;
	regex_t xiaoqureg;
	regex_t pricereg;
	regex_t showroomreg;

	regmatch_t pmatch;
	char *href = "href=\\\"http.*?\\\"";//get info url reg
	char *title = "<a.*?onclick.*?>.*?</a>";
	char *xiaoqu = "<a href.*?class=\\\"a_xq1\\\">.*?</a>";
	char *price = "<b\\sclass=\'pri\'>.*?</b>";
	char *showroom="<span\\sclass=\\\"showroom\\\">.*?</span>";

	char ref[1024] = { 0 };
	char t_title[512] = { 0 };
	char t_xiaoqu[255] = { 0 };
	char t_price[16] = { 0 };
	char t_showroom[32] = { 0 };

	char *temp = body;
	char *ti;

	int len = 0;
	if ( body == NULL || strlen(body) == 0 )
	{
		return;
	}

	if ( regcomp(&reg , href , 0) !=0 || regcomp( &titlereg , title , 0)!=0||regcomp(&xiaoqureg, xiaoqu ,0) != 0 || regcomp( &pricereg ,price,0)!= 0||regcomp(&showroomreg,showroom,0) != 0)
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
	sprintf(ref , "%s",temp+6);
	temp+=len;
	// get title
	if ( regexec( &titlereg,temp,1,&pmatch, 0 ) == REG_NOMATCH )
	{
		return;
	}
	len = pmatch.rm_eo - pmatch.rm_so;
	temp+=pmatch.rm_so;
	if ( (ti = strstr(temp , ">")) == NULL)
	{
		return;
	}
	ti++;
	*(temp+len-4) = 0;	
	sprintf(t_title , "%s",ti);
	temp+=len;
	// get xiaoqu	
	if ( regexec( &xiaoqureg,temp,1,&pmatch, 0 ) == REG_NOMATCH )
	{
		return;
	}
	len = pmatch.rm_eo - pmatch.rm_so;
	temp+=pmatch.rm_so;
	if ( (ti = strstr(temp , ">")) == NULL)
	{
		return;
	}
	ti++;
	*(temp+len-4) = 0;	
	sprintf(t_xiaoqu , "%s",ti);
	temp+=len;
	//get price
	if ( regexec( &pricereg,temp,1,&pmatch, 0 ) == REG_NOMATCH )
	{
		return;
	}
	len = pmatch.rm_eo - pmatch.rm_so;
	temp+=pmatch.rm_so;
	if ( (ti = strstr(temp , ">")) == NULL)
	{
		return;
	}
	ti++;
	*(temp+len-4) = 0;	
	sprintf(t_price , "%s",ti);
	temp+=len;
	//get showroom
	if ( regexec( &showroomreg,temp,1,&pmatch, 0 ) == REG_NOMATCH )
	{
		return;
	}
	len = pmatch.rm_eo - pmatch.rm_so;
	temp+=pmatch.rm_so;
	if ( (ti = strstr(temp , ">")) == NULL)
	{
		return;
	}
	ti++;
	*(temp+len-7) = 0;	
	sprintf(t_showroom , "%s",ti);
	temp+=len;
	///////////////////////
	puts(host);
	puts(cityName);
	puts(ref);	
	puts(t_title);
	puts(t_xiaoqu);
	puts(t_price);
	puts(t_showroom);
	saveToDB(t_title,cityName,t_xiaoqu,t_showroom,t_price,ref,host);
	//////////////////////
	regfree(&reg);
	regfree(&titlereg);
	regfree(&xiaoqureg);
	regfree(&pricereg);
	regfree(&showroomreg);

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
	
	initDB("house.db");

	if ( type != 2 )
	{
		return;
	}
//	pthread_mutex_lock(&outlock);
	if (regcomp(&reg,regexstr,0)!=0 || regcomp(&cityr,cityreg,0)!=0 )
	{
		puts("comp err");
//		pthread_mutex_unlock(&outlock);
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

	//	puts(cityName);

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
			save(host, cityName, temp);
			temp+=len+1;
			//	printf("%d\n",len);
		}
	}
	regfree(&reg);
	regfree(&cityr);
//	pthread_mutex_unlock(&outlock);
	return;
}

/*
int main()
{
	char *buf = malloc( 1024*1024 *3 );
	int fd = open("chuzu.html",O_RDONLY);
	int len = read(fd , buf , 1024*1024*3);
	buf[len] = 0;
	output("bj.58.com",buf,3);
	close(fd);
	return 0;
}
*/
