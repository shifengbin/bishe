#ifndef __URL_H__
#define __URL_H__
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "../Persistence/Persistence.h"




class URL
{
private:
	int id;
	char *urlStr;
	int type;
	int deep;
	int state;
public:
	URL()
	{
		id = 0;
		urlStr = NULL;
		type = 0;
		deep = 0;
		state = 0;
	}

	~URL()
	{
		if( urlStr != NULL )
		{
			delete[] urlStr;
		}
	}
	int getId()
	{
		return id;
	}

	void setId( int id)
	{
		this->id = id;
	}

	char *getURLStr()
	{
		return urlStr;
	}

	int setURLStr( const char *str)
	{
		int length = strlen( str ) + 1;
		urlStr = new char[length];
		if ( urlStr == NULL )
		{	
			return -1;
		}
		sprintf( urlStr,"%s",str);
		return 0;
	}

	int getType()
	{
		return type;
	}

	void setType( int type)
	{
		this->type = type;
	}

	int getDeep()
	{
		return deep;
	}

	void setDeep( int deep )
	{
		this->deep = deep;
	}

	int getState()
	{
		return state;
	}

	void setState( int state)
	{
		this->state = state;
	}
	
	int setStateToDB( int state )
	{
		char buf[1024] = { 0 };
		Persistence *db = Persistence::getPersistence();
		sprintf(buf,"update url set state=%d where id=%d",state,this->id);
		db->exec(buf);
	
	}
	
	int save()
	{
		char buf[1024] = { 0 };
		Persistence *db = Persistence::getPersistence();
		sprintf(buf,"insert into url(urlstr,type,deep) values('%s',%d,%d)",this->urlStr,this->type,this->deep);
		db->exec(buf);
	}
};

#endif
