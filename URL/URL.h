#ifndef __URL_H__
#define __URL_H__
#include <unistd.h>
#include <stdio.h>
#include <string.h>




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
};

#endif
