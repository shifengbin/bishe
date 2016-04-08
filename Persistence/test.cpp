#include "Persistence.h"
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>

int select( void *data , int count, char **value, char **name)
{

	for( int i = 0; i < count ; i++)
	{
		printf("%s=%s ",name[i],value[i]);
	}	
	puts("");

	return 0;
}



int main()
{
	Persistence *p = Persistence::getPersistence();
	p->exec("create table URL(id integer primary key,name varchar(255))");
	p->exec("insert into URL(name) values('zhangsan')");
	p->exec("insert into URL(name) values('zhangsan')");
	p->exec("insert into URL(name) values('zhangsan')");
	p->exec("insert into URL(name) values('zhangsan')");
	p->exec("insert into URL(name) values('zhangsan')");
	p->exec("insert into URL(name) values('zhangsan')");
	p->exec("insert into URL(name) values('zhangsan')");
	p->exec("insert into URL(name) values('zhangsan')");
	p->exec("insert into URL(name) values('zhangsan')");
	p->exec("insert into URL(name) values('zhangsan')");
	p->exec("insert into URL(name) values('zhangsan')");
	p->query("select * from URL limit 2",select,NULL);
	return 0;
}
