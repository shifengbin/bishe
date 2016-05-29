#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

#include "./ConfigParser/configparser.h"
#include "./URLManager/URLManager.h"
#include "./URL/URL.h"
#include "./TaskControl/TaskControl.h"
#include "./log/mylog.h"
#include "./dns/DNSCache.h"
#include "./Download/Download.h"
#include "./HTTP/HTTP.h"

#include "./parserurl/URLParser.h"


int main()
{

	ConfigParser *config = ConfigParser::getConfigParser();
	if ( config == NULL )
	{
		mylog( ERROR, "Config Error!");
		return -1;
	}

	URLManager *urlm = URLManager::getURLManager();
	if ( urlm == NULL )
	{
		mylog( ERROR, "URLManager Error!");
		return -1;
	}
	
	TaskControl tasks( config->getJobNum() , download );
	URL *tUrl = NULL;


	while( 1 )
	{
		urlm->loadURL();
		if (!tasks.getCurrentRun() && !urlm->getCurrentSize() )
		{
			puts("END");
			break;
		}
		
		if ( tasks.isAllTaskDone() )
		{
			for ( int i = 0 ; i < config->getJobNum() && (tUrl = urlm->popURL()) !=NULL; i++)
			{
				tasks.addTaskToQueue( tUrl);
			}
		}

		if ( config->getDuration() != 0 )
		{
			sleep(config->getDuration());
		}
		else
		{
			sleep(2);
		}

	}
	
	
	return 0;
}
