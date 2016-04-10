#include <stdlib.h>
#include "../Persistence/Persistence.h"
#include "URLManager.h"
#include "../ConfigParser/configparser.h"

#define ID     "id"
#define URLSTR "urlstr"
#define TYPE   "type"
#define DEEP   "deep"
#define STATE  "state"


URLManager *URLManager::um = NULL;
//Queue<URL> urlQue;

int load( void *um , int count, char **vals ,char **colname)
{
	int i;
	Queue<URL>* que = (Queue<URL>*)um;
	URL *temp = new URL;
	if ( temp == NULL )
	{
		return -1;
	}

	for( i = 0; i < count; i++)
	{
		if ( !strcasecmp( ID ,colname[i]) )
		{
			temp->setId(atoi(vals[i]));
		} 
		else if ( !strcasecmp( URLSTR , colname[i]) )
		{
			temp->setURLStr( vals[i] );
		}
		else if ( !strcasecmp( TYPE , colname[i]) )
		{
			temp->setType( atoi( vals[i] ) );	
		}
		else if ( !strcasecmp( DEEP , colname[i]) )
		{
			temp->setState( atoi( vals[i] ) );
		}
		else if ( !strcasecmp( STATE , colname[i] ) )
		{
			temp->setState( atoi( vals[i] ) );
		}
//		puts(vals[i]);
	}
	que->push( temp );

	return 0;	
}


URLManager::URLManager()
{
	ConfigParser *config = ConfigParser::getConfigParser();
	this->urlQue = new Queue<URL>(config->getMethod());
}

URLManager::~URLManager()
{
	delete urlQue;
}

URLManager* URLManager::getURLManager()
{
	if ( um == NULL )
	{
		um = new URLManager();
	}
	return um;
}

int URLManager::getCurrentSize()
{
	return urlQue->getCount();
}

int URLManager::loadURL()
{
	int length = urlQue->getCount();
	int loadcount;
	Persistence *db;
	char sql[512] = { 0 };

	if ( length < URLLESSIZE )
	{
		//here need load url
		loadcount = URLMAXSIZE - length;
		db = Persistence::getPersistence();
		
		if ( db == NULL )
		{
			return -1;
		}
		sprintf(sql,"select * from url where state=0 limit %d",loadcount);
		db->query(sql,load,this->urlQue);
	}
		//nothing
	return 0;
}

URL* URLManager::popURL()
{
	return urlQue->pop();
}
