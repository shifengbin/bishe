#include <stdio.h>
#include <arpa/inet.h>

#include "./ConfigParser/configparser.h"
#include "./URLManager/URLManager.h"
#include "./URL/URL.h"
#include "./TaskControl/TaskControl.h"
#include "./log/mylog.h"
#include "./dns/DNSCache.h"
#include "./Download/Download.h"


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
	//TaskControl tasks( config->getJobNum() , test );
	URL *tUrl = NULL;


	while( 1 )
	{
		urlm->loadURL();
		if (!tasks.getCurrentRun() && !urlm->getCurrentSize() )
		{
			puts("END");
			break;
		}
		
		//printf("run:%d count:%d\n",tasks.getCurrentRun(),urlm->getCurrentSize());
		if ( tasks.isAllTaskDone() )
		{
			for ( int i = 0 ; i < config->getJobNum() && (tUrl = urlm->popURL()) !=NULL; i++)
			{
				//puts("addTask");
				tasks.addTaskToQueue( tUrl);
			}
		}

		if ( config->getDuration() != 0 )
		{
			sleep(config->getDuration());
		}
		else
		{
			sleep(1);
		}

	}
	
	
	return 0;
}
